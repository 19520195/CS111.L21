from tkinter import *

class TextEditor:
    def __init__(self, app):
        self.frame = Frame(app)

        self.index_column = Text(self.frame, wrap=NONE, font=("Consolas", 16), background="#2d2d2d", fg ="#FFFFFF", width=3, height=0)
        self.index_column.insert(1.0, "1")
        self.index_column.configure(selectbackground=self.index_column.cget("bg"), state=DISABLED)
        self.coding_scrollbar = Scrollbar(self.frame, background='#F0F1F2')

        self.coding_scrollbar.pack(side=RIGHT, fill=Y)

        self.coding_space = Text(self.frame, wrap=NONE, font=("Consolas", 16), background="#2d2d2d", fg ="#FFFFFF", yscrollcommand=self.coding_scrollbar.set, undo=True, height=0)
        self.coding_space.config(tabs=4, insertbackground="Red", insertwidth=4)

        self.coding_scrollbar.config(command=self.coding_space.yview)
        self.index_column.pack(side=LEFT, fill=Y)
        self.coding_space.pack(side=LEFT, fill=BOTH, expand=True)

    def render(self):
        self.frame.pack(side=TOP, fill=BOTH, expand=True, pady=1)
