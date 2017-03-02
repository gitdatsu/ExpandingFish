#include "Field.h"

void Field::setup(int type) {
	colSize = ofGetWidth() / colNum;
	rowSize = ofGetHeight() / rowNum;
	ofVec2f v = ofVec2f(3, 0);
	switch (type) {
	case 0:
		//force circle
		for (int i = 0; i < colNum; i++) {
			for (int j = 0; j < rowNum; j++) {
				if (i < colNum / 2) {//
					if (j < rowNum / 2) {//2
						force[i][j] = ofVec2f(0, -1);
					}
					else {//3
						force[i][j] = ofVec2f(1, 0);
					}
				}
				else {
					if (j < rowNum / 2) {//1
						force[i][j] = ofVec2f(-1, 0);
					}
					else {//4
						force[i][j] = ofVec2f(0, 1);
					}
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 4; k++) {
					switch (i) {
					case 0://2
						force[j + 2][k] = ofVec2f(-1, -1);
						break;
					case 1://3
						force[k][j + 4] = ofVec2f(1, -1);
						break;
					case 2://4
						force[j + 4][k + 4] = ofVec2f(1, 1);
						break;
					case 3://1
						force[k + 4][j + 2] = ofVec2f(-1, 1);
						break;
					}
				}
			}
		}
		break;

	case 1:
		//force random
		for (int i = 0; i < colNum; i++) {
			for (int j = 0; j < rowNum; j++) {
				force[i][j] = v.rotate(ofRandom(360));
			}
		}
		break;

	case 2:
		//force face center.
		float x, y;
		for(int i=0;i<colNum;i++){
			x = colSize*i + colSize / 2;
			for (int j = 0; j < rowNum; j++) {
				y = rowSize*i + rowSize / 2;
				force[i][j].x = ofGetWidth() / 2 - x;
				force[i][j].y = ofGetHeight() / 2 - y;
			}
		}
		break;

	case 3:
		//force straight
		for(int i=0;i<colNum;i++){
			for (int j = 0; j < rowNum; j++) {
				force[i][j] = ofVec2f(1,0);
			}
		}
		break;

	default:
		//force straight
		for (int i = 0; i<colNum; i++) {
			for (int j = 0; j < rowNum; j++) {
				force[i][j] = ofVec2f(1, 0);
			}
		}
		break;
	}
}

ofVec2f Field::getForce(ofVec2f pos) {
	float x, y;//0~width,0~height
	x = pos.x + ofGetWidth() / 2;//pos.x => x
	y = pos.y + ofGetHeight() / 2;//pos.y => y
	if ((0 < x && x < ofGetWidth()) && (0 < y && y < ofGetHeight())) {//in Window
		int xNum, yNum;
		xNum = x / colSize;
		if (xNum < 0) xNum = 0;
		else if (colNum - 1 < xNum) xNum = colNum - 1;
		yNum = rowNum - (y / rowSize);
		if (yNum < 0) yNum = rowNum - 1;
		else if (rowNum - 1 < yNum) yNum = 0;
		return force[xNum][yNum];
	}
	else {// out of window
		return -pos.getScaled(3.0);
	}
}
