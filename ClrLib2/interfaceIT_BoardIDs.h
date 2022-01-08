#pragma once

/*
 * TEKWorx Limited Public API source code
 *
 * Unpublished Copyright © 2004 - 2017 by TEKWorx Limited, All rights reserved.
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

#define INTERFACEIT_GET_PRODUCT(HEX_CODE)	(((HEX_CODE) & 0xFF00) >> 8)
#define INTERFACEIT_GET_MODEL(HEX_CODE)		(((HEX_CODE) & 0xFF) >> 0)
#define IIT_PRODUCT(HEX_CODE)	(((HEX_CODE) & 0xFF00) >> 8)
#define IIT_MODEL(HEX_CODE)		(((HEX_CODE) & 0xFF) >> 0)

 /**
  *	Board type identifiers
  */
#define	INTERFACEIT_BOARD_ALL						NULL

  // Misc
  // FDS-MFP - Origional version
#define FDS_MFP											0x0201
#define FDS_MFP_TEXT									"0201"

// FDS-SYS boards - Older origional boards
#define INTERFACEIT_BOARD_FDSSYS1						0x32E1
#define INTERFACEIT_BOARD_FDSSYS1_TEXT					"32E1"
#define INTERFACEIT_BOARD_FDSSYS2						0x32E2
#define INTERFACEIT_BOARD_FDSSYS2_TEXT					"32E2"
#define INTERFACEIT_BOARD_FDSSYS3						0x32E0
#define INTERFACEIT_BOARD_FDSSYS3_TEXT					"32E0"
#define INTERFACEIT_BOARD_FDSSYS4						0x32E3
#define INTERFACEIT_BOARD_FDSSYS4_TEXT					"32E3"

/*
 * Radios
 */
 // Base
#define INTERFACEIT_BOARD_RADIO_CODE					0x4C00
#define INTERFACEIT_BOARD_RADIO_CODE_TEXT				"4C"

// 737 NAV v1
#define INTERFACEIT_BOARD_FDS737NGNAV					0x4C55
#define INTERFACEIT_BOARD_FDS737NGNAV_ID				0x0055
#define INTERFACEIT_BOARD_FDS737NGNAV_TEXT				"4C55"
#define INTERFACEIT_BOARD_FDS737NGNAV_ID_TEXT			"55"

// 737 COMM v1
#define INTERFACEIT_BOARD_FDS737NGCOMM					0x4C56
#define INTERFACEIT_BOARD_FDS737NGCOMM_ID				0x0056
#define INTERFACEIT_BOARD_FDS737NGCOMM_TEXT				"4C56"
#define INTERFACEIT_BOARD_FDS737NGCOMM_ID_TEXT			"56"

// A320 Multi v1
#define INTERFACEIT_BOARD_FDSA320MULTI					0x4C57
#define INTERFACEIT_BOARD_FDSA320MULTI_ID				0x0057
#define INTERFACEIT_BOARD_FDSA320MULTI_TEXT				"4C57"
#define INTERFACEIT_BOARD_FDSA320MULTI_ID_TEXT			"57"

// 737 NAV v2
#define INTERFACEIT_BOARD_FDS737NGNAV_V2				0x4C58
#define INTERFACEIT_BOARD_FDS737NGNAV_V2_ID				0x0058
#define INTERFACEIT_BOARD_FDS737NGNAV_V2_TEXT			"4C58"
#define INTERFACEIT_BOARD_FDS737NGNAV_V2_ID_TEXT		"58"

// 737 COMM v2
#define INTERFACEIT_BOARD_FDS737NGCOMM_V2				0x4C59
#define INTERFACEIT_BOARD_FDS737NGCOMM_V2_ID			0x0059
#define INTERFACEIT_BOARD_FDS737NGCOMM_V2_TEXT			"4C59"
#define INTERFACEIT_BOARD_FDS737NGCOMM_V2_ID_TEXT		"59"

