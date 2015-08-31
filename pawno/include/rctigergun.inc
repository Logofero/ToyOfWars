/*
 * [include] RC Tiger Gun
 * Version          : v3
 * Release          : v1, 7 aug 2015
 * Update           : v3, 8 aug 2015
 * Contributors     : VanillaRain, Nero_3D, Logofero aka fERO
 *
 * INSTALL:
 *      1) Copy file "rctigergun.inc" in folder "pawno/include"
 *      2) Add line in gamemode #include <rctigergun>
 *      3) Compile gamemode. Enjoy!
 *
 * CONTROL:
 *      FIRE/ACTION  - Shooting of RC gun
 *      ENTER        - Enter/Exit to/of RC Vehicles
 *
 * CHANGES:
 * v1, 7 aug 2015 Maked  : base of the script by VanillaRain
 * v2, 7 aug 2015 Edited : fix minor bugs, mod saved as include by Logofero
 * v3, 8 aug 2015 Added  : optimized algorithm from Nero_3D. Builder by Logofero
 */
 
// Build v3 by Logofero
#define RCTANKGUN_GUN_RATE          (50) // Rate gun in ms. Now it's a machinegun
#define RCTANKGUN_GUN_RANGE         (100.0) // Maximal distance of the projectile. Added in v3
#define ENABLE_SHOT_RANDOM_COLOR    (0) // if you disabled (0) with projectiles do not change color
#define RCTANKGUN_RANGE_ENTER       (1.2) // Enter range in tank. Added in v3
#define RCTANKGUN_RANGE_EXIT        (1.5) // Exit range in tank. Added in v3
#define RCTANKGUN_MODEL_TANK        (564) // RC Tiger
#define RCTANKGUN_TIME_FIDE_ENTER   (2000) // Freezing camera for enter in tank. Added in v3
#define RC_HAS_GUN_MODELS           441,464,465,564,501 // Added for gamemode Toy of Wars

/* Offned for v3
new FireShot[MAX_PLAYERS];
new gRocketObj[MAX_PLAYERS][MAX_OBJECTS];
*/

// Version by Nero_3D ---------------------------------------------------
enum eObjectInfo {
    eObjectRocket
}

new eObjectInfo: gObjectInfo[MAX_OBJECTS];
// EOF Version by Nero_3D ---------------------------------------------------

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
    new neonid;
    switch(teamcolorid) {
        case 0 : neonid = 18647; //Red
        case 1 : neonid = 18649; //Green
        case 2 : neonid = 18648; //Blue
        case 3 : neonid = 18651; //Pink
        case 4 : neonid = 18650; //Yellow
        case 5 : neonid = 18652; //White
        default : neonid = 18652; //White
    }
    return neonid;
}

/*
 * native IsPlayerKeyPress(playerid, keycode);
 */
stock IsPlayerKeyPress(playerid, keycode) { 
    new key, updown, leftright;
    GetPlayerKeys(playerid, key, updown, leftright);
    //printf("PRESS player %d key %d updown %d leftright %d",playerid, key, updown, leftright);
    if(key & keycode) return 1;
    
    else if(keycode == KEY_UP && updown == -128 && leftright == 0) return 1;
    else if(keycode == KEY_DOWN && updown == 128 && leftright == 0) return 1;
    else if(keycode == KEY_LEFT && updown == 0 && leftright == -128) return 1;
    else if(keycode == KEY_RIGHT && updown == 0 && leftright == 128) return 1;    
    return 0;
}

/*
 * native IsRCVehicleHasGun(vehicleid);
 */
stock IsRCVehicleHasGun(vehicleid) {
    switch(GetVehicleModel(vehicleid)) {
        case RC_HAS_GUN_MODELS : return true;
    }
    return false;
}

/*
 * native GetRCVehicleGunRate(vehicleid);
 */
// Added for gamemode Toy Of Wars
stock GetRCVehicleGunRate(vehicleid) {
    switch(GetVehicleModel(vehicleid)) {
        case 564        : return 1000; // RC Tiger - Assaulter
        case 465,501    : return 700; // Heli 1,2 - Mahineguner
        case 441        : return 500; // RC Car - Defender
        case 464        : return 4500; // RC Plane - Sniper
    }
    return 0;
}

/*
 * native GetRCVehicleGunRange(vehicleid);
 */
