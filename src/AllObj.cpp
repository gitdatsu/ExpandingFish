#include "AllObj.h"

void AllObj::setup() {
	//new fish porn
	for (int i = 0; i < fishlistSize; i++) {
		fishlistVec.emplace_back();
	}
}

void AllObj::update(vector<ofVec2f> obs) {
	for (int i = 0; i < fishlistVec.size(); i++) {
		if (!fishlistVec[i].update(obs)) {//if life of a fish is 0
			//delete fish
			fishlistVec.erase(fishlistVec.begin() + i);
			if (fishlistVec.size() < 3) {
				//new fish porn
				for (int i = fishlistVec.size(); i < fishlistSize; i++) {
					fishlistVec.emplace_back();
				}
			}
			
		}
	}
}

void AllObj::draw() {
	for (int i = 0; i < fishlistVec.size(); i++) {
		fishlistVec[i].draw();
	}
}
