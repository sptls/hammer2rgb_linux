#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "usb.h"
#include "settings.h"

int main(int argc, char **argv)
{

    kb_settings kbs = {0};
    if(argc == 1)
    {
        ShowUsage();
        return 0;
    }

    for(int i = 1; i < argc; i++)
    {
        if(GetSettings(argv[i], &kbs))
        {
            printf("Setting \"%s\" is not valid\n", argv[i]);
            ShowUsage();
            return 1;
        }
    }

    if(kbs.add_usb_rule)
    {
        AddUsbUdevRule();
        return 0;
    }

    if(InitUsb())
    {
        printf("Failed to init libusb\n");
        return 1;
    }

    if(GetKeyboardHandle())
    {
        printf("Failed to get keyboard handle\n");
        return 1;
    }

    if(kbs.change_color)
    {
        if(kbs.effect == 0)
        {
            printf("No effect selected, aborting\n");
            return 1;
        }
        ChangeColor(&kbs);
    }

    if(kbs.effect)
    {
        ChangeEffect(&kbs);
    }

    FinishUsb();
    return 0;
}
