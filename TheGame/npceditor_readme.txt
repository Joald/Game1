How To Use The NPC Editor
=========================
1. Type in the name of the NPC. Any of the associated resources with that NPC 
also have to use the same name (images, dialogue files etc.). The product of this
editor will be named the_name_you_type_in_here.npc No endlines allowed.
2. Enter the health points of the NPC. This is rather straightforward, it just has
to be an integer. (May get scaled with future additions of difficulty
and max health increases.
3. Simply enter 1 if the NPC is supposed to run straight to the player
as soon as they enter the level and follow him wherever he goes. 
If not, type in 0.
It can be changed later by scripts/code. 
4. Passive behaviour means that it will not engage in fighting unless attacked;
Aggressive means that once the player is close enough to them
it will initiate fight with him;
Friendly behaviour means that if player is in combat and close enough to them, they will
engage in combat on player's side.
This can also be changed in-game.
