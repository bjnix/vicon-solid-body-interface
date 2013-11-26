/*ViconSegment class
 * Author: 4/11/2013 : Brent Nix : bjnix at mtu dot edu
 * 
 * Description: a segment object for the Vicon Input Interface
 */
#include "ViconSegment.h"


ViconSegment::ViconSegment(const char * SubjectName,const char * SegmentName,ViconDataStreamSDK::CPP::Client *SegClient)
{
    ViconSegment::SubjectName = SubjectName;
    ViconSegment::SegmentName = SegmentName;
    ViconSegment::SegClient = SegClient;
    ViconSegment::X_Y_Z = new double[3];
    ViconSegment::phi_theta_psi = new double[3];
    ViconSegment::getTranslation();
    ViconSegment::getOrientationEuler();
}
/*
ViconSegment::~ViconSegment()
{
    delete [] ViconSegment::X_Y_Z;
    delete [] ViconSegment::phi_theta_psi;
}
*/


/*
std::string ViconSegment::getSubjectName(){
return ViconSegment::SubjectName;
}
std::string ViconSegment::getSegmentName(){
return ViconSegment::SegmentName;
}
*/
double * ViconSegment::getTranslation()
{
    //Number of segments currently represented/tracked by the vicon system
    Output_GetSegmentGlobalTranslation Output = ViconSegment::SegClient->GetSegmentGlobalTranslation( SubjectName, SegmentName );
    if(!Output.Occluded())
    { 
        X_Y_Z = Output.Translation();
    }
    return X_Y_Z;
}

double * ViconSegment::getOrientationEuler()
{
    Output_GetSegmentGlobalRotationEulerXYZ Output = ViconSegment::SegClient->GetSegmentGlobalRotationEulerXYZ( SubjectName, SegmentName ).Rotation;
    if(!Output.Occluded())
    {
        phi_theta_psi = Output.Rotation();
    }
    return }
//getter methods for individual components
double ViconSegment::getX()
{ 
    X_Y_Z = ViconSegment::getTranslation(); 
    return X_Y_Z[0];
}
double ViconSegment::getY()
{ 
    X_Y_Z = ViconSegment::getTranslation();
    return X_Y_Z[1];
}
double ViconSegment::getZ()
{ 
    X_Y_Z = ViconSegment::getTranslation(); 
    return X_Y_Z[2];
}
double ViconSegment::getPhi()
{
    phi_theta_psi = ViconSegment::getOrientationEuler();
    return phi_theta_psi[0];
}
double ViconSegment::getTheta()
{
    phi_theta_psi = ViconSegment::getOrientationEuler();
    return phi_theta_psi[1];
}
double ViconSegment::getPsi()
{
    phi_theta_psi = ViconSegment::getOrientationEuler();
    return phi_theta_psi[2];
}
