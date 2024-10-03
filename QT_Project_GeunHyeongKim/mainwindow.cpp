#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "player.h"
#include <QRandomGenerator>
#include <iostream>
#include <QDesktopServices>
#include <QUrl>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , xPos(90)  // 초기 x 좌표
    , yPos(110) // 초기 y 좌표
    , Move(false)  // 현재 이동 중인지 여부를 나타내는 변수
    , rotationAngle(0) // 회전 각도
    , knifeYPos(0)     // Knife 초기 y 좌표 설정
    , Turn(true)  // 회전 상태
    , attackCount(0)    // Attack 버튼 클릭 횟수 초기화
    , isKnifeMoving(false) // Knife 애니메이션 상태
{
    ui->setupUi(this);

    ui->rankList->setVisible(false);

    playerName = "";

    // QTimer 초기화
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::moveViewDown);

    // 회전을 위한 타이머 초기화
    rotationTimer = new QTimer(this);
    connect(rotationTimer, &QTimer::timeout, this, &MainWindow::rotateWoodImage);

    // Knife 타이머 초기화
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
    sceneWood = new QGraphicsScene(this);  // Wood
    ui->Wood->setScene(sceneWood);  // Wood QGraphicsView

    // Knife_image QGraphicsView에 대한 설정
    sceneKnife = new QGraphicsScene(this);  // Knife_image
    ui->Knife_image->setScene(sceneKnife);  // Knife QGraphicsView

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
    ui->Attack->setVisible(false);

    // Level QSlider 설정
    ui->Level->setRange(1, 5);  // 슬라이더 범위 설정
    ui->Level->setValue(1);  // 초기 값 설정
    connect(ui->Level, &QSlider::valueChanged, this, &MainWindow::updateLevelLabel);

    // QLineEdit의 textEdited 시그널과 슬롯 연결
    connect(ui->Name, &QLineEdit::textEdited, this, &MainWindow::on_lineEdit_textEdited);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Startbutton_clicked()
{
    // 버튼 클릭 시 QGraphicsView 이동 시작
    if (!Move) {
        Move = true;  // 이동 중임을 표시
        timer->start(1);  // 1ms마다 moveViewDown 호출

        // 점수를 초기화하고 QLabel에 표시
        ui->Score->setText("0");

        // Level QSlider의 현재 값을 QLabel에 표시
        updateLevelLabel(ui->Level->value());

        // Attack 버튼 보이기
        ui->Attack->setVisible(true); // Attack 버튼을 보이도록 설정

        // rankList QLabel 숨기기
        ui->rankList->setVisible(false);  // 게임 시작 시 숨김
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
        Move = false;  // 이동 중 아님으로 설정

        ui->Wood->setVisible(true);
        ui->Knife_image->setVisible(true);

        // Wood 이미지 회전 시작
        rotationTimer->start(16);
    }
}

