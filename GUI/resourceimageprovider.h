#ifndef RESOURCEIMAGEPROVIDER_H
#define RESOURCEIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include "datasource.h"

class ResourceImageProvider : public QQuickImageProvider
{
public:
    ResourceImageProvider(QQuickImageProvider::ImageType type, DataSource* source);
    ~ResourceImageProvider();
    QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize);
    QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize);

private:
    DataSource * source;
};

#endif // RESOURCEIMAGEPROVIDER_H

