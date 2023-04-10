#include "widget.h"
#include "ui_widget.h"

#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 设置标题
    setWindowTitle("贪吃蛇");

    // 使用定时器
    timer = new QTimer();
    // 信号与槽
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));

    // 设定窗口大小，不可改变
    setFixedSize(512,340);

    // 初始化蛇身体
    QRectF rect(256, 170, nodeWidth, nodeHeight);
    snack.append(rect);
    addTop();
    addTop();
    addTop();
    addTop();

    // 初始化奖品
    addNewReword();
}

Widget::~Widget()
{
    delete ui;
}

// 控制方向
void Widget::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_W:
        if(moveFlag != DIR_DOWN){
            moveFlag = DIR_UP;
        }
        break;
    case Qt::Key_S:
        if(moveFlag != DIR_UP){
            moveFlag = DIR_DOWN;
        }
        break;
    case Qt::Key_A:
        if(moveFlag != DIR_RIGHT){
            moveFlag = DIR_LEFT;
        }
        break;
    case Qt::Key_D:
        if(moveFlag != DIR_LEFT){
            moveFlag = DIR_RIGHT;
        }
        break;
    case Qt::Key_Space:
        if (gameStart == false){
            gameStart = true;
            // 启动定时器
            timer->start(time);
        }else {
            gameStart = false;
            // 关闭定时器
            timer->stop();
        }
        break;
    default:
        break;
    }
}


void Widget::timeout(){
    int count = 1;
    // 判断有没有重合
    if (snack[0].intersects(rewardNode)){
        count++;
        addNewReword();
    }

    while(count--){
        switch (moveFlag){
            case DIR_UP:
                // 在顶部加一个小方块，在底部减少一个小方块
                addTop();
                break;
            case DIR_DOWN:
                addDown();
                break;
            case DIR_LEFT:
                addLeft();
                break;
            case DIR_RIGHT:
                addRight();
                break;
            default:
                break;
        }
    }

    deleteLast();
    update();
}

void Widget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen pen;
    QBrush brush;
//    // 背景图片
//    QPixmap pix;
//    pix.load("./12.jpg");
//    painter.drawPixmap(0, 0, 1024, 680, pix);

    // 画蛇
    pen.setColor(Qt::black);
    brush.setColor(Qt::darkMagenta);
    brush.setStyle(Qt::SolidPattern);
    painter.setPen(pen);
    painter.setBrush(brush);

    for(int i =0;i<snack.length(); i++){
        painter.drawRect(snack[i]);
    }

    // 画奖品
    pen.setColor(Qt::red);
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawEllipse(rewardNode);

    if (checkContact()){
        QFont font("方正舒体", 30, QFont::ExtraLight, false);
        painter.setFont(font);
        painter.drawText((this->width()-500)/2,
                         (this->height()-30)/2,
                         QString("GAME OVER!"));
        timer->stop();
    }

    QWidget::paintEvent(event);
}

// 删除最后一截
void Widget::deleteLast(){
    snack.removeLast();
}

// 往上走
void Widget::addTop(){
    QPointF leftTop;
    QPointF rightBottom;

    if (snack[0].y() - nodeHeight < 0){
        leftTop = QPointF(snack[0].x(),this->height()-nodeHeight);
        rightBottom = QPoint(snack[0].x() + nodeWidth, this->height());
    }else {
        leftTop = QPointF(snack[0].x(),snack[0].y()-nodeHeight);
        rightBottom = snack[0].topRight();
    }

    snack.insert(0, QRectF(leftTop, rightBottom));
}

// 往下走
void Widget::addDown(){
    QPointF leftTop;
    QPointF rightBottom;

    if (snack[0].y() + nodeHeight*2 > this->height()){
        leftTop = QPointF(snack[0].x(),0);
        rightBottom = QPoint(snack[0].x() + nodeWidth, nodeHeight);
    }else {
        leftTop = snack[0].bottomLeft();
        rightBottom = snack[0].bottomRight() + QPoint(0, nodeHeight);
    }

    snack.insert(0, QRectF(leftTop, rightBottom));
}

// 往左走
void Widget::addLeft(){
    QPointF leftTop;
    QPointF rightBottom;

    if (snack[0].x() - nodeWidth < 0){
        leftTop = QPointF(this->width() - nodeWidth, snack[0].y());
    }else {
        leftTop = snack[0].topLeft() - QPoint(nodeWidth, 0);
    }
    rightBottom = leftTop + QPointF(nodeWidth, nodeHeight);
    snack.insert(0, QRectF(leftTop, rightBottom));
}

// 往右走
void Widget::addRight(){
    QPointF leftTop;
    QPointF rightBottom;

    if (snack[0].x() + nodeWidth*2 > this->width()){
        leftTop = QPointF(0, snack[0].y());
    }else {
        leftTop = snack[0].topRight();
    }
    rightBottom = leftTop + QPointF(nodeWidth, nodeHeight);
    snack.insert(0, QRectF(leftTop, rightBottom));
}

// 添加奖品
void Widget::addNewReword(){
    rewardNode = QRectF(
                qrand()%(this->width()/20) * 20,
                qrand()%(this->height()/20) * 20,
                nodeWidth,
                nodeHeight);
}

// 碰撞检测,接触到当前的点，判定为失败
bool Widget::checkContact(){
    for(int i=0;i<snack.length();i++)
        for(int j=1+i;j<snack.length();j++){
            if(snack[i] == snack[j]){
                return true;
            }
        }
    return false;
}
