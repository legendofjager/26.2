#include "TASK.h"
#include <stdlib.h>
#include <stdio.h>

// �������� ������ ������� ������
CyclicList* create_list(int id) {
    CyclicList* list = (CyclicList*)malloc(sizeof(CyclicList));
    list->current = NULL;
    list->id = id;
    return list;
}

// �������� �������� ����� ������
CyclicList* copy_list(CyclicList* original, int new_id) {
    if (original == NULL) return NULL;

    CyclicList* copy = create_list(new_id);
    if (original->current == NULL) return copy;

    Node* orig_node = original->current;
    do {
        insert_after(copy, orig_node->data);
        orig_node = orig_node->next;
    } while (orig_node != original->current);

    return copy;
}

// ������� ������ �������� ����� ��������
void insert_after(CyclicList* list, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;

    if (list->current == NULL) {
        // ������ ����
        new_node->prev = new_node;
        new_node->next = new_node;
        list->current = new_node;
    } else {
        // ������� � �������� ������
        new_node->prev = list->current;
        new_node->next = list->current->next;
        list->current->next->prev = new_node;
        list->current->next = new_node;
    }
}

// ������� ������ �������� ����� �������
void insert_before(CyclicList* list, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;

    if (list->current == NULL) {
        // ������ ����
        new_node->prev = new_node;
        new_node->next = new_node;
        list->current = new_node;
    } else {
        // ������� � �������� ������
        new_node->prev = list->current->prev;
        new_node->next = list->current;
        list->current->prev->next = new_node;
        list->current->prev = new_node;
    }
}

// �������� �������� ��������
void delete_current(CyclicList* list) {
    if (list->current == NULL) return; // ������ ����

    Node* to_delete = list->current;

    if (to_delete->next == to_delete) {
        // ������������ ������� � ������
        list->current = NULL;
    } else {
        // ��������� ����� �������� ���������
        to_delete->prev->next = to_delete->next;
        to_delete->next->prev = to_delete->prev;
        // ���������� ������� ��������� �� ��������� �������
        list->current = to_delete->next;
    }

    free(to_delete);
}

// ������� � ���������� ��������
void move_next(CyclicList* list) {
    if (list->current != NULL) {
        list->current = list->current->next;
    }
}

// ������� � ����������� ��������
void move_prev(CyclicList* list) {
    if (list->current != NULL) {
        list->current = list->current->prev;
    }
}

// ����� ������ � �������� �������� ��������
void print_list(CyclicList* list) {
    if (list->current == NULL) {
        printf("������ %d: ����\n", list->id);
        return;
    }

    printf("������ %d: [", list->id);
    Node* start = list->current;
    Node* current = start;

    do {
        if (current == list->current) {
            printf(" (%d) ", current->data); // ������� �������
        } else {
            printf(" %d ", current->data);
        }
        current = current->next;
    } while (current != start);

    printf("]\n");
}

// ������������ ������ ������
void free_list(CyclicList* list) {
    if (list == NULL) return;

    Node* current = list->current;
    if (current != NULL) {
        Node* start = current;
        do {
            Node* temp = current;
            current = current->next;
            free(temp);
        } while (current != start);
    }

    free(list);
}
