#include "TASK.h"
#include <stdlib.h>
#include <stdio.h>

// Создание нового пустого списка
CyclicList* create_list(int id) {
    CyclicList* list = (CyclicList*)malloc(sizeof(CyclicList));
    list->current = NULL;
    list->id = id;
    return list;
}

// Создание глубокой копии списка
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

// Вставка нового элемента после текущего
void insert_after(CyclicList* list, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;

    if (list->current == NULL) {
        // Список пуст
        new_node->prev = new_node;
        new_node->next = new_node;
        list->current = new_node;
    } else {
        // Вставка в непустой список
        new_node->prev = list->current;
        new_node->next = list->current->next;
        list->current->next->prev = new_node;
        list->current->next = new_node;
    }
}

// Вставка нового элемента перед текущим
void insert_before(CyclicList* list, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;

    if (list->current == NULL) {
        // Список пуст
        new_node->prev = new_node;
        new_node->next = new_node;
        list->current = new_node;
    } else {
        // Вставка в непустой список
        new_node->prev = list->current->prev;
        new_node->next = list->current;
        list->current->prev->next = new_node;
        list->current->prev = new_node;
    }
}

// Удаление текущего элемента
void delete_current(CyclicList* list) {
    if (list->current == NULL) return; // Список пуст

    Node* to_delete = list->current;

    if (to_delete->next == to_delete) {
        // Единственный элемент в списке
        list->current = NULL;
    } else {
        // Обновляем связи соседних элементов
        to_delete->prev->next = to_delete->next;
        to_delete->next->prev = to_delete->prev;
        // Перемещаем текущий указатель на следующий элемент
        list->current = to_delete->next;
    }

    free(to_delete);
}

// Переход к следующему элементу
void move_next(CyclicList* list) {
    if (list->current != NULL) {
        list->current = list->current->next;
    }
}

// Переход к предыдущему элементу
void move_prev(CyclicList* list) {
    if (list->current != NULL) {
        list->current = list->current->prev;
    }
}

// Вывод списка с отметкой текущего элемента
void print_list(CyclicList* list) {
    if (list->current == NULL) {
        printf("Список %d: пуст\n", list->id);
        return;
    }

    printf("Список %d: [", list->id);
    Node* start = list->current;
    Node* current = start;

    do {
        if (current == list->current) {
            printf(" (%d) ", current->data); // Текущий элемент
        } else {
            printf(" %d ", current->data);
        }
        current = current->next;
    } while (current != start);

    printf("]\n");
}

// Освобождение памяти списка
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
