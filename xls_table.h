#ifndef XLS_TABLE_H
#define XLS_TABLE_H

#ifdef WIN32_1
#include <ActiveQt/QAxObject>
#endif
#include <QtCore>
#include "common.h"

using namespace std;

/**
@author Anatoly Sova,,,
*/

class XLS_Table {

#ifdef WIN32_1
private:
    static QList<QVariantList> getRowValues( QAxObject * worksheet );
    static void createChart(QAxObject *excel, QAxObject *workbook, QAxObject *worksheet, vector<point> &data);
    static void setRowValues(QAxObject * worksheet, vector<point> data);
    XLS_Table();

public:
    static QList<QVariantList> openXLS(QString name);
    static void saveXLS(QString name, vector<point> &data);
#endif
};
#endif
