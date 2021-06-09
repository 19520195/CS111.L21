from tkinter import *

class Output:
    def __init__(self, main_application):
        self.text_frame = Frame(main_application)
        # Horizontal (x) Scroll bar
        self.xscrollbar = Scrollbar(self.text_frame, orient = HORIZONTAL)
        self.xscrollbar.pack(side = BOTTOM, fill = X)

        # Vertical (y) Scroll Bar
        self.yscrollbar = Scrollbar(self.text_frame)
        self.yscrollbar.pack(side = RIGHT, fill = Y)

        self.text_editor = Text(self.text_frame, wrap = NONE, relief = FLAT, font = ("Consolas", 16), background = "#2d2d2d", fg ="#FFFFFF", xscrollcommand = self.xscrollbar.set, yscrollcommand = self.yscrollbar.set, height = 7)
        self.text_editor.config(tabs = 4, insertofftime = 0, insertbackground = "Red", insertwidth = 4)
        self.text_editor.pack(fill = BOTH, padx = 5, pady = 5, expand = True)

        self.xscrollbar.config(command = self.text_editor.xview)
        self.yscrollbar.config(command = self.text_editor.yview)

        self.text_editor.insert(1.0,"Output:\n")