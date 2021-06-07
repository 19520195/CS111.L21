import os
from tkinter import *
from tkinter import filedialog
from GUI_Text_Editor import Text_Editor

class Main_Menu:
    def __init__(self,main_application,text_editor,icons) :
        self.url = ""
        self.main_menu = Menu()
        theme_choice = StringVar()

        run = Menu(self.main_menu, tearoff = False)
        file = Menu(self.main_menu, tearoff = False)
        edit = Menu(self.main_menu, tearoff = False)
        color_theme = Menu(self.main_menu, tearoff = False)

        def run_code(event = None) :
            output = Tk()
            output.geometry("500x500")
            output.title("Result")
            text_ouput = Text_Editor(output)
            text_ouput.text_editor.insert("1.0","Hello")
            output.mainloop()
            return

        def config_color(keys, clr):
            text_editor.tag_delete(clr)
            for word in keys :
                start_pos = "1.0"
                while True:
                    start_pos = text_editor.search(word, start_pos, stopindex = END)
                    if not start_pos:
                        break
                    end_pos = f"{start_pos}+{len(word)}c"
                    text_editor.tag_add(clr, start_pos, end_pos)
                    start_pos = end_pos
                    text_editor.tag_config(clr, foreground = clr)


        def auto_color(event = None):
            control_word = ("clear ", "while ", "not ", " do", "end;", "end ")
            builtin_word = ("export ", "incr ", "decr ", "assign ")
            digit_word   = [str(_) for _ in range(10)]

            config_color(control_word, "#40aedf")
            config_color(builtin_word, "#eaaa37")
            config_color(digit_word  , "#88cc88")
        
        #NEW FILE FUNCTIONALITY
        def new_file(event = None):
            self.url = ""
            text_editor.delete(1.0, END)
            auto_color()
            main_application.title("New file")

        #OPEN FUNCTIONALITY
        def open_file(event = None):
            self.url = filedialog.askopenfilename(title = "Select File", filetypes = [("Bare Bones", "*.bb"), ("All Files", "*.*")])
            try:
                with open(self.url, "r") as fr:
                    text_editor.delete(1.0, END)
                    text_editor.insert(1.0, fr.read())
                    auto_color()
            except FileNotFoundError:
                return
            except:
                return
            main_application.title(os.path.basename(self.url))
            auto_color()

        def save_file(event = None):
            try:
                if self.url:
                    content =  str(text_editor.get(1.0, END))
                    with open(self.url, "w", encoding = "utf-8") as fw:
                        fw.write(content)
                    main_application.title(os.path.basename(self.url))

                else:
                    url = filedialog.asksaveasfilename(title = "Select File", defaultextension = ".bb", filetypes = [("Bare Bones", "*.bb"), ("All Files", "*.*")])
                    fo = open(url, "w")
                    code = text_editor.get("1.0", END)
                    fo.write(code)
                    fo.close()
                    main_application.title(os.path.basename(url))
            except:
                main_application.title(os.path.basename(url))
                return
            main_application.title(os.path.basename(url))


        #save as
        def save_as(event = None):
            try:
                self.url = filedialog.asksaveasfilename(title = "Select File", defaultextension = ".bb", filetypes = [("Bare Bones", "*.bb"), ("All Files", "*.*")])
                fo = open(self.url, "w")
                code = text_editor.get("1.0", END)
                fo.write(code)
                fo.close()
                main_application.title(os.path.basename(self.url))
            except:
                return

        def redo(event = None) :
            text_editor.edit_redo
            auto_color()

        def undo(event = None) :
            text_editor.edit_undo
            auto_color()

        def clear_all(event = None) :
            text_editor.delete(1.0, END)

        ############ find functionality
        def find_func(event = None):

            def find():
                word = find_input.get()
                text_editor.tag_remove("match", "1.0", END)
                matches = 0
                if word:
                    start_pos = "1.0"
                    while True:
                        start_pos = text_editor.search(word, start_pos, stopindex = END)
                        if not start_pos:
                            break
                        end_pos = f"{start_pos}+{len(word)}c"
                        text_editor.tag_add("match", start_pos, end_pos)
                        matches +=  1
                        start_pos = end_pos
                        text_editor.tag_config("match", foreground = "red", background = "yellow")

            def replace():
                word = find_input.get()
                replace_text = replace_input.get()
                content = text_editor.get(1.0, END)
                new_content = content.replace(word, replace_text)
                text_editor.delete(1.0, END)
                text_editor.insert(1.0, new_content)
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

        file.add_command(label = "New", image = icons.new, compound = LEFT, accelerator = "Ctrl+N", command = new_file)
        file.add_command(label = "Open", image = icons.open, compound = LEFT, accelerator = "Ctrl+O", command = open_file)
        file.add_command(label = "Save", image = icons.save, compound = LEFT, accelerator = "Ctrl+S", command = save_file)
        file.add_command(label = "Save As", image = icons.save_as, compound = LEFT, accelerator = "Ctrl+Alt+S", command = save_as)

        edit.add_command(label = "Copy", image = icons.copy, compound = LEFT, accelerator = "Ctrl+C", command = lambda:text_editor.event_generate("<Control c>"))
        edit.add_command(label = "Paste", image = icons.paste, compound = LEFT, accelerator = "Ctrl+V", command = lambda:text_editor.event_generate("<Control v>"))
        edit.add_command(label = "Cut", image = icons.cut, compound = LEFT, accelerator = "Ctrl+X", command = lambda:text_editor.event_generate("<Control x>"))
        edit.add_command(label = "Clear all", image = icons.clear_all, compound = LEFT, accelerator = "Ctrl+Alt+X", command = lambda:text_editor.delete(1.0, END))
        edit.add_command(label = "Undo", image = icons.undo, compound = LEFT, accelerator = "Ctrl+Z", command = undo)
        edit.add_command(label = "Redo", image = icons.redo, compound = LEFT, accelerator = "Ctrl+Y", command = redo)
        edit.add_command(label = "Find", image = icons.find, compound = LEFT, accelerator = "Ctrl+F", command = find_func)

        run.add_command(label = "Run", image = icons.run, compound = LEFT, accelerator = "F9", command = run_code)
        
        ## color theme
        def change_theme():
            chosen_theme = theme_choice.get()
            color_tuple = color_dict.get(chosen_theme)
            fg_color, bg_color = color_tuple[0], color_tuple[1]
            text_editor.config(background = bg_color, fg = fg_color)

        color_icons = (icons.light_default, icons.light_plus, icons.dark, icons.red, icons.monokai, icons.night)

        color_dict = {
            "Light Default": ("#000000", "#ffffff"),
            "Light Plus": ("#474747", "#e0e0e0"),
            "Dark": ("#c4c4c4", "#2d2d2d"),
            "Pink": ("#2d2d2d", "#ffe8e8"),
            "Monokai": ("#474747", "#d3b774"),
            "Night Blue": ("#ededed", "#6b9dc2")
        }

        count = 0
        for i in color_dict:
            color_theme.add_radiobutton(label = i, image = color_icons[count], variable = theme_choice, compound = LEFT, command = change_theme)
            count += 1
        
        self.main_menu.add_cascade(label = "File", menu = file)
        self.main_menu.add_cascade(label = "Edit", menu = edit)
        self.main_menu.add_cascade(label = "Color Theme", menu = color_theme)
        self.main_menu.add_cascade(label = "Run", menu = run)

        main_application.config(menu = self.main_menu)
        
        main_application.bind("<Control-n>", new_file)
        main_application.bind("<Control-o>", open_file)
        main_application.bind("<Control-s>", save_file)
        main_application.bind("<Control-Alt-s>", save_as)

        main_application.bind("<Key>", auto_color)
        main_application.bind("<Control-z>", undo)
        main_application.bind("<Control-y>", redo)
        main_application.bind("<Control-f>", find_func)
        main_application.bind("<Control-Alt-x>", clear_all)
        main_application.bind("<F9>", run_code)
