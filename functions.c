#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"


char* generate_random_card(){
    // Empieza es generador de numeros random
    srand(time(NULL));
    // card color array                           
    const char *color[5] = {"black", "red", "green", "yellow", "blue"};
    // card rank array  
    const char *rank[14] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "skip", "reverse", "draw", "wild", "wild_4"};
    // struct card in functions.h
    card random_card;
    // Generates random number(0-4) for color
    int card_color = rand() %5;                   
    // if to ensure imposible combinations of cards happen
    if (card_color == 0)                          
    {
    // Generates random number(0-1) for rank     
    int card_rank = rand() %1;
    // add 13 to card_rank so black cards are wild_4 o wild                    
    card_rank = card_rank + 13;
    // Assigns color to card                   
    random_card.color = (char*)color[card_color]; 
    // Assigns rank to card
    random_card.rank = (char*)rank[card_rank];          
    }
    else
    {
    // random number (0-12) for rank
    int card_rank = rand() %12;                   
    // Assigns color to card
    random_card.color = (char*)color[card_color]; 
    // Assigns rank to card 
    random_card.rank = (char*)rank[card_rank];    
    }
    //Generate static char to use in main.c
    static char generated_card[50];
    //create imageapth with 
    sprintf(generated_card,"cards/%s%s.png",random_card.color,random_card.rank);
    return generated_card;
}
