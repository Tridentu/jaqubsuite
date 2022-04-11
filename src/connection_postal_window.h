

#pragma once

#include <QDialog>
#include <jaqubsuite/jaqub_connection.h>
#include <jaqubsuite/jaqub_plugin.h>

namespace Ui {
     class ConnectionPostalWindow;
}




class ConnectionPostalWindow : public QDialog {
    Q_OBJECT
public:
    ConnectionPostalWindow(QWidget* parent, JaqubConnection* connection);
    ~ConnectionPostalWindow();
public:
    void setPlugin(JaqubPlugin* plugin);
private:
    void setBold();
    void setItalic();
    void setUnderlined();
    void setTextColor(const QColor& newTextColor);
    void resetMessage();
    void sendMessage();
    void notifyMessageSent(bool isError);
private:
    JaqubConnection* m_Connection;
    bool m_Bold = false;
    bool m_Italic = false;
    bool m_Underline = false;
    QScopedPointer<Ui::ConnectionPostalWindow> m_Ui;
    JaqubPlugin* m_Plugin;
};
