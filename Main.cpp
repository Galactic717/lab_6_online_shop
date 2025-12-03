#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>  // Для SetConsoleCP
#include "utils.h"
using namespace std;

// ✅ Функція очищення екрану
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

bool login() {
    string name, password, fileUser, fileHash;
    cout << "=== ВХІД ДО СИСТЕМИ ===\n";
    cout << "Ім'я користувача: ";
    cin >> name;
    cout << "Пароль: ";
    cin >> password;

    ifstream fin("users.txt"); // 🔹 Тепер без "..\\"
    if (!fin.is_open()) {
        cerr << "Помилка: файл users.txt не знайдено.\n";
        return false;
    }

    string hash = simpleHash(password);
    while (fin >> fileUser >> fileHash) {
        if (!fileHash.empty() && fileHash.back() == '\r')
            fileHash.pop_back();

        if (fileUser == name && fileHash == hash) {
            fin.close();
            return true;
        }
    }
    fin.close();
    cout << "Невірний логін або пароль!\n";
    return false;
}

void mainMenu() {
    int choice;
    do {
        cout << "\n=== ГОЛОВНЕ МЕНЮ ===\n";
        cout << "1. Редагування списку\n";
        cout << "2. Підтвердження замовлення\n";
        cout << "9. Вихід з акаунту\n";
        cout << "0. Завершити роботу\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case 1:
            editList();
            break;
        case 2:
            confirmOrder();
            break;
        case 9:
            cout << "Вихід з акаунту...\n";
            return;
        case 0:
            cout << "Завершення роботи.\n";
            exit(0);
        default:
            cout << "Невірний вибір!\n";
        }
    } while (true);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    while (true) {
        if (login()) {
            clearScreen(); // 🔹 Виклик замість system("cls");
            mainMenu();
        }
    }
    return 0;
}
