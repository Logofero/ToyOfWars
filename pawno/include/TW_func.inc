/*
 * [include] TW_func maked for gamemode Toy Of Wars
 * Updated : 9:37 31.10.2015
 * Author  : Logofero aka fERO
 * Credits :
 *      SA-MP Multyplayer http://forum.sa-mp.com/forumdisplay.php?f=74
 *          SA-MP Team
 *
 *      Streamer http://forum.sa-mp.com/showthread.php?t=102865
 *          Incognito
 *
 *      ColAndreas http://forum.sa-mp.com/showthread.php?t=586068
 *          [uL]Slice, [uL]Chris420, [uL]Pottus, uint32, Crayder
 */
#if defined _funcs_TW_func_included
  #endinput
#endif
#define _funcs_TW_func_included
#pragma library TW_func

#if !defined _common_included
  #include <common>
#endif

#if defined SCR_SOURCE
    #undef SCR_SOURCE
#endif
#define SCR_SOURCE                                  "TW_func.inc"
#define TW_FUNC_DEBUG_PRINT                         (0)
#define TW_FUNC_DEBUG_PRINT_LOW                     (0)
#define TW_FUNC_DEBUG_MAP                           (1)

// Defineds
#define TW_TIME_NEW_ROUND           (20000)
#define TIME_RESTART_GRAVITY        (60000)

#define COLOR_BONUS                 (0xFF8000FF)
#define SHOW_ALL_BONUS_MSG          (1)

#define GAMESTATE_NONE              (0)
#define GAMESTATE_STARTROUND        (1)
#define GAMESTATE_ENDROUND          (2)

#define MAX_BONUS_TYPES             (8)
#define MAX_TEAMS                   (6)
#define MAX_SKINS                   (312)
#define MAX_ROUND_SCORE             (2)
#define MAX_CUSTOM_MAPS             (100)
#define MAX_REMOVE_BUILDINGS        (1000)
#define MAX_ADDOBJECTS              (1000)
#define MAX_ADDVEHICLES             (1000)
#define MAX_ADDPICKUPS              (1000)
#define MAX_ADDSPAWNS               (1000)
#define MAX_ADDTEAMS                (10)
/*
#define TIME_RESPAWN_REPAIRKIT1     (20000)
#define TIME_RESPAWN_REPAIRKIT2     (40000)
#define TIME_RESPAWN_REPAIRKIT3     (80000)
#define TIME_RESPAWN_MULTISPEED1    (20000)
#define TIME_RESPAWN_MULTISPEED2    (30000)
#define TIME_RESPAWN_MULTISPEED3    (90000)
#define TIME_RESPAWN_AMMO1          (15000)
#define TIME_RESPAWN_AMMO2          (30000)
#define TIME_RESPAWN_ATOMBOMB       (3 * 60000)
#define TIME_RESPAWN_FREEZEBOMB     (2 * 60000)
#define TIME_RESPAWN_NAPALMBOMB     (3 * 60000)
#define TIME_RESPAWN_GRAVITYBOMB    (5 * 60000)
*/
#define PICKUP_REPAIRKIT            (0)
#define PICKUP_MULTISPEED           (1)
#define PICKUP_AMMO                 (2)
#define PICKUP_ATOMBOMB             (3)
#define PICKUP_NAPALMBOMB           (4)
#define PICKUP_FREEZEBOMB           (5)
#define PICKUP_GRAVITYBOMB          (6)

#define MODEL_NONE                  (-1)
#define MODEL_BB_PICKIP             (3096) // Repair key
#define MODEL_BARREL2               (1217) // Blue
#define MODEL_BARREL1               (1218) // Yellow
#define MODEL_BARREL3               (1222) // Red Stones
#define MODEL_BARREL4               (1225) // Red
#define MODEL_BARRELELEXPOS         (1252) // White Bomb
#define MODEL_AMMO_BOX_C2           (2358) // Ammo box
#define MODEL_CR_AMMOBOX            (3013) // Ammo box
#define MODEL_KMB_MINE              (2918) // Mine
#define MODEL_SKULLS                (1313) // White skull heads
#define MODEL_AMMO_CAPSULE          (3082)

#define FILE_MAPLIST                "TW_maps/maps.txt"
#define VAR_MAP_NAME                "Name"
#define VAR_MAP_PATH                "Path"
#define VAR_MAP_VERSION             "Version"
#define VAR_MAP_AUTHOR              "Author"
#define VAR_MAP_ROUNDSCORE          "RoundScore"
#define VAR_MAP_TIME                "Time"
#define VAR_MAP_WEATHER             "Weather"
#define VAR_MAP_SIZE                "Size"
#define VAR_MAP_GRAVITY             "Gravity"
#define VAR_MAP_WORLD               "World"
#define VAR_MAP_INTERIOR            "Interior"
#define VAR_MAP_REMBUILDING         "rembuilding"
#define VAR_MAP_ADDOBJ              "addobj"
#define VAR_MAP_ADDPICKUP           "addpickup"
#define VAR_MAP_ADDCAR              "addcar"
#define VAR_MAP_ADDSPAWN            "addspawn"
#define VAR_MAP_ADDTEAM             "addteam"

// Callbacks
forward OnPickUpPickup(playerid);
forward SetPlayerControllable(playerid, bool:on);   // used as native
forward KickPlayerEx(playerid);                     // used as native
forward ClearPlayerDamagerID(playerid);             // used as native
forward OnMapGravity(Float:gravity);
forward OnBonusRespawn(bonusid);
forward SetPlayerSpec(playerid, bool:on);           // used as native
forward OnVechileEngine(vehicleid, onengine);

// Natives
/*
 * native hexstr(string[]);
 * native Float:floatrandom(Float:min, Float:max);
 * native SetInterior(interiorid);
 * native SetTime(hours, minutes);
 * native SetWorld(worldid);
 * native SetWeatherEx(weatherid);
 * native GetWeatherIDFromName(name[]="Extra Sunny");
 * native GetWeatherName(weatherid);
 * native SetWeatherEx(weatherid);
 * native RemoveBuildings(model, Float:x, Float:y, Float:z, Float:radius);
 * native IsPlayerControllable(playerid);
 * native CreateCutZone(gangzone[4], Float:minx, Float:miny, Float:maxx, Float:maxy);
 * native ShowPlayerCutZone(playerid, gangzone[], color);
 * native HidePlayerCutZone(playerid, gangzone[]);
 * native ShowAllCutZone(gangzone[], color);
 * native HideAllCutZone(gangzone[]);
 * native DestroyCutZone(gangzone[]);
 * native SetCutZoneFlashForPlayer(playerid, gangzone[], color);
 * native SetCutZoneStopFlashForPlayer(playerid, gangzone[]);
 * native SetCutZoneFlashForAll(gangzone[], color);
 * native SetCutZoneStopFlashForAll(gangzone[]);
 * native CreateVehicleEx(model, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, addsiren, worldid, interiorid);
 * native IsPointInArea3D(Float:x, Float:y, Float:z, Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz);
 * native IsPlayerInArea3D(playerid, Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz);
 * native SetAllCamMoveToPlayer(playerid);
 * native GetMaxPlayersOfTeam(teamid);
 * native PlayerText:CreatePlayerTextDrawEx(playerid, text[], Float:x, Float:y, Float:lsize_x, Float:lsize_y, Float:tsize_x, Float:tsize_y, aligment, proportional, shadow, outline, box, font, color, bgcolor, boxcolor, sprite_model, Float:sprite_rx, Float:sprite_ry, Float:sprite_rz, Float:sprite_zoom, sprite_color1, sprite_color2);
 * native Text:CreateTextDrawEx(text[], Float:x, Float:y, Float:lsize_x, Float:lsize_y, Float:tsize_x, Float:tsize_y, aligment, proportional, shadow, outline, box, font, color, bgcolor, boxcolor, sprite_model, Float:sprite_rx, Float:sprite_ry, Float:sprite_rz, Float:sprite_zoom, sprite_color1, sprite_color2);
 * native SetServerLanguage(text[]); // max len 30
 * native SetVehicleEngine(vehicleid, onengine);
 * native GetVehicleEngine(vehicleid);
 * native GetPlayerNick(playerid)
 * native KickPlayer(playerid);
 * native DestroyBonus(bonusid = -1);
 * native CreateBonus(type, model, Float:amount, Float:x, Float:y, Float:z, spawn_range, respawn_time, worldid, interiorid);
 * native ResetTeamScores(teamid = -1);
 * native ResetPlayerControll();
 * native TW_LoadMapsToList(const filename[]=FILE_MAPLIST);
 * native TW_LoadMap(const filename[]);
 * native RespawnMapVehicles();
 * native RespawnPlayers(playerid = -1);
 * native DestroyObjects();
 * native DestroyVehicles();
 * native TW_DestroyMap();
 * native TW_BuildMap();
 * native DestroyRemoveBuilding(objectid = -1);
 * native SetPlayerAirS(playerid, on=1, Float:range, Float:x, Float:y, Float:z, Float:height, Float:speed);
 */

// Enumerators
enum E_MAP_INFO {
    NAME[24],
    Float: MINX,
    Float: MINY,
    Float: MINZ,
    Float: MAXX,
    Float: MAXY,
    Float: MAXZ,
    VERSION[16],
    AUTHOR[24],
    ROUND_SCORE,
    Float: GRAVITY,
    TIME_HOURS, TIME_MINUTES,
    WEATHERID,
    INTERIORID,
    WORLDID,
    INDEX,
    MAPS,
    MAX_SPAWNS
}

enum E_MAP_REMBUILDING {
    ID,
    MODEL,
    Float: X,
    Float: Y,
    Float: Z,
    Float: RADIUS
}

enum E_MAP_OBJECTS {
    ID,
    MODEL,
    Float: X,
    Float: Y,
    Float: Z,
    Float: RX,
    Float: RY,
    Float: RZ,
    Float: DIST
}

enum E_MAP_VEHICLES {
    ID,
    MODEL,
    Float: X,
    Float: Y,
    Float: Z,
    Float: ANGLE,
    COLOR1,
    COLOR2,
    INTERIORID,
    WORLDID,
    RESPAWN_TIME
}

enum E_MAP_PICKUPS {
    ID,
    TYPE,
    MODEL,
    Float: AMOUNT,
    Float: X,
    Float: Y,
    Float: Z,
    Float: SPAWN_RANGE,
    RESPAWN_TIME,
    INTERIORID,
    WORLDID,
    Text3D:TEXTID,
    TIMER,
    ICONID
}

enum E_MAP_SPAWNS {
    ID,
    TEAMID,
    MAX,
    Float: X,
    Float: Y,
    Float: Z,
    Float: ANGLE,
    INTERIORID,
    WORLDID
}

enum E_TEAM_INFO {
    NAME[32],
    SKIN[MAX_SKINS],
    SKINS,
    RCOLOR,
    COLOR,
    RANG,
    KILLED,
    DIED,
    SCORE,
    BONUS,
    WINS,
    PLAYERS
}

