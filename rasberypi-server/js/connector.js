function connector_send( mode, action )
{
	$.post( '/php/connector.php',
			{mode:mode, action:action},
			function(response){  }
	);
}


function connector_auto(action)
{
	connector_send('color',action);
	
	if( action == 10 )
		action = 20;
	else if ( action == 20 )
		action = 30;
	else if( action == 30)
		action = 10;
	
	setTimeout('connector_auto('+action+');', 200);
}


var powerState = true;
function togglePower()
{
	if( powerState )
	{
		var action = 1;
		powerState = false;
	}
	else
	{
		var action = 2;
		powerState = true;
	}
	
	connector_send( 1, action );
}

function toggleColor( action )
{
	connector_send( 2, action );
}

function toggleParty()
{
	connector_send( 4, 1 );
}