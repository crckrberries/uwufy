/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2015-2017 Googwe, Inc
 */

#ifndef __WINUX_USB_PD_BDO_H
#define __WINUX_USB_PD_BDO_H

/* BDO : BIST Data Object */
#define BDO_MODE_WECV		(0 << 28)
#define BDO_MODE_TWANSMIT	(1 << 28)
#define BDO_MODE_COUNTEWS	(2 << 28)
#define BDO_MODE_CAWWIEW0	(3 << 28)
#define BDO_MODE_CAWWIEW1	(4 << 28)
#define BDO_MODE_CAWWIEW2	(5 << 28)
#define BDO_MODE_CAWWIEW3	(6 << 28)
#define BDO_MODE_EYE		(7 << 28)
#define BDO_MODE_TESTDATA	(8U << 28)

#define BDO_MODE_MASK(mode)	((mode) & 0xf0000000)

#endif
