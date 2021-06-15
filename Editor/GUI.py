import os
from tkinter.ttk import *
from tkinter import *
from tkinter import font, colorchooser, filedialog, messagebox
from typing import Counter
from GUI_ICONS import Icons
from GUI_Output import Output
from GUI_Tool_Bar import Tool_Bar
from GUI_Main_Menu import Main_Menu
from GUI_Text_Editor import Text_Editor

main_path = os.path.dirname(os.path.realpath(__file__))
print(main_path)


main_application = Tk()
main_application.geometry("1360x900")
main_application.title("Barebones editor")

icons = Icons(main_path,main_application)

text_output = Output(main_application)

text_editor = Text_Editor(main_application)

main_menu = Main_Menu(main_application, text_editor.text_editor, text_output, icons)

tool_bar = Tool_Bar(main_application, text_editor.text_editor)


tool_bar.tool_bar.pack(side = TOP, fill = X)
text_output.text_frame.pack(side = BOTTOM , fill = BOTH, expand = True)
text_editor.text_frame.pack(side = BOTTOM , fill = BOTH, expand = True)

main_application.mainloop()
