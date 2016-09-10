#include "depend.h"
#include "config.h"

#include <strstream>


CConfig::CConfig(char* szFullFileName)
	: m_localip(NULL),
	m_type(NULL),
	m_ip(NULL),
	m_port(NULL),
	m_periodmin(NULL),
	m_avgsize(NULL),
	m_lastpos(NULL),
	m_date(NULL),
	m_uploadseq(NULL),
	m_logpath(NULL),
	m_targetpath(NULL),
	m_localpath(NULL),
	m_level(NULL),
	m_outputpath(NULL),
	m_prefix(NULL)
{
	m_myDoc = new TiXmlDocument(szFullFileName);
}

CConfig::~CConfig()
{
	if (m_myDoc)
	{
		delete m_myDoc;
		m_myDoc = NULL;
	}
}

bool CConfig::Load()
{
	bool bRet = true;
	do
	{
		if (!m_myDoc->LoadFile())
		{
			bRet = false;
			break;
		}
		TiXmlHandle docHandle(m_myDoc);
		m_localip = docHandle.FirstChild(XML_E_SETTINGS).FirstChild(XML_E_MEDIASERVER).FirstChild(XML_E_LOCALIP).ToElement();
		if (m_localip == NULL)
		{
			bRet = false;
			break;
		}
		m_type = docHandle.FirstChild(XML_E_SETTINGS).FirstChild(XML_E_MEDIASERVER).FirstChild(XML_E_TYPE).ToElement();
		if (m_type == NULL)
		{
			bRet = false;
			break;
		}
		m_ip = docHandle.FirstChild(XML_E_SETTINGS).FirstChild(XML_E_CONTROLSERVER).FirstChild(XML_E_IP).ToElement();
		if (m_ip == NULL)
		{
			bRet = false;
			break;
		}
		m_port = docHandle.FirstChild(XML_E_SETTINGS).FirstChild(XML_E_CONTROLSERVER).FirstChild(XML_E_PORT).ToElement();
		if (m_port == NULL)
		{
			bRet = false;
			break;
		}
		m_periodmin = docHandle.FirstChild(XML_E_SETTINGS).FirstChild(XML_E_LOGUPLOAD).FirstChild(XML_E_PERIODMIN).ToElement();
		if (m_periodmin == NULL)
		{
			bRet = false;
			break;
		}
		m_avgsize = docHandle.FirstChild(XML_E_SETTINGS).FirstChild(XML_E_LOGUPLOAD).FirstChild(XML_E_AVGSIZE).ToElement();
		if (m_avgsize == NULL)
		{
			bRet = false;
			break;
		}
		m_lastpos = docHandle.FirstChild(XML_E_SETTINGS).FirstChild(XML_E_LOGUPLOAD).FirstChild(XML_E_LASTPOS).ToElement();
		if (m_lastpos == NULL)
		{
			bRet = false;
			break;
		}
		m_date = docHandle.FirstChild(XML_E_SETTINGS).FirstChild(XML_E_LOGUPLOAD).FirstChild(XML_E_DATE).ToElement();
		if (m_date == NULL)
		{
			bRet = false;
			break;
		}
		m_uploadseq= docHandle.FirstChild(XML_E_SETTINGS).FirstChild(XML_E_LOGUPLOAD).FirstChild(XML_E_UPLOADSEQ).ToElement();
		if (m_uploadseq == NULL)
		{
			bRet = false;
			break;
		}
		m_logpath = docHandle.FirstChild(XML_E_SETTINGS).FirstChild(XML_E_LOGUPLOAD).FirstChild(XML_E_LOGPATH).ToElement();
		if (m_logpath == NULL)
		{
			bRet = false;
			break;
		}
		m_targetpath = docHandle.FirstChild(XML_E_SETTINGS).FirstChild(XML_E_MOUNT).FirstChild(XML_E_TARGETPATH).ToElement();
		if (m_targetpath == NULL)
		{
			bRet = false;
			break;
		}
		m_localpath = docHandle.FirstChild(XML_E_SETTINGS).FirstChild(XML_E_MOUNT).FirstChild(XML_E_LOCALPATH).ToElement();
		if (m_localpath == NULL)
		{
			bRet = false;
			break;
		}
		m_level = docHandle.FirstChild(XML_E_SETTINGS).FirstChild(XML_E_LOG).FirstChild(XML_E_LEVEL).ToElement();
		if (m_level == NULL)
		{
			bRet = false;
			break;
		}
		m_outputpath= docHandle.FirstChild(XML_E_SETTINGS).FirstChild(XML_E_LOG).FirstChild(XML_E_OUTPUTPATH).ToElement();
		if (m_outputpath == NULL)
		{
			bRet = false;
			break;
		}
		m_prefix= docHandle.FirstChild(XML_E_SETTINGS).FirstChild(XML_E_LOG).FirstChild(XML_E_PREFIX).ToElement();
		if (m_prefix == NULL)
		{
			bRet = false;
			break;
		}
	} while(false);
	return bRet;
}

bool CConfig::Save()
{
	return m_myDoc->SaveFile();
}

