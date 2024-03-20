// Name: Noah Tavis

// Date: 02/14/24

// Class: CS145 Computer Science II

// Project: Phone Book

// Purpose: To use linked list to construct a phone book using user input

package Phonebook;

import java.util.Scanner;

public class TestClass {
    public static void main(String[] args) { //prints menu
        //initializes scanner and phonebook
        boolean menu = true;
        Scanner input = new Scanner(System.in);
        PhonebookManager book = new PhonebookManager();

        while (menu) {
            System.out.println("Please select an option:");
            System.out.println("(1) Add a Contact");
            System.out.println("(2) Delete a Contact");
            System.out.println("(3) View Contacts");
            System.out.println("(4) Search by Name");
            System.out.println("(5) Search by Address");
            System.out.println("(6) Search by Phone Number");
            System.out.println("(7) Edit a Contact");
            System.out.println("(0) Quit the Program");
            String choice = input.nextLine().toLowerCase();

            //most println and input.nextLine statements are for spacing
            //theres not a specific order, I just put them in places I thought
            //would result in the cleanest looking terminal using trial and error
            switch (choice) {
                case "add":
                case "add a contact":
                case "add contact":
                case "1":
                    System.out.println();
                    add(input, book, false, 0);
                    System.out.println();
                    break;
                case "del":
                case "delete":
                case "delete a contact":
                case "delete contact":
                case "2":
                    System.out.println();
                    delete(input, book);
                    break;
                case "view":
                case "view contacts":
                case "3":
                    if (book.head == null) {
                        System.out.printf("Please add a contact first%n%n");
                    }
                    else {
                        System.out.println();
                        book.print();
                    }
                    break;
                case "name":
                case "search name":
                case "search by name":
                case "4":
                    //by = 0, search by name
                    System.out.println();
                    search(input, book, 0);
                    break;
                case "address":
                case "search address":
                case "search by address":
                case "5":
                    //by = 1, search by address
                    System.out.println();
                    search(input, book, 1);
                    break;
                case "number":
                case "search number":
                case "search phone number":
                case "search by phone number":
                case "6":
                    //by = 2, search by number
                    System.out.println();
                    search(input, book, 2);
                    break;
                case "edit":
                case "edit contact":
                case "edit a contact":
                case "7":
                    System.out.println();
                    edit(input, book);
                    break;
                case "quit":
                case "q":
                case "0":
                    menu = false;
                    break;
                default:
                    //catches invalid input
                    System.out.println();
                    System.out.println("Please select a valid option\n");
                    break;
            }//end switch
        }//end while loop
        input.close();
    }//end main

    //adds information as a node in the list
    //boolean edit keeps track of whether add was called in the edit
    //method or in the main method. True while in edit method, false otherwise
    private static void add(Scanner input, PhonebookManager book, boolean edit, int editIndex) {
        boolean bool = true;
        int index = -1;

        if (edit) {
            index = editIndex;
        }
        
        if (!edit) {
            //allows user to place new information at the beginning, end or
            //in the middle of the linked list
            while (bool) {
                System.out.printf("What contact number would you like to assign new contact?%n");
                System.out.printf("Enter (f) For first contact%n");
                System.out.printf("Enter (l) For last contact%n");
                String choice = input.next().toLowerCase();
                if (choice.equals("f")) {
                    index = 0;
                    bool = false;
                }
                else if (choice.equals("l")){
                    bool = false;
                }
                else {
                    //tries to parse an int from the string gathered from the user
                    //and sets index to that number
                    try {
                        index = Integer.parseInt(choice) - 1;
                        //if the user didnt input a number that falls between the current
                        //number of nodes, re-prompt them
                        if (index < 0) {
                            System.out.printf("Please enter a positive ");
                            System.out.printf("integer for contact number%n");
                        }
                        else if (index > book.getNodeNumber()) {
                            System.out.printf("There are less than %d ", index);
                            System.out.printf("contacts - enter an integer that ");
                            System.out.printf("falls between the number of existing contacts.%n");
                        }
                        else {
                            bool = false;
                        }
                    }
                    //catches inputs that arent numbers
                    catch (Exception e) {
                        System.out.printf("Please enter a valid option for new contact%n");
                        input.nextLine();
                    }
                }
            }//end while
        }//end edit if statement

        //asks for information to store in linked list
        System.out.printf("Enter first name: ");
        if (!edit) {
            input.nextLine();
        }
        String firstName = input.nextLine();
        System.out.printf("Enter last name: ");
        String lastName = input.nextLine();
        System.out.printf("Enter address: ");
        String address = input.nextLine();
        System.out.printf("Enter city: ");
        String city = input.nextLine();
        System.out.printf("Enter phone number: ");
        String number = input.nextLine();
        //if index isn't specified, add to end of the list
        if (index == -1) {
            book.add(firstName, lastName, address, city, number);
        }
        //otherwise add to specific index
        else {
            book.add(firstName, lastName, address, city, number, index);
        }
    }//end add

