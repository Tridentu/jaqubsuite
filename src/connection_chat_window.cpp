#include "connection_chat_window.h"
#include "ui_connection_chat_window.h"


ConnectionChatWindow::ConnectionChatWindow(QWidget* parent, JaqubConnection* connection) : QDialog(parent), m_ui(new Ui::ConnectionChatWindow), m_Connection(connection)
{
    m_ui->setupUi(this);
}

ConnectionChatWindow::~ConnectionChatWindow()
{
    
}





