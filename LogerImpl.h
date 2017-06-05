#include <string>
class LoggerImpl
{
public:
	virtual ~LoggerImpl() {}
	virtual void console_log(std::string & str) = 0;
	virtual void file_log(
		std::string & file, std::string & str) = 0;
	virtual void socket_log(
		std::string & host, int port, std::string & str) = 0;
};

class ST_LoggerImpl : public LoggerImpl
{
public:
	void console_log(std::string & str);
	void file_log(std::string & file, std::string & str);
	void socket_log(
		std::string & host, int port, std::string & str);
};

class MT_LoggerImpl : public LoggerImpl
{
public:
	void console_log(std::string & str);
	void file_log(std::string & file, std::string & str);
	void socket_log(
		std::string & host, int port, std::string & str);
};


