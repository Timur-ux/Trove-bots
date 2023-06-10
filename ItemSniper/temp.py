from pyautogui import position
from keyboard import wait

while True:
    wait("+")
    print(*position())