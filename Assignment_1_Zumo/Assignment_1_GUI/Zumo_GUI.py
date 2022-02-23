from tkinter import *
import serial

ser = serial.Serial('COM12', 9600)

def forward():	
	ser.write(b'w')
	myLabel.config(text = "Forward")

def turn_left():
	ser.write(b'a')
	myLabel.config(text = "Left")

def turn_right():
	ser.write(b'd')
	myLabel.config(text = "Right")

def backward():
	ser.write(b's')
	myLabel.config(text = "Backward")

def u_turn():
	ser.write(b'b')
	myLabel.config(text = "U turn")

def left_turn_90():
	ser.write(b'l')
	myLabel.config(text = "90 degree left turn")

def right_turn_90():
	ser.write(b'r')
	myLabel.config(text = "90 degree right turn")

def manual_navigation():
	ser.write(b'c')	
	myLabel.config(text = "Auto navigation, press 'a' or 'd' at the end of corridoor.")

def Auto_navigation():
	ser.write(b'x')
	myLabel.config(text = "Auto navigation, press 'l' or 'r' at the end of corridoor.")

app= Tk()
app.geometry("1280x720")

myLabel = Label(text="")
myLabel.place(x=600, y=600)

forward_button = Button(app, text="Forward", width=20, command=forward)
forward_button.place(x=600, y=100)

left_button = Button(app, text="Left", width=20, command=turn_left)
left_button.place(x=400, y=250)

right_button = Button(app, text="Right", width=20, command=turn_right)
right_button.place(x=800, y=250)

back_button = Button(app, text="Backward", width=20, command=backward)
back_button.place(x=600, y=400)

u_turn_button = Button(app, text="180", width=20, command=u_turn)
u_turn_button.place(x=600, y=500)

left_turn_button = Button(app, text="90 Left", width=20, command=left_turn_90)
left_turn_button.place(x=400, y=100)

right_turn_button = Button(app, text="90 Right", width=20, command=right_turn_90)
right_turn_button.place(x=800, y=100)

manual_button = Button(app, text="Manual Navigation", width=20, command=manual_navigation)
manual_button.place(x=400, y=400)

auto_button = Button(app, text="Auto Navigation", width=20, command=Auto_navigation)
auto_button.place(x=800, y=400)


app.mainloop()