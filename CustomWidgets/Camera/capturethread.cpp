#include <QApplication>
#include <QDataStream>
#include <QString>
#include <QDebug>
#include <QBuffer>
#include <QImage>
#include <typeinfo>
#include "capturethread.h"

#include <iostream>
#include <QFile>

#define CLEAR(x) memset(&(x), 0, sizeof(x))

CaptureThread::CaptureThread(QObject *parent) : QThread(parent)
{
    devam=false;
    fd = -1;
    n_buffers = 0;
}

void CaptureThread::run(){

    fd = -1;

    if(!deviceName.isEmpty()){
#if (QT_VERSION >= 0x050000)
        qDebug()<<"dev:"<<deviceName.toLatin1().constData();
        dev_name=(char*)deviceName.toLatin1().constData();
#else
        qDebug()<<"dev:"<<deviceName.toAscii().constData();
        dev_name=(char*)deviceName.toAscii().constData();
#endif // (QT_VERSION >= 0x050000)
    }

    fd = v4l2_open(dev_name, O_RDWR | O_NONBLOCK, 0);
    if (fd < 0) {
           qDebug("Cannot open device");
           quit();
           return;
    }


    static struct v4lconvert_data *v4lconvert_data;
    static struct v4l2_format src_fmt;
    static unsigned char *dst_buf;

    CLEAR(fmt);
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width       = 320;
    fmt.fmt.pix.height      = 240;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB24;
    fmt.fmt.pix.field       = V4L2_FIELD_INTERLACED;
    xioctl(fd, VIDIOC_S_FMT, &fmt);
    if (fmt.fmt.pix.pixelformat != V4L2_PIX_FMT_RGB24) {
           printf("Libv4l didn't accept RGB24 format. Can't proceed.\n");
           return;
    }
    if ((fmt.fmt.pix.width != 320) || (fmt.fmt.pix.height != 240))
           printf("Warning: driver is sending image at %dx%d\n",
                   fmt.fmt.pix.width, fmt.fmt.pix.height);


    v4lconvert_data = v4lconvert_create(fd);
    if (v4lconvert_data == NULL)
        qDebug("v4lconvert_create");
    if (v4lconvert_try_format(v4lconvert_data, &fmt, &src_fmt) != 0)
        qDebug("v4lconvert_try_format");
    xioctl(fd, VIDIOC_S_FMT, &src_fmt);
    dst_buf = (unsigned char*)malloc(fmt.fmt.pix.sizeimage);
    CLEAR(req);
    req.count = 2;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    xioctl(fd, VIDIOC_REQBUFS, &req);

    buffers = (buffer*)calloc(req.count, sizeof(*buffers));
    for (n_buffers = 0; n_buffers < req.count; ++n_buffers) {
           CLEAR(buf);

           buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
           buf.memory      = V4L2_MEMORY_MMAP;
           buf.index       = n_buffers;

           xioctl(fd, VIDIOC_QUERYBUF, &buf);

           buffers[n_buffers].length = buf.length;
           buffers[n_buffers].start = v4l2_mmap(NULL, buf.length,
                         PROT_READ | PROT_WRITE, MAP_SHARED,
                         fd, buf.m.offset);

           if (MAP_FAILED == buffers[n_buffers].start) {
                   qDebug("mmap");
                   return;
           }
    }

    for (unsigned int i = 0; i < n_buffers; ++i) {
           CLEAR(buf);
           buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
           buf.memory = V4L2_MEMORY_MMAP;
           buf.index = i;
           xioctl(fd, VIDIOC_QBUF, &buf);
    }
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    xioctl(fd, VIDIOC_STREAMON, &type);

    qDebug()<<"buf.timecode.type:"<< buf.timecode.type;

    int di=0;
    char header [50];
    sprintf(header,"P6\n%d %d 255\n",fmt.fmt.pix.width,fmt.fmt.pix.height);
    devam=true;
    while(devam){
        do {
                FD_ZERO(&fds);
                FD_SET(fd, &fds);

                /* Timeout. */
                tv.tv_sec = 2;
                tv.tv_usec = 0;

                r = select(fd + 1, &fds, NULL, NULL, &tv);
        } while ((r == -1 && (errno = EINTR)));
        if (r == -1) {
                qDebug("select");
                return;
        }

        CLEAR(buf);
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        xioctl(fd, VIDIOC_DQBUF, &buf);
            
        if (v4lconvert_convert(v4lconvert_data,
                                &src_fmt,
                                &fmt,
                                (unsigned char*)buffers[buf.index].start, buf.bytesused,
                                dst_buf, fmt.fmt.pix.sizeimage) < 0) {
                if (errno != EAGAIN)
                        qDebug("v4l_convert");
        }

        unsigned char* asil=(unsigned char*)malloc(fmt.fmt.pix.sizeimage+qstrlen(header));
        memmove(asil, dst_buf, fmt.fmt.pix.sizeimage);
        memmove(asil+qstrlen(header), asil, fmt.fmt.pix.sizeimage);
        memcpy(asil,header,qstrlen(header));

        QImage *qq=new QImage();
        if(qq->loadFromData(asil,fmt.fmt.pix.sizeimage+qstrlen(header),"PPM")){
            emit renderedImage(*qq);
        }
        free(asil);
        delete qq;

        xioctl(fd, VIDIOC_QBUF, &buf);
        di++;
    }

    qDebug()<<"buf.timecode.type:"<< buf.timecode.type;
    qDebug()<<"totalFrameCount:"<<di;

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    xioctl(fd, VIDIOC_STREAMOFF, &type);
    for (unsigned int i = 0; i < n_buffers; ++i)
           v4l2_munmap(buffers[i].start, buffers[i].length);

    v4l2_close(fd);
/*
    if(!deviceName.compare("/dev/video0"))
        deviceName = "/dev/video1";
    else
        deviceName = "/dev/video0";
*/

//    this->run();
}
CaptureThread::~CaptureThread()
{
    devam=false;

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    xioctl(fd, VIDIOC_STREAMOFF, &type);
    for (unsigned int i = 0; i < n_buffers; ++i)
           v4l2_munmap(buffers[i].start, buffers[i].length);

    v4l2_close(fd);

    fd = -1;
    condition.wakeOne();

    wait();
}

void CaptureThread::stopCapture()
{   
    devam=false;
    if(fd != -1)
    {
        try{
            type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            xioctl(fd, VIDIOC_STREAMOFF, &type);
            v4l2_close(fd);
        }catch(...){}
        fd = -1;
    }
    quit();

    qDebug()<<"stop camera capture";
}

void CaptureThread::startCapture()
{
        qDebug()<<"start camera capture";
        this->start();
}
/*
void CaptureThread::onStopCapture()
{
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    xioctl(fd, VIDIOC_STREAMOFF, &type);
    for (int i = 0; i < n_buffers; ++i)
           v4l2_munmap(buffers[i].start, buffers[i].length);
    v4l2_close(fd);
}*/

void CaptureThread::setDeviceName(QString fileN) {
    deviceName=fileN;
}

QString CaptureThread::getDeviceName()
{
    return deviceName;
}
