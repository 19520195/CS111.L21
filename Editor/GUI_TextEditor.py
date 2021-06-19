from tkinter import *

class TextEditor:
    def __init__(self, app):
        self.text_frame = Frame(app)

        self.index = Text(self.text_frame, wrap=NONE, font=("Consolas", 16), background="#2d2d2d", fg ="#FFFFFF", width=3)
        self.index.insert(1.0, " 1\n 2\n .\n .")

        self.index.configure(selectbackground=self.index.cget('bg'), state="disabled")
        self.index.pack(side=LEFT, expand=True)

        # Vertical (y) Scroll Bar
        self.yscrollbar = Scrollbar(self.text_frame, background='#F0F1F2')
        self.yscrollbar.pack(side=RIGHT, fill=Y)

        self.text_editor = Text(self.text_frame, wrap=NONE, relief=FLAT, font=("Consolas", 16), background="#2d2d2d", fg ="#FFFFFF", yscrollcommand=self.yscrollbar.set, undo=True)
        self.text_editor.config(tabs=4, insertofftime=0, insertbackground="Red", insertwidth=4)
        self.text_editor.pack(side=LEFT, fill=BOTH, expand=True)

        self.yscrollbar.config(command=self.text_editor.yview)
