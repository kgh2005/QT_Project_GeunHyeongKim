#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsPixmapItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Startbutton_clicked();        // Start 버튼 클릭 시 호출
    void moveViewDown();                  // QGraphicsView를 아래로 이동
    void rotateWoodImage();               // Wood 이미지를 회전
    void updateLevelLabel(int value);     // 슬라이더 값 업데이트
    void on_lineEdit_textEdited(const QString &arg1); // 라인 에디트 수정 시 호출
    void on_horizontalSlider_actionTriggered(int action); // 슬라이더 동작 시 호출
    void on_Attack_clicked();              // Attack 버튼 클릭 시 호출
    void moveKnife();                      // Knife 애니메이션 이동
    void updateKnifeLabel();               // Knife QLabel 업데이트

private:
    Ui::MainWindow *ui;                   // UI 객체 포인터
    QGraphicsScene *scene;                 // 초기 이미지 씬
    QGraphicsScene *sceneWood;             // Wood 씬
    QGraphicsScene *sceneKnife;            // Knife 씬
    QTimer *timer;                         // QGraphicsView 이동 타이머
    QTimer *rotationTimer;                 // Wood 회전 타이머
    QTimer *knifeTimer;                    // Knife 애니메이션을 위한 타이머
    QGraphicsPixmapItem *negativeImageItem; // Wood 이미지 아이템
    int xPos;                              // QGraphicsView의 초기 x 좌표
    int yPos;                              // QGraphicsView의 초기 y 좌표
    bool isMoving;                         // 현재 이동 중인지 여부를 나타내는 변수
    int rotationAngle;                     // Wood의 회전 각도
    int knifeYPos;                         // Knife의 y 좌표
    bool isRotating;                       // 회전 상태를 위한 변수
    int attackCount;                       // Attack 버튼 클릭 횟수
    bool isKnifeMoving;                    // Knife 애니메이션 상태를 나타내는 변수
};

#endif // MAINWINDOW_H
