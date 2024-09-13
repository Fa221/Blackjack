#include <stdio.h>
#include <stdlib.h>

int dealing()
{
    int i;
    int card_raw = 0;
    int card = 0;
        card_raw = rand() % 13 + 1;
    for(i = 0; i < 1; i++){
        card_raw = rand() % 13 + 1;
            if (card_raw == 1){
                card = 11;
            }else if (card_raw == 0 || card_raw == 10 || card_raw == 11 || card_raw == 12){
                card = 10;
            }else{
                card = card_raw;
        }
    }
    return card;
}

void playing(double* money, int* player_card_total, int* dealer_card_total, int* gamerecord, double* sum, double* bet)
{
    int WON = 0;
    int LOSS = 1;
    int BJ = 2;
    int BUST = 3;
    int PUSH = 4;
    char decision;
    int add = 0;
    printf("Place your bet between 0 and 1000--> ");
    scanf("%lf", &*bet);
    int pc1 = dealing();
    int pc2 = dealing();
    int dc1 = dealing();
    int dc2 = dealing();
    *dealer_card_total = dc1 + dc2;
    *player_card_total = pc1 + pc2;
    printf("Your first card was %d your second card was %d and your total is %d\n", pc1, pc2, *player_card_total);
    printf("The dealers card was %d\n", dc2);
    printf("What would you like to do now(hit --> h, stand --> s)?: ");
    scanf(" %c", &decision);
    while (decision == 'h' && *player_card_total < 21){
        add = dealing();
        *player_card_total = *player_card_total + add;
        add = 0;
        printf("Your total now is %d\n", *player_card_total);
        printf("What would you like to do now(hit --> h, stand --> s)?: ");
        scanf(" %c", &decision);
        }
    if (*player_card_total > 21){
        printf("Bust! Your total was %d\n", *player_card_total);
        printf("The dealers hole card was %d\n", dc1);
        *money = *money - *bet;
        *sum = *sum - *bet;
        gamerecord[BUST]++;
    }else if(*player_card_total < 21 && *player_card_total < *dealer_card_total){
        printf("Loss! Your total was %d, the dealer had %d\n", *player_card_total, *dealer_card_total);
        printf("The dealers hole card was %d\n", dc1);
        *money = *money - *bet;
        *sum = *sum - *bet;
        gamerecord[LOSS]++;
    }else if(*player_card_total < 21 && *player_card_total > *dealer_card_total){
        printf("Win! Your total was %d, the dealer had %d\n", *player_card_total, *dealer_card_total);
        printf("The dealers hole card was %d\n", dc1);
        *money = *money + *bet;
        *sum = *sum + *bet;
        gamerecord[WON]++;
    }else if(*player_card_total == 21){
        printf("Blackjack! Your total was %d, the dealer had %d\n", *player_card_total, *dealer_card_total);
        printf("The dealers hole card was %d\n", dc1);
        *money = *money + (*bet * 1.5);
        *sum = *sum + (*bet * 1.5);
        gamerecord[BJ]++;
    }else if(*player_card_total < 21 && player_card_total == dealer_card_total){
        printf("PUSH! Your total was %d, the dealer had %d\n", *player_card_total, *dealer_card_total);
        printf("The dealers hole card was %d\n", dc1);
        *money = *money;
        *sum = *sum;
        gamerecord[PUSH]++;
    }
}

double beginning(int* gamerecord, double* money)
{
    FILE *game;
    char buffer[15];
    int line = 0;
    if ((game = fopen("C:/Users/Faraz/Desktop\blackjack.txt", "r")) == NULL){
        printf("new game\n");
    } else {
        printf("continual game\n");
        while (fgets(buffer, 15, game)){
            if (line == 0){
                *money = atof(buffer);
            } else if (line == 1){
                gamerecord[0] = atoi(buffer);
            } else if (line == 2){
                gamerecord[1] = atoi(buffer);
            }else if (line == 3){
                gamerecord[2] = atoi(buffer);
            }else if (line == 4){
                gamerecord[3] = atoi(buffer);
            }else if (line == 5){
                gamerecord[4] = atoi(buffer);
            }else if (line == 6){
                gamerecord[5] = atoi(buffer);
            }
            line++;
        }
    }
}
double ending(double* money, int* gamerecord, double* sum)
{
    char buffer[15];
    int i=0;
    int j=0;
    FILE *game;
    printf("Thank you for playing! Here are your results\n");
    printf("Money: %lf\n", *money);
    printf("Amount of money earned/lost: %lf\n", *sum);
    printf("Number of Wins --> %d\n", gamerecord[0]);
    printf("Number of Losses --> %d\n", gamerecord[1]);
    printf("Number of BlackJacks --> %d\n", gamerecord[2]);
    printf("Number of Busts --> %d\n", gamerecord[3]);
    printf("Number of Pushes --> %d\n", gamerecord[4]);

    if ((game = fopen("C:/Users/Faraz/Desktop/blackjack.txt", "r")) != NULL){
        save_line_float(game, money);
        for (j=0; j < 6; j++) {
            save_line_int(game, gamerecord[j]);
        }
    }
}

void save_line_float(FILE *game, double *money_val) {
    char buffer[15];
    int i;
    for (i=0; i < 15; i++) {
        buffer[i] = ' ';
    }
    sprintf(buffer, "%.2f", money_val);
    fprintf(game, "%s\n", buffer);
}
void save_line_int(FILE *game, int int_val) {
    char buffer[15];
    int i;
    for (i=0; i < 15; i++) {
        buffer[i] = ' ';
    }
    sprintf(buffer, "%d", int_val);
    fprintf(game, "%s\n", buffer);
}

int main()
{
    int gamerecord[5] = {0,0,0,0,0};
//------------------------------------------------------------------------------
    char choice;
    double money = 1000;
    double sum = 0;
    double bet = 0;
    int player_card_total = 0;
    int dealer_card_total = 0;
//------------------------------------------------------------------------------
    beginning(&money, &gamerecord);
    printf("Welcome! Ready to start? (yes --> y, No --> n): ");
    scanf(" %c", &choice);
    while (choice == 'y' && money > 0){
        playing(&money, &player_card_total, &dealer_card_total, &gamerecord, &sum, &bet);
        printf("Play again? (yes --> y, No --> n): ");
        printf("\n");
        scanf(" %c", &choice);
    }
    ending(&money, &gamerecord, &sum);
    return 0;
}



