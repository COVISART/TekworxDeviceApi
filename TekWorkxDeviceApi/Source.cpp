/*
 * TEKWorx Limited Public API Test source code
 *
 * Unpublished Copyright (C) 2004 - 2014 by TEKWorx Limited, All rights reserved.
 *
 * No part of this file may be duplicated, revised, translated, localized or
 * modified in any manner or compiled, linked or uploaded or downloaded to or
 * from any computer system without the prior written consent of TEKWorx Limited.
 *
 * DISCLAIMER:
 *
 * TEKWorx Limited disclaims and excludes any and all express, implied,
 * and statutory warranties, including, without limitation, warranties
 * of good title, warranties against infringement, and the implied
 * warranties of merchantibility and fitness for a particular purpose.
 * TEKWorx Limited does not warrant that the software will satisfy
 * customer's requirements or that the licensed works are without defect
 * or error or that the operation of the software will be uninterrupted.
 * TEKWorx Limited makes no warranties respecting any technical services
 * or support tools provided under the agreement, and disclaims all other
 * warranties, including the implied warranties of merchantability and
 * fitness for a particular purpose.
 *
 */

 /*
	 This is a sample application that describes controlling various components
	 that the interfaceIT API exposes.  Some interfaces are not released to the
	 public or have not been designed yet, however there are function that are
	 exposed in this API for future use.

	 This code is intended for learning purposes only.
 */


 // interfaceITAPI_Test.cpp : Defines the entry point for the console application.
 //

#include "pch.h"
#include <windows.h>
#include "interfaceIT_BoardInfo.h"
#include "interfaceIT_BoardIDs.h"
#include "interfaceITAPI_Data.h"

#include "Simulator.h"
#include <conio.h>
#include <stdlib.h>

/*
 *	Function prototypes
 */
void Test_LED(DWORD hSession, BOARDCAPS bcData);
void Test_7Segment(DWORD hSession, BOARDCAPS bcData);
void Test_Dataline(DWORD hSession, BOARDCAPS bcData);
void Test_Switches(DWORD hSession, BOARDCAPS bcData);
void Test_Servo(DWORD hSession, BOARDCAPS bcdata);
void Test_Brightness(DWORD hSession, BOARDCAPS bcdata);
void Test_AnalogInput(DWORD hSession, BOARDCAPS bcData);
void Test_DeviceChangeNotification();
bool LoadPointers(HMODULE hinterfaceITAPI);
void DumpBoardList(char* pBuffer, DWORD dwSize);

/*
 *	Global variables
 */

 /*
  * API Functions
  */
PINTERFACEIT_OPENCONTROLLERS pOpenControllers = NULL;
PINTERFACEIT_GETDEVICELIST pGetDeviceList = NULL;
PINTERFACEIT_GETCONTROLLERCOUNT pGetControllerCount = NULL;
PINTERFACEIT_CLOSECONTROLLERS pCloseControllers = NULL;
PINTERFACEIT_BIND pBind = NULL;
PINTERFACEIT_UNBIND pUnBind = NULL;
PINTERFACEIT_GETBOARDINFO pGetBoardInfo = NULL;
PINTERFACEIT_LED_ENABLE pLED_Enable = NULL;
PINTERFACEIT_LED_TEST pLED_Test = NULL;
PINTERFACEIT_LED_SET pLED_Set = NULL;
PINTERFACEIT_SWITCH_ENABLE_CALLBACK pSwitch_Enable_Callback = NULL;
PINTERFACEIT_SWITCH_ENABLE_POLL pSwitch_Enable_Poll = NULL;
PINTERFACEIT_SWITCH_GET_ITEM pSwitch_Get_Item = NULL;
PINTERFACEIT_SWITCH_GET_STATE pSwitch_Get_State = NULL;
PINTERFACEIT_GETAPIVERSION pGetAPIVersion = NULL;
PINTERFACEIT_7SEGMENT_ENABLE p7Segment_Enable = NULL;
PINTERFACEIT_7SEGMENT_DISPLAY p7Segment_Display = NULL;
PINTERFACEIT_DATALINE_ENABLE pDataline_Enable = NULL;
PINTERFACEIT_DATALINE_SET pDataline_Set = NULL;
PINTERFACEIT_SERVO_ENABLE pServo_Enable = NULL;
PINTERFACEIT_SERVO_SET_POSITION pServo_Set_Position = NULL;
PINTERFACEIT_SERVO_SET_CENTER pServo_Set_Center = NULL;
PINTERFACEIT_BRIGHTNESS_ENABLE pBrightness_Enable = NULL;
PINTERFACEIT_BRIGHTNESS_SET pBrightness_Set = NULL;
PINTERFACEIT_ANALOG_ENABLE pAnalog_Enable = NULL;
PINTERFACEIT_ANALOG_GET_VALUE pAnalog_GetValue = NULL;
PINTERFACEIT_ANALOG_GET_VALUES pAnalog_GetValues = NULL;
PINTERFACEIT_LICENSE_GETMACHINEACTIVATIONID pLicense_GetMachineActivationID = NULL;
PINTERFACEIT_LICENSE_SETMACHINEACTIVATION pLicense_SetMachineActivation = NULL;
PINTERFACEIT_LICENSE_ISACTIVATED pLicense_IsActivated;
PINTERFACEIT_SETBOARDOPTIONS pSetOptions;
PINTERFACEIT_ENABLE_DEVICECHANGE_NOTIFICATION_CALLBACK pEnable_Device_Change_CallBack = NULL;
PINTERFACEIT_ENABLELOGGING pEnableLogging = NULL;

