from pyautogui import position
from keyboard import wait

print("Dont forget set , between numbers")
while True:
    wait('+')
    print('{',*position(), '}', end=',')