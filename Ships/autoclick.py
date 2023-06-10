from keyboard import is_pressed, press, release, wait
from pyautogui import click, position, moveTo
from random import randint
from time import sleep

def run():
    while True:
        if is_pressed('-'):
            return
        sleep(1+randint(1, 20)/20)
        press("p")
        sleep(0.2)
        release("p")

while True:
    wait('+')
    run()