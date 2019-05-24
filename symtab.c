
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

/* the list of line numbers of the source 
 * code in which a variable is referenced
 */
typedef struct LineListRec {
    int lineno;
    struct LineListRec* next;
} * LineList;

/* The record in the bucket lists for
 * each variable, including name, 
 * assigned memory location, and
 * the list of line numbers in which
 * it appears in the source code
 */
typedef struct BucketListRec {
    char* name;
    LineList lines;
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
    table->parent                = state.currentScope;
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

static void printHashTable(BucketList table[], FILE* listing)
{
    for (int i = 0; i < SIZE; ++i) {
        if (table[i] != NULL) {
            BucketList l = table[i];
            while (l != NULL) {
                fprintf(listing, "%-14s ", l->name);
                /* LineList t = l->lines; */
                /* fprintf(listing, "%-14s ", l->name); */
                /* fprintf(listing, "%-8d  ", l->memloc); */
                /* while (t != NULL) { */
                /*     fprintf(listing, "%4d ", t->lineno); */
                /*     t = t->next; */
                /* } */
                /* fprintf(listing, "\n"); */
                /* l = l->next; */
            }
        }
    }
}

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(FILE* listing)
{
    fprintf(listing, "Variable Name  Location   Line Numbers\n");
    fprintf(listing, "-------------  --------   ------------\n");
    
    LocalSymbolTable localTable = state.root;
    while(localTable)
    {
        printHashTable(localTable->hashTable, listing);
        localTable = localTable->next;
    }
} /* printSymTab */
