/*
 * [Gamemode] Toy Of Wars
 * Mode         : TDM
 * Map          : Custom locations
 * Release      : v1, 8 aug 2015
 * Updated      : v3e1, 2 nov 2015
 * Status       : Complited
 * Contributors : VanillaRain, Nero_3D, Logofero aka fERO
 * Credits:
 *      SA-MP Multyplayer http://forum.sa-mp.com/forumdisplay.php?f=74
 *          SA-MP Team
 *
 *      Zamaroht's TextDraw Editor
 *          Zamaroht
 *
 *      Streamer http://forum.sa-mp.com/showthread.php?t=102865
 *          Incognito
 *
 *      ColAndreas http://forum.sa-mp.com/showthread.php?t=586068
 *          [uL]Slice, [uL]Chris420, [uL]Pottus, uint32, Crayder

 Description:
 You have to fight on a toy cars against other teams. Every team has its own color.

 Controls:
 Fire - Shot of gun
 Enter - Enter/Exit RC cars

 Commands:
 /team [id] - change team
 /map [id] - change Map
 /boom [playerid] - explode player
 /air - air strike

*/
#if defined SCR_SOURCE
    #undef SCR_SOURCE
#endif
#define SCR_SOURCE              "TW_func.inc"
#define SCR_NAME                "Toy of Wars"
#define SCR_VER                 "v3e1"
#define SCR_REL                 "v1, 8 aug 2015"
#define SCR_UPD                 "v3e1, 2 nov 2015"
#define SCR_CONTRIBUTORS        "VanillaRain, Nero_3D, Logofero"
#define SCR_URL                 "http://forum.sa-mp.com/showthread.php?t=584939"
#define SCR_URL2                "http://forum.sa-mp.com"

#define DEBUG_PRINT             (0)
#define DEBUG_PRINT_LOW         (0)
#define ENABLE_CLIENTINFO       (0) // Show news replace language
#define ENABLE_GAMEINFO         (1) // Show news in game
#define ENABLE_CLIENTMAPNAME    (1) // Show name of map replace language

// General Includes
#include <a_samp>
#include <streamer>
#include <colandreas>
#include <TW_rccars>
#include <TW_func>
#include <TW_gui>
#include <PFCMD>

// Callbacks
forward OnModeInfo();
forward OnStartRound();
forward OnEndRound();
forward OnPlayerEnteredInVehicle(playerid, vehicleid);
forward OnPlayerExitedOfVehicle(playerid, vehicleid);
forward OnPlayerDisconnected(playerid, reason);

// Anticheat system -------------------------------------------------------------------------------
#define COLOR_KICK                  (0xFF8000FF)
new anticheat[MAX_PLAYERS];
// EOF Anticheat system -------------------------------------------------------------------------------

// Custom functions -------------------------------------------------------------------------------
// Saved to TW_func.inc
// EOF Custom functions -------------------------------------------------------------------------------

// Game News -------------------------------------------------------------------------------
#if ENABLE_GAMEINFO
new timer_modeinfo;
new modeinfos[][24]={
    SCR_NAME,
    SCR_URL2,
    SCR_UPD,
    "Attack my Toys!!!",
    "Tanks best weapon",
    "Planes best weapon",
    "Atom bomb and nobody.",
    "For fans RC Models",
    "Use cmd /team",
    "Run,run,run rabbit",
    "Battle City live", // Battle City (Namco) Not forgotten
    "Toy commander"
}
#endif

public OnModeInfo()
{
    #if DEBUG_PRINT_LOW
    printf("[CALLBACK:"SCR_SOURCE"] OnModeInfo()\n");
    #endif

    static
        time,
        lastindex
    ;
    new
        msg[256],
        count = tickcount(),
        index = random(sizeof(modeinfos))
    ;
    while ((lastindex >= 2 && lastindex <= 10) && (index >= 2 && index <= 10) || (lastindex == index)) {
        index = random(sizeof(modeinfos));
    }
    if (time < count) {

        if (index == 0) {
            // Default logo 'Toy Of Wars'
            format(msg, sizeof(msg), "%s", modeinfos[index]);
            time = count + 3 * 60000;
        } else if (index == 1) {
            // Show URL2
            format(msg, sizeof(msg), "%s", modeinfos[index]);
            time = count + 10000;
        } else if (index == 2) {
            // Show update info
            format(msg, sizeof(msg), "Updated: %s", modeinfos[index]);
            time = count + 10000;
        } else {
            // Others words
            format(msg, sizeof(msg), "%s", modeinfos[index]);
            time = count + 2500;
        }

        if (tdraw_geninfo[1] != Text:INVALID_TEXT_DRAW) TextDrawSetString(tdraw_geninfo[1], msg);

        #if ENABLE_CLIENTINFO
        format(msg, sizeof(msg), "Info: %s", modeinfos[index]);
        SetServerLanguage(msg);
        #endif

        lastindex = index;
    }
}
// EOF Game News -------------------------------------------------------------------------------

main() {
    //RespawnAllVehicles();

    #if ENABLE_GAMEINFO
    timer_modeinfo = SetTimer("OnModeInfo", 1000, 1);
    #endif
    
}

