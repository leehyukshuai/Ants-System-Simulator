#ifndef COLONY_H
#define COLONY_H
#include "ant.h"
#include <QPoint>

class Colony
{
private:
    int n;  // 城市数目
    double rou; // 信息衰散速率
    double increment;   // 蚂蚁放置信息素的量
    int target; // 希望突破的目标，如果有蚂蚁突破，给予极大的奖励(target为-1时直接忽略)
    int push;   // 奖励的力度
    int best;   // 该colony中至今为止发现的最优路径长度
    QVector<int> best_path;  // 该colony中至今为止发现的最优路径
    QVector<Ant *> ants; // 存储所有的蚂蚁指针
    QVector<QVector<int>> dist;   // 存储各个地点之间的距离
    QVector<QVector<double>> pher; // 存储各个地点之间的信息素浓度
public:
    Colony(QVector<QPoint>& map, int ants_num, double rou, double increment, int record, int push, double _alpha_value, double _beta_value,
           double _alpha_bias, double _beta_bias);  // 构造函数，需要生成所有蚂蚁并加载地图
    ~Colony();
    void update(); // 一次完整迭代，控制所有蚂蚁走完全部路程并更新信息素状态
    void update_pher();  // 更新信息素浓度
    int get_best() const;
    const QVector<int> get_best_path() const;
    const QVector<Ant *> &get_ants() const;
    const QVector<QVector<double>> &get_pher() const;

};

#endif // COLONY_H
