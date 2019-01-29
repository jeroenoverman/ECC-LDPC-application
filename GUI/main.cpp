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
    DataSource dataSource;
    ctx->setContextProperty("dataSource", &dataSource);

    engine.addImageProvider(QLatin1String("ecc_source"), new ResourceImageProvider(QQuickImageProvider::Image, &dataSource));


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}
