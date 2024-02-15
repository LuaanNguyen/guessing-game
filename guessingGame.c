//Luan Nguyen
//CSE240 A5 
//Due: Tuesday, February 13th at 11:59pm 

// 1. Using the guessing game code provided in our slides, add code to do the following:
// - prompt the user for their name
// - count the number of guesses for the user
// - keep the name and number of guesses in a data structure like a struct
// - keep an array of 5 structs to store the current leaders
// - when the user quits, the current leaders should be saved to a text file
// - when the game is started, the file should be read, if it exists

#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>


//create a struct to store the information for each player 
struct Player { 
    char name[100];
    int guesses; 
};

//This method saves current leader 
void saveCurrentLeader(struct Player leaders[], int numberOfLeaders ) {
    char filename[] = "/Users/luannguyen/Desktop/CSE240/leaders.txt"; //You can enter your own file name here
    FILE* fp = fopen( filename, "a");
    //check if the file exists
    if (fp == NULL) {
        printf("File is not found! Check your path again.\n");
        return;
    }
    for (int i = 0; i < numberOfLeaders; i++) {
        fprintf(fp, "%s %d\n", leaders[i].name, leaders[i].guesses);
    }
    fclose(fp); 

}

//This method gets the number of guess from the user
int getGuess() {
    int guess; 
    printf("Guess a value between 10 and 100: ");
    int userGuess = scanf("%d", &guess);
    while(getchar() != '\n'); // clear buffer

    while (userGuess != 1 || guess < 10 || guess > 100)
    {
        printf("Make sure your guess is between 10 and 100: ");
        userGuess = scanf("%d", &guess);
        while(getchar() != '\n'); // clear buffer
    }
    return guess;
}

//Game logic
int playGuessingGame() {
    int numberOfGuesses = 0;
    //Generate random number between 10 and 100 
    srand((unsigned int)time(NULL));
    int correctNumber = rand() % 91 + 10;
    double squareRoot = sqrt(correctNumber);

    printf("%.8f is the square root of what number? ", squareRoot);
    bool done = true;

    while (done) {
        int userGuess = getGuess(); 

        if (userGuess < correctNumber) {
            printf("Too low, guess again. ");
            numberOfGuesses++;
        }
        else if (userGuess > correctNumber) {
            printf("Too high, guess again. ");
             numberOfGuesses++;
        }
        else {
            done = false;
            numberOfGuesses++;
        }
    }
    printf("You got it, baby!\n");
    printf("You made %d guesses.\n", numberOfGuesses);
    return numberOfGuesses;
}

//This method display the current leaders from the file
void displayCurrentLeader(struct Player leaders[], int numberOfLeaders) {
    printf("Here are the current leaders:\n"); 
    for (int i = 0; i <= numberOfLeaders; i++) {
        printf("%s made %d guesses\n", leaders[i].name, leaders[i].guesses);
    }
}


int main() {
    char input;
    char playerName[100];
    struct Player leaders[5]; 
    int numberOfLeaders = 0;


    char filename[] = "/Users/luannguyen/Desktop/CSE240/leaders.txt";
    FILE* fp = NULL;
    fp = fopen( filename, "r");
    if (fp != NULL) {
        int returnValue;
        while (numberOfLeaders < 5 && (returnValue = fscanf(fp, "%s %d", leaders[numberOfLeaders].name, &leaders[numberOfLeaders].guesses)== 2)) 
        {
            numberOfLeaders ++;
        }
        fclose(fp);
    }

    do { 
        int numberOfGuesses = 0;

        printf("Welcome! Press 'q' to quit or any other key to continue: \n"); 
        scanf(" %c", &input);

        //if the user enters "q", exit the program
        if(input == 'q') {
            printf("Bye Bye!\n");
            saveCurrentLeader(leaders, numberOfLeaders);//save file before exit the program
            return 0;
        }

        printf("Please enter your name to start: \n");
        scanf(" %s", leaders[numberOfLeaders].name);

        //game logic 
        numberOfGuesses = playGuessingGame();

        //update the current leader into struct and display them
        leaders[numberOfLeaders].guesses = numberOfGuesses;
        displayCurrentLeader(leaders, numberOfLeaders);
        numberOfLeaders++;
        
    } while (input != 'q');
    printf("Bye Bye!");
    return 0; 
}