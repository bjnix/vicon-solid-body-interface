#ifndef VICONSEGMENT_H
#define VICONSEGMENT_H
#include "ViconClient.h"


class ViconSegment
{
  private:
    double * X_Y_Z;
    double * phi_theta_psi;
    //const char * SegmentName;
    //const char * SubjectName;
    const String & SubjectName;
    const String & SegmentName;

    ViconDataStreamSDK::CPP::Client *SegClient;
  public:
    double * setTranslation();
    double * setOrientationEuler();
    double getX();
    double getY();
    double getZ();
    double getPhi();
    double getTheta();
    double getPsi(); 

    getSubjectName();
    getSegmentName();

    ViconSegment(const String & SubjectName, const String & SegmentName, ViconDataStreamSDK::CPP::Client *SegClient);

    //ViconSegment(const char * SubjectName, const char * SegmentName, ViconDataStreamSDK::CPP::Client *SegClient);
    //~ViconSegment();



};
#endif
