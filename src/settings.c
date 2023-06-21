#include "settings.h"

int GetSettings(char *arg, kb_settings *kbs)
{
    if(strlen(arg) > VC_MAX_EFFECT_NAME_LEN)
    {
        return VC_ERR_INVALID_OPTION;
    }

    /**
     * Make copy of passed arg and set all
     * characters to lowercase
    */
    char tmp_argv[VC_MAX_EFFECT_NAME_LEN] = {0};
    strcpy(tmp_argv, arg);

    for(int i = 0; i < strlen(tmp_argv); i++)
        tmp_argv[i] = tolower(tmp_argv[i]);

    if(strcmp(tmp_argv, "--help") == 0)
    {
        ShowUsage();
        return VC_SHOW_INFO;
    }
    if(strcmp(tmp_argv, "--options") == 0)
    {
        ShowOptions();
        return VC_SHOW_INFO;
    }
    if(strcmp(tmp_argv, "--version") == 0)
    {
        printf("%s\n", HAMMER2RGB_VERSION);
        return VC_SHOW_INFO;
    }

    /**
     * Speed and brightness value are stored in
     * single byte. Speed have 4 steps and
     * brightnes 3.
     * 
     * This byte looks like this 0xSB.
     * Where "S" is speed and "B" is
     * brightness.
     * 
     * So when we send 0x21 to keyboard it will
     * set speed to "2" and brightness to "1".
     * 
     * Speed ranges between 0 and 3, brightness
     * between 0 and 2. We decrement passed arg
     * by -1 so user can type "b1" instead of "b0".
     * 
     * Passing 0x00 will NOT turn of keyboard 
     * backlight or stop effect. It's just lowest
     * setting of speed and brightness
    */
    if(strlen(tmp_argv) == 2)
    {
        if(tmp_argv[0] == 's')
        {
            if(kbs->change_speed == VC_TRUE)
            {
                return VC_ERR_MULTI_OPTIONS;
            }
            if(tmp_argv[1] > '0' && tmp_argv[1] < '5')
            {
                kbs->sb_byte += 0x10 * (tmp_argv[1] - '1');
                kbs->change_speed = VC_TRUE;
                return VC_OK;
            }
            else
            {
                return VC_ERR_SPEED_VALUE;
            }
        }
        else if(tmp_argv[0] == 'b')
        {
            if(kbs->change_brightness == VC_TRUE)
            {
                return VC_ERR_MULTI_OPTIONS;
            }
            if(tmp_argv[1] > '0' && tmp_argv[1] < '4')
            {
                kbs->sb_byte += (tmp_argv[1] - '1');
                kbs->change_brightness = VC_TRUE;
                return VC_OK;
            }
            else
            {
                return VC_ERR_BRIGHTNES_VALUE;
            }
        }
    }

    if(strcmp(tmp_argv, "off") == 0)
    {
        kbs->colorRED = 0x00;
        kbs->colorGREEN = 0x00;
        kbs->colorBLUE = 0x00;
        kbs->effect = 0x00; 
        kbs->change_effect = VC_TRUE;
        kbs->change_color = VC_TRUE;
        return VC_OK;
    }

    /**
     * Get custom color values
    */
    if(strlen(tmp_argv) == VC_RGB_SETTING_LEN)
    {
        return GetRGB(tmp_argv, kbs);
    }
    
    if(strcmp(tmp_argv, "--add-usb-rule") == 0)
    {
        kbs->add_usb_rule = VC_TRUE;
        return VC_OK;
    }

    for(int i = 0; i < VC_NR_OF_EFFECTS; i++)
    {
        if(strcmp(tmp_argv, effect_name[i]) == 0)
        {
            if(kbs->change_effect == VC_TRUE)
            {
                return VC_ERR_MULTI_OPTIONS;
            }

            kbs->effect=effect_values[i];
            kbs->color_offset=effect_color_offset[i];
            kbs->rc_offset=random_color_offset[i];
            kbs->sb_byte_offset=speed_and_brightness_offset[i];
            kbs->change_effect = VC_TRUE;
            return VC_OK;
        }
    }
    for(int i = 0; i < VC_NR_OF_COLOR_PRESETS; i++)
    {
        if(strcmp(tmp_argv, color_name[i]) == 0)
        {
            if(kbs->change_color == VC_TRUE)
            {
                return VC_ERR_MULTI_OPTIONS;
            }

            kbs->change_color = VC_TRUE;
            if(strcmp(tmp_argv, "random_color") == 0)
            {
                kbs->random_color = VC_RANDOM_COLOR_VALUE;
                return VC_OK;
            }
            kbs->colorRED   = color_values[i][0];
            kbs->colorGREEN = color_values[i][1];
            kbs->colorBLUE  = color_values[i][2];

            return VC_OK;
        }
    }

    return VC_ERR_INVALID_OPTION;
};

