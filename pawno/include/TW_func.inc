/*
 * [include] TW_func maked for gamemode Toy Of Wars
 * Updated : 20:18 17.08.2015
 * Author  : Logofero aka fERO
 */

#define SetPlayerVID(%1,%2)   SetPVarInt(%1, "VEHICLEID", (0+%2))
#define GetPlayerVID(%1)      GetPVarInt(%1, "VEHICLEID")

/*
 * native IsPlayerControllable(playerid);
 */
stock IsPlayerControllable(playerid) {
    if (!GetPVarInt(playerid, "CONTROLLABLE")) return true;
    return false;
}

/*
 * native Float:floatrandom(Float:min, Float:max);
 */
stock Float:floatrandom(Float:min, Float:max) {
    new num = floatround(min);
	return (float(random((floatround(max) - num) * 100) + (num * 100)) / 100.0);
}

/*
 * native CreateCutZone(gangzone[4], Float:minx, Float:miny, Float:maxx, Float:maxy);
 */
stock CreateCutZone(gangzone[4], Float:minx, Float:miny, Float:maxx, Float:maxy) {

    #if DEBUG_PRINT
    printf("[FUNC:TW_func.inc] CreateCutZone:\n\tminx %.4f miny %.4f maxx %.4f maxy %.4f\n", minx, miny, maxx, maxy);
    #endif

    gangzone[0] = GangZoneCreate(minx, maxy, maxx, 3000.0);         // top
    gangzone[1] = GangZoneCreate(-3000.0, -3000.0, minx, 3000.0);   // left
    gangzone[2] = GangZoneCreate(minx, -3000.0, maxx, miny);        // bottom
    gangzone[3] = GangZoneCreate(maxx, -3000.0, 3000.0, 3000.0);    // right
}

/*
 * native ShowPlayerCutZone(playerid, gangzone[4], color);
 */
stock ShowPlayerCutZone(playerid, gangzone[4], color) {
    for (new i; i < 4; i++) {
        GangZoneShowForPlayer(playerid, gangzone[i], color);
    }
}

/*
 * native HidePlayerCutZone(playerid, gangzone[4]);
 */
stock HidePlayerCutZone(playerid, gangzone[4]) {
    for (new i; i < 4; i++) {
        GangZoneHideForPlayer(playerid, gangzone[i]);
    }
}

/*
 * native ShowAllCutZone(gangzone[4], color);
 */
stock ShowAllCutZone(gangzone[4], color) {
    for (new i; i < 4; i++) {
        GangZoneShowForAll(gangzone[i], color);
    }
}

/*
 * native HideAllCutZone(gangzone[4]);
 */
stock HideAllCutZone(gangzone[4]) {
    for (new i; i < 4; i++) {
        GangZoneHideForAll(gangzone[i]);
    }
}

/*
 * native DestroyCutZone(gangzone[4]);
 */
stock DestroyCutZone(gangzone[4]) {
    for (new i; i < 4; i++) {
        GangZoneHideForAll(gangzone[i]);
        GangZoneDestroy(gangzone[i]);
    }
}

/*
 * native SetCutZoneFlashForPlayer(playerid, gangzone[4], color);
 */
stock SetCutZoneFlashForPlayer(playerid, gangzone[4], color) {
    for (new i; i < 4; i++) {
        GangZoneFlashForPlayer(playerid, gangzone[i], color);
    }
}

/*
 * native SetCutZoneStopFlashForPlayer(playerid, gangzone[4]);
 */
stock SetCutZoneStopFlashForPlayer(playerid, gangzone[4]) {
    for (new i; i < 4; i++) {
        GangZoneStopFlashForPlayer(playerid, gangzone[i]);
    }
}

/*
 * native SetCutZoneFlashForAll(gangzone[4], color);
 */
stock SetCutZoneFlashForAll(gangzone[4], color) {
    for (new i; i < 4; i++) {
        GangZoneFlashForAll(gangzone[i], color);
    }
}

/*
 * native SetCutZoneStopFlashForAll(gangzone[4]);
 */
stock SetCutZoneStopFlashForAll(gangzone[4]) {
    for (new i; i < 4; i++) {
        GangZoneStopFlashForAll(gangzone[i]);
    }
}

/*
 * native CreateVehicleEx(model, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, addsiren, worldid, interiorid);
 */
stock CreateVehicleEx(model, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, addsiren, worldid, interiorid) {
    new vehicleid;
    vehicleid = CreateVehicle(model, x, y, z, rotation, color1, color2, respawn_delay, addsiren);
    //vehicleid = AddStaticVehicleEx(model, x, y, z, rotation, color1, color2, respawn_delay, addsiren);

    if (!vehicleid) return INVALID_VEHICLE_ID;
    LinkVehicleToInterior(vehicleid, interiorid);
    SetVehicleVirtualWorld(vehicleid, worldid);
    return vehicleid;
}

/*
 * native IsPointInArea3D(Float:x, Float:y, Float:z, Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz);
 */
stock IsPointInArea3D(Float:x, Float:y, Float:z, Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz) {
    if (x >= minx && x <= maxx && y >= miny && y <= maxy && z >= minz && z <= maxz) {
        return true;
    }
    return false;
}

