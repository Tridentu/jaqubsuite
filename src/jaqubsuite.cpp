#include "jaqubsuite.h"
#include "ui_jaqubsuite.h"
#include <QApplication>
#include <QAction>
#include <KStandardAction>
#include <KNotification>
#include <KLocalizedString>
#include <KActionCollection>
#include "connection_dialog.h"
#include "connection_chat_window.h"
#include "connection_postal_window.h"

JaqubSuiteWindow::JaqubSuiteWindow(QWidget *parent) :
    KXmlGuiWindow(parent),
    m_ui(new Ui::jaqubsuite)
{
    m_ui->setupUi(this);
    KStandardAction::quit(qApp, &QCoreApplication::quit, actionCollection());
    KStandardAction::openNew(this, &JaqubSuiteWindow::newConnection, actionCollection());
    loadCommPlugins();
    m_Dialog = new ConnectionDialog(m_PluginNames);
    connect(m_Dialog, &ConnectionDialog::accepted, this, &JaqubSuiteWindow::addConnectionWindow);
    setupGUI(StandardWindowOption::Default, "/usr/share/kxmlgui5/jaqubsuite/JaqubSuiteui.rc");
    
}

void JaqubSuiteWindow::newConnection()
{
    m_Dialog->show();
}

void JaqubSuiteWindow::loadCommPlugins()
{
    JaqubPluginLoader *loader = new JaqubPluginLoader(this);
    connect(loader, &JaqubPluginLoader::pluginLoaded, this, &JaqubSuiteWindow::addCommPlugin);
    loader->loadAllPlugins();
}

QDialog* JaqubSuiteWindow::GetNewWindow(JaqubPluginUIType uiType, JaqubSuiteWindow* window, JaqubConnection* connection){
    switch(uiType){
        case JaqubPluginUIType::Chat:
            return  new ConnectionChatWindow(window, connection);
        case JaqubPluginUIType::Postal:
            return new ConnectionPostalWindow(window, connection);
        default:
            return  new ConnectionChatWindow(window, connection);

    }
}
void JaqubSuiteWindow::notifyMessageSent(bool isError){
    if(!isError){
        qDebug() << "Message sent.";
        KNotification::event("mailSent", i18n("Mail Message Sent"), i18n("Your message was sent."), "internet-mail", this, KNotification::CloseOnTimeout, "jaqubsuite");
    } else {
        qDebug() << "Message failed to send.";
        KNotification::event("mailSentFailed", i18n("Mail Message Failed"), i18n("Your message failed to send."), "internet-mail", this, KNotification::CloseOnTimeout, "jaqubsuite");
    }
   
}

void JaqubSuiteWindow::addConnectionWindow()
{
    qDebug() << "Grabbing connection... ";
    QString connType = m_Dialog->getType();
    auto conn = ConnectionDialog::getConnection(); 
    qDebug() << connType;
    auto plugin = getPlugin(connType);
    if(plugin){
        qDebug() << "Logging in... ";
        plugin->login(m_Dialog->getConnectionUrl(), m_Dialog->getUserName(), m_Dialog->getPassword());
        if (!m_Dialog->getSecConnectionUrl().isEmpty()){
            plugin->loginSecondary(m_Dialog->getSecConnectionUrl(), m_Dialog->getUserName(), m_Dialog->getPassword());
        }
    }
    QDialog* window = GetNewWindow(plugin->getUIType(), this,  m_Dialog->getConnection());
    switch(plugin->getUIType()){
        case JaqubPluginUIType::Postal:
            reinterpret_cast<ConnectionPostalWindow*>(window)->setPlugin(plugin);
            
            break;
        case JaqubPluginUIType::Chat:
            break;
    }
    window->show();
    qDebug() << "Added new connection: " << window->windowTitle();
}

void JaqubSuiteWindow::addCommPlugin(JaqubPlugin* plugin)
{
    m_PluginNames << plugin->getTitle();
    switch(plugin->getUIType()){
        case JaqubPluginUIType::Postal:
            connect(plugin, &JaqubPlugin::messageSent, this, &JaqubSuiteWindow::notifyMessageSent);
            break;
        case JaqubPluginUIType::Chat:
            break;
    }
    pluginInterfaces.append(plugin);
}

JaqubPlugin * JaqubSuiteWindow::getPlugin(const QString& name)
{
    JaqubPlugin* result = nullptr;
    for (auto plugin : pluginInterfaces){
        if(plugin->getTitle() != name)
            continue;
        result = plugin;
        break;
    }
    return result;
}


JaqubSuiteWindow::~JaqubSuiteWindow() = default;