// 737 NAV / COMM
#define INTERFACEIT_BOARD_FDS737NGNAVCOMM				0x4C5A
#define INTERFACEIT_BOARD_FDS737NGNAVCOMM_ID			0x005A
#define INTERFACEIT_BOARD_FDS737NGNAVCOMM_TEXT			"4C5A"
#define INTERFACEIT_BOARD_FDS737NGNAVCOMM_ID_TEXT		"5A"

// FDS-CDU
#define INTERFACEIT_BOARD_FDS_CDU						0x3302
#define INTERFACEIT_BOARD_FDS_CDU_TEXT					"3302"

// FDS-A-ACP
#define INTERFACEIT_BOARD_FDS_A_ACP						0x3303
#define INTERFACEIT_BOARD_FDS_A_ACP_TEXT				"3303"

// FDS-A-RMP
#define INTERFACEIT_BOARD_FDS_A_RMP						0x3304
#define INTERFACEIT_BOARD_FDS_A_RMP_TEXT				"3304"

// FDS-XPNDR
#define FDS_XPNDR										0x3305
#define FDS_XPNDR_TEXT									"3305"

// FDS-737NG-ELECT
#define FDS_737_ELECT									0x3306
#define FDS_737_ELECT_TEXT								"3306"

// FS-MFP v2
#define INTERFACEIT_BOARD_MFP_V2						0x3307
#define INTERFACEIT_BOARD_MFP_V2TEXT					"3307"

// FDS-CONTROLLER-MCP
#define FDS_CONTROLLER_MCP								0x330A
#define FDS_CONTROLLER_MCP_TEXT							"330A"

// FDS-CONTROLLER-EFIS-CA
#define FDS_CONTROLLER_EFIS_CA							0x330B
#define FDS_CONTROLLER_EFIS_CA_TEXT						"330B"

// FDS-CONTROLLER-EFIS-FO
#define FDS_CONTROLLER_EFIS_FO							0x330C
#define FDS_CONTROLLER_EFIS_FO_TEXT						"330C"

// FDS-737NG-MCP-ELVL - Not production
#define FDS_737NG_MCP_ELVL								0x3310
#define FDS_737NG_MCP_ELVL_TEXT							"3310"

// FDS-737-EL-MCP
#define FDS_737_EL_MCP									0x3311
#define FDS_737_EL_MCP_TEXT								"3311"
#define FDS_737_MX_MCP									0x3311
#define FDS_737_MX_MCP_TEXT								"3311"

// FDS-787-MCP
#define FDS_787NG_MCP									0x3319
#define FDS_787NG_MCP_TEXT								"3319"

// FDS-A320-FCU
#define FDS_A320_FCU									0x3316
#define FDS_A320_FCU_TEXT								"3316"

// FDS_747_RADIO (MULTI_COMM)
#define FDS_747_RMP										0x3318
#define FDS_747_RMP_TEXT								"3318"
#define FDS_7X7_MCOMM									0x3318
#define FDS_7X7_MCOMM_TEXT								"3318"

// FDS-CDU v9
#define FDS_CDU_V9										0x331A
#define FDS_CDU_V9_TEXT									"331A"

// FDS-A-TCAS V1
#define FDS_A_TCAS										0x331B
#define FDS_A_TCAS_TEXT									"331B"

// FDS-A-ECAM v1
#define FDS_A_ECAM										0x331C
#define FDS_A_ECAM_TEXT									"331C"

// FDS-A-CLOCK v1
#define FDS_A_CLOCK										0x331D
#define FDS_A_CLOCK_TEXT								"331D"

#define FDS_A_RMP_V2									0x331E
#define FDS_A_RMP_V2_TEXT								"331E"

#define FDS_A_ACP_V2									0x331F
#define FDS_A_ACP_V2_TEXT								"331F"

#define A320_PEDESTAL									0x3320
#define A320_PEDESTAL_TEXT								"3320"

