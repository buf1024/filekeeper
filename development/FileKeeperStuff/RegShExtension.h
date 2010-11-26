#pragma once

#include "stl.h"
#include <Guiddef.h>
#include "Singleton.h"

namespace lgc
{
	class RegShExtension : public Singleton<RegShExtension>
	{
	public:
		//ContexMenu Handler
		HRESULT STDMETHODCALLTYPE RegCtxMenuHandler(Std_String strProgName, const CLSID& clsid);
		HRESULT STDMETHODCALLTYPE UnRegCtxMenuHandler(Std_String strProgName);

	};

}


