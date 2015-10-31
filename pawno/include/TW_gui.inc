/*
 * GUI for gamemode Toy Of Wars
 * Update   : 9:37 31.10.2015
 * Author   : Logofero aka fERO
 * Credits  :
 *      SA-MP Multyplayer http://forum.sa-mp.com/forumdisplay.php?f=74
 *          SA-MP Team
 *
 *      Zamaroht's TextDraw Editor
 *          Zamaroht
 */

// Textdraw info -------------------------------------------------------------------------------
new
    Text: tdraw_geninfo[2] = {Text:INVALID_TEXT_DRAW,...},
    Text: tdraw_mapinfo = Text:INVALID_TEXT_DRAW,
    Text: tdraw_teamlist[2] = {Text:INVALID_TEXT_DRAW,...},
    Text: tdraw_alert = Text:INVALID_TEXT_DRAW,
    Text: tdraw_win[14] = {Text:INVALID_TEXT_DRAW,...}, // 2
    PlayerText: tdraw_carview[3] = {PlayerText:INVALID_TEXT_DRAW,...},
    PlayerText: tdraw_gunammo[2] = {PlayerText:INVALID_TEXT_DRAW,...},
    PlayerText: tdraw_carhp[2] = {PlayerText:INVALID_TEXT_DRAW,...},
    Text: tdraw_cross[2]
;
// EOF Textdraw info -------------------------------------------------------------------------------

