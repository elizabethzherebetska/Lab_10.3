#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;

enum TrainType { REGULAR, COMFORT, EXPRESS };
string trainTypeStr[] = { "���������", "ϳ��������� ��������", "��������� �������" };

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
        cout << endl << "������� ��:" << endl;
        cout << " [1] - �������� ����� � ���������" << endl;
        cout << " [2] - ���� ����� �� �����" << endl;
        cout << " [3] - ������ ����� �����" << endl;
        cout << " [4] - �������� �����" << endl;
        cout << " [5] - ���������� �����" << endl;
        cout << " [6] - ���������� �� �������� �����������" << endl;
        cout << " [7] - ���������� �� ����� �����������" << endl;
        cout << " [8] - �����, �� �������� ���� ��������� ����" << endl;
        cout << " [9] - �������� ������� � ����" << endl;
        cout << " [10] - ����������� ������� � �����" << endl;
        cout << " [0] - ����� �� ���������� ������ ��������" << endl;
        cout << "������ ��������: ";
        cin >> menuItem;
        switch (menuItem) {
        case 1:
            cout << "������ ������� ������ � ������� N: ";
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
            cout << "������� ����������� �� �������� �����������." << endl;
            break;
        case 7:
            SortByDepartureTime(schedule, N);
            cout << "������� ����������� �� ����� �����������." << endl;
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
            cout << "�� ����� ��������� ��������! ��� ������ ����� - ����� ��������� ������ ����" << endl;
        }
    } while (menuItem != 0);

    delete[] schedule;
    return 0;
}

void Create(TrainSchedule* schedule, const int N) {
    int type;
    for (int i = 0; i < N; i++) {
        cout << "����� � " << i + 1 << ":" << endl;
        cin.ignore();
        cout << " ����� ������ �����������: ";
        getline(cin, schedule[i].destination);
        cout << " ��� ���������� (0 - ���������, 1 - ϳ��������� ��������, 2 - ��������� �������): ";
        cin >> type;
        schedule[i].type = (TrainType)type;
        cout << " ��� ����������� (��:��): ";
        cin >> schedule[i].departureTime;
    }
}

void Print(TrainSchedule* schedule, const int N) {
    cout << "===================================================================" << endl;
    cout << "| � | ����� �����������      | ���                     | ���       |" << endl;
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

    cout << "��������� ������ ������:\n";
    Create(&schedule[N], 1);
    N++;
}

void RemoveTrain(TrainSchedule*& schedule, int& N) {
    if (N == 0) {
        cout << "������� �������!\n";
        return;
    }

    int index;
    cout << "������ ����� ������ ��� ��������� (1-" << N << "): ";
    cin >> index;
    if (index < 1 || index > N) {  
        cout << "������������ �����!\n";
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

    cout << "����� ��������.\n";
}

void EditTrain(TrainSchedule* schedule, const int N) {
    int index;
    cout << "������ ����� ������ ��� ����������� (1-" << N << "): ";
    cin >> index;
    if (index < 1 || index > N) { 
        cout << "������������ �����!\n";
        return;
    }

    cout << "����������� ������ � " << index << ":\n";
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
    cout << "������ ��� (��:��): ";
    cin >> inputTime;

    cout << "�����, �� �������� ���� " << inputTime << ":" << endl;
    bool found = false;
    for (int i = 0; i < N; i++) {
        if (schedule[i].departureTime > inputTime) {
            cout << "����� �����������: " << schedule[i].destination
                << ", ���: " << trainTypeStr[schedule[i].type]
                << ", ��� �����������: " << schedule[i].departureTime << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "���� �����, �� �������� ���� " << inputTime << "." << endl;
    }
}

void SaveToFile(TrainSchedule* schedule, const int N) {
    string filename;
    cout << "������ ����� ����� ��� ����������: ";
    cin >> filename;

    ofstream file(filename);
    if (!file.is_open()) {
        cout << "������� �������� ����� ��� ������!" << endl;
        return;
    }
    file << N << endl;
    for (int i = 0; i < N; i++) {
        file << schedule[i].destination << endl;
        file << schedule[i].type << endl;
        file << schedule[i].departureTime << endl;
    }
    file.close();
    cout << "������� ������ ��������� � ���� " << filename << "." << endl;
}

void LoadFromFile(TrainSchedule*& schedule, int& N) {
    string filename;
    cout << "������ ����� ����� ��� ������������: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "������� �������� ����� ��� �������!" << endl;
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
    cout << "������� ������ ����������� � ����� " << filename << "." << endl;
}
