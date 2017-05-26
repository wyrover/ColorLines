#include "ColorLinesMultigameWidget.h"

#include <assert.h>

#include <QHBoxLayout>

#include "Lines/ColorLinesBuilder.h"
#include "Snake/SnakeGameBuilder.h"
#include "Tetris/TetrisGameBuilder.h"

ColorLinesMultigameWidget::ColorLinesMultigameWidget(QWidget *parent)
    : QWidget(parent),
      gameWidget(NULL)
{
    QHBoxLayout *lay = new QHBoxLayout;
    setLayout(lay);

    menuWidget = new MenuWidget;
    lay->addWidget(menuWidget);
    connect(menuWidget, SIGNAL(runColorLines()), this, SLOT(runColorLines()));
    connect(menuWidget, SIGNAL(runSnake()), this, SLOT(runSnake()));
    connect(menuWidget, SIGNAL(runTetris()), this, SLOT(runTetris()));

    layout()->setMargin(0);
}

ColorLinesMultigameWidget::~ColorLinesMultigameWidget()
{
}

void ColorLinesMultigameWidget::runGame(AbstractGameBuilder *builder)
{
    assert(gameWidget == NULL);

    menuWidget->hide();

    {
        AbstractColorLinesGame *game;
        builder->createGame(game, gameWidget);
        this->game = QSharedPointer<AbstractColorLinesGame>(game);
    }

    gameWidget->setFocus();
    layout()->addWidget(gameWidget);
}


void ColorLinesMultigameWidget::keyPressEvent(QKeyEvent *e)
{
    e->ignore();
}

void ColorLinesMultigameWidget::keyReleaseEvent(QKeyEvent *e)
{
    e->ignore();
}

void ColorLinesMultigameWidget::runColorLines()
{

    ColorLinesBuilder b;
    runGame(&b);
}

void ColorLinesMultigameWidget::runSnake()
{
    SnakeGameBuilder b;
    runGame(&b);

}

void ColorLinesMultigameWidget::runTetris()
{
    TetrisGameBuilder b;
    runGame(&b);
}