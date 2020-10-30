#include "common_list.h"

void list_init(List* list, uint8_t list_type)
{
    list->list_type = list_type;
    list->list_length = 0;
    list->begin = 0;
    list->end = 0;
    list->index = 0;
}

void list_insert_first(List* list, Node* node)
{
    list->begin = node;
    list->end = node;
    node->prev = node;
    node->next = node;
    node->list = list;
    ++list->list_length;
}

void list_insert_end(List* list, Node* node)
{
    if (list->list_length == 0) {
        list_insert_first(list, node);
    } else {
        node->prev = list->end;
        node->next = list->begin;
        list->begin->prev = node;
        list->end->next = node;
        list->end = node;
        node->list = list;
        ++list->list_length;
    }
}

void list_insert_begin(List* list, Node* node)
{
    if (list->list_length == 0) {
        list_insert_first(list, node);
    } else {
        node->next = list->begin;
        node->prev = list->end;
        list->begin->prev = node;
        list->end->next = node;
        node->list = list;
        list->begin = node;
        ++list->list_length;
    }
}

void list_remove_last(List* list)
{
    list->list_length = 0;
    list->begin = 0;
    list->end = 0;
    list->index = 0;
}

void list_remove_begin(List* list)
{
    list->begin = list->begin->next;
    list->begin->prev = list->end;
    list->end->next = list->begin;
    --list->list_length;
}

void list_remove_end(List* list)
{
    list->end = list->end->prev;
    list->end->next = list->begin;
    list->begin->prev = list->end;
    --list->list_length;
}

Node* list_get_max(List* list)
{
    if (list->list_type == LIST_NORMAL) {
        return 0;
    } else if (list->list_type == LIST_ASCENDING) {
        return list->end;
    } else {
        return list->begin;
    }
}

Node* list_get_min(List* list)
{
    if (list->list_type == LIST_NORMAL) {
        return 0;
    } else if (list->list_type == LIST_ASCENDING) {
        return list->begin;
    } else {
        return list->end;
    }
}

void list_remove(List* list, Node* node)
{
    if (list->begin == node) { //第一个或者只有一个
        list_remove_begin(list);
    } else if (list->end == node) { //最后一个
        list_remove_end(list);
    } else { //第二个到倒数第二个
        list->index = list->begin->next;
        while (list->index != list->end) {
            if (list->index == node) {
                list->index->prev->next = list->index->next;
                list->index->next->prev = list->index->prev;
                --list->list_length;
                break;
            } else {
                list->index = list->index->next;
            }
        }
    }
}

uint8_t list_insert_ascending(List* list, Node* node)
{
    if (list->list_length == 0) {
        list_insert_first(list, node);
    } else {
        if (list->end->priority <= node->priority) { //判断最后一个节点或者是只有一个节点
            if (list->end == node) {
                return 0; //节点已经存在直接退出  
            } 
            list_insert_end(list, node);
        } else if (list->begin->priority > node->priority) { //判断第一个节点
            if (list->begin == node) {
                return 0; //节点已经存在直接退出  
            } 
            list_insert_begin(list, node);
        } else { //判断第二个到倒数第二个节点
            list->index = list->begin->next;
            while (list->index != list->end) { 
                if (list->index->priority <= node->priority) {
                    if (list->index == node) {
                        return 0; //节点已经存在直接退出  
                    } 
                    list->index = list->index->next;
                } else {
                    break;
                }
            }

            node->next = list->index;
            node->prev = list->index->prev;
            list->index->prev->next = node;
            list->index->prev = node;
            node->list = list;
            ++list->list_length;
        }
    }

    return 1;
}

uint8_t list_insert_descending(List* list, Node* node)
{
    if (list->list_length == 0) {
        list_insert_first(list, node);
    } else {
        if (list->end->priority >= node->priority) { //判断最后一个节点或者是只有一个节点
            if (list->end == node) {
                return 0; //节点已经存在直接退出  
            } 
            list_insert_end(list, node);
        } else if (list->begin->priority < node->priority) { //判断第一个节点
            if (list->begin == node) {
                return 0; //节点已经存在直接退出  
            } 
            list_insert_begin(list, node);
        } else { //判断第二个到倒数第二个节点
            list->index = list->begin->next;
            while (list->index != list->end) {
                if (list->index->priority >= node->priority) {
                    if (list->index == node) {
                        return 0; //节点已经存在直接退出  
                    } 
                    list->index = list->index->next;
                } else {
                    break;
                }
            }

            node->next = list->index;
            node->prev = list->index->prev;
            list->index->prev->next = node;
            list->index->prev = node;
            node->list = list;
            ++list->list_length;
        }
    }

    return 1;
}
