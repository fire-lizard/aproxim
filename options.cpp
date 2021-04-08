#include "options.h"
#include "ui_options.h"

options::options(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::options)
{
    m_ui->setupUi(this);
    for (int index = 0; index < QStyleFactory::keys().size(); index++)
    {
        m_ui->selected_style->addItem(QStyleFactory::keys()[index]);
    }
    m_ui->selected_plot->addItem("Cartesian");
    m_ui->selected_plot->addItem("Polar");
}

options::~options()
{
    delete m_ui;
}

int options::chartType() const
{
    return m_ui->selected_plot->currentIndex();
}

void options::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void options::on_buttonBox_accepted() const
{
    QApplication::setStyle(m_ui->selected_style->itemText(m_ui->selected_style->currentIndex()));
}
