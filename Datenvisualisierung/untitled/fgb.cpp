#include <QImage>
#include <iostream>

fgb::fgb() {

}

QImage fgb::mapSliceToImage(QString path)
{
    QImage uhhlogo;
    uhhlogo.load(path);
    return uhhlogo.convertToFormat(QImage::Format_RGBA8888);

}
void fgb::setDataSlice(float* dataFromFilter)
{
    dataSlice = dataFromFilter;

}
