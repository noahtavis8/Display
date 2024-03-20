// Name: Noah Tavis

// Date: 01/19/24

// Class: CS145 Computer Science II

// Project: Lab 2 Card Shuffling and Dealing

// Purpose: Use a deck of cards to populate a 5 card hand and check if that hand has a pair

package Lab2;

public class Card {
    private final String face; //face of card ("Ace", "Deuce", ...)
    private final String suit; //suit of card ("Hearts", "Diamonds", ...)

    //two-argument constructor initializes card's face and suit
    public Card(String cardFace, String cardSuit) {
        this.face = cardFace;
        this.suit = cardSuit;
    }

    public String getFace() {
        return this.face;
    }

    public String getSuit() {
        return this.suit;
    }

    //return String representation of Card
    public String toString() {
        return face + " of " + suit;
    }
} //end class
