#ifndef GOCELL_H
#define GOCELL_H

#include <QDialog>

namespace Ui {
class GoCell;
}

class GoCell : public QDialog
{
    Q_OBJECT

public:
    explicit GoCell(QWidget *parent = nullptr);
    QString cell() const;

    ~GoCell();

private:
    Ui::GoCell *ui;

};

#endif // GOCELL_H
