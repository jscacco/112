"""
 ******************************************************************************
 *
 * Name:	
 *
 * Date:	
 *
 * Assignment:	
 *
 * Purpose: test out tkinter	
 *
 *****************************************************************************/
"""
 
import tkinter as tk

def doit():
    print("Don't worry, it's done.")

class Square:
    def __init__(self, window, x, y):
        self._canvas = tk.Canvas(window, background="#D2D2D2", width=50,
                                 height=50)
        self._canvas.place(x=x, y=y)
        self._rect = self._canvas.create_rectangle(1, 1, 50, 50)
        


def start():
    window = tk.Tk()
    window.geometry("400x400")

    
    quitButton = tk.Button(window, text="Quit", command=window.destroy)
    quitButton.place(x=330, y=365)

    doitButton = tk.Button(window, text="Do it!", command=doit)
    doitButton.place(x=10, y=365)

    mainMenu = tk.Menu(window)
    fileMenu = tk.Menu(mainMenu)
    fileMenu.add_command(label="Quit", command=window.destroy)
    fileMenu.add_separator()
    mainMenu.wm(x=0, y=0)

    window.mainloop()
    print("Done")

if __name__ == "__main__":
    start()
