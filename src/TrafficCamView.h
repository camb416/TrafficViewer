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
    bool isSelected;
    float r;
    float dr;
    
public:
    TrafficCamView(TrafficCamModel _model){
        model = _model;
        
        pos =  vec3(0); // position
        dpos = vec3(0); // destination position
        
        w = h = 20.0f;
        r = dr = 0;
        
    }
    void setPos(vec3 _pos){
        dpos = _pos;
    };
    vec2 getPos(){
        return vec2(pos);
    }
    string getUrl(){
      
            return model.getUrl();
       
    }
    void update(bool _isSelected){
        isSelected = _isSelected;
        pos += (dpos-pos)/4.0f;
        if(isSelected){
            dr = r = 15.0f;
        } else {
            dr = 2.0f;
        }
        r += (dr-r)/16.0f;
    }
    ~TrafficCamView(){
        // empty destructor
    }
    void draw();
    void load();
};

#endif /* TrafficCamView_hpp */
