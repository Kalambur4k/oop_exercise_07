/******************************************************************************
Velesov Daniil LAB7 OOP 19Var
*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "Figure.cpp"
using namespace std;

void printmenu(){//печать меню
    std::cout << "1 - Add rectangle" << std::endl;
    std::cout << "2 - Add rhombus" << std::endl;
    std::cout << "3 - Add trapezoid" << std::endl;
    std::cout << "4 - Show current figures" << std::endl;
    std::cout << "5 - Start information printing" << std::endl;
    std::cout << "6 - Delete last figure" << std::endl;
    std::cout << "***************************************" << std::endl;
    std::cout << "n - Create new vector" << std::endl;
    std::cout << "s - Save vector as file(!)" << std::endl;
    std::cout << "l - Load vector from file(!)" << std::endl;
    std::cout << "u - Undo last step(!)" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "7 - Print help" << std::endl;
    std::cout << "8 - Exit" << std::endl;
    };

void checkSaved( int &sav ) {//проверка файла на сохранение
    char a = '\0';
    if(sav != 1){
        std::cout << "File wasn't saved. Are you sure you want to continue? Every unsaved progress will be lost FOREVER." << std::endl;
        std::cout << "y to continue\n any key to decline;" << std::endl;
        std::cin >> a;
        if(a == 'y'){
            sav = 1;
        }
        else{
            std::cout << "Denied" << std::endl;
        };
    }
}

using PFigure = std::shared_ptr<Figure>;

int main()
{
    RectFactory*  re_factory(new RectFactory);//"фабрика" прямоугольников
    RhomFactory*  rh_factory(new RhomFactory) ;//"фабрика" ромбов
    TrapFactory*  trap_factory(new TrapFactory) ;//"фабрика" трапеций
    std::vector<PFigure> figur, cmd;//вектор фигур
    double inc_a,inc_b,inc_c;//переменные для фигур
    char a;//переменная для switch
    int sav = 1;//проверка на сохранение файла, пустой файл считается сохраненным
    std::cout << "OOP lab #7. Author: Velesov Daniil M8O - 208B - 19." << std::endl;

    std::cout << "Hello there. It is a Figure Calculator.\nAdd Figures to Figures Vector and start calculating info by using 5 in menu.\nCalculator finds figures squares,coordinates." << std::endl;
    std::cout << "Also you can always control your progress by special keys under '***' line." << std::endl;
    printmenu();
    while (a != '8'){//меню выбора действий
        std::cin >> a;
        if(a=='1'){
            std::cout << "Creating rectangle" << std::endl;
            std::cout << "width:" << std::endl;
            std::cin >> inc_a;//длина
            std::cout << "height:" << std::endl;
            std::cin >> inc_b;//ширина
            figur.push_back(PFigure(re_factory -> createFigure(inc_a,inc_b)));
            cmd.push_back(PFigure(nullptr));
            sav = 0;
            std::cout << "DONE!" << std::endl;
        };
        if(a=='2'){
            std::cout << "Creating rhombus:" << std::endl;
            std::cout << "diagonal 1:" << std::endl;
            std::cin >> inc_a;//диагональ 1
            std::cout << "diagonal 2:" << std::endl;
            std::cin >> inc_b;//диагональ 2
            figur.push_back(PFigure(rh_factory -> createFigure(inc_a,inc_b)));
            cmd.push_back(PFigure(nullptr));
            sav = 0;
            std::cout << "DONE!" << std::endl;
        };

        if(a=='3'){
            std::cout << "Creating trapezoid:" << std::endl;
            std::cout << "base of trapezoid 1:" << std::endl;
            std::cin >> inc_a;//основание 1
            std::cout << "base of trapezoid 2:" << std::endl;
            std::cin >> inc_b;//основание 2
            std::cout << "height:" << std::endl;
            std::cin >> inc_c;//высота
            figur.push_back(PFigure(trap_factory -> createFigure(inc_a,inc_b,inc_c)));
            cmd.push_back(PFigure(nullptr));
            sav = 0;
            std::cout << "DONE!" << std::endl;
        };

        if(a=='4'){
            std::cout << "Vector contains:"<<std::endl;
            for (const auto&obj: figur) {
                obj -> showFigureType();
            }
            std::cout << "DONE!" << std::endl;
        };

        if(a=='5'){
            for (const auto&obj: figur) {
                obj -> showFigureType();
                obj -> getSquare();
                obj -> getCoordinates();
            };
            std::cout << "DONE!" << std::endl;
        };

        if(a=='6'){
            if ( figur.size() > 0 ) {
                cmd.push_back(PFigure(figur.back()));
                figur.pop_back();
                sav = 0;
                std::cout << "DONE!" << std::endl;
            } else {
                std::cout << "Nothing to delete" << std::endl;
            }
        };

        if(a=='7'){
            printmenu();
        };

        if(a=='8'){
            checkSaved(sav);
            if ( sav != 1 ) {
                a=0;
            }
        }
//SAVE FILE------------------------------------
        if(a=='s'){
            std::string fname;
            std::cout << "Enter file name" << std::endl;
            std::cin >> fname;
            ofstream f( fname, ios_base::out | ios_base::binary );
            int fSize = figur.size();
            f.write( (char*) (&fSize), sizeof(int) );
            for (const auto&obj: figur) {
                int magic = obj->getMagic();
                f.write( (char*) (&magic), sizeof(int) );
                obj->save(f);
            };
            f.close();
            sav = 1;
            std::cout << "File Saved!" << std::endl;
        };
//SAVE FILE------------------------------------
//LOAD FILE------------------------------------
        if(a=='l'){
            checkSaved( sav );
            if ( sav == 1 ) {
                figur.clear();
                cmd.clear();
                std::string fname;
                std::cout << "Enter file name" << std::endl;
                std::cin >> fname;
                ifstream f( fname, ios_base::in | ios_base::binary );
                int fSize;
                f.read( (char*) (&fSize), sizeof(int) );
                for ( int i = 0; i < fSize; i++ ) {
                    int magic;
                    f.read( (char*) (&magic), sizeof(int) );
                    Factory *fc;
                    switch( magic ) {
                        case 1:
                            fc = re_factory;
                            break;
                        case 2:
                            fc = rh_factory;
                            break;
                        case 3:
                            fc = trap_factory;
                            break;
                        default:
                            std::cout << "Error reading file!" << std::endl;
                            break;
                    }
                    figur.push_back(PFigure(fc->loadFigure(f)));
                }
                f.close();
                std::cout << "File loaded!" << std::endl;
            }
        };
//LOAD FILE------------------------------------
//NEW DOCUMENT---------------------------------
        if(a=='n'){
            checkSaved( sav );
            if ( sav == 1 ){
                figur.clear();
                cmd.clear();
                std::cout << "File created!" << std::endl;
            };
        };
//NEW DOCUMENT--------------------------------
//UNDO LAST STEP------------------------------
         if(a=='u'){
            if ( cmd.size() > 0 ) {
                PFigure f = cmd.back();
                if ( f == nullptr ) {
                    figur.pop_back();
                } else {
                    figur.push_back(f);
                }
                cmd.pop_back();
                std::cout << "last step has been undone!" << std::endl;
            } else {
                std::cout << "Nothing to undo" << std::endl;
            }
        };
//UNDO LAST STEP------------------------------
    };
//очистка из памяти
    delete re_factory;
    delete rh_factory;
    delete trap_factory;

    return 0;
};
