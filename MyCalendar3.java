// Name: Noah Tavis

// Date: 12/4/23

// Class: CS &141A Face-to-Fact

// Assignment: Calendar Part 3

// Purpose: Allow the user to view differrnt dates of choice with events on a calendar.

// Citation: This program references Deitel/Deitel - 11th edition (Late Objects)

// Hours Spent: I think I spent about 4 hours on this assignment

package calendarStuff;
import java.util.*;
import java.io.*; //preps system for calendar functions and scanner functions


public class MyCalendar3 {
    public static String[][] calendarEvent = new String[12][];
    public static void main(String[] args) { //brings up menu for user

        Scanner input = new Scanner(System.in); //defines input as scanner variable
        int menu = 0;
        initializeArray(); //initializes global array capacity
        initializeWithFile("calendarEvents.txt"); //hardcoded event file

        while (menu != -1) { //while the menu value is not negative 1, prompt the user
            menu = mainMenu(input, menu);
        }

        input.close(); //closes the input variable's recourses from the scanner function
    }

    public static int mainMenu(Scanner input, int month) { //main menu function
        boolean fb = false; //initially sets fb to false. fb is set to true if the file print option is chosen.
        //I chose to re-use the userCalendar with tweaks in case fb is true function to print a calendar to a file
        System.out.printf("Please type a command%n");
        System.out.printf("    \"e\" to enter a date and display the corresponding calendar%n");
        System.out.printf("    \"t\" to get todays date and display today's calendar%n");
        System.out.printf("    \"n\" to display the next month%n");
        System.out.printf("    \"p\" to display the previous month%n");
        System.out.printf("    \"ev\" to add an event to the calendar%n");
        System.out.printf("    \"fp\" to print a month to a seperate text file%n");
        System.out.printf("    \"q\" to quit the program%n");
        String choice = input.next();
        
        /* Each input from the user calls a different method, each of which returns a month value if needed.
            * This month value is then returned to main, which continues the loop and allows
            * 'p' and 'n' to be used. If
            * the user enters 'q', the method returns -1, thus ending the menu loop.
            * If the user enters 'n' or 'p' before there is a calendar to draw from, an error message
            * is printed and the user is re-promted. If the user doesn't enter a valid command, an
            * error message is displayed and the user is re-prompted. */

            switch(choice) {
                case "e":
                    month = userCalendar(input, fb);
                    break;
                case "t":
                    month = todaysCalendar();
                    break;
                case "n":
                    if (month == 0) {
                        System.out.printf("Please begin with a calendar using \"e\" or \"t\"%n");      
                        break;
                    }
                    else {
                        month = nextCalendar(month, input);
                        break;
                    }
                case "p":
                    if (month == 0) {
                        System.out.printf("Please begin with a calendar using \"e\" or \"t\"%n");      
                        break;
                    }
                    else {
                        month = previousCalendar(month, input);
                        break;
                    }
                case "ev":
                    addEvent(input);
                    break;
                case "fp":
                    fb = true;
                    userCalendar(input, fb);
                    fb = false;
                    break;
                case "q":
                    month = -1;
                    break;
                default:
                    System.out.printf("Please enter a valid command.%n");
                    break;
            }
            return month;
    }

    public static void initializeArray() {
        //uses findDays method to make the 2D array large enough to hold a single event per day of the year
        for (int i = 1; i < 13; i++) {
            int days = findDays(i);
            calendarEvent[i - 1] = new String[days];
        }
    }

    public static void initializeWithFile(String fileName) { //fill array with data from file
        try (Scanner reader = new Scanner(new File(fileName))) {
            while(reader.hasNextLine()) { //while the file still has events to give
                //split the line into each part and fill array
                String line = reader.nextLine();
                String[] parts = line.split(" ");
                int eventDay = dayFromDate(parts[0]); //use dayFromDate and monthFromDate to gather
                //days and months from mm/dd character
                int eventMonth = monthFromDate(parts[0]);
                calendarEvent[eventMonth - 1][eventDay - 1] = parts[1];
            }
        }
        catch (FileNotFoundException e) { //if calendarEvents.txt cant be found for some reason, print an error message
            System.out.printf("Error 404 - calendarEvents.txt not found%n");
        }
    }

