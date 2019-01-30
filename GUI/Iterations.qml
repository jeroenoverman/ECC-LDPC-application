import QtQuick 2.9
import QtQuick.Controls 2.2
import QtCharts 2.3
import QtQuick.Layouts 1.12

//property alias demo_page: demo_page
Page {
    id: iterations_page
    width: 600
    height: 400


    antialiasing: true
    property int margin: 10




    header: Label {
        text: qsTr("Iterations")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }



    Column{
        id: main_layout
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: margin
        spacing: 20

        Row{

            height: parent.height*0.5 - parent.spacing
            width: parent.width
            spacing: 10
            Column {
                height: parent.height
                width: 0.3 * parent.width

                Label {
                    id: label_it_0
                    text: qsTr("Iteration 0")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Image {
                    id: iter_0
                    height: parent.height - label_it_0.height - label_it_0_1.height
                    width: parent.width
                    antialiasing: true
                    fillMode: Image.PreserveAspectFit
                    source: "image://ecc_source/original"
                    cache: false
                }
                Label {
                    id: label_it_0_1
                    text: qsTr("BER")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Column {
                height: parent.height
                width: 0.3 * parent.width
                Label {
                    id: label_it_1
                    text: qsTr("Iteration 1")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Image {
                    id: iter_1
                    height: parent.height - label_it_1.height - label_it_1_1.height
                    width: parent.width
                    antialiasing: true
                    fillMode: Image.PreserveAspectFit
                    source: "image://ecc_source/original"
                    cache: false
                }
                Label {
                    id: label_it_1_1
                    text: qsTr("BER")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
            Column {
                height: parent.height
                width: 0.3 * parent.width
                Label {
                    id: label_it_2
                    text: qsTr("Iteration 2")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Image {
                    id: iter_2
                    height: parent.height - label_it_2.height - label_it_2_1.height
                    width: parent.width
                    antialiasing: true
                    fillMode: Image.PreserveAspectFit
                    source: "image://ecc_source/original"
                    cache: false
                }
                Label {
                    id: label_it_2_1
                    text: qsTr("BER")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }

        Row{
            spacing: 10
            width: parent.width
            height: parent.height*0.5 - parent.spacing

            Column {
                height: parent.height
                width: 0.3 * parent.width
                Label {
                    id: label_it_3
                    text: qsTr("Iteration 3")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Image {
                    id: iter_3
                    height: parent.height - label_it_3.height - label_it_3_1.height
                    width: parent.width
                    antialiasing: true
                    fillMode: Image.PreserveAspectFit
                    source: "image://ecc_source/original"
                    cache: false
                }
                Label {
                    id: label_it_3_1
                    text: qsTr("BER")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
            Column {
                height: parent.height
                width: 0.3 * parent.width
                Label {
                    id: label_it_4
                    text: qsTr("Iteration 4")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Image {
                    id: iter_4
                    height: parent.height - label_it_4.height - label_it_4_1.height
                    width: parent.width
                    antialiasing: true
                    fillMode: Image.PreserveAspectFit
                    source: "image://ecc_source/original"
                    cache: false
                }
                Label {
                    id: label_it_4_1
                    text: qsTr("BER")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
            Column {
                height: parent.height
                width: 0.3 * parent.width
                Label {
                    id: label_it_5
                    text: qsTr("Iteration 5")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Image {
                    id: iter_5
                    height: parent.height - label_it_5.height - label_it_5_1.height
                    width: parent.width
                    antialiasing: true
                    fillMode: Image.PreserveAspectFit
                    source: "image://ecc_source/original"
                    cache: false
                }
                Label {
                    id: label_it_5_1
                    text: qsTr("BER")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }

    }
    Connections {
        target: dataSource
        onSend_demo_data: {
            console.log("ITerations: Received bar set from c++")
//            dataSource.updateDemoGraph(chartView.series(0), chartView.axisY(chartView.series(0)));
            iter_0.source = "";
            iter_0.source = "image://ecc_source/original";
            iter_1.source = "";
            iter_1.source = "image://ecc_source/iter0_belief";
            iter_2.source = "";
            iter_2.source = "image://ecc_source/iter1_belief";
            iter_3.source = "";
            iter_3.source = "image://ecc_source/iter2_belief";
            iter_4.source = "";
            iter_4.source = "image://ecc_source/iter3_belief";
            iter_5.source = "";
            iter_5.source = "image://ecc_source/logli";


        }
    }
    Connections {
        target: swipeView
        onPage_changed: {

            console.log("(Iterations) page changed: " + number)
            if (number == 2){
                dataSource.calculateDemo()
            }
        }
    }


}



