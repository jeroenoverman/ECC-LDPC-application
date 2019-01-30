#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QAbstractBarSeries>

QT_BEGIN_NAMESPACE
class QQuickView;
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QObject *parent = nullptr);

Q_SIGNALS:

public slots:
    void updateDemoGraph(QAbstractBarSeries *series, QAbstractAxis* y_axis);
    void updateSNRAxis(QAbstractAxis * x_axis, QAbstractAxis* y_axis);
    void updateSNRGraph(QAbstractSeries *series, int type);
    void set_AWGN_parameters(float snr);
    void set_LDPC_parameters(QString matrix, int max_it);
    void set_graph_parameters(int num_runs, float snr_low, float snr_high, float step_size);
    void calculateDemo(void);
    void calculateGraph(void);


signals:
    void send_demo_data(void);
    void send_graph_data(void);
private:
    unsigned int* image_to_bits(QImage image);
    QImage bits_to_image(unsigned int* bits);


    QQuickView *m_appViewer;
    QList<QVector<QPointF> > m_data;
    int m_index;

    //settings
    float snr;
    QString matrix;
    int max_it;
    int num_runs;
    float snr_low;
    float snr_high;
    float snr_step;

    //demo data
    float ber_none, ber_bitflip, ber_belief;
    float max_ber_demo;
public:
    QImage image;
    QImage image_no_ecc;
    QImage image_bitflip;
    QImage image_belief;
private:
    int image_width;
    int image_height;


    //graph dat
    QList<QPointF> ber_none_series;
    QList<QPointF> ber_bitflip_series;
    QList<QPointF> ber_belief_series;
    float max_ber;




};



#endif // DATASOURCE_H
