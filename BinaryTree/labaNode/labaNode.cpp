#include <iostream>
#include <random>
#include <stdlib.h>
#include <climits>
#include <queue>
#include <iomanip>
#include <cmath>
#include <windows.h>

using namespace std;



//Объявление структуры бинарного дерева
struct BinaryTree {
    int Data;
    BinaryTree* Left;
    BinaryTree* Right;
};

BinaryTree* BTree = NULL;

//Функция верного ввода
int getValidCin(const char* text, int min = INT_MIN, int max = INT_MAX) {
    int value;
    while (true) {
        cout << text << endl;
        if (cin >> value && value >= min && value <= max) {

            return value;
        }
        else { 
            cout << "Ошибка ввода, введите число от " << min << " до " << max << "\n" << endl; 
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}


// Красивый вывод дерева
void PrintTree(BinaryTree* Node, int depth = 0, int indent = 5) {
    if (Node == nullptr) return;

    // Затем левое поддерево (оно будет снизу)
    PrintTree(Node->Left, depth + 1, indent);


    // Печатаем текущий узел с отступом
    for (int i = 0; i < depth * indent; i++) cout << ' ';
    cout << Node->Data << '\n';

    // Сначала правое поддерево (оно будет сверху)
    PrintTree(Node->Right, depth + 1, indent);
}


//Создание бинарного дерева - строим дерево
void Make_Binary_Tree(BinaryTree** Node, int n) {
    if (n <= 0) {
        *Node = nullptr;
        return;
    }

    *Node = new BinaryTree();
    (*Node)->Data = 1 + rand() % 100;//Задаем значение вершины(левой)
    cout << "Изначальное значение вершины номер: "<< n << " равно:" << (*Node)->Data;
    if ((*Node)->Data % 2 != 0 || (*Node)->Data == 1) 
        cout << " Число нечетное, нового значения нет" << endl;
    if ((*Node)->Data % 2 == 0) {
        (*Node)->Data /= 2; //Если четное, то уменьшаем в два раза
        cout << " Новое значение равно: " << (*Node)->Data << endl;
    }

    // если нужно создать ещё хотя бы 1 вершину, делаем правого (лист)
    if (n > 1) {
        (*Node)->Right = new BinaryTree();
        (*Node)->Right->Data = 1 + rand() % 100;
        cout << "Изначальное значение вершины номер: " << n-1 << " равно:" << (*Node)->Right->Data;
        if ((*Node)->Right->Data % 2 != 0 || (*Node)->Right->Data == 1) 
            cout <<" Число нечетное, нового значения нет" << endl;
        if ((*Node)->Right->Data % 2 == 0) { 
            (*Node)->Right->Data /= 2;
            cout << " Новое значение равно: " << (*Node)->Right->Data << endl;
        }
        (*Node)->Right->Left = nullptr;
        (*Node)->Right->Right = nullptr;
    }
    else {
        (*Node)->Right = nullptr;
    }

    // для левого потомка оставшиеся вершины, кроме текущей и правого листа
    int left_count = n - 2; //т.к создали правую и саму корневую
    if (left_count > 0)
        Make_Binary_Tree(&((*Node)->Left), left_count);
    else
        (*Node)->Left = nullptr;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "rus");
    int N = getValidCin("Введите кол-во вершин(узлов) дерева \n", 1, 200);
    BinaryTree* Node = nullptr;
    Make_Binary_Tree(&Node, N);
    cout << endl;
    cout << endl << "ASCII представление бинарного дерева:" << endl;
    PrintTree(Node);

    return 0;
}























