#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::quitClick()
{
    this->close();
}

void MainWindow::aboutClick()
{
    QMessageBox::about(this, "About", "Approximator 1.9. Author - Anatoly Sova.");
}

void MainWindow::newClick() const
{
    for (int i = 0;i < ui->data_table->columnCount();i++)
    {
        for (int j = 0;j < ui->data_table->rowCount();j++)
        {
            QTableWidgetItem *item = ui->data_table->item(j, i);
            if (item) item->setText("");
        }
    }
}

void MainWindow::openClick()
{
    QFileDialog sdialog(this);
    QStringList filters;
    filters << "Text files (*.txt)" << "CSV files (*.csv)" << "XML files (*.xml)" << "JSON files (*.json)";
#ifdef WIN32
    filters << "Microsoft Excel 2003 files (*.xls)" << "Microsoft Excel files (*.xlsx)";
#endif
    sdialog.setNameFilters(filters);
    sdialog.setAcceptMode(QFileDialog::AcceptOpen);
    if (sdialog.exec() == QDialog::Accepted)
    {
    	const QString filename = sdialog.selectedFiles()[0];
	    const QString selected_filter = sdialog.selectedNameFilter();
        if (selected_filter == "Text files (*.txt)")
        {
            QFile file(filename);
			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
				return;
			int index = 0;
            while (!file.atEnd())
            {
				QString str = file.readLine();
				QStringList values = str.split('\t');
				if (values.count() == 2)
				{
					ui->data_table->setItem(index, 0, new QTableWidgetItem(values[0]));
					ui->data_table->setItem(index, 1, new QTableWidgetItem(values[1]));
				}
                index++;
            }
            file.close();
        }
		else if (selected_filter == "CSV files (*.csv)")
		{
			QFile file(filename);
			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
				return;
			int index = 0;
			while (!file.atEnd())
			{
				QString str = file.readLine();
				QStringList values = str.split(',');
				if (values.count() == 2)
				{
					ui->data_table->setItem(index, 0, new QTableWidgetItem(values[0]));
					ui->data_table->setItem(index, 1, new QTableWidgetItem(values[1]));
				}
				index++;
			}
			file.close();
		}
		else if (selected_filter == "XML files (*.xml)")
		{
			QFile file(filename);
			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
				return;
			const QByteArray xml_data = file.readAll();
			QXmlStreamReader *reader = new QXmlStreamReader(xml_data);
			int index = 0;
			while (!reader->atEnd())
			{
				if (reader->readNext() == QXmlStreamReader::StartElement && 
					(reader->name() == "X" || reader->name() == "Y"))
				{
					const int column = reader->name() == "X" ? 0 : 1;
					const QString value = reader->readElementText();
					ui->data_table->setItem(index, column, new QTableWidgetItem(value));
					if (reader->name() == "Y")
					{
						index++;
					}
				}
			}
			file.close();
		}
		else if (selected_filter == "JSON files (*.json)")
		{
			QFile file(filename);
			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
				return;
			const QByteArray json_data = file.readAll();
			QJsonParseError jerror{};
			QJsonDocument jdoc = QJsonDocument::fromJson(json_data, &jerror);
			if (jerror.error != QJsonParseError::NoError)
			{
				QMessageBox::about(this, "Error", jerror.errorString());
				return;
			}
			QJsonObject json_obj = jdoc.object();
			QJsonArray json_array = json_obj.value("Data").toArray();
			int index = 0;
			for (const QJsonValueRef &item : json_array)
			{
				auto keys = item.toObject().keys();
				const QString x = item.toObject().value("X").toString();
				const QString y = item.toObject().value("Y").toString();
				ui->data_table->setItem(index, 0, new QTableWidgetItem(x));
				ui->data_table->setItem(index, 1, new QTableWidgetItem(y));
				index++;
			}
			file.close();
		}
#ifdef WIN32
        else if (selected_filter == "Microsoft Excel 2003 files (*.xls)" ||
				 selected_filter == "Microsoft Excel files (*.xlsx)")
		{
			QList<QVariantList> list = XLS_Table::openXLS(filename);
			const int count = list.count();
			for (int index = 0; index < count; index++)
			{
				QStringList values;
				values.append(list[index][0].toString());
				values.append(list[index][1].toString());
				ui->data_table->setItem(index, 0, new QTableWidgetItem(values[0]));
				ui->data_table->setItem(index, 1, new QTableWidgetItem(values[1]));
			}
		}
#endif
    }
}

