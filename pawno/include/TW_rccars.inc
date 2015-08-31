/*
 * [include] RC Cars (OLD name 'RC Tiger Gun')
 * Version          : v4
 * Release          : v1, 7 aug 2015
 * Update           : v4, 21 aug 2015
 * Contributors     : VanillaRain, Nero_3D, Logofero aka fERO
 *
 * INSTALL:
 *      1) Copy file "rctigergun.inc" in folder "pawno/include"
 *      2) Add line in gamemode #include <TW_rccars>
 *      3) Compile gamemode. Enjoy!
 *
 * CONTROL:
 *      FIRE        - Shot of RC gun
 *      ENTER       - Enter/Exit to/of RC Vehicle
 *
 * CHANGES:
 * v1, 7 aug 2015 Maked     : base of the script by VanillaRain
 * v2, 7 aug 2015 Edited    : fix minor bugs, mod saved as include by Logofero
 * v3, 8 aug 2015 Added     : optimized algorithm from Nero_3D. Builder by Logofero
 * v4, 21 aug 2015 Edited   : special update for gamemode 'Toy Of Wars' new functions by Logofero
 */

// Build v4 by Logofero
#define ENABLE_SHOT_RANDOM_COLOR    (0) // if you disabled (0) with projectiles do not change color
#define RCCAR_RANGE_ENTER           (1.2) // Enter range in tank. Added in v3
#define RCCAR_RANGE_EXIT            (1.5) // Exit range in tank. Added in v3
#define RCCAR_TIME_FIDE_ENTER       (500) // Freezing camera for enter in tank. Added in v3
#define RC_HAS_GUN_MODELS           441,464,465,564,501 // Added for gamemode Toy of Wars
#define RC_TIME_CLEAR_DAMAGEID      (60000) // Time removal ID which caused damage to player

// RC cars info ---------------------------------------------------
#define RCCAR_MAX_AMMO              (50)
#define RCCAR_MAX_HP                (1000.0)

enum E_RCCAR_INFO {
    Float: HP,
    Float: MAXHP,
    AMMO,
    MAXAMMO,
    GUNID
}
new rccar_info[MAX_VEHICLES][E_RCCAR_INFO];

// RC gun functions. Added for Toy Of Wars
#define RCCAR_SetHP(%1,%2)          rccar_info[%1][HP]=%2
#define RCCAR_GetHP(%1)             rccar_info[%1][HP]
#define RCCAR_SetMaxHP(%1,%2)       rccar_info[%1][MAXHP]=%2
#define RCCAR_GetMaxHP(%1)          rccar_info[%1][MAXHP]
#define RCCAR_SetAmmo(%1,%2)        rccar_info[%1][AMMO]=%2
#define RCCAR_GetAmmo(%1)           rccar_info[%1][AMMO]
#define RCCAR_SetMaxAmmo(%1,%2)     rccar_info[%1][MAXAMMO]=%2
#define RCCAR_GetMaxAmmo(%1)        rccar_info[%1][MAXAMMO]
#define RCCAR_SetGun(%1,%2)         rccar_info[%1][GUNID]=%2
#define RCCAR_GetGun(%1)            rccar_info[%1][GUNID]
// EOF RC cars info ---------------------------------------------------

enum eObjectInfo {
    OBJECTID, OWNERID, VEHICLEID
}
new gObjectInfo[MAX_OBJECTS][eObjectInfo];

// New functions by Logofero ---------------------------------------------------

#define MAX_TEAM_COLOR (6)

/*
 * native GetRGBRedOfColor(color);
 * native GetRGBGreenOfColor(color);
 * native GetRGBBlueOfColor(color);
 * native GetRGBAlphaOfColor(color);
 * native SetPlayerRandomColor(playerid);
 */
#define GetRGBRedOfColor(%1) (color >> 24) & 0xFF
#define GetRGBGreenOfColor(%1) (color >> 16) & 0xFF
#define GetRGBBlueOfColor(%1) (color >> 8) & 0xFF
#define GetRGBAlphaOfColor(%1) (color & 0xFF)
#define SetPlayerRandomColor(%1) SetPlayerColor(%1, (random(0xFF)<<24 | random(0xFF)<<16 | random(0xFF)<<8 | 0xFF))

/*
 * native GetTeamColorIDOfColor(color);
 */
