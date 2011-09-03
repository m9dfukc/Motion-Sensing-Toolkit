/*
 *  ofxMsSettings.h
 *  msToolkit
 *
 *  Created by Andreas on 30.08.11.
 *  Copyright 2011 invertednothing. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include <iostream>

namespace ofxMs {
	
	class Settings {
	public:
		static Settings* getInstance();
		void method();
		~Settings() 
		{
			delete single;
			instanceFlag = false;
		}
		
		// tracking vars
		int smooth;
		bool bDampMotionVector;
				
		// communication vars
		bool bSendOsc;
		string oscHost;
		int oscPort;
		
		// layout vars
		int lastCurrentPanel;
		int currentPanel;
		
		// quad warping
		ofPoint quadWarpScaled[4];
		ofPoint quadWarpOriginal[4];
		
		// xml file
		vector <string> xmlFiles;
		string currentXmlFile;
		
		// video grabber to access camera settings
		// might be NULL!
		ofVideoGrabber* videoGrabber;
		
	private:
		static bool instanceFlag;
		static Settings *single;
		Settings() 
		{
			videoGrabber = NULL;
			//private constructor
		}
	};
	
}
