#include <iostream>
#include <string>
#include <vector>

#include "colorf.h"

using namespace std;

vector<string> SplitWithCharacters(const string& str, int splitLength) {
  int NumSubstrings = str.length() / splitLength;
  vector<string> ret;

  for (int i = 0; i < NumSubstrings; i++) {
     ret.push_back(str.substr(i * splitLength, splitLength));
  }

  // If there are leftover characters, create a shorter item at the end.
  if (str.length() % splitLength != 0) {
      ret.push_back(str.substr(splitLength * NumSubstrings));
  }


  return ret;
}

Color::Color(float r, float g, float b) {
  this->r = r;
  this->g = g;
  this->b = b;
}

Color::Color() {
  this->r = 0;
  this->g = 0;
  this->b = 0;
}

auto Color::show() -> void {
  cout << "R: " << this->r << " G: " << this->g << " B: " << this->b << endl;
}

string Color::rgb2hex() {
  string hex = "#";

  hex += to_string(this->r*255);
  hex += to_string(this->g*255);
  hex += to_string(this->b*255);

  return hex;
}

Color hex2rgb(string hex) {
  Color c;

  if(hex.at(0) == '#') {
      hex.erase(0, 1);
  }

  while(hex.length() != 6) {
      hex += "0";
  }

  vector<string> colori=SplitWithCharacters(hex,2);

  c.r = (stoi(colori[0],nullptr,16)/255);
  c.g = (stoi(colori[1],nullptr,16)/255);
  c.b = (stoi(colori[2],nullptr,16)/255);
  
  return c;
}