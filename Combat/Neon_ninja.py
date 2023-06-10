from keyboard import press, release, is_pressed
from pyautogui import move, position, drag
import pydirectinput
import pyautogui
from time import sleep
m1atack = 'p'
m2atack = ','
ab1 = '1'
ab2 = '2'

def click(b):
    press(b)
    release(b)
pydirectinput.PAUSE = 0.02
def run():
    while True:
        pydirectinput.keyUp('w')
        pydirectinput.move(20, None)
        pydirectinput.keyDown('s')
        pydirectinput.press(m2atack)
        pydirectinput.keyUp('s')
        sleep(0.1)
        pydirectinput.move(-20, None)
        pydirectinput.keyDown('w')
        if(is_pressed('4')):
            pydirectinput.keyUp('w')
            return
        sleep(2)

pressed = False
while True:
    sleep(0.2)
    if(is_pressed('4')):
        run()
        sleep(3)
        
