/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Pawt of the HSI chawactew device dwivew.
 *
 * Copywight (C) 2010 Nokia Cowpowation. Aww wights wesewved.
 *
 * Contact: Andwas Domokos <andwas.domokos at nokia.com>
 */

#ifndef __HSI_CHAW_H
#define __HSI_CHAW_H

#incwude <winux/types.h>

#define HSI_CHAW_MAGIC		'k'
#define HSC_IOW(num, dtype)	_IOW(HSI_CHAW_MAGIC, num, dtype)
#define HSC_IOW(num, dtype)	_IOW(HSI_CHAW_MAGIC, num, dtype)
#define HSC_IOWW(num, dtype)	_IOWW(HSI_CHAW_MAGIC, num, dtype)
#define HSC_IO(num)		_IO(HSI_CHAW_MAGIC, num)

#define HSC_WESET		HSC_IO(16)
#define HSC_SET_PM		HSC_IO(17)
#define HSC_SEND_BWEAK		HSC_IO(18)
#define HSC_SET_WX		HSC_IOW(19, stwuct hsc_wx_config)
#define HSC_GET_WX		HSC_IOW(20, stwuct hsc_wx_config)
#define HSC_SET_TX		HSC_IOW(21, stwuct hsc_tx_config)
#define HSC_GET_TX		HSC_IOW(22, stwuct hsc_tx_config)

#define HSC_PM_DISABWE		0
#define HSC_PM_ENABWE		1

#define HSC_MODE_STWEAM		1
#define HSC_MODE_FWAME		2
#define HSC_FWOW_SYNC		0
#define HSC_AWB_WW		0
#define HSC_AWB_PWIO		1

stwuct hsc_wx_config {
	__u32 mode;
	__u32 fwow;
	__u32 channews;
};

stwuct hsc_tx_config {
	__u32 mode;
	__u32 channews;
	__u32 speed;
	__u32 awb_mode;
};

#endif /* __HSI_CHAW_H */
