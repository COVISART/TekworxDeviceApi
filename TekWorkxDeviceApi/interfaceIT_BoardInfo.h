#pragma once

/*
 * TEKWorx Limited Public API source code
 *
 * Unpublished Copyright © 2004 - 2010 by TEKWorx Limited, All rights reserved.
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

 /**
  *	Board information structure
  */
typedef struct {
	int nLEDCount;				// Total number of LED outputs
	int nLEDFirst;				// First LED output number
	int nLEDLast;				// Last LED output number
	int nSwitchCount;			// Total number of switches
	int nSwitchFirst;			// First switch input number
	int nSwitchLast;			// Last switch input number
	int n7SegmentCount;			// Total number of 7 Segment output (future)
	int n7SegmentFirst;			// First 7 Segment output number (future)
	int n7SegmentLast;			// Last 7 Segment output number (future)
	int nDatalineCount;			// Total datalines
	int nDatalineFirst;			// First dataline number
	int nDatalineLast;			// Last dataline number
	int nServoController;		// Total servo controllers
	int nServoControllerFirst;	// First servo controller
	int nServoControllerLast;	// Last servo controller
	int nReserved4;
	int nReserved5;
	int nReserved6;
	int nReserved7;
	int nReserved8;
	int nReserved9;
	CHAR szBoardType[5];		// Null-terminated string containing the board type identifier
	CHAR szManufactureDate[9];	// Null-terminated string containing the manufacture date of the board
	DWORD dwFeatures;			// Features that are currently enabled on the board
	int nUpdateLevel;			// Update level that is currently applied to this board
} BOARDCAPS, * PBOARDCAPS;

/**
 *	Features
 */
#define INTERFACEIT_FEATURE_NONE					0x00000000

#define INTERFACEIT_FEATURE_INPUT_SWITCHES			0x00000001
#define INTERFACEIT_FEATURE_INPUT_RC				0x00000002
#define INTERFACEIT_FEATURE_INPUT_SPI				0x00000004
#define INTERFACEIT_FEATURE_INPUT_DATALINE			0x00000008
#define INTERFACEIT_FEATURE_INPUT_IIC				0x00000010
#define INTERFACEIT_FEATURE_INPUT_RESERVED6			0x00000020
#define INTERFACEIT_FEATURE_INPUT_RESERVED7			0x00000040
#define INTERFACEIT_FEATURE_INPUT_RESERVED8			0x00000080

#define INTERFACEIT_FEATURE_OUTPUT_LED				0x00000100
#define INTERFACEIT_FEATURE_OUTPUT_LCD				0x00000200
#define INTERFACEIT_FEATURE_OUTPUT_7SEGMENT			0x00000400
#define INTERFACEIT_FEATURE_OUTPUT_SPI				0x00000800
#define INTERFACEIT_FEATURE_OUTPUT_IIC				0x00001000
#define INTERFACEIT_FEATURE_OUTPUT_DATALINE			0x00002000
#define INTERFACEIT_FEATURE_OUTPUT_SERVO			0x00004000
#define INTERFACEIT_FEATURE_OUTPUT_RESERVED16		0x00008000

#define INTERFACEIT_FEATURE_SPECIAL_BRIGHTNESS		0x00010000
#define INTERFACEIT_FEATURE_SPECIAL_ANALOG_INPUT	0x00020000
#define INTERFACEIT_FEATURE_SPECIAL_ANALOG16_INPUT	0x00040000
