import QtQuick 2.9
import QtQuick.Controls 2.2
import QtCharts 2.3
import QtQuick.Layouts 1.12

//property alias demo_page: demo_page
Page {
    id: demo_page
    width: 600
    height: 400
    property alias chartView: chartView
    property alias loading_widget: loading_widget

    antialiasing: true
    property int margin: 10




    header: Label {
        text: qsTr("Low density parity check demo")
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
        Row {
            id: rowLayout
            height: 0.5 * parent.height - 0.5 * margin
            width: parent.width
            //            Layout.fillWidth: true
            spacing: 10
            Column {
                id: orignal_image_column
                height: parent.height
                width: 0.25 * parent.width - margin

                Label {
                    id: label_original
                    text: qsTr("Original")
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Image {
                    id: original_image
                    width: parent.width //0.25 *parent.width - margin
                    height: parent.height - label_original.height
                    antialiasing: true
                    fillMode: Image.PreserveAspectFit
                    source: "image://ecc_source/original"
                    cache: false
                }
            }

            Image {
                id: right_arrow
                anchors.verticalCenter: parent.verticalCenter
                antialiasing: true
                fillMode: Image.PreserveAspectFit
                source: "arrow.png"
                width: 0.25 * parent.width - margin
                cache: false
            }

            Column {
                id: without_image_column
                height: parent.height
                width: 0.25 * parent.width - margin

                Label {
                    id: label_without
                    text: qsTr("Without ECC")
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Image {
                    id: image_without
                    width: parent.width
                    height: parent.height - label_original.height
                    antialiasing: true
                    fillMode: Image.PreserveAspectFit
                    source: "image://ecc_source/none"
                    cache: false
                }
            }

            Column {
                id: bitflip_image_column
                height: parent.height
                width: 0.25 * parent.width - margin

                Label {
                    id: label_bitflip
                    text: qsTr("Bitflipping")
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Image {
                    id: image_bitflip
                    width: parent.width
                    height: parent.height - label_bitflip.height
                    antialiasing: true
                    fillMode: Image.PreserveAspectFit
                    source: "image://ecc_source/bitflip"
                    cache: false
                }
            }
        }
        Row {
            id: rowLayout2

            height: 0.5 * parent.height - 0.5 * margin
            width: parent.width
            spacing: 10

            ChartView {
                id: chartView
                width: 0.75 * parent.width - 1 * margin
                height: parent.height
                //backgroundColor: "#c34e4e"
                //theme: ChartView.ChartThemeBrownSand
                antialiasing: true
                legend.visible: false
                //Legend.visible: false
                ValueAxis {
                    min: 0
                    max: 1
                    id: y_axis
                    titleText: "BER"
                    titleFont: Qt.font({pointSize: 16})
                    labelsFont: Qt.font({pointSize:16})
                }

                BarSeries {
                    id: biterrorrate
                    axisY: y_axis
                    axisX: BarCategoryAxis {
                        categories: ["No ECC", "bitflipping", "likelihood"]
                        labelsFont: Qt.font({pointSize: 16})
                    }
                    BarSet {
                        values: [0.4, 0.8, 0.9]
                    }
                }


            }

            Column {
                id: logli_image_column
                height: parent.height
                width: 0.25 * parent.width - margin

                Label {
                    id: label_logli
                    text: qsTr("Loglikelihood")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Image {
                    id: image_logli
                    width: parent.width
                    height: parent.height - label_logli.height
                    antialiasing: true
                    fillMode: Image.PreserveAspectFit
                    source: "image://ecc_source/logli"
                    cache: false
                }
            }
        }
    }

    Rectangle{
        id: loading_widget
        anchors.fill: parent
        color: "#D3D3D3"
        Label {
            text: qsTr("Loading")
            font.pixelSize: Qt.application.font.pixelSize * 2
            verticalAlignment: "AlignVCenter"
            horizontalAlignment: "AlignHCenter"
        }
        visible: false


    }

    Connections {
        target: dataSource
        onSend_demo_data: {
            console.log("Received bar set from c++")
            dataSource.updateDemoGraph(chartView.series(0), chartView.axisY(chartView.series(0)));
            original_image.source = "";
            original_image.source = "image://ecc_source/original";
            image_without.source = "";
            image_without.source = "image://ecc_source/none";
            image_bitflip.source = "";
            image_bitflip.source = "image://ecc_source/bitflip";
            image_logli.source = "";
            image_logli.source = "image://ecc_source/logli";
            loading_widget.visible= false

        }
    }
    Connections {
        target: swipeView
        onPage_changed: {

            console.log("(DEMO) page changed: " + number)
            if (number == 1){
                loading_widget.visible = true
                dataSource.calculateDemo()
            }
        }
    }


}



