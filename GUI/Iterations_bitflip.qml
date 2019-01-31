import QtQuick 2.9
import QtQuick.Controls 2.2
import QtCharts 2.3
import QtQuick.Layouts 1.12


Page {
    id: iterations_bitflip_page
    width: 600
    height: 400


    antialiasing: true
    property int margin: 10




    header: Label {
        text: qsTr("Iterations bit flipping")
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
                    text: qsTr("Initial image ")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Image {
                    id: iter_0_image
                    height: parent.height - label_it_0.height - label_it_0_1.height
                    width: parent.width
                    antialiasing: true
                    fillMode: Image.PreserveAspectFit
                    source: "image://ecc_source/original"
                    cache: false
                }
                Label {
                    id: label_it_0_1
                    text: qsTr("BER: ")
                    anchors.horizontalCenter: parent.horizontalCenter
                }

            }

            Column {
                height: parent.height
                width: 0.3 * parent.width
                Label {
                    id: label_it_1
                    text: qsTr("Iteration ")
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Image {
                    id: iter_1_image
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
                    id: iter_2_image
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
                    id: iter_3_image
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
                    id: iter_4_image
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
                    text: qsTr("Final image")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Image {
                    id: iter_5_image
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
            iter_0_image.source = "";
            iter_0_image.source = "image://ecc_source/none";
            iter_1_image.source = "";
            iter_1_image.source = "image://ecc_source/iter0_bitflip";
            iter_2_image.source = "";
            iter_2_image.source = "image://ecc_source/iter1_bitflip";
            iter_3_image.source = "";
            iter_3_image.source = "image://ecc_source/iter2_bitflip";
            iter_4_image.source = "";
            iter_4_image.source = "image://ecc_source/iter3_bitflip";
            iter_5_image.source = "";
            iter_5_image.source = "image://ecc_source/bitflip";

            label_it_0_1.text = qsTr("BER: ") + qsTr(Number(ber_orig).toFixed(3).toString())
            label_it_1_1.text = qsTr("BER: ") + qsTr(Number(ber_bf_0).toFixed(3).toString())
            label_it_2_1.text = qsTr("BER: ") + qsTr(Number(ber_bf_1).toFixed(3).toString())
            label_it_3_1.text = qsTr("BER: ") + qsTr(Number(ber_bf_2).toFixed(3).toString())
            label_it_4_1.text = qsTr("BER: ") + qsTr(Number(ber_bf_3).toFixed(3).toString())
            label_it_5_1.text = qsTr("BER: ") + qsTr(Number(ber_bf_final).toFixed(3).toString())


        }
    }
    Connections {
        target: swipeView
        onPage_changed: {

            console.log("(Iterations) page changed: " + number)
            if (number == 3){
                dataSource.calculateDemo()
            }
        }
    }
    Connections {
        target: settings
        onIters_changed: {
            label_it_1.text = qsTr("Iteration ") + qsTr(Number(iter0).toString())
            label_it_2.text = qsTr("Iteration ") + qsTr(Number(iter1).toString())
            label_it_3.text = qsTr("Iteration ") + qsTr(Number(iter2).toString())
            label_it_4.text = qsTr("Iteration ") + qsTr(Number(iter3).toString())
        }
    }




}



