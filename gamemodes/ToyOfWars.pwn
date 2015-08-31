/*
 * [Gamemode] Toy Of Wars
 * Server       : sa-mp 0.3.7 R1
 * Mode         : TDM
 * Map          : Custom locations
 * Release      : v1, 8 aug 2015
 * Updated      : v2, 21 aug 2015
 * Contributors : VanillaRain, Nero_3D, Logofero aka fERO
 * Credits      : Zamaroht - tool 'Zamaroht's TextDraw Editor'

 Description:
 You have to fight on a toy cars against other teams. Every team has its own color.

 Teams:
 0. Red
 1. Green
 2. Blue
 3. Purple
 4. Yellow
 5. White

 Units:
 RCTiger        Tank
 RCBandit       Car
 RCRaider       Helicopter     
 RCGoblin       Helicopter     
 RCBaron        Airplane       

 Cost:
 Humen          +50 score
 RCTiger        +90 score
 RCBandit       +70 score
 RCRaider       +100 score
 RCGoblin       +100 score
 RCBaron        +120 score
 
 Health:
 RCTiger        1200 hp
 RCBandit       900 hp
 RCRaider       800 hp
 RCGoblin       800 hp
 RCBaron        700 hp

 Max. Ammo:
 RCTiger        25 bullets
 RCBandit       30 bullets
 RCRaider       30 bullets
 RCGoblin       30 bullets
 RCBaron        20 bullets
 
 Maps:
 0. Abandoned base v1   1200 score
 1. Abandoned base v2   1500 score

 Controls:
 Fire - Shot of gun
 Enter - Enter/Exit RC cars

 Commands:
 /team [0-5] - change team

 Changes v2:
 + Interface to create an exclusive toy stylistics:
   General bar
   Team list
   Health bar
   Ammo bar
   RC model view and name   

 + Added pickups bonuses:
   Repair kit - add vehicle health
   Multi speed - multiplies speed
   Ammo - add bullets
   Atom Bomb - explode all enemies
   Freeze Bomb - freezes all enemies in a specified time
   Napalm Bomb - sets fire to all enemies
   Gravity Bomb - changing times gravity

 + Added keep zone for map
 + Expanded cmd /team
   Now the player can choose to team use: /team [0-5] - number of team

 + Added debug commands:
   /map [ID] - change map
   /boom [player ID] - explode player
   /tank - create RCTiger

 + Change the settings for RC guns:
   Ammunition for RC guns is now reloading by picking 'Ammo'.

 + Fixed:
   A player could sit in hot or explode vehicles and teleport out of the map. Now you can not entering RC car when it is burning.
   When a player dies in RC Model, the camera is reset and returned to the place of boarding the vehicle. Now the camera is fixed on vehicle exploded.

 - Currently there are no function 'loader' to load custom maps from a file.
   ~Maybe it will be added next update.

 NOTE:
 (!) Projectiles fly through the comrades, but they still inflict damage if an explosion near.
 (~) Since I tested it on one player - there may be bugs with more players.
     If something is not working, please report as possible will be fixed in the next update.
*/
#define SCR_NAME                "Toy of Wars"
#define SCR_REL                 "v1, 8 aug 2015"
#define SCR_UPD                 "v2, 21 aug 2015"
#define SCR_CONTRIBUTORS        "VanillaRain, Nero_3D, Logofero"
#define SCR_CREDITS             "Zamaroht"
#define SCR_URL                 "http://forum.sa-mp.com/showthread.php?t=584939"
#define SCR_URL2                "http://forum.sa-mp.com"

#define DEBUG_PRINT             (0)
#define DEBUG_PRINT_LOW         (0)
#define DEBUG_CMD               (1)
#define ENABLE_CLIENTINFO       (0) // Show news replace language
#define ENABLE_GAMEINFO         (1) // Show news in game
#define ENABLE_CLIENTMAPNAME    (1) // Show name of map replace language

// General Includes
#include <a_samp>
#include <TW_func>
#include <TW_rccars>

// Team info -------------------------------------------------------------------------------
#define MAX_ROUND_SCORE (2)

new TW_team_scores[6];
#define TW_SetTeamScore(%1,%2)      TW_team_scores[%1]=%2
#define TW_GetTeamScore(%1)         TW_team_scores[%1]

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
    M, Float:X, Float:Y, Float:Z, Float:A, WORLDID, INTERIORID
}
new Float:TW_team_spawns[][E_TW_TEAM_SPAWNS]={
    //{400,413.9564,2489.6082,16.4844,352.9059, 0, 0},
    {564,186.8744,2457.9622,15.6485,353.6849, 0, 0},
    {564,297.2267,2552.5649,15.9896,148.8161, 0, 0},
    {564,130.5372,2570.4592,15.5857,206.7869, 0, 0},
    {564,337.9150,2458.8169,15.6506,17.4222, 0, 0},
    {564,407.9163,2542.4590,15.6870,150.9815, 0, 0},
    {564,122.3155,2456.9219,15.6538,313.9525, 0, 0},
    {564,282.4990,2551.4607,15.9881,200.8863, 0, 0},
    {564,252.0264,2448.9578,15.6537,3.3902, 0, 0},
    {564,236.0696,2547.8904,15.9062,185.8480, 0, 0},
    {441,339.0960,2538.3423,15.9624,184.9098, 0, 0},
    {564,430.4706,2479.0410,15.6537,46.2860, 0, 0},
    {564,435.4735,2535.3398,15.5344,104.4680, 0, 0},
    {564,317.4437,2540.0908,15.9809,204.5701, 0, 0},
    {564,332.5363,2538.4146,15.9735,167.4324, 0, 0},
    {564,383.8864,2588.0435,15.6070,188.3061, 0, 0},
    {441,428.1509,2548.7959,15.3754,87.6297, 0, 0},
    {564,427.9746,2544.1382,15.4331,92.9834, 0, 0},
    {465,368.1618,2537.2239,15.8201,177.2921, 0, 0}, // heli 1
    {501,363.0760,2537.0415,15.8453,178.4647, 0, 0}, // heli 2
    {464,403.5965,2441.6038,15.9549,359.5815, 0, 0} // plane
};
// EOF Team info -------------------------------------------------------------------------------