// Added for gamemode Toy Of Wars
stock Float:GetRCVehicleGunRange(vehicleid) {
    switch(GetVehicleModel(vehicleid)) {
        case 564        : return 100.0; // RC Tiger
        case 465,501    : return 40.0; // Heli 1,2
        case 441        : return 20.0; // RC Car
        case 464        : return 120.0; // RC Plane
    }
    return 0.0;
}

/*
 * native GetRCVehicleGunType(vehicleid);
 */
// Added for gamemode Toy Of Wars
stock GetRCVehicleGunType(vehicleid) {
    switch(GetVehicleModel(vehicleid)) {
        case 564        : return 11; // RC Tiger 
        case 465,501    : return 1; // Heli 1,2 
        case 441        : return 12; // RC Car 
        case 464        : return 9; // RC Plane
    }
    return 0;
}
// EOF new functions ---------------------------------------------------

/* Offned for v3
// Version by VanillaRain ---------------------------------------------------

new FireShot[MAX_PLAYERS];
new gRocketObj[MAX_PLAYERS][MAX_OBJECTS];

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 564 && FireShot[playerid] == 0 && KEY_FIRE & newkeys)// Only run the code if the object doesn't already exist, otherwise more objects will take up gRocketObj and the previous ones won't be deleted
 	{
  		SetPlayerTime(playerid,0,0);
        new
        	vehicleid = GetPlayerVehicleID(playerid),
         	Float:x,
            Float:y,
            Float:z,
            Float:r,
            Float:dist = 50.0,
            Float:tmpang,
            Float:tmpx,
            Float:tmpy,
            Float:tmpz;

		FireShot[playerid] = 1;
        SetTimerEx("ShotFire", RCTANKGUN_GUN_RATE, 0, "i", playerid);
        GetVehiclePos(vehicleid, x, y, z);
        
        GetVehicleZAngle(vehicleid, r);
        new rand = random(12);
         switch(rand)
        {
        	case 0: gRocketObj[playerid] = CreateObject(18647, x, y, z, 0, 0, r);
            case 1: gRocketObj[playerid] = CreateObject(18648, x, y, z, 0, 0, r);
            case 2: gRocketObj[playerid] = CreateObject(18649, x, y, z, 0, 0, r);
            case 3: gRocketObj[playerid] = CreateObject(18650, x, y, z, 0, 0, r);
            case 4: gRocketObj[playerid] = CreateObject(18651, x, y, z, 0, 0, r);
            case 5: gRocketObj[playerid] = CreateObject(18652, x, y, z, 0, 0, r);
            case 6: gRocketObj[playerid] = CreateObject(18647, x, y, z, 0, 0, r+90);
            case 7: gRocketObj[playerid] = CreateObject(18648, x, y, z, 0, 0, r+90);
            case 8: gRocketObj[playerid] = CreateObject(18649, x, y, z, 0, 0, r+90);
            case 9: gRocketObj[playerid] = CreateObject(18650, x, y, z, 0, 0, r+90);
            case 10: gRocketObj[playerid] = CreateObject(18651, x, y, z, 0, 0, r+90);
            case 11: gRocketObj[playerid] = CreateObject(18652, x, y, z, 0, 0, r+90);
		} 
		for(new i;i<MAX_PLAYERS;i++)
        {
            if(IsPlayerConnected(i))
        	if(i == playerid)continue;
            if(IsPlayerInRangeOfPoint(i, 50.0, x, y, z))
            {
            	GetPlayerPos(i, tmpx, tmpy, tmpz);
                tmpang = (90-atan2(tmpy-y, tmpx-x));
                if(tmpang < 0)tmpang = 360.0+tmpang;
                tmpang = 360.0 - tmpang;
                if(floatabs(tmpang-r) < 5.0)
                {
                	dist = GetPlayerDistanceFromPoint(i, x, y, z);
                }
            }
		}
		MoveObject(gRocketObj[playerid],x + (dist * floatsin(-r, degrees)),y + (dist * floatcos(-r, degrees)),z,100.0);                             // Nice and fast!
	}
    #if defined TIGERGUN_OnPlayerKeyStateChange
        return CallLocalFunction("TIGERGUN_OnPlayerKeyStateChange", "iii", playerid, newkeys, oldkeys);
    #else
        return 1;
    #endif  	
}
#if defined _ALS_OnPlayerKeyStateChange
    #undef OnPlayerKeyStateChange
#else
    #define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange TIGERGUN_OnPlayerKeyStateChange
forward TIGERGUN_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);

forward ShotFire(playerid);
public ShotFire(playerid)
{
     FireShot[playerid] = 0;
     return 1;
} 
// EOF Version by VanillaRain ---------------------------------------------------

// Version by Nero_3D ---------------------------------------------------
// Actual algorithm

enum eObjectInfo {
    eObjectRocket
}

new eObjectInfo: gObjectInfo[MAX_OBJECTS];

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    switch(newkeys & (newkeys ^ oldkeys)) {
        case KEY_FIRE: {
            new
                vehicleid = GetPlayerVehicleID(playerid)
            ;
            if(vehicleid) {
                if(GetVehicleModel(vehicleid) == 564) {
                    static
                        delay[MAX_PLAYERS]
                    ;
                    new
                        count = tickcount()
                    ;
                    if(delay[playerid] < count) {
                        new
                            objectid,
                            Float: X,
                            Float: Y,
                            Float: Z,
                            Float: vX,
                            Float: vY,
                            Float: vZ,
                            Float: rX,
                            Float: rZ
                        ;
                        GetVehicleRotationQuat(vehicleid, rX, X, Y, Z);

                        vX = 2.0 * (Y * X + Z * rX);
                        vY = 1.0 - 2.0 * (Z * Z + X * X);
                        vZ = 2.0 * (Y * Z - X * rX);
                        rZ = atan2(vY, vX) - 90.0;
                        rX = asin(vZ);

                        GetVehiclePos(vehicleid, X, Y, Z);
                        objectid = CreateObject(18647 + random(6), X, Y, Z, rX, 0, rZ);

                        if(objectid != INVALID_OBJECT_ID) {
                            new
                                Float: tX,
                                Float: tY,
                                Float: tZ
                            ;
                            rX = 50.0;

                            for(new i = GetPlayerPoolSize(); i >= 0; --i) {
                                if(IsPlayerInRangeOfPoint(i, rX, X, Y, Z) && i != playerid) {
                                    GetPlayerPos(i, tX, tY, tZ);

                                    tX -= X;
                                    tY -= Y;
                                    tZ -= Z;

                                    rZ = VectorSize(vY * tZ - vZ * tY, vZ * tX - vX * tZ, vX * tY - vY * tX);

                                    if(rZ < 5.0) { // distance point to line
                                        rZ = vX * tX + vY * tY + vZ * tZ; // dot product - also distance vehicle-impact

                                        if(0.0 < rZ) { // check if it is before the tank
                                            rX = rZ;
                                        }
                                    }
                                }
                            }
                            MoveObject(objectid, X + vX * rX, Y + vY * rX, Z + vZ * rX, 100.0);
                            SetPlayerTime(playerid, 0, 0);

                            gObjectInfo[objectid] = eObjectRocket;
                            delay[playerid] = count + 1000;
                        }
                    }
                }
            }
        }
    }
    return true;
}

public OnObjectMoved(objectid) {
    switch(gObjectInfo[objectid]) {
        case eObjectRocket: {
            new
                Float: X,
                Float: Y,
                Float: Z
            ;
            GetObjectPos(objectid, X, Y, Z);
            CreateExplosion(X, Y, Z, 11, 3.0);
            DestroyObject(objectid);
        }
    }
}  
// EOF Version by Nero_3D ---------------------------------------------------
*/

