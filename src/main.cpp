#include "jaqubsuite.h"
#include <KLocalizedString>
#include <KAboutData>
#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    KLocalizedString::setApplicationDomain("JaqubSuite");

    KAboutData aboutData(
            QStringLiteral("JaqubSuite"),
            i18n("JaqubSuite"),
            QStringLiteral("0.1"),
            i18n("Tridentu-RK's official communications app."),
            KAboutLicense::GPL,
            i18n("(c) 2022"),
            i18n("This app can be adapteed to many protocols (including email)."),
            QStringLiteral("https://tridentu.github.io/jaqubsuite"),
            QStringLiteral("tridentuorg@protonmail.com")
    );
    KAboutData::setApplicationData(aboutData);
    aboutData.setDesktopFileName("jaqubsuite.desktop");
    app.setApplicationName("jaqubsuite");
    QCommandLineParser parser;

    aboutData.setupCommandLine(&parser);
    parser.process(app);
    aboutData.processCommandLine(&parser);
    JaqubSuiteWindow w;
    w.show();

    return app.exec();
}

