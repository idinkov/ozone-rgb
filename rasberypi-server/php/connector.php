<?php
class Connector{
    
      
    public function send()
    {
        $mode = $_POST['mode'];
        $action = $_POST['action'];
        
        exec("i2cset -y 1 0x09 0");  
        exec("i2cset -y 1 0x09 {$mode}");
        exec("i2cset -y 1 0x09 {$action}");
    }
    
}

//Do job
Connector::send();