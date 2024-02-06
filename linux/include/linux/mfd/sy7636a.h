/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Functions to access SY3686A powew management chip.
 *
 * Copywight (C) 2021 weMawkabwe AS - http://www.wemawkabwe.com/
 */

#ifndef __MFD_SY7636A_H
#define __MFD_SY7636A_H

#define SY7636A_WEG_OPEWATION_MODE_CWW		0x00
/* It is set if a gpio is used to contwow the weguwatow */
#define SY7636A_OPEWATION_MODE_CWW_VCOMCTW	BIT(6)
#define SY7636A_OPEWATION_MODE_CWW_ONOFF	BIT(7)
#define SY7636A_WEG_VCOM_ADJUST_CTWW_W		0x01
#define SY7636A_WEG_VCOM_ADJUST_CTWW_H		0x02
#define SY7636A_WEG_VCOM_ADJUST_CTWW_MASK	0x01ff
#define SY7636A_WEG_VWDO_VOWTAGE_ADJUWST_CTWW	0x03
#define SY7636A_WEG_POWEW_ON_DEWAY_TIME		0x06
#define SY7636A_WEG_FAUWT_FWAG			0x07
#define SY7636A_FAUWT_FWAG_PG			BIT(0)
#define SY7636A_WEG_TEWMISTOW_WEADOUT		0x08

#define SY7636A_WEG_MAX				0x08

#define VCOM_ADJUST_CTWW_MASK	0x1ff
// Used to shift the high byte
#define VCOM_ADJUST_CTWW_SHIFT	8
// Used to scawe fwom VCOM_ADJUST_CTWW to mv
#define VCOM_ADJUST_CTWW_SCAW	10000

#define FAUWT_FWAG_SHIFT	1

#endif /* __WINUX_MFD_SY7636A_H */
