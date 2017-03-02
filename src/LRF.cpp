#include "LRF.h"


//exe 
void LRF::setup() {
	std::cout << "LRF->setup start." << std::endl;
	screen_width = 3400;
	screen_height = 2300;
	to_screen_length =150;
	connect_LRF();
}

vector<ofVec2f> LRF::update() {
	//setting_LRF(180, 4);
	exe_LRF(1);
	return obs;
}

void LRF::draw() {
	for (int i = 0; i < obs.size(); ++i) {
		ofPushMatrix();
		ofTranslate(obs[i].x,obs[i].y);
		ofSetColor(255, 255, 255);//0,0,0
		ofCircle(0,0,5);
		ofPopMatrix();
	}
}

void LRF::end_LRF() {
	std::cout << "begin end_LRF" << std::endl;
	urg_close(&urg);
}

// make method
void LRF::connect_LRF() {
	std::cout << "begin connect" << std::endl;
	const char connect_device[] = "COM3";
	const long connect_baudrate = 115200;

	try {
		std::cout << "begin connect -> urg_open" << std::endl;
		ret = urg_open(&urg, URG_SERIAL, connect_device, connect_baudrate);
		if (ret < 0) throw "open error.";
	}
	catch (const char *str) {
		std::cout << str << std::endl;
	}
}

void LRF::setting_LRF(int deg, int step) {
	std::cout << "begin setting_LRF" << std::endl;
	if (0 < deg&&deg < 240) {//
		first_step = urg_rad2step(&urg, -deg / 2);
		last_step = urg_rad2step(&urg, deg / 2);
	}
	else {
		first_step = -120;
		last_step = 120;
	}
	skip_step = step;

	try {
		ret = urg_set_scanning_parameter(&urg, first_step, last_step, skip_step);
			if (ret < 0) throw "set scanning parameter error.";
			//length_data = (long *)malloc(sizeof(long) * urg_max_data_size(&urg));
			//if (length_data == NULL) throw "malloc error.";
	}
	catch (const char *str) {
		std::cout << str << std::endl;
	}
}

void LRF::exe_LRF(int st) {
	try {
		length_data = (long *)malloc(sizeof(long) * urg_max_data_size(&urg));
			if (length_data == NULL) throw "malloc error.";
		ret = urg_start_measurement(&urg, URG_DISTANCE, scan_time, 0);//1,scan_time
			if (ret < 0) throw "start_measurement error.";
		length_data_size = urg_get_distance(&urg, length_data, NULL);//NULL,&timestamp
			if (length_data_size < 0) throw "get_distance error.";
	}
	catch (const char *str) {
		std::cout << str << std::endl;
	}
	calc_LRF();
}






void LRF::calc_LRF() {
	obs.erase(obs.begin(), obs.end());
	float winX = ofGetWidth();
	float winY = ofGetHeight();
	for (int i = 0; i < length_data_size; ++i) {
		radian = urg_index2rad(&urg, i);
		length = length_data[i];
		// \todo check length is valid
		pos = ofVec2f((long)(length * cos(radian)), (long)(length * sin(radian)));
		pos.rotate(90);
		//pos is position of LRF.
		if (inScreen(pos)) {
			pos.x = ofMap(pos.x, -screen_width / 2, screen_width / 2, -winX / 2, winX / 2);
			pos.y = ofMap(pos.y-to_screen_length, 0, screen_height, -winY / 2, winY / 2+200);
			//pos is position of pixel
			obs.emplace_back(pos);
		}
	}
}

bool LRF::inScreen(ofVec2f lrf_pos) {
	if (-screen_width / 2 < lrf_pos.x && lrf_pos.x < screen_width / 2) {//x check
		if (to_screen_length < lrf_pos.y && lrf_pos.y < screen_height+to_screen_length) {//y check
			return true;
		}
	}
	return false;
}

int LRF::getsize() {
	return length_data_size;
}

void LRF::printData_LRF() {
	for (int i = 0; i < length_data_size; i++) {
		std::cout << length_data[i] << std::endl;
	}
	if (0 < length_data_size) std::cout << "print." << std::endl;
}
