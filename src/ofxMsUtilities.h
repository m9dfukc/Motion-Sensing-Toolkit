/*
 *  ofxMsUtilities.h
 *  msToolkit
 *
 *  Created by Andreas on 01.09.11.
 *  Copyright 2011 invertednothing. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxCv.h"

namespace ofxMs {
	
	namespace utilities {
	
		using namespace cv;
		using namespace ofxCv;
		
		void getSubImage( ofImage* input, ofImage* output, const ofPoint dst[4] )  
		{ 
			int inW  = input->getWidth(); 
			int inH  = input->getHeight();  
			int outW = output->getWidth();  
			int outH = output->getHeight();  
			int bpp  = 1;
			unsigned char* inputData	= input->getPixels();
			unsigned char* outputData	= output->getPixels();
			
			int x1 = dst[0].x;
			int y1 = dst[0].y;
			int x2 = dst[1].x;
			int y2 = dst[1].y;  
			int x3 = dst[2].x;
			int y3 = dst[2].y; 
			int x4 = dst[3].x;
			int y4 = dst[3].y;
			
			for(int x=0;x<outW;x++) 
			{  
				for(int y=0;y<outH;y++) 
				{  
					float xlrp = x/(float)outW;  
					float ylrp = y/(float)outH;  
					int xinput = (x1*(1-xlrp)+x2*xlrp)*(1-ylrp) + (x4*(1-xlrp)+x3*xlrp)*ylrp;  
					int yinput = (y1*(1-ylrp)+y4*ylrp)*(1-xlrp) + (y2*(1-ylrp)+y3*ylrp)*xlrp;  
					int inIndex = (xinput + yinput*inW)*bpp;  
					int outIndex = (x+y*outW)*bpp;  
					memcpy((void*)(outputData+outIndex),(void*)(inputData+inIndex),sizeof(unsigned char)*bpp);  
				}  
			}  
		};
		
		
		ofVec2f getFlowOffset( const Mat& flow, int x, int y ) 
		{
			const Vec2f& vec = flow.at<Vec2f>(y, x);
			return ofVec2f(vec[1], vec[0]);
		};
		
		
		ofVec2f getFlowPosition( const Mat& flow, int x, int y ) 
		{
			const Vec2f& vec = flow.at<Vec2f>(y, x);
			return ofVec2f(x + vec[1], y + vec[0]);
		};
		
		
		void drawFlow( const Mat& flow, unsigned int stepSize ) 
		{
			for( int i = 0; i < flow.rows; i += stepSize ) 
			{
				for( int j = 0; j < flow.cols; j += stepSize ) 
				{
					ofVec2f cur(j, i);
					ofLine(cur, getFlowPosition(flow, j, i));
				} 
			}
		};
		
		void drawFeatures( vector<Point2f>& prevPts, vector<Point2f>& nextPts ) 
		{
			for( int i = 0; i < prevPts.size(); i++ ) 
			{
				ofLine( toOf(prevPts[i]), toOf(nextPts[i]) );
			}
		};
		
	};
	
};

