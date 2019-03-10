"""
/******************************************************************************
 *
 * Name:	Jack Scacco
 *
 * Date:	9-22-17
 *
 * Assignment: Project 3 (Blackjack)	
 *
 * Purpose: To create a functioning blackjack game that includes a deck 
 class and a card class.
 
 * Extra Note: Throughout the program I use 'stay' instead of 'stand'
because I thought that was the correct terminology. I use 'stand'
only on the button the user sees.
 *****************************************************************************/
"""

import tkinter as tk
import random 

class Game:
    """This class extends the Tk system to create a class that can be
    manipulated with tk methods as well as custom ones."""

    def __init__(self):
        """ The constructor. Creates a window with width and
        height at location loc."""
        #Call tk.Tk() to create an actual window/application
        self._window = tk.Tk()

        #Establish boundaries of window
        self._window.geometry("800x400")

        #Create a variable to keep track of the current round
        self._active = True

        #Establish a deck
        self._deck = Deck(self._window)
        self._deck.fill()
        self._deck.shuffle()

        #Create the user's and dealer's hand
        self._userHand = Hand(self, "user")
        self._dealerHand = Hand(self, "dealer")

        #Create score variables for both the user and the dealer
        self._userScore = 0
        self._dealerScore = 0

        #Create a label to keep track of score
        self._scoreboard = tk.Label(self._window, 
                                    text="User Score: %d Dealer Score: %d"
                                    %(self._userScore, self._dealerScore))
        self._scoreboard.pack()

        #Create a Hit  button that places a random card in the player's hand
        self._hitButton = tk.Button(self._window, text="Hit!", 
                                    command=self.hitbuttonPressed)
        self._hitButton.place(x=300, y=30)

        #Create a Stay button that stays the player
        self._stayButton = tk.Button(self._window, text="Stand", 
                                     command=self.stayButtonPressed)
        self._stayButton.place(x=365, y=30)

        #Create a button that resets the game
        self._resetButton = tk.Button(self._window, text="Reset", 
                                      command=self.reset)
        self._resetButton.place(x=440, y=30)
        #CITE: stackoverflow.com
        #DESC: How to disable/enable a button
        self._resetButton.config(state="disabled")

        #Create a Quit button
        self._quitButton = tk.Button(self._window, text="Quit", 
                                     command=self.quitself)
        self._quitButton.place(x=720, y=360)

        #Create two labels that denote the player and user hands
        self._dealerLabel = tk.Label(self._window, text="Dealer Hand:")
        self._dealerLabel.place(x=20, y=75)
        self._userLabel = tk.Label(self._window, text="User Hand:")
        self._userLabel.place(x=20, y=225)
        
        #Deal two cards to both players
        self.deal()

    def checkRound(self):
        """This method checks to see if either player has busted 
        or won or if both players have stayed and ends the round if so."""
        if(self.checkScores() or (self._userHand.getStay() 
                                  and self._dealerHand.getStay())):
            self.endRound()
           
    def hitbuttonPressed(self):
        """This method will complete the user's turn and then
        the dealer's turn"""
        self.hitPlayer()
        self.checkRound()

    def stayButtonPressed(self):
        """This recursive method will stay the user then 
        complete the dealer's turn"""
        self.stayPlayer()

        if self._active:
            self.dealerTurn()
            self.checkRound()
            #If the dealer is not done, go again!
            self.stayButtonPressed()

    def checkScores(self):
        """This method will check to see if either score is 
        above or equal to 21"""
        if(self._userHand.getScore() == 21 or 
           self._dealerHand.getScore() == 21 or
           self._userHand.getScore() < 0 or 
           self._dealerHand.getScore() < 0):
            return True
        return False

    def start(self):
        """This method is called when the grpahics system is ready
        to be run."""
        self._window.mainloop()

    def quitself(self):
        """This method is run to close out the application. It is called
        by the Quit button"""
        self._window.destroy()
    
    def deal(self):
        """This method deals two cards to the player and two to the computer"""
        self.hitPlayer()
        self.hitDealer()
        self.hitPlayer()
        self.hitDealer()

        #Check for 21 or bust
        self.checkRound()

    def hitPlayer(self):
        """This method places a card from the deck in the player's hand"""
        #Draw a card from the deck
        newCard = self._deck.draw()

        #Add it to the player's hand
        self._userHand.addTo(newCard)

        #Display the hand
        self._userHand.display()

    def stayPlayer(self):
        """This method "stays" the player"""
        self._userHand.changeStay()
    
    def hitDealer(self):
        """This method places a card from the deck
        in the dealer's hand"""
        #Draw a card from the deck
        newCard = self._deck.draw()

        #Add it to the dealer's hand
        self._dealerHand.addTo(newCard)

        #Display the hand
        self._dealerHand.display()

    def dealerTurn(self):
        """This method will determine if the dealer will hit or stay."""
        if self._dealerHand.getScore() < 17:
            #Hit
            self.hitDealer()
        elif self._dealerHand.getScore() >= 17:
            #Stay
            self._dealerHand.changeStay() 

    def endRound(self):
        """This method ends the round"""
        #Prevent the user from messing around
        self._active = False

        #Enable the reset button and disable the others
        self._resetButton.config(state="normal")
        self._hitButton.config(state="disabled")
        self._stayButton.config(state="disabled")

        #Display all cards
        self._dealerHand.showCards()
        self._userHand.showCards()
         
        #Determine who won the round and add to their score as
        #well as update temporary variables
        if self._userHand.compareScore(self._dealerHand):
            #(User Won)
            self._userScore += 1
        elif self._dealerHand.compareScore(self._userHand):
            #(Dealer Won)
            self._dealerScore += 1

        #Update the scoreboard
        self._scoreboard.config(text="User Score: %d Dealer Score: %d"
                                %(self._userScore, self._dealerScore))

    def reset(self):
        """This method resets the deck, players' hands, and visible cards"""
        #Disable reset button and enable the others
        self._resetButton.config(state="disabled")
        self._hitButton.config(state="normal")
        self._stayButton.config(state="normal")
        #Reset the hands
        self._userHand.reset()
        self._dealerHand.reset()
        #Reset deck
        self._deck.reset()
        
        #Re-enable the game
        self._active = True

        #Deal to both players
        self.deal()
        
