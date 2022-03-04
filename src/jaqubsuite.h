#ifndef JAQUBSUITE_H
#define JAQUBSUITE_H

#include <QMainWindow>
#include <QScopedPointer>

namespace Ui {
class jaqubsuite;
}

class jaqubsuite : public QMainWindow
{
    Q_OBJECT

public:
    explicit jaqubsuite(QWidget *parent = nullptr);
    ~jaqubsuite() override;

private:
    QScopedPointer<Ui::jaqubsuite> m_ui;
};

#endif // JAQUBSUITE_H
