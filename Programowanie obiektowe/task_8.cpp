#include <iostream>
#include <string>

class Media
 {
private:
std::string filename;

public:
    Media(const std::string& _filename) : filename(_filename){}

const std::string& getFilename() const
{
    return filename;
}

virtual void play() = 0;
virtual void pause() = 0;

virtual ~Media() = default;
 };

class AudioPlayer : virtual public Media
{
public:
    AudioPlayer(const std::string& _filename) : Media(_filename) 
    {}

    void play() override 
    {
        std::cout << "AudioPlayer start playing: " << getFilename() << std::endl; 
    }

    void pause() override
    {
        std::cout << "AudioPlayer is paused: " << getFilename() << std::endl;
    }

    void setVoluume()
    {
        std::cout << "AudioPlayer is setting voluume: " << getFilename() << std::endl;
    }

};


class VideoPlayer : virtual public Media
{
public:
    VideoPlayer(const std::string& _filename) : Media(_filename) 
    {}
void play() override 
{
    std::cout << "AudioPlayer start playing: " << getFilename() << std::endl; 
}

void pause() override
{
    std::cout << "AudioPlayer is paused: " << getFilename() << std::endl;
}

void setBrightness()
{
        std::cout << "VideoPlayer is setting brightness: " << getFilename() << std::endl;
}

};

#include <iostream>
#include <string>

class Media
 {
private:
std::string filename;

public:
    Media(const std::string& _filename) : filename(_filename)
    {}

const std::string& getFilename() const
{
    return filename;
}

virtual void play() = 0;
virtual void pause() = 0;

virtual ~Media() = default;
 };

class AudioPlayer : virtual public Media
{
public:
    AudioPlayer(const std::string& _filename) : Media(_filename) 
    {}

    void play() override 
    {
        std::cout << "AudioPlayer start playing: " << getFilename() << std::endl; 
    }

    void pause() override
    {
        std::cout << "AudioPlayer is paused: " << getFilename() << std::endl;
    }

    void setVoluume()
    {
        std::cout << "AudioPlayer is setting voluume: " << getFilename() << std::endl;
    }

};


class VideoPlayer : virtual public Media
{
public:
    VideoPlayer(const std::string& _filename) : Media(_filename) 
    {}
void play() override 
{
    std::cout << "AudioPlayer start playing: " << getFilename() << std::endl; 
}

void pause() override
{
    std::cout << "AudioPlayer is paused: " << getFilename() << std::endl;
}

void setBrightness()
{
        std::cout << "VideoPlayer is setting brightness: " << getFilename() << std::endl;
}

};



class AVPlayer : public AudioPlayer, public VideoPlayer
{
public:
    AVPlayer(const std::string& _filename) : AudioPlayer(_filename),  VideoPlayer(_filename), Media(_filename){}
    void play() override{
        std::cout << ""
    }







int main()
{
    


    return 0;
}