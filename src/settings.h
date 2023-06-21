#ifndef VOLCANO_RGB_SETTINGS
#define VOLCANO_RGB_SETTINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

#include "constants.h"
#include "packets.h"

/**
 * This struct contains settings and color values
 * that are later put into packet that will be
 * send to keyboard
*/
typedef struct kb_settings_
{
    /**
     * Effects
    */
    unsigned char effect;
    unsigned char change_effect;
    /**
     * Colors
    */
    unsigned char colorRED;
    unsigned char colorGREEN;
    unsigned char colorBLUE;
    unsigned char random_color;
    unsigned char change_color;
    int           color_offset;
    int           rc_offset;
    /**
     * Speed and brightnes are defined
     * in the same byte
    */
    unsigned char sb_byte;
    int           sb_byte_offset;
    unsigned char change_brightness;
    unsigned char change_speed;
    /**
     * Other
    */
    int           add_usb_rule;
    
} kb_settings;

/**
 * Prints usage
*/
void ShowUsage();

/**
 * This functions parses settings passed to program
 * @param arg char* to string with setting
 * @param kbs pointer to kb_settings struct that will recive settings
 * @return VC_OK on succes, other values on error
*/
int GetSettings(char *arg, kb_settings *kbs);

/**
 * This function sets rgb value in keybaord settings
 * @param color char* string describing color in format of RRGGBB
 * @param kbs kb_settings pointer to recive color
 * @return VC_OK on succes, other values on error
*/
int GetRGB(char *color, kb_settings *kbs);

void ShowOptions();

static const char effect_name[VC_NR_OF_EFFECTS][VC_MAX_EFFECT_NAME_LEN] = {
    "snake",
    "neon_stream",
    "reaction",
    "sine_wave",
    "fixed_on",
    "respire",
    "rainbow",
    "flash_away",
    "raindrops",
    "rainbow_wheel",
    "ripples_shining",
    "stars_twinkle",
    "shadow_disappear"
};

//"game_mode" effect not supported for now
static const int effect_values[VC_NR_OF_EFFECTS] = {
    0x01, //snake
    0x02, //neon_stream
    0x03, //reaction
    0x04, //sine_wave
    0x05, //fixed_on
    0x06, //respire
    0x07, //rainbow
    0x08, //flash_away
    0x09, //raindrops
    0x0A, //rainbow_wheel
    0x0B, //ripples_shining
    0x0C, //stars_twinkle
    0x0D  //shadow_disappear
};

/**
 * some effect have special color properties
*/
static const int effect_color_offset[VC_NR_OF_EFFECTS] = {
    29,
    50, //neon_stream seems to ingore color change through software
    71,
    92,
    113,
    134,
    0,
    176,
    197,
    0,
    239,
    0,
    281,
};

static const char color_name[VC_NR_OF_COLOR_PRESETS][VC_MAX_EFFECT_NAME_LEN] = {
    "red",
    "green",
    "blue",
    "yellow",
    "purple",
    "magenta",
    "cyan",
    "random_color"
};

static const unsigned char color_values[VC_NR_OF_COLOR_PRESETS][3] = {
    { 0xFF, 0x00, 0x00 },
    { 0x00, 0xFF, 0x00 },
    { 0x00, 0x00, 0xFF },
    { 0xFF, 0xFF, 0x00 },
    { 0x80, 0x00, 0x80 },
    { 0xFF, 0x00, 0xFF },
    { 0x00, 0xFF, 0xFF },
    { 0x00, 0x00, 0x00 } // random_color, not used
};

static const int random_color_offset[VC_NR_OF_EFFECTS] = {
    34,
    36,
    38,
    40,
    42,
    44,
    46,
    48,
    50,
    52,
    54,
    56,
    58,
};

static const int speed_and_brightness_offset[VC_NR_OF_EFFECTS] = {
    35,
    37,
    39,
    41,
    43,
    45,
    47,
    49,
    51,
    53,
    55,
    57,
    59,
};

#endif