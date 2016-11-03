//
//  TrafficCamView.cpp
//  TrafficViewer
//
//  Created by Cameron Browning on 11/2/16.
//
//


#include "TrafficCamView.h"
#include "cinder/gl/gl.h"

using namespace cinder::app;

void TrafficCamView::load(){
    console() << model.getUrl();
    // text stuff
    std::string normalFont( "Arial" );
    TextLayout simple;
    simple.setFont( Font(normalFont,20) );
    simple.setColor( Color( 1, 0, 0.1f ) );
    simple.addLine( model.getName() );
    nameTex = gl::Texture2d::create( simple.render( true, false ) );
    
}
void TrafficCamView::draw(){
    gl::pushMatrices();
    gl::translate(x, y);
    gl::drawSolidCircle(vec2(0,0),2,0);
    gl::translate(5,-5); // skootch text over
    gl::draw(nameTex,Rectf(0,0,nameTex->getWidth()/2,nameTex->getHeight()/2));
    gl::popMatrices();
}