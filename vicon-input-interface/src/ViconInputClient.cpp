#include "ViconInputClient.h"

using namespace ViconDataStreamSDK::CPP;



ViconInputClient::ViconInputClient(const char * hostname, std::string * SubjectNames, std::string *SegmentNames, unsigned int bodyCount)
{
	
	ViconInputClient::hostname = hostname;
	ViconAddSolidBody(SubjectNames,SegmentNames,bodyCount);
	viconInit();
}

namespace
{
	std::string Adapt( const bool i_Value )
	{
		return i_Value ? "True" : "False";
	}

	std::string Adapt( const Direction::Enum i_Direction )
	{
		switch( i_Direction )
		{
			case Direction::Forward:
				return "Forward";
			case Direction::Backward:
				return "Backward";
			case Direction::Left:
				return "Left";
			case Direction::Right:
				return "Right";
			case Direction::Up:
				return "Up";
			case Direction::Down:
				return "Down";
			default:
				return "Unknown";
		}
	}

	std::string Adapt( const DeviceType::Enum i_DeviceType )
	{
		switch( i_DeviceType )
		{
			case DeviceType::ForcePlate:
				return "ForcePlate";
			case DeviceType::Unknown:
			default:
				return "Unknown";
		}
	}

	std::string Adapt( const Unit::Enum i_Unit )
	{
		switch( i_Unit )
		{
			case Unit::Meter:
				return "Meter";
			case Unit::Volt:
				return "Volt";
			case Unit::NewtonMeter:
				return "NewtonMeter";
			case Unit::Newton:
				return "Newton";
			case Unit::Kilogram:
				return "Kilogram";
			case Unit::Second:
				return "Second";
			case Unit::Ampere:
				return "Ampere";
			case Unit::Kelvin:
				return "Kelvin";
			case Unit::Mole:
				return "Mole";
			case Unit::Candela:
				return "Candela";
			case Unit::Radian:
				return "Radian";
			case Unit::Steradian:
				return "Steradian";
			case Unit::MeterSquared:
				return "MeterSquared";
			case Unit::MeterCubed:
				return "MeterCubed";
			case Unit::MeterPerSecond:
				return "MeterPerSecond";
			case Unit::MeterPerSecondSquared:
				return "MeterPerSecondSquared";
			case Unit::RadianPerSecond:
				return "RadianPerSecond";
			case Unit::RadianPerSecondSquared:
				return "RadianPerSecondSquared";
			case Unit::Hertz:
				return "Hertz";
			case Unit::Joule:
				return "Joule";
			case Unit::Watt:
				return "Watt";
			case Unit::Pascal:
				return "Pascal";
			case Unit::Lumen:
				return "Lumen";
			case Unit::Lux:
				return "Lux";
			case Unit::Coulomb:
				return "Coulomb";
			case Unit::Ohm:
				return "Ohm";
			case Unit::Farad:
				return "Farad";
			case Unit::Weber:
				return "Weber";
			case Unit::Tesla:
				return "Tesla";
			case Unit::Henry:
				return "Henry";
			case Unit::Siemens:
				return "Siemens";
			case Unit::Becquerel:
				return "Becquerel";
			case Unit::Gray:
				return "Gray";
			case Unit::Sievert:
				return "Sievert";
			case Unit::Katal:
				return "Katal";

			case Unit::Unknown:
			default:
				return "Unknown";
		}
	}
}

ViconSegment * ViconInputClient::ViconAddSolidBody(std::string * SubjectNames, std::string * SegmentName, unsigned int bodyCount);
{
	
	ViconInputClient::
	for(int bodyIndex = 0; bodyIndex < bodyCount; bodyIndex++ )
	{
		solidBodys.push_back(new ViconSegment(subject_0,segment_0,&MyClient));
	}
	return solidBodys;
}

void ViconInputClient::viconExit()
{
    MyClient.DisableSegmentData();
//    MyClient.DisableMarkerData();
//    MyClient.DisableUnlabeledMarkerData();
//    MyClient.DisableDeviceData();

	// TODO: Disconnect seems to cause a hang. -Scott Kuhl
    // Disconnect and dispose
    int t = clock();
    std::cout << " Disconnecting..." << std::endl;
    MyClient.Disconnect();
    int dt = clock() - t;
    double secs = (double) (dt)/(double)CLOCKS_PER_SEC;
    std::cout << " Disconnect time = " << secs << " secs" << std::endl;
}
/**
 * viconInit
 * Method called to start vicon server
 *
 */
