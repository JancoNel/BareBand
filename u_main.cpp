//---------------------------------------------------------------------------

#include <vcl.h>
#include <Windows.h>
#include <wlanapi.h>
#include <wininet.h>
#include <string>
#include <vector>
#include <stdlib.h>

#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "wininet.lib")

#pragma hdrstop

#include "u_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_BareBand* frm_BareBand;
//---------------------------------------------------------------------------
__fastcall Tfrm_BareBand::Tfrm_BareBand(TComponent* Owner) : TForm(Owner) {}

// ---- Utility Logging Function ----
void Log(const std::string &msg)
{
    frm_BareBand->RichEdit1->Lines->Add(msg.c_str());
}

// ---- Extract XML Tag ----
std::string ExtractXMLTag(const std::string &xml, const std::string &tag)
{
    std::string open = "<" + tag + ">";
    std::string close = "</" + tag + ">";
    size_t start = xml.find(open);
    size_t end = xml.find(close);
    if (start == std::string::npos || end == std::string::npos)
        return "";
    start += open.length();
    return xml.substr(start, end - start);
}

// --- Wi-Fi Signal ---
int GetWiFiSignalStrength()
{
    HANDLE hClient = NULL;
    DWORD dwMaxClient = 2, dwCurVersion = 0;
    PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
    PWLAN_CONNECTION_ATTRIBUTES pConnectInfo = NULL;
    DWORD connectInfoSize = sizeof(WLAN_CONNECTION_ATTRIBUTES);
    WLAN_OPCODE_VALUE_TYPE opCode = wlan_opcode_value_type_invalid;

    if (WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient) !=
        ERROR_SUCCESS)
        return -1;

    if (WlanEnumInterfaces(hClient, NULL, &pIfList) != ERROR_SUCCESS)
        return -1;

    for (int i = 0; i < (int)pIfList->dwNumberOfItems; i++) {
        WLAN_INTERFACE_INFO iface = pIfList->InterfaceInfo[i];
        if (WlanQueryInterface(hClient, &iface.InterfaceGuid,
                wlan_intf_opcode_current_connection, NULL, &connectInfoSize,
                (PVOID*)&pConnectInfo, &opCode) == ERROR_SUCCESS)
        {
            int quality =
                pConnectInfo->wlanAssociationAttributes.wlanSignalQuality;
            WlanFreeMemory(pConnectInfo);
            WlanCloseHandle(hClient, NULL);
            return quality;
        }
    }

    WlanCloseHandle(hClient, NULL);
    return -1;
}

// --- Ping ---
bool PingHost(const char* host)
{
    std::string command = "ping -n 1 -w 1000 " + std::string(host) + " >nul";
    return system(command.c_str()) == 0;
}

// --- HTTP GET ---
std::string HttpGet(const std::string &url)
{
    std::wstring wurl(url.begin(), url.end());

    HINTERNET hInternet = InternetOpenW(
        L"TowerSentinel", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) {
        Log("InternetOpenW failed.");
        return "";
    }

    HINTERNET hConnect = InternetOpenUrlW(
        hInternet, wurl.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hConnect) {
        Log("InternetOpenUrlW failed.");
        InternetCloseHandle(hInternet);
        return "";
    }

    char buffer[4096];
    DWORD bytesRead;
    std::string result;

    while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) &&
           bytesRead)
        result.append(buffer, bytesRead);

    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    return result;
}

// --- Main Diagnostic Logic ---
std::string mainer()
{
    int wifi = GetWiFiSignalStrength();
    Log("Wi-Fi Signal Quality: " + std::to_string(wifi));

    if (wifi != -1 && wifi < 40) {
        Log("Weak Wi-Fi signal detected.");
        return "WIFI_ISSUE";
    }

    if (!PingHost("192.168.8.1")) {
		Log("Router not reachable (192.168.8.1).");
		Log("(Are you connected to a LTE router?)");
        return "WIFI_ISSUE";
    }
    Log("Router reachable.");

    if (!PingHost("8.8.8.8")) {
        Log("Google DNS not reachable — possible SIM/ISP issue.");
        return "ISP_DOWN";
    }
    Log("Internet reachable via 8.8.8.8.");

    std::string lte = HttpGet("http://192.168.8.1/api/device/signal");
    if (lte.empty()) {
        Log("Failed to get LTE info from router.");
        return "TOWER_PROBLEM";
    }

    try {
        int rsrp = std::stoi(ExtractXMLTag(lte, "rsrp"));
        int rsrq = std::stoi(ExtractXMLTag(lte, "rsrq"));
        int sinr = std::stoi(ExtractXMLTag(lte, "sinr"));

        Log("RSRP: " + std::to_string(rsrp));
        Log("RSRQ: " + std::to_string(rsrq));
        Log("SINR: " + std::to_string(sinr));

        if (rsrp < -105 || rsrq < -15 || sinr < 0) {
            Log("Signal metrics indicate tower issue.");
            return "TOWER_PROBLEM";
        }
    } catch (...) {
        Log("Error parsing LTE signal XML.");
        return "TOWER_PROBLEM";
    }

    Log("Everything looks good.");
    return "ALL_GOOD";
}

//---------------------------------------------------------------------------

void __fastcall Tfrm_BareBand::btn_diagnoseClick(TObject* Sender)
{

	RichEdit1->Lines->Clear();
	RichEdit1->Lines->Add("Logs");
	RichEdit1->Lines->Add("________________________________________") ;

	std::string status = mainer();

	if (status == "WIFI_ISSUE")
		Label1->Caption = "Local Wi-Fi problem.";
	else if (status == "ISP_DOWN")
        Label1->Caption = "Internet down – possible SIM/ISP problem.";
    else if (status == "TOWER_PROBLEM")
        Label1->Caption = "Tower signal weak or fluctuating.";
    else
        Label1->Caption = "All systems normal.";
}
//---------------------------------------------------------------------------



void __fastcall Tfrm_BareBand::FormActivate(TObject *Sender)
{

btn_diagnose->SetFocus();

}
//---------------------------------------------------------------------------