stock GetTeamColorIDOfColor(color) {
    //printf("red %h green %h blue %h alpha %h", GetRGBRedOfColor(color), GetRGBGreenOfColor(color), GetRGBBlueOfColor(color), GetRGBAlphaOfColor(color));

    if (GetRGBRedOfColor(color) > 0 && GetRGBRedOfColor(color) <= 0xFF
    && GetRGBGreenOfColor(color) < 0x7F
    && GetRGBBlueOfColor(color) < 0x7F) {
        //printf("GetTeamColorIDOfColor teamcolor 'Red' id %d color %h", 0, color);
        return 0;

    } else if (GetRGBGreenOfColor(color) > 0 && GetRGBGreenOfColor(color) <= 0xFF
    && GetRGBRedOfColor(color) < 0x7F
    && GetRGBBlueOfColor(color) < 0x7F) {
        //printf("GetTeamColorIDOfColor teamcolor 'Green' id %d color %h", 1, color);
        return 1;

    } else if (GetRGBBlueOfColor(color) > 0 && GetRGBBlueOfColor(color) <= 0xFF
    && GetRGBRedOfColor(color) < 0x7F
    && GetRGBGreenOfColor(color) < 0x7F) {
        //printf("GetTeamColorIDOfColor teamcolor 'Blue' id %d color %h", 2, color);
        return 2;

    } else if (GetRGBRedOfColor(color) > 0 && GetRGBRedOfColor(color) <= 0xFF
    && GetRGBBlueOfColor(color) > 0 && GetRGBBlueOfColor(color) <= 0xFF
    && GetRGBGreenOfColor(color) < 0x7F) {
        //printf("GetTeamColorIDOfColor teamcolor 'Pink' id %d color %h", 3, color);
        return 3;

    } else if (GetRGBRedOfColor(color) > 0 && GetRGBRedOfColor(color) <= 0xFF
    && GetRGBGreenOfColor(color) > 0 && GetRGBGreenOfColor(color) <= 0xFF
    && GetRGBBlueOfColor(color) < 0x7F) {
        //printf("GetTeamColorIDOfColor teamcolor 'Yellow' id %d color %h", 4, color);
        return 4;

    }
    //printf("GetTeamColorIDOfColor teamcolor 'White' id %d color %h", 5, color);
    return 5;
}

/*
 * native GetNeonModelOfTeamColorID(teamcolorid);
 */
stock GetNeonModelOfTeamColorID(teamcolorid) {
    new model;
    switch(teamcolorid) {
        case 0 : model = 18647; //Red
        case 1 : model = 18649; //Green
        case 2 : model = 18648; //Blue
        case 3 : model = 18651; //Pink
        case 4 : model = 18650; //Yellow
        case 5 : model = 18652; //White
        default : model = 18652; //White
    }
    return model;
}

/*
 * native IsPlayerKeyPress(playerid, keycode);
 */
stock IsPlayerKeyPress(playerid, keycode) {
    new key, updown, leftright;
    GetPlayerKeys(playerid, key, updown, leftright);
    //printf("PRESS player %d key %d updown %d leftright %d",playerid, key, updown, leftright);
    if(key & keycode) return true;

    else if(keycode == KEY_UP && updown == -128 && leftright == 0) return true;
    else if(keycode == KEY_DOWN && updown == 128 && leftright == 0) return true;
    else if(keycode == KEY_LEFT && updown == 0 && leftright == -128) return true;
    else if(keycode == KEY_RIGHT && updown == 0 && leftright == 128) return true;
    return false;
}

/*
 * native GetVeahiclePassengerID(vehicleid, seatid);
 */
stock GetVeahiclePassengerID(vehicleid, seatid) {
    for (new p = GetPlayerPoolSize(); p >= 0; --p) {
        if (vehicleid == GetPlayerVehicleID(p) && seatid == GetPlayerVehicleSeat(p)) {
            return p;
        }
    }
    return INVALID_PLAYER_ID;
}

/*
 * native IsVeahicleUnoccupied(vehicleid);
 */
stock IsVeahicleUnoccupied(vehicleid) {
    new v;
    for (new p = GetPlayerPoolSize(); p >= 0; --p) {
        v = GetPlayerVehicleID(p);
        if (vehicleid == v && v && vehicleid) {
            return false;
        }
    }
    return true;
}

/*
 * native IsVehicleRCHasGun(vehicleid);
 */
stock IsVehicleRCHasGun(vehicleid) {
    switch(GetVehicleModel(vehicleid)) {
        case RC_HAS_GUN_MODELS : return true;
    }
    return false;
}

/*
 * native IsVehicleRC(vehicleid);
 */
