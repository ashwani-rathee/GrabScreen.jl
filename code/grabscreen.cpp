#include<string>
#include<jlcxx/jlcxx.hpp>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdint>
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;
std::vector<std::uint8_t> screenshot(int Width = 1920, int Height = 1080, int originx=0, int originy=0)
{
    // int Width = 0;
    // int Height = 0;
    // int BitsPerPixel = 0;

    std::vector<std::uint8_t> Pixels;

    Display* display = XOpenDisplay(nullptr);
    Window root = DefaultRootWindow(display);

    XWindowAttributes attributes = {0};
    XGetWindowAttributes(display, root, &attributes);
    if(Width > attributes.width || Height > attributes.height){
        cout << "Error: Width or Height is larger than the screen resolution" << endl;
        throw std::invalid_argument( "received error" );
        // return ; 
    }

    if(Width+originx > attributes.width || Height+originy > attributes.height){
        cout << "Error: Width or Height is larger than the screen resolution, set origins less" << endl;
        throw std::invalid_argument( "received error" );
        // return ; 
    }
    // Width = attributes.width;
    // Height = attributes.height;

    XImage* img = XGetImage(display, root, originx, originy , Width, Height, AllPlanes, ZPixmap);
    // BitsPerPixel = img->bits_per_pixel;
    Pixels.resize(Width * Height * 4);

    memcpy(&Pixels[0], img->data, Pixels.size());

    XDestroyImage(img);
    XCloseDisplay(display);
    return Pixels;
}

std::string greet()
{
   return "hello, world";
}


std::string greetname(std::string name)
{
   return "hello, " + name;
}

JLCXX_MODULE define_julia_module(jlcxx::Module& mod)
{
  mod.method("greet", &greet);
  mod.method("greetname", &greetname);
  mod.method("screenshot", &screenshot);
}


