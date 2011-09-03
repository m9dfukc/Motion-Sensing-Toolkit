/*
 *  ofxMsGuiManager.cpp
 *  msToolkit
 *
 *  Created by Andreas on 30.08.11.
 *  Copyright 2011 invertednothing. All rights reserved.
 *
 */

#include "ofxMsGuiManager.h"

namespace ofxMs {
	
	void GuiManager::setup( int fW, int fH ) 
	{
		frameWidth  = fW;
		frameHeight = fH;
		
		Settings* settings = Settings::getInstance();
		
		ofxAutoControlPanel::setup(250, 500);
		
		addPanel("calcOpticalFlowFarneback");
		addSlider("gridSize", 5, 2, 30, true);
		addSlider("pyrScale", .5, 0, 1);
		addSlider("levels", 4, 1, 8, true);
		addSlider("winsize", 8, 4, 64, true);
		addSlider("iterations", 2, 1, 8, true);
		addSlider("polyN", 7, 5, 10, true);
		addSlider("polySigma", 1.5, 1.1, 2);
		addToggle("FARNEBACK_GAUSSIAN", true);
		
		addPanel("calcOpticalFlowPyrLK");
		addSlider("winSize", 32, 4, 64, true);
		addSlider("maxLevel", 3, 0, 8, true);
		addSlider("maxFeatures", 200, 1, 1000);
		addSlider("qualityLevel", 0.01, 0.001, .02);
		addSlider("minDistance", 4, 1, 16);
		
		settings->quadWarpOriginal[0].set(0, 0);
		settings->quadWarpOriginal[1].set(frameWidth, 0);
		settings->quadWarpOriginal[2].set(frameWidth, frameHeight);
		settings->quadWarpOriginal[3].set(0, frameHeight);
		
		settings->quadWarpScaled[0].set(0, 0);
		settings->quadWarpScaled[1].set(frameWidth, 0);
		settings->quadWarpScaled[2].set(frameWidth, frameHeight);
		settings->quadWarpScaled[3].set(0, frameHeight);
		
		quadGui.setup("undist");
		quadGui.width  = frameWidth;
		quadGui.height = frameHeight;
		quadGui.disableAppEvents();
		
		ofPoint quadSrc[4];
		quadSrc[0].set(0, 0);
		quadSrc[1].set(frameWidth, 0);
		quadSrc[2].set(frameWidth, frameHeight);
		quadSrc[3].set(0, frameHeight);
		quadGui.setQuadPoints(quadSrc);
		quadGui.bCameraView = true;
		
	}
	
	void GuiManager::update()
	{
		Settings* settings = Settings::getInstance();
		
		ofPoint * scaledPoints = quadGui.getScaledQuadPoints(frameWidth,frameHeight);
		for( int i=0; i<4; i++ )
		{
			settings->quadWarpScaled[i] = scaledPoints[i];
		}
	}
	
	void GuiManager::setActivePreview(int previewIndex)
	{
		/* todo: catch the active preview and activate the predistortion/the levelgrid/... */
	}
	
	void GuiManager::draw() 
	{
		quadGui.draw();
	}
	
	void GuiManager::keyPressed( ofKeyEventArgs& event ) 
	{
		/* todo: overwrite this in the final version */
		if(event.key == '\t') 
		{
			if(hidden) 
			{
				show();
			} 
			else 
			{
				hide();
			}
		}
		
		if(event.key == 'f') 
		{
			ofToggleFullscreen();
		}
	}
	
}
