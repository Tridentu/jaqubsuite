

#pragma once

#include <QDialog>
#include <jaqubsuite/jaqub_connection.h>

namespace Ui {
     class ConnectionChatWindow;
}

class ConnectionChatWindow : public QDialog {
    Q_OBJECT
public:
    ConnectionChatWindow(QWidget* parent, JaqubConnection* connection);
    ~ConnectionChatWindow();
private:
    JaqubConnection* m_Connection;
    QScopedPointer<Ui::ConnectionChatWindow> m_ui;
    
};
