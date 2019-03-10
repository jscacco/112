"""
/******************************************************************************
 *
 * Name: Jack Scacco	
 *
 * Date: 8-29-17	
 *
 * Assignment:	Project 1
 *
 * Purpose: To create and manipulate a "Length" class
 *
 *****************************************************************************/
"""
class Length:
    """A class to represent composite lengths in a useful way."""
    def __init__(self, feet, inches):
        """The constructor. Feet and inches may be any int value."""
        self._ft = feet
        self._in = inches

    def checkFormat(self):
        """checks if the inches are less than 12 and corrects if not"""
        if self._in > 12:
            self._ft = (self._in //  12)
            self._in %= 12
    
    def setFeet(self, feet):
        """Updates number of feet in the length. May  be any int value."""
        self._ft = feet

    def setInches(self, inches):
        """ Updates number of inches in the Length. May be any int value."""
        self._in = inches
        self.checkFormat()
    
    def getFeet(self):
        """Reutrns the number of feet in the Length."""
        self.checkFormat()
        return (self._ft)
        
    def getInches(self):
        """Returns the number of inches in the Length."""
        self.checkFormat()
        return (self._in)

    def add(self, other):
        """Adds another Length to this one, returning a new Length."""
        self._ft += other.getFeet()
        self._in += other.getInches()
        self.checkFormat()
        return (self._ft, self._in)

    def __add__(self, other):
        """overloaded operator that enables the use of + with Lengths."""
        return self.add(other)

    def toString(self):
        """Converts a Length to a string. Format: 10 feet, 1 inch"""
        self.checkFormat()
        return str(self._ft) + " feet, " + str(self._in)  + " inches"

    def __str__(self):
        """Overloaded operator that enables the use of  string contexts."""
        return self.toString()

def main():
    """main function"""
    len1 = Length(6, 3)
    len2 = Length(0, 15)
    print(len1.toString())
    print(len2)
    

if __name__ == "__main__":
    main()

# CITE: Python Essential Reference
# DESC: Reference and clarification of numerous functions and their uses
