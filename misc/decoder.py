"""******************************************************************************
 *r
 * Name:	Jack Scacco
 *
 * Date:	10-6-17
 *
 * Assignment: Decode FEZ lanuguage!	
 *
 * Purpose:	
 *
 *****************************************************************************"""
if __name__ == "__main__":
    main()

def generateCipher():
    cipher = [26]
    letters = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
               't', 'u', 'v', 'w', 'x', 'y', 'x', 'y', 'z']

    for c1 in letters:
        for num1 in range(0, 26):
            cipher[num1] = c1
            for c2 in letters[1:]:
                for num2 in range(1, 26):
                    cipher[num2] = c2
                    for c3 in letters[2:]:
                        for num3 in range(2, 26):
                            cipher[num3] = c3
                            for c4 in letters[3:]:
                                for num4 in range(3, 26):
                                    cipher[num4] = c4
                                    for c5 in letters[4:]:
                                        for num5 in range(4, 26):
                                            cipher[num5] = c5
                                            for c6 in letters[5:]:
                                                for num6 in range(5, 26):
                                                    cipher[num6] = c6
                                                    for c7 in letters[6:]:
                                                        for num7 in range(6, 26):
                                                            cipher[num7] = c7
                                                            for c8 in letters[7:]:
                                                                for num8 in range(7, 26):
                                                                    cipher[num8] = c8
                                                                    for c9 in letters[8:]:
                                                                        for num9 in range(8, 26):
                                                                            cipher[num9] = c9
                                                                            for c10 in letters[9:]:
                                                                                for num10 in range(9, 26):
                                                                                    cipher[num10] = c10
                                                                                    for c11 in letters[10:]:
                                                                                        for num11 in range(10, 26):
                                                                                            cipher[num11] = c11
                                                                                            for c12 in letters[11:]:
                                                                                                for num12 in range(11, 26):
                                                                                                    cipher[num12] = c12
                                                                                                    for c13 in letters[12:]:
                                                                                                        for num13 in range(12, 26):
                                                                                                            cipher[num13] = c13
                                                                                                            for c14 in letters[13:]:
                                                                                                                for num14 in range(13, 26):
                                                                                                                    cipher[num14] = c14
                                                                                                                    for c15 in letters[14:]:
                                                                                                                        for num15 in range(14, 26):
                                                                                                                            cipher[num15] = c15
                                                                                                                            for c16 in letters[15:]:
                                                                                                                                for num16 in range(15, 26):
                                                                                                                                    cipher[num16] = c16
                                                                                                                                    for c17 in letters[16:]:
                                                                                                                                        for num17 in range(16, 26):
                                                                                                                                            cipher[num17] = c17
                                                                                                                                            for c18 in letters[17:]:
                                                                                                                                                for num18 in range(17, 26):
                                                                                                                                                    cipher[num18] = c18
                                                                                                                                                    for c19 in letters[18:]:
                                                                                                                                                        for num19 in range(18, 26):
                                                                                                                                                            cipher[num19] = c19
                                                                                                                                                            for c20 in letters[19:]:
                                                                                                                                                                for num20 in range(19, 26):
                                                                                                                                                                    cipher[num20] = c20
                                                                                                                                                                    for c21 in letters[20:]:
                                                                                                                                                                        for num21 in range(20, 26):
                                                                                                                                                                            cipher[num21] = c21
                                                                                                                                                                            for c22 in letters[21:]:
                                                                                                                                                                                for num22 in range(21, 26):
                                                                                                                                                                                    cipher[num22] = c22
                                                                                                                                                                                    for c23 in letters[22:]:
                                                                                                                                                                                        for num23 in range(22, 26):
                                                                                                                                                                                            cipher[num23] = c23
                                                                                                                                                                                            for c24 in letters[23:]:
                                                                                                                                                                                                for num24 in range(23, 26):
                                                                                                                                                                                                    cipher[num24] = c24
                                                                                                                                                                                                    for c25 in letters[24:]:
                                                                                                                                                                                                        for num25 in range(24, 26):
                                                                                                                                                                                                            cipher[num25] = c25
                                                                                                                                                                                                            for c26 in letters[25:]:
                                                                                                                                                                                                                for num26 in range(25, 26):
                                                                                                                                                                                                                    cipher[num26] = c26
                                                                                                                                                                                                                    print(cipher)
                                                                                                                                                                                                                    
                                
                
            

def main():
  

    message = [1, 5, 6, 9, 1, 5, 13, 17, 21, 3, 2, 21, 13, 9, 18, 22, 14, 22, 20, 20, 4, 5, 18, 21, 24,  17, 1, 22, 2, 1, 5, 17, 5, 1, 21, 14, 9, 17, 5, 18, 21, 24, 11, 21, 5, 12, 14, 17, 21, 3, 11, 22, 3, 23, 9, 12, 5, 12, 21, 11, 5, 2, 1, 22, 3, 11, 12, 21, 11, 5, 21, 3, 5, 1, 5, 17, 5, 16, 24, 12]

    generateCipher()

    
