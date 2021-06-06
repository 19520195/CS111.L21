import os
from tkinter.ttk import *
from tkinter import *
from tkinter import font, colorchooser, filedialog, messagebox
from typing import Counter

url = ""           #GLOBAL VARIABLE
main_path = os.path.dirname(os.path.realpath(__file__))
print(main_path)

main_application = Tk()
main_application.geometry("1200x800")
main_application.title("Barebones editor")

def config_color(keys, clr):
    text_write_code.tag_delete(clr)
    for word in keys :
        start_pos = "1.0"
        while True:
            start_pos = text_write_code.search(word, start_pos, stopindex = END)
            if not start_pos:
                break
            end_pos = f"{start_pos}+{len(word)}c"
            text_write_code.tag_add(clr, start_pos, end_pos)
            start_pos = end_pos
            text_write_code.tag_config(clr, foreground = clr)


def auto_color(event = None):
    control_word = ("clear ", "while ", "not ", " do", "end;", "end ")
    builtin_word = ("export ", "incr ", "decr ", "assign ")
    digit_word   = [str(_) for _ in range(10)]

    config_color(control_word, "#40aedf")
    config_color(builtin_word, "#eaaa37")
    config_color(digit_word  , "#88cc88")

#################### MAIN MENU ########################
main_menu = Menu()

#------------------file tab-------------------------#
new_icon = PhotoImage(file = "./Icons/new.png")
open_icon = PhotoImage(file = "./Icons/open.png")
save_icon = PhotoImage(file = "./Icons/save.png")
save_as_icon = PhotoImage(file = "./Icons/save_as.png")
exit_icon = PhotoImage(file = "./Icons/exit.png")

file = Menu(main_menu, tearoff = False)

#----------------------------edit tab----------------------------#
copy_icon = PhotoImage(file = "./Icons/copy.png")
paste_icon = PhotoImage(file = "./Icons/paste.png")
cut_icon = PhotoImage(file = "./Icons/cut.png")
clearall_icon = PhotoImage(file = "./Icons/clear_all.png")
find_icon = PhotoImage(file = "./Icons/find.png")
undo_icon = PhotoImage(file = "./Icons/undo.png")
redo_icon = PhotoImage(file = "./Icons/redo.png")

edit = Menu(main_menu, tearoff = False)

#-------------------------------window---------------------#
light_default_icon = PhotoImage(file = "./Icons/light_default.png")
light_plus_icon = PhotoImage(file = "./Icons/light_plus.png")
dark_icon = PhotoImage(file = "./Icons/dark.png")
red_icon = PhotoImage(file = "./Icons/red.png")
monokai_icon = PhotoImage(file = "./Icons/monokai.png")
night_icon = PhotoImage(file = "./Icons/night_blue.png")

color_theme = Menu(main_menu, tearoff = False)

theme_choice = StringVar()
color_icons = (light_default_icon, light_plus_icon, dark_icon, red_icon, monokai_icon, night_icon)

color_dict = {
    "Light Default": ("#000000", "#ffffff"),
    "Light Plus": ("#474747", "#e0e0e0"),
    "Dark": ("#c4c4c4", "#2d2d2d"),
    "Pink": ("#2d2d2d", "#ffe8e8"),
    "Monokai": ("#474747", "#d3b774"),
    "Night Blue": ("#ededed", "#6b9dc2")
}

#cascade
main_menu.add_cascade(label = "File", menu = file)
main_menu.add_cascade(label = "Edit", menu = edit)
main_menu.add_cascade(label = "Color Theme", menu = color_theme)

#&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& end of Main menu &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


############################################## TOOL BAR ##########################

tool_bar = Label(main_application)
tool_bar.pack(side = TOP, fill = X)

##font box
font_tuple = font.families()
font_family = StringVar()
font_box = Combobox(tool_bar, width = 30, textvariable = font_family, state = "readonly")
font_box["values"] = font_tuple
font_box.current(font_tuple.index("Consolas"))
font_box.grid(row = 0, column = 0, padx = 5)

#size box
size_var = IntVar()
font_size = Combobox(tool_bar, width = 14, textvariable = size_var, state = "readonly")
font_size["values"] = tuple(range(8, 80, 2))
font_size.current(4)
font_size.grid(row = 0, column = 1, padx = 5)
#&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& end toolbar&&&&&&&&&&&&&&&&&&&&&&&&&&&&

