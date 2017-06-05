#include "stdafx.h"
#include "Loger.h"
#include "LogerImpl.h"

Logger::Logger(LoggerImpl* p) : pimpl(p)
{ }

Logger::~Logger()
{
	delete pimpl;
}

ConsoleLogger::ConsoleLogger() : Logger(
#ifdef MT
	new MT_LoggerImpl()
#else
	new ST_LoggerImpl()
#endif
	)
{ }

void ConsoleLogger::log(std::string & str)
{
	pimpl->console_log(str);
}

FileLogger::FileLogger(std::string & file_name) : Logger(
#ifdef MT
	new MT_LoggerImpl()
#else
	new ST_LoggerImpl()
#endif
	), file(file_name)
{ }

void FileLogger::log(std::string & str)
{
	pimpl->file_log(file, str);
}

SocketLogger::SocketLogger(std::string & remote_host,
	int remote_port) : Logger(
#ifdef MT
	new MT_LoggerImpl()
#else
	new ST_LoggerImpl()
#endif
	), host(remote_host), port(remote_port)
{ }

void SocketLogger::log(std::string & str)
{
	pimpl->socket_log(host, port, str);
}