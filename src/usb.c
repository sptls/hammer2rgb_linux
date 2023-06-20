#include "usb.h"
#include <stdio.h>

int InitUsb()
{
    return libusb_init(NULL);
};

int GetKeyboardHandle()
{
    libusb_device **list;
    ssize_t cnt = libusb_get_device_list(NULL, &list);
    int err = 0, keyboard_found = 0;
    
    for (ssize_t i = 0; i < cnt; i++) 
    {
        libusb_device *device = list[i];
        struct libusb_device_descriptor desc;


        libusb_get_device_descriptor(device, &desc);
        if(desc.idVendor == 0x258A && desc.idProduct == 0x0016)
        {
            keyboard_found = VC_TRUE;
            err = libusb_open(device, &kb_handle);
            if(err)
            {
                if(err == LIBUSB_ERROR_ACCESS)
                {
                    printf("No acces to usb device!\nFix by runing \"sudo hammer2kb --add-usb-rule\"\n");
                    return 1;
                }
                printf("failed to open device! Error code: %i\n", err);
                return 1;
            }

            err = libusb_set_auto_detach_kernel_driver(kb_handle, 1);
            if(err != LIBUSB_SUCCESS)
            {
                printf("Failed to detach kernel driver! %i\n", err);
                return 1;
            }

            err = libusb_claim_interface(kb_handle, VC_KB_INTERFACE_NR);
            if(err)
            {
                printf("Failed to claim device interface! %i\n", err);
                return 1;
            }

            libusb_free_device_list(list, 1);
            break;
        }
    }

    if(keyboard_found != VC_TRUE)
    {
        printf("Modecom Volcano Hammer 2 RGB keyboard not found!\n");
    }

    return 0;

};

int FinishUsb()
{
    libusb_release_interface(kb_handle, VC_KB_INTERFACE_NR);
    libusb_close(kb_handle);
    libusb_exit(NULL);
};

int SendPacket(unsigned char *packet)
{
    int err = libusb_control_transfer(kb_handle, 
                VC_USB_REQUEST_TYPE, 
                VC_USB_REQUEST, 
                VC_USB_WVALUE, 
                VC_USB_WINDEX, 
                packet, 
                VC_USB_PACKET_SIZE,
                VC_USB_TIMEOUT_MS
                );
    return err;
};

int ChangeEffect(kb_settings *kbs)
{
    kb_effect_packet[VC_PACKET_EFFECT_INDEX] = kbs->effect;
    kb_effect_packet[VC_PACKET_APPLY_EFFECT_INDEX] = VC_PACKET_APPLY_EFFECT;
    kb_effect_packet[VC_PACKET_RANDOM_COLOR_INDEX + kbs->rc_offset] = kbs->random_color;

    return SendPacket(kb_effect_packet);
};

int ChangeColor(kb_settings *kbs)
{
    /**
     * Some effects require to send "empty" effect first in order to
     * change color
    */
    kb_settings kbs_tmp = {0};
    ChangeEffect(&kbs_tmp);

    if(kbs->random_color == 0)
    {
        kb_color_packet[VC_PACKET_RED_INDEX + kbs->color_offset] = kbs->colorRED;
        kb_color_packet[VC_PACKET_GREEN_INDEX + kbs->color_offset] = kbs->colorGREEN;
        kb_color_packet[VC_PACKET_BLUE_INDEX + kbs->color_offset] = kbs->colorBLUE;
    }

    return SendPacket(kb_color_packet);
};

int AddUsbUdevRule()
{
    const char usb_rule_path[] = "/usr/lib/udev/rules.d/70-hammer2-kb.rules";
    FILE *f;
    f = fopen(usb_rule_path, "w");
    if(f == NULL)
    {
        printf("Failed to open file \"%s\" error code: %i\n", usb_rule_path, errno);
        if(errno == EACCES)
        {
            printf("File can't be accesed. Permission denied. Try sudo\n");
        }
        return 1;
    }

    const char usb_rule_string[] = "SUBSYSTEM==\"usb\", ATTRS{idProduct}==\"0016\", ATTRS{idVendor}==\"258a\", MODE=\"0660\", TAG+=\"uaccess\"\n\0";
    fprintf(f, usb_rule_string);

    fclose(f);

    printf("Rule set in \"%s\"\nNow reboot you machine or reload UDEV rules with \"sudo udevadm trigger\"\n", usb_rule_path);

    return 0;
};