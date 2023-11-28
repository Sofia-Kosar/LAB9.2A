#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Major { KI, INF, MATH, PHYSICS, ART };
string majorStr[] = { "��������� �����", "�����������", "���������� �� ��������", "Գ���� �� �����������", "������� ��������" };

struct Student
{
    string prizv;
    unsigned int kurs;
    Major major;
    int physics;
    int math;
    int IT;
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
void CountGoodGrades(Student* p, const int N);
double CalculatePercentGoodPhysicsMath(Student* p, const int N);
void Sort1(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const unsigned int kurs, const double avgGrade);


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "������ N: "; cin >> N;

    Student* p = new Student[N];
    Create(p, N);
    Print(p, N);

    double percent;

    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "������� ��:" << endl << endl;
        cout << " [1] - �������� ����� � ���������" << endl;
        cout << " [2] - ���� ����� �� �����" << endl;
        cout << " [3] - ���� ������ �� �������� ��������," << endl;
        cout << " �� ����� ������ 5 � ������ � ����������" << endl << endl;
        cout << " [4] - ���� �������� �� ������� ������ ����� " << endl << endl;
        cout << " [5] - ���������� �������� 1 " << endl;
        cout << " [6] - �������� ������������� �� ���� �����" << endl;
        cout << " [7] - ������� �����" << endl;
        cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
        cout << "������ ��������: "; cin >> menuItem;
        cout << endl << endl << endl;
        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            percent = CalculatePercentGoodPhysicsMath(p, N);
            cout << "������� ��������, �� �������� '5' � � ������ � � ����������: " << fixed << setprecision(2) << percent << "%" << endl;
            break;
        case 4:
        {
            // ��������� ������� ������ '�����' � ������� ��������
            CountGoodGrades(p, N);
            break;
        }
        case 5:
            // ���������� ��������
            Sort1(p, N);
            Print(p, N);
            break;
        case 6:
            // �������� ������������� �� ���� �����
            PrintIndexSorted(p, IndexSort(p, N), N);
            break;
        case 7:
            // �������� ����� ��������
        {
            string searchPrizv;
            unsigned int searchKurs;
            double searchAvgGrade;

            cout << "������ ������� ��������: ";
            cin.ignore(); // �������� '\n' � ����� ��������
            getline(cin, searchPrizv);

            cout << "������ ����� �����: ";
            cin >> searchKurs;

            cout << "������ ������� ���: ";
            cin >> searchAvgGrade;

            int foundIndex = BinSearch(p, N, searchPrizv, searchKurs, searchAvgGrade);
            if (foundIndex != -1) {
                cout << "�������� �������� � ���������� ������� " << foundIndex + 1 << endl;
            }
            else {
                cout << "�������� �������� �� ��������" << endl;
            }
        }
        break;
        case 0:
            break;
        default:
            cout << "�� ����� ��������� ��������! "
                "��� ������ ����� - ����� ��������� ������ ����" << endl;
            break;
        }
    } while (menuItem != 0);
    return 0;
}

void Create(Student* p, const int N)
{
    int major;

    for (int i = 0; i < N; i++)
    {
        cout << "������� � " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();

        cout << " �������: "; getline(cin, p[i].prizv);
        cout << " ����: "; cin >> p[i].kurs;
        cout << " ������������ (0 - ��������� �����, 1 -����������� , 2 -���������� �� �������� , 3 -Գ���� �� �����������, 4 -������� ��������): ";
        cin >> major;
        p[i].major = static_cast<Major>(major);
        cout << " ������ "; cin >> p[i].physics;
        cout << " ���������� "; cin >> p[i].math;
        cout << " ����������� "; cin >> p[i].IT;
        cout << endl;
    }
}

void Print(Student* p, const int N)
{
    cout << "=========================================================================================="
        << endl;
    cout << "|  � |   �������   | ���� | ������������          | Գ���� | ���������� | �����������  |"
        << endl;
    cout << "-----------------------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << p[i].prizv
            << "| " << setw(4) << right << p[i].kurs << " "
            << "| " << setw(23) << left << majorStr[p[i].major];
        cout << "| " << setw(7) << right << p[i].physics
            << "| " << setw(11) << right << p[i].math
            << "| " << setw(12) << right << p[i].IT;
        cout << " |" << endl;
    }
    cout << "=========================================================================================="
        << endl;
    cout << endl;
}

