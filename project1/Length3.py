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
        self._in = inches + feet*12
    
    def setFeet(self, feet):
        """Updates number of feet in the length. May  be any int value."""
        self._in %= 12
        self._in += 12*feet

    def setInches(self, inches):
        """ Updates number of inches in the Length. May be any int value."""
        self._in -= self._in % 12
        self._in += inches
    
    def getFeet(self):
        """Reutrns the number of feet in the Length."""
        return self._in // 12
        
    def getInches(self):
        """Returns the number of inches in the Length."""
        return self._in % 12

    def add(self, other):
        """Adds another Length to this one, returning a new Length."""
        self._in += (other.getInches() + other.getFeet())
        return (self.getFeet, self.getInches)

    def __add__(self, other):
        """overloaded operator that enables the use of + with Lengths."""
        return self.add(other)

    def toString(self):
        """Converts a Length to a string. Format: 10 feet, 1 inch"""
        return  str(self.getFeet()) +" feet, "+str(self.getInches())+" inches"

    def __str__(self):
        """Overloaded operator that enables the use of  string contexts."""
        return self.toString()

def main():
    """main function"""
    len1 = Length(6, 3)
    len2 = Length(10, 10)
    len1.add(len2)
    print(len1.toString())

if __name__ == "__main__":
    main()
