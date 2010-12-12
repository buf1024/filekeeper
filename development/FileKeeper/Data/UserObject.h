#pragma once
#include "persistobject.h"

class DataPool;
class UserObject :
	public PersistObject
{
public:
	UserObject(DataPool* pPool = NULL);
	~UserObject(void);

	virtual void Persist();
	virtual void Restore();

public:
	void SetUserName(Std_String strUserName);
	Std_String GetUserName();

	void SetPassword(Std_String strPass);
	Std_String GetPassword();

	void SetDescription(Std_String strDesc);
	Std_String GetDescription();

	int GetEncryptPath(list<Std_String>& rgpPath);
	bool DropEncryptPath(Std_String strPath);

private:
	Std_String m_strName;
	Std_String m_strPass;
	Std_String m_strDesc;
};
