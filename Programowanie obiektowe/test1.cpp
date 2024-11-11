/*
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

*/

/*

#include <iostream>
#include <cstring>


class Rocket 
{
public:
    virtual void showInfo() = 0;
    virtual ~Rocket() {}

};


class Technical_data : public Rocket 
{
private:
    std::string name;
    int ProductionYear;
    int length;
    int width;
    std::string Fuel;
    char* seats;


public:
    Technical_data (const std::string& _name, const int _ProductionYear, const int _length, const int _width, const std::string& _Fuel, const char* _seats) : name(_name), ProductionYear(_ProductionYear), length(_length), width(_width), Fuel(_Fuel)
    {
        seats = new char[strlen(_seats)+1];
        strcpy(seats, _seats);
    }

    ~Technical_data()
    {
        delete [] seats;
    }

    Technical_data(const Technical_data& source) : name(source.name), ProductionYear(source.ProductionYear),length(source.length), width(source.width), Fuel(source.Fuel)
    {
        seats = new char[strlen(source.seats)+1];
        strcpy(seats, source.seats);
    }

    Technical_data& operator =( const Technical_data &source )
    {
        if (this != &source)
        {
            name = source.name;
            ProductionYear = source.ProductionYear;
            length = source.length;
            width = source.width;
            Fuel = source.Fuel;
            delete [] seats;
            seats = new char[strlen(source.seats)+1];
            strcpy(seats, source.seats);
        }
        return *this;
    }

    const int area()
    {
        return length * width;
    }

    friend std::ostream& operator<<(std::ostream& out, const Technical_data &other )
    {
        out << "name: "<< other.name << "\nProduction Year: "<< other.ProductionYear << "\nlength: " << other.length << "\nwidth: " << other.width << "\nFuel: "<< other.Fuel << "\nSeats: " << other.seats << std::endl;
        return out;
    }

    bool operator == (const Technical_data& source) const
    {
        return name==source.name && ProductionYear==source.ProductionYear && length==source.length && width==source.width && Fuel==source.Fuel && strcmp(seats,source.seats)==0;
    }

    virtual void showInfo()override
    {
        std::cout<<"\nSpecification about this Rocket: \n" <<*this<<std::endl;
    }

};



int main()
{
    Technical_data rakieta1("Elafi",1998,24,5,"liquid hydrogen","6");
    rakieta1.showInfo();

    Technical_data rakieta2("Baggi",1943,53,2,"rocket-grade","2");
    rakieta2.showInfo();

    Technical_data rakieta3("Funfo",2004,16,32,"LOX","4");
    rakieta3.showInfo();

        if (rakieta1==rakieta2)
    {
        std::cout<<"są takie same" << std::endl;
    }
    else
    {
        std::cout << "są rózne" << std::endl;
    }

    rakieta1 = rakieta2;
    rakieta1.showInfo();

    int areaR = rakieta3.area();
    std::cout <<"Area of rakieta3: " << areaR <<std::endl;

    Technical_data rakieta4 = rakieta3;
    rakieta4.showInfo();

    if (rakieta1==rakieta2)
    {
        std::cout<<"są takie same" << std::endl;
    }
    else
    {
        std::cout << "są rózne" << std::endl;
    }

    Rocket* ptr = &rakieta3;
    ptr -> showInfo();

    return 0;
}

*/


#include <iostream>
#include <cstring>
#include <cmath>

class TV 
{
//static int unique_id;
public:
    virtual void showInfo() = 0;
    virtual ~TV() {};
};

class Params : public TV 
{
private:
    int height;
    int length;
    std::string brand;
    char* energyCategory;

public:
    Params(const int _height, const int _length, const std::string& _brand, const char* _energyCategory) : height(_height), length(_length), brand(_brand)
    {
        energyCategory = new char [strlen(_energyCategory)+1];
        strcpy(energyCategory, _energyCategory);
    }

    ~Params() 
    {
        delete [] energyCategory;
    }

    Params(const Params& soruce) : height(soruce.height), length(soruce.length), brand(soruce.brand)
    {
        energyCategory = new char [strlen(soruce.energyCategory)+1];
        strcpy(energyCategory, soruce.energyCategory);
    }

    Params& operator=(const Params& source)
    {
        if (this !=&source)
        {
            height=source.height;
            length=source.length;
            brand=source.brand;
            delete [] energyCategory;
            energyCategory = new char[strlen(source.energyCategory)+1];
            strcpy(energyCategory, source.energyCategory);
        }
        return *this;
    }

    const double diagonal()
    {
        double result = std::sqrt(length * length + height * height);
        double inch = result / 2.54;
        return inch ;
    }
    
    friend std::ostream& operator<<(std::ostream& out, const Params &other)
    {
        out << "\n wysokość: "<<other.height<< "\n długość: "<< other.length <<"\n marka: "<<other.brand<< "\n Kategoria Energii: "<<other.energyCategory<<std::endl;
        return out;
    }

    bool operator==(const Params& source)
    {
    return length==source.length && height==source.height && brand==source.brand && strcmp(energyCategory, source.energyCategory)==0;
    }


    virtual void showInfo()override
    {
        std::cout << "Information of your TV: \n" << *this << std::endl;
    }

};

//int Params::unique_id=123;

int main()
{
    Params telewizor1(10,20,"samsung","A");
    telewizor1.showInfo();
    
    int inches = telewizor1.diagonal();
    std::cout<<"\n Telewizor1 ma tyle cali: " << inches <<std::endl;

    Params telewizor2(32,50,"sfdsgng","B");
    telewizor2.showInfo();

    Params telewizor3(20,53,"samdsadsung","C");
    telewizor3.showInfo();

    telewizor1=telewizor3;
    telewizor1.showInfo();

    if(telewizor1==telewizor2)
    {
        std::cout<<"tv1 i tv2 są takie same"<<std::endl;
    }
    else
    {
        std::cout<<"tv1 i tv2 nie są takie same"<<std::endl;
    }

    Params telewizor4 = telewizor2;
    telewizor4.showInfo();

    TV *ptr = &telewizor4;
    ptr->showInfo();

    return 0;
}