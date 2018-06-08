# -*- coding: UTF-8 -*-
import sqlite3
from tkinter import *
import sys
from tkinter.messagebox import askyesno
import time

flag=0
conn=sqlite3.connect('D:/note.sqlite')
cu=conn.cursor()
cu.execute('''
				create table if not exists admin(
				id integer primary key,
				password text);'''
			)

class Land():
	def __init__(self):
		pass
	
	def register(self):
		def confirm():
			if (entry.get()==None or entry1.get()==None or entry2.get()==None):
				entry3.insert(0,'请正确填写')
			elif entry1.get() != entry2.get() :
				entry3.insert(0,'两次密码不正确')
			else:
				cu.execute('insert into admin values({},{});'.format(entry.get(),entry1.get()))
				conn.commit()
				entry.delete(0,END)
				entry1.delete(0,END)
				entry2.delete(0,END)
				entry3.insert(0,"注册成功")
		def exit_register():
			top.destroy()
		top=Toplevel()
		top.title('注册')
		top.geometry()
		lab=Label(top,text='请输入用户名:')
		lab.grid(row=0,column=0,sticky='w')
		entry=Entry(top)
		entry.grid(row=0,column=1,columnspan=3)
		lab1=Label(top,text='请输入密码:')
		lab1.grid(row=1,column=0,sticky='w')
		entry1=Entry(top)
		entry1.grid(row=1,column=1,columnspan=3)
		lab2=Label(top,text='请确认密码:')
		lab2.grid(row=2,column=0,sticky='w')
		entry2=Entry(top)
		entry2.grid(row=2,column=1,columnspan=3)
		button=Button(top,text='注册',command=confirm)
		button.grid(row=3,column=0,columnspan=2)
		button1=Button(top,text='退出',command=exit_register)
		button1.grid(row=3,column=2,columnspan=2)
		entry3=Entry(top)
		entry3.grid(row=4,column=0,rowspan=2,columnspan=4)
	
	def main(self):
		def clear():
			root.destroy()
		def close_root():
			top=Toplevel()
			lab3=Label(top,text='登录成功!')
			lab3.grid(row=0)
			button3=Button(top,text='确定',command=clear)
			button3.grid(row=1)
		def fllush():
			entry.delete(0,END)
			entry1.delete(0,END)
		def closeWindow():
			ans = askyesno(title='Warning',message='Close the window?')
			if ans:
				sys.exit(0)
			else:
				return
		def landing():
			entry2.delete(0,END)
			corsor=cu.execute("select * from admin where id='{}' AND password='{}';".format(entry.get(),entry1.get()))
			rows=corsor.fetchone()
			if rows[1]==entry1.get():
				entry2.insert('insert',"登录成功")
				close_root()
			else:
				entry2.insert('insert',"密码错误")
				entry1.delete(0,END)
		def exit():
			conn.close()
			sys.exit(0)			
		root=Tk()
		root.title("登录")
		root.geometry('200x200')
		lab1=Label(root,text="用户名")
		lab1.grid(row=0,column=0,sticky='w')
		entry=Entry(root)
		entry.grid(row=0,column=1,columnspan=3)
		lab2=Label(root,text="密码")
		lab2.grid(row=1,column=0,sticky='w')
		entry1=Entry(root,show='*')
		entry1.grid(row=1,column=1,columnspan=3)
		button=Button(root,text='登录',command=landing)
		button.grid(row=2,column=0,columnspan=2)
		button1=Button(root,text='注册',command=self.register)
		button1.grid(row=2,column=2)
		button2=Button(root,text='关闭',command=close_root)
		button2.grid(row=2,column=3,sticky='e')
		entry2=Entry(root,bd=0)
		entry2.grid(row=3,column=0,columnspan=4,rowspan=3)
		root.protocol('WM_DELETE_WINDOW',closeWindow)
		root.mainloop()