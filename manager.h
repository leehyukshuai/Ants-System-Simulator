#ifndef MANAGER_H
#define MANAGER_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QFormLayout>

class Manager : public QWidget
{
    Q_OBJECT
private:
    QLabel *ants_label;
    QLabel *iters_label;
    QLabel *alpha_value_label;
    QLabel *alpha_bias_label;
    QLabel *beta_value_label;
    QLabel *beta_bias_label;
    QLabel *rou_value_label;
    QLabel *increment_label;
    QSpinBox *ants_spinbox;
    QSpinBox *iters_spinbox;
    QDoubleSpinBox *alpha_value_spinbox;
    QDoubleSpinBox *alpha_bias_spinbox;
    QDoubleSpinBox *beta_value_spinbox;
    QDoubleSpinBox *beta_bias_spinbox;
    QDoubleSpinBox *rou_value_spinbox;
    QDoubleSpinBox *increment_spinbox;
    // some new
    QLabel *record_label; // 记录当前突破的目标
    QSpinBox *record_spinbox;
    QLabel *push_label;     // 记录push的力度
    QSpinBox *push_spinbox;

public:
    explicit Manager(QWidget *parent = nullptr);
    int ants_num();
    int iters_num();
    double alpha_value();
    double beta_value();
    double alpha_bias();
    double beta_bias();
    double rou_value();
    double increment_value();
    double push_value();
    int record();

public slots:
    void on_record_update(int new_record);
};

#endif // MANAGER_H
