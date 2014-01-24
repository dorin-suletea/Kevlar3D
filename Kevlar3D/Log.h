#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include "Paths.h"
#include "GLIncludes.h"
#include "Vector.h"

class Log
{
private:
	std::string								m_logContext;
	mutable std::ofstream					m_outputStream;
	static const std::shared_ptr<Log>		const s_instance ;	    
											Log(void);


public:
	static const std::shared_ptr<Log>		GetInstance(void);
	void									SetContext(std::string const &context);
	void									LogInfo(std::string const &message)const;
	void									LogInfo(const Vector3 &message)const;

	void									LogErr(std::string const &message)const;
	void									LogErr(char* message)const;
	void									LogErr(int message)const;
	void									LogErr(const GLubyte * message)const;
	void									LogErr(const GLchar * message)const;
											~Log(void);

	static const std::string				LOG_NO_CONTEXT ;
};

