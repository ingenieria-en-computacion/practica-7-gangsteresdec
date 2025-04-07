#include <check.h>
#include <stdlib.h>
#define LINKED_LIST_IMPLEMENTATION
#include "linked_list.h"

// Función auxiliar para imprimir enteros (usada en pruebas)
void print_int(int value) {
    printf("%d ", value);
}
// Función auxiliar para imprimir flotantes (usada en pruebas)
void print_float(float value) {
    printf("%f ", value);
}
// Función auxiliar para imprimir caracteres (usada en pruebas)
void print_char(char value) {
    printf("%c ", value);
}

// Función auxiliar para comparar enteros
bool int_cmp(int a, int b) {
    return a == b;
}
// Función auxiliar para comparar flotantes
bool float_cmp(float a, float b) {
    return a == b;
}
// Función auxiliar para comparar caracteres
bool char_cmp(char a, char b) {
    return a == b;
}

/* ------------------------------------- */
/* Tests para listas de enteros (List_int) */
/* ------------------------------------- */

START_TEST(test_list_create) {
    //DECLARE_LINKED_LIST(int);
    List_int* list = list_int_create();
    ck_assert_ptr_nonnull(list);
    ck_assert_ptr_null(list->head);
    ck_assert_ptr_null(list->tail);
    ck_assert_uint_eq(list->length, 0);
    list_int_destroy(list);
}
END_TEST

START_TEST(test_append_and_length) {
    List_int* list = list_int_create();
    
    ck_assert(list_int_append(list, 10));
    ck_assert_uint_eq(list_int_length(list), 1);
    
    ck_assert(list_int_append(list, 20));
    ck_assert_uint_eq(list_int_length(list), 2);
    
    list_int_destroy(list);
    ck_assert_ptr_null(list);
}
END_TEST

START_TEST(test_insert_and_get) {
    List_int* list = list_int_create();
    int value = 0;
    
    list_int_insert(list, 10, 0);
    list_int_insert(list, 30, 1);
    list_int_insert(list, 20, 1);    
    
    ck_assert(list_int_get(list, 1, &value));
    ck_assert_int_eq(value, 20);
    
    list_int_destroy(list);
}
END_TEST

START_TEST(test_remove) {
    List_int* list = list_int_create();
    list_int_append(list, 10);
    list_int_append(list, 20);
    list_int_append(list, 30);
    
    ck_assert(list_int_remove_at(list, 1));  // Elimina 20
    ck_assert_uint_eq(list_int_length(list), 2);
    
    int value = 0;
    ck_assert(list_int_get(list, 1, &value));
    ck_assert_int_eq(value, 30);  // Lista: [10, 30]
    
    list_int_destroy(list);
}
END_TEST

/* ------------------------------------- */
/* Tests para listas de flotantes (List_float) */
/* ------------------------------------- */

START_TEST(test_list_create) {
    List_float* list = list_float_create();
    ck_assert_ptr_nonnull(list);
    ck_assert_ptr_null(list->head);
    ck_assert_ptr_null(list->tail);
    ck_assert_ufloat_eq(list->length, 0);
    list_float_destroy(list);
}
END_TEST

START_TEST(test_append_and_length) {
    List_float* list = list_float_create();
    
    ck_assert(list_float_append(list, 10.96));
    ck_assert_ufloat_eq(list_float_length(list), 1);
    
    ck_assert(list_float_append(list, 20.69));
    ck_assert_ufloat_eq(list_float_length(list), 2);
    
    list_float_destroy(list);
    ck_assert_ptr_null(list);
}
END_TEST

START_TEST(test_insert_and_get) {
    List_float* list = list_float_create();
    float value = 0;
    
    list_float_insert(list, 10.23, 0);
    list_float_insert(list, 30.46, 1);
    list_float_insert(list, 20.57, 1);    
    
    ck_assert(list_float_get(list, 1, &value));
    ck_assert_float_eq(value, 20.57);
    
    list_float_destroy(list);
}
END_TEST

START_TEST(test_remove) {
    List_float* list = list_float_create();
    list_float_append(list, 10.23);
    list_float_append(list, 20.46);
    list_float_append(list, 30.57);
    
    ck_assert(list_float_remove_at(list, 1));  // Elimina 20.46
    ck_assert_ufloat_eq(list_float_length(list), 2);
    
    float value = 0;
    ck_assert(list_float_get(list, 1, &value));
    ck_assert_float_eq(value, 30.57);  // Lista: [10.23, 30.57]
    
    list_float_destroy(list);
}
END_TEST

/* ------------------------------------- */
/* Tests para listas de caracteres (List_char) */
/* ------------------------------------- */

START_TEST(test_list_create) {

    List_char* list = list_char_create();
    ck_assert_ptr_nonnull(list);
    ck_assert_ptr_null(list->head);
    ck_assert_ptr_null(list->tail);
    ck_assert_uchar_eq(list->length, 0);
    list_char_destroy(list);
}
END_TEST

START_TEST(test_append_and_length) {
    List_char* list = list_char_create();
    
    ck_assert(list_char_append(list, a));
    ck_assert_uchar_eq(list_char_length(list), 1);
    
    ck_assert(list_char_append(list, b));
    ck_assert_uchar_eq(list_char_length(list), 2);
    
    list_char_destroy(list);
    ck_assert_ptr_null(list);
}
END_TEST

START_TEST(test_insert_and_get) {
    List_char* list = list_char_create();
    char value = 0;
    
    list_char_insert(list, a, 0);
    list_char_insert(list, c, 1);
    list_char_insert(list, b, 1);    
    
    ck_assert(list_char_get(list, 1, &value));
    ck_assert_char_eq(value, b);
    
    list_char_destroy(list);
}
END_TEST

START_TEST(test_remove) {
    List_char* list = list_char_create();
    list_char_append(list, a);
    list_char_append(list, b);
    list_char_append(list, c);
    
    ck_assert(list_char_remove_at(list, 1));  // Elimina b
    ck_assert_uint_eq(list_char_length(list), 2);
    
    int value = 0;
    ck_assert(list_char_get(list, 1, &value));
    ck_assert_int_eq(value, c);  // Lista: [10, 30]
    
    list_char_destroy(list);
}
END_TEST

/* ------------------------------------- */
/* Suite de pruebas principal */
/* ------------------------------------- */

Suite* linked_list_suite(void){
    Suite* s = suite_create("Linked List");
    
    TCase* tc_core = tcase_create("Core Functions");
    tcase_add_test(tc_core, test_list_create);
    tcase_add_test(tc_core, test_append_and_length);
    tcase_add_test(tc_core, test_insert_and_get);
    tcase_add_test(tc_core, test_remove);
    
    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    int number_failed;
    SRunner* sr = srunner_create(linked_list_suite());
    
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
