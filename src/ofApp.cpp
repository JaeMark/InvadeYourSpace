#include "ofApp.h"

#include "Projectile.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetWindowShape(750, 550);
	ofSetRectMode(OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofDrawRectangle(heroCoordinate.x, heroCoordinate.y, 20, 10);
	for (auto& heroProjectile : heroProjectiles) {
		heroProjectile.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'a') {
		heroCoordinate.x -= heroMovementSpeed;
	}
	if (key == 'd') {
		heroCoordinate.x += heroMovementSpeed;
	}
	if (key == 'w') {
		heroProjectiles.push_back(Projectile{ heroCoordinate, Projectile::Type::friendly });
	}

	if (heroCoordinate.x < leftBoundary) {
		heroCoordinate.x = leftBoundary;
	}
	if (heroCoordinate.x > rightBoundary) {
		heroCoordinate.x = rightBoundary;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
