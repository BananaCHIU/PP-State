#include "instruction.h"
#include "ui_instruction.h"
#include <QPushButton>

Instruction::Instruction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Instruction)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    //Background Image
    QPixmap bkgnd(":images/res/bg.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    //back button
    btn_back = new QPushButton(this);
    QPixmap img_back(":images/res/btn_back.png");
    img_back = img_back.scaled(200, 60, Qt::KeepAspectRatio, Qt::FastTransformation);
    QIcon backIcon(img_back);
    btn_back->setIcon(backIcon);
    btn_back->setIconSize(img_back.rect().size());
    // set size and location of the button
    btn_back->setGeometry(this->size().width()/2 - img_back.rect().size().width()/2, this->size().height() - 125, img_back.rect().size().width(), img_back.rect().size().height());
    // Connect button signal to appropriate slot
    connect(btn_back, SIGNAL (released()), this, SLOT (handleBackButton()));
}

Instruction::~Instruction()
{
    delete btn_back;
    delete ui;

}

void Instruction::handleBackButton(){
    close();
}
