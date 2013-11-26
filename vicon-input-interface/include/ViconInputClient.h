#ifndef VICONINPUTCLIENT_H
#define VICONINPUTCLIENT_H

#include "ViconSegment.h"
#include "ViconClient.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

class String
{
public:
  // A string which we are not responsible for deallocating
  inline
  String( const char * i_pString = 0 )
  : m_pString( 0 )
  , m_pConstString( i_pString )
  , m_pStringFactory( 0 )
  {
  }

  // A string which we are not responsible for deallocating
  String( const std::string & i_rString )
  : m_pString( 0 )
  , m_pConstString( i_rString.c_str() )
  , m_pStringFactory( 0 )
  {
  }

  // Copy constructor
  inline
  String( const String & i_rString )
  {
    m_pConstString = i_rString.m_pConstString;
    m_pStringFactory = i_rString.m_pStringFactory;
    if( m_pStringFactory )
    {
      m_pString = m_pStringFactory->AllocAndCopyString( i_rString.m_pString );
    }
    else
    {
      m_pString = 0;
    }
  }

  inline
  ~String()
  {
    if( m_pStringFactory )
    {
      m_pStringFactory->FreeString( m_pString );
    }
  }

  // A string which we are responsible for deallocating
  inline
  void Set( const char * i_pString, IStringFactory & i_rStringFactory )
  {
    m_pString = i_rStringFactory.AllocAndCopyString( i_pString );
    m_pStringFactory = &i_rStringFactory;
    m_pConstString = 0;
  }

  inline
  operator std::string() const
  {
    if( m_pStringFactory )
    {
      return std::string( m_pString );
    }
    else
    {
      return std::string( m_pConstString );
    }
  }

private:
        char     * m_pString;
  const char     * m_pConstString;
  IStringFactory * m_pStringFactory;
};

// Streaming operator for String
inline std::ostream & operator<<( std::ostream & io_rStream, const String & i_rString )
{
  io_rStream << std::string( i_rString );
  return io_rStream;
}


class ViconInputClient
{
	private:
	const char * hostname;
    void viconInit();
    unsigned int bodyCount;
    std::vector<ViconSegment> solidBodys;
    
	
	public:
	void viconExit();
	
	ViconDataStreamSDK::CPP::Client MyClient; //may cause collisions later if making multiple clients
	void viconUpdate();	
	//void exitCallback(void);
	void printViconData(ViconSegment * segment);

	ViconInputClient(const char * hostname);
};
#endif