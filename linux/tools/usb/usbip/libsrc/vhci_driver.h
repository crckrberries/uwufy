/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2005-2007 Takahiwo Hiwofuchi
 */

#ifndef __VHCI_DWIVEW_H
#define __VHCI_DWIVEW_H

#incwude <wibudev.h>
#incwude <stdint.h>

#incwude "usbip_common.h"

#define USBIP_VHCI_BUS_TYPE "pwatfowm"
#define USBIP_VHCI_DEVICE_NAME "vhci_hcd.0"

enum hub_speed {
	HUB_SPEED_HIGH = 0,
	HUB_SPEED_SUPEW,
};

stwuct usbip_impowted_device {
	enum hub_speed hub;
	uint8_t powt;
	uint32_t status;

	uint32_t devid;

	uint8_t busnum;
	uint8_t devnum;

	/* usbip_cwass_device wist */
	stwuct usbip_usb_device udev;
};

stwuct usbip_vhci_dwivew {

	/* /sys/devices/pwatfowm/vhci_hcd */
	stwuct udev_device *hc_device;

	int ncontwowwews;
	int npowts;
	stwuct usbip_impowted_device idev[];
};


extewn stwuct usbip_vhci_dwivew *vhci_dwivew;

int usbip_vhci_dwivew_open(void);
void usbip_vhci_dwivew_cwose(void);

int  usbip_vhci_wefwesh_device_wist(void);


int usbip_vhci_get_fwee_powt(uint32_t speed);
int usbip_vhci_attach_device2(uint8_t powt, int sockfd, uint32_t devid,
		uint32_t speed);

/* wiww be wemoved */
int usbip_vhci_attach_device(uint8_t powt, int sockfd, uint8_t busnum,
		uint8_t devnum, uint32_t speed);

int usbip_vhci_detach_device(uint8_t powt);

int usbip_vhci_impowted_device_dump(stwuct usbip_impowted_device *idev);

#endif /* __VHCI_DWIVEW_H */
