#include "datasource.h"
#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtCore/QDebug>
#include <QtCore/QRandomGenerator>
#include <QtCore/QtMath>

#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QBarSeries>
#include<QtCharts/QBarSet>

#include "LDPC_app_base.h"

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

DataSource::DataSource(QObject *parent) :
    QObject(parent),

    m_index(-1)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();
//    qRegisterMetaType<QAbstractBarSeries*>();

    QString rsrcid = ":/test1.png"; //+ id;
    image.load(rsrcid);
//    unsigned int * stream;
//    stream = image_to_bits(image);
//    image_no_ecc = bits_to_image(stream);
//    delete [] stream;

}

void DataSource::updateDemoGraph(QAbstractBarSeries *series, QAbstractAxis* y_axis)
{
    if(series) {
        QBarSeries *barseries = static_cast<QBarSeries *>(series);
        barseries->remove(barseries->barSets().at(0));
        QBarSet* temp = new QBarSet("generated");
        temp->append(ber_none);
        temp->append(ber_bitflip);
        temp->append(ber_belief);
        barseries->append(temp);

    }
    if(y_axis)
    {
        y_axis->setMax(max_ber_demo);
    }

}

void DataSource::updateSNRAxis(QAbstractAxis *x_axis, QAbstractAxis *y_axis)
{
    if(x_axis)
    {
        x_axis->setMax(snr_high);
        x_axis->setMin(snr_low);
    }
    if(y_axis)
    {
        y_axis->setMin(0);
        y_axis->setMax(max_ber);
    }
}

void DataSource::updateSNRGraph(QAbstractSeries *series, int type)
{
    if(series) {
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);
        xySeries->clear();

        switch (type) {
            case 0:
                xySeries->append(ber_belief_series);
                break;
            case 1:
                xySeries->append(ber_none_series);
                break;
            case 2:
                xySeries->append(ber_bitflip_series);

                break;
        }



    }
}

void DataSource::set_AWGN_parameters(float snr)
{

    qInfo() << "New snr set: " << snr;
    this->snr = snr;


}

void DataSource::set_LDPC_parameters(QString matrix, int max_it)
{
    qInfo() << "New LDPC parameters set "<< matrix << " and " << max_it;
    this->matrix = matrix;
    this->max_it = max_it;
}

void DataSource::set_graph_parameters(int num_runs, float snr_low, float snr_high, float step_size)
{
    qInfo() << "New graph parameters set " << num_runs << " - " << snr_low << " - " << snr_high << " - " << step_size;
    this->num_runs = num_runs;
    this->snr_low = snr_low;
    this->snr_high = snr_high;
    this->snr_step = step_size;
}

void DataSource::calculateDemo()
{
    LDPC_app_base ab;

    std::vector<std::string> files = {"H_n648-z27-r1_2.alist","H_n648-z27-r2_3.alist","H_n648-z27-r3_4.alist","H_n648-z27-r5_6.alist"};
    ab.add_alist_files(files);
    LDPC_info ldpc_info;

#if 0
    /* Random data instead of image of 2 blocks + 42 in size */
    int size = 324*2+42;
    int *r_bin_signal = new int[size];

    /* Generate random binary signal of 1 block (K size) */
    auto myrand = std::bind(std::uniform_int_distribution<int>{0, 1},
            std::mt19937(std::random_device{}()));

    for (int i=0; i<size; i++) {
        r_bin_signal[i] = myrand();
    }
#endif

    unsigned int * stream;
    stream = image_to_bits(image);
    int size = image_width * image_height * 32;
    qDebug() << "stream size   " << size;

    /* Return data */
    int *data_out_bp = new int[size];
    int *data_out_bf = new int[size];
    int *data_out_raw = new int[size];

    /* Apply and reconstruct */
    ab.run_data_app(ldpc_info,
            data_out_bp, data_out_bf, data_out_raw, (int *)stream,
            size, snr, max_it, ab.getMatrix(/*"H_n648-z27-r1_2.alist"*/matrix.toStdString()));

//    ldpc_info.print();
    max_ber_demo = 0;
    ber_none = ldpc_info.get_entry(snr).BER_no_ecc;
    if (ber_none > max_ber_demo)
        max_ber_demo = ber_none;
    ber_bitflip = ldpc_info.get_entry(snr).BER_bf;
    if (ber_bitflip > max_ber_demo)
        max_ber_demo = ber_bitflip;
    ber_belief = ldpc_info.get_entry(snr).BER;
    if(ber_belief > max_ber_demo)
        max_ber_demo = ber_belief;

    image_no_ecc = bits_to_image((unsigned int *)data_out_raw);
    image_bitflip = bits_to_image((unsigned int *)data_out_bf);
    image_belief = bits_to_image((unsigned int *)data_out_bp);
    qDebug() << "SNR " << snr;
    delete [] stream;
    delete [] data_out_bp;
    delete [] data_out_bf;
    delete [] data_out_raw;

    send_demo_data();
}

