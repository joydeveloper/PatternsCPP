#include "stdafx.h"
#include <iostream>
#include "LogerImpl.h"
#include "AppInterface.h"
using namespace appinterface;
void ST_LoggerImpl::console_log(std::string & str)
{
	ShowMessage("Single-threaded console logger") ;
}

void ST_LoggerImpl::file_log(std::string & file, std::string & str)
{
	appinterface::ShowMessage("Single-threaded file logger") ;
}

void ST_LoggerImpl::socket_log(
	std::string & host, int port, std::string & str)
{
	appinterface::ShowMessage("Single-threaded socket logger") ;
};

void MT_LoggerImpl::console_log(std::string & str)
{
	appinterface::ShowMessage( "Multithreaded console logger");
}

void MT_LoggerImpl::file_log(std::string & file, std::string & str)
{
	appinterface::ShowMessage("Multithreaded file logger") ;
}

void MT_LoggerImpl::socket_log(
	std::string & host, int port, std::string & str)
{
	appinterface::ShowMessage("Multithreaded socket logger");
}