// Pickup info -------------------------------------------------------------------------------
#define COLOR_BONUS                 (0xFF8000FF)
#define SHOW_ALL_BONUS_MSG          (1)

#define MAX_BONUS_TYPES             (7)

#define MAX_REPAIRKIT               (5)
#define MAX_MULTISPEED              (5)
#define MAX_AMMO                    (5)
#define MAX_ATOMBOMBS               (1)
#define MAX_NAPALMBOMBS             (1)
#define MAX_FREEZEBOMBS             (1)
#define MAX_GRAVITYBOMBS            (1)
#define MAX_BONUS                   (MAX_REPAIRKIT + MAX_MULTISPEED + MAX_AMMO + MAX_ATOMBOMBS + MAX_FREEZEBOMBS + MAX_GRAVITYBOMBS)

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
#define TIME_RESTART_GRAVITY        (60000)

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

enum E_PICKUP_BONUS {
    ID, TYPE, MODEL, Float:AMOUNT, Float:SPAWN_RANGE, RESPAWN_TIME, Text3D:TEXTID, NUM, WORLDID, INTERIORID
}
new pickup_bonus[MAX_BONUS][E_PICKUP_BONUS];

enum E_TW_KITS {
    TYPE, MODEL, Float:AMOUNT, Float:X, Float:Y, Float:Z, Float:SPAWN_RANGE, RESPAWN_TIME, WORLDID, INTERIORID
}
new TW_kits[][E_TW_KITS]={
    {PICKUP_MULTISPEED,     MODEL_BARREL1,              2.0,        304.7697, 2506.6682, 16.1844, 0.0, TIME_RESPAWN_MULTISPEED1, 0,0},
    {PICKUP_REPAIRKIT,      MODEL_BB_PICKIP,            150.0,      266.0848,2587.7427,16.1766, 0.0, TIME_RESPAWN_REPAIRKIT1, 0,0},
    {PICKUP_AMMO,           MODEL_AMMO_BOX_C2,          10.0,       408.0122,2528.1943,16.2790, 0.0, TIME_RESPAWN_AMMO1, 0,0},
    {PICKUP_MULTISPEED,     MODEL_BARREL1,              3.0,        385.5745,2499.9893,16.1844, 0.0, TIME_RESPAWN_MULTISPEED2, 0,0},
    {PICKUP_REPAIRKIT,      MODEL_BB_PICKIP,            250.0,      383.4079,2604.6257,16.1844, 0.0, TIME_RESPAWN_REPAIRKIT2, 0,0},
    {PICKUP_ATOMBOMB,       MODEL_KMB_MINE,             12.0,       175.5026,2495.2485,16.4897, 180.0, TIME_RESPAWN_ATOMBOMB, 0,0},
    {PICKUP_AMMO,           MODEL_AMMO_BOX_C2,          10.0,       269.3474,2403.4399,17.2801, 0.0, TIME_RESPAWN_AMMO1, 0,0},
    {PICKUP_MULTISPEED,     MODEL_BARREL4,              10.0,       110.4415,2425.1160,20.5162, 0.0, TIME_RESPAWN_MULTISPEED3, 0,0},
    {PICKUP_MULTISPEED,     MODEL_BARREL1,              3.0,        167.8669,2510.4993,15.9119, 0.0, TIME_RESPAWN_MULTISPEED2, 0,0},
    {PICKUP_REPAIRKIT,      MODEL_BB_PICKIP,            500.0,      -18.2778,2326.5002,23.5100, 0.0, TIME_RESPAWN_REPAIRKIT3, 0,0},
    {PICKUP_AMMO,           MODEL_CR_AMMOBOX,           20.0,       232.4911,2634.5984,16.9860, 0.0, TIME_RESPAWN_AMMO2, 0,0},
    {PICKUP_FREEZEBOMB,     MODEL_SKULLS,               10000.0,    333.2957,2490.7693,16.4844, 100.0, TIME_RESPAWN_FREEZEBOMB, 0,0},
    {PICKUP_NAPALMBOMB,     MODEL_BARREL3,              6.0,        175.5026,2495.2485,16.1897, 200.0, TIME_RESPAWN_NAPALMBOMB, 0,0},
    {PICKUP_MULTISPEED,     MODEL_BARREL1,              3.5,        350.9307,2454.0090,20.5541, 0.0, TIME_RESPAWN_MULTISPEED3, 0,0},
    {PICKUP_GRAVITYBOMB,    MODEL_AMMO_CAPSULE,         0.001,      175.5026,2495.2485,16.4897, 168.0, TIME_RESPAWN_GRAVITYBOMB, 0,0}
}

new bonus_limit[MAX_BONUS_TYPES];
// EOF Pickup info -------------------------------------------------------------------------------

// Map info -------------------------------------------------------------------------------
#define TW_TIME_NEW_ROUND       (10000)
#define GAMESTATE_NONE          (0)
#define GAMESTATE_STARTROUND    (1)
#define GAMESTATE_ENDROUND      (2)

new gamestate;
new TW_keepzone[4];
new current_mapid;

enum E_MAPINFO {
    NAME[24],
    AUTHOR[24],
    ROUND_SCORE,
    TIME_HOURE,
    TIME_MINUTE,
    WEATHERID,
    INTERIORID,
    WORLDID,
    Float: GRAVITY,
    Float: MINX,
    Float: MINY,
    Float: MINZ,
    Float: MAXX,
    Float: MAXY,
    Float: MAXZ
}

new TW_mapinfo[][E_MAPINFO]={
    //{-116.2822, 2310.4036, -50.0000, 458.4461, 2719.5530, 200.0000}
    {"Abandoned base v1", "", 1200, 3,0, 3, 0,0, 0.008, -116.2822, 2310.4036, -50.0000, 497.4070, 2722.4204, 500.0000},
    {"Abandoned base v2", "Logofero", 1500, 12,50, 5, 0,0, 0.006, -116.2822, 2310.4036, -50.0000, 497.4070, 2722.4204, 500.0000}
};