stock IsVehicleRC(vehicleid) {
    switch(GetVehicleModel(vehicleid)) {
        case 564,441,465,501,464 : return true;
    }
    return false;
}

/*
 * native GetVehicleRCGunRate(vehicleid);
 */
stock GetVehicleRCGunRate(vehicleid) {
    switch(GetVehicleModel(vehicleid)) {
        case 564        : return 1000; // RC Tiger - Assaulter
        case 465,501    : return 700; // Heli 1,2 - Mahineguner
        case 441        : return 500; // RC Car - Defender
        case 464        : return 3500; // RC Plane - Sniper
    }
    return 0;
}

/*
 * native GetVehicleRCGunRange(vehicleid);
 */
stock Float:GetVehicleRCGunRange(vehicleid) {
    switch(GetVehicleModel(vehicleid)) {
        case 564        : return 100.0; // RC Tiger
        case 465,501    : return 40.0; // Heli 1,2
        case 441        : return 20.0; // RC Car
        case 464        : return 120.0; // RC Plane
    }
    return 0.0;
}

/*
 * native GetVehicleRCGunBulletType(vehicleid);
 */
stock GetVehicleRCGunBulletType(vehicleid) {
    switch(GetVehicleModel(vehicleid)) {
        case 564        : return 11; // RC Tiger
        case 465,501    : return 12; // Heli 1,2
        case 441        : return 12; // RC Car
        case 464        : return 11; // RC Plane (6,7 big)
    }
    return 0;
}

/*
 * native GetVehicleRCGunBulletSpeed(vehicleid);
 */
stock Float:GetVehicleRCGunBulletSpeed(vehicleid) {
    switch(GetVehicleModel(vehicleid)) {
        case 564        : return 100.0; // RC Tiger
        case 465,501    : return 90.0; // Heli 1,2
        case 441        : return 80.0; // RC Car
        case 464        : return 120.0; // RC Plane
    }
    return 0.0;
}

/*
 * native Float:GetVehicleRCGunBulletSize(vehicleid);
 */
stock Float:GetVehicleRCGunBulletSize(vehicleid) {
    switch(GetVehicleModel(vehicleid)) {
        case 564        : return 1.8; // RC Tiger
        case 465,501    : return 1.2; // Heli 1,2
        case 441        : return 1.0; // RC Car
        case 464        : return 3.0; // RC Plane
    }
    return 0.0;
}

/*
 * native Float:GetVehicleRCMaxHP(vehicleid);
 */
stock Float:GetVehicleRCMaxHP(vehicleid) {
    switch(GetVehicleModel(vehicleid)) {
        case 564        : return 1200.0; // RC Tiger
        case 465,501    : return 800.0; // Heli 1,2
        case 441        : return 900.0; // RC Car
        case 464        : return 700.0; // RC Plane
    }
    return 0.0;
}

/*
 * native GetVehicleRCGunMaxAmmo(vehicleid);
 */
stock GetVehicleRCGunMaxAmmo(vehicleid) {
    switch(GetVehicleModel(vehicleid)) {
        case 564        : return 25; // RC Tiger
        case 465,501    : return 30; // Heli 1,2
        case 441        : return 30; // RC Car
        case 464        : return 20; // RC Plane
    }
    return 0;
}

/*
 * native GetVehicleRCCostScores(vehicleid);
 */
stock GetVehicleRCCostScores(vehicleid) {
    switch(GetVehicleModel(vehicleid)) {
        case 564        : return 90; // RC Tiger
        case 465,501    : return 100; // Heli 1,2
        case 441        : return 70; // RC Car
        case 464        : return 120; // RC Plane
    }
    return 0;
}

/*
 * native CreateExplosionByPlayer(playerid, Float:x, Float:y, Float:z, type, Float:range, bool:damage_team = false);
 */
stock CreateExplosionByPlayer(playerid, Float:x, Float:y, Float:z, type, Float:range, bool:damage_team = false) {
    // Custom damage for OnPlayerDeath()
    CreateExplosion(x, y, z, type, range);
    for (new p = GetPlayerPoolSize(); p >= 0; p--) {
        if ((GetPlayerTeam(playerid) == GetPlayerTeam(p) && damage_team) || (GetPlayerTeam(playerid) != GetPlayerTeam(p))) {
            if (IsPlayerInRangeOfPoint(p, range, x, y, z)) {

                // Custom damage
                /* new vehicleid = GetPlayerVehicleID(p);
                if (vehicleid && !IsPlayerControllable(p)) {
                    new Float: hp;
                    GetVehicleHealth(vehicleid, hp);
                    SetVehicleHealth(vehicleid, hp - 330.0);
                } */

                SetPVarInt(p, "DAMAGERID", playerid);
                SetTimerEx("ClearPlayerDamagerID", RC_TIME_CLEAR_DAMAGEID, 0, "i", p);
            }
        }
    }

}

