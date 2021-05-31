
import os
from tkinter.ttk import *
from tkinter import *
from time import sleep

main_application = Tk()
main_application.geometry('1200x800')
main_application.title('IDE for BareBones')

#################### MAIN MENU ########################
main_menu=Menu()

def config_color(keys, Clr):
    for word in keys :
        matches = 0
        if word:
            start_pos = '1.0'
            while True:
                start_pos = textWriteCode.search(word, start_pos, stopindex=END)
                if not start_pos:
                    break 
                end_pos = f'{start_pos}+{len(word)}c'
                textWriteCode.tag_add(Clr, start_pos, end_pos)
                matches += 1
                start_pos = end_pos
                textWriteCode.tag_config(Clr, foreground=Clr)


def auto_color(event=None):
    blue = ("clear","while","not","do","end")
    green = ("export", "incr", "decr", "assign")
    pink = ("0","1","2","3","4","5","6","7","8","9")
    red = (";","=")
    config_color(blue,"blue")
    config_color(green,"green")
    config_color(pink,"#FF1493")
    config_color(red,"red")
       

#------------------file tab-------------------------#
new_icon=PhotoImage(file="./Icons/new.png")
open_icon=PhotoImage(file="./Icons/open.png")
save_icon=PhotoImage(file="./Icons/save.png")
save_as_icon=PhotoImage(file="./Icons/save_as.png")
exit_icon=PhotoImage(file="./Icons/exit.png")

file=Menu(main_menu, tearoff=False)


#----------------------------edit tab----------------------------#
copy_icon=PhotoImage(file="./Icons/copy.png")
paste_icon=PhotoImage(file="./Icons/paste.png")
cut_icon=PhotoImage(file="./Icons/cut.png")
clearall_icon=PhotoImage(file="./Icons/clear_all.png")
find_icon=PhotoImage(file="./Icons/find.png")

edit=Menu(main_menu, tearoff=False)

#-------------------------------window---------------------#
light_default_icon=PhotoImage(file='./Icons/light_default.png')
light_plus_icon=PhotoImage(file='./Icons/light_plus.png')
dark_icon=PhotoImage(file='./Icons/dark.png')
red_icon=PhotoImage(file='./Icons/red.png')
monokai_icon=PhotoImage(file='./Icons/monokai.png')
night_icon=PhotoImage(file='./Icons/night_blue.png')

color_theme=Menu(main_menu, tearoff=False)

theme_choice=StringVar()
color_Icons=(light_default_icon,light_plus_icon,dark_icon,red_icon,monokai_icon,night_icon)

color_dict={
    'Light Default':('#000000','#ffffff'),
    'Light Plus':('#474747','e0e0e0'),
    'Dark':('#c4c4c4','#2d2d2d'),
    'Red':('#2d2d2d','#ffe8e8'),
    "Monokai":('#d3b774','#474747'),
    'Night Blue':('#ededed','#6b9dc2')
}



#cascade
main_menu.add_cascade(label="File",menu=file)
main_menu.add_cascade(label="Edit",menu=edit)
# main_menu.add_cascade(label="View",menu=view)
main_menu.add_cascade(label="Color Theme",menu=color_theme)

#&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& end of Main menu &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


############################################## TOOL BAR ##########################

tool_bar=Label(main_application)
tool_bar.pack(side=TOP,fill=X)

##font box
font_tuple=font.families()
font_family=StringVar()
font_box=Combobox(tool_bar,width=30,textvariable=font_family,state='readonly')
font_box['values']=font_tuple
font_box.current(font_tuple.index('Times New Roman'))
font_box.grid(row=0,column=0,padx=5)


#size box
size_var=IntVar()
font_size=Combobox(tool_bar, width=14,textvariable=size_var, state='readonly')
font_size['values']=tuple(range(8,80,2))
font_size.current(4)
font_size.grid(row=0,column=1,padx=5)


#&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& end toolbar&&&&&&&&&&&&&&&&&&&&&&&&&&&&


########################################  TEXT EDITOR ##################################

