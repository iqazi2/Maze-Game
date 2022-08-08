#include "grid.h"
#include "maze.h"
#include <random>
#include <set>
#include <utility>
using namespace std;

/* Change this constant to contain your full first and last name (middle is ok
 * too).
 *
 * WARNING: Once you've set set this constant and started exploring your maze,
 * do NOT edit the value of kYourName. Changing kYourName will change which
 * maze you get back, which might invalidate all your hard work!
 */
const string kYourName = "Ibrahim Qazi";

/* Change these constants to contain the paths out of your mazes. */
const string kPathOutOfRegularMaze = "WWSSENSSWWEENWNNWSS";
const string kPathOutOfTwistyMaze = "NWEWEENWNE";

void itemTracker(bool &ret1, bool &ret2, bool &ret3, bool &retAll,
                 MazeCell *curr);
bool readThroughMoves(MazeCell *curr, const string moves);

// Function Header Comment: This function takes the current spot in the maze and
// reads the string of moves and moves according to letter and what it
// represents
bool readThroughMoves(MazeCell *curr, const string moves) {
  bool ret1 = false; // Potion
  bool ret2 = false; // Spellbook
  bool ret3 = false; // Wand
  bool retAll = false;
  itemTracker(ret1, ret2, ret3, retAll, curr);
  for (int i = 0; i < moves.size(); i++) {
    // cout << "MOVES[i]" << moves[i] << endl;
    if ((moves[i] == 'S' || moves[i] == 's') && curr->south != nullptr) {
      curr = curr->south;
      // if S than move curr to the address at south etc
      itemTracker(ret1, ret2, ret3, retAll, curr);
    } else if ((moves[i] == 'N' || moves[i] == 'n') && curr->north != nullptr) {
      curr = curr->north;
      itemTracker(ret1, ret2, ret3, retAll, curr);
    } else if ((moves[i] == 'E' || moves[i] == 'e') && curr->east != nullptr) {
      curr = curr->east;
      itemTracker(ret1, ret2, ret3, retAll, curr);
    } else if ((moves[i] == 'W' || moves[i] == 'w') && curr->west != nullptr) {
      curr = curr->west;
      itemTracker(ret1, ret2, ret3, retAll, curr);
      // this is once all items are found.
    } else {
      return false;
    }
  }
  return retAll;
}

// Function Header Comment: The itemTracker function keeps track of the bools
// that symbolize the items. ret1 = potion. ret2 = spellbook, etc,
void itemTracker(bool &ret1, bool &ret2, bool &ret3, bool &retAll,
                 MazeCell *curr) {

  if (curr->whatsHere == "Potion") {
    ret1 = true;
    // if the curr spot contains the potion it will say it's found by indicating
    // ret1 = true and the others i.e ret 2 and ret 3 follow this same protocol
  }
  if (curr->whatsHere == "Spellbook") {
    ret2 = true;
  }
  if (curr->whatsHere == "Wand") {
    ret3 = true;
  }
  if (ret1 == true && ret2 == true && ret3 == true) {
    retAll = true;
  }
  return;
}

// Function Header Comment: isPathToFreedom sets a variable equal to where a
// person starts in the maze and runs it through the other functions described
// above their respective function defintions
bool isPathToFreedom(MazeCell *start, const string &moves) {

  MazeCell *curr = start;
  // readThroughMoves(curr, moves);
  bool legality = readThroughMoves(curr, moves);
  // this indicates whether the path is legal. so if legality is true than the
  // path in the string is a legal path

  return legality;
}