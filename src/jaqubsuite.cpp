#include "jaqubsuite.h"
#include "ui_jaqubsuite.h"

jaqubsuite::jaqubsuite(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::jaqubsuite)
{
    m_ui->setupUi(this);
}

jaqubsuite::~jaqubsuite() = default;