public OnGameModeInit()
{
    #if DEBUG_PRINT
    printf("[CALLBACK:"SCR_SOURCE"] OnGameModeInit()\n");
    #endif

    printf("\n-------------------------------------------------------------------------------\n\n\tGamemode     : %s\n\tRelease      : %s\n\tUpdate       : %s\n\tUrl          : %s\n\tContributors : %s", \
        SCR_NAME, SCR_REL, SCR_UPD, SCR_URL, SCR_CONTRIBUTORS
    );
    print("\tCredits      : \n\n\tSA-MP Multyplayer\n\t  SA-MP Team\n\n\tZamaroht's TextDraw Editor\n\t  Zamaroht\n\n\tStreamer\n\t  Incognito\n\n\tColAndreas\n\t  [uL]Slice,\n\t  [uL]Chris420,\n\t  [uL]Pottus,\n\t  uint32,\n\t  Crayder\n\n-------------------------------------------------------------------------------\n");

    CA_RemoveBuilding(-1, 0.0, 0.0, 0.0, 3000.0);
	CA_Init();

    // Set base gamemode settings
    SetGameModeText(SCR_NAME" "SCR_VER);
    UsePlayerPedAnims();
    EnableStuntBonusForAll(false);
    DisableInteriorEnterExits();
    ManualVehicleEngineAndLights();

    // Create TextDraw's
    TW_CreateHudGenInfo();
    TW_CreateHudMapInfo();
    TW_CreateHudTeamList();
    TW_CreateHudAlert();
    TW_CreateHudWin();
    TW_CreateHudCrosshair();

	TW_GetMapState() = GAMESTATE_NONE;
	OnStartRound();
	return 1;
}

public OnGameModeExit()
{
    #if DEBUG_PRINT
    printf("[CALLBACK:"SCR_SOURCE"] OnGameModeExit()\n");
    #endif

    // Destroy timer of event OnModeInfo()
    #if ENABLE_GAMEINFO
    KillTimer(timer_modeinfo);
    #endif

    // Destroy TextDraw's
    TW_DestroyHudGenInfo();
    TW_DestroyHudMapInfo();
    TW_DestroyHudAlert();
    TW_DestroyHudWin();
    TW_DestroyHudTeamList();
    TW_DestroyHudCrosshair();

    // Destroy keep zone
    DestroyCutZone(keepzone);

    // Destroy vehicles
    for (new v = GetVehiclePoolSize(); v >= 1; --v) {
        DestroyVehicle(v);
    }

    TW_GetMapState() = GAMESTATE_NONE;
    return 1;
}

public OnIncomingConnection(playerid, ip_address[], port)
{
    #if DEBUG_PRINT_LOW
    printf("[CALLBACK:"SCR_SOURCE"] OnIncomingConnection:\n\tplayerid %d\n\tip %s\n\tport %d\n", playerid, ip_address, port);
    #endif

    return 1;
}

public OnPlayerConnect(playerid)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:"SCR_SOURCE"] OnPlayerConnect:\n\tplayerid %d\n", playerid);
    #endif

    // Set player random team
    //SetPlayerRandomColor(playerid);
    //SetPlayerColor(playerid, TW_team_colors[random(sizeof(TW_team_colors))] );

    //new teamid = random( TW_GetMapTeams() );
    //SetPlayerTeam(playerid, teamid);
    //SetPlayerColor(playerid, TW_GetTeamColor(teamid));


    // Show Welcome messange
    new msg[256];
    SendClientMessage(playerid, 0xFF0000FF, "-------------------------------------------------------------------------------------------------------------------------------");
    format(msg, sizeof(msg),"*** Welcome to %s (%s)! This is a game for fans of RC Models. Use cmd: /team - change team ***", SCR_NAME, SCR_UPD);
    SendClientMessage(playerid, 0xFF0000FF, msg);
    SendClientMessage(playerid, 0xFF0000FF, "-------------------------------------------------------------------------------------------------------------------------------");

    // Create TextDraw's
    TW_CreateHudCarHP(playerid);
    TW_CreateHudGunAmmo(playerid);
    TW_ShowHudGenInfo(playerid);

    // Show map info
    TW_ShowHudMapInfo(playerid);

    TW_RemoveBuildings(playerid);

    GetPlayerGameState(playerid) = 1;
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:"SCR_SOURCE"] OnPlayerDisconnect:\n\tplayerid %d\n\treason %d\n", playerid, reason);
    #endif

    // Hide TextDraw's
    TW_HideHudTeamList(playerid);
    TW_HideHudGenInfo(playerid);
    TW_HideHudMapInfo(playerid);
    TW_HideHudAlert(playerid);
    TW_HideHudWin(playerid);
    TW_HideHudCarHP(playerid);
    TW_HideHudGunAmmo(playerid);

    // Hide GangZone
    HidePlayerCutZone(playerid, keepzone);

    // Reset player states
    anticheat[playerid] = 0;

    GetPlayerGameState(playerid) = 0;

    SetTimerEx("OnPlayerDisconnected", 200, 0, "ii", playerid, reason);
    return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:"SCR_SOURCE"] OnPlayerRequestClass:\n\tplayerid %d\n\tclassid %d\n", playerid, classid);
    #endif

    new teamid;
    if (GetPlayerGameState(playerid) == 1) {
        GetPlayerGameState(playerid) = 2;
        teamid = random( TW_GetMapTeams() );
        SetPlayerTeam(playerid, teamid);
        SetPlayerColor(playerid, TW_GetTeamColor(teamid));
    }

    // Pass class selector (Fast spawn - no button)
    teamid = GetPlayerTeam(playerid); //GetTeamColorIDOfColor(GetPlayerColor(playerid));

    SetPlayerVirtualWorld(playerid, map_spawns[teamid][WORLDID]);
    SetPlayerInterior(playerid, map_spawns[teamid][INTERIORID]);
    //printf("playerid %d team %d skin %d", playerid, teamid, map_spawns[teamid][SKIN]);
    new skinid = TW_GetTeamSkin(teamid, random( TW_GetTeamMaxSkins(teamid) ) );

    new index = random(map_info[MAX_SPAWNS]);
    while (map_spawns[index][TEAMID] != teamid && map_spawns[index][TEAMID] != -1) {
        index = random(map_info[MAX_SPAWNS]);
    }
    SetSpawnInfo(playerid, teamid, skinid, map_spawns[index][X], map_spawns[index][Y], map_spawns[index][Z], map_spawns[index][ANGLE], 0, 0, 0, 0, 0, 0);
    SpawnPlayer(playerid);
    return 1;
}

