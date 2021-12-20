#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QMainWindow>
#include <QTableWidget>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QLabel>
#include <QStatusBar>
#include "gocell.h"
#include "finddialog.h"
#include <QFileDialog>
#include <QTextStream>
#include <QApplication>

class SpreadSheet : public QMainWindow
{
    Q_OBJECT

public:
    SpreadSheet(QWidget *parent = nullptr);
    ~SpreadSheet();

protected:
    void setupMainWidget();
    void createActions();
    void createMenus();
    void createToolBars();
    void makeConnexions();

private slots:
    void close();
    void updateStatusBar(int, int); //Respond for the call changed
    void goCellSlot();
    void findSlot();
    void newfileslot();
    void saveasslot();
    void saveSlot();
    void loadslot();
    void cutslot();
    void copyslot();
    void pasteslot();
    void deleteslot();
    void selectrowslot();
    void selectrcolslot();
    void openrecentfilesslot();
    void aboutslot();
    void aboutqtslot();




private:
    void saveContent(QString filename);
    void loadContent(QString filename);


 //Pointers
private:
    // --------------- Central Widget -------------//
    QTableWidget *spreadsheet;
    // --------------- Actions       --------------//
    QList<QAction*> files;
    QAction * newFile;
    QAction * open;
    QAction * save;
    QAction * saveAs;
    QAction * exit;
    QAction *cut;
    QAction *copy;
    QAction *paste;
    QAction *deleteAction;
    QAction *find;
    QAction *row;
    QAction *Column;
    QAction *all;
    QAction *goCell;
    QAction*findDialog;
    QAction *recalculate;
    QAction *sort;
    QAction *showGrid;
    QAction *auto_recalculate;
    QAction *about;
    QAction *aboutQt;


    // --------- copy paste ------------
    QString topaste;


    // --------- Clipboard ------------
    QClipboard* clipboard = QApplication::clipboard();

    // ---------- Menus ----------
    QMenu *FileMenu;
    QMenu *editMenu;
    QMenu *toolsMenu;
    QMenu *optionsMenu;
    QMenu *helpMenu;
    QMenu* recentfile;

    //---------name current file------------
    QString * currentFile;

    //  ----- - Widget pouyr la bare d'etat
    QLabel *cellLocation;  //position de la cellule active
    QLabel *cellFormula;   // Formuel de la cellue active

    QString abouttext = "It our version of a spreadsheet , a small application for organizing,"
"  and storing  data in tabular form. That contains some usefull tools such as:\n "
"--(Go to cell) : [that leads you to the cell by typing it's position]\n "
"--(find) : [that looks dor the existing of a certain string]\n"
"and other basic tools like :\n recent files (last 5 files), cut, copy, past, select row/column(for a certain selected cell)..."
;

};

#endif // SPREADSHEET_H
