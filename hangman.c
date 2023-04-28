//Adam Nguyen
//This program plays hangman
//Includes game difficulty, score system, customizable word bank

#include <stdio.h>
#include <string.h>
#include <stdlib.h>     // for call to rand() and srand()
#include <time.h>       // for call to time() in srand(time(NULL))
#include <ctype.h>

#define DEBUG 0        // 1-development mode, prints more info;
                        //0 - user mode, prints less
#define MAX_WRONG 6

char *toLowerCase(char *s)
{
    if (DEBUG == 1)
    {
        printf("\n\n****DEBUG****\n");
        printf("toLowerCase input is %s\n", s);
    }

    for (int i = 0; i < strlen(s); i++)
    {
        s[i] = tolower(s[i]);
    }

    if (DEBUG == 1)
    {
        printf("toLowerCase return is %s\n\n", s);
    }

    return s;
}

int userInput(char input[50])
{
    //returns 0 for int, 1 for float, 2 for char, 3 for string, 4 for mix

    if (DEBUG == 1)
    {
        printf("\n\n****DEBUG****\n");
        printf("userInput input is %s\n", input);
    }

    int isChar = 0, isFloat = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if (!((input[i]>='0') && (input[i]<='9')))
        {
            if (input[i] == '.')
            {
                isFloat++;
            }
            else
            {
                isChar++;
            }
        }
    }
    if ((isChar == 1) && (isFloat == 0))
    {
        if (DEBUG == 1)
        {
            printf("Char Detected\n\n");
        }
        return 2;
    }
    else if ((isFloat == 1) && (isChar == 0))
    {
        if (DEBUG == 1)
        {
            printf("Float Detected\n\n");
        }
        return 1;
    }
    else if ((isChar > 1) && (isFloat == 0))
    {
        if (DEBUG == 1)
        {
            printf("String Detected\n\n");
        }
        return 3;
    }
    else if ((isFloat == 0) && (isChar == 0))
    {
        if (DEBUG == 1)
        {
            printf("Int Detected\n\n");
        }
        return 0;
    }
    else
    {
        if (DEBUG == 1)
        {
            printf("Unknown Detected\n\n");
        }
        return 4;
    }
}