#define TW_GetMapName(%1)           TW_mapinfo[%1][NAME]
#define TW_GetMapAuthor(%1)         TW_mapinfo[%1][AUTHOR]
#define TW_GetMapScore(%1)          TW_mapinfo[%1][ROUND_SCORE]
#define TW_GetMapTimeH(%1)          TW_mapinfo[%1][TIME_HOURE]
#define TW_GetMapTimeM(%1)          TW_mapinfo[%1][TIME_MINUTE]

#define TW_GetMapWeather(%1)        TW_mapinfo[%1][WEATHERID]
#define TW_GetMapGravity(%1)        TW_mapinfo[%1][GRAVITY]
#define TW_GetMapInterior(%1)       TW_mapinfo[%1][INTERIORID]
#define TW_GetMapWorld(%1)          TW_mapinfo[%1][WORLDID]

#define TW_GetMapMinX(%1)           TW_mapinfo[%1][MINX]
#define TW_GetMapMinY(%1)           TW_mapinfo[%1][MINY]
#define TW_GetMapMinZ(%1)           TW_mapinfo[%1][MINZ]

#define TW_GetMapMaxX(%1)           TW_mapinfo[%1][MAXX]
#define TW_GetMapMaxY(%1)           TW_mapinfo[%1][MAXY]
#define TW_GetMapMaxZ(%1)           TW_mapinfo[%1][MAXZ]
// EOF Map info -------------------------------------------------------------------------------

#if DEBUG_CMD
static
   bool:vehiclemaked[MAX_VEHICLES]
;
#endif

// Anticheat system -------------------------------------------------------------------------------
#define COLOR_KICK                  (0xFF8000FF)
new anticheat[MAX_PLAYERS];
// EOF Anticheat system -------------------------------------------------------------------------------

// Custom Includes
#include <TW_hud>

// Custom functions -------------------------------------------------------------------------------
// Saved to TW_func.inc

/*
 * native TW_InitMap(mapid);
 */
stock TW_InitMap(mapid) {
    // Destroy vehicles
    for (new v = GetVehiclePoolSize(); v >= 1; --v) {
        DestroyVehicle(v);
    }
    // Destroy pickups
    for (new i; i < MAX_PICKUPS; i++) {
        DestroyPickup(i);
    }
    // Create vehicles
    for (new i; i < sizeof(TW_team_spawns); i++) {
        CreateVehicleEx(TW_team_spawns[i][M], TW_team_spawns[i][X], TW_team_spawns[i][Y], TW_team_spawns[i][Z], TW_team_spawns[i][A], 3, 0, 60, 0, TW_team_spawns[i][WORLDID], TW_team_spawns[i][INTERIORID]);
    }
    RespawnAllVehicles();
    // Create bonus
    ClearAllBonus();
    for (new i; i < sizeof(TW_kits); i++) {
        CreateBonus(TW_kits[i][TYPE], TW_kits[i][MODEL], TW_kits[i][AMOUNT], TW_kits[i][X], TW_kits[i][Y], TW_kits[i][Z], TW_kits[i][SPAWN_RANGE], TW_kits[i][RESPAWN_TIME], TW_kits[i][WORLDID], TW_kits[i][INTERIORID]);
    }
    // Destroy GangZone
    DestroyCutZone(TW_keepzone);
    // Create GangZone
    CreateCutZone(TW_keepzone, TW_GetMapMinX(mapid), TW_GetMapMinY(mapid), TW_GetMapMaxX(mapid), TW_GetMapMaxY(mapid));
    // Set parameters for world
    SetWorldTime(TW_GetMapTimeH(mapid));
    SetWeather(TW_GetMapWeather(mapid));
    SetGravity(TW_GetMapGravity(mapid));
    // Set parameters for players
    for (new p = GetPlayerPoolSize(); p >= 0; --p) {
        // Remove map builders
        //RemoveBuildingForPlayer(playerid, 16773, 397.4766, 2476.6328, 19.5156, 0.25);
        //RemoveBuildingForPlayer(playerid, 16775, 412.1172, 2476.6328, 19.5156, 0.25);
        SetPlayerTime(p, TW_GetMapTimeH(mapid), TW_GetMapTimeM(mapid));
        SetPlayerWeather(p, TW_GetMapWeather(mapid));
        SetPlayerInterior(p, TW_GetMapInterior(mapid));
        SetPlayerVirtualWorld(p, TW_GetMapWorld(mapid));
        ShowPlayerCutZone(p, TW_keepzone, 0xFF000044);
        TW_ShowHudMapInfo(p, mapid);
    }

    #if ENABLE_CLIENTMAPNAME
    new
        msg[128]
    ;
    format(msg, sizeof(msg), "%s %d/%d ", TW_GetMapName(mapid), mapid+1, sizeof(TW_mapinfo));
    SetServerLanguage(msg);
    #endif
}

/*
 * native ClearAllBonus();
 */
stock ClearAllBonus() {
    for (new i; i < MAX_BONUS; i++) {
        if (pickup_bonus[i][ID] != 65535) {
            DestroyPickup(pickup_bonus[i][ID]);
        }
        pickup_bonus[i][ID] = 65535;
        if (pickup_bonus[i][TEXTID] != Text3D:INVALID_3DTEXT_ID) {
            Delete3DTextLabel(pickup_bonus[i][TEXTID]);
        }
        pickup_bonus[i][TEXTID] = Text3D:INVALID_3DTEXT_ID;
        pickup_bonus[i][MODEL] = 0;
        pickup_bonus[i][TYPE] = -1;
        pickup_bonus[i][NUM] = 0;
        pickup_bonus[i][AMOUNT] = 0.0;
        pickup_bonus[i][WORLDID] = 0;
        pickup_bonus[i][INTERIORID] = 0;
        pickup_bonus[i][SPAWN_RANGE] = 0.0;
        pickup_bonus[i][RESPAWN_TIME] = 0;
    }
    for (new i; i < sizeof(bonus_limit); i++) {
        bonus_limit[i]=0;
    }
}

