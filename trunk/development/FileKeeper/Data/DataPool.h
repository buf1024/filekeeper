//=============================================================================
/**
* @file	    DataPool.h
* @brief	Basic database class
* @author	heidong
* @version	1.0
* @date		2010-12-13 20:52:11
*/
//=============================================================================
#pragma once
#include <Singleton.h>
#include <stl.h>
#include "ForbidOpt.h"

#include "sqlite3.h"

using namespace lgc;

class UserObject;
class ProgObject;
class PersistObject;

class DataPool
	: public Singleton<DataPool>
{
public:
	DataPool(void);
	~DataPool(void);

public:
	/**@name DataPool basic function*/
	/**@{*/
    /** Method Empty
     * 
     * Delete all data in the database
     * @return true if successfully, false otherwise
     */
	bool Empty();
    /** Method Init
     * 
     * Initialize the Database
     * @param strFile The Database filename
     * @return  true if successfully, false otherwise
     */ 
	bool Init(Std_String strFile);
    /** Method ExecRawSql
     * 
     * Execute the raw sql
     * @param strSql The SQL
     * @return true if succesfully, false otherwise
     */
    bool ExecRawSql(string strSql);
    /** Method SetDbFile
     * 
     * Set an new database file and initialize it.
     * @param strFile The Database filename
     */
	void SetDbFile(Std_String strFile);
    /** Method GetDbFile
     * 
     * Get the current database filename
     * @return The Database filename
     */
	Std_String GetDbFile();
	/**@}*/

	/**@name Persist Object function*/
	/**@{*/
	/**Get user from database
	*@param strUserName The User Name
	*@return NULL if the user not found, othewise the user
	*/
	UserObject* GetUser(Std_String strUserName);
	/**Get All users from the database
	*@param rgpUsers The returned users in the database
	*@return The count of the users
	*/
	int GetUser(list<UserObject*>& rgpUsers);

    /** Method PersistUser
     * 
     * Persist a userobject into the database. update or create new one.
     * @param pUser The persist object
     * @return true if succesfully, false otherwise
     */
	bool PersistUser(UserObject* pUser);

	/**Get program from the database
	*@param strProg The program
	*@return NULL if the program not found, othewise the program
	*/
	ProgObject* GetProg(Std_String strProg);
	/**Get All programs from the database
	*@param rgpProgs The returned programs in the database
	*@return The count of the programs
	*/
	int GetProg(list<ProgObject*>& rgpProgs);
    /** Method PersistProg
     * 
     * Persist a programobject into the database. update or create new one.
     * @param pProg The Program object
     * @return true if succesfully, false otherwise
     */
	bool PersistProg(ProgObject* pProg);
	/**@}*/

	/**@name Forbidden function*/
	/**@{*/
	/**Get the forbidden path the forbid all program access
	*@param rgpPath The returned forbidden path
	*@return the count of forbidden path
	*/
	int GetForbidPath(list<Std_String>& rgpPath);
	/**Get the forbidden path of the specific program
	*@param strProgPath The program path
	*@param rgpPath The returned forbidden path
	*@return the count of forbidden path
	*/
	int GetForbidPath(Std_String strProgPath, list<ForbidOpt>& rgpPath);
	/**Add a new forbidden path
	*@param strProgPath The program path
	*@param strPath The new path
	*@param nOpt The forbidden mask
	*@return true if successfully add, othwerwise false
	*/
	bool AddForbidPath(Std_String strProgPath, Std_String strPath, int nOpt = 0x07);
    /** Method AddForbidPath
     * 
     * Add a new forbidden path the forbidden all program access
     * @param strPath The new path
     * @return true if successfully add, othwerwise false
     */
	bool AddForbidPath(Std_String strPath);
	/**Delete a forbidden path
	*@param strProgPath The program path
	*@param strPath The path
	*@return true if successfully delete, othwerwise false
	*/
	bool DropForbidPath(Std_String strProgPath, Std_String strPath);
    /** Method DropForbidPath
     * 
     * Delete a forbidden path that forbid all program access
     * @param strPath The path
     * @return true if successfully delete, othwerwise false
     */
	bool DropForbidPath(Std_String strPath);
	/**Change the forbidden path forbidden mask
	*@param strProgPath The program path
	*@param strPath The path
	*@param nOpt The forbidden mask
	*@return true if successfully changed, othwerwise false
	*/
	bool ChangeForbidPathOpt(Std_String strProgPath, Std_String strPath, int nOpt);
	
	/**Get the path forbidden option
	*@param rgpProg the returned programs
	*@return the count of the program
	*/
	int GetPathForbidProg(Std_String strPath, list<ProgObject*>& rgpProg);
    /** Method AddPathForbidProg
     * 
     * Set Path that forbid specific progragm to access
     * @param strPath The Path
     * @param strProgPath The program path
     * @param nOpt The forbidden mask
     * @return true if successfull add, false otherwise
     */
	bool AddPathForbidProg(Std_String strPath, Std_String strProgPath, int nOpt = 0x07);
	/**@}*/

	/**@name Encryption function*/
	/**@{*/
	/**Get the encrypt path
	*@param rgpPath the encrypt path by all user
	*@return the count of the encrypt path
	*/
	int GetEncryptPath(list<Std_String>& rgpPath);
	/**Get the encrypt path of some user
	*@param strUser the user
	*@param rgpPath the encrypt path
	*@return the count of the encrypt path
	*/
	int GetEncryptPath(Std_String strUser, list<Std_String>& rgpPath);
	/**Get the encrypt path of some user
	*@param strUser the user
	*@param strPath the new encrypt path
	*@return true if successfully add, false otherwise
	*/
    /** Method: AddEncryptPath
     * 
     * 
     * @param strUser
     * @param strPath
     * @return
     * @date    2010-12-14 (21:52)
     * @author  heidong
     */
	bool AddEncryptPath(Std_String strUser, Std_String strPath);
	/**delete the encrypt path of some user
	*@param strUser the user
	*@param strPath the new encrypt path
	*@return true if successfully add, false otherwise
	*/
	bool DropEncryptPath(Std_String strUser, Std_String strPath);
	/**@}*/

private:
    bool InitDBData();
    UserObject* BuildUserObject(sqlite3_stmt* pStmt);
    ProgObject* BuildProgObject(sqlite3_stmt* pStmt);

private:
	sqlite3* m_pDB;
	Std_String m_strDbFile;
	bool m_bInit;
};
