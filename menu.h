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
    Menu(bool state = 0,QWidget *parent = nullptr);

    ~Menu();

private:
    Ui::Menu *ui;
    QPushButton *btn_play;
    QPushButton *btn_ins;
    QPushButton *btn_quit;
    QMediaPlayer *music;
    QMovie *movie {nullptr};
    QLabel *processLabel {nullptr};

    void createMenu();

private slots:
    void handlePlayButton();
    void handleInsButton();
    void handleQuitButton();
};

#endif // MENU_H