/*
 * stock CreateBonus(type, model, Float:amount, Float:x, Float:y, Float:z, spawn_range, respawn_time, worldid, interiorid);
 */
stock CreateBonus(type, model, Float:amount, Float:x, Float:y, Float:z, Float:spawn_range, respawn_time, worldid, interiorid) {

    #if DEBUG_PRINT
    printf("[FUNC:TW_func.inc] CreateBonus:\n\ttype %d model %d amount %.1f\n\txyz %.4f %.4f %.4f\n\tspawn_range %.1f respawn_time %d worldid %d interiorid %d\n", type, model, amount, x, y, z, spawn_range, respawn_time, worldid, interiorid);
    #endif

    for (new i; i < MAX_BONUS; i++) {
        if (pickup_bonus[i][ID] == 65535) {

            new msg[256];
            switch (type) {
                case 0 : {
                    if (bonus_limit[type] >= MAX_REPAIRKIT) {
                        return 65535
                    }
                    format(msg, sizeof(msg), "{00FF00}Health kit +%.0f hp", amount);
                } case 1 : {
                    if (bonus_limit[type] >= MAX_MULTISPEED) {
                        return 65535
                    }
                    format(msg, sizeof(msg), "{FF8080}Multi Speed x%.1f", amount);
                } case 2 : {
                    if (bonus_limit[type] >= MAX_AMMO) {
                        return 65535
                    }
                    format(msg, sizeof(msg), "{AAAAAA}Ammo box +%.0f", amount);
                } case 3 : {
                    if (bonus_limit[type] >= MAX_ATOMBOMBS) {
                        return 65535
                    }
                    format(msg, sizeof(msg), "{FFFFFF}Atom Bomb");
                } case 4 : {
                    if (bonus_limit[type] >= MAX_NAPALMBOMBS) {
                        return 65535
                    }
                    format(msg, sizeof(msg), "{FFFF80}Napalm Bomb");
                } case 5 : {
                    if (bonus_limit[type] >= MAX_FREEZEBOMBS) {
                        return 65535
                    }
                    format(msg, sizeof(msg), "{33CCFF}Freeze Bomb %.1f sec", amount / 1000.0);
                } case 6 : {
                    if (bonus_limit[type] >= MAX_GRAVITYBOMBS) {
                        return 65535
                    }
                    format(msg, sizeof(msg), "{DDCCFF}Gravity Bomb %.4f", amount);
                }
            }
            if (spawn_range > 0.0) {
                x += floatrandom(-spawn_range, spawn_range);
                y += floatrandom(-spawn_range, spawn_range);
            }
            new pickupdid = CreatePickup(model, 14, x, y, z, worldid);
            if (pickupdid == 65535) return 65535;

            pickup_bonus[i][ID] = pickupdid;
            pickup_bonus[i][TYPE] = type;
            pickup_bonus[i][AMOUNT] = amount;
            pickup_bonus[i][WORLDID] = worldid;
            pickup_bonus[i][INTERIORID] = interiorid;
            pickup_bonus[i][SPAWN_RANGE] = spawn_range;
            pickup_bonus[i][RESPAWN_TIME] = respawn_time;
            pickup_bonus[i][TEXTID] = Create3DTextLabel(msg, 0xFFFFFFFF, x, y, z + 0.3, 3000.0, worldid, 1);
            //pickup_bonus[i][NUM]++;
            bonus_limit[type]++;
            return pickupdid;
        }
    }
    return 65535;
}
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
    "Battle City live" // Battle City (Namco) Not forgotten
}
#endif

forward OnModeInfo();
public OnModeInfo()
{
    #if DEBUG_PRINT_LOW
    printf("[CALLBACK:ToyOfWars.pwn] OnModeInfo()\n");
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

main () {
    //RespawnAllVehicles();

    #if ENABLE_GAMEINFO
    timer_modeinfo = SetTimer("OnModeInfo", 1000, 1);
    #endif
}

public OnGameModeInit()
{
    #if DEBUG_PRINT
    printf("[CALLBACK:ToyOfWars.pwn] OnGameModeInit()\n");
    #endif

    printf("\n-------------------------------------------------------------------------------\n\n\tGamemode     : %s\n\tRelease      : %s\n\tUpdate       : %s\n\tContributors : %s\n\tCredits      : %s\n\tUrl          : %s\n\n-------------------------------------------------------------------------------\n", \
        SCR_NAME, SCR_REL, SCR_UPD, SCR_CONTRIBUTORS, SCR_CREDITS, SCR_URL
    );

    // Set base gamemode settings
    SetGameModeText(SCR_NAME);
    EnableStuntBonusForAll(false);
    DisableInteriorEnterExits();
    ManualVehicleEngineAndLights();

    // Create TextDraw's
    TW_CreateHudGenInfo();
    TW_CreateHudMapInfo();
    TW_CreateHudTeamList();
    TW_CreateHudAlert();
    TW_CreateHudWin();

	gamestate = GAMESTATE_NONE;
	return 1;
}

public OnGameModeExit()
{
    #if DEBUG_PRINT
    printf("[CALLBACK:ToyOfWars.pwn] OnGameModeExit()\n");
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

    // Destroy keep zone
    DestroyCutZone(TW_keepzone);

    // Destroy vehicles
    for (new v = GetVehiclePoolSize(); v >= 1; --v) {
        DestroyVehicle(v);
    }

    gamestate = GAMESTATE_NONE;
    return 1;
}

public OnIncomingConnection(playerid, ip_address[], port)
{
    #if DEBUG_PRINT_LOW
    printf("[CALLBACK:ToyOfWars.pwn] OnIncomingConnection:\n\tplayerid %d\n\tip %s\n\tport %d\n", playerid, ip_address, port);
    #endif

    return 1;
}

public OnPlayerConnect(playerid)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:ToyOfWars.pwn] OnPlayerConnect:\n\tplayerid %d\n", playerid);
    #endif

    // Set player random team
    //SetPlayerRandomColor(playerid);
    SetPlayerColor(playerid, TW_team_colors[random(sizeof(TW_team_colors))] );

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
    TW_ShowHudMapInfo(playerid, current_mapid);
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:ToyOfWars.pwn] OnPlayerDisconnect:\n\tplayerid %d\n\treason %d\n", playerid, reason);
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
    HidePlayerCutZone(playerid, TW_keepzone);

    // Reset player states
    anticheat[playerid] = 0;

    SetTimerEx("OnPlayerDisconnected", 200, 0, "ii", playerid, reason);
    return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:ToyOfWars.pwn] OnPlayerRequestClass:\n\tplayerid %d\n\tclassid %d\n", playerid, classid);
    #endif

    // Pass class selector (Fast spawn - no button)
    new teamid = GetTeamColorIDOfColor(GetPlayerColor(playerid));
    SetSpawnInfo(playerid, teamid, TW_team_skins[teamid], TW_team_spawns[teamid][X], TW_team_spawns[teamid][Y], TW_team_spawns[teamid][Z], TW_team_spawns[teamid][A], 0, 0, 0, 0, 0, 0);
    SpawnPlayer(playerid);
    return 1;
}

