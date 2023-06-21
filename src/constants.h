#ifndef VC_MODECOM_CONSTANTS_H_
#define VC_MODECOM_CONSTANTS_H_

/**
 * USB packets
*/
#define VC_USB_PACKET_SIZE              1032
#define VC_PACKET_EFFECT_INDEX          21
#define VC_PACKET_APPLY_EFFECT_INDEX    22
#define VC_PACKET_APPLY_EFFECT          0x21
#define VC_PACKET_RED_INDEX             2
#define VC_PACKET_GREEN_INDEX           1
#define VC_PACKET_BLUE_INDEX            0
#define VC_RANDOM_COLOR_VALUE           0x07

/**
 * USB settings
*/
#define VC_KB_INTERFACE_NR              1
#define VC_USB_REQUEST_TYPE             0x21
#define VC_USB_REQUEST                  0x09
#define VC_USB_WVALUE                   0x0306
#define VC_USB_WINDEX                   0x01
#define VC_USB_PACKET_SIZE              1032
#define VC_USB_TIMEOUT_MS               1000

/**
 * Effects
*/
#define VC_NR_OF_EFFECTS                13
#define VC_NR_OF_COLOR_PRESETS          8
#define VC_MAX_EFFECT_NAME_LEN          30
#define VC_RGB_SETTING_LEN              6

/**
 * Error codes, etc.
*/
#define VC_OK                           0
#define VC_SHOW_INFO                    200
#define VC_UDEV_RULE_ADDED              150
#define VC_TRUE                         1
#define VC_ERR_MULTI_OPTIONS            2
#define VC_ERR_INVALID_OPTION           3
#define VC_ERR_INVALID_COLOR_VALUE      4
#define VC_ERR_PERMISION                5
#define VC_ERR_KB_NOT_FOUND             6
#define VC_ERR_BRIGHTNES_VALUE          7
#define VC_ERR_SPEED_VALUE              8
#define VC_ERR_USB                      100


#endif