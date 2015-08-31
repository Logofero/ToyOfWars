/*
 * [Gamemode] Toy Of Wars (Based [include]RCTigerGun)
 * Server       : sa-mp 0.3.7
 * Release      : v1, 8 aug 2015
 * Contributors : VanillaRain, Nero_3D, Logofero aka fERO
 * Credits      : Zamaroht - tool 'Zamaroht's TextDraw Editor'
 
 Description:   
 You have to fight in the toy car in the desert for one of the teams. 
 
 Total teams:
 1 Red Team
 2 Green
 3 Blue
 4 Purple
 5 Yellow
 6 White

 Units: 
 Tank - RCTiger,
 Car - RCBandit, 
 Helicopter - RCRaider,
 Helicopter - RCGoblin, 
 Airplane - Baron
 
 Controls:
 Fire - Shot of gun
 Enter - Enter/Exit RC cars
*/
#define SCR_NAME            "Toy of Wars"
#define SCR_REL             "v1, 8 aug 2015"
#define SCR_UPD             "v1, 8 aug 2015"
#define SCR_CONTRIBUTORS    "VanillaRain, Nero_3D, Logofero"
#define SCR_CREDITS         "Zamaroht"

#include <a_samp>
#include <rctigergun>

new TW_team_skins[]={120, 107, 115, 104, 110, 100};
new TW_team_colors[]={
    0xFF0000FF,
    0x00FF00FF,
    0x307DFEFF,
    0xFF00FFFF,
    0xFFFF00FF,
    0xFFFFFFFF
};
new TW_team_ncolors[][8]={
    "Red",
    "Green",
    "Blue",
    "Purple",
    "Yellow",
    "White"
};
enum E_TW_TEAM_SPAWNS {
    M, Float:X, Float:Y, Float:Z, Float:A
}
new Float:TW_team_spawns[][E_TW_TEAM_SPAWNS]={
    {564,186.8744,2457.9622,15.6485,353.6849},
    {564,297.2267,2552.5649,15.9896,148.8161},
    {564,130.5372,2570.4592,15.5857,206.7869},
    {564,337.9150,2458.8169,15.6506,17.4222},
    {564,407.9163,2542.4590,15.6870,150.9815},
    {564,122.3155,2456.9219,15.6538,313.9525},   
    {564,282.4990,2551.4607,15.9881,200.8863},
    {564,252.0264,2448.9578,15.6537,3.3902},
    {564,236.0696,2547.8904,15.9062,185.8480},
    {441,339.0960,2538.3423,15.9624,184.9098},
    {564,430.4706,2479.0410,15.6537,46.2860},
    {564,435.4735,2535.3398,15.5344,104.4680},   
    {564,317.4437,2540.0908,15.9809,204.5701},
    {564,332.5363,2538.4146,15.9735,167.4324},
    {564,383.8864,2588.0435,15.6070,188.3061},
    {441,428.1509,2548.7959,15.3754,87.6297},
    {564,427.9746,2544.1382,15.4331,92.9834},
    {465,368.1618,2537.2239,15.8201,177.2921}, // heli 1
    {501,363.0760,2537.0415,15.8453,178.4647}, // heli 2    
    {464,403.5965,2441.6038,15.9549,359.5815} // plane
};

main () {
    printf("\n-------------------------------------------------------------------------------\n\n\tGamemode     : %s\n\tRelease      : %s\n\tContributors : %s\n\tCredits      : %s\n\n-------------------------------------------------------------------------------\n", \
    SCR_NAME, SCR_REL, SCR_CONTRIBUTORS, SCR_CREDITS
    ); 
}

public OnGameModeInit()
{
    SetGameModeText(SCR_NAME);
    AddPlayerClass(0, 0.0, 0.0, 2.0, 0.0, 0, 0, 0, 0, 0, 0);
    SetWorldTime(0);
    
    // Tank and player spawns 
    for (new i; i < sizeof(TW_team_spawns); i++) {
        //AddPlayerClassEx(i, TW_team_skins[i], TW_team_spawns[i][0], TW_team_spawns[i][1], TW_team_spawns[i][2], TW_team_spawns[i][3], 0, 0, 0, 0, 0, 0);
        AddStaticVehicleEx(TW_team_spawns[i][M], TW_team_spawns[i][X], TW_team_spawns[i][Y], TW_team_spawns[i][Z], TW_team_spawns[i][A], 0, 0, 60);
    }    
	return 1;
}

public OnIncomingConnection(playerid, ip_address[], port) 
{
    return 1;
}

