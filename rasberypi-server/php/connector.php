<?php
class Connector{
    
    //Define local Arduino Master IP
    private static $ip = '10.0.1.69';
    
    private function _curl( $url, $params = [] )
    {
        if( count( $params ) )
            $url .= "?".http_build_query( $params );
        
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        $output = curl_exec($ch);
        curl_close($ch);
        
        return $output;
    }
    
    public function send()
    {
        $mode = $_POST['mode'];
        $action = $_POST['action'];
        
        $params = [ 'mode' => $mode,
                    'action' => $action ];
        
        $url = self::$ip;
        
        echo self::_curl( $url, $params );
    }
    
}

//Do job
Connector::send();