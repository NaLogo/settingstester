QT += qml quick widgets concurrent

CONFIG += c++11, console, qmltypes

VERSION = 1.0.0

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        cpp/settingstester.cpp \
        cpp/testworker.cpp \
        main.cpp

RESOURCES += qml.qrc

TRANSLATIONS += \
    SettingsTest_en_001.ts
CONFIG += lrelease
CONFIG += embed_translations

# QML Types base config
QML_IMPORT_NAME = de.devlg.qmltypes
QML_IMPORT_MAJOR_VERSION = 1

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD/cpp
QML2_IMPORT_PATH = $$PWD/cpp

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH = $$PWD/cpp

# Add our cpp path again to allow qml type registration to find them
INCLUDEPATH += $$PWD/cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    cpp/settingstester.h \
    cpp/testworker.h

DISTFILES += \
    _clang-format \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
