//========================================================================
// FILE - Fl_Table.cxx                                                  //
// For the Fast Light Tool Kit (FLTK) - www.fltk.org                    //
//========================================================================
//                                                                      //
// Table to dsiplay the data of the atomic structures.                  //
//                                                                      //
//======================================================================//
//  This file is part of xmolvis                                        //
//                                                                      //
//  xmolvis is free software: you can redistribute it and/or modify     //
//  it under the terms of the GNU General Public License as published by//
//  the Free Software Foundation, either version 3 of the License, or   //
//  (at your option) any later version.                                 //
//                                                                      //
//  xmolvis is distributed in the hope that it will be useful,          //
//  but WITHOUT ANY WARRANTY; without even the implied warranty of      //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the       //
//  GNU General Public License for more details.                        //
//                                                                      //
//  You should have received a copy of the GNU General Public License   //
//  along with xmolvis.  If not, see <http://www.gnu.org/licenses/>.    //
//======================================================================//

#ifndef __TABLE_H_
#define __TABLE_H_

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Scrollbar.H>
#include <FL/Fl_Widget.H>
#include <vector>

#define TABLE_WHEN_DCLICK  16


class CTable : public Fl_Group {
public:
  typedef bool (*Highlighter)(int, const char **, Fl_Color &);
  typedef int (*Comparator)(const char*, const char*);

private:
  struct ColumnInfo {
    bool hidden;
    const char *title;
    int width;
    Fl_Align align;
    Comparator comparator;
  };

  // Scrollbars
  Fl_Scrollbar *hScroll, *vScroll;

  // Popup menu
  const Fl_Menu_Item *popupMenu;
  bool menuAlloc;

  // Column data
  std::vector<struct ColumnInfo> header;

  // Cell data
  std::vector<char**> data;
  Highlighter highlighter;


  // CTable dimensions
  int tableHeight, tableWidth;
  int oX, oY, oW, oH;  // Outer dimensions (widget - box)
  int iX, iY, iW, iH;  /*
         * CTable area dimensions
         * (outer dimension - header - scrollbars)
         */

  // For optimization
  int topRow, bottomRow, leftCol, rightCol;
  int topRowY, leftColX;

  int Row, Col;
  int nCols, nRows;  // Number of rows and columns
  int cPos;    // Column where new entry is added.

  int resizing, dragX;
  int pushed;
  int sortColumn;

  // Object sizes
  int scrollbarSize;
  int headerHeight;
  int rowHeight;

  int selected;
  char **curRow;

  // Various flags
  bool ascent;
  bool canResize, canSort;
  bool noMoreColumns;
  bool toBeSorted;
  bool dimensionsChanged;
  bool headerEnabled;
  bool headerRedraw;

  void dSort(int start, int end, Comparator compare);
  void aSort(int start, int end, Comparator compare);

protected:
  virtual int handle(int event);

  virtual void drawHeader(int x, int y);
  virtual void drawRow(int row, char *rowData[], int x, int y);

  virtual void draw();
  virtual void resize(int x, int y, int w, int h);

  void calcDimensions();
  void scrolled();
  void resized();

  static void scrollCallback(Fl_Widget *widget, void *data);

public:
  CTable(int x, int y, int w, int h, char *label = NULL);
  ~CTable();

  bool headerOn() const;
  void headerOn(bool enabled);
  bool allowResize() const;
  void allowResize(bool allow);
  bool allowSort() const;
  void allowSort(bool allow);

  int headerSize() const;
  void headerSize(int height);
  int rowSize() const;
  void rowSize(int height);
  int scrollbSize() const;
  void scrollbSize(int size);

  Fl_Align columnAlign(int column) const;
  void columnAlign(int column, Fl_Align align);
  int columnWidth(int column) const;
  void columnWidth(int column, int width);
  const char *columnTitle(int column);
  void columnTitle(int column, const char *title);
  bool columnHidden(int column);
  void columnHidden(int column, bool hidden);

  void sort();
  void sort(int column, bool ascent);
  void getSort(int &sortColumn, bool &ascent);

  void setHighlighter(Highlighter highlighter);

  void addColumn(const char *label, int width = 150,
      Fl_Align align = (Fl_Align)(FL_ALIGN_RIGHT | FL_ALIGN_CLIP),
      Comparator comparator = NULL);
  void addHiddenColumn(const char *label);

  void addCell(const char *data);
  void addCell(int data);
  void addRow(int cols, ...);
  void addFromTSV(const char *data);
  void removeRow(int row);
  void clear(bool removeColumns = false);

  void where(int x, int y, int &row, int &column, int &resize);
  void scrollTo(int pos);

  int columns();
  int rows();
  int column();
  int row();
  void value(int selection);
  int value();
  char *valueAt(int row, int column);
  int intValueAt(int row, int column);
  void valueAt(int row, int column, char *data);
  void valueAt(int row, int column, int data);

  const char **getRow(int row);

  const Fl_Menu_Item *menu();
  void menu(const Fl_Menu_Item *m);
  void menuCopy(const Fl_Menu_Item *m);
  void menuClear();

  static int compareInt(const char *val1, const char *val2);
};

#endif
