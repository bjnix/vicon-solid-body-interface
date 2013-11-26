#ifndef VICONINPUTCLIENT_H
#define VICONINPUTCLIENT_H

#include "ViconSegment.h"
#include "ViconClient.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

class ViconInputClient
{
	private:
	const char * hostname;
    void viconInit();
    unsigned int bodyCount;
    ViconSegment * solidBodys[bodyCount];
    
	
	public:
	void viconExit();
	
	ViconDataStreamSDK::CPP::Client MyClient; //may cause collisions later if making multiple clients
	void viconUpdate();	
	//void exitCallback(void);
	void printViconData(ViconSegment * segment);

	ViconInputClient(const char * hostname);
};
#endif