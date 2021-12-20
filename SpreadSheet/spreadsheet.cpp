#include "spreadsheet.h"
#include <QPixmap>
#include <QMenuBar>
#include <QToolBar>
#include <QApplication>
#include <QMessageBox>
#include <QClipboard>



SpreadSheet::SpreadSheet(QWidget *parent)
    : QMainWindow(parent)
{
    //Seting the spreadsheet

    setupMainWidget();

    // Creaeting Actions
    createActions();

    // Creating Menus
    createMenus();


    //Creating the tool bar
    createToolBars();

    //making the connexions
    makeConnexions();


    //Creating the labels for the status bar (should be in its proper function)
    cellLocation = new QLabel("(1, 1)");
    cellFormula = new QLabel("");
    statusBar()->addPermanentWidget(cellLocation);
    statusBar()->addPermanentWidget(cellFormula);

    //initialize filename
    currentFile=nullptr;
//    topaste=nullptr;
    //spreadsheetname
    setWindowIcon(QIcon(":/xls.png"));
    setWindowTitle("Buffer");
}

void SpreadSheet::setupMainWidget()
{
    spreadsheet = new QTableWidget;
    spreadsheet->setRowCount(100);
    spreadsheet->setColumnCount(100);
    setCentralWidget(spreadsheet);

}

SpreadSheet::~SpreadSheet()
{
    delete spreadsheet;

    // --------------- Actions       --------------//
    delete newFile;
    delete open;
    delete save;
    delete saveAs;
    delete exit;
    delete cut;
    delete copy;
    delete paste;
    delete deleteAction;
    delete find;
    delete row;
    delete Column;
    delete all;
    delete goCell;
    delete recalculate;
    delete sort;
    delete showGrid;
    delete auto_recalculate;
    delete about;
    delete aboutQt;

    // ---------- Menus ----------
    delete FileMenu;
    delete editMenu;
    delete toolsMenu;
    delete optionsMenu;
    delete helpMenu;
}

void SpreadSheet::createActions()
{
    // --------- New File -------------------
   QPixmap newIcon(":/new_file.png");
   newFile = new QAction(newIcon, "&New", this);
   newFile->setShortcut(tr("Ctrl+N"));


    // --------- open file -------------------
   QPixmap openIcon(":/open_file.png");
   open = new QAction(openIcon, "&Open", this);
   open->setShortcut(tr("Ctrl+O"));

    // --------- save file -------------------
   QPixmap SaveIcon(":/save_file.png");
   save = new QAction(SaveIcon, "&Save", this);
   save->setShortcut(tr("Ctrl+S"));

    // --------- save As file -------------------
   saveAs = new QAction("save &As", this);


    // --------- cut file -------------------
   QPixmap cutIcon(":/cut_icon.png");
   cut = new QAction(cutIcon, "&Cut", this);
   cut->setShortcut(tr("Ctrl+X"));

   // --------- copy menu -----------------
   QPixmap CopyIcon(":/Copy_file.png");
   copy = new QAction(CopyIcon, "&Copy", this);
   copy->setShortcut(tr("Ctrl+C"));

   // --------- paste menu -----------------
   QPixmap PasteIcon(":/Paste_file.png");
   paste = new QAction(PasteIcon, "&Paste", this);
   paste->setShortcut(tr("Ctrl+V"));

   // --------- delete menu -----------------
   QPixmap DeleteIcon(":/Delete_file.png");
   deleteAction = new QAction(DeleteIcon, "&Delete", this);
   deleteAction->setShortcut(tr("Del"));


   row  = new QAction("&Row", this);
   Column = new QAction("&Column", this);
   all = new QAction("&All", this);
   all->setShortcut(tr("Ctrl+A"));


   // --------- find menu -----------------
   QPixmap findIcon(":/search_icon.png");
   find= new QAction(findIcon, "&Find", this);
   find->setShortcut(tr("Ctrl+F"));

   // --------- goCell menu -----------------
   QPixmap goCellIcon(":/go_to_icon.png");
   goCell = new QAction( goCellIcon, "&Go to Cell", this);
   goCell->setShortcut(tr("f5"));

   // --------- recalculate menu -----------------
   recalculate = new QAction("&Recalculate",this);
   recalculate->setShortcut(tr("F9"));


   // --------- sort menu -----------------
   sort = new QAction("&Sort");



   showGrid = new QAction("&Show Grid");
   showGrid->setCheckable(true);
   showGrid->setChecked(spreadsheet->showGrid());

   auto_recalculate = new QAction("&Auto-recalculate");
   auto_recalculate->setCheckable(true);
   auto_recalculate->setChecked(true);


   QPixmap AboutIcon(":/About.png");
   about =  new QAction(AboutIcon,"&About", this);

   QPixmap qtIcon(":/qt_icon.png");
   aboutQt = new QAction(qtIcon, "About &Qt",this);

    // --------- exit -------------------
   QPixmap exitIcon(":/quit_icon.png");
   exit = new QAction(exitIcon,"&Exit", this);
   exit->setShortcut(tr("Ctrl+Q"));
}

