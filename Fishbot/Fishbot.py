from keyboard import press, release, is_pressed, wait
from pyautogui import position, screenshot, locateOnScreen
import pyautogui
import numpy as np
from time import sleep
from PIL import Image

def getPhoto(biasX, biasY, width, height):
    global pos
    startpos = [*pos]
    startpos[0] -= biasX
    startpos[1] -= biasY
    im = screenshot(region=(*startpos, width, height))
    return im

def addToCache(cache, im):
    if(len(cache) >= 11):
        cache.remove(cache[0])
    cache.append(im)
    return cache

def imSum(im):
    sum = [0, 0, 0]
    for d1 in im:
        for d2 in d1:
            for i in range(3):
                sum[i] += d2[i]
    return sum

def click(button):
    press(button)
    sleep(0.3)
    release(button)

def getDiff(im, imPrev):
    return abs(sum(imSum(im)) - sum(imSum(imPrev)))
def mean(arr):
    return sum(arr)/len(arr)


def run():
    global count
    cache = []
    while True:
        # if count > 25:
        #     return
        # chekFishBuff()
        sleep(1)
        click('f')
        sleep(2)
        im = np.asarray(getPhoto(50, 350, 100, 100))
        imPrev = im
        sleep(0.5)
        for i in range(80):
            if(is_pressed('-')):
                click('f')
                return
            im = np.asarray(getPhoto(50, 150, 100, 100))
            diff = getDiff(im, imPrev)
            cache = addToCache(cache, diff)
            print(diff)
            if((i > 15)  and (diff > 2e5)):
                click('f')
                cache.clear()
                count+=1
                break
            imPrev = im
            sleep(0.2)
        print('------------', count)

def chekFishBuff():
    if(locateOnScreen('buff.png', region=(0, 0, 600, 600), confidence=0.8) == None):
        click('t')

def StoragePhoto(width, height, name):
    im = getPhoto(30, 30, width, height)
    im.save(name)

while True:
    wait('+')
    pos = list(position())
    count = 0
    run()





