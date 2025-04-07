#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// ----------------------------
// Macro para declarar estructuras y prototipos
// ----------------------------
#define DECLARE_LINKED_LIST(TYPE) \
    typedef struct Node_##TYPE { \
        TYPE data; \
        struct Node_##TYPE* next; \
    } Node_##TYPE; \
    Node_##TYPE* node_##TYPE##_create(TYPE);\
    Node_##TYPE* node_##TYPE##_destroy(Node_##TYPE*);\
    \
    typedef struct { \
        Node_##TYPE* head; \
        Node_##TYPE* tail; \
        size_t length; \
    } List_##TYPE; \
    \
    List_##TYPE* list_##TYPE##_create(void); \
    void list_##TYPE##_destroy(List_##TYPE* list); \
    bool list_##TYPE##_insert(List_##TYPE* list, TYPE data, size_t pos); \
    bool list_##TYPE##_append(List_##TYPE* list, TYPE data); \
    bool list_##TYPE##_remove_at(List_##TYPE* list, size_t pos); \
    bool list_##TYPE##_get(const List_##TYPE* list, size_t pos, TYPE* out); \
    size_t list_##TYPE##_length(const List_##TYPE* list); \
    void list_##TYPE##_print(const List_##TYPE* list, void (*print_fn)(TYPE)); \
    bool list_##TYPE##_contains(const List_##TYPE* list, TYPE data); \
    bool list_##TYPE##_remove(List_##TYPE* list, TYPE data);

