#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include <QCoreApplication>
#include <QAction>
#include <QMenu>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QMessageBox>
#include <QMainWindow>
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include "logger.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_bntStart_clicked();
    void handleKeyPress(char key);
    void on_btnStop_clicked();

    void on_pushButton_clicked();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    QSystemTrayIcon *m_trayIcon;
    QMenu *m_trayIconMenu;
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void createTrayIcon();

    Ui::MainWindow *ui;
    Logger *logger;
    int Save(int _key, const char *file);
    const char* GetTimestamp();
};
#endif // MAINWINDOW_H

