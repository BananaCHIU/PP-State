#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private:
    Ui::Menu *ui;
    QPushButton *m_button;
private slots:
    void handleButton();
};

#endif // MENU_H
