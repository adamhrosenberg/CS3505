#ifndef MODEL_H
#define MODEL_H


/*
 * Alec Adair, Stuart Johnsen, Adam Rosenberg, Darin Stoker
 * 3/25/16
 *
 */
#include <vector>
#include <string>
#include <QImage>
#include <QColor>
#include <QLinearGradient>

class Model
{
public:
    //Variables

    //Functions
    Model(int width, int height);
    Model();
    ~Model();
    int addFrame(int width, int height);
    int amountOfFrames();
    QImage getFrame(int frameIndex);
    void deleteFrame(int frameIndex);
    int getFrameCount();
    int getFrameWidth(int frameIndex);
    int getFrameHeight(int frameIndex);
    void setPixelValueInFrame(int frameIndex, int pixelX, int pixelY,
                                int red, int green, int blue, int alpha);
    QColor getPixelValueInFrame(int frameIndex, int pixelX, int pixelY);
    void saveSSP(std::string filename, std::string filepath);
    bool openSSP(std::string filename, std::string filepath);
    void exportGIF(std::string filename, std::string filepath, int FPS);

private:
    //Variables
    std::vector<QImage> frames;

    //Functions
};

#endif // MODEL_H
