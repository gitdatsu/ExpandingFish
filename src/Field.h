#pragma once
#include "ofMain.h"
class Field {
private :
	ofVec2f force[8][8];
	int colNum = 8;
	int rowNum = 8;
	float colSize, rowSize;

public :
	void setup(int type);
	ofVec2f getForce(ofVec2f pos);
};