#include "TASK.h"
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#define MAX_LISTS 10

// Главное меню
void print_main_menu() {
    printf("\n--- Главное меню ---\n");
    printf("1. Создать новый список\n");
    printf("2. Выбрать список\n");
    printf("3. Удалить список\n");
    printf("4. Вывести все списки\n");
    printf("5. Выход\n");
    printf("Выберите действие: ");
}

// Меню операций со списком
void print_list_menu() {
    printf("\n--- Операции со списком ---\n");
    printf("1. Перейти к следующему элементу\n");
    printf("2. Перейти к предыдущему элементу\n");
    printf("3. Вставить после текущего\n");
    printf("4. Вставить перед текущим\n");
    printf("5. Удалить текущий элемент\n");
    printf("6. Создать копию списка\n");
    printf("7. Вернуться в главное меню\n");
    printf("Выберите действие: ");
}

int main() {

    setlocale(LC_ALL, "Russian");

    CyclicList* lists[MAX_LISTS] = {NULL};
    int list_count = 0;
    int next_id = 1;
    int current_list_id = -1;

    while (1) {
        print_main_menu();
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Создать новый список
                if (list_count < MAX_LISTS) {
                    lists[list_count] = create_list(next_id++);
                    printf("Создан список с ID: %d\n", lists[list_count]->id);
                    list_count++;
                } else {
                    printf("Достигнуто максимальное количество списков!\n");
                }
                break;

            case 2: // Выбрать список
                if (list_count == 0) {
                    printf("Нет доступных списков!\n");
                    break;
                }

                printf("Доступные списки (ID): ");
                for (int i = 0; i < list_count; i++) {
                    printf("%d ", lists[i]->id);
                }
                printf("\nВведите ID списка: ");

                int select_id;
                scanf("%d", &select_id);

                int found = 0;
                for (int i = 0; i < list_count; i++) {
                    if (lists[i]->id == select_id) {
                        current_list_id = i;
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("Список с ID %d не найден!\n", select_id);
                    break;
                }

                // Меню операций с выбранным списком
                while (1) {
                    printf("\nТекущий список: %d\n", lists[current_list_id]->id);
                    print_list(lists[current_list_id]);

                    print_list_menu();
                    int list_choice;
                    scanf("%d", &list_choice);

                    switch (list_choice) {
                        case 1: // Следующий элемент
                            move_next(lists[current_list_id]);
                            break;

                        case 2: // Предыдущий элемент
                            move_prev(lists[current_list_id]);
                            break;

                        case 3: // Вставить после текущего
                            printf("Введите значение: ");
                            int value_after;
                            scanf("%d", &value_after);
                            insert_after(lists[current_list_id], value_after);
                            break;

                        case 4: // Вставить перед текущим
                            printf("Введите значение: ");
                            int value_before;
                            scanf("%d", &value_before);
                            insert_before(lists[current_list_id], value_before);
                            break;

                        case 5: // Удалить текущий элемент
                            delete_current(lists[current_list_id]);
                            break;

                        case 6: // Создать копию
                            if (list_count < MAX_LISTS) {
                                CyclicList* copy = copy_list(
                                    lists[current_list_id],
                                    next_id++
                                );
                                lists[list_count++] = copy;
                                printf("Создана копия списка с ID: %d\n", copy->id);
                            } else {
                                printf("Достигнуто максимальное количество списков!\n");
                            }
                            break;

                        case 7: // Выход в главное меню
                            current_list_id = -1;
                            break;

                        default:
                            printf("Неверный выбор!\n");
                    }

                    if (list_choice == 7) break;
                }
                break;

            case 3: // Удалить список
                if (list_count == 0) {
                    printf("Нет доступных списков!\n");
                    break;
                }

                printf("Введите ID списка для удаления: ");
                int delete_id;
                scanf("%d", &delete_id);

                int delete_index = -1;
                for (int i = 0; i < list_count; i++) {
                    if (lists[i]->id == delete_id) {
                        delete_index = i;
                        break;
                    }
                }

                if (delete_index == -1) {
                    printf("Список с ID %d не найден!\n", delete_id);
                    break;
                }

                // Удаляем список
                free_list(lists[delete_index]);

                // Сдвигаем остальные списки
                for (int i = delete_index; i < list_count - 1; i++) {
                    lists[i] = lists[i + 1];
                }

                lists[list_count - 1] = NULL;
                list_count--;

                // Сбрасываем текущий список, если он был удален
                if (current_list_id == delete_index) {
                    current_list_id = -1;
                }
                printf("Список %d удален\n", delete_id);
                break;

            case 4: // Вывести все списки
                if (list_count == 0) {
                    printf("Нет доступных списков!\n");
                    break;
                }

                printf("\n--- Все списки ---\n");
                for (int i = 0; i < list_count; i++) {
                    print_list(lists[i]);
                }
                break;

            case 5: // Выход
                // Освобождаем память
                for (int i = 0; i < list_count; i++) {
                    free_list(lists[i]);
                }
                return 0;

            default:
                printf("Неверный выбор!\n");
        }
    }
}
