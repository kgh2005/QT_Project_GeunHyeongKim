#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>  // QTimer 추가

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
    void on_Startbutton_clicked();
    void moveViewDown();  // 이동 메서드 추가

    void on_lineEdit_textEdited(const QString &arg1);
    void on_horizontalSlider_actionTriggered(int action);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;              // 그래픽 씬
    QGraphicsScene *sceneWood;          // Wood 씬 추가
    int xPos;
    int yPos;                           // y 좌표
    QTimer *timer;                      // 타이머 추가
    bool isMoving;                      // 이동 중인지 여부
    void centerViews();
};

#endif // MAINWINDOW_H
