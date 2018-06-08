# -*- coding: UTF-8 -*-
from tkinter import *
import win32ui
import sqlite3
import sys
import os
import land

land1=land.Land()
land1.main()

def build1():
	def destory():
		top.destroy()
	top=Toplevel()
	top.title('保存')
	lab=Label(top,text='文件名')
	lab.grid(row=0,column=0,sticky='w')
	entry=Entry(top)
	entry.grid(row=0,column=1)
	button=Button(top,text='确认',command=destory)
	button.grid(row=0,column=2)
	filename=entry.get()
	fp=open(filename,'a+')
	root.title(filename)
	fp.close()

def build():
	dlg= win32ui.CreateFileDialog(1)
	dlg.SetOFNInitialDir('Desktop')  
	dlg.DoModal()  
	filename=dlg.GetPathName()
	fp=open(filename,'a+')
	fp.write(text.get(1.0,END))
	root.title(filename)
	fp.close()
	
def watch():
	dlg= win32ui.CreateFileDialog(1)
	dlg.SetOFNInitialDir('Desktop')  
	dlg.DoModal()  
	filename=dlg.GetPathName()
	fp=open(filename,'r')
	content=fp.read()
	text.insert(1.0,content)
	
def move_file():
	def confirm():
		os.remove(entry.get())
		top.destroy()
	top=Toplevel()
	top.title('删除')
	lab=Label(top,text='文件名')
	lab.grid(row=0,column=0,sticky='w')
	entry=Entry(top)
	entry.grid(row=0,column=1)
	button=Button(top,text='确认',command=confirm)
	button.grid(row=0,column=2)
	
def exit0():
	sys.exit(0)
	
root=Tk()
root.title('记事本  author:lp')
root.geometry('400x300')
main_menu=Menu(root)
fmenu=Menu(main_menu)
main_menu.add_cascade(label='新建',menu=fmenu)
fmenu.add_command(label='保存',command=build1)
fmenu.add_command(label='另存为',command=build)
fmenu.add_command(label='删除',command=move_file)
main_menu.add_command(label='查看',command=watch)
main_menu.add_command(label='退出',command=exit0)
main_menu.add_command(label='关于')
root.config(menu=main_menu)
text=Text(root)
text.grid(row=1,rowspan=9,column=0,columnspan=4)
root.mainloop()