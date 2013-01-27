#ifndef ECPP3DCAMERA_H_
#define ECPP3DCAMERA_H_

#include "glm/glm.hpp"
namespace ECpp3d {

 /*
 * Class: Camera
 *
 * The idea beheind the Camera is that it is abel to tell, the projection
 * matrix and the view matrix.
 *
 *
 */

class Camera : public Object {
public:
    const glm::mat4 & getProjMatrix() const;
    const glm::mat4 & getViewMatrix() const;
};

}
#endif
