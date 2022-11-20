#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	// prevent window resize
	ofGLFWWindowSettings settings;
	settings.resizable = false;
	ofCreateWindow(settings);
	return ofRunApp(new ofApp);
}