public OnPlayerSpawn(playerid)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:ToyOfWars.pwn] OnPlayerSpawn:\n\tplayerid %d\n", playerid);
    #endif

    // Reset player states
    ClearPlayerDamagerID(playerid);
    //SetCameraBehindPlayer(playerid);

    if (gamestate == GAMESTATE_NONE) { // First spawn
        OnStartRound();
    } else if (gamestate == GAMESTATE_STARTROUND) {
        // Show keep zone
        ShowPlayerCutZone(playerid, TW_keepzone, 0xFF000044);
        // Show TextDraw's
        TW_ShowHudTeamList(playerid);
        SetPlayerControllable(playerid, true);
    } else if (gamestate == GAMESTATE_ENDROUND) {
        SetPlayerControllable(playerid, false);
    }
    return 1;
}


public OnVehicleSpawn(vehicleid)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:ToyOfWars.pwn] OnVehicleSpawn:\n\tvehicleid %d\n", vehicleid);
    #endif

    #if DEBUG_CMD
    if (vehiclemaked[vehicleid]) {
        vehiclemaked[vehicleid] = false;
        DestroyVehicle(vehicleid);
    }
    #endif
    SetVehicleEngine(vehicleid, 1);
    return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:ToyOfWars.pwn] OnPlayerDeath:\n\tplayerid %d\n\tkillerid %d\n\treason %d\n", playerid, killerid, reason);
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
            score = 50; // For killing men 50 score
        }
        TW_SetTeamScore(teamid, TW_GetTeamScore(teamid)+score);
        if (TW_GetTeamScore(teamid) < 0) {
            TW_SetTeamScore(teamid, 0);
        }
        // Update hud
        TW_ShowHudTeamList(playerid);
        
        // Give player score
        SetPlayerScore(killerid, GetPlayerScore(killerid)+1);

        // Round winner
        if (TW_GetTeamScore(teamid) >= TW_GetMapScore(current_mapid)) { //
            TW_ShowAllHudWin(killerid);
            SetAllCamMoveToPlayer(killerid);
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
            name[MAX_PLAYER_NAME]
        ;
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
    HidePlayerCutZone(playerid, TW_keepzone);
    return 1;
}

