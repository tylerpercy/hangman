//
//  hangman.cpp
//  
//
//  Created by Tyler Percy on 11/5/20.
//

#include <stdio.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <cmath>
#include <algorithm>

using namespace std;

/* FUNCTION DECLARATIONS */
vector<string> getWordList(ifstream&);
bool guessWord(string, string);
bool guessLetter(char, string&, string);

int main(int argc, char* argv[]) {
    
    // seeding using time to get a different word each time you play.
    srand(time(NULL));

    /* VARIABLE DECLARATIONS */
    const int totalGuesses = 10;
    int guessCount = totalGuesses;
    int index;
    bool guessed;
    vector<string> prevGuesses;
    string filename;
    string input;
    string guessState;
    string wordToGuess;
    string bodyparts[10] = {"head", "torso", "left arm", "right arm", "left leg",
        "right leg", "left eye", "right eye", "nose", "mouth"};
    
    // getting file name from the user
    cout << "Please enter your filename: ";
    cin >> filename;
    ifstream infile(filename);
    
    // exit the program if the filename is invalid
    if (!infile.good()) {
        cerr << "File not found." << endl;
        exit(1);
    }
    
    vector<string> words = getWordList(infile); // extract words from file
    index = rand() % words.size(); // get index to use to get our word
    wordToGuess = words[index]; // gets the word from words vector
    guessState = wordToGuess;
    
    for (int i = 0; i < wordToGuess.length(); i++) {
        guessState[i] = '_';
    }
    
    /* MAIN LOOP */
    while (guessCount > 0 and guessState != wordToGuess) {
        guessed = false;
        cout << "You have " << guessCount << " guesses remaining." << endl;
        cout << "Current state of word: " << guessState << endl;
        cout << "Please guess a letter or the word: ";
        cin >> input; // user guesses word or letter
        cout << endl;
       
        // check to see if user has already guessed this word or letter
        if (count(prevGuesses.begin(), prevGuesses.end(), input)) {
            cout << "You already made this guess!" << endl << endl;
            continue; // begin new loop iteration
        }
        else {
            // add current guess to list of guesses so we know what
            // the user has guessed so far
            prevGuesses.push_back(input);
        }
       
        // if the user guesses a letter
        if (input.length() == 1) {
            char letterInput = input[0]; // convert guess to a letter
            // check if letter is in word user is trying to guess
            guessed = guessLetter(letterInput, guessState, wordToGuess);
            if (guessed) {
                cout << letterInput << " was found!" << endl;
            }
            else {
                cout << "Your guess was incorrect." << endl;
                cout << "The following body part has been drawn: " << bodyparts[abs(guessCount-10)] << endl;
            }
        }
        // if the user guesses a word
        else if (input.length() > 1) {
            // check if user guessed the correct word
            guessed = guessWord(input, wordToGuess);
            // exit loop if word is correct
            if (guessed) {
                break;
            }
            else {
                cout << "Your guess was incorrect." << endl;
                cout << "The following body part has been drawn: " << bodyparts[abs(guessCount-10)] << endl;
            }
        }
        else
            cout << "Invalid Guess." << endl;
        
        guessCount--; // decrement guess counter per iteration of the loop
        cout << endl;
       
    }
    
    // outcome of the game
    if (guessed) {
        cout << "You Win!" << endl;
    }
    else {
        cout << "You Lose." << endl;
        cout << "The word was: " << wordToGuess << endl;
    }

    return 0;
}

/*
 * Function: getWordList
 *
 * Parameters:
 *   ifs: ifstream object that is the file we are opening to get a list of words.
 *
 * Postcondition:
 *   A list of words will be returned in a string vector
*/
vector<string> getWordList(ifstream& ifs) {
    
    string word;
    vector<string> list;
    while (ifs >> word) {
        list.push_back(word);
    }
    
    return list;
}

/*
 * Function: guessWord
 *
 * Parameters:
 *   guess: string that is the user's inputted guess.
 *    word: the word that the user is attempting to guess.
 *
 * Postcondition:
 *   true or false will be returned depending on whether the user's guess
 *   is identical to the solution.
 */
bool guessWord(string guess, string word) {
    bool result = (guess == word) ? true : false;
    return result;
}

/*
 * Function: guessWord
 *
 * Parameters:
 *        guess: string that is the user's inputted guess.
 *   guessState: a pointer referring to the progress the user has made
                 in guessing the correct word.
 *         word: the word that the user is attempting to guess.
 *
 * Postcondition:
 *   true or false will be returned depending on whether the letter the
 *   user guessed is present in the solution.
 */
bool guessLetter(char guess, string &guessState, string word) {
    bool result = false;
    for (int i = 0; i < guessState.length(); i++) {
        if (guess == word[i]) {
            guessState[i] = guess; // show letter in solution instead of '_'
            result = true; // flag that we found a letter in solution
        }
    }
    // modifies the value but not the memory location
                        // so the changes persist once leaving the function.
    
    return result;
}


