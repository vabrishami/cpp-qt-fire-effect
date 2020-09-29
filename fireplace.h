/***************************************************************************
 * Author:     Vahid Abrishami (vahid.abrishami@helsinki.fi)
***************************************************************************/
#ifndef FIREPLACE_H
#define FIREPLACE_H

#include <QtGui>
#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include "fireflame.h"

/** Class for graphic view of fire flame effect.
    This class includes routines to show the fire, and call fire object 
    routines such as incresing/decreasing decay and speed direction.*/
class FirePlace : public QWidget {
    Q_OBJECT

public:
    FirePlace(int w, int h);

    // Events
private slots:
    // Events for buttons
    void quit();
    void pause();
    void start();
    void onTimerUpdate();
    void increaseDecay();
    void decreaseDecay();
    void rightWind();
    void leftWind();
    void noWind();
    void chooseRandomPallete();

private:
    // Timer for updaing the fire
    QTimer* timer;
    // Fire image to be shown
    QImage image;
    // Fire color pallete
    QVector<QRgb> colorTable;
    // Label to show QImage in
    QLabel* imageLabel;
    // Label objects
    QLabel* decayLabel;
    // Button objects
    QPushButton* quitButton;
    QPushButton* startButton;
    QPushButton* pauseButton;
    QPushButton* decayUButton;
    QPushButton* decayDButton;
    QPushButton* rightWindButton;
    QPushButton* leftWindButton;
    QPushButton* noWindButton;
    QPushButton* colorButton;

    Fire* fireData; // Fire object

    // Methods --------------------------------------------------------- */
    // This method sets the color palletes different than real fire color
    void setColorPallete(const QVector<QRgb>& stops);
    // This method sets the color palletes for real fire color
    void setColorPallete();
    // Method to assign the image array to Qimage (image)
    void makeFireImg();
    // Initialize the objects
    void initWidgets();
    // Connect events to methods
    void connectWidgets();
    void createLayeout();
};
#endif
