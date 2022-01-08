#pragma once

#ifdef _WIN64
#define IITAPI_DLL_NAME	"interfaceITAPI x64.dll"
#else
#define IITAPI_DLL_NAME	"interfaceITAPI.dll"
#endif

/**
 *	Switch callback definition
 */
typedef BOOL(CALLBACK* INTERFACEIT_KEY_NOTIFY_PROC)(DWORD hSession, int nSwitch, int nDirection);

/**
 *	Device change notification
 */
typedef BOOL(CALLBACK* INTERFACEIT_DEVICE_CHANGE_NOTIFY_PROC)(int nAction);

typedef struct {
	int nSwitch;
	int nDirection;
} SWITCHINFO;

/**
 * Device Notification
 */
#define INTERFACEIT_DEVICE_REMOVAL			0x01
#define INTERFACEIT_DEVICE_ARRIVAL			0x02

 /**
  *	Switch direction information
  */
#define INTERFACEIT_SWITCH_DIR_UNKNOWN		0xFF
#define INTERFACEIT_SWITCH_DIR_UP			0x0
#define INTERFACEIT_SWITCH_DIR_DOWN			0x1

  /**
   *	Board options
   */
#define INTERFACEIT_BOARD_OPTION_NONE		0x0
#define INTERFACEIT_BOARD_OPTION_CDUKEYS	0x1		// CDU v9 does not need this.  Used for v7 CDU
#define INTERFACEIT_BOARD_OPTION_FORCE64	0x2		// Requred for the new FDS-CONTROLLER-MCP boards for relay to function
#define INTERFACEIT_BOARD_OPTION_RESERVED3	0x4

   /**
	*	Error codes
	*/
#define IITAPI_ERR_BASE												0

#define IITAPI_ERR_OK							(IITAPI_ERR_BASE -  0)
#define IITAPI_ERR_CONTROLLERS_OPEN_FAILED		(IITAPI_ERR_BASE -  1)
#define IITAPI_ERR_CONTROLLERS_ALREADY_OPENED	(IITAPI_ERR_BASE -  2)
#define IITAPI_ERR_CONTROLLERS_NOT_OPENED		(IITAPI_ERR_BASE -  3)
#define IITAPI_ERR_INVALID_HANDLE				(IITAPI_ERR_BASE -  4)
#define IITAPI_ERR_INVALID_POINTER				(IITAPI_ERR_BASE -  5)
#define IITAPI_ERR_INVALID_CONTROLLER_NAME		(IITAPI_ERR_BASE -  6)
#define IITAPI_ERR_FAILED						(IITAPI_ERR_BASE -  7)
#define IITAPI_ERR_INVALID_CONTROLLER_POINTER	(IITAPI_ERR_BASE -  8)
#define IITAPI_ERR_INVALID_CALLBACK				(IITAPI_ERR_BASE -  9)
#define IITAPI_ERR_RETRIEVING_CONTROLLER		(IITAPI_ERR_BASE - 10)
#define IITAPI_ERR_NOT_ENABLED					(IITAPI_ERR_BASE - 11)
#define IITAPI_ERR_BUFFER_NOT_LARGE_ENOUGH		(IITAPI_ERR_BASE - 12)
#define IITAPI_ERR_BUFFER_NOT_LARGE_ENOUGHT		(IITAPI_ERR_BASE - 12)	// Previous release typo
#define IITAPI_ERR_PARAMETER_LENGTH_INCORRECT	(IITAPI_ERR_BASE - 13)
#define IITAPI_ERR_PARAMETER_OUT_OF_RANGE		(IITAPI_ERR_BASE - 14)
#define IITAPI_ERR_FEATURE_NOT_AVAILABLE		(IITAPI_ERR_BASE - 15)
#define IITAPI_ERR_ALREADY_ENABLED				(IITAPI_ERR_BASE - 16)
#define IITAPI_ERR_NO_ITEMS						(IITAPI_ERR_BASE - 17)
#define IITAPI_ERR_CONTROLLER_ALREADY_BOUND		(IITAPI_ERR_BASE - 18)
#define IITAPI_ERR_NO_CONTROLLERS_FOUND			(IITAPI_ERR_BASE - 19)
#define IITAPI_ERR_UNKNOWN						(IITAPI_ERR_BASE - 20)
#define IITAPI_ERR_NOT_LICENSED					(IITAPI_ERR_BASE - 21)
#define IITAPI_ERR_INVALID_LICENSE				(IITAPI_ERR_BASE - 22)
#define IITAPI_ERR_ALREADY_LICENSED				(IITAPI_ERR_BASE - 23)
#define IITAPI_ERR_GENERATING_ACTIVATIONID		(IITAPI_ERR_BASE - 24)
#define IITAPI_ERR_EXPIRED_LICENSE				(IITAPI_ERR_BASE - 25)
#define IITAPI_ERR_EXPIRED_TRIAL				(IITAPI_ERR_BASE - 26)

	/* CPPDOC_BEGIN_EXCLUDE */

	/*
	 *	Exported function typedefs
	 */