void SpreadSheet::close()
{

    auto reply = QMessageBox::question(this, "Exit",
                                       "Do you really want to quit?");
    if(reply == QMessageBox::Yes)
        qApp->exit();
}

void SpreadSheet::createMenus()
{
    // --------  File menu -------//
    FileMenu = menuBar()->addMenu("&File");
    FileMenu->addAction(newFile);
    FileMenu->addAction(open);
    FileMenu->addAction(save);
    FileMenu->addAction(saveAs);
    FileMenu->addSeparator();
    recentfile = FileMenu->addMenu("&Recent files");
    FileMenu->addSeparator();
    FileMenu->addAction(exit);

    //------------- Edit menu --------/
    editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction(cut);
    editMenu->addAction(copy);
    editMenu->addAction(paste);
    editMenu->addAction(deleteAction);
    editMenu->addSeparator();
    auto select = editMenu->addMenu("&Select");
    select->addAction(row);
    select->addAction(Column);
    select->addAction(all);

    editMenu->addAction(find);
    editMenu->addAction(goCell);



    //-------------- Toosl menu ------------
    toolsMenu = menuBar()->addMenu("&Tools");
    toolsMenu->addAction(recalculate);
    toolsMenu->addAction(sort);



    //Optins menus
    optionsMenu = menuBar()->addMenu("&Options");
    optionsMenu->addAction(showGrid);
    optionsMenu->addAction(auto_recalculate);


    //----------- Help menu ------------
    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(about);
    helpMenu->addAction(aboutQt);
}

void SpreadSheet::createToolBars()
{

    //Crer une bare d'outils
    auto toolbar1 = addToolBar("File");


    //Ajouter des actions acette bar
    toolbar1->addAction(newFile);
    toolbar1->addAction(save);
    toolbar1->addSeparator();
    toolbar1->addAction(exit);


    //Creer une autre tool bar
    auto toolbar2  = addToolBar("ToolS");
    toolbar2->addAction(goCell);
    auto toolbar3  = addToolBar("ToolS");
    toolbar3->addAction(find);
}

void SpreadSheet::updateStatusBar(int row, int col)
{
    QString cell{"(%0, %1)"};
   cellLocation->setText(cell.arg(row+1).arg(col+1));

}

