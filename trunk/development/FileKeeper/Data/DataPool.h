#pragma once
#include <Singleton.h>
#include <stl.h>

using namespace lgc;

class UserObject;
class ProgObject;
class PersistObject;

class DataPool : public Singleton<DataPool>
{
public:
	DataPool(void);
	~DataPool(void);

public:
	bool Empty();

	UserObject* GetUser(Std_String strUserName);
	int GetUser(list<UserObject*>& rgpUsers);

	ProgObject* GetProg(Std_String strProg);
	int GetProg(list<ProgObject*>& rgpProgs);

	int GetForbidPath(list<Std_String>& rgpPath);
	int GetForbidPath(Std_String strProgPath, list<Std_String>& rgpPath);
	bool DropForbidPath(Std_String strProgPath, Std_String strPath);
	int GetPathForbidProg(Std_String strPath, list<ProgObject*>& rgpProg);

	int GetEncryptPath(Std_String strUser, list<Std_String>& rgpPath);
	bool DataPool::DropEncryptPath(Std_String strUser, Std_String strPath);
};