    public static void addEvent(Scanner input) { //gathers user events
        //initialize variables
        boolean k = true;
        int i = 0;
        while (k) {
            try {
                //ask the user for an event and a date
                System.out.printf("Enter an event with the format (mm/dd event_title)%n");
                if (i == 0) {
                    input.nextLine(); //consume very first newline character
                    i++;
                }
                String event = input.nextLine();
                String parts[] = event.split(" ");
                //if the event is the correct number of parts, attempt to gather date information.
                //The catch statement prevents crashes for the possible passed errors. 
                if (parts.length == 2) {
                    int eventDay = dayFromDate(parts[0]);
                    int eventMonth = monthFromDate(parts[0]);
                    int validity = checkValidity(eventMonth, eventDay); //check date validity
                    if (validity == 0) {
                        //if the date is valid and the user used the correct format, populate the array with the event
                        //on the correct day
                        calendarEvent[eventMonth - 1][eventDay - 1] = parts[1];
                        System.out.printf("Event successfully stored.%n");
                        k = false; //prevent loop from running again
                    }
                    //possible error statements, which continue the loop and re-prompts the user for a
                    //correctly formatted event
                    else {
                        System.out.printf("Please enter a valid date for your event.%n");
                    }
                }
                else {
                    System.out.printf("Invalid format. Be sure to use underscores for spaces in your event title.%n");
                }
            }
            catch (Exception e) {
                System.out.printf("Invalid format. Please try again.%n");
            }
        }
    }

    public static int userCalendar(Scanner input, boolean fb) { //draws calendar based on a date the user inputs

        //I used this method for the "fp" command becuase it already covers most of the code I would have to 
        //re-write anwyay. The key difference is the while loop just below, and the if statements further below.
        //both of which I tried to explain with comments

        //initializes each variable
        int i = 0;
        int k = 0;
        int userMonth = 0;
        int userDay = 0;
        int startDay = 0;
        int days = 0;
        String fileName = "no";
        boolean fbb = true; //for the wile loop that only runs if "fp" command is called
        //printstream initializations in case "fp" is called
        PrintStream console = System.out;
        PrintStream writer = System.out;

        //if the file print command is called, fb will be true, and the program will ask the user for an output file
        if (fb) {
            while (fbb) {
                try {
                    System.out.printf("What file would you like to print to? ");
                    input.nextLine();
                    fileName = input.nextLine();
                    File fileOut = new File(fileName);
                    //then it will switch the writer printstream to the output file
                    writer = new PrintStream(fileOut);
                    fbb = false;
                }
                catch (FileNotFoundException e) {
                    //if the file isn't found for whatever reason, restart the loop
                    System.out.printf("File not found. Please try again%n");
                }
            } 
        }

        //while i = 0, the user is prompted to input a date
        //try catch statement to catch possible errors
        //if an error occurs, print an error message and re-prompt the user

        while (i == 0) {
            try {
                System.out.printf("What date would you like to look at? (mm/dd) ");
                if (k == 0 && !fb) {
                    input.nextLine(); //consumes very first new line character
                    k++;
                }
                String userDate = input.nextLine().trim();

                userMonth = monthFromDate(userDate); //uses monthFromDate method to derive the month from the date the user inputted and stores as userMonth
                userDay = dayFromDate(userDate); //uses dayFromDate method to derive the day from the date the user inputted and stores as userDay
                startDay = dayOfWeek(userMonth); //gets a day for the calendar to start on
                days = findDays(userMonth); //gets how many days of the month to print
                int validity = checkValidity(userMonth, userDay); //validates the user's date input

                if (validity == 0) { //if date input is valid, terminate while loop and draw month
                    i = 1;
                }
                else { //if the date is invalid, re-prompt
                    System.out.printf("Date invalid. Please try again.%n");
                    i = 0;
                }
            }
            catch (Exception e) {
                System.out.printf("Date invalid. Please try again.%n");
                i = 0;
            }
        }
        //everything for the "fp" command is the same except for this key difference. I looked up how to switch an output stream
        //to a file I specicfied, and its actually pretty easy. Above this I got the output file information, and below this I set
        //System.out to print to that file. That way, anytime I print something using printf or println, it prints
        //to a file instead of to the terminal. I then call drawMonth and displayDate, both of which are now programmed to print to
        //the output file. At the end of the userCalender method, System.out switches back to the console, which makes print statements
        //print to the terminal. All of this only happens if "fb" is set to true, which only happens when "fp" is called.
        if (fb) {
            System.setOut(writer);
        }
        drawMonth(userMonth, startDay, days, userDay); //calls drawMonth method to draw the user's calendar to the terminal
        displayDate(userDay, userMonth); //writes the month and the day using displayDate
        if (fb) {
            System.setOut(console);
            System.out.printf("Calendar successfully printed to %s%n", fileName);
        }
        return userMonth; //returns the month value to the menu function
    }

