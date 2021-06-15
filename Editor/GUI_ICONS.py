import os
from tkinter import *

class Icons:
    def __init__(self,main_path,main_application) :
        self.new = PhotoImage(file=os.path.join(main_path, "Icons", "new.png"))
        self.open = PhotoImage(file=os.path.join(main_path, "Icons", "open.png"))
        self.save = PhotoImage(file=os.path.join(main_path, "Icons", "save.png"))
        self.save_as = PhotoImage(file=os.path.join(main_path, "Icons", "save_as.png"))
        self.exit = PhotoImage(file=os.path.join(main_path, "Icons", "exit.png"))

        self.copy = PhotoImage(file=os.path.join(main_path, "Icons", "copy.png"))
        self.paste = PhotoImage(file=os.path.join(main_path, "Icons", "paste.png"))
        self.cut = PhotoImage(file=os.path.join(main_path, "Icons", "cut.png"))
        self.clear_all = PhotoImage(file=os.path.join(main_path, "Icons", "clear_all.png"))
        self.find = PhotoImage(file=os.path.join(main_path, "Icons", "find.png"))
        self.undo = PhotoImage(file=os.path.join(main_path, "Icons", "undo.png"))
        self.redo = PhotoImage(file=os.path.join(main_path, "Icons", "redo.png"))

        self.run = PhotoImage(file=os.path.join(main_path, "Icons", "run.png"))

        self.light_default = PhotoImage(file=os.path.join(main_path, "Icons", "light_default.png"))
        self.light_plus = PhotoImage(file=os.path.join(main_path, "Icons", "light_plus.png"))
        self.dark = PhotoImage(file=os.path.join(main_path, "Icons", "dark.png"))
        self.red = PhotoImage(file=os.path.join(main_path, "Icons", "red.png"))
        self.monokai = PhotoImage(file=os.path.join(main_path, "Icons", "monokai.png"))
        self.night = PhotoImage(file=os.path.join(main_path, "Icons", "night_blue.png"))
