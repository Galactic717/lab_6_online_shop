#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/*
    === МОДУЛЬ РЕДАГУВАННЯ СПИСКУ ТОВАРІВ ===
    Програма розділена на три логічні частини:
    1. Ввід даних користувачем
    2. Обробка даних (збереження у файл)
    3. Вивід результатів на екран
*/

// --- 1. ВВІД ---
vector<string> inputProducts() {
    vector<string> products;
    string product;
    cout << "\nВведіть назви товарів (введіть 'stop' щоб завершити):\n";
    while (true) {
        cout << "Товар: ";
        cin >> product;
        if (product == "stop") break;
        products.push_back(product);
    }
    return products;
}

// --- 2. ОБРОБКА ---
void saveProducts(const vector<string>& products) {
    ofstream fout("products.txt");
    if (!fout.is_open()) {
        cerr << "Помилка відкриття файлу products.txt!\n";
        return;
    }
    for (auto& p : products) fout << p << endl;
    fout.close();
    cout << "Список товарів збережено.\n";
}

// --- 3. ВИВІД ---
void showProducts() {
    ifstream fin("products.txt");
    if (!fin.is_open()) {
        cout << "Файл продуктів порожній або не існує.\n";
        return;
    }
    cout << "\n=== СПИСОК ТОВАРІВ ===\n";
    string product;
    while (getline(fin, product)) {
        cout << "• " << product << endl;
    }
    fin.close();
}

// --- ГОЛОВНА ФУНКЦІЯ МОДУЛЯ ---
void editList() {
    cout << "\n--- МОДУЛЬ РЕДАГУВАННЯ СПИСКУ ---\n";
    vector<string> products = inputProducts();  // Ввід
    saveProducts(products);                     // Обробка
    showProducts();                             // Вивід
}
