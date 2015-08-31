/*
 * Hud for gamemode Toy Of Wars
 * Revision : 1:17 20.08.2015
 * Author   : Logofero aka fERO
 */

// Textdraw info -------------------------------------------------------------------------------
new
    Text: tdraw_geninfo[2] = {Text:INVALID_TEXT_DRAW,...},
    Text: tdraw_mapinfo = Text:INVALID_TEXT_DRAW,
    Text: tdraw_teamlist[2] = {Text:INVALID_TEXT_DRAW,...},
    Text: tdraw_alert = Text:INVALID_TEXT_DRAW,
    Text: tdraw_win[2] = {Text:INVALID_TEXT_DRAW,...}
    //Text: tdraw_radarcap = Text:INVALID_TEXT_DRAW
;
new
    PlayerText: tdraw_carview[3] = {PlayerText:INVALID_TEXT_DRAW,...},
    PlayerText: tdraw_gunammo[2] = {PlayerText:INVALID_TEXT_DRAW,...},
    PlayerText: tdraw_carhp[2] = {PlayerText:INVALID_TEXT_DRAW,...}
;
// EOF Textdraw info -------------------------------------------------------------------------------

/*
native TW_CreateHudGenInfo();
native TW_CreateHudMapInfo();
native TW_CreateHudTeamList();
native TW_CreateHudAlert();
native TW_CreateHudWin();
native TW_CreateHudCarHP(playerid);
native TW_CreateHudGunAmmo(playerid);
native TW_CreateHudCarView(playerid);

native TW_DestroyHudGenInfo();
native TW_DestroyHudMapInfo();
native TW_DestroyHudTeamList();
native TW_DestroyHudAlert();
native TW_DestroyHudWin();
native TW_DestroyHudCarHP(playerid);
native TW_DestroyHudGunAmmo(playerid);
native TW_DestroyHudCarView(playerid);

native TW_ShowHudGenInfo();
native TW_ShowHudMapInfo();
native TW_ShowHudTeamList();
native TW_ShowHudAlert(playerid);
native TW_ShowHudWin(playerid);
native TW_ShowHudCarHP(playerid);
native TW_ShowHudGunAmmo(playerid);
native TW_ShowHudCarView(playerid);

native TW_HideHudGenInfo();
native TW_HideHudMapInfo();
native TW_HideHudTeamList();
native TW_HideHudAlert(playerid);
native TW_HideHudWin(playerid);
native TW_HideHudCarHP(playerid);
native TW_HideHudGunAmmo(playerid);
native TW_HideHudCarView(playerid);
*/