class Card(tk.Canvas):
    """This class creates a Card widget that can be manipulated
    within the app. It extends tk.Canvas"""
    def __init__(self, window, loc=(-100, -100), faceUp=False, suit="spades", 
                 rank="ten", value=10,
                 frontImage="cardImages/s1.gif"):
        """The constructor. Creates a card in window of dimensions 
        widthxheight at location loc with background 'image.'"""
        #This code esablishes instance variables
        self._window = window
        self._front = tk.PhotoImage(file=frontImage)
        self._back = tk.PhotoImage(file="cardImages/back.gif")
        self._suit = suit
        self._rank = rank
        self._value = value
        self._loc = loc
        self._faceUp = faceUp

        #Set the width and height to the dimensions of the image supplied
        self._width = self._front.width()
        self._height = self._front.height()
        
        #Call the parent constructor so that there is a canvas to use
        tk.Canvas.__init__(self, self._window, width=self._width,
                           height=self._height)

        #Place the card at location loc
        (x, y) = self._loc
        self.place(x=x, y=y)

        #create a partial border to create a 3D effect
        self._rect = self.create_rectangle(1, 1, self._width, self._height)

        #Set the card's image to the card back
        self.image = self.create_image(0, 0, anchor='nw', image=self._front)

    def flip(self):
        """This fucntion flips the card over to its other side"""
        if not self._faceUp:
            #Flip card 'face up'
            self.flipUp()
        else: 
            #Flip card 'face down'
            self.flipDown()

    def moveBy(self, loc):
        """This method is a pseudo-move method that is seen with canvases, but 
        is designed specifically for the card"""
        #Get the current coordinates
        x = self.winfo_x()
        y = self.winfo_y()

        #Unpack tuple for the change in position
        (dx, dy) = loc
        
        #Set new coordinates
        newx = x + dx
        newy = y + dy

        #Actually move the widget
        self.place(x=newx, y=newy)

    def moveTo(self, loc):
        """This method moves the card to a specific location"""
        #Unpack the tuple
        (x, y) = loc

        #Place the card
        self.place(x=x, y=y)

    def show(self):
        """This method moves the card to a visible location"""
        self.moveBy((5000, 5000))
    
    def unshow(self):
        """This method moves the card to a non-visible location"""
        self.moveTo((-5000, -5000))

    def setValue(self, value):
        """This method changes the value of the card and is used with aces."""
        self._value = value

    def getValue(self):
        """This method returns the value of the card"""
        return self._value

    def getSuit(self):
        """This method returns the suit of the card"""
        return self._suit

    def getName(self):
        """This method returns the name (rank) of the card"""
        return self._rank

    def flipUp(self):
        """This method flips the card face up"""
        self.itemconfig(self.image, image=self._front)
        self._faceUp = True

    def flipDown(self):
        """This method flips the card face down"""
        self.itemconfig(self.image, image=self._back)
        self._faceUp = False

