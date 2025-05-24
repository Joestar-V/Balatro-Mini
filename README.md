Hello, I'm Joey Valencia and this is my final project for CS 151. It's a game called Balatro-Mini, inspired by the popular virtual card game Balatro. In said game, the player draws and discards hands of cards as they see fit to make the ideal poker hand for the purpose of obtaining a high score. Each round, the hand you play will have to yield a greater score than a certain, increasingly high required score to beat. This is possible through multipliers and extra score points obtained from your type of poker hand or from jokers, special modifiers the player can collect after each round. It's based on strategy and random chance, and your objective is to reach the highest round you possibly can.
The game should run as long as you have all the files and can be played using only number inputs in the command line. The player is given numbered choices and they can select their choice, sometimes multiple choices, by typing the numbers of the choices they choose. The game ends once the player fails to make a high-enough scoring hand and game over is reached.
This game makes use of :
	Inheritance through it's Joker classes, as all different types of jokers are children of the parent Joker class. 
	Polymorphism also through the jokers, each one of them has their own implementation of the applyEffect() method which is purely virtual in parent Joker class.
	An Abstract Class, which is the Joker parent class. No instance of this class is ever created, only of it's derived children.
	C++ STL Data Structures through the use of vectors and maps such as the ones used to keep track of how many cards of each rank and suit are in each hand.
	A Custom Data Structure, that being the hand, which is a list of card nodes that is navigated using ->next

There may be more instances of these or other concepts being used in the code but some of them are unused or insignificant. For example, overloaded operators were added to the cards, but not used.
