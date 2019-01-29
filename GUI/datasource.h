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
    void updateDemoGraph(QAbstractBarSeries *series);
    void updateSNRGraph(QAbstractSeries *series);
    void set_AWGN_parameters(float snr);
    void set_LDPC_parameters(QString matrix, int max_it);
    void set_graph_parameters(int num_runs, float snr_low, float snr_high, float step_size);
    void calculateDemo(void);
    void calculateGraph(void);


signals:
    void send_demo_data(void);
    void send_graph_data(void);
private:
    QQuickView *m_appViewer;
    QList<QVector<QPointF> > m_data;
    int m_index;
    float snr;
    QString matrix;
    int max_it;
    int num_runs;
    float snr_low;
    float snr_high;
    float snr_step;

};



#endif // DATASOURCE_H
