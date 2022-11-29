#include "viewer.h"
#include <QDebug>

Viewer::Viewer(QWidget *parent) : QWidget(parent)
{
}

void Viewer::update(const Colony *colony, bool best)
{
    canvas = QPixmap(size());
    canvas.fill();
    QPainter painter(&canvas);
    // 先绘制各个结点
    QPen dotPen(Qt::black);
    dotPen.setWidth(10);
    painter.setPen(dotPen);
    foreach (QPoint p, map) {
        painter.drawPoint(p);
    }
    if (colony) {
        // 绘制出信息素路径
        QColor pherColor("orange");
        QPen blurPen;
        blurPen.setWidth(6);
        const QVector<QVector<double>> &pher = colony->get_pher();
        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map.size(); ++j) {
                pherColor.setAlpha((pher[i][j] * 10.0 > 255) ? 255 : pher[i][j] * 10.0);
                blurPen.setColor(pherColor);
                painter.setPen(blurPen);
                painter.drawLine(map[i], map[j]);
            }
        }
        // 绘制出历史最短路径
        QPen bestPen(QColor(0, 255, 100, 200));
        bestPen.setWidth(1);
        painter.setPen(bestPen);
        const QVector<int> &best_path = colony->get_best_path();
        for (int i = 1; i < best_path.size(); ++i) {
            painter.drawLine(map[best_path[i-1]], map[best_path[i]]);
        }
        // 绘制出当前最短路径
        QPen linePen(QColor("blue"));
        linePen.setWidth(1);
        painter.setPen(linePen);
        const Ant *ant = colony->get_ants().at(0);
        const QVector<int> &path = ant->get_path();
        for (int i = 1; i < path.size(); ++i) {
            painter.drawLine(map[path[i-1]], map[path[i]]);
        }
    }
}

void Viewer::initialize(const QVector<QPoint> &_map)
{
    map = _map;
    update(nullptr);
}

void Viewer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), canvas);
    QWidget::paintEvent(event);
}

void Viewer::show_path(const QVector<int> &path)
{
    QPainter painter(&canvas);
    QPen pen(Qt::red);
    pen.setWidth(4);
    painter.setPen(pen);
    for (int i = 1; i < path.size(); ++i) {
        painter.drawLine(map[path[i-1]], map[path[i]]);
    }
    repaint();
}
