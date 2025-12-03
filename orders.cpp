#include <iostream>
#include <fstream>
#include <string>
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
    cout << "\nВведіть назву товару, який потрібно замовити: ";
    cin >> product;
    return product;
}

// --- 2. ОБРОБКА ---
bool processOrder(const string& product) {
    ofstream fout("orders.txt", ios::app); // додаємо в кінець файлу
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
    cout << "\n--- МОДУЛЬ ПІДТВЕРДЖЕННЯ ЗАМОВЛЕННЯ ---\n";
    string product = inputOrder();            // Ввід
    if (processOrder(product))                // Обробка
        cout << "Замовлення збережено!\n";
    else
        cout << "Помилка при підтвердженні замовлення!\n";
    showOrders();                             // Вивід
}