public OnPlayerUpdate(playerid)
{
    #if DEBUG_PRINT_LOW
    printf("[CALLBACK:ToyOfWars.pwn] OnPlayerUpdate:\n\tplayerid %d\n", playerid);
    #endif

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
    if (delay[playerid] < time && gamestate == GAMESTATE_STARTROUND) {
        if (!IsPointInArea3D(x, y, z, TW_GetMapMinX(current_mapid), TW_GetMapMinY(current_mapid), TW_GetMapMinZ(current_mapid), TW_GetMapMaxX(current_mapid), TW_GetMapMaxY(current_mapid), TW_GetMapMaxZ(current_mapid))) {
            SetCutZoneFlashForPlayer(playerid, TW_keepzone, 0xFF000077);
            //SendClientMessage(playerid, 0xFF0000FF, "You are outside of battlefield, go back!");
            TextDrawShowForPlayer(playerid, tdraw_alert);
            new
                Float: hp
            ;
            GetPlayerHealth(playerid, hp);
            SetPlayerHealth(playerid, hp - 5.0);
        } else {
            SetCutZoneStopFlashForPlayer(playerid, TW_keepzone);
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
    printf("[CALLBACK:ToyOfWars.pwn] OnPlayerText:\n\tplayerid %d\n\ttext %s\n", playerid, text);
    #endif

    new
        msg[256],
        name[MAX_PLAYER_NAME]
    ;
    GetPlayerName(playerid, name, sizeof(name));
    new teamid = GetPlayerTeam(playerid);
    format(msg, sizeof(msg), "[Team: %s] %s(%d): {FFFFFF}%s", TW_team_ncolors[teamid], name, playerid, text);
    SendClientMessageToAll(GetPlayerColor(playerid), msg);
    SetPlayerChatBubble(playerid, msg, GetPlayerColor(playerid), 60.0, 5000);
    return 0;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
    #if DEBUG_PRINT
    printf("[CALLBACK:ToyOfWars.pwn] OnPlayerCommandText:\n\tplayerid %d\n\tcmdtext %s\n", playerid, cmdtext);
    #endif

	if (strfind(cmdtext, "/team", true, 0) != -1)
	{
	    strdel(cmdtext, 0, 5);
        new
            msg[256]
        ;
	    if (!strlen(cmdtext)) {
            format(msg, sizeof(msg), "Invalid cmd. Use: /team [0-%d]", sizeof(TW_team_ncolors)-1);
            SendClientMessage(playerid, 0xFF0000FF, msg);
            return 1;
	    }
	    new
	       teamid = strval(cmdtext),
	       name[MAX_PLAYER_NAME]
	    ;
        if (teamid < 0 || teamid >= sizeof(TW_team_ncolors)) {
            format(msg, sizeof(msg), "Invalid team ID. Limit: 0 to %d", sizeof(TW_team_ncolors)-1);
            SendClientMessage(playerid, 0xFF0000FF, msg);
            return 1;
        }
        GetPlayerName(playerid, name, sizeof(name));
  		format(msg, sizeof(msg),"*** %s(%d) changed his team on %s", name, playerid, TW_team_ncolors[teamid]);
  		SendClientMessageToAll(TW_team_colors[teamid], msg);
	    SetPlayerColor(playerid, TW_team_colors[teamid]);
	    ForceClassSelection(playerid);
	    SetPlayerHealth(playerid, 0.0);
	    return 1;
	}

    #if DEBUG_CMD
    if (IsPlayerAdmin(playerid)) {
	if (strfind(cmdtext, "/boom", true, 0) != -1)
	{
	    strdel(cmdtext, 0, 5);
        new
	       msg[256]
	    ;
	    if (!strlen(cmdtext)) {
	       format(msg, sizeof(msg), "Invalid cmd. Use: /boom [player ID]");
	       SendClientMessage(playerid, 0xFF0000FF, msg);
	       return 1;
	    }
	    new
	       toid = strval(cmdtext)
	    ;
	    if (!IsPlayerConnected(toid)) {
	       format(msg, sizeof(msg), "Invalid player ID (%d)", toid);
	       SendClientMessage(playerid, 0xFF0000FF, msg);
	       return 1;
	    }
	    new
	       //msg[256],
	       Float: x,
	       Float: y,
	       Float: z
	    ;
	    GetPlayerPos(toid, x,y,z);
  		CreateExplosionByPlayer(playerid, x, y, z, 11, 20.0, true)
  		new
	       name[MAX_PLAYER_NAME]
	    ;
	    GetPlayerName(playerid, name, sizeof(name));
  		format(msg, sizeof(msg),"Administrator has exploded %s(%d)", name, toid);
  		SendClientMessageToAll(0xFF0000FF, msg);
	    return 1;
	}
	if (strfind(cmdtext, "/map", true, 0) != -1)
	{
        strdel(cmdtext, 0, 4);
        new
	       msg[256]
	    ;
	    if (!strlen(cmdtext)) {
	       format(msg, sizeof(msg), "Invalid cmd. Use: /map [0-%d]", sizeof(TW_mapinfo)-1);
	       SendClientMessage(playerid, 0xFF0000FF, msg);
	       return 1;
	    }
	    new
	       mapid = strval(cmdtext)
	    ;
	    if (mapid < 0 || mapid >= sizeof(TW_mapinfo)) {
	       format(msg, sizeof(msg), "Invalid Map ID. Limit: 0 to %d", sizeof(TW_mapinfo)-1);
	       SendClientMessage(playerid, 0xFF0000FF, msg);
	       return 1;
	    }
        current_mapid = mapid;
        OnStartRound();

        format(msg, sizeof(msg),"Administrator has changed map on '%s'", TW_GetMapName(mapid));
  		SendClientMessageToAll(0xFF0000FF, msg);
        return 1;
	}
	if (strcmp("/tank", cmdtext, true, 10) == 0)
	{
	    new
	       msg[256],
	       Float:x,
	       Float:y,
	       Float:z,
	       Float:a
	    ;
	    GetPlayerPos(playerid, x,y,z);
	    GetPlayerFacingAngle(playerid, a);
  		new vehicleid = CreateVehicle(564, x,y,z, a, -1,-1, 60);
  		if (!vehicleid) return 0;
  		SetVehicleToRespawn(vehicleid);
  		vehiclemaked[vehicleid] = true;
  		format(msg, sizeof(msg),"Administrator created RCTiger");
  		SendClientMessageToAll(0xFF0000FF, msg);
	    return 1;
	}
	}
	#endif
    return 0;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:ToyOfWars.pwn] OnPlayerPickUpPickup:\n\tplayerid %d\n\tpickupid %d\n", playerid, pickupid);
    #endif

    for (new i; i < MAX_BONUS; i++) {
        if (pickup_bonus[i][ID] != 65535 && pickup_bonus[i][ID] == pickupid && GetPlayerInterior(playerid) == pickup_bonus[i][INTERIORID]) {
            new vehicleid = GetPlayerVehicleID(playerid);
            if (vehicleid) {
                new
                    Float:x,
                    Float:y,
                    Float:z
                ;
                switch (pickup_bonus[i][TYPE]) {
                    case 0 : {
                        new
                            Float: hp
                        ;
                        GetVehicleHealth(vehicleid, hp);
                        RepairVehicle(vehicleid); // Repairs the damage model and resets the health
                        if (RCCAR_GetMaxHP(vehicleid) > 0.0 && hp+pickup_bonus[i][AMOUNT] >= RCCAR_GetMaxHP(vehicleid)) SetVehicleHealth(vehicleid, RCCAR_GetMaxHP(vehicleid));
                        else SetVehicleHealth(vehicleid, hp+pickup_bonus[i][AMOUNT]);

                        new msg[256];
                        format(msg, sizeof(msg), "{00FF00}[ Used Health Kit +%.0f hp... ]",  pickup_bonus[i][AMOUNT]);
                        SetPlayerChatBubble(playerid, msg, COLOR_BONUS, 60.0, 4500);

                        #if SHOW_ALL_BONUS_MSG
                        new name[MAX_PLAYER_NAME];
                        GetPlayerName(playerid, name, sizeof(name));
                        format(msg, sizeof(msg), "{00FF00}* %s(%d) pickuped health kit +%.0f hp", name, playerid, pickup_bonus[i][AMOUNT]);
                        SendClientMessageToAll(-1, msg);
                        #endif
                    } case 1 : {
                        //GetPlayerPos(playerid, x, y, z);
                        //GetVehicleZAngle(vehicleid, a);
                        GetVehicleVelocity(vehicleid, x, y, z);
                        SetVehicleVelocity(vehicleid, x * pickup_bonus[i][AMOUNT], y * pickup_bonus[i][AMOUNT], z * pickup_bonus[i][AMOUNT]);
                        //SetVehicleAngularVelocity(vehicleid, x * multnitro, y * multnitro, z);

                        new msg[256];
                        format(msg, sizeof(msg), "{FF8080}[ Used Multi Speed x%.1f... ]",  pickup_bonus[i][AMOUNT]);
                        SetPlayerChatBubble(playerid, msg, COLOR_BONUS, 60.0, 4500);

                        #if SHOW_ALL_BONUS_MSG
                        new name[MAX_PLAYER_NAME];
                        GetPlayerName(playerid, name, sizeof(name));
                        format(msg, sizeof(msg), "{FF8080}* %s(%d) pickuped multi speed x%.1f", name, playerid, pickup_bonus[i][AMOUNT]);
                        SendClientMessageToAll(-1, msg);
                        #endif
                    } case 2 : {
                        if (RCCAR_GetAmmo(vehicleid)+floatround(pickup_bonus[i][AMOUNT]) <= RCCAR_GetMaxAmmo(vehicleid)) RCCAR_SetAmmo(vehicleid, RCCAR_GetAmmo(vehicleid) + floatround(pickup_bonus[i][AMOUNT]));
                        else RCCAR_SetAmmo(vehicleid, RCCAR_GetMaxAmmo(vehicleid));

                        new msg[256];
                        format(msg, sizeof(msg), "{AAAAAA}[ Used Ammo +%.0f... ]",  pickup_bonus[i][AMOUNT]);
                        SetPlayerChatBubble(playerid, msg, COLOR_BONUS, 60.0, 4500);

                        #if SHOW_ALL_BONUS_MSG
                        new name[MAX_PLAYER_NAME];
                        GetPlayerName(playerid, name, sizeof(name));
                        format(msg, sizeof(msg), "{AAAAAA}* %s(%d) pickuped ammo +%.0f", name, playerid, pickup_bonus[i][AMOUNT]);
                        SendClientMessageToAll(-1, msg);
                        #endif
                    } case 3 : {
                        ExplosionAllByPlayer(playerid, 11, pickup_bonus[i][AMOUNT], false);

                        new msg[256];
                        SetPlayerChatBubble(playerid, "{FFFFFF}[ Used Atom Bomb... ]", COLOR_BONUS, 60.0, 4500);

                        #if SHOW_ALL_BONUS_MSG
                        new name[MAX_PLAYER_NAME];
                        GetPlayerName(playerid, name, sizeof(name));
                        format(msg, sizeof(msg), "{FFFFFF}* %s(%d) pickuped Atom Bomb", name, playerid);
                        SendClientMessageToAll(-1, msg);
                        #endif
                    } case 4 : {
                        ExplosionAllByPlayer(playerid, 1, pickup_bonus[i][AMOUNT], false);

                        new msg[256];
                        SetPlayerChatBubble(playerid, "{FFFF80}[ Used Napalm Bomb... ]", COLOR_BONUS, 60.0, 4500);

                        #if SHOW_ALL_BONUS_MSG
                        new name[MAX_PLAYER_NAME];
                        GetPlayerName(playerid, name, sizeof(name));
                        format(msg, sizeof(msg), "{FFFF80}* %s(%d) pickuped Napalm Bomb", name, playerid);
                        SendClientMessageToAll(-1, msg);
                        #endif
                    } case 5 : {
                        for (new v = GetVehiclePoolSize(); v >= 1; --v) {
                            if (v != GetPlayerVehicleID(playerid)) {
                                SetVehicleEngine(v, 0);
                                RCCAR_SetGun(v, 0);
                                SetTimerEx("OnVechileEngine", floatround(pickup_bonus[i][AMOUNT]), 0, "ii", v, 1);
                            }
                        }
                        new msg[256];
                        SetPlayerChatBubble(playerid, "{33CCFF}[ Used Freeze Bomb... ]", COLOR_BONUS, 60.0, 4500);

                        #if SHOW_ALL_BONUS_MSG
                        new name[MAX_PLAYER_NAME];
                        GetPlayerName(playerid, name, sizeof(name));
                        format(msg, sizeof(msg), "{33CCFF}* %s(%d) pickuped Freeze Bomb %.1f sec", name, playerid, pickup_bonus[i][AMOUNT] / 1000.0);
                        SendClientMessageToAll(-1, msg);
                        #endif
                    } case 6 : {
                        OnMapGravity(pickup_bonus[i][AMOUNT]);
                        SetTimerEx("OnMapGravity", TIME_RESTART_GRAVITY, 0, "f", TW_GetMapGravity(current_mapid));

                        new msg[256];
                        SetPlayerChatBubble(playerid, "{DDCCFF}[ Used Gravity Bomb... ]", COLOR_BONUS, 60.0, 4500);

                        #if SHOW_ALL_BONUS_MSG
                        new name[MAX_PLAYER_NAME];
                        GetPlayerName(playerid, name, sizeof(name));
                        format(msg, sizeof(msg), "{DDCCFF}* %s(%d) pickuped Gravity Bomb %.4f", name, playerid, pickup_bonus[i][AMOUNT]);
                        SendClientMessageToAll(-1, msg);
                        #endif
                    }
                }
                SetTimerEx("OnBonusRespawn", pickup_bonus[i][RESPAWN_TIME], false, "i", i);
                if (pickup_bonus[i][TEXTID] != Text3D:INVALID_3DTEXT_ID) {
                    Delete3DTextLabel(pickup_bonus[i][TEXTID]);
                    pickup_bonus[i][TEXTID] = Text3D:INVALID_3DTEXT_ID;
                }
                DestroyPickup(pickupid);
                pickup_bonus[i][ID] = 65535;
                pickup_bonus[i][SPAWN_RANGE] = 0.0;
                pickup_bonus[i][RESPAWN_TIME] = 0;
                pickup_bonus[i][AMOUNT] = 0.0;
                bonus_limit[pickup_bonus[i][TYPE]]--;
                if (bonus_limit[pickup_bonus[i][TYPE]] < 0) {
                    bonus_limit[pickup_bonus[i][TYPE]] = 0;
                }
                pickup_bonus[i][TYPE] = -1;
                return 1;
            }
            break;
        }
    }
    return 1;
}

/*
public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:ToyOfWars.pwn] OnPlayerTakeDamage:\n\tplayerid %d\n\tissuerid %d\n\tamount %.1f\n\tweaponid %d\n\tbodypart %d\n", playerid, issuerid, amount, weaponid, bodypart);
    #endif

    new msg[256];
    format(msg, sizeof(msg), "OnPlayerTakeDamage playerid %d issuerid %d amount %.1f weaponid %d bodypart %d", playerid, issuerid, amount, weaponid, bodypart);

    SendClientMessageToAll(-1, msg);
    return 1;
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:ToyOfWars.pwn] OnPlayerGiveDamage:\n\tplayerid %d\n\tdamagedid %d\n\tamount %.1f\n\tweaponid %d\n\tbodypart %d\n", playerid, damagedid, amount, weaponid, bodypart);
    #endif

    new msg[256];
    format(msg, sizeof(msg), "OnPlayerGiveDamage playerid %d damagedid %d amount %.1f weaponid %d bodypart %d", playerid, damagedid, amount, weaponid, bodypart);

    SendClientMessageToAll(-1, msg);
    return 1;
}
*/

// Custom callbacks -------------------------------------------------------------------------------
forward OnStartRound();
public OnStartRound()
{
    new
        msg[256],
        teamid
    ;
    TW_HideAllHudWin();
    TW_InitMap(current_mapid);
    for (new i; i < sizeof(TW_team_scores); i++) {
        TW_team_scores[i] = 0;
    }
    for (new p = GetPlayerPoolSize(); p >= 0; --p) {
        //TogglePlayerSpectating(p, false);
        SetPlayerControllable(p, true);
        SetCameraBehindPlayer(p);
        SetPlayerHealth(p, 100.0);

        // Show TextDraw's
        TW_ShowHudMapInfo(p, current_mapid);
        TW_ShowHudTeamList(p);

        teamid = GetPlayerTeam(p);
        format(msg, sizeof(msg),"~r~New Round~n~~%.1s~You team is %s!", TW_team_ncolors[teamid][0], TW_team_ncolors[teamid]);
        GameTextForPlayer(p, msg, 8000, 5);
        //SpawnPlayer(p);
    }
    gamestate = GAMESTATE_STARTROUND;
    return true;
}

forward OnEndRound();
public OnEndRound()
{
    gamestate = GAMESTATE_ENDROUND;
    for (new p = GetPlayerPoolSize(); p >= 0; --p) {
        // Hide GangZone
        HidePlayerCutZone(p, TW_keepzone);

        // Hide TextDraw's
        TW_HideHudAlert(p);
        TW_HideHudMapInfo(p);
        TW_HideHudTeamList(p);
        //TogglePlayerSpectating(p, true);
    }
    current_mapid++;
    if (current_mapid >= sizeof(TW_mapinfo)) {
        current_mapid = 0;
    }
    SetTimer("OnStartRound", TW_TIME_NEW_ROUND, 0); // New round
    return true;
}

forward OnPlayerEnteredInVehicle(playerid, vehicleid);
public OnPlayerEnteredInVehicle(playerid, vehicleid)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:ToyOfWars.pwn] OnPlayerEnteredInVehicle:\n\tplayerid %d\n\tvehicleid %d\n", playerid, vehicleid);
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

