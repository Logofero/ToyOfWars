 * [Gamemode] Toy Of Wars
 * Server       : sa-mp 0.3.7 R1
 * Mode         : TDM
 * Map          : Custom locations
 * Release      : v1, 8 aug 2015
 * Updated      : v2, 21 aug 2015
 * Contributors : VanillaRain, Nero_3D, Logofero aka fERO
 * Credits      : Zamaroht - tool 'Zamaroht's TextDraw Editor'

 * Description:
 You have to fight on a toy cars against other teams. Every team has its own color.

 * Teams:
 0. Red
 1. Green
 2. Blue
 3. Purple
 4. Yellow
 5. White

 * Units:
 RCTiger        Tank
 RCBandit       Car
 RCRaider       Helicopter     
 RCGoblin       Helicopter     
 RCBaron        Airplane       

 * Cost:
 Humen          +50 score
 RCTiger        +90 score
 RCBandit       +70 score
 RCRaider       +100 score
 RCGoblin       +100 score
 RCBaron        +120 score
 
 * Health:
 RCTiger        1200 hp
 RCBandit       900 hp
 RCRaider       800 hp
 RCGoblin       800 hp
 RCBaron        700 hp

 * Max. Ammo:
 RCTiger        25 bullets
 RCBandit       30 bullets
 RCRaider       30 bullets
 RCGoblin       30 bullets
 RCBaron        20 bullets
 
 * Maps:
 0. Abandoned base v1   1200 score
 1. Abandoned base v2   1500 score

 * Controls:
 Fire - Shot of gun
 Enter - Enter/Exit RC cars

 * Commands:
 /team [0-5] - change team

 * Changes v2:
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

 * NOTE:
 (!) Projectiles fly through the comrades, but they still inflict damage if an explosion near.
 (~) Since I tested it on one player - there may be bugs with more players.
     If something is not working, please report as possible will be fixed in the next update.