/*
 * Helper functions
 */
int _KeyPressed(void) {
	if (_kbhit()) {
		_getch();
		return true;
	}
	return false;
}

/*
 *	Callback to receive notification of a switch change
 */
BOOL CALLBACK KeyPressedProc(DWORD hSession, int nSwitch, int nDir)
{
	printf("\tSession %d, Switch %d is now (%d) %s\n",
		hSession, nSwitch, nDir, nDir == INTERFACEIT_SWITCH_DIR_DOWN ? "on / down" : "off / up");

	return TRUE;
}

/*
 *	Callback to receive device change notificaitons
 */
BOOL CALLBACK DeviceChangeProc(int nAction)
{
	printf("\tAn interfaceIT device was %s\n",
		nAction == INTERFACEIT_DEVICE_ARRIVAL ? "added" : "removed");

	return TRUE;
}

/*
 *	Main function
 */
int main(int argc, char* argv[])
{
	int nKey = 0;
	int nRet = IITAPI_ERR_OK;

	/*
	 *	Load the API DLL
	 */
	LPCWSTR IITAPI_DLL_NAME_X = L"interfaceITAPI x64.dll";

	HMODULE hinterfaceITAPI = LoadLibrary(IITAPI_DLL_NAME_X);
	if (!hinterfaceITAPI) {
		printf("Unable to locate and/or load %s.  Error %d\n", IITAPI_DLL_NAME, GetLastError());
		return -1;
	}


	/*
	 *	Load all the entry points we want to use
	 */
	if (LoadPointers(hinterfaceITAPI) == false) {
		printf("Unable to locate all the required entry points.\nPress any key to exit\n");
		_getch();
		return -1;
	}

	printf("Do you want to enable API function logging? (Y/N) ");
	nKey = _getche();
	printf("\n");
	if (nKey == 'y' || nKey == 'Y') {
		if ((nRet = pEnableLogging(true)) == 0)
			printf("Logging enabled\n");
		else
			printf("Error (%d) enabling logging\n", nRet);
	}

	char szAPIVersion[MAX_PATH] = { 0 };
	DWORD dwAPIVerSize = sizeof(szAPIVersion);

	nRet = pGetAPIVersion(szAPIVersion, &dwAPIVerSize);
	if (nRet == IITAPI_ERR_OK) {
		printf("interfaceIT API version %s\n\n", szAPIVersion);

		/*
		 * License the API
		 */
		 /* Licensing removed in version 1.6 */

		 /* Device Change Notificaiton
		  *
		  */
		Test_DeviceChangeNotification();

		/*
		 *	Open the controllers / API
		 */
		if ((nRet = pOpenControllers()) == IITAPI_ERR_OK) {
			DWORD dwSize = 0;
			char* pBuffer = NULL;
			char* pszBoard = INTERFACEIT_BOARD_ALL;
			int nTotalControllers = -1;

			/*
			 *	Get the total number of controllers attached to the system
			 */
			if ((nRet = pGetControllerCount(&nTotalControllers)) == IITAPI_ERR_OK)
				printf("Total controllers detected: %d\n\n", nTotalControllers);
			else
				printf("Unable to retrieve the total number of controllers.  Error %d\n\n", nRet);

			/*
			 *	Find out how much memory we need to allocate by passing NULL
			 */
			pGetDeviceList(NULL, &dwSize, pszBoard);
			/*
			 *	Allocate Buffer
			 */
			pBuffer = new char[dwSize + 1];
			/*
			 *	Retrieve a list of all connected boards
			 */
			nRet = pGetDeviceList(pBuffer, &dwSize, pszBoard);

			if (nRet == IITAPI_ERR_OK && dwSize != 1) {
				int nPos = 0;
				int nDevice = 0;

				DumpBoardList(pBuffer, dwSize);

				while (1) {
					nDevice++;
					char szData[MAX_PATH] = { 0 };
					strcpy_s(szData, _countof(szData), pBuffer + nPos);
					int nSize = strlen(szData);
					// Check if we are done processing the list
					if (nSize == 0)
						break;
					else {
						nPos += nSize + 1;
						DWORD hSession = 0;
						/*
						 *	Bind to this board
						 */
						if ((nRet = pBind(szData, &hSession)) == IITAPI_ERR_OK) {
							/*
							 *	Retrieve information about this board
							 */
							BOARDCAPS bcData = { 0 };
							if ((nRet = pGetBoardInfo(hSession, &bcData)) == IITAPI_ERR_OK) {
								printf("Board %s manufactured on %s has the following features:\n", bcData.szBoardType, bcData.szManufactureDate);
								if (bcData.dwFeatures == INTERFACEIT_FEATURE_NONE)
									printf("\tNo features programmed.\n\tPlease obtain the update patch for this board.\n");
								if (bcData.dwFeatures & INTERFACEIT_FEATURE_INPUT_SWITCHES)
									printf("\t%d Switches (%d - %d)\n", bcData.nSwitchCount, bcData.nSwitchFirst, bcData.nSwitchLast);
								if (bcData.dwFeatures & INTERFACEIT_FEATURE_OUTPUT_LED)
									printf("\t%d LEDs (%d - %d)\n", bcData.nLEDCount, bcData.nLEDFirst, bcData.nLEDLast);
								if (bcData.dwFeatures & INTERFACEIT_FEATURE_OUTPUT_7SEGMENT)
									printf("\t%d 7 Segments (%d - %d)\n", bcData.n7SegmentCount, bcData.n7SegmentFirst, bcData.n7SegmentLast);
								if (bcData.dwFeatures & INTERFACEIT_FEATURE_OUTPUT_DATALINE)
									printf("\t%d Datalines (%d - %d)\n", bcData.nDatalineCount, bcData.nDatalineFirst, bcData.nDatalineLast);
								if (bcData.dwFeatures & INTERFACEIT_FEATURE_OUTPUT_SERVO)
									printf("\t%d Servos (%d - %d)\n", bcData.nServoController, bcData.nServoControllerFirst, bcData.nServoControllerLast);
								if (bcData.dwFeatures & INTERFACEIT_FEATURE_SPECIAL_BRIGHTNESS)
									printf("\tBrightness control supported\n");
								if (bcData.dwFeatures & INTERFACEIT_FEATURE_SPECIAL_ANALOG_INPUT)
									printf("\tAnalog input supported (Single Channel)\n");
								if (bcData.dwFeatures & INTERFACEIT_FEATURE_SPECIAL_ANALOG16_INPUT)
									printf("\tAnalog input supported (16 Channels)\n");
								printf("\n");
							}

							printf("Do you wish to test this board? (Y/N) ");
							nKey = _getche();
							printf("\n");
							if (nKey == 'y' || nKey == 'Y') {
								Test_LED(hSession, bcData);

								Test_7Segment(hSession, bcData);
								/*Test_Dataline(hSession, bcData);
								Test_Switches(hSession, bcData);
								Test_Servo(hSession, bcData);
								Test_Brightness(hSession, bcData);
								Test_AnalogInput(hSession, bcData);*/
							}
							pUnBind(hSession);
						}
						else {
							printf("Unable to bind to the board (%d)\n", nRet);
						}
					}
					printf("\n");
				} // while
			}
			else {
				if (dwSize == 1)	// Check for an empty buffer
					printf("Not devices were found.\n");
			}

			delete[] pBuffer;

			pCloseControllers();
		}
		else if (nRet == IITAPI_ERR_NO_CONTROLLERS_FOUND) {
			printf("\nNo interfaceIT controllers found\n");
		}
		else if (nRet == IITAPI_ERR_EXPIRED_TRIAL) {
			printf("\nYour trial period has expired.\n");
		}
		else if (nRet == IITAPI_ERR_EXPIRED_LICENSE) {
			printf("\nYour license key has expired");
		}
		else {
			printf("\nError opening interfaceIT controllers.  Error %d\n", nRet);
		}
	}


	// Free the DLL
	FreeLibrary(hinterfaceITAPI);
	printf("\nAPI finished.  Press any key to close\n");
	_getch();
	return 0;
}

