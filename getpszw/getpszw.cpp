
#include <iostream>
#include <objbase.h>
//#include <WinSock2.h>
//#include <Iphlpapi.h>
#include <netcon.h>
#pragma comment(lib,"Iphlpapi.lib")

//#pragma comment(lib,"Rpcrt4.lib")//GUID

//#pragma comment(lib,"ole32.lib")
using namespace std;




int main(int argc, char* argv[])
{
	INetConnectionManager *pManager;
	INetConnection *pConnection;
	IEnumNetConnection *pEnum;
	ULONG           celtFetched;
	CoInitialize(NULL);
	CoCreateInstance(CLSID_ConnectionManager, NULL, CLSCTX_SERVER, IID_INetConnectionManager, (void**)&pManager);
	pManager->EnumConnections(NCME_DEFAULT, &pEnum);
	pManager->Release();
	while (pEnum->Next(1, &pConnection, &celtFetched) == S_OK)
	{
		NETCON_PROPERTIES*   properties;
		pConnection->GetProperties(&properties);
		DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, properties->pszwName, -1, NULL, 0, NULL, FALSE);
		DWORD dwNum2 = WideCharToMultiByte(CP_OEMCP, NULL, properties->pszwDeviceName, -1, NULL, 0, NULL, FALSE);
		char *psText;
		char *psText2;
		psText = new char[dwNum];
		psText2 = new char[dwNum2];
		if (!psText)
		{
			delete[]psText;
		}
		if (!psText2)
		{
			delete[]psText2;
		}
		WideCharToMultiByte(CP_OEMCP, NULL, properties->pszwName, -1, psText, dwNum, NULL, FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, properties->pszwDeviceName, -1, psText2, dwNum2, NULL, FALSE);
		printf(psText);
		printf("\r\n");
		printf(psText2);
		printf("\r\n");
		delete[]psText;
		delete[]psText2;
	}
	system("pause");
	return 0;
}