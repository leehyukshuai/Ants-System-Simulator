#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QWidget>
#include <QMainWindow>
#include <QTextBrowser>
#include <QPushButton>
#include <QTextStream>
#include <QTimer>
#include <QVector>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QHBoxLayout>
#include <QFile>
#include "colony.h"
#include "viewer.h"
#include "manager.h"

class Simulator : public QWidget
{
    Q_OBJECT
private:
    Colony *colony;
    int count;
    QTimer *timer;
    QVector<QPoint> map;
    int best_record;
    QVector<int> best_record_path;
    Viewer *viewer;
    Manager *manager;
    QTextBrowser *info;
    QPushButton *set_map;
    QPushButton *simulate;
    QPushButton *best_btn;
    QSpinBox *speed_box;

public:
    explicit Simulator(QWidget *parent = 0);
    ~Simulator();

private:
    void update_info();  // 更新info面板
    void print_summary();    // 更新info面板，输出最后总结
    void load_map(); // 从文件map.txt中加载地图
    void save_map();    // 保存地图文件

signals:
    void record_changed(int new_record);

private slots:
    void on_show_best_clicked();    // 展示最佳路线
    void simulate_end();  // 停止计时器，设置record
    void update();   // 更新数据并刷新输出
    void on_simulate_clicked(); // 当开始按钮被按下，启动模拟
    void on_set_map_clicked();    // 当设置地图按钮被按下，重设地图
};

#endif // SIMULATOR_H
