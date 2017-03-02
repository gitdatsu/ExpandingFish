#include "Fish.h"
//B#include "AllObj.h"

Fish::Fish() {
	//load image
	fish[0].loadImage("fish/left5.png");
	fish[1].loadImage("fish/left4.png");
	fish[2].loadImage("fish/left3.png");
	fish[3].loadImage("fish/left2.png");
	fish[4].loadImage("fish/middle0.png");
	fish[5].loadImage("fish/right2.png");
	fish[6].loadImage("fish/right3.png");
	fish[7].loadImage("fish/right4.png");
	fish[8].loadImage("fish/right5.png");
	setup();
}

void Fish::setup() {
	//Fish specify
	type = 1;//(int)ofRandom(3); 
	//pos
	pos = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
	pos = pos.rotate(ofRandom(-180,180));

	//speed,angle
	speed.x = ofRandom(-1.0, 1.0);
	speed.y = ofRandom(-1.0, 1.0);
	if (speed.x != 0) imgAngle = 180 * atan(speed.y / speed.x) / PI;
	else {
		if (speed.y > 0) imgAngle = 90;
		else imgAngle = -90;
	}

	//image
	imgNum = (int)ofRandom(8);
	imgState = true;
	imgAlpha = 255;
	b_imgWidth = 60;//base imgWidth b_imgWidth:b_imgHeight = 3:7
	b_imgHeight = 140;//base imageHeight
	imgWidth = b_imgWidth;
	imgHeight = b_imgHeight;
	imgChange = false;

	// color
	color = ofColor(255 * (int)ofRandom(2), 255 * (int)ofRandom(2), 255 * (int)ofRandom(2));
	if (color.red==0 && color.green==0 && color.blue==0) color = ofColor(255,255,255);
	
	//other
	frameCount = 0;
	
	lifeMax = 300.0;
	life = lifeMax;
	
	hitLength = 100;

	force.setup(type);
}

bool Fish::update(vector<ofVec2f> obs) {
	//death fish
	if (life <= 0) {
		if (imgWidth <= 0 || imgHeight <= 0) return false;
		imgAlpha-=5;
		if (imgAlpha<0) return false;
	}

	obslist = obs;
	move();
	//life decrease when pos is out of window.
	//if (!((-ofGetWidth() / 2 < pos.x&&pos.x < ofGetWidth() / 2) && (-ofGetHeight() / 2 < pos.y&&pos.y < ofGetHeight() / 2))) life--;
	
	changeImage();
	frameCount++;

	return true;
}

void Fish::draw() {
	ofPushMatrix();
	image.setAnchorPercent(0.5, 0.5);
	ofTranslate(pos.x, pos.y);
	ofRotateZ(imgAngle + 180);
	ofSetColor(color,imgAlpha);
	image.draw(0, 0, imgWidth, imgHeight);
	ofPopMatrix();
}

void Fish::move() {
	//vec
	calcVec();
	//speed
	speed = speed.getScaled(abs_speed+3*(1-life/lifeMax));
	//pos
	pos += speed;
}

void Fish::calcVec() {
	//force field
	addVec(force.getForce(pos));
	avoidObj(obslist);
	//adjust for image
	ofVec2f base = ofVec2f(1, 0);
	imgAngle = base.angle(speed) - 90;
}

void Fish::addVec(ofVec2f vec) {
	speed += vec;
}

void Fish::avoidObj(vector<ofVec2f> obs) {
	ofVec2f vec;
	for (int i = 0; i < obs.size(); i++) {
		vec = obs[i] - pos;//subtract pos and obs
		//hit
		if (vec.length() < 50 + hitLength*(1 - life / lifeMax)) {
			if (0 < life) {
				life -= 1;
			}
		}
	}
}

void Fish::changeImage() {
	//img size
	imgWidth = (1+5*(1-life/lifeMax))*b_imgWidth;
	imgHeight = (1+5*(1-life / lifeMax))*b_imgHeight;
	//img
	if (frameCount % 5 == 0) {
		if (imgNum <= 0) {
			imgState = true;
			imgNum = 1;
		}
		else if (imgNum >= 8) {
			imgState = false;
			imgNum = 6;
		}
		if (imgState) imgNum++;
		else imgNum--;
		image = fish[imgNum];
	}
}