int menu()
{
    printf("Welcome to Hangman!\n\n");
    printf("1. Play Game\n2. Custom Word Bank\n3. Exit\n\n");
    printf("Type your selection ");

    int level, score = 0, games = 0, EAnogame = 0;
    char input[50];
    scanf("%s", input);

    if (DEBUG == 1)
    {
        printf("\n\n****DEBUG****\n");
        printf("User inputted %s\n", input);
    }

    if ((userInput(input) == 0) || (userInput(input) == 3))  //checks if input is a Int or a String
    {
        if ((atoi(input) == 1) || !(strcmp("play", toLowerCase(input))))   // Game Menu
        {
            int mode = 1;
            while (mode == 1)
            {
                printf("\nSelect game difficulty\n1. Easy\n2. Medium\n3. Hard\n4. Custom\n5. Go back to menu\n\n");
                printf("Type your selection ");
                scanf("%s", input);
                if ((userInput(input) == 0) || (userInput(input) == 3))
                {
                    if (DEBUG == 1)
                    {
                        printf("\n\n****DEBUG****\n");
                        printf("Valid Input\n\n");
                    }

                    if ((atoi(input) == 5) || !(strcmp("menu", toLowerCase(input))))
                    {

                        printf("\n\nReturning to menu...\n\n\n");
                        return 0;
                    }
                    else if ((atoi(input) == 1) || !(strcmp("easy", toLowerCase(input))))
                    {
                        level = 1;
                    }
                    else if ((atoi(input) == 2) || !(strcmp("medium", toLowerCase(input))))
                    {
                        level = 2;
                    }
                    else if ((atoi(input) == 3) || !(strcmp("hard", toLowerCase(input))))
                    {
                        level = 3;
                    }
                    else if ((atoi(input) == 4) || !(strcmp("custom", toLowerCase(input))))
                    {
                        level = 4;
                    }
                    else if (atoi(input) == 69)
                    {
                        printf("\n\n****Nice****\nAlso invalid Game Menu Choice\n\n");
                    }
                    else
                    {
                        printf("\n\nInvalid Game Menu Choice\n\n");
                    }

                    if (DEBUG == 1)
                    {
                        printf("\n\n****DEBUG****\n");
                        printf("Current score is %d\n\n", score);
                    }

                    if (level != 0)
                    {
                        games++;
                        score += game(level);                //game starts
                        int replay = 1;
                        EAnogame = 0;
                        while (replay == 1)     // Replay menu
                        {
                            printf("Do you want to play again?\n0. No\n1. Yes\nType your selection ");
                            scanf("%s", input);

                            if (DEBUG == 1)
                            {
                                printf("\n\n****DEBUG****\n");
                                printf("User inputted %s\n", input);
                            }

                            if (userInput(input) == 0)
                            {
                                if (DEBUG == 1)
                                {
                                    printf("\n\n****DEBUG****\n");
                                    printf("Valid Int Input\n\n");
                                }

                                if (atoi(input) == 0)   //No
                                {
                                    mode = 0;
                                    replay = 0;

                                    if (DEBUG == 1)
                                    {
                                        printf("\n\n****DEBUG****\n");
                                        printf("Returning score: %d\nGames played: %d\n\n", score, games);
                                    }
                                    printf("\n\nYour final score is %d out of %d\n\n", score, games);
                                    return 0;
                                }
                                else if (atoi(input) == 1)  //Yes
                                {
                                    mode = 1;
                                    replay = 0;

                                    if (DEBUG == 1)
                                    {
                                        printf("\n\n****DEBUG****\n");
                                        printf("Current score: %d\nCurrent games played: %d\n\n", score, games);
                                    }

                                    printf("\n\nYour current score is %d out of %d\n\n", score, games);
                                }
                                else
                                {
                                    if (DEBUG == 1)
                                    {
                                        printf("\n\n****DEBUG****\n");
                                        printf("EAnogame %d\n\n", EAnogame);
                                    }

                                    if (EAnogame == 5)  //EASTER EGG: No Game
                                    {
                                        printf("\n****Im not playing anymore****\n\n");
                                        score = 0;
                                        printf("\n\nYour final score is %d out of %d\n\n", score, games);
                                        mode = 0;
                                        replay = 0;
                                        return 0;
                                    }
                                    else
                                    {
                                        printf("\n****That's not an option****\n\n");
                                        replay = 1;
                                        EAnogame++;
                                    }
                                }
                            }
                            else if (userInput(input) == 3)
                            {

                                if (DEBUG == 1)
                                {
                                    printf("\n\n****DEBUG****\n");
                                    printf("Valid String Input\n\n");
                                }

                                if (!(strcmp("no", toLowerCase(input))))    //No
                                {
                                    mode = 0;
                                    replay = 0;

                                    if (DEBUG == 1)
                                    {
                                        printf("\n\n****DEBUG****\n");
                                        printf("Returning score: %d\nGames played: %d\n\n", score, games);
                                    }
                                    printf("\n\nYour final score is %d out of %d\n\n", score, games);
                                    return 0;

                                }
                                else if (!strcmp("yes", toLowerCase(input)))    //Yes
                                {
                                    mode = 1;
                                    replay = 0;

                                    if (DEBUG == 1)
                                    {
                                        printf("\n\n****DEBUG****\n");
                                        printf("Current score: %d\nCurrent games played: %d\n\n", score, games);
                                    }

                                    printf("\n\nYour current score is %d out of %d\n\n", score, games);
                                }
                                else
                                {
                                    if (DEBUG == 1)
                                    {
                                        printf("\n\n****DEBUG****\n");
                                        printf("EAnogame %d\n\n", EAnogame);
                                    }

                                    if (EAnogame == 5)  //EASTER EGG: No Game
                                    {
                                        printf("\n****Im not playing anymore****\n\n");
                                        score = 0;
                                        printf("\n\nYour final score is %d out of %d\n\n", score, games);
                                        mode = 0;
                                        replay = 0;
                                        return 0;
                                    }
                                    else
                                    {
                                        printf("\n****That's not an option****\n\n");
                                        replay = 1;
                                        EAnogame++;
                                    }
                                }
                            }
                            else
                            {
                                if (DEBUG == 1)
                                {
                                    printf("\n\n****DEBUG****\n");
                                    printf("EAnogame %d\n\n", EAnogame);
                                }

                                if (EAnogame == 5)  //EASTER EGG: No Game
                                {
                                    printf("\n****Im not playing anymore****\n\n");
                                    score = 0;
                                    printf("\n\nYour final score is %d out of %d\n\n", score, games);
                                    mode = 0;
                                    replay = 0;
                                    return 0;
                                }
                                else
                                {
                                    printf("\n****That's not an option****\n\n");
                                    replay = 1;
                                    EAnogame++;
                                }

                            }
                        }
                    }
                }
                else
                {
                    printf("\n\nInvalid Game Menu Choice\n\n");
                }
            }
        }
        else if ((atoi(input) == 2) || !(strcmp("custom", toLowerCase(input)))) // Custom Words Menu
        {
            int customLoop = 0;
            while (customLoop == 0)
            {
                printf("\n\nCustom Words Menu\n-----------------\n1. Show custom words list\n2. Add word\n3. Remove word\n4. Go back to menu\n\nType your selection ");
                scanf("%s", input);
                if ((userInput(input) == 0) || (userInput(input) == 3))
                {
                    if (DEBUG == 1)
                    {
                        printf("\n\n****DEBUG****\n");
                        printf("Valid Input\n\n");
                    }

                    if ((atoi(input) == 1) || !(strcmp("custom", toLowerCase(input))))
                    {
                        printFile("custom.txt");
                    }
                    else if ((atoi(input) == 2) || !(strcmp("add", toLowerCase(input))))
                    {
                        editFile("custom.txt", 1);
                    }
                    else if ((atoi(input) == 3) || !(strcmp("remove", toLowerCase(input))))
                    {
                        editFile("custom.txt", 0);
                    }
                    else if ((atoi(input) == 4) || !(strcmp("menu", toLowerCase(input))))
                    {
                        printf("\n\nReturning to menu...\n\n\n");
                        return 0;
                    }
                    else
                    {
                        printf("\n\nInvalid Custom Menu Choice\n");
                    }
                }
                else
                {
                    printf("\n\nInvalid Custom Menu Choice\n");
                }
            }
        }
        else if ((atoi(input) == 3) || !(strcmp("exit", toLowerCase(input))))  // Exit
        {
            return 1;
        }
        else if (atoi(input) == 69)
        {
            printf("\n\n****Nice****\nAlso invalid Main Menu Choice\n\n");
        }
        else    // User does not choose 1, 2, or 3 in Main Menu
        {
            printf("\n\nInvalid Main Menu Choice\n\n\n");
            return 0;
        }
    }
    else    //User does not enter a Int in Main Menu
    {
        printf("\n\nInvalid Main Menu Choice\n\n\n");
        return 0;
    }

}

