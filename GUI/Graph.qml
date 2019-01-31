import QtQuick 2.9
import QtQuick.Controls 2.2
import QtCharts 2.3

Page {
    width: 600
    height: 400
    property int margin: 10

    header: Label {
        text: qsTr("Bit error rate vs signal to noise ratio")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    ChartView {
        id: chartView
        width: parent.width
        height: parent.height
        //backgroundColor: "#c34e4e"
        //theme: ChartView.ChartThemeBrownSand
        antialiasing: true
        title: "BER/SNR"
        titleFont: Qt.font({pointSize: 13})

        ValueAxis {
            id: valueAxisY // vertical axis
            min: 0
            max: 1.0
            titleText: "BER"
            titleFont: Qt.font({pointSize: 16})
            labelsFont: Qt.font({pointSize: 16})
//            tickCount: 5
            //reverse: true;
        }
        ValueAxis {
            id: valueAxisX
            min: -4
            max: 10
            titleText: "SNR"
            titleFont: Qt.font({pointSize: 16})
            labelsFont: Qt.font({pointSize: 16})
        }

        //Legend.visible: false
        LineSeries {
            name: "Belief propagation"
            axisY : valueAxisY
            axisX : valueAxisX

        }
        LineSeries {
            name: "Bit flipping"
            axisY : valueAxisY
            axisX : valueAxisX

        }
        LineSeries {
            name: "No ECC"
            axisY : valueAxisY
            axisX : valueAxisX
        }
        LineSeries {
            name: "Theoretical no ECC"
            axisY : valueAxisY
            axisX : valueAxisX
        }

        legend.font: Qt.font({pointSize: 16})

    }
    Connections {
        target: dataSource
        onSend_graph_data: {
            console.log("Received graph set from c++")
            dataSource.updateSNRGraph(chartView.series(0),0);
            dataSource.updateSNRGraph(chartView.series(1),1);
            dataSource.updateSNRGraph(chartView.series(2),2);
            dataSource.updateSNRGraph(chartView.series(3),3);
            dataSource.updateSNRAxis(chartView.axisX(chartView.series(0)),chartView.axisY(chartView.series(0)))

        }
    }
    Connections {
        target: swipeView
        onPage_changed: {

            console.log("(graph) page changed: " + number)
            if (number == 4){

                dataSource.calculateGraph()
            }
        }
    }
}