public OnPlayerSpawn(playerid)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:"SCR_SOURCE"] OnPlayerSpawn:\n\tplayerid %d\n", playerid);
    #endif

    // Reset player states
    ClearPlayerDamagerID(playerid);

    /* if (TW_GetMapState() == GAMESTATE_NONE) { // First spawn

        //OnStartRound();
        new teamid = GetPlayerTeam(playerid); //GetTeamColorIDOfColor(GetPlayerColor(playerid)); //GetPlayerTeam(playerid);
        new skinid = TW_GetTeamSkin(teamid, random(TW_GetTeamMaxSkins(teamid)) );
        SetSpawnInfo(playerid, teamid, skinid, map_spawns[teamid][X], map_spawns[teamid][Y], map_spawns[teamid][Z], map_spawns[teamid][ANGLE], 0, 0, 0, 0, 0, 0);
    */
    if (TW_GetMapState() == GAMESTATE_STARTROUND) {
        //new index = random(map_info[MAX_SPAWNS]);
        new teamid = GetPlayerTeam(playerid);
        new index = random(map_info[MAX_SPAWNS]);
        while (map_spawns[index][TEAMID] != teamid && map_spawns[index][TEAMID] != -1) {
            index = random(map_info[MAX_SPAWNS]);
        }
        SetPlayerVirtualWorld(playerid, map_spawns[index][WORLDID]);
        SetPlayerInterior(playerid, map_spawns[index][INTERIORID]);
        SetPlayerPos(playerid, map_spawns[index][X], map_spawns[index][Y], map_spawns[index][Z]);
        SetPlayerFacingAngle(playerid, map_spawns[index][ANGLE]);
        //SetSpawnInfo(playerid, index, map_spawns[index][SKIN], map_spawns[index][X], map_spawns[index][Y], map_spawns[index][Z], map_spawns[index][ANGLE], 0, 0, 0, 0, 0, 0);
        SetCameraBehindPlayer(playerid);

        // Show keep zone
        ShowPlayerCutZone(playerid, keepzone, 0xFF000044);
        // Show TextDraw's
        TW_ShowHudTeamList(playerid);
        SetPlayerControllable(playerid, true);
    } else if (TW_GetMapState() == GAMESTATE_ENDROUND) {
        SetAllCamMoveToPlayer(TW_GetMapTeamWinner(), playerid, CAMERA_CUT);
        SetTimerEx("SetPlayerControllable", 1000, false, "ii", playerid, false);
    }
    return 1;
}

