from tkinter import *
from tkinter.ttk import *
from tkinter import font

class Tool_Bar:
    def __init__(self, main_application, text_editor):
        self.tool_bar = Label(main_application)
        self.tool_bar.pack(side = TOP, fill = X)

        ##font box
        self.font_tuple = font.families()
        self.font_family = StringVar()
        self.font_box = Combobox(self.tool_bar, width = 30, textvariable = self.font_family, state = "readonly")
        self.font_box["values"] = self.font_tuple
        self.font_box.current(self.font_tuple.index("Consolas"))
        self.font_box.grid(row = 0, column = 0, padx = 5)

        #size box
        self.size_var = IntVar()
        self.font_size = Combobox(self.tool_bar, width = 14, textvariable = self.size_var, state = "readonly")
        self.font_size["values"] = tuple(range(8, 20, 1))
        self.font_size.current(8)
        self.font_size.grid(row = 0, column = 1, padx = 5)
        
        def change_font(main_application):
            text_editor.config(font = (self.font_family.get(), self.size_var.get()))

        def change_fontsize(main_application):
            text_editor.config(font = (self.font_family.get(), self.size_var.get()))

        self.font_box.bind("<<ComboboxSelected>>", change_font)
        self.font_size.bind("<<ComboboxSelected>>", change_fontsize)
 