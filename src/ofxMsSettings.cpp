/*
 *  ofxMsSettings.cpp
 *  msToolkit
 *
 *  Created by Andreas on 30.08.11.
 *  Copyright 2011 invertednothing. All rights reserved.
 *
 */

#include "ofxMsSettings.h"

namespace ofxMs { 
	
	bool Settings::instanceFlag = false;
	Settings* Settings::single = NULL;

	Settings* Settings::getInstance()
	{
		if( !instanceFlag )
		{
			single = new Settings();
			instanceFlag = true;

			single->smooth = 0; 
			single->oscHost = "localhost";
			single->oscPort = 12000;
			
		}
		return single;
	}
}
