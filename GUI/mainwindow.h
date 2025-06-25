#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <queue>
#include <unordered_map>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Patient {
    QString name;
    int age;
    QString problem;
    int priority;

    bool operator<(const Patient& other) const {
        return priority > other.priority;
    }
};

class MainWindow :

public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_serveButton_clicked();
    void on_showButton_clicked();
    void on_searchButton_clicked();
    void on_removeButton_clicked();
    void on_exitButton_clicked();

    void on_pushButton_5_clicked();


    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    std::priority_queue<Patient> pq;
    std::vector<Patient> patientList;
    std::unordered_map<QString, int> problemPriority;
};

#endif // MAINWINDOW_H