void MainWindow::saveClick()
{
    QFileDialog sdialog(this);
    QStringList filters;
    filters << "Text files (*.txt)" << "CSV files (*.csv)" << "XML files (*.xml)" << "JSON files (*.json)";
#ifdef WIN32
    filters << "Microsoft Excel 2003 files (*.xls)" << "Microsoft Excel files (*.xlsx)";
#endif
    sdialog.setNameFilters(filters);
    sdialog.setAcceptMode(QFileDialog::AcceptSave);
    if (sdialog.exec() == QFileDialog::Accepted)
    {
	    const QString filename = sdialog.selectedFiles()[0];
	    const QString selected_filter = sdialog.selectedNameFilter();
        if (selected_filter == "Text files (*.txt)")
        {
            QFile file(filename);
			if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
				return;
			char t = '\t';
            char n = '\n';
            string str_x;
            string str_y;
            int index = -1;
            do
            {
                index++;
                QTableWidgetItem *item_x = ui->data_table->item(index, 0);
                QTableWidgetItem *item_y = ui->data_table->item(index, 1);
                if (item_x && item_y)
                {
                    str_x = item_x->text().toStdString();
                    str_y = item_y->text().toStdString();
                }
                else
                {
                    str_x = "";
                    str_y = "";
                }
                if (!str_x.empty() && !str_y.empty())
                {
                    file.write(str_x.c_str(), str_x.length());
					file.write(&t, 1);
					file.write(str_y.c_str(), str_y.length());
					file.write(&n, 1);
                }
            }
            while (!str_x.empty() && !str_y.empty());
            file.close();
        }
		else if (selected_filter == "CSV files (*.csv)")
		{
			QFile file(filename);
			if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
				return;
			char t = ',';
			char n = '\n';
			string str_x;
			string str_y;
			int index = -1;
			do
			{
				index++;
				QTableWidgetItem *item_x = ui->data_table->item(index, 0);
				QTableWidgetItem *item_y = ui->data_table->item(index, 1);
				if (item_x && item_y)
				{
					str_x = item_x->text().toStdString();
					str_y = item_y->text().toStdString();
				}
				else
				{
					str_x = "";
					str_y = "";
				}
				if (!str_x.empty() && !str_y.empty())
				{
					file.write(str_x.c_str(), str_x.length());
					file.write(&t, 1);
					file.write(str_y.c_str(), str_y.length());
					file.write(&n, 1);
				}
			}
			while (!str_x.empty() && !str_y.empty());
			file.close();
		}
		else if (selected_filter == "XML files (*.xml)")
		{
			QFile file(filename);
			if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
				return;
			QString *xml_data = new QString();
			QXmlStreamWriter *writer = new QXmlStreamWriter(xml_data);
			writer->setAutoFormatting(true);
			writer->writeStartDocument();
			writer->writeStartElement("Data");
			QString str_x;
			QString str_y;
			int index = -1;
			do
			{
				index++;
				QTableWidgetItem *item_x = ui->data_table->item(index, 0);
				QTableWidgetItem *item_y = ui->data_table->item(index, 1);
				if (item_x && item_y)
				{
					str_x = item_x->text();
					str_y = item_y->text();
				}
				else
				{
					str_x = "";
					str_y = "";
				}
				if (str_x != "" && str_y != "")
				{
					writer->writeTextElement("X", str_x);
					writer->writeTextElement("Y", str_y);
				}
			}
			while (str_x != "" && str_y != "");
			writer->writeEndElement();
			writer->writeEndDocument();
			file.write(xml_data->toStdString().c_str(), xml_data->length());
			file.close();
		}
		else if (selected_filter == "JSON files (*.json)")
		{
			QFile file(filename);
			if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
				return;
			QJsonObject json_obj;
			QJsonArray json_array;
			QString str_x;
			QString str_y;
			int index = -1;
			do
			{
				index++;
				QTableWidgetItem *item_x = ui->data_table->item(index, 0);
				QTableWidgetItem *item_y = ui->data_table->item(index, 1);
				if (item_x && item_y)
				{
					str_x = item_x->text();
					str_y = item_y->text();
				}
				else
				{
					str_x = "";
					str_y = "";
				}
				if (str_x != "" && str_y != "")
				{
					QJsonObject value;
					value["X"] = str_x.toStdString().c_str();
					value["Y"] = str_y.toStdString().c_str();
					json_array.append(value);
				}
			} while (str_x != "" && str_y != "");
			json_obj["Data"] = json_array;
			QJsonDocument json_doc(json_obj);
			QString json_string = json_doc.toJson();
			file.write(json_string.toStdString().c_str(), json_string.length());
			file.close();
		}
#ifdef WIN32
		else if (selected_filter == "Microsoft Excel 2003 files (*.xls)" ||
				 selected_filter == "Microsoft Excel files (*.xlsx)")
		{
			QVector <QPointF> src_data;
			string str_x;
			string str_y;
			int index = -1;
			do
			{
				index++;
				QTableWidgetItem *item_x = ui->data_table->item(index, 0);
				QTableWidgetItem *item_y = ui->data_table->item(index, 1);
				if (item_x && item_y)
				{
					str_x = item_x->text().replace(',', '.').toStdString();
					str_y = item_y->text().replace(',', '.').toStdString();
				}
				else
				{
					str_x = "";
					str_y = "";
				}
				if (!str_x.empty() && !str_y.empty())
				{
					const double x = strtod(str_x.c_str(), nullptr);
					const double y = strtod(str_y.c_str(), nullptr);
					src_data.push_back(QPointF(x, y));
				}
			}
			while (!str_x.empty() && !str_y.empty());
			XLS_Table::saveXLS(filename, src_data);
		}
#endif
	}
}

