#include <iostream>
#include <cstring>


class esp32_with_screen {
public:
    virtual void showInfo()=0;
    virtual ~esp32_with_screen() {}

};

class Params : public esp32_with_screen 
{
static int unique_id;
private:
    int width;
    int length;
    std::string model;
    char* energyCategory;

public:
    Params (const int &_width, const int &_lenght, const std::string _model, const char* _energyCategory) : length(_lenght), width(_width), model(_model) 
    {
        energyCategory = new char[strlen(_energyCategory)+1];
        strcpy(energyCategory, _energyCategory);
    }

    ~Params() 
    {
        delete [] energyCategory;
    }

    Params (const Params &source) : length(source.length), width(source.width), model(source.model) 
    {
        energyCategory = new char[strlen(source.energyCategory)+1];
        strcpy(energyCategory, source.energyCategory);
    }

    Params& operator = (const Params& source)
    {
        if(this !=&source)
        {
            length = source.length;
            width = source.width;
            model = source.model;
            delete [] energyCategory;
            energyCategory = new char[strlen(source.energyCategory)+1];
            strcpy(energyCategory, source.energyCategory);
        }
        return *this;

    }

    const int esp_area()
    {
        return length * width;
    }

    friend std::ostream& operator <<(std::ostream&  out, const Params &other )
    {
        out << "Length: " <<other.length<< "\nwidth: " <<other.width<< "\nmodel: " <<other.model<< "\nenergy Category: "<<other.energyCategory<< std::endl;
        return out; 
    }

    bool operator==(const Params &source) const 
    {
        return length == source.length && width == source.width && model == source.model && strcmp(energyCategory, source.energyCategory)==0;
    }

    virtual void showInfo()override
    {
        std::cout << "Information of this esp: \n";
        std::cout <<*this<<std::endl;
    }

};

int Params::unique_id=10;

int main ()
{
    Params esp1(10,20,"esp32_OLED_LCD","C");
    esp1.showInfo();
    Params esp2(15,5,"esp8266","A");
    esp2.showInfo();
    Params esp3(30,50,"espD1_mini", "B");
    esp3.showInfo();

    int area = esp2.esp_area();
    std::cout <<"Area of esp2: " << area <<std::endl;

    esp1 = esp2;
    std::cout << "Operator przypisania (głeboka kopia) esp1 ma teraz parametry esp2: \n" << esp1 <<std::endl;

    Params esp4 = esp3;
    std::cout << "stworzyliśmy nowy obiekt esp4 który ma dane po esp3: \n" << std::endl;
    esp4.showInfo();

    std::cout << "Operator porównania esp1 z esp2 \n" << std::endl;
    if (esp1 == esp2)
    {
        std::cout << "Są takie same \n" << std::endl;
    }
    else
    {
        std::cout << "Nie są takie same \n" << std::endl;
    }

    std::cout << "Test polimorfizmu: " << std::endl;
    esp32_with_screen* ptr = &esp3;
    ptr -> showInfo();


    return 0;
}