    public static int checkValidity(int userMonth, int days) { //validates possible date inputs

        /* This function takes a day and a month and validates it.
        * Months 1, 3, 5, 7, 8, 10 and 12 all have 31 days
        * Months 4, 6, 9 and 11 all have 30 days
        * And month 2 has 28 days. If a month is greater than 12 or less than 1,
        * pass 1 for invalid. If a day is less than 0 or greater than the days
        * in the month, pass 1 for invalid. Otherwise, pass 0 for valid.
        */

        int i = 1;
        if (userMonth > 12 || userMonth <= 0) {
            i = 1;
        }
        else if ((userMonth == 1 | userMonth == 3 | userMonth == 5 | userMonth == 7 | userMonth == 8 | userMonth == 10 | userMonth == 12) && (days > 31 || days <= 0)) {
            i = 1;
        }
        else if ((userMonth == 4 | userMonth == 6 | userMonth == 9 | userMonth == 11) && (days > 30 || days <= 0)) {
            i = 1;
        }
        else if ((userMonth == 2) && (days > 28 || days <= 0)) {
            i = 1;
        }
        else {
            i = 0;
        }
        return i;
    }

    public static int findDays(int month) { //gets the days in a month for the draw month/row functions
        int days = 0;
        if (month == 2) {
            days = 29;
        }
        else if (month == 1 | month == 3 | month == 5 | month == 7 | month == 8 | month == 10 | month == 12) {
            days = 31;
        }
        else if (month == 4 | month == 6 | month == 9 | month == 11) {
            days = 30;
        } 
        return days;
    }

    public static int todaysCalendar() {
        Calendar sysCalendar = Calendar.getInstance(); //assings  calendar usage to sysCalender variable
        int sysDay = sysCalendar.get(Calendar.DATE); //gets today's date and stores as sysDay
        int sysMonth = sysCalendar.get(Calendar.MONTH) + 1; //gets today's month and stores as sysMonth
        int startDay = dayOfWeek(sysMonth); //gets the day of the week to start drawing on
        int days = findDays(sysMonth); //gets the days in the month
        drawMonth(sysMonth, startDay, days, sysDay); //draws today's month using drawMonth method
        displayDate(sysDay, sysMonth); //writes today's month and the day using displayDate
        return sysMonth; //return month value to menu function
    }

    public static int dayFromDate(String userDate) {
        //derrives the day from the user input and returns as an integer
        //passes an error if there is no '/' character, but this is caught by the try catch statements
        int index = userDate.indexOf("/");
        String day = userDate.substring(index + 1);
        int dayI = Integer.parseInt(day);
        return dayI;
    }

    public static int dayOfWeek(int month) { //gets the day of the week to start drawing the month on

        /* We need to know where to start drawing the month from. To do this, first we must get what
        * day to start on out of 365. We know that we will start drawing at the beginning of the month,
        * so we really only need to add every day of each month that comes before it. Since we start on day 
        * 1, we set yearDay to 1, then add days depending on how many months there are before. We can do
        * this with a for loop, which loops as many times as there are previous months. As i counts up, it
        * covers each month number, which leads to the correct number of days to add to yearDay as shown below.
        */
        int yearDay = 1;

        for (int i = 0; i < month; i++) {
            yearDay += findDays(i);
        }

        return (yearDay) % 7; //not entirely sure why adding 6 to yearDay works as opposed to 2, but it does so I'm not gonna mess with it
    }

    public static int monthFromDate(String userDate) {
        //derrives the month from the user input and returns as an integer
        //passes an error if there is no '/' character, but this is caught by the try catch statements
        int index = userDate.indexOf("/");
        String month = userDate.substring(0, index);
        int monthI = Integer.parseInt(month);
        return monthI;
    }

