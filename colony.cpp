#include "colony.h"

Colony::Colony(QVector<QPoint> &map, int ants_num, double _rou, double _increment, int _record, int _push, double _alpha_value, double _beta_value, double _alpha_bias, double _beta_bias)
{
    n = map.size();
    rou = _rou;
    increment = _increment;
    target = _record;
    push = _push;
    best = 0x7fffffff;
    dist.resize(n);
    pher.resize(n);
    for (int i = 0; i < n; ++i) {
        dist[i].resize(n);
        pher[i].resize(n);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            // 使用集合距离
//            dist[i][j] = dist[j][i] = sqrt(pow(map[i].x() - map[j].x(), 2) + pow(map[i].y() - map[j].y(), 2));
//                    (map[i]-map[j]).manhattanLength();
            // 使用曼哈顿距离
            dist[i][j] = dist[j][i] = (map[i]-map[j]).manhattanLength();
            pher[i][j] = pher[j][i] = 1.0;
        }
    }
    for (int i = 0; i < ants_num; ++i) {
        double alpha = _alpha_value + (qrand() % RAND_MAX * _alpha_bias / RAND_MAX);
        double beta = _beta_value + (qrand() % RAND_MAX * _beta_bias / RAND_MAX);
        ants.append(new Ant(i + 1, (alpha >= 0 ? alpha : 0), (beta >= 0 ? beta : 0)));
    }
}

Colony::~Colony()
{
    for (Ant * ant : ants) {
        delete ant;
    }
}

void Colony::update()
{
    int n = dist.size();
    for (Ant *ant : ants) {
        ant->reset();
        for (int i = 0; i < n; ++i) {
            ant->update(dist, pher);
        }
    }
    // 将ants全部sort，方便其他部件访问
    std::sort(ants.begin(), ants.end(), [](const Ant *a1, const Ant *a2){ return a1->get_length() < a2->get_length(); });
    update_pher();
    for (int i = 0; i < ants.size(); ++i) {
        ants[i]->set_rank(i+1);
    }

}

void Colony::update_pher()
{
    // 所有有向边的pher都先衰减
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            pher[i][j] *= (1 - rou);
        }
    }
    // 所有蚂蚁根据自己的表现留下pher
    for (int i = 0; i < ants.size(); ++i) {
        // 策略：优胜者多留，进步者多留
        double delta = 10 * increment / ants[i]->get_length();
        if (ants[i]->get_length() < best) { // 更新记录
            best = ants[i]->get_length();
            best_path = ants[i]->get_path();
        }
//        if (ants[i]->get_rank() != -1 && i > ants[i]->get_rank() + 5) {  // 大退步！
//            delta *= 0.1;
//        }
        if (target > 0 && ants[i]->get_length() < target) {     // 突破记录，多留一些
            delta *= push;
        }
        for (int j = 0; j < n; ++j) {
            pher[ants[i]->get_path()[j]][ants[i]->get_path()[j+1]] += delta;
        }
    }
}

int Colony::get_best() const
{
    return best;
}

const QVector<int> Colony::get_best_path() const
{
    return best_path;
}

const QVector<QVector<double> > &Colony::get_pher() const
{
    return pher;
}

const QVector<Ant *> &Colony::get_ants() const
{
    return ants;
}
