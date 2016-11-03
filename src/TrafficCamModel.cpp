//
//  TrafficCam.cpp
//  TrafficViewer
//
//  Created by Cameron Browning on 11/2/16.
//
//
#include "TrafficCamModel.h"
#include <stdio.h>

using namespace ci;
using namespace ci::app;
using namespace std;



TrafficCamModel::TrafficCamModel(string _name,
                       string _url,
                       float _lat,
                       float _lng){
    name = _name;
    url = _url;
    pos = vec2(_lat,_lng);
    isSelected = false;
    
}
TrafficCamModel::~TrafficCamModel(){
    // empty destructor
}