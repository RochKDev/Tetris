#ifndef TETRIS_GUI_COLOREDSQUARE_H
#define TETRIS_GUI_COLOREDSQUARE_H
#include "qwidget.h"
namespace Tetris {
    class ColoredSquare : public QWidget {
    public:
        ColoredSquare(QWidget *parent = nullptr, QColor color = Qt::white)
                : QWidget(parent), m_color(color) {}

        void setColor(QColor color);
        ~ColoredSquare() = default;

    protected:
        void paintEvent(QPaintEvent *event) override;

    private:
        QColor m_color;
    };
}
#endif //TETRIS_GUI_COLOREDSQUARE_H
