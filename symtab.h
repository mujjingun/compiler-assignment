/****************************************************/
/* File: symtab.h                                   */
/* Symbol table interface for the TINY compiler     */
/* (allows only one symbol table)                   */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h>

typedef struct ActivationRecord* Record;
typedef struct SymTableStateRec* SymTable;

/* 
 * initialize symbol table
 */
SymTable st_init(void (*freeRecord)(Record));

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert(SymTable state, const char* name, Record record);

/*
 * Create a new child scope
 */ 
void st_enter_scope(SymTable state);

/*
 * Go back to the previous scope
 */ 
void st_exit_scope(SymTable state);

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
Record st_lookup(SymTable state, char* name);

/*
 * destroy symbol table
 */
void st_free(SymTable state);

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(SymTable state, const char* heading, void (*print)(const char*, Record));

#endif
