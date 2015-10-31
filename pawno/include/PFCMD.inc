/*
 * [include] PFCMD (PRE FORMATTED CMD)
 * Compatibility : gamemode, filterscript
 * Release       : v1.0, 1 sep 2015
 * Author        : Logofero aka fERO
 * Credits       : SA-MP team
 *
 * Description:
 *      What is it? This Easy, Fast, User friendly Command Maker.
 *
 * NOTE:
 *      (!) It Wraper on OnPlayerCommandText: No pafos, no memory hacks, no 'super-puper' execution speed, no other useless inclusions.
 *      [+] All functionality in one include CMD.inc: You do not need third-party plugins/includes.
 *      [+] CMD stored arguments in array: You do not need sscanf or other functions. You do not have to format string before using it.
 *      [+] Not disables original OnPlayerCommandText: It works with all features.
 *
 * INSTALL:
 *      1. Copy file CMD.inc in path 'Server\pawno\include\'
 *      2. Add line #include <PFCMD> after #include <a_samp> to top in gamemode/filterscript:
 *
 *          #include <PFCMD>
 *
 *      3. Making new command. Add lines:
 *          // --------------------------------------------------------------------------------
 *          // (A) All commands checked against in one callback (Recommended):
 *          // --------------------------------------------------------------------------------
 *          CMD:Commands(playerid, params[]) {
 *              // CMD: /give [playerid] [money]
 *              if (CMD_IsExec(playerid, "give")) { // Argumet 0 string 'give'
 *                  if (!IsPlayerConnected(CMD_ArgInt(playerid, 1))) { // Argumet 1 integer 'id'
 *                      SendClientMessange(playerid, -1, "CMD: Invalid Player ID");
 *                      return 0;
 *                  }
 *                  GivePlayerMoney(playerid, CMD_ArgInt(playerid, 1), CMD_ArgInt(playerid, 2)); // Argumet 2 integer 'money'
 *                  SendClientMessange(playerid, -1, "You gave yourself a cash reward.");
 *                  return 1;
 *              }
 *              // <- New command
 *              return 0;
 *          }
 *          // --------------------------------------------------------------------------------
 *          // (B) Command is a separate function (sensitive to upper and lower case):
 *          // --------------------------------------------------------------------------------
 *          CMD:give(playerid, params[]) { // give is name command
 *              if (!IsPlayerConnected(CMD_ArgInt(playerid, 1))) { // Argumet 1 return integer 'id'
 *                  SendClientMessange(playerid, -1, "CMD: Invalid Player ID");
 *                  return 0;
 *              }
 *              GivePlayerMoney(playerid, CMD_ArgInt(playerid, 1), CMD_ArgInt(playerid, 2)); // Argumet 2 return integer 'money'
 *              SendClientMessange(playerid, -1, "You gave yourself a cash reward.");
 *              return 1;
 *          }
 *          CMD:new(playerid, args) { // <- New command
 *              // Done
 *              return 1;
 *          }
 *
 *      4. Recompile your gamemode/filterscript. Enjoy!
 *
 *  < All you need is just a small wit
 *    And the sea of creativity. >
 *
 */
#if defined _funcs_CMD_included
  #endinput
#endif
#define _funcs_CMD_included
#pragma library CMD

#define CMD_DEBUG_LOW       (0)             // Debug print in server console
#define ENABLE_CMD_MODE     (0)             // 0 - CMD:name(playerid, args); 1 - CMD:Commands(playerid, args);
#define COLOR_INVALID_CMD   (0xFF1100FF)    // Color for text 'CMD: Invalid command'
#define ENABLE_CLEANED_CMD  (1)             // Cleaned after calling command. NOTE: If found bugs in timers disabled it.
#define STORAGE_TIME_CMD    (200)           // Time to clean input command in ms

// Command limits
// Max cmd lenght 128 charaters
#define MAX_CMD_ARGUMENTS   (10)             // Max amount stored in array of arguments + command name
#define MAX_CMD_ARGLENGHT   (24)            // Max lenght argument

// Declared variables
//enum E_CMDS {
//    ARG[MAX_CMD_ARGLENGHT]
//}
new cmdstores[MAX_PLAYERS][MAX_CMD_ARGUMENTS][MAX_CMD_ARGLENGHT];
new cmdtimers[MAX_PLAYERS];
new cmdtmaxargs[MAX_PLAYERS];

/*
 * native IsCompared(string1[], string2[], bool:ignore_case=true);  // Compare string "A" == "B"
 * native CMD_ClearArguments(playerid);                             // Clear all stored arguments of player
 * native CMD_IsExec(playerid, cmd[], bool:ignore_case=true);       // Check command execution
 * native CMD_ArgString(playerid, index);                           // (string) Get argument by index
 * native CMD_ArgInt(playerid, index);                              // (integer) Get argument by index
 * native CMD_ArgFloat(playerid, index);                            // (float) Get argument by index
 * native CMD_ArgHex(playerid, index);                              // (integer) Get argument by index NOTE: string hex "0xFFFFFFFF" convert to integer
 */

// Stuff functions
// From    : gl_common.inc
// Credits : Copyright (c) SA-MP team
#if !defined token_by_delim
stock token_by_delim(const string[], return_str[], delim, start_index)
{
	new x;
	while (string[start_index] != EOS && string[start_index] != delim) {
	    return_str[x] = string[start_index];
	    x++;
	    start_index++;
	}
	return_str[x] = EOS;
	if (string[start_index] == EOS) start_index = (-1);
	return start_index;
}
#define __token_by_delim__
#endif

#if !defined strtok
stock strtok(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}
#define __strtok__
#endif

