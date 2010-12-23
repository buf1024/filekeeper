//=============================================================================
/**
* @file	    ProgObject.h
* @brief	Program object
* @author	heidong
* @version	1.0
* @date		2010-12-13 20:53:48
*/
//=============================================================================
#pragma once
#include "persistobject.h"
#include "ForbidOpt.h"

class DataPool;
/**Program Persisitent Object*/
class ProgObject :
	public PersistObject
{
public:
	/**@name Consturctor & Destructor*/
	/**@{*/
	/**Constructor
	*@param pPool The data source of Persistent object, if pPool is NULL, use the default one.
	*/
	ProgObject(DataPool* pPool = NULL);
	/**destructor*/
	~ProgObject(void);
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
	/**Set the program path
	*@param strProgPath The program path
	*/
	void SetProgPath(Std_String strProgPath);
	/**Get program path
	*@return the program path
	*/
	Std_String GetProgPath();
	/**Get the program name
	*@return the program name
	*/
    Std_String GetProgName();

	/**Set program footprint
	*@param strFootprint the program footprint
	*/
	void SetFootprint(Std_String strFootprint);
	/**Get the program footprint
	*@return the program footprint
	*/
	Std_String GetFootprint();

	/**Set the program description
	*@param strDesc the program description
	*/
	void SetDescription(Std_String strDesc);
	/**Get the program description
	*@return the program description
	*/
	Std_String GetDescription();

    /**Set the program Option
	*@param nOpt <0 ignore program, other normal
	*/
    void SetOption(int nOpt);
    /**Get the program option
	*@return the program option
	*/
    int GetOption();

	/**@}*/

	/**@name program forbid option*/
	/**@{*/
	/**Get the forbidden path
	*@param rgpPathOpt The path and option the user
	*@return the count of the forbidden path
	*/
	int GetForbidPath(list<ForbidOpt>& rgpPathOpt);
	/**Get the path forbidden option
	*@param strPath The path
	*@return the Option of the path, 0xFF if not forbidden
	*/
	int GetPathForbidOpt(Std_String strPath);
	/**Add a new forbidden path
	*@param strPath The new path
	*@param nOpt The forbidden mask
	*@return true if successfully add, othwerwise false
	*/
	bool AddForbidPath(Std_String strPath, int nOpt = 0x07);
	/**Delete a forbidden path
	*@param strPath The path
	*@return true if successfully delete, othwerwise false
	*/
	bool DropForbidPath(Std_String strPath);
	/**Change the forbidden path forbidden mask
	*@param strPath The path
	*@param nOpt The forbidden mask
	*@return true if successfully changed, othwerwise false
	*/
	bool ChangeForbidPathOpt(Std_String strPath, int nOpt);
	/**@}*/
	
private:
	Std_String m_strPath; /**<The Program path*/
	Std_String m_strFootprint; /**<The footprint of the program, CRC32 Value*/
	Std_String m_strDesc; /**<The Program description*/
    int m_nOption;
};