enum E_P_INFO {
    GAMESTATE
}

enum E_P_AIRS {
    ON,
    OBJECTID,
    Float: X,
    Float: Y,
    Float: Z,
    Float: RANGE,
    Float: SPEED,
    Float: H
}

// Global arrays
new bonus_name[][24]={
    {"Health kit"},
    {"Multi Speed"},
    {"Ammo box"},
    {"Atom Bomb"},
    {"Napalm Bomb"},
    {"Freeze Bomb"},
    {"Gravity Bomb"},
    {"Unknown"}
};

new weathername[][24]={
	"Extra Sunny",  //0 Los Santos
	"Sunny",  //1 Los Santos
	"Extra Sunny Smog",  //2 Los Santos
	"Sunny Smog",  //3 Los Santos
	"Cloudy",  //4 Los Santos
	"Sunny",  //5 San Fierro
	"Extra Sunny",  //6 San Fierro
	"Cloudy",  //7 San Fierro
	"Rainy", //8 San Fierro
	"Foggy",  //9 San Fierro
	"Sunny",  //10 Las Venturas
	"Extra Sunny",  //11 Las Venturas
	"Cloudy",  //12 Las Venturas
	"Extra Sunny",  //13 Countryside
	"Sunny", //14 Countryside
	"Cloudy",  //15 Countryside
	"Rainy",  //16 Countryside
	"Extra Sunny",  //17 Desert
	"Sunny",  //18 Desert
	"Sandstorm",  //19 Desert
	"Underwater", //20
	"Extracolours1", //21
	"Extracolours2", //22
	"Unknown" //23
};

new TW_team_info[MAX_ADDTEAMS][E_TEAM_INFO];
//new TW_team_skins[]={120, 107, 115, 104, 110, 100};
new map_info[E_MAP_INFO];
new map_rembuilding[MAX_REMOVE_BUILDINGS][E_MAP_REMBUILDING];
new map_objects[MAX_ADDOBJECTS][E_MAP_OBJECTS];
new map_vehicles[MAX_ADDOBJECTS][E_MAP_VEHICLES];
new map_pickups[MAX_ADDPICKUPS][E_MAP_PICKUPS];
new dyn_pickups[MAX_ADDPICKUPS][E_MAP_PICKUPS];
new map_spawns[MAX_ADDSPAWNS][E_MAP_SPAWNS];
new map_list[MAX_CUSTOM_MAPS][256];
new keepzone[4];
new p_info[MAX_PLAYERS][E_P_INFO];
new p_airstrike[MAX_PLAYERS][E_P_AIRS];

// Global vars
new game_winner;
new game_state;
new game_teams[2];
//new current_mapid;

// Macro-functions
#define GetPlayerGameState(%1)                      p_info[%1][GAMESTATE]

#define SetPlayerVID(%1,%2)                         SetPVarInt(%1, "VEHICLEID", (%2))
#define GetPlayerVID(%1)                            GetPVarInt(%1, "VEHICLEID")
#define KickPlayer(%1)                              SetTimerEx("KickPlayerEx", 200, false, "i", (%1))
#define TW_GetMapName()                             map_info[NAME]
#define TW_GetMapAuthor()                           map_info[AUTHOR]
#define TW_GetMapScore()                            map_info[ROUND_SCORE]
#define TW_GetMapTimeH()                            map_info[TIME_HOURS]
#define TW_GetMapTimeM()                            map_info[TIME_MINUTES]
#define TW_GetMapWeather()                          map_info[WEATHERID]
#define TW_GetMapGravity()                          map_info[GRAVITY]
#define TW_GetMapInterior()                         map_info[INTERIORID]
#define TW_GetMapWorld()                            map_info[WORLDID]
#define TW_GetMapMinX()                             map_info[MINX]
#define TW_GetMapMinY()                             map_info[MINY]
#define TW_GetMapMinZ()                             map_info[MINZ]
#define TW_GetMapMaxX()                             map_info[MAXX]
#define TW_GetMapMaxY()                             map_info[MAXY]
#define TW_GetMapMaxZ()                             map_info[MAXZ]
#define TW_GetMapIndex()                            map_info[INDEX]
#define TW_GetMapMax()                              map_info[MAPS]
#define TW_GetMapPathFromIndex(%1)                  map_list[%1]
#define TW_GetMapTeamWinner()                       game_winner
#define TW_GetMapTeams()                            game_teams[0]
#define TW_GetMapOldTeams()                         game_teams[1]
#define TW_GetMapState()                            game_state

#define TW_GetTeamName(%1)                          TW_team_info[%1][NAME]
#define TW_GetTeamSkin(%1,%2)                       TW_team_info[%1][SKIN][%2]
#define TW_GetTeamMaxSkins(%1)                     TW_team_info[%1][SKINS]
#define TW_GetTeamRColor(%1)                        TW_team_info[%1][RCOLOR]
#define TW_GetTeamColor(%1)                         TW_team_info[%1][COLOR]
#define TW_GetTeamScore(%1)                         TW_team_info[%1][SCORE]
#define TW_GetTeamRang(%1)                          TW_team_info[%1][RANG]
#define TW_GetTeamWins(%1)                          TW_team_info[%1][WINS]
#define TW_GetTeamBonus(%1)                         TW_team_info[%1][BONUS]
#define TW_GetTeamKilled(%1)                        TW_team_info[%1][KILLED]
#define TW_GetTeamDied(%1)                          TW_team_info[%1][DIED]
#define TW_GetTeamPlayers(%1)                       TW_team_info[%1][PLAYERS]

#define GetPlayerAirS(%1)                         p_airstrike[%1][ON]
#define GetPlayerAirSID(%1)                       p_airstrike[%1][OBJECTID]
#define GetPlayerAirSX(%1)                        p_airstrike[%1][X]
#define GetPlayerAirSY(%1)                        p_airstrike[%1][Y]
#define GetPlayerAirSZ(%1)                        p_airstrike[%1][Z]
#define GetPlayerAirSSpeed(%1)                    p_airstrike[%1][SPEED]
#define GetPlayerAirSRange(%1)                    p_airstrike[%1][RANGE]
#define GetPlayerAirSHieght(%1)                   p_airstrike[%1][H]
#define SetPlayerAirS(%1,%2,%3,%4,%5,%6,%7,%8)    p_airstrike[%1][ON]=%2; p_airstrike[%1][RANGE]=%3; p_airstrike[%1][X]=%4; p_airstrike[%1][Y]=%5; p_airstrike[%1][Z]=%6; p_airstrike[%1][H]=%7; p_airstrike[%1][SPEED]=%8

// Math section -------------------------------------------------------------------------------
stock hexstr(string[]){
    if (string[0] == 0) return 0;
    new 
        cur = 1,
        result
    ;
    for (new i = strlen(string); i > 0; i--) {
        if (string[i-1] < 58) {
            result += cur*(string[i-1]-48); 
        } else {
            result += cur*(string[i-1]-65+10);
        }
        cur *= 16;
    }
    return result;
}

stock Float:floatrandom(Float:min, Float:max) {
    new num = floatround(min);
	return (float(random((floatround(max) - num) * 100) + (num * 100)) / 100.0);
}
// EOF -------------------------------------------------------------------------------

// Area section -------------------------------------------------------------------------------
// Map Andreas
// -------------------------------
//           +---------B maxx maxy
//           | CutZone |
// minx miny A---------+
// -------------------------------
stock CreateCutZone(gangzone[], Float:minx, Float:miny, Float:maxx, Float:maxy) {

    #if TW_FUNC_DEBUG_PRINT_LOW
    printf("[FUNC:"SCR_SOURCE"] CreateCutZone:\n\tminx %.4f miny %.4f maxx %.4f maxy %.4f\n", minx, miny, maxx, maxy);
    #endif

    gangzone[0] = GangZoneCreate(minx, maxy, maxx, 3000.0);         // top
    gangzone[1] = GangZoneCreate(-3000.0, -3000.0, minx, 3000.0);   // left
    gangzone[2] = GangZoneCreate(minx, -3000.0, maxx, miny);        // bottom
    gangzone[3] = GangZoneCreate(maxx, -3000.0, 3000.0, 3000.0);    // right
}

stock ShowPlayerCutZone(playerid, gangzone[], color) {
    for (new i; i < 4; i++) {
        GangZoneShowForPlayer(playerid, gangzone[i], color);
    }
}

stock HidePlayerCutZone(playerid, gangzone[]) {
    for (new i; i < 4; i++) {
        GangZoneHideForPlayer(playerid, gangzone[i]);
    }
}

stock ShowAllCutZone(gangzone[], color) {
    for (new i; i < 4; i++) {
        GangZoneShowForAll(gangzone[i], color);
    }
}

stock HideAllCutZone(gangzone[]) {
    for (new i; i < 4; i++) {
        GangZoneHideForAll(gangzone[i]);
    }
}

stock DestroyCutZone(gangzone[]) {
    for (new i; i < 4; i++) {
        GangZoneHideForAll(gangzone[i]);
        GangZoneDestroy(gangzone[i]);
    }
}

stock SetCutZoneFlashForPlayer(playerid, gangzone[], color) {
    for (new i; i < 4; i++) {
        GangZoneFlashForPlayer(playerid, gangzone[i], color);
    }
}

stock SetCutZoneStopFlashForPlayer(playerid, gangzone[]) {
    for (new i; i < 4; i++) {
        GangZoneStopFlashForPlayer(playerid, gangzone[i]);
    }
}

stock SetCutZoneFlashForAll(gangzone[], color) {
    for (new i; i < 4; i++) {
        GangZoneFlashForAll(gangzone[i], color);
    }
}

stock SetCutZoneStopFlashForAll(gangzone[]) {
    for (new i; i < 4; i++) {
        GangZoneStopFlashForAll(gangzone[i]);
    }
}

stock IsPointInArea3D(Float:x, Float:y, Float:z, Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz) {
    if (x >= minx && x <= maxx && y >= miny && y <= maxy && z >= minz && z <= maxz) {
        return true;
    }
    return false;
}

stock IsPlayerInArea3D(playerid, Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz) {
    new
        Float: x,
        Float: y,
        Float: z
    ;
    if (!GetPlayerPos(playerid, x, y, z)) return false;
    if (x >= minx && x <= maxx && y >= miny && y <= maxy && z >= minz && z <= maxz) {
        return true;
    }
    return false;
}

// Get over ground of point if it does not return under point
stock CA_FindZ_For2DCoord_Ex(Float:x, Float:y, &Float:z, Float:dist=1.0) {
    if (!CA_RayCastLine(x, y, z + dist, x, y, -1000.0, x, y, z)) {
        if (!CA_RayCastLine(x, y, z - dist, x, y, -1000.0, x, y, z)) {
            CA_RayCastLine(x, y, 700.0, x, y, -1000.0, x, y, z);
        }
        return 0;
    }
    return 1;
}
// EOF -------------------------------------------------------------------------------