#ifndef INTERFACEITAPI_EXPORTS

	 /**
	  * Main functions
	  */
typedef int (*PINTERFACEIT_OPENCONTROLLERS)(void);
typedef int (*PINTERFACEIT_GETDEVICELIST)(char* pszBuffer, DWORD* dwSize, char* pBoardType/* = NULL*/);
typedef int (*PINTERFACEIT_CLOSECONTROLLERS)(void);

/**
 * Controller Functions
 */
typedef int (*PINTERFACEIT_BIND)(const char* pszController, DWORD* phSession);
typedef int (*PINTERFACEIT_UNBIND)(DWORD hSession);
typedef int (*PINTERFACEIT_GETBOARDINFO)(DWORD hSession, BOARDCAPS* pbc);
typedef int (*PINTERFACEIT_SETBOARDOPTIONS)(DWORD hSession, DWORD dwOptions);
typedef int (*PINTERFACEIT_GETCONTROLLERCOUNT)(int* pnControllerCount);

/**
 * LED Functions
 */
typedef int (*PINTERFACEIT_LED_ENABLE)(DWORD hSession, bool bEnable/* = true*/);
typedef int (*PINTERFACEIT_LED_TEST)(DWORD hSession, bool bEnable/* = true*/);
typedef int (*PINTERFACEIT_LED_SET)(DWORD hSession, int nLED, bool bOn/* = true*/);

/**
 * Switch Functions
 */
typedef int (*PINTERFACEIT_SWITCH_ENABLE_CALLBACK)(DWORD hSession, bool bEnable, INTERFACEIT_KEY_NOTIFY_PROC pProc);
typedef int (*PINTERFACEIT_SWITCH_ENABLE_POLL)(DWORD hSession, bool bEnable);
typedef int (*PINTERFACEIT_SWITCH_GET_ITEM)(DWORD hSession, int* pnSwitch, int* pnDirection);
typedef int (*PINTERFACEIT_SWITCH_GET_STATE)(DWORD hSession, int nSwitch, int* pnState);

/**
 * 7 Segment Functions
 */
typedef int (*PINTERFACEIT_7SEGMENT_ENABLE)(DWORD hSession, bool bEnable/* = true*/);
typedef int (*PINTERFACEIT_7SEGMENT_DISPLAY)(DWORD hSession, const char* pszData, int nStart);

/**
 * Dataline Functions
 */
typedef int (*PINTERFACEIT_DATALINE_ENABLE)(DWORD hSession, bool bEnable/* = true*/);
typedef int (*PINTERFACEIT_DATALINE_SET)(DWORD hSession, int nDataline, bool bOn/* = true*/);

/**
 *	Servo Functions
 */
typedef int (*PINTERFACEIT_SERVO_ENABLE)(DWORD hSession, bool bEnable/* = true*/);
typedef int (*PINTERFACEIT_SERVO_SET_POSITION)(DWORD hSession, int nController, int nServo, int nPos);
typedef int (*PINTERFACEIT_SERVO_SET_CENTER)(DWORD hSession, int nController, int nServo, int nPos);

/**
 * Brightness Functions
 */
typedef int (*PINTERFACEIT_BRIGHTNESS_ENABLE)(DWORD hSession, bool bEnable/* = true*/);
typedef int (*PINTERFACEIT_BRIGHTNESS_SET)(DWORD hSession, int nBrightness);

/**
 * Analog Input Functions
 */
typedef int (*PINTERFACEIT_ANALOG_ENABLE)(DWORD hSession, bool bEnable/* = true*/);
typedef int (*PINTERFACEIT_ANALOG_GET_VALUE)(DWORD hSession, int nReserved, int* pnValue);
typedef int (*PINTERFACEIT_ANALOG_GET_VALUES)(DWORD hSession, unsigned char* pbValues, int nValuesSize);

/**
 *	Licensing functions - Deprecated - Not for new development
 */
typedef int (*PINTERFACEIT_LICENSE_GETMACHINEACTIVATIONID)(char* pBuffer, DWORD* dwSize);
typedef int (*PINTERFACEIT_LICENSE_SETMACHINEACTIVATION)(char* pBuffer);
typedef int (*PINTERFACEIT_LICENSE_ISACTIVATED)();

/**
 * Device change notification
 */
typedef int (*PINTERFACEIT_ENABLE_DEVICECHANGE_NOTIFICATION_CALLBACK)(bool bEnable, INTERFACEIT_DEVICE_CHANGE_NOTIFY_PROC pProc);

/**
 *	Misc functions
 */
typedef int (*PINTERFACEIT_GETAPIVERSION)(char* pBuffer, DWORD* dwSize);
typedef int (*PINTERFACEIT_ENABLELOGGING)(bool bEnable);

#endif

/* CPPDOC_END_EXCLUDE */
