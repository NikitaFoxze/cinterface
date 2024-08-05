/*

	About: Controller interface system
	Author: Foxze

*/

#if defined _interface_config_included
	#endinput
#endif

#define _interface_config_included

/*

	* Defines *

*/

#if !defined MAX_FUNCTION_NAME
	#define MAX_FUNCTION_NAME 32
#endif

// Create textdraws and show
#define InterfaceCreate:%0(%1) \
	forward icr_%0(%1); \
	public icr_%0(%1)

// Closing textdraws and choise hide/destroy
#define InterfaceClosing:%0(%1,%2) \
	forward icg_%0(%1,%2); \
	public icg_%0(%1,%2)

// Close textdraws
#define InterfaceClose:%0(%1) \
	forward ics_%0(%1); \
	public ics_%0(%1)

// Using OnPlayerClickPlayerTextDraw
#define InterfacePlayerClick:%0(%1) \
	forward ipc_%0(%1); \
	public ipc_%0(%1)

// Using OnPlayerClickTextDraw
#define InterfaceClick:%0(%1) \
	forward icl_%0(%1); \
	public icl_%0(%1)

#define Interface: #

/*

	* Vars *

*/

static
	bool:gIsInterfaceOpen[MAX_PLAYERS char],
	gInterfaceFunction[MAX_PLAYERS][MAX_FUNCTION_NAME],
	gInterfaceFunctionClick[MAX_PLAYERS][MAX_FUNCTION_NAME];

/*

	* Functions *

*/

stock Interface_Show(playerid, const function[])
{
	if(Interface_IsOpen(playerid))
		Interface_Close(playerid, gInterfaceFunction[playerid][4]);

	gIsInterfaceOpen{playerid} = true;
	gInterfaceFunction[playerid] = "ipc_";
	gInterfaceFunctionClick[playerid] = "icl_";

	strcat(gInterfaceFunction[playerid], function, sizeof(gInterfaceFunction[]));
	strcat(gInterfaceFunctionClick[playerid], function, sizeof(gInterfaceFunctionClick[]));

	new 
		call_func[MAX_FUNCTION_NAME char] = !"icr_";

	strcat(call_func, function);
	return CallLocalFunction(call_func, "d", playerid);
}

stock Interface_Closing(playerid, const function[], bool:hide)
{
	gIsInterfaceOpen{playerid} = false;
	gInterfaceFunction[playerid][0] = '\0';
	gInterfaceFunctionClick[playerid][0] = '\0';

	new 
		call_func[MAX_FUNCTION_NAME char] = !"icg_";

	strcat(call_func, function);
	return CallLocalFunction(call_func, "dd", playerid, hide);
}

stock Interface_Close(playerid, const function[])
{
	if(!Interface_IsOpen(playerid)) 
		return 0;

	gIsInterfaceOpen{playerid} = false;
	gInterfaceFunction[playerid][0] = '\0';
	gInterfaceFunctionClick[playerid][0] = '\0';

	new 
		call_func[MAX_FUNCTION_NAME char] = !"ics_";

	strcat(call_func, function);
	return CallLocalFunction(call_func, "d", playerid);
}

stock Interface_IsOpen(playerid, const function[] = "")
{
	if(isnull(function))
		return _:gIsInterfaceOpen{playerid};

	if(!isnull(gInterfaceFunction[playerid])
	&& gIsInterfaceOpen{playerid}
	&& strcmp(gInterfaceFunction[playerid][4], function) == 0)
		return 1;

	return 0;
}

/*

	* Callbacks *

*/

/*
    OnPlayerClickPlayerTextDraw
*/

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if(Interface_IsOpen(playerid))
		return CallLocalFunction(gInterfaceFunction[playerid], "dd", playerid, _:playertextid);

	#if defined IC_OnPlayerClickPlayerTextDraw
		return IC_OnPlayerClickPlayerTextDraw(playerid, playertextid);
	#else
		return 0;
	#endif
}

/*
    OnPlayerClickTextDraw
*/

public OnPlayerClickTextDraw(playerid, Text:clickedid) 
{
	if(Interface_IsOpen(playerid))
		return CallLocalFunction(gInterfaceFunctionClick[playerid], "dd", playerid, _:clickedid);

	#if defined IC_OnPlayerClickTextDraw
		return IC_OnPlayerClickTextDraw(playerid, clickedid);
	#else
		return 0;
	#endif
}

/*
    ALS
*/

#if defined _ALS_OnPlayerClickPlayerTextDra\
	|| defined _ALS_OnPlayerClickPlayerTD
	#undef OnPlayerClickPlayerTextDraw
#else
	#define _ALS_OnPlayerClickPlayerTextDra
	#define _ALS_OnPlayerClickPlayerTD
#endif
#define OnPlayerClickPlayerTextDraw IC_OnPlayerClickPlayerTextDraw
#if defined IC_OnPlayerClickPlayerTextDraw
	forward IC_OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid);
#endif


#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw IC_OnPlayerClickTextDraw
#if defined IC_OnPlayerClickTextDraw
	forward IC_OnPlayerClickTextDraw(playerid, Text:clickedid);
#endif