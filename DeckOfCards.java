// Name: Noah Tavis

// Date: 01/19/24

// Class: CS145 Computer Science II

// Project: Lab 2 Card Shuffling and Dealing

// Purpose: Use a deck of cards to populate a 5 card hand and check if that hand has a pair

package Lab2;

import java.security.SecureRandom;

public class DeckOfCards {
    private static final SecureRandom randomNumbers = new SecureRandom();
    private static final int NUMBER_OF_CARDS = 52;

    private Card[] deck = new Card[NUMBER_OF_CARDS];
    private int currentCard = 0;

    //constructor fills deck of cards
    public DeckOfCards() {
        String[] faces = {"Ace", "Deuce", "Three", "Four", "Five", "Six",
            "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
        String[] suits = {"Hearts", "Diamonds", "Clubs", "Spades",};

        //populate deck with card objects
        for (int count = 0; count < deck.length; count++) {
            deck[count] =
                new Card(faces[count % 13], suits[count / 13]);
        }
    } //end of DeckOfCards

    //shuffle deck of cards with one-pass algorithm
    public void shuffle() {
        //next call to dealCard should start at deck[0] again
        currentCard = 0;

        //for each Card, pick another random card (0-51) and swap them
        for (int first = 0; first < deck.length; first++) {
            int second = randomNumbers.nextInt(NUMBER_OF_CARDS);

            Card temp = deck[first];
            deck[first] = deck[second];
            deck[second] = temp;
        }
    } //end of Shuffle

    //deal one card
    public Card dealCard() {
        //determine whether cards remain to be delt
        if (currentCard < deck.length) {
            return deck[currentCard++]; //return current card in array
        }
        else {
            return null; //return null if all cards are delt
        }
    } //end of dealCard

    //display entire deck
    public String toString() {
        String sDeck = ""; //initialize string

        //loop 52 times for 52 cards
        for (int i = 1; i < 53; i++) {
            //each iteration add the string of the card to the sDeck string
            sDeck = sDeck + deck[i - 1];

            //unless the current card is the last one, include a comma and a space
            if (i != 52) {
                sDeck = sDeck + ", ";
            }
            
            //every fourth card include a newline character
            if (i % 4 == 0) {
                sDeck = sDeck + "\n";
            }
        } //end of for loop
        return sDeck;
    } //end of toString
} //end class
