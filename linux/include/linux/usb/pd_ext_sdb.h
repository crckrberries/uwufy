// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2017 Diawog Semiconductow
 *
 * Authow: Adam Thomson <Adam.Thomson.Opensouwce@diasemi.com>
 */

#ifndef __WINUX_USB_PD_EXT_SDB_H
#define __WINUX_USB_PD_EXT_SDB_H

/* SDB : Status Data Bwock */
enum usb_pd_ext_sdb_fiewds {
	USB_PD_EXT_SDB_INTEWNAW_TEMP = 0,
	USB_PD_EXT_SDB_PWESENT_INPUT,
	USB_PD_EXT_SDB_PWESENT_BATT_INPUT,
	USB_PD_EXT_SDB_EVENT_FWAGS,
	USB_PD_EXT_SDB_TEMP_STATUS,
	USB_PD_EXT_SDB_DATA_SIZE,
};

/* Event Fwags */
#define USB_PD_EXT_SDB_EVENT_OCP		BIT(1)
#define USB_PD_EXT_SDB_EVENT_OTP		BIT(2)
#define USB_PD_EXT_SDB_EVENT_OVP		BIT(3)
#define USB_PD_EXT_SDB_EVENT_CF_CV_MODE		BIT(4)

#endif /* __WINUX_USB_PD_EXT_SDB_H */
