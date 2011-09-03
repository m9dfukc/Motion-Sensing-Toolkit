/*
 *  ofxMotionSensing.cpp
 *  msToolkit
 *
 *  Created by Andreas on 30.08.11.
 *  Copyright 2011 invertednothing. All rights reserved.
 *
 */

#include "ofxMotionSensing.h"
#include "ofxMsUtilities.h"

//scales down tracking images for improved performance
#define TRACKING_SCALE_FACTOR .25

//Fix for FMAX not in Visual Studio C++
#if defined _MSC_VER
#define fmax max
#define fmin min
#pragma warning (disable:4996)
#define snprintf sprintf_s
#endif

namespace ofxMs {
	
	MotionSensing::MotionSensing()
	{
		bSource = bDimensions = bGui = false;
	}
	
	MotionSensing::~MotionSensing()
	{
		/* todo: free all the event stuff from the GuiManager */
	}
	
	void MotionSensing::setup() 
	{
		if( !bSource ) 
		{ 
			ofLogWarning() << "Input Source not set!" << std::endl;
			return;
		}
		
		width    = (int)((float)source->getWidth() * TRACKING_SCALE_FACTOR);
		height   = (int)((float)source->getHeight() * TRACKING_SCALE_FACTOR);
		
		prev.allocate(width, height, OF_IMAGE_GRAYSCALE);
		next.allocate(width, height, OF_IMAGE_GRAYSCALE);
		undist.allocate(width, height, OF_IMAGE_GRAYSCALE);
		camera.allocate(width, height, OF_IMAGE_GRAYSCALE);
		
		panel.setup(width, height);
		
		cameraPreview.setup(width, height, CAMERA_PREVIEW);
		cameraPreview.setImage(camera);
		
		adjustedPreview.setup(width, height, ADJUSTED_PREVIEW);
		adjustedPreview.setImage(undist);
		
		dataPreview.setup(width, height, DATA_PREVIEW);
		dataPreview.setImage(prev);
		
		if( !bGui )
		{
			cameraPreview.setTitle("Camera Input View", "Camera");
			cameraPreview.setColor(218,173,90);

			adjustedPreview.setTitle("Adjusted Camera View", "Adjusted");
			adjustedPreview.setColor(174,139,138);
			
			dataPreview.setTitle("Data Output View", "Output");
			dataPreview.setColor(113,171,154);
			
			activePreviewIndex = 2;
		}
		
		bGui = bDimensions = true;
	}
	
	void MotionSensing::setup( ofImage* _source ) 
	{ 
		if( _source->getWidth() > 0 && _source->getHeight() > 0) 
		{
			bSource = true;
			source = _source;
		}
		setup();
	}
	
	void MotionSensing::setSource( ofImage* _source ) 
	{ 
		if( source != _source && _source->getWidth() > 0 && _source->getHeight() > 0 ) 
		{
			bSource = true;
			source = _source;
		}
		setup();
	}
	
	void MotionSensing::update() 
	{
		if( !bGui || !bDimensions || !bSource ) return;
		
		Settings* settings = Settings::getInstance();

		camera.setFromPixels(source->getPixels(), source->getWidth(), source->getHeight(), OF_IMAGE_GRAYSCALE);
		camera.resize(width, height);
		
		utilities::getSubImage(&camera, &undist, settings->quadWarpScaled);
		prev.setFromPixels(next.getPixels(), next.getWidth(), next.getHeight(), OF_IMAGE_GRAYSCALE);
		next.setFromPixels(undist.getPixels(), undist.getWidth(), undist.getHeight(), OF_IMAGE_GRAYSCALE);
				
		cameraPreview.update(camera);
		adjustedPreview.update(undist);
		dataPreview.update(prev);
		
		panel.update();
		trackMotion();
	}
	
	
	void MotionSensing::trackMotion()
	{
		if( !bGui || !bDimensions || !bSource ) return;
		
		if(panel.getSelectedPanel() == 0) 
		{
			calcOpticalFlowFarneback(
									 toCv(prev),
									 toCv(next),
									 flow,
									 panel.getValueF("pyrScale"),
									 panel.getValueF("levels"),
									 panel.getValueF("winsize"),
									 panel.getValueF("iterations"),
									 panel.getValueF("polyN"),
									 panel.getValueF("polySigma"),
									 panel.getValueB("FARNEBACK_GAUSSIAN") ? OPTFLOW_FARNEBACK_GAUSSIAN : 0
									 );
		} 
		else 
		{
			prevPts.clear();
			goodFeaturesToTrack(
								toCv(prev),
								prevPts,
								panel.getValueI("maxFeatures"),
								panel.getValueF("qualityLevel"),
								panel.getValueF("minDistance"));
			
			vector<uchar> status;
			vector<float> err;
			int winSize = panel.getValueI("winSize");
			calcOpticalFlowPyrLK(
								 toCv(prev),
								 toCv(next),
								 prevPts,
								 nextPts,
								 status,
								 err,
								 cv::Size(winSize, winSize),
								 panel.getValueI("maxLevel")
								 );
		}
	}
	
	
	void MotionSensing::draw()
	{
		if( !bGui || !bDimensions || !bSource ) return;
		
		ofBackground(0);
		
		ofPushMatrix();
		
		ofSetColor(255);
		ofTranslate(0, 0);
		ofScale(1.0, 1.0, 1.0);
		
		cameraPreview.draw();
		adjustedPreview.draw();
		dataPreview.draw();
		
		/*
		camera.draw(0, 0);
		panel.draw();
		prev.draw(width, 0);
		next.draw(width*2, 0);
		 */
		
		ofTranslate(width*2, 0);
		if(panel.getSelectedPanel() == 0) {
			utilities::drawFlow(flow, panel.getValueF("gridSize"));
		} else {
			utilities::drawFeatures(prevPts, nextPts);
		}
		
		ofPopMatrix();	
	}
	
	
	void MotionSensing::setupOsc( string ip, int port ) 
	{
		// todo
	}
	
	
	void MotionSensing::setVideoGrabber( ofVideoGrabber* grabber )
	{
		// todo
	}
	
	
	void MotionSensing::updatePreview()
	{
		
	}
	
	void MotionSensing::setActivePreview(int previewIndex)
	{
		
	}

	bool MotionSensing::inCameraView()
	{
		// todo
		return true;
	}
	
	
	bool MotionSensing::inAdjustedView() 
	{
		// todo
		return true;
	}
	
	
	bool MotionSensing::inDataView() 
	{
		// todo
		return true;
	}

}

