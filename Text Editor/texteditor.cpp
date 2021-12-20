#include "texteditor.h"
#include "ui_texteditor.h"
#include <QPlainTextEdit>
#include <QTextCursor>
#include <QClipboard>
#include <QMessageBox>
#include <iostream>
#include <QFileDialog>
#include <QTextStream>




TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TextEditor)
{
    ui->setupUi(this);
    currentFile=nullptr;

    setWindowTitle("Untitled - Text Editor");
    setWindowIcon(QIcon(":/text-editor-icon-4.jpg"));
    connect(ui->plainTextEdit,&QPlainTextEdit::copyAvailable,this,&TextEditor::textSelected);

}

TextEditor::~TextEditor()
{
    delete ui;
}


void TextEditor::textSelected(bool isselected)
{
    if (isselected){
        ui->actionCut->setEnabled(true);
        ui->actionCopy->setEnabled(true);
   }
}



void TextEditor::on_actionNew_triggered()
{

    auto newfile = new TextEditor;
    newfile->show();

}
void TextEditor::saveContent(QString filename)
{
    QFile file(filename);

    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);

                    out  << ui->plainTextEdit->toPlainText();
        }

    file.close();



}
void TextEditor::loadContent(QString filename)
{

    QFile file(filename);

    if(file.open(QIODevice::ReadOnly))
    {
           QTextStream in(&file);
           QString text;

           while(!in.atEnd())
           {
               QString line;
               line=in.readLine();
               text+=line;
               text+="\n";
           }


           ui->plainTextEdit->setPlainText(text);


    }
}

void TextEditor::on_actionOpen_triggered()
{
    QFileDialog d;
    auto filen = d.getOpenFileName();
    currentFile=new QString(filen);
    setWindowTitle(*currentFile);
    loadContent(filen);

}
void TextEditor::on_actionSave_triggered()
{
    if(!currentFile)
    {
        QFileDialog D;
        auto filename =D.getSaveFileName();
        currentFile=new QString(filename);
        setWindowTitle(*currentFile);
    }
     saveContent(*currentFile);

}

void TextEditor::on_actionSave_As_triggered()
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
void TextEditor::on_action_About_triggered()
{
    QMessageBox::about(this,"About Text Editor",text);

}

void TextEditor::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this,"about_QT");

}