    public static int nextCalendar(int month, Scanner input) { //adds to the month value, which loops if already at 12
        if (month == 12) {
            month = 1;
        }
        else {
            month++;
        }
        month = monthCycle(month, input); //calls monthCycle which draws a new month
        return month; //returns new month value to menu
    }

    public static int previousCalendar(int month, Scanner input) { //subtracts from the month value, which loops if already at 1
        if (month == 1) {
            month = 12;
        }
        else {
            month--;
        }
        month = monthCycle(month, input); //calls monthCycle which draws a new month
        return month; //returns new month value to menu
    }

    public static int monthCycle(int month, Scanner input) { //draws next or previous month
        //initializes each variable
        int i = 1;
        int k = 0;
        String dayI = "no";
        int day = 0;
        int days = 0;

        /* Since I can't return more than one variable with a function, and we can't use arrays,
        * I need to ask the user again for a day to look at. This uses similar code to the 
        * userCalendar function, with a few differences. The loop re-promts the user for a day
        * while the user gives invalid days, which prevents the program from crashing. If there
        * is an error (say the user enters a string intstead of an int for a day), the try/catch 
        * statement re-prompts the user
        */

        while (i == 1) {
            try {
                System.out.printf("What day would you like to look at? (dd) ");
                if (k == 0) {
                    input.nextLine(); //consumes very first newline character
                    k++;
                }
                dayI = input.nextLine(); //gathers new day

                day = Integer.parseInt(dayI); //gathers an int from the string
                days = findDays(month); //finds days in the month
                int validity = checkValidity(month, day); //validates user's day against the month
                if (validity == 0) {
                    i = 0;
                }
                else {
                    System.out.printf("Invalid day. Please try again.%n");
                    i = 1;
                }
            }
            catch (Exception e) {
                System.out.printf("Invalid day. Please try again.%n");
                day = 0;
                i = 1;
            }
        }
        int startDay = dayOfWeek(month); //gathers a day to start printing from
        drawMonth(month, startDay, days, day); //draws new calendar
        return month; //passes month to menu method
    }

    public static void drawMonth(int month, int startDay, int days, int highlight) { //draws a calendar
        //calls drawACSII method to draw the ACSII art on top of the calendar
        drawACSII();

        System.out.printf("                                                            %d%n", month); //prints month above calendar

        //Since I coded the drawRow method to skip numbers below 1, we can
        //subtract from 1 as many times as the startDay calls for to print the
        //blank spaces on the calendar. This begins the month on the correct
        //day of the week.
        int row = 1;
        for (int k = 0; k < startDay; k++) {
            row--;
        }

        //initially sets calendar to print 5 rows, but sets to 6 if needed
        int rowLimit = 5;
        if (startDay >= 5 && days == 31) {
            rowLimit = 6;
        }
        else if (startDay == 6 && days == 30) {
            rowLimit = 6;
        }
        

        //prints "="s along the top of each row and then calls drawRow method to draw each row
        for(int i = 0; i < rowLimit; i++) {

            for(int j = 0; j < 120; j++) {
                System.out.printf("=");
            }

            System.out.printf("%n");
            row = drawRow(row, month, highlight); //drawRow method returns a new row value to be used again for each row.
            //This is how I kept track of each day's number in each row
        }

        //prints another line of "="s to the bottom of the finished calendar
        for(int j = 0; j < 120; j++) {
                System.out.printf("=");
        }

        System.out.printf("%n"); //prints a new line
    }

