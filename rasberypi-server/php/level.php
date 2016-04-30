<?php

$level = $_POST['level'];

if( $level > 100000 )
    $level = 100;
else 
    $level = ceil( ($level / 100000) * 100 );

echo $level;