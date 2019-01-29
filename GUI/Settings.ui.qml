import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12

Page {
    width: 1024
    height: 768
    property alias h_matrix: h_matrix
    property alias toolTip_step_size: toolTip_step_size
    property alias step_size: step_size
    property alias value_label_step_size: value_label_step_size
    property alias value_label_snr_range1: value_label_snr_range1
    property alias value_label_snr_range3: value_label_snr_range3
    property alias toolTip_snr_range2: toolTip_snr_range2
    property alias toolTip_snr_range1: toolTip_snr_range1
    property alias snr_range: snr_range
    property alias toolTip_avg_iter: toolTip_avg_iter
    property alias avg_iter: avg_iter
    property alias value_label_avg_iterations: value_label_avg_iterations
    property alias value_label_max_iterations: value_label_max_iterations
    property alias toolTip_decode_iter: toolTip_decode_iter
    property alias decode_iter: decode_iter
    property alias value_label_snr_demo: value_label_snr_demo
    property alias toolTip_snr_demo: toolTip_snr_demo
    property alias snr_demo: snr_demo
    property int margin: 10

    header: Label {
        text: qsTr("Settings")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    ColumnLayout {
        id: main_column
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: margin
        spacing: 10

        GroupBox {
            id: awgn_channel
            title: "AWGN channel settings"
            Layout.fillWidth: true
            ColumnLayout {
                anchors.fill: parent
                RowLayout {
                    Label {
                        id: label_snr_demo
                        text: qsTr("SNR (dB): ")
                    }
                    Label {
                        id: value_label_snr_demo
                    }
                    Label {
                        id: label_snr_demo2
                        text: qsTr(" dB")
                    }
                }

                Slider {
                    id: snr_demo
                    stepSize: 0.1
                    from: -5
                    value: 4
                    to: 10
                    //                    padding: 35
                    //                    topPadding: 35

                    //                    valueIndicatorVisible: true
                    //                    onValueChanged:
                    Layout.fillWidth: true
                    ToolTip {
                        id: toolTip_snr_demo
                        parent: snr_demo.handle
                        visible: snr_demo.pressed
                        text: "test"
                        topMargin: 1 //snr_demo.valueAt(slider.position).toFixed(1)
                    }
                }
            }
        }

        GroupBox {
            id: ldpc
            title: "LDPC settings"
            Layout.fillWidth: true
            ColumnLayout {
                anchors.fill: parent
                Label {
                    id: label_h_matrix
                    text: qsTr("Code rate")
                }

                ComboBox {
                    id: h_matrix
                    textRole: "key"
                    Layout.fillWidth: true
                    model: ListModel {
                        ListElement {
                            key: "1/2"
                            value: 123
                        }
                        ListElement {
                            key: "2/3"
                            value: 456
                        }
                        ListElement {
                            key: "3/4"
                            value: 789
                        }
                        ListElement {
                            key: "5/6"
                            value: 1024
                        }
                    }
                }

                ColumnLayout {
                    RowLayout {
                        Label {
                            id: label_max_iterations
                            text: qsTr("Max iterations decoder: ")
                        }
                        Label {
                            id: value_label_max_iterations
                        }
                    }
                    Slider {
                        id: decode_iter
                        stepSize: 1
                        from: 1
                        value: 8
                        to: 20

                        //                        topPadding: 35
                        Layout.fillWidth: true
                        ToolTip {
                            id: toolTip_decode_iter
                            parent: decode_iter.handle
                            visible: decode_iter.pressed
                            text: "test"
                        }
                    }
                }
            }
        }

        GroupBox {
            id: graph_box
            title: "Graph settings"
            Layout.fillWidth: true
            ColumnLayout {
                anchors.fill: parent

                RowLayout {
                    Label {
                        id: label_avg_iterations
                        text: qsTr("Number of runs: ")
                    }
                    Label {
                        id: value_label_avg_iterations
                    }
                }
                Slider {
                    id: avg_iter
                    stepSize: 1
                    from: 1
                    value: 10
                    to: 20

                    //                        topPadding: 35
                    Layout.fillWidth: true
                    ToolTip {
                        id: toolTip_avg_iter
                        parent: avg_iter.handle
                        visible: avg_iter.pressed
                        text: "test"
                    }
                }

                RowLayout {
                    Label {
                        id: label_snr_range
                        text: qsTr("SNR range: From ")
                    }
                    Label {
                        id: value_label_snr_range1
                    }
                    Label {
                        id: value_label_snr_range2
                        text: qsTr(" to ")
                    }
                    Label {
                        id: value_label_snr_range3
                    }
                    Label {
                        id: value_label_snr_range4
                        text: qsTr(" dB")
                    }
                }
                RangeSlider {
                    id: snr_range
                    second.value: 6
                    first.value: -3
                    stepSize: 0.1
                    from: -5

                    to: 20

                    //                        topPadding: 35
                    Layout.fillWidth: true
                    ToolTip {
                        id: toolTip_snr_range1
                        parent: snr_range.first.handle
                        visible: snr_range.first.pressed
                        text: "test"
                    }
                    ToolTip {
                        id: toolTip_snr_range2
                        parent: snr_range.second.handle
                        visible: snr_range.second.pressed
                        text: "test"
                    }
                }
                RowLayout {
                    Label {
                        id: label_step_size
                        text: qsTr("Step size: ")
                    }
                    Label {
                        id: value_label_step_size
                    }
                    Label {
                        id: label_step_size2
                        text: qsTr(" dB")
                    }
                }
                Slider {
                    id: step_size
                    stepSize: 0
                    from: 0
                    value: 0.5
                    to: 2

                    //                        topPadding: 35
                    Layout.fillWidth: true
                    ToolTip {
                        id: toolTip_step_size
                        parent: step_size.handle
                        visible: step_size.pressed
                        text: "test"
                    }
                }
            }
        }
    }
}
