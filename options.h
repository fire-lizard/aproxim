#ifndef OPTIONS_H
#define OPTIONS_H

#include <QtWidgets/QtWidgets>
#include <qobjectdefs.h>

#include "mainwindow.h"

namespace Ui {
class options;
}

class options : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(options)
public:
    explicit options(QWidget *parent = nullptr);
    virtual ~options();
    int chartType() const;

protected:
    void changeEvent(QEvent *e) override;

private:
    Ui::options *m_ui;

private slots:
    void on_buttonBox_accepted() const;
};

#endif // OPTIONS_H
