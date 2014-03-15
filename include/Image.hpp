#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <gccore.h>
#include <png.h>
#include "pngu.h"
#include <malloc.h>

class Image
{
public:
//Constructor
        //From file
                Image(char *filename) {loadFromFile(filename);}
        //From buffer
                Image(uint8_t *buf_data)  {loadFromBuffer(buf_data);}
//Destructor
        ~Image();
//Methods
        //Clears the image
                void clear();
        //Loads from file
                int loadFromFile(char *filename);
        //Loads from buffer
                int loadFromBuffer(uint8_t *buf_data);
        //Sets to the GX
                void setGX(int texmap) {GX_LoadTexObj(&texObj, texmap);}
        //Gets image width
                int getWidth() {return width;}
        //Gets image height
                int getHeight() {return height;}
//Variables
        uint8_t  *data;
        uint32_t width, height;
        GXTexObj texObj;
};


#endif