void MainWindow::differentialClick() const
{
	QVector <QPointF> src_data;
	string str_x;
    string str_y;
    int index = -1;
    do
    {
        index++;
        QTableWidgetItem *item_x = ui->data_table->item(index, 0);
        QTableWidgetItem *item_y = ui->data_table->item(index, 1);
        if (item_x && item_y)
        {
            str_x = item_x->text().replace(',', '.').toStdString();
            str_y = item_y->text().replace(',', '.').toStdString();
        }
        else
        {
            str_x = "";
            str_y = "";
        }
        if (!str_x.empty() && !str_y.empty())
        {
	        const double x = strtod(str_x.c_str(), nullptr);
	        const double y = strtod(str_y.c_str(), nullptr);
            src_data.push_back(QPointF(x,y));
        }
    }
    while (!str_x.empty() && !str_y.empty());
    for (int idx = 0;idx < src_data.size();idx++)
    {
	    const double val = DataAnalysis::LagrangeD(src_data, src_data[idx].x());
        ui->data_table->item(idx, 1)->setText(QString::number(val));
    }
}

void MainWindow::integralClick() const
{
    QVector <QPointF> src_data;
	string str_x;
    string str_y;
    int index = -1;
    do
    {
        index++;
        QTableWidgetItem *item_x = ui->data_table->item(index, 0);
        QTableWidgetItem *item_y = ui->data_table->item(index, 1);
        if (item_x && item_y)
        {
            str_x = item_x->text().replace(',', '.').toStdString();
            str_y = item_y->text().replace(',', '.').toStdString();
        }
        else
        {
            str_x = "";
            str_y = "";
        }
        if (!str_x.empty() && !str_y.empty())
        {
	        const double x = strtod(str_x.c_str(), nullptr);
	        const double y = strtod(str_y.c_str(), nullptr);
            src_data.push_back(QPointF(x, y));
        }
    }
    while (!str_x.empty() && !str_y.empty());
    for (int idx = 0;idx < src_data.size();idx++)
    {
	    const double val = DataAnalysis::Simpson(0, src_data[idx].x(), src_data);
        ui->data_table->item(idx, 1)->setText(QString::number(val));
    }
}