#if !defined strrest
stock strrest(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}
	new offset = index;
	new result[128];
	while ((index < length) && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}
#define __strrest__
#endif
// EOF Stuff functions

// Macro functions
//#define IsCompared(%1,%2,%3)  (strcmp(%1, %2, %3)==0)
#define CMD:%0(%1)              forward %0(%1);\
                                public %0(%1)
#define CMD_ArgString(%1,%2)    cmdstores[%1][%2][0]
#define CMD_ArgInt(%1,%2)       strval(cmdstores[%1][%2][0])
#define CMD_ArgFloat(%1,%2)     floatstr(cmdstores[%1][%2][0])
#define CMD_Arguments(%1)       cmdtmaxargs[%1]

// Stock functions
stock CMD_IsExec(playerid, cmd[], bool:ignore_case=true) {
    if (cmd[0] == '\0' || cmdstores[playerid][0][0] == '\0') return false;
    if (strcmp(cmd, cmdstores[playerid][0][0], ignore_case)==0) return true;
    return false;
}

stock IsCompared(string1[], string2[], bool:ignore_case=true) {
    if (string1[0] == '\0' || string2[0] == '\0') return false;
    if (strcmp(string1, string2, ignore_case)==0) return true;
    return false;
}

stock CMD_ArgHex(playerid, index) {
    new string[256];
    format(string, sizeof(string), "%s", cmdstores[playerid][index]);
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
    #if CMD_DEBUG_LOW
    printf("[FUNC:cmd.inc] CMD_ArgHex:\n\tplayerid %d\n\tindex %d\n\thex 0x%08h", playerid, index, result);
    #endif
    return result;
}

stock CMD_ArgSpaceString(string[], index) {
    new
        i,
        j,
        s, 
        pos, 
        result[256],
        num, 
        len = strlen(string)
    ;
    while ((s = string[pos]) && pos < len) {
        //printf("pos %d i %d == index %d num %d text '%c' result '%s'", pos, i, index, num, s, result);
        if (s == ' ' && i < index) {
            i++; 
            num++;
        } else {
            if (i >= index) {
                result[j] = s;
                j++;
            } else {
                num++;
            }
        }
        pos++;
    }  
    //string[len - num] = EOS; 
    //format(string, len, "%s", string[pos]);
    //printf("pos %d index %d str '%s'", pos, index, string);
    return result;
}

// Callback functions
forward CMD_ClearArguments(playerid);
public CMD_ClearArguments(playerid) {
    for (new i; i < MAX_CMD_ARGUMENTS; i++) {
        cmdstores[playerid][i][0] = '\0'
    }
    cmdtmaxargs[playerid] = 0;
    #if ENABLE_CLEANED_CMD
    KillTimer(cmdtimers[playerid]);
    #endif

    #if CMD_DEBUG_LOW
    printf("[FUNC:cmd.inc] CMD_ClearArguments:\n\tplayerid %d", playerid);
    #endif
    return true;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
    //strdel(cmdtext, 0, 1);
    new
        text[128],
        index,
        token
    ;
    while ((text = strtok(cmdtext, index)) && index < MAX_CMD_ARGUMENTS * MAX_CMD_ARGLENGHT) {
        if (!strlen(text)) break;

        #if CMD_DEBUG_LOW
        printf("[FUNC:cmd.inc] CMDParser: playerid %d cmd '%s' token[%d] '%s'", playerid, cmdtext, token, text);
        #endif

        format(cmdstores[playerid][token], 128, "%s", text);
        index++;
        token++;
    }
    if (token) {
        cmdtmaxargs[playerid] = token;
        #if ENABLE_CLEANED_CMD
        cmdtimers[playerid] = SetTimerEx("CMD_ClearArguments", STORAGE_TIME_CMD, 0, "i", playerid);
        #endif

        #if ENABLE_CMD_MODE
        //new funcname[24];
        //format(funcname, sizeof(funcname), "%s", cmdstores[playerid][0][1]);
        if (CallLocalFunction(cmdstores[playerid][0][1], "is", playerid, cmdtext)) {

            #if CMD_DEBUG_LOW
            printf("[FUNC:cmd.inc] CallLocalFunction:\n\tfunc %s\n\tplayerid %d", cmdstores[playerid][0][1], playerid);
            #endif

            return true;
        }
        #else
        if (CallLocalFunction("Commands", "is", playerid, cmdtext)) {

            #if CMD_DEBUG_LOW
            printf("[FUNC:cmd.inc] CallLocalFunction:\n\tfunc %s\n\tplayerid %d", "Commands", playerid);
            #endif

            return true;
        }
        #endif
    }
    //strins(cmdtext, "/", 0, strlen(cmdtext)+1);

    #if CMD_DEBUG_LOW
    printf("[FUNC:cmd.inc] CallLocalFunction:\n\tfunc %s\n\tplayerid %d", "CMD_OnPlayerCommandText", playerid);
    #endif

    return CallLocalFunction("CMD_OnPlayerCommandText", "is", playerid, cmdtext); //CMD_OnPlayerCommandText(playerid, cmdtext);
}
#if defined _ALS_OnPlayerCommandText
    #undef OnPlayerCommandText
#else
    #define _ALS_OnPlayerCommandText
#endif
#define OnPlayerCommandText CMD_OnPlayerCommandText
forward CMD_OnPlayerCommandText(playerid, cmdtext[]);

#if defined __token_by_delim__
    #undef token_by_delim
	#undef __token_by_delim__
#endif

#if defined __strtok__
    #undef strtok
	#undef __strtok__
#endif

#if defined __strrest__
    #undef strrest
	#undef __strrest__
#endif