void printFile (char* fileName)
{
    FILE * fp = fopen(fileName, "r+");
    char line[50];
    int size;

    if (fp == NULL)
    {
        printf("Failed to open file\n\n");
    }
    else
    {
        fgets(line, 50, fp);
        size = atoi(line);
        printf("\n\nWord Count: %d\n", size);
        for (int i = 0; i < size; i++)
        {
            fgets(line, 50, fp);
            printf("%s", line);
        }
    }
}

void editFile (char* fileName, int mode)    //mode (0 for remove, 1 for add)
{
    char edit[50], line[50];
    int size;

    FILE * fp = fopen(fileName, "r+");
    if (fp == NULL)
    {
        printf("Failed to open file\n\n");
    }
    else
    {
        fgets(line, 50, fp);
        size = atoi(line);  //Gets amount of words in file

        if (DEBUG == 1)
        {
            printf("\n\n****DEBUG****\n");
            printf("Size is %d\n", size);
        }

        char store[size][50];

        if (mode == 0)  //Remove word
        {
            printf("\nWhich word do you want to remove? ");
            scanf("%s", edit);

            if (DEBUG == 1)
            {
                printf("\n\n****DEBUG****\n");
                printf("edit is %s\n", edit);
            }

            for (int i = 0; i < size; i++)      //stores words from file
            {
                fgets(line, 50, fp);
                line[strlen(line) - 1] = '\0';
                printf("line is %s\n", line);
                if ((strcmp(line, toLowerCase(edit))) == 0) //skips word that needs to be removed
                {
                    printf("Skipped %s\n", line);
                }
                else
                {
                    strcpy(store[i], line);
                }
            }

            fclose(fp);
            fp = fopen(fileName, "w+");
            if (fp == NULL)
            {
                printf("Failed to open file\n\n");
            }
            else
            {
                fprintf(fp, "%d\n", size-1);        //prints the amount of words to file
                for (int i = 0; i < size; i++)      //reprints words to file
                {
                    fprintf(fp, "%s\n", store[i]);
                }
            }
            printf("\n\n****%s has been removed to custom word list****\n\n", edit);
        }
        else if (mode == 1) //Add word
        {
            printf("\nWhat word do you want to add? ");
            scanf("%s", edit);

            if (DEBUG == 1)
            {
                printf("\n\n****DEBUG****\n");
                printf("edit is %s\n", edit);
            }

            for (int i = 0; i < size; i++)
            {
                fgets(line, 50, fp);
                line[strlen(line) - 1] = '\0';
                strcpy(store[i], line);
            }

            fclose(fp);
            fp = fopen(fileName, "w+");
            if (fp == NULL)
            {
                printf("Failed to open file\n\n");
            }
            else
            {
                fprintf(fp, "%d\n", size+1);        //prints the amount of words to file
                for (int i = 0; i < size; i++)      //reprints words to file
                {
                    fprintf(fp, "%s\n", store[i]);
                }
                fprintf(fp, "%s\n", edit);          //prints added word to file
            }
            printf("\n\n****%s has been added to custom word list****\n\n", edit);
        }
        fclose(fp);
    }
}