class Deck:
    """This class will function as a deck of 52 cards"""
    def __init__(self, window):
        """The constructor"""
        self._window = window
        self._deck = []

    def fill(self):
        """This method fills the deck with 52 cards, in order"""
        #Define all of the possible attributes of a card
        allSuits = ["c", "d", "h", "s"]
        allRanks = ["a", "2", "3", "4", "5", "6", "7", "8",
                    "9", "1", "j", "q", "k"]
        allSuitNames = ["clubs", "diamonds", "hearts", "spades"]
        allRankNames = ["ace", "two", "three", "four", "five", "six", "seven", 
                        "eight", "nine", "ten", "jack", "queen", "king"]
        allValues = [11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

        #Create 3 decks
        for _ in range(0, 3):
            #Cycle through every possible card and add it to the deck
            for s_ in range(0, 4):
                for r_ in range(0, 13):
                    suit = allSuitNames[s_]
                    rank = allRankNames[r_]
                    value = allValues[r_]
                    imageName = ("cardImages/%s%s.gif" % 
                                 (allSuits[s_], allRanks[r_]))
                    newCard = Card(self._window, (-100, 100), False, suit, 
                                   rank, value, imageName)
                    self._deck.append(newCard)

    def shuffle(self):
        """This method shuffles the deck"""
        tempDeck = []
        #Insert the cards from the deck to a temporary deck in a random order
        for _ in range(len(self._deck)):
            index = random.randrange(len(self._deck))
            tempDeck.append(self._deck[index])
            #CITE: www.tutorialspoint.com/python/list_remove.htm
            #DESC: Clarification of syntax for the remove method
            self._deck.pop(index)

        #Set the actual deck to the temporary deck
        self._deck = tempDeck

    def draw(self):
        """This method will remove the top card from the 
        deck and remove it from the decklist"""
        #'Draw' the card
        card = self._deck[0]
        
        #Remove card from deck
        self._deck.remove(self._deck[0])

        #Pass the card
        return card

    def reset(self):
        """This method refills and reshuffles the deck"""
        #CITE: stackoverflow.com/questions/1400608
        #DESC: How to delete all objects in a list
        #Delete the deck's objects
        del self._deck[:]
        
        #Refill
        self.fill()
 
        #Re-shuffle
        self.shuffle()
        
class Hand:
    """This class will represent the cards in either 
    the player or the dealer's hand"""
    def __init__(self, window, player="user"):
        """The constructor"""
        self._hand = []
        self._window = window
        self._player = player
        self._stay = False
        self._score = 0

    def addTo(self, card):
        """This method will add a card to the hand"""
        #Add card
        self._hand.append(card)
        
        #Add card's value to score
        self._score += card.getValue()

    def display(self):
        """This method will place the cards of the hand in the window"""
        for card in self._hand:
            #Set the Y location and orientation of 
            #the card based on who is playing
            if self._player == "user":
                yPos = 260
                card.flipUp()
            else:
                yPos = 110
                #If the card is the dealer's first, flip it up
                if self._hand.index(card) == 0:
                    card.flipUp()
                else:
                    card.flipDown()
            #Place the card
            #CITE: stackoverflow.com/questions/questions/176918
            #DESC: Clarification on the 'index' method
            card.moveTo((80*self._hand.index(card)+100, yPos))

    def getScore(self):
        """This method calculates the score of the hand"""
        if self._score > 21:
            #Bust
            #Set a temp score to test if it's still a bust when using 1 for aces
            tempScore = 0
            for card in self._hand:
                #Try 1 for all aces
                if card.getName() == "ace":
                    tempScore += 1
                else:
                    #Proceed as normal if not an ace
                    tempScore += card.getValue()
            if tempScore > 21:
                #If we still bust, say so
                return -1 
            #If not, say so
            return tempScore
        #If there is no bust even with aces as 1, return as normal
        return self._score

    def getStay(self):
        """This method returns True if the hand has stayed and 
        false if it still in play."""
        if self._stay:
            return True
        return False

    def showCards(self):
        """This method flips all of the cards 
        face up (for use at the end of the game)"""
        for card in self._hand:
            card.flipUp()

    def compareScore(self, other):
        """This method takes the score of the 
        hand and compares it to that of another.
        It returns true if the hand's score is bigger 
        and false if the other's is bigger"""
        if self.getScore() > other.getScore() and self.getScore() <= 21:
            return True
        return False
    
    def changeStay(self):
        """This method changes the stay value of the hand."""
        self._stay = True
    
    def reset(self):
        """This method empties the hand"""
        #Remove from screen
        for card in self._hand:
            card.unshow()
        
        #Reset actual hand
        del self._hand[:]

        #Reset 'stay' boolean
        self._stay = False

        #Reset hand score
        self._score = 0
        
def main():
    """The first function called"""
    #Initialize the application
    mainWindow = Game()
    
    #Hand control over to the graphics interface
    mainWindow.start()

    #Confirm that the program is still running after the app is closed
    print("Done!")

if __name__ == "__main__":
    main()


    
