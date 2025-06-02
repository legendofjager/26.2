#ifndef TASK_H
#define TASK_H

// ��������� ���� ������
typedef struct Node {
    int data;           // �������� ��������
    struct Node* prev;  // ��������� �� ���������� �������
    struct Node* next;  // ��������� �� ��������� �������
} Node;

// ��������� ������������ ����������� ������
typedef struct {
    Node* current;      // ������� ������� ������
    int id;             // ���������� ������������� ������
} CyclicList;

// ������� ��� ������ �� �������
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
