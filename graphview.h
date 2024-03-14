#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsView>

class GraphView : public QGraphicsView {
public:
    GraphView(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // GRAPHVIEW_H
