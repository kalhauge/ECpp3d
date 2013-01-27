//
//  ECpp3dImage.h
//  ECpp3d
//
//  Created by Christian Gram Kalhauge on 22/01/13.
//
//

#ifndef ECpp3d_ECpp3dImage_h
#define ECpp3d_ECpp3dImage_h

#include "ECpp3dUtils.h"
#include <glm/glm.hpp>

namespace ECpp3d {

struct ImageSize {
    GLsizei width;
    GLsizei height;
    GLsizei depth;
};

ImageSize makeImageSize(GLsizei width,GLsizei height,GLsizei depth);


class Image : public Object {
	GLenum      format;
	GLenum      type;
	ImageSize   size;
	GLubyte*    data;
    GLsizei     pixelSize;

    void allocateSpace();
    void clearSpace();
public:

	typedef std::pair<float,glm::vec4> gradvector;
	typedef std::vector<gradvector> gradient;
    Image();
    Image(ImageSize size);
    Image(ImageSize size,GLenum data_format, GLenum data_type);
    ~Image();
 
    GLenum getFormat() const;
    GLenum getType() const;
    const GLubyte * getData() const;
    const ImageSize & getSize() const;
   
    GLubyte * getPixelIndex(GLsizei x, GLsizei y);
    const GLubyte * getPixelIndex(GLsizei x, GLsizei y) const;

    Image * rotateCCW();

    void toJPEG(const std::string & filename, int quality = 100) const throw (IOException);

    static Image * fromJPEG(const std::string & filename)
        throw (IOException);
    static Image * fromGradient(GLint width, const gradient & gradient);
    static Image * createCubeMapImages(const Image * jpg);

};
    
}


#endif
