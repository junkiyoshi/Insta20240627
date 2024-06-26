#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(1.2);
	ofEnableDepthTest();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	//ofRotateX(ofGetFrameNum());
	//ofRotateY(ofGetFrameNum());

	ofColor color;

	ofFill();
	ofSetColor(0);
	ofDrawSphere(245);

	for (int k = 0; k < 20; k++) {

		color.setHsb(ofRandom(255), 255, 255);

		ofPushMatrix();
		ofRotateZ(ofRandom(360));

		auto location = glm::vec3(0, 0, 250);
		auto radius = (int)(ofRandom(1000) + ofGetFrameNum() * 2) % 180 - 100;

		if (radius < 0) {

			auto z = ofMap(radius, -100, 0, 1500, 0);

			ofSetColor(color);
			ofDrawLine(location + glm::vec3(0, 0, z), location + glm::vec3(0, 0, z + 80));
		}
		else {

			ofSetColor(color, radius > 25 ? ofMap(radius, 25, 80, 255, 0) : 255);

			ofNoFill();
			ofBeginShape();
			for (int deg = 0; deg < 360; deg++) {

				auto vertex = location + glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
				vertex = glm::normalize(vertex) * 250;

				ofVertex(vertex);
			}
			ofEndShape(true);

			ofSetColor(color, radius > 25 ? ofMap(radius, 25, 80, 32, 0) : 32);

			ofFill();
			ofBeginShape();
			for (int deg = 0; deg < 360; deg++) {

				auto vertex = location + glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
				vertex = glm::normalize(vertex) * 250;

				ofVertex(vertex);
			}
			ofEndShape(true);
		}

		ofPopMatrix();
	}

	this->cam.end();

	int start = 270 + 62;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}