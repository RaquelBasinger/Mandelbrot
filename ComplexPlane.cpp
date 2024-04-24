#include "ComplexPlane.h"
#include <stdio.h>


ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight){
    m_pixel_size = {pixelWidth, pixelHeight};
    m_aspectRatio = (pixelWidth * 1.0)/(pixelHeight * 1.0);
    m_plane_center = {0,0};
    m_plane_size = {BASE_WIDTH, BASE_HEIGHT * m_aspectRatio};
    m_zoomCount = 0;
    m_state = State::CALCULATING;
    m_vArray.setPrimitiveType(Points);
    m_vArray.resize(pixelWidth * pixelHeight);
}
void ComplexPlane::draw(RenderTarget& target, RenderStates states) const{
    target.draw(m_vArray);
}
void ComplexPlane::zoomIn(){
    m_zoomCount++;
    float new_x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
    float new_y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
    m_plane_size = {new_x, new_y};
    m_state = CALCULATING;
}
void ComplexPlane::zoomOut(){
    m_zoomCount--;
    float new_x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
    float new_y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
    m_plane_size = {new_x, new_y};
    m_state = CALCULATING;
}
void ComplexPlane::setCenter(Vector2i mousePixel){
    
}
void ComplexPlane::setMouseLocation(Vector2i mousePixel){
    
}
void ComplexPlane::loadText(Text& text){
    
}
void ComplexPlane::updateRender(){
    if(m_state == CALCULATING){
        int pixelHeight = m_pixel_size.y;
        int pixelWidth = m_pixel_size.x;
        for(int i = 0; i < pixelHeight; i++){
            for(int j = 0; j < pixelWidth; j++){
                Uint8 r, g, b;
                vArray[j + i * pixelWidth].position = {(float)j, (float)i};
                //ComplexPlane::mapPixelToCoords;
                //ComplexPlane::countIterations();
                vArray[j + i * pixelWidth].color = { r,g,b };
            }
        }
        m_state = DISPLAYING;
    }
}
int ComplexPlane::countIterations(Vector2f coord){
    int iter = 0;
    double re = coord.x;
    double im = coord.y;
    complex<double> c (re, im);
    complex<double> z (0,0);
    while(abs(z) < 2.0 && iter < 64){
        z = z*z + c;
        iter++;
    }
    return iter;
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b){
    
}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel){
    Vector2f complexPixel;
    Vector2i monitor_Width = VideoMode::getDesktopMode().width;
    Vector2i monitor_Height = VideoMode::getDesktopMode().height;
    float complexPixel.x = mousePixel.x;
    float complexPixel.y = mousePixel.y;
    complexPixel.x = (complexPixel.x / monitor_Width) * m_plane_size.x + (m_plane_center.x - m_plane_size.x / 2.0)
    complexPixel.y = ((complexPixel.y - monitor_Height)/(0 - monitor_Height)) * m_plane_size.y + (m_plane_center.y - m_plane_size.y / 2.0)
    return complexPixel;
}
