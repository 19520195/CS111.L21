import os
import string
import subprocess
from tkinter import *

class MainMenu:
    def __init__(self, app, text_editor, output, icons) :
        self.url = ""
        self.main_menu = Menu()
        theme_choice = StringVar()

        run = Menu(self.main_menu, tearoff=False)
        file = Menu(self.main_menu, tearoff=False)
        edit = Menu(self.main_menu, tearoff=False)
        color_theme = Menu(self.main_menu, tearoff=False)

        def run_code(event=None):
            if not save_file(event):
                return False

            src_path = os.path.dirname(os.path.realpath(__file__))
            src_path = os.path.abspath(os.path.join(src_path, ".."))
            bin_dir = os.path.join(src_path, "Binaries", "Barebones")

            pipe_read, pipe_write = os.pipe()
            pipe_write = os.fdopen(pipe_write)
            subprocess.check_call([bin_dir, "-i" + self.url], stdout=pipe_write)
            pipe_write.close()

            pipe_read = os.fdopen(pipe_read)
            output.text_output.config(state="normal")
            output.text_output.delete(1.0, END)
            output.text_output.insert(1.0, pipe_read.read())
            output.text_output.config(state="disable")
            pipe_read.close()

            return

        def config_color(words, clr):
            text_editor.tag_delete(clr)

            for word in words :
                start_pos = "1.0"
                while True:
                    start_pos = text_editor.search(word, start_pos, stopindex=END)
                    if not start_pos:
                        break
                    end_pos = f"{start_pos}+{len(word)}c"
                    row, column = start_pos.split(".")

                    if "#" not in text_editor.get(f"{row}.0", start_pos) :
                        prev_char = text_editor.get(f"{start_pos}-1c", start_pos).upper()
                        next_char = text_editor.get(end_pos, f"{end_pos}+1c").upper()
                        if prev_char not in string.ascii_uppercase and next_char not in string.ascii_uppercase or start_pos == "1.0" :
                            text_editor.tag_add(clr, start_pos, end_pos)
                    start_pos = end_pos

            text_editor.tag_config(clr, foreground=clr)


        def auto_color(event=None):
            control_word = ("clear", "while", "not", "do", "end")
            builtin_word = ("export", "incr", "decr", "assign")
            digit_word   = [str(_) for _ in range(10)]

            config_color(control_word, "#40aedf")
            config_color(builtin_word, "#eaaa37")
            config_color(digit_word  , "#88cc88")

            text_editor.tag_delete("comment")

            start_pos = "1.0"
            while True:
                start_pos = text_editor.search("#", start_pos, stopindex=END)
                if not start_pos:
                    break
                row, column = start_pos.split(".")
                end_pos = f"{row}.end"
                text_editor.tag_add("comment", start_pos, end_pos)
                start_pos = end_pos

            text_editor.tag_config("comment", foreground="#808080")

        #NEW FILE FUNCTIONALITY
        def new_file(event=None):
            self.url = ""
            text_editor.delete(1.0, END)
            auto_color()
            app.title("New file")

        #OPEN FUNCTIONALITY
        def open_file(event=None):
            self.url = filedialog.askopenfilename(title="Select File", filetypes=[("Bare Bones", "*.bb"), ("All Files", "*.*")])
            try:
                with open(self.url, "r") as fr:
                    text_editor.delete(1.0, END)
                    text_editor.insert(1.0, fr.read())
                    auto_color()
            except FileNotFoundError:
                return
            except:
                return
            app.title(os.path.basename(self.url))
            auto_color()

        def save_file(event=None):
            try:
                if self.url:
                    content =  str(text_editor.get(1.0, END))
                    with open(self.url, "w", encoding="utf-8") as fw:
                        fw.write(content)
                    app.title(os.path.basename(self.url))
                else:
                    self.url = filedialog.asksaveasfilename(title="Select File", defaultextension=".bb", filetypes=[("Bare Bones", "*.bb"), ("All Files", "*.*")])
                    if self.url == "":
                        return False
                    fo = open(self.url, "w")
                    code = text_editor.get("1.0", END)
                    fo.write(code)
                    fo.close()
                    app.title(os.path.basename(self.url))
            except:
                app.title(os.path.basename(self.url))
            app.title(os.path.basename(self.url))
            return True


        def comment (event=None):
            try:
                row_start, column_start = map(int, text_editor.index("sel.first").split("."))
                row_end, column_end = map(int, text_editor.index("sel.last").split("."))
                for i in range(row_end - row_start + 1):
                    id = f"{row_start + i}.{0}"
                    text_editor.insert(id, "# ")
            except:
                row, column = map(int, text_editor.index("insert").split("."))
                id = f"{row}.{0}"
                text_editor.insert(id, "# ")

            auto_color()

        def uncomment (event=None):
            try:
                row_start, column_start = map(int, text_editor.index("sel.first").split("."))
                row_end, column_end = map(int, text_editor.index("sel.last").split("."))
                for i in range(row_end - row_start + 1):
                    if text_editor.get(f"{row_start + i}.{0}", f"{row_start + i}.{2}") == "# " :
                        text_editor.delete(f"{row_start + i}.{0}", f"{row_start + i}.{2}")
                        continue

                    pos = text_editor.search("#", f"{row_start + i}.{0}", stopindex=f"{row_start + i}.end")
                    if pos :
                        text_editor.delete(pos, f"{pos}+1c")

            except:
                row, column = map(int, text_editor.index("insert").split("."))
                start = f"{row}.{0}"
                end = f"{row}.{2}"

                if text_editor.get(start, end) == "# " :
                    text_editor.delete(start, end)
                    return

                pos = text_editor.search("#", f"{row}.{0}", stopindex=f"{row}.end")
                if pos :
                    text_editor.delete(pos, f"{pos}+1c")

            auto_color()

        #save as
        def save_as(event=None):
            try:
                self.url = filedialog.asksaveasfilename(title="Select File", defaultextension=".bb", filetypes=[("Bare Bones", "*.bb"), ("All Files", "*.*")])
                fo = open(self.url, "w")
                code = text_editor.get("1.0", END)
                fo.write(code)
                fo.close()
                app.title(os.path.basename(self.url))
            except:
                return

        def redo(event=None) :
            text_editor.edit_redo
            auto_color()

        def undo(event=None) :
            text_editor.edit_undo
            auto_color()

        def clear_all(event=None) :
            text_editor.delete(1.0, END)

        ############ find functionality
        def find_func(event=None):

            def find():
                word = find_input.get()
                text_editor.tag_remove("match", "1.0", END)
                matches = 0
                if word:
                    start_pos = "1.0"
                    while True:
                        start_pos = text_editor.search(word, start_pos, stopindex=END)
                        if not start_pos:
                            break
                        end_pos = f"{start_pos}+{len(word)}c"
                        text_editor.tag_add("match", start_pos, end_pos)
                        matches +=  1
                        start_pos = end_pos
                        text_editor.tag_config("match", foreground="red", background="yellow")

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
            find_frame = LabelFrame(find_dialogue, text="Find/Replace")
            find_frame.pack(pady=20)

            ## labels
            text_find_label = Label(find_frame, text="Find : ")
            text_replace_label = Label(find_frame, text= "Replace")

            ## entry
            find_input = Entry(find_frame, width=30)
            replace_input = Entry(find_frame, width=30)

            ## button
            find_button = Button(find_frame, text="Find", command=find)
            replace_button = Button(find_frame, text= "Replace", command=replace)

            ## label grid
            text_find_label.grid(row=0, column=0, padx=4, pady=4)
            text_replace_label.grid(row=1, column=0, padx=4, pady=4)

            ## entry grid
            find_input.grid(row=0, column=1, padx=4, pady=4)
            replace_input.grid(row=1, column=1, padx=4, pady=4)

            ## button grid
            find_button.grid(row=2, column=0, padx=8, pady=4)
            replace_button.grid(row=2, column=1, padx=8, pady=4)

            find_dialogue.mainloop()

        ## color theme
        def change_theme():
            chosen_theme = theme_choice.get()
            color_tuple = color_dict.get(chosen_theme)
            fg_color, bg_color = color_tuple[0], color_tuple[1]
            text_editor.config(background=bg_color, fg=fg_color)

        color_icons = (icons.light_default, icons.light_plus, icons.dark, icons.red, icons.monokai, icons.night)

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
            color_theme.add_radiobutton(label = i, image=color_icons[count], variable=theme_choice, compound=LEFT, command=change_theme)
            count += 1

        file.add_command(label = "New", image=icons.new, compound=LEFT, accelerator="Ctrl+N", command=new_file)
        file.add_command(label = "Open", image=icons.open, compound=LEFT, accelerator="Ctrl+O", command=open_file)
        file.add_command(label = "Save", image=icons.save, compound=LEFT, accelerator="Ctrl+S", command=save_file)
        file.add_command(label = "Save As", image=icons.save_as, compound=LEFT, accelerator="Ctrl+Alt+S", command=save_as)

        edit.add_command(label = "Copy", image=icons.copy, compound=LEFT, accelerator="Ctrl+C", command=lambda:text_editor.event_generate("<Control c>"))
        edit.add_command(label = "Paste", image=icons.paste, compound=LEFT, accelerator="Ctrl+V", command=lambda:text_editor.event_generate("<Control v>"))
        edit.add_command(label = "Cut", image=icons.cut, compound=LEFT, accelerator="Ctrl+X", command=lambda:text_editor.event_generate("<Control x>"))
        edit.add_command(label = "Clear all", image=icons.clear_all, compound=LEFT, accelerator="Ctrl+Alt+X", command=lambda:text_editor.delete(1.0, END))
        edit.add_command(label = "Undo", image=icons.undo, compound=LEFT, accelerator="Ctrl+Z", command=undo)
        edit.add_command(label = "Redo", image=icons.redo, compound=LEFT, accelerator="Ctrl+Y", command=redo)
        edit.add_command(label = "Find", image=icons.find, compound=LEFT, accelerator="Ctrl+F", command=find_func)
        edit.add_command(label="Comment", compound=LEFT, accelerator="Control-Shift-C", command=comment)
        edit.add_command(label="UnComment", compound=LEFT, accelerator="Control-Shift-X", command=uncomment)

        run.add_command(label = "Run", image=icons.run, compound=LEFT, accelerator="F9", command=run_code)

        self.main_menu.add_cascade(label="File", menu=file)
        self.main_menu.add_cascade(label="Edit", menu=edit)
        self.main_menu.add_cascade(label="Color Theme", menu=color_theme)
        self.main_menu.add_cascade(label="Run", menu=run)

        app.config(menu=self.main_menu)

        app.bind("<Control-n>", new_file)
        app.bind("<Control-o>", open_file)
        app.bind("<Control-s>", save_file)
        app.bind("<Control-Alt-s>", save_as)

        app.bind("<Key>", auto_color)
        app.bind("<Control-z>", undo)
        app.bind("<Control-y>", redo)
        app.bind("<Control-f>", find_func)
        app.bind("<Control-Alt-x>", clear_all)
        app.bind("<Control-Shift-C>", comment)
        app.bind("<Control-Shift-X>", uncomment)

        app.bind("<F9>", run_code)
