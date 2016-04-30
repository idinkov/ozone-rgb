import sys
import numpy
import time
from PyQt4 import QtCore, QtGui
import PyQt4.Qwt5 as Qwt
from recorder import *
from curl import *

step = 0;

def plotSomething( step ):
    if SR.newAudio==False: 
        return False
    ys=SR.fft()
    newys=int(ys[0])
    
    SR.newAudio=False
    
    data = urllib.urlencode({'level' : newys})
    req = urllib2.Request("http://10.0.1.13/php/level.php", data)
    res = urllib2.urlopen(req)
    html =  res.read()
    print html
    
    if newys > 80000:
        #print newys
        #print step
        
        if step == 0:
            req = urllib2.Request('http://10.0.1.13/php/beat.php')
            urllib2.urlopen(req)
            
        return True
    
    return False

if __name__ == "__main__":

    SR=SwhRecorder()
    SR.setup()
    SR.continuousStart()
    while True:
            
        if plotSomething( step ):
            step = 1
        
        if step != 0:
            step += 1
            if step == 4:
                step = 0
            
        time.sleep(0.1)
    
    SR.close()