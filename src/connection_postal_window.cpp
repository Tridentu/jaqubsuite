#include "connection_postal_window.h"
#include <QToolButton>
#include <KRichTextEdit>
#include <KNotifications/KNotification>
#include <KColorButton>
#include "ui_connection_postal_window.h"

ConnectionPostalWindow::ConnectionPostalWindow(QWidget* parent, JaqubConnection* connection) : QDialog(parent) , m_Ui(new Ui::ConnectionPostalWindow), m_Connection(connection)
{
    m_Ui->setupUi(this);
    connect(m_Ui->boldButton, &QToolButton::clicked,  this, &ConnectionPostalWindow::setBold);
    connect(m_Ui->italicButton, &QToolButton::clicked,  this, &ConnectionPostalWindow::setItalic);
    connect(m_Ui->underlineButton, &QToolButton::clicked,  this, &ConnectionPostalWindow::setUnderlined);
    connect(m_Ui->alignLeft, &QToolButton::clicked,  m_Ui->messageField, &KRichTextEdit::alignLeft);
    connect(m_Ui->alignCenter, &QToolButton::clicked,  m_Ui->messageField, &KRichTextEdit::alignCenter);
    connect(m_Ui->alignRight, &QToolButton::clicked,  m_Ui->messageField, &KRichTextEdit::alignRight);
    connect(m_Ui->justifyButton, &QToolButton::clicked,  m_Ui->messageField, &KRichTextEdit::alignJustify);
    connect(m_Ui->textColor, &KColorButton::changed,  this, &ConnectionPostalWindow::setTextColor);
    connect(m_Ui->discardButton, &QToolButton::clicked,  this, &ConnectionPostalWindow::resetMessage);
    connect(m_Ui->sendButton, &QToolButton::clicked,  this, &ConnectionPostalWindow::sendMessage);

}

ConnectionPostalWindow::~ConnectionPostalWindow()
{
    
    
}

void ConnectionPostalWindow::setPlugin(JaqubPlugin* plugin)
{
    if(m_Plugin)
        disconnect(plugin, &JaqubPlugin::messageSent, this, &ConnectionPostalWindow::notifyMessageSent);
    m_Plugin = plugin;
    if(m_Plugin)
        connect(plugin, &JaqubPlugin::messageSent, this, &ConnectionPostalWindow::notifyMessageSent);

}

void ConnectionPostalWindow::notifyMessageSent(bool isError)
{
     resetMessage();
}



void ConnectionPostalWindow::resetMessage()
{
    m_Ui->messageField->clear();
    m_Bold = false;
    m_Ui->messageField->setTextBold(m_Bold);
    m_Italic = false;
    m_Ui->messageField->setTextItalic(m_Italic);
    m_Underline = false;
    m_Ui->messageField->setTextUnderline(m_Underline);
    m_Ui->messageField->setTextForegroundColor(QColor("#FFFFFF"));
    m_Ui->messageField->alignLeft();
    m_Ui->ccField->clear();
    m_Ui->bccField->clear();
    m_Ui->recipientField->clear();
    m_Ui->subjectField->clear();
    m_Ui->senderNameField->clear();
}


void ConnectionPostalWindow::sendMessage()
{
    QMap<QString, QString> messageData;
    if(m_Ui->recipientField->text().isEmpty())
        return;
    messageData.insert("recipient", m_Ui->recipientField->text());
    if(!m_Ui->ccField->text().isEmpty())
        messageData.insert("recipientCC", m_Ui->ccField->text());
    if(!m_Ui->bccField->text().isEmpty())
        messageData.insert("recipientBCC", m_Ui->bccField->text());
    if(!m_Ui->subjectField->text().isEmpty())
        messageData.insert("subject", m_Ui->subjectField->text());
    else
        messageData.insert("subject", "No Subject");
    if(m_Ui->messageField->textOrHtml().isEmpty())
        return;
     if(m_Ui->senderNameField->text().isEmpty())
        return;
    messageData.insert("senderName", m_Ui->senderNameField->text());
    QString message = m_Ui->messageField->textOrHtml();
    qDebug() << "Sending message";
    if(!m_Plugin)
        return;
    m_Plugin->send(message, messageData);
}





void ConnectionPostalWindow::setTextColor(const QColor& newTextColor)
{
    m_Ui->messageField->setTextForegroundColor(newTextColor);
}




void ConnectionPostalWindow::setItalic()
{
    m_Italic = !m_Italic;
    m_Ui->messageField->setTextItalic(m_Italic);
}


void ConnectionPostalWindow::setBold()
{
    m_Bold = !m_Bold;
    m_Ui->messageField->setTextBold(m_Bold);
}



void ConnectionPostalWindow::setUnderlined()
{
    m_Underline = !m_Underline;
    m_Ui->messageField->setTextUnderline(m_Underline);
}

