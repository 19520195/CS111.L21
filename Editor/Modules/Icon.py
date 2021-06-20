from os.path import *
from tkinter import PhotoImage

class Icon:
    def __init__(self) :
        self.path = abspath(join(dirname(realpath(__file__)), "..", "Icons"))
        self.icon = dict({
            "new"       : PhotoImage(file=join(self.path, "new.png")),
            "open"      : PhotoImage(file=join(self.path, "open.png")),
            "save"      : PhotoImage(file=join(self.path, "save.png")),
            "save_as"   : PhotoImage(file=join(self.path, "save_as.png")),
            "exit"      : PhotoImage(file=join(self.path, "exit.png")),
            "copy"      : PhotoImage(file=join(self.path, "copy.png")),
            "paste"     : PhotoImage(file=join(self.path, "paste.png")),
            "cut"       : PhotoImage(file=join(self.path, "cut.png")),
            "clear_all" : PhotoImage(file=join(self.path, "clear_all.png")),
            "find"      : PhotoImage(file=join(self.path, "find.png")),
            "undo"      : PhotoImage(file=join(self.path, "undo.png")),
            "redo"      : PhotoImage(file=join(self.path, "redo.png")),
            "run"       : PhotoImage(file=join(self.path, "run.png")),

            "light_default": PhotoImage(file=join(self.path, "light_default.png")),
            "light_plus"   : PhotoImage(file=join(self.path, "light_plus.png")),
            "dark"         : PhotoImage(file=join(self.path, "dark.png")),
            "red"          : PhotoImage(file=join(self.path, "red.png")),
            "monokai"      : PhotoImage(file=join(self.path, "monokai.png")),
            "night"        : PhotoImage(file=join(self.path, "night_blue.png"))
        })

    def get(self, name):
        return self.icon[name]
