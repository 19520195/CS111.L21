from tkinter import *
from .Textbase import Textbase

class Output(Textbase):
    def __init__(self, app):
        self.frame = Frame(app)
        self.text = Text(self.frame, wrap=CHAR, font=("Consolas", 16), background="#2d2d2d", fg ="#FFFFFF", height=4.5)
        self.text.config(tabs=4, insertofftime=0, insertbackground="Red", insertwidth=4)
        self.text.insert(1.0, "--- Your stdout will be displayed here --- ")
        self.text.configure(state="disabled")
        self.text.pack(side=LEFT, fill=X, pady=1, expand=True)

    def render(self):
        self.frame.pack(side=TOP, fill=BOTH)
