//
//  ECpp3dImage.cpp
//  ECpp3d
//
//  Created by Christian Gram Kalhauge on 22/01/13.
//
//

#include "tools/ECpp3dImage.h"
#include <jpeglib.h>
#include <vector>

namespace ECpp3d {


ImageSize makeImageSize(GLsizei width,GLsizei height,GLsizei depth) {
    return (ImageSize) {width,height,depth};
}

Image::Image(){
    this->size = makeImageSize(0,0,0);
    this->format = GL_RGB;
    this->type = GL_UNSIGNED_BYTE;
    this->data = 0;

}

Image::Image(ImageSize size) {
    this->size = size;
    this->format = GL_RGB;
    this->type = GL_UNSIGNED_BYTE;
    this->data = 0;
}

Image::Image(ImageSize size, GLenum data_format, GLenum data_type) {
    this->size = size;
    this->format = data_format;
    this->type = data_type;
    this->data = 0;
}

Image::~Image() {
    clearSpace();
}

GLenum Image::getFormat() const {
    return format;
}
GLenum Image::getType() const {
    return type;
}

const ImageSize & Image::getSize() const {
    return size;
}

const GLubyte * Image::getData() const {
    return data;
}


Image * Image::fromJPEG(const std::string & filename)
    throw (IOException){
    
    struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	JSAMPROW row_pointer[1];

	FILE * infile = fopen(filename.c_str(),"rb");
	if(!infile) throw IOException("Could not find file: " + filename);

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress((j_decompress_ptr) &cinfo);
	jpeg_stdio_src( &cinfo, infile );
	jpeg_read_header( &cinfo, 1 );

	jpeg_start_decompress( &cinfo );

	GLsizei width = cinfo.output_width;
	GLsizei height = cinfo.output_height;
	int num = cinfo.output_components;

	GLenum format;

	switch(num) {
		case (1): format = GL_R8; break;
        case (2): format = GL_RG; break;
		case (3): format = GL_RGB; break;
		case (4): format = GL_RGBA; break;
		default :
			throw Exception("Trying to load an unknown format, or the image is empty");
	}
    
    Image * image = new Image(makeImageSize(width,height,1),format, GL_UNSIGNED_BYTE);
    image->allocateSpace();
	row_pointer[0] = (unsigned char *)malloc(width*num);
	int location = 0;
	while( cinfo.output_scanline < cinfo.image_height )
	{
		jpeg_read_scanlines( &cinfo, row_pointer, 1 );
		for(unsigned int i=0; i<cinfo.image_width*cinfo.num_components;i++)
			image->data[location++] = row_pointer[0][i];
	}

	jpeg_finish_decompress( &cinfo );
	jpeg_destroy_decompress( &cinfo );
	free( row_pointer[0] );
	fclose( infile );
    
    return image;
}


GLubyte * Image::getPixelIndex(GLsizei x, GLsizei y) {
    return data + (pixelSize * (size.width* y +x));     
}


const GLubyte * Image::getPixelIndex(GLsizei x, GLsizei y) const {
    return data + (pixelSize * (size.width* y +x));     
}



Image * Image::fromGradient(GLint width, const gradient & gradient) {
    std::vector<glm::vec4> data;
    int index = 0;
	float now = 0, stripsize = gradient[1].first;
	for(int i = 0; i < width; i++) {
		float value = ((float) i ) / width;
		if(value > stripsize + now) {
			index ++;
			now = gradient[index].first;
			stripsize = gradient[index+1].first - now;
		}
		float part = (value - now) / stripsize;
		glm::vec4 color = gradient[index].second 
            * (1-part) + gradient[index+1].second * part;
		data.push_back(color);
	}
    Image * image = new Image(makeImageSize(width,1,1),GL_RGBA,GL_FLOAT);
    image->allocateSpace();
    memcpy(image->data,&data[0],data.size()*sizeof(glm::vec4));
    return image;
    
}

void Image::allocateSpace() {
    clearSpace();
    pixelSize=typeSize(type)*formatSize(format);
    int bytes = pixelSize * size.width * size.height * size.depth;
    data = new GLubyte[bytes];
}


void Image::clearSpace() {
    if(data) {
        delete [] data;
        data = 0;
    }
}

/*
 * toJPEG
 *
 * Saves a image into jpeg
 *
 * Code stolen from http://www.andrewnoske.com/wiki/index.php?title=Jpeglib_libray,
 * and edited to suit the program.
 *
 */

void Image::toJPEG(const std::string & filename, int quality) const throw (IOException){
  
    struct jpeg_compress_struct cinfo;    // basic info for JPEG properties
    struct jpeg_error_mgr jerr;           // in case of error
    FILE * outfile;                       // target file
    JSAMPROW row_pointer[1];              // pointer to JSAMPLE row[s]

    
    // Allocate copressing file
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);


    if ((outfile = fopen(filename.c_str(), "wb")) == NULL) {
        throw IOException("Could not open file: " + filename);
    }

    //Startup the Jpg
    jpeg_stdio_dest(&cinfo, outfile);


    cinfo.image_width  = size.width;
    cinfo.image_height = size.height;
    cinfo.input_components = formatSize(format); 
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE);

 
    jpeg_start_compress(&cinfo, TRUE);

    while (cinfo.next_scanline < cinfo.image_height)
    {
        row_pointer[0] = (JSAMPLE*) this->getPixelIndex(0,cinfo.next_scanline);
        (void) jpeg_write_scanlines(&cinfo,row_pointer , 1);
    }

    jpeg_finish_compress(&cinfo);
    fclose(outfile);
    jpeg_destroy_compress(&cinfo);

}

Image * Image::rotateCCW(){
    ImageSize oldsize = size;
    size = makeImageSize(oldsize.height,oldsize.width,oldsize.depth);
    
    GLubyte * old = this->data;
    this->data = 0;
    allocateSpace();
    
    //TODO Speed it up
     for(int y = 0; y < size.height; y++)
        for(int x = 0; x < size.width; x++ ) {
         memcpy(this->getPixelIndex(x,y),
                 &old[(y + (oldsize.width - x)*oldsize.height)*pixelSize],
                 pixelSize);
        }
    delete [] old;
    
    return this;

}


Image * Image::createCubeMapImages(const Image * crossImage) {
    Image * images = new Image[6];
    ImageSize size = makeImageSize(crossImage->size.width/4
                        ,crossImage->size.height/3,1);
    int i = 0;
    int row =0;
    Area a[] =  {   
       Area(size.width*2,size.height,size.width,size.height),      // X-
       Area(0,size.height,size.width,size.height),                 // X+
       Area(size.width,0,size.width,size.height),                  // Y+
       Area(size.width,size.height*2,size.width,size.height),      // Y-
       Area(size.width,size.height,size.width,size.height),        // Z-
       Area(size.width*3,size.height,size.width,size.height),      // Z+
    };
    
    for (i = 0; i < 6; i ++) {
        images[i].size = size;
        images[i].format = crossImage->format;
        images[i].type = crossImage->type;
        images[i].allocateSpace();
        for(row = 0; row < a[i].height; ++row){
            memcpy(images[i].getPixelIndex(0,row)
                    ,crossImage->getPixelIndex(a[i].x,row + a[i].y)
                    ,crossImage->pixelSize * size.width);
        }
    }
//    images[2].rotateCCW();
//    images[2].rotateCCW();
//   images[3].rotateCCW();
//    images[3].rotateCCW();
    return images;
}




}
