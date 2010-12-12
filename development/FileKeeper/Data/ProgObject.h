#pragma once
#include "persistobject.h"

class DataPool;
class ProgObject :
	public PersistObject
{
public:
	ProgObject(DataPool* pPool = NULL);
	~ProgObject(void);

public:
	void SetProgPath(Std_String strProgPath);
	Std_String GetProgPath();
	Std_String GetProgName();

	void SetFootprint(Std_String strFootprint);
	Std_String GetFootprint();

	void SetDescription(Std_String strDesc);
	Std_String GetDescription();


	int GetForbidPath(list<Std_String>& rgpPath);
	bool DropForbidPath(Std_String strPath);

private:
	Std_String m_strPath;
	Std_String m_strFootprint;
	Std_String m_strDesc;
};
