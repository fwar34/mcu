#ifndef _COMMON_LIST_H_
#define _COMMON_LIST_H_

#include <stdint.h>

struct _List;
typedef struct _Node {
    uint8_t data;
    struct _Node* prev;
    struct _Node* next;
    struct _List* list;
} Node;

typedef struct _List {
    uint8_t list_type;
    uint16_t list_length;
    Node* begin;
    Node* end;
    Node* index;
} List;

enum ListType
{
    LIST_NORMAL,
    LIST_ASCENDING,
    LIST_DESCENDING
};

void list_init(List* list, uint8_t list_type);
void list_insert_end(List* list, Node* node);
void list_insert_begin(List* list, Node* node);
Node* list_get_max(List* list);
Node* list_get_min(List* list);
void list_remove(List* list, Node* node);
//下面两次接口在一个程序中只能使用一个，要么升序要么降序，不能同时使用
void list_insert_ascending(List* list, Node* node);
void list_insert_descending(List* list, Node* node);

#endif
