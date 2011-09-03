/*
 *  ofxMsOscSender.h
 *  msToolkit
 *
 *  Created by Andreas on 30.08.11.
 *  Copyright 2011 invertednothing. All rights reserved.
 *
 */

#pragma once

#include "ofxOSC.h"

namespace ofxMs {

	class OscSender : public ofxOscSender
	{
	public :
		string	ip, oldip;
		int		port, oldport;
		
		OscSender();
		OscSender( string _ip, int _port );
		void setupSender(string _ip, int _port);
		void update();
		
		/* Baustelle, Vektorliste zu übergeben! */
		void movementUpdated ( int cameraWidth, int cameraHeight );
		
		void send ( ofxOscMessage m );
		void reroute( string _ip, int _port );
		
	};
	
}
