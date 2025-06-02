#include "TASK.h"
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#define MAX_LISTS 10

// ������� ����
void print_main_menu() {
    printf("\n--- ������� ���� ---\n");
    printf("1. ������� ����� ������\n");
    printf("2. ������� ������\n");
    printf("3. ������� ������\n");
    printf("4. ������� ��� ������\n");
    printf("5. �����\n");
    printf("�������� ��������: ");
}

// ���� �������� �� �������
void print_list_menu() {
    printf("\n--- �������� �� ������� ---\n");
    printf("1. ������� � ���������� ��������\n");
    printf("2. ������� � ����������� ��������\n");
    printf("3. �������� ����� ��������\n");
    printf("4. �������� ����� �������\n");
    printf("5. ������� ������� �������\n");
    printf("6. ������� ����� ������\n");
    printf("7. ��������� � ������� ����\n");
    printf("�������� ��������: ");
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
            case 1: // ������� ����� ������
                if (list_count < MAX_LISTS) {
                    lists[list_count] = create_list(next_id++);
                    printf("������ ������ � ID: %d\n", lists[list_count]->id);
                    list_count++;
                } else {
                    printf("���������� ������������ ���������� �������!\n");
                }
                break;

            case 2: // ������� ������
                if (list_count == 0) {
                    printf("��� ��������� �������!\n");
                    break;
                }

                printf("��������� ������ (ID): ");
                for (int i = 0; i < list_count; i++) {
                    printf("%d ", lists[i]->id);
                }
                printf("\n������� ID ������: ");

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
                    printf("������ � ID %d �� ������!\n", select_id);
                    break;
                }

                // ���� �������� � ��������� �������
                while (1) {
                    printf("\n������� ������: %d\n", lists[current_list_id]->id);
                    print_list(lists[current_list_id]);

                    print_list_menu();
                    int list_choice;
                    scanf("%d", &list_choice);

                    switch (list_choice) {
                        case 1: // ��������� �������
                            move_next(lists[current_list_id]);
                            break;

                        case 2: // ���������� �������
                            move_prev(lists[current_list_id]);
                            break;

                        case 3: // �������� ����� ��������
                            printf("������� ��������: ");
                            int value_after;
                            scanf("%d", &value_after);
                            insert_after(lists[current_list_id], value_after);
                            break;

                        case 4: // �������� ����� �������
                            printf("������� ��������: ");
                            int value_before;
                            scanf("%d", &value_before);
                            insert_before(lists[current_list_id], value_before);
                            break;

                        case 5: // ������� ������� �������
                            delete_current(lists[current_list_id]);
                            break;

                        case 6: // ������� �����
                            if (list_count < MAX_LISTS) {
                                CyclicList* copy = copy_list(
                                    lists[current_list_id],
                                    next_id++
                                );
                                lists[list_count++] = copy;
                                printf("������� ����� ������ � ID: %d\n", copy->id);
                            } else {
                                printf("���������� ������������ ���������� �������!\n");
                            }
                            break;

                        case 7: // ����� � ������� ����
                            current_list_id = -1;
                            break;

                        default:
                            printf("�������� �����!\n");
                    }

                    if (list_choice == 7) break;
                }
                break;

            case 3: // ������� ������
                if (list_count == 0) {
                    printf("��� ��������� �������!\n");
                    break;
                }

                printf("������� ID ������ ��� ��������: ");
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
                    printf("������ � ID %d �� ������!\n", delete_id);
                    break;
                }

                // ������� ������
                free_list(lists[delete_index]);

                // �������� ��������� ������
                for (int i = delete_index; i < list_count - 1; i++) {
                    lists[i] = lists[i + 1];
                }

                lists[list_count - 1] = NULL;
                list_count--;

                // ���������� ������� ������, ���� �� ��� ������
                if (current_list_id == delete_index) {
                    current_list_id = -1;
                }
                printf("������ %d ������\n", delete_id);
                break;

            case 4: // ������� ��� ������
                if (list_count == 0) {
                    printf("��� ��������� �������!\n");
                    break;
                }

                printf("\n--- ��� ������ ---\n");
                for (int i = 0; i < list_count; i++) {
                    print_list(lists[i]);
                }
                break;

            case 5: // �����
                // ����������� ������
                for (int i = 0; i < list_count; i++) {
                    free_list(lists[i]);
                }
                return 0;

            default:
                printf("�������� �����!\n");
        }
    }
}
