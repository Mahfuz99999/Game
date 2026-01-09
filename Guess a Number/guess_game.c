#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Function prototypes
void printWelcome();
void printMenu();
int getDifficulty();
int generateNumber(int min, int max);
int playGame(int min, int max, int attempts);
void printScore(int score, int gamesPlayed);
void printHighLow(int guess, int target);
void printGameOver(int target);
void printVictory(int attemptsUsed, int maxAttempts);

int main() {
    int choice;
    int score = 0;
    int gamesPlayed = 0;
    int min, max, attempts;
    
    // Seed random number generator
    srand(time(NULL));
    
    printWelcome();
    
    do {
        printMenu();
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);
        
        // Clear input buffer
        while(getchar() != '\n');
        
        switch(choice) {
            case 1: // Easy
                min = 1;
                max = 50;
                attempts = 10;
                score += playGame(min, max, attempts);
                gamesPlayed++;
                break;
                
            case 2: // Medium
                min = 1;
                max = 100;
                attempts = 7;
                score += playGame(min, max, attempts);
                gamesPlayed++;
                break;
                
            case 3: // Hard
                min = 1;
                max = 200;
                attempts = 5;
                score += playGame(min, max, attempts);
                gamesPlayed++;
                break;
                
            case 4: // Custom
                printf("\n=== CUSTOM DIFFICULTY ===\n");
                printf("Enter minimum number: ");
                scanf("%d", &min);
                printf("Enter maximum number: ");
                scanf("%d", &max);
                printf("Enter number of attempts: ");
                scanf("%d", &attempts);
                
                // Clear input buffer
                while(getchar() != '\n');
                
                if (min >= max) {
                    printf("Invalid range! Minimum must be less than maximum.\n");
                    printf("Using default range 1-100 instead.\n");
                    min = 1;
                    max = 100;
                }
                
                if (attempts <= 0) {
                    printf("Invalid attempts! Using default of 7.\n");
                    attempts = 7;
                }
                
                score += playGame(min, max, attempts);
                gamesPlayed++;
                break;
                
            case 5: // Show score
                printScore(score, gamesPlayed);
                break;
                
            case 6: // Exit
                printf("\nThank you for playing!\n");
                printScore(score, gamesPlayed);
                break;
                
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
        
        printf("\n");
        
    } while (choice != 6);
    
    return 0;
}

void printWelcome() {
    printf("====================================\n");
    printf("       GUESS THE NUMBER GAME\n");
    printf("====================================\n");
    printf("Welcome! I'm thinking of a number.\n");
    printf("Can you guess what it is?\n\n");
}

void printMenu() {
    printf("=== MAIN MENU ===\n");
    printf("1. Easy (1-50, 10 attempts)\n");
    printf("2. Medium (1-100, 7 attempts)\n");
    printf("3. Hard (1-200, 5 attempts)\n");
    printf("4. Custom difficulty\n");
    printf("5. Show current score\n");
    printf("6. Exit\n");
}

int generateNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

int playGame(int min, int max, int attempts) {
    int target = generateNumber(min, max);
    int guess;
    int attemptsUsed = 0;
    int score = 0;
    
    printf("\n=== NEW GAME ===\n");
    printf("I've picked a number between %d and %d.\n", min, max);
    printf("You have %d attempts to guess it.\n", attempts);
    printf("Let's begin!\n\n");
    
    for (attemptsUsed = 1; attemptsUsed <= attempts; attemptsUsed++) {
        printf("Attempt %d/%d: Enter your guess: ", attemptsUsed, attempts);
        
        // Check if input is valid
        if (scanf("%d", &guess) != 1) {
            printf("Invalid input! Please enter a number.\n");
            
            // Clear input buffer
            while(getchar() != '\n');
            attemptsUsed--;  // Don't count invalid attempt
            continue;
        }
        
        // Clear input buffer
        while(getchar() != '\n');
        
        // Check if guess is in range
        if (guess < min || guess > max) {
            printf("Your guess is out of range (%d-%d). Try again.\n", min, max);
            attemptsUsed--;  // Don't count out-of-range attempt
            continue;
        }
        
        // Check if guess is correct
        if (guess == target) {
            printVictory(attemptsUsed, attempts);
            
            // Calculate score: more points for fewer attempts
            score = (attempts - attemptsUsed + 1) * 10;
            printf("You earned %d points!\n", score);
            return score;
        }
        
        // Give hint
        printHighLow(guess, target);
    }
    
    // Player ran out of attempts
    printGameOver(target);
    return 0;  // No points for losing
}

void printHighLow(int guess, int target) {
    int difference = abs(guess - target);
    
    if (guess < target) {
        printf("Too low! ");
    } else {
        printf("Too high! ");
    }
    
    // Give additional hints based on how close the guess is
    if (difference > 50) {
        printf("You're very far away.\n");
    } else if (difference > 25) {
        printf("You're quite far away.\n");
    } else if (difference > 10) {
        printf("You're getting warmer.\n");
    } else if (difference > 5) {
        printf("You're getting hot!\n");
    } else {
        printf("You're very close!\n");
    }
}

void printVictory(int attemptsUsed, int maxAttempts) {
    printf("\n");
    printf("************************************\n");
    printf("   CONGRATULATIONS! YOU WIN!\n");
    printf("   You guessed it in %d attempts!\n", attemptsUsed);
    
    // Different messages based on performance
    if (attemptsUsed == 1) {
        printf("   Incredible! First try!\n");
    } else if (attemptsUsed <= maxAttempts / 3) {
        printf("   Outstanding performance!\n");
    } else if (attemptsUsed <= maxAttempts / 2) {
        printf("   Great job!\n");
    } else {
        printf("   Good work!\n");
    }
    
    printf("************************************\n");
}

void printGameOver(int target) {
    printf("\n");
    printf("####################################\n");
    printf("          GAME OVER\n");
    printf("   The number was: %d\n", target);
    printf("   Better luck next time!\n");
    printf("####################################\n");
}

void printScore(int score, int gamesPlayed) {
    printf("\n=== YOUR STATISTICS ===\n");
    printf("Total games played: %d\n", gamesPlayed);
    printf("Total score: %d\n", score);
    
    if (gamesPlayed > 0) {
        printf("Average score per game: %.1f\n", (float)score / gamesPlayed);
    }
    
    printf("=======================\n");
}