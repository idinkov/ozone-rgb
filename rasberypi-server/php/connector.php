<?php
class Connector{
    
      
    public function send( $mode = false, $action = false )
    {
    	if( !$mode )
            $mode = $_POST['mode'];
    	if( !$action )
            	$action = $_POST['action'];
        
        exec("i2cset -y 1 0x09 0");  
        exec("i2cset -y 1 0x09 {$mode}");
        exec("i2cset -y 1 0x09 {$action}");
    }
    
}

//Do job
Connector::send();
