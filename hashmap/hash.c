//http://liuzhiqiangruc.iteye.com/blog/1871334

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>

// 初始化
// 1. 桶大小固定 128
// 2. 元素从内存中动态申请
// 3. 尽可能不要产生冲突
//
//  key 使用整数值
//
// 功能:
// 1. 插入，支持覆盖
// 2. 删除，注意回收内存
// 3. 遍历
//
// 数据结构体设计:
//

// 定义key和value类型
typedef uint32_t ENTRY_KEY;
typedef uint32_t ENTRY_VALUE;
#define MAX_HASH_SIZE 128

typedef struct _entry {
    ENTRY_KEY key;           // key
    ENTRY_VALUE value;       // value
    struct _entry* hashNext; // 出现hash冲突时，指向下一个冲突的元素
    struct _entry* prev;     // 前一个元素
    struct _entry* next;     // 后一个元素
} Entry;

typedef struct _hashTable {
    Entry* head;       // 第一个元素
    Entry* tail;       // 最后一个元素
    Entry* entry[MAX_HASH_SIZE]; // 固定桶大小，当然也可以修改为动态申请
} HashTable;

// 实现
// hash 函数
#define hash(x) x%MAX_HASH_SIZE

int put(HashTable* table, ENTRY_KEY key, ENTRY_VALUE value)
{
    printf("put [%d,%d]\n", key, value);
    uint32_t index = hash(key);
    Entry* last = NULL;
    Entry* e = table->entry[index];
    while(e != NULL && e->value != value) {
        last = e;
        e = e->hashNext;
    }

    if (e) {
        // replace an entry
        return 0;
    }

    e = (Entry*)malloc(sizeof(Entry));
    e->key = key;
    e->value = value;

    if (NULL != table->entry[index]) {
        // put to the last position of conflict link
        last->hashNext = e;
        e->hashNext = NULL;
    } else {
        // put to an empty bucket
        table->entry[index] = e;
    }

    if (NULL == table->head) {
        // empty hash table
         table->head = table->tail = e;
         return 0;
    }

    // set the last entry as tail
    table->tail->next = e;
    e->prev = table->tail;
    e->next = NULL;
    table->tail = e;

    return 0;
}

int del(HashTable* table, ENTRY_KEY key, ENTRY_VALUE value)
{
    printf("del [%d,%d]\n", key, value);
    uint32_t index = hash(key);
    Entry* e = table->entry[index];
    // Not found
    if (NULL == e) return 0;

    if (table->head == e) {
        table->head = e->next;
    } else if (table->tail == e) {
        table->tail = e->prev;
    } else {
        e->prev->next = e->next;
        e->next->prev = e->prev;
    }

    free(e);
    return 0;
}

void view(HashTable* table)
{
    printf("Hash table:\n");
    if (NULL == table) return;
    Entry* e = table->head;
    while (e) {
        printf("k-v [%d, %d]\n", e->key, e->value);
        e = e->next;
    }
    printf("\n");
}

int main()
{
    HashTable table;
    table.head = table.tail = NULL;

    uint32_t i = 0;
    for (i=0; i<MAX_HASH_SIZE; i++) table.entry[i] = NULL;

    put(&table, 1, 2);
    put(&table, 7, 2);
    put(&table, 1, 8);
    put(&table, 3, 9);
    view(&table);

    del(&table, 1, 8);
    view(&table);

    put(&table, 1, 8);
    view(&table);

    return 0;
}