// Natives
/*
// Create GUI
native TW_CreateHudGenInfo();
native TW_CreateHudMapInfo();
native TW_CreateHudTeamList();
native TW_CreateHudAlert();
native TW_CreateHudWin();
native TW_CreateHudCarHP(playerid);
native TW_CreateHudGunAmmo(playerid);
native TW_CreateHudCarView(playerid);
// Destroy GUI
native TW_DestroyHudGenInfo();
native TW_DestroyHudMapInfo();
native TW_DestroyHudTeamList();
native TW_DestroyHudAlert();
native TW_DestroyHudWin();
native TW_DestroyHudCarHP(playerid);
native TW_DestroyHudGunAmmo(playerid);
native TW_DestroyHudCarView(playerid);
// Show GUI
native TW_ShowHudGenInfo(playerid = -1);
native TW_ShowHudMapInfo(playerid = -1);
native TW_ShowHudTeamList(playerid = -1);
native TW_ShowHudAlert(playerid = -1);
native TW_ShowHudWin(playerid = -1);
native TW_ShowHudCarHP(playerid);
native TW_ShowHudGunAmmo(playerid);
native TW_ShowHudCarView(playerid);
// Hide GUI
native TW_HideHudGenInfo(playerid = -1);
native TW_HideHudMapInfo(playerid = -1);
native TW_HideHudTeamList(playerid = -1);
native TW_HideHudAlert(playerid = -1);
native TW_HideHudWin(playerid = -1);
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

stock TW_ShowHudGenInfo(playerid = -1) {
    if (playerid != -1) {
        for (new i; i < sizeof(tdraw_geninfo); i++) {
            TextDrawShowForPlayer(playerid, tdraw_geninfo[i]);
        }
    } else {
        for (new i; i < sizeof(tdraw_geninfo); i++) {
            TextDrawShowForAll(tdraw_geninfo[i]);
        }
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

stock TW_ShowHudMapInfo(playerid = -1) {
    new msg[256];
    if (strlen(TW_GetMapAuthor()) > 0) format(msg, sizeof(msg), "~y~Map: ~w~%s~n~~y~Round score: ~w~%d~n~~y~Time: ~w~%02d:%02d~n~~y~Weather: ~w~%s (%d)~n~~y~Author: ~w~%s", TW_GetMapName(), TW_GetMapScore(), TW_GetMapTimeH(), TW_GetMapTimeM(), GetWeatherName(TW_GetMapWeather()), TW_GetMapWeather(), TW_GetMapAuthor());
    else format(msg, sizeof(msg), "Map: ~w~%s~n~Round score: ~w~%d~n~Time: ~w~%02d:%02d~n~Weather: ~w~%s (%d)", TW_GetMapName(), TW_GetMapScore(), TW_GetMapTimeH(), TW_GetMapTimeM(), GetWeatherName(TW_GetMapWeather()), TW_GetMapWeather());
    TextDrawSetString(tdraw_mapinfo, msg);
    if (playerid != -1) {
        TextDrawShowForPlayer(playerid, tdraw_mapinfo);
    } else {
        TextDrawShowForAll(tdraw_mapinfo);
    }
}

stock TW_HideHudMapInfo(playerid = -1) {
    if (playerid != -1) {
        TextDrawHideForPlayer(playerid, tdraw_mapinfo);
    } else {
        TextDrawHideForAll(tdraw_mapinfo);  
    }
}

stock TW_DestroyHudMapInfo() {
    TextDrawHideForAll(tdraw_mapinfo);
    TextDrawDestroy(tdraw_mapinfo);
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
    	0xFFFFFFFF, 0x000000FF, 0x00000033, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
}

stock TW_ShowHudTeamList(playerid = -1) {
    new msg[256];
    for (new i; i < TW_GetMapTeams(); i++) {
        if (GetMaxPlayersOfTeam(i) > 0) {
            format(msg, sizeof(msg), "%s%s: %d~n~", msg, TW_GetTeamName(i), TW_GetTeamScore(i));
        } else {
            // Reset team score if no players
            TW_GetTeamRang(i) = 0;
            TW_GetTeamKilled(i) = 0;
            TW_GetTeamDied(i) = 0;
            TW_GetTeamScore(i) = 0;
            TW_GetTeamBonus(i) = 0;
            TW_GetTeamWins(i) = 0;
        }
    }
    if (tdraw_teamlist[1] != Text:INVALID_TEXT_DRAW) {
        TextDrawSetString(tdraw_teamlist[1], msg);
    }
    
    if (playerid != -1) {
        for (new i; i < sizeof(tdraw_teamlist); i++) {
            TextDrawShowForPlayer(playerid, tdraw_teamlist[i]);
        }
    } else {
        for (new i; i < sizeof(tdraw_teamlist); i++) {
            TextDrawShowForAll(tdraw_teamlist[i]);
        }
    }
}

stock TW_HideHudTeamList(playerid = -1) {
    new msg[256];
    for (new i; i < TW_GetMapTeams(); i++) {
        if (GetMaxPlayersOfTeam(i) > 0) {
            format(msg, sizeof(msg), "%s%s: %d~n~", msg, TW_GetTeamName(i), TW_GetTeamScore(i));
        } else {
            // Reset team score if no players
            TW_GetTeamRang(i) = 0;
            TW_GetTeamKilled(i) = 0;
            TW_GetTeamDied(i) = 0;
            TW_GetTeamScore(i) = 0;
            TW_GetTeamBonus(i) = 0;
            TW_GetTeamWins(i) = 0;
        }
    }
    if (tdraw_teamlist[1] != Text:INVALID_TEXT_DRAW) {
        TextDrawSetString(tdraw_teamlist[1], msg);
    }
    
    if (playerid != -1) {
        for (new i; i < sizeof(tdraw_teamlist); i++) {
            TextDrawHideForPlayer(playerid, tdraw_teamlist[i]);
        }
    } else {
        for (new i; i < sizeof(tdraw_teamlist); i++) {
            TextDrawHideForAll(tdraw_teamlist[i]);
        }
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

stock TW_ShowHudAlert(playerid = -1) {
    if (playerid != -1) {
        TextDrawShowForPlayer(playerid, tdraw_alert);
    } else {
        TextDrawShowForAll(tdraw_alert);
    }
}

stock TW_HideHudAlert(playerid = -1) {
    if (playerid != -1) {
        TextDrawHideForPlayer(playerid, tdraw_alert);
    } else {
        TextDrawHideForAll(tdraw_alert);
    }
}

stock TW_DestroyHudAlert() {
    TextDrawHideForAll(tdraw_alert);
    TextDrawDestroy(tdraw_alert);
}

stock TW_CreateHudWin() {
    // Head title
    tdraw_win[0] = CreateTextDrawEx(
    	"_", //text
    	320.000000, 167.000000, //x, y
    	0.409997, 9.299998, //letterx, lettery
    	160.000000, 344.000000, //textsizex, textsizey
    	2, 1, 0, 1, 0, 2, //aligment, proportional, shadow, outline, box, font
    	0xFF0000FF, 0x000000FF, 0x00000044, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
    tdraw_win[1] = CreateTextDrawEx(
    	"]]] TEAM GREEN WINNER! ]]]", //text
    	320.000000, 170.000000, //x, y
    	0.369998, 1.399999, //letterx, lettery
    	40.000000, 342.000000, //textsizex, textsizey
    	2, 1, 0, 1, 1, 2, //aligment, proportional, shadow, outline, box, font
    	0xFF0000FF, 0x000000FF, 0x00000044, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
    tdraw_win[2] = CreateTextDrawEx(
    	"TEAM", //text
    	204.000000, 188.000000, //x, y
    	0.250000, 0.899999, //letterx, lettery
    	14.000000, 110.000000, //textsizex, textsizey
    	2, 1, 0, 0, 1, 1, //aligment, proportional, shadow, outline, box, font
    	0xFF8000FF, 0x000000FF, 0x00000044, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
    tdraw_win[3] = CreateTextDrawEx(
    	"RANG", //text
    	291.000000, 188.000000, //x, y
    	0.250000, 0.899999, //letterx, lettery
    	14.000000, 55.000000, //textsizex, textsizey
    	2, 1, 0, 0, 1, 1, //aligment, proportional, shadow, outline, box, font
    	0xFF8000FF, 0x000000FF, 0x00000044, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
    tdraw_win[4] = CreateTextDrawEx(
    	"KILL/DIED", //text
    	349.000000, 188.000000, //x, y
    	0.250000, 0.899999, //letterx, lettery
    	14.000000, 51.000000, //textsizex, textsizey
    	2, 1, 0, 0, 1, 1, //aligment, proportional, shadow, outline, box, font
    	0xFF8000FF, 0x000000FF, 0x00000044, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
    tdraw_win[5] = CreateTextDrawEx(
    	"SCORE", //text
    	396.000000, 188.000000, //x, y
    	0.250000, 0.899999, //letterx, lettery
    	14.000000, 34.000000, //textsizex, textsizey
    	2, 1, 0, 0, 1, 1, //aligment, proportional, shadow, outline, box, font
    	0xFF8000FF, 0x000000FF, 0x00000044, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
    tdraw_win[6] = CreateTextDrawEx(
    	"BONUS", //text
    	435.000000, 188.000000, //x, y
    	0.250000, 0.899999, //letterx, lettery
    	14.000000, 34.000000, //textsizex, textsizey
    	2, 1, 0, 0, 1, 1, //aligment, proportional, shadow, outline, box, font
    	0xFF8000FF, 0x000000FF, 0x00000044, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
    tdraw_win[7] = CreateTextDrawEx(
    	"WINS", //text
    	474.000000, 188.000000, //x, y
    	0.250000, 0.899999, //letterx, lettery
    	14.000000, 34.000000, //textsizex, textsizey
    	2, 1, 0, 0, 1, 1, //aligment, proportional, shadow, outline, box, font
    	0xFF8000FF, 0x000000FF, 0x00000044, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    ); 
    tdraw_win[8] = CreateTextDrawEx(
    	"Player(0)~n~Player(1)~n~Player(2)~n~Player(3)~n~Player(4)~n~Player(5)~n~", //text
    	204.000000, 200.000000, //x, y
    	0.250000, 0.899999, //letterx, lettery
    	14.000000, 110.000000, //textsizex, textsizey
    	2, 1, 0, 0, 1, 1, //aligment, proportional, shadow, outline, box, font
    	0xFFFFFFFF, 0x000000FF, 0x00000044, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
    tdraw_win[9] = CreateTextDrawEx(
    	"]~n~]]~n~]]]~n~]]]]~n~]]]]]~n~]]]]]]~n~", //text
    	291.000000, 200.000000, //x, y
    	0.250000, 0.899999, //letterx, lettery
    	14.000000, 55.000000, //textsizex, textsizey
    	2, 1, 0, 0, 1, 2, //aligment, proportional, shadow, outline, box, font
    	0xFFFFFFFF, 0x000000FF, 0x00000044, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
    tdraw_win[10] = CreateTextDrawEx(
    	"0~n~12~n~222~n~1000~n~10900~n~4656~n~", //text
    	349.000000, 200.000000, //x, y
    	0.250000, 0.899999, //letterx, lettery
    	14.000000, 51.000000, //textsizex, textsizey
    	2, 1, 0, 0, 1, 1, //aligment, proportional, shadow, outline, box, font
    	0xFFFFFFFF, 0x000000FF, 0x00000044, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
    tdraw_win[11] = CreateTextDrawEx(
    	"100~n~1000~n~10000~n~100000~n~1000000~n~10000000~n~", //text
    	396.000000, 200.000000, //x, y
    	0.250000, 0.899999, //letterx, lettery
    	14.000000, 34.000000, //textsizex, textsizey
    	2, 1, 0, 0, 1, 1, //aligment, proportional, shadow, outline, box, font
    	0xFFFFFFFF, 0x000000FF, 0x00000044, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
    tdraw_win[12] = CreateTextDrawEx(
    	"0~n~100~n~2000~n~34444~n~6777~n~10000000~n~", //text
    	435.000000, 200.000000, //x, y
    	0.250000, 0.899999, //letterx, lettery
    	14.000000, 34.000000, //textsizex, textsizey
    	2, 1, 0, 0, 1, 1, //aligment, proportional, shadow, outline, box, font
    	0xFFFFFFFF, 0x000000FF, 0x00000044, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
    tdraw_win[13] = CreateTextDrawEx(
    	"100000~n~10000~n~2222~n~3333~n~0~n~10000000~n~", //text
    	474.000000, 200.000000, //x, y
    	0.250000, 0.899999, //letterx, lettery
    	14.000000, 34.000000, //textsizex, textsizey
    	2, 1, 0, 0, 1, 1, //aligment, proportional, shadow, outline, box, font
    	0xFFFFFFFF, 0x000000FF, 0x00000044, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
}

stock GetRangOfStars(rang) {
    new string[16];
    switch (rang) {
        case 1..2 : string = "]";
        case 3..4 : string = "]]";   
        case 5..6 : string = "]]]";   
        case 7..8 : string = "]]]]";   
        case 9..10 : string = "]]]]]";  
        case 11..12 : string = "]]]]]]";   
        case 13..14 : string = "]]]]]]]";  
        case 15..16 : string = "]]]]]]]]";  
        default  : string = "-";       
    }
    return string;
}

stock TW_ShowHudWin(playerid = -1) {
    new
        teamid = GetPlayerTeam(TW_GetMapTeamWinner()),
        //name[MAX_PLAYER_NAME],
        title[64],
        name_info[256],
        rang_info[256],
        kill_info[256],
        score_info[256],
        bonus_info[256],
        wins_info[256]
    ;
    if (teamid == 255) return false;
    //8 - [team]name, 9 - rang, 10 - killed/died, 11 - score, 12 - bonus, 13 - wins
    
    format(title, sizeof(title), "]]] TEAM %s WINS! ]]]", TW_GetTeamName(teamid));
    TextDrawSetString(tdraw_win[1], title);
    
    for (new i; i < TW_GetMapTeams(); i++) {
        if (teamid == i) format(name_info, sizeof(name_info), "%s~r~%s~w~~n~", name_info, TW_GetTeamName(i));
        else format(name_info, sizeof(name_info), "%s%s~n~", name_info, TW_GetTeamName(i));
        TextDrawSetString(tdraw_win[8], name_info);
        
        if (teamid == i) format(rang_info, sizeof(rang_info), "%s~r~%s~w~~n~", rang_info, GetRangOfStars(TW_GetTeamWins(i)));
        else format(rang_info, sizeof(rang_info), "%s%s~n~", rang_info, GetRangOfStars(TW_GetTeamWins(i)));
        TextDrawSetString(tdraw_win[9], rang_info);
        
        if (teamid == i) format(kill_info, sizeof(kill_info), "%s~r~%d/%d~w~~n~", kill_info, TW_GetTeamKilled(i), TW_GetTeamDied(i));
        else format(kill_info, sizeof(kill_info), "%s%d/%d~n~", kill_info, TW_GetTeamKilled(i), TW_GetTeamDied(i));
        TextDrawSetString(tdraw_win[10], kill_info);
        
        if (teamid == i) format(score_info, sizeof(score_info), "%s~r~%d~w~~n~", score_info, TW_GetTeamScore(i));
        else format(score_info, sizeof(score_info), "%s%d~n~", score_info, TW_GetTeamScore(i));
        TextDrawSetString(tdraw_win[11], score_info);
        
        if (teamid == i) format(bonus_info, sizeof(bonus_info), "%s~r~%d~w~~n~", bonus_info, TW_GetTeamBonus(i));
        else format(bonus_info, sizeof(bonus_info), "%s%d~n~", bonus_info, TW_GetTeamBonus(i));
        TextDrawSetString(tdraw_win[12], bonus_info);
        
        if (teamid == i) format(wins_info, sizeof(wins_info), "%s~r~%d~w~~n~", wins_info, TW_GetTeamWins(i));
        else format(wins_info, sizeof(wins_info), "%s%d~n~", wins_info, TW_GetTeamWins(i));
        TextDrawSetString(tdraw_win[13], wins_info);
    }   
    if (playerid != -1) {
        for (new i; i < sizeof(tdraw_win); i++) {
            TextDrawShowForPlayer(playerid, tdraw_win[i]);
        }
    } else {
        for (new i; i < sizeof(tdraw_win); i++) {
            TextDrawShowForAll(tdraw_win[i]);
        } 
    }
    return true;
}

stock TW_HideHudWin(playerid = -1) {
    if (playerid != -1) {
        for (new i; i < sizeof(tdraw_win); i++) {
            TextDrawHideForPlayer(playerid, tdraw_win[i]);
        }
    } else {
        for (new i; i < sizeof(tdraw_win); i++) {
            TextDrawHideForAll(tdraw_win[i]);
        }
    }
    return true;
}

stock TW_DestroyHudWin() {
    for (new i; i < sizeof(tdraw_win); i++) {
        TextDrawHideForAll(tdraw_win[i]);
        TextDrawDestroy(tdraw_win[i]);
    }
}

stock TW_CreateHudCrosshair() {
    tdraw_cross[0] = CreateTextDrawEx(
    	"particle:lockon", //text
    	288.000000, 195.000000, //x, y
    	0.500000, 1.000000, //letterx, lettery
    	64.000000, 58.000000, //textsizex, textsizey
    	2, 1, 1, 0, 1, 4, //aligment, proportional, shadow, outline, box, font
    	0x00FF0044, 0x000000FF, 0x000000FF, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
    tdraw_cross[1] = CreateTextDrawEx(
    	"particle:lockonFire", //text
    	288.000000, 195.000000, //x, y
    	0.500000, 1.000000, //letterx, lettery
    	64.000000, 58.000000, //textsizex, textsizey
    	2, 1, 1, 0, 1, 4, //aligment, proportional, shadow, outline, box, font
    	0x00FF0044, 0x000000FF, 0x000000FF, //color, bgcolor, boxcolor
    	-1, 0.0000, 0.0000, 0.0000, 1.000000, 0, 0 //sprite_model, sprite_rx, sprite_ry, sprite_rz, sprite_zoom, sprite_color1, sprite_color2
    );
}

stock TW_ShowHudCrosshair(playerid = -1) {   
    if (playerid != -1) {
        for (new i; i < sizeof(tdraw_cross); i++) {
            TextDrawShowForPlayer(playerid, tdraw_cross[i]);
        }
    } else {
        for (new i; i < sizeof(tdraw_cross); i++) {
            TextDrawShowForAll(tdraw_cross[i]);
        }
    }
}

stock TW_HideHudCrosshair(playerid = -1) {   
    if (playerid != -1) {
        for (new i; i < sizeof(tdraw_cross); i++) {
            TextDrawHideForPlayer(playerid, tdraw_cross[i]);
        }
    } else {
        for (new i; i < sizeof(tdraw_cross); i++) {
            TextDrawHideForAll(tdraw_cross[i]);
        }
    }
}

stock TW_DestroyHudCrosshair() {
    for (new i; i < sizeof(tdraw_cross); i++) {
        TextDrawHideForAll(tdraw_cross[i]);
        TextDrawDestroy(tdraw_cross[i]);
    }
}