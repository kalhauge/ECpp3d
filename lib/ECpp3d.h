//
//  ECpp3d.h
//  ecpp3d
//
//  Created by Christian Gram Kalhauge on 04/11/12.
//  Copyright (c) 2012 Kalhauge. All rights reserved.
//

#ifndef ecpp3d_ECpp3d_h
#define ecpp3d_ECpp3d_h

#include <iostream>
#include <string>
#include <sstream>
#include "ECpp3dOpenGL.h"

namespace ECpp3d {

class ECpp3dObject {
	virtual const std::string toString() const {
		std::stringstream s;
		s << "<ECpp3dObject at:" << this << ">";
		return s.str();
	}

	friend std::ostream& operator<< (std::ostream& stream, const ECpp3dObject& object) {
		return stream << object.toString();
	}
};

class ECpp3dException : public ECpp3dObject {
	std::string message;
public:
    ~ECpp3dException() {}

    virtual void setMessage(const char * message){
    	this->message = std::string(message);
    }

    virtual const std::string getMessage() const {return message;}
    const std::string toString() const {return getMessage();}
};

void printspecs(std::ostream & out);
}

#include "ECpp3dShaderProgram.h"
#include "ECpp3dMath.h"
#endif