public OnVehicleSpawn(vehicleid)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:"SCR_SOURCE"] OnVehicleSpawn:\n\tvehicleid %d\n", vehicleid);
    #endif

    SetVehicleEngine(vehicleid, 1);
    return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:"SCR_SOURCE"] OnPlayerDeath:\n\tplayerid %d\n\tkillerid %d\n\treason %d\n", playerid, killerid, reason);
    #endif

    // Hide TextDraw's
    TW_HideHudCarHP(playerid);
    TW_HideHudGunAmmo(playerid);
    TW_DestroyHudCarView(playerid);

    if (killerid != INVALID_PLAYER_ID || GetPVarInt(playerid, "DAMAGERID") != INVALID_PLAYER_ID) {
        // Player is killed
        if (GetPVarInt(playerid, "DAMAGERID") != INVALID_PLAYER_ID) {
            killerid = GetPVarInt(playerid, "DAMAGERID")
            //SetPVarInt(playerid, "DAMAGERID", INVALID_PLAYER_ID);
        }

        // fix: do not give score for killing himself
        if (playerid != killerid) {
        new teamid = GetPlayerTeam(killerid); //GetTeamColorIDOfColor(GetPlayerColor(killerid));
        new vehicleid = GetPlayerVehicleID(playerid);
        new score;

        if (vehicleid) {
            score = GetVehicleRCCostScores(vehicleid);
        } else {
            score = 50; // For killing humen 50 score
        }
        TW_GetTeamScore(teamid) += score;
        TW_GetTeamKilled(teamid) += 1;
        if (TW_GetTeamScore(teamid) < 0) {
            TW_GetTeamScore(teamid) = 0;
        }
        // Update hud
        TW_ShowHudTeamList(playerid);

        // Give player score
        SetPlayerScore(killerid, GetPlayerScore(killerid)+1);

        // Round winner
        if (TW_GetTeamScore(teamid) >= TW_GetMapScore()) { //
            TW_GetMapTeamWinner() = killerid;
            TW_GetTeamWins(teamid) += 1;
            TW_ShowHudWin();
            //SetAllCamMoveToPlayer(killerid);
            OnEndRound();
            return 1;
        }
        } // EOF fix

        new
            msg[256],
            name[MAX_PLAYER_NAME],
            kname[MAX_PLAYER_NAME]
        ;
        GetPlayerName(killerid, kname, sizeof(kname));
        GetPlayerName(playerid, name, sizeof(name));

        format(msg, sizeof(msg),"~r~%s(%d) Is Killed %s(%d)", kname, killerid, name, playerid);
        GameTextForAll(msg, 6000, 4); //1
    } else {
        // Player is dead
        new
            msg[256],
            name[MAX_PLAYER_NAME],
            teamid = GetPlayerTeam(playerid)
        ;
        if (teamid != 255) TW_GetTeamDied(teamid) += 1;
        GetPlayerName(playerid, name, sizeof(name));
        SetPlayerScore(playerid, GetPlayerScore(playerid)-1);
        if (GetPlayerScore(playerid) < 0) {
            SetPlayerScore(playerid, 0);
        }
        format(msg, sizeof(msg),"~r~%s(%d) Is Dead", name, playerid);
        GameTextForAll(msg, 6000, 4); //1
    }
    // Hide keep zone
    TW_HideHudAlert(playerid);
    HidePlayerCutZone(playerid, keepzone);
    return 1;
}

