#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

void boardvalues();
char symbols[9];
void displayboard(char letter);
bool winner_(char letter, int a);
bool winner_x(char letter, int a);
bool winner_l(char letter, int a);

int main(void)
{
    printf("\n*********************\n");
    printf("  TIC TAC TOE GAME\n");
    printf("*********************\n\n");

    char player1[50], player2[50], name[50], name1[50], name2[50];
    printf("Enter Player 1 Name: ");
    fgets(name1, sizeof(name1), stdin);
    name1[strlen(name1) - 1] = '\0';

    printf("Enter Player 2 Name: ");
    fgets(name2, sizeof(name2), stdin);
    name2[strlen(name2) - 1] = '\0';

    int namechecking = 0;
    do
    {
        printf("\nWho want to play first: ");
        fgets(name, sizeof(name), stdin);
        name[strlen(name) - 1] = '\0';
        if (((strcmp(name, name1) == 0) || (strcmp(name, name2) == 0)))
        {
            namechecking = 1;
            break;
        }
        printf("Only names %s and %s are Valid!\n", name1, name2);
    } while (namechecking == 0);

    strcpy(player1, name);
    if (strcmp(name1, name) == 0)
    {
        strcpy(player2, name2);
    }
    else
    {
        strcpy(player2, name1);
    }

    char cross = 'X';
    char circle = 'O';

    printf("\nGuidelines: %s and %s, Press the below key numbers to place the symbols!\n", name1, name2);
    boardvalues();

    player1[0] = toupper(player1[0]);
    player2[0] = toupper(player2[0]);

    char winner[50];
    int choice1, choice2, i;
    for (i = 0; i < 9; i++)
    {
        if ((i + 1) % 2 == 0)
        {
            printf("%s Turn: ", player2);
            scanf("%d", &choice2);

            if (symbols[choice2 - 1] == 'O' || symbols[choice2 - 1] == 'X' || (choice2 < 1 || choice2 > 9))
            {
                printf("%s did't placed properly the symbol!\n\n", player2);
                i--;
            }
            else
            {
                symbols[choice2 - 1] = 'O';
                displayboard(circle);
            }
        }
        else
        {
            printf("%s Turn: ", player1);
            scanf("%d", &choice1);

            if (symbols[choice1 - 1] == 'X' || symbols[choice1 - 1] == 'O' || (choice1 < 1 || choice1 > 9))
            {
                printf("%s did't placed properly the symbol!\n\n", player1);
                i--;
            }
            else
            {
                symbols[choice1 - 1] = 'X';
                displayboard(cross);
            }
        }

        if (winner_(cross, 1) || winner_(cross, 4) || winner_(cross, 7) || winner_x(cross, 1)
            || winner_x(cross, 3) || winner_l(cross, 0) || winner_l(cross, 1) || winner_l(cross, 2))
        {
            printf("\n%s WON!\n\n", player1);
            strcpy(winner, player1);
            break;
        }
        else if (winner_(circle, 1) || winner_(circle, 4) || winner_(circle, 7) || winner_x(circle, 1)
            || winner_x(circle, 3) || winner_l(circle, 0) || winner_l(circle, 1) || winner_l(circle, 2))
        {
            printf("\n%s WON!\n\n", player2);
            strcpy(winner, player2);
            break;
        }
    }

    if (strcmp(winner, player1) != 0 && strcmp(winner, player2) != 0)
    {
        printf("Game Over! It's a Tie.\n\n");
        return 0;
    }

    FILE *file = fopen("History.txt", "a");
    if (file == NULL)
    {
        printf("Game was not saved!\n");
        return 2;
    }

    fprintf(file, "• Match: %s VS %s\n", player1, player2);
    fprintf(file, "• Result: %s WON! 🏆\n\n", winner);
    fclose(file);
    return 0;
}

void boardvalues()
{
    for (int i = 1; i <= 9; i++)
    {
        printf("| %d |", i);
        if (i == 3 || i == 6)
        {
            printf("\n");
        }
    }
    printf("\n\n");
}

void displayboard(char letter)
{
    printf("\n");
    for (int i = 1; i <= 9; i++)
    {
        if (symbols[i - 1] == 'O' || symbols[i - 1] == 'X')
        {
            printf("| %c |", symbols[i - 1]);
            if (i == 3|| i == 6)
                printf("\n");
        }
        else
        {
            printf("|   |");
            if (i == 3 || i == 6)
                printf("\n");
        }
    }
    printf("\n\n");
}

bool winner_(char letter, int a)
{
    if (symbols[a - 1] == letter && symbols[a] == letter && symbols[a + 1] == letter)
    {
        return true;
    }
    return false;
}

bool winner_x(char letter, int a)
{
    if (a == 1)
    {
        if (symbols[0] == letter && symbols[4] == letter && symbols[8] == letter)
        {
             return true;
        }
    }
    else
    {
        if (symbols[2] == letter && symbols[4] == letter && symbols[6] == letter)
        {
            return true;
        }
    }
    return false;
}

bool winner_l(char letter, int a)
{
    for (int i = a; i < 9; i += 3)
    {
        if (symbols[i] == letter && symbols[i + 3] == letter && symbols[i + 6] == letter)
        {
            return true;
            break;
        }
    }
    return false;
}

