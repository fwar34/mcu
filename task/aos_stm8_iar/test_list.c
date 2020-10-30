#include <string.h>
#include <stdio.h>
#include "common_list.h"

void list_output(List* list)
{
    printf("list output:\n");
    for (list->index = list->begin; list->index != list->end; list->index = list->index->next) {
        printf("node %p address %p priority %u\n",
               list->index->data, list->index, list->index->priority);
    }
    printf("node %p address %p priority %u\n", list->index->data, list->end, list->end->priority);
}

int main()
{
    List list;
    Node nodes[20];
    list_init(&list, LIST_ASCENDING);
    memset(nodes, 0, 20 * sizeof(Node));
    list_insert_first(&list, &nodes[0]);
    list_insert_end(&list, &nodes[1]);
    uint64_t i;
    for (i = 1; i < 19; ++i) {
        nodes[i].priority = i % 5;
        nodes[i].data = (void*)i;
        printf("insert node %lu address %p priority %u\n",
               i, &nodes[i], nodes[i].priority);
        list_insert_ascending(&list, &nodes[i]);
    }
    list_output(&list);

    list_remove(&list, list.begin);
    printf("list remove begin\n");
    list_output(&list);

    list_remove(&list, &nodes[3]);
    printf("list remove node 3 address %p priority %u\n",
           &nodes[3], nodes[3].priority);
    list_output(&list);

    list_remove(&list, &nodes[18]);
    printf("list remove node 18 address %p priority %u\n",
           &nodes[18], nodes[18].priority);
    list_output(&list);


    list_remove(&list, &nodes[9]);
    printf("list remove node 9 address %p priority %u\n",
           &nodes[9], nodes[9].priority);
    list_output(&list);


    list_remove(&list, list.end);
    printf("list remove end\n");
    list_output(&list);
}
