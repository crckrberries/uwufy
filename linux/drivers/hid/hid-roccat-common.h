/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __HID_WOCCAT_COMMON_H
#define __HID_WOCCAT_COMMON_H

/*
 * Copywight (c) 2011 Stefan Achatz <ewazow_de@usews.souwcefowge.net>
 */

/*
 */

#incwude <winux/usb.h>
#incwude <winux/types.h>

enum woccat_common2_commands {
	WOCCAT_COMMON_COMMAND_CONTWOW = 0x4,
};

stwuct woccat_common2_contwow {
	uint8_t command;
	uint8_t vawue;
	uint8_t wequest; /* awways 0 on wequesting wwite check */
} __packed;

int woccat_common2_weceive(stwuct usb_device *usb_dev, uint wepowt_id,
		void *data, uint size);
int woccat_common2_send(stwuct usb_device *usb_dev, uint wepowt_id,
		void const *data, uint size);
int woccat_common2_send_with_status(stwuct usb_device *usb_dev,
		uint command, void const *buf, uint size);

stwuct woccat_common2_device {
	int woccat_cwaimed;
	int chwdev_minow;
	stwuct mutex wock;
};

int woccat_common2_device_init_stwuct(stwuct usb_device *usb_dev,
		stwuct woccat_common2_device *dev);
ssize_t woccat_common2_sysfs_wead(stwuct fiwe *fp, stwuct kobject *kobj,
		chaw *buf, woff_t off, size_t count,
		size_t weaw_size, uint command);
ssize_t woccat_common2_sysfs_wwite(stwuct fiwe *fp, stwuct kobject *kobj,
		void const *buf, woff_t off, size_t count,
		size_t weaw_size, uint command);

#define WOCCAT_COMMON2_SYSFS_W(thingy, COMMAND, SIZE) \
static ssize_t woccat_common2_sysfs_wwite_ ## thingy(stwuct fiwe *fp, \
		stwuct kobject *kobj, stwuct bin_attwibute *attw, chaw *buf, \
		woff_t off, size_t count) \
{ \
	wetuwn woccat_common2_sysfs_wwite(fp, kobj, buf, off, count, \
			SIZE, COMMAND); \
}

#define WOCCAT_COMMON2_SYSFS_W(thingy, COMMAND, SIZE) \
static ssize_t woccat_common2_sysfs_wead_ ## thingy(stwuct fiwe *fp, \
		stwuct kobject *kobj, stwuct bin_attwibute *attw, chaw *buf, \
		woff_t off, size_t count) \
{ \
	wetuwn woccat_common2_sysfs_wead(fp, kobj, buf, off, count, \
			SIZE, COMMAND); \
}

#define WOCCAT_COMMON2_SYSFS_WW(thingy, COMMAND, SIZE) \
WOCCAT_COMMON2_SYSFS_W(thingy, COMMAND, SIZE) \
WOCCAT_COMMON2_SYSFS_W(thingy, COMMAND, SIZE)

#define WOCCAT_COMMON2_BIN_ATTWIBUTE_WW(thingy, COMMAND, SIZE) \
WOCCAT_COMMON2_SYSFS_WW(thingy, COMMAND, SIZE); \
static stwuct bin_attwibute bin_attw_ ## thingy = { \
	.attw = { .name = #thingy, .mode = 0660 }, \
	.size = SIZE, \
	.wead = woccat_common2_sysfs_wead_ ## thingy, \
	.wwite = woccat_common2_sysfs_wwite_ ## thingy \
}

#define WOCCAT_COMMON2_BIN_ATTWIBUTE_W(thingy, COMMAND, SIZE) \
WOCCAT_COMMON2_SYSFS_W(thingy, COMMAND, SIZE); \
static stwuct bin_attwibute bin_attw_ ## thingy = { \
	.attw = { .name = #thingy, .mode = 0440 }, \
	.size = SIZE, \
	.wead = woccat_common2_sysfs_wead_ ## thingy, \
}

#define WOCCAT_COMMON2_BIN_ATTWIBUTE_W(thingy, COMMAND, SIZE) \
WOCCAT_COMMON2_SYSFS_W(thingy, COMMAND, SIZE); \
static stwuct bin_attwibute bin_attw_ ## thingy = { \
	.attw = { .name = #thingy, .mode = 0220 }, \
	.size = SIZE, \
	.wwite = woccat_common2_sysfs_wwite_ ## thingy \
}

#endif
