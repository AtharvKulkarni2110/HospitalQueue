#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Problem -> Priority
    problemPriority["heart attack"] = 1;
    problemPriority["fracture"] = 2;
    problemPriority["fever"] = 4;
    problemPriority["cold"] = 5;
    problemPriority["checkup"] = 6;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_addButton_clicked() {
    QString name = ui->nameEdit->text();
    int age = ui->ageEdit->text().toInt();
    QString problem = ui->problemEdit->text();
    int priority = problemPriority.count(problem) ? problemPriority[problem] : 10;


    Patient p{name, age, problem, priority};
    pq.push(p);
    patientList.push_back(p);
    ui->outputBox->append("Added: " + name + ", Priority: " + QString::number(priority));
}

void MainWindow::on_serveButton_clicked() {
    if (pq.empty()) {
        ui->outputBox->append("No patients to serve.");
        return;
    }

    Patient p = pq.top(); pq.pop();

    auto it = std::remove_if(patientList.begin(), patientList.end(), [&](Patient& x) {
        return x.name == p.name && x.age == p.age && x.problem == p.problem;
    });
    patientList.erase(it, patientList.end());

    ui->outputBox->append("Serving: " + p.name + " (" + p.problem + ")");
}

void MainWindow::on_showButton_clicked() {
    ui->outputBox->append("Current Queue:");
    auto temp = pq;
    while (!temp.empty()) {
        Patient p = temp.top(); temp.pop();
        ui->outputBox->append("- " + p.name + ", " + p.problem + ", Priority: " + QString::number(p.priority));
    }
}

void MainWindow::on_searchButton_clicked() {
    QString name = ui->nameEdit->text();
    for (const Patient& p : patientList) {
        if (p.name == name) {
            ui->outputBox->append("Found: " + p.name + ", " + p.problem);
            return;
        }
    }
    ui->outputBox->append("Patient not found.");
}

void MainWindow::on_removeButton_clicked() {
    QString target = ui->nameEdit->text().trimmed();
    bool removed = false;

    // Create new list with non-matching names
    std::vector<Patient> updatedList;
    for (const Patient& p : patientList) {
        if (p.name.compare(target, Qt::CaseInsensitive) != 0) {
            updatedList.push_back(p); // Keep this patient
        } else {
            removed = true; // Found and skipping this one
        }
    }

    if (!removed) {
        ui->outputBox->append("No patient named \"" + target + "\" found.");
        return;
    }

    // Replace patient list
    patientList = updatedList;

    // Rebuild the heap
    std::priority_queue<Patient> newpq;
    for (const Patient& p : patientList)
        newpq.push(p);
    pq = newpq;

    ui->outputBox->append("Removed all patients named \"" + target + "\".");
}


void MainWindow::on_exitButton_clicked() {
    QApplication::quit();  // Cleanly closes the app
}

void MainWindow::on_pushButton_5_clicked()
{

}


void MainWindow::on_pushButton_clicked()
{

}

