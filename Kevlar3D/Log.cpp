#include "Log.h"

//--------------------------------------------
//statics
const std::string
Log::LOG_NO_CONTEXT="undef";

const std::shared_ptr<Log>
Log::s_instance = std::shared_ptr<Log>(new Log());
//--------------------------------------------


//--------------------------------------------
//creation
Log::Log(void):m_logContext(Log::LOG_NO_CONTEXT),m_outputStream()
{
	std::cout<<"Log build";
	this->m_outputStream.open(LOGFILE_PATH+"k3Log.log");
	if (!this->m_outputStream.is_open())
		throw "Can't open logfile, check paths";
	this->m_outputStream<<"LogInit"<<std::endl;
}

Log::~Log(void)
{
	this->m_outputStream<<"LogDispose"<<std::endl;;
	this->m_outputStream.close();
}

const std::shared_ptr<Log>
Log::GetInstance(void)
{
	return Log::s_instance;
}

void 
Log::SetContext(std::string const &context)
{
	this->m_logContext=context;
}
//--------------------------------------------


//--------------------------------------------
//logic
void 
Log::LogInfo(std::string const &message)const
{
	std::cout<<"loginfo";
	std::cout<<"[Info] - ["<<this->m_logContext<<"] "<<message<<std::endl;
	this->m_outputStream<<std::string("-Info- [")<<this->m_logContext<<"] "<<message<<std::endl;
}

void 
Log::LogErr(std::string const &message)const
{
	std::cout<<"-Err- ["<<this->m_logContext<<"] "<<message<<std::endl;
	this->m_outputStream<<std::string("-Err- [")<<this->m_logContext<<"] "<<message<<std::endl;
}
void					
Log::LogErr(const GLubyte * message) const
{
	std::cout<<"-Err- ["<<this->m_logContext<<"] "<<message<<std::endl;
	this->m_outputStream<<std::string("-Err- [")<<this->m_logContext<<"] "<<message<<std::endl;
}

void					
Log::LogErr(const GLchar * message)const
{
	std::cout<<"-Err- ["<<this->m_logContext<<"] "<<message<<std::endl;
	this->m_outputStream<<std::string("-Err- [")<<this->m_logContext<<"] "<<message<<std::endl;
}
								
//--------------------------------------------





