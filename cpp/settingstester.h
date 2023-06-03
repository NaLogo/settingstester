#ifndef SETTINGSTESTER_H
#define SETTINGSTESTER_H

#include <QObject>
#include <QQmlEngine>
#include <QtConcurrent>

#include "testworker.h"

class SettingsTester : public QObject {
        Q_OBJECT
        QML_ELEMENT
        QML_SINGLETON
    public:
        explicit SettingsTester(QObject *parent = nullptr);

        static SettingsTester *instance();
        static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

        Q_INVOKABLE void runTest();

        void sendProgress(int p);

    private:
        static SettingsTester *m_pThis;

        TestWorker *m_worker;
        void startTestProcess();
        QFuture<void> m_testFuture;

    signals:
        void testProgress(int percentage);
        void testResults(QVariantMap results);

    private slots:
        void privTestProgress(int percentage);
        void privTestResults(QVariantMap results);
};

#endif // SETTINGSTESTER_H
