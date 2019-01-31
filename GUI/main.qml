import QtQuick 2.9
import QtQuick.Controls 2.2
import QtCharts 2.3

ApplicationWindow {
    visible: true
    width: 1024
    height: 768
    title: qsTr("LDPC Demo")
    font.pointSize: 12

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        signal page_changed(var number)


        Settings {
            id:settings
            signal iters_changed(var iter0, var iter1, var iter2, var iter3)

            Component.onCompleted:  {
                dataSource.set_image_parameters(image_select.model.get(image_select.currentIndex).value)
                dataSource.set_AWGN_parameters(snr_demo.value)
                dataSource.set_LDPC_parameters(h_matrix.model.get(h_matrix.currentIndex).value, decode_iter.value, iter0.value, iter1.value, iter2.value, iter3.value)
                dataSource.set_graph_parameters(avg_iter.value, snr_range.first.value, snr_range.second.value, step_size.value)

                iters_changed(iter0.value, iter1.value, iter2.value, iter3.value)
            }

            image_select {
                onCurrentIndexChanged: {
                    dataSource.set_image_parameters(image_select.model.get(image_select.currentIndex).value)
                    preview_image.source = image_select.model.get(image_select.currentIndex).value
                }
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
                    dataSource.set_LDPC_parameters(h_matrix.model.get(h_matrix.currentIndex).value, decode_iter.value, iter0.value, iter1.value, iter2.value, iter3.value)
                }
            }
            h_matrix{
                onCurrentIndexChanged: {
                    dataSource.set_LDPC_parameters(h_matrix.model.get(h_matrix.currentIndex).value, decode_iter.value, iter0.value, iter1.value, iter2.value, iter3.value)
                }
            }

            iter0{
                onValueChanged: {
                    dataSource.set_LDPC_parameters(h_matrix.model.get(h_matrix.currentIndex).value, decode_iter.value, iter0.value, iter1.value, iter2.value, iter3.value)
                    iters_changed(iter0.value, iter1.value, iter2.value, iter3.value)
                }
            }
            iter1{
                onValueChanged: {
                    dataSource.set_LDPC_parameters(h_matrix.model.get(h_matrix.currentIndex).value, decode_iter.value, iter0.value, iter1.value, iter2.value, iter3.value)
                    iters_changed(iter0.value, iter1.value, iter2.value, iter3.value)
                }
            }
            iter2{
                onValueChanged: {
                    dataSource.set_LDPC_parameters(h_matrix.model.get(h_matrix.currentIndex).value, decode_iter.value, iter0.value, iter1.value, iter2.value, iter3.value)
                    iters_changed(iter0.value, iter1.value, iter2.value, iter3.value)
                }
            }
            iter3{
                onValueChanged: {
                    dataSource.set_LDPC_parameters(h_matrix.model.get(h_matrix.currentIndex).value, decode_iter.value, iter0.value, iter1.value, iter2.value, iter3.value)
                    iters_changed(iter0.value, iter1.value, iter2.value, iter3.value)
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
            id: demo_page


            Component.onCompleted: {
//                dataSource.calculateDemo()
            }

        }

        Iterations {

        }
        Iterations_bitflip {

        }

        Graph {
            Component.onCompleted: {
//                dataSource.calculateGraph()
            }

        }
        Info{

        }

        onCurrentIndexChanged: swipeView.page_changed(swipeView.currentIndex)
    }



    header: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Settings")

        }

        TabButton {
            id: demo_button
            text: qsTr("Demo")

        }
        TabButton {
            text: qsTr("Iterations BP")
        }
        TabButton {
            text: qsTr("Iterations BF")
        }
        TabButton {
            text: qsTr("BER vs. SNR")
        }
        TabButton {
            text: qsTr("Info")
        }
    }
}