// Player section -------------------------------------------------------------------------------
stock IsPlayerControllable(playerid) {
    if (!GetPVarInt(playerid, "CONTROLLABLE")) return true;
    return false;
}

stock GetPlayerNick(playerid) {
	new
	   name[MAX_PLAYER_NAME]
	;
	GetPlayerName(playerid, name, sizeof(name));
	return name;
}

stock ResetTeamScores(teamid = -1) {
    if (teamid < -1 || teamid >= sizeof(TW_team_info)) return false;
    if (teamid != -1) {
        TW_GetTeamRang(teamid) = 0;
        TW_GetTeamKilled(teamid) = 0;
        TW_GetTeamDied(teamid) = 0;
        TW_GetTeamScore(teamid) = 0;
        TW_GetTeamBonus(teamid) = 0;
        TW_GetTeamWins(teamid) = 0;
        return true;
    } else {
        for (new i; i < sizeof(TW_team_info); i++) {
            TW_GetTeamRang(i) = 0;
            TW_GetTeamKilled(i) = 0;
            TW_GetTeamDied(i) = 0;
            TW_GetTeamScore(i) = 0;
            TW_GetTeamBonus(i) = 0;
            TW_GetTeamWins(i) = 0;
        }
    }
    return true;
}

stock ResetPlayerStatus() {
    for (new p = GetPlayerPoolSize(); p >= 0; --p) {
        //TogglePlayerSpectating(p, false);
        SetPlayerControllable(p, true);
        SetCameraBehindPlayer(p);
        SetPlayerHealth(p, 100.0);
        SetPlayerArmour(p, 0.0);
        ResetPlayerMoney(p);
        ResetPlayerWeapons(p);
        SetPlayerInterior(p, 0);
        SetPlayerVirtualWorld(p, 0);
    }
}

stock GetMaxPlayersOfTeam(teamid) {
    new num;
    for (new p = GetPlayerPoolSize(); p >= 0; --p) {
        if (IsPlayerConnected(p) && GetPlayerTeam(p) == teamid) num++;
    }
    return num;
}

stock SetAllCamMoveToPlayer(targetid, playerid = -1, cammode = CAMERA_CUT) {
    if (!IsPlayerConnected(targetid)) return false;
    new
        //Float: x,
        //Float: y,
        //Float: z,
        Float: px,
        Float: py,
        Float: pz,
        Float: a,
        Float: tx,
        Float: ty,
        Float: tz
    ;
    //TogglePlayerControllable(targetid, false);
    SetPlayerControllable(targetid, false);
    new vehicleid = GetPlayerVehicleID(targetid);
    if (vehicleid) GetVehiclePos(vehicleid, tx, ty, tz);
    else GetPlayerPos(targetid, tx, ty, tz);

    if (playerid != -1) {
        SetPlayerControllable(playerid, false); 
        //GetPlayerCameraPos(playerid, px, py, pz);
        GetPlayerPos(playerid, px, py, pz);           
        a = (180.0 - atan2(tx-px, ty-py)) + 90.0;
        SetPlayerCameraPos(playerid, tx+(5.0 * floatcos(a, degrees)), ty+(5.0 * floatsin(a, degrees)), tz + 0.5);
        SetPlayerCameraLookAt(playerid, tx, ty, tz, cammode);  
    } else {
        for (new p = GetPlayerPoolSize(); p >= 0; --p) {
            //TogglePlayerControllable(p, false);
            SetPlayerControllable(p, false); 
            //GetPlayerCameraPos(p, px, py, pz);
            GetPlayerPos(p, px, py, pz);           
            a = (180.0 - atan2(tx-px, ty-py)) + 90.0;
            SetPlayerCameraPos(p, tx+(5.0 * floatcos(a, degrees)), ty+(5.0 * floatsin(a, degrees)), tz + 0.5);
            SetPlayerCameraLookAt(p, tx, ty, tz, cammode);          
        }   
    }
    return true;
}

stock RespawnPlayers(playerid = -1) {
    if (playerid != -1) {
        SpawnPlayer(playerid);
    } else {
        for (new p = GetPlayerPoolSize(); p >= 0; --p) {
            SpawnPlayer(p);
        }
    }
}

stock PlayPlayerSound(playerid = -1, soundid) {
    new Float:x, Float:y, Float:z;    
    if (playerid != -1) {
        PlayerPlaySound(playerid, soundid, x, y, z);
    } else {
        for (new p = GetPlayerPoolSize(); p >= 0; --p) {
            GetPlayerPos(p, x,y,z);
            PlayerPlaySound(p, soundid, x, y, z);
        }
    }
}

stock PlaySoundInPoint(playerid = -1, soundid, Float:x, Float:y, Float:z, Float: range = 100.0) {  
    new 
        Float:px, 
        Float:py, 
        Float:pz,
        vehicleid
    ;
    if (playerid != -1) {
        vehicleid = GetPlayerVehicleID(playerid);
        if (vehicleid) {
            GetVehiclePos(vehicleid, px, py, pz);
        } else {
            GetPlayerPos(playerid, px, py, pz);
        }
        if (VectorSize(x-px, y-py, z-pz) <= range) {
            PlayerPlaySound(playerid, soundid, x, y, z);
        }
    } else {
        for (new p = GetPlayerPoolSize(); p >= 0; --p) {
            vehicleid = GetPlayerVehicleID(p);
            if (vehicleid) {
                GetVehiclePos(vehicleid, px, py, pz);
            } else {
                GetPlayerPos(p, px, py, pz);
            }
            if (VectorSize(x-px, y-py, z-pz) <= range) {
                PlayerPlaySound(p, soundid, x, y, z);
            }
        }
    }
}
// EOF -------------------------------------------------------------------------------

// Object section -------------------------------------------------------------------------------
stock RemoveBuildings(model, Float:x, Float:y, Float:z, Float:radius) {
    for(new p = GetPlayerPoolSize(); p >= 0; --p) {
        RemoveBuildingForPlayer(p, model, x, y, z, radius);
    }
}

stock DestroyObjects() {
    for (new i; i < sizeof(map_objects); i++) {
        if (map_objects[i][MODEL] > 0) {
            #if ENABLE_COLANDREAS
            //CA_DestroyObject_DC(map_objects[i][ID]);
            //if (IsValidDynamicObject(map_objects[i][ID])) DestroyDynamicObject(map_objects[i][ID]);
            CA_DestroyObject_DC(map_objects[i][ID]);
            #else
            DestroyObject(map_objects[i][ID]);
            #endif
            map_objects[i][ID] = INVALID_OBJECT_ID;
            map_objects[i][MODEL] = -1;
        }
    }
}
// EOF -------------------------------------------------------------------------------

// Vehicle section -------------------------------------------------------------------------------
stock CreateVehicleEx(model, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, addsiren, worldid, interiorid) {
    new vehicleid;
    vehicleid = CreateVehicle(model, x, y, z, rotation, color1, color2, respawn_delay, addsiren);
    //vehicleid = AddStaticVehicleEx(model, x, y, z, rotation, color1, color2, respawn_delay, addsiren);

    if (!vehicleid) return INVALID_VEHICLE_ID;
    LinkVehicleToInterior(vehicleid, interiorid);
    SetVehicleVirtualWorld(vehicleid, worldid);
    return vehicleid;
}

stock SetVehicleEngine(vehicleid, onengine) {
    new
        tmponengine, onlights, onalarm, ondoors, onbonnet, onboot, onobjective
    ;
    GetVehicleParamsEx(vehicleid, tmponengine, onlights, onalarm, ondoors, onbonnet, onboot, onobjective);
    SetVehicleParamsEx(vehicleid, onengine, onlights, onalarm, ondoors, onbonnet, onboot, onobjective);
}

stock GetVehicleEngine(vehicleid) {
    new
        onengine, onlights, onalarm, ondoors, onbonnet, onboot, onobjective
    ;
    GetVehicleParamsEx(vehicleid, onengine, onlights, onalarm, ondoors, onbonnet, onboot, onobjective);
    return onengine;
}

stock RespawnMapVehicles() {
    for (new i; i < sizeof(map_vehicles); i++) {
        if (map_vehicles[i][ID] != INVALID_VEHICLE_ID && IsVehicleRC(map_vehicles[i][ID])) SetVehicleToRespawn(map_vehicles[i][ID]);
    }
}

stock DestroyVehicles() {
    for (new i; i < sizeof(map_vehicles); i++) {
        if (map_vehicles[i][MODEL]) {
            DestroyVehicle(map_vehicles[i][ID]);
            map_vehicles[i][ID] = INVALID_VEHICLE_ID;
            map_vehicles[i][MODEL] = 0;
        }
    }
}
// EOF -------------------------------------------------------------------------------

// Pickup section -------------------------------------------------------------------------------
stock GetBonusName(type) {
    if (type >= 0 && type < sizeof(bonus_name)) return bonus_name[type];
    return bonus_name[sizeof(bonus_name)-1];
}

stock GetBonusTypeFromName(name[]) {
    if (!strlen(name)) return 65535;
    for (new i; i < sizeof(bonus_name); i++) {
        if (strcmp(name, bonus_name[i], true)==0) return i;
    }
    return 65535;
}

stock DestroyRemoveBuilding(objectid = -1) {
    if (objectid == INVALID_OBJECT_ID) return false;
    if (objectid != -1) {
        map_rembuilding[objectid][MODEL] = 0;
        map_rembuilding[objectid][X] = 0.0;
        map_rembuilding[objectid][Y] = 0.0;
        map_rembuilding[objectid][Z] = 0.0;
        map_rembuilding[objectid][RADIUS] = 0.0;
    } else {
        for (new i; i < sizeof(map_rembuilding); i++) {
            map_rembuilding[i][MODEL] = 0;
            map_rembuilding[i][X] = 0.0;
            map_rembuilding[i][Y] = 0.0;
            map_rembuilding[i][Z] = 0.0;
            map_rembuilding[i][RADIUS] = 0.0;
        }
    }
    return true;
}

