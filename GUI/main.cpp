#include <QtWidgets/QApplication>
#include "resourceimageprovider.h"

#include "datasource.h"


#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{

    qDebug() << QDir::currentPath();


    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//    QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext* ctx = engine.rootContext();
//    QThread* thread = new QThread;
    DataSource* dataSource = new DataSource();
//    dataSource->moveToThread(thread);
//    connect(dataSource, SIGNAL (error(QString)), nullptr, SLOT (errorString(QString)));
//    connect(thread, SIGNAL (started()), dataSource, SLOT (process()));
//    connect(dataSource, SIGNAL (finished()), thread, SLOT (quit()));
//    connect(dataSource, SIGNAL (finished()), dataSource, SLOT (deleteLater()));
//    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
//    thread->start();
    ctx->setContextProperty("dataSource", dataSource);

    engine.addImageProvider(QLatin1String("ecc_source"), new ResourceImageProvider(QQuickImageProvider::Image, dataSource));


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
