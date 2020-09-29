#include "fireplace.h"
#include <QtGui>
#include <QDebug>

FirePlace::FirePlace(int w, int h)
{
    fireData = new Fire(w, h);
    image = QImage(w, h, QImage::Format_RGB888);
    setColorPallete();
    initWidgets();
    connectWidgets();
    createLayeout();
    timer->start(50);
}

/* This method initializes color table by generating
fire like colors in the HSL space.
Lightness is 0..255 for x=0..128, and 255 for x=128..255*/
void FirePlace::setColorPallete()
{
    colorTable.clear();
    for (int x = 0; x < palleteSize; x++)

        colorTable.push_back((QColor::fromHslF((x / 3) / 255.0, 1, std::min(255, x * 2) / 255.0)).rgb());
}

/* This method can make different palletes depends on color
stops defined by a vector. */
void FirePlace::setColorPallete(const QVector<QRgb>& stops)
{
    colorTable.clear();
    int vectorSize = stops.size() - 1;
    int range = palleteSize / vectorSize;
    int r1, r2, g1, g2, b1, b2;
    double rf, bf, gf;
    for (int i = 0; i < vectorSize; i++) {
        r1 = rf = qRed(stops[i]);
        r2 = qRed(stops[i + 1]);
        g1 = gf = qGreen(stops[i]);
        g2 = qGreen(stops[i + 1]);
        b1 = bf = qBlue(stops[i]);
        b2 = qBlue(stops[i + 1]);
        double rn = (r2 - r1) / double(range);
        double gn = (g2 - g1) / double(range);
        double bn = (b2 - b1) / double(range);
        for (int j = 0; j < range; j++) {
            rf += rn;
            gf += gn;
            bf += bn;
            colorTable.push_back((QColor(rf, gf, bf).rgb()));
        }
    }
}

void FirePlace::initWidgets()
{
    // Label objects
    imageLabel = new QLabel("");
    imageLabel->setStyleSheet("border: 1px solid black");
    decayLabel = new QLabel("Change decay:");
    // Button objects
    quitButton = new QPushButton("Quit");
    startButton = new QPushButton("Start");
    pauseButton = new QPushButton("Pause");
    decayUButton = new QPushButton("+");
    decayDButton = new QPushButton("-");
    rightWindButton = new QPushButton("East Wind");
    leftWindButton = new QPushButton("West Wind");
    noWindButton = new QPushButton("No Wind");
    colorButton = new QPushButton("Try a random color");
    timer = new QTimer(this);
}

void FirePlace::connectWidgets()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerUpdate()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quit()));
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(pause()));
    connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
    connect(decayUButton, SIGNAL(clicked()), this, SLOT(increaseDecay()));
    connect(decayDButton, SIGNAL(clicked()), this, SLOT(decreaseDecay()));
    connect(rightWindButton, SIGNAL(clicked()), this, SLOT(rightWind()));
    connect(leftWindButton, SIGNAL(clicked()), this, SLOT(leftWind()));
    connect(noWindButton, SIGNAL(clicked()), this, SLOT(noWind()));
    connect(colorButton, SIGNAL(clicked()), this, SLOT(chooseRandomPallete()));
}

void FirePlace::createLayeout()
{
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(imageLabel, 0, 0, 1, 3);
    layout->addWidget(startButton, 1, 0);
    layout->addWidget(pauseButton, 1, 1);
    layout->addWidget(quitButton, 1, 2);
    layout->addWidget(decayLabel, 2, 0);
    layout->addWidget(decayUButton, 2, 1);
    layout->addWidget(decayDButton, 2, 2);
    layout->addWidget(rightWindButton, 3, 0);
    layout->addWidget(leftWindButton, 3, 1);
    layout->addWidget(noWindButton, 3, 2);
    layout->addWidget(colorButton, 4, 0, 1, 3);
    setLayout(layout);
    setWindowTitle(tr("Fire Flame Effect"));
}
// Randomly chooses one of the ready pallaetes
void FirePlace::chooseRandomPallete()
{
    QVector<QRgb> stops;
    int randomNum = rand() % 3;
    switch (randomNum) {
    case 0:
        setColorPallete();
        break;
    case 1: // Color effect 1: Black - Red - Green
        stops.push_back((QColor(0, 0, 0).rgb()));
        stops.push_back((QColor(205, 30, 60).rgb()));
        stops.push_back((QColor(40, 161, 58).rgb()));
        stops.push_back((QColor(40, 205, 60).rgb()));
        stops.push_back((QColor(255, 255, 50).rgb()));
        stops.push_back((QColor(255, 255, 0).rgb()));
        stops.push_back((QColor(255, 255, 0).rgb()));
        setColorPallete(stops);
        break;
    case 2: // Color effect 1: Black - Blue - Red
        stops.push_back((QColor(0, 0, 0).rgb()));
        stops.push_back((QColor(107, 212, 215).rgb()));
        stops.push_back((QColor(255, 109, 128).rgb()));
        stops.push_back((QColor(255, 255, 255).rgb()));
        stops.push_back((QColor(255, 255, 255).rgb()));
        stops.push_back((QColor(255, 255, 255).rgb()));
        setColorPallete(stops);
    default:
        break;
    }
}

void FirePlace::quit()
{
    QMessageBox messageBox;
    messageBox.setWindowTitle(tr("Notepad"));
    messageBox.setText(tr("Do you really want to quit?"));
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::No);
    if (messageBox.exec() == QMessageBox::Yes)
        qApp->quit();
}

void FirePlace::pause()
{
    timer->stop();
}
void FirePlace::start()
{
    timer->start(50); // 20 frames per second
}

void FirePlace::onTimerUpdate()
{
    makeFireImg();
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->show();
}

void FirePlace::increaseDecay()
{
    fireData->increaseDecay();
}

void FirePlace::decreaseDecay()
{
    fireData->decreaseDecay();
}

void FirePlace::rightWind()
{
    fireData->setWindDirection(EAST);
}
void FirePlace::leftWind()
{
    fireData->setWindDirection(WEST);
}
void FirePlace::noWind()
{
    fireData->setWindDirection(NOWIND);
}
void FirePlace::makeFireImg()
{
    fireData->startFire();
    fireData->updateFire();
    for (int i = 0; i < fireData->getHeight(); i++)
        for (int j = 0; j < fireData->getWidth(); j++)
            image.setPixel(j, i, colorTable[fireData->getArray(i, j)]);
}
