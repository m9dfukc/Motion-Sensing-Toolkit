/*
 *  ofxMsGuiManager.h
 *  msToolkit
 *
 *  Created by Andreas on 30.08.11.
 *  Copyright 2011 invertednothing. All rights reserved.
 *
 */

#pragma once

#include "ofxAutoControlPanel.h"
#include "ofxMsSettings.h"
#include "ofxCvCoordWarpingGui.h"

namespace ofxMs {
	
	class GuiManager : public ofxAutoControlPanel {
	public:
		void setup(int fW, int fH);
		void draw();
		void update();
		void setActivePreview(int previewIndex);
		
		void keyPressed(ofKeyEventArgs& event);
		
	private:
		ofxCvCoordWarpingGui quadGui;
		int activePreviewIndex;
		int frameWidth;
		int frameHeight;
	};
	
}