row1 = Frame(main_application)
row1.pack(fill = BOTH, expand = True)
# Horizontal (x) Scroll bar
xscrollbar = Scrollbar(row1, orient=HORIZONTAL)
xscrollbar.pack(side=BOTTOM, fill=X)

# Vertical (y) Scroll Bar
yscrollbar = Scrollbar(row1)
yscrollbar.pack(side=RIGHT, fill=Y)
# text write code
textWriteCode = Text(row1, wrap=NONE, relief=FLAT,font=("Times New Roman",16) , xscrollcommand=xscrollbar.set, yscrollcommand=yscrollbar.set)

textWriteCode.pack( fill = BOTH, padx = 5, pady = 5, expand = True) 

xscrollbar.config(command=textWriteCode.xview)
yscrollbar.config(command=textWriteCode.yview)


######## font family and font size functionality
current_font_family='Times New Roman'
current_font_size=13

def change_font(main_application):
    global current_font_family
    current_font_family= font_family.get()
    textWriteCode.configure(font=(current_font_family,current_font_size))

def change_fontsize(main_application):
    global current_font_size
    current_font_size= size_var.get()
    textWriteCode.configure(font=(current_font_family,current_font_size))

font_box.bind('<<ComboboxSelected>>',change_font)
font_size.bind('<<ComboboxSelected>>',change_fontsize)


# textWriteCode.configure(font=('Times New Roman',13))
#&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& END OF TEXT EDITOR &&&&&&&&&&&&&&&&&&&&&&&


#######################################################   main menu functionality #####################


url=''           #GLOBAL VARIABLE

#NEW FILE FUNCTIONALITY
def new_file(event=None):
    global url
    url=''
    textWriteCode.delete(1.0,END)
    main_application.title("New file")

file.add_command(label="NEW",image=new_icon,compound=LEFT,accelerator='CTRL+N',command=new_file)


#OPEN FUNCTIONALITY
def open_file(event=None):
    global url
    url=filedialog.askopenfilename(title='Select File',filetypes=[("Bare Bones", "*.bb"), ("All Files", "*.*")])
    try:
        with open(url,'r') as fr:
            textWriteCode.delete(1.0,END)
            textWriteCode.insert(1.0,fr.read())
            auto_color()
    except FileNotFoundError:
        return
    except:
        return
    main_application.title(os.path.basename(url))

file.add_command(label="OPEN",image=open_icon,compound=LEFT,accelerator="CTRL+O",command=open_file)

def save_file(event=None):
    global url
    try:
        if url:
            content= str(textWriteCode.get(1.0,END))
            with open(url,'w',encoding='utf-8') as fw:
                fw.write(content)
            main_application.title(os.path.basename(url))
            
        else:
            url = filedialog.asksaveasfilename(title='Select File', filetypes=[("Bare Bones", "*.bb"), ("All Files", "*.*")])
            fo = open(url,"w")
            code = textWriteCode.get("1.0",END)
            fo.write(code)
            fo.close()
            main_application.title(os.path.basename(url))
    except:
        main_application.title(os.path.basename(url))
        return
    main_application.title(os.path.basename(url))

file.add_command(label="SAVE",image=save_icon,compound=LEFT,accelerator="CTRL+S",command=save_file)



#save as 
def save_as(event=None):
    global url
    try:
        content=textWriteCode.get(1.0,END)
        url=filedialog.asksaveasfile(mode='w',defaultextension='.txt',filetypes=(('Text File','*.txt'),('All files','*.*')))
        url.write(content)
        url.close()
    except:
        return

file.add_command(label="SAVE AS",image=save_icon,compound=LEFT,accelerator="CTRL+ALT+S",command=save_as)


## exit functionality 

def exit_func(event=None):
    global url, text_changed
    try:
        if text_changed:
            mbox = messagebox.askyesnocancel('Warning', 'Do you want to save the file ?')
            if mbox is True:
                if url:
                    content = textWriteCode.get(1.0, END)
                    with open(url, 'w', encoding='utf-8') as fw:
                        fw.write(content)
                        main_application.destroy()
                else:
                    content2 = str(textWriteCode.get(1.0, END))
                    url = filedialog.asksaveasfile(mode = 'w', defaultextension='.txt', filetypes=(('Text File', '*.txt'), ('All files', '*.*')))
                    url.write(content2)
                    url.close()
                    main_application.destroy()
            elif mbox is False:
                main_application.destroy()
        else:
            main_application.destroy()
    except:
        return 
