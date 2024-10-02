#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , xPos(90)  // 초기 x 좌표
    , yPos(110) // 초기 y 좌표
    , isMoving(false)  // 현재 이동 중인지 여부를 나타내는 변수
    , rotationAngle(0) // 회전 각도
    , knifeYPos(0)     // Knife 초기 y 좌표 설정
    , isRotating(true)  // 회전 상태
    , attackCount(0)    // Attack 버튼 클릭 횟수 초기화
    , isKnifeMoving(false) // Knife 애니메이션 상태
{
    ui->setupUi(this);

    // QTimer 초기화
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::moveViewDown);

    // 회전을 위한 타이머 초기화
    rotationTimer = new QTimer(this);
    connect(rotationTimer, &QTimer::timeout, this, &MainWindow::rotateWoodImage);

    // Knife 애니메이션 타이머 초기화
    knifeTimer = new QTimer(this);
    connect(knifeTimer, &QTimer::timeout, this, &MainWindow::moveKnife); // moveKnife와 연결

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
    sceneWood = new QGraphicsScene(this);  // Wood를 위한 새로운 씬 생성
    ui->Wood->setScene(sceneWood);  // Wood QGraphicsView에 씬 설정

    // Knife_image QGraphicsView에 대한 설정
    sceneKnife = new QGraphicsScene(this);  // Knife_image를 위한 새로운 씬 생성
    ui->Knife_image->setScene(sceneKnife);  // Knife QGraphicsView에 씬 설정

    // Wood QGraphicsView에서 스크롤바 숨기기
    ui->Wood->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Wood->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Knife_image QGraphicsView에서 스크롤바 숨기기
    ui->Knife_image->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Knife_image->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Wood 이미지 추가 및 크기 조절
    QPixmap negativePixmap(":/image/target.png");  // 이미지 경로 설정
    QPixmap scaledNegativePixmap = negativePixmap.scaled(200, 200, Qt::KeepAspectRatio);  // 크기 조정
    negativeImageItem = sceneWood->addPixmap(scaledNegativePixmap);
    negativeImageItem->setPos(0, 0);  // 이미지를 초기 위치에 배치

    // Knife 이미지 추가 및 크기 조절
    QPixmap knifePixmap(":/image/knife.png");  // 이미지 경로 설정
    QPixmap scaledKnifePixmap = knifePixmap.scaled(100, 100, Qt::KeepAspectRatio);  // 크기 조정
    QGraphicsPixmapItem *knifeImageItem = sceneKnife->addPixmap(scaledKnifePixmap);
    knifeImageItem->setPos(0, 0);  // 이미지를 초기 위치에 배치

    // 초기 상태에서 Wood와 Knife 이미지를 숨김
    ui->Wood->setVisible(false);
    ui->Knife_image->setVisible(false);

    // Level QSlider 설정
    ui->Level->setRange(1, 5);  // 슬라이더 범위 설정
    ui->Level->setValue(1);  // 초기 값 설정
    connect(ui->Level, &QSlider::valueChanged, this, &MainWindow::updateLevelLabel);
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

        // Level QSlider의 현재 값을 QLabel에 표시
        updateLevelLabel(ui->Level->value());
    }
}

void MainWindow::moveViewDown()
{
    // QGraphicsView의 y좌표를 변경하여 아래로 이동
    yPos += 1;  // y 좌표를 1만큼 아래로 이동
    ui->Startimage->move(xPos, yPos);  // QGraphicsView의 새로운 위치 설정

    // Startimage가 화면 하단에 도달하면 Wood와 Knife 이미지를 나타냄
    if (yPos >= height()) {
        timer->stop();  // 타이머 중지
        isMoving = false;  // 이동 중 아님으로 설정

        ui->Wood->setVisible(true);
        ui->Knife_image->setVisible(true);

        // Wood 이미지 회전 시작
        rotationTimer->start(16);  // 약 60 FPS로 회전 (16ms마다 rotateWoodImage 호출)
    }
}