char* levelToFile(int level)
{
    char* str;
    if (DEBUG == 1)
    {
        printf("\n\n****DEBUG****\n");
        printf("levelToFile input is %d\n", level);
    }

    if (level == 1)
    {
        str = "easy.txt";
    }
    else if (level == 2)
    {
        str = "medium.txt";
    }
    else if (level == 3)
    {
        str = "hard.txt";
    }
    else if (level == 4)
    {
        str = "custom.txt";
    }
    if (DEBUG == 1)
    {
        printf("levelToFile return is %s\n\n", str);
    }
    return str;
}

int game (int level)    //must return 1 if win, 0 if loss
{
    if (DEBUG == 1)
    {
        printf("\n\n****DEBUG****\n");
        printf("Game has started\n\n");
    }

    srand(time(NULL));

    int lineNum = 0, idx = 0, error = 0, turn = 0, EAwrongInput = 0, EAsameLetter = 0;
    char word[51], guess[50] = "", input[50];

    FILE * fp = NULL;
    fp = fopen(levelToFile(level), "r+");

    if (fp == NULL)
    {
        printf("Failed to open file\n\n");
        return 0;
    }
    else
    {
        fscanf(fp, "%d", &lineNum);
        idx = rand()%lineNum+1;           //idx will be a number between 1 and (N)
        for(int i = 0; i <= idx; i++)     //assumes there are at least N words in the file
        {
            fscanf(fp, "%s", word);
        }

        if (DEBUG == 1)
        {
            printf("\n\n****DEBUG****\n");
            printf("Random index = %d\nHidden word: %s\n\n", idx, word);
        }

        fclose(fp);
        int check[strlen(word)];
        for (int i = 0; i < strlen(word); i++)
        {
            check[i] = 0;
        }

        while(error <= MAX_WRONG)
        {

            guess[50] = "";
            int win = 1;

            if (DEBUG == 1)
            {
                printf("\n\n****DEBUG****\n");
                printf("Turn number %d\nError count %d\nWin is %d\nInput is %s\nHidden word is %s\nGuessed Letters: %s\nCheck Array: ", turn, error, win, input, word, guess);
                for (int i = 0; i < strlen(word); i++)
                {
                    printf("%d", check[i]);
                }
                printf("\nEaster Egg:\nWrong Input is %d\nSame Letter is %d", EAwrongInput, EAsameLetter);
                printf("\n\n");
            }

            printf("\nLevel: %d\n\n", level);     //level indicator
            printLife(error);

            printf("Letters Guessed: ");
            if(turn == 0)
            {
                printf("None\n");
            }
            else
            {
                printf("%s\n", guess);  //prints used letters
            }

            printf("Number of bad guesses: (%d / 6)\n\n", error);

            for (int i = 0; i < strlen(word); i++)  //prints empty and guessed letters
            {
                if(check[i] == 1)
                {
                    printf("%c ", word[i]);
                }
                else
                {
                    win = 0;
                    printf("_ ");
                }
            }

            if (win == 1)   //Detects if user won
            {
                printf("\n\nYou Won!!!\n\n");
                return 1;
            }

            printf("\n\nEnter a letter ");
            scanf("%s", input);

            int match = 0;
            if (userInput(input) == 2)                      //if user input is char
            {
                for (int i = 0; i < strlen(guess); i++)     //checks if letter was already guessed
                {
                    if (tolower(guess[i]) == tolower(input[0]))
                    {
                        if (DEBUG == 1)
                        {
                           printf("\n\nMATCH\n\n");
                        }

                        match = 1;
                    }
                }


                if (match == 0)
                {
                    int foundLetter = 0;

                    if (DEBUG == 1)
                    {
                        printf("\n\n****DEBUG****\n");
                        printf("\n\nLetter Added\n\n");
                    }

                    guess[turn] = tolower(input[0]);

                    for (int i = 0; i < strlen(word); i++)      //checks if letter in the word
                    {
                        if(tolower(word[i]) == tolower(input[0]))
                        {
                            check[i] = 1;
                            foundLetter = 1;
                        }
                    }
                    if(foundLetter == 0)
                    {
                        error++;
                    }
                }
                else    //EASTER EGG: Same Letter
                {
                    EAsameLetter++;
                    if ((EAsameLetter >= 5) && (EAsameLetter <= 10))
                    {
                        printf("\nYOU GUESSED THE LETTER ALREADY!!!\n");
                    }
                    else if (EAsameLetter == 68)
                    {
                        printf("\n\n****You have guessed the same letter 68 times now... ****\n\n");
                    }
                    else if (EAsameLetter == 69)
                    {
                        printf("\n\n****Nice****\n\n");
                    }
                    else
                    {
                        printf("\nYou already guessed this letter, try another letter\n");
                    }
                }
            }
            else if (userInput(input) == 3)     //user input is a String
            {
                if (!strcmp(word, toLowerCase(input)))  //checks if string is the word
                {
                    printf("\n\nYou Won!!!\n\n");
                    return 1;
                }
                else if (!strcmp("tammy", toLowerCase(input)))
                {
                    printf("\n\n****Just for you cutie****\n\n");   //EASTER EGG: for Tammy
                    if (error > 0)
                    {
                        error--;
                    }
                }
                else if ((!strcmp("richard", toLowerCase(input))) || (!strcmp("bitchard", toLowerCase(input))))
                {
                    printf("\n\n****Just for you bitch****\n\n");   //EASTER EGG: For Richard
                    error++;
                }
            }
            else        //EASTER EGG: Wrong Input
            {

                if (EAwrongInput == 3)
                {
                    printf("\n\n****Please, just enter a letter****\n\n");
                }
                else if ((EAwrongInput > 3) && (EAwrongInput < 6))
                {
                    printf("\n\n****Honestly you're wasting your time****\n\n");
                }
                else if (EAwrongInput == 6)
                {
                    printf("\n\n****I would commend you for being persistent but you're annoying me now****\n\n");
                }
                else if ((EAwrongInput == 7) || (EAwrongInput == 8))
                {
                    printf("\n\n****Stop.****\n\n");
                }
                else if (EAwrongInput == 9)
                {
                    printf("\n\n****Seriously STOP.****\n\n");
                }
                else if (EAwrongInput == 10)
                {
                    printf("\n\n****FUCK YOU RICHARD****\n\n");
                    error = 6;
                }
                else
                {
                    printf("\n\n****Wrong input, enter a letter****\n\n");
                }
                EAwrongInput++;

                if(DEBUG == 1)
                {
                    printf("\n\n****DEBUG****\n");
                    printf("EAwrongInput: %d\n\n", EAwrongInput);
                }
            }

            turn++;

            if (error == 6)
            {
                printf("------|\n");
                printf("|     |\n");
                printf("|     O\n");
                printf("|     |\n");
                printf("|    /|\\           YOU ARE DEAD\n");
                printf("|     |\n");
                printf("|    / \\\n");
                printf("-------------\n");
                printf("The word was: %s\n\n", word);
                return 0;
            }
        } //end of loop
    return 0;
    }
}

