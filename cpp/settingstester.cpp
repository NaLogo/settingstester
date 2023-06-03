#include "settingstester.h"

SettingsTester* SettingsTester::m_pThis = nullptr;

SettingsTester::SettingsTester(QObject* parent) : QObject{parent} {}

SettingsTester* SettingsTester::instance() {
    if (m_pThis == nullptr) {
        m_pThis = new SettingsTester;
    }
    return m_pThis;
}

QObject* SettingsTester::qmlInstance(QQmlEngine* engine, QJSEngine* scriptEngine) {
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return SettingsTester::instance();
}

void SettingsTester::runTest() {
    m_worker = new TestWorker(this);

    connect(m_worker, SIGNAL(workerProgress(int)), this, SLOT(privTestProgress(int)), Qt::QueuedConnection);
    connect(m_worker, SIGNAL(workerResults(QVariantMap)), this, SLOT(privTestResults(QVariantMap)), Qt::QueuedConnection);

    m_testFuture = QtConcurrent::run(m_worker, &TestWorker::runTestProcess);
}

void SettingsTester::privTestProgress(int percentage) {
    emit testProgress(percentage);
}

void SettingsTester::privTestResults(QVariantMap results) {
    disconnect(m_worker);
    delete m_worker;
    m_worker = nullptr;
    emit testResults(results);
}
