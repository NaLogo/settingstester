#ifndef SETTINGSTESTER_H
#define SETTINGSTESTER_H

#include <QObject>
#include <QQmlEngine>

class SettingsTester : public QObject {
        Q_OBJECT
        QML_ELEMENT
        QML_SINGLETON
    public:
        explicit SettingsTester(QObject *parent = nullptr);

        static SettingsTester *instance();
        static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    private:
        static SettingsTester *m_pThis;

    signals:
};

#endif // SETTINGSTESTER_H
