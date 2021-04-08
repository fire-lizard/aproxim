#include "xls_table.h"

QString osVersion()
{
#ifdef Q_OS_LINUX
    return "Linux";
#else
#ifdef Q_OS_DARWIN
    return "Mac OS X";
#else
#ifdef Q_OS_WIN
    return "Windows";
#else
    return "Other";
#endif
#endif
#endif
}

#ifdef WIN32

QList<QVariantList> XLS_Table::openXLS(QString name)
{
    //Создаем объект Excel.Application
    QAxObject * excel = new QAxObject( "Excel.Application", nullptr );
    //Выбрасываем исключение, если объект application_ невалидный
    //if( !excel ) throw std::exception( "Excel.Application" );
    //После этого Excel перестает выбрасывать предупреждения
    excel->dynamicCall( "SetDisplayAlerts", QVariant( false ) );
    //Создаем объект Workbooks (коллекция книг)
    QAxObject * workbooks = excel->querySubObject( "Workbooks" );
    //Выбрасываем исключение, если объект workbooks невалидный
    //if( !workbooks ) throw std::exception( "Application.Workbooks" );

    QAxObject* workbook = workbooks->querySubObject( "Open(const QString&)", QString(name.replace('/', '\\')) );
    //Получаем доступ к активному листу
    QAxObject * worksheets = workbook->querySubObject( "Sheets" );
    const int xlWorksheet =-4167;
    const int count = worksheets->property("Count").toInt();
    QAxObject * worksheet = nullptr;
    for (int index = 1; index <= count; index++)
    {
        worksheet = worksheets->querySubObject( "Item(QVariant)", QVariant(index) );
        //Выбрасываем исключение, если объект worksheet невалидный
        //if( !worksheet ) throw std::exception( "Workbook.ActiveSheet" );
        if (worksheet->property("Type").toInt() == xlWorksheet)
        {
            break;
        }
    }

    QList<QVariantList> result = getRowValues(worksheet);

    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");
    delete excel;
    return result;
}

void XLS_Table::saveXLS(QString name, vector<point> &data)
{
    //Создаем объект Excel.Application
    QAxObject * excel = new QAxObject( "Excel.Application", nullptr );
    //Выбрасываем исключение, если объект application_ невалидный
    //if( !excel ) throw std::exception( "Excel.Application" );
    //Устанавливаем количество листов на новой книге равным 1
    excel->dynamicCall( "SetSheetsInNewWorkbook(int)", QVariant( 1 ) );
    //После этого Excel перестает выбрасывать предупреждения
    excel->dynamicCall( "SetDisplayAlerts", QVariant( false ) );
    //Создаем объект Workbooks (коллекция книг)
    QAxObject * workbooks = excel->querySubObject( "Workbooks" );
    //Выбрасываем исключение, если объект workbooks невалидный
    //if( !workbooks ) throw std::exception( "Application.Workbooks" );
    //Добавляем новую книгу
    QAxObject * workbook = workbooks->querySubObject( "Add()" );
    //Выбрасываем исключение, если объект workbook невалидный
    //if( !workbook ) throw std::exception( "Workbooks.Add()" );
    //Получаем доступ к активному листу
    QAxObject * worksheet = workbook->querySubObject( "ActiveSheet" );
    //Выбрасываем исключение, если объект worksheet невалидный
    //if( !worksheet ) throw std::exception( "Workbook.ActiveSheet" );

    setRowValues(worksheet, data);

    createChart(excel, workbook, worksheet, data);

    workbook->dynamicCall( "SaveAs(QVariant)", QVariant(name.replace('/', '\\')) );
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");
    delete excel;
}

void XLS_Table::createChart(QAxObject *excel, QAxObject *workbook, QAxObject *worksheet, vector<point> &data)
{
    //Создаем объект Charts (коллекция областей диаграмм)
    QAxObject * charts = workbook->querySubObject( "Charts" );
    //Выбрасываем исключение, если объект charts невалидный
    //if( !charts ) throw std::exception( "Workbook.Charts" );
    //Добавляем новую область диаграмм
    QAxObject * chart = charts->querySubObject( "Add()" );
    //Выбрасываем исключение, если объект chart невалидный
    //if( !chart ) throw std::exception( "Charts.Add()" );
    //Устанавливаем тип области диаграмм
    chart->dynamicCall( "ChartType", QVariant( "xlXYScatter" ) );

    //Получаем доступ к текущему ряду области диаграмм
    QAxObject * series = chart->querySubObject( "SeriesCollection(const QVariant&)", QVariant( 1 ) );
    //Выбрасываем исключение, если объект series невалидный
    //if( !series ) throw std::exception( "SeriesCollection(const QVariant&)" );

    const double version = strtod(excel->property("Version").toString().split('.')[0].toStdString().c_str(), nullptr);
    if (version >= 12)
    {
        chart->querySubObject( "SeriesCollection(const QVariant&)", QVariant( 2 ) )->dynamicCall("Delete()");
    }

    const int count = data.size();
    QAxObject * x1 = worksheet->querySubObject( "Cells( int, int )", 1, 1 );
    QAxObject * x2 = worksheet->querySubObject( "Cells( int, int )", count, 1 );
    QAxObject * y1 = worksheet->querySubObject( "Cells( int, int )", 1, 2 );
    QAxObject * y2 = worksheet->querySubObject( "Cells( int, int )", count, 2 );
    QVariantList params;
    params.append(x1->asVariant());
    params.append(x2->asVariant());

    //Получаем объект Range для оси X в виде QVariant
    QVariant source = worksheet->dynamicCall( "Range(const QVariant&, const QVariant&)", params );
    //Устанавливаем диапазон значаний X для ряда
    series->dynamicCall( "XValues", source );
    //Получаем объект Range для оси Y в виде QVariant
    params.clear();
    params.append(y1->asVariant());
    params.append(y2->asVariant());
    source = worksheet->dynamicCall( "Range(const QVariant&, const QVariant&)", params );
    //Устанавливаем диапазон значаний Y для ряда
    series->dynamicCall( "Values", source );
}

QList<QVariantList> XLS_Table::getRowValues( QAxObject * worksheet )
{
    QList<QVariantList> data;	//Data list from excel, each QVariantList is worksheet row
    bool isEmpty;	//when all the cells of row are empty, it means that file is at end (of course, it maybe not right for different excel files. it's just criteria to calculate somehow row count for my file)
    int row = 0;

    do
    {
        QVariantList dataRow;
        isEmpty = true;
        row++;
        for (int column = 1; column <= 2; column++)
        {
            QAxObject* cell = worksheet->querySubObject("Cells( int, int )", row, column);
            QString value = cell->property("Value").toString();
            if (!value.isEmpty() && isEmpty)
            {
                isEmpty = false;
            }
            dataRow.append(value);
        }
        data.append(dataRow);
    }
    while (!isEmpty);
    return data;
}

void XLS_Table::setRowValues( QAxObject * worksheet, vector<point> data )
{
    const int count = data.size();
    for (int index = 0; index < count; index++)
    {
        worksheet->querySubObject( "Cells( int, int )", index + 1, 1 )->dynamicCall("SetValue", QVariant(data[index].x));
        worksheet->querySubObject( "Cells( int, int )", index + 1, 2 )->dynamicCall("SetValue", QVariant(data[index].y));
    }
}

XLS_Table::XLS_Table() = default;

#endif