stock GetVeahiclePassengerID(vehicleid, seatid) {
    for (new p = GetPlayerPoolSize(); p >= 0; --p) {        
        if (vehicleid == GetPlayerVehicleID(p) && seatid == GetPlayerVehicleSeat(p)) {
            return p;
        }
    }
    return INVALID_PLAYER_ID;
}

forward PutPlayerInVehicleEx(playerid, vehicleid, seatid);
public PutPlayerInVehicleEx(playerid, vehicleid, seatid) {
    PutPlayerInVehicle(playerid, vehicleid, seatid);
    SetCameraBehindPlayer(playerid);
    TogglePlayerControllable(playerid, true);
    return true;
}

public OnPlayerUpdate(playerid)
{
    if (IsPlayerKeyPress(playerid, KEY_SECONDARY_ATTACK)) { 
        new vehicleid = GetPlayerVehicleID(playerid);
        new
            Float: X,
            Float: Y,
            Float: Z
        ;
        if (!vehicleid) {
            for(new v = GetVehiclePoolSize(); v >= 0; --v) {
                if (!IsRCVehicleHasGun(v)) continue;
                
                GetVehiclePos(v, X, Y, Z);  
                if (IsPlayerInRangeOfPoint(playerid, RCTANKGUN_RANGE_ENTER, X, Y, Z) && GetVeahiclePassengerID(vehicleid, 0) == INVALID_PLAYER_ID) {
                 
                    // Hide skin player if he sits in a toy vehicles ---------------------------------------------------
                    new
                        Float: X2,
                        Float: Y2,
                        Float: Z2
                    ; 
                    TogglePlayerControllable(playerid, false);
                    GetPlayerCameraFrontVector(playerid, X2, Y2, Z2);  
                    X2 = X + X2 * 1.0;
                    Y2 = Y + X2 * 1.0;
                    Z2 = Z + X2 * 1.0;                     
                    GetPlayerCameraPos(playerid, X, Y, Z);                                        
                    SetPlayerPos(playerid, X, Y, Z - 50.0);                    
                    SetPlayerCameraPos(playerid, X * 1.0, Y * 1.0, Z * 1.0);                    
                    //SetPlayerCameraLookAt(playerid, X2, Y2, Z2, CAMERA_MOVE);                      
                    GetVehiclePos(v, X2, Y2, Z2);  
                    SetPlayerCameraLookAt(playerid, X2, Y2, Z2, CAMERA_MOVE);                    
                    SetTimerEx("PutPlayerInVehicleEx", RCTANKGUN_TIME_FIDE_ENTER, 0, "iii", playerid, v, 0); // Making delay time for hide   
                    // EOF ---------------------------------------------------
                    
                }
            }       
        } else if (IsRCVehicleHasGun(vehicleid)) {
            GetVehiclePos(vehicleid, X, Y, Z);             
            RemovePlayerFromVehicle(playerid); 
            SetPlayerPos(playerid, X + RCTANKGUN_RANGE_EXIT, Y + RCTANKGUN_RANGE_EXIT, Z + 0.5); // Remove player from toy vehicle   
        }        
    }
    if(IsPlayerKeyPress(playerid, KEY_FIRE + KEY_ACTION))// Only run the code if the object doesn't already exist, otherwise more objects will take up gRocketObj and the previous ones won't be deleted
 	{
 	    
 	    /* Offned for v3
 	    // Version Logofero ---------------------------------------------------
 	    FireShot[playerid] = GetTickCount();
  		SetPlayerTime(playerid,0,0);
        new
        	vehicleid = GetPlayerVehicleID(playerid),
         	Float:x,
            Float:y,
            Float:z,
            Float:r,
            Float:dist = 50.0,
            Float:tmpang,
            Float:tmpx,
            Float:tmpy,
            Float:tmpz;

		//FireShot[playerid] = 1; // Offned for v2
        //SetTimerEx("ShotFire", 1000, 0, "i", playerid); // Offned for v2
        GetVehiclePos(vehicleid, x, y, z);                      
        GetVehicleZAngle(vehicleid, r);

        #if ENABLE_SHOT_RANDOM_COLOR 
        // Nick change color with every shot
        SetPlayerRandomColor(playerid);
        #endif
        
		new id = CreateObject(GetNeonModelOfTeamColorID(GetTeamColorIDOfColor(GetPlayerColor(playerid))), x + (1.0 * floatsin(-r, degrees)),y + (1.0 * floatcos(-r, degrees)), z + 0.48, 0, 0, r);
		gRocketObj[playerid][id] = id;
		
		for(new i;i<MAX_PLAYERS;i++)
        {
            if(IsPlayerConnected(i))
        	if(i == playerid)continue;
            if(IsPlayerInRangeOfPoint(i, 50.0, x, y, z))
            {
            	GetPlayerPos(i, tmpx, tmpy, tmpz);
                tmpang = (90-atan2(tmpy-y, tmpx-x));
                if(tmpang < 0)tmpang = 360.0+tmpang;
                tmpang = 360.0 - tmpang;
                if(floatabs(tmpang-r) < 5.0)
                {
                	dist = GetPlayerDistanceFromPoint(i, x, y, z);
                }
            }
		}
		MoveObject(gRocketObj[playerid][id],x + (dist * floatsin(-r, degrees)),y + (dist * floatcos(-r, degrees)),z, 100.0);
		*/
		// EOF Version Logofero ---------------------------------------------------

        // Version by Nero_3D ---------------------------------------------------
        new
            vehicleid = GetPlayerVehicleID(playerid)
        ;
        if(vehicleid) {
            if(IsRCVehicleHasGun(GetPlayerVehicleID(playerid))) {
                static
                    delay[MAX_PLAYERS]
                ;
                new
                    count = tickcount()
                ;
                if(delay[playerid] < count) {
                    new
                        objectid,
                        Float: X,
                        Float: Y,
                        Float: Z,
                        Float: vX,
                        Float: vY,
                        Float: vZ,
                        Float: rX,
                        Float: rZ
                    ;
                    GetVehicleRotationQuat(vehicleid, rX, X, Y, Z);

                    vX = 2.0 * (Y * X + Z * rX);
                    vY = 1.0 - 2.0 * (Z * Z + X * X);
                    vZ = 2.0 * (Y * Z - X * rX);
                    rZ = atan2(vY, vX) - 90.0;
                    rX = asin(vZ);

                    GetVehiclePos(vehicleid, X, Y, Z);
                    //objectid = CreateObject(18647 + random(6), X, Y, Z, rX, 0, rZ); // Offned for v3
                    
                    #if ENABLE_SHOT_RANDOM_COLOR 
                    // Nick change color with every shot by Logofero
                    SetPlayerRandomColor(playerid);
                    #endif
                    
                    // It creates a neon colors depending nick Player by Logofero
                    objectid = CreateObject( GetNeonModelOfTeamColorID( GetTeamColorIDOfColor( GetPlayerColor(playerid) ) ), X, Y, Z + 0.45, rX, 0, rZ);                   

                    if(objectid != INVALID_OBJECT_ID) {
                        new
                            Float: tX,
                            Float: tY,
                            Float: tZ
                        ;
                        rX = GetRCVehicleGunRange(vehicleid);

                        for(new i = GetPlayerPoolSize(); i >= 0; --i) {
                            if(IsPlayerInRangeOfPoint(i, rX, X, Y, Z) && i != playerid) {
                                GetPlayerPos(i, tX, tY, tZ);

                                tX -= X;
                                tY -= Y;
                                tZ -= Z;

                                rZ = VectorSize(vY * tZ - vZ * tY, vZ * tX - vX * tZ, vX * tY - vY * tX);

                                if(rZ < 5.0) { // distance point to line
                                    rZ = vX * tX + vY * tY + vZ * tZ; // dot product - also distance vehicle-impact

                                    if(0.0 < rZ) { // check if it is before the tank
                                        rX = rZ;
                                    }
                                }
                            }
                        }
                        MoveObject(objectid, X + vX * rX, Y + vY * rX, Z + vZ * rX, 100.0);
                        //SetPlayerTime(playerid, 0, 0); // Offned for v3

                        gObjectInfo[objectid] = eObjectRocket;
                        delay[playerid] = count + GetRCVehicleGunRate(vehicleid);
                    }
                }
            }
        }	
        // EOF Version by Nero_3D ---------------------------------------------------					
	}
    #if defined TIGERGUN_OnPlayerUpdate
        return CallLocalFunction("TIGERGUN_OnPlayerUpdate", "i", playerid);
    #else
        return 1;
    #endif  	
}
#if defined _ALS_OnPlayerUpdate
    #undef OnPlayerUpdate
