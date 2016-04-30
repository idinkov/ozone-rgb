<?php
include("connector.php");

$level = $_POST['level'];

if( $level > 80000 )
    $level = 100;
else 
    $level = ceil( ($level / 80000) * 100 );

Connector::send( 5, $level );