public OnPlayerConnect(playerid) 
{
    SetPlayerRandomColor(playerid);
    
    new msg[256];
    SendClientMessage(playerid, 0xFF0000FF, "-------------------------------------------------------------------------------------------------------------------------------");
    format(msg, sizeof(msg),"*** Welcome to %s (%s)! This is a game for fans of RC Models. Use cmd: /team - change team ***", SCR_NAME, SCR_UPD);
    SendClientMessage(playerid, 0xFF0000FF, msg);
    SendClientMessage(playerid, 0xFF0000FF, "-------------------------------------------------------------------------------------------------------------------------------");
    //new name[MAX_PLAYER_NAME];
    //GetPlayerName(playerid, name, sizeof(name));
    //format(msg, sizeof(msg),"~r~Welcome to %s!", SCR_NAME);
    //GameTextForPlayer(playerid, msg, 6000, 5);
    return 1;
}

public OnPlayerDisconnect(playerid, reason) 
{
    return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
    new teamid = GetTeamColorIDOfColor(GetPlayerColor(playerid));   
    SetSpawnInfo(playerid, teamid, TW_team_skins[teamid], TW_team_spawns[teamid][X], TW_team_spawns[teamid][Y], TW_team_spawns[teamid][Z], TW_team_spawns[teamid][A], 0, 0, 0, 0, 0, 0);
    SpawnPlayer(playerid);
    return 1;
}

public OnPlayerSpawn(playerid) 
{
    new msg[256];
    new teamid = GetTeamColorIDOfColor(GetPlayerColor(playerid)); 
    format(msg, sizeof(msg),"~r~You team is %s!", TW_team_ncolors[teamid]);
    GameTextForPlayer(playerid, msg, 6000, 5);
    SetCameraBehindPlayer(playerid);
    return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
    if (killerid != INVALID_PLAYER_ID) {
        new msg[256];
        new kname[MAX_PLAYER_NAME];
        new name[MAX_PLAYER_NAME];        
        GetPlayerName(playerid, name, sizeof(name));
        GetPlayerName(killerid, kname, sizeof(kname));       
        //new teamid = GetTeamColorIDOfColor(GetPlayerColor(playerid)); 
        //new kteamid = GetTeamColorIDOfColor(GetPlayerColor(killerid));                 
        SetPlayerScore(killerid, GetPlayerScore(killerid)+1);
        format(msg, sizeof(msg),"~r~%s(%d) <killed> %s(%d)", kname, killerid, name, playerid);      
        GameTextForAll(msg, 6000, 5); 
    } else {
        new msg[256];
        new name[MAX_PLAYER_NAME];        
        GetPlayerName(playerid, name, sizeof(name));
        SetPlayerScore(playerid, GetPlayerScore(playerid)-1);
        if (GetPlayerScore(playerid) < 0) SetPlayerScore(playerid, 0);
        
        format(msg, sizeof(msg),"~r~%s(%d) <dead>", name, playerid);      
        GameTextForAll(msg, 6000, 5);          
    }
    return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
    /*
	if (strcmp("/tank", cmdtext, true, 10) == 0)
	{
	    new msg[256]; 
	    new Float:x, Float:y, Float:z, Float:a;
	    GetPlayerPos(playerid, x,y,z);
	    GetPlayerFacingAngle(playerid, a);
  		CreateVehicle(564, x,y,z, a, -1,-1, 60);
  		//PutPlayerInVehicle(playerid, id, 0);	

        new name[MAX_PLAYER_NAME];
        GetPlayerName(playerid, name, sizeof(name));  		
  		format(msg, sizeof(msg),"*** %s(%d) maked new tank.", name, playerid);	
  		SendClientMessageToAll(0x00FF10FF, msg);
	    return 1;
	} 
	*/  	
	if (strcmp("/team", cmdtext, true, 10) == 0)
	{	
	    SetPlayerRandomColor(playerid);
        new msg[256]; 
        new name[MAX_PLAYER_NAME];
        GetPlayerName(playerid, name, sizeof(name));  	
        new teamid = GetTeamColorIDOfColor(GetPlayerColor(playerid));           	
  		format(msg, sizeof(msg),"*** %s(%d) changed his team on %s", name, playerid, TW_team_ncolors[teamid]);	
  		SendClientMessageToAll(TW_team_colors[teamid], msg);
        //SetSpawnInfo(playerid, teamid, TW_team_skins[teamid], TW_team_spawns[teamid][X], TW_team_spawns[teamid][Y], TW_team_spawns[teamid][Z], TW_team_spawns[teamid][A], 0, 0, 0, 0, 0, 0);	    
	    ForceClassSelection(playerid);
	    //SpawnPlayer(playerid);
	    SetPlayerHealth(playerid, 0.0);
	    return 1;
	}	
    return 0;
}