#define A320_OH_ELECT_DISP								0x3321
#define A320_OH_ELECT_DISP_TEXT							"3321"

#define FDS_A320_35VU									0x3321
#define FDS_A320_35VU_TEXT								"3321"

#define FDS_IRS											0x3322
#define FDS_IRS_TEXT									"3322"

#define FDS_OM1											0x3323
#define FDS_OM1_TEXT									"3323"

#define FDS_OE1											0x3324
#define FDS_OE1_TEXT									"3324"

#define FDS_GM1											0x3325
#define FDS_GM1_TEXT									"3325"

#define	FDS_NDF_GDS_NCP									0x3326
#define	FDS_NDF_GDS_NCP_TEXT							"3326"

#define FDS_777_MX_MCP									0x3327
#define FDS_777_MX_MCP_TEXT								"3327"

#define FDS_DCP_EFIS									0x3328
#define FDS_DCP_EFIS_TEXT								"3328"

#define FDS_747_MX_MCP									0x3329
#define FDS_747_MX_MCP_TEXT								"3329"

// 5 Position EFIS
#define FDS_737_PMX_EFIS_5_CA							0x332A
#define FDS_737_PMX_EFIS_5_CA_TEXT						"332A"

// 5 Position EFIS
#define FDS_737_PMX_EFIS_5_FO							0x332B
#define FDS_737_PMX_EFIS_5_FO_TEXT						"332B"

// 737 Pro MX MCP
#define FDS_737_PMX_MCP									0x332C
#define FDS_737_PMX_MCP_TEXT							"332C"

// 737 Pro MX EFIS (Encoder) - CA
#define FDS_737_PMX_EFIS_E_CA							0x332D
#define FDS_737_PMX_EFIS_E_CA_TEXT						"332D"

// 737 Pro MX EFIS (Encoder) - FO
#define FDS_737_PMX_EFIS_E_FO							0x332E
#define FDS_737_PMX_EFIS_E_FO_TEXT						"332E"

// 737 MAX 
#define FDS_737_MAX_ABRAKE_EFIS							0x332F
#define FDS_737_MAX_ABRAKE_EFIS_TEXT					"332F"

// 787 Tuning and Control Panel
#define FDS_787_TCP										0x3330
#define FDS_787_TCP_TEXT								"3330"

// C17 AFCSP
#define FDS_C17_AFCSP									0x33EF
#define FDS_C17_AFCSP_TEXT								"33EF"

// JetMAX Boards
#define JetMAX_737_MCP									0x330F
#define JetMAX_737_MCP_TEXT								"330F"

#define JetMAX_737_RADIO								0x3401
#define JetMAX_737_RADIO_TEXT							"3401"

#define JetMAX_737_XPNDR								0x3402
#define JetMAX_737_XPNDR_TEXT							"3402"

#define JetMAX_777_MCP									0x3403
#define JetMAX_777_MCP_TEXT								"3403"

#define JetMAX_737_MCP_V2								0x3404
#define JetMAX_737_MCP_V2_TEXT							"3404"


// interfaceIT™ Boards
#define IIT_HIO_32_64									0x4101
#define IIT_HIO_32_64_TEXT								"4101"

#define IIT_HIO_64_128									0x4102
#define IIT_HIO_64_128_TEXT								"4102"

#define IIT_HIO_128_256									0x4103
#define IIT_HIO_128_256_TEXT							"4103"

#define IIT_HI_128										0x4105
#define IIT_HI_128_TEXT									"4105"

#define IIT_HRI_8										0x4106
#define IIT_HRI_8_TEXT									"4106"

#define IIT_RELAY_8										0x4107
#define IIT_RELAY_8_TEXT								"4107"

#define IIT_DEV											0x4108
#define IIT_DEV_TEXT									"4108"

#define HIO_RELAY_8										0x4109
#define HIO_RELAY_8_TEXT								"4109"

