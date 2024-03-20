// Name: Noah Tavis

// Date: 01/19/24

// Class: CS145 Computer Science II

// Project: Lab 2 Card Shuffling and Dealing

// Purpose: Use a deck of cards to populate a 5 card hand and check if that hand has a pair

// Exersise 7.16a - 7.16e

package Lab2;

public class PokerHand {
    private Card[] hand = new Card[5];

    //constructor in case a deck is used to randomize card order
    public PokerHand(DeckOfCards myDeck) {
        for (int i = 0; i < 5; i++) {
            hand[i] = myDeck.dealCard();
        }
    }

    //contructor in case 5 cards are manually inputted
    public PokerHand(Card one, Card two, Card three, Card four, Card five) {
        hand[0] = one;
        hand[1] = two;
        hand[2] = three;
        hand[3] = four;
        hand[4] = five;
    }

    //checks if a pair is present in hand
    public boolean containsPair() {
        boolean pair = false;

        //both for loops count to 5 and compare each card
        //one by one. If any card's face matches that of 
        //another card, return true
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (i != j && hand[i].getFace().equals(hand[j].getFace())) {
                    pair = true;
                }
            }
        }

        return pair;
    } //end containsPair

    //checks if two different pairs are present
    public boolean containsTwoPairs() {
        //initialize variables
        boolean onePair = false;
        boolean twoPair = false;
        String faceOne = "nothing";

        //both loops count to 5 and compare each card's face
        //to every card in the deck. If the faces of two cards
        //match, store the face in "faceOne" and set "onePair"
        //to true
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (i != j && hand[i].getFace().equals(hand[j].getFace())) {
                    onePair = true;
                    faceOne = hand[i].getFace();
                }
            }
        }

        //both loops again compare each card, but "twoPair" gets
        //set to true only if "onePair" was set to true and the
        //new matching face does not equal the face from before
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (i != j 
                    && onePair
                    && hand[i].getFace().equals(hand[j].getFace())
                    && !hand[i].getFace().equals(faceOne)) {
                    twoPair = true;
                }
            }
        }

        return twoPair;
    } //end containsTwoPairs


    public boolean containsThreeOfAKind() {
        boolean three = false;

        //three loops this time, all counting to 5, and "three" 
        //gets set to true only if three different cards all
        //have equal faces
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                for(int k = 0; k < 5; k++) {
                    if (i != j 
                        && j != k 
                        && k != i 
                        && hand[i].getFace().equals(hand[j].getFace())
                        && hand[i].getFace().equals(hand[k].getFace())) {
                        three = true;
                    }
                }
            }
        }

        return three;
    }//end containsThreeOfAKind

    public boolean containsFlush() {
        boolean flush = true;

        //flush gets set to false if any card does not have the same
        //suit as another card
        for (int i = 0; i < 5; i++) {
            if (!hand[i].getSuit().equals(hand[0].getSuit())) {
                flush = false;
            }
        }

        return flush;
    } //end of containsFlush

    //converts your hand to a string in brackets
    public String toString() {
        String sHand = "[";
        for (int i = 0; i < 5; i++) {
            sHand = sHand + hand[i];
            if (i != 4) {
                sHand = sHand + ", ";
            }
        }
        sHand = sHand + "]";
        return sHand;
    }//end toString
}//end class
