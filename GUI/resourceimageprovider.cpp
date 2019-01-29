#include "resourceimageprovider.h"
#include <QImage>
#include <QPixmap>

#include <QDebug>
#include <string>

ResourceImageProvider::ResourceImageProvider(QQuickImageProvider::ImageType type) :
    QQuickImageProvider(type)
{
    // This space intentionally left blank.
}

ResourceImageProvider::~ResourceImageProvider()
{
    // This space intentionally left blank.
}

QImage ResourceImageProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
    QString rsrcid = ":/Screenshot_20180121-164046.png"; //+ id;
    QImage image(rsrcid);
    QImage result;

    QImage test(320,400, QImage::Format_RGB16);

    for(int i =0; i<320; ++i) {
        for(int j = 0; j < 400; ++j){


            QRgb rgb = image.pixel(i,j);
            if(id == "original") {

            }
            if (id == "none") {
                rgb = qRgb(qRed(rgb),0,0);
            }
            if(id == "bitflip") {
                rgb = qRgb(0,qGreen(rgb),0);
            }
            if(id == "logli") {
                rgb = qRgb(0,0,qBlue(rgb));
            }




            test.setPixel(i, j, rgb);

        }

    }

    if (requestedSize.isValid()) {
        result = test.scaled(requestedSize, Qt::KeepAspectRatio);
    } else {
        result = test;
    }
    *size = result.size();
    return result;
}

QPixmap ResourceImageProvider::requestPixmap(const QString& id, QSize* size, const QSize& requestedSize)
{
    QString rsrcid = ":/" + id;
    QPixmap image(rsrcid);
    QPixmap result;

    if (requestedSize.isValid()) {
        result = image.scaled(requestedSize, Qt::KeepAspectRatio);
    } else {
        result = image;
    }
    *size = result.size();
    return result;
}
