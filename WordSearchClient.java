// Name: Noah Tavis

// Date: 2/6/24

// Class: CS145 Computer Science II

// Project: Word Search Generator

// Purpose: To randomly generate a word search with words given by the user

package WordSearch;

import java.util.Scanner;

public class WordSearchClient {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        boolean menu = true;
        WordSearch wordSearch = new WordSearch();
        printIntro();

        while(menu) {
            System.out.printf("Please select an option:%n");
            System.out.printf("Generate a new word search (g)%n");
            System.out.printf("Print out your word search (p)%n");
            System.out.printf("Show the solution to your word search (s)%n");
            System.out.printf("Quit the program (q)%n");
            String choice = input.next();

            switch(choice) {
                case "g":
                    wordSearch = generate(input, wordSearch);
                    break;
                case "p":
                    print(wordSearch);
                    break;
                case "s":
                    showSolution(wordSearch);
                    break;
                case "q":
                    menu = false;
                    break;
                default:
                    System.out.printf("Please enter a valid option.%n%n");

            }
        }//end while loop

        input.close();
    }//end main

    private static void printIntro() { //gives introduction
        System.out.printf("Welcome to my word search generator!%n");
        System.out.printf("This program will allow you to generate");
        System.out.printf(" your own word search puzzle%n");
    }

    //generates word search
    private static WordSearch generate(Scanner input, WordSearch wordSearch) {
        int words = 0;
        boolean bool = true;
        //asks how many words user would like to find and catches inputs that arent integers
        while(bool) {
            try {
                System.out.printf("How many words would you like to find? ");
                words = input.nextInt();
                bool = false;
            }
            catch (Exception e) {
                System.out.printf("Please enter an integer for the number of words%n");
            }
        }
        //makes array with length of the number of words given by user
        String[] wordsArray = new String[words];
        //prompts user for words and fills array with given words
        for(int i = 0; i < words; i++) {
            System.out.printf("Word %d: ", i + 1);
            wordsArray[i] = input.next().toLowerCase();
        }
        System.out.printf("%n");
        //sends array to WordSearch for generation
        wordSearch = new WordSearch(wordsArray);
        return wordSearch;
    } //end generate

    private static void print(WordSearch wordSearch) { //prints word search
        //checks if word search is generated, if not print an error message and return
        if (wordSearch.constructed()) {
            System.out.printf("%nPlease begin by generating a word search%n%n");
            return;
        }
        //if word search is generated, print it
        System.out.printf("%n%s", wordSearch.toString(1));
    }

    private static void showSolution(WordSearch wordSearch) { //prints solution
        //checks if word search is generated, if not print an error message and return
        if (wordSearch.constructed()) {
            System.out.printf("%nPlease begin by generating a word search%n%n");
            return;
        }
        //if word search is generated, print solution
        System.out.printf("%n%s", wordSearch.toString(2));
    }
}//end class
