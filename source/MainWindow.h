//
// Created by zhb15 on 1/24/24.
//

#ifndef TEST_MAINWINDOW_H
#define TEST_MAINWINDOW_H

#include <memory>

#include <QMainWindow>
#include <QDebug>
#include <QLabel>
#include <QImage>
#include <QTimer>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>

#define DATA_PATH "../data/"

class MainWindow: public QMainWindow {
    Q_OBJECT;
public:
    using camera_ptr = std::unique_ptr<cv::VideoCapture, void (*)(cv::VideoCapture *)>;

    explicit MainWindow(QWidget *parent = nullptr);

    QImage CvMat2QImage(cv::Mat);
private:
    QLabel *picturePlane;
    QPushButton *openCameraButton;
    QPushButton *closeCameraButton;
    QTimer *timer;

    cv::Mat frame;
    std::vector<cv::Rect> detections {};
    cv::CascadeClassifier faceCascade {};
    static void DeleteCamera(cv::VideoCapture *device) { device->release(); }
    camera_ptr camera {camera_ptr(new cv::VideoCapture{}, DeleteCamera)};
};

#endif //TEST_MAINWINDOW_H