void MainWindow::rotateWoodImage()
{
    if (Turn) {
        // Wood 이미지 회전
        int speed = ui->Level->value();  // QSlider의 현재 값을 가져옴 (1~5)
        rotationAngle += (2.5 * speed);    // 회전 각도 speed
        if (rotationAngle >= 180) {
            rotationAngle = 180; // 180도를 넘지 않도록 설정
            Turn = false;  // 회전 상태를 멈춤

            // 1~3초 사이의 랜덤 시간 생성
            int randomDelay = QRandomGenerator::global()->bounded(1000, 3000);
            QTimer::singleShot(randomDelay, this, [this]() { // 랜덤 시간 후 다시 회전 시작
                Turn = true; // 회전 상태를 다시 활성화
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
    playerName = arg1; // QLineEdit에서 입력받은 값을 playerName 변수에 저장
    ui->Name->setText(playerName); // QLabel에 플레이어 이름 출력
    std::cout << "Current Player Name: " << playerName.toStdString() << std::endl; // 플레이어 이름 출력
}


void MainWindow::on_horizontalSlider_actionTriggered(int action)
{

}

void MainWindow::on_Attack_clicked()
{
    if (!isKnifeMoving) {
        attackCount++;
        ui->Knife->setText(QString::number(attackCount));

        knifeYPos = ui->Knife_image->y();
        knifeTimer->start(16);
        isKnifeMoving = true;

        if (attackCount > 5) {
            // Player 객체 생성
            Player player(playerName, ui->Level->value(), ui->Score->text().toInt());

            ui->SuccessFail->setText("Fail");
            ui->SuccessFail->setVisible(true);
            ui->rankList->setVisible(true);  // Fail 시 rankList 보이기

            // 파일에서 기존 Player 정보를 불러옴
            std::vector<Player> players = Player::loadFromFile();

            // 새 Player 객체를 players 벡터에 추가
            players.push_back(player);

            // 내림차순으로 랭킹을 정렬 (Level 우선, 그 다음 Score)
            std::sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
                if (a.getLevel() == b.getLevel()) {
                    return a.getScore() > b.getScore(); // 점수가 같으면 Score로 비교
                }
                return a.getLevel() > b.getLevel(); // Level 우선 비교
            });

            // 파일에 업데이트된 랭킹을 저장
            Player::saveRankingToFile(players);

            // rankList QLabel에 랭킹을 표시
            QString rankingText;
            for (const auto& player : players) {
                rankingText += player.getRankingString() + "\n\n\n";
            }
            ui->rankList->setText(rankingText); // QLabel에 랭킹 텍스트 추가

            // Level과 Score 초기화
            ui->Level->setValue(1);
            ui->Score->setText("0");
            attackCount = 0;
            ui->Knife->setText(QString::number(attackCount));

            knifeTimer->stop();

            // 1초 후 초기화
            QTimer::singleShot(1000, this, [this]() {
                ui->SuccessFail->setVisible(false);
                resetToInitialState();
            });
        }
    }
}





void MainWindow::resetToInitialState()
{
    xPos = 90;
    yPos = 110;
    ui->Startimage->move(xPos, yPos);
    ui->Knife_image->move(ui->Knife_image->x(), 430);
    knifeYPos = 430;

    ui->Knife_image->setVisible(false);
    ui->Attack->setVisible(false);
    ui->Score->setText("0");
    attackCount = 0;

    Move = false;
    isKnifeMoving = false;

    ui->Startbutton->setEnabled(true);
}


void MainWindow::moveKnife()
{
    if (!isKnifeMoving) {
        return; // Knife가 움직이고 있지 않으면 아무것도 하지 않음
    }

    // Knife를 위로 이동
    knifeYPos -= 10;
    ui->Knife_image->move(ui->Knife_image->x(), knifeYPos);  // 새로운 위치 설정


    if (knifeYPos <= 50) {
        knifeYPos = 430;
        ui->Knife_image->move(ui->Knife_image->x(), knifeYPos);
        knifeTimer->stop();
        isKnifeMoving = false;
        return;
    }

    // 충돌 체크
    QRect knifeRect = ui->Knife_image->geometry();  // Knife의 현재 위치 가져오기
    QRectF woodRect = negativeImageItem->mapRectToScene(negativeImageItem->boundingRect());

    // 충돌 감지
    if (knifeRect.bottom() >= woodRect.top() && knifeRect.left() < woodRect.right() && knifeRect.right() > woodRect.left()) {
        ui->Score->setText(QString::number(ui->Score->text().toInt() + 1)); // 점수 증가

        // 점수가 2 이상이면 "Good" 표시
        if (ui->Score->text().toInt() >= 2) {
            ui->SuccessFail->setText("Good");
            ui->SuccessFail->setVisible(true);

            // Level을 1 증가시키고 최대 값을 넘지 않도록 설정
            int newLevel = ui->Level->value() + 1;
            if (newLevel <= ui->Level->maximum()) {
                ui->Level->setValue(newLevel); // Level을 1 증가시킴
            }

            // attackCount 초기화
            attackCount = 0;
            ui->Knife->setText(QString::number(attackCount));  // QLabel에 공격 횟수 표시

            // 1초 후에 SuccessFail QLabel을 숨김
            QTimer::singleShot(1000, this, [this]() {
                ui->SuccessFail->setVisible(false); // 다시 숨김
            });

            ui->Score->setText("0"); // 점수 초기화
        }

        // Knife와 Wood 모두 정지
        knifeTimer->stop();
        rotationTimer->stop();

        // 1초 후에 다시 시작
        QTimer::singleShot(1000, this, [this]() {
            ui->Knife_image->setVisible(false);
            knifeYPos = 430; // 초기 위치로 재설정
            ui->Knife_image->move(ui->Knife_image->x(), knifeYPos); // Knife를 초기 위치에 배치
            ui->Knife_image->setVisible(true);
            knifeTimer->start(16); // 다시 애니메이션 시작
            rotationTimer->start(16); // Wood 회전 재개
            Turn = true; // Wood 회전 상태 재개
            isKnifeMoving = false; // Knife가 더 이상 움직이지 않음을 표시
        });
    }

    // Knife가 Wood의 위치에 도달하면 타이머 중지
    if (knifeYPos <= (ui->Wood->y() - ui->Knife_image->height())) {
        knifeTimer->stop();  // 타이머 중지
        ui->Knife_image->setVisible(false);
        knifeYPos = 430;       // y좌표 초기화
        ui->Knife_image->move(ui->Knife_image->x(), knifeYPos); // Knife를 초기 위치에 배치
        ui->Knife_image->setVisible(true);
        isKnifeMoving = false; // Knife가 더 이상 움직이지 않음을 표시
    }
}


void MainWindow::updateKnifeLabel()
{
    ui->Knife->setText(QString::number(attackCount));  // QLabel에 공격 횟수 표시
}



void MainWindow::on_rankList_linkActivated(const QString &link)
{

}