void SpreadSheet::makeConnexions()
{

    // --------- Connexion for the  select all action ----/
    connect(all, &QAction::triggered,
            spreadsheet, &QTableWidget::selectAll);

    // Connection for the  show grid
    connect(showGrid, &QAction::triggered,
            spreadsheet, &QTableWidget::setShowGrid);

    //Connection for the exit button
    connect(exit, &QAction::triggered, this, &SpreadSheet::close);

    //connectting the chane of any element in the spreadsheet with the update status bar
    connect(spreadsheet, &QTableWidget::cellClicked, this,  &SpreadSheet::updateStatusBar);

    //connnetthe  gocell action
    connect(goCell, &QAction::triggered, this, &SpreadSheet::goCellSlot);

    //connnet the find action
    connect(find, &QAction::triggered, this, &SpreadSheet::findSlot);

    //connnet the savefile action
    connect(save,&QAction::triggered,this,&SpreadSheet::saveSlot);

    //connnet the saveAsfile action
    connect(saveAs,&QAction::triggered,this,&SpreadSheet::saveasslot);

    //connnet the newfile action
    connect(newFile,&QAction::triggered,this,&SpreadSheet::newfileslot);

    //connect the openfile action
    connect(open,&QAction::triggered,this,&SpreadSheet::loadslot);

    //connect the copy action
    connect(copy,&QAction::triggered,this,&SpreadSheet::copyslot);

    //connect the cut action
    connect(cut,&QAction::triggered,this,&SpreadSheet::cutslot);

    //connect the paste action
    connect(paste,&QAction::triggered,this,&SpreadSheet::pasteslot);

    //connect the delete action
    connect(deleteAction,&QAction::triggered,this,&SpreadSheet::deleteslot);

    //connect the select row
    connect(row,&QAction::triggered,this,&SpreadSheet::selectrowslot);

    //connect the select col
    connect(Column,&QAction::triggered,this,&SpreadSheet::selectrcolslot);

    //connect the about-Qt
    connect(aboutQt,&QAction::triggered,this,&SpreadSheet::aboutqtslot);

    //connect the about
    connect(about,&QAction::triggered,this,&SpreadSheet::aboutslot);


}

void SpreadSheet::goCellSlot()
{
    //Creating the dialog
    GoCell D;

    //Executing the dialog and storing the user response
    auto reply = D.exec();

    //Checking if the dialog is accepted
    if(reply == GoCell::Accepted)
    {

        //Getting the cell text
        auto cell = D.cell();

        //letter distance
        int row = cell[0].toLatin1() - 'A';
        cell.remove(0,1);

        //second coordinate
        int col =  cell.toInt();


        //changing the current cell
        spreadsheet->setCurrentCell(row, col-1);
    }
}
void SpreadSheet::findSlot()
{

    FindDialog f;
     auto reply = f.exec();
     if(reply == FindDialog::Accepted)
     {

         auto cellfield = f.textfield();

   for(int i=0;i<spreadsheet->rowCount();i++)
   {
       for(int j=0;j<spreadsheet->columnCount();j++)
       {
           if(spreadsheet->item(i,j))
           {
                if(spreadsheet->item(i,j)->text()==cellfield)
                      spreadsheet->setCurrentCell( i,  j);
           }
       }
   }
 }
}


void  SpreadSheet::saveSlot()
{
    if(!currentFile)
    {
        QFileDialog D;
        auto filename =D.getSaveFileName();
        currentFile=new QString(filename);
        setWindowTitle(*currentFile);
//        QMessageBox::information(this,"title","you choosed this-_-"+filename);
    }


    saveContent(*currentFile);


}

void SpreadSheet::saveContent(QString filename)
{
    QFile file(filename);

     if(file.open(QIODevice::WriteOnly))
     {
         QTextStream out(&file);
         for(int i=0;i<spreadsheet->rowCount();i++)
         {
             for(int j=0;j<spreadsheet->columnCount();j++)
             {
                 auto cell = spreadsheet->item(i,j);
                 if(cell)
                 {
                     out  << cell->text() << ",";
                 }

             }
              out<< Qt::endl;
         }
     }

    if(files.length()==5)
    {
        int c=0;
       for(int i=0;i<files.length();i++)
       {
           if(filename==files[i]->text())
           {
               c+=i;
           }
       }
       if(c==0)
       {
           files.pop_back();
           files.push_front(new QAction(filename));

       }
       else
       {
           files.move(c,0);

       }
        recentfile->clear();
        recentfile->addActions(files);
        for(int i=0; i <files.size(); i++)
            connect(files[i],&QAction::triggered,this,&SpreadSheet::openrecentfilesslot);
    }

     if(files.length()>=0&&files.length()<5)
    {
         int c=-1;
        for(int i=0;i<files.length();i++)
        {
            if(filename==files[i]->text())
            {
                c=i;
            }
        }
        if(c==-1)
        {
            files.push_front(new QAction(filename));
        }
        else
        {
            files.move(c,0);

        }

     }
     recentfile->clear();
     recentfile->addActions(files);
     for(int i=0; i <files.size(); i++)
         connect(files[i],&QAction::triggered,this,&SpreadSheet::openrecentfilesslot);


    file.close();

}
void SpreadSheet::loadContent(QString filename)
{

    for(int i=0;i<spreadsheet->rowCount();i++)
    {
        for(int j=0;j<spreadsheet->columnCount();j++)
        {
            auto cell = spreadsheet->item(i,j);
            if(cell)
            {
                cell->setText("");
            }
        }
    }



    QFile file(filename);

    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        int row=0;
        while(!in.atEnd())
        {
            int col=0;
            QString line;
            line=in.readLine();
             auto tokens=line.split(QChar(','));
             for(QString s:tokens)
             {
                 auto cell = new QTableWidgetItem(s);
                 spreadsheet->setItem(row,col,cell);
                 col++;
             }
             row++;
        }
    }
}