forward OnPlayerExitedOfVehicle(playerid, vehicleid);
public OnPlayerExitedOfVehicle(playerid, vehicleid)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:ToyOfWars.pwn] OnPlayerExitedOfVehicle:\n\tplayerid %d\n\tvehicleid %d\n", playerid, vehicleid);
    #endif

    // Hide TextDraw's
    TW_HideHudCarHP(playerid);
    TW_HideHudGunAmmo(playerid);

    // Hide RC view
    TW_DestroyHudCarView(playerid);
    return true;
}

forward OnBonusRespawn(bonusid);
public OnBonusRespawn(bonusid)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:ToyOfWars.pwn] OnBonusRespawn:\n\tid %d respawn_time %d type %d\n", bonusid, TW_kits[bonusid][RESPAWN_TIME], TW_kits[bonusid][TYPE]);
    #endif

    CreateBonus(TW_kits[bonusid][TYPE], TW_kits[bonusid][MODEL], TW_kits[bonusid][AMOUNT], TW_kits[bonusid][X], TW_kits[bonusid][Y], TW_kits[bonusid][Z], TW_kits[bonusid][SPAWN_RANGE], TW_kits[bonusid][RESPAWN_TIME], TW_kits[bonusid][WORLDID], TW_kits[bonusid][INTERIORID]);
    return true;
}

