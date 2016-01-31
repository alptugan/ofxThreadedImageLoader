#pragma once

#include "ofThread.h"
#include "ofImage.h"
#include "ofURLFileLoader.h"
#include "ofTypes.h" 
#include "ofThreadChannel.h"


using namespace std;

class ofxThreadedImageLoader : public ofThread {
public:
    ofxThreadedImageLoader();
    ~ofxThreadedImageLoader();

	void loadFromDisk(ofImage& image, string file);
	void loadFromURL(ofImage& image, string url);
    
    struct ThreadedLoaderEvent {
        string filename;
        string url;
        string name;
        int idNum;
    };
    
    ofEvent<ThreadedLoaderEvent> ThreadedLoaderE;

protected:
	void update(ofEventArgs & a);
    virtual void threadedFunction();
	void urlResponse(ofHttpResponse & response);
    
    // Entry to load.
    struct ofImageLoaderEntry {
        ofImageLoaderEntry() {
            image = NULL;
        }
        
        ofImageLoaderEntry(ofImage & pImage) {
            image = &pImage;
        }
        ofImage* image;
        string filename;
        string url;
        string name;
        int idNum;
    };
    
    
    


    typedef map<string, ofImageLoaderEntry>::iterator entry_iterator;

	int                 nextID;
    int                 lastUpdate;

	map<string,ofImageLoaderEntry> images_async_loading; // keeps track of images which are loading async
	ofThreadChannel<ofImageLoaderEntry> images_to_load_from_disk;
	ofThreadChannel<ofImageLoaderEntry> images_to_update;
    
    
};


