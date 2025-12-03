#include <iostream>
#include <fstream>
#include <string>
#include <limits>   // Для std::numeric_limits
#include <clocale>  // Для setlocale
#include <cstdlib>  // Для setlocale, _putenv

using namespace std;

/*
    === МОДУЛЬ ПІДТВЕРДЖЕННЯ ЗАМОВЛЕННЯ ===
    Програма розділена на три логічні частини:
    1. Ввід замовлення
    2. Обробка (запис у файл)
    3. Вивід списку замовлень
*/

// --- 1. ВВІД ---
string inputOrder() {
    string product;

    // Вхідний цикл для обробки порожнього вводу (ВИПРАВЛЕННЯ OrderTest4)
    while (true) {
        cout << "\nВведіть назву товару, який потрібно замовити: ";

        // ВИПРАВЛЕННЯ OrderTest3: Використовуємо getline() для зчитування всього рядка
        if (!getline(cin, product)) {
            cerr << "Помилка читання вводу.\n";
            return "";
        }

        // ВИПРАВЛЕННЯ OrderTest4: Перевірка на порожній ввід.
        if (product.empty()) {
            cout << "Помилковий ввід. Назва товару не може бути порожньою. Спробуйте ще раз.\n";
        }
        else {
            break;
        }
    }

    return product;
}

// --- 2. ОБРОБКА ---
bool processOrder(const string& product) {
    if (product.empty()) {
        cerr << "Неможливо обробити порожнє замовлення.\n";
        return false;
    }

    ofstream fout("orders.txt", ios::app);
    if (!fout.is_open()) {
        cerr << "Помилка запису у файл orders.txt!\n";
        return false;
    }
    fout << product << endl;
    fout.close();
    return true;
}

// --- 3. ВИВІД ---
void showOrders() {
    ifstream fin("orders.txt");
    if (!fin.is_open()) {
        cout << "\nЗамовлень поки немає.\n";
        return;
    }

    cout << "\n=== СПИСОК ЗАМОВЛЕНЬ ===\n";
    string order;
    while (getline(fin, order)) {
        cout << "• " << order << endl;
    }
    fin.close();
}

// --- ГОЛОВНА ФУНКЦІЯ МОДУЛЯ ---
void confirmOrder() {
    if (cin.peek() == '\n') {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "\n--- МОДУЛЬ ПІДТВЕРДЖЕННЯ ЗАМОВЛЕННЯ ---\n";
    string product = inputOrder();               // Ввід

    if (product.empty()) {
        cout << "Замовлення скасовано.\n";
    }
    else if (processOrder(product)) {          // Обробка
        cout << "Замовлення збережено!\n";
    }
    else {
        cout << "Помилка при підтвердженні замовлення!\n";
    }
    showOrders();                                // Вивід
}

// --- ТОЧКА ВХОДУ ПРОГРАМИ (main) ---
int main() {
    // ВСТАНОВЛЕННЯ УКРАЇНСЬКОЇ ЛОКАЛІ ДЛЯ КОНСОЛІ
    // Ці команди забезпечують коректне відображення та зчитування кирилиці

    // Для Windows (MSVC): Встановлює кодування вводу/виводу на UTF-8 (для cygwin/mingw/інших) 
    // або на українську кодову сторінку.
    // Якщо ви використовуєте Visual Studio:
    setlocale(LC_ALL, "uk_UA.UTF-8");

    // Для деяких IDE або старих компіляторів на Windows, може знадобитися:
    // setlocale(LC_ALL, "Ukrainian"); 
    // system("chcp 1251"); // Встановлює кодову сторінку Windows на 1251

    // Для більшої універсальності, особливо на Unix-подібних системах:
    setlocale(LC_ALL, ""); // Встановлює локаль за замовчуванням у системі

    // Викликаємо основний модуль
    confirmOrder();

    return 0;
}