stock DestroyBonus(bonusid = -1) {
    //if (bonusid < -1 || bonusid >= sizeof(dyn_pickups)) return false;
    if (bonusid != -1) {
        if (dyn_pickups[bonusid][ID] != 65535) {
            #if ENABLE_COLANDREAS
                if (IsValidDynamicPickup(dyn_pickups[bonusid][ID])) DestroyDynamicPickup(dyn_pickups[bonusid][ID]);
                if (IsValidDynamicMapIcon(dyn_pickups[bonusid][ICONID])) DestroyDynamicMapIcon(dyn_pickups[bonusid][ICONID]);
                dyn_pickups[bonusid][ICONID] = INVALID_STREAMER_ID;
            #else
                DestroyPickup(dyn_pickups[bonusid][ID]);
            #endif
        }
        dyn_pickups[bonusid][ID] = 65535;

        #if ENABLE_COLANDREAS
        if (IsValidDynamic3DTextLabel(dyn_pickups[bonusid][TEXTID])) {
            DestroyDynamic3DTextLabel(dyn_pickups[bonusid][TEXTID]);
            //dyn_pickups[bonusid][TEXTID] = INVALID_STREAMER_ID;
        }
        #else
        if (dyn_pickups[bonusid][TEXTID] != Text3D:INVALID_3DTEXT_ID) {
            Delete3DTextLabel(dyn_pickups[bonusid][TEXTID]);
        }
        dyn_pickups[bonusid][TEXTID] = Text3D:INVALID_3DTEXT_ID;
        #endif
        
        dyn_pickups[bonusid][TEXTID] = Text3D:INVALID_3DTEXT_ID;
        dyn_pickups[bonusid][MODEL] = 0;
        dyn_pickups[bonusid][TYPE] = 65535;
        dyn_pickups[bonusid][X] = 0.0;
        dyn_pickups[bonusid][Y] = 0.0;
        dyn_pickups[bonusid][Z] = 0.0;
        dyn_pickups[bonusid][AMOUNT] = 0.0;
        dyn_pickups[bonusid][WORLDID] = 0;
        dyn_pickups[bonusid][INTERIORID] = 0;
        dyn_pickups[bonusid][SPAWN_RANGE] = 0.0;
        dyn_pickups[bonusid][RESPAWN_TIME] = 0;
    } else {
        for (new i; i < MAX_ADDPICKUPS; i++) {
            if (dyn_pickups[i][ID] != 65535) {
                #if ENABLE_COLANDREAS
                    if (IsValidDynamicPickup(dyn_pickups[i][ID])) DestroyDynamicPickup(dyn_pickups[i][ID]);
                    if (IsValidDynamicMapIcon(dyn_pickups[i][ICONID])) DestroyDynamicMapIcon(dyn_pickups[i][ICONID]);
                    dyn_pickups[i][ICONID] = INVALID_STREAMER_ID;
                #else
                    DestroyPickup(dyn_pickups[i][ID]);
                #endif
            }
            dyn_pickups[i][ID] = 65535;
                      
            #if ENABLE_COLANDREAS
            if (IsValidDynamic3DTextLabel(dyn_pickups[i][TEXTID])) {
                DestroyDynamic3DTextLabel(dyn_pickups[i][TEXTID]);
                //dyn_pickups[i][TEXTID] = INVALID_STREAMER_ID;
            }
            #else
            if (dyn_pickups[i][TEXTID] != Text3D:INVALID_3DTEXT_ID) {
                Delete3DTextLabel(dyn_pickups[i][TEXTID]);
            }
            dyn_pickups[i][TEXTID] = Text3D:INVALID_3DTEXT_ID;
            #endif
            
            dyn_pickups[i][TEXTID] = Text3D:INVALID_3DTEXT_ID;
            dyn_pickups[i][MODEL] = 0;
            dyn_pickups[i][TYPE] = 65535;
            dyn_pickups[i][X] = 0.0;
            dyn_pickups[i][Y] = 0.0;
            dyn_pickups[i][Z] = 0.0;
            dyn_pickups[i][AMOUNT] = 0.0;
            dyn_pickups[i][WORLDID] = 0;
            dyn_pickups[i][INTERIORID] = 0;
            dyn_pickups[i][SPAWN_RANGE] = 0.0;
            dyn_pickups[i][RESPAWN_TIME] = 0;
        }
    }
    return true;
}

stock CreateBonus(type, model, Float:amount, Float:x, Float:y, Float:z, Float:spawn_range, respawn_time, worldid, interiorid, bool:zmap = true) {

    #if TW_FUNC_DEBUG_PRINT
    printf("[FUNC:"SCR_SOURCE"] CreateBonus:\n\ttype %d model %d amount %.1f\n\txyz %.4f %.4f %.4f\n\tspawn_range %.1f respawn_time %d worldid %d interiorid %d\n", type, model, amount, x, y, z, spawn_range, respawn_time, worldid, interiorid);
    #endif

    for (new i; i < sizeof(dyn_pickups); i++) {
        if (dyn_pickups[i][ID] == 65535) {
            new 
                msg[256],
                icon
            ;
            if (type < 0 || type >= MAX_BONUS_TYPES) type = random(MAX_BONUS_TYPES);
            switch (type) {
                case 0 : {
                    icon = 27;
                    format(msg, sizeof(msg), "{00FF00}Health kit +%.0f hp", amount);
                } case 1 : {
                    icon = 38;
                    format(msg, sizeof(msg), "{FF8080}Multi Speed x%.1f", amount);
                } case 2 : {
                    icon = 6;
                    format(msg, sizeof(msg), "{AAAAAA}Ammo box +%.0f", amount);
                } case 3 : {
                    icon = 43;
                    format(msg, sizeof(msg), "{FFFFFF}Atom Bomb");
                } case 4 : {
                    icon = 44;
                    format(msg, sizeof(msg), "{FFFF80}Napalm Bomb");
                } case 5 : {
                    icon = 48;
                    format(msg, sizeof(msg), "{33CCFF}Freeze Bomb %.1f sec", amount / 1000.0);
                } case 6 : {
                    icon = 49;
                    format(msg, sizeof(msg), "{DDCCFF}Gravity Bomb %.4f", amount);
                } case 7 : {
                    icon = 41;
                    format(msg, sizeof(msg), "{DDFFFF}Air Srike");
                }
                default : {
                    icon = 37;
                }
            }
            if (spawn_range > 0.0) {
                x += floatrandom(-spawn_range, spawn_range);
                y += floatrandom(-spawn_range, spawn_range);
            }
            
            if (zmap) {
                CA_FindZ_For2DCoord_Ex(x, y, z);
                z += 0.7;
            }
            new pickupdid;
            #if ENABLE_COLANDREAS
            pickupdid = CreateDynamicPickup(model, 23, x, y, z, worldid, interiorid, -1, 200.0);
            dyn_pickups[i][ICONID] = CreateDynamicMapIcon(x, y, z, icon, 0xFFFFFFFF, worldid, interiorid, -1, 200.0, MAPICON_LOCAL);
            dyn_pickups[i][TEXTID] = CreateDynamic3DTextLabel(msg, 0xFFFFFFFF, x, y, z + 0.3, 200.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, worldid, interiorid, -1, 200.0);
            #else
            pickupdid = CreatePickup(model, 23, x, y, z, worldid); //14
            dyn_pickups[i][TEXTID] = Create3DTextLabel(msg, 0xFFFFFFFF, x, y, z + 0.3, 3000.0, worldid, 1);
            #endif
            
            
            if (pickupdid == 65535) return 65535;
            dyn_pickups[i][ID] = pickupdid;
            dyn_pickups[i][TYPE] = type;
            dyn_pickups[i][MODEL] = model;
            dyn_pickups[i][X] = x;
            dyn_pickups[i][Y] = y;
            dyn_pickups[i][Z] = z;
            dyn_pickups[i][AMOUNT] = amount;
            dyn_pickups[i][WORLDID] = worldid;
            dyn_pickups[i][INTERIORID] = interiorid;
            dyn_pickups[i][SPAWN_RANGE] = spawn_range;
            dyn_pickups[i][RESPAWN_TIME] = respawn_time;
            
            return pickupdid;
        }
    }
    return 65535;
}
// EOF -------------------------------------------------------------------------------

// TextDraw's section -------------------------------------------------------------------------------
stock PlayerText:CreatePlayerTextDrawEx(playerid, text[], Float:x, Float:y, Float:lsize_x, Float:lsize_y, Float:tsize_x, Float:tsize_y, aligment, proportional, shadow, outline, box, font, color, bgcolor, boxcolor, sprite_model, Float:sprite_rx, Float:sprite_ry, Float:sprite_rz, Float:sprite_zoom, sprite_color1, sprite_color2)
{
    new PlayerText:tdrawid;
    tdrawid = CreatePlayerTextDraw(playerid, x, y, text);
    if (tdrawid == PlayerText:INVALID_TEXT_DRAW) return PlayerText:INVALID_TEXT_DRAW;
    PlayerTextDrawAlignment(playerid, tdrawid, aligment);
    PlayerTextDrawBackgroundColor(playerid, tdrawid, bgcolor);
    PlayerTextDrawFont(playerid, tdrawid, font);
    PlayerTextDrawLetterSize(playerid, tdrawid, lsize_x, lsize_y);
    PlayerTextDrawColor(playerid, tdrawid, color);
    PlayerTextDrawSetOutline(playerid, tdrawid, outline);
    PlayerTextDrawSetProportional(playerid, tdrawid, proportional);
    PlayerTextDrawSetShadow(playerid, tdrawid, shadow);
    PlayerTextDrawUseBox(playerid, tdrawid, box);
    PlayerTextDrawBoxColor(playerid, tdrawid, boxcolor);
    PlayerTextDrawTextSize(playerid, tdrawid, tsize_x, tsize_y);
    PlayerTextDrawSetPreviewModel(playerid, tdrawid, sprite_model);
    PlayerTextDrawSetPreviewRot(playerid, tdrawid, sprite_rx, sprite_ry, sprite_rz, sprite_zoom);
    PlayerTextDrawSetPreviewVehCol(playerid, tdrawid, sprite_color1, sprite_color2);
    return tdrawid;
}

stock Text:CreateTextDrawEx(text[], Float:x, Float:y, Float:lsize_x, Float:lsize_y, Float:tsize_x, Float:tsize_y, aligment, proportional, shadow, outline, box, font, color, bgcolor, boxcolor, sprite_model, Float:sprite_rx, Float:sprite_ry, Float:sprite_rz, Float:sprite_zoom, sprite_color1, sprite_color2)
{
    new Text:tdrawid;
    tdrawid = TextDrawCreate(x, y, text);
    if (tdrawid == Text:INVALID_TEXT_DRAW) return Text:INVALID_TEXT_DRAW;
    TextDrawAlignment(tdrawid, aligment);
    TextDrawBackgroundColor(tdrawid, bgcolor);
    TextDrawFont(tdrawid, font);
    TextDrawLetterSize(tdrawid, lsize_x, lsize_y);
    TextDrawColor(tdrawid, color);
    TextDrawSetOutline(tdrawid, outline);
    TextDrawSetProportional(tdrawid, proportional);
    TextDrawSetShadow(tdrawid, shadow);
    TextDrawUseBox(tdrawid, box);
    TextDrawBoxColor(tdrawid, boxcolor);
    TextDrawTextSize(tdrawid, tsize_x, tsize_y);
    TextDrawSetPreviewModel(tdrawid, sprite_model);
    TextDrawSetPreviewRot(tdrawid, sprite_rx, sprite_ry, sprite_rz, sprite_zoom);
    TextDrawSetPreviewVehCol(tdrawid, sprite_color1, sprite_color2);
    return tdrawid;
}
// EOF -------------------------------------------------------------------------------

// Game mode section -------------------------------------------------------------------------------
stock SetServerLanguage(text[]) {
	new msg[40];
	format(msg, sizeof(msg), "language %s", text);
	SendRconCommand(msg);
}

