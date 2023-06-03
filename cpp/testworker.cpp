#include "testworker.h"

TestWorker::TestWorker(QObject *parent) : QObject{parent} {}

void TestWorker::runTestProcess() {
    QSettings settings;
    qint64 start, end;

    // get current timestamp before we begin with our testing
    start = QDateTime::currentMSecsSinceEpoch();

    settings.beginGroup("testStorage");

    // clear potential previous values first
    settings.remove("");

    // NOTICE: Debug statements for each value will introduce a delay - the timestamps will be correct, though

    for (int i = 1; i <= 100; i++) {
        // qDebug() << "GROUP:" << i << "- BEGIN";
        settings.beginGroup("group_" + QString::number(i));

        for (int j = 1; j <= 1000; j++) {
            QString value = generateRandomValue(128);
            // qDebug() << "Key:"
            //          << "subkey_" + QString::number(j) << "Value:" << value;
            settings.setValue("subkey_" + QString::number(j), value);
        }

        emit workerProgress(i);

        settings.endGroup();

        // qDebug() << "GROUP:" << i << "- END";
    }

    settings.endGroup();

    settings.sync();

    // get new timestamp after we finished testing
    end = QDateTime::currentMSecsSinceEpoch();

    QVariantMap resultMap;

    resultMap.insert("start", QDateTime::fromMSecsSinceEpoch(start).toString("hh:mm:ss.z"));
    resultMap.insert("end", QDateTime::fromMSecsSinceEpoch(end).toString("hh:mm:ss.z"));
    resultMap.insert("passed", (end - start) / 1000);

    emit workerResults(resultMap);
}

QString TestWorker::generateRandomValue(int length) {
    QString source = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-_.,0123456789";
    int sourceLength = source.length();
    QString result = "";

    for (int i = 0; i < length; i++) {
        int index = QRandomGenerator::system()->generate() % sourceLength;
        QChar nextChar = source.at(index);
        result.append(nextChar);
    }

    return result;
}
