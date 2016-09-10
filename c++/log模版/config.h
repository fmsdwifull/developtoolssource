#include "tinystr.h"
#include "tinyxml.h"

#define XML_E_SETTINGS      "settings"
#define XML_E_MEDIASERVER   "mediaserver"
#define XML_E_LOCALIP       "localip"
#define XML_E_TYPE          "type"
#define XML_E_CONTROLSERVER "controlserver"
#define XML_E_IP            "ip"
#define XML_E_PORT          "port"
#define XML_E_LOGUPLOAD     "logupload"
#define XML_E_PERIODMIN     "periodmin"
#define XML_E_AVGSIZE       "avgsize"
#define XML_E_LASTPOS       "lastpos"
#define XML_E_DATE          "date"
#define XML_E_UPLOADSEQ     "uploadseq"
#define XML_E_LOGPATH       "logpath"
#define XML_E_MOUNT         "mount"
#define XML_E_TARGETPATH    "targetpath"
#define XML_E_LOCALPATH     "localpath"
#define XML_E_LOG           "log"
#define XML_E_LEVEL         "level"
#define XML_E_OUTPUTPATH    "outputpath"
#define XML_E_PREFIX        "prefix"

class CConfig
{
public:
	CConfig(char* szFullFileName);
	~CConfig();
	bool Load();
	bool Save();
	const char* GetValueString(const char* szTag);
	int GetValueInt(const char* szTag);
	long GetValueLong(const char* szTag);
	bool SetValueString(const char* szTag, const char* szValue);
	bool SetValueInt(const char* szTag, int iValue);
	bool SetValueLong(const char* szTag, long iValue);
	
private:
	TiXmlDocument* m_myDoc;
	TiXmlElement* m_localip;
	TiXmlElement* m_type;
	TiXmlElement* m_ip;
	TiXmlElement* m_port;
	TiXmlElement* m_periodmin;
	TiXmlElement* m_avgsize;
	TiXmlElement* m_lastpos;
	TiXmlElement* m_date;
	TiXmlElement* m_uploadseq;
	TiXmlElement* m_logpath;
	TiXmlElement* m_targetpath;
	TiXmlElement* m_localpath;
	TiXmlElement* m_level;
	TiXmlElement* m_outputpath;
	TiXmlElement* m_prefix;
};