    //deletes a specific contact
    private static void delete(Scanner input, PhonebookManager book) {
        //if phonebook doesnt have any information, tell user to add
        //a contact first
        if (book.head == null) {
            System.out.printf("Please add a contact first%n%n");
            return;
        }
        //searches for contact to delete based on name
        //if multiple contacts with the same name are found, only
        //the first will be deleted
        System.out.printf("Enter the name of the contact you would like to delete%n");
        System.out.printf("If multiple contacts with the same name are");
        System.out.printf(" found, only the first will be deleted.%n");
        int[] index = getIndexes(input, book, 0);
        //if no contact with specified name is found, return to menu
        if (index[0] == -1) {
            System.out.println();
            System.out.printf("No such contact found.%n%n");
            return;
        }
        //otherwise proceed
        else {
            System.out.println();
            System.out.printf("Contact found:%n");
            System.out.println();
            //print contact
            book.print(index[0]);
            boolean bool = true;
            //makes sure user would like to delete this contact from their book
            while(bool) {
                System.out.printf("Would you like to delete this contact? (y/n) ");
                char choice = input.next().toLowerCase().charAt(0);
                //if user enters n, save the contact and return to menu
                if (choice == 'n') {
                    System.out.println();
                    System.out.printf("Contact preserved.%n%n");
                    input.nextLine();
                    return;
                }
                //otherwise delete contact
                else if (choice == 'y') {
                    book.delete(index[0]);
                    System.out.println();
                    System.out.printf("Contact deleted%n");
                    System.out.println();
                    input.nextLine();
                    return;
                }
                //catches and inputs that arent yes or no answers and re-prompts
                else {
                    System.out.printf("Please choose (y) for yes or (n) for no%n");
                }
            }//end while
        }//end else
    }//end delete

    //searches for a contact and prints if found
    private static void search(Scanner input, PhonebookManager book, int by) {
        //if phonebook doesnt have any information, tell user to add
        //a contact first
        if (book.head == null) {
            System.out.printf("Please add a contact first%n%n");
            return;
        }
        int[] index = getIndexes(input, book, by);
        //if no contact is found tell user
        if (index[0] == -1) {
            System.out.printf("%nNo such contact found.%n%n");
        }
        //if contacts are found, print them
        else {
            System.out.println();
            System.out.printf("Contact(s) found:%n%n");
            for (int i = 0; i < index.length; i++){
                if (index[i] != -1) {
                    book.print(index[i]);
                }
            }
        }
    }//end search

    //searches for the indexes of specific contacts
    //by dictates whether to search by name (0) address (1) or number (2)
    private static int[] getIndexes(Scanner input, PhonebookManager book, int by) {
        int[] index = null;
        //asks for information and sends to manager's search method
        if (by == 0) {
            System.out.printf("First name of contact: ");
            String fName = input.nextLine();
            System.out.printf("Last name of contact: ");
            String lName = input.nextLine();
            String name = fName + lName;
            index = book.search(by, name);
        }
        else if (by == 1) {
            System.out.print("Address of contact: ");
            String address = input.nextLine();
            index = book.search(by, address);
        }
        else if (by == 2) {
            System.out.printf("Phone number of contact: ");
            String number = input.nextLine();
            index = book.search(by, number);
        }
        //returns the array of indexes
        return index;
    }//end getIndexes

    //edits a specific contact
    //I chose not to make different edit functions for different types
    //of edits because I thought reusing the delete and add code would
    //accomplish the same thing in a more efficient manner 
    private static void edit(Scanner input, PhonebookManager book) {
        //if phonebook doesnt have any information, tell user to add
        //a contact first
        if (book.head == null) {
            System.out.printf("Please add a contact first%n%n");
            return;
        }
        //asks for the name of the contact user would like to edit
        //if multiple are found, only first will be edited
        System.out.printf("Enter the name of the contact you would like to edit%n");
        System.out.printf("If multiple contacts with the same name are");
        System.out.printf(" found, only the first will be edited.%n");
        //searches for indexes
        int[] index = getIndexes(input, book, 0);
        //if no contact with specified name is found, return to menu
        if (index[0] == -1) {
            System.out.println();
            System.out.printf("No such contact found%n%n");
            return;
        }
        //otherwise proceed
        else {
            System.out.println();
            System.out.printf("Contact found:%n");
            System.out.println();
            book.print(index[0]);
            System.out.printf("Please enter your changes%n");
            //here is the reused code. Edit deletes the node
            //from the book and makes a new one with users changes
            //at the same index as the old contact
            book.delete(index[0]);
            add(input, book, true, index[0]);
            System.out.println();
            System.out.printf("Contact saved%n%n");
        }
    }//end edit
}//end class
