

#include "ui_connection_dialog.h"
#include "connection_dialog.h"



JaqubConnection* ConnectionDialog::s_Connection = nullptr;



ConnectionDialog::ConnectionDialog(QStringList names) : m_ui(new Ui::JaqubCreateConnectionDialog), m_Names(names), m_Connection(JaqubConnection())
{
  
  setupDialog();   
}

ConnectionDialog::~ConnectionDialog()
{
    
}


void ConnectionDialog::setupDialog()
{
    m_ui->setupUi(this);
    m_ui->connectionTypeCB->addItems(m_Names);
    connect(m_ui->connectionTypeCB, &KHistoryComboBox::currentTextChanged, this, &ConnectionDialog::setConnectionType);
    connect(m_ui->connectionNameField, &KTextEdit::textChanged, this, &ConnectionDialog::setConnectionName);
    connect(m_ui->connectionUriField, &KLineEdit::textChanged, this, &ConnectionDialog::setConnectionUrl);
    connect(m_ui->passwordField, &KLineEdit::textChanged, this, &ConnectionDialog::setPassword);
    connect(m_ui->usernameField, &KLineEdit::textChanged, this, &ConnectionDialog::setUsername);
    connect(m_ui->buttonBox, &QDialogButtonBox::accepted, this, &ConnectionDialog::setConnectionStatic);
    m_Connection.connectionType = m_ui->connectionTypeCB->currentText();
}

void ConnectionDialog::setConnectionName()
{
    m_Connection.name = m_ui->connectionNameField->toPlainText();
}


void ConnectionDialog::setConnectionStatic()
{
    s_Connection = &m_Connection;
}


void ConnectionDialog::setConnectionUrl()
{
    m_Connection.connectionUri = QUrl(m_ui->connectionUriField->text());
}

QString ConnectionDialog::getUserName()
{
    return m_Connection.username;
}

QString ConnectionDialog::getPassword()
{
    return m_Connection.password;
}


QUrl ConnectionDialog::getConnectionUrl()
{
    return m_Connection.connectionUri;
}




JaqubConnection* ConnectionDialog::getConnection()
{
    return s_Connection;
}

void ConnectionDialog::setPassword()
{
    m_Connection.password = m_ui->passwordField->text();
}

void ConnectionDialog::setUsername()
{
    m_Connection.username = m_ui->usernameField->text();
}

void ConnectionDialog::setConnectionType(const QString& text)
{
    m_Connection.connectionType = text;
}

QString ConnectionDialog::getType()
{
    return m_Connection.connectionType;
}


