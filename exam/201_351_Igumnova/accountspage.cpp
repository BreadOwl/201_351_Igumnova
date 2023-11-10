#include "accountspage.h"
#include <QPalette>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <QtWidgets>
#include <QApplication>
#include <QWidget>
#include <openssl/evp.h>
#include <openssl/aes.h>

QByteArray key = "password123";
QByteArray encryptData(const QByteArray &data, const QByteArray &key);
QByteArray decryptData(const QByteArray &encryptedData, const QByteArray &key);

AccountsPage::AccountsPage(QWidget *parent)
    : QWidget(parent)
{
    // Открываем JSON файл
    QFile fileJson("./data.json");
//    QFile file("data.json");
    if (!fileJson.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, "Ошибка", "Не удалось открыть файл!");
    }
    QByteArray jsonData = fileJson.readAll();
    fileJson.close();

    // Парсим JSON
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);

    // Получаем массив объектов из JSON
    QJsonArray jsonArray = jsonDoc.array();

    // Шифруем данные
    //QByteArray encryptedData = encryptData(jsonData, key);

    // Расшифровываем данные
    QByteArray decryptedData = decryptData(jsonData, key);

     //Инициализируем массив счетов
    accounts = {
        {1, 1000.0, QDate(2021, 1, 1), "blue"},
        {2, 2000.0, QDate(2021, 2, 1), "green"},
        {3, 3000.0, QDate(2021, 3, 1), "red"},
        {4, 4000.0, QDate(2021, 4, 1),"yellow"},
        {5, 5000.0, QDate(2021, 5, 1),"purple"}
    };
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

QByteArray encryptData(const QByteArray &data, const QByteArray &key)
{
    AES_KEY aesKey;
    AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(key.constData()), 256, &aesKey);

    QByteArray encryptedData;

    int dataLength = data.length();

    // Расчет длины дополнительного блока
    int paddingLength = AES_BLOCK_SIZE - dataLength % AES_BLOCK_SIZE;
    int paddedDataLength = dataLength + paddingLength;

    // Создание выходного массива с дополнительным блоком
    encryptedData.resize(paddedDataLength);

    // Записываем оригинальные данные в выходной массив
    memcpy(encryptedData.data(), data.constData(), dataLength);

    // Заполняем остаток выходного массива случайными данными
    for (int i = dataLength; i < paddedDataLength; i++) {
        encryptedData[i] = qrand() % 256;
    }

    // Шифруем данные по блокам
    for (int i = 0; i < paddedDataLength; i += AES_BLOCK_SIZE) {
        AES_encrypt(reinterpret_cast<const unsigned char*>(encryptedData.constData() + i),
                    reinterpret_cast<unsigned char*>(encryptedData.data() + i),
                    &aesKey);
    }

    return encryptedData;
}



QByteArray decryptData(const QByteArray &encryptedData, const QByteArray &key)
{
    AES_KEY aesKey;
    AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(key.constData()), 256, &aesKey);

    int encryptedDataLength = encryptedData.length();
    int paddingLength = AES_BLOCK_SIZE - encryptedDataLength % AES_BLOCK_SIZE;

    QByteArray decryptedData;
    decryptedData.resize(encryptedDataLength);

    // Расшифровываем данные по блокам
    for (int i = 0; i < encryptedDataLength; i += AES_BLOCK_SIZE) {
        AES_decrypt(reinterpret_cast<const unsigned char*>(encryptedData.constData() + i),
                    reinterpret_cast<unsigned char*>(decryptedData.data() + i),
                    &aesKey);
    }

    decryptedData.chop(paddingLength); // Удаляем дополнительный блок

    return decryptedData;
}
