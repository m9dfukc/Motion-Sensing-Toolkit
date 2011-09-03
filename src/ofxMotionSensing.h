/*
 *  ofxMotionSensing.h
 *  msToolkit
 *
 *  Created by Andreas on 30.08.11.
 *  Copyright 2011 invertednothing. All rights reserved.
 *
 */
#pragma once

#include "ofxMsSettings.h"
#include "ofxMsGuiManager.h"
#include "ofxMsView.h"
#include "ofxCv.h"
#include "ofxMsOscSender.h"

#define CAMERA_PREVIEW		0
#define ADJUSTED_PREVIEW	1
#define DATA_PREVIEW		2

namespace ofxMs {
	
	using namespace cv;
	using namespace ofxCv;
	
	class MotionSensing {

	public:
		MotionSensing();
		~MotionSensing();
		void setup();
		void setup(ofImage* _source);
		void setSource(ofImage* _source);
		void update();
		void draw();
		
		void setupOsc(string ip, int port);
		void setVideoGrabber(ofVideoGrabber* grabber);
		
		void updatePreview();
		void setActivePreview(int previewIndex);
		
		bool inCameraView();
		bool inAdjustedView();
		bool inDataView();
		
	protected:
		
		void trackMotion();
		
		int width, height;
		bool bSource, bDimensions, bGui;
		
		Mat flow;
		ofImage prev, next, undist, camera;
		ofImage* source;
		
		vector<Point2f> prevPts, nextPts;
		
		ofRectangle activeView;
		View cameraPreview;
		View adjustedPreview;
		View dataPreview;
		int oldPreviewIndex, activePreviewIndex;

		ofxCvCoordWarpingGui quadGui;
		
		OscSender oscClient;
		GuiManager panel;
		
	};
	
}


