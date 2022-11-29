#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QVector>
#include <QPainter>
#include <QResizeEvent>
#include <QColor>
#include "colony.h"

class Viewer : public QWidget
{
    Q_OBJECT
private:
    QPixmap canvas;
    QVector<QPoint> map;  // 地图的备份
public:
    explicit Viewer(QWidget *parent = nullptr);
    void update(const Colony *colony, bool best = 0);  // 默认显示colony中最佳路径
    void initialize(const QVector<QPoint>&_map); // 初始化地图内容
    void paintEvent(QPaintEvent *event);
    void show_path(const QVector<int> &path);
};

#endif // VIEWER_H
