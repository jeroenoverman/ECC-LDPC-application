#ifndef RESOURCEIMAGEPROVIDER_H
#define RESOURCEIMAGEPROVIDER_H

#include <QQuickImageProvider>

class ResourceImageProvider : public QQuickImageProvider
{
public:
    ResourceImageProvider(QQuickImageProvider::ImageType type);
    ~ResourceImageProvider();
    QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize);
    QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize);
};

#endif // RESOURCEIMAGEPROVIDER_H

