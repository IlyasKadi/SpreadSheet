#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class TextEditor; }
QT_END_NAMESPACE

class TextEditor : public QMainWindow
{
    Q_OBJECT

public:
    TextEditor(QWidget *parent = nullptr);
    ~TextEditor();

private:
    Ui::TextEditor *ui;
    QString text="It's our version of a Text Editor , a small application for editing plain text.\n"
                                                                                      "That contain some basic tools such as :"
                 "                                                                     cut, copy, past, newfile, openfile save,..";

private:
    QString * currentFile;
    void saveContent(QString filename);
    void loadContent(QString filename);

private slots:
    void textSelected(bool isselected);//to enable cut and copy actions once a text is selected

  private slots:
      void on_actionNew_triggered();
      void on_actionOpen_triggered();
      void on_actionSave_triggered();
      void on_actionSave_As_triggered();
      void on_action_About_triggered();
      void on_actionAbout_Qt_triggered();


};
#endif // TEXTEDITOR_H
