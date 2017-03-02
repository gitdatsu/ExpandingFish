#pragma once
#include "urg_sensor.h"
#include "urg_utils.h"
#include <stdlib.h>
#include <iostream>
#include "ofMain.h"

/*
how to use this class
1.connect_LRF
2.setting_LRF
*/


class LRF {
private:
	//base
	urg_t urg;//urg
	int ret;//return to error check
	long *length_data;//data list
	int length_data_size;//data list size
	//setting para
	int scan_time;
	int first_step;//digree start
	int last_step;//digree end
	int skip_step;
	//timestamp
	long timestamp;
	//calc
	double radian;
	long length;
	ofVec2f pos;
	vector<ofVec2f> obs;
	//screen
	float screen_width, screen_height;//display window on floor this size.
	float to_screen_length;//length of urg to bottom of window

public:
	//urg method
	void connect_LRF();
	void setting_LRF(int deg, int step);
	void exe_LRF(int st);
	void end_LRF();
	void printData_LRF();
	void calc_LRF();
	//other
	void setup();
	vector<ofVec2f> update();
	void draw();
	int getsize();
	bool inScreen(ofVec2f lrf_pos);
};