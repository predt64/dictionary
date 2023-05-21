
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <algorithm>
#include <conio.h>
#include <iomanip>

using namespace std;

class List
{
public:
    ~List();

    List();

    void push_back(string en, string ru,string note,string lat);

    int GetSize() { return size; }

    string& operator()(const int index);
    string& operator[](const int index);
    string& operator[](const long index);
    string& operator[](const float index);
private:

    class Node {
    public:
        Node* pnext;
        string en, ru, note, lat;
        Node(string en = "", string ru = "",string note ="",string lat="", Node * pnext = nullptr)
        {
            this->en = en;
            this->ru = ru;
            this->note = note;
            this->lat = lat;
            this->pnext = pnext;
        }
    };
    int size;
    Node* head;
};

List::List()
{
    size = 0;
    head = nullptr;
}

List::~List()
{

}

void List::push_back(string en,string ru,string note,string lat) {
    if (head == nullptr)
    {
        head = new Node(en, ru,note,lat);
    }
    else
    {
        Node* current = head;
        while (current->pnext != nullptr)
        {
            current = current->pnext;
        }
        current->pnext = new Node(en, ru,note,lat);
    }
    size++;
}

string& List::operator()(const int index)
{
    int counter = 0;
    Node* current = this->head;
    while (current != nullptr)
    {
        if (index == counter)
            return current->ru;
        current = current->pnext;
        counter++;
    }
}

string& List::operator[](const int index)
{
    int counter = 0;
    Node* current = this->head;
    while (current != nullptr)
    {
        if (index == counter)
            return current->en;
        current = current->pnext;
        counter++;
    }
}

string& List::operator[](const long index)
{
    int counter = 0;
    Node* current = this->head;
    while (current != nullptr)
    {
        if (index == counter)
            return current->note;
        current = current->pnext;
        counter++;
    }
}

string& List::operator[](const float index)
{int counter = 0;
Node* current = this->head;
while (current != nullptr)
{
    if (index == counter)
        return current->lat;
    current = current->pnext;
    counter++;
}
}
enum ConsoleColor
{
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15
};

void SetColor(int text, int background)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
void gotoxy(int x, int y)
{
    COORD scrn;

    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

    scrn.X = x; scrn.Y = y;

    SetConsoleCursorPosition(hOuput, scrn);
}
void pos1()
{
    gotoxy(55, 4);
    cout << "     ";
    gotoxy(50, 2);
    cout << "     ";
    gotoxy(45, 1);
    cout << "<====";
    Sleep(140);
}
void pos2()
{
    gotoxy(45, 1);
    cout << "     ";
    gotoxy(52, 3);
    cout << "     ";
    gotoxy(50, 2);
    cout << "<====";
    Sleep(140);
}
void pos3()
{
    gotoxy(55, 4);
    cout << "     ";
    gotoxy(50, 2);
    cout << "     ";
    gotoxy(52, 3);
    cout << "<====";
    Sleep(140);
}
void pos4()
{
    gotoxy(45, 1);
    cout << "     ";
    gotoxy(52, 3);
    cout << "     ";
    gotoxy(55, 4);
    cout << "<====";
    Sleep(140);
}
void menu() {
    cout << "Вас приветствует программа ' SLOVAR'®'по переводу слов с английского языка на русский(и наоборот) + немного латинского\n" <<
        " Нажмите '1' для перехода в режим перевода\n" <<
        " Нажмите '2' для перехода в режим добавления слов\n" <<
        " Нажмите '3' для перехода в режим создания заметок\n" <<
        " Нажмите '4' для перехода в режим просмотра словаря\n";
    gotoxy(76, 10);
    cout << " Для выхода из программы нажмите 'esc' ";
    gotoxy(0, 0);
}

