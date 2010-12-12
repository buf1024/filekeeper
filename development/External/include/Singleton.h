//=============================================================================
/**
* @file	    Singleton.h
* @brief	
* @author	heidong
* @version	1.0
* @date		2010-10-15 21:30:07
*/
//=============================================================================

#pragma once

namespace lgc
{
	/**Sington supper class.
	*Use the static functions to abtain an instance or release resource.
	*Not to initialize it when you want it to serve as a sington.
	*/
	template <typename TheClass>
	class Singleton
	{
	protected:
		Singleton()
		{

		}
	public:
		virtual ~Singleton()
		{

		}
	public:
		/**The pointer form of sington
		* @return an unique sington
		*/
		static TheClass* GetInstPtr()
		{
			if (sm_pInst == NULL)
			{
				sm_pInst = new TheClass;
			}
			return sm_pInst;
		}
		/**The reference form of sington
		* @return an unique sington
		*/
		static TheClass& GetInst()
		{
			if (sm_pInst == NULL)
			{
				sm_pInst = new TheClass;
			}
			return *sm_pInst;
		}
		/**Release the sington*/
		static void ReleaseRC()
		{
			if (sm_pInst != NULL)
			{
				delete sm_pInst;
				sm_pInst = NULL;
			}
		}
	private:
		static TheClass* sm_pInst;
	};

	template <typename TheClass>
	TheClass* Singleton<TheClass>::sm_pInst = NULL;
}