// ----------------------------
// Macro para implementación
// ----------------------------
#define IMPLEMENT_LINKED_LIST(TYPE) \
    Node_##TYPE* node_##TYPE##_create(TYPE data){\
        Node_##TYPE* new_node = malloc(sizeof(Node_##TYPE)); \
        new_node->data = data;\
        new_node->next = NULL;\
        return new_node;\
    }\
    \
    Node_##TYPE* node_##TYPE##_destroy(Node_##TYPE *node){\
        if(node->next ==NULL){\
            free(node);\
            return NULL;\
        }\
        return node;\
    }\
    List_##TYPE* list_##TYPE##_create(void) { \
        List_##TYPE* list = malloc(sizeof(List_##TYPE)); \
        if (!list) return NULL; \
        list->head = list->tail = NULL; \
        list->length = 0; \
        return list; \
    } \
    \
    void list_##TYPE##_destroy(List_##TYPE* list) { \
        if (!list || !list->head) return; \
        Node_##TYPE* current = list->head; \
    do { \
        Node_##TYPE* temp = current; \
        current = current->next; \
        free(temp); \
    } while (current != list->head);\
    list->head = list->tail = NULL; \
    list->length = 0; \
        free(list); \
    } \
    \
    bool list_##TYPE##_insert(List_##TYPE* list, TYPE data, size_t pos) { \
        if (!list || pos > list->length) return false; \
        \
        Node_##TYPE* new_node = node_##TYPE##_create(data); \
        if (!new_node) return false; \
        \
        if (pos == 0) { \
            new_node->next = list->head; \
            list->head = new_node; \
            if (!list->tail) { \
                list->tail = new_node; \
                new_node->next = new_node; \
            } else { \
                list->tail->next = list->head; \
            } \
        } else if (pos == list->length) { \
            new_node->next = list->head; \
            list->tail->next = new_node; \
            list->tail = new_node; \
        } else { \
            Node_##TYPE* current = list->head; \
            for (size_t i = 0; i < pos - 1; ++i) { \
                current = current->next; \
            } \
            new_node->next = current->next; \
            current->next = new_node; \
        } \
        \
        list->length++; \
        return true; \
    } \
    \
    bool list_##TYPE##_append(List_##TYPE* list, TYPE data) { \
        return list_##TYPE##_insert(list, data, list->length); \
    } \
    \
    bool list_##TYPE##_remove_at(List_##TYPE* list, size_t pos) { \
        if (!list || pos >= list->length) return false; \
        \
        Node_##TYPE* to_delete = NULL; \
        \
        if (pos == 0) { \
            to_delete = list->head; \
            if (list->length == 1) { \
                list->head = list->tail = NULL; \
            } else { \
                list->head = list->head->next; \
                list->tail->next = list->head; \
            }\
        } else { \
            Node_##TYPE* current = list->head; \
            for (size_t i = 0; i < pos - 1; ++i) { \
                current = current->next; \
            } \
            to_delete = current->next; \
            current->next = to_delete->next; \
            if (pos == list->length - 1) { \
                list->tail = current; \
                list->tail->next = list->head; \
            }\
        } \
        \
        free(to_delete); \
        list->length--; \
        return true; \
    } \
    \
    bool list_##TYPE##_get(const List_##TYPE* list, size_t pos, TYPE* out) { \
        if (!list || !out || pos >= list->length) return false; \
        \
        Node_##TYPE* current = list->head; \
        for (size_t i = 0; i < pos; ++i) { \
            current = current->next; \
        } \
        \
        *out = current->data; \
        return true; \
    } \
    \
    size_t list_##TYPE##_length(const List_##TYPE* list) { \
        return list ? list->length : 0; \
    } \
    \
    bool list_##TYPE##_is_empty(const List_##TYPE* list) { \
        return list ? list->length == 0 : true; \
    } \
    \
    void list_##TYPE##_clear(List_##TYPE* list) { \
        if (!list || !list->head) return; \
        Node_##TYPE* current = list->head; \
        do { \
            Node_##TYPE* temp = current; \
            current = current->next; \
            free(temp); \
        } while (current != list->head);\
        \
        list->head = list->tail = NULL; \
        list->length = 0; \
    } \
    \
    void list_##TYPE##_print(const List_##TYPE* list, void (*print_fn)(TYPE)) { \
        if (!list || !print_fn) return; \
        \
        if (!list->head) { \
            printf("[]\n"); \
            return; \
        } \
        \
        printf("["); \
        Node_##TYPE* current = list->head; \
        size_t i = 0; \
        do { \
            print_fn(current->data); \
            if (++i < list->length) printf(", "); \
            current = current->next; \
        } while (current != list->head); \
        printf("]\n"); \
    } \
    \
    bool list_##TYPE##_contains(const List_##TYPE* list, TYPE data) { \
        if (!list || !list->head) return false; \
        \
        Node_##TYPE* current = list->head; \
        do { \
            if (current->data == data) { \
                return true; \
            } \
            current = current->next; \
        } while (current != list->head); \
        \
        return false; \
    } \
    \
    bool list_##TYPE##_remove(List_##TYPE* list, TYPE data) { \
        if (!list || !list->head) return false; \
        \
        Node_##TYPE* current = list->head; \
        Node_##TYPE* prev = list->tail; \
        \
        do { \
            if (current->data == data) { \
                if (current == list->head) { \
                    list->head = current->next; \
                    if (list->length == 1) { \
                        list->head = list->tail = NULL; \
                    } else { \
                        list->tail->next = list->head; \
                    } \
                } else if (current == list->tail) { \
                    list->tail = prev; \
                    list->tail->next = list->head; \
                } else { \
                    prev->next = current->next; \
                } \
                \
                free(current); \
                list->length--; \
                return true; \
            } \
            \
            prev = current; \
            current = current->next; \
        } while (current != list->head); \
        \
        return false; \
    }

// ----------------------------
// Declaración para tipos concretos
// ----------------------------
DECLARE_LINKED_LIST(int)
DECLARE_LINKED_LIST(char)
DECLARE_LINKED_LIST(float)

// ----------------------------
// Implementación para tipos concretos
// ----------------------------
#ifdef CIRCULAR_LINKED_LIST_IMPLEMENTATION
IMPLEMENT_LINKED_LIST(int)
IMPLEMENT_LINKED_LIST(char)
IMPLEMENT_LINKED_LIST(float)
#endif