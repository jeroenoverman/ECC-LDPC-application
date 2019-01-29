import QtQuick 2.9
import QtQuick.Controls 2.2
import QtCharts 2.3

ApplicationWindow {
    visible: true
    width: 1024
    height: 768
    title: qsTr("Tabs")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex


        Settings {

            Component.onCompleted:  {
                dataSource.set_AWGN_parameters(snr_demo.value)
                dataSource.set_LDPC_parameters(h_matrix.model.get(h_matrix.currentIndex).value, decode_iter.value)
                dataSource.set_graph_parameters(avg_iter.value, snr_range.first.value, snr_range.second.value, step_size.value)
            }

            toolTip_snr_demo{
                text: snr_demo.valueAt(snr_demo.position).toFixed(1)
            }
            value_label_snr_demo {
                text: snr_demo.value.toFixed(1)
            }
            snr_demo{
                onValueChanged: {
                    dataSource.set_AWGN_parameters(snr_demo.value)
                }
            }

            toolTip_decode_iter{
                text: decode_iter.valueAt(decode_iter.position).toFixed(1)
            }
            value_label_max_iterations{
                text: decode_iter.value.toFixed(1)
            }
            decode_iter {
                onValueChanged: {
                    dataSource.set_LDPC_parameters(h_matrix.model.get(h_matrix.currentIndex).value, decode_iter.value)
                }
            }
            h_matrix{
                onCurrentIndexChanged: {
                    dataSource.set_LDPC_parameters(h_matrix.model.get(h_matrix.currentIndex).value, decode_iter.value)
                }
            }

            toolTip_avg_iter {
                text: avg_iter.valueAt(avg_iter.position).toFixed(0)
            }
            value_label_avg_iterations {
                text: avg_iter.value.toFixed(0)
            }
            avg_iter {
                onValueChanged: {
                    dataSource.set_graph_parameters(avg_iter.value, snr_range.first.value, snr_range.second.value, step_size.value)
                }
            }

            toolTip_snr_range1{
                text: snr_range.valueAt(snr_range.first.position).toFixed(1)
            }
            value_label_snr_range1{
                text: snr_range.first.value.toFixed(1)
            }

            toolTip_snr_range2 {
                text: snr_range.valueAt(snr_range.second.position).toFixed(1)
            }
            value_label_snr_range3{
                text: snr_range.second.value.toFixed(1)
            }
            snr_range{
                first.onMoved: {
                    dataSource.set_graph_parameters(avg_iter.value, snr_range.first.value, snr_range.second.value, step_size.value)
                }
                second.onMoved: {
                    dataSource.set_graph_parameters(avg_iter.value, snr_range.first.value, snr_range.second.value, step_size.value)
                }
            }

            toolTip_step_size{
                text: step_size.valueAt(step_size.position).toFixed(1)
            }
            value_label_step_size{
                text: step_size.value.toFixed(1)
            }
            step_size {
                onValueChanged: {
                    dataSource.set_graph_parameters(avg_iter.value, snr_range.first.value, snr_range.second.value, step_size.value)
                }
            }

        }

        Demo {




        }

        Graph {
        }
    }



    header: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Settings")

        }

        TabButton {
            text: qsTr("Demo")
            onClicked: {
                dataSource.calculateDemo()
            }
        }
        TabButton {
            text: qsTr("BER vs. SNR")
            onClicked: dataSource.calculateGraph()
        }
    }
}
