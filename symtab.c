
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
static int hash(const char* key)
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
    const char* name;
    Record record;
    struct BucketListRec* next;
} * BucketList;

/* The local scope symbol table  */
typedef struct LocalSymbolTableRec {
    BucketList hashTable[SIZE];
    struct LocalSymbolTableRec* parent;
    struct LocalSymbolTableRec* next;
} * LocalSymbolTable;


struct SymTableStateRec
{
    LocalSymbolTable root;            // global root of symbol table
    LocalSymbolTable lastConstructed; // local symbol table previously constructed
    LocalSymbolTable currentScope;    // current local scope symbol table
    void (*freeRecord)(Record);       // destructor for the record

};

/* 
 * initialize symbol table
 */
SymTable st_init(void (*freeRecord)(Record))
{
    SymTable state = malloc(sizeof(struct SymTableStateRec));

    LocalSymbolTable table = malloc(sizeof(struct LocalSymbolTableRec));
    for (int i = 0; i < SIZE; ++i) {
        table->hashTable[i] = NULL;
    }
    table->parent          = NULL;
    table->next            = NULL;
    state->currentScope     = table;
    state->lastConstructed  = table;
    state->root             = table;
    state->freeRecord       = freeRecord;

    return state;
}

static void freeHashTable(SymTable state, BucketList table[])
{
    for (int i = 0; i < SIZE; ++i) {
        BucketList p = table[i];
        while (p != NULL) {
            BucketList t = p->next;
            state->freeRecord(p->record);
            free(p);
            p = t;
        }
    }
}

void st_free(SymTable state)
{
    LocalSymbolTable localTable = state->root;
    while(localTable)
    {
        LocalSymbolTable t = localTable->next;
        freeHashTable(state, localTable->hashTable);
        free(localTable);
        localTable = t;
    }

    free(state);
}

static BucketList accessHashTable(int key, BucketList table[], const char* name)
{
    BucketList l = table[key];
    while ((l != NULL) && (strcmp(name, l->name) != 0))
        l = l->next;
    return l;
}

void st_enter_scope(SymTable state)
{
    LocalSymbolTable table       = malloc(sizeof(struct LocalSymbolTableRec));
    for (int i = 0; i < SIZE; ++i) {
        table->hashTable[i] = NULL;
    }
    table->parent                = state->currentScope;
    table->next                  = NULL;
    state->currentScope           = table;
    state->lastConstructed->next  = table;
    state->lastConstructed        = table;
}

void st_exit_scope(SymTable state)
{
    state->currentScope = state->currentScope->parent;
}

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert(SymTable state, const char* name, Record record)
{
    int key                   = hash(name);
    LocalSymbolTable symTable = state->currentScope;
    BucketList bucket         = malloc(sizeof(struct BucketListRec));
    bucket->name              = name;
    bucket->record            = record;
    bucket->next              = symTable->hashTable[key];
    symTable->hashTable[key]  = bucket;
} /* st_insert */

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
Record st_lookup(SymTable state, char* name)
{
    LocalSymbolTable table = state->currentScope;
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
void printSymTab(SymTable state, void (*print)(const char*, Record))
{
    LocalSymbolTable localTable = state->root;
    while(localTable)
    {
        printHashTable(localTable->hashTable, print);
        localTable = localTable->next;
    }
} /* printSymTab */
