from tkinter        import *
from Modules.Input  import Input
from Modules.Output import Output
from Modules.Menu   import Menu

import os
import string
import subprocess
import Modules.Utilities as bbu

class App:
    TITLE = "{} - Barebones IDE"
    filepath = ""
    font = ("Courier New", 16)

    color = dict({
        "fg"     : "#dcdcdc",
        "bg"     : "#1d2432",
        "digit"  : "#adc5a2",
        "control": "#ff636f",
        "builtin": "#63b7fc",
    })

    def __init__(self) -> None:
        self.app = Tk()
        self.app.geometry("800x600")
        self.app.title(self.TITLE.format("Untitled"))

        # self.icon = Icon(self.app)
        self.input  = Input(self)
        self.output = Output(self)
        self.menu   = Menu(self, self.input.text)

        # tool_bar = ToolBar(app, text_editor.coding_space)
        # tool_bar.tool_bar.pack(side=TOP, fill=X)

        self.app.bind("<Control-n>"    , self.file_new   )
        self.app.bind("<Control-o>"    , self.file_open  )
        self.app.bind("<Control-s>"    , self.file_save  )
        self.app.bind("<Control-Alt-s>", self.file_saveas)

        self.app.bind("<Key>"            , self.code_colidx     )
        self.app.bind("<Control-f>"      , self.code_find       )
        self.app.bind("<Control-z>"      , self.code_undo       )
        self.app.bind("<Control-y>"      , self.code_redo       )
        self.app.bind("<Control-Shift-c>", self.code_comment    )
        self.app.bind("<Control-Shift-x>", self.code_undocomment)
        self.app.bind("<Control-Alt-x>"  , self.input.clear     )

        self.app.bind("<F9>"        , self.code_execute)
        self.app.bind("<Control-F9>", self.code_compile)

    def code_colidx(self, event=None):
        self.code_color(event)
        self.code_index(event)

    def code_color(self, event=None):
        def config_color(words, clr):
            self.input.text.tag_delete(clr)

            for word in words:
                start_pos = "1.0"
                while True:
                    start_pos = self.input.text.search(word, start_pos, stopindex=END)
                    if not start_pos:
                        break
                    end_pos = f"{start_pos}+{len(word)}c"
                    row, column = start_pos.split(".")

                    if "#" not in self.input.text.get(f"{row}.0", start_pos):
                        prev_char = self.input.text.get(f"{start_pos}-1c", start_pos).upper()
                        next_char = self.input.text.get(end_pos, f"{end_pos}+1c").upper()
                        if prev_char not in string.ascii_uppercase and next_char not in string.ascii_uppercase or start_pos == "1.0":
                            self.input.text.tag_add(clr, start_pos, end_pos)
                    start_pos = end_pos

            self.input.text.tag_config(clr, foreground=clr)

        digit_word   = list(map(str, range(10)))
        control_word = ("while", "do", "if", "then", "not", "end")
        builtin_word = ("incr", "decr", "clear", "assign", "export", "import")

        config_color(digit_word  , self.color["digit"]  )
        config_color(control_word, self.color["control"])
        config_color(builtin_word, self.color["builtin"])

        self.input.text.tag_delete("comment")

        start_pos = "1.0"
        while True:
            start_pos = self.input.text.search("#", start_pos, stopindex=END)
            if not start_pos:
                break
            row, column = start_pos.split(".")
            end_pos = f"{row}.end"
            self.input.text.tag_add("comment", start_pos, end_pos)
            start_pos = end_pos

        self.input.text.tag_config("comment", foreground="#828c9b")

    def code_index(self, event=None):
        num_lines = self.input.get().count('\n')
        self.input.index.configure(state=NORMAL)
        self.input.index.delete(1.0, END)
        self.input.index.insert(END, ''.join(map(lambda i: "{:3d}".format(i+1), range(num_lines))))
        self.input.index.configure(state=DISABLED)

        Y, _ = self.input.text.yview()
        self.input.index.yview_moveto(Y)

    def file_new(self, event=None):
        self.input.clear()
        self.app.title(self.TITLE.format("Untitiled"))

    def file_open(self, event=None):
        def callback(filepath, content):
            self.input.set(content)
            self.code_colidx()

            self.filepath = filepath
            self.app.title(self.TITLE.format(os.path.basename(filepath)))
        try:
            bbu.AskOpenFile(callback)
            return True
        except: return False

    def file_saveas(self, event=None):
        def callback(filepath):
            self.filepath = filepath
            self.app.title(self.TITLE.format(os.path.basename(filepath)))

        try: bbu.AskSaveFile(self.input.get(), callback)
        except: return False
        return True

    def file_save(self, event=None):
        try:
            if self.filepath:
                bbu.SaveFile(self.filepath, self.input.get())
            else: self.file_saveas(event)
        except: return False
        return True

    def code_undo(self, event=None):
        self.input.text.edit_undo()
        self.code_colidx(event)

    def code_redo(self, event=None):
        self.input.text.edit_redo()
        self.code_colidx(event)

    def code_comment(self, event=None):
        try:
            row_start, column_start = map(int, self.input.text.index("sel.first").split("."))
            row_end, column_end = map(int, self.input.text.index("sel.last").split("."))
            for i in range(row_end - row_start + 1):
                id = f"{row_start + i}.{0}"
                self.input.text.insert(id, "# ")
        except:
            row, column = map(int, self.input.text.index("insert").split("."))
            id = f"{row}.{0}"
            self.input.text.insert(id, "# ")
        self.code_color(event)

    def code_undocomment(self, event=None):
        try:
            row_start, column_start = map(int, self.input.index("sel.first").split("."))
            row_end, column_end = map(int, self.input.index("sel.last").split("."))
            for i in range(row_end - row_start + 1):
                if self.input.get(f"{row_start + i}.{0}", f"{row_start + i}.{2}") == "# " :
                    self.input.delete(f"{row_start + i}.{0}", f"{row_start + i}.{2}")
                    continue
                pos = self.input.search("#", f"{row_start + i}.{0}", stopindex=f"{row_start + i}.end")
                if pos :
                    self.input.delete(pos, f"{pos}+1c")
        except:
            row, column = map(int, self.input.index("insert").split("."))
            start = f"{row}.{0}"
            end = f"{row}.{2}"

            if self.input.get(start, end) == "# " :
                self.input.delete(start, end)
                return

            pos = self.input.search("#", f"{row}.{0}", stopindex=f"{row}.end")
            if pos :
                self.input.delete(pos, f"{pos}+1c")
        self.code_color()

    def code_find(self, event=None):
        def find():
            word = find_input.get()
            self.input.text.tag_remove("match", "1.0", END)
            matches = 0
            if word:
                start_pos = "1.0"
                while True:
                    start_pos = self.input.text.search(word, start_pos, stopindex=END)
                    if not start_pos:
                        break
                    end_pos = f"{start_pos}+{len(word)}c"
                    self.input.text.tag_add("match", start_pos, end_pos)
                    matches +=  1
                    start_pos = end_pos
                    self.input.text.tag_config("match", foreground="red", background="yellow")

        def replace():
            word = find_input.get()
            replace_text = replace_input.get()
            content = self.input.text.get(1.0, END)
            new_content = content.replace(word, replace_text)
            self.input.text.delete(1.0, END)
            self.input.text.insert(1.0, new_content)
            self.code_color()

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

    def code_run(self, *arg, event=None):
        if not self.file_save(event):
            return False

        src_path = os.path.dirname(os.path.realpath(__file__))
        prog_path = os.path.abspath(os.path.join(src_path, "..", "..", "Binaries", "Barebones"))
        pipe_read, pipe_write = os.pipe()
        pipe_write = os.fdopen(pipe_write)
        subprocess.call([prog_path] + list(arg), stdout=pipe_write)
        pipe_write.close()

        pipe_read = os.fdopen(pipe_read)
        self.output.text.config(state="normal")
        self.output.set(pipe_read.read() + "> Complete")
        self.output.text.config(state="disable")
        pipe_read.close()
        return True

    def code_execute(self, event=None):
        return self.code_run("-i" + self.filepath, event=event)

    def code_compile(self, event=None):
        dir_in = self.filepath
        dir_out = self.filepath
        if 0 <= dir_out.find("."):
            dir_out = dir_out[:dir_out.find(".")]
        return self.code_run("-i" + dir_in, "-o" + dir_out, event=event)

    def render(self) -> None:
        self.input.render()
        self.output.render()

        self.menu.render(self.app)
        self.app.mainloop()