void ShowUsage()
{
    printf("Usage: hammer2kb [EFFECT] [COLOR] off bN sN --help --options --add-usb-rule --version\n");
    printf("Version: %s\n\n", HAMMER2RGB_VERSION);
    printf("This program changes effects and colors of Volcano Modecom HAMMER 2 RGB mechanical keyboard\n");
    printf("Changing color, brightness or speed alwas need to have effect defined.\n");
    printf("Options are case insensitive and don't have to be in order\n");
    printf("\t[EFFECT]\t- selected effect\n");
    printf("\t[COLOR}\t\t- sets color in format of \"RRGGBB\" or as preset, eg. \"red\"\n\n");
    printf("\toff\t\t- turns off keyboard backlight\n");
    printf("\tbN\t\t- sets brightnes where N is value between 1-3\n");
    printf("\tsN\t\t- sets speed where N is value between 1-4\n");
    printf("\t--help\t\t- show this message\n");
    printf("\t--options\t- show available keyboard effects and color presets\n");
    printf("\t--add-usb-rule\t- adds UDEV rule to access keybaord USB without root permission\n");
    printf("\t--version\t\t- print version\n");
};

int GetRGB(char *color, kb_settings *kbs)
{
    if(kbs->change_color)
    {
        return VC_ERR_MULTI_OPTIONS;
    }

    /**
     * Check if passed color have correct value
    */
    for(int i = 0; i < VC_RGB_SETTING_LEN; i++)
    {
        if( (color[i] < '0' || color[i] > '9') &&
            (color[i] < 'a' || color[i] > 'f') )
        {
            return VC_ERR_INVALID_COLOR_VALUE;
        }
    }

    char *ptr_color = color;
    char tmp_color[2] = { 0 };
    unsigned char *ptr_kb_color = &(kbs->colorRED);
    for(; ptr_kb_color != &(kbs->random_color); ptr_color+=2, ptr_kb_color++)
    {
        strncpy(tmp_color, ptr_color, 2);
        *ptr_kb_color = (unsigned char)strtol(tmp_color, NULL, 16);
    }

    kbs->change_color = VC_TRUE;
    return VC_OK;
};

void ShowOptions()
{
    printf("\nList of keyboard effects:\n");
    for(int i = 0; i < VC_NR_OF_EFFECTS; i++)
    {
        printf("\t%s\n", effect_name[i]);
    }

    printf("\nList of color presets:\n");
    for(int i = 0; i < VC_NR_OF_COLOR_PRESETS; i++)
    {
        printf("\t%s\n", color_name[i]);
    }

    printf("\nExamples:\n");
    printf("  Set effect to \"sine_wave\", color to magenta, brightness to 2 and speed to 4\n");
    printf("\t\"$ hammer2kb sine_wave magenta b2 s4\"\n");
    printf("  Set effect to \"fixed_on\" and color to hex value FF00FF\n");
    printf("\t\"$ hammer2kb fixed_on ff00ff\"\n");
    printf("  Turn off keyboard backlight\n");
    printf("\t\"$ hammer2kb off\"\n");
}