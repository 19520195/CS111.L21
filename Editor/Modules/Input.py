from tkinter import *
from .Textbase import Textbase

class Input(Textbase):
    def __init__(self, app):
        self.frame = Frame(app.app)

        self.scrollbar = Scrollbar(self.frame, background='#F0F1F2')
        self.scrollbar.pack(side=RIGHT, fill=Y)

        self.index = Text(self.frame, wrap=CHAR, font=app.font, fg="#237893", bg=app.color["bg"], width=4, height=0, highlightthickness=0, bd=0)
        self.index.insert(1.0, "  1 ")
        self.index.config(selectbackground=self.index.cget("bg"), state=DISABLED)

        self.text = Text(self.frame, wrap=NONE, font=app.font, fg=app.color["fg"], bg=app.color["bg"], undo=True, height=0, highlightthickness=0, bd=0)
        self.text.config(tabs=4, insertbackground=app.color["fg"], insertwidth=1)

        def scroll_si(X, Y):
            self.scrollbar.set(X, Y)
            self.index.yview_moveto(X)

        def scroll_st(X, Y):
            self.scrollbar.set(X, Y)
            self.text.yview_moveto(X)

        def scroll_ti(X, Y):
            self.text.yview(X, Y)
            self.index.yview(X, Y)

        self.text     .config(yscrollcommand=scroll_si)
        self.index    .config(yscrollcommand=scroll_st)
        self.scrollbar.config(       command=scroll_ti)

        self.index.pack(side=LEFT, fill=Y)
        self.text.pack(side=LEFT, fill=BOTH, expand=True)

    def render(self):
        self.frame.pack(side=TOP, fill=BOTH, expand=True, pady=(2, 0))
