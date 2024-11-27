#include <iostream>
#include <string>
using namespace std;

struct Book
{
    string author;
    string book_name;
    string company;
    string year;
    string str_count;
};

struct Elem
{
    Book inf;
    Elem* next;
    Elem* pred;
};

struct List
{
    Elem* first = 0;
    int len = 0;
};

void push_back(List& list, Elem* p) {
    if (list.first == 0) {
        list.first = p->next = p->pred = p;
        ++list.len;
    }
    else
    {
        p->next = list.first;
        p->pred = list.first->pred;
        list.first->pred->next = p;
        list.first->pred = p;
        ++list.len;
    }
}

void push_first(List& list, Elem* p) {
    push_back(list, p);
    list.first = p;
}

void after(List& list, Elem* pZad, Elem* p)
{
    p->next = pZad->next;
    p->pred = pZad;
    pZad->next->pred = p;
    pZad->next = p;
    ++list.len;
}

Elem* pop(List& list, Elem* p)
{
    if (list.first == 0 ) return 0;
    if (list.first->next == list.first)
    {
        if (p == list.first)
        {
            list.first = 0;
            return p;
        }
        else return 0;
    }
    if (p == list.first) list.first = list.first->next;
    p->pred->next = p->next;
    p->next->pred = p->pred;
    --list.len;
    return p;
}

void print(List& list) {
    int i = 1;
    Elem* p = list.first;
    int n = 0;
    do {
        //cout << "Книга " << i << endl;
        cout << p->inf.author << endl;
        /*cout << p->inf.book_name << endl;
        cout << p->inf.company << endl;
        cout << p->inf.year << endl;
        cout << p->inf.str_count << endl;
        ++i;*/
        ++n;
        p = p->next;
    } while (p != list.first);
    cout << n << endl;
}

void sort(List& list) {
    Elem* min;
    Elem* p = list.first->next;
    Elem* f,* _p;
    for (int i = 1; i < list.len; i++) {
        min = p->pred;
        for (int j = 0; j < i; ++j) {
            if (min->inf.author < p->inf.author) {
                after(list, min, pop(list, p));
                break;
            }
            min = min->pred;
        }
        if (min == list.first->pred) {
            push_first(list, pop(list, p));
        }
        p = list.first->next;
        for (int j = 0; j < i; ++j) p = p->next;
    }
}

string randomStrGen(int length) {
    static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    string result;
    result.resize(length);
    for (int i = 0; i < length; i++)
        result[i] = charset[rand() % charset.length()];

    return result;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));
    List Books;
    Elem* p;
    /*string a1;
    string a2;
    string a3;
    string a4;
    string a5;
    getline(cin, a1);
    while (a1 != "") {
        getline(cin, a2);
        getline(cin, a3);
        getline(cin, a4);
        getline(cin, a5);
        p = new Elem;
        p->inf = {a1, a2, a3, a4, a5};
        push_back(Books, p);
        cout << endl;
        getline(cin, a1);
    }*/
    for (int i = 0; i < 1000; ++i) {
        p = new Elem;
        p->inf = {randomStrGen(6), "", "", "", ""};
        push_back(Books, p);
    }
 //   cout << "Not sorted" << endl;
 //   print(Books);
    cout << "\n\nSorted\n\n" << endl;
    sort(Books);
    print(Books);
}