/*
 * stock ExplosionAllByPlayer(playerid, type=11, Float:range=1.0, bool:damage_team = false);
 */
stock ExplosionAllByPlayer(playerid, type=11, Float:range=1.0, bool:damage_team = true) {
    new
        Float: x,
        Float: y,
        Float: z
    ;
    for (new p = GetPlayerPoolSize(); p >= 0; p--) {
        if ((GetPlayerTeam(playerid) == GetPlayerTeam(p) && damage_team) || (GetPlayerTeam(playerid) != GetPlayerTeam(p))) {
            if (playerid != p && GetPlayerPos(p, x, y, z)) {
                CreateExplosion(x, y, z, type, range);
                if (IsPlayerInRangeOfPoint(p, range, x, y, z)) {

                    // Custom damage
                    /* new vehicleid = GetPlayerVehicleID(p);
                    if (vehicleid && !IsPlayerControllable(p)) {
                        new Float: hp;
                        GetVehicleHealth(vehicleid, hp);
                        SetVehicleHealth(vehicleid, hp - 330.0);
                    } */

                    SetPVarInt(p, "DAMAGERID", playerid);
                    SetTimerEx("ClearPlayerDamagerID", RC_TIME_CLEAR_DAMAGEID, 0, "i", p);
                }
            }
        }
    }
    return true;
}
// EOF new functions ---------------------------------------------------

