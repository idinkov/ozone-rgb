function connector_send( mode, action )
{
	$.post( '/php/connector.php',
			{mode:mode, action:action},
			function(response){  }
	);
}

var powerState = true;
function togglePower()
{
	if( powerState )
	{
		var action = "off";
		powerState = false;
	}
	else
	{
		var action = "on";
		powerState = true;
	}
	
	connector_send( 'power', action );
}

function toggleColor( action )
{
	connector_send( 'color', action );
}