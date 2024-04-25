#include <iostream>
#include "ComplexPlane.h"
using namespace std;
using namespace sf;

int main(){
    int pixelWidth = VideoMode::getDesktopMode().width / 2;
    int pixelHeight = VideoMode::getDesktopMode().height / 2;
    VideoMode vm(pixelWith,pixelHeight);
    RenderWindow window(vm, "Mandelbrot Set", Style::Default);
    
    ComplexPlane mandelbrotSet(pixelWidth, pixelHeight);
    sf::Font font;
    sf::Text text;
    if(!font.loadFromFile("Freedom-10eM.ttf")){
        cout << "Error! Could not load font" << endl;
    }
    
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) {window.close();}
            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Right){
                    mandelbrotSet.zoomOut();
                    mandelbrotSet.setCenter({event.mouseButton.x, event.mouseButton.y});
                }
                else if(event.mouseButton.button == sf::Mouse::Left){
                    mandelbrotSet.zoomIn();
                    mandelbrotSet.setCenter({event.mouseButton.x, event.mouseButton.y});
                }
            }
            if (event.type == sf::Event::MouseMoved){
                mandelbrotSet.setMouseLocation({ event.mouseButton.x, event.mouseButton.y });
            }
            if(Keyboard::isKeyPressed(Keyboard::Escape)){
                window.close();
            }
            mandelbrotSet.updateRender();
            mandelbrotSet.loadText(text);
            window.clear();
            window.draw(mandelbrotSet);
            window.draw(text);
            window.display();
        }
    }
    return 0;
}
