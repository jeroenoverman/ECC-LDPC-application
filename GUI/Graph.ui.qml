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
        width: parent.width
        height: parent.height
        //backgroundColor: "#c34e4e"
        //theme: ChartView.ChartThemeBrownSand
        antialiasing: true

        LogValueAxis {
            id: valueAxisY // vertical axis
            min: 0
            max: 10000000.0
//            tickCount: 5
            //reverse: true;
        }
        //Legend.visible: false
        LineSeries {
            name: "loglikelihood"
            axisY : valueAxisY
            XYPoint { x: 0; y: 10 }
            XYPoint { x: 1.1; y: 200.1 }
            XYPoint { x: 1.9; y: 3000.3 }
            XYPoint { x: 2.1; y: 40000.1 }
            XYPoint { x: 2.9; y: 400000.9 }
            XYPoint { x: 3.4; y: 7000000.0 }
            XYPoint { x: 4.1; y: 9000000.3 }
        }
        LineSeries {
            name: "Without ECC"
            axisY : valueAxisY
            XYPoint { x: 0; y: 10 }
            XYPoint { x: 1.1; y: 20.1 }
            XYPoint { x: 1.9; y: 300.3 }
            XYPoint { x: 2.1; y: 2000.1 }
            XYPoint { x: 2.9; y: 40000.9 }
            XYPoint { x: 3.4; y: 300000.0 }
            XYPoint { x: 4.1; y: 3000000.3 }
        }
        LineSeries {
            name: "Bitflipping"
            axisY : valueAxisY
            XYPoint { x: 0; y: 10 }
            XYPoint { x: 1.1; y: 10.1 }
            XYPoint { x: 1.9; y: 200.3 }
            XYPoint { x: 2.1; y: 3000.1 }
            XYPoint { x: 2.9; y: 40000.9 }
            XYPoint { x: 3.4; y: 500000.0 }
            XYPoint { x: 4.1; y: 6000000.3 }
        }

    }
}
