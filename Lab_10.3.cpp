#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;

enum TrainType { REGULAR, COMFORT, EXPRESS };
string trainTypeStr[] = { "Звичайний", "Підвищеного комфорту", "Швидкісний експрес" };

struct TrainSchedule {
    string destination;
    TrainType type;
    string departureTime;
};

void Create(TrainSchedule* schedule, const int N);
void Print(TrainSchedule* schedule, const int N);
void AddTrain(TrainSchedule*& schedule, int& N);
void RemoveTrain(TrainSchedule*& schedule, int& N);
void EditTrain(TrainSchedule* schedule, const int N);
void SortByDestination(TrainSchedule* schedule, const int N);
void SortByDepartureTime(TrainSchedule* schedule, const int N);
void TrainsAfterTime(TrainSchedule* schedule, const int N);
void SaveToFile(TrainSchedule* schedule, const int N);
void LoadFromFile(TrainSchedule*& schedule, int& N);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N = 0;
    TrainSchedule* schedule = nullptr;

    int menuItem;
    do {
        cout << endl << "Виберіть дію:" << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - додати новий запис" << endl;
        cout << " [4] - видалити запис" << endl;
        cout << " [5] - редагувати запис" << endl;
        cout << " [6] - сортування за станцією призначення" << endl;
        cout << " [7] - сортування за часом відправлення" << endl;
        cout << " [8] - поїзди, що відходять після введеного часу" << endl;
        cout << " [9] - зберегти розклад у файл" << endl;
        cout << " [10] - завантажити розклад з файлу" << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl;
        cout << "Введіть значення: ";
        cin >> menuItem;
        switch (menuItem) {
        case 1:
            cout << "Введіть кількість записів у розкладі N: ";
            cin >> N;
            delete[] schedule;
            schedule = new TrainSchedule[N];
            Create(schedule, N);
            break;
        case 2:
            Print(schedule, N);
            break;
        case 3:
            AddTrain(schedule, N);
            break;
        case 4:
            RemoveTrain(schedule, N);
            break;
        case 5:
            EditTrain(schedule, N);
            break;
        case 6:
            SortByDestination(schedule, N);
            cout << "Розклад відсортовано за станцією призначення." << endl;
            break;
        case 7:
            SortByDepartureTime(schedule, N);
            cout << "Розклад відсортовано за часом відправлення." << endl;
            break;
        case 8:
            TrainsAfterTime(schedule, N);
            break;
        case 9:
            SaveToFile(schedule, N);
            break;
        case 10:
            LoadFromFile(schedule, N);
            break;
        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);

    delete[] schedule;
    return 0;
}

void Create(TrainSchedule* schedule, const int N) {
    int type;
    for (int i = 0; i < N; i++) {
        cout << "Запис № " << i + 1 << ":" << endl;
        cin.ignore();
        cout << " Назва пункту призначення: ";
        getline(cin, schedule[i].destination);
        cout << " Тип електрички (0 - Звичайний, 1 - Підвищеного комфорту, 2 - Швидкісний експрес): ";
        cin >> type;
        schedule[i].type = (TrainType)type;
        cout << " Час відправлення (ГГ:ХХ): ";
        cin >> schedule[i].departureTime;
    }
}

void Print(TrainSchedule* schedule, const int N) {
    cout << "===================================================================" << endl;
    cout << "| № | Пункт призначення      | Тип                     | Час       |" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << i + 1 << " | " << setw(20) << left << schedule[i].destination
            << "| " << setw(24) << left << trainTypeStr[schedule[i].type]
            << "| " << setw(9) << right << schedule[i].departureTime << " |" << endl;
    }
    cout << "===================================================================" << endl;
}

void AddTrain(TrainSchedule*& schedule, int& N) {
    TrainSchedule* newSchedule = new TrainSchedule[N + 1];
    for (int i = 0; i < N; i++) {
        newSchedule[i] = schedule[i];
    }
    delete[] schedule;
    schedule = newSchedule;

    cout << "Додавання нового запису:\n";
    Create(&schedule[N], 1);
    N++;
}

void RemoveTrain(TrainSchedule*& schedule, int& N) {
    if (N == 0) {
        cout << "Розклад порожній!\n";
        return;
    }

    int index;
    cout << "Введіть номер запису для видалення (1-" << N << "): ";
    cin >> index;
    if (index < 1 || index > N) {  
        cout << "Неправильний номер!\n";
        return;
    }

    TrainSchedule* newSchedule = new TrainSchedule[N - 1];
    for (int i = 0, j = 0; i < N; i++) {
        if (i != index - 1) {
            newSchedule[j++] = schedule[i];
        }
    }
    delete[] schedule;
    schedule = newSchedule;
    N--;

    cout << "Запис видалено.\n";
}

void EditTrain(TrainSchedule* schedule, const int N) {
    int index;
    cout << "Введіть номер запису для редагування (1-" << N << "): ";
    cin >> index;
    if (index < 1 || index > N) { 
        cout << "Неправильний номер!\n";
        return;
    }

    cout << "Редагування запису № " << index << ":\n";
    Create(&schedule[index - 1], 1);
}

void SortByDestination(TrainSchedule* schedule, const int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (schedule[j].destination > schedule[j + 1].destination) {
                swap(schedule[j], schedule[j + 1]);
            }
        }
    }
}

void SortByDepartureTime(TrainSchedule* schedule, const int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (schedule[j].departureTime > schedule[j + 1].departureTime) {
                swap(schedule[j], schedule[j + 1]);
            }
        }
    }
}

void TrainsAfterTime(TrainSchedule* schedule, const int N) {
    string inputTime;
    cout << "Введіть час (ГГ:ХХ): ";
    cin >> inputTime;

    cout << "Поїзди, що відходять після " << inputTime << ":" << endl;
    bool found = false;
    for (int i = 0; i < N; i++) {
        if (schedule[i].departureTime > inputTime) {
            cout << "Пункт призначення: " << schedule[i].destination
                << ", Тип: " << trainTypeStr[schedule[i].type]
                << ", Час відправлення: " << schedule[i].departureTime << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Немає поїздів, що відходять після " << inputTime << "." << endl;
    }
}

void SaveToFile(TrainSchedule* schedule, const int N) {
    string filename;
    cout << "Введіть назву файлу для збереження: ";
    cin >> filename;

    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Помилка відкриття файлу для запису!" << endl;
        return;
    }
    file << N << endl;
    for (int i = 0; i < N; i++) {
        file << schedule[i].destination << endl;
        file << schedule[i].type << endl;
        file << schedule[i].departureTime << endl;
    }
    file.close();
    cout << "Розклад успішно збережено у файл " << filename << "." << endl;
}

void LoadFromFile(TrainSchedule*& schedule, int& N) {
    string filename;
    cout << "Введіть назву файлу для завантаження: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Помилка відкриття файлу для читання!" << endl;
        return;
    }
    file >> N;
    delete[] schedule;
    schedule = new TrainSchedule[N];

    for (int i = 0; i < N; i++) {
        file.ignore();
        getline(file, schedule[i].destination);
        int type;
        file >> type;
        schedule[i].type = (TrainType)type;
        file >> schedule[i].departureTime;
    }
    file.close();
    cout << "Розклад успішно завантажено з файлу " << filename << "." << endl;
}