/*
 *	Test the LED (if they exist on this board)
 */
void Test_LED(DWORD hSession, BOARDCAPS bcData)
{
	int nKey = 0;
	int nRet = 0;
	if (bcData.dwFeatures & INTERFACEIT_FEATURE_OUTPUT_LED) {
		printf("Do you wish to test LED's? (Y/N) ");
		nKey = _getche();
		printf("\n");
		if (nKey == 'y' || nKey == 'Y') {
			printf("\nTesting LED's\n");
			// Test LED functions
			nRet = pLED_Enable(hSession, true);
			printf("\tTurning on test mode\n");
			if ((nRet = pLED_Test(hSession, true)) == IITAPI_ERR_OK) {
				nKey = _getche();
				Sleep(2000);
				printf("\tTurning off test mode\n");
				pLED_Test(hSession, false);
				/*Sleep(1000);
				printf("\tTurning on then off each LED\n");
				for (int nLED = bcData.nLEDFirst; nLED < bcData.nLEDLast + 1; nLED++) {
					printf("\n Led: %d \n", nLED);
					nRet = pLED_Set(hSession, nLED, true);
					if (div(nLED, 2).rem == 0)
						printf(".");

					//Sleep(100);
					nKey = _getche();
					nRet = pLED_Set(hSession, nLED, false);
				}*/
			}
			nRet = pLED_Enable(hSession, false);
			printf("\n");
		}
	}
}

