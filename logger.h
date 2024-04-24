#ifndef LOGGER_H
#define LOGGER_H
#include <QThread>
#include <windows.h>
class Logger : public QThread
{
    Q_OBJECT
public:
    void stopLoggingThread();
protected:
    void run() override;
    volatile bool canRun;
signals:
    void stopLogging();
    void keyPressed(char key);
private slots:
};


#endif // LOGGER_H