/*
 * native IsPlayerInArea3D(playerid, Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz);
 */
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

/*
 * native RespawnAllVehicles();
 */
stock RespawnAllVehicles() {
    for (new v = GetVehiclePoolSize(); v >= 1; --v) {
        SetVehicleToRespawn(v);
    }
}

/*
 * native SetAllCamMoveToPlayer(playerid);
 */
stock SetAllCamMoveToPlayer(playerid) {
    if (!IsPlayerConnected(playerid)) return false;
    new
        Float: x,
        Float: y,
        Float: z,

        Float: px,
        Float: py,
        Float: pz,

        Float: tx,
        Float: ty,
        Float: tz
    ;
    //TogglePlayerControllable(playerid, false);
    SetPlayerControllable(playerid, false);

    new vehicleid = GetPlayerVehicleID(playerid);
    if (!vehicleid) GetPlayerPos(playerid, tx, ty, tz);
    else GetVehiclePos(vehicleid, tx, ty, tz);

    for (new p = GetPlayerPoolSize(); p >= 0; --p) {
        //TogglePlayerControllable(p, false);
        SetPlayerControllable(p, false);

        //GetPlayerCameraPos(p, px, py, pz);
        GetPlayerPos(p, px, py, pz);

        GetPlayerCameraFrontVector(p, x, y, z);

        SetPlayerCameraPos(playerid, px+x * -3.0, py+y * -3.0, pz+z * -3.0);
        SetPlayerCameraLookAt(playerid, tx, ty, tz, CAMERA_MOVE);

        //TogglePlayerControllable(p, true);
    }
    //TogglePlayerControllable(playerid, true);
    return true;
}

/*
 * native GetMaxPlayersOfTeam(teamid);
 */
stock GetMaxPlayersOfTeam(teamid) {
    new num;
    for (new p = GetPlayerPoolSize(); p >= 0; --p) {
        if (IsPlayerConnected(p) && GetPlayerTeam(p) == teamid) num++;
    }
    return num;
}

/*
 * native PlayerText:CreatePlayerTextDrawEx(playerid, text[], Float:x, Float:y, Float:lsize_x, Float:lsize_y, Float:tsize_x, Float:tsize_y, aligment, proportional, shadow, outline, box, font, color, bgcolor, boxcolor, sprite_model, Float:sprite_rx, Float:sprite_ry, Float:sprite_rz, Float:sprite_zoom, sprite_color1, sprite_color2);
 */
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

/*
 * native Text:CreateTextDrawEx(text[], Float:x, Float:y, Float:lsize_x, Float:lsize_y, Float:tsize_x, Float:tsize_y, aligment, proportional, shadow, outline, box, font, color, bgcolor, boxcolor, sprite_model, Float:sprite_rx, Float:sprite_ry, Float:sprite_rz, Float:sprite_zoom, sprite_color1, sprite_color2);
 */
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

/*
 * native SetServerLanguage(text[]); // max len 30
 */
stock SetServerLanguage(text[]) {
	new msg[40];
	format(msg, sizeof(msg), "language %s", text);
	SendRconCommand(msg);
}

/*
 * native SetVehicleEngine(vehicleid, onengine);
 */
stock SetVehicleEngine(vehicleid, onengine) {
    new
        tmponengine, onlights, onalarm, ondoors, onbonnet, onboot, onobjective
    ;
    GetVehicleParamsEx(vehicleid, tmponengine, onlights, onalarm, ondoors, onbonnet, onboot, onobjective);
    SetVehicleParamsEx(vehicleid, onengine, onlights, onalarm, ondoors, onbonnet, onboot, onobjective);
}

/*
 * native GetVehicleEngine(vehicleid);
 */
stock GetVehicleEngine(vehicleid) {
    new
        onengine, onlights, onalarm, ondoors, onbonnet, onboot, onobjective
    ;
    GetVehicleParamsEx(vehicleid, onengine, onlights, onalarm, ondoors, onbonnet, onboot, onobjective);
    return onengine;
}

// Custom callbacks -------------------------------------------------------------------------------

forward SetPlayerControllable(playerid, bool:on);
public SetPlayerControllable(playerid, bool:on)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:TW_func.inc] SetPlayerControllable:\n\tplayerid %d on %b\n", playerid, on);
    #endif

    if (on) {
        SetPVarInt(playerid, "CONTROLLABLE", 0);
    } else {
        SetPVarInt(playerid, "CONTROLLABLE", 1);
    }
    TogglePlayerControllable(playerid, on);
    return true;
}

forward KickPlayer(playerid);
public KickPlayer(playerid)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:TW_func.inc] KickPlayer:\n\tplayerid %d\n", playerid);
    #endif

    Kick(playerid);
    return true;
}

forward ClearPlayerDamagerID(playerid);
public ClearPlayerDamagerID(playerid)
{
    #if DEBUG_PRINT
    printf("[CALLBACK:TW_func.inc] ClearPlayerDamagerID:\n\tplayerid %d\n\tdamagerid %d\n", playerid, GetPVarInt(playerid, "DAMAGERID"));
    #endif

    SetPVarInt(playerid, "DAMAGERID", INVALID_PLAYER_ID);
    return 1;
}
// EOF Custom callbacks -------------------------------------------------------------------------------