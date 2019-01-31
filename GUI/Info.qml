import QtQuick 2.9
import QtQuick.Controls 2.2
import QtCharts 2.3
import QtQuick.Layouts 1.12

//property alias demo_page: demo_page
Page {
    id: info_page
    width: 600
    height: 400


    antialiasing: true
    property int margin: 10




    header: Label {
        text: qsTr("Info")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }



    Column {
        id: main_layout
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: margin
        spacing: 10

        Text {
            id: info_text
            text: qsTr("<h1>Test heading</h1> <b>bold text</b><p>Test paragraaf</p>")
        }

    }


}



