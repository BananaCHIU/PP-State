#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QPushButton>
#include <QtMultimedia>
#include <QtMultimediaWidgets>

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
    QMediaPlayer *music;
private slots:
    void handleButton();
};

#endif // MENU_H
