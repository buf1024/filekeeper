//=============================================================================
/**
* @file	    Reg.h
* @brief	
* @author	heidong
* @version	1.0
* @date		2010-10-15 20:16:23
*/
//=============================================================================
#pragma once

#include <list>
#include <map>
#include <functional>
#include "Singleton.h"
#include "stl.h"

namespace lgc
{
	/**
	*Take example:
	*
	*[HKEY_CURRENT_USER\Software\Google]
	*[HKEY_CURRENT_USER\Software\Google\Common]
	*[HKEY_CURRENT_USER\Software\Google\Common\Rlz]
	*[HKEY_CURRENT_USER\Software\Google\Common\Rlz\Events]
	*[HKEY_CURRENT_USER\Software\Google\Common\Rlz\Events\N]
	*"N1A"=dword:00000001
	*[HKEY_CURRENT_USER\Software\Google\Common\Rlz\PTimes]
	*"N"=hex(b):80,0a,a1,e1,c8,3e,cb,01
	*[HKEY_CURRENT_USER\Software\Google\Common\Rlz\RLZs]
	*"N1"="1N1GGPY_zhCN389"
	*
	*"N1"="1N1GGPY_zhCN389" is RegData
	*[HKEY_CURRENT_USER\Software\Google\Common\Rlz\RLZs] is RegNode
	*/

	/**RegData encapsulates all type of data.*/	
	class RegData
	{
	public:
		/**default constructors*/
		RegData();
		/**destructor*/
		~RegData();
		/**copy constructor*/
		RegData(const RegData& other);
	public:
		/**@name operators*/
		/**@{*/
		/**assign operator*/
		RegData& operator = (const RegData& other);
		/**==operator, if the key name is equal than the data is equal*/
		bool operator == (const RegData& other);
		/**!=operator, if the key name is not equal than the data is not equal*/
		bool operator != (const RegData& other);
		/**@}*/

	public:		
		/**@name operations*/
		/**@{*/
		/**Check wether the RegData is valide.
		*@return true is is valide, otherwise false.
		*/
		bool IsDataValid() const;

		/**Convenient function to set the value, We should use this function instead of others
		*@param nType The Type of the RegData, correspond type please referece MSDN
		*@param strKey The Name
		*@param pData The data
		*@param dwDataLen The length of the data
		*/
		void SetValue(DWORD dwType, const Std_String strKey, const void* pData, DWORD dwDataLen);
		/**The Type of the RegData
		*@param nType The Type of the RegData, correspond type please referece MSDN
		*/
		void SetDataType(DWORD nType);
		/**Get The type of RegData
		*@return The type of RegData
		*/
		DWORD GetDataType() const;

		/**Set the Name of the RegData Item
		*@param strKeyName The Name
		*/
		void SetKeyName(const Std_String strKeyName);
		/**Get the key name of the RegData Item
		*@return The RegData Name
		*/
		Std_String GetKeyName() const;
		
		/**Set the RegData Item Value
		*@param pData The data
		*@param dwLength The length of the data
		*/
		void SetData(const VOID* pData, DWORD dwLength);
		/**Get the RegData Item Value
		*@return the RegData Item Value
		*/
		const VOID* GetData() const;	

		/**Set the lenght of the RegData
		*@param nLengh The length
		*/
		void SetDataLength(DWORD nLength);
		/**Get the Data lenght
		*@return the length of the RegData
		*/
		DWORD GetDataLength() const;
		/**@}*/

	private:

		//The Type
		DWORD m_nType;	
		//The KeyName
		Std_String m_strKeyName;
		//The Data
		VOID* m_pRegData;
		//The Length of the data
		DWORD m_nLength;
	};

	/*Data comparer. Use internal, Client should advoid calling this Class*/
	template<typename TheClass>
	class RegDataCompare : public std::binary_function<TheClass*, TheClass*, bool>
	{
	public:
		/*Compare function*/
		bool operator()(TheClass* pLeft, TheClass* pRight) const;
	};