stock TW_CreateHudGenInfo() {
    // Bckground
    tdraw_geninfo[0] = CreateTextDrawEx(
        "_", 552.000000, 79.000000,
        0.480000, 1.799998,
        70.000000, 110.000000,
        2, 1, 0, 1, 1, 1,
        -1, 255, 255,
        0, 0.0,0.0,0.0,0.0, 0, 0
    );
    // Logo
    tdraw_geninfo[1] = CreateTextDrawEx(
    	SCR_NAME, //text
    	552.000000, 82.000000, //x, y
    	0.270000, 1.100000, //letterx, lettery
    	607.000000, 112.000000, //textsizex, textsizey
    	2, 1, 0, 1, 1, 1, //aligment, proportional, shadow, outline, box, font
    	0xFF0000FF, 0xFF000022, 0x00000000, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
}

stock TW_ShowAllHudGenInfo() {
    for (new i; i < sizeof(tdraw_geninfo); i++) {
        TextDrawShowForAll(tdraw_geninfo[i]);
    }
}

stock TW_ShowHudGenInfo(playerid) {
    for (new i; i < sizeof(tdraw_geninfo); i++) {
        TextDrawShowForPlayer(playerid, tdraw_geninfo[i]);
    }
}

stock TW_HideHudGenInfo(playerid) {
    for (new i; i < sizeof(tdraw_geninfo); i++) {
        TextDrawHideForPlayer(playerid, tdraw_geninfo[i]);
    }
}

stock TW_DestroyHudGenInfo() {
    for (new i; i < sizeof(tdraw_geninfo); i++) {
        TextDrawHideForAll(tdraw_geninfo[i]);
        TextDrawDestroy(tdraw_geninfo[i]);
    }
}

stock TW_CreateHudMapInfo() {
    tdraw_mapinfo = CreateTextDrawEx(
    	"Map desc", //text
    	552.000000, 98.000000, //x, y
    	0.209999, 0.799995, //letterx, lettery
    	20.000000, 110.000000, //textsizex, textsizey
    	2, 1, 0, 1, 1, 1, //aligment, proportional, shadow, outline, box, font
    	0xFF8000FF, 0x000000FF, 0x00000033, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
}

stock TW_ShowHudMapInfo(playerid, mapid) {
    new msg[256];

    if (strlen(TW_GetMapAuthor(mapid)) > 0) format(msg, sizeof(msg), "Map: %s~n~Round score: %d~n~Time: %02d:%02d~n~Weather: %d~n~Author: %s", TW_GetMapName(mapid), TW_GetMapScore(mapid), TW_GetMapTimeH(mapid), TW_GetMapTimeM(mapid), TW_GetMapWeather(mapid), TW_GetMapAuthor(mapid));
    else format(msg, sizeof(msg), "Map: %s~n~Round score: %d~n~Time: %02d:%02d~n~Weather: %d", TW_GetMapName(mapid), TW_GetMapScore(mapid), TW_GetMapTimeH(mapid), TW_GetMapTimeM(mapid), TW_GetMapWeather(mapid));

    TextDrawSetString(tdraw_mapinfo, msg);
    TextDrawShowForPlayer(playerid, tdraw_mapinfo);
}

stock TW_HideHudMapInfo(playerid) {
    //for (new i; i < sizeof(tdraw_teamlist); i++) {
        TextDrawHideForPlayer(playerid, tdraw_mapinfo);
    //}
}

stock TW_DestroyHudMapInfo() {
    //for (new i; i < sizeof(tdraw_mapinfo); i++) {
        TextDrawHideForAll(tdraw_mapinfo);
        TextDrawDestroy(tdraw_mapinfo);
    //}
}

stock TW_CreateHudTeamList() {
    // Head title
    tdraw_teamlist[0] = CreateTextDrawEx(
    	"Team Score:", //text
    	552.000000, 139.000000, //x, y
    	0.279998, 1.099995, //letterx, lettery
    	20.000000, 110.000000, //textsizex, textsizey
    	2, 1, 0, 1, 1, 1, //aligment, proportional, shadow, outline, box, font
    	0xFFAA00FF, 0xFFAA0011, 0x000000FF, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
    // Teams
    tdraw_teamlist[1] = CreateTextDrawEx(
    	"Teams", //text
    	552.000000, 152.000000, //x, y
    	0.259999, 0.999993, //letterx, lettery
    	20.000000, 110.000000, //textsizex, textsizey
    	2, 1, 0, 1, 1, 1, //aligment, proportional, shadow, outline, box, font
    	0xFF0000FF, 0x000000FF, 0x00000033, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
}

stock TW_ShowHudTeamList(playerid) {
    new msg[256];
    for (new i; i < 6; i++) {
        if (GetMaxPlayersOfTeam(i) > 0) {
            format(msg, sizeof(msg), "%s~%.1s~%s %d~n~", msg, TW_team_ncolors[i], TW_team_ncolors[i], TW_team_scores[i]);
        } else {
            TW_team_scores[i] = 0; // Reset team score if no players
        }
    }
    if (tdraw_teamlist[1] != Text:INVALID_TEXT_DRAW) {
        TextDrawSetString(tdraw_teamlist[1], msg);
    }
    for (new i; i < sizeof(tdraw_teamlist); i++) {
        TextDrawShowForPlayer(playerid, tdraw_teamlist[i]);
    }
}

stock TW_ShowAllHudTeamList() {
    new msg[256];
    for (new i; i < 6; i++) {
        if (GetMaxPlayersOfTeam(i) > 0) {
            format(msg, sizeof(msg), "%s~%.1s~%s %d~n~", msg, TW_team_ncolors[i], TW_team_ncolors[i], TW_team_scores[i]);
        } else {
            TW_team_scores[i] = 0; // Reset team score if no players
        }
    }
    if (tdraw_teamlist[1] != Text:INVALID_TEXT_DRAW) {
        TextDrawSetString(tdraw_teamlist[1], msg);
    }
    for (new i; i < sizeof(tdraw_teamlist); i++) {
        TextDrawShowForAll(tdraw_teamlist[i]);
    }
}

stock TW_HideHudTeamList(playerid) {
    new msg[256];
    for (new i; i < 6; i++) {
        if (GetMaxPlayersOfTeam(i) > 0) {
            format(msg, sizeof(msg), "%s~%.1s~%s %d~n~", msg, TW_team_ncolors[i], TW_team_ncolors[i], TW_team_scores[i]);
        } else {
            TW_team_scores[i] = 0; // Reset team score if no players
        }
    }
    if (tdraw_teamlist[1] != Text:INVALID_TEXT_DRAW) {
        TextDrawSetString(tdraw_teamlist[1], msg);
    }
    for (new i; i < sizeof(tdraw_teamlist); i++) {
        TextDrawHideForPlayer(playerid, tdraw_teamlist[i]);
    }
}

stock TW_DestroyHudTeamList() {
    for (new i; i < sizeof(tdraw_teamlist); i++) {
        TextDrawHideForAll(tdraw_teamlist[i]);
        TextDrawDestroy(tdraw_teamlist[i]);
    }
}

stock TW_CreateHudCarView(playerid) {
    new vehicleid = GetPlayerVehicleID(playerid);
    //if (!IsVehicleRC(vehicleid)) return false;
    new name[24];
    // Background
    tdraw_carview[0] = CreatePlayerTextDrawEx(
        playerid, "_", 520.000000, 25.000000,
        0.400000, 5.499997,
        58.000000, 46.000000,
        2, 1, 0, 0, 1, 0,
        -1, 255, 255,
        0, 0.0, 0.0, 0.0, 0.0, 0, 0
    );
    switch (GetVehicleModel(vehicleid)) {
        case 564 : {
            // RCTiger icon
            tdraw_carview[1] = CreatePlayerTextDrawEx(
                playerid, "RCTiger", 491.000000, 12.000000,
                1.000000, 1.000000,
                68.000000, 60.000000,
                2, 1, 0, 0, 1, 5,
                -1, 0, 0,
                564, 329.0, 0.0, 346.0, 0.699999, 0, 0
            );
            name = "RC Tiger";
        } case 441 : {
            // RCBandit icon
            tdraw_carview[1] = CreatePlayerTextDrawEx(
                playerid, "RCBandit", 485.000000, 12.000000,
                1.000000, 1.000000,
                75.000000, 65.000000,
                2, 1, 0, 0, 1, 5,
                -1, 0, 0,
                441, 331.0,0.0,341.0,0.399999, 3, 0
            );
            name = "RC Bandit";
        } case 465 : {
            // RCRider icon
            tdraw_carview[1] = CreatePlayerTextDrawEx(
                playerid, "RCRider", 484.000000, 13.000000,
                1.000000, 1.000000,
                75.000000, 65.000000,
                2, 1, 0, 0, 1, 5,
                -1, 0, 0,
                465, 330.0,0.0,326.0,0.599999, 0, 0
            );
            name = "RC Rider";
        } case 501 : {
            // RCGoblin icon
            tdraw_carview[1] = CreatePlayerTextDrawEx(
                playerid, "RCGoblin", 484.000000, 13.000000,
                1.000000, 1.000000,
                75.000000, 65.000000,
                2, 1, 0, 0, 1, 5,
                -1, 0, 0,
                501, 330.0,0.0,326.0,0.599999, 0, 0
            );
            name = "RC Goblin";
        } case 464 : {
            // RCBaron icon
            tdraw_carview[1] = CreatePlayerTextDrawEx(
                playerid, "RCBaron", 484.000000, 13.000000,
                1.000000, 1.000000,
                75.000000, 65.000000,
                2, 1, 0, 0, 1, 5,
                -1, 0, 0,
                464, 340.0,0.0,330.0, 0.599999, 0, 0
            );
            name = "RC Baron";
        } default : {
            // Unknown icon
            tdraw_carview[1] = CreatePlayerTextDrawEx(
                playerid, "RCBaron", 484.000000, 13.000000,
                1.000000, 1.000000,
                75.000000, 65.000000,
                2, 1, 0, 0, 1, 5,
                -1, 0, 0,
                -1, 340.0,0.0,330.0, 0.699999, 0, 0
            );
            name = "Unknown";
        }
    }
    // RC Name
    tdraw_carview[2] = CreatePlayerTextDrawEx(
        playerid, name,
        520.000000, 67.000000,
        0.219998, 0.699998,
        20.000000, 42.000000,
        2, 1, 0, 1, 1, 1,
        0xFFFFFFFF, 0x000000FF, 0xCC6600FF,
        0, 0.0, 0.0, 0.0, 0.0, 0, 0
    );
}

stock TW_ShowHudCarView(playerid) {
    new vehicleid = GetPlayerVehicleID(playerid);
    if (!IsVehicleRC(vehicleid)) return false;

    for (new i; i < sizeof(tdraw_carview); i++) {
        if (tdraw_carview[i] != PlayerText:INVALID_TEXT_DRAW) {
            PlayerTextDrawShow(playerid, tdraw_carview[i]);
        }
    }
    return true;
}

stock TW_HideHudCarView(playerid) {
    //new vehicleid = GetPlayerVehicleID(playerid);
    for (new i; i < sizeof(tdraw_carview); i++) {
        if (tdraw_carview[i] != PlayerText:INVALID_TEXT_DRAW) {
            PlayerTextDrawHide(playerid, tdraw_carview[i]);
        }
    }
    return true;
}

stock TW_DestroyHudCarView(playerid) {
    //new vehicleid = GetPlayerVehicleID(playerid);
    for (new i; i < sizeof(tdraw_carview); i++) {
        if (tdraw_carview[i] != PlayerText:INVALID_TEXT_DRAW) {
            PlayerTextDrawHide(playerid, tdraw_carview[i]);
            PlayerTextDrawDestroy(playerid, tdraw_carview[i]);
        }
    }
    return true;
}

stock TW_CreateHudCarHP(playerid) {
    // HP icon
    tdraw_carhp[0] = CreatePlayerTextDrawEx(
    	playerid, "HP_ICON", //text
    	35.000000, 287.000000, //x, y
    	0.140000, 8.099995, //letterx, lettery
    	38.000000, 38.000000, //textsizex, textsizey
    	2, 1, 1, 0, 0, 5, //aligment, proportional, shadow, outline, box, font
    	0xFFFFFFFF, 0x00000000, 0x00000000, //color, bgcolor, boxcolor
    	3096, 350.0000, 10.0000, 340.0000, 1.299999, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
    // HP amount
    tdraw_carhp[1] = CreatePlayerTextDrawEx(
    	playerid, "1000 HP", //text
    	76.000000, 302.000000, //x, y
    	0.289999, 0.999997, //letterx, lettery
    	142.000000, 38.000000, //textsizex, textsizey
    	1, 1, 0, 0, 1, 1, //aligment, proportional, shadow, outline, box, font
    	0x00FF0066, 0x00000000, 0x00000044, //color, bgcolor, boxcolor
    	2358, 344.0000, 0.0000, 150.0000, 0.900002, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
}

stock TW_ShowHudCarHP(playerid) {
    new vehicleid = GetPlayerVehicleID(playerid);
    if (!IsVehicleRC(vehicleid)) return false;

    for (new i; i < sizeof(tdraw_carhp); i++) {
        //if (tdraw_carhp[i] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawShow(playerid, tdraw_carhp[i]);
        //}
    }
    return true;
}

stock TW_HideHudCarHP(playerid) {
    //new vehicleid = GetPlayerVehicleID(playerid);
    for (new i; i < sizeof(tdraw_carhp); i++) {
        //if (tdraw_carhp[i] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawHide(playerid, tdraw_carhp[i]);
        //}
    }
    return true;
}

stock TW_DestroyHudCarHP(playerid) {
    //new vehicleid = GetPlayerVehicleID(playerid);
    for (new i; i < sizeof(tdraw_carhp); i++) {
        if (tdraw_carhp[i] != PlayerText:INVALID_TEXT_DRAW) {
            PlayerTextDrawHide(playerid, tdraw_carhp[i]);
            PlayerTextDrawDestroy(playerid, tdraw_carhp[i]);
        }
    }
    return true;
}

stock TW_CreateHudGunAmmo(playerid) {
    // Ammo icon
    tdraw_gunammo[0] = CreatePlayerTextDrawEx(
    	playerid, "AMMO_ICON", //text
    	34.000000, 303.000000, //x, y
    	0.140000, 8.099995, //letterx, lettery
    	38.000000, 38.000000, //textsizex, textsizey
    	2, 1, 1, 0, 0, 5, //aligment, proportional, shadow, outline, box, font
    	0xFFFFFFFF, 0x00000000, 0x00000000, //color, bgcolor, boxcolor
    	2358, 350.0000, 0.0000, 150.0000, 1.000002, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
    // Ammo amount
    tdraw_gunammo[1] = CreatePlayerTextDrawEx(
    	playerid, "100 / 100", //text
    	76.000000, 316.000000, //x, y
    	0.289999, 0.999997, //letterx, lettery
    	142.000000, 38.000000, //textsizex, textsizey
    	1, 1, 0, 0, 1, 1, //aligment, proportional, shadow, outline, box, font
    	0xAAAAAA66, 0x00000000, 0x00000044, //color, bgcolor, boxcolor
    	2358, 344.0000, 0.0000, 150.0000, 0.900002, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
}

stock TW_ShowHudGunAmmo(playerid) {
    new vehicleid = GetPlayerVehicleID(playerid);
    if (!IsVehicleRC(vehicleid)) return false;

    for (new i; i < sizeof(tdraw_gunammo); i++) {
        //if (tdraw_gunammo[i] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawShow(playerid, tdraw_gunammo[i]);
        //}
    }
    return true;
}

stock TW_HideHudGunAmmo(playerid) {
    //new vehicleid = GetPlayerVehicleID(playerid);
    for (new i; i < sizeof(tdraw_gunammo); i++) {
        //if (tdraw_gunammo[i] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawHide(playerid, tdraw_gunammo[i]);
        //}
    }
    return true;
}

stock TW_DestroyHudGunAmmo(playerid) {
    //new vehicleid = GetPlayerVehicleID(playerid);
    for (new i; i < sizeof(tdraw_gunammo); i++) {
        if (tdraw_gunammo[i] != PlayerText:INVALID_TEXT_DRAW) {
            PlayerTextDrawHide(playerid, tdraw_gunammo[i]);
            PlayerTextDrawDestroy(playerid, tdraw_gunammo[i]);
        }
    }
    return true;
}

stock TW_CreateHudAlert() {
    tdraw_alert = CreateTextDrawEx(
	"You are outside of battlefield. Go back!", //text
    	320.000000, 340.000000, //x, y
    	0.250000, 1.000000, //letterx, lettery
    	50.000000, 310.000000, //textsizex, textsizey
    	2, 1, 0, 1, 1, 1, //aligment, proportional, shadow, outline, box, font
    	0xFF0000FF, 0x000000FF, 0x00000044, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
}

stock TW_ShowHudAlert(playerid) {
    //for (new i; i < sizeof(tdraw_alert); i++) {
        TextDrawShowForPlayer(playerid, tdraw_alert);
    //}
}

stock TW_HideHudAlert(playerid) {
    //for (new i; i < sizeof(tdraw_alert); i++) {
        TextDrawHideForPlayer(playerid, tdraw_alert);
    //}
}

stock TW_DestroyHudAlert() {
    //for (new i; i < sizeof(tdraw_alert); i++) {
        TextDrawHideForAll(tdraw_alert);
        TextDrawDestroy(tdraw_alert);
    //}
}

stock TW_CreateHudWin() {
    // Head title
    tdraw_win[0] = CreateTextDrawEx(
    	"Winner", //text
    	320.000000, 192.000000, //x, y
    	0.379999, 1.399999, //letterx, lettery
    	20.000000, 164.000000, //textsizex, textsizey
    	2, 1, 0, 1, 1, 1, //aligment, proportional, shadow, outline, box, font
    	0xFFFF8099, 0x000000FF, 0x00000044, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
    // Players
    tdraw_win[1] = CreateTextDrawEx(
    	"Players", //text
    	320.000000, 210.000000, //x, y
    	0.219999, 0.799998, //letterx, lettery
    	20.000000, 164.000000, //textsizex, textsizey
    	2, 1, 0, 1, 1, 1, //aligment, proportional, shadow, outline, box, font
    	0xFFFFFFFF, 0x000000FF, 0x00000044, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
}

stock TW_ShowHudWin(playerid) {
    for (new i; i < sizeof(tdraw_win); i++) {
        TextDrawShowForPlayer(playerid, tdraw_win[i]);
    }
}

stock TW_ShowAllHudWin(winnerid) {
    new
        teamid = GetPlayerTeam(winnerid),
        name[MAX_PLAYER_NAME],
        title[64],
        info[256]
    ;
    if (teamid == 255) return false;
    for (new p = GetPlayerPoolSize(); p >= 0; --p) {
        if (GetPlayerTeam(p) == teamid) {
        GetPlayerName(p, name, sizeof(name));
        format(info, sizeof(info), "%s~%.1s~%s(%d) Score: %d~n~", info, TW_team_ncolors[teamid], name, p, GetPlayerScore(p));
        }
    }
    format(title, sizeof(title), "Win Team '%s'", TW_team_ncolors[teamid]);
    TextDrawSetString(tdraw_win[0], title);
    TextDrawSetString(tdraw_win[1], info);

    // Win
    for (new i; i < sizeof(tdraw_win); i++) {
        TextDrawShowForAll(tdraw_win[i]);
    }
    return true;
}

stock TW_HideHudWin(playerid) {
    for (new i; i < sizeof(tdraw_win); i++) {
        TextDrawHideForPlayer(playerid, tdraw_win[i]);
    }
}

stock TW_HideAllHudWin() {
    for (new i; i < sizeof(tdraw_win); i++) {
        TextDrawHideForAll(tdraw_win[i]);
    }
    return true;
}

stock TW_DestroyHudWin() {
    for (new i; i < sizeof(tdraw_win); i++) {
        TextDrawHideForAll(tdraw_win[i]);
        TextDrawDestroy(tdraw_win[i]);
    }
}

/* Unused
stock TW_CreateHudRadarCap() {
    // Radar cap
    tdraw_radarcap = CreateTextDrawEx(
        "_", 88.000000, 338.000000, //text, x, y
    	0.300000, 11.600008, //letterx, lettery
    	270.000000, 107.000000, //textsizex, textsizey
    	2, 1, 1, 0, 0, 1, //aligment, proportional, shadow, outline, box, font
    	0xFFFFFFFF, 0x000000FF, 0x000000BB, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
}
*/