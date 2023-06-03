import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import de.devlg.qmltypes 1.0

Window {
    id: mainWindow
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    visible: true
    title: qsTr("Settings Tester")

    property var appClass: SettingsTester;

    property string startTime: "";
    property string endTime: "";
    property int secondTime: 0;

    function runTest() {
        startTestButton.enabled = false;
        resultTexts.visible = false;
        testProgressBar.value = 0;
        testProgressBar.visible = true;
        SettingsTester.runTest();
    }

    Connections {
        target: appClass;

        function onTestResults(results) {
            // console.log(JSON.stringify(results));
            startTime = results.start;
            endTime = results.end;
            secondTime = results.passed;

            testProgressBar.visible = false;
            resultTexts.visible = true;

            startTestButton.enabled = true;
        }

        function onTestProgress(percentage) {
            testProgressBar.value = percentage;
        }

    }


    Flickable {
        id: contentScrollView
        anchors.fill: parent
        clip: true

        contentWidth: parent.width
        contentHeight: contentColumn.height

        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.horizontal: ScrollBar {
            interactive: false
            policy: ScrollBar.AlwaysOff
        }

        ScrollBar.vertical: ScrollBar {
            policy: contentScrollView.contentHeight > parent.height ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
            interactive: contentScrollView.contentHeight > parent.height
        }

        Column {
            id: contentColumn
            width: parent.width
            height: implicitHeight
            spacing: 0

            Text {
                id: titleText
                width: parent.width
                height: implicitHeight

                horizontalAlignment: Text.AlignHCenter
                maximumLineCount: 5
                wrapMode: Text.WordWrap
                font.pointSize: 25
                font.bold: true

                text: qsTr("Settings Tester")
            }

            Spacer {
                height: 5
            }

            Text {
                id: infoText
                width: parent.width
                height: implicitHeight

                horizontalAlignment: Text.AlignHCenter
                maximumLineCount: 15
                wrapMode: Text.WordWrap
                font.pointSize: 15

                text: qsTr("Tap the button below to generate 100.000 random settings entries.")
            }

            Spacer {
                height: 3
            }

            Text {
                id: infoSecondText
                width: parent.width
                height: implicitHeight

                horizontalAlignment: Text.AlignHCenter
                maximumLineCount: 15
                wrapMode: Text.WordWrap
                font.pointSize: 15

                text: qsTr("The results will be shown once the process is completed.")
            }

            Spacer {
                height: 10
            }

            Button {
                id: startTestButton
                anchors {
                    horizontalCenter: parent.horizontalCenter
                }

                palette.buttonText: "black"

                background: Rectangle {
                    color: startTestButton.down ? "#d0d0d0" : enabled ? "#e0e0e0" : "#bababa"
                }

                text: qsTr("Start Test")
                onClicked: runTest();
            }

            Spacer {
                height: 20
            }

            Item {
                id: resultItem
                width: parent.width
                height: 100
                clip: true

                ProgressBar {
                    id: testProgressBar
                    width: parent.width * 0.75
                    height: 20
                    visible: false

                    anchors.horizontalCenter: parent.horizontalCenter

                    from: 0
                    to: 100

                    value: 0
                }

                Item {
                    id: resultTexts
                    width: parent.width * 0.75
                    height: childrenRect.height
                    clip: true
                    visible: false

                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        id: resultStartedText
                        width: parent.width
                        height: implicitHeight

                        maximumLineCount: 15
                        wrapMode: Text.WordWrap
                        font.pointSize: 15

                        text: qsTr("The process started at:") + " " + startTime;
                    }

                    Text {
                        id: resultEndedText
                        width: parent.width
                        height: implicitHeight

                        anchors {
                            top: resultStartedText.bottom
                            topMargin: 5
                        }

                        maximumLineCount: 15
                        wrapMode: Text.WordWrap
                        font.pointSize: 15

                        text: qsTr("The process ended at:") + " " + endTime;
                    }

                    Text {
                        id: resultSecondsText
                        width: parent.width
                        height: implicitHeight

                        anchors {
                            top: resultEndedText.bottom
                            topMargin: 10
                        }

                        maximumLineCount: 15
                        wrapMode: Text.WordWrap
                        font.pointSize: 15

                        text: qsTr("The process took about") + " " + secondTime + " " + qsTr("seconds.");
                    }
                }
            }

        }

    }
}
