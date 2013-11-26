#include "ViconInputClient.h"
#include <iostream>
int main()
{
    ViconInputClient * vClient1 = new ViconInputClient("141.219.28.17:801");
    

    ViconSegment * mySeg = new ViconSegment("Wand","Wand",&vClient1->MyClient);
    double n = mySeg->getX();
    std::cout << n << std::endl;

    delete mySeg;
	vClient1->viconExit();
}