void DataSource::calculateGraph()
{

    LDPC_app_base ab;
    std::vector<std::string> files = {"H_n648-z27-r1_2.alist","H_n648-z27-r2_3.alist","H_n648-z27-r3_4.alist","H_n648-z27-r5_6.alist"};
    ab.add_alist_files(files);

    std::vector<double> SNRdb_list;//{-5, -4, -3, -2, -1, -0.5, 0, 0.5, 1, 2, 3, 4, 5, 7, 10, 11, 12, 14, 16};

    for (float i = snr_low; i <= snr_high; i += snr_step) {

        SNRdb_list.push_back(i);
    }

    // 5 runs per SNR, 8 iterations per belief prop decoding
    LDPC_info ldpc_info_r1_2;
    ab.run_bersim_app(ldpc_info_r1_2, SNRdb_list, num_runs, max_it, ab.getMatrix(matrix.toStdString()));
//    ldpc_info_r1_2.print();

    ber_none_series.clear();
    ber_bitflip_series.clear();
    ber_belief_series.clear();
    max_ber = 0;
    for (auto snr_v : ldpc_info_r1_2.get_snr_vec()) {
        ber_none_series.append(QPointF(snr_v,ldpc_info_r1_2.get_entry(snr_v).BER_no_ecc));
        ber_bitflip_series.append(QPointF(snr_v,ldpc_info_r1_2.get_entry(snr_v).BER_bf));
        ber_belief_series.append(QPointF(snr_v,ldpc_info_r1_2.get_entry(snr_v).BER));
        if(ldpc_info_r1_2.get_entry(snr_v).BER_no_ecc > max_ber)
            max_ber = ldpc_info_r1_2.get_entry(snr_v).BER_no_ecc;
        if(ldpc_info_r1_2.get_entry(snr_v).BER_bf > max_ber)
            max_ber = ldpc_info_r1_2.get_entry(snr_v).BER_bf;
        if(ldpc_info_r1_2.get_entry(snr_v).BER > max_ber)
            max_ber = ldpc_info_r1_2.get_entry(snr_v).BER;

    }

    send_graph_data();
}

unsigned int *DataSource::image_to_bits(QImage image)
{
    int stream_size = image.height() * image.width() * 32;
    qDebug() << "Stream size i2b: " << stream_size;
    qDebug() << "Image w: " << image.width() << "Image h: " << image.height();
    unsigned int *bitstream = new unsigned int[stream_size];
    int stream_cnt = 0;

    // Store image size
    image_width = image.width();
    image_height = image.height();

    for (int x = 0;x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            unsigned int bits = image.pixel(x,y);
            for (int b=0; b<32; b++) {
                bitstream[stream_cnt++] = (bits>>b) & 1;
            }
        }
    }

    return bitstream;
}

QImage DataSource::bits_to_image(unsigned int *bitstream)
{
    QImage new_image(image_width, image_height, QImage::Format_RGB16);

    int stream_cnt = 0;
    for (int x = 0;x < new_image.width(); x++) {
        for (int y = 0; y < new_image.height(); y++) {
            unsigned int bits = 0;
            for (int b=0; b<32; b++) {
                bits |= (bitstream[stream_cnt++] & 1) << b;
            }
            bits |= 0xffU << 24;
            QRgb pixel = (QRgb)bits;

            new_image.setPixel(x,y, pixel);
        }
    }

    return new_image;

}