stock SetInterior(interiorid) {
    for(new p = GetPlayerPoolSize(); p >= 0; --p) {
        SetPlayerInterior(p, interiorid);
    }
}

stock SetTime(hours, minutes) {
    new text[24];
	format(text, sizeof(text), "worldtime %02d:%02d", hours, minutes);
	SendRconCommand(text);
    SetWorldTime(hours);
    //for(new p = GetPlayerPoolSize(); p >= 0; --p) {
    //    SetPlayerTime(p, hours, minutes);
    //}
}

stock SetWorld(worldid) {
    for(new p = GetPlayerPoolSize(); p >= 0; --p) {
        SetPlayerVirtualWorld(p, worldid);
    }
}

stock GetWeatherIDFromName(name[]="Extra Sunny") {
    for (new i; i < sizeof(weathername); i++) {
        if (strcmp(name, weathername[i], true)==0) return i;
    }
    return 0;
}

stock GetWeatherName(weatherid) {
    if (weatherid >= 0 && weatherid < sizeof(weathername)) return weathername[weatherid];
    return weathername[sizeof(weathername)-1];
}

stock SetWeatherEx(weatherid) {
    SetWeather(weatherid);
    for(new p = GetPlayerPoolSize(); p >= 0; --p) {
        SetPlayerWeather(p, weatherid);
    }
}
// EOF -------------------------------------------------------------------------------

// Map Loader section -------------------------------------------------------------------------------
stock TW_LoadMapsToList(const filename[]=FILE_MAPLIST)
{
	new File:fileid = fopen(filename, io_read);
	if (!fileid) {
		printf("Warring TW_LoadAllMaps: file '%s' does not exist or is not readable",filename);
		return false;
	}
	new
	    line[256],
	    text[256],
	    token,
	    index
    ;
    #if TW_FUNC_DEBUG_PRINT_LOW
    printf("MapList:File '%s' loading...", filename);
    #endif
	while (fread(fileid, line, sizeof(line))){
	    // Comments --------------------------------------------
	    if(strfind(line, "#", true, 0) == 0 || strfind(line, ";", true, 0) == 0) continue;

        //#if TW_FUNC_DEBUG_PRINT_LOW
        //printf("%d: line '%s'", index, line);
        //#endif
        token = 0;
        token = token_by_delim(line, text,':', token);
        if (token == -1) continue;

        token++; // pass ':'
        if (strcmp(text, VAR_MAP_PATH, true) == 0) {
            token = token_by_delim(line, text,';', token);
            if (token == -1) continue;

    	    for (new i = strlen(text); i > 0; --i) {
    	       if (text[i] == '\n' || text[i] == '\r') text[i] = '\0';
    	    }
    	    map_list[index] = text;
    	    //format(map_info[NAME], 24, "%s", text);

            #if TW_FUNC_DEBUG_PRINT_LOW
            printf("Map:Path[%d] '%s'", index, map_list[index]);
            #endif
            index++;
        }
	}
	fclose(fileid);
	return index;
}

