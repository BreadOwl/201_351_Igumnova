#include "accountspage.h"
#include <QPalette>

AccountsPage::AccountsPage(QWidget *parent)
    : QWidget(parent)
{
    // Инициализируем массив счетов
    accounts = {
        {1, 1000.0, QDate(2021, 1, 1)},
        {2, 2000.0, QDate(2021, 2, 1)},
        {3, 3000.0, QDate(2021, 3, 1)},
        {4, 4000.0, QDate(2021, 4, 1)},
        {5, 5000.0, QDate(2021, 5, 1)}
    };

    // Создаем элементы интерфейса
    idLabel = new QLabel;
    amountLabel = new QLabel;
    dateLabel = new QLabel;

    previousButton = new QPushButton("Назад");
    nextButton = new QPushButton("Вперед");

    // Создаем горизонтальный слой для кнопок
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(previousButton);
    buttonLayout->addWidget(nextButton);

    // Создаем вертикальный слой для элементов интерфейса
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(idLabel);
    mainLayout->addWidget(amountLabel);
    mainLayout->addWidget(dateLabel);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    // Загружаем данные первого счета
    currentIndex = 0;
    loadAccount(currentIndex);

    // Подключаем сигналы к слотам
    connect(previousButton, &QPushButton::clicked, this, &AccountsPage::previousAccount);
    connect(nextButton, &QPushButton::clicked, this, &AccountsPage::nextAccount);
}

void AccountsPage::previousAccount()
{
    // Проверяем, есть ли предыдущий счет
    if (currentIndex > 0) {
        currentIndex--;
        loadAccount(currentIndex);
    }
}

void AccountsPage::nextAccount()
{
    // Проверяем, есть ли следующий счет
    if (currentIndex < accounts.size() - 1) {
        currentIndex++;
        loadAccount(currentIndex);
    }
}

void AccountsPage::loadAccount(int index)
{
    // Загружаем данные счета по указанному индексу
    Account account = accounts[index];

    // Отображаем данные счета
    idLabel->setText("ID: " + QString::number(account.id));
    amountLabel->setText("Сумма: " + QString::number(account.amount));
    dateLabel->setText("Дата открытия: " + account.openingDate.toString());

}
