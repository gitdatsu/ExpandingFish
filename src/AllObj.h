#pragma once
#include <vector>
#include "ofMain.h"
#include "Fish.h"

//class Fish;
/*

*/
class AllObj {
private:
	//all fish
	const int fishlistSize = 15;
	vector<Fish> fishlistVec;//all fish

	//all obs
	vector<ofVec2f> obs;//all obstacle

public:
	void setup();
	void update(vector<ofVec2f> obs);
	void draw();
};