public OnPlayerUpdate(playerid)
{
    //#if DEBUG_PRINT_LOW
    //printf("[CALLBACK:"SCR_SOURCE"] OnPlayerUpdate:\n\tplayerid %d\n", playerid);
    //#endif

    // Anti cheat -------------------------------------------------------------------------------
    if (GetPlayerWeapon(playerid) > 0 && !anticheat[playerid]) {
        new
            msg[256],
            name[MAX_PLAYER_NAME]
        ;
        GetPlayerName(playerid, name, sizeof(name));
        format(msg, sizeof(msg), "Server: %s(%d) has kicked. Reason: WeaponHack", name, playerid);
        SendClientMessageToAll(COLOR_KICK, msg);

        anticheat[playerid] = 1;
        SetTimerEx("KickPlayer", 200, 0, "i", playerid);
        return 1;
    }
    // EOF Anti cheat -------------------------------------------------------------------------------

    // Get player position -------------------------------------------------------------------------------
    new
        Float: x, Float: y, Float: z
    ;
    new vehicleid = GetPlayerVehicleID(playerid);
    if (vehicleid) {
        new
            msg[256],
            Float:hp
        ;
        GetVehiclePos(vehicleid, x, y, z);
        GetVehicleHealth(vehicleid, hp);
        if (hp < 0.0) hp = 0.0;
        format(msg, sizeof(msg), "%.0f HP", hp);
        PlayerTextDrawSetString(playerid, tdraw_carhp[1], msg);
        format(msg, sizeof(msg), "%d / %d", RCCAR_GetAmmo(vehicleid), RCCAR_GetMaxAmmo(vehicleid));
        PlayerTextDrawSetString(playerid, tdraw_gunammo[1], msg);

        OnPickUpPickup(playerid);
    } else {
        GetPlayerPos(playerid, x, y, z);
    }
    // EOF Get player position -------------------------------------------------------------------------------

    // Keep zone -------------------------------------------------------------------------------
    static
        delay[MAX_PLAYERS]
    ;
    new
        time = tickcount()
    ;
    if (delay[playerid] < time && TW_GetMapState() == GAMESTATE_STARTROUND) {
        if (!IsPointInArea3D(x, y, z, TW_GetMapMinX(), TW_GetMapMinY(), TW_GetMapMinZ(), TW_GetMapMaxX(), TW_GetMapMaxY(), TW_GetMapMaxZ())) {
            SetCutZoneFlashForPlayer(playerid, keepzone, 0xFF000077);
            PlayPlayerSound(playerid, 1091);
            //SendClientMessage(playerid, 0xFF0000FF, "You are outside of battlefield, go back!");
            TextDrawShowForPlayer(playerid, tdraw_alert);
            new
                Float: hp
            ;
            GetPlayerHealth(playerid, hp);
            SetPlayerHealth(playerid, hp - 5.0);
        } else {
            PlayPlayerSound(playerid, 1091);
            SetCutZoneStopFlashForPlayer(playerid, keepzone);
            TextDrawHideForPlayer(playerid, tdraw_alert);
        }
        delay[playerid] = time + 2000;
    }
    // EOF Keep zone -------------------------------------------------------------------------------

    // New callbacks -------------------------------------------------------------------------------
    if (vehicleid && !GetPlayerVID(playerid)) {
        OnPlayerEnteredInVehicle(playerid, vehicleid);
        SetPlayerVID(playerid, vehicleid)
    } else if (!vehicleid && GetPlayerVID(playerid)) {
        OnPlayerExitedOfVehicle(playerid, GetPlayerVID(playerid));
        SetPlayerVID(playerid, 0);
    }
    // Eof naw callbacks -------------------------------------------------------------------------------

    if (GetPlayerAirS(playerid) == 1) {
        if (IsPlayerKeyPress(playerid, KEY_FIRE)) {
            GetPlayerAirS(playerid) = 0;
            TW_HideHudCrosshair(playerid);
            SetPlayerControllable(playerid, true);
            SetCameraBehindPlayer(playerid);
            //SetTimerEx("CreateExplosionByPlayer", 5000, 0, "ifffifi", playerid, GetPlayerAirSX(playerid), GetPlayerAirSY(playerid), GetPlayerAirSZ(playerid), 7, GetPlayerAirSRange(playerid), false);
            new objectid = CreateObject(354, GetPlayerAirSX(playerid), GetPlayerAirSY(playerid), GetPlayerAirSZ(playerid)+GetPlayerAirSHieght(playerid), 0.0, -90.0, 0.0, 200.0);

            #if ENABLE_COLANDREAS
            //new
            //   Float:x,
            //   Float:y,
            //   Float:z
            //;
            if (!CA_RayCastLine(GetPlayerAirSX(playerid), GetPlayerAirSY(playerid), 700.0, GetPlayerAirSX(playerid), GetPlayerAirSY(playerid), -1000.0, x, y, z)) {
                MoveObject(objectid, GetPlayerAirSX(playerid), GetPlayerAirSY(playerid), GetPlayerAirSZ(playerid), GetPlayerAirSSpeed(playerid));
            } else {
                MoveObject(objectid, x, y, z, GetPlayerAirSSpeed(playerid));
            }
            #else
            MoveObject(objectid, GetPlayerAirSX(playerid), GetPlayerAirSY(playerid), GetPlayerAirSZ(playerid), GetPlayerAirSSpeed(playerid));
            #endif

            GetPlayerAirSID(playerid) = objectid;

        } else {

        if (IsPlayerKeyPress(playerid, KEY_W)) {
            GetPlayerAirSY(playerid) += GetPlayerAirSSpeed(playerid);
            SetPlayerCameraPos(playerid, GetPlayerAirSX(playerid), GetPlayerAirSY(playerid), GetPlayerAirSZ(playerid)+GetPlayerAirSHieght(playerid));
            SetPlayerCameraLookAt(playerid, GetPlayerAirSX(playerid), GetPlayerAirSY(playerid)+0.05, GetPlayerAirSZ(playerid)-0.5, CAMERA_MOVE);
        }
        if (IsPlayerKeyPress(playerid, KEY_A)) {
            GetPlayerAirSX(playerid) += GetPlayerAirSSpeed(playerid);
            SetPlayerCameraPos(playerid, GetPlayerAirSX(playerid), GetPlayerAirSY(playerid), GetPlayerAirSZ(playerid)+GetPlayerAirSHieght(playerid));
            SetPlayerCameraLookAt(playerid, GetPlayerAirSX(playerid), GetPlayerAirSY(playerid)+0.05, GetPlayerAirSZ(playerid)-0.5, CAMERA_MOVE);
        }
        if (IsPlayerKeyPress(playerid, KEY_S)) {
            GetPlayerAirSY(playerid) -= GetPlayerAirSSpeed(playerid);
            SetPlayerCameraPos(playerid, GetPlayerAirSX(playerid), GetPlayerAirSY(playerid), GetPlayerAirSZ(playerid)+GetPlayerAirSHieght(playerid));
            SetPlayerCameraLookAt(playerid, GetPlayerAirSX(playerid), GetPlayerAirSY(playerid)+0.05, GetPlayerAirSZ(playerid)-0.5, CAMERA_MOVE);
        }
        if (IsPlayerKeyPress(playerid, KEY_D)) {
            GetPlayerAirSX(playerid) -= GetPlayerAirSSpeed(playerid);
            SetPlayerCameraPos(playerid, GetPlayerAirSX(playerid), GetPlayerAirSY(playerid), GetPlayerAirSZ(playerid)+GetPlayerAirSHieght(playerid));
            SetPlayerCameraLookAt(playerid, GetPlayerAirSX(playerid), GetPlayerAirSY(playerid)+0.05, GetPlayerAirSZ(playerid)-0.5, CAMERA_MOVE);
        }
        //InterpolateCameraPos(playerid, Float:FromX, Float:FromY, Float:FromZ, Float:ToX, Float:ToY, Float:ToZ, 1000, CAMERA_CUT);
        //InterpolateCameraLookAt(playerid, Float:FromX, Float:FromY, Float:FromZ, Float:ToX, Float:ToY, Float:ToZ, 1000, CAMERA_CUT);
        }
    }
    return 1;
}

