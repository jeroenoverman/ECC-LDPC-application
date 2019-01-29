#include "resourceimageprovider.h"
#include <QImage>
#include <QPixmap>

#include <QDebug>
#include <string>

ResourceImageProvider::ResourceImageProvider(QQuickImageProvider::ImageType type, DataSource* source) :
    QQuickImageProvider(type)
{
    // This space intentionally left blank.
    this->source = source;
}

ResourceImageProvider::~ResourceImageProvider()
{
    // This space intentionally left blank.
}

QImage ResourceImageProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
    QString rsrcid = ":/trump.png"; //+ id;
    QImage image;
    QImage result;

//    QImage test(320,400, QImage::Format_RGB16);

//    for(int i =0; i<320; ++i) {
//        for(int j = 0; j < 400; ++j){


//            QRgb rgb = image.pixel(i,j);
//            if(id == "original") {

//            }
//            if (id == "none") {
//                rgb = qRgb(qRed(rgb),0,0);
//            }
//            if(id == "bitflip") {
//                rgb = qRgb(0,qGreen(rgb),0);
//            }
//            if(id == "logli") {
//                rgb = qRgb(0,0,qBlue(rgb));
//            }




//            test.setPixel(i, j, rgb);

//        }

//    }

    if(id == "original") {
        image = source->image;
    }
    if (id == "none") {
        image = source->image_no_ecc;
    }
    if(id == "bitflip") {
        image = source->image_bitflip;
    }
    if(id == "logli") {
        image = source->image_belief;
    }

    if (requestedSize.isValid()) {
        result = image.scaled(requestedSize, Qt::KeepAspectRatio);
    } else {
        result = image;
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
