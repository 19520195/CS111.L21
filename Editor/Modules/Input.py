from tkinter import *
from .Textbase import Textbase

class Input(Textbase):
    def __init__(self, app):
        self.frame = Frame(app)

        self.index = Text(self.frame, wrap=NONE, font=("Consolas", 16), background="#2d2d2d", fg ="#FFFFFF", width=3, height=0)
        self.index.insert(1.0, "1")
        self.index.configure(selectbackground=self.index.cget("bg"), state=DISABLED)

        self.scrollbar = Scrollbar(self.frame, background='#F0F1F2')
        self.scrollbar.pack(side=RIGHT, fill=Y)

        self.text = Text(self.frame, wrap=NONE, font=("Consolas", 16), background="#2d2d2d", fg ="#FFFFFF", yscrollcommand=self.scrollbar.set, undo=True, height=0)
        self.text.config(tabs=4, insertbackground="Red", insertwidth=4)

        self.index.pack(side=LEFT, fill=Y)
        self.text.pack(side=LEFT, fill=BOTH, expand=True)
        self.scrollbar.config(command=self.text.yview)

    def render(self):
        self.frame.pack(side=TOP, fill=BOTH, expand=True, pady=1)
