#pragma once
#include "pch.h"
#include <windows.h>
#include "interfaceIT_BoardInfo.h"
#include "interfaceITAPI_Data.h"
#include <filesystem>
#include <iostream>
#include <string>

#include <conio.h>
#include <stdlib.h>
#include <msclr/marshal_cppstd.h>
#include <filesystem>

using namespace CommonClasses;
using std::cout;
using std::cin;
using std::endl;
using std::filesystem::current_path;

/*
 *	Global variables
 */

/*
 * API Functions
 */
inline PINTERFACEIT_OPENCONTROLLERS p_open_controllers = nullptr;
inline PINTERFACEIT_GETDEVICELIST p_get_device_list = nullptr;
inline PINTERFACEIT_GETCONTROLLERCOUNT p_get_controller_count = nullptr;
inline PINTERFACEIT_CLOSECONTROLLERS p_close_controllers = nullptr;
inline PINTERFACEIT_BIND p_bind = nullptr;
inline PINTERFACEIT_UNBIND p_un_bind = nullptr;
inline PINTERFACEIT_GETBOARDINFO p_get_board_info = nullptr;
inline PINTERFACEIT_LED_ENABLE p_led_enable = nullptr;
inline PINTERFACEIT_LED_TEST p_led_test = nullptr;
inline PINTERFACEIT_LED_SET p_led_set = nullptr;
inline PINTERFACEIT_SWITCH_ENABLE_CALLBACK p_switch_enable_callback = nullptr;
inline PINTERFACEIT_SWITCH_ENABLE_POLL p_switch_enable_poll = nullptr;
inline PINTERFACEIT_SWITCH_GET_ITEM p_switch_get_item = nullptr;
inline PINTERFACEIT_SWITCH_GET_STATE p_switch_get_state = nullptr;
inline PINTERFACEIT_GETAPIVERSION p_get_api_version = nullptr;
inline PINTERFACEIT_7SEGMENT_ENABLE p7_segment_enable = nullptr;
inline PINTERFACEIT_7SEGMENT_DISPLAY p7_segment_display = nullptr;
inline PINTERFACEIT_DATALINE_ENABLE p_dataline_enable = nullptr;
inline PINTERFACEIT_DATALINE_SET p_dataline_set = nullptr;
inline PINTERFACEIT_SERVO_ENABLE p_servo_enable = nullptr;
inline PINTERFACEIT_SERVO_SET_POSITION p_servo_set_position = nullptr;
inline PINTERFACEIT_SERVO_SET_CENTER p_servo_set_center = nullptr;
inline PINTERFACEIT_BRIGHTNESS_ENABLE p_brightness_enable = nullptr;
inline PINTERFACEIT_BRIGHTNESS_SET p_brightness_set = nullptr;
inline PINTERFACEIT_ANALOG_ENABLE p_analog_enable = nullptr;
inline PINTERFACEIT_ANALOG_GET_VALUE p_analog_get_value = nullptr;
inline PINTERFACEIT_ANALOG_GET_VALUES p_analog_get_values = nullptr;
inline PINTERFACEIT_LICENSE_GETMACHINEACTIVATIONID p_license_get_machine_activation_id = nullptr;
inline PINTERFACEIT_LICENSE_SETMACHINEACTIVATION p_license_set_machine_activation = nullptr;
inline PINTERFACEIT_LICENSE_ISACTIVATED p_license_is_activated;
inline PINTERFACEIT_SETBOARDOPTIONS p_set_options;
inline PINTERFACEIT_ENABLE_DEVICECHANGE_NOTIFICATION_CALLBACK p_enable_device_change_call_back = nullptr;
inline PINTERFACEIT_ENABLELOGGING p_enable_logging = nullptr;


/*
 * Helper functions
 */
inline int key_pressed(void)
{
    if (_kbhit())
    {
        _getch();
        return true;
    }
    return false;
}


