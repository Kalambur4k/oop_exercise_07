#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

//абстрактный класс фигур
class Figure
{
public:
    virtual void getSquare() = 0; //площадь
    virtual void getCoordinates() = 0; //координаты фигуры
    virtual void showFigureType() = 0; //вывод названия фигуры
    virtual int getMagic() = 0;
    virtual void save(ostream &f) = 0; //запись в файл
    virtual ~Figure() {} //деструктор
};

//прямоугольник
class Rectangle : public Figure
{
private:
    double width; //ширина
    double height; //высота
public:
    Rectangle()
    {
    }
    Rectangle(double w, double h) : width(w), height(h)
    {
    }
    Rectangle(istream &f){
        f.read( (char*) (&width), sizeof(double) );
        f.read( (char*) (&height), sizeof(double) );
    }
    void save(ostream &f){
        f.write( (char*) (&width), sizeof(double) );
        f.write( (char*) (&height), sizeof(double) );
    }
    void getSquare()
    {
        std::cout << "Rectangle Square: "<< width * height << std::endl;
    }
    void getCoordinates()
    {
        std::cout << "Rectangle Coords:"<<"(0,0);("<< width <<";0);("<< width <<";"<< height <<");(0;"<< height <<")." << std::endl;
    }
    void showFigureType()
    {
        std::cout << "Rectangle" << std::endl;
    }
    int getMagic() { return 1; }
};
//Ромб
class Rhombus : public Figure
{
private:
    double diag1; //Диагональ 1
    double diag2; //Диагональ 2
public:
    Rhombus()
    {
    }
    Rhombus(double d1, double d2) : diag1(d1), diag2(d2)
    {
    }
    Rhombus(istream &f){
        f.read( (char*) (&diag1), sizeof(double) );
        f.read( (char*) (&diag2), sizeof(double) );
    }
    void save(ostream &f){
        f.write( (char*) (&diag1), sizeof(double) );
        f.write( (char*) (&diag2), sizeof(double) );
    }
    void getSquare()
    {
        std::cout << "Rhombus Square: "<< diag1 * diag2 * 0.5 << std::endl;
    }
    void getCoordinates()
    {
        std::cout << "Rhombus Coords:"<<"(0,0);("<< diag2/2 <<";"<<diag1/2<<");(0;"<< diag1 <<");("<< -diag2/2 <<";"<< diag1/2 <<")." << std::endl;
    }
    void showFigureType()
    {
        std::cout << "Rhombus" << std::endl;
    }
    int getMagic() { return 2; }
};
//Трапеция
class Trapezoid : public Figure
{
private:
    double a; //Основание 1
    double b; //Основание 2
    double h; //Высота
public:
    Trapezoid()
    {
    }
    Trapezoid(double a, double b,double h) : a(a), b(b), h(h)
    {
    }
    Trapezoid(istream &f){
        f.read( (char*) (&a), sizeof(double) );
        f.read( (char*) (&b), sizeof(double) );
        f.read( (char*) (&h), sizeof(double) );
    }
    void save(ostream &f){
        f.write( (char*) (&a), sizeof(double) );
        f.write( (char*) (&b), sizeof(double) );
        f.write( (char*) (&h), sizeof(double) );
    }
    void getSquare()
    {
        std::cout << "Trapezoid Square: "<<  (a+b)*0.5*h << std::endl;
    }
    void getCoordinates()
    {
        std::cout << "Trapezoid Coords:"<<"(0,0);("<< a <<";0);(" << b << ";"<< h << ");(0;"<< h <<")." << std::endl;
    }
    void showFigureType()
    {
        std::cout << "Trapezoid" << std::endl;
    }
    int getMagic() { return 3; }
};

// Фабрики объектов
class Factory
{
public:
    virtual Figure* createFigure() = 0; //создание фигуры
    virtual Figure* loadFigure(istream &f) = 0; //загрузка
    virtual ~Factory() {} //деструктор
};

class RectFactory: public Factory //фабрика прямоугольников
{
public:
    Figure *createFigure(){
		return reinterpret_cast<Figure*>(new Rectangle());
    }
    Figure* createFigure(double width,double height) {
        return reinterpret_cast<Figure*>(new Rectangle(width,height));
    }
    Figure* loadFigure(istream &f) {
        return reinterpret_cast<Figure*>(new Rectangle(f));
    }
};

class RhomFactory: public Factory //фабрика ромбов
{
 public:
    Figure *createFigure(){
        return reinterpret_cast<Figure*>(new Rhombus());
    }
    Figure* createFigure(double diag1,double diag2) {
        return reinterpret_cast<Figure*>(new Rhombus(diag1,diag2));
    }
    Figure* loadFigure(istream &f) {
        return reinterpret_cast<Figure*>(new Rhombus(f));
    }
};

class TrapFactory: public Factory //фабрика трапеций
{
  public:
    Figure *createFigure(){
		return reinterpret_cast<Figure*>(new Trapezoid());
    }
    Figure* createFigure(double a,double b,double h) {
      return reinterpret_cast<Figure*>(new Trapezoid(a,b,h));
    }
    Figure* loadFigure(istream &f) {
      return reinterpret_cast<Figure*>(new Trapezoid(f));
    }
};
