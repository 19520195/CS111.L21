import os
from tkinter import *
from tkinter.ttk import *
from GUI_Icons import Icons
from GUI_Output import Output
from GUI_ToolBar import ToolBar
from GUI_MainMenu import MainMenu
from GUI_TextEditor import TextEditor

app = Tk()
app.geometry("800x600")
app.title("Barebones editor")

icons = Icons(os.path.dirname(os.path.realpath(__file__)), app)

text_output = Output(app)
text_editor = TextEditor(app)
main_menu = MainMenu(app, text_editor.text_editor, text_output, icons)

tool_bar = ToolBar(app, text_editor.text_editor)
tool_bar.tool_bar.pack(side=TOP, fill=X)

text_output.text_frame.pack(side=BOTTOM, fill=BOTH, expand=True)
text_editor.text_frame.pack(side=BOTTOM, fill=BOTH, expand=True)

app.mainloop()
