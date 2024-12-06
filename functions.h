#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <time.h>

typedef struct{
    char *color;
    char *rank;
} card;

char* generate_random_card();

#endif