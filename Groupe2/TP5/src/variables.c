#include "variables.h"

// Initialiser la table des variables
void init_symbol_table()
{
    for (int i = 0; i < MAX_VARIABLES; i++)
    {
        symbol_table[i].is_defined = 0;
    }
}

// Fonction pour définir une variable
int set_variable(const char *name, const char *value)
{
    Variable *var = get_variable(name);
    if (var == NULL)
    {
        for (int i = 0; i < MAX_VARIABLES; i++)
        {
            if (!symbol_table[i].is_defined)
            {
                strncpy(symbol_table[i].name, name, MAX_VARIABLE_NAME_LEN);
                symbol_table[i].is_defined = 1;

                // Déterminer le type de valeur
                if (strchr(value, '.') != NULL)
                {
                    double real_value = atof(value);
                    symbol_table[i].type = VARIABLE_REAL;
                    symbol_table[i].value.real_value = real_value;
                }
                else if (value[0] == '"')
                {
                    symbol_table[i].type = VARIABLE_STRING;
                    strncpy(symbol_table[i].value.string_value, value + 1, strlen(value) - 2);
                    symbol_table[i].value.string_value[strlen(value) - 2] = '\0';
                }
                else
                {
                    int int_value = atoi(value);
                    symbol_table[i].type = VARIABLE_INT;
                    symbol_table[i].value.int_value = int_value;
                }
                return 1;
            }
        }
        return 0;
    }
    else
    {
        // Vérifier le type existant
        if (var->type == VARIABLE_INT && strchr(value, '.') == NULL && value[0] != '"')
        {
            var->value.int_value = atoi(value);
        }
        else if (var->type == VARIABLE_REAL && strchr(value, '.') != NULL)
        {
            var->value.real_value = atof(value);
        }
        else if (var->type == VARIABLE_STRING && value[0] == '"')
        {
            strncpy(var->value.string_value, value + 1, strlen(value) - 2);
            var->value.string_value[strlen(value) - 2] = '\0';
        }
        else
        {
            fprintf(stderr, "Erreur : changement de type non autorisé pour la variable %s\n", name);
            return 0;
        }
        return 1;
    }
}

// Fonction pour obtenir une variable
Variable *get_variable(const char *name)
{
    for (int i = 0; i < MAX_VARIABLES; i++)
    {
        if (symbol_table[i].is_defined && strncmp(symbol_table[i].name, name, MAX_VARIABLE_NAME_LEN) == 0)
        {
            return &symbol_table[i];
        }
    }
    return NULL;
}

// Fonction pour obtenir la valeur d'une variable sous forme de chaîne de caractères
char *get_variable_value(const char *name)
{
    Variable *var = get_variable(name);
    if (var == NULL)
    {
        return NULL;
    }

    switch (var->type)
    {
    case VARIABLE_INT:
        snprintf(var->value.string_value, MAX_STRING_VALUE_LEN, "%d", var->value.int_value);
        break;
    case VARIABLE_REAL:
        snprintf(var->value.string_value, MAX_STRING_VALUE_LEN, "%.2f", var->value.real_value);
        break;
    case VARIABLE_STRING:
        break;
    default:
        fprintf(stderr, "Erreur : type de variable inconnu\n");
        break;
    }

    return var->value.string_value;
}

// Fonction pour afficher une variable
void print_variable(const Variable *variable)
{
    if (variable == NULL || !variable->is_defined)
    {
        fprintf(stderr, "Erreur : la variable n'est pas définie\n");
        return;
    }

    switch (variable->type)
    {
    case VARIABLE_INT:
        printf("%s = %d\n", variable->name, variable->value.int_value);
        break;
    case VARIABLE_REAL:
        printf("%s = %.2f\n", variable->name, variable->value.real_value);
        break;
    case VARIABLE_STRING:
        printf("%s = \"%s\"\n", variable->name, variable->value.string_value);
        break;
    default:
        fprintf(stderr, "Erreur : type de variable inconnu\n");
        break;
    }
}