int main()
{
    List voc;
    int button = 0, pos = 1, action = 0;
    const int UP = 72, DOWN = 80, ENTER = 13, ESCAPE = 27;
    SetConsoleCP(1251); SetConsoleOutputCP(1251);
    fstream file;
    fstream latinFile;
    file.open("wrds.txt", fstream::in | fstream::out|fstream::app );
    latinFile.open("Текстовый Документ.txt", fstream::in | fstream::out | fstream::app);
    string ru, en, note, latin;
    long digit; float latinDigit = 0;
    while (!file.eof())
    {
        getline(file, en, '[');
        if (en.length() == 0)
            break;
        en.pop_back();
        if ((en[0] >= '1')&& (en[0] <= '9'))
        {
            digit = stoi(en);
            getline(file, ru, '\n');
            ru.erase(0, 1);
            voc[digit] = ru;
            continue;
        }
        getline(file, ru, '\n');
            ru.erase(0, ru.find(']') + 2);
            if (ru.find('(') != ru.npos)
                ru.erase(ru.find('('), ru.find(')'));
            if (ru.find(',') != ru.npos)
                    ru.replace(ru.find(','), ru.length()-ru.find(','), "");
                    while (ru.find('.') != ru.npos)
                    {
                        ru.erase(0, ru.find_first_of('.'));
                        ru.replace(ru.find('.'), 1, "");
                    }
                while (ru[0] == ' ')
                    ru.erase(0, 1);
                transform(en.begin(), en.end(), en.begin(), ::tolower);
                voc.push_back(en, ru,note,latin);     
    }
    while (!latinFile.eof())
    {
        getline(latinFile, ru, '\n');
        getline(latinFile, ru, '\n');        
        getline(latinFile, latin, '\n');
        getline(latinFile, latin, '\n');
        if (latin.find(',') != latin.npos)
        latin.erase(latin.find(','), latin.length());
        if (ru.find(',') != ru.npos)
            ru.erase(ru.find(','), ru.length());
        if (ru.find('(') != ru.npos)
            ru.erase(ru.find('(')-1, ru.length());
        bool flag = 1;
        latinDigit = 0;
        for (int i = 0; i < voc.GetSize(); i++)
        {
            if (ru == voc(i))
            {
                voc[latinDigit] = latin;
                flag = 0;
                break;
            }
            latinDigit++;
        }
        if (flag == 1)
            voc.push_back(en, ru, note, latin);
        if (ru == "яремный")
            break;
    }
    latin = "";
    menu();
    pos1();
    while (true) {
        do
        {
            gotoxy(0, 0);
            button = _getch();
            gotoxy(0, 20);
            if (button == ENTER)
                break;
            if (button == ESCAPE)
                break;
            if (button >= '1' && button <= '4')
                break;
        } while (button != 224);
        if (button == ESCAPE)
            exit(0);
        else if (button == ENTER)
            action = pos;
        else if (button >= '1' && button <= '4')
        {
            action = button - '0';
        }
        else
        {
            button = _getch(); // забираем оставшееся в буфере число
            if (button == DOWN) // если стрлка вниз
            {
                pos++;
                if (pos == 5)
                    pos = 1;
            }
            if (button == UP)// если стрелка вверх 
            {
                pos--;
                if (pos == 0)
                    pos = 4;
            }
        }

        switch (action)
        {
        case 1:
        {
            system("cls");
            gotoxy(0, 0);
            cout << "для выхода в меню введите слово 'назад'\n введите слово для перевода: ";
            string word;
            getline(cin, word);
            if (word == "назад")
                break;
            if (word == "")
                break;
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            cout << "\n перевод вашего слова - ";
            long j = 0;
            float k = 0;
            for (int i = 0; i < voc.GetSize(); i++)
            {
                if (word == voc(i))//
                {
                    cout << voc[i] << "\n";
                    cout << "\n ваша заметка - ";
                    cout << voc[j] << "\n";
                    cout << "\n перевод на латинский - ";
                    cout << voc[k] << "\n";
                    break;
                }
                if (word == voc[i])
                {
                    cout << voc(i) << "\n";
                    cout << "\n ваша заметка - ";
                    cout << voc[j] << "\n";
                    cout << "\n перевод на латинский - ";
                    cout << voc[k] << "\n";
                    break;
                }
                if (word == voc[k])
                {
                    cout << voc(i) << "\n";
                    cout << "\n ваша заметка - ";
                    cout << voc[j] << "\n";
                    cout << "\n перевод на английский - ";
                    cout << voc[j] << "\n";
                    break;
                }
                if (i == voc.GetSize() - 1)
                    cout << " неизвестен.\n";
                j++;
                k++;
            }
            cout << "\n";
            system("pause");
            break;
        }
        case 2:
        {
            system("cls");
            gotoxy(0, 0);
            cout << "для выхода в меню введите слово 'назад'\nВведите слово: ";
            string word;
            string translation;
            getline(cin, word);
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            if (word == "назад")
                break;
            cout << "\nВведите перевод вашего слова: ";
            getline(cin, translation);
            transform(translation.begin(), translation.end(), translation.begin(), ::tolower);
            if (translation == "назад")
                break;
            bool flag = 0;
            for (int i = 0; i < voc.GetSize(); i++)
            {
                if (word == voc(i) || translation == voc(i))//
                {
                    flag = 1;
                    break;
                }
                if (word == voc[i] || translation == voc[i])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
            {
                cout << "слово или его перевод уже существует\n";
                system("pause");
                break;
            }
            fstream file;//
            file.open("wrds.txt", fstream::in | fstream::out | fstream::app);// я не знаю зачем это но без этого оно не работает.
            file << word << " [] " << translation << '\n';
            file.close();
            file.open("ords.txt", fstream::in | fstream::out | fstream::app);
            voc.push_back(word, translation, note, latin);
            break;
        }
        case 3:
        {
            system("cls");
            gotoxy(0, 0);
            cout << "Введите слово для которого будет создана заметка: ";
            string word;
            getline(cin, word);
            if (word == "назад")
                break;
            if (word == "")
                break;
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            bool flag = 0;
            long curr = 0;
            int count = 0;
            for (int i = 0; i < voc.GetSize(); i++)
            {
                if (word == voc(i))//
                {
                    flag = 1;
                    curr = i;
                    break;
                }
                if (word == voc[i])
                {
                    flag = 1;
                    curr = i;
                    break;
                }
                count++;
            }
            if (flag == 0) {
                cout << " не найдено.\n";
                system("pause");
            }
            else if(voc[count] != "") 
            {
                if(voc[count]!=""){}
                cout << "\nВведите заметку: ";
                string note;
                getline(cin, note);
                if (note == "назад")
                    break;
                voc[curr] = note;
                fstream file;//
                file.open("wrds.txt", fstream::in | fstream::out | fstream::app);// я не знаю зачем это но без этого оно не работает.
                file << curr << " [] " << note << '\n';
                file.close();
            }
            break;
        }
        case 4:
        {
            system("cls");
            int q = 0;
            long j = 0; 
            float k = 0;
            while (true) {
                system("cls");
                gotoxy(70, 5);
                cout << " Для выхода в меню нажмите 'esc' ";
                gotoxy(90, 20);
                cout << "|  стрелка вверх - вверх";
                gotoxy(90, 19);
                cout << "/\\";
                gotoxy(90, 25);
                cout << "|  стрелка вниз - вниз";
                gotoxy(90, 26);
                cout << "\\/";
                gotoxy(0, 0);
                j = q;
                k = j;
                for (int i = q; i < q + 30; i++)
                {
                    if (i >= voc.GetSize() || i < 0)
                        break;
                    SetColor(15, 0);
                    cout << "слово: "; SetColor(0, 15); 
                    cout << voc(i); SetColor(15, 0);
                    cout << " перевод: "; SetColor(0, 15); 
                    if(voc[i]!="\n")
                    cout << voc[i]; SetColor(15, 0); 
                    cout << " заметка: "; SetColor(0, 15); 
                    cout << voc[j]; SetColor(15, 0);
                    cout << " на латинском: "; 
                    SetColor(0, 15); cout << voc[k]; 
                    SetColor(15, 0); cout << '\n';
                    j++;
                    k = j;
                }
                do {
                    button = _getch();
                    gotoxy(0, 20);
                    if (button == ESCAPE)
                        break;
                } while (button != 224);
                if (button == ESCAPE)
                    break;
                else
                {
                    button = _getch(); // забираем оставшееся в буфере число
                    if (button == DOWN) // если стрлка вниз
                    {
                        q += 30;
                        if (q >= voc.GetSize())
                            q = 0;
                    }
                    else if (button == UP)// если стрелка вверх 
                    {
                        q -= 30;
                        if (q < 0)
                            q = voc.GetSize() - 30;
                    }
                }
            }
            break;
        }
        }
        if (action != 0)
        {
            system("cls");
            menu();
        }
        action = 0;
        switch (pos) //перемещение стрелочки
        {
        case 1:
            pos1();
            break;
        case 2:
            pos2();
            break;
        case 3:
            pos3();
            break;
        case 4:
            pos4();
            break;
        }
    }
}