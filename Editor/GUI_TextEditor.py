from tkinter import *

class TextEditor:
    def __init__(self, app):
        self.text_frame = Frame(app)
        # Horizontal (x) Scroll bar
        self.xscrollbar = Scrollbar(self.text_frame, orient=HORIZONTAL)
        self.xscrollbar.pack(side=BOTTOM, fill=X)

        # Vertical (y) Scroll Bar
        self.yscrollbar = Scrollbar(self.text_frame)
        self.yscrollbar.pack(side=RIGHT, fill=Y)

        self.text_editor = Text(self.text_frame, wrap=NONE, relief=FLAT, font=("Consolas", 16), background="#2d2d2d", fg ="#FFFFFF", xscrollcommand=self.xscrollbar.set, yscrollcommand=self.yscrollbar.set, undo=True)
        self.text_editor.config(tabs=4, insertofftime=0, insertbackground="Red", insertwidth=4)
        self.text_editor.pack(fill=BOTH, padx=5, pady=5, expand=True)

        self.xscrollbar.config(command=self.text_editor.xview)
        self.yscrollbar.config(command=self.text_editor.yview)
