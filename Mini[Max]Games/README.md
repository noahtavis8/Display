# Mini[Max] Games
### Video Demo:  [Mini[Max] Games Demo](https://youtu.be/8d7yMM4DuRA)
### Description

Welcome, one and all, to Mini[Max] Games!

This project is a web-based application that uses Flask and Python to operate. Its purpose is to provide four simple games for the user to play, optionally against a friend or against a computer AI opponent. These games are **Tic-Tac-Toe**, **Minesweeper**, **Nim** and **Connect 4**.

### Requirements

Uses flask and flask_session.

### How to use

Ensure necessary libraries (flask, flask_session) are installed before running. 

If you execute app.py in a terminal window, you'll see a line with a link: "Running on http://___". Your machine will host a private development environment with the application at that address. Follow it to view in any browser.

### /helpers

This is where the game logic for each game is kept. Inside there are four game python files, each with some game framework and some bot logic for that game: /helpers/game_name.py.

Three of these files were project assignments from CS50AI that I had already completed (Tic-Tac-Toe, Minesweeper and Nim). Essentially, I just imported them over from that class and replaced the given command-line front end with some flask web app details that are gone over later.

The fourth game, Connect 4, was something that I made by repurposing the MiniMax algorithm from Tic-Tac-Toe. You’ll notice that it still uses “X” and “O” as the player titles. I needed to improve MiniMax by updating a few things - a better util function, alpha-beta pruning, and depth limitation. Alpha-beta pruning and depth limitation were easier than I thought to implement; they were well known and simple to search for and add, so the only thing was the new board evaluation function. I looked up some Connect 4 strategies, and center column control was something to prioritize. I also added some reward for having pieces in a row, and some punishment when the opponent (the user) has 4 pieces in a row. With these pieces added to the reworked Tic-Tac-Toe algorithm, I had a clean bot to work with. 

### /routes

Here is where the Flask blueprints are stored. Every page on the website has its own route file, all of which correspond to its own blueprint, which are stored in the application object when it's loaded. 

There's not a whole lot to note about that here, it's just the backend for the template html rendering. Each game has its own route file as well, named with an ‘R’: game_nameR.py.

### /static and /static/images

This is where the styles and images are stored. The styles sheet is a bit messy; realistically I should have separate files inside of another /styles directory for each page. 

Again, not much to say here. Static files that are used to enhance the look and feel of the web application. 

### /templates 

This is where all of the html front-end templates are stored. Using Jinja, the software Flask uses for templating, every html file extends the layout.html file, where the nav bar is laid out and some placeholders for other things are laid out as well. 

I made the choice early on to style the main block section in layout.html (bad idea). After I had formatted the game buttons on the home page, I realized I didn’t want the same style, so I made another block and toggled the older one off whenever I didn't need it with session.

### General design decisions

Each game follows the same format in general. It uses Flask’s session to keep track of the game board, and the bot logic to keep track of what moves are allowed, what happens after each move, and player win status. Each of these operations for game logic are carried out in respective helpers/game_name.py files. They all take as input the board layout, typically a list of all the spots on the board and their current contents. These lists are serializeable, making them suitable for session use. 

Decisions as to whether the player wants to play a computer, how hard they want their game to be, and similar are also stored in session. Every time the user visits home, about, or resources, session is cleared, meaning the user must go through the process of choosing a game and how they want to play it again. 

Each game also has a how to play page, in which instructions are laid out. Session is not cleared when accessing, and when the back arrow is pressed, they are returned to their current game and its current state. 

Both **Tic-Tac-Toe** and **Connect 4** use MiniMax with alpha-beta pruning as their decision engine. Connect 4 implements depth-limitation as well, set to a max-depth of 4. 

**Minesweeper** uses its own logic, in which inferences are made based on a knowledgebase of cells and mines contained within given sets of cells. In this game, the user doesn’t play against the bot, rather they can call upon its knowledge and ask it to make a move for them. It selects randomly if it doesn’t know a correct move to play.

The **Nim** bot uses Q-learning and plays a user-specified number of games to train on to build its knowledgebase. This was a little tricky to keep track of with session, as everything stored must be serializeable. Instead of storing the NimAI object (not allowed with session), I chose to store its knowledge base and replace a new bot’s knowledge base with the built one from session every move. When the user specifies the number of games to play and hits submit, the bot trains, and its knowledgebase then gets stored, once. This way, only one knowledgebase is built per game instance, and during the game its recycled without ever having to train multiple times. 

The front-end game board logic is unique for each game. There was a specific way I wanted my games to feel, so every time the game logic was done, I made a new game board front end unique to the bot. 

For each game, each available spot can be clicked on as a button. User input is verified through each game’s route file, and only available moves are allowed through POST. The selection logic for Minesweeper, Nim, and Connect 4 is handled with some JS. Minesweeper uses it for right and left click capability for each cell. Nim uses it to handle selection of only one item from a pile (and how items look when selected, slightly raised). Connect 4 uses it to handle multiple cells for each column constituting the same single move for a single column. 

The about page gives the user a slight overview of the inspiration for the project, as well as some slight insight into how the bots for the page were created. 

The resources page goes over the outside resources I called upon to make the project. 

### Final notes

I think that's it! I hope whoever sees this enjoys the project, as relatively simple as the end product is. It took me a lot of time (much more than I was expecting) and it gave me a lot of real project experience with even just a relatively small idea. 

Thank you to those who put on CS50 and CS50AI. I really enjoyed those classes and they gave me a lot of real world experience with computer programming and surface level machine learning. 
