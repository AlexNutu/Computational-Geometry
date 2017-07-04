#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <math.h>
#include "Triangulare.h"
using namespace std;
using namespace sf;
#define PI 3.14159265



int main()
{
    RenderWindow window(VideoMode(1000,800),"Triangulare");
    Triangulare T;
    T.init();
    T.linesCheck();
    Vector2f A(5, 6), B(8,3);
    while(window.isOpen())
	{
	    window.clear();
	    Event event;
        vector<Punct> VECTOR = T.getVect();
        vector<Punct> redLines;
        CircleShape circle(3) ;
        circle.setFillColor(Color::Red) ;
        circle.setOrigin(circle.getRadius()/2,circle.getRadius()/2) ;
        circle.setPosition(Vector2f(400 + 50*T.getPoint().coordX, 400 - 50*T.getPoint().coordY)) ;
        window.draw(circle) ;
	    for(int i = 0; i < VECTOR.size(); i++)
        {
            CircleShape circle(3) ;
            circle.setFillColor(Color::Green) ;
            circle.setOrigin(circle.getRadius()/2,circle.getRadius()/2) ;
            circle.setPosition(Vector2f(400 + 50*VECTOR[i].coordX, 400 - 50*VECTOR[i].coordY)) ;
            window.draw(circle) ;
            if(VECTOR[i].pointOnLine == false){
                if(i != VECTOR.size() - 1){
                    Vertex line[] =
                    {
                        Vertex(Vector2f(400 + 50*VECTOR[i].coordX, 400 - 50*VECTOR[i].coordY), Color::Green),
                        Vertex(Vector2f(400 + 50*VECTOR[i + 1].coordX, 400 - 50*VECTOR[i + 1].coordY), Color::Green)
                    };
                    window.draw(line, 2, Lines);
                }
                else{
                    Vertex line[] =
                    {
                        Vertex(Vector2f(400 + 50*VECTOR[i].coordX, 400 - 50*VECTOR[i].coordY), Color::Green),
                        Vertex(Vector2f(400 + 50*VECTOR[0].coordX, 400 - 50*VECTOR[0].coordY), Color::Green)
                    };
                window.draw(line, 2, Lines);
                }
            }else{
                if(i != VECTOR.size() - 1){
                    Vertex line[] =
                    {
                        Vertex(Vector2f(400 + 50*VECTOR[i].coordX, 400 - 50*VECTOR[i].coordY), Color::Red),
                        Vertex(Vector2f(400 + 50*VECTOR[i + 1].coordX, 400 - 50*VECTOR[i + 1].coordY), Color::Red)
                    };
                    window.draw(line, 2, Lines);
                }
                else{
                    Vertex line[] =
                    {
                        Vertex(Vector2f(400 + 50*VECTOR[i].coordX, 400 - 50*VECTOR[i].coordY), Color::Red),
                        Vertex(Vector2f(400 + 50*VECTOR[0].coordX, 400 - 50*VECTOR[0].coordY), Color::Red)
                    };
                window.draw(line, 2, Lines);
                }
            }
        }
	    while(window.pollEvent(event))
        {
            if(event.type == Event::Closed){ window.close(); }
            if(event.type == Event::KeyPressed)
            {
                if(event.key.code == Keyboard::Space)
                {
                    if(T.getSize() > 3)
                    {
                        T.earClip();
                    }
                    else {T.Clear(); cout << "\nTriangulare terminata!"; if(!T.getBool())cout << " Punctul P este in afara poligonului";}
                }
                if(event.key.code == Keyboard::Escape){ window.close(); }
            }
        }
        window.display();
	}
    return 0;
}