/*
 *	Test the 7 Segment (if they exist on this board)
 */
void Test_7Segment(DWORD hSession, BOARDCAPS bcData)
{
	int nKey = 0;
	int nRet = 0;
	if (bcData.dwFeatures & INTERFACEIT_FEATURE_OUTPUT_7SEGMENT) {
		printf("Do you wish to test 7 Segment's? (Y/N) ");
		nKey = _getche();
		printf("\n");
		if (nKey == 'y' || nKey == 'Y') {
			printf("\nTesting 7 Segment displays's\n");
			// Test LED functions
			nRet = p7Segment_Enable(hSession, true);
			printf("\tTurning on then off each 7 Segment");
			char c = '8';
			char* seven = &c;
			for (int nDisplay = bcData.n7SegmentFirst; nDisplay < bcData.n7SegmentLast + 1; nDisplay++) {

				nRet = p7Segment_Display(hSession, "3.", nDisplay);
				printf("\n Display: %d \n", nDisplay);
				nKey = _getche();
				printf(".");
				//Sleep(200);
				nRet = p7Segment_Display(hSession, "8.", nDisplay);
			}
			//nRet = p7Segment_Enable(hSession, false);
			printf("\n");
		}
	}
}

/*
 *	Test the LED (if they exist on this board)
 */
void Test_Dataline(DWORD hSession, BOARDCAPS bcData)
{
	int nKey = 0;
	int nRet = 0;
	if (bcData.dwFeatures & INTERFACEIT_FEATURE_OUTPUT_DATALINE) {
		printf("Do you wish to test Datalines? (Y/N) ");
		nKey = _getche();
		printf("\n");
		if (nKey == 'y' || nKey == 'Y') {
			printf("\nTesting Dataline\n");

			nRet = pDataline_Enable(hSession, true);
			printf("\tTurning on then off each dataline");
			for (int nDataline = bcData.nDatalineFirst; nDataline < bcData.nDatalineLast + 1; nDataline++) {
				nRet = pDataline_Set(hSession, nDataline, true);
				printf(".");
				Sleep(500);
				nRet = pDataline_Set(hSession, nDataline, false);
			}
			nRet = pDataline_Enable(hSession, false);
			printf("\n");
		}
	}
}

/*
 *	Enable and test the switches (if they exist on this board)
 */
