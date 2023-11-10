#include "accountspage.h"
#include <QPalette>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/aes.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <QtWidgets>
#include <QApplication>
#include <QWidget>

// Функция для шифрования данных
QByteArray encryptData(const QByteArray& data, const unsigned char* key) {
    EVP_CIPHER_CTX* ctx;
    int len;
    int ciphertext_len;
    unsigned char iv[AES_BLOCK_SIZE];
    unsigned char ciphertext[data.size() + AES_BLOCK_SIZE];

    memset(iv, 0x00, AES_BLOCK_SIZE);

    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    EVP_EncryptUpdate(ctx, ciphertext, &len, reinterpret_cast<const unsigned char*>(data.data()), data.size());
    ciphertext_len = len;

    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return QByteArray(reinterpret_cast<const char*>(ciphertext), ciphertext_len);
}

// Функция для расшифрования данных
QByteArray decryptData(const QByteArray& data, const unsigned char* key) {
    EVP_CIPHER_CTX* ctx;
    int len;
    int plaintext_len;
    unsigned char iv[AES_BLOCK_SIZE];
    unsigned char plaintext[data.size()];

    memset(iv, 0x00, AES_BLOCK_SIZE);

    ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    EVP_DecryptUpdate(ctx, plaintext, &len, reinterpret_cast<const unsigned char*>(data.data()), data.size());
    plaintext_len = len;

    EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return QByteArray(reinterpret_cast<const char*>(plaintext), plaintext_len);
}

AccountsPage::AccountsPage(QWidget *parent)
    : QWidget(parent)
{
    QFile file("data.json");
    if (file.exists()) {
        if (file.open(QIODevice::ReadOnly)) {
            // Файл успешно открыт
        } else {
            // Ошибка открытия файла
            QMessageBox::information(this, "Ошибка", "Не удалось открыть файл!");
        }
    } else {
        // Файл не существует
        QMessageBox::information(this, "Ошибка", "Файла не существует!");
    }
//    if (!file.open(QIODevice::ReadOnly)) {
//        QMessageBox::information(this, "Ошибка", "Не удалось открыть файл!");
//    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(jsonData);
////    if (!document.isObject()) {
////        QMessageBox::information(this, "Ошибка", "Не удалось прочитать JSON объект!");
////    }

    QJsonObject jsonObject = document.object();
////    if (!jsonObject.contains("accounts") || !jsonObject["accounts"].isArray()) {
////        QMessageBox::information(this, "Ошибка", "Некорректная структура JSON файла!");
////    }

    QJsonArray accountsArray = jsonObject["accounts"].toArray();
    QList<Account> accounts;

    foreach (const QJsonValue &value, accountsArray) {
        if (value.isObject()) {
            QJsonObject accountObject = value.toObject();

            int id = accountObject["id"].toInt();
            double amount = accountObject["amount"].toDouble();

            QString dateString = accountObject["date"].toString();
            QDate date = QDate::fromString(dateString, "yyyy-MM-dd");
            QString color = accountObject["color"].toString();

            Account account{id, amount, date, color};
            accounts.append(account);
        }
    }

//    // Выводим данные для проверки
//    foreach (const Account &account, accounts) {
//        qDebug() << account.id << account.amount << account.date.toString("yyyy-MM-dd");
//    }

     //Инициализируем массив счетов
//    accounts = {
//        {1, 1000.0, QDate(2021, 1, 1), "blue"},
//        {2, 2000.0, QDate(2021, 2, 1), "green"},
//        {3, 3000.0, QDate(2021, 3, 1), "red"},
//        {4, 4000.0, QDate(2021, 4, 1),"yellow"},
//        {5, 5000.0, QDate(2021, 5, 1),"purple"}
//    };
    // Шифрование данных
//    encryptedData = encryptData(QByteArray(reinterpret_cast<const char*>(accounts.data()), sizeof(accounts)), key);

//    // Расшифрование данных
//    decryptedData = decryptData(encryptedData, key);

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
    dateLabel->setText("Дата открытия: " + account.date.toString());
    QPalette p(palette());
    p.setColor(QPalette::Background, QColor(account.color));
    setAutoFillBackground(true);
    setPalette(p);
}
