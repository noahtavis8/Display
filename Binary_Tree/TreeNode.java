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

//Individual node manager
public class TreeNode {
    public BigInteger data;
    public String firstName;
    public String lastName;
    public String address;
    public String city;
    public String state;
    public String zip;
    public String email;
    public String phoneNumber;
    public TreeNode left;
    public TreeNode right;

    //constructor in case left and right values are not provided
    public TreeNode (BigInteger data, String firstName, String lastName, String address,
                    String city, String state, String zip, String email, String phoneNumber) {
        this.data = data;
        this.firstName = firstName;
        this.lastName = lastName;
        this.city = city;
        this.state = state;
        this.address = address;
        this.zip = zip;
        this.email = email;
        this.phoneNumber = phoneNumber;
        left = null;
        right = null;
    }

    //constructor in case left and right pointers are provided
    public TreeNode(BigInteger data, String firstName, String lastName, String address,
                    String city, String state, String zip, String email, String phoneNumber,
                    TreeNode left, TreeNode right) {
        this.data = data;
        this.firstName = firstName;
        this.lastName = lastName;
        this.city = city;
        this.state = state;
        this.email = email;
        this.address = address;
        this.zip = zip;
        this.phoneNumber = phoneNumber;
        this.left = left;
        this.right = right;
    }

    //converts node to a string that displays each value
    public String toString() {
        String string = "\nName: ";
        string += lastName + ", " + firstName;
        string += "\nAddress: ";
        string += address;
        string += "\nCity: ";
        string += city;
        string += "\nState: ";
        string += state;
        string += "\nZip: ";
        string += zip;
        string += "\nEmail: ";
        string += email;
        string += "\nPhone Number: ";
        string += phoneNumber + "\n\n";
        return string;
    }
} //end class
