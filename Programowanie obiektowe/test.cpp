#include <iostream>

class Animal {
public:
    virtual void Sound() const = 0;
    virtual ~Animal() {} 
};


class Dog : public Animal {
private:
std::string *name;

public:
    Dog(const std::string &name) : name(new std::string(name)) {}
    Dog(const Dog &other) : name(new std::string(*other.name)) {}
    Dog& operator=(const Dog &other)
    {
        if (this != &other) 
        {
            delete name;
            name = new std::string(*other.name);
        }
        return *this;
    }



    ~Dog() {delete name;}

};




int main() {




    return 0;
}


//****************************************//


#include <iostream>
#include <cstring>

class Console{
public:
    Console(const char* _serialNumber) {
        int length;
        length = strlen(_serialNumber);
        serialNumber = new char[length+1];
        strcpy(serialNumber, _serialNumber);
    };

    Console(const Console& other){
        std::cout << "Constructor copy" << std::endl;
        int length = strlen(other.serialNumber);
        serialNumber = new char[length+1];
        serialNumber = other.serialNumber;
        
    };

    ~Console(){
        delete[] serialNumber;
        std::cout << "Destroyer" << std::endl;
    };

    Console& operator=(const Console& other){
        if(this == &other){
            return *this;
        }
        int length = strlen(other.serialNumber);
        delete[] serialNumber;
        serialNumber = new char[length+1];
        strcpy(serialNumber, other.serialNumber);



    }

    virtual const void Information()=0;

protected:
    char*  serialNumber;
};


class Portable : public Console{
public:
    Portable(bool _bluray, int _disk,const std::string& _brand,const char* _serialNumber) : bluray(_bluray), disk(_disk), brand(_brand), Console(_serialNumber){};
    Portable(const Portable& other ) : Console(other){
        this->bluray = other.bluray ;
        this->disk = other.disk;
        this->brand = other.brand;
        std::cout<<"Kontruktor kopiujący"<<std::endl << std::endl;
    }
    void addBluRay(){
        this->bluray = true;
        std::cout<<"BluRay has just added"<<std::endl << std::endl;;

    }

    const void Information() override{
        std::cout << "Brand: " << brand << std::endl;
        std::cout << "Serial Number: " << Console::serialNumber << std::endl;
        std::cout << "Disk Size: " << disk << " GB" << std::endl;
        if (bluray) {
            std::cout << "This console has a BluRay" << std::endl << std::endl;
        } else {
            std::cout << "This console does not have a BluRay" << std::endl <<std::endl;
        }
    }

private:
    bool bluray;
    int disk;
    std::string brand;

};


int main(){
    Portable p(false, 1000, "sony", "n4kj32n4");
    Portable d(true, 150, "micro", "n4kj32n4");
    std::cout << "KUTAS KOZLA" << std::endl;
    Portable j(p);
    std::cout << "Object j copied argument from p" << std::endl;
    j.Information();
    p.Information();
    std::cout << "kUTAS KOZLA" << std::endl;
    d.Information();
    p = d;
    std::cout << "kUTAS KOZLA" << std::endl;
    p.Information();
    
    


    return 0;
}



//*******************************************//



#include <cstring>
#include <iostream>

class Microwave
{
public:
    virtual void showInfo()=0;
    virtual ~Microwave(){};

};

class Params : public Microwave
{
public:
    static int unique_id;
    Params(const int &_lenght, const int &_width, const std::string _name, const char* _energyCategory ):lenght(_lenght), width(_width),name(_name)
    {
        enegryCategory = new char[strlen(_energyCategory)+1];
        strcpy(enegryCategory,_energyCategory);
    }
    ~Params()
    {
        delete [] enegryCategory;
    }

    Params(const Params &source):lenght(source.lenght),width(source.width), name(source.name)
    {
        enegryCategory = new char[strlen(source.enegryCategory)+1];
        strcpy(enegryCategory,source.enegryCategory);  
    }

//_zwracany_typ_ & operator = ( const typ & );

    Params& operator=(const Params& source)
    {
        if(this != &source)
        {
            lenght = source.lenght;
            width = source.width;
            name = source.name;
            delete [] enegryCategory;
            enegryCategory = new char[strlen(source.enegryCategory)+1];
            strcpy(enegryCategory,source.enegryCategory);

        }
        return *this;
    } 

    const int  screenFielied()
    {
        int screen = lenght * width;
        return screen;
    }

    friend std::ostream& operator<<(std::ostream& out,const Params &other)
    {
        out<<"Lenght: "<<other.lenght<<" Width : "<<other.width<<" Name: "<<other.name<< " Energy category: "<<other.enegryCategory<<std::endl;
        return out;
    }

    bool operator==(const Params &source)const
    {
        return lenght == source.lenght && width == source.width && name == source.name && strcmp(enegryCategory, source.enegryCategory)==0 ;
    }

    virtual void showInfo()override
    {
        std::cout<<"Info about your microfala: \n";
        std::cout<<*this<<std::endl;
    }



private:
    int lenght;
    int width;
    std::string name;
    char* enegryCategory;        

};

