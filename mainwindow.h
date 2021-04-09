#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <vector>
#include <QtCharts/QPolarChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>

#include "approximator.h"
#include "dataanalysis.h"
#include "options.h"
#include "util.h"
#include "xls_table.h"

namespace Ui
{
class MainWindowClass;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindowClass *ui;

    double _a1{}, _b1{}, _b2{};
    vector<double> _mbx;
    signed char _n0{};
    vector<double> _data_x;
    vector<double> _data_y;
    vector<double> _data_y1;
    int _chartType{};

private slots:
    void on_data_table_cellChanged(int row, int column) const;
    void on_data_table_cellActivated(int row, int column) const;
    void approximateClick();
    void optionsClick();
    void calculatePointClick();
    void integralClick() const;
    void differentialClick() const;
    void saveClick();
    void openClick();
    void newClick() const;
    void aboutClick();
    void quitClick();
    void findModelClick() const;
    void generateClick();
    void saveImageClick();
};

#endif // MAINWINDOW_H