########################################  TEXT EDITOR ##################################

menu_frame = Frame(main_application)
menu_frame.pack(fill = BOTH, expand = True)
# Horizontal (x) Scroll bar
xscrollbar = Scrollbar(menu_frame, orient = HORIZONTAL)
xscrollbar.pack(side = BOTTOM, fill = X)

# Vertical (y) Scroll Bar
yscrollbar = Scrollbar(menu_frame)
yscrollbar.pack(side = RIGHT, fill = Y)

text_write_code = Text(menu_frame, wrap = NONE, relief = FLAT, font = ("Consolas", 16), background = "#2d2d2d", fg ="#c4c4c4", xscrollcommand = xscrollbar.set, yscrollcommand = yscrollbar.set, undo = True)
text_write_code.config(tabs = 4, insertofftime = 0, insertbackground = "Red", insertwidth = 4)
text_write_code.pack( fill = BOTH, padx = 5, pady = 5, expand = True)

xscrollbar.config(command = text_write_code.xview)
yscrollbar.config(command = text_write_code.yview)

######## font family and font size functionality
def change_font(main_application):
    text_write_code.configure(font = (font_family.get(), size_var.get()))

def change_fontsize(main_application):
    text_write_code.configure(font = (font_family.get(), size_var.get()))

font_box.bind("<<ComboboxSelected>>", change_font)
font_size.bind("<<ComboboxSelected>>", change_fontsize)

#&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& END OF TEXT EDITOR &&&&&&&&&&&&&&&&&&&&&&&


#######################################################   main menu functionality #####################

#NEW FILE FUNCTIONALITY
def new_file(event = None):
    global url
    url = ""
    text_write_code.delete(1.0, END)
    auto_color()
    main_application.title("New file")

file.add_command(label = "New", image = new_icon, compound = LEFT, accelerator = "Ctrl+N", command = new_file)

#OPEN FUNCTIONALITY
def open_file(event = None):
    global url
    url = filedialog.askopenfilename(title = "Select File", filetypes = [("Bare Bones", "*.bb"), ("All Files", "*.*")])
    try:
        with open(url, "r") as fr:
            text_write_code.delete(1.0, END)
            text_write_code.insert(1.0, fr.read())
            auto_color()
    except FileNotFoundError:
        return
    except:
        return
    main_application.title(os.path.basename(url))
    auto_color()

file.add_command(label = "Open", image = open_icon, compound = LEFT, accelerator = "Ctrl+O", command = open_file)

def save_file(event = None):
    global url
    try:
        if url:
            content =  str(text_write_code.get(1.0, END))
            with open(url, "w", encoding = "utf-8") as fw:
                fw.write(content)
            main_application.title(os.path.basename(url))

        else:
            url = filedialog.asksaveasfilename(title = "Select File", defaultextension = ".bb", filetypes = [("Bare Bones", "*.bb"), ("All Files", "*.*")])
            fo = open(url, "w")
            code = text_write_code.get("1.0", END)
            fo.write(code)
            fo.close()
            main_application.title(os.path.basename(url))
    except:
        main_application.title(os.path.basename(url))
        return
    main_application.title(os.path.basename(url))

file.add_command(label = "Save", image = save_icon, compound = LEFT, accelerator = "Ctrl+S", command = save_file)

#save as
def save_as(event = None):
    global url
    try:
        url = filedialog.asksaveasfilename(title = "Select File", defaultextension = ".bb", filetypes = [("Bare Bones", "*.bb"), ("All Files", "*.*")])
        fo = open(url, "w")
        code = text_write_code.get("1.0", END)
        fo.write(code)
        fo.close()
        main_application.title(os.path.basename(url))
    except:
        return

file.add_command(label = "Save As", image = save_icon, compound = LEFT, accelerator = "Ctrl+Alt+S", command = save_as)

def redo(event = None) :
    text_write_code.edit_redo
    auto_color()

def undo(event = None) :
    text_write_code.edit_undo
    auto_color()

def clear_all(event = None) :
    text_write_code.delete(1.0, END)

