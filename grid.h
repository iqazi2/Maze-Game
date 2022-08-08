// TO DO:  Write file header.

// TO DO:  Update the member function comments to reflect your own style.

#pragma once

#include <algorithm>
#include <exception>
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T> class Grid {
private:
  struct CELL {
    CELL *Next; // InLine Comment: each cell's (i.e node's) pointer to the next
    T Val;      // Inline Comment: value of each cell
    size_t NumCols; // total # of columns (0..NumCols-1)
    CELL(CELL *_Next = nullptr, T _Val = T(),
         size_t _NumCols = 0) { // InLine Commment: constructs a cell
      Next = _Next; // InLine Comment: with next initialized to nullptr
      Val = _Val;
      NumCols =
          _NumCols; // InLine Comment: number of cells in the row is equal to 0
    }
  };

  size_t NumRows; // total # of rows (0..NumRows-1)
  CELL **Rows;    // C array of linked lists
public:
  // FUNCTION HEADER COMMENT:
  // default constructor:
  //
  // Called automatically by C++ to construct a 4x4 Grid.  All
  // elements are initialized to the default value of T.
  //

  Grid() {

    // FUNCTION HEADER COMMENT:
    // initialize 4 rows
    Rows = new CELL *[4];
    // InLine Comment: simply allocates memory and initializes the grid as a
    // whole with type "cell", as in, "made up of cells" (c-style array), which
    // is CELL **Rows. with size 4.

    NumRows = 4; // total rows in the grid

    // allocate the first cell of the linked list with default value:
    for (size_t r = 0; r < NumRows; ++r) {
      // InLine Comment: r = the first row in the grid, size_t is never negative
      Rows[r] = new CELL(nullptr, T(), 4);
      // InLine Comment: at the index (r) in the grid (rows), it will create a
      // new cell with 4 columns (NumCols == 4) as shown in the grid in
      // Milestone 1
      CELL *cur = Rows[r];
      // InLine Comment: initializes new cell pointer set equal to the cell,
      // which was just allocated (in the same iteration) at index r

      // create the linked list for this row.
      for (size_t c = 1; c < Rows[r]->NumCols; ++c) {
        //  starts at column = 1 in array (2nd) which is currently a nullptr and
        //  will keep allocating/iterating until index (c) = NumCols - 1 (will
        //  allocate entire row)
        cur->Next = new CELL(nullptr, T());
        cur = cur->Next;
      }
    }
  }

  // FUNCTION HEADER COMMENT:
  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a Grid with R rows,
  // where each row has C columns. All elements are initialized to
  // the default value of T.
  //

  Grid(size_t R, size_t C) {
    // TO DO:  Write this parameterized constructor.
    // cout << "parameterized constructor called." << endl;
    if (R <= 0 || C <= 0) {
      throw invalid_argument("row or col out of bounds");
    }
    Rows = new CELL *[R];
    NumRows = R;

    for (size_t r = 0; r < NumRows; r++) {
      Rows[r] = new CELL(nullptr, T(), C);
      // InLine Comment: at the index (r) in the grid (rows), it will create a
      // new cell with number of columns (size_t C) (NumCols == C) as shown in
      // the grid in Milestone 1
      CELL *cur = Rows[r];
      for (size_t c = 1; c < Rows[r]->NumCols; c++) {
        cur->Next = new CELL(nullptr, T());
        cur = cur->Next;
      }
    }
  }

  // FUNCTION HEADER COMMENT:
  //
  // destructor:
  //
  // Called automatically by C++ to free the memory associated by the vector.
  //

  virtual ~Grid() {
    // TO DO:  Write this destructor.
    for (size_t r = 0; r < NumRows; r++) {
      CELL *cur = Rows[r];
      CELL *prev;
      while (cur != nullptr) {
        prev = cur;
        cur = cur->Next;
        delete prev;
      }
    }
    if (NumRows > 0) {
      delete[] Rows;
    }
    NumRows = 0;
  }

  // FUNCTION HEADER COMMENT:
  //
  // copy constructor:
  //
  // Called automatically by C++ to construct a Grid that contains a
  // copy of an existing Grid.  Example: this occurs when passing
  // Grid as a parameter by value
  //
  //   void somefunction(Grid<int> G2)  <--- G2 is a copy:
  //   { ... }
  //

  Grid(const Grid<T> &other) {
    // TO DO:  Write this copy constructor.
    // cout << "COPY CONSTRUCTOR CALLED" << endl;

    this->NumRows = other.NumRows;
    this->Rows = new CELL *[this->NumRows]; // allocates memory
    // cout << "NUMROWS " << this->NumRows << endl;
    if (this->NumRows <= 0) {
      throw invalid_argument("row or col out of bounds");
    }
    // cout << "NUMROWS " << this->NumRows << endl;
    for (size_t i = 0; i < this->NumRows; i++) {
      // cout << "b4this->Rows[i]" << endl;
      this->Rows[i] =
          new CELL(nullptr, other.Rows[i]->Val, other.Rows[i]->NumCols);
      // cout << "this->Rows[i]" << this->Rows[i];
      CELL *thisCurr =
          this->Rows[i]; // InLine Comment: to keep track of this list
      CELL *otherCurr =
          other.Rows[i]; // InLine Comment: to keep track of other list
      for (size_t j = 1; j < this->Rows[i]->NumCols; j++) {
        thisCurr->Next =
            new CELL(nullptr, otherCurr->Next->Val, otherCurr->NumCols);
        thisCurr = thisCurr->Next;
        otherCurr = otherCurr->Next;
      }
    }
  }

  // FUNCTION HEADER COMMENT:
  //
  // copy operator=
  //
  // Called when you assign one vector into another, i.e. this = other;
  //

  Grid &operator=(const Grid &other) {

    if (this->NumRows > 0) {
      for (size_t r = 0; r < this->NumRows; r++) {
        CELL *cur = this->Rows[r];
        CELL *prev; // this variable will be deleted
        while (cur != nullptr) {
          prev = cur;
          cur = cur->Next;
          delete prev; // deleting last variable and letting cur iterate
        }
      }
      delete[] Rows;
    }

    this->NumRows = other.NumRows;
    this->Rows = new CELL *[this->NumRows];

    for (size_t i = 0; i < this->NumRows; i++) {
      this->Rows[i] =
          new CELL(nullptr, other.Rows[i]->Val, other.Rows[i]->NumCols);
      CELL *thisCurr = this->Rows[i];
      CELL *otherCurr = other.Rows[i];
      for (size_t j = 1; j < this->Rows[i]->NumCols; j++) {
        thisCurr->Next =
            new CELL(nullptr, otherCurr->Next->Val, otherCurr->NumCols);
        thisCurr = thisCurr->Next;
        otherCurr = otherCurr->Next;
      }
    }
    return *this;
  }

  // FUNCTION HEADER COMMENT:
  //
  // numrows
  //
  // Returns the # of rows in the Grid.  The indices for these rows
  // are 0..numrows-1.
  //

  size_t numrows() const {

    // TO DO:  Write this function.

    return NumRows; // TO DO:  update this, it is only here so code compiles.
  }

  // FUNCTION HEADER COMMENT:
  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  For now, each row will have the same number of columns.
  //

  size_t numcols(size_t r) const {
    // TO DO:  Write this function
    // cout << "numcols called" << endl;
    if (r > NumRows || r < 0) {
      throw invalid_argument("row out of bounds");
    }
    return this->Rows[r]->NumCols;
  }

  // FUNCTION HEADER COMMENT:
  //
  // size
  //
  // Returns the total # of elements in the grid.
  //

  size_t size() const {
    // TO DO:  Write this function.
    size_t size = Rows[0]->NumCols * NumRows;
    return size; // TO DO:  update this, it is only here so code compiles.
  }

  // FUNCTION HEADER COMMENT:
  //
  // ()
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    grid(r, c) = ...
  //    cout << grid(r, c) << endl;
  //

  T &operator()(size_t r, size_t c) {
    // T temp;
    // TO DO:  Write this function.
    if (r > NumRows || r < 0 || c > this->Rows[0]->NumCols || c < 0) {
      throw invalid_argument("row or col out of bounds");
    }
    CELL *curr =
        this->Rows[r]; // this sets it equal to row at index r starting 0
    for (size_t j = 0; j < this->Rows[r]->NumCols; j++) {
      if (j == c) { // if the column number j is equal to given c
        return curr->Val;
      }
      curr = curr->Next;
    }
  }

  // FUNCTION HEADER COMMENT:
  //
  // _output
  //
  // Outputs the contents of the grid; for debugging purposes.  This is not
  // tested.
  //

  void _output() {
    // TO DO:  Write this function.
    for (size_t r = 0; r < this->NumRows; r++) {
      CELL *curr = this->Rows[r];
      for (size_t c = 0; c < this->Rows[r]->NumCols;
           c++) { // simply for output to help debug later on
        cout << curr->Val << " ";
        curr = curr->Next;
      }
      cout << endl;
    }
  }
};