void Test_Switches(DWORD hSession, BOARDCAPS bcData)
{
	int nKey = 0;
	int nRet = 0;
	if (bcData.dwFeatures & INTERFACEIT_FEATURE_INPUT_SWITCHES) {
		printf("Do you wish to test switches? (Y/N) ");
		nKey = _getche();
		printf("\n");
		if (nKey == 'y' || nKey == 'Y') {
			// Test switch functions
			nRet = IITAPI_ERR_OK;

			printf("Do you wish to set any options? (Y/N) ");
			nKey = _getche();
			printf("\n");
			if (nKey == 'y' || nKey == 'Y') {
				printf("\tPlease enter the OR'ed value for the options you want set: ");
				char szOptions[MAX_PATH] = { 0 };
				size_t stRead = 0;
				_cgets_s(szOptions, MAX_PATH, &stRead);
				int nOptions = atoi(szOptions);
				printf("\n\tSetting options to %d\n", nOptions);
				nRet = pSetOptions(hSession, nOptions);
				if (nRet == IITAPI_ERR_OK)
					printf("\tOptions set.");
				else
					printf("\tOptions set failed (%d)", nRet);
			}

			printf("\nTesting switches - *** Press any key to terminate switch test ***\n");

			printf("\nDo you wish to test Callback or Poll mode (C / P) ? ");
			int nMode = _getche();
			printf("\n");
			if (nMode == 'c' || nMode == 'C') {
				if ((nRet = pSwitch_Enable_Callback(hSession, true, KeyPressedProc)) == IITAPI_ERR_OK) {
					while (!_KeyPressed()) {
						Sleep(250);
					}
					nRet = pSwitch_Enable_Callback(hSession, false, NULL);
				}
				else {
					printf("Error during switch callback enable.  Error %d\n", nRet);
				}
			}
			else if (nMode == 'p' || nMode == 'P') {
				if ((nRet = pSwitch_Enable_Poll(hSession, true)) == IITAPI_ERR_OK) {
					int nSwitch = 0;
					int nDirection = -1;
					while (!_KeyPressed()) {
						int nGetRet = pSwitch_Get_Item(hSession, &nSwitch, &nDirection);
						if (nGetRet == IITAPI_ERR_OK) {
							KeyPressedProc(hSession, nSwitch, nDirection);
						}
						else if (nGetRet != IITAPI_ERR_NO_ITEMS) {
							printf("\nError reading switch information.  Error %d\n", nGetRet);
						}
						else {
							Sleep(100);
						}
					}
					nRet = pSwitch_Enable_Poll(hSession, false);
				}
				else {
					printf("Error during switch poll enable.  Error %d\n", nRet);
				}
			}
		}
	}
}

/*
 *	Enable and test the servos (if they exist on this board)
 *
 *	These calls are not supported and are only here for potential future expansion
 */
void Test_Servo(DWORD hSession, BOARDCAPS bcData)
{
	int nKey = 0;
	int nRet = 0;
	if (bcData.dwFeatures & INTERFACEIT_FEATURE_OUTPUT_SERVO) {
		printf("Do you wish to test servos? (Y/N) ");
		nKey = _getche();
		printf("\n");
		if (nKey == 'y' || nKey == 'Y') {
			printf("\nTesting Servo(s)\n");

			nRet = pServo_Enable(hSession, true);
			if (nRet == IITAPI_ERR_OK) {
				int nController = 'a';
				while (nController < '1' || nController > '8') {
					printf("\tPlease select a servo controller (1 - 8): ");
					nController = _getche();
					printf("\n");
				}
				nController -= 0x30;

				int nServo = 'a';
				while (nServo < '0' || nServo > '7') {
					printf("\tPlease select a servo (0 - 7): ");
					nServo = _getche();
					printf("\n");
				}
				nServo -= 0x30;

				while (1) {
					char szBuffer[32] = { 30 };
					//char* pData = NULL;
					size_t stSizeRead = 0;
					printf("\tPlease enter the position for servo %d on controller %d (0-255 / s / q): ", nServo, nController);
					if (_cgets_s(szBuffer, _countof(szBuffer), &stSizeRead) == 0) {
						if (_stricmp(szBuffer, "q") == 0) {
							break;
						}
						else if (_stricmp(szBuffer, "s") == 0) {	// sweep
							int nPos = -1;
							for (nPos = 0; nPos < 256; nPos++) {
								nRet = pServo_Set_Position(hSession, nController, nServo, nPos);
								if (nRet != IITAPI_ERR_OK) {
									printf("Error setting the position of servo %d on controller %d.  Error %d\n", nServo, nController, nRet);
									break;
								}
								Sleep(2);
							}
							Sleep(200);
							for (nPos = 255; nPos >= 0; nPos--) {
								nRet = pServo_Set_Position(hSession, nController, nServo, nPos);
								if (nRet != IITAPI_ERR_OK) {
									printf("Error setting the position of servo %d on controller %d.  Error %d\n", nServo, nController, nRet);
									break;
								}
								Sleep(2);
							}
							Sleep(100);
							nRet = pServo_Set_Position(hSession, nController, nServo, 128);
						}
						else {
							int nPos = atoi(szBuffer);
							if (nPos >= 0 && nPos <= 255) {
								nRet = pServo_Set_Position(hSession, nController, nServo, nPos);
								if (nRet != IITAPI_ERR_OK) {
									printf("Error setting the position of servo %d on controller %d.  Error %d\n", nServo, nController, nRet);
									break;
								}
							}
						}
					}
				}
				nRet = pServo_Enable(hSession, false);
			}
			else {
				printf("Error enabling servo control.  Error %d\n", nRet);
			}
		}
	}
}