void MainWindow::rotateWoodImage()
{
    if (isRotating) {
        // Wood 이미지 회전
        int speed = ui->Level->value();  // QSlider의 현재 값을 가져옴 (1~5)
        rotationAngle += (5 * speed);    // 회전 각도를 speed에 비례하여 증가시킴
        if (rotationAngle >= 180) {
            rotationAngle = 180; // 180도를 넘지 않도록 설정
            isRotating = false;  // 회전 상태를 멈춤

            // 1~3초 사이의 랜덤 시간 생성
            int randomDelay = QRandomGenerator::global()->bounded(1000, 3000); // 1000ms (1초)부터 3000ms (3초) 사이
            QTimer::singleShot(randomDelay, this, [this]() { // 랜덤 시간 후 다시 회전 시작
                isRotating = true; // 회전 상태를 다시 활성화
                rotationAngle = 0; // 각도 초기화
            });
        }
        negativeImageItem->setRotation(rotationAngle);  // 이미지 회전 적용
    }
}

void MainWindow::updateLevelLabel(int value)
{
    ui->levelSlider->setText(QString::number(value));  // QLabel에 슬라이더 값 표시
}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    // 라인 에디트에 텍스트 입력 시 동작 설정
}

void MainWindow::on_horizontalSlider_actionTriggered(int action)
{
    // 슬라이더 동작 설정
}

void MainWindow::on_Attack_clicked()
{
    if (!isKnifeMoving) { // Knife가 이미 움직이고 있지 않은 경우에만 시작
        attackCount++;  // 공격 횟수 증가
        ui->Knife->setText(QString::number(attackCount));  // QLabel에 공격 횟수 표시

        // Knife 애니메이션 시작
        knifeYPos = ui->Knife_image->y();  // 현재 Knife의 y좌표 가져오기
        knifeTimer->start(16);  // 약 60 FPS로 moveKnife 호출
        isKnifeMoving = true; // Knife가 움직이고 있음을 표시
    }
}

void MainWindow::moveKnife()
{
    if (!isKnifeMoving) {
        return; // Knife가 움직이고 있지 않으면 아무것도 하지 않음
    }

    // Knife를 위로 이동
    knifeYPos -= 10;  // y좌표를 위로 10씩 감소
    ui->Knife_image->move(ui->Knife_image->x(), knifeYPos);  // 새로운 위치 설정

    // Knife가 y축 70에 도달하면 초기 위치로 돌아감
    if (knifeYPos <= 50) {
        knifeYPos = 430; // 초기 위치로 재설정
        ui->Knife_image->move(ui->Knife_image->x(), knifeYPos); // Knife를 초기 위치에 배치
        knifeTimer->stop();  // 타이머 중지
        isKnifeMoving = false; // Knife가 더 이상 움직이지 않음을 표시
        return;  // 추가적인 처리를 방지하기 위해 함수 종료
    }

    // 충돌 체크
    QRect knifeRect = ui->Knife_image->geometry();  // Knife의 현재 위치 가져오기
    QRectF woodRect = negativeImageItem->mapRectToScene(negativeImageItem->boundingRect());

    // 충돌 감지
    if (knifeRect.bottom() >= woodRect.top() && knifeRect.left() < woodRect.right() && knifeRect.right() > woodRect.left()) {
        ui->Score->setText(QString::number(ui->Score->text().toInt() + 1)); // 점수 증가

        // Knife와 Wood 모두 정지
        knifeTimer->stop(); // 현재 애니메이션 중지
        rotationTimer->stop(); // Wood 회전 중지

        // 1초 후에 다시 애니메이션 시작
        QTimer::singleShot(1000, this, [this]() {
            knifeYPos = 430; // 초기 위치로 재설정
            ui->Knife_image->move(ui->Knife_image->x(), knifeYPos); // Knife를 초기 위치에 배치
            knifeTimer->start(16); // 다시 애니메이션 시작
            rotationTimer->start(16); // Wood 회전 재개
            isRotating = true; // Wood 회전 상태 재개
            isKnifeMoving = false; // Knife가 더 이상 움직이지 않음을 표시
        });
    }

    // Knife가 Wood의 위치에 도달하면 타이머 중지
    if (knifeYPos <= (ui->Wood->y() - ui->Knife_image->height())) {
        knifeTimer->stop();  // 타이머 중지
        knifeYPos = 430;       // y좌표 초기화
        ui->Knife_image->move(ui->Knife_image->x(), knifeYPos); // Knife를 초기 위치에 배치
        isKnifeMoving = false; // Knife가 더 이상 움직이지 않음을 표시
    }
}

void MainWindow::updateKnifeLabel()
{
    ui->Knife->setText(QString::number(attackCount));  // QLabel에 공격 횟수 표시
}
