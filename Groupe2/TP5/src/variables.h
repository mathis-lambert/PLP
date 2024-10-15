#ifndef VARIABLES_H
#define VARIABLES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#define MAX_VARIABLES 100
#define MAX_VARIABLE_NAME_LEN 64
#define MAX_STRING_VALUE_LEN 256

// Enumération des types de variables
typedef enum
{
    VARIABLE_INT,
    VARIABLE_REAL,
    VARIABLE_STRING
} VariableType;

// Structure représentant une variable
typedef struct
{
    char name[MAX_VARIABLE_NAME_LEN]; // Nom de la variable (UTF-8)
    VariableType type;                // Type de la variable
    union
    {
        int int_value;
        double real_value;
        char string_value[MAX_STRING_VALUE_LEN];
    } value;
    int is_defined; // Indique si la variable est définie
} Variable;

// Table des variables (table de symboles)
Variable symbol_table[MAX_VARIABLES];

// Fonctions pour gérer les variables
void init_symbol_table();
int set_variable(const char *name, const char *value);
Variable *get_variable(const char *name);
char *get_variable_value(const char *name);
void print_variable(const Variable *variable);

#endif // VARIABLES_H