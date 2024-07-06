#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct Node
{
    char* key;
    int value;
    struct Node* next;
} Node;

typedef struct
{
    Node** buckets;
} HashTable;

unsigned int HashFunction(const char* key)
{
    unsigned long int value = 0;

    for (int i = 0; i < strlen(key); i++)
    {
        value += key[i];
    }

    return value % TABLE_SIZE;
}

HashTable* Init()
{
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->buckets = (Node**)malloc(TABLE_SIZE * sizeof(Node*));
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        table->buckets[i] = NULL;
    }
    return table;
}

void Add(HashTable* table, const char* key, int value)
{
    unsigned int bucket = HashFunction(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = _strdup(key);
    newNode->value = value;
    newNode->next = table->buckets[bucket];
    table->buckets[bucket] = newNode;
}

int Search(HashTable* table, const char* key)
{
    unsigned int bucket = HashFunction(key);
    Node* node = table->buckets[bucket];
    while (node != NULL)
    {
        if (strcmp(node->key, key) == 0)
        {
            return node->value;
        }
        node = node->next;
    }
    return -1;
}

void Delete(HashTable* table, const char* key)
{
    unsigned int bucket = HashFunction(key);
    Node* node = table->buckets[bucket];
    Node* prev = NULL;

    while (node != NULL && strcmp(node->key, key) != 0)
    {
        prev = node;
        node = node->next;
    }

    if (node == NULL)
    {
        return;
    }

    if (prev == NULL)
    {
        table->buckets[bucket] = node->next;
    }
    else
    {
        prev->next = node->next;
    }

    free(node->key);
    free(node);
}

void FreeTable(HashTable* table)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Node* node = table->buckets[i];
        while (node != NULL)
        {
            Node* temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}

int main(void)
{
    HashTable* table = Init();

    Add(table, "key1", 1);
    Add(table, "key2", 2);
    Add(table, "key3", 3);

    printf("key1: %d\n", Search(table, "key1"));
    printf("key2: %d\n", Search(table, "key2"));
    printf("key3: %d\n", Search(table, "key3"));

    Delete(table, "key2");
    printf("key2: %d\n", Search(table, "key2"));

    FreeTable(table);

    return 0;
}