void printLife (int wrongs)
{
    switch(wrongs)   //death indicator (image)
    {
    case 0:
        printf("------|\n|     |\n|\n|\n|\n|\n|\n-------------\n");
        break;
    case 1:
        printf("------|\n|     |\n|     O\n|\n|\n|\n|\n-------------\n");
        break;
    case 2:
        printf("------|\n|     |\n|     O\n|     |\n|     |\n|     |\n|\n-------------\n");
        break;
    case 3:
        printf("------|\n");
        printf("|     |\n");
        printf("|     O\n");
        printf("|     |\n");
        printf("|    /|\n");
        printf("|     |\n");
        printf("|\n");
        printf("-------------\n");
        break;
    case 4:
        printf("------|\n");
        printf("|     |\n");
        printf("|     O\n");
        printf("|     |\n");
        printf("|    /|\\\n");
        printf("|     |\n");
        printf("|\n");
        printf("-------------\n");
        break;
    case 5:
        printf("------|\n");
        printf("|     |\n");
        printf("|     O\n");
        printf("|     |\n");
        printf("|    /|\\\n");
        printf("|     |\n");
        printf("|    /\n");
        printf("-------------\n");
        break;
    }
}

int main()
{
    int keepPlaying = 0;

    while (keepPlaying == 0)
    {
        keepPlaying = menu();
    }

    printf("\n\n****Thank you for playing my game! Goodbye!****\n\n");
}
