#pragma once

#include <KXmlGuiWindow>
#include <QScopedPointer>

#include <jaqubsuite/jaqub_plugin.h>

#include <jaqubsuite/jaqub_plugin_loader.h>

#include "connection_dialog.h"
namespace Ui {
    class jaqubsuite;
}

class JaqubSuiteWindow : public KXmlGuiWindow
{
    Q_OBJECT

public:
    explicit JaqubSuiteWindow(QWidget *parent = nullptr);
    ~JaqubSuiteWindow() override;
public:
    static QDialog* GetNewWindow(JaqubPluginUIType uiType, JaqubSuiteWindow* window, JaqubConnection* connection);
    
private:
    void newConnection();
    void loadCommPlugins();
    void addConnectionWindow();
    void notifyMessageSent(bool isError);
private:
    void addCommPlugin(JaqubPlugin* plugin);
    JaqubPlugin* getPlugin(const QString& name);
private:
    QScopedPointer<Ui::jaqubsuite> m_ui;
    QStringList m_PluginNames;
    QList<JaqubPlugin*> pluginInterfaces;
    ConnectionDialog* m_Dialog;
    
};