void ViconInputClient::viconInit()
{
    // Connect to a server
    std::cout << "Connecting to " << ViconInputClient::hostname << " ..." << std::flush;
	int attemptConnectCount = 0;
	const int MAX_CONNECT_ATTEMPTS=2;
    while( !MyClient.IsConnected().Connected && attemptConnectCount < MAX_CONNECT_ATTEMPTS)
    {
		attemptConnectCount++;
		bool ok = false;
		ok =( MyClient.Connect( ViconInputClient::hostname ).Result == Result::Success );
		if(!ok)
			std::cout << "Warning - connect failed..." << std::endl;
		std::cout << ".";
		sleep(1);
    }
	if(attemptConnectCount == MAX_CONNECT_ATTEMPTS)
	{
		printf("Giving up making connection to Vicon system\n");
		return;
	}
    std::cout << std::endl;
/* TODO: bjnix at mtu dot edu | 11.13.2013
	add enumeration for input, so as to let user input what types of data to enable
*/
    // Enable some different data types
    MyClient.EnableSegmentData();
    //MyClient.EnableMarkerData();
    //MyClient.EnableUnlabeledMarkerData();
    //MyClient.EnableDeviceData();

    std::cout << "Segment Data Enabled: "          << Adapt( MyClient.IsSegmentDataEnabled().Enabled )         << std::endl;
    std::cout << "Marker Data Enabled: "           << Adapt( MyClient.IsMarkerDataEnabled().Enabled )          << std::endl;
    std::cout << "Unlabeled Marker Data Enabled: " << Adapt( MyClient.IsUnlabeledMarkerDataEnabled().Enabled ) << std::endl;
    std::cout << "Device Data Enabled: "           << Adapt( MyClient.IsDeviceDataEnabled().Enabled )          << std::endl;

    // Set the streaming mode
    //MyClient.SetStreamMode( ViconDataStreamSDK::CPP::StreamMode::ClientPull );
    // MyClient.SetStreamMode( ViconDataStreamSDK::CPP::StreamMode::ClientPullPreFetch );
    MyClient.SetStreamMode( ViconDataStreamSDK::CPP::StreamMode::ServerPush );

    // Set the global up axis
    MyClient.SetAxisMapping( Direction::Forward, 
                             Direction::Left, 
                             Direction::Up ); // Z-up
    // MyClient.SetGlobalUpAxis( Direction::Forward, 
    //                           Direction::Up, 
    //                           Direction::Right ); // Y-up

    Output_GetAxisMapping _Output_GetAxisMapping = MyClient.GetAxisMapping();
    std::cout << "Axis Mapping: X-" << Adapt( _Output_GetAxisMapping.XAxis ) 
			  << " Y-" << Adapt( _Output_GetAxisMapping.YAxis ) 
			  << " Z-" << Adapt( _Output_GetAxisMapping.ZAxis ) << std::endl;

    // Discover the version number
    Output_GetVersion _Output_GetVersion = MyClient.GetVersion();
    std::cout << "Version: " << _Output_GetVersion.Major << "." 
			  << _Output_GetVersion.Minor << "." 
			  << _Output_GetVersion.Point << std::endl;

}
/* TODO: bjnix at mtu dot edu | 11.13.2013
	hide update process from user to clean things up
*/

void ViconInputClient::viconUpdate()
{
	std::string SubjectName;
	std::string SegmentName;
	unsigned int SubjectCount;
	unsigned int SegmentCount;
	unsigned int SubjectIndex;
	unsigned int SegmentIndex;

	while(MyClient.GetFrame().Result != Result::Success) 
	{
		sleep(1);
		std::cout(".");
	}
	SubjectCount = MyClient.GetSubjectCount().SubjectCount;
	/* TODO: bjnix at mtu dot edu | 11.13.2013
		make sure to change this to accept vector input 
	*/
	for(std::vector<ViconSegment>::iterator iter = solidBodys.begin() ; iter != solidBodys.end(); ++iter )
	{
		iter.setTranslation(MyClient.GetSegmentGlobalTranslation(iter.getSubjectName,iter.getSegmentName);
	    SegmentCount = MyClient.GetSegmentCount( SubjectName ).SegmentCount;

	    for(SegmentIndex = 0; SegmentIndex < SegmentCount; SegmentIndex)
		{
			SegmentName = MyClient.GetSegmentName( SubjectName, SegmentIndex).SegmentName;

			Output_GetSegmentGlobalTranslation _Output_GlobalTranslation = MyClient.GetSegmentGlobalTranslation(SubjectName, SegmentName);
			Output_GetSegmentGlobalRotationEulerXYZ _Output_GlobalRotationEuler = MyClient.GetSegmentGlobalRotationEulerXYZ(SubjectName, SegmentName);
			//Output_GetSegmentGlobalRotationHelical _Output_GlobalRotationHelical = MyClient.GetSegmentGlobalRotationHelical(SubjectName, SegmentName);
			//Output_GetSegmentGlobalRotationMatrix _Output_GlobalRotationMatrix = MyClient.GetSegmentGlobalRotationMatrix(SubjectName, SegmentName);
			//Output_GetSegmentGlobalRotationQuaternion _Output_GlobalRotationQuaternion = MyClient.GetSegmentGlobalRotationQuaternion(SubjectName, SegmentName);
			


		}
	}

}

/*
// an atexit() callback:
void ViconInputClient::exitCallback()
{
	viconExit();
	return;
}
*/
/**
*	This function will print the vicon segment objects' coordinates
*
*	@param *segment is a pointer to a ViconSegment, which we will print.
*	
*/
void ViconInputClient::printViconData(ViconSegment *segment){
		double * tester = segment->getTranslation();
		//segment->printSubjectName();
		//std::cout << "Translation Data:" << std::endl;
		//std::cout << "( " << ", " << tester[0]/1000/2 << ", " << segment->getY()/1000/2 << ", " << segment->getZ()/1000/2 << " )" << std::endl;
		//X is left/right
		//Y is forwards and backwards
		//Z is	up/down.
}
