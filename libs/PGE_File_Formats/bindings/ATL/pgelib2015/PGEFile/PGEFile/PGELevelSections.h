// PGELevelSections.h: Deklaration von CPGELevelSections

#pragma once
#include "resource.h"       // Hauptsymbole



#include "PGEFile_i.h"
#include "Utils/ComUtils.h"
#include "PGELevelSection.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Singlethread-COM-Objekte werden auf der Windows CE-Plattform nicht vollst�ndig unterst�tzt. Windows Mobile-Plattformen bieten beispielsweise keine vollst�ndige DCOM-Unterst�tzung. Definieren Sie _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA, um ATL zu zwingen, die Erstellung von Singlethread-COM-Objekten zu unterst�tzen und die Verwendung eigener Singlethread-COM-Objektimplementierungen zu erlauben. Das Threadmodell in der RGS-Datei wurde auf 'Free' festgelegt, da dies das einzige Threadmodell ist, das auf Windows CE-Plattformen ohne DCOM unterst�tzt wird."
#endif

using namespace ATL;


// CPGELevelSections

class ATL_NO_VTABLE CPGELevelSections :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPGELevelSections, &CLSID_PGELevelSections>,
	public IDispatchImpl<PGEComUtils::CommonComCollectionImpl<IPGELevelSections, IPGELevelSection, CPGELevelSection>, &IID_IPGELevelSections, &LIBID_PGEFileLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CPGELevelSections()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PGELEVELSECTIONS)

DECLARE_NOT_AGGREGATABLE(CPGELevelSections)

BEGIN_COM_MAP(CPGELevelSections)
	COM_INTERFACE_ENTRY(IPGELevelSections)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



};

OBJECT_ENTRY_NON_CREATEABLE_EX_AUTO(__uuidof(PGELevelSections), CPGELevelSections)
