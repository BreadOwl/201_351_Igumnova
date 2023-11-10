#ifndef ACCOUNTSPAGE_H
#define ACCOUNTSPAGE_H

#pragma once

#include <QtWidgets>
#include <QVector>

// Создаем структуру счета
struct Account {
    int id;
    double amount;
    QDate openingDate;
};

class AccountsPage: public QWidget
{
    Q_OBJECT
public:
    AccountsPage(QWidget *parent = nullptr);

private slots:
    void previousAccount();
    void nextAccount();

signals:
    void newWin();

private:
    QVector<Account> accounts;
    int currentIndex;
    QLabel *idLabel;
    QLabel *amountLabel;
    QLabel *dateLabel;
    QPushButton *previousButton;
    QPushButton *nextButton;

    void loadAccount(int index);
};

#endif // ACCOUNTSPAGE_H
