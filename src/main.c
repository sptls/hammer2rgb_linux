#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "usb.h"
#include "settings.h"
#include "constants.h"

int main(int argc, char **argv)
{

    kb_settings kbs = {0};
    if(argc == 1)
    {
        printf("hammer2rgb: missing argumets\n");
        printf("try \"hammer2rgb --help\"\n");
        return VC_SHOW_INFO;
    }

    for(int i = 1; i < argc; i++)
    {
        int err = GetSettings(argv[i], &kbs);
        switch(err)
        {
            case VC_OK:
                break;
            case VC_SHOW_INFO:
                return VC_OK;

            case VC_ERR_MULTI_OPTIONS:
                printf("Cannot set same option multiple times\n");
                return VC_ERR_MULTI_OPTIONS;
                
            case VC_ERR_INVALID_OPTION:
                printf("Setting \"%s\" is not valid\n", argv[i]);
                ShowUsage();
                return VC_ERR_INVALID_OPTION;
                
            case VC_ERR_INVALID_COLOR_VALUE:
                printf("Color %s is not valid\n", argv[i]);
                return VC_ERR_INVALID_COLOR_VALUE;
                
            case VC_ERR_BRIGHTNES_VALUE:
                printf("Brightness value %s in not correct\n", argv[i]);
                printf("It should be \"b[1-3]\"\neg. \"hammer2rgb fixed_on red b2\"\n");
                return VC_ERR_BRIGHTNES_VALUE;
                
            case VC_ERR_SPEED_VALUE:
                printf("Speed value %s in not correct\n", argv[i]);
                printf("It should be \"b[1-4]\"\neg. \"hammer2rgb fixed_on red s3\"\n");
                return VC_ERR_SPEED_VALUE;
        }
    }

    if(kbs.add_usb_rule)
    {
        return AddUsbUdevRule();
    }

    if(InitUsb())
    {
        printf("Failed to init libusb\n");
        return VC_ERR_USB;
    }

    if(GetKeyboardHandle())
    {
        printf("Failed to get keyboard handle\n");
        return VC_ERR_USB;
    }

    if(kbs.change_color)
    {
        if(kbs.effect == 0 && kbs.change_effect != VC_TRUE)
        {
            printf("No effect selected, aborting\n");
            return VC_ERR_INVALID_OPTION;
        }
        ChangeColor(&kbs);
    }

    if(kbs.change_effect)
    {
        ChangeEffect(&kbs);
    }

    FinishUsb();
    return VC_OK;
}

