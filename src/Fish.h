#pragma once
#include "ofMain.h"
#include "Field.h"

//class AllObj;

class Fish {
private :
	//vec
	ofVec2f pos;
	ofVec2f speed;
	float abs_speed = 20.0f;
	//image
	ofImage image;
	ofImage fish[9];
	int imgNum;
	bool imgState;//how to exchange image
	float imgAngle;//object angle
	float imgAlpha;//alpha num
	float imgWidth, imgHeight;//image width,height
	float b_imgWidth, b_imgHeight;//base image width,height
	bool imgChange;//true:size change
	//force
	Field force;
	//other
	int type;//kind of moving, 0~3
	int frameCount;
	float life;//life use some method
	float lifeMax;//max life
	float hitLength;

	ofColor color;

	vector<ofVec2f> obslist;

public :
	Fish();

	void setup();
	bool update(vector<ofVec2f> obs);
	void draw();

	void move();
	void calcVec();
	void addVec(ofVec2f vec);
	void avoidObj(vector<ofVec2f> obs);
	void changeImage();
};