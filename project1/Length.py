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
INCHES_PER_FOOT = 12
class Length:
    """A class to represent composite lengths in a useful way."""
    def __init__(self, feet, inches):
        """The constructor. Feet and inches may be any int value."""
        self._in = inches + feet*INCHES_PER_FOOT
    
    def setFeet(self, feet):
        """Updates number of feet in the length. May  be any int value."""
        self._in %= INCHES_PER_FOOT
        self._in += INCHES_PER_FOOT*feet

    def setInches(self, inches):
        """ Updates number of inches in the Length. May be any int value."""
        self._in -= self._in % INCHES_PER_FOOT
        self._in += inches
    
    def getFeet(self):
        """Reutrns the number of feet in the Length."""
        return self._in // INCHES_PER_FOOT
        
    def getInches(self):
        """Returns the number of inches in the Length."""
        return self._in % INCHES_PER_FOOT

    def add(self, other):
        """Adds another Length to this one, returning a new Length."""
        feet = other.getFeet()+ self.getFeet()
        inches = other.getInches() + self.getInches()
        newL = Length(feet, inches)
        return newL

    def __add__(self, other):
        """overloaded operator that enables the use of + with Lengths."""
        return self.add(other)

    def toString(self):
        """Converts a Length to a string. Format: 10 feet, 1 inch"""
        if self.getFeet() == 1:
            fF = "foot"
        else:
            fF = "feet"

        if self.getInches() == 1:
            iF = "inch"
        else:
            iF = "inches"

        return  str(self.getFeet())+" "+fF+", "+str(self.getInches())+" "+iF

    def __str__(self):
        """Overloaded operator that enables the use of  string contexts."""
        return self.toString()

def main():
    """main function"""
    len1 = Length(1, 3)
    len2 = Length(10, 10)
    len3 = len1.add(len2)
    print(len1)
    print(len2)
    print(len3)

if __name__ == "__main__":
    main()
