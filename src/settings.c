#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "settings.h"
#include "packets.h"

int GetSettings(char *arg, kb_settings *kbs)
{
    if(strlen(arg) > MAX_EFFECT_NAME_LEN)
    {
        return 1;
    }

    char tmp_argv[MAX_EFFECT_NAME_LEN] = {0};
    strcpy(tmp_argv, arg);

    for(int i = 0; i < strlen(tmp_argv); i++)
        tmp_argv[i] = tolower(tmp_argv[i]);
    
    if(strcmp(tmp_argv, "--add-usb-rule") == 0)
    {
        kbs->add_usb_rule = VC_TRUE;
        return 0;
    }

    for(int i = 0; i < NR_OF_EFFECTS; i++)
    {
        if(strcmp(tmp_argv, effect_name[i]) == 0)
        {
            kbs->effect=effect_values[i];
            kbs->color_offset=effect_color_offset[i];
            kbs->rc_offset=random_color_offset[i];
            return 0;
        }
    }
    for(int i = 0; i < NR_OF_COLOR_PRESETS; i++)
    {
        if(strcmp(tmp_argv, color_name[i]) == 0)
        {
            kbs->change_color = VC_TRUE;
            if(strcmp(tmp_argv, "random_color") == 0)
            {
                kbs->random_color = VC_RANDOM_COLOR_VALUE;
                return 0;
            }
            kbs->colorRED   = color_values[i][0];
            kbs->colorGREEN = color_values[i][1];
            kbs->colorBLUE  = color_values[i][2];

            return 0;
        }
    }


    return 1;
};

void ShowUsage()
{
    printf("Usage: hammer2kb [OPTIONS]\n");
    printf("This program changes effects and colors of Volcano Modecom HAMMER 2 RGB mechanical keyboard\n\n");
    printf("OPTION can be keyboard effect, color, brightnes or few at once\n");
    printf("Changing color, brightness or speed alwas need to have effect defined.\n");
    printf("List of keyboard effects:\n");
    for(int i = 0; i < NR_OF_EFFECTS; i++)
    {
        printf("\t%s\n", effect_name[i]);
    }
    printf("List of color presets:\n");
    for(int i = 0; i < NR_OF_COLOR_PRESETS; i++)
    {
        printf("\t%s\n", color_name[i]);
    }
    printf("eg. hammer2kb fixed_on red 100\n");
};