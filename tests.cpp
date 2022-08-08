#include "EscapeTheLabyrinth.h"
#include "grid.h"
#include "maze.h"
#include <gtest/gtest.h>
#include <map>
#include <set>
#include <sstream>
#include <vector>

TEST(grid, defaultConstructor) {
  Grid<int> g1;
  EXPECT_EQ(g1.numrows(), 4);
}

TEST(grid, parameterizedConstructor) {
  int N = 10;
  for (size_t r = 1; r < N; r++) {
    // this varies according to r and c indices in for loop
    for (size_t c = 1; c < N; c++) {
      Grid<int> g1(r, c);
      EXPECT_EQ(g1.numrows(), r);
    }
  }
}

TEST(grid, numrowsdefaultConstructor) {
  Grid<int> g1;
  EXPECT_EQ(g1.numrows(), 4);
  // initialized to 4
}

TEST(grid, numrowsparameterizedConstructor) {
  int N = 10;

  for (size_t r = 1; r < N; r++) {
    for (size_t c = 1; c < N; c++) {
      Grid<int> g1(r, c);
      EXPECT_EQ(g1.numrows(), r);
      // this varies based on for loop
    }
  }
}

TEST(grid, numcolsdefaultConstructor) {
  Grid<int> g1;

  for (int i = 0; i < g1.numrows(); i++) {
    EXPECT_EQ(g1.numcols(i), 4);
  }
}

TEST(grid, numcolsparameterizedConstructor) {
  int N = 50;
  for (size_t r = 1; r < N; r++) {
    for (size_t c = 1; c < N; c++) {
      Grid<int> g1(r, c);
      EXPECT_EQ(g1.numcols(r-1), c);
    }
  }
}

TEST(grid, sizedefaultConstructor) {
  Grid<int> g1;
  EXPECT_EQ(g1.size(), 16);
}

TEST(grid, sizeparameterizedConstructor) {
  for (size_t r = 1; r < 10; r++) {
    for (size_t c = 1; c < 10; c++) {
      Grid<int> g1(r, c);
      EXPECT_EQ(g1.size(), r * c);
    }
  }
}

TEST(grid, copyConstructor) {
  for (size_t r = 1; r < 100; r++) {
    for (size_t c = 1; c < 5; c++) {
      Grid<int> g1(r, c);
      g1(r - 1, c - 1) = r + c;
      Grid<int> g2(g1);

      EXPECT_EQ(g1.numrows(), g2.numrows());
      EXPECT_EQ(g1.numcols(r - 1), g2.numcols(r - 1));
      EXPECT_EQ(g1.size(), g2.size());
      EXPECT_EQ(g1(r - 1, c - 1), g2(r - 1, c - 1));
    }
  }
}

TEST(grid, copyOperatorInts) {
  for (size_t r = 1; r < 100; r++) {
    for (size_t c = 1; c < 5; c++) {
      Grid<int> g1(r, c); // this one is different than getter in () operator
      Grid<int> g2;
      g2 = g1;

      EXPECT_EQ(g2.numrows(), g1.numrows());
      EXPECT_EQ(g1.numcols(r - 1), g2.numcols(r - 1));
      EXPECT_EQ(g1.size(), g2.size());
      EXPECT_EQ(g1(r - 1, c - 1), g2(r - 1, c - 1));
    }
  }
}

TEST(grid, copyOperatordoubles) {
  for (size_t r = 1; r < 100; r++) {
    for (size_t c = 1; c < 5; c++) {
      Grid<double> g1(r, c);
      g1(r - 1, c - 1) = (r * c) + 0.1;
      Grid<double> g2;
      g2 = g1;
      EXPECT_EQ(g2.numrows(), g1.numrows());
      EXPECT_EQ(g1.numcols(r - 1), g2.numcols(r - 1));
      EXPECT_EQ(g1.size(), g2.size());
      EXPECT_EQ(g1(r - 1, c - 1), g2(r - 1, c - 1));
    }
  }
}

TEST(grid, copyOperatorchar) {
  for (size_t r = 1; r < 100; r++) {
    for (size_t c = 1; c < 5; c++) {
      Grid<char> g1(r, c);
      g1(r - 1, c - 1) = (r * c) + 'a';
      Grid<char> g2;
      g2 = g1;

      EXPECT_EQ(g2.numrows(), g1.numrows());
      EXPECT_EQ(g1.numcols(r - 1), g2.numcols(r - 1));
      EXPECT_EQ(g1.size(), g2.size());
      EXPECT_EQ(g1(r - 1, c - 1), g2(r - 1, c - 1));
    }
  }
}

TEST(grid, copyOperatorstrings) {
  for (size_t r = 1; r < 100; r++) {
    for (size_t c = 1; c < 5; c++) {
      Grid<string> g1(r, c);
      g1(r - 1, c - 1) = "`f";
      Grid<string> g2;
      g2 = g1;

      EXPECT_EQ(g2.numrows(), g1.numrows());
      EXPECT_EQ(g1.numcols(r - 1), g2.numcols(r - 1));
      EXPECT_EQ(g1.size(), g2.size());
      EXPECT_EQ(g1(r - 1, c - 1), g2(r - 1, c - 1));
    }
  }
}