void CountGoodGrades(Student* p, const int N)
{
    int countPhysics = 0;
    int countMath = 0;
    int countIT = 0;

    for (int i = 0; i < N; i++)
    {
        if (p[i].physics == 4) {
            countPhysics++;
        }

        if (p[i].math == 4) {
            countMath++;
        }

        if (p[i].IT == 4) {
            countIT++;
        }
    }

    cout << "==============================================" << endl;
    cout << "ʳ������ ������ '�����' � ������� ��������:" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Գ����: " << countPhysics << " | ����������: " << countMath << " | �����������: " << countIT << endl;
    cout << "==============================================" << endl;
}

double CalculatePercentGoodPhysicsMath(Student* p, const int N)
{
    if (N == 0) {
        return 0.0;
    }

    int k = 0;

    for (int i = 0; i < N; i++)
    {
        if (p[i].physics == 5 && p[i].math == 5) {
            k++;
        }
    }

    return 100.0 * k / N;
}

void Sort1(Student* p, const int N)
{
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
    {
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
        {
            if ((p[i1].physics + p[i1].math + p[i1].IT) > (p[i1 + 1].physics + p[i1 + 1].math + p[i1 + 1].IT) ||
                ((p[i1].physics + p[i1].math + p[i1].IT) == (p[i1 + 1].physics + p[i1 + 1].math + p[i1 + 1].IT) &&
                    p[i1].kurs > p[i1 + 1].kurs) ||
                ((p[i1].physics + p[i1].math + p[i1].IT) == (p[i1 + 1].physics + p[i1 + 1].math + p[i1 + 1].IT) &&
                    p[i1].kurs == p[i1 + 1].kurs &&
                    p[i1].prizv < p[i1 + 1].prizv))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
        }
    }
}
int* IndexSort(Student* p, const int N)
{
    int* I = new int[N];

    for (int i = 0; i < N; i++)
        I[i] = i;

    int i, j, value;

    for (i = 1; i < N; i++)
    {
        value = I[i];

        for (j = i - 1; j >= 0 && ((p[I[j]].physics + p[I[j]].math + p[I[j]].IT) > (p[value].physics + p[value].math + p[value].IT) ||
            ((p[I[j]].physics + p[I[j]].math + p[I[j]].IT) == (p[value].physics + p[value].math + p[value].IT) &&
                p[I[j]].kurs > p[value].kurs) ||
            ((p[I[j]].physics + p[I[j]].math + p[I[j]].IT) == (p[value].physics + p[value].math + p[value].IT) &&
                p[I[j]].kurs == p[value].kurs &&
                p[I[j]].prizv > p[value].prizv));
            j--)
        {
            I[j + 1] = I[j];
        }

        I[j + 1] = value;
    }

    return I;
}

void PrintIndexSorted(Student* p, int* I, const int N)
{
    cout << "=========================================================================================="
        << endl;
    cout << "|  � |   �������   | ���� | ������������          | Գ���� | ���������� | �����������  |"
        << endl;
    cout << "-----------------------------------------------------------------------------------------"
        << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << p[I[i]].prizv
            << "| " << setw(4) << right << p[I[i]].kurs << " "
            << "| " << setw(23) << left << majorStr[p[I[i]].major];
        cout << "| " << setw(7) << right << p[I[i]].physics
            << "| " << setw(11) << right << p[I[i]].math
            << "| " << setw(12) << right << p[I[i]].IT;
        cout << " |" << endl;
    }

    cout << "=========================================================================================="
        << endl;
    cout << endl;
}
int BinSearch(Student* p, const int N, const string prizv, const unsigned int kurs, const double avgGrade)
{
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (p[m].prizv == prizv && p[m].kurs == kurs && ((p[m].physics + p[m].math + p[m].IT) / 3.0) == avgGrade)
            return m;

        if ((p[m].prizv < prizv) ||
            (p[m].prizv == prizv && p[m].kurs < kurs) ||
            (p[m].prizv == prizv && p[m].kurs == kurs && ((p[m].physics + p[m].math + p[m].IT) / 3.0) < avgGrade))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);

    return -1;
}