/*
public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
    printf("OnVehicleDamageStatusUpdate vehicleid %d playerid %d", vehicleid, playerid);

    new msg[256];
    format(msg, sizeof(msg), "OnVehicleDamageStatusUpdate vehicleid %d playerid %d", vehicleid, playerid);

    SendClientMessageToAll(-1, msg);
    return 1;
}
*/

public OnPlayerText(playerid, text[])
{
    #if DEBUG_PRINT
    printf("[CALLBACK:"SCR_SOURCE"] OnPlayerText:\n\tplayerid %d\n\ttext %s\n", playerid, text);
    #endif

    new
        msg[256],
        name[MAX_PLAYER_NAME]
    ;
    GetPlayerName(playerid, name, sizeof(name));
    new teamid = GetPlayerTeam(playerid);
    format(msg, sizeof(msg), "[Team: %s] %s(%d): {FFFFFF}%s", TW_GetTeamName(teamid), name, playerid, text);
    SendClientMessageToAll(GetPlayerColor(playerid), msg);
    SetPlayerChatBubble(playerid, msg, GetPlayerColor(playerid), 60.0, 5000);
    return 0;
}

CMD:Commands(playerid, params[]) {

	if (CMD_IsExec(playerid, "/team")) {
        new
            msg[256]
        ;
	    if (CMD_ArgString(playerid, 1) == '\0') {
            format(msg, sizeof(msg), "Invalid cmd. Use: /team [0-%d]", TW_GetMapTeams()-1);
            SendClientMessage(playerid, 0xFF0000FF, msg);
            return 1;
	    }
	    new
	       name[MAX_PLAYER_NAME]
	    ;
        if (CMD_ArgInt(playerid, 1) < 0 || CMD_ArgInt(playerid, 1) >= TW_GetMapTeams()) {
            format(msg, sizeof(msg), "Invalid team ID. Limit: 0 to %d", TW_GetMapTeams()-1);
            SendClientMessage(playerid, 0xFF0000FF, msg);
            return 1;
        }
        SetPlayerColor(playerid, TW_GetTeamColor(CMD_ArgInt(playerid, 1)));
	    SetPlayerTeam(playerid, CMD_ArgInt(playerid, 1));
        GetPlayerName(playerid, name, sizeof(name));
  		format(msg, sizeof(msg),"*** %s(%d) changed his team on %s", name, playerid, TW_GetTeamName(CMD_ArgInt(playerid, 1)));
  		SendClientMessageToAll(TW_GetTeamColor(CMD_ArgInt(playerid, 1)), msg);
	    //ForceClassSelection(playerid);
	    new skinid = TW_GetTeamSkin(CMD_ArgInt(playerid, 1), random(TW_GetTeamMaxSkins(CMD_ArgInt(playerid, 1))) );
	    SetSpawnInfo(playerid, CMD_ArgInt(playerid, 1), skinid, map_spawns[CMD_ArgInt(playerid, 1)][X], map_spawns[CMD_ArgInt(playerid, 1)][Y], map_spawns[CMD_ArgInt(playerid, 1)][Z], map_spawns[CMD_ArgInt(playerid, 1)][ANGLE], 0, 0, 0, 0, 0, 0);
	    SetPlayerHealth(playerid, 0.0);
	    //SpawnPlayer(playerid);
	    return 1;
	}

    if (IsPlayerAdmin(playerid)) {
    if (CMD_IsExec(playerid, "/air")) {
        new
            Float:x,
            Float:y,
            Float:z
        ;
        SetPlayerControllable(playerid, false);
        new vehicleid = GetPlayerVehicleID(playerid);
        if (vehicleid) {
            GetVehiclePos(vehicleid, x, y, z);
        } else {
            GetPlayerPos(playerid, x, y, z);
        }
        SetPlayerAirS(playerid,1,20.0,x,y,z,100.0,20.0);
        SetPlayerCameraPos(playerid, GetPlayerAirSX(playerid), GetPlayerAirSY(playerid), GetPlayerAirSZ(playerid)+GetPlayerAirSHieght(playerid));
        SetPlayerCameraLookAt(playerid, GetPlayerAirSX(playerid), GetPlayerAirSY(playerid)+0.05, GetPlayerAirSZ(playerid)-0.05, CAMERA_CUT);
        TW_ShowHudCrosshair(playerid);
        return 1;
    }
	if (CMD_IsExec(playerid, "/boom")) {
        new
	       msg[256]
	    ;
	    if (CMD_ArgString(playerid, 1) == '\0') {
	       format(msg, sizeof(msg), "Invalid cmd. Use: /boom [playerid]");
	       SendClientMessage(playerid, 0xFF0000FF, msg);
	       return 1;
	    }
	    if (!IsPlayerConnected(CMD_ArgInt(playerid, 1))) {
	       format(msg, sizeof(msg), "Invalid player ID (%d)", CMD_ArgInt(playerid, 1));
	       SendClientMessage(playerid, 0xFF0000FF, msg);
	       return 1;
	    }
	    new
	       //msg[256],
	       Float: x,
	       Float: y,
	       Float: z
	    ;
	    GetPlayerPos(CMD_ArgInt(playerid, 1), x,y,z);
  		CreateExplosionByPlayer(playerid, x, y, z, 11, 20.0, true)
  		new
	       name[MAX_PLAYER_NAME]
	    ;
	    GetPlayerName(CMD_ArgInt(playerid, 1), name, sizeof(name));
  		format(msg, sizeof(msg),"Administrator has exploded %s(%d)", name, CMD_ArgInt(playerid, 1));
  		SendClientMessageToAll(0xFF0000FF, msg);
	    return 1;
	}
	if (CMD_IsExec(playerid, "/map")) {
        new
	       msg[256]
	    ;
	    if (CMD_ArgString(playerid, 1) == '\0') {
	       format(msg, sizeof(msg), "Invalid cmd. Use: /map [0-%d]", sizeof(map_list)-1);
	       SendClientMessage(playerid, 0xFF0000FF, msg);
	       return 1;
	    }
	    if (CMD_ArgInt(playerid, 1) < 0 || CMD_ArgInt(playerid, 1) >= sizeof(map_list)) {
	       format(msg, sizeof(msg), "Invalid Map ID. Limit: 0 to %d", sizeof(map_list)-1);
	       SendClientMessage(playerid, 0xFF0000FF, msg);
	       return 1;
	    }
        TW_GetMapIndex() = CMD_ArgInt(playerid, 1);
        OnStartRound();

        format(msg, sizeof(msg),"Administrator has changed map on '%s'", TW_GetMapName());
  		SendClientMessageToAll(0xFF0000FF, msg);
        return 1;
	}
    }
    return 0;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
    #if DEBUG_PRINT
    printf("[CALLBACK:"SCR_SOURCE"] OnPlayerCommandText:\n\tplayerid %d\n\tcmdtext %s\n", playerid, cmdtext);
    #endif

    return 0;
}

