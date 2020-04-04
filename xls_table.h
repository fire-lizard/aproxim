#ifndef XLS_TABLE_H
#define XLS_TABLE_H

#ifdef WIN32
#include <ActiveQt/QAxObject>
#endif
#include <QtCore>

using namespace std;

/**
@author Anatoly Sova,,,
*/

class XLS_Table{

#ifdef WIN32
private:
	static QList<QVariantList> getRowValues( QAxObject * worksheet );
    static void createChart(QAxObject *excel, QAxObject *workbook, QAxObject *worksheet, QVector<QPointF> &data);
    static void setRowValues(QAxObject * worksheet, QVector<QPointF> data);
	XLS_Table();

public:
	static QList<QVariantList> openXLS(QString name);
    static void saveXLS(QString name, QVector<QPointF> &data);
#endif
};
#endif