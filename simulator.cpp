#include "simulator.h"
#include <QDebug>

Simulator::Simulator(QWidget *parent) :
    QWidget(parent)
{
    best_record = 0x7fffffff;
    colony = nullptr;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    viewer = new Viewer();
    manager = new Manager();
    connect(this, SIGNAL(record_changed(int)), manager, SLOT(on_record_update(int)));
    info = new QTextBrowser();
    set_map = new QPushButton("Reset Map");
    connect(set_map, SIGNAL(clicked(bool)), this, SLOT(on_set_map_clicked()));
    simulate = new QPushButton("Simulate");
    connect(simulate, SIGNAL(clicked(bool)), this, SLOT(on_simulate_clicked()));
    best_btn = new QPushButton("Show");
    connect(best_btn, SIGNAL(clicked(bool)), this, SLOT(on_show_best_clicked()));
    speed_box = new QSpinBox();
    speed_box->setRange(1, 16);
    speed_box->setValue(1);

    QHBoxLayout *upperLayout = new QHBoxLayout;
    upperLayout->addWidget(viewer, 1);
    upperLayout->addWidget(info, 1);
    QHBoxLayout *lowerLayout = new QHBoxLayout;
    lowerLayout->addWidget(manager);
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(set_map);
    buttonLayout->addWidget(speed_box);
    buttonLayout->addWidget(simulate);
    buttonLayout->addWidget(best_btn);
    lowerLayout->addLayout(buttonLayout);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(lowerLayout);

    this->setWindowTitle("Ants Simulater");
    this->setLayout(mainLayout);
    this->resize(1200, 800);
    this->setStyleSheet("font: 25 9pt \"Microsoft YaHei\";");
    load_map();
}

Simulator::~Simulator()
{
}

void Simulator::update()
{
    if (count <= 0) {
        simulate_end();
        return;
    }
    count -= 1;
    colony->update();
    update_info();
    viewer->update(colony);
    QWidget::update();
}

void Simulator::update_info()
{
    info->append(QString().sprintf("Iter [%d]:", manager->iters_num() - count));
    const QVector<Ant *> &ants = colony->get_ants();
    for (int i = 0; i < ants.size(); ++i) {
        QString description;
        description.sprintf("%2d Ant[%2d] α:%.1f β:%.1f d:%2d",
                             i, ants[i]->get_id(), ants[i]->get_alpha(), ants[i]->get_beta(), ants[i]->get_length());
        info->append(description);
    }
}

void Simulator::print_summary()
{
    info->append("Summary: no summary.");
    QFile file("log.txt");
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << info->toPlainText();
        file.close();
    }
}

void Simulator::load_map()
{
    QFile file("map.txt");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        int n;
        stream >> n;
        map.resize(n);
        for (int i = 0; i < n; ++i) {
            stream >> map[i].rx() >> map[i].ry();
        }
        file.close();
        best_record = 0x7fffffff;
        best_record_path.clear();
        emit record_changed(-1);
        viewer->initialize(map);
    } else {
        qDebug() << "Can't open file";
    }
}

void Simulator::save_map()
{
    QFile file("map.txt");
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << map.size() << "\n";
        for (int i = 0; i < map.size(); ++i) {
            stream << map[i].x() << " " << map[i].y() << "\n";
        }
        file.close();
        load_map();
    }
}

void Simulator::on_show_best_clicked()
{
    viewer->show_path(best_record_path);
}

void Simulator::simulate_end()
{
    timer->stop();
    int best = colony->get_best();
    emit record_changed(best);
    viewer->update(colony, 1);
    if (colony->get_best() < best_record) {
        best_record = colony->get_best();
        best_record_path = colony->get_best_path();
    }
    print_summary();
}

void Simulator::on_simulate_clicked()
{
    if (colony) {
        delete colony;
    }
    info->append("Begin Simulator!");
    colony = new Colony(map, manager->ants_num(), manager->rou_value(), manager->increment_value(), manager->record(),
             manager->push_value(), manager->alpha_value(), manager->beta_value(), manager->alpha_bias(), manager->beta_bias());
    count = manager->iters_num();
    timer->start(1000.0 / speed_box->value());
}

void Simulator::on_set_map_clicked()
{
    bool ok;
    int size = QInputDialog::getInt(this, "Set Map Size", "Input the map size", 20, 6, 200, 1, &ok);
    if (ok) {
        map.clear();
        for (int i = 0; i < size; ++i) {
            map.append(QPoint(rand() % viewer->width(), rand() % viewer->height()));
        }
        save_map();
    }
}
