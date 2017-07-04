#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <math.h>
using namespace std;

ifstream in("date.in");

class Triangulare;

class Punct{
public:
    double coordX, coordY;
    bool ureche, pointOnLine;

    Punct(double a, double b):coordX(a), coordY(b){ureche = false; pointOnLine = false;}
    Punct(){ureche = false; pointOnLine = false;}
    void setCoord(double a, double b){coordX = a; coordY = b;}
    void afisare()
    {
        cout << "[" << coordX << ", " << coordY << "]";
    }
    float determinant(Punct v)
    {
        float result = this->coordX*v.coordY - this->coordY*v.coordX ;
        return result ;
    }
};



class Triangulare{
    vector<Punct> POLIGON;
    vector<Punct> COPY_POLIGON;
    Punct P;
    bool pointFound;
public:
    bool pointInsideCheck(Punct toCheck, Punct A, Punct B, Punct C)
    {
        float alpha = ((B.coordY - C.coordY)*(toCheck.coordX - C.coordX) + (C.coordX - B.coordX)*(toCheck.coordY - C.coordY)) / ((B.coordY - C.coordY)*(A.coordX - C.coordX) + (C.coordX - B.coordX)*(A.coordY - C.coordY));
        float beta = ((C.coordY - A.coordY)*(toCheck.coordX - C.coordX) + (A.coordX - C.coordX)*(toCheck.coordY - C.coordY)) / ((B.coordY - C.coordY)*(A.coordX - C.coordX) + (C.coordX - B.coordX)*(A.coordY - C.coordY));
        float gamma = 1.0f - alpha - beta;
        if(alpha > 0 && beta > 0 && gamma > 0)return true;
        return false;
    }

    vector<Punct> getVect(){return POLIGON;}

    bool earCheck(int indice)
    {
        int vecin_1, vecin_2;
        if(indice == 0){vecin_1 = POLIGON.size() - 1; vecin_2 = indice + 1;}
        else if(indice == POLIGON.size() - 1){vecin_1 = indice - 1; vecin_2 = 0;}
        else {vecin_1 = indice - 1; vecin_2 = indice + 1;}
        Punct AUX1, AUX2;
        AUX1.coordX = POLIGON[indice].coordX - POLIGON[vecin_1].coordX;
        AUX1.coordY = POLIGON[indice].coordY - POLIGON[vecin_1].coordY;
        AUX2.coordX = POLIGON[vecin_2].coordX - POLIGON[indice].coordX;
        AUX2.coordY = POLIGON[vecin_2].coordY - POLIGON[indice].coordY;
        if(AUX1.determinant(AUX2) < 0)
        {
            return false;
        }
        else
        {
            for(int i = 0; i < COPY_POLIGON.size(); i++)
            {
                if(pointInsideCheck(COPY_POLIGON[i], POLIGON[vecin_2], POLIGON[indice], POLIGON[vecin_1]))return false;
            }
        }
        return true;
    }

    void init()
    {
        int sizeV; double A, B;
        in >> sizeV >> A >> B;
        P.setCoord(A, B);
        for(int i = 0; i < sizeV; i++)
        {
            in >> A >> B;
            POLIGON.push_back(Punct(A, B));
        }
        COPY_POLIGON = POLIGON;
        pointFound = false;
        for(int i = 0; i < POLIGON.size(); i++)
        {
            if(earCheck(i)){POLIGON[i].ureche = true;}
        }
    }

    int getSize(){return POLIGON.size();}

    Punct getPoint(){return P;}

    void linesCheck()
    {
        for(int i = 0; i < POLIGON.size() - 1; i++)
        {
            Punct A1 = POLIGON[i], A2 = POLIGON[i + 1];
            double a = A1.coordY - A2.coordY, b = A2.coordX - A1.coordX, c = A1.coordX * A2.coordY - A1.coordY * A2.coordX;
            if(a * P.coordX + b * P.coordY + c == 0) {
                if(!(P.coordX < min(A1.coordX, A2.coordX) || P.coordX > max(A1.coordX, A2.coordX) || P.coordY < min(A1.coordY, A2.coordY) || P.coordY > max(A1.coordY, A2.coordY)))
                {
                    pointFound = true;
                    cout<<"Punctul este pe latura: "; A1.afisare(); cout<<", "; A2.afisare();
                    POLIGON[i].pointOnLine = true;
                    break;
                }
            }
        }
        Punct A1 = POLIGON[0], A2 = POLIGON[POLIGON.size() - 1];
        double a = A1.coordY - A2.coordY, b = A2.coordX - A1.coordX, c = A1.coordX * A2.coordY - A1.coordY * A2.coordX;
        if(a * P.coordX + b * P.coordY + c == 0) {
            if(!(P.coordX < min(A1.coordX, A2.coordX) || P.coordX > max(A1.coordX, A2.coordX) || P.coordY < min(A1.coordY, A2.coordY) || P.coordY > max(A1.coordY, A2.coordY)))
            {
                pointFound = true;
                cout<<"Punctul este pe latura: "; A1.afisare(); cout<<", "; A2.afisare();
                POLIGON[POLIGON.size() - 1].pointOnLine = true;
            }
        }
    }

    void Clear(){ POLIGON.clear(); }

    bool getBool(){ return pointFound; }

    void afisareTriunghi(int indice)
    {
        int vecin_1, vecin_2;
        if(indice == 0){vecin_1 = POLIGON.size() - 1; vecin_2 = indice + 1;}
        else if(indice == POLIGON.size() - 1){vecin_1 = indice - 1; vecin_2 = 0;}
        else {vecin_1 = indice - 1; vecin_2 = indice + 1;}
        cout << "\nTriunghi gasit! Coordonate: "; POLIGON[vecin_1].afisare(); cout << ", "; POLIGON[indice].afisare(); cout << ", "; POLIGON[vecin_2].afisare();
    }

    void earClip()
    {
         bool urecheGasita = false;
         int indice = 0;
         int vecin_1, vecin_2;
         if(indice == 0){vecin_1 = POLIGON.size() - 1; vecin_2 = indice + 1;}
         else if(indice == POLIGON.size() - 1){vecin_1 = indice - 1; vecin_2 = 0;}
         else {vecin_1 = indice - 1; vecin_2 = indice + 1;}
         while(!urecheGasita)
         {
             if(earCheck(indice))
             {
                 urecheGasita = true;
                 afisareTriunghi(indice);
                 if(!pointFound)if(pointInsideCheck(P, POLIGON[vecin_2], POLIGON[indice], POLIGON[vecin_1])){ pointFound = true; cout << "<-- Punctul a fost gasit!"; }
                 POLIGON.erase(POLIGON.begin() + indice);
             }
             indice++;
         }
    }
};

