/*
 *  ofxMsView.h
 *  msToolkit
 *
 *  Created by Andreas on 30.08.11.
 *  Copyright 2011 invertednothing. All rights reserved.
 *
 */

#pragma once

#include "ofxOpenCv.h"
#include "ofxCv.h"

#define preview_width 160
#define preview_height 120

#define large_width 640
#define large_height 480

#define view_spacing 10
#define view_smallBorder 2
#define view_largeBorder 10


namespace ofxMs {

	
	using namespace cv;
	using namespace ofxCv;
		
	class View : public ofRectangle {
	public:
		
		View()
		{
			bImage = false;
		}
		
		~View()
		{
			bImage = false;
		}
		
		void setup( int w, int h, int _viewId = 0 )
		{
			ofAddListener(ofEvents.mouseMoved, this, &View::mouseMoved);
			image.allocate(w, h, OF_IMAGE_GRAYSCALE);
			bActive = bRolled = false;
			viewId = _viewId;
			width = preview_width;
			height = preview_height;
			x = _viewId * (preview_width + view_spacing);
			y = large_height + view_spacing;
		};
		
		void setImage( ofImage _image )
		{
			bImage = true;
			image = _image;
		}
		
		void setColor( int r, int g, int b )
		{
			color.r = r;
			color.g = g;
			color.b = b;
		}
		
		void setActive( bool active=true )
		{
			bActive = active;
		}
		
		void setTitle( string _title, string _shortTitle = "" )
		{
			title = _title;
			if (_shortTitle == "") shortTitle = title;
			else shortTitle = _shortTitle;
		}
		
		void update( ofImage _image )
		{
			bImage = true;
			image = _image;
		}

		void draw()
		{
			ofPushStyle();
			ofDisableAlphaBlending();
			ofPushMatrix();
			//ofTranslate( (int)x, (int)y );
			
			//draw border
			if( bRolled && !bActive )
			{
				ofNoFill();
				ofSetLineWidth(3);
				ofSetColor(color.r, color.g, color.b);
				ofRect(-1,-1,width+2,height+2);			
			} 
			else if( bActive )
			{			
				ofNoFill();
				ofSetLineWidth(3);
				ofSetColor( color.r, color.g, color.b );
				ofRect( -1, -1, width+2, height+2 );
				ofFill();	
				ofRect( -2, height+view_smallBorder*3 + 1, width+2, view_largeBorder*2 );
			};
			
			ofFill(); 
			ofSetHexColor(0xffffff);
			
			ofDrawBitmapString( shortTitle, view_largeBorder, height + view_largeBorder*2 );
			
			if ( bRolled || bActive ) ofSetColor( color.r, color.g, color.b );
			if ( image.getWidth() > 0 && image.getHeight() > 0 && bImage ) image.draw( x, y, width, height );
			else ofLog(OF_LOG_WARNING, title+" image not allocated!");
			
			ofPopMatrix();
			ofPopStyle();
			
		};
		
		void drawLarge()
		{		
			if ( image.getWidth() > 0 && image.getHeight() > 0 && bImage ) image.draw( 0, 0, large_width, large_height );
			else ofLog(OF_LOG_WARNING, title+" image not allocated!");

			ofPushStyle();
			ofNoFill();
			ofSetColor(color.r, color.g, color.b);
			ofSetLineWidth(3);
			ofRect(0, 0, large_width, large_height);
			ofPopStyle();	
			
			ofSetHexColor(0xffffff);
			ofDrawBitmapString(title,  view_largeBorder, view_largeBorder*2);
		};
		
		void mouseMoved( ofMouseEventArgs &e )
		{
			bRolled = isInsideRect(e.x, e.y);
		}
		
		bool isInsideRect(float _x, float _y)
		{
			return ( _x >= x && _x <= x + width && _y >= y && _y <= y + height );
		}
		
		bool isActive() 
		{
			return bActive;
		}
		
		ofImage getImage() 
		{
			return image;
		}
		
	protected:
		string title, shortTitle;
		int viewId;
				
		ofColor color;
		ofImage image;
		
		bool bActive;
		bool bRolled;
		bool bImage;
	};
}