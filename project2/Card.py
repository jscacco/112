"""
/******************************************************************************
 *
 * Name:	Jack Scacco
 *
 * Date:	9-12-17
 *
 * Assignment: Project 2	
 *
 * Purpose: To create a graphical card class that will complete certain actions 
 based on how many times a button has been clicked.
 *
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
        self._window.geometry("400x400")

        #Create the card to be used in the program and place it off-screen
        (self._suit, self._rank, self._value, 
         self._imageName) = self.randomizeCard()

        self._card = Card(self._window, (100, -100), self._suit, self._rank, 
                          self._value, self._imageName, "cardImages/back.gif")

        #Create a Do It button that performs different actions based on 
        #number of clicks
        clickButton = tk.Button(self._window, text="Do it!", 
                                command=self.clicked)
        clickButton.place(x=0, y=0)

        #Create a variable for the window that tracks the number of button 
        #clicks
        self.clickCount = 0

    def start(self):
        """This method is called when the grpahics system is ready
        to be run."""
        self._window.mainloop()

    def quitself(self):
        """This method is run to close out the application. It is called
        by the Quit button"""
        self._window.destroy()

    def clicked(self):
        """This function tells the program what to do when the Do It button is 
        clicked based on how many times it has already been clicked"""
        if self.clickCount == 0:
            #Move the card to a visible location on the screen
            self._card.show()
        elif self.clickCount == 1:
            #Flip the card over
            self._card.flip()
        elif self.clickCount == 2:
            #Move the card 10 pixels to the right
            self._card.moveBy((10, 0))
        elif self.clickCount == 3:
            #Move the card to an invisible location
            self._card.unshow()
        elif self.clickCount == 4:
            #Flip the card over
            self._card.flip()
        elif self.clickCount == 5:
            #Move the card 10 pixels to the right
            self._card.moveBy((10, 0))
        elif self.clickCount == 6:
            #Move the card back to a visible location on the screen
            self._card.show()
        elif self.clickCount == 7:
            #Close the window
            self.quitself()

        self.clickCount += 1
        
    def randomizeCard(self):
        """This method randomizes the card that is shown"""
        #This section of code establishes the possible suits and ranks
        allSuits = ["c", "s", "d", "h"]
        allRanks = ["a", "2", "3", "4", "5", "6", "7", "8", "9", "1",
                    "j", "q", "k"]
        allSuitNames = ["clubs", "spades", "diamonds", "hearts"]
        allRankNames = ["ace", "two", "three", "four", "five", "six",
                        "seven", "eight", "nine", "ten", "jack", "queen",
                        "king"]
        allRankValues = [11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
        
        #This section of code randomly assigns  suit and rank indices
        self.suitIndex = random.randrange(0, 4)
        self.rankIndex = random.randrange(0, 13)

        #Assign a suit, rank, names, and value to the card
        self.suit = allSuits[self.suitIndex]
        self.rank = allRanks[self.rankIndex]
        self.suitName = allSuitNames[self.suitIndex]
        self.rankName = allRankNames[self.rankIndex]
        self.value = allRankValues[self.rankIndex]

        #Create the name of the card with string formatting
        imageName = "cardImages/%s%s.gif" % (self.suit, self.rank)

        return (self.suit, self.rank, self.value, imageName)
        
class Card(tk.Canvas):
    """This class creates a Card widget that can be manipulated
    within the app. It extends tk.Canvas"""
    def __init__(self, window, loc, suit="spades", rank="ten", value=10,
                 frontImage="cardImages/s1.gif",
                 backImage="cardImages/back.gif"):
        """The constructor. Creates a card in window of dimensions 
        widthxheight at location loc with background 'image.'"""
        #This code esablishes instance variables
        self._window = window
        self._front = tk.PhotoImage(file=frontImage)
        self._back = tk.PhotoImage(file=backImage)
        self._suit = suit
        self._rank = rank
        self._value = value
        self._loc = loc

        #This keeps track of the card's appearance
        self.faceUp = False

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
        self.image = self.create_image(0, 0, anchor='nw', image=self._back)

    def flip(self):
        """This fucntion flips the card over to its other side"""
        if not self.faceUp:
            #Flip card 'face up'
            self.itemconfig(self.image, image=self._front)
            self.faceUp = True
        else: 
            #Flip card 'face down'
            self.itemconfig(self.image, image=self._back)
            self.faceUp = False

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
        self.moveBy((0, 200))
    
    def unshow(self):
        """This method moves the card to a non-visible location"""
        self.moveBy((0, -200))

    def getValue(self):
        """This method returns the value of the card"""
        return self._value

    def getSuit(self):
        """This method returns the suit of the card"""
        return self._suit

    def getName(self):
        """This method returns the name (rank) of the card"""
        return self._rank

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

#CITE: TAs
#DESC: Assisted with general diificulties in setting up the framework

#CITE: stackoverflow.com
#DESC: Clarificiation on syntax and uses of several methods

#CITE: effbot.org/tkinterbook/place.htm
#DESC: Clarified the canvas.place() method

#CITE: effbot.org/pyfaq/how-do-i-generate-random-numbers-in-python
#DESC: Clarification on how to create random numbers
    
