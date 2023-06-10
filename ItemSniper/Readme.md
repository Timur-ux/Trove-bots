# Item Sniper (BETA)

Item sniper upload market every 3 seconds and if first item's cost below number you set - buy it.

It is beta version so for use it you need some skill in Cheat Engine.

## How to use it

1. Open main.cpp and in row 'bypass.attach(<num>)' set Game's id. You can see game's id in process explorer.

  Remember: next steps you need do again every time you close market or enter the game. 

2. In game: open market and find for any item.
3. Using Cheat Engine find static pointer to first item's cost. I don't explain how do this because i won't.
4. Insert in file main.cpp in row 'vector<uintprt_t> offsets = {...}' path of static pointer in '...' place.
5. After that in file ReloadBuy.cpp insert coordinates of SEARCH button, buy first item button and CONFIRM button. You can find coordinates of these buttons using according file in 'tool' directory.
  Coordiantes of SEARCH button input in reload function X, Y variable, FIB and CONFIRM in buy function in x1, y1 and x2, y2 respectively.
6. In file main.cpp in 47 row input cost per unit below which bot will buy item.
## Starting
  
Input in cmd: 'g++ main.cpp -o main.exe'
Input in cmd: './main.exe'

Open game window and wait. Bot will update market scan most low-cost item and if he's cost below you set - buy it.
