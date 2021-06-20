from tkinter import *
from tkinter.filedialog import *

BAREBONE_FILETYPE = list([
    ("Barebones", "*.bb"),
    ("All files", "*.*"),
])

def SaveFile(filepath, content) -> None:
    with open(filepath, "w") as fs:
        fs.write(content)

def AskOpenFile(callback) -> None:
    filepath = askopenfilename(title="Select file", filetypes=BAREBONE_FILETYPE)
    with open(filepath, "r") as fs:
        callback(filepath, fs.read())

def AskSaveFile(content, callback) -> None:
    filepath = asksaveasfilename(title="Save file", filetypes=BAREBONE_FILETYPE)
    SaveFile(filepath, content)
    callback(filepath)
