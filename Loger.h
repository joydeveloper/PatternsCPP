#include <string>

// ќпережающее объ€вление
//Bridge pattern
class LoggerImpl;

class Logger
{
public:
	Logger(LoggerImpl* p);
	virtual ~Logger();
	virtual void log(std::string & str) = 0;
protected:
	LoggerImpl * pimpl;
};

class ConsoleLogger : public Logger
{
public:
	ConsoleLogger();
	void log(std::string & str);
};

class FileLogger : public Logger
{
public:
	FileLogger(std::string & file_name);
	void log(std::string & str);
private:
	std::string file;
};

class SocketLogger : public Logger
{
public:
	SocketLogger(std::string & remote_host, int remote_port);
	void log(std::string & str);
private:
	std::string host;
	int    port;
};