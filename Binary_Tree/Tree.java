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
import java.util.NoSuchElementException;

//tree manager class
public class Tree {
    private static TreeNode root;

    //constructor with no arguments
    public Tree() {
        root = null;
    }

    //constructor with every bit of information
    public void add(BigInteger value, String firstName, String lastName, String address,
                String city, String state, String zip, String email, String phoneNumber) {
        root = add(root, value, firstName, lastName, address,
                city, state, zip,  email, phoneNumber);
        //prints the newest contact
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
        System.out.print(string);
    }

    //adds a new node to the tree
    //in this case, "value" is the number that represents the alphebetized key of the
    //contact. If the number is less than the current node, add contact to the left and
    //vise versa
    public TreeNode add(TreeNode root, BigInteger value, String firstName, String lastName,
        String address, String city, String state, String zip, String email, String phoneNumber) {
        if (root == null) {
            root = new TreeNode(value, firstName,
                        lastName, address, city, state, zip, email, phoneNumber);
        }
        else if (root.data.compareTo(value) > 0) {
            root.left = add(root.left, value, firstName,
            lastName, address, city, state, zip, email, phoneNumber);
        }
        else if (root.data.compareTo(value) < 0) {
            root.right = add(root.right, value, firstName,
            lastName, address, city, state, zip, email, phoneNumber);
        }
        else {
            return root;
        }
        return root;
    }

    //removes a node based on name
    public void remove(BigInteger value) {
        root = remove(root, value);
    }

    //removes a node based on name. Very similar to power point code
    public TreeNode remove(TreeNode root, BigInteger value){
        if(root == null) {
            return null;
        }
        else if (root.data.compareTo(value) > 0) {
            root.left = remove(root.left, value);
        }
        else if (root.data.compareTo(value) < 0) {
            root.right = remove(root.right, value);
        }
        else {
            if (root.right == null) {
                return root.left;
            }
            else if (root.left == null) {
                return root.right;
            }
            else {
                root.data = getMin(root.right);
                root.right = remove(root.right, root.data);
            }
        }
        return root;
    }

    //returns the first contact in the alphabetized list
    public BigInteger getMin() {
        if (root == null) {
            throw new NoSuchElementException();
        }
        return getMin(root);
    }

    private BigInteger getMin(TreeNode root) {
        if (root.left == null) {
            return root.data;
        }
        else {
            return getMin(root.left);
        }
    }

    public boolean contains(BigInteger value) {
        return contains(root, value);
    }

    //returns true if the tree contains the value (name) and false if not
    public boolean contains(TreeNode root, BigInteger value) {
        if(root == null) {
            return false;
        }
        else if (root.data.compareTo(value) == 0) {
            return true;
        }
        else if (root.data.compareTo(value) > 0) {
            return contains(root.left, value);
        }
        else {
            return contains(root.right, value);
        }
    }

    //prints the tree in pre order
    public void preOrder() {
        preOrder(root);
    }

    //in pre order, we first print the current node, then each left node,
    //then each right node
    public void preOrder(TreeNode root) {
        if (root == null) {
            System.out.printf("No nodes");
        }
        else {
            System.out.print(root);
            if(root.left != null) {
                preOrder(root.left);
            }
            if(root.right != null) {
                preOrder(root.right);
            }
        } 
    }

    //prints list in post order
    public void postOrder() {
        postOrder(root);
    }

    //in post order, we first print the left nodes, then the right nodes, 
    //then the current node
    public void postOrder(TreeNode root) {
        if (root == null) {
            System.out.printf("No nodes");
        }
        else {
            if(root.left != null) {
                postOrder(root.left);
            }
            if(root.right != null) {
                postOrder(root.right);
            }
            System.out.print(root);
        } 
    }

    //prints list in order
    public void inOrder() {
        inOrder(root);
    }

    //in order prints the left nodes, then the current node and then the right nodes
    public void inOrder(TreeNode root) {
        if (root == null) {
            System.out.printf("No nodes");
        }
        else {
            if(root.left != null) {
                inOrder(root.left);
            }
            System.out.print(root);
            if(root.right != null) {
                inOrder(root.right);
            }
        } 
    }

    //modifies a node
    public void modify(BigInteger data, String firstName, String lastName,
        String address, String city, String state, String zip, 
        String email, String number, BigInteger editData) {
        root = modify(root, data, firstName, lastName, address,
        city, state, zip, email, number, editData);
    }

    //if the vale (name) of the current node is equal to the value we are looking for,
    //update information. Otherwise, recurse
    private TreeNode modify(TreeNode root, BigInteger data, String firstName,
        String lastName, String address, String city,
        String state, String zip, String email, String number, BigInteger editData) {
        if (root.data.compareTo(editData) == 0) {
            root.data = data;
            root.firstName = firstName;
            root.lastName = lastName;
            root.address = address;
            root.city = city;
            root.state = state;
            root.zip = zip;
            root.email = email;
            root.phoneNumber = number;
        }
        else if (root.data.compareTo(editData) > 0) {
            root.left = modify(root.left, data, firstName, lastName, 
            address, city, state, zip, email, number, editData);
        }
        else if (root.data.compareTo(editData) < 0) {
            root.right = modify(root.right, data, firstName, lastName, 
            address, city, state, zip, email, number, editData);
        }
        return root;
    }

    //searches for a node based on name
    public void search(BigInteger data) {
        search(data, root);
    }

    //if the name of the current node equals the name searched
    //print it. Otherwise, recurse
    public void search(BigInteger data, TreeNode root) {
        if (root.data.compareTo(data) == 0) {
            System.out.print(root);
        }
        else if (root.data.compareTo(data) > 0) {
            search(data, root.left);
        }
        else if (root.data.compareTo(data) < 0) {
            search(data, root.right);
        }
    }
}