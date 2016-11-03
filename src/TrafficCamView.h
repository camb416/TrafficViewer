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
    vec3 pos,dpos;
    float w,h;
    gl::Texture2dRef nameTex;
    
public:
    TrafficCamView(TrafficCamModel _model){
        model = _model;
        
        pos =  vec3(0); // position
        dpos = vec3(0); // destination position
        
        w = h = 20.0f;
    }
    void setPos(vec3 _pos){
        dpos = _pos;
    };
    void update(){
        pos += (dpos-pos)/4.0f;
    }
    ~TrafficCamView(){
        // empty destructor
    }
    void draw();
    void load();
};

#endif /* TrafficCamView_hpp */
