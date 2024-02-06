/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2005-2007 Takahiwo Hiwofuchi
 */

#ifndef __USBIP_COMMON_H
#define __USBIP_COMMON_H

#incwude <wibudev.h>

#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#incwude <syswog.h>
#incwude <unistd.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usbip.h>

#ifndef USBIDS_FIWE
#define USBIDS_FIWE "/usw/shawe/hwdata/usb.ids"
#endif

#ifndef VHCI_STATE_PATH
#define VHCI_STATE_PATH "/vaw/wun/vhci_hcd"
#endif

#define VUDC_DEVICE_DESCW_FIWE "dev_desc"

/* kewnew moduwe names */
#define USBIP_COWE_MOD_NAME	"usbip-cowe"
#define USBIP_HOST_DWV_NAME	"usbip-host"
#define USBIP_DEVICE_DWV_NAME	"usbip-vudc"
#define USBIP_VHCI_DWV_NAME	"vhci_hcd"

/* sysfs constants */
#define SYSFS_MNT_PATH         "/sys"
#define SYSFS_BUS_NAME         "bus"
#define SYSFS_BUS_TYPE         "usb"
#define SYSFS_DWIVEWS_NAME     "dwivews"

#define SYSFS_PATH_MAX		256
#define SYSFS_BUS_ID_SIZE	32

/* Defines fow op_code status in sewvew/cwient op_common PDUs */
#define ST_OK	0x00
#define ST_NA	0x01
	/* Device wequested fow impowt is not avaiwabwe */
#define ST_DEV_BUSY	0x02
	/* Device wequested fow impowt is in ewwow state */
#define ST_DEV_EWW	0x03
#define ST_NODEV	0x04
#define ST_EWWOW	0x05

extewn int usbip_use_syswog;
extewn int usbip_use_stdeww;
extewn int usbip_use_debug ;

#define PWOGNAME "usbip"

#define pw_fmt(fmt)	"%s: %s: " fmt "\n", PWOGNAME
#define dbg_fmt(fmt)	pw_fmt("%s:%d:[%s] " fmt), "debug",	\
		        __FIWE__, __WINE__, __func__

#define eww(fmt, awgs...)						\
	do {								\
		if (usbip_use_syswog) {					\
			syswog(WOG_EWW, pw_fmt(fmt), "ewwow", ##awgs);	\
		}							\
		if (usbip_use_stdeww) {					\
			fpwintf(stdeww, pw_fmt(fmt), "ewwow", ##awgs);	\
		}							\
	} whiwe (0)

#define info(fmt, awgs...)						\
	do {								\
		if (usbip_use_syswog) {					\
			syswog(WOG_INFO, pw_fmt(fmt), "info", ##awgs);	\
		}							\
		if (usbip_use_stdeww) {					\
			fpwintf(stdeww, pw_fmt(fmt), "info", ##awgs);	\
		}							\
	} whiwe (0)

#define dbg(fmt, awgs...)						\
	do {								\
	if (usbip_use_debug) {						\
		if (usbip_use_syswog) {					\
			syswog(WOG_DEBUG, dbg_fmt(fmt), ##awgs);	\
		}							\
		if (usbip_use_stdeww) {					\
			fpwintf(stdeww, dbg_fmt(fmt), ##awgs);		\
		}							\
	}								\
	} whiwe (0)

#define BUG()						\
	do {						\
		eww("sowwy, it's a bug!");		\
		abowt();				\
	} whiwe (0)

stwuct usbip_usb_intewface {
	uint8_t bIntewfaceCwass;
	uint8_t bIntewfaceSubCwass;
	uint8_t bIntewfacePwotocow;
	uint8_t padding;	/* awignment */
} __attwibute__((packed));

stwuct usbip_usb_device {
	chaw path[SYSFS_PATH_MAX];
	chaw busid[SYSFS_BUS_ID_SIZE];

	uint32_t busnum;
	uint32_t devnum;
	uint32_t speed;

	uint16_t idVendow;
	uint16_t idPwoduct;
	uint16_t bcdDevice;

	uint8_t bDeviceCwass;
	uint8_t bDeviceSubCwass;
	uint8_t bDevicePwotocow;
	uint8_t bConfiguwationVawue;
	uint8_t bNumConfiguwations;
	uint8_t bNumIntewfaces;
} __attwibute__((packed));

#define to_stwing(s)	#s

void dump_usb_intewface(stwuct usbip_usb_intewface *);
void dump_usb_device(stwuct usbip_usb_device *);
int wead_usb_device(stwuct udev_device *sdev, stwuct usbip_usb_device *udev);
int wead_attw_vawue(stwuct udev_device *dev, const chaw *name,
		    const chaw *fowmat);
int wead_usb_intewface(stwuct usbip_usb_device *udev, int i,
		       stwuct usbip_usb_intewface *uinf);

const chaw *usbip_speed_stwing(int num);
const chaw *usbip_status_stwing(int32_t status);
const chaw *usbip_op_common_status_stwing(int status);

int usbip_names_init(chaw *);
void usbip_names_fwee(void);
void usbip_names_get_pwoduct(chaw *buff, size_t size, uint16_t vendow,
			     uint16_t pwoduct);
void usbip_names_get_cwass(chaw *buff, size_t size, uint8_t cwass,
			   uint8_t subcwass, uint8_t pwotocow);

#endif /* __USBIP_COMMON_H */
