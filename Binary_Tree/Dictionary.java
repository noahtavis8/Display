// Name: Noah Tavis

// Date: 3/15/24

// Class: CS145 Computer Science II

// Project: BST Dictionary

// Purpose: To use a BST to create a contact dictionary

// BINARY SEARCH TREE USED

// I couldn't figure out how to balance the tree 
// however I successfully ordered it alphabetically
// by last name then first name

package BinarySearchTree;

import java.math.BigInteger;
import java.util.Scanner;

//interactive class

//I wasnt sure why the primary key was needed - I decided to base
//the search and modify methods on the contact's name to make things
//easier for the user - so rather than make a random unique number
//for each node that would never be used, I just decided to omit the
//key entirely

public class Dictionary {
    public static Tree tree = new Tree();

    //main menu method asks user what to do
    //fairly straightforward, uses switch case statement
    public static void main(String[] args) {
        boolean menu = true;
        Scanner input = new Scanner(System.in);
        intro(); //prints intro message

        while (menu) {
            System.out.println("Please choose an option:");
            System.out.println("(1) Add a Contact");
            System.out.println("(2) Modify a Contact");
            System.out.println("(3) Search for a Contact");
            System.out.println("(4) Delete a Contact");
            System.out.println("(5) List Contacts");
            System.out.println("(6) Exit");
            String choice = input.nextLine().toLowerCase();

            switch (choice) {
                case "1":
                case "add":
                case "add contact":
                case "add a contact":
                    add(input, 0, new BigInteger("-1"));
                    break;
                case "2":
                case "modify":
                case "modify contact":
                case "modify a contact":
                    if (tree != null) {
                        modify(input);
                    }
                    else {
                        System.out.printf("%nPlease add a contact first%n%n");
                    }
                    break;
                case "3":
                case "search":
                case "search contact":
                case "search for a contact":
                    if (tree != null) {
                        search(input);
                    }
                    else {
                        System.out.printf("%nPlease add a contact first%n%n");
                    }
                    break;
                case "4":
                case "delete":
                case "delete contact":
                case "delete a contact":
                    if (tree != null) {
                        delete(input);
                    }
                    else {
                        System.out.printf("%nPlease add a contact first%n%n");
                    }
                    break;
                case "5":
                case "list":
                case "list contacts":
                    if (tree != null) {
                        list(input);
                    }
                    else {
                        System.out.printf("%nPlease add a contact first%n%n");
                    }
                    break;
                case "6":
                case "exit":
                case "q":
                    menu = false;
                    break;
                default:
                    System.out.println("Please choose a valid option\n");
            }
        }
        input.close(); //closes scanner memory
    }//end main

    //adds contact information to BST
    private static void add(Scanner input, int addOrEdit, BigInteger editData) {
        System.out.printf("Enter first name: ");
        String firstName = input.nextLine();
        System.out.printf("Enter last name: ");
        String lastName = input.nextLine();
        System.out.printf("Enter address: ");
        String address = input.nextLine();
        System.out.printf("Enter city: ");
        String city = input.nextLine();
        System.out.printf("Enter state: ");
        String state = input.nextLine();
        System.out.printf("Enter zip: ");
        String zip = input.nextLine();
        System.out.printf("Enter email: ");
        String email = input.nextLine();
        System.out.printf("Enter phone number: ");
        String number = input.nextLine();

        //the data value will always be a number that represents the contact's
        //name in an alphebetized way such that lower numbers are first alphabetically
        //this is my version of the primary key used for searching contacts
        //this is also how I ordered the tree - numbers that are lower than the current number
        //go to the left, others go to the right

        BigInteger data = alphabetize((lastName + firstName).toLowerCase().trim());
        //if the add method is called with a 1, it signifies modification
        //and calls the modify method from tree. Otherwise, it adds a new node
        if (addOrEdit == 0) {
            tree.add(data, firstName, lastName, address, city, state, zip, email, number);
        }
        //like I did in PhoneBook, instead of asking the user for 
        //specific information they would like to edit I just 
        //prompted for all new information using the add method
        //and then sent that information to the BST manager
        else if (addOrEdit == 1) {
            tree.modify(data, firstName, lastName, address, city,
                    state, zip, email, number, editData);
        }
    }//end add

