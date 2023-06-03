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