/*
 *	Test the LED (if they exist on this board)
 */
void Test_Brightness(DWORD hSession, BOARDCAPS bcData)
{
	int nKey = 0;
	int nRet = 0;
	if (bcData.dwFeatures & INTERFACEIT_FEATURE_SPECIAL_BRIGHTNESS) {
		printf("Do you wish to test Brightness? (Y/N) ");
		nKey = _getche();
		printf("\n");
		if (nKey == 'y' || nKey == 'Y') {
			printf("\nTesting Brightness\n");

			nRet = pBrightness_Enable(hSession, true);
			if (nRet == IITAPI_ERR_OK) {
				printf("\tRamping brightness up.");
				for (int nBrightness = 0; nBrightness < 256; nBrightness++) {
					if ((nRet = pBrightness_Set(hSession, nBrightness)) != IITAPI_ERR_OK) {
						printf("\nError %d setting brightness to %d\n", nBrightness, nRet);
						break;
					}
					if (nBrightness % 10 == 3)
						printf(".");
					Sleep(10);
				}
				printf("\n");

				/*printf("\tRamping brightness down.");
				for (int nBrightness = 255; nBrightness >= 0; nBrightness--) {
					if ((nRet = pBrightness_Set(hSession, nBrightness)) != IITAPI_ERR_OK) {
						printf("\nError %d setting brightness to %d\n", nBrightness, nRet);
						break;
					}
					if (nBrightness % 10 == 3)
						printf(".");
					Sleep(10);
				}*/

				//nRet = pBrightness_Enable(hSession, false);
				printf("\n");
			}
		}
	}
}

/*
 *	Test the analog input (if it exists on the board)
 */
void Test_AnalogInput(DWORD hSession, BOARDCAPS bcData)
{
	int nKey = 0;
	int nRet = 0;
	if (bcData.dwFeatures & INTERFACEIT_FEATURE_SPECIAL_ANALOG_INPUT || bcData.dwFeatures & INTERFACEIT_FEATURE_SPECIAL_ANALOG16_INPUT) {
		printf("Do you wish to test the analog input? (Y/N) ");
		nKey = _getche();
		printf("\n");
		if (nKey == 'y' || nKey == 'Y') {
			printf("\nTesting analog input.  Press any key to start (then any key to stop)\n");
			_getch();
			nRet = pAnalog_Enable(hSession, true);
			if (nRet == IITAPI_ERR_OK) {
				unsigned char bChannelData[16] = { 0 };
				int nChannelData = 16;
				int nCurrentValue = -1;
				while (!_KeyPressed()) {
					if (bcData.dwFeatures & INTERFACEIT_FEATURE_SPECIAL_ANALOG_INPUT) {
						nCurrentValue = 0;
						printf("\tReading value: ");
						int nGetRet = pAnalog_GetValue(hSession, 0, &nCurrentValue);
						if (nGetRet == IITAPI_ERR_OK) {
							printf("%d\n", nCurrentValue);
						}
						else {
							printf("Error %d\n", nGetRet);
							break;
						}
					}
					else if (bcData.dwFeatures & INTERFACEIT_FEATURE_SPECIAL_ANALOG16_INPUT) {
						printf("Channels: ");
						int nGetRet = pAnalog_GetValues(hSession, bChannelData, nChannelData);
						if (nGetRet == IITAPI_ERR_OK) {
							printf("%.03d %.03d %.03d %.03d %.03d %.03d %.03d %.03d %.03d %.03d %.03d %.03d %.03d %.03d %.03d %.03d\n",
								bChannelData[0], bChannelData[1], bChannelData[2], bChannelData[3],
								bChannelData[4], bChannelData[5], bChannelData[6], bChannelData[7],
								bChannelData[8], bChannelData[9], bChannelData[10], bChannelData[11],
								bChannelData[12], bChannelData[13], bChannelData[14], bChannelData[15]);
						}
						else {
							printf("Error %d\n", nGetRet);
							break;
						}
					}
					else {
						break;
					}
				}
				nRet = pAnalog_Enable(hSession, false);
			}
			else {
				printf("Error enabling analog inputs: %d\n", nRet);
			}
		}
	}
}