void MainWindow::calculatePointClick()
{
	const unsigned char f = ui->selected_function->currentIndex() + 1;
    func deps[17] = {Func1,Func2,Func3,Func4,Func5,Func6,Func7,Func8,
        Func9,Func10,Func11,Func12,Func13,Func14,Func15,Func16,Func17};
	double y1 = 0;
	const double precision = pow((double)10, ui->selected_precision->value());
    ui->value_x->text().replace(',', '.');
	const double x1 = strtod(ui->value_x->text().toStdString().c_str(), nullptr);
    if (ui->selected_function->currentIndex() <= 0)
    {
        y1 = deps[0](_a1, _b1, x1);
    }
    else
    {
        if (f < 18)
        {
            y1 = deps[ui->selected_function->currentIndex()](_a1, _b1, x1);
        }
        else
        {
            if (f == 18)
            {
                y1 = Func18(_a1, _b1, x1, _n0);
            }
            if (f == 19)
            {
                y1 = Func19(_mbx, x1, _n0);
            }
            if (f == 20)
            {
                y1 = Func20(_a1, _b1, _b2, x1);
            }
        }
    }
    y1 = floor(y1 * precision);
    y1 /= precision;
    ui->value_y->setText(QString::number(y1));
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void MainWindow::optionsClick()
{
    options *opts = new options();
    opts->exec();
    if (opts->result() == QDialog::Accepted)
    {
		_chartType = opts->chartType();
    }
	delete opts;
}

void MainWindow::approximateClick()
{
    QVector<QPointF> src_data;
    QVector<QPointF> linear_data;
    QVector<QPointF> dst_data;
    vector<QVector<QVector3D>> linear_data_2;
    double delta = 0;
    double sigma = 0;
    double r = 0;
    double nu = 0;
	const unsigned char f = ui->selected_function->currentIndex() + 1;
	const double precision = pow((double)10, ui->selected_precision->value());
	src_data.clear();
    linear_data.clear();
    dst_data.clear();
    linear_data_2.clear();
    string str_x;
    string str_y;
    int index = -1;
    do
    {
        index++;
        QTableWidgetItem *item_x = ui->data_table->item(index, 0);
        QTableWidgetItem *item_y = ui->data_table->item(index, 1);
        if (item_x && item_y)
        {
            str_x = item_x->text().replace(',', '.').toStdString();
            str_y = item_y->text().replace(',', '.').toStdString();
        }
        else
        {
            str_x = "";
            str_y = "";
        }
        if (!str_x.empty() && !str_y.empty())
        {
	        const double x = strtod(str_x.c_str(), nullptr);
	        const double y = strtod(str_y.c_str(), nullptr);
            src_data.push_back(QPointF(x, y));
        }
    }
    while (!str_x.empty() && !str_y.empty());
    if (f == 18 || f == 19)
    {
		_n0 = static_cast<signed char>(QInputDialog::getInt(this, tr("Input power of N"), "", 1));
	}
	const int row = CalculateData(src_data, dst_data, _a1, _b1, _b2, _n0, _mbx, f);
    if (row != 0)
    {
        if (row == -1)
        {
            QMessageBox::about(this, "Error", "Solution not found");
        }
        if (row > 0)
        {
            QMessageBox::about(this, "Error", "Division by zero in row " + QString::number(row));
        }
        return;
    }
	_data_x.clear();
	_data_x.resize(src_data.size());
	_data_y.clear();
	_data_y.resize(src_data.size());
	_data_y1.clear();
	_data_y1.resize(src_data.size());
    int idx = 0;
    for (auto& index_src : src_data)
    {
		_data_x[idx] = index_src.x();
		_data_y[idx] = index_src.y();
        idx++;
    }
    idx = 0;
    for (auto& index_dst : dst_data)
    {
		_data_y1[idx] = index_dst.y();
        double value = index_dst.y();
        value = floor(value * precision);
        value /= precision;
        ui->data_table->setItem(idx, 2, new QTableWidgetItem(QString::number(value).replace(',', '.')));
        idx++;
    }
    for (int index_diff = 0;index_diff < src_data.size();index_diff++)
    {
        double d = 100 * abs(src_data[index_diff].y() - dst_data[index_diff].y());
        d /= src_data[index_diff].y();
        d = floor(d * precision);
        d /= precision;
        ui->data_table->setItem(index_diff, 3, new QTableWidgetItem(QString::number(d).replace(',', '.')));
    }
	QChart *chart;
	QScatterSeries *series1 = new QScatterSeries(this);
	QLineSeries *series2 = new QLineSeries(this);
	QVector<QPointF> graph_src_data(src_data);
	QVector<QPointF> graph_dst_data(dst_data);
	if (_chartType == 0)
	{
		chart = new QChart();
	}
	else
	{
		chart = new QPolarChart();
		for (int graphIndex = 0; graphIndex < src_data.size(); graphIndex++)
		{
			double ro = sqrt(pow(src_data[graphIndex].x(), 2) + pow(src_data[graphIndex].y(), 2));
			double fi = sqrt(src_data[graphIndex].x() == 0 ? M_PI_2 : atan(src_data[graphIndex].y() / src_data[graphIndex].x()));
			graph_src_data[graphIndex].setX(ro);
			graph_src_data[graphIndex].setY(fi);
			ro = sqrt(pow(dst_data[graphIndex].x(), 2) + pow(dst_data[graphIndex].y(), 2));
			fi = sqrt(dst_data[graphIndex].x() == 0 ? M_PI_2 : atan(dst_data[graphIndex].y() / dst_data[graphIndex].x()));
			graph_dst_data[graphIndex].setX(ro);
			graph_dst_data[graphIndex].setY(fi);
		}
	}
	for (int pointIndex = 0; pointIndex < src_data.size(); pointIndex++)
	{
		series1->append(graph_src_data[pointIndex]);
		series2->append(graph_dst_data[pointIndex]);
	}
	chart->addSeries(series1);
	chart->addSeries(series2);
	chart->createDefaultAxes();
	ui->data_plot->setChart(chart);
	CalculateCoefficients(src_data, dst_data, _mbx, _n0, delta, sigma, r, nu, f);
	_b1 = floor(_b1 * precision);
	_b1 /= precision;
	_a1 = floor(_a1 * precision);
	_a1 /= precision;
    if (f <= 18 || f == 20)
    {
        ui->value_a->setText("A = " + QString::number(_b1));
        ui->value_b->setText("B = " + QString::number(_a1));
    }
    if (f == 19)
    {
        ui->value_a->setText("");
        ui->value_b->setText("");
        ui->value_b2->setText("");
        QString caption = "";
        for (unsigned char index_data = 0;index_data < abs(_n0) + 1;index_data++)
        {
            caption += "B";
            caption += QString::number(index_data);
            caption += " = ";
			_mbx[index_data] = floor(_mbx[index_data] * precision);
			_mbx[index_data] /= precision;
            caption += QString::number(_mbx[index_data]);
            caption += ";";
        }
        ui->value_a->setText(caption);
    }
    if (f == 20)
    {
		_b2 = floor(_b2 * precision);
		_b2 /= precision;
        ui->value_b2->setText("B2 = " + QString::number(_b2));
    }
    delta = floor(delta * precision);
    delta /= precision;
    ui->value_ad->setText(tr("Average deviation: ") + QString::number(delta));
    sigma = floor(sigma * precision);
    sigma /= precision;
    ui->value_aqd->setText(tr("Mean-square deviation: ") + QString::number(sigma));
    r = floor(r * precision);
    r /= precision;
    nu = floor(nu * precision);
    nu /= precision;
    if (f <= 18 || f == 20)
    {
        ui->value_cc->setText(tr("Correlation coefficient: ") + QString::number(r));
    }
    if (f == 19)
    {
        ui->value_cc->setText(tr("Correlation ratio: ") + QString::number(nu));
    }
}

void MainWindow::on_data_table_cellActivated(int row, int column) const
{
    if (row == ui->data_table->rowCount() - 1)
    {
        ui->data_table->setRowCount(ui->data_table->rowCount() + 1);
    }
}

void MainWindow::on_data_table_cellChanged(int row, int column) const
{
    if (row == ui->data_table->rowCount() - 1)
    {
        ui->data_table->setRowCount(ui->data_table->rowCount() + 1);
    }
}

void MainWindow::findModelClick() const
{
	// TEST - FILLING DATA
	/*for (int idx = 1; idx <= 100; idx++)
	{
		ui->data_table->setItem(idx - 1, 0, new QTableWidgetItem(QString::number(idx)));
		ui->data_table->setItem(idx - 1, 1, new QTableWidgetItem(QString::number(pow(idx, 2))));
	}*/
	QVector<QPointF> src_data;
	QVector<QPointF> linear_data;
	QVector<QPointF> dst_data;
	vector<QVector<QVector3D>> linear_data_2;
	src_data.clear();
	linear_data.clear();
	dst_data.clear();
	linear_data_2.clear();
	string str_x;
	string str_y;
	int index = -1;
	do
	{
		index++;
		QTableWidgetItem *item_x = ui->data_table->item(index, 0);
		QTableWidgetItem *item_y = ui->data_table->item(index, 1);
		if (item_x && item_y)
		{
			str_x = item_x->text().replace(',', '.').toStdString();
			str_y = item_y->text().replace(',', '.').toStdString();
		}
		else
		{
			str_x = "";
			str_y = "";
		}
		if (!str_x.empty() && !str_y.empty())
		{
			const double x = strtod(str_x.c_str(), nullptr);
			const double y = strtod(str_y.c_str(), nullptr);
			src_data.push_back(QPointF(x,y));
		}
	}
	while (!str_x.empty() && !str_y.empty());
	if (src_data.empty()) return;
	unsigned char func = Epsilon(src_data);
	/*
	Epsilon = 1 -> 1
	Epsilon = 2 -> 7
	Epsilon = 3 -> 12
	Epsilon = 4 -> 9
	Epsilon = 5 -> 3
	Epsilon = 6 -> 2
	Epsilon = 7 -> 10
	*/
	switch (func)
	{
		case 2:func = 7;break;
		case 3:func = 12;break;
		case 4:func = 9;break;
		case 5:func = 3;break;
		case 6:func = 2;break;
		case 7:func = 10;break;
		default:func = 1;
	}
	this->ui->selected_function->setCurrentIndex(func + 1);
}