inline bool load_pointers(const HMODULE h_interface_itapi)
{
    p_open_controllers = reinterpret_cast<PINTERFACEIT_OPENCONTROLLERS>(GetProcAddress(
        h_interface_itapi, "interfaceIT_OpenControllers"));
    p_get_device_list = reinterpret_cast<PINTERFACEIT_GETDEVICELIST>(GetProcAddress(
        h_interface_itapi, "interfaceIT_GetDeviceList"));
    p_get_controller_count = reinterpret_cast<PINTERFACEIT_GETCONTROLLERCOUNT>(GetProcAddress(
        h_interface_itapi, "interfaceIT_GetTotalControllers"));
    p_close_controllers = reinterpret_cast<PINTERFACEIT_CLOSECONTROLLERS>(GetProcAddress(
        h_interface_itapi, "interfaceIT_CloseControllers"));
    p_bind = reinterpret_cast<PINTERFACEIT_BIND>(GetProcAddress(h_interface_itapi, "interfaceIT_Bind"));
    p_un_bind = reinterpret_cast<PINTERFACEIT_UNBIND>(GetProcAddress(h_interface_itapi, "interfaceIT_UnBind"));
    p_get_board_info = reinterpret_cast<PINTERFACEIT_GETBOARDINFO>(GetProcAddress(
        h_interface_itapi, "interfaceIT_GetBoardInfo"));
    p_led_enable = reinterpret_cast<PINTERFACEIT_LED_ENABLE>(
        GetProcAddress(h_interface_itapi, "interfaceIT_LED_Enable"));
    p_led_test = reinterpret_cast<PINTERFACEIT_LED_TEST>(GetProcAddress(h_interface_itapi, "interfaceIT_LED_Test"));
    p_led_set = reinterpret_cast<PINTERFACEIT_LED_SET>(GetProcAddress(h_interface_itapi, "interfaceIT_LED_Set"));
    p_switch_enable_callback = reinterpret_cast<PINTERFACEIT_SWITCH_ENABLE_CALLBACK>(GetProcAddress(h_interface_itapi,
        "interfaceIT_Switch_Enable_Callback"));
    p_switch_enable_poll = reinterpret_cast<PINTERFACEIT_SWITCH_ENABLE_POLL>(GetProcAddress(
        h_interface_itapi, "interfaceIT_Switch_Enable_Poll"));
    p_switch_get_item = reinterpret_cast<PINTERFACEIT_SWITCH_GET_ITEM>(GetProcAddress(
        h_interface_itapi, "interfaceIT_Switch_Get_Item"));
    p_switch_get_state = reinterpret_cast<PINTERFACEIT_SWITCH_GET_STATE>(GetProcAddress(
        h_interface_itapi, "interfaceIT_Switch_Get_State"));
    p_get_api_version = reinterpret_cast<PINTERFACEIT_GETAPIVERSION>(GetProcAddress(
        h_interface_itapi, "interfaceIT_GetAPIVersion"));
    p7_segment_enable = reinterpret_cast<PINTERFACEIT_7SEGMENT_ENABLE>(GetProcAddress(
        h_interface_itapi, "interfaceIT_7Segment_Enable"));
    p7_segment_display = reinterpret_cast<PINTERFACEIT_7SEGMENT_DISPLAY>(GetProcAddress(
        h_interface_itapi, "interfaceIT_7Segment_Display"));
    p_dataline_enable = reinterpret_cast<PINTERFACEIT_DATALINE_ENABLE>(GetProcAddress(
        h_interface_itapi, "interfaceIT_Dataline_Enable"));
    p_dataline_set = reinterpret_cast<PINTERFACEIT_DATALINE_SET>(GetProcAddress(
        h_interface_itapi, "interfaceIT_Dataline_Set"));
    p_servo_enable = reinterpret_cast<PINTERFACEIT_SERVO_ENABLE>(GetProcAddress(
        h_interface_itapi, "interfaceIT_Servo_Enable"));
    p_servo_set_position = reinterpret_cast<PINTERFACEIT_SERVO_SET_POSITION>(GetProcAddress(
        h_interface_itapi, "interfaceIT_Servo_Set_Position"));
    p_servo_set_center = reinterpret_cast<PINTERFACEIT_SERVO_SET_CENTER>(GetProcAddress(
        h_interface_itapi, "interfaceIT_Servo_Set_Center"));
    p_brightness_enable = reinterpret_cast<PINTERFACEIT_BRIGHTNESS_ENABLE>(GetProcAddress(
        h_interface_itapi, "interfaceIT_Brightness_Enable"));
    p_brightness_set = reinterpret_cast<PINTERFACEIT_BRIGHTNESS_SET>(GetProcAddress(
        h_interface_itapi, "interfaceIT_Brightness_Set"));
    p_analog_enable = reinterpret_cast<PINTERFACEIT_ANALOG_ENABLE>(GetProcAddress(
        h_interface_itapi, "interfaceIT_Analog_Enable"));
    p_analog_get_value = reinterpret_cast<PINTERFACEIT_ANALOG_GET_VALUE>(GetProcAddress(
        h_interface_itapi, "interfaceIT_Analog_GetValue"));
    p_analog_get_values = reinterpret_cast<PINTERFACEIT_ANALOG_GET_VALUES>(GetProcAddress(
        h_interface_itapi, "interfaceIT_Analog_GetValues"));
    p_license_get_machine_activation_id = reinterpret_cast<PINTERFACEIT_LICENSE_GETMACHINEACTIVATIONID>(GetProcAddress(
        h_interface_itapi, "interfaceIT_License_GetMachineActivationID"));
    p_license_set_machine_activation = reinterpret_cast<PINTERFACEIT_LICENSE_SETMACHINEACTIVATION>(GetProcAddress(
        h_interface_itapi, "interfaceIT_License_SetMachineActivation"));
    p_license_is_activated = reinterpret_cast<PINTERFACEIT_LICENSE_ISACTIVATED>(GetProcAddress(
        h_interface_itapi, "interfaceIT_License_IsActivated"));
    p_set_options = reinterpret_cast<PINTERFACEIT_SETBOARDOPTIONS>(GetProcAddress(
        h_interface_itapi, "interfaceIT_SetBoardOptions"));
    p_enable_device_change_call_back = reinterpret_cast<PINTERFACEIT_ENABLE_DEVICECHANGE_NOTIFICATION_CALLBACK>(
        GetProcAddress(
            h_interface_itapi, "interfaceIT_Enable_DeviceChange_Notification_Callback"));
    p_enable_logging = reinterpret_cast<PINTERFACEIT_ENABLELOGGING>(GetProcAddress(
        h_interface_itapi, "interfaceIT_EnableLogging"));

    /*
     *	Check we have all the entry points
     */
    if (!p_open_controllers || !p_get_device_list || !p_close_controllers || !p_get_controller_count ||
        !p_bind || !p_un_bind || !p_get_board_info ||
        !p_led_enable || !p_led_test || !p_led_set ||
        !p_switch_enable_callback || !p_switch_enable_poll || !p_switch_get_item || !p_switch_get_state ||
        !p7_segment_enable || !p7_segment_display ||
        !p_dataline_enable || !p_dataline_set ||
        !p_servo_enable || !p_servo_set_position || !p_servo_set_center ||
        !p_brightness_enable || !p_brightness_set ||
        !p_analog_enable || !p_analog_get_value || !p_analog_get_values ||
        !p_license_get_machine_activation_id || !p_license_set_machine_activation || !p_license_is_activated ||
        !p_enable_device_change_call_back ||
        !p_set_options ||
        !p_enable_logging ||
        !p_get_api_version)
    {
        return false;
    }

    return true;
}


/*
 *	Callback to receive device change notifications
 */
inline BOOL CALLBACK device_change_proc(const int n_action)
{
    printf("\tAn interfaceIT device was %s\n",
           n_action == INTERFACEIT_DEVICE_ARRIVAL ? "added" : "removed");

    return TRUE;
}

inline BOOL CALLBACK key_pressed_proc(const DWORD h_session, const int n_switch, const int n_dir)
{
    //printf("\tSession %d, Switch %d is now (%d) %s\n", hSession, nSwitch, nDir, nDir == INTERFACEIT_SWITCH_DIR_DOWN ? "on / down" : "off / up");
    CallBack::switch_callback_invoker(h_session, n_switch, n_dir);
    return TRUE;
}