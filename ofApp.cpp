#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);

	this->hexagon_height = 40;
	this->hexagon_width = 10;
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int x = 120; x <= ofGetWidth() - 120; x += this->hexagon_height * 1.5) {

		for (int y = 120; y <= ofGetHeight() - 120; y += this->hexagon_height * 3) {

			this->draw_digital(glm::vec2(x, y));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_digital(glm::vec2 location) {

	vector<pair<glm::vec2, float>> part_list = {
		make_pair<glm::vec2, float>(location + glm::vec2(0, -this->hexagon_height), 90),
		make_pair<glm::vec2, float>(location + glm::vec2(this->hexagon_height * -0.5, this->hexagon_height * 0.5), 0),
		make_pair<glm::vec2, float>(location + glm::vec2(this->hexagon_height * 0.5, this->hexagon_height * 0.5), 0),
		make_pair<glm::vec2, float>(location + glm::vec2(0, 0), 90),
		make_pair<glm::vec2, float>(location + glm::vec2(this->hexagon_height * -0.5, this->hexagon_height * -0.5), 0),
		make_pair<glm::vec2, float>(location + glm::vec2(this->hexagon_height * 0.5, this->hexagon_height * -0.5), 0),
		make_pair<glm::vec2, float>(location + glm::vec2(0, this->hexagon_height), 90)
	};

	for (auto& part : part_list) {

		auto noise_value = ofNoise(part.first.x, part.first.y, (ofGetFrameNum() + ofRandom(1000)) * 0.015);

		if (noise_value < 0.65) {
		
			this->draw_hexagon(part.first, part.second);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_hexagon(glm::vec2 location, float deg) {

	ofPushMatrix();
	ofTranslate(location);
	ofRotate(deg);

	vector<glm::vec2> vertices;

	vertices.push_back(glm::vec2(this->hexagon_width * -0.4, this->hexagon_height * -0.4));
	vertices.push_back(glm::vec2(this->hexagon_width * -0.4, this->hexagon_height *  0.4));
	vertices.push_back(glm::vec2(0, this->hexagon_height *  0.5));
	vertices.push_back(glm::vec2(this->hexagon_width *  0.4, this->hexagon_height *  0.4));
	vertices.push_back(glm::vec2(this->hexagon_width *  0.4, this->hexagon_height * -0.4));
	vertices.push_back(glm::vec2(0, this->hexagon_height *  -0.5));

	ofFill();
	ofSetColor(39);

	ofBeginShape();
	ofVertices(vertices);
	ofEndShape(true);

	ofNoFill();
	ofSetColor(239);

	ofBeginShape();
	ofVertices(vertices);
	ofEndShape(true);

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}