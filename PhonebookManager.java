// Name: Noah Tavis

// Date: 02/14/24

// Class: CS145 Computer Science II

// Project: Phone Book

// Purpose: To use linked list to construct a phone book using user input

package Phonebook;

public class PhonebookManager { //methods for phonebook linked list
    ListNode head;

    //constructor with no parameters
    public PhonebookManager() {
        head = null;
    }
    
    //add a node to the end of the list
    public void add(String firstName, String lastName, 
                    String address, String city, String number) {
        //if there is no first node, point to the new node
        if (head == null) {
            head = new ListNode(firstName, lastName, address, city, number);
        }
        //otherwise add node to the end of the list
        else {
            ListNode current = head;
            while (current.next != null) {
                current = current.next;
            }
            current.next = new ListNode(firstName, lastName, address, city, number);
        }
    }

    //add node to a specific index in the list
    public void add(String firstName, String lastName, 
                    String address, String city, String number, int index) {
        //if adding to index 0, add node to the start of the list
        if (index == 0) {
            head = new ListNode(firstName, lastName, address, city, number, head);
        }
        //otherwise count to index and add there
        else {
            ListNode current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current.next;
            }
            current.next = new ListNode(firstName, lastName, address,
                                        city, number, current.next);
        }
    }

    //returns the number of nodes in the list
    public int getNodeNumber() {
        int counter = 0;
        ListNode current = head;
        while(current != null) {
            current = current.next;
            counter++;
        }
        return counter--;
    }

    //prints each node in the list
    public void print() {
        ListNode current = head;
        int counter = 1;
        while(current != null) {
            System.out.println("Contact: " + counter);
            System.out.println("First name: " + current.firstName);
            System.out.println("Last name: " + current.lastName);
            System.out.println("Address: " + current.address);
            System.out.println("City: " + current.city);
            System.out.println("Phone number: " + current.number);
            System.out.println();
            current = current.next;
            counter++;
        }
    }

    //prints just one node in the list, specified with index
    public void print(int index) {
        ListNode current = head;
        //counts to index to get to specific node
        for (int i = 0; i < index; i++) {
            current = current.next;
        }
        System.out.println("Contact: " + (index + 1));
        System.out.println("First name: " + current.firstName);
        System.out.println("Last name: " + current.lastName);
        System.out.println("Address: " + current.address);
        System.out.println("City: " + current.city);
        System.out.println("Phone number: " + current.number);
        System.out.println();
    }

    //searches by name (by = 0), address (by = 1) or number (by = 2)
    public int[] search(int by, String check) {
        //array to return multiple nodes
        //initialize to the number of nodes in case every node contains
        //search parameters
        int[] index = new int[getNodeNumber()];
        //initializes with -1 in each array slot instead of 0
        for(int i = 0; i < index.length; i++) {
            index[i] = -1;
        }
        ListNode current = head;
        //keeps track of spot in the array
        int arrayCounter = 0;
        //keeps track of specific index being stored
        int indexCounter = 0;
        boolean bool = false;
        while(current != null) {
            bool = false;
            //if current node matches the search parameters, set bool to true
            if (by == 0) {
                if (check.equals(current.firstName + current.lastName)) {
                    bool = true;
                }
            }
            else if (by == 1) {
                if (check.equals(current.address)) {
                    bool = true;
                }
            }
            else if (by == 2) {
                if (check.equals(current.number)) {
                    bool = true;
                }
            }
            //if parameters are met, store the index in the index array
            //increment arrayCounter for next possible met search
            if (bool) {
                index[arrayCounter] = indexCounter;
                arrayCounter++;
            }
            //increment indexCounter each time loop is ran to keep track of node index
            indexCounter++;
            current = current.next;
        }
        //return index array
        return index;
    }//end search

    //deletes a specific node, specified with int index
    public void delete(int index) {
        if(index == 0) {
            head = head.next;
            return;
        }
        ListNode current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current.next;
        }
        current.next = current.next.next;
    }
}