void SpreadSheet::loadslot()
{
    QFileDialog d;
    auto filen = d.getOpenFileName();
    currentFile=new QString(filen);
    setWindowTitle(*currentFile);
    loadContent(filen);
}

void SpreadSheet::cutslot()
{
    auto cell = spreadsheet->item(spreadsheet->currentRow(),spreadsheet->currentColumn());
    QString cellc =cell->text();
    clipboard->setText(cellc);
    cell->setText("");

}
void SpreadSheet::pasteslot()
{
    QString text = clipboard->text();
    auto  cell = spreadsheet->item(spreadsheet->currentRow(),spreadsheet->currentColumn());

      if(!cell)
      {
          cell = new QTableWidgetItem((text));
          spreadsheet->setItem(spreadsheet->currentRow(),spreadsheet->currentColumn(),cell);
      }


     cell->setText(text);
}

void SpreadSheet::deleteslot()
{

    int selcol = spreadsheet->currentColumn();
    int selrow = spreadsheet->currentRow();

    auto cell = spreadsheet->item(selrow,selcol);

    cell->setText("");
}

void SpreadSheet::copyslot()
{
    auto cell = spreadsheet->item(spreadsheet->currentRow(),spreadsheet->currentColumn());

    QString cellc =cell->text();
    clipboard->setText(cellc);

}
void SpreadSheet::selectrowslot()
{

  int row = spreadsheet->currentRow();

    for(int i=0;i<spreadsheet->columnCount();i++)
    {
        auto  cell = spreadsheet->item(row,i);
        cell =new QTableWidgetItem;
        spreadsheet->setItem(row,i,cell);
        cell->setSelected(true);

    }

}

void SpreadSheet::selectrcolslot()
{

  int col = spreadsheet->currentColumn();

    for(int i=0;i<spreadsheet->rowCount();i++)
    {
        auto  cell = spreadsheet->item(i,col);
        cell =new QTableWidgetItem;
        spreadsheet->setItem(i,col,cell);
        cell->setSelected(true);

    }



}

void SpreadSheet::openrecentfilesslot()
{
    auto action = dynamic_cast<QAction*>(sender());
    if(action)
    {
        QString path = action->text();
        currentFile=new QString(path);
        loadContent(path);
         setWindowTitle(path);
    }
}

void SpreadSheet::newfileslot()
{
    auto newfile = new SpreadSheet;
    newfile->show();
}

void SpreadSheet::aboutqtslot()
{
    QMessageBox::aboutQt(this,"about_QT");
}


void SpreadSheet::aboutslot()
{
    QMessageBox::about(this,"About spreadsheet",abouttext);
}

void SpreadSheet::saveasslot()
{
    if(currentFile)
    {
        QFileDialog D;
        auto filename =D.getSaveFileName();
        currentFile=new QString(filename);
        setWindowTitle(*currentFile);
        saveContent(*currentFile);
    }


}

