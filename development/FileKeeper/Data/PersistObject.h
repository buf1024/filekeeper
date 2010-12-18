//=============================================================================
/**
* @file	    PersistObject.h
* @brief	Super class of persist object
* @author	heidong
* @version	1.0
* @date		2010-12-13 20:53:15
*/
//=============================================================================
#pragma once

#include <stl.h>

class DataPool;

/**The base class of persistent object*/
class PersistObject
{
public:
	/**@name Consturctor & Destructor*/
	/**@{*/
	/**Constructor
	*@param pPool The data source of Persistent object, if pPool is NULL, use the default one.
	*/
	PersistObject(DataPool* pPool = NULL);
	/**virtual destructor*/
	virtual ~PersistObject(void);
	/**@}*/

public:
	/**@name Basic function*/
	/**@{*/
	/**Persist the object into database*/
	virtual bool Persist();
	/**Refresh data from database*/
	virtual bool Refresh();
	/**@}*/

    /** Method GetDataPool
     * 
     * Get Current Datapool, if not set return the global one 
     * @return The Datapool
     */
	DataPool* GetDataPool();

protected:
	DataPool* m_pDataPool; /**<The database source*/
};