#else
    #define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate TIGERGUN_OnPlayerUpdate
forward TIGERGUN_OnPlayerUpdate(playerid);

public OnObjectMoved(objectid)
{
     /* Offned for v3
     for(new i;i<MAX_PLAYERS;i++)
     {
         if(objectid == gRocketObj[i][objectid])
         {
             new
             	Float:x,
              	Float:y,
               	Float:z;

             GetObjectPos(gRocketObj[i][objectid], x, y, z);
             CreateExplosion(x, y, z, 11, 3.0);
             DestroyObject(objectid);
             gRocketObj[i][objectid] = INVALID_OBJECT_ID;
         }
    }
    */
    // EOF Offned
    
    // Version by NERO_3D ---------------------------------------------------	
    switch(gObjectInfo[objectid]) {
        case eObjectRocket: {
            new
                Float: X,
                Float: Y,
                Float: Z
            ;
            GetObjectPos(objectid, X, Y, Z);
            CreateExplosion(X, Y, Z, 11, 3.0);
            DestroyObject(objectid);
        }
    } 
    // EOF Version by NERO_3D ---------------------------------------------------	
    
    #if defined TIGERGUN_OnObjectMoved
        return CallLocalFunction("TIGERGUN_OnObjectMoved", "i", objectid);
    #else
        return 1;
    #endif              
}
#if defined _ALS_OnObjectMoved
    #undef OnObjectMoved
#else
    #define _ALS_OnObjectMoved
#endif
#define OnObjectMoved TIGERGUN_OnObjectMoved
forward TIGERGUN_OnObjectMoved(objectid);
// EOF Build v3 by Logofero ---------------------------------------------------
