#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , xPos(90)  // 초기 x 좌표
    , yPos(110) // 초기 y 좌표
    , isMoving(false)  // 현재 이동 중인지 여부를 나타내는 변수
{
    ui->setupUi(this);

    // QTimer 초기화
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::moveViewDown);

    // QGraphicsScene 생성
    scene = new QGraphicsScene(this);
    ui->Startimage->setScene(scene);

    // QGraphicsView에서 스크롤바 숨기기
    ui->Startimage->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Startimage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 이미지 추가
    QPixmap StartimagePixmap(":/image/logo.png");  // 이미지 경로 설정
    QGraphicsPixmapItem *startimageItem = scene->addPixmap(StartimagePixmap);
    startimageItem->setPos(0, 0);  // 이미지를 초기 위치에 배치

    // QGraphicsView의 초기 위치 설정
    ui->Startimage->move(xPos, yPos);  // 지정된 위치로 이동

    // Wood QGraphicsView에 대한 설정
    sceneWood = new QGraphicsScene(this);  // Negative를 위한 새로운 씬 생성
    ui->Wood->setScene(sceneWood);  // Negative QGraphicsView에 씬 설정

    // Wood QGraphicsView에서 스크롤바 숨기기
    ui->Wood->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Wood->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Wood QGraphicsView의 배경을 투명하게 설정
    ui->Wood->setStyleSheet("background: transparent;");

    // Wood 이미지 추가 및 크기 조절
    QPixmap negativePixmap(":/image/target.png");  // 이미지 경로 설정
    QPixmap scaledPixmap = negativePixmap.scaled(200, 200, Qt::KeepAspectRatio);  // 크기 조정
    QGraphicsPixmapItem *negativeImageItem = sceneWood->addPixmap(scaledPixmap);
    negativeImageItem->setPos(0, 0);  // 이미지를 초기 위치에 배치

    // 초기 상태에서 Wood를 숨김
    ui->Wood->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Startbutton_clicked()
{
    // 버튼 클릭 시 QGraphicsView 이동 시작
    if (!isMoving) {
        isMoving = true;  // 이동 중임을 표시
        timer->start(1);  // 1ms마다 moveViewDown 호출
    }
}

void MainWindow::moveViewDown()
{
    // QGraphicsView의 y좌표를 변경하여 아래로 이동
    yPos += 1;  // y 좌표를 1만큼 아래로 이동
    ui->Startimage->move(xPos, yPos);  // QGraphicsView의 새로운 위치 설정

    // Startimage가 화면 하단에 도달하면 Wood를 나타냄
    if (yPos >= height()) {
        timer->stop();  // 타이머 중지
        isMoving = false;  // 이동 중 아님으로 설정

        // Wood QGraphicsView를 보이게 함
        ui->Wood->setVisible(true);
    }
}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{

}

void MainWindow::on_horizontalSlider_actionTriggered(int action)
{

}
