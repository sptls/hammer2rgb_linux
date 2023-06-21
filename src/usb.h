#ifndef VOLCANO_USB_H_
#define VOLCANO_USB_H_

#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <errno.h>

#include "packets.h"
#include "settings.h"
#include "constants.h"

static libusb_device_handle *kb_handle = NULL;

int InitUsb();
int GetKeyboardHandle();
int FinishUsb();
int SendPacket(unsigned char *packet);
int ChangeEffect(kb_settings *kbs);
int ChangeColor(kb_settings *kbs);
int AddUsbUdevRule();

#endif