/*
public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:"SCR_SOURCE"] OnPlayerTakeDamage:\n\tplayerid %d\n\tissuerid %d\n\tamount %.1f\n\tweaponid %d\n\tbodypart %d\n", playerid, issuerid, amount, weaponid, bodypart);
    #endif

    new msg[256];
    format(msg, sizeof(msg), "OnPlayerTakeDamage playerid %d issuerid %d amount %.1f weaponid %d bodypart %d", playerid, issuerid, amount, weaponid, bodypart);

    SendClientMessageToAll(-1, msg);
    return 1;
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:"SCR_SOURCE"] OnPlayerGiveDamage:\n\tplayerid %d\n\tdamagedid %d\n\tamount %.1f\n\tweaponid %d\n\tbodypart %d\n", playerid, damagedid, amount, weaponid, bodypart);
    #endif

    new msg[256];
    format(msg, sizeof(msg), "OnPlayerGiveDamage playerid %d damagedid %d amount %.1f weaponid %d bodypart %d", playerid, damagedid, amount, weaponid, bodypart);

    SendClientMessageToAll(-1, msg);
    return 1;
}
*/

public OnObjectMoved(objectid)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:"SCR_SOURCE"] OnObjectMoved:\n\tobjectid %d\n\tshot_objectid %d\n\tshot_vehicleid %d\n\tshot_ownerid %d\n", objectid, gObjectInfo[objectid][OBJECTID], gObjectInfo[objectid][VEHICLEID], gObjectInfo[objectid][OWNERID]);
    #endif

    new
        Float:x,
        Float:y,
        Float:z
    ;
    GetObjectPos(objectid, x, y, z);
    for (new p = GetPlayerPoolSize(); p >= 0; --p) {
        if (GetPlayerAirSID(p) == objectid) {
            DestroyObject(objectid);
            GetPlayerAirSID(p) = INVALID_OBJECT_ID;
            CreateExplosionByPlayer(p, x, y, z, 6, GetPlayerAirSRange(p), false);
            CreateExplosionByPlayer(p, x, y, z, 2, GetPlayerAirSRange(p), false);
        }
    }

    return 1;
}

