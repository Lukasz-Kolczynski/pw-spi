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

/*

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

*/

/*
#include <iostream>
#include <cstring>

class Pokemon 
{
public:
    virtual void showInfo() = 0;
    virtual ~Pokemon () {};
};


class Ability : public Pokemon 
{
private:
    int attack_damage;
    std::string ultimate;
    int HP;
    std::string name;
    char* tier;

public:
    static int pokedexID;
    Ability(const int _attack_damage, const std::string& _ultimate, const int _HP, const std::string& _name, const char* _tier) : 
    attack_damage(_attack_damage), ultimate(_ultimate), HP(_HP), name(_name)
    {
        tier = new char[strlen(_tier)+1];
        strcpy(tier,_tier);
    }

    ~Ability () 
    {
        delete [] tier;
    }

    Ability (const Ability &source): attack_damage(source.attack_damage), ultimate(source.ultimate), HP(source.HP), name(source.name)
    {
        tier = new char[strlen(source.tier)+1];
        strcpy(tier, source.tier);
    }


    Ability& operator =(const Ability &source) 
    {
        if (this != &source)
        {
            attack_damage = source.attack_damage;
            ultimate = source.ultimate;
            HP = source.HP;
            name = source.name;
            delete [] tier;
            tier = new char[strlen(source.tier)+1];
            strcpy(tier, source.tier);
        }
        return *this;
    }

    const int UseUlt()
    {
        return 2*attack_damage;
    }

    friend std::ostream& operator<<(std::ostream& out, const Ability &other)
    {
        out << "\nattack Damage: " <<other.attack_damage<< "\nultimate: "<< other.ultimate << "\nHP: " << other.HP << "\nName: " << other.name << "\nTier: " << other.tier << std::endl;
        return out;
    }

    bool operator ==(const Ability &source) const
    {
        return attack_damage==source.attack_damage && ultimate==source.ultimate && HP==source.HP && name==source.name && strcmp(tier, source.tier)==0;
    }

    virtual void showInfo()override
    {
        std::cout << "Information of your Pokemon: \n" <<*this<<"ID: "<<pokedexID<<std::endl;
    }


};

int Ability::pokedexID = 10;


int main()
{
    Ability p1(15,"Splash",69,"Wodzianka","S");
    p1.showInfo();
    Ability p2(25,"Fire",23,"awawe","A");
    p2.showInfo();
    Ability p3(55,"Ground",43,"bebe","B");
    p3.showInfo();

    std::cout << "p1 po zmianie danych z p2: " <<std::endl;
    p1=p2;
    p1.showInfo();

    if(p1==p2)
    {
        std::cout <<"p1 i p2 sa takie same"<< std::endl;
    }
    else
    {
        std::cout << "p1 i p2 sa różne" <<std::endl;
    }

    Pokemon *ptr = &p3;
    ptr->showInfo();


    return 0;
}

*/

#include <iostream>
#include <cstring>
#include <cmath>


class Family 
{
public:
    virtual void showInfo() = 0;
    virtual ~Family () {};
};

class Person : public Family
{
private:
    std::string name;
    std::string who;
    int age;
    char* kids; 



public:
    static int PersonID;
    Person(const std::string& _name, const std::string& _who, const int _age, const char* _kids) : name(_name), who(_who), age(_age)
    {
        kids = new char[strlen(_kids)+1];
        strcpy(kids, _kids);
    }

    void set_new_kid(const std::string& _name, const std::string& _who, const int _age, const char* _kids) 
    {
        name = _name;
        who = _who;
        age = _age;
        delete [] kids;
        kids = new char[strlen(_kids)+1];
        strcpy(kids, _kids);
    }

    int get_age()
    {
        return age;
    }

 std::string get_name()
    {
        return name;
    }
    
    
    char* get_kids()
    {
        return kids;
    }

    ~Person () 
    {
        delete [] kids;
    }

    Person (const Person &source) : name(source.name), who(source.who), age(source.age)
    {
        kids = new char[strlen(source.kids)+1];
        strcpy(kids, source.kids);
    }


    Person& operator = (const Person &source)
    {
        if(this != &source)
        { 
            name = source.name;
            who = source.who;
            age = source.age;
            delete [] kids;
            kids = new char[strlen(source.kids)+1];
            strcpy(kids, source.kids);
        }
        return *this;
    }


    const int date_of_birth()
    {
        int date_now = 2024;
        int date_born = date_now - age;
        return date_born;
    }


    friend std::ostream& operator << (std::ostream& out, const Person &other)
    {
        out << "\nname: " << other.name << "\nwho in family?: " << other.who << "\nage: " << other.age << "\nHow many kids?: " << other.kids << std::endl;
        return out;
    }


    bool operator == (const Person &source) const
    {
        return name == source.name && who == source.who && age == source.age && strcmp(kids, source.kids)== 0;
    }

    virtual void showInfo()override
    {
        std::cout << "Informations about this family: \n" << *this <<"ID osoby: "<<PersonID<< std::endl;
    }


};

int Person::PersonID=10;


int main() 
{
    Person p1("Łukasz", "Dad", 30, "2");
    p1.showInfo();
    Person p2("Kinga", "Mom", 29, "2");
    p2.showInfo();
    Person p3("Nikola", "Kid", 3, "0");
    p3.showInfo();

    Person p4=p2;
    p4.showInfo();

    p4 = p3;
    p3.showInfo();

    if(p3==p4)
    {
        std::cout << "są takie same" << std::endl;
    }
    else
    {
        std::cout << "nie są takie same" << std::endl;
    }

    p4.set_new_kid("Leon","kid",1,"0");
    p4.showInfo();
    
    std::cout << "getter z p1:  "<<p1.get_kids()<<std::endl;

    return 0;
}