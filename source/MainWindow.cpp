//
// Created by zhb15 on 1/24/24.
//

#include "MainWindow.h"

template <typename... T> inline __attribute__((__always_inline__)) void ignore_unused(T &&...) {}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    setWindowTitle(QObject::tr("Qt 5.12 - OpenCV 4"));

    setMinimumSize(1024, 512);
    setMaximumSize(1920, 1080);

    picturePlane = new QLabel();
    timer = new QTimer(this);
    openCameraButton = new QPushButton(QObject::tr("Open Camera"));
    closeCameraButton = new QPushButton(QObject::tr("Close Camera"));
    auto *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(openCameraButton);
    buttonLayout->addWidget(closeCameraButton);
    auto *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(picturePlane);
    mainLayout->addLayout(buttonLayout);
    auto *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    QObject::connect(openCameraButton, &QPushButton::clicked, [this]() {
        if(!camera->open(0)) {
            qDebug() << "Error: Unable to open camera !";
            close();
        }
        if(!faceCascade.load(DATA_PATH "haarcascade_frontalface_alt2.xml")) {
            qDebug() << "Error: when loading the face cascade classifier !";
            close();
        }
        timer->start(24);
    });
    QObject::connect(closeCameraButton, &QPushButton::clicked, [this]() {
        picturePlane->setPixmap(QPixmap{});
        timer->stop();
    });

    QObject::connect(timer, &QTimer::timeout, [this]() {
        *camera >> frame;
        faceCascade.detectMultiScale(frame, detections, 1.1, 3, 0);
        for(auto &elem: detections) {
            cv::rectangle(frame, elem, cv::Scalar(255, 0, 0));
        }
        QImage img = CvMat2QImage(frame);
        img = img.scaled(picturePlane->width(), picturePlane->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        picturePlane->setPixmap(QPixmap::fromImage(img));
    });
}

QImage MainWindow::CvMat2QImage(cv::Mat image) {
    if(1 == image.channels()) {
        return {image.data, image.cols, image.rows, image.cols * image.channels(), QImage::Format_Indexed8};
    }
    if(3 == image.channels()) {
        cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
        return {image.data, image.cols, image.rows, image.cols * image.channels(), QImage::Format_RGB888};
    }
    return {};
}