file.add_command(label='Exit', image=exit_icon, compound=LEFT, accelerator='Ctrl+Q', command=exit_func)


## edit tab

############ find functionality

def find_func(event=None):

    def find():
        word = find_input.get()
        textWriteCode.tag_remove('match', '1.0', END)
        matches = 0
        if word:
            start_pos = '1.0'
            while True:
                start_pos = textWriteCode.search(word, start_pos, stopindex=END)
                if not start_pos:
                    break 
                end_pos = f'{start_pos}+{len(word)}c'
                textWriteCode.tag_add('match', start_pos, end_pos)
                matches += 1
                start_pos = end_pos
                textWriteCode.tag_config('match', foreground='red', background='yellow')
    
    def replace():
        word = find_input.get()
        replace_text = replace_input.get()
        content = textWriteCode.get(1.0, END)
        new_content = content.replace(word, replace_text)
        textWriteCode.delete(1.0, END)
        textWriteCode.insert(1.0, new_content)

    find_dialogue = Toplevel()
    find_dialogue.geometry('450x250+500+200')
    find_dialogue.title('Find')
    find_dialogue.resizable(0,0)

    ## frame 
    find_frame = tLabelFrame(find_dialogue, text='Find/Replace')
    find_frame.pack(pady=20)

    ## labels
    text_find_label = tLabel(find_frame, text='Find : ')
    text_replace_label = tLabel(find_frame, text= 'Replace')

    ## entry 
    find_input = tEntry(find_frame, width=30)
    replace_input = tEntry(find_frame, width=30)

    ## button 
    find_button = tButton(find_frame, text='Find', command=find)
    replace_button = tButton(find_frame, text= 'Replace', command=replace)

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


edit.add_command(label="COPY",image=copy_icon,compound=LEFT,accelerator="CTRL+C", command=lambda:textWriteCode.event_generate("<Control c>"))
edit.add_command(label="PASTE",image=paste_icon,compound=LEFT,accelerator="CTRL+V",command=lambda:textWriteCode.event_generate("<Control v>"))
edit.add_command(label="CUT",image=cut_icon,compound=LEFT,accelerator="CTRL+X", command=lambda:textWriteCode.event_generate("<Control x>"))
edit.add_command(label="CLEAR ALL",image=clearall_icon,compound=LEFT,accelerator="CTRL+ALT+X", command=lambda:textWriteCode.delete(1.0,END))
edit.add_command(label="FIND",image=find_icon,compound=LEFT,accelerator="CTRL+F",command = find_func)
edit.add_command(label="Fill Color",compound=LEFT,accelerator="CTRL+P",command = auto_color)

## window tab
## color theme 
def change_theme():
    chosen_theme = theme_choice.get()
    color_tuple = color_dict.get(chosen_theme)
    fg_color, bg_color = color_tuple[0], color_tuple[1]
    textWriteCode.config(background=bg_color, fg=fg_color) 
count = 0 
for i in color_dict:
    color_theme.add_radiobutton(label = i, image=color_Icons[count], variable=theme_choice, compound=LEFT, command=change_theme)
    count += 1 

main_application.config(menu=main_menu)
main_application.bind("<Control-n>", new_file)
main_application.bind("<Control-o>", open_file)
main_application.bind("<Control-s>", save_file)
main_application.bind("<Control-Alt-s>", save_as)
main_application.bind("<Control-q>", exit_func)
main_application.bind("<Control-f>", find_func)
main_application.bind("<Control-p>", auto_color)

# colorCode = Thread(target=auto_color)
# colorCode.start()

def handle_button_run_code() :
    code = textWriteCode.get("1.0",END)
    # print (code)
    return
        
row2= Frame(main_application)
row2.pack(side = RIGHT)

bttRunCode = Button(row2, text = "Run", font=("Arial",18), command = handle_button_run_code)
bttRunCode.pack(side = RIGHT, padx = 5, pady = 5)


main_application.mainloop()