#ifndef TESTWORKER_H
#define TESTWORKER_H

#include <QObject>
#include <QSettings>
#include <QRandomGenerator>
#include <QDateTime>

class TestWorker : public QObject {
        Q_OBJECT
    public:
        explicit TestWorker(QObject *parent = nullptr);

        void runTestProcess();

    private:
        QString generateRandomValue(int length);

    signals:
        void workerProgress(int percentage);
        void workerResults(QVariantMap results);
};

#endif // TESTWORKER_H
