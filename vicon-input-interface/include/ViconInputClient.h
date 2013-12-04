#ifndef VICONINPUTCLIENT_H
#define VICONINPUTCLIENT_H

#include "ViconSegment.h"
#include "ViconClient.h"

//#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

class ViconInputClient
{
	private:
	const char * hostname;
    void viconInit();
    std::vector<ViconSegment> solidBodys;
    
	
	public:
	//void exitCallback(void);
	ViconDataStreamSDK::CPP::Client MyClient; //may cause collisions later if making multiple clients

	void viconExit();
	void viconUpdate();	
	void printViconData(ViconSegment * segment);
	std::vector<ViconSegment> viconAddSolidBody(std::vector<std::string> SubjectNames, std::vector<std::string> SegmentNames);

	ViconInputClient(const char * hostname, std::vector<std::string> SubjectNames, std::vector<std::string> SegmentNames);
};
#endif