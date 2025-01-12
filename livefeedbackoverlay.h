#ifndef LIVEFEEDBACKOVERLAY_H
#define LIVEFEEDBACKOVERLAY_H

#include <QMainWindow>

namespace Ui {
class LiveFeedbackOverlay;
}

class QSettings;

namespace Yate {
class LiveFeedbackOverlay : public QMainWindow
{
    Q_OBJECT

public:
    explicit LiveFeedbackOverlay(QWidget *parent = nullptr);
    ~LiveFeedbackOverlay();

private slots:
    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);
    void mouseReleaseEvent(QMouseEvent *evt);
    void mouseDoubleClickEvent(QMouseEvent *event);
public slots:
    void onUpdateMessage(QString msg);

signals:
    void onDoubleClicked();

protected:
    void showEvent(QShowEvent *evt);

private:
    Ui::LiveFeedbackOverlay *ui;
    QPointF oldPos_;
    bool isMoving_;
    QSettings *settings_;
};
}
#endif // LIVEFEEDBACKOVERLAY_H