TEST(grid, copyOperatorinvalid) {
  for (size_t r = 1; r < 100; r++) {
    for (size_t c = 1; c < 5; c++) {
      Grid<char> g1(r, c);
      g1(r - 1, c - 1) = (r * c) + 'a';
      Grid<char> g2;
      g2 = g1;
      EXPECT_EQ(g2.numrows(), g1.numrows());
      EXPECT_EQ(g1.numcols(r - 1), g2.numcols(r - 1));
      EXPECT_EQ(g1.size(), g2.size());
      EXPECT_EQ(g1(r - 1, c - 1), g2(r - 1, c - 1));
    }
  }
}

TEST(grid, setterreferenceOperator) {
  Grid<int> g1(100, 5);
  for (int r = 0; r < 100; r++) {
    for (int c = 0; c < 5; c++) {
      g1(r, c) = r * c;
      // cout<< "g1(" << r << "," << c << ") " << g1(r,c) << endl;
      // int i = g1(r, c);
      // cout<< "i: " << i << endl;
      EXPECT_EQ(g1(r, c), r * c);
      // EXPECT_EQ(i, r*c);
    }
  }
}

TEST(grid, getterreferenceOperator) {
  Grid<int> g1(100, 5);
  for (size_t r = 0; r < 100; r++) {
    for (size_t c = 0; c < 5; c++) {
      g1(r, c) = r * c;
      // cout<< "g1(" << r << "," << c << ") " << g1(r,c) << endl;
      int i = g1(r, c);
      // cout<< "i: " << i << endl;
      // EXPECT_EQ(g1(r,c), r*c);
      EXPECT_EQ(i, r * c);
    }
  }
}

TEST(grid, outputints) {
  Grid<int> g(10, 6);
  // checks ints compatibility in the list
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 6; j++) {
      g(i, j) = 1 + (i * j);
      EXPECT_EQ(g(i, j), 1 + (i * j));
    }
  }
  g._output();
}

TEST(grid, outputdoubles) {
  Grid<double> g(10, 6);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 6; j++) {
      g(i, j) = 1.1 + (i * j);
      EXPECT_EQ(g(i, j), 1.1 + (i * j));
    }
  }
  g._output();
}

// TEST(grid, outputstring) {
//   Grid<string> g(10, 6);

//   for (int i = 0; i < 10; i++) {
//     for (int j = 0; j < 6; j++) {
//       g(i,j) = "ll";

//     }
//   }
//   g._output();
// }

// TEST(grid, outputchars) {
//   Grid<char> g(10, 6);

//   for (int i = 0; i < 10; i++) {
//     for (int j = 0; j < 6; j++) {
//       g(i,j) =  'a';
//     }
//   }
//   g._output();
// }

// TO DO:  As you get to each milestone, you can comment out these provided
// tests.  They currently use grid.h and will segfault until you implement
// grid correctly.

// Provided Test: sample maze from handout, make lots more yourself!
TEST(maze, basic) {
  vector<string> textMaze;

  textMaze.push_back("* *-W *");
  textMaze.push_back("| |   |");
  textMaze.push_back("*-* * *");
  textMaze.push_back("  | | |");
  textMaze.push_back("S *-*-*");
  textMaze.push_back("|   | |");
  textMaze.push_back("*-*-* P");

  Maze m(textMaze);

  MazeCell *start = m.getStart(2, 2);

  /* These paths are the ones in the handout. They all work. */
  EXPECT_TRUE(isPathToFreedom(start, "ESNWWNNEWSSESWWN"));
  EXPECT_TRUE(isPathToFreedom(start, "SWWNSEENWNNEWSSEES"));
  EXPECT_TRUE(isPathToFreedom(start, "WNNEWSSESWWNSEENES"));

  /* These paths don't work, since they don't pick up all items. */
  EXPECT_FALSE(isPathToFreedom(start, "ESNW"));
  EXPECT_FALSE(isPathToFreedom(start, "SWWN"));
  EXPECT_FALSE(isPathToFreedom(start, "WNNE"));

  /* These paths don't work, since they aren't legal paths. */
  EXPECT_FALSE(isPathToFreedom(start, "WW"));
  EXPECT_FALSE(isPathToFreedom(start, "NN"));
  EXPECT_FALSE(isPathToFreedom(start, "EE"));
  EXPECT_FALSE(isPathToFreedom(start, "SS"));
}

