#include "../headers/ColoredSquare.h"
#include "qpainter.h"
namespace Tetris {
        void ColoredSquare::setColor(QColor color) {
            m_color = color;
            update();
        }
        void ColoredSquare::paintEvent(QPaintEvent *event){
            QPainter painter(this);
            painter.fillRect(rect(), m_color);
        }
}
