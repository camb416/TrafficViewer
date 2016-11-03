//
//  TrafficCam.h
//  TrafficViewer
//
//  Created by Cameron Browning on 11/2/16.
//
//

#ifndef TrafficCamModel_h
#define TrafficCamModel_h

#include <string>
using namespace cinder;
using namespace std;

class TrafficCamModel {
private:
    string name;
    string url;
    vec2 pos;
public:
    TrafficCamModel(){};
    TrafficCamModel(string _name,
               string _url,
               float _lat,
               float _lng);
    ~TrafficCamModel();
    string getUrl(){
        return url;
    }
    string getName(){
        return name;
    }
};

#endif /* TrafficCam_h */
