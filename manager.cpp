#include "manager.h"

Manager::Manager(QWidget *parent) : QWidget(parent)
{
    ants_label = new QLabel("Ants number:");
    iters_label = new QLabel("Iters number:");
    alpha_value_label = new QLabel("Alpha value:");
    beta_value_label = new QLabel("Beta value:");
    alpha_bias_label = new QLabel("Alpha bias:");
    beta_bias_label = new QLabel("Beta bias:");
    rou_value_label = new QLabel("Rou value:");
    increment_label = new QLabel("Increment:");
    ants_spinbox = new QSpinBox();
    ants_spinbox->setRange(1, 1000);
    ants_spinbox->setSingleStep(1);
    ants_spinbox->setValue(10);
    iters_spinbox = new QSpinBox();
    iters_spinbox->setRange(1, 100);
    iters_spinbox->setSingleStep(1);
    iters_spinbox->setValue(6);
    alpha_value_spinbox = new QDoubleSpinBox();
    alpha_value_spinbox->setRange(0.0, 10.0);
    alpha_value_spinbox->setSingleStep(1);
    alpha_value_spinbox->setValue(4);
    beta_value_spinbox = new QDoubleSpinBox();
    beta_value_spinbox->setRange(0.0, 10.0);
    beta_value_spinbox->setSingleStep(1);
    beta_value_spinbox->setValue(4);
    alpha_bias_spinbox = new QDoubleSpinBox();
    alpha_bias_spinbox->setRange(0.0, 10.0);
    alpha_bias_spinbox->setSingleStep(1);
    alpha_bias_spinbox->setValue(2);
    beta_bias_spinbox = new QDoubleSpinBox();
    beta_bias_spinbox->setRange(0.0, 10.0);
    beta_bias_spinbox->setSingleStep(1);
    beta_bias_spinbox->setValue(2);
    rou_value_spinbox = new QDoubleSpinBox();
    rou_value_spinbox->setRange(0.0, 1.0);
    rou_value_spinbox->setSingleStep(0.05);
    rou_value_spinbox->setValue(0.2);
    increment_spinbox = new QDoubleSpinBox();
    increment_spinbox->setRange(0.0, 100.0);
    increment_spinbox->setSingleStep(1);
    increment_spinbox->setValue(20);

    record_label = new QLabel("Record:");
    record_spinbox = new QSpinBox();
    record_spinbox->setValue(-1);
    record_spinbox->setRange(-1, 100000);
    push_label = new QLabel("Push:");
    push_spinbox = new QSpinBox();
    push_spinbox->setValue(20);
    push_spinbox->setRange(1, 200);


    QHBoxLayout *mainLayout = new QHBoxLayout();
    QFormLayout *leftLayout = new QFormLayout();
    QFormLayout *rightLayout = new QFormLayout();
    leftLayout->addRow(ants_label, ants_spinbox);
    leftLayout->addRow(alpha_value_label, alpha_value_spinbox);
    leftLayout->addRow(beta_value_label, beta_value_spinbox);
    leftLayout->addRow(rou_value_label, rou_value_spinbox);
    leftLayout->addRow(record_label, record_spinbox);
    rightLayout->addRow(iters_label, iters_spinbox);
    rightLayout->addRow(alpha_bias_label, alpha_bias_spinbox);
    rightLayout->addRow(beta_bias_label, beta_bias_spinbox);
    rightLayout->addRow(increment_label, increment_spinbox);
    rightLayout->addRow(push_label, push_spinbox);
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    this->setLayout(mainLayout);
}

int Manager::ants_num()
{
    return ants_spinbox->value();
}

int Manager::iters_num()
{
    return iters_spinbox->value();
}

double Manager::alpha_value()
{
    return alpha_value_spinbox->value();
}

double Manager::beta_value()
{
    return beta_value_spinbox->value();
}

double Manager::alpha_bias()
{
    return alpha_bias_spinbox->value();
}

double Manager::beta_bias()
{
    return beta_bias_spinbox->value();
}

double Manager::rou_value()
{
    return rou_value_spinbox->value();
}

double Manager::increment_value()
{
    return increment_spinbox->value();
}

double Manager::push_value()
{
    return push_spinbox->value();
}

int Manager::record()
{
    return record_spinbox->value();
}

void Manager::on_record_update(int new_record)
{
    if (new_record == -1   // 当重置地图等操作时，设置纪录为-1
        || record_spinbox->value() == -1  // 当前还未有过纪录
        || new_record < record_spinbox->value()) {  // 突破记录
        record_spinbox->setValue(new_record);
    }
}
