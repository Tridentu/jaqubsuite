
#pragma once

#include <QDialog>
#include <QScopedPointer>
#include <jaqubsuite/jaqub_connection.h>

namespace Ui {
 class JaqubCreateConnectionDialog;   
}


class ConnectionDialog : public QDialog {
    Q_OBJECT
public:
    ConnectionDialog(QStringList names);
    ~ConnectionDialog();
public:
    static JaqubConnection* getConnection();
    QString getType();
    QString getUserName();
    QString getPassword();
    QUrl getConnectionUrl();
    
private:
    void setConnectionType(const QString& text);
    void setConnectionName();
    void setConnectionUrl();
    void setConnectionStatic();
    void setPassword();
    void setUsername();
private:
    void setupDialog();
    QScopedPointer<Ui::JaqubCreateConnectionDialog> m_ui;
    QStringList m_Names;
    static JaqubConnection* s_Connection;
    JaqubConnection m_Connection;

};
