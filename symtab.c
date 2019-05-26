
/****************************************************/
/* File: symtab.c                                   */
/* Symbol table implementation for the TINY compiler*/
/* (allows only one symbol table)                   */
/* Symbol table is implemented as a chained         */
/* hash table                                       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "symtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* SIZE is the size of the hash table */
#define SIZE 211

/* SHIFT is the power of two used as multiplier
   in hash function  */
#define SHIFT 4

/* the hash function */
static int hash(char* key)
{
    int temp = 0;
    int i = 0;
    while (key[i] != '\0') {
        temp = ((temp << SHIFT) + key[i]) % SIZE;
        ++i;
    }
    return temp;
}

/* The record in the bucket lists for
 * each variable, including name, 
 * assigned memory location, and
 * the list of line numbers in which
 * it appears in the source code
 */
typedef struct BucketListRec {
    char* name;
    Record record;
    struct BucketListRec* next;
} * BucketList;

/* The local scope symbol table  */
typedef struct LocalSymbolTableRec {
    BucketList hashTable[SIZE];
    struct LocalSymbolTableRec* parent;
    struct LocalSymbolTableRec* next;
} * LocalSymbolTable;


typedef struct SymTableStateRec
{
    LocalSymbolTable root;            // global root of symbol table
    LocalSymbolTable lastConstructed; // local symbol table previously constructed
    LocalSymbolTable currentScope;    // current local scope symbol table

} SymbolTableState;

SymbolTableState state;

/* 
 * initialize symbol table
 */
void st_init()
{
    LocalSymbolTable table = malloc(sizeof(struct LocalSymbolTableRec));
    for (int i = 0; i < SIZE; ++i) {
        table->hashTable[i] = NULL;
    }
    table->parent          = NULL;
    table->next            = NULL;
    state.currentScope     = table;
    state.lastConstructed  = table;
    state.root             = table;
}

static void freeHashTable(BucketList table[])
{
    for (int i = 0; i < SIZE; ++i) {
        BucketList p = table[i];
        while (p != NULL) {
            BucketList t = p->next;
            free(t);
            p = t;
        }
    }
}

void st_free()
{
    LocalSymbolTable localTable = state.root;
    while(localTable)
    {
        freeHashTable(localTable->hashTable);
        LocalSymbolTable t = localTable->next;
        free(localTable);
        localTable = t;
    }
}

static BucketList accessHashTable(int key, BucketList table[], char* name)
{
    BucketList l = table[key];
    while ((l != NULL) && (strcmp(name, l->name) != 0))
        l = l->next;
    return l;
}

void st_enter_scope()
{
    LocalSymbolTable table       = malloc(sizeof(struct LocalSymbolTableRec));
    for (int i = 0; i < SIZE; ++i) {
        table->hashTable[i] = NULL;
    }
    table->parent                = state.currentScope;
    table->next                  = NULL;
    state.currentScope           = table;
    state.lastConstructed->next  = table;
    state.lastConstructed        = table;
}

void st_exit_scope()
{
    state.currentScope = state.currentScope->parent;
}

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert(char* name, Record record)
{
    int key                   = hash(name);
    LocalSymbolTable symTable = state.currentScope;
    BucketList bucket         = accessHashTable(key, symTable->hashTable, name);
    bucket                    =  malloc(sizeof(struct BucketListRec));
    bucket->name              = name;
    bucket->next              = NULL;
    bucket->record            = record;
    symTable->hashTable[key]  = bucket;
} /* st_insert */

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
Record st_lookup(char* name)
{
    LocalSymbolTable table = state.currentScope;
    int key                = hash(name);
    BucketList bucket      = NULL;
    while(table && !bucket)
    {
        bucket = accessHashTable(key, table->hashTable, name);
        table  = table->parent;
    }
    if(!bucket)
        return NULL;
    else
        return bucket->record;
}

static void printHashTable(BucketList table[], void (*print)(const char*, Record))
{
    for (int i = 0; i < SIZE; ++i) {
        BucketList p = table[i];
        while (p != NULL) {
            print(p->name, p->record);
            p = p->next;
        }
    }
}

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(void (*print)(const char*, Record))
{
    LocalSymbolTable localTable = state.root;
    while(localTable)
    {
        printHashTable(localTable->hashTable, print);
        localTable = localTable->next;
    }
} /* printSymTab */
