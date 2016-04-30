import urllib2
import urllib

class Curl:
    def onBeat(self):
        req = urllib2.Request('http://10.0.1.13/php/beat.php')
        res = urllib2.urlopen(req)