from tkinter import *

class Output:
    def __init__(self, app):
        self.text_frame = Frame(app)

        self.text_output = Text(self.text_frame, wrap=NONE, relief=FLAT, font=("Consolas", 16), background="#2d2d2d", fg ="#FFFFFF", height=5)
        self.text_output.config(tabs=4, insertofftime=0, insertbackground="Red", insertwidth=4)
        self.text_output.pack(side=LEFT, fill=BOTH, pady=1, expand=True)

        self.text_output.insert(1.0, "--- Your stdout will be displayed here --- ")
        self.text_output.configure(state="disabled")