int Params::unique_id = 1245;



int main()
{

    Params mikrofala(20,30,"niggerTrigger","A");
    mikrofala.showInfo();

    Params mikrofala_2(40,30,"pozdro","C");
    std::cout<<"Mikrofala przed kopią";
    mikrofala_2.showInfo();

    //Operator przypisania "=" , głębokie kopie
    std::cout<<"Mikrofala po kopii: ";
    mikrofala_2 = mikrofala;
    mikrofala_2.showInfo();

    //Konstruktor kopiujący 
    Params mikrofala_3 = mikrofala_2;
    std::cout<<"Mikrofala III ma parametry mikrofali II która ma parametry mikrofali I : ";
    mikrofala_3.showInfo();
    
    //operator porównania

    if(mikrofala == mikrofala_2)
    {
        std::cout<<"Są takie same";
        return true;
    }else
    {
        std::cout<<"Nie są takie same";
        return false;
    }

    //Test polimorfizm 
    std::cout<<"Moja mikrofala polimorficzna";
    Microwave* ptr = &mikrofala;
    ptr->showInfo();

    return 0;
}




//***************************************************//


#include <cstring>
#include <iostream>

class Sensor
{
public:
    virtual void showInfo() = 0;
    virtual ~Sensor() {};
};

class Params : public Sensor
{
public:
    static std::string date;

    Params(const unsigned int &_hpa, const int &_temp, const char* _categoryOfFall, const std::string &_cloudiness)
        : hpa(_hpa), temp(_temp), cloudiness(_cloudiness)
    {
        categoryOfFall = new char[strlen(_categoryOfFall) + 1];
        strcpy(categoryOfFall, _categoryOfFall);
    }

    Params(const Params &source)
        : hpa(source.hpa), temp(source.temp), cloudiness(source.cloudiness)
    {
        categoryOfFall = new char[strlen(source.categoryOfFall) + 1];
        strcpy(categoryOfFall, source.categoryOfFall);
    }

    ~Params()
    {
        delete[] categoryOfFall;
    }

    const int absoluteValOfTemp(int temp)
    {
        if (temp < 0)
        {
            unsigned int absoluteVal = temp * (-1);
            return absoluteVal;
        }
        return temp;
    }

    Params& operator=(const Params& source)
    {
        if(this != &source)
        {
            hpa = source.hpa;
            temp = source.temp;
            cloudiness = source.cloudiness;
            delete[] categoryOfFall;
            categoryOfFall = new char[strlen(source.categoryOfFall) + 1];
            strcpy(categoryOfFall, source.categoryOfFall);
        }
        return *this;
    }

    bool operator==(const Params &other)const
    {
        return hpa == other.hpa && temp == other.temp && strcmp(categoryOfFall,other.categoryOfFall)==0 && cloudiness == other.cloudiness;
    }

    friend std::ostream& operator<<(std::ostream &out, const Params &p)
    {
        out << "HPA: " << p.hpa << " Temp: " << p.temp << " CategoryOfFall: " << p.categoryOfFall << " Cloudiness: " << p.cloudiness;
        return out;
    }

    void showInfo() override
    {
        std::cout << "Weather Information: " << std::endl;
        std::cout << *this << std::endl;
    }

private:
    int hpa;
    unsigned int temp;
    char *categoryOfFall;
    std::string cloudiness;
};

std::string Params::date = "30.10.2018";

int main()
{
    //tworzenie obiektu i testowanie funkcji;
    Params weather1(1013,5,"Rain","partly cloudly");
    std::cout<<"Orginal weather"<<weather1<<std::endl;
    weather1.showInfo();

    //testowanie konstruktora kopiującego;
    Params weather2 = weather1;
    std::cout<<"\nCopierd weather object: "<<weather2;
    weather2.showInfo();

    //testowanie operator przypisania głeboka kopia

    Params weather3(1020,10,"Snow","Clear sky");
    std::cout<<"\nOrginal object before assigment"<<std::endl;
    weather3.showInfo();


    //testowanie operatora przypisania
    weather3 = weather1;
    std::cout<<"Weather 3 is now weather1: ";
    weather3.showInfo();


    //testowanie polimorfizmu 
    Sensor* sensorPtr = &weather1;
    std::cout<<"Testowanie polimorfizmu wywołanie info wskaźnikiem";
    sensorPtr->showInfo();

    //testawanie operatora << dla weather1;
    std::cout << "\nTesting operator << for weather1:" << std::endl;
    std::cout<<weather1<<std::endl;

    //testowanie operatora ==

    std::cout<<"\nTestowanie czy weather 1 == weather 2 ";

    if(weather1 == weather2)
    {
        std::cout<<"sa takie same";
    }else
    {
        std::cout<<"sa rozne";
    }

    std::cout<<"\nTestowanie czy weather 1 == weather  ";
    if(weather1 == weather3)
    {
        std::cout<<"sa takie same";
    }else
    {
        std::cout<<"sa rozne";
    }



    return 0;
}