    public static int drawRow(int row, int month, int highlight) { //draws each row of the calendar
        //Method begins by deciding the maximum number of days to print, based on the days in each month
        int dayLimit = findDays(month);
        
        //prints the first line of each box, using increasing day numbers stored as "row"
        /* If the row number equals the day that the user chose, I put stars around the day
        * number to highlight it. The first two if/else statements keep spacing correct.
        * If the number in the day exceeds the number of days in the month, omit this number
        * from being printed.
        */
        String[] events = new String[7]; //makes a new array to store events in a more usable way for this function
        for(int i = 0; i < 7; i++) {
            //I used a second array to store events in, which makes it so I can use the row value
            //as my [i] value. This if statement checks if the row value actually has a valid date and
            //if the calendarEvents array is populated. If both are true, fill the events array
            //with the day-specific event.

            //I also changed the spacing of the calendar to print 16 spaces, which is the assumed limit for event titles.
            if (row > 0 && row < (dayLimit + 1) && calendarEvent[month - 1][row - 1] != null) {
                events[i] = calendarEvent[month - 1][row - 1];
            }
            if (row == highlight && row < 10) {
                System.out.printf("|*%d*             ", row);
            }
            else if (row == highlight && row >= 10){
                System.out.printf("|*%d*            ", row);
            }
            else if (row <= 0) {
                System.out.printf("|                ");
            }
            else if (row < 10) {
                System.out.printf("|%d               ", row);
            }
            else if (row >= 10 && row <= dayLimit) {
                System.out.printf("|%d              ", row);
            }
            else if (row > dayLimit) {
                System.out.printf("|                ");
            }
            row++; //iterates on row variable as each box is printed
        }

        System.out.printf("|%n"); //finishes the final box with "|"

        //prints the rest of the boxes for each row

        //here is where I printed the events to the calendar. Lines 516 and 517 loop to build calendar squares
        //row by row. The if statement on line 521 checks if the current row is the first one, and if it is, 
        //make the spacer value the length of the event to be printed. Then it prints the event (if there is one)
        //and the loop continues, printing space characters to fill the rest of the square. After the first row, 
        //business as usual.
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 7; j++) {
                int spacer = 0;
                System.out.printf("|");
                if (i == 0 && events[j] != null) {
                    spacer = events[j].length();
                    System.out.printf("%s", events[j]);
                }
                for (int k = 0; k < (16 - spacer); k++) {
                    System.out.printf(" ");
                }
            }
            System.out.printf("|%n");
        }

        return row; //returns the increased row value to continue counting days for each box
    }

    public static void drawACSII() {
        //prints my ACSII art above each calendar box
        //The art is a simple text message that reads "ACSII X JAVA"

        System.out.printf("%n");

        //adds a line of "="s to make things look good
        for(int j = 0; j < 120; j++) {
            System.out.printf("=");
        }

        System.out.printf("%n");

        //all of the next for loops only draw the first line of the ACSII art
        //This was tedious to code, so I only did it for the first line
        for(int i = 0; i < 46; i++) {
            System.out.printf(" ");
        }

        for(int i = 0; i < 4; i++) {
            System.out.printf("|");
        }

        for(int i = 0; i < 6; i++) {
            System.out.printf(" ");
        }

        for(int i = 0; i < 6; i++) {
            System.out.printf("|");
        }

        for(int i = 0; i < 4; i++) {
            System.out.printf(" ");
        }

        for(int i = 0; i < 5; i++) {
            System.out.printf("|");
        }

        for(int i = 0; i < 3; i++) {
            System.out.printf(" ");
        }

        for(int i = 0; i < 2; i++) {
            System.out.printf("|");
        }

        for(int i = 0; i < 2; i++) {
            System.out.printf(" ");
        }

        for(int i = 0; i < 2; i++) {
            System.out.printf("|");
        }

        //prints the rest of the ACSII art
        System.out.printf("%n");
        System.out.println("                                            ||    ||   ||        ||       ||  ||");
        System.out.println("                                            ||||||||   ||          ||     ||  ||");
        System.out.println("                                            ||    ||   ||            ||   ||  ||");
        System.out.println("                                            ||    ||    ||||||   |||||    ||  ||");
        System.out.printf("%n");   
        System.out.println("                                                          %     %");
        System.out.println("                                                           %   %");
        System.out.println("                                                            % %");
        System.out.println("                                                           %   %");
        System.out.println("                                                          %     %");
        System.out.printf("%n");
        System.out.println("                                            $$     $$$$     $$       $$     $$$$");
        System.out.println("                                            $$   $$    $$    $$     $$    $$    $$");
        System.out.println("                                            $$   $$$$$$$$     $$   $$     $$$$$$$$");
        System.out.println("                                        $$  $$   $$    $$      $$ $$      $$    $$");
        System.out.println("                                          $$     $$    $$       $$$       $$    $$");

        //finishes art with a row of "="s
        for(int j = 0; j < 120; j++) {
                    System.out.printf("=");
                }
        System.out.printf("%n");
        }

    public static void displayDate(int day, int month) {
        //prints the month and the day at the end of each calendar box
        System.out.printf("Month: %d%nDay: %d%n", month, day);
    }
}
                           