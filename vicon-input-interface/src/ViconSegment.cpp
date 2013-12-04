/*ViconSegment class
 * Author: 4/11/2013 : Brent Nix : bjnix at mtu dot edu
 * 
 * Description: a segment object for the Vicon Input Interface
 */
#include "ViconSegment.h"


ViconSegment::ViconSegment(std::string SubjectName,std::string SegmentName,ViconDataStreamSDK::CPP::Client * segClient)
{
    ViconSegment::SubjectName = SubjectName;
    ViconSegment::SegmentName = SegmentName;
    ViconSegment::segClient = segClient;
    ViconSegment::X_Y_Z = new double[3];
    ViconSegment::phi_theta_psi = new double[3];
    ViconSegment::setTranslation(segClient->GetSegmentGlobalTranslation(SubjectName,SegmentName));
    ViconSegment::setOrientationEuler(segClient->GetSegmentGlobalRotationEulerXYZ(SubjectName, SegmentName));
}
/*
ViconSegment::~ViconSegment()
{
    delete [] ViconSegment::X_Y_Z;
    delete [] ViconSegment::phi_theta_psi;
}
*/


double * ViconSegment::setTranslation(ViconDataStreamSDK::CPP::Output_GetSegmentGlobalTranslation Output)
{
    if(!Output.Occluded)
    { 
        X_Y_Z = Output.Translation;
    }
    return X_Y_Z;
}

double * ViconSegment::setOrientationEuler(ViconDataStreamSDK::CPP::Output_GetSegmentGlobalRotationEulerXYZ Output)
{
    if(!Output.Occluded)
    {
        phi_theta_psi = Output.Rotation;
    }
    return phi_theta_psi;
}
//getter mthods for array values
double * ViconSegment::getTranslation()
{
    return X_Y_Z;
}
double * ViconSegment::getOrientationEuler()
{
    return phi_theta_psi;
}
//getter methods for individual components
double ViconSegment::getX()
{ 
    return X_Y_Z[0];
}
double ViconSegment::getY()
{ 
    return X_Y_Z[1];
}
double ViconSegment::getZ()
{ 
    return X_Y_Z[2];
}
double ViconSegment::getPhi()
{
    return phi_theta_psi[0];
}
double ViconSegment::getTheta()
{
    return phi_theta_psi[1];
}
double ViconSegment::getPsi()
{
    return phi_theta_psi[2];
}
std::string ViconSegment::getSubjectName(){
    return SubjectName;
}
std::string ViconSegment::getSegmentName(){
    return SegmentName;
}
