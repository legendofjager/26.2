#ifndef TASK_H
#define TASK_H

// Структура узла списка
typedef struct Node {
    int data;           // Значение элемента
    struct Node* prev;  // Указатель на предыдущий элемент
    struct Node* next;  // Указатель на следующий элемент
} Node;

// Структура циклического двусвязного списка
typedef struct {
    Node* current;      // Текущий элемент списка
    int id;             // Уникальный идентификатор списка
} CyclicList;

// Функции для работы со списком
CyclicList* create_list(int id);
CyclicList* copy_list(CyclicList* original, int new_id);
void insert_after(CyclicList* list, int value);
void insert_before(CyclicList* list, int value);
void delete_current(CyclicList* list);
void move_next(CyclicList* list);
void move_prev(CyclicList* list);
void print_list(CyclicList* list);
void free_list(CyclicList* list);

#endif
