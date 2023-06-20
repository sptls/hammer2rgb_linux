#ifndef VOLCANO_USB_H_
#define VOLCANO_USB_H_

#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <errno.h>
#include "packets.h"
#include "settings.h"

#define VC_KB_INTERFACE_NR 1
#define VC_USB_REQUEST_TYPE 0x21
#define VC_USB_REQUEST 0x09
#define VC_USB_WVALUE 0x0306
#define VC_USB_WINDEX 0x01
#define VC_USB_PACKET_SIZE 1032
#define VC_USB_TIMEOUT_MS 1000

static libusb_device_handle *kb_handle = NULL;

int InitUsb();
int GetKeyboardHandle();
int FinishUsb();
int SendPacket(unsigned char *packet);
int ChangeEffect(kb_settings *kbs);
int ChangeColor(kb_settings *kbs);
int AddUsbUdevRule();

#endif