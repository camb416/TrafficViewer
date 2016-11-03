//
//  TrafficCamView.h
//  TrafficViewer
//
//  Created by Cameron Browning on 11/2/16.
//
//

#ifndef TrafficCamView_h
#define TrafficCamView_h
#include "TrafficCamModel.h"
#include <stdio.h>

class TrafficCamView{
private:
    TrafficCamModel model;
    Surface surface;
    float x,y;
    float w,h;
    gl::Texture2dRef nameTex;
    
public:
    TrafficCamView(TrafficCamModel _model){
        model = _model;
        x = y = 0.0f;
        w = h = 20.0f;
    }
    void setPos(vec2 _pos){
        x = _pos.x;
        y = _pos.y;
    };
    ~TrafficCamView(){
        // empty destructor
    }
    void draw();
    void load();
};

#endif /* TrafficCamView_hpp */
