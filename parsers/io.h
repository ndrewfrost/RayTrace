/*
 * io.h
 *
 */

#ifndef IO_H_
#define IO_H_

#include <iostream>
#include "math/geometry.h"


namespace PPMWriter{

	template<typename T>
	void PPMWriter(const int width,const int height,Vec3<T>* framebuffer, const char* filename){
		std::ofstream ofs(filename, std::ios::out | std::ios::binary);
		ofs << "P6\n" << width << " " << height << "\n255\n";
		for (uint32_t i = 0; i < height * width; ++i) {
		char r = (char)(framebuffer[i].x);
		char g = (char)(framebuffer[i].y);
		char b = (char)(framebuffer[i].z);
		ofs << r << g << b;
		}

		ofs.close();

	}
};



#endif /* PMMWRITER_H_ */
