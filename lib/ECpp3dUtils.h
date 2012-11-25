/*
 * ECpp3dUtils.h
 *
 *  Created on: 20/11/2012
 *      Author: christian
 */

#ifndef ECPP3DUTILS_H_
#define ECPP3DUTILS_H_


#include <iostream>
#include <string>
#include <sstream>
#include <vector>

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

    virtual void setMessage(const std::string & message){
    	this->message = std::string(message);
    }

    virtual const std::string getMessage() const {return message;}
    const std::string toString() const {return getMessage();}
};

void printspecs(std::ostream & out);


}



#endif /* ECPP3DUTILS_H_ */
