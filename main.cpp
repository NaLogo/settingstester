#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QSettings>

#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[]) {
    // set application names and identifiers
    QApplication::setOrganizationName("Dev-LG");
    QApplication::setOrganizationDomain("dev-lg.de");
    QApplication::setApplicationName("SettingsTest");

    // call settings once to finalize the above settings
    QSettings settings;

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    // register our main cpp file as a singleton object for qml
    // qmlRegisterSingletonType<SettingsTester>("de.dev-lg.settingstest.app", 1, 0, "SettingsTester", &SettingsTester::qmlInstance);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "SettingsTest_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
            &engine, &QQmlApplicationEngine::objectCreated, &app,
            [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl) QCoreApplication::exit(-1);
            },
            Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