############ find functionality
def find_func(event = None):

    def find():
        word = find_input.get()
        text_write_code.tag_remove("match", "1.0", END)
        matches = 0
        if word:
            start_pos = "1.0"
            while True:
                start_pos = text_write_code.search(word, start_pos, stopindex = END)
                if not start_pos:
                    break
                end_pos = f"{start_pos}+{len(word)}c"
                text_write_code.tag_add("match", start_pos, end_pos)
                matches +=  1
                start_pos = end_pos
                text_write_code.tag_config("match", foreground = "red", background = "yellow")

    def replace():
        word = find_input.get()
        replace_text = replace_input.get()
        content = text_write_code.get(1.0, END)
        new_content = content.replace(word, replace_text)
        text_write_code.delete(1.0, END)
        text_write_code.insert(1.0, new_content)
        auto_color()

    find_dialogue = Toplevel()
    find_dialogue.geometry("450x250+500+200")
    find_dialogue.title("Find")
    find_dialogue.resizable(0, 0)

    ## frame
    find_frame = LabelFrame(find_dialogue, text = "Find/Replace")
    find_frame.pack(pady = 20)

    ## labels
    text_find_label = Label(find_frame, text = "Find : ")
    text_replace_label = Label(find_frame, text =  "Replace")

    ## entry
    find_input = Entry(find_frame, width = 30)
    replace_input = Entry(find_frame, width = 30)

    ## button
    find_button = Button(find_frame, text = "Find", command = find)
    replace_button = Button(find_frame, text =  "Replace", command = replace)

    ## label grid
    text_find_label.grid(row = 0, column = 0, padx = 4, pady = 4)
    text_replace_label.grid(row = 1, column = 0, padx = 4, pady = 4)

    ## entry grid
    find_input.grid(row = 0, column = 1, padx = 4, pady = 4)
    replace_input.grid(row = 1, column = 1, padx = 4, pady = 4)

    ## button grid
    find_button.grid(row = 2, column = 0, padx = 8, pady = 4)
    replace_button.grid(row = 2, column = 1, padx = 8, pady = 4)

    find_dialogue.mainloop()

edit.add_command(label = "Copy", image = copy_icon, compound = LEFT, accelerator = "Ctrl+C", command = lambda:text_write_code.event_generate("<Control c>"))
edit.add_command(label = "Paste", image = paste_icon, compound = LEFT, accelerator = "Ctrl+V", command = lambda:text_write_code.event_generate("<Control v>"))
edit.add_command(label = "Cut", image = cut_icon, compound = LEFT, accelerator = "Ctrl+X", command = lambda:text_write_code.event_generate("<Control x>"))
edit.add_command(label = "Clear all", image = clearall_icon, compound = LEFT, accelerator = "Ctrl+Alt+X", command = lambda:text_write_code.delete(1.0, END))
edit.add_command(label = "Undo", image = undo_icon, compound = LEFT, accelerator = "Ctrl+Z", command = undo)
edit.add_command(label = "Redo", image = redo_icon, compound = LEFT, accelerator = "Ctrl+Y", command = redo)
edit.add_command(label = "Find", image = find_icon, compound = LEFT, accelerator = "Ctrl+F", command = find_func)

## color theme
def change_theme():
    chosen_theme = theme_choice.get()
    color_tuple = color_dict.get(chosen_theme)
    fg_color, bg_color = color_tuple[0], color_tuple[1]
    text_write_code.config(background = bg_color, fg = fg_color)

count = 0
for i in color_dict:
    color_theme.add_radiobutton(label = i, image = color_icons[count], variable = theme_choice, compound = LEFT, command = change_theme)
    count += 1

main_application.config(menu = main_menu)
main_application.bind("<Control-n>", new_file)
main_application.bind("<Control-o>", open_file)
main_application.bind("<Control-s>", save_file)
main_application.bind("<Control-Alt-s>", save_as)

main_application.bind("<Key>", auto_color)
main_application.bind("<Control-z>", undo)
main_application.bind("<Control-y>", redo)
main_application.bind("<Control-f>", find_func)
main_application.bind("<Control-Alt-x>", clear_all)

def handle_button_run_code() :
    # code = text_write_code.get("1.0", END)
    return

run_frame = Frame(main_application)
run_frame.pack(side = RIGHT)

bttRunCode = Button(run_frame, text = "Run", font = ("Consolas", 18), command = handle_button_run_code)
bttRunCode.pack(side = RIGHT, padx = 5, pady = 5)

main_application.mainloop()
