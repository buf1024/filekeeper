//=============================================================================
/**
* @file	    UserObject.h
* @brief	User object
* @author	heidong
* @version	1.0
* @date		2010-12-13 20:54:37
*/
//=============================================================================
#pragma once
#include "persistobject.h"

class DataPool;
/**The User Persistent Object*/
class UserObject :
	public PersistObject
{
public:
	/**@name Consturctor & Destructor*/
	/**@{*/
	/**Constructor
	*@param pPool The data source of Persistent object, if pPool is NULL, use the default one.
	*/
	UserObject(DataPool* pPool = NULL);
	/**destructor*/
	~UserObject(void);
	/**@}*/


	/**
	*@see PersistObject::Persist()
	*/
	virtual bool Persist();
	/**
	*@see PersistObject::Refresh()
	*/
	virtual bool Refresh();

public:
	/**@name Getter and Setter of attributes*/
	/**@{*/
	/**Set User Name
	*@param strUserName The User Name
	*/
	void SetUserName(Std_String strUserName);
	/**Get the user name
	*@return The User Name
	*/
	Std_String GetUserName();

	/**Set User Password
	*@param strPass The User Password
	*/
	void SetPassword(Std_String strPass);
	/**Get the user Password
	*@return The User Password
	*/
	Std_String GetPassword();

	/**Set User Description
	*@param strDesc The User Description
	*/
	void SetDescription(Std_String strDesc);
	/**Get the user Description
	*@return The User Description
	*/
	Std_String GetDescription();
	/**@}*/
	
	/**@name Encryption*/
	/**@{*/
	/**Get the encryption path
	*@param rgpPath The paths the user encrypt
	*@return the count of the encrypted path
	*/
	int GetEncryptPath(list<Std_String>& rgpPath);
	/**Add a new encryption path
	*@param strPath The new path the user encrypt
	*@return true if successfully added
	*/
	bool AddEncryptPath(Std_String strPath);
	/**Delete the encrypted path
	*@param strPath The Path
	*@return true delete successfully, false otherwise
	*/
	bool DropEncryptPath(Std_String strPath);
	/**@}*/

private:
	Std_String m_strName; /**<The User Name*/
	Std_String m_strPass; /**<The User Password*/
	Std_String m_strDesc; /**<The User Description*/
};