    //modifies BST
    private static void modify(Scanner input) {
        System.out.printf("Please enter the first and last name of the%n");
        System.out.printf("contact you would like to modify exactly as%n");
        System.out.printf("it was entered%n");
        System.out.printf("Enter first name: ");
        String firstName = input.nextLine();
        System.out.printf("Enter last name: ");
        String lastName = input.nextLine();
        BigInteger data = alphabetize((lastName + firstName).toLowerCase().trim());
        //checks if the contact is in the BST
        boolean contains = tree.contains(data);
        //if not, let the user know and return to menu
        if (!contains) {
            System.out.printf("%nContact not found%n%n");
            return;
        }
        //if it is, re-use the add method (this time with a value of 1) to
        //modify the BST
        else {
            System.out.printf("Contact found! Please re-enter their information%n");
            add(input, 1, data);
        }
    }

    //searches for a node by name and prints it
    //very similar code to the modify method 
    //(probably could have made them into one method)
    private static void search(Scanner input) {
        System.out.printf("Please enter the first and last name of the%n");
        System.out.printf("contact you would like to modify exactly as%n");
        System.out.printf("it was entered%n");
        System.out.printf("Enter first name: ");
        String firstName = input.nextLine();
        System.out.printf("Enter last name: ");
        String lastName = input.nextLine();
        BigInteger data = alphabetize((lastName + firstName).toLowerCase().trim());
        boolean contains = tree.contains(data);
        if (!contains) {
            System.out.printf("%nContact not found%n%n");
            return;
        }
        else {
            System.out.printf("%nContact found:");
            tree.search(data);
        }
    }

    //searches for a node by name and deletes it
    //again, very similar code to the modify and search methods
    private static void delete(Scanner input) {
        System.out.printf("Please enter the first and last name of the%n");
        System.out.printf("contact you would like to modify exactly as%n");
        System.out.printf("it was entered%n");
        System.out.printf("Enter first name: ");
        String firstName = input.nextLine();
        System.out.printf("Enter last name: ");
        String lastName = input.nextLine();
        BigInteger data = alphabetize((lastName + firstName).toLowerCase().trim());
        boolean contains = tree.contains(data);
        if (!contains) {
            System.out.printf("%nContact not found%n%n");
            return;
        }
        else {
            System.out.printf("%nContact deleted%n%n");
            tree.remove(data);
        }
    }

    //lists contacts user has entered
    private static void list(Scanner input) {
        boolean menu = true;
        while (menu) {
            System.out.printf("How would you like to list your contacts?%n");
            System.out.printf("(1) Pre-Order%n");
            System.out.printf("(2) In-Order%n");
            System.out.printf("(3) Post-Order%n");
            String choice = input.nextLine().toLowerCase();

            switch (choice) {
                case "1":
                case "pre":
                case "pre-order":
                    tree.preOrder();
                    menu = false;
                    break;
                case "2":
                case "in":
                case "in-order":
                    tree.inOrder();
                    menu = false;
                    break;
                case "3":
                case "post":
                case "post-order":
                    tree.postOrder();
                    menu = false;
                    break;
                default:
                    System.out.printf("Please select a valid option%n");
                    break;
            }
        }
    }//end list

    //prints intro message
    private static void intro() {
        System.out.println("Welcome to Dictionary, a program");
        System.out.println("that allows you to add, modify");
        System.out.println("and delete contact information");
        System.out.println();
    }

    //converts a string (always lastName + firstName) to a number
    //this is how I alphabetized the tree - lower numbers than the
    //current number go to the left of the current node and vice versa

    //I used BigInteger because a longer name sometimes reaches the 
    //memory limit of an int or a long
    private static BigInteger alphabetize(String string) {
        //starts every alphabet number with a 1
        String total = "1";
        for (int i = 0; i < string.length(); i++) {
            //gets numerical number of the char being checked
            int num = string.charAt(i) - 96;
            //if the number is less than 10, add a 0 to the string
            //to ensure that letters like a (1) and z (26) get compared
            //in the same manner
            if (num < 10) {
                total += "0" + num;
            }
            else {
                total += num;
            }
        }
        return new BigInteger(total);
    }
}//end class