#ifndef VOLCANO_RGB_SETTINGS
#define VOLCANO_RGB_SETTINGS

#define NR_OF_EFFECTS 13
#define MAX_EFFECT_NAME_LEN 30
#define NR_OF_COLOR_PRESETS 8

#define VC_TRUE 1

typedef struct kb_settings_
{
    unsigned char effect;
    unsigned char colorRED;
    unsigned char colorGREEN;
    unsigned char colorBLUE;
    unsigned char random_color;
    unsigned char change_color;
    unsigned char brightnes;
    unsigned char speed;
    int           add_usb_rule;
    int           color_offset;
    int           rc_offset;
} kb_settings;

static const char effect_name[NR_OF_EFFECTS][MAX_EFFECT_NAME_LEN] = {
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
static const int effect_values[NR_OF_EFFECTS] = {
    0x01, //snake, brightness, speed, color, random color
    0x02, //neon stream, speed, 
    0x03, //reaction, brightness, speed, color, random color
    0x04, //sine_wave, b, s, c, rc
    0x05, //fixed_od, b, c, rc
    0x06, //respire, s, c, rc
    0x07, //rainbow, s
    0x08, //flash_away, b, s, c, rc
    0x09, //raindrops, b, s, c, rc
    0x0A, //rainbow_wheel, s
    0x0B, //ripples_shining, b, s, c, rc
    0x0C, //stars_twinkle, b, s
    0x0D  //shadow_disappear, b, s, c, rc
};

/**
 * some effect have special color properties
*/
static const int effect_color_offset[] = {
    29,
    0,
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

static const char color_name[NR_OF_COLOR_PRESETS][MAX_EFFECT_NAME_LEN] = {
    "red",
    "green",
    "blue",
    "yellow",
    "purple",
    "magenta",
    "cyan",
    "random_color"
};

static const unsigned char color_values[NR_OF_COLOR_PRESETS][3] = {
    { 0xFF, 0x00, 0x00 },
    { 0x00, 0xFF, 0x00 },
    { 0x00, 0x00, 0xFF },
    { 0xFF, 0xFF, 0x00 },
    { 0x80, 0x00, 0x80 },
    { 0xFF, 0x00, 0xFF },
    { 0x00, 0xFF, 0xFF },
    { 0x00, 0x00, 0x00 } // random_color, not used
};

static const int random_color_offset[NR_OF_EFFECTS] = {
    0,
    0,
    4,
    6,
    8,
    10,
    12,
    14,
    16,
    18,
    20,
    22,
    24,
};


void ShowUsage();
int GetSettings(char *arg, kb_settings *kbs);

#endif