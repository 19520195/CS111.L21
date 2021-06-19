from tkinter import *

class Output:
    def __init__(self, app):
        self.frame = Frame(app)
        self.output_space = Text(self.frame, wrap=CHAR, font=("Consolas", 16), background="#2d2d2d", fg ="#FFFFFF", height=4.5)
        self.output_space.config(tabs=4, insertofftime=0, insertbackground="Red", insertwidth=4)
        self.output_space.insert(1.0, "--- Your stdout will be displayed here --- ")
        self.output_space.configure(state="disabled")
        self.output_space.pack(side=LEFT, fill=X, pady=1, expand=True)

    def render(self):
        self.frame.pack(side=TOP, fill=BOTH)
