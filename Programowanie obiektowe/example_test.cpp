#include <iostream>
#include <cmath>
#include <stdexcept>

template <typename T>
class Vector
{
public:
    virtual double length() const = 0;
    virtual void normalize() = 0;
    virtual ~Vector() = default;
};

template <typename T>
class Vector2D : public Vector<T>
{
protected:
    T a;
    T b;

public:
    Vector2D(T _a, T _b) : a(_a), b(_b) {}

    double length() const override
    {
        double a2D = pow(a, 2);
        double b2D = pow(b, 2);
        return sqrt(a2D + b2D);
    }

    void normalize() override
    {
        double len2D = length();
        if (len2D == 0)
        {
            throw std::runtime_error("Nie można znormalizować wektora o długości 0.");
        }

        this->a /= len2D;
        this->b /= len2D;
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector2D<T> &vec)
    {
        out << "Pierwsza składowa: " << vec.a << "\n"
            << "Druga składowa: " << vec.b << "\n";
        return out;
    }
};

template <typename T>
class Vector3D : public Vector2D<T>
{
private:
    T c;

public:
    Vector3D(T _a, T _b, T _c) : Vector2D<T>(_a, _b), c(_c) {}

    double length() const override
    {
        double a3D = pow(this->a, 2);
        double b3D = pow(this->b, 2);
        double c3D = pow(this->c, 2);
        return sqrt(a3D + b3D + c3D);
    }

    void normalize() override
    {
        double len3D = length();
        if (len3D == 0)
        {
            throw std::runtime_error("Nie można znormalizować wektora o długości 0.");
        }

        this->a /= len3D;
        this->b /= len3D;
        this->c /= len3D;
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector3D<T> &vec)
    {
        out << "Pierwsza składowa: " << vec.a << "\n"
            << "Druga składowa: " << vec.b << "\n"
            << "Trzecia składowa: " << vec.c << "\n";
        return out;
    }
};

int main()
{
    try
    {
        Vector2D<double> vec2D(3.7, 4.2);
        std::cout << "\nWektor 2D przed normalizacją:\n" << vec2D;
        std::cout << "Długość przed normalizacją: " << vec2D.length() << "\n";

        vec2D.normalize();
        std::cout << "Wektor 2D po normalizacji:\n" << vec2D;
        std::cout << "Długość po normalizacji: " << vec2D.length() << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Błąd: " << e.what() << std::endl;
    }

    try
    {
        Vector3D<int> vec3D(1, 2, 3);
        std::cout << "\nWektor 3D przed normalizacją:\n" << vec3D;
        std::cout << "Długość przed normalizacją: " << vec3D.length() << "\n";

        vec3D.normalize();
        std::cout << "Wektor 3D po normalizacji:\n" << vec3D;
        std::cout << "Długość po normalizacji: " << vec3D.length() << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Błąd: " << e.what() << "\n";
    }

    try
    {
        Vector3D<int> zeroVec(0, 0, 0);
        std::cout << "\nWektor zerowy przed normalizacją:\n" << zeroVec;
        zeroVec.normalize(); // To rzuci wyjątek
    }
    catch (const std::exception &e)
    {
        std::cerr << "Błąd: " << e.what() << "\n";
    }

    return 0;
}
