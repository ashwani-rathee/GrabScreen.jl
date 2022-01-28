#include<string>
#include<jlcxx/jlcxx.hpp>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdint>
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;
std::vector<std::uint8_t> screenshot(int Width = 1920, int Height = 1080, int originx=0, int originy=0, int type=1)
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
    if(type == 0 )
        return Pixels;
    else if(type==1){
        std::vector<std::uint8_t> Pixels2;
        Pixels2.resize(Width * Height * 3);
        int j = 0;
        for(int i=0; i<Pixels.size(); i+=4){
            Pixels2[j] = Pixels[i+2];
            Pixels2[j+1] = Pixels[i+1];
            Pixels2[j+2] = Pixels[i];
            j=j+3;
        }
        return Pixels2;
    }
    else if(type==2){
        std::vector<std::uint8_t> Pixels2;
        Pixels2.resize(Width * Height * 1);
        int j=0;
        for(int i=0; i<Pixels.size(); i+=4){
            //Average method
            // uint8_t sum = Pixels[i] + Pixels[i+1] + Pixels[i+2];
            // uint8_t avg= sum / 3;

            //visual perception correction
            uint8_t avg = 0.114*Pixels[i] + 0.587*Pixels[i+1] + 0.299*Pixels[i+2];
            Pixels2[j] = avg;
            j++;
        }
        return Pixels2;
    }
    else{
        cout << "Error: type is not correct" << endl;
        throw std::invalid_argument( "received error" );
        // return ; 
    }
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


// int main(){
//     std::vector<std::uint8_t> a = screenshot();
//     cout<<a.size()<<endl;
//     // for(int i=0; i<100; i++){
//     //     cout << unsigned(a[i]) << endl;
//     // }
//     // cout << a[0:10] << endl;
//     return 0;
// }