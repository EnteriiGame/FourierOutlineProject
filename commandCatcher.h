#ifndef COMMANDCATCHER_H
#define COMMANDCATCHER_H

#include <QThread>
#include <QDebug>
#include <iostream>
#include <string>

class TerminalReader : public QThread {
    Q_OBJECT
public:
    void run() override {
        std::string input;
        while (true) {
            std::getline(std::cin, input);
            if(input!="")emit commandReceived(QString::fromStdString(input));
        }
    }

signals:
    void commandReceived(QString cmd);
};

#endif // COMMANDCATCHER_H
