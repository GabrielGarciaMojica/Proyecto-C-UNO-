#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



void generate_random_card(){

    const char *color[5] = {"Black", "Red", "Green", "Yellow", "Blue"};
    const char *rank[14] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "skip", "reverse", "draw", "wild", "wild_4"};

    typedef struct 
    {
        char *color;
        char *rank;
    } card;

    card random_card;

    int card_color = rand() %5;                   //Genera numero random (0-4)

    if (card_color == 0)                          //Si la carta es negra
    {
    int card_rank = random() %1;                  // Genera numero random (0-1) 
    card_rank = card_rank + 13;                   // Suma 1 a ese numero para asegurar que el rango sea wild_4 o wild
    random_card.color = (char*)color[card_color]; // Asigna el color a la carta
    random_card.rank = (char*)rank[card_rank];    // Asigna el rango a la carta      
    }
    else
    {
    int card_rank = random() %12;                 // Genera numero random (0-12)
    random_card.color = (char*)color[card_color]; // Asigna el color a la carta
    random_card.rank = (char*)rank[card_rank];    // Asigna el rango a la carta 
    }
    
    printf("The card is a %s %s\n", random_card.color, random_card.rank); // Imprime la carta generada
    
}

int main(){
    srand(time(NULL));       // Empieza es generador de numeros random
    generate_random_card();  // Llama la funcion
    return 0;                
}