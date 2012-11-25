//
// ECpp3d.cpp


#include "ECpp3dUtils.h"

namespace ECpp3d {

void printspecs(std::ostream & out) {
  out << "Vendor:   " << glGetString(GL_VENDOR) << std::endl;
  out << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
  out << "Version:  " << glGetString(GL_VERSION) << std::endl;
  out << "GLSL:     " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

}
typedef std::vector<ECpp3dObject> objects;


}

