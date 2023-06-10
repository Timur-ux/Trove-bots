from keyboard import press, release, is_pressed
from time import sleep
m1atack = 'p'
m2atack = ','
ab1 = '1'
ab2 = '2'

def click(b):
    press(b)
    sleep(0.2)
    release(b)

def run():
    sleep(1)
    while True:
        if is_pressed('4'):
            release(m1atack)
            return
        press(m1atack)
        click(m2atack)

while True:
    sleep(1)
    if(is_pressed('4')):
        click(m1atack)
        run()
