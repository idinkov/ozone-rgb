import sys
import numpy
import time
from PyQt4 import QtCore, QtGui
import PyQt4.Qwt5 as Qwt
from recorder import *

def plotSomething():
    if SR.newAudio==False: 
        return
    xs,ys=SR.fft()
    #c.setData(xs,ys)
    print ys
    SR.newAudio=False

if __name__ == "__main__":


    SR=SwhRecorder()
    SR.setup()
    SR.continuousStart()
    
    while True:
        plotSomething()
        time.sleep(0.1)
    
    SR.close()