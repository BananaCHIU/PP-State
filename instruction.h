#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class Instruction;
}

class Instruction : public QWidget
{
    Q_OBJECT

public:
    explicit Instruction(QWidget *parent = nullptr);
    ~Instruction();

private:
    Ui::Instruction *ui;
    QPushButton* btn_back;
private slots:
    void handleBackButton();
};

#endif // INSTRUCTION_H
