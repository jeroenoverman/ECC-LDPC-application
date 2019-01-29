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
}

void DataSource::updateDemoGraph(QAbstractBarSeries *series)
{
    if(series) {
        QBarSeries *barseries = static_cast<QBarSeries *>(series);
        barseries->remove(barseries->barSets().at(0));
        QBarSet* temp = new QBarSet("generated");
        temp->append(0.1);
        temp->append(0.2);
        temp->append(0.3);
        barseries->append(temp);

    }

}

void DataSource::updateSNRGraph(QAbstractSeries *series)
{
    if(series) {
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);


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
    send_demo_data();
}

void DataSource::calculateGraph()
{
    send_graph_data();
}




