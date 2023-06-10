from keyboard import press, release, is_pressed
from pyautogui import position, screenshot, locateAllOnScreen, locateCenterOnScreen, moveTo, click, center
import pyautogui
from time import sleep
from PIL import Image

def getPhoto(biasX, biasY, width, height):
    startpos = list(position())
    startpos[0] -= biasX
    startpos[1] -= biasY
    im = screenshot(region=(*startpos, width, height))
    return im


def clickb(button):
    press(button)
    sleep(0.3)
    release(button)

def printMousePos():
    print(position())

def dragTo(x, y, duration):
    pyautogui.mouseDown()
    moveTo(x, y, duration=duration)
    pyautogui.mouseUp()

def getFieldsPos():
    size = 50
    im = Image.open('temp.png')#getPhoto(size, size, size, size)
    poss = list(locateAllOnScreen(im, confidence=0.9))
    for i in poss:
        i = center(i)
        print(i)

def run():
    beginpos = [1589, 205]
    dragPos = [1890, 890]
    confirmPos = [866, 586]
    delta = 65
    clickb('b')
    sleep(1)
    im = Image.open('BuidlerInventory.png')
    moveTo(*locateCenterOnScreen(im, confidence=0.7))
    click()
    moveTo(*beginpos)
    click()
    prevPos = [beginpos[0]-delta, beginpos[1]]
    for i in range(10):
        for j in range(5):
            if(is_pressed('-')):
                return
            prevPos[0] += delta
            moveTo(*prevPos)
            dragTo(*dragPos, duration=0.2)
            moveTo(*confirmPos)
            click()
        prevPos[0] = beginpos[0]-delta
        prevPos[1] += delta

    
pyautogui.PAUSE = 0.1



while True:
    if(is_pressed('+')):
        try:
            run()
        except:
            continue
        





