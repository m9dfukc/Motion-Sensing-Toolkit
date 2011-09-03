/*
 *  ofxMsOscSender.cpp
 *  msToolkit
 *
 *  Created by Andreas on 30.08.11.
 *  Copyright 2011 invertednothing. All rights reserved.
 *
 */

#include "ofxMsOscSender.h"

namespace ofxMs {
	
	OscSender::OscSender(){};
	
	OscSender::OscSender( string _ip, int _port )
	{
		setupSender( _ip, _port );
	};

	void OscSender::setupSender(string _ip, int _port)
	{
		ip = oldip = _ip;
		port = oldport = _port;
		
		stringstream message;
		message << "SETTING UP SENDER @ " <<ip<< ":" <<port;
		ofLog(OF_LOG_VERBOSE, message.str());
		
		setup(ip, port);
	};
	

	void OscSender::update()
	{ 
		if( strcmp( oldip.c_str(), ip.c_str() ) != 0 || oldport != port )
		{
			oldip = ip;
			oldport = port;
			reroute(ip, port);				
		}
	};
	
	void OscSender::movementUpdated( int cameraWidth, int cameraHeight )
	{
		ofxOscMessage m;
		m.setAddress("motionsensing/movementUpdated/");
		send(m);
	};
	
	void OscSender::send( ofxOscMessage m )
	{
		sendMessage(m);
	};
	
	void OscSender::reroute( string _ip, int _port )
	{
		stringstream portstream;
		portstream << _port;
		ofLog( OF_LOG_VERBOSE, "ofxMsOscSender: REROUTING TO " + ip + ", " + portstream.str() );
		ip = _ip;
		port = _port;
		setup( ip, port );
	};

}
