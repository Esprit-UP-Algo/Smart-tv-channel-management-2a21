#include "graphview.h"
#include <QResizeEvent>

GraphView::GraphView(QWidget *parent) : QGraphicsView(parent) {}

void GraphView::resizeEvent(QResizeEvent *event) {
    fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}
