from keyboard import is_pressed, press, release, wait
from pyautogui import click, position, moveTo
from random import randint
from time import sleep

def run():
    press('p')
    wait('-')
    release('p')
    

while True:
    wait('+')
    run()