/*
 *	Test the device change notification
 */
void Test_DeviceChangeNotification()
{
	int nKey = 0;
	int nRet = 0;
	printf("Do you wish to test device change notification? (Y/N) ");
	nKey = _getche();
	printf("\n\n");
	if (nKey == 'y' || nKey == 'Y') {
		// Test change notificaiton
		nRet = IITAPI_ERR_OK;

		printf("\nTesting change notificaiton - *** Press any key to stop monitoring ***\n");

		if ((nRet = pEnable_Device_Change_CallBack(true, DeviceChangeProc)) == IITAPI_ERR_OK) {
			while (!_KeyPressed()) {
				Sleep(250);
			}
			nRet = pEnable_Device_Change_CallBack(false, NULL);
		}
		else {
			printf("Error enabling the device change callback.  Error %d\n", nRet);
		}
	}
}

/*
 *	Dump the list of controllers we have read
 */
void DumpBoardList(char* pBuffer, DWORD dwSize)
{
	int nDevice = 0;
	int nPos = 0;

	printf("Controller List\n");
	while (1) {
		nDevice++;
		char szData[MAX_PATH] = { 0 };
		strcpy_s(szData, _countof(szData), pBuffer + nPos);
		int nSize = strlen(szData);
		// Check if we are done processing the list
		if (nSize == 0)
			break;
		else {
			nPos += nSize + 1;
			printf("\tController %.02d: %s\n", nDevice, szData);
		}
	}
	printf("\n");
}

