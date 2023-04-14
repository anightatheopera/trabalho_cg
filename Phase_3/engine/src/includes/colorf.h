#ifndef COLORF_H
#define COLORF_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Color {
	public:
  		float r;
  		float g;
  		float b;

		Color(float r, float g, float b);
		Color(string hex);
		Color();

		auto show() -> void;
		auto apply() -> void;
	

};

#endif