// Custom callbacks -------------------------------------------------------------------------------
public OnStartRound()
{
    new
        msg[256 * 2]
    ;
    PlayPlayerSound(-1, 1188);
    TW_HideHudWin();
    //ResetTeamScores();
    for (new i; i < sizeof(TW_team_info); i++) {
        TW_GetTeamRang(i) = 0;
        TW_GetTeamKilled(i) = 0;
        TW_GetTeamDied(i) = 0;
        TW_GetTeamScore(i) = 0;
        TW_GetTeamBonus(i) = 0;
        //TW_GetTeamWins(i) = 0;
    }
    ResetPlayerStatus();
    TW_DestroyMap();
    new maps = TW_LoadMapsToList(FILE_MAPLIST);
    if (!maps) {
        printf("Error OnStartRound: The rotation list is not loaded any map. NOTE: Check map list %s", FILE_MAPLIST);
        return true;
    } else {
        if (TW_GetMapIndex() > maps) TW_GetMapIndex() = maps-1;
    }
    //TW_GetMapIndex() = current_mapid;
    TW_GetMapMax() = maps;
    TW_GetMapOldTeams() = TW_GetMapTeams();
    TW_LoadMap(TW_GetMapPathFromIndex(TW_GetMapIndex()));
    TW_BuildMap();
    TW_ShowHudTeamList();
    TW_ShowHudMapInfo();
    // Reset all teams if current team more > max teams
    new 
        teamid,
        skinid
    ;
    //printf("old max teams %d, new max teams %d", TW_GetMapOldTeams(), TW_GetMapTeams());
    if (TW_GetMapOldTeams() != TW_GetMapTeams()) {
        //printf("Reset all teams if current team more > max teams");
        for (new p = GetPlayerPoolSize(); p >= 0; --p) {
            teamid = random( TW_GetMapTeams() );
            skinid = TW_GetTeamSkin(teamid, random( TW_GetTeamMaxSkins(teamid) ) );
            SetPlayerTeam(p, teamid);
            SetPlayerColor(p, TW_GetTeamColor(teamid));
            SetSpawnInfo(p, teamid, skinid, map_spawns[teamid][X], map_spawns[teamid][Y], map_spawns[teamid][Z], map_spawns[teamid][ANGLE], 0, 0, 0, 0, 0, 0);
        }
    }       
    RespawnPlayers();
    format(msg, sizeof(msg),"~r~]]] New Round ]]]~n~~y~Map: ~w~%s~n~~y~RoundScores: ~w~%d", map_info[NAME], map_info[ROUND_SCORE]);
    GameTextForAll(msg, 5000, 5);
    //if (!strlen(map_info[AUTHOR])) map_info[AUTHOR][0] = "Unknown";
    //format(msg, sizeof(msg),"{FF0000}New Round: {FFFFFF}Map %d/%d: %s Version %s RoundScores: %d Author: %s", TW_GetMapIndex()+1, maps, map_info[VERSION], map_info[NAME], map_info[ROUND_SCORE], map_info[AUTHOR]);
    if (strlen(map_info[AUTHOR])) {
        format(msg, sizeof(msg),"New Round: Map %d/%d: '%s' Version %s RoundScores: %d Author: %s",
        TW_GetMapIndex()+1, maps, map_info[NAME], map_info[VERSION], map_info[ROUND_SCORE], map_info[AUTHOR]
        );
    } else {
        format(msg, sizeof(msg),"New Round: Map %d/%d: '%s' Version %s RoundScores: %d",
        TW_GetMapIndex()+1, maps, map_info[NAME], map_info[VERSION], map_info[ROUND_SCORE]
        );
    }
    SendClientMessageToAll(0xFF0000FF, msg);
    TW_GetMapState() = GAMESTATE_STARTROUND;
    return true;
}

public OnEndRound()
{
    TW_GetMapState() = GAMESTATE_ENDROUND;
    //HideAllCutZone(keepzone);
    //DestroyBonus();
    SetAllCamMoveToPlayer(TW_GetMapTeamWinner(), -1, CAMERA_MOVE);
    PlayPlayerSound(-1, 1187);
    TW_HideHudAlert();
    TW_HideHudMapInfo();
    TW_HideHudTeamList();
    TW_GetMapIndex()++;
    if (TW_GetMapIndex() >= TW_GetMapMax()) {
        TW_GetMapIndex() = 0;
    }
    SetTimer("OnStartRound", TW_TIME_NEW_ROUND, 0); // New round
    return true;
}

public OnPlayerEnteredInVehicle(playerid, vehicleid)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:"SCR_SOURCE"] OnPlayerEnteredInVehicle:\n\tplayerid %d\n\tvehicleid %d\n", playerid, vehicleid);
    #endif

    // Show TextDraw's
    TW_ShowHudCarHP(playerid);
    TW_ShowHudGunAmmo(playerid);

    // Recreate RC view TextDraw's
    TW_DestroyHudCarView(playerid);
    TW_CreateHudCarView(playerid);
    TW_ShowHudCarView(playerid);
    return true;
}

public OnPlayerExitedOfVehicle(playerid, vehicleid)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:"SCR_SOURCE"] OnPlayerExitedOfVehicle:\n\tplayerid %d\n\tvehicleid %d\n", playerid, vehicleid);
    #endif

    // Hide TextDraw's
    TW_HideHudCarHP(playerid);
    TW_HideHudGunAmmo(playerid);

    // Hide RC view
    TW_DestroyHudCarView(playerid);
    return true;
}

public OnPlayerDisconnected(playerid, reason)
{
    // Update hud
    TW_HideHudTeamList(playerid);
    return true;
}
// EOF Custom callbacks -------------------------------------------------------------------------------