#include "ComplexPlane.h"
#include <stdio.h>


ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight){
    m_pixel_size = {pixelWidth, pixelHeight};
    m_aspectRatio = ((float)pixelWidth)/((float)pixelHeight);
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
    m_state = State::CALCULATING;
}
void ComplexPlane::zoomOut(){
    m_zoomCount--;
    float new_x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
    float new_y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
    m_plane_size = {new_x, new_y};
    m_state = State::CALCULATING;
}
void ComplexPlane::setCenter(Vector2i mousePixel){
    Vector2f newCenter = mapPixelToCoords(mousePixel);
    m_plane_center = newCenter;
    m_state = State::CALCULATING;
}
void ComplexPlane::setMouseLocation(Vector2i mousePixel){
    m_mouseLocation = mapPixelToCoords(mousePixel);
}
void ComplexPlane::loadText(Text& text){
    stringstream ss;
    ss << "Mandelbrot Set\n";
    ss << "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")\n";
    ss << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")\n";
    ss << "Left-click to Zoom in\n";
    ss << "Right-click to Zoom out\n";
    text.setString(ss.str());
}
void ComplexPlane::updateRender(){
    if(m_state == State::CALCULATING){
        int pixelHeight = m_pixel_size.y;
        int pixelWidth = m_pixel_size.x;
        for(int i = 0; i < pixelHeight; i++){
            for(int j = 0; j < pixelWidth; j++){
                Uint8 r, g, b;
                Vector2f coord_j_i;
                size_t iters;
                m_vArray[j + i * pixelWidth].position = {(float)j, (float)i};
                coord_j_i = mapPixelToCoords({j,i});
                iters = countIterations(coord_j_i);
                iterationsToRGB(iters, r, g, b);
                m_vArray[j + i * pixelWidth].color = { r,g,b };
            }
        }
        m_state = State::DISPLAYING;
    }
}
int ComplexPlane::countIterations(Vector2f coord){
    complex<double> c(coord.x, coord.y);
    complex<double>x(0, 0);
    size_t count = 0;
    while (abs(x) < 2 && count < MAX_ITER)
    {
        x = pow(x, 2) + c;
        count++;
    }
    return count;
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b){
    if(count == MAX_ITER){
        r = 0;
        g = 0;
        b = 0;
    }
    else if(count < 10){
        r = 255;
        g = 64;
        b = 0;
    }
    else if(count < 20){
        r = 255;
        g = 208;
        b = 0;
    }
    else if(count < 30){
        r = 0;
        g = 247;
        b = 255;
    }
    else if(count < 40){
        r = 51;
        g = 0;
        b = 255;
    }
    else if(count < 50){
        r = 217;
        g = 0;
        b = 255;
    }
    else if(count < 65){
        r = 0;
        g = 255;
        b = 102;
    }
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
