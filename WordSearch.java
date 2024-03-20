// Name: Noah Tavis

// Date: 2/6/24

// Class: CS145 Computer Science II

// Project: Word Search Generator

// Purpose: To randomly generate a word search with words given by the user

package WordSearch;

import java.security.SecureRandom;

public class WordSearch {
    //
    private char[][] wordSearch;
    private char[][] solution;
    private String[] omitted;
    private String[] toFind;
    private static final SecureRandom randomNumbers = new SecureRandom();

    //constructor for use with no strings
    public WordSearch() {
    }

    //constructor for use with strings
    public WordSearch(String[] words) {
        toFind = words;
        String longWord = "";
        int length;
        //finds the longest word in the array of words
        //stores longest word as longWord
        for(int i = 0; i < words.length; i++) {
            if(words[i].length() > longWord.length()) {
                longWord = words[i];
            }
        }
        //if the number of words exceeds the longest words
        //length, then set length to # of words + 3
        //else set length to longest words length + 3
        if (words.length > longWord.length()) {
            length = words.length + 3;
        }
        else {
            length = longWord.length() + 3;
        }
        //initializes each array to the size of length
        //this produces a square for the words to be placed into
        //that is 3 characters longer than the longest word or the 
        //number of words to place
        wordSearch = new char[length][length];
        solution = new char[length][length];
        //initializes omitted to the number of words to place
        //in the very unlikely event that each word cannot be placed
        //within the square alotted for the word search
        //oCount keeps track of the array value of each word that cannot be placed
        omitted = new String[words.length];
        int oCount = 0;

        //loop runs as long as there are words to be placed
        for (int i = 0; i < words.length; i++) {
            //int direction is how I specified how I wanted to place
            //each word. Each word gets a random value for direction
            //0 for horizontal placement, 1 for vertical and 2 for diagonal
            int direction = randomNumbers.nextInt(3);
            int check = 0;
            //count keeps track of the number of attempts to place a word
            //with a unique direction
            int count = 0;

            //this loop only runs once if 'place' successfully places the word
            //in question. If the word cannot be
            //placed with its specified direction in 100 random attempts, 
            //place will return 1 and the loop gets reset with a new direction 
            //to attempt
            one:
            for(int j = 0; j < 1; j++) {
                check = place(words[i], length, direction);
                    if (check == 1) {
                        j--;
                        count++;
                        if (direction == 2) {
                            direction = 0;
                        }
                        else {
                            direction++;
                        }
                    }
                    //after all 3 directions have been attempted, if the word
                    //still cannot be placed add it to the omitted array and break
                    //out of the loop
                    if (count == 3) {
                        omitted[oCount] = words[i];
                        oCount++;
                        break one;
                    }
            }
        }

        //after all words have been placed or omitted, fill the rest of each array
        //with random letters or "#"s
        for(int i = 0; i < length; i++) {
            for(int j = 0; j < length; j++) {
                if (wordSearch[i][j] == '\0') {
                    wordSearch[i][j] = (char)randomNumbers.nextInt(97, 123);
                    solution[i][j] = '-';
                }
            }
        }
    }