TEST(maze, STUDENTMAZE1) {
  vector<string> textMaze;

  textMaze.push_back("W *-S *");
  textMaze.push_back("| |   |");
  textMaze.push_back("*-* * *");
  textMaze.push_back("  | | |");
  textMaze.push_back("* *-*-*");
  textMaze.push_back("|   | |");
  textMaze.push_back("*-P-* *");

  Maze m(textMaze);

  MazeCell *start = m.getStart(0, 2);

  EXPECT_FALSE(isPathToFreedom(start, "SESNW"));
  EXPECT_FALSE(isPathToFreedom(start, "SSWWN"));
  EXPECT_FALSE(isPathToFreedom(start, "SWNNE"));

  EXPECT_FALSE(isPathToFreedom(start, "WW"));
  EXPECT_FALSE(isPathToFreedom(start, "NN"));
  EXPECT_FALSE(isPathToFreedom(start, "EE"));
  EXPECT_FALSE(isPathToFreedom(start, "SS"));
}

TEST(maze, STUDENTMAZE2) {
  vector<string> textMaze;
  // different mazes to ensure it works with any and every
  textMaze.push_back("* * *");
  textMaze.push_back("     ");
  textMaze.push_back("W * S");
  textMaze.push_back("     ");
  textMaze.push_back("P * *");

  Maze m(textMaze);

  MazeCell *start = m.getStart(2, 1);
  // start of current person in maze

  EXPECT_FALSE(isPathToFreedom(start, "EWNEES"));
  EXPECT_FALSE(isPathToFreedom(start, "NWSEE"));
  EXPECT_FALSE(isPathToFreedom(start, "ENWWS"));
  EXPECT_FALSE(isPathToFreedom(start, "SWNNEES"));
}

// Provided Test: don't allow going through walls
TEST(maze, tryingToGoThroughWalls) {
  vector<string> textMaze;

  textMaze.push_back("* S *");
  textMaze.push_back("     ");
  textMaze.push_back("W * P");
  textMaze.push_back("     ");
  textMaze.push_back("* * *");

  Maze m(textMaze);

  MazeCell *start = m.getStart(1, 1);

  EXPECT_FALSE(isPathToFreedom(start, "WNEES"));
  EXPECT_FALSE(isPathToFreedom(start, "NWSEE"));
  EXPECT_FALSE(isPathToFreedom(start, "ENWWS"));
  EXPECT_FALSE(isPathToFreedom(start, "SWNNEES"));
}

// Provided Test: Works when starting on an item
TEST(maze, startOnItem) {
  vector<string> textMaze;

  textMaze.push_back("P-S-W");

  Maze m(textMaze);
  MazeCell *start = m.getStart(0, 0);

  EXPECT_TRUE(isPathToFreedom(start, "EE"));
  start = m.getStart(0, 1);
  EXPECT_TRUE(isPathToFreedom(start, "WEE"));
  start = m.getStart(0, 2);
  EXPECT_TRUE(isPathToFreedom(start, "WW"));
}

// Provided Test: Reports errors if given illegal characters.
TEST(maze, invalidChar) {
  vector<string> textMaze;

  textMaze.push_back("* *-W *");
  textMaze.push_back("| |   |");
  textMaze.push_back("*-* * *");
  textMaze.push_back("  | | |");
  textMaze.push_back("S *-*-*");
  textMaze.push_back("|   | |");
  textMaze.push_back("*-*-* P");

  Maze m(textMaze);
  MazeCell *start = m.getStart(0, 0);

  /* These paths contain characters that aren't even close to permissible. */
  EXPECT_FALSE(isPathToFreedom(start, "Q"));
  EXPECT_FALSE(isPathToFreedom(start, "X"));
  EXPECT_FALSE(isPathToFreedom(start, "!"));
  EXPECT_FALSE(isPathToFreedom(start, "?"));

  EXPECT_FALSE(isPathToFreedom(start, "n"));
  EXPECT_FALSE(isPathToFreedom(start, "s"));
  EXPECT_FALSE(isPathToFreedom(start, "e"));
  EXPECT_FALSE(isPathToFreedom(start, "w"));

  ///* These are tricky - they're legal paths that happen to have an unexpected
  // * character at the end.
  start = m.getStart(2, 2);
  EXPECT_FALSE(isPathToFreedom(start, "ESNWWNNEWSSESWWNQ"));
  EXPECT_FALSE(isPathToFreedom(start, "SWWNSEENWNNEWSSEES!!!"));
  EXPECT_FALSE(isPathToFreedom(start, "WNNEWSSESWWNSEENES??"));
}

// Provided Test: This tests your personalized regular maze to see if you were
// able to escape.
TEST(maze, escapeRegularMaze) {
  Maze m(4, 4);
  MazeCell *start = m.mazeFor(kYourName);
  EXPECT_TRUE(isPathToFreedom(start, kPathOutOfRegularMaze));
}

// Provided Test: This tests your personalized twisty maze to see if you were
// able to escape.
TEST(maze, escapeTwistyMaze) {
  Maze m(4, 4);
  MazeCell *start = m.twistyMazeFor(kYourName);
  EXPECT_TRUE(isPathToFreedom(start, kPathOutOfTwistyMaze));
}
