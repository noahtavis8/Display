// Name: Noah Tavis

// Date: 02/14/24

// Class: CS145 Computer Science II

// Project: Phone Book

// Purpose: To use linked list to construct a phone book using user input


package Phonebook;

public class ListNode { //class for the nodes of the linked list
    //variables to keep track of
    String firstName;
    String lastName;
    String address; 
    String city;
    String number;
    ListNode next;

    //constructor without next pointer
    public ListNode(String firstName, String lastName, String address, 
                    String city, String number) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.address = address;
        this.city = city;
        this.number = number;
        this.next = null;
    }

    //constructer with next pointer
    public ListNode(String firstName, String lastName, String address, 
                    String city, String number, ListNode next) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.address = address;
        this.city = city;
        this.number = number;
        this.next = next;
    }
}
