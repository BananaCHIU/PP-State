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
    QPushButton *btn_play;
    QPushButton *btn_ins;
    QMediaPlayer *music;

private slots:
    void handlePlayButton();
    void handleInsButton();
};

#endif // MENU_H
