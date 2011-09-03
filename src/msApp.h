#pragma once

#include "ofMain.h"
#include "ofxLibdc.h"
#include "ofxMotionSensing.h"

//#define _USE_LIVE_VIDEO

class msApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

        #ifdef _USE_LIVE_VIDEO
		//ofVideoGrabber 		vidGrabber;
		ofxLibdc::Camera		camera;
		ofxLibdc::Grabber		grabber;
		ofxLibdc::PointGrey		pointGrey;
		#else 
		ofVideoPlayer			vidPlayer;
		#endif
	
		ofxMs::MotionSensing	tracker;
	
		ofImage					curFrame;
		int						camWidth, camHeight;
};

