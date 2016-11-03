#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Json.h"
#include <unistd.h>
#include "glm/gtc/random.hpp"
#include "cinder/CameraUi.h"
#include "cinder/params/Params.h"


#include "TrafficCamModel.h"
#include "TrafficCamView.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class TrafficViewerApp : public App {
  public:
   
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    void keyDown( KeyEvent event ) override;
    
   static void prepare( Settings *settings );
    
    void parseCamerasFile( const string &filename );
    void loadViews();
    void updateCameraViews();
    void drawCameraViews();
    void randomizeLocs();

    gl::Texture2dRef myTex, mSimpleTexture;
    vector<TrafficCamModel> trafficCamModels;
    vector<TrafficCamView> trafficCamViews;
    
    CameraPersp					mObjectCam;
    CameraPersp					mViewCam;
    CameraPersp					mViewCamInit;
    CameraUi					mCamUi;
    
    // params for the main camera
    params::InterfaceGlRef		mParams;
    vec3						mEyePoint;
    vec3						mLookAt;
    float						mFov;
    float						mAspectRatio;
    float						mNearPlane;
    float						mFarPlane;
    vec2						mLensShift;
    
};

void TrafficViewerApp::prepare(Settings *settings){
    settings->setWindowSize( 1280, 720 );
    settings->setHighDensityDisplayEnabled();
}

void TrafficViewerApp::setup()
{
    
    char cCurrentPath[FILENAME_MAX];
    if (!getcwd(cCurrentPath, sizeof(cCurrentPath)))
    {
        cout << errno;
    }
    printf("The current working directory is %s", cCurrentPath);
    
    
    
    ///////////////////////////
    // load file
    
    string line;
    ifstream myfile (getAssetPath( "jsonfile.json" ).string());
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            console() << line << '\n';
        }
        myfile.close();
    }
    
    else console() << "Unable to open file";

    //
    ///////////////////////////
    
    console() << "textfile.txt lives at: " << getAssetPath( "textfile.txt" ) << std::endl;
    
    string myUrl = "http://207.251.86.238/cctv884.jpg";
    auto img = loadImage(loadUrl(myUrl));
    myTex = gl::Texture2d::create(img);
    
    // Load the latest earthquake information.
    // parseEarthquakes( "http://earthquake.usgs.gov/earthquakes/feed/v1.0/summary/2.5_week.geojson" );
    
    parseCamerasFile("cameras.json");
    console() << "json parsed...";
    
    loadViews();
    
    
    

    
}

void TrafficViewerApp::mouseDown( MouseEvent event )
{
}

void TrafficViewerApp::update()
{
    updateCameraViews();
}

void TrafficViewerApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    gl::enableDepthRead();
    gl::enableDepthWrite();
    gl::draw(myTex);
    drawCameraViews();
    gl::disableDepthRead();
    gl::disableDepthWrite();
    gl::draw(mSimpleTexture);
}
void TrafficViewerApp::loadViews(){
    
    for( auto &thisView : trafficCamViews){
       // thisView.setPos()
        thisView.load();
    }
}
void TrafficViewerApp::drawCameraViews(){
    
    for( auto &thisView : trafficCamViews){

        thisView.draw();
    }
}
void TrafficViewerApp::updateCameraViews(){
    
    for( auto &thisView : trafficCamViews){
        
        thisView.update();
    }
}

void TrafficViewerApp::keyDown( KeyEvent event )
{
    if( event.getChar() == 'f' ) {
        // Toggle full screen when the user presses the 'f' key.
        setFullScreen( ! isFullScreen() );
    }
    else if( event.getCode() == KeyEvent::KEY_SPACE ) {
        // Clear the list of points when the user presses the space bar.
        randomizeLocs();
    }
    else if( event.getCode() == KeyEvent::KEY_ESCAPE ) {
        // Exit full screen, or quit the application, when the user presses the ESC key.
        if( isFullScreen() )
            setFullScreen( false );
        else
            quit();
    }
}

void TrafficViewerApp::randomizeLocs(){
    vec2 winc = getWindowCenter();
    for( auto &thisView : trafficCamViews){
        
        thisView.setPos(vec3(winc.x,winc.y,0) + glm::ballRand(100.0f));
        
    }
}

void TrafficViewerApp::parseCamerasFile(const string &filename){
    try {
        const JsonTree json( loadAsset( filename ) );
        
       // for( auto &thisCamera : json.getChildren() ) {
        for(int i=0;i<json.getChildren().size();i++){
            
            JsonTree thisCamera = json.getChild(i);
            
            const string &title = thisCamera["name"].getValue();
            const string &url = thisCamera["camera"].getValue();
            const float &lat = thisCamera["lat"].getValue<float>();
            const float &lng = thisCamera["lng"].getValue<float>();
            console() << "title: " << title << std::endl;
            TrafficCamModel tcm = TrafficCamModel(title,url,lat,lng);
            trafficCamModels.push_back(tcm);
            TrafficCamView tcv = TrafficCamView(tcm);
            
            float lowLat = 40.507726f;
            float highLat = 40.883900f;
            float lowLng = -74.230371f;
            float highLng = -73.713777f;
            vec2 win = getWindowSize();
            
            float outLat = lmap(lat,highLat,lowLat,10.0f,(float)win.y-10.0f);
            float outLng = lmap(lng,lowLng,highLng,10.0f,(float)win.x-10.0f);
            tcv.setPos(vec3(outLng,outLat,glm::linearRand(-5.0f,5.0f)));
            trafficCamViews.push_back(tcv);
            
        }
    }
    catch( ci::Exception &exc ) {
        console() << "Failed to parse json, what: " << exc.what() << std::endl;
    }
    
}

CINDER_APP( TrafficViewerApp, RendererGl, TrafficViewerApp::prepare )
