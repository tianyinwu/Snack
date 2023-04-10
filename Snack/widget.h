#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QKeyEvent>
#include<QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {class Widget;}
QT_END_NAMESPACE

//1.按键处理
//2.使用定时器
//3.渲染

enum Direct {
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN
};



class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    // 渲染、绘图
    void paintEvent(QPaintEvent *event);

    // 按键处理
    void addTop();
    void addDown();
    void addRight();
    void addLeft();

    // 添加奖品的函数
    void addNewReword();

    // 碰撞检验
    bool checkContact();

    // 按键处理
    void keyPressEvent (QKeyEvent *event);

    void deleteLast();

private:
    Ui::Widget *ui;
    // 表示方向,默认向上
    int moveFlag = DIR_RIGHT;
    bool gameStart = false;

    // 定时器
    QTimer *timer;
    int time = 100;  // 超时时间间隔

    // 蛇
    QList <QRectF> snack;

    // 奖品
    QRectF rewardNode;

    // 小方块的大小
    int nodeWidth = 20;
    int nodeHeight = 20;

protected slots:
    void timeout();
};

#endif // WIDGET_H
