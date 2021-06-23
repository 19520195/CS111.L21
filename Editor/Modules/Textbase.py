from tkinter import *

class Textbase:
    def get(self):
        return self.text.get(1.0, END)

    def set(self, content):
        self.text.delete(1.0, END)
        self.text.insert(END, content)

    def clear(self):
        self.text.delete(1.0, END)