bool LoadPointers(HMODULE hinterfaceITAPI)
{
	pOpenControllers = (PINTERFACEIT_OPENCONTROLLERS)GetProcAddress(hinterfaceITAPI, "interfaceIT_OpenControllers");
	pGetDeviceList = (PINTERFACEIT_GETDEVICELIST)GetProcAddress(hinterfaceITAPI, "interfaceIT_GetDeviceList");
	pGetControllerCount = (PINTERFACEIT_GETCONTROLLERCOUNT)GetProcAddress(hinterfaceITAPI, "interfaceIT_GetTotalControllers");
	pCloseControllers = (PINTERFACEIT_CLOSECONTROLLERS)GetProcAddress(hinterfaceITAPI, "interfaceIT_CloseControllers");
	pBind = (PINTERFACEIT_BIND)GetProcAddress(hinterfaceITAPI, "interfaceIT_Bind");
	pUnBind = (PINTERFACEIT_UNBIND)GetProcAddress(hinterfaceITAPI, "interfaceIT_UnBind");
	pGetBoardInfo = (PINTERFACEIT_GETBOARDINFO)GetProcAddress(hinterfaceITAPI, "interfaceIT_GetBoardInfo");
	pLED_Enable = (PINTERFACEIT_LED_ENABLE)GetProcAddress(hinterfaceITAPI, "interfaceIT_LED_Enable");
	pLED_Test = (PINTERFACEIT_LED_TEST)GetProcAddress(hinterfaceITAPI, "interfaceIT_LED_Test");
	pLED_Set = (PINTERFACEIT_LED_SET)GetProcAddress(hinterfaceITAPI, "interfaceIT_LED_Set");
	pSwitch_Enable_Callback = (PINTERFACEIT_SWITCH_ENABLE_CALLBACK)GetProcAddress(hinterfaceITAPI, "interfaceIT_Switch_Enable_Callback");
	pSwitch_Enable_Poll = (PINTERFACEIT_SWITCH_ENABLE_POLL)GetProcAddress(hinterfaceITAPI, "interfaceIT_Switch_Enable_Poll");
	pSwitch_Get_Item = (PINTERFACEIT_SWITCH_GET_ITEM)GetProcAddress(hinterfaceITAPI, "interfaceIT_Switch_Get_Item");
	pSwitch_Get_State = (PINTERFACEIT_SWITCH_GET_STATE)GetProcAddress(hinterfaceITAPI, "interfaceIT_Switch_Get_State");
	pGetAPIVersion = (PINTERFACEIT_GETAPIVERSION)GetProcAddress(hinterfaceITAPI, "interfaceIT_GetAPIVersion");
	p7Segment_Enable = (PINTERFACEIT_7SEGMENT_ENABLE)GetProcAddress(hinterfaceITAPI, "interfaceIT_7Segment_Enable");
	p7Segment_Display = (PINTERFACEIT_7SEGMENT_DISPLAY)GetProcAddress(hinterfaceITAPI, "interfaceIT_7Segment_Display");
	pDataline_Enable = (PINTERFACEIT_DATALINE_ENABLE)GetProcAddress(hinterfaceITAPI, "interfaceIT_Dataline_Enable");
	pDataline_Set = (PINTERFACEIT_DATALINE_SET)GetProcAddress(hinterfaceITAPI, "interfaceIT_Dataline_Set");
	pServo_Enable = (PINTERFACEIT_SERVO_ENABLE)GetProcAddress(hinterfaceITAPI, "interfaceIT_Servo_Enable");
	pServo_Set_Position = (PINTERFACEIT_SERVO_SET_POSITION)GetProcAddress(hinterfaceITAPI, "interfaceIT_Servo_Set_Position");
	pServo_Set_Center = (PINTERFACEIT_SERVO_SET_CENTER)GetProcAddress(hinterfaceITAPI, "interfaceIT_Servo_Set_Center");
	pBrightness_Enable = (PINTERFACEIT_BRIGHTNESS_ENABLE)GetProcAddress(hinterfaceITAPI, "interfaceIT_Brightness_Enable");
	pBrightness_Set = (PINTERFACEIT_BRIGHTNESS_SET)GetProcAddress(hinterfaceITAPI, "interfaceIT_Brightness_Set");
	pAnalog_Enable = (PINTERFACEIT_ANALOG_ENABLE)GetProcAddress(hinterfaceITAPI, "interfaceIT_Analog_Enable");
	pAnalog_GetValue = (PINTERFACEIT_ANALOG_GET_VALUE)GetProcAddress(hinterfaceITAPI, "interfaceIT_Analog_GetValue");
	pAnalog_GetValues = (PINTERFACEIT_ANALOG_GET_VALUES)GetProcAddress(hinterfaceITAPI, "interfaceIT_Analog_GetValues");
	pLicense_GetMachineActivationID = (PINTERFACEIT_LICENSE_GETMACHINEACTIVATIONID)GetProcAddress(hinterfaceITAPI, "interfaceIT_License_GetMachineActivationID");
	pLicense_SetMachineActivation = (PINTERFACEIT_LICENSE_SETMACHINEACTIVATION)GetProcAddress(hinterfaceITAPI, "interfaceIT_License_SetMachineActivation");
	pLicense_IsActivated = (PINTERFACEIT_LICENSE_ISACTIVATED)GetProcAddress(hinterfaceITAPI, "interfaceIT_License_IsActivated");
	pSetOptions = (PINTERFACEIT_SETBOARDOPTIONS)GetProcAddress(hinterfaceITAPI, "interfaceIT_SetBoardOptions");
	pEnable_Device_Change_CallBack = (PINTERFACEIT_ENABLE_DEVICECHANGE_NOTIFICATION_CALLBACK)GetProcAddress(hinterfaceITAPI, "interfaceIT_Enable_DeviceChange_Notification_Callback");
	pEnableLogging = (PINTERFACEIT_ENABLELOGGING)GetProcAddress(hinterfaceITAPI, "interfaceIT_EnableLogging");

	/*
	 *	Check we have all the entry points
	 */
	if (!pOpenControllers || !pGetDeviceList || !pCloseControllers || !pGetControllerCount ||
		!pBind || !pUnBind || !pGetBoardInfo ||
		!pLED_Enable || !pLED_Test || !pLED_Set ||
		!pSwitch_Enable_Callback || !pSwitch_Enable_Poll || !pSwitch_Get_Item || !pSwitch_Get_State ||
		!p7Segment_Enable || !p7Segment_Display ||
		!pDataline_Enable || !pDataline_Set ||
		!pServo_Enable || !pServo_Set_Position || !pServo_Set_Center ||
		!pBrightness_Enable || !pBrightness_Set ||
		!pAnalog_Enable || !pAnalog_GetValue || !pAnalog_GetValues ||
		!pLicense_GetMachineActivationID || !pLicense_SetMachineActivation || !pLicense_IsActivated ||
		!pEnable_Device_Change_CallBack ||
		!pSetOptions ||
		!pEnableLogging ||
		!pGetAPIVersion) {
		return false;
	}

	return true;
}