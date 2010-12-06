#include "StdAfx.h"
// EventSink.cpp
#include "eventsink.h"

ULONG EventSink::AddRef()
{
    return InterlockedIncrement(&m_lRef);
}

ULONG EventSink::Release()
{
    LONG lRef = InterlockedDecrement(&m_lRef);
    if(lRef == 0)
        delete this;
    return lRef;
}

HRESULT EventSink::QueryInterface(REFIID riid, void** ppv)
{
    if (riid == IID_IUnknown || riid == IID_IWbemObjectSink)
    {
        *ppv = (IWbemObjectSink *) this;
        AddRef();
        return WBEM_S_NO_ERROR;
    }
    else return E_NOINTERFACE;
}


//HRESULT EventSink::Indicate(long lObjectCount, IWbemClassObject **apObjArray)
//{
//	HRESULT hres = S_OK;
//
//    for (int i = 0; i < lObjectCount; i++)
//    {
//        printf("Event occurred\n");
//    }
//
//    return WBEM_S_NO_ERROR;
//}
//HRESULT EventSink::Indicate(LONG lObjectCount, IWbemClassObject **ppObjArray)
//{
//    HRESULT            hr;
//    _variant_t         vPackageID;   // pkg status properties
//    _variant_t         vTarget;         // pkg status object
//    IUnknown          *pIUnknown;
//    IWbemClassObject  *pinstPkgStatus = NULL;
//
//    for( int i = 0; i < lObjectCount; i++ )
//    {
//        hr = (ppObjArray[i])->Get(L"TargetInstance", 0, &vTarget, NULL, NULL);
//        pIUnknown = (IUnknown *)vTarget;
//        hr = pIUnknown->QueryInterface(IID_IWbemClassObject, (void **)&pinstPkgStatus);
//        pIUnknown->Release();
//
//        hr = pinstPkgStatus->Get(L"PackageID", 0, &vPackageID, NULL, NULL);
//        pinstPkgStatus->Release();
//        pinstPkgStatus = NULL;
//
//        //Do something with the information
//    }
//    return WBEM_NO_ERROR;
//} 
void Print(HRESULT& hres, _variant_t& vVAR, LPCWSTR tagName);

HRESULT EventSink::Indicate(long lObjectCount, IWbemClassObject **apObjArray)
{
    HRESULT hres = S_OK;

    try
    {
        for (int i = 0; i < lObjectCount; i++)
        {
            VARIANT vVar;
			_variant_t         vTarget;         // pkg status object
			IUnknown          *pIUnknown;
			IWbemClassObject  *pinstPkgStatus = NULL;
			_variant_t         vName;   // 
			_variant_t         vExecutablePath;   // 
			_variant_t         vCommandLine;   // 

			hres = (apObjArray[0])->Get(L"TargetInstance", 0, &vTarget, NULL, NULL);
			if (FAILED(hres))
            {
                cout << "Failed to get TargetInstance in apObjArray[i]: " << hres << endl;
            }//if

			pIUnknown = (IUnknown *)vTarget;
			hres = pIUnknown->QueryInterface(IID_IWbemClassObject, (void **)&pinstPkgStatus);
			if (FAILED(hres))
            {
                cout << "Failed to get IID_IWbemClassObject in TargetInstance: " << hres << endl;
            }//if
			pIUnknown->Release();

			//==================================================================================
			hres = pinstPkgStatus->Get(L"Name", 0, &vName, NULL, NULL);
			Print(hres, vName, L"Name");

			hres = pinstPkgStatus->Get(L"ExecutablePath", 0, &vExecutablePath, NULL, NULL);
			Print(hres, vExecutablePath, L"ExecutablePath");

			hres = pinstPkgStatus->Get(L"CommandLine", 0, &vCommandLine, NULL, NULL);
			Print(hres, vCommandLine, L"CommandLine");

			pinstPkgStatus->Release();
			pinstPkgStatus = NULL;

			cout << endl << endl;
       
        }//for
	}//try
    catch(_com_error &err)
    {
        cout << "caught _com_error: " << err.Error() << endl;
		cout << "caught Description: " << err.Description() << endl;
		cout << "caught ErrorMessage: " << err.ErrorMessage() << endl;
    }//catch

    return WBEM_S_NO_ERROR;
}//Indicate

//By kavin.2010-12-06
void Print(HRESULT& hres, _variant_t& vVAR, LPCWSTR tagName)
{
	try
	{
		if (FAILED(hres))
		{
			cout << "Failed to get Name: " << hres << endl;
		}//if
		else
		{
			_variant_t vExecPath;
			vExecPath.Attach(vVAR);

			wcout << tagName << ": ";
			if (vExecPath.vt == VT_NULL)
				wcout << tagName << L" is null." << endl;
			else
				cout << (const char*)((_bstr_t)vExecPath) << endl;// 
		}//else
	}//try
    catch(_com_error &err)
    {
        cout << "caught _com_error: " << err.Error() << endl;
		cout << "caught Description: " << err.Description() << endl;
		cout << "caught ErrorMessage: " << err.ErrorMessage() << endl;
    }//catch
}



HRESULT EventSink::SetStatus(
            /* [in] */ LONG lFlags,
            /* [in] */ HRESULT hResult,
            /* [in] */ BSTR strParam,
            /* [in] */ IWbemClassObject __RPC_FAR *pObjParam
        )
{
    if(lFlags == WBEM_STATUS_COMPLETE)
    {
        printf("Call complete. hResult = 0x%X\n", hResult);
    }
    else if(lFlags == WBEM_STATUS_PROGRESS)
    {
        printf("Call in progress.\n");
    }

    return WBEM_S_NO_ERROR;
}    // end of EventSink.cpp