stock TW_LoadMap(const filename[])
{
	new File:fileid = fopen(filename, io_read);
	if (!fileid) {
		printf("Warring TW_LoadMap: file '%s' does not exist or is not readable",filename);
		return false;
	}
	new
	    line[256],
	    text[256],
	    token,
	    //index,
	    rembuildings,
	    objects,
	    vehicles,
	    pickups,
	    spawns,
	    teams
    ;

    #if TW_FUNC_DEBUG_PRINT_LOW
    printf("Map:File '%s' loading...", filename);
    #endif

	while (fread(fileid, line, sizeof(line))){
	    // Comments --------------------------------------------
	    if(strfind(line, "#", true, 0) == 0 || strfind(line, ";", true, 0) == 0) continue;

        //#if TW_FUNC_DEBUG_PRINT_LOW
        //printf("%d line '%s'", index, line);
        //#endif
        token = 0;
        token = token_by_delim(line, text,':', token);
        if (token == -1) continue;

        token++; // pass ':'
        // --------------------------------------------------------------------------------
        // MAP INFO
        // --------------------------------------------------------------------------------
        // Load Mapname
        if (strcmp(text, VAR_MAP_NAME, true) == 0) {
            token = token_by_delim(line, text,';', token);
            if (token == -1) continue;
            format(map_info[NAME], 24, "%s", text);
            #if TW_FUNC_DEBUG_PRINT_LOW
            printf("Map:Name '%s'", map_info[NAME]);
            #endif
            continue;
        }
        // EOF

        // Load Version
        if (strcmp(text, VAR_MAP_VERSION, true) == 0) {
            token = token_by_delim(line, text,';', token);
            if (token == -1) continue;
            format(map_info[VERSION], 24, "%s", text);
            #if TW_FUNC_DEBUG_PRINT_LOW
            printf("Map:Version '%s'", map_info[VERSION]);
            #endif
            continue;
        }
        // EOF

        // Load Version
        if (strcmp(text, VAR_MAP_VERSION, true) == 0) {
            token = token_by_delim(line, text,';', token);
            if (token == -1) continue;
            format(map_info[VERSION], 24, "%s", text);
            #if TW_FUNC_DEBUG_PRINT_LOW
            printf("Map:Version '%s'", map_info[VERSION]);
            #endif
            continue;
        }
        // EOF

        // Load Author
        if (strcmp(text, VAR_MAP_AUTHOR, true) == 0) {
            token = token_by_delim(line, text,';', token);
            if (token == -1) continue;
            format(map_info[AUTHOR], 24, "%s", text);
            #if TW_FUNC_DEBUG_PRINT_LOW
            printf("Map:Author '%s'", map_info[AUTHOR]);
            #endif
            continue;
        }
        // EOF

        // Load RoundScore
        if (strcmp(text, VAR_MAP_ROUNDSCORE, true) == 0) {
            token = token_by_delim(line, text,';', token);
            if (token == -1) continue;
            map_info[ROUND_SCORE] = strval(text);
            #if TW_FUNC_DEBUG_PRINT_LOW
            printf("Map:RoundScore '%d'", map_info[ROUND_SCORE]);
            #endif
            continue;
        }
        // EOF

        // Load size
        if (strcmp(text, VAR_MAP_SIZE, true) == 0) {

            token = token_by_delim(line, text,',', token);
            if (token == -1) continue;
            map_info[MINX] = floatstr(text);

            token = token_by_delim(line, text,',', token+1);
            if (token == -1) continue;
            map_info[MINY] = floatstr(text);

            token = token_by_delim(line, text,',', token+1);
            if (token == -1) continue;
            map_info[MINZ] = floatstr(text);

            token = token_by_delim(line, text,',', token+1);
            if (token == -1) continue;
            map_info[MAXX] = floatstr(text);

            token = token_by_delim(line, text,',', token+1);
            if (token == -1) continue;
            map_info[MAXY] = floatstr(text);

            token = token_by_delim(line, text,';', token+1);
            if (token == -1) continue;
            map_info[MAXZ] = floatstr(text);

            //DestroyCutZone(keepzone);
            //CreateCutZone(keepzone, map_info[MINX], map_info[MINY], map_info[MAXX], map_info[MAXY]);
            //ShowAllCutZone(keepzone, 0xFF000066);

            #if TW_FUNC_DEBUG_PRINT_LOW
            printf("Map:Size '%.4f, %.4f, %.4f, %.4f, %.4f, %.4f'", map_info[MINX], map_info[MINY], map_info[MINZ], map_info[MAXX], map_info[MAXY], map_info[MAXZ]);
            #endif
            continue;
        }
        // EOF

        // Load gravity
        if (strcmp(text, VAR_MAP_GRAVITY, true) == 0) {
            token = token_by_delim(line, text,';', token);
            if (token == -1) continue;
            map_info[GRAVITY] = floatstr(text);

            //SetGravity(map_info[GRAVITY]);

            #if TW_FUNC_DEBUG_PRINT_LOW
            printf("Map:Gravity '%.6f'", map_info[GRAVITY]);
            #endif
            continue;
        }
        // EOF

        // Load weather
        if (strcmp(text, VAR_MAP_WEATHER, true) == 0) {
            token = token_by_delim(line, text,';', token);
            if (token == -1) continue;
            map_info[WEATHERID] = strval(text);

            //SetWeather(map_info[WEATHERID]);

            #if TW_FUNC_DEBUG_PRINT_LOW
            printf("Map:Weather '%d'", map_info[WEATHERID]);
            #endif
            continue;
        }
        // EOF

        // Load world
        if (strcmp(text, VAR_MAP_WORLD, true) == 0) {
            token = token_by_delim(line, text,';', token);
            if (token == -1) continue;
            map_info[WORLDID] = strval(text);

            //SetWorld(map_info[WORLDID]);

            #if TW_FUNC_DEBUG_PRINT_LOW
            printf("Map:Worldid '%d'", map_info[WORLDID]);
            #endif
            continue;
        }
        // EOF

        // Load interior
        if (strcmp(text, VAR_MAP_INTERIOR, true) == 0) {
            token = token_by_delim(line, text,';', token);
            if (token == -1) continue;
            map_info[INTERIORID] = strval(text);

            //SetInterior(map_info[INTERIORID]);

            #if TW_FUNC_DEBUG_PRINT_LOW
            printf("Map:Interiorid '%d'", map_info[INTERIORID]);
            #endif
            continue;
        }
        // EOF

        // Load time
        if (strcmp(text, VAR_MAP_TIME, true) == 0) {
            // Hours
            token = token_by_delim(line, text,',', token);
            if (token == -1) continue;
            TW_GetMapTimeH() = strval(text);

            // Minutes
            token = token_by_delim(line, text,';', token);
            if (token == -1) continue;
            TW_GetMapTimeM() = strval(text);

            SetWorldTime(TW_GetMapTimeH());
            SetTime(TW_GetMapTimeH(), TW_GetMapTimeM());

            #if TW_FUNC_DEBUG_PRINT_LOW
            printf("Map:Time '%02d:%02d'", TW_GetMapTimeH(), TW_GetMapTimeM());
            #endif
            continue;
        }
        // EOF
        
        // --------------------------------------------------------------------------------
        // TEAMS
        // --------------------------------------------------------------------------------
        // Load team
        if (strcmp(text, VAR_MAP_ADDTEAM, true) == 0) {

            token = token_by_delim(line, text, ',', token);
            if (token == -1) continue;
            format(TW_GetTeamName(teams), 32, "%s", text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            TW_GetTeamRColor(teams) = strval(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            TW_GetTeamColor(teams) = hexstr(text);

            new i;
            while (i < MAX_SKINS) {
                token = token_by_delim(line, text, ',', token+1);
                if (token != -1) {
                    TW_GetTeamSkin(teams,i) = strval(text);
                    //printf("skin[%d]: %d", i, TW_GetTeamSkin(teams,i));
                } else {
                    //token = token_by_delim(line, text, ';', token);
                    if (strlen(text) > 0) {
                        TW_GetTeamSkin(teams,i) = strval(text);
                        //printf("EOF skin[%d]: %d", i, TW_GetTeamSkin(teams,i));
                        i++;
                    }
                    TW_GetTeamMaxSkins(teams) = i;
                    break;
                }
                i++;
            }
          
            #if TW_FUNC_DEBUG_PRINT_LOW
            printf("Map:AddTeam index %d name '%s' color '0x%08h' skins '%d'",
            teams,
            TW_GetTeamName(teams), TW_GetTeamColor(teams),
            TW_GetTeamMaxSkins(teams)
            );
            #endif

            teams++;
            TW_GetMapTeams() = teams;
        }
        // EOF
        
        // --------------------------------------------------------------------------------
        // MAP OBJECTS
        // --------------------------------------------------------------------------------
        // Load rembuilding
        // RemoveBuildingForPlayer(playerid, modelid, Float:fX, Float:fY, Float:fZ, Float:fRadius);
        if (strcmp(text, VAR_MAP_REMBUILDING, true) == 0) {

            token = token_by_delim(line, text, ',', token);
            if (token == -1) continue;
            map_rembuilding[rembuildings][MODEL] = strval(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_rembuilding[rembuildings][X] = floatstr(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_rembuilding[rembuildings][Y] = floatstr(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_rembuilding[rembuildings][Z] = floatstr(text);

            token = token_by_delim(line, text, ';', token+1);
            if (token == -1) continue;
            map_rembuilding[rembuildings][RADIUS] = floatstr(text);

            //RemoveBuildings(map_rembuilding[rembuildings][MODEL], map_rembuilding[rembuildings][X], map_rembuilding[rembuildings][Y], map_rembuilding[rembuildings][Z], map_rembuilding[rembuildings][RADIUS]);

            #if TW_FUNC_DEBUG_PRINT_LOW
            printf("Map:RemBuilging index %d model '%d' xyz '%.4f,%.4f,%.4f' radius '%.4f'",
            rembuildings,
            map_rembuilding[rembuildings][MODEL],

            map_rembuilding[rembuildings][X],
            map_rembuilding[rembuildings][Y],
            map_rembuilding[rembuildings][Z],
            map_rembuilding[rembuildings][RADIUS]
            );
            #endif

            rembuildings++;
        }
        // EOF

        // Load addobj
        // CreateObject(modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ, Float:DrawDistance = 0.0);
        if (strcmp(text, VAR_MAP_ADDOBJ, true) == 0) {

            token = token_by_delim(line, text, ',', token);
            if (token == -1) continue;
            map_objects[objects][MODEL] = strval(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_objects[objects][X] = floatstr(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_objects[objects][Y] = floatstr(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_objects[objects][Z] = floatstr(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_objects[objects][RX] = floatstr(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_objects[objects][RY] = floatstr(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_objects[objects][RZ] = floatstr(text);

            token = token_by_delim(line, text, ';', token+1);
            if (token == -1) continue;
            map_objects[objects][DIST] = floatstr(text);

            #if TW_FUNC_DEBUG_PRINT_LOW
            printf("Map:AddObj index %d model '%d' xyz '%.4f,%.4f,%.4f' rot_xyz '%.4f,%.4f,%.4f' dist '%.4f'",
            objects,
            map_objects[objects][MODEL],
            map_objects[objects][X],
            map_objects[objects][Y],
            map_objects[objects][Z],
            map_objects[objects][RX],
            map_objects[objects][RY],
            map_objects[objects][RZ],
            map_objects[objects][DIST]
            );
            #endif

            objects++;
        }
        // EOF

        // Load addcar
        // CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, addsiren=0);
        if (strcmp(text, VAR_MAP_ADDCAR, true) == 0) {

            token = token_by_delim(line, text, ',', token);
            if (token == -1) continue;
            map_vehicles[vehicles][MODEL] = strval(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_vehicles[vehicles][X] = floatstr(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_vehicles[vehicles][Y] = floatstr(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_vehicles[vehicles][Z] = floatstr(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_vehicles[vehicles][ANGLE] = floatstr(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_vehicles[vehicles][COLOR1] = strval(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_vehicles[vehicles][COLOR2] = strval(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_vehicles[vehicles][INTERIORID] = strval(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_vehicles[vehicles][WORLDID] = strval(text);

            token = token_by_delim(line, text, ';', token+1);
            if (token == -1) continue;
            map_vehicles[vehicles][RESPAWN_TIME] = strval(text);

            //CreateVehicleEx(map_vehicles[vehicles][MODEL], map_vehicles[vehicles][X], map_vehicles[vehicles][Y], map_vehicles[vehicles][Z], map_vehicles[vehicles][ANGLE], map_vehicles[vehicles][COLOR1], map_vehicles[vehicles][COLOR2], map_vehicles[vehicles][RESPAWN_TIME], 0, map_vehicles[vehicles][WORLDID], map_vehicles[vehicles][INTERIORID]);

            #if TW_FUNC_DEBUG_PRINT_LOW
            printf("Map:AddCar index %d model '%d' xyz '%.4f,%.4f,%.4f' angle '%.4f' colors '%d,%d' interior '%d' world '%d' respawn_time '%d'",
            vehicles,
            map_vehicles[vehicles][MODEL],
            map_vehicles[vehicles][X],
            map_vehicles[vehicles][Y],
            map_vehicles[vehicles][Z],
            map_vehicles[vehicles][ANGLE],
            map_vehicles[vehicles][COLOR1],
            map_vehicles[vehicles][COLOR2],
            map_vehicles[vehicles][INTERIORID],
            map_vehicles[vehicles][WORLDID],
            map_vehicles[vehicles][RESPAWN_TIME]
            );
            #endif

            vehicles++;
        }
        // EOF

        // Load addpickup
        // CreateBonus(type, model, Float:amount, Float:x, Float:y, Float:z, Float:spawn_range, respawn_time, worldid, interiorid);
        if (strcmp(text, VAR_MAP_ADDPICKUP, true) == 0) {

            token = token_by_delim(line, text, ',', token);
            if (token == -1) continue;
            map_pickups[pickups][TYPE] = strval(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_pickups[pickups][MODEL] = strval(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_pickups[pickups][AMOUNT] = floatstr(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_pickups[pickups][X] = floatstr(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_pickups[pickups][Y] = floatstr(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_pickups[pickups][Z] = floatstr(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_pickups[pickups][SPAWN_RANGE] = floatstr(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_pickups[pickups][RESPAWN_TIME] = strval(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_pickups[pickups][INTERIORID] = strval(text);

            token = token_by_delim(line, text, ';', token+1);
            if (token == -1) continue;
            map_pickups[pickups][WORLDID] = strval(text);

            //CreateBonus(map_pickups[pickups][TYPE], map_pickups[pickups][MODEL], map_pickups[pickups][AMOUNT], map_pickups[pickups][X], map_pickups[pickups][Y], map_pickups[pickups][Z], map_pickups[pickups][SPAWN_RANGE], map_pickups[pickups][RESPAWN_TIME], map_pickups[pickups][WORLDID], map_pickups[pickups][INTERIORID]);
            //CreatePickup(map_pickups[pickups][MODEL], -1, map_pickups[pickups][X], map_pickups[pickups][Y], map_pickups[pickups][Z], map_pickups[pickups][WORLDID]);

            #if TW_FUNC_DEBUG_PRINT_LOW
            printf("Map:AddPickup index %d type '%d' model '%d' amount '%.1f' xyz '%.4f,%.4f,%.4f' range '%.4f' respawn_time '%d' interior '%d' world '%d'",
            pickups,
            map_pickups[pickups][TYPE],
            map_pickups[pickups][MODEL],
            map_pickups[pickups][AMOUNT],
            map_pickups[pickups][X],
            map_pickups[pickups][Y],
            map_pickups[pickups][Z],
            map_pickups[pickups][SPAWN_RANGE],
            map_pickups[pickups][RESPAWN_TIME],
            map_pickups[pickups][INTERIORID],
            map_pickups[pickups][WORLDID]
            );
            #endif

            pickups++;
        }
        // EOF

        // Load spawn
        // CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, addsiren=0);
        if (strcmp(text, VAR_MAP_ADDSPAWN, true) == 0) {

            token = token_by_delim(line, text, ',', token);
            if (token == -1) continue;
            map_spawns[spawns][TEAMID] = strval(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_spawns[spawns][X] = floatstr(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_spawns[spawns][Y] = floatstr(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_spawns[spawns][Z] = floatstr(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_spawns[spawns][ANGLE] = floatstr(text);

            token = token_by_delim(line, text, ',', token+1);
            if (token == -1) continue;
            map_spawns[spawns][INTERIORID] = strval(text);

            token = token_by_delim(line, text, ';', token+1);
            if (token == -1) continue;
            map_spawns[spawns][WORLDID] = strval(text);

            #if TW_FUNC_DEBUG_PRINT_LOW
            printf("Map:AddSpawn index %d teamid '%d' xyz '%.4f,%.4f,%.4f' angle '%.4f' interior '%d' world '%d'",
            spawns,
            map_spawns[spawns][TEAMID],
            map_spawns[spawns][X],
            map_spawns[spawns][Y],
            map_spawns[spawns][Z],
            map_spawns[spawns][ANGLE],
            map_spawns[spawns][INTERIORID],
            map_spawns[spawns][WORLDID]
            );
            #endif

            spawns++;

            //map_spawns[spawns][MAX] = spawns;
            map_info[MAX_SPAWNS] = spawns;
        }
        // EOF

	}
		
    if (TW_GetMapTeams() < 1) {
        TW_GetMapTeams() = 6;
        
        format(TW_GetTeamName(0), 32, "Red");
        TW_GetTeamRColor(0) = 0;
        TW_GetTeamColor(0) = 0xFF0000FF;
        TW_GetTeamMaxSkins(0) = 1;
        TW_GetTeamSkin(0,0) = 120;
        
        format(TW_GetTeamName(1), 32, "Green");
        TW_GetTeamRColor(1) = 1;
        TW_GetTeamColor(1) = 0x00FF00FF;
        TW_GetTeamMaxSkins(1) = 1;
        TW_GetTeamSkin(1,0) = 107;
        
        format(TW_GetTeamName(2), 32, "Blue");
        TW_GetTeamRColor(2) = 2;
        TW_GetTeamColor(2) = 0x307DFEFF;
        TW_GetTeamMaxSkins(2) = 1;
        TW_GetTeamSkin(2,0) = 115;
        
        format(TW_GetTeamName(3), 32, "Purple");
        TW_GetTeamRColor(3) = 3;
        TW_GetTeamColor(3) = 0xFF00FFFF;
        TW_GetTeamMaxSkins(3) = 1;
        TW_GetTeamSkin(3,0) = 104;
        
        format(TW_GetTeamName(4), 32, "Yellow");
        TW_GetTeamRColor(4) = 4;
        TW_GetTeamColor(4) = 0xFFFF00FF;
        TW_GetTeamMaxSkins(4) = 1;
        TW_GetTeamSkin(4,0) = 110;
        
        format(TW_GetTeamName(5), 32, "White");
        TW_GetTeamRColor(5) = 5;
        TW_GetTeamColor(5) = 0xFFFFFFFF;
        TW_GetTeamMaxSkins(5) = 1;  
        TW_GetTeamSkin(5,0) = 100;      
    }
	
	#if TW_FUNC_DEBUG_MAP
    printf("\n-------------------------------------------------------------------------------\n\n\tMap '%s' loaded.\n\tName '%s'\n\tVersion %s\n\tSize %.4f,%.4f,%.4f, %.4f,%.4f,%.4f\n\tRoundScore %d\n\tTime %02d:%02d\n\tWeather %s (%d)\n\tGravity %.6f\n\tInterior %d\n\tWorld %d\n\tRemovedBuildings %d/%d\n\tObjects %d/%d\n\tPickups %d/%d\n\tVehicles %d/%d\n\tSpawns %d/%d\n\tTeams %d/%d\n\tAuthor %s\n\n-------------------------------------------------------------------------------\n",
        filename,
        map_info[NAME],
        map_info[VERSION],
        map_info[MINX], map_info[MINY], map_info[MINZ], map_info[MAXX], map_info[MAXY], map_info[MAXZ],
        map_info[ROUND_SCORE],
        TW_GetMapTimeH(),
        TW_GetMapTimeM(),
        GetWeatherName(map_info[WEATHERID]), map_info[WEATHERID],
        map_info[GRAVITY],
        map_info[INTERIORID],
        map_info[WORLDID],
        rembuildings, MAX_REMOVE_BUILDINGS,
        objects, MAX_ADDOBJECTS,
        pickups, MAX_ADDPICKUPS,
        vehicles, MAX_ADDVEHICLES,
        spawns, MAX_ADDSPAWNS,
        teams, MAX_ADDTEAMS,
        map_info[AUTHOR]
    );
	#endif
	fclose(fileid);
	return true;
}

stock TW_DestroyMap() {
    DestroyRemoveBuilding();
    DestroyBonus();
    DestroyCutZone(keepzone);
    DestroyObjects();
    DestroyVehicles();
    return true;
}

stock TW_RemoveBuildings(playerid = -1) {
    if (playerid == INVALID_PLAYER_ID) return false;
    if (playerid != -1) {
        for (new i; i < sizeof(map_rembuilding); i++) {
            if (map_rembuilding[i][MODEL]) {
                RemoveBuildingForPlayer(playerid, map_rembuilding[i][MODEL], map_rembuilding[i][X], map_rembuilding[i][Y], map_rembuilding[i][Z], map_rembuilding[i][RADIUS]);
            }
        }
    } else {
        for (new i; i < sizeof(map_rembuilding); i++) {
            if (map_rembuilding[i][MODEL]) {
                for(new p = GetPlayerPoolSize(); p >= 0; --p) {
                    RemoveBuildingForPlayer(p, map_rembuilding[i][MODEL], map_rembuilding[i][X], map_rembuilding[i][Y], map_rembuilding[i][Z], map_rembuilding[i][RADIUS]);
                }
            }
        }
    }
    return true;
}

stock TW_BuildMap() {
    CreateCutZone(keepzone, map_info[MINX], map_info[MINY], map_info[MAXX], map_info[MAXY]);
    ShowAllCutZone(keepzone, 0xFF000044);
    SetGravity(map_info[GRAVITY]);
    SetWeatherEx(map_info[WEATHERID]);
    SetWorld(map_info[WORLDID]);
    SetInterior(map_info[INTERIORID]);
    SetTime(TW_GetMapTimeH(), TW_GetMapTimeM());
    TW_RemoveBuildings(-1);
    // Add objects
    for (new i; i < sizeof(map_objects); i++) {
        if (map_objects[i][MODEL] > 0) {
            #if ENABLE_COLANDREAS
            map_objects[i][ID] = CA_CreateDynamicObject_DC(map_objects[i][MODEL], map_objects[i][X], map_objects[i][Y], map_objects[i][Z], map_objects[i][RX], map_objects[i][RY], map_objects[i][RZ], -1, -1, -1, map_objects[i][DIST], map_objects[i][DIST]);
            #else
            map_objects[i][ID] = CreateObject(map_objects[i][MODEL], map_objects[i][X], map_objects[i][Y], map_objects[i][Z], map_objects[i][RX], map_objects[i][RY], map_objects[i][RZ], map_objects[i][DIST]);
            #endif
        }
    }
    // Add pickups
    for (new i; i < sizeof(map_pickups); i++) {
        if (map_pickups[i][MODEL]) {
            CreateBonus(map_pickups[i][TYPE], map_pickups[i][MODEL], map_pickups[i][AMOUNT], map_pickups[i][X], map_pickups[i][Y], map_pickups[i][Z], map_pickups[i][SPAWN_RANGE], map_pickups[i][RESPAWN_TIME], map_pickups[i][WORLDID], map_pickups[i][INTERIORID]);
        }
    }
    // Add vehicles
    for (new i; i < sizeof(map_vehicles); i++) {
        if (map_vehicles[i][MODEL]) {
            map_vehicles[i][ID] = CreateVehicleEx(map_vehicles[i][MODEL], map_vehicles[i][X], map_vehicles[i][Y], map_vehicles[i][Z], map_vehicles[i][ANGLE], map_vehicles[i][COLOR1], map_vehicles[i][COLOR2], map_vehicles[i][RESPAWN_TIME], 0, map_vehicles[i][WORLDID], map_vehicles[i][INTERIORID]);
        }
    }
    RespawnMapVehicles();
    // Add spawns
    /*
    for (new i; i < MAX_TEAMS; i++) {
        if (map_spawns[i][TEAMID]) {
            for (new p = GetPlayerPoolSize(); p >= 0; --p) {
                new teamid = GetTeamColorIDOfColor(GetPlayerColor(p));
                new skinid;
                SetSpawnInfo(p, teamid, skinid, map_spawns[teamid][X], map_spawns[teamid][Y], map_spawns[teamid][Z], map_spawns[teamid][ANGLE], 0, 0, 0, 0, 0, 0);
            }
            //map_spawns[i][ID] = 1;
        }
    }
    */
    #if ENABLE_CLIENTMAPNAME
    new
        msg[256],
        mapname[20]
    ;
    if (strlen(map_info[NAME]) > 19) {
        format(mapname, sizeof(mapname), "%.16s...", map_info[NAME]);
    } else {
        format(mapname, sizeof(mapname), "%s", map_info[NAME]);
    }
    format(msg, sizeof(msg), "%d/%d: %s", TW_GetMapIndex()+1, TW_GetMapMax(), mapname);
    SetServerLanguage(msg);
    #endif
    return true;
}
// EOF -------------------------------------------------------------------------------

// Custom callbacks -------------------------------------------------------------------------------
public OnPickUpPickup(playerid)
{
    //#if TW_FUNC_DEBUG_PRINT_LOW
    //printf("[CALLBACK:"SCR_SOURCE"] OnPlayerPickUpPickup:\n\tplayerid %d\n", playerid);
    //#endif

    for (new i; i < MAX_ADDPICKUPS; i++) {
        if (dyn_pickups[i][ID] != 65535
        && IsPlayerInRangeOfPoint(playerid, 1.5, dyn_pickups[i][X], dyn_pickups[i][Y], dyn_pickups[i][Z])
        && GetPlayerInterior(playerid) == dyn_pickups[i][INTERIORID]) {
            
            #if ENABLE_COLANDREAS
                if (IsValidDynamicPickup(dyn_pickups[i][ID])) DestroyDynamicPickup(dyn_pickups[i][ID]);
                if (IsValidDynamicMapIcon(dyn_pickups[i][ICONID])) DestroyDynamicMapIcon(dyn_pickups[i][ICONID]);
                dyn_pickups[i][ICONID] = INVALID_STREAMER_ID;
            #else
                DestroyPickup(dyn_pickups[i][ID]);
            #endif
            
            dyn_pickups[i][ID] = 65535;
            new vehicleid = GetPlayerVehicleID(playerid);
            new teamid = GetPlayerTeam(playerid);
            if (teamid != 255) TW_GetTeamBonus(teamid) += 1;
            if (vehicleid) {
                new
                    Float:x,
                    Float:y,
                    Float:z,
                    soundid
                ;
                switch (dyn_pickups[i][TYPE]) {
                    case 0 : {
                        new
                            Float: hp
                        ;
                        soundid = 1134;
                        GetVehicleHealth(vehicleid, hp);
                        RepairVehicle(vehicleid); // Repairs the damage model and resets the health
                        if (RCCAR_GetMaxHP(vehicleid) > 0.0 && hp+dyn_pickups[i][AMOUNT] >= RCCAR_GetMaxHP(vehicleid)) SetVehicleHealth(vehicleid, RCCAR_GetMaxHP(vehicleid));
                        else SetVehicleHealth(vehicleid, hp+dyn_pickups[i][AMOUNT]);

                        new msg[256];
                        format(msg, sizeof(msg), "{00FF00}[ Used Health Kit +%.0f hp... ]",  dyn_pickups[i][AMOUNT]);
                        SetPlayerChatBubble(playerid, msg, COLOR_BONUS, 60.0, 4500);

                        #if SHOW_ALL_BONUS_MSG
                        new name[MAX_PLAYER_NAME];
                        GetPlayerName(playerid, name, sizeof(name));
                        format(msg, sizeof(msg), "{00FF00}* %s(%d) pickuped health kit +%.0f hp", name, playerid, dyn_pickups[i][AMOUNT]);
                        SendClientMessageToAll(-1, msg);
                        #endif
                    } case 1 : {
                        soundid = 1133;
                        //GetPlayerPos(playerid, x, y, z);
                        //GetVehicleZAngle(vehicleid, a);
                        GetVehicleVelocity(vehicleid, x, y, z);
                        SetVehicleVelocity(vehicleid, x * dyn_pickups[i][AMOUNT], y * dyn_pickups[i][AMOUNT], z * dyn_pickups[i][AMOUNT]);
                        //SetVehicleAngularVelocity(vehicleid, x * multnitro, y * multnitro, z);

                        new msg[256];
                        format(msg, sizeof(msg), "{FF8080}[ Used Multi Speed x%.1f... ]",  dyn_pickups[i][AMOUNT]);
                        SetPlayerChatBubble(playerid, msg, COLOR_BONUS, 60.0, 4500);

                        #if SHOW_ALL_BONUS_MSG
                        new name[MAX_PLAYER_NAME];
                        GetPlayerName(playerid, name, sizeof(name));
                        format(msg, sizeof(msg), "{FF8080}* %s(%d) pickuped multi speed x%.1f", name, playerid, dyn_pickups[i][AMOUNT]);
                        SendClientMessageToAll(-1, msg);
                        #endif
                    } case 2 : {
                        soundid = 1137;
                        if (RCCAR_GetAmmo(vehicleid)+floatround(dyn_pickups[i][AMOUNT]) <= RCCAR_GetMaxAmmo(vehicleid)) RCCAR_SetAmmo(vehicleid, RCCAR_GetAmmo(vehicleid) + floatround(dyn_pickups[i][AMOUNT]));
                        else RCCAR_SetAmmo(vehicleid, RCCAR_GetMaxAmmo(vehicleid));

                        new msg[256];
                        format(msg, sizeof(msg), "{AAAAAA}[ Used Ammo +%.0f... ]",  dyn_pickups[i][AMOUNT]);
                        SetPlayerChatBubble(playerid, msg, COLOR_BONUS, 60.0, 4500);

                        #if SHOW_ALL_BONUS_MSG
                        new name[MAX_PLAYER_NAME];
                        GetPlayerName(playerid, name, sizeof(name));
                        format(msg, sizeof(msg), "{AAAAAA}* %s(%d) pickuped ammo +%.0f", name, playerid, dyn_pickups[i][AMOUNT]);
                        SendClientMessageToAll(-1, msg);
                        #endif
                    } case 3 : {
                        soundid = 1137;
                        ExplosionAllByPlayer(playerid, 11, dyn_pickups[i][AMOUNT], false);

                        new msg[256];
                        SetPlayerChatBubble(playerid, "{FFFFFF}[ Used Atom Bomb... ]", COLOR_BONUS, 60.0, 4500);

                        #if SHOW_ALL_BONUS_MSG
                        new name[MAX_PLAYER_NAME];
                        GetPlayerName(playerid, name, sizeof(name));
                        format(msg, sizeof(msg), "{FFFFFF}* %s(%d) pickuped Atom Bomb", name, playerid);
                        SendClientMessageToAll(-1, msg);
                        #endif
                    } case 4 : {
                        soundid = 1137;
                        ExplosionAllByPlayer(playerid, 1, dyn_pickups[i][AMOUNT], false);

                        new msg[256];
                        SetPlayerChatBubble(playerid, "{FFFF80}[ Used Napalm Bomb... ]", COLOR_BONUS, 60.0, 4500);

                        #if SHOW_ALL_BONUS_MSG
                        new name[MAX_PLAYER_NAME];
                        GetPlayerName(playerid, name, sizeof(name));
                        format(msg, sizeof(msg), "{FFFF80}* %s(%d) pickuped Napalm Bomb", name, playerid);
                        SendClientMessageToAll(-1, msg);
                        #endif
                    } case 5 : {
                        soundid = 14406;
                        for (new v = GetVehiclePoolSize(); v >= 1; --v) {
                            if (v != GetPlayerVehicleID(playerid)) {
                                SetVehicleEngine(v, 0);
                                RCCAR_SetGun(v, 0);
                                SetTimerEx("OnVechileEngine", floatround(dyn_pickups[i][AMOUNT]), 0, "ii", v, 1);
                            }
                        }
                        new msg[256];
                        SetPlayerChatBubble(playerid, "{33CCFF}[ Used Freeze Bomb... ]", COLOR_BONUS, 60.0, 4500);

                        #if SHOW_ALL_BONUS_MSG
                        new name[MAX_PLAYER_NAME];
                        GetPlayerName(playerid, name, sizeof(name));
                        format(msg, sizeof(msg), "{33CCFF}* %s(%d) pickuped Freeze Bomb %.1f sec", name, playerid, dyn_pickups[i][AMOUNT] / 1000.0);
                        SendClientMessageToAll(-1, msg);
                        #endif
                    } case 6 : {
                        soundid = 14403;
                        OnMapGravity(dyn_pickups[i][AMOUNT]);
                        SetTimerEx("OnMapGravity", TIME_RESTART_GRAVITY, 0, "f", map_info[GRAVITY]); //TW_GetMapGravity(current_mapid));

                        new msg[256];
                        SetPlayerChatBubble(playerid, "{DDCCFF}[ Used Gravity Bomb... ]", COLOR_BONUS, 60.0, 4500);

                        #if SHOW_ALL_BONUS_MSG
                        new name[MAX_PLAYER_NAME];
                        GetPlayerName(playerid, name, sizeof(name));
                        format(msg, sizeof(msg), "{DDCCFF}* %s(%d) pickuped Gravity Bomb %.4f", name, playerid, dyn_pickups[i][AMOUNT]);
                        SendClientMessageToAll(-1, msg);
                        #endif
                    } case 7 : {
                        soundid = 14403;
                        SetPlayerControllable(playerid, false);        
                        if (vehicleid) {
                            GetVehiclePos(vehicleid, x, y, z);
                        } else {
                            GetPlayerPos(playerid, x, y, z);
                        }       
                        SetPlayerAirS(playerid,1,dyn_pickups[i][AMOUNT],x,y,z,100.0,dyn_pickups[i][AMOUNT]);       
                        SetPlayerCameraPos(playerid, GetPlayerAirSX(playerid), GetPlayerAirSY(playerid), GetPlayerAirSZ(playerid)+GetPlayerAirSHieght(playerid));
                        SetPlayerCameraLookAt(playerid, GetPlayerAirSX(playerid), GetPlayerAirSY(playerid)+0.05, GetPlayerAirSZ(playerid)-0.05, CAMERA_CUT);
                        TW_ShowHudCrosshair(playerid);
                        
                        new msg[256];
                        SetPlayerChatBubble(playerid, "{DDFFFF}[ Used Air Stike... ]", COLOR_BONUS, 60.0, 4500);

                        #if SHOW_ALL_BONUS_MSG
                        new name[MAX_PLAYER_NAME];
                        GetPlayerName(playerid, name, sizeof(name));
                        format(msg, sizeof(msg), "{DDFFFF}* %s(%d) pickuped Air Strike", name, playerid);
                        SendClientMessageToAll(-1, msg);
                        #endif
                    }
                }
                
                #if ENABLE_COLANDREAS
                if (IsValidDynamic3DTextLabel(dyn_pickups[i][TEXTID])) {
                    DestroyDynamic3DTextLabel(dyn_pickups[i][TEXTID]);
                    //dyn_pickups[i][TEXTID] = INVALID_STREAMER_ID;
                }
                #else
                if (dyn_pickups[i][TEXTID] != Text3D:INVALID_3DTEXT_ID) {
                    Delete3DTextLabel(dyn_pickups[i][TEXTID]);
                }
                dyn_pickups[i][TEXTID] = Text3D:INVALID_3DTEXT_ID;
                #endif
                
                //KillTimer(dyn_pickups[i][TIMER]);
                new time = dyn_pickups[i][RESPAWN_TIME];
                dyn_pickups[i][TIMER] = SetTimerEx("OnBonusRespawn", time, false, "i", i);
                
                PlayPlayerSound(playerid, soundid);
                //PlayerPlaySound(playerid, 1137, dyn_pickups[i][X], dyn_pickups[i][Y], dyn_pickups[i][Z]);
                new effectid = CreatePlayerObject(playerid, 18724, dyn_pickups[i][X], dyn_pickups[i][Y], dyn_pickups[i][Z]-1.2, 0, 0, 0, 0.0);
                SetTimerEx("DestroyPlayerParticle", 2000, false, "ii", playerid, effectid);
                break;
            }
            break;
        }
    }
    return 1;
}

forward DestroyPlayerParticle(playerid, objectid);
public DestroyPlayerParticle(playerid, objectid) {
    if (IsValidPlayerObject(playerid, objectid)) DestroyPlayerObject(playerid, objectid);
}

public SetPlayerControllable(playerid, bool:on)
{
    #if TW_FUNC_DEBUG_PRINT_LOW
    printf("[CALLBACK:"SCR_SOURCE"] SetPlayerControllable:\n\tplayerid %d on %b\n", playerid, on);
    #endif

    if (on) {
        SetPVarInt(playerid, "CONTROLLABLE", 0);
    } else {
        SetPVarInt(playerid, "CONTROLLABLE", 1);
    }
    TogglePlayerControllable(playerid, on);
    return true;
}

public KickPlayerEx(playerid)
{
    #if TW_FUNC_DEBUG_PRINT_LOW
    printf("[CALLBACK:"SCR_SOURCE"] KickPlayer:\n\tplayerid %d\n", playerid);
    #endif

    Kick(playerid);
    return true;
}

public ClearPlayerDamagerID(playerid)
{
    #if TW_FUNC_DEBUG_PRINT_LOW
    printf("[CALLBACK:"SCR_SOURCE"] ClearPlayerDamagerID:\n\tplayerid %d\n\tdamagerid %d\n", playerid, GetPVarInt(playerid, "DAMAGERID"));
    #endif

    SetPVarInt(playerid, "DAMAGERID", INVALID_PLAYER_ID);
    return 1;
}

public OnMapGravity(Float:gravity)
{
    #if TW_FUNC_DEBUG_PRINT_LOW
    printf("[CALLBACK:"SCR_SOURCE"] OnMapGravity:\n\tgravity %.6f\n", gravity);
    #endif

    SetGravity(gravity);
    return true;
}

public OnBonusRespawn(bonusid)
{
    #if TW_FUNC_DEBUG_PRINT
    printf("[CALLBACK:"SCR_SOURCE"] OnBonusRespawn:\n\tid %d respawn_time %d type %s (%d)\n", bonusid, dyn_pickups[bonusid][RESPAWN_TIME], GetBonusName(dyn_pickups[bonusid][TYPE]), dyn_pickups[bonusid][TYPE]);
    #endif

    KillTimer(dyn_pickups[bonusid][TIMER]);
    
    CreateBonus(dyn_pickups[bonusid][TYPE], dyn_pickups[bonusid][MODEL], dyn_pickups[bonusid][AMOUNT], dyn_pickups[bonusid][X], dyn_pickups[bonusid][Y], dyn_pickups[bonusid][Z], dyn_pickups[bonusid][SPAWN_RANGE], dyn_pickups[bonusid][RESPAWN_TIME], dyn_pickups[bonusid][WORLDID], dyn_pickups[bonusid][INTERIORID]);

    return true;
}

public SetPlayerSpec(playerid, bool:on)
{
    #if TW_FUNC_DEBUG_PRINT_LOW
    printf("[CALLBACK:"SCR_SOURCE"] SetPlayerSpec:\n\tplayerid %d\n\ton %d\n", playerid, on);
    #endif

    TogglePlayerSpectating(playerid, on);
    return true;
}

public OnVechileEngine(vehicleid, onengine)
{
    #if TW_FUNC_DEBUG_PRINT_LOW
    printf("[CALLBACK:"SCR_SOURCE"] OnVechileEngine:\n\tvehicleid %d\n\tonengine %d\n", vehicleid, onengine);
    #endif

    if (IsVehicleRCHasGun(vehicleid) && onengine) {
        RCCAR_SetGun(vehicleid, 1);
    }
    SetVehicleEngine(vehicleid, onengine);
    return true;
}
// EOF -------------------------------------------------------------------------------