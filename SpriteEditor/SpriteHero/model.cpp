#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <QDebug>
#include <QBuffer>
#include <QFileDialog>
#include "model.h"
//#include "Magick++.h"

using namespace std;
//using namespace Magick;

Model::Model(int width, int height){
    addFrame(width, height);    //Add first frame
}

Model::Model(){

}

Model::~Model(){

}

//Creates a new frame, fills the frame with white pixels,
//and adds it to the frames vector. It returns the index of the
//frame that was just added.
int Model::addFrame(int width, int height){
    QImage newFrame(width, height, QImage::Format_ARGB32);
    newFrame.fill(Qt::transparent);
    frames.push_back(newFrame);
    return frames.size()-1;
}

//Returns the frame for any given index.
QImage Model::getFrame(int frameIndex){
    return frames[frameIndex];
}

//Deletes the given frame from the frames vector. If deleting the
//frame would cause the frames vector to be empty, a new empty frame
//is automatically created.
void Model::deleteFrame(int frameIndex){
    int width = getFrameWidth(frameIndex);
    int height = getFrameHeight(frameIndex);
    frames.erase(frames.begin() + (frameIndex - 1));
    if(frames.size() == 0)
        addFrame(width, height);
}

//Returns the number of frames in the frames vector.
int Model::getFrameCount(){
    return frames.size();
}

//Returns the width of the indicated frame.
int Model::getFrameWidth(int frameIndex){
    return frames[frameIndex].width();
}

//Returns the height of the indicated frame.
int Model::getFrameHeight(int frameIndex){
    return frames[frameIndex].height();
}

//Sets the value of the pixel in the indicated frame.
void Model::setPixelValueInFrame(int frameIndex, int pixelX, int pixelY,
                            int red, int green, int blue, int alpha){
    frames[frameIndex].setPixel(pixelX, pixelY, qRgba(red, green, blue, alpha));
}

//Returns the color of the pixel at the indicated position in the indicated frame.
QColor Model::getPixelValueInFrame(int frameIndex, int pixelX, int pixelY){
    return frames[frameIndex].pixel(pixelX, pixelY);
}

//Saves all the frames into a .SSP file. As per the spec, only the width and
//height of the first frame is given, so the other frames are assumed to be
//of the same size, although this is not programatically enforced.
void Model::saveSSP(std::string filename, std::string filepath){
    //Check file extension
    if(filename.find(".ssp")==std::string::npos){
        filename += ".ssp";
    }
    //Fix filepath if needed
    if(filepath.back() != '/' && filepath.size() > 0)
        filepath.append("/");
    string fullFilepath = filepath + filename;
    cout << "Full filepath: " << fullFilepath << endl;

    //Open the file so that is can be filled (create as needed).
    ofstream myFile;
    myFile.open(fullFilepath);
    ostringstream oss;
    oss << getFrameWidth(0);
    oss << " ";
    oss <<getFrameHeight(0);
    oss << "\n";
    oss << frames.size();
    oss << "\n";

    //Fill the file with the sprite data.
    for(int frameIndex = 0; frameIndex < frames.size(); frameIndex++)
    {
        for(int i = 0; i < frames[frameIndex].height(); i++)
        {
            for(int j = 0; j < frames[frameIndex].width(); j++)
            {
                cout << "Pixel: " << hex << frames[frameIndex].pixel(j, i) << endl;
                oss << ((frames[frameIndex].pixel(j, i) >> 16) & 0xff); //Red
                oss << " ";
                oss << ((frames[frameIndex].pixel(j, i) >> 8) & 0xff);  //Green
                oss << " ";
                oss << ((frames[frameIndex].pixel(j, i) >> 0) & 0xff);  //Blue
                oss << " ";
                oss << ((frames[frameIndex].pixel(j, i) >> 24) & 0xff); //Alpha
                if(j+1 < frames[frameIndex].width())    //No spaces at the end of lines
                    oss << " ";
            }
            oss << "\n";    //Newline at the end of a row
        }
    }

    myFile << oss.str();
    myFile.close();
    cout<<"save success"<<endl;
}

//Returns whether or not the file could be opened and parsed. Checks the validity
//of a frame by checking the given dimensions and frame count to make sure that they
//are within the maximum allowed frame count and size.
//
//Will return false if input file could not be parsed. Deletes all frames in model
//and inserts versions from file.
//
//As per the spec, the width and height at the top of the file are assumed to be the
//width and height of every frame. The sizes of the frames are not programatically
//checked and are assumed to be of the correct format.
//
//Checks for invalid file extensions, invalid headers, and non-square image sizing(not allowed).
bool Model::openSSP(std::string filename, std::string filepath){
    int maxWidth = 512;
    int maxHeight = maxWidth;
    int maxFrames = 100;
    string widthStr;
    string heightStr;
    string numFramesStr;

    //Check file extension
    if(filename.find(".ssp")==std::string::npos){
        cout << "Must load file with .ssp file extension." << endl;
        return false;
    }

    //Fix filepath if needed
    if(filepath.back() != '/' && filepath.size() > 0)
        filepath.append("/");

    //Delete all frames
    frames.clear();

    //Read in file
    string fullFilepath =  filepath + filename;
    ifstream myFile(fullFilepath);
    if(myFile.is_open()) {
        getline(myFile, widthStr, ' ');
        getline(myFile, heightStr);
        getline(myFile, numFramesStr);
    }
    else {
        cout << "File didn't open correctly." << endl;
        return false;   //File didn't open correctly
    }

    if(widthStr.size() <= 0 || heightStr.size() <= 0 || numFramesStr.size() <= 0){
        cout << "Invalid input." << endl;
        return false;   //Invalid input
    }

    int width = atoi(widthStr.c_str());
    int height = atoi(heightStr.c_str());
    int numFrames = atoi(numFramesStr.c_str());

    cout << "width: "<< width << endl;
    cout << "height: " << height << endl;
    cout << "numFrames:: " << numFrames << endl;

    if(width > maxWidth || height > maxHeight || numFrames > maxFrames || width != height){
        cout << "Incorrect sizing" << endl;
        return false;   //Incorrect sizing
    }

    //Read in the pixel values
    if(myFile.is_open()) {
        for(int frameNumber = 0; frameNumber < numFrames; frameNumber++){
            int frameIndex = addFrame(width, height);
            cout << "Frame Count: " << getFrameCount()<< endl;
            for(int lineNumber = 0; lineNumber < height; lineNumber++){
                string line;

                getline(myFile, line);
                stringstream ss(line);

                string redStr;
                string greenStr;
                string blueStr;
                string alphaStr;

                int red;
                int green;
                int blue;
                int alpha;

                for(int pixelSet = 0; pixelSet < width; pixelSet++){
                    ss >> redStr;
                    ss >> greenStr;
                    ss >> blueStr;
                    ss >> alphaStr;

                    red = atoi(redStr.c_str());
                    green = atoi(greenStr.c_str());
                    blue = atoi(blueStr.c_str());
                    alpha = atoi(alphaStr.c_str());

                    // cout << red << endl;
                    // cout << green << endl;
                    // cout << blue << endl;
                    // cout << alpha << endl;

                    setPixelValueInFrame(frameIndex, pixelSet, lineNumber,
                                            red, green, blue, alpha);
                }
            }
        }
        cout << "Finished load from file." << endl;
    }
    else
        return false;
    cout << "Success!" << endl;
    return true;    //Success!
}
int Model::amountOfFrames(){
    return frames.size();
}
void Model::exportGIF(string filename, string filepath, int FPS){
//    if(filename.find(".gif")==std::string::npos){
//        filename += ".gif";
//    }
//    if(filepath.back() != '/' && filepath.size() > 0)
//        filepath.append("/");
//    string fullFilepath = filepath + filename;

//    cout << "Full filepath: " << fullFilepath << endl;
//    vector<Image> gifFrames;

//    QByteArray ba;
//    QBuffer buffer(&ba);
//    buffer.open(QIODevice::ReadWrite);
//    for(unsigned int i = 0; i < frames.size(); i++)
//    {
//        frames[i].save(&buffer, "PNG");
//        Blob blob(buffer.data(), buffer.size());
//        Image image;
//        image.read(blob);
//        // 60 FPS / 100 ticks/sec = 1 frame / 600 ticks
//        // 3 frames / 5 ticks -> 1 frame per 5/3 ticks
//        double secondsPerFrame = 100*(1 / FPS);
//        image.animationDelay(secondsPerFrame);
//        gifFrames.push_back(image);
//        buffer.reset();
//    }
//    for_each (gifFrames.begin(), gifFrames.end(), gifDisposeMethodImage(2));

//    writeImages(gifFrames.begin(), gifFrames.end(), fullFilepath);
}