    //attempts to place a word into wordsearch with a specified direction
    private int place(String word, int length, int direction) {
        //orientation dictates whether the word will be placed backwards (0)
        //or forwards (1). 
        int orientation = randomNumbers.nextInt(2);
        int diagonal = 0;
        int attempts = 0;
        int column = 0;
        int row = 0;
        boolean check = false;
        char[] array = word.toCharArray();

        //checks if free space is available in 100 attempts
        while (attempts < 100) {
            int count = 0;
            //if diagonal generates as 0 and direction dictates diagonal placement,
            //attempts searches for space in a '\' orientation,
            //if it generates as 1 attempts will search oreintated like '/'
            //each attempt will re-orient diagonal placement
            diagonal = randomNumbers.nextInt(2);

            /*'row' and 'column' serve as our starting points for each word
             *in the wordSearch array. Based on the specified direction for 
             *the words placement, values for row and column will be
             *randomly generated within a bound area. As we check for empty
             *spaces, we will start from wordSearch[row][column] and increment
             *row and/or column values to check if each potential place in the 
             *wordSearch array is empty or not.*/

             //this if/else block gets random starting values based on direction
            if (direction == 0) {
                row = randomNumbers.nextInt(length);
                column = randomNumbers.nextInt(length - word.length() + 1);
            }
            else if (direction == 1) {
                row = randomNumbers.nextInt(length - word.length() + 1);
                column = randomNumbers.nextInt(length);
            }
            else if (direction == 2) {
                if (diagonal == 0) {
                    row = randomNumbers.nextInt(length - word.length() + 1);
                    column = randomNumbers.nextInt(length - word.length() + 1);
                }
                else {
                    row = randomNumbers.nextInt(length - word.length() + 1);
                    column = randomNumbers.nextInt(word.length() - 1, length);
                }
            }

            //this for loop checks if each place in the array is empty or not.
            //if it is empty, increment counter, then increment row and/or 
            //column based on direction and repeat
            for(int i = 0; i < word.length(); i++) {
                if (wordSearch[row][column] == '\0') {
                    count++;
                }

                if (direction == 0) {
                    column++;
                }
                else if (direction == 1) {
                    row++;
                }
                else {
                    if (diagonal == 0) {
                        row++;
                        column++;
                    }
                    else {
                        row++;
                        column--;
                    }
                }
            }

            //if the count ends up equal to the word's length, we know that
            //placement will be valid. Set check = true and break out of attempt
            //loop
            if (count == word.length()) {
                check = true;
                attempts = 100;
            }
            //increment attempt in case placement is invalid and re-randomize
            //our starting place
            attempts++;
        }//end attempt while loop

        //if placement is valid, reset column and row values to what they were
        //when they were generated to get back to our starting point and place
        //the word
        if (check) {
            if (direction == 0) {
                column -= word.length();
            }
            else if (direction == 1) {
                row -= word.length();
            }
            else {
                if (diagonal == 0) {
                    row -= word.length();
                    column -= word.length();
                }
                else {
                    row -= word.length();
                    column += word.length();
                }
            }
            
            //if orientation is 0, we start from the last letter in the word and
            //count down to place it backwards. Each time a letter is placed,
            //increment row and column values accordingly.
            if (orientation == 0) {
                for(int i = word.length() - 1; i > -1; i--) {
                    wordSearch[row][column] = array[i];
                    solution[row][column] = array[i];
                    if (direction == 0) {
                        column++;
                    }
                    else if (direction == 1) {
                        row++;
                    }
                    else {
                        if (diagonal == 0) {
                            row++;
                            column++;
                        }
                        else {
                            row++;
                            column--;
                        }
                    }
                }
            }
            //else, if orientation is 1, we start from the first letter in the
            //word and count up to place it forwards.
            else {
                for(int i = 0; i < word.length(); i++) {
                    wordSearch[row][column] = array[i];
                    solution[row][column] = array[i];
                    if (direction == 0) {
                        column++;
                    }
                    else if (direction == 1) {
                        row++;
                    }
                    else {
                        if (diagonal == 0) {
                            row++;
                            column++;
                        }
                        else {
                            row++;
                            column--;
                        }
                    }
                }
            }
            //if placement was successfull, return 0
            return 0;
        }
        //if placement was unsuccessful, return 1
        return 1;
    }//end place

    //if wordSearch hasn't been initialized, this method will return true
    //this is in case the user enters 'p' or 's' without generating a word
    //search first
    public boolean constructed() {
        return wordSearch == null;
    }

    public String toString(int choice) { //returns string representation of wordSearch
        //initializes string
        String sWordSearch = "";

        //add a line of '=' on top of the word search
        for(int i = 0; i < (wordSearch.length * 5) - 4; i++) {
            sWordSearch += "=";
        }
        sWordSearch += "\n";

        //both loops run as long as the length of one row of letters. if the user
        //chooses to print the word search, the string returned will be filled with
        //random letters as well as chosen words. If the user chooses to print the
        //solution, the string returned will be filled with '#' and chosen words
        for(int i = 0; i < wordSearch.length; i++) {
            for(int j = 0; j < wordSearch.length; j++) {
                if (choice == 1) {
                    sWordSearch += wordSearch[i][j] + "    ";
                }
                else if (choice == 2) {
                    sWordSearch += solution[i][j] + "    ";
                }
            }
            if (i != wordSearch.length - 1) {
                sWordSearch += "\n\n";
            }
        }

        //add a line of '=' to the bottom of the word search
        sWordSearch += "\n";
        for(int i = 0; i < (wordSearch.length * 5) - 4; i++) {
            sWordSearch += "=";
        }
        sWordSearch += "\n";
        //display the words the user chose at the bottom of the word search
        if(choice == 1) {
            sWordSearch += "Words to find:\n";
            for(int i = 0; i < toFind.length; i++) {
                sWordSearch += toFind[i] + "\n";
            }
        }
        //in case there are words that cannot be places, display those as well
        for(int i = 0; i < omitted.length; i++) {
            if(i == 0 && omitted[i] != null) {
                sWordSearch += "Words omitted:\n";
            }
            if(omitted[i] != null) {
                sWordSearch += omitted[i] + "\n";
            }
        }
        sWordSearch += "\n";
        return sWordSearch;
    }//end toString
}//end class
