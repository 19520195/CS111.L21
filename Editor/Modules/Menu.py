import tkinter

from .Icon import Icon
from tkinter import LEFT

class Menu:
    def __init__(self, app, text_editor) :
        self.icon = Icon()
        self.menu = tkinter.Menu()
        theme_choice = tkinter.StringVar()

        sub_file  = tkinter.Menu(self.menu, tearoff=False)
        sub_edit  = tkinter.Menu(self.menu, tearoff=False)
        sub_theme = tkinter.Menu(self.menu, tearoff=False)
        sub_go    = tkinter.Menu(self.menu, tearoff=False)

        def change_theme():
            chosen_theme = theme_choice.get()
            color_tuple = color_dict.get(chosen_theme)
            fg_color, bg_color = color_tuple[0], color_tuple[1]
            text_editor.config(background=bg_color, fg=fg_color)

        color_icons = (self.icon.get("light_default"), self.icon.get("light_plus"), self.icon.get("dark"), self.icon.get("red"), self.icon.get("monokai"), self.icon.get("night"))

        color_dict = {
            "Light Default": ("#000000", "#ffffff"),
            "Light Plus": ("#474747", "#e0e0e0"),
            "Dark": ("#FFFFFF", "#2d2d2d"),
            "Pink": ("#2d2d2d", "#ffe8e8"),
            "Monokai": ("#474747", "#d3b774"),
            "Night Blue": ("#ededed", "#6b9dc2")
        }

        count = 0
        for i in color_dict:
            sub_theme.add_radiobutton(label=i, image=color_icons[count], variable=theme_choice, compound=LEFT, command=change_theme)
            count += 1

        sub_file.add_command(label="New"         , image=self.icon.get("new")      , compound=LEFT, accelerator="Ctrl+N"         , command=app.file_new   )
        sub_file.add_command(label="Open"        , image=self.icon.get("open")     , compound=LEFT, accelerator="Ctrl+O"         , command=app.file_open  )
        sub_file.add_command(label="Save"        , image=self.icon.get("save")     , compound=LEFT, accelerator="Ctrl+S"         , command=app.file_save  )
        sub_file.add_command(label="Save as"     , image=self.icon.get("save_as")  , compound=LEFT, accelerator="Ctrl+Alt+S"     , command=app.file_saveas)

        sub_edit.add_command(label="Copy"        , image=self.icon.get("copy")     , compound=LEFT, accelerator="Ctrl+C"         , command=app.input.text.event_generate("<Control C>"))
        sub_edit.add_command(label="Paste"       , image=self.icon.get("paste")    , compound=LEFT, accelerator="Ctrl+V"         , command=app.input.text.event_generate("<Control V>"))
        sub_edit.add_command(label="Cut"         , image=self.icon.get("cut")      , compound=LEFT, accelerator="Ctrl+X"         , command=app.input.text.event_generate("<Control X>"))
        sub_edit.add_command(label="Clear all"   , image=self.icon.get("clear_all"), compound=LEFT, accelerator="Ctrl+Alt+X"     , command=app.input.clear     )
        sub_edit.add_command(label="Undo"        , image=self.icon.get("undo")     , compound=LEFT, accelerator="Ctrl+Z"         , command=app.code_undo       )
        sub_edit.add_command(label="Redo"        , image=self.icon.get("redo")     , compound=LEFT, accelerator="Ctrl+Y"         , command=app.code_redo       )
        sub_edit.add_command(label="Find"        , image=self.icon.get("find")     , compound=LEFT, accelerator="Ctrl+F"         , command=app.code_find       )
        sub_edit.add_command(label="Comment"                                   , compound=LEFT, accelerator="Control-Shift-C", command=app.code_comment    )
        sub_edit.add_command(label="Undo comment"                              , compound=LEFT, accelerator="Control-Shift-X", command=app.code_undocomment)

        sub_go.add_command(label="Execute"      , image=self.icon.get("run")      , compound=LEFT, accelerator="F9"             , command=app.code_execute)
        sub_go.add_command(label="Compile"      , image=self.icon.get("run")      , compound=LEFT, accelerator="Ctrl+F9"        , command=app.code_compile)


        self.menu.add_cascade(label="File" , menu=sub_file )
        self.menu.add_cascade(label="Edit" , menu=sub_edit )
        self.menu.add_cascade(label="Theme", menu=sub_theme)
        self.menu.add_cascade(label="Go"   , menu=sub_go   )

    def render(self, app) -> None:
        app.config(menu=self.menu)

