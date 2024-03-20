// Name: Noah Tavis

// Date: 01/19/24

// Class: CS145 Computer Science II

// Project: Lab 2 Card Shuffling and Dealing

// Purpose: Use a deck of cards to populate a 5 card hand and check if that hand has a pair

package Lab2;

public class MainLab2Test {
    public static void main(String[] args) {
        DeckOfCards myDeck = new DeckOfCards();
        myDeck.shuffle();

        PokerHand myPokerHand = new PokerHand(myDeck);
        
        // PokerHand myPokerHand = new PokerHand(
        //     new Card("Four", "Spades"),
        //     new Card("Queen", "Clubs"),
        //     new Card("Four", "Hearts"),
        //     new Card("Queen", "Diamonds"),
        //     new Card("Four", "Diamonds")
        // );

        System.out.printf("My poker hand looks like this: %n%s%n%n", myPokerHand);
        System.out.println("Contains a pair? \t\t" + myPokerHand.containsPair());
        System.out.println("Contains two pairs? \t\t" + myPokerHand.containsTwoPairs());
        System.out.println("Contains three of a kind? \t" + myPokerHand.containsThreeOfAKind());
        System.out.println("Contains a flush? \t\t" + myPokerHand.containsFlush());

    } //end main
} //end class