forward SetPlayerSpec(playerid, bool:on);
public SetPlayerSpec(playerid, bool:on)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:ToyOfWars.pwn] SetPlayerSpec:\n\tplayerid %d\n\ton %d\n", playerid, on);
    #endif

    TogglePlayerSpectating(playerid, on);
    return true;
}

forward OnVechileEngine(vehicleid, onengine);
public OnVechileEngine(vehicleid, onengine)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:ToyOfWars.pwn] OnVechileEngine:\n\tvehicleid %d\n\tonengine %d\n", vehicleid, onengine);
    #endif

    if (IsVehicleRCHasGun(vehicleid) && onengine) {
        RCCAR_SetGun(vehicleid, 1);
    }
    SetVehicleEngine(vehicleid, onengine);
    return true;
}

forward OnMapGravity(Float:gravity);
public OnMapGravity(Float:gravity)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:ToyOfWars.pwn] OnMapGravity:\n\tgravity %.6f\n", gravity);
    #endif

    SetGravity(gravity);
    return true;
}

forward OnPlayerDisconnected(playerid, reason)
public OnPlayerDisconnected(playerid, reason)
{
    // Update hud
    TW_HideHudTeamList(playerid);
    return true;
}
// EOF Custom callbacks -------------------------------------------------------------------------------