	/**The RegNode Data.
	*When a new object is construct, It tries to retrive as much data as possible.
	*We usually use the RegFactory to create a new object of the type
	*/
	class RegNode
	{	
		typedef std::list<RegData*>::iterator REGDataIterator;
		typedef std::map<Std_String, RegNode*>::iterator REGNodeIterator;
	public:
		/**@name Constructor & Destructor*/
		/**@{*/
		/**Constructor
		*@param hKey The Reg Key
		*@param bUpdata The flag specific wether update data when the object is desconstruct
		*/
		RegNode(HKEY hRootKey, Std_String strCurSubKey, HKEY hKey, bool bUpdate = false);
		/**Destructor, Release resource*/
		virtual ~RegNode();
		/**@}*/
	public:
		/**Add a new regdata the the node
		*@param pRegData The RegData
		*@param bOverwrite The flag specific wether update the data to a new one if it exists
		*@return true if successfully added, false otherwise.
		*/
		bool AddRegData(RegData* pRegData, bool bOverwrite = true);
		/**Convenient function to set the value
		*@param nType The Type of the RegData, correspond type please referece MSDN
		*@param strKey The Name
		*@param pData The data
		*@param dwDataLen The length of the data
		*@param bOverwrite The flag specific wether update the data to a new one if it exists
		*@return true if successfully added, false otherwise.
		*/
		bool AddRegData(DWORD dwType, const Std_String strKey, const void* pData, DWORD dwDataLen, bool bOverwrite = true);
		/**Get the specfic key value
		*@param strKey The Key
		*@param regData The value get from the node
		*@return true if the value is successfully copy to the target.
		*/
		bool GetRegData(const Std_String strKey, RegData& regData);


		/**Add an new node. if the node exsist, just return it.
		*@param strKey The subkey name
		*@return the exsting/New NodeData, or NULL if fail
		*/
		RegNode* AddNode(const Std_String strKey);
		/**Delete the specific subkey
		*Delete the specific subkey
		*@param strKey The subkey, if it is empty delete itself
		*@return true if the specific key is delete, otherwise false
		*/
		bool DeleteNode(const Std_String strKey = _T(""));
		/**Get the specific key node data
		*@param strKey The subkey
		*@return the RegNode or NULL if does not exist.
		*/
		RegNode* GetNode(const Std_String strKey);

		/**Save the data
		*@return true is successfully save, false otherwise
		*/
		bool Save();

		Std_String GetRelativeSubKey();
		HKEY GetRootHKEY();
		HKEY GetCurrentHKEY();
		bool IsValid() const;

		bool DestroySave();
		void SetDestroySave(bool bUpdate);


	protected:
		void InitData();
		void ClearUp();

	protected:
		HKEY m_hKey;
		bool m_bUpdate;

		/****/
		HKEY m_hRootKey;
		Std_String m_strSubKey;
		/****/

	private:
		std::list<RegData*> m_lstRegData;
		std::map<Std_String, RegNode*> m_mapRegNode;

	};
	
	/**The Factory of RegUtil*/
	class RegFactory : public Singleton<RegFactory>
	{
	public:

		/**To Create or Get an exsiting RegGoupData
		*@param hKey The Root Reg KEY
		*@param strSubKey The subkey path
		*@param bUpdate The flag spcific wether save the changed values when object is deconstuct.
		*@return an exsiting/new RegGroupData, NULL if fails.
		*/
		RegNode* CreateRegNode(HKEY hKey, const Std_String strSubKey, bool bUpdate = false);
		/**To Get an exsiting RegGoupData
		*@param hKey The Root Reg KEY
		*@param strSubKey The subkey path
		*@param bUpdate The flag spcific wether save the changed values when object is deconstuct.
		*@return an exsiting/new RegNode, NULL if fails.
		*/
		RegNode* GetRegNode(HKEY hKey, const Std_String strSubKey, bool bUpdate = false);
	};
}

