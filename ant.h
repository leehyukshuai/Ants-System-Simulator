#ifndef ANT_H
#define ANT_H
#include <QVector>
#include <QSet>

class Ant
{
private:
    int id; // 蚂蚁的唯一标识
    double alpha;   // 控制蚂蚁的信息启发因子
    double beta;    // 控制蚂蚁的自我选择因子
    int length;    // path的总长度
    int rank;   // 上一次迭代该蚂蚁的排名
    QVector<int> path;   // 记录蚂蚁走的路径
    QSet<int> visited;

public:
    Ant(int _id, double _alpha, double _beta);
    void update(const QVector<QVector<int>>&dist, const QVector<QVector<double>>&pher);  // 控制蚂蚁走到下一个地点
    int select_next(const QVector<QVector<int>>&dist, const QVector<QVector<double>>&pher);  // 选择蚂蚁下一次要走的城市
    void reset();
    int get_length() const;
    int get_rank() const;
    int get_id() const;
    double get_alpha() const;
    double get_beta() const;
    void set_rank(int _rank);
    const QVector<int> &get_path() const;

};

#endif // ANT_H
