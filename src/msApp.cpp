#include "msApp.h"

void msApp::setup(){
	
	/*
	pointGrey.setup();
	pointGrey.set1394b(true);
	pointGrey.setSize(320, 240);
	 */
	vidPlayer.loadMovie("test.mov");
	vidPlayer.play();
	curFrame.allocate(vidPlayer.getWidth(), vidPlayer.getHeight(), OF_IMAGE_COLOR);
		
	tracker.setup(&curFrame);

}

void msApp::update(){
	ofBackground(100, 100, 100);
	
	bool bNewFrame = false;
	
	vidPlayer.idleMovie();
	bNewFrame = vidPlayer.isFrameNew();
	
	if( bNewFrame ) 
	{
		curFrame.setFromPixels(vidPlayer.getPixels(), vidPlayer.getWidth(), vidPlayer.getHeight(), OF_IMAGE_COLOR);
		curFrame.setImageType(OF_IMAGE_GRAYSCALE);
		curFrame.update();
		
		tracker.update();
	}

	/*
	if(pointGrey.grabVideo(curFrame)) {
		curFrame.update();
		tracker.update(&curFrame);
	}*/
}

void msApp::draw(){
	tracker.draw();
}

void msApp::keyPressed(int key){

	switch (key){
		case ' ':
			std::cout << " spacebar " << std::endl;
			break;
	}
}

void msApp::keyReleased(int key){

}

void msApp::mouseMoved(int x, int y ){

}

void msApp::mouseDragged(int x, int y, int button){

}

void msApp::mousePressed(int x, int y, int button){

}

void msApp::mouseReleased(int x, int y, int button){

}

void msApp::windowResized(int w, int h){

}

void msApp::gotMessage(ofMessage msg){

}

void msApp::dragEvent(ofDragInfo dragInfo){ 

}