public OnVehicleSpawn(vehicleid)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:TW_rccars.inc] OnVehicleSpawn:\n\tvehicleid %d\n", vehicleid);
    #endif

    if (IsVehicleRCHasGun(vehicleid)) {
        RCCAR_SetHP(vehicleid, GetVehicleRCMaxHP(vehicleid));
        RCCAR_SetMaxHP(vehicleid, GetVehicleRCMaxHP(vehicleid));
        RCCAR_SetAmmo(vehicleid, GetVehicleRCGunMaxAmmo(vehicleid));
        RCCAR_SetMaxAmmo(vehicleid, GetVehicleRCGunMaxAmmo(vehicleid));
        RCCAR_SetGun(vehicleid, 1);

        SetVehicleHealth(vehicleid, RCCAR_GetHP(vehicleid));
    }

    #if defined RCCAR_OnVehicleSpawn
        return CallLocalFunction("RCCAR_OnVehicleSpawn", "i", vehicleid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnVehicleSpawn
    #undef OnVehicleSpawn
#else
    #define _ALS_OnVehicleSpawn
#endif
#define OnVehicleSpawn RCCAR_OnVehicleSpawn
forward RCCAR_OnVehicleSpawn(vehicleid);

public OnPlayerDeath(playerid, killerid, reason)
{
    // Fix: Set cam look to vehicle if player is dead in RC car
    new vehicleid = GetPlayerVehicleID(playerid);
    if (IsVehicleRCHasGun(vehicleid)) {
        new
            Float: x,
            Float: y,
            Float: z,

            Float: tx,
            Float: ty,
            Float: tz
        ;
        GetVehiclePos(vehicleid, tx, ty, tz);
        GetPlayerCameraPos(playerid, x, y, z);
        RemovePlayerFromVehicle(playerid);
        SetPlayerPos(playerid, tx, ty, tz - 50.0);
        SetPlayerCameraPos(playerid, x, y, z);
        SetPlayerCameraLookAt(playerid, tx, ty, tz, CAMERA_CUT);
    }
    // EOF Fix

    #if defined RCCAR_OnPlayerDeath
        return CallLocalFunction("RCCAR_OnPlayerDeath", "iii", playerid, killerid, reason);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerDeath
    #undef OnPlayerDeath
#else
    #define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath RCCAR_OnPlayerDeath
forward RCCAR_OnPlayerDeath(playerid, killerid, reason);

public OnPlayerUpdate(playerid)
{
    // Version by Logofero ---------------------------------------------------
    // Enter/Exit to/of RC vehicle
    if (IsPlayerKeyPress(playerid, KEY_SECONDARY_ATTACK)) {
        new vehicleid = GetPlayerVehicleID(playerid);
        new
            Float: x,
            Float: y,
            Float: z,
            Float: hp
        ;
        if (!vehicleid) {
            for(new v = GetVehiclePoolSize(); v >= 1; --v) {
                if (!IsVehicleRCHasGun(v) || v == INVALID_VEHICLE_ID) continue;
                GetVehicleHealth(v, hp);
                GetVehiclePos(v, x, y, z);
                if (IsPlayerInRangeOfPoint(playerid, RCCAR_RANGE_ENTER, x, y, z) && IsVeahicleUnoccupied(v) && hp >= 250.0) {

                    // Hide skin if a player entere in toy vehicle ---------------------------------------------------
                    new
                        Float: x2,
                        Float: y2,
                        Float: z2
                    ;
                    TogglePlayerControllable(playerid, false);
                    GetPlayerCameraFrontVector(playerid, x2, y2, z2);
                    x2 = x + x2 * 1.0;
                    y2 = y + x2 * 1.0;
                    z2 = z + x2 * 1.0;
                    GetPlayerCameraPos(playerid, x, y, z);
                    SetPlayerPos(playerid, x, y, z - 50.0);
                    SetPlayerCameraPos(playerid, x * 1.0, y * 1.0, z * 1.0);
                    //SetPlayerCameraLookAt(playerid, x2, y2, z2, CAMERA_MOVE);
                    GetVehiclePos(v, x2, y2, z2);
                    SetPlayerCameraLookAt(playerid, x2, y2, z2, CAMERA_MOVE);
                    SetTimerEx("PutPlayerInVehicleRC", RCCAR_TIME_FIDE_ENTER, 0, "iii", playerid, v, 0); // Making delay time for hide
                    // EOF Hide skin ---------------------------------------------------

                }
            }
        } else if (IsVehicleRCHasGun(vehicleid)) {

            GetVehiclePos(vehicleid, x, y, z);
            RemovePlayerFromVehicle(playerid);
            SetPlayerPos(playerid, x + RCCAR_RANGE_EXIT, y + RCCAR_RANGE_EXIT, z + 0.5); // Remove player from toy vehicle
        }
    }
    // Shot of RC gun
    if(IsPlayerControllable(playerid) && IsPlayerKeyPress(playerid, KEY_FIRE))// Only run the code if the object doesn't already exist, otherwise more objects will take up gRocketObj and the previous ones won't be deleted
 	{

        // Version by Nero_3D ---------------------------------------------------
        new
            vehicleid = GetPlayerVehicleID(playerid)
        ;
        if(vehicleid) {
            if(IsVehicleRCHasGun(GetPlayerVehicleID(playerid)) && RCCAR_GetGun(vehicleid) && RCCAR_GetAmmo(vehicleid) > 0) {
                static
                    delay[MAX_PLAYERS]
                ;
                new
                    count = tickcount()
                ;
                if(delay[playerid] < count) {
                    new
                        objectid,
                        Float: x,
                        Float: y,
                        Float: z,
                        Float: vx,
                        Float: vy,
                        Float: vz,
                        Float: rx,
                        Float: rz
                    ;
                    GetVehicleRotationQuat(vehicleid, rx, x, y, z);

                    vx = 2.0 * (y * x + z * rx);
                    vy = 1.0 - 2.0 * (z * z + x * x);
                    vz = 2.0 * (y * z - x * rx);
                    rz = atan2(vy, vx) - 90.0;
                    rx = asin(vz);

                    GetVehiclePos(vehicleid, x, y, z);

                    #if ENABLE_SHOT_RANDOM_COLOR
                    // Nick change color with every shot by Logofero
                    SetPlayerRandomColor(playerid);
                    #endif

                    // It creates a neon colors depending nick Player by Logofero
                    objectid = CreateObject( GetNeonModelOfTeamColorID( GetTeamColorIDOfColor( GetPlayerColor(playerid) ) ), x, y, z + 0.45, rx, 0, rz);

                    if(objectid != INVALID_OBJECT_ID) {
                        new
                            Float: tx,
                            Float: ty,
                            Float: tz
                        ;
                        rx = GetVehicleRCGunRange(vehicleid);
                        // Bullet magnet
                        for(new i = GetPlayerPoolSize(); i >= 0; --i) {
                            if(IsPlayerInRangeOfPoint(i, rx, x, y, z) && i != playerid && GetPlayerTeam(playerid) != GetPlayerTeam(i)) {
                                GetPlayerPos(i, tx, ty, tz);

                                tx -= x;
                                ty -= y;
                                tz -= z;

                                rz = VectorSize(vy * tz - vz * ty, vz * tx - vx * tz, vx * ty - vy * tx);

                                if(rz < GetVehicleRCGunBulletSize(vehicleid)) { // distance point to line
                                    rz = vx * tx + vy * ty + vz * tz; // dot product - also distance vehicle-impact

                                    if(0.0 < rz) { // check if it is before the tank
                                        rx = rz;
                                    }
                                }
                                break;
                            }
                        }
                        MoveObject(objectid, x + vx * rx, y + vy * rx, z + vz * rx, GetVehicleRCGunBulletSpeed(vehicleid));
                        //SetPlayerTime(playerid, 0, 0); // Offned for v3

                        // Added by Logofero in v4 ---------------------------------------------------
                        gObjectInfo[objectid][OBJECTID] = objectid;
                        gObjectInfo[objectid][OWNERID] = playerid;
                        gObjectInfo[objectid][VEHICLEID] = vehicleid;

                        // Gun rate
                        delay[playerid] = count + GetVehicleRCGunRate(vehicleid);

                        // Ammo limit. Added for Toy Of Wars
                        RCCAR_SetAmmo(vehicleid, RCCAR_GetAmmo(vehicleid)-1);
                        if (RCCAR_GetAmmo(vehicleid) < 0) RCCAR_SetAmmo(vehicleid, 0);
                        // EOF Added by Logofero in v4 ---------------------------------------------------
                    }
                }
            }
        }
        // EOF Version by Nero_3D ---------------------------------------------------
	}
    #if defined RCCAR_OnPlayerUpdate
        return CallLocalFunction("RCCAR_OnPlayerUpdate", "i", playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerUpdate
    #undef OnPlayerUpdate
#else
    #define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate RCCAR_OnPlayerUpdate
forward RCCAR_OnPlayerUpdate(playerid);

public OnObjectMoved(objectid)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:TW_rccars.inc] OnObjectMoved:\n\tobjectid %d\n\tshot_objectid %d\n\tshot_vehicleid %d\n\tshot_ownerid %d\n", objectid, gObjectInfo[objectid][OBJECTID], gObjectInfo[objectid][VEHICLEID], gObjectInfo[objectid][OWNERID]);
    #endif

    // Version by NERO_3D ---------------------------------------------------
    if (gObjectInfo[objectid][OBJECTID] != INVALID_OBJECT_ID) { // Edited by Logofero
         new
             Float: x,
             Float: y,
             Float: z
         ;
         GetObjectPos(objectid, x, y, z);
         //CreateExplosion(x, y, z, 11, 3.0); // Offned for v4

         // Added by Logofero in v4
         DestroyObject(objectid);
         CreateExplosionByPlayer(gObjectInfo[objectid][OWNERID], x, y, z, GetVehicleRCGunBulletType(gObjectInfo[objectid][VEHICLEID]), 3.0, false); // Custom damage for OnPlayerDeath()

         gObjectInfo[objectid][OWNERID] = INVALID_PLAYER_ID;
         gObjectInfo[objectid][OBJECTID] = INVALID_OBJECT_ID;
         gObjectInfo[objectid][VEHICLEID] = INVALID_VEHICLE_ID;
         // EOF
    }
    // EOF Version by NERO_3D ---------------------------------------------------

    #if defined RCCAR_OnObjectMoved
        return CallLocalFunction("RCCAR_OnObjectMoved", "i", objectid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnObjectMoved
    #undef OnObjectMoved
#else
    #define _ALS_OnObjectMoved
#endif
#define OnObjectMoved RCCAR_OnObjectMoved
forward RCCAR_OnObjectMoved(objectid);
// EOF Build v4 by Logofero ---------------------------------------------------

// Custom callbacks ---------------------------------------------------
forward PutPlayerInVehicleRC(playerid, vehicleid, seatid);
public PutPlayerInVehicleRC(playerid, vehicleid, seatid)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:TW_rccars.inc] PutPlayerInVehicleRC:\n\tplayerid %d\n\tvehicleid %d\n\tseatid %d\n", playerid, vehicleid, seatid);
    #endif

    PutPlayerInVehicle(playerid, vehicleid, seatid);
    //SetCameraBehindPlayer(playerid);
    TogglePlayerControllable(playerid, true);
    return true;
}
// EOF Custom callbacks ---------------------------------------------------