const char* CConfig::GetValueString(const char* szTag)
{
	if (strcmp(szTag, XML_E_LOCALIP) == 0)
	{
		return m_localip->GetText();
	}
	if (strcmp(szTag, XML_E_IP) == 0)
	{
		return m_ip->GetText();
	}
	else if (strcmp(szTag, XML_E_DATE) == 0)
	{
		return m_date->GetText();
	}
	else if (strcmp(szTag, XML_E_LOGPATH) == 0)
	{
		return m_logpath->GetText();
	}
	else if (strcmp(szTag, XML_E_TARGETPATH) == 0)
	{
		return m_targetpath->GetText();
	}
	else if (strcmp(szTag, XML_E_LOCALPATH) == 0)
	{
		return m_localpath->GetText();
	}
	else if (strcmp(szTag, XML_E_OUTPUTPATH) == 0)
	{
		return m_outputpath->GetText();
	}
	else if (strcmp(szTag, XML_E_PREFIX) == 0)
	{
		return m_prefix->GetText();
	}
	else
	{
		return NULL;
	}
}

int CConfig::GetValueInt(const char* szTag)
{
	if (strcmp(szTag, XML_E_TYPE) == 0)
	{
		return atoi(m_type->GetText());
	}
	else if (strcmp(szTag, XML_E_PORT) == 0)
	{
		return atoi(m_port->GetText());
	}
	else if (strcmp(szTag, XML_E_PERIODMIN) == 0)
	{
		return atoi(m_periodmin->GetText());
	}
	else if (strcmp(szTag, XML_E_AVGSIZE) == 0)
	{
		return atoi(m_avgsize->GetText());
	}
	else if (strcmp(szTag, XML_E_UPLOADSEQ) == 0)
	{
		return atoi(m_uploadseq->GetText());
	}
	else if (strcmp(szTag, XML_E_LEVEL) == 0)
	{
		return atoi(m_level->GetText());
	}
	else
	{
		return 0;
	}
}

long CConfig::GetValueLong(const char* szTag)
{
	if (strcmp(szTag, XML_E_LASTPOS) == 0)
	{
		return atol(m_lastpos->GetText());
	}
	else
	{
		return 0;
	}
}

bool CConfig::SetValueString(const char* szTag, const char* szValue)
{
	bool bRet = true;
	TiXmlElement* tmp;
	if (strcmp(szTag, XML_E_LOCALIP) == 0)
	{
		tmp = m_localip;
	}
	if (strcmp(szTag, XML_E_IP) == 0)
	{
		tmp = m_ip;
	}
	else if (strcmp(szTag, XML_E_DATE) == 0)
	{
		tmp = m_date;
	}
	else if (strcmp(szTag, XML_E_LOGPATH) == 0)
	{
		tmp = m_logpath;
	}
	else if (strcmp(szTag, XML_E_TARGETPATH) == 0)
	{
		tmp = m_targetpath;
	}
	else if (strcmp(szTag, XML_E_LOCALPATH) == 0)
	{
		tmp = m_localpath;
	}
	else if (strcmp(szTag, XML_E_OUTPUTPATH) == 0)
	{
		tmp = m_outputpath;
	}
	else if (strcmp(szTag, XML_E_PREFIX) == 0)
	{
		tmp = m_prefix;
	}
	else
	{
		bRet = false;
	}
	if (bRet)
	{
		TiXmlNode * oldnode = tmp->FirstChild();
		TiXmlText newText(szValue);
		tmp->ReplaceChild(oldnode, newText);
		if (!Save())
		{
			bRet = false;
		}
	}
	return bRet;
}

bool CConfig::SetValueInt(const char* szTag, int iValue)
{
	bool bRet = true;
	TiXmlElement* tmp;
	if (strcmp(szTag, XML_E_TYPE) == 0)
	{
		tmp = m_type;
	}
	if (strcmp(szTag, XML_E_PORT) == 0)
	{
		tmp = m_port;
	}
	else if (strcmp(szTag, XML_E_PERIODMIN) == 0)
	{
		tmp = m_periodmin;
	}
	else if (strcmp(szTag, XML_E_AVGSIZE) == 0)
	{
		tmp = m_avgsize;
	}
	else if (strcmp(szTag, XML_E_UPLOADSEQ) == 0)
	{
		tmp = m_uploadseq;
	}
	else if (strcmp(szTag, XML_E_LEVEL) == 0)
	{
		tmp = m_level;
	}
	else
	{
		bRet = false;
	}
	if (bRet)
	{
		TiXmlNode * oldnode = tmp->FirstChild();
		std::strstream strtmp;
		strtmp << iValue;
		strtmp << '\0';
		TiXmlText newText(strtmp.str());
		tmp->ReplaceChild(oldnode, newText);
		if (!Save())
		{
			bRet = false;
		}
	}
	return bRet;
}

bool CConfig::SetValueLong(const char* szTag, long iValue)
{
	bool bRet = true;
	TiXmlElement* tmp;
	if (strcmp(szTag, XML_E_LASTPOS) == 0)
	{
		tmp = m_lastpos;
	}
	else
	{
		bRet = false;
	}
	if (bRet)
	{
		TiXmlNode * oldnode = tmp->FirstChild();
		std::strstream strtmp;
		strtmp << iValue;
		strtmp << '\0';
		TiXmlText newText(strtmp.str());
		tmp->ReplaceChild(oldnode, newText);
		if (!Save())
		{
			bRet = false;
		}
	}
	return bRet;
}

