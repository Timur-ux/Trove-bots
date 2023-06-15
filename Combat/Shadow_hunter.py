from keyboard import press, release, is_pressed, wait
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
    sleep(0.5)
    while True:
        if is_pressed('4'):
            release(m1atack)
            sleep(2)
            return
        press(m1atack)
        sleep(1)
        release(m1atack)

while True:
    wait('4')
    click(m1atack)
    run()
