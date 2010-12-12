#pragma once

#include <stl.h>

class DataPool;
class PersistObject
{
public:
	PersistObject(DataPool* pPool = NULL);
	virtual ~PersistObject(void);

public:
	virtual void Persist();
	virtual void Restore();

protected:
	DataPool* m_pDataPool;
};
