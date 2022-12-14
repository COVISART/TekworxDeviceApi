#include "pch.h"

#include "TekWorxAPI.h"

using namespace System;
using namespace Runtime::InteropServices;
namespace fs = std::filesystem;

namespace TekWorxAPI
{
    public ref class Device
    {
    public:
    public:
        delegate void OnSwitchChangedDelegate(int);
    public:
        Device()
        {
            [[maybe_unused]] int nKey = 0;
            int nRet = IITAPI_ERR_OK;
            fs::path current_dir = fs::current_path() /= IITAPI_DLL_NAME;
            auto IITAPI_DLL_NAME_X = current_dir.c_str();
            //cout << "Device Api: " << current_dir << endl;

            /*
             *	Load the API DLL
             */
            const HMODULE hinterface_itapi = LoadLibrary(IITAPI_DLL_NAME_X);
            if (!hinterface_itapi)
            {
                printf("Unable to locate and/or load %s.  Error %lu\n", IITAPI_DLL_NAME, GetLastError());
            }

            if (load_pointers(hinterface_itapi) == false)
            {
                printf("Unable to locate all the required entry points.\nPress any key to exit\n");
                _getch();
            }
        }

    public:
        int OpenControllers()
        {
            return p_open_controllers();
        }

        int CloseControllers()
        {
            return p_close_controllers();
        }

    public:
        array<String^>^ GetDeviceList(System::String^% p_buffer, DWORD% dw_size, String^ p_board_type, int% error,
            const int count_of_device/* = NULL*/)
        {
            int retval;
            char* pBuffer;
            DWORD dwSize = dw_size;
            auto dataString = gcnew array<String^>(count_of_device);
            if (p_buffer == nullptr)
            {
                pBuffer = "";
            }
            else
            {
                pBuffer = new char[dwSize + 1];
            }
            char* pszBoard;
            if (p_board_type == nullptr)
            {
                pszBoard = NULL;
            }
            else
            {
                pszBoard = _strdup(msclr::interop::marshal_as<std::string>(p_board_type).c_str());
            }
            if (p_buffer == nullptr)
            {
                retval = p_get_device_list(NULL, &dwSize, pszBoard);
            }
            else
            {
                retval = p_get_device_list(pBuffer, &dwSize, pszBoard);
                int nDevice = 0;
                int nPos = 0;

                while (true)
                {
                    nDevice++;
                    char szData[MAX_PATH] = { 0 };
                    strcpy_s(szData, _countof(szData), pBuffer + nPos);
                    auto n_size = static_cast<int>(strlen(szData));
                    // Check if we are done processing the list
                    if (n_size == 0)
                        break;
                    nPos += n_size + 1;
                    dataString[nDevice - 1] = gcnew String(szData);
                    printf("\tController %.02d: %s\n", nDevice, szData);
                }
            }
            dw_size = dwSize;
            error = retval;
            return dataString;
        }

    public:
    public:
        int GetBoardInfo(DWORD hSession, WrapperClasses::BOARDCAPSlib% cap)
        {
            BOARDCAPS retCaps = { 0 };
            int retval = p_get_board_info(hSession, &retCaps);

            cap.dwFeatures = retCaps.dwFeatures;
            cap.n7SegmentCount = retCaps.n7SegmentCount;
            cap.n7SegmentFirst = retCaps.n7SegmentFirst;
            cap.n7SegmentLast = retCaps.n7SegmentLast;

            cap.nDatalineCount = retCaps.nDatalineCount;
            cap.nDatalineFirst = retCaps.nDatalineFirst;
            cap.nDatalineLast = retCaps.nDatalineLast;

            cap.nLEDCount = retCaps.nLEDCount;
            cap.nLEDLast = retCaps.nLEDLast;
            cap.nLEDFirst = retCaps.nLEDFirst;

            cap.nReserved4 = retCaps.nReserved4;
            cap.nReserved5 = retCaps.nReserved5;
            cap.nReserved6 = retCaps.nReserved6;
            cap.nReserved7 = retCaps.nReserved7;
            cap.nReserved8 = retCaps.nReserved8;
            cap.nReserved9 = retCaps.nReserved9;

            cap.nSwitchCount = retCaps.nSwitchCount;
            cap.nSwitchFirst = retCaps.nSwitchFirst;
            cap.nSwitchLast = retCaps.nSwitchLast;

            cap.nUpdateLevel = retCaps.nUpdateLevel;
            cap.szBoardType = gcnew String(retCaps.szBoardType);
            cap.szManufactureDate = gcnew String(retCaps.szManufactureDate);

            cap.dwFeatures = retCaps.dwFeatures;
            return retval;
        }

        int BindDevicce(String^ DeviceID, DWORD% hSession)
        {
            DWORD localSession;
            int nRet;
            char szData[MAX_PATH];
            strcpy_s(szData, msclr::interop::marshal_as<std::string>(DeviceID).c_str());
            if ((nRet = p_bind(szData, &localSession)) == IITAPI_ERR_OK)
            {
                //All_LED_Enable(localSession);
                p_led_enable(localSession, true);
                hSession = localSession;
                return nRet;
            }

            hSession = localSession;
            return 0;
        }

        int UnbindDevicce(DWORD hSession)
        {
            int nRet;
            nRet = p_un_bind(hSession);
            return nRet;
        }

        int All_LED_Enable(DWORD hSession)
        {
            int nRet;
            nRet = p_led_enable(hSession, true);
            //printf("All_LED_Enable: %d\n", nRet);
            return nRet;
        }

        int All_Led_Test(DWORD hSession)
        {
            int nRet;
            nRet = p_led_test(hSession, true);
            //printf("Led Test: %d\n", nRet);
            return nRet;
        }

        /*int All_LED_Enable(DWORD hSession, BOARDCAPS bcData)
        {
            int nKey = 0;
            int nRet = 0;

            if (bcData.dwFeatures & INTERFACEIT_FEATURE_OUTPUT_LED) {
                nRet = pLED_Enable(hSession, true);
            }
            return nRet;
        }*/
        int All_LED_Disable(DWORD hSession)
        {
            int nRet;
            nRet = p_led_enable(hSession, false);
            //printf("All_LED_Disable: %d\n", nRet);
            return nRet;
        }

        int All_Led_Test_Close(DWORD hSession)
        {
            int nRet;
            nRet = p_led_test(hSession, false);
            //printf("Led Test: %d\n", nRet);
            return nRet;
        }

        /*int All_LED_Disable(DWORD hSession, BOARDCAPS bcData)
        {
            int nKey = 0;
            int nRet = 0;

            if (bcData.dwFeatures & INTERFACEIT_FEATURE_OUTPUT_LED) {
                nRet = pLED_Enable(hSession, false);
            }
            return nRet;
        }*/

        int LED_Enable(DWORD hSession)
        {
            int nRet = 0;
            nRet = p_led_enable(hSession, true);
            return nRet;
        }

        int LED_Set(DWORD hSession, int target, bool state)
        {
            int nRet = 0;
            nRet = p_led_set(hSession, target, state);
            return nRet;
        }

        int LED_Disable(DWORD hSession)
        {
            int nRet = 0;
            nRet = p_led_enable(hSession, false);
            return nRet;
        }

        int All_7Segment_Enable(DWORD hSession)
        {
            int nRet = 0;
            nRet = p7_segment_enable(hSession, true);
            printf("All_7Segment_Enable: %d\n", nRet);
            return nRet;
        }

        int All_7Segment_Disable(DWORD hSession)
        {
            int nRet = 0;
            nRet = p7_segment_enable(hSession, false);
            return nRet;
        }

        /*
        *
        * This function sets the 7 Segment data. You can set individual segment by specifing the segment and the character to display,
        * or you can set sections of segment by specifing the start and passing in the entire string.
        */
        int _7Segment_Display(DWORD hSession, int target, int input)
        {
            char str[10];
            _itoa_s(input, str, 10);
            int nRet = 0;
            nRet = p7_segment_display(hSession, str, target);
            return nRet;
        }

        int _7Segment_Display(DWORD hSession, int target, String^ input)
        {
            char str[10];
            strcpy_s(str, msclr::interop::marshal_as<std::string>(input).c_str());
            int nRet = 0;
            nRet = p7_segment_display(hSession, str, target);
            return nRet;
        }

        int _7Segment_Float(DWORD hSession, int target, String^ input)
        {
            char str[20];
            //itoa(input, str, 10);

            //printf(str, sizeof input, "%f", input);
            strcpy_s(str, msclr::interop::marshal_as<std::string>(input).c_str());
            //printf("Data: input %s -> %s\n", input, str);
            int nRet = 0;
            nRet = p7_segment_display(hSession, str, target);
            return nRet;
        }

        static double round(const float var)
        {
            // 37.66666 * 100 =3766.66 
            // 3766.66 + .5 =3767.16    for rounding off value 
            // then type cast to int so value is 3767 
            // then divided by 100 so the value converted into 37.67 
            return (var * 100 + .5) / 100;
        }

        static int switch_enable(const DWORD h_session)
        {
            int nRet = 0;
            if ((nRet = p_switch_enable_callback(h_session, true, key_pressed_proc)) == IITAPI_ERR_OK)
            {
                printf("Switch callback enable.  Code %d\n", nRet);
            }
            else
            {
                printf("Error during switch callback enable.  Error %d\n", nRet);
            }
            return nRet;
        }

        static int switch_disable(DWORD hSession)
        {
            int nRet = 0;
            nRet = p_switch_enable_callback(hSession, false, NULL);
            return nRet;
        }

        /*
         *	Test the LED (if they exist on this board)
         */
        static int brightness_enable(DWORD hSession)
        {
            return p_brightness_enable(hSession, true);
        }

        int Brightness_Disable(DWORD hSession) 
        {
            return p_brightness_enable(hSession, false);
        }

        int Brightness_Set(DWORD hSession, int Brightness)
        {
            return p_brightness_set(hSession, Brightness);
        }

        int Analog_Enable(DWORD hSession)
        {
            return p_analog_enable(hSession, true);
        }

        int Analog_Disable(DWORD hSession)
        {
            return p_analog_enable(hSession, false);
        }

        int Analog_Get(DWORD hSession, int% output)
        {
            int nCurrentValue = -1;
            int nRet = p_analog_get_value(hSession, 0, &nCurrentValue);
            output = nCurrentValue;
            return nRet;
        }

        int DataLine_Enable(DWORD hSession)
        {
            return p_dataline_enable(hSession, true);
        }

        int DataLine_Disable(DWORD hSession)
        {
            return p_dataline_enable(hSession, false);
        }

        int DataLine_Set(DWORD hSession, int target, bool status)
        {
            return p_dataline_set(hSession, target, status);
        }

        int Servo_Enable(DWORD hSession, bool status)
        {
            return p_servo_enable(hSession, status);
        }

        int Servo_Set_Center(DWORD hSession, int nController, int nServo, int nPos)
        {
            return p_servo_set_center(hSession, nController, nServo, nPos);
        }

        int Servo_Set_Position(DWORD hSession, int nController, int nServo, int nPos)
        {
            return p_servo_set_position(hSession, nController, nServo, nPos);
        }

    public:
        int GetControllerCount(int% pnControllerCount)
        {
            int nTotalControllers = -1;
            int retval = p_get_controller_count(&nTotalControllers);

            pnControllerCount = nTotalControllers;
            return retval;
        }
    };
}
