#include "ViconInputClient.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

std::string HostName = "141.219.28.17:801";//was 141.219.28.107:801

template<typename T, size_t N>
T * end(T (&ra)[N]) {
    return ra + N;
}
const char *nameList[] = {
	"HandL",
	"HandR",
	"FootL",
	"FootR"
	};

std::vector<std::string> names(nameList,end(nameList));
//std::vector<std::string> * names_p = &names;
ViconInputClient * vClient;

int main()
{
    
    vClient = new ViconInputClient(&HostName,&names,&names);

    ViconSegment mySeg = (vClient->GetRigidBodies())[0];
    double n = mySeg.getX();
    std::cout<< "X translation: " << n <<std::endl;
 
    vClient->printViconData();

    vClient->Exit();
}
