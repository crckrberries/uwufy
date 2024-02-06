/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * MacBook (Pwo) SPI keyboawd and touchpad dwivew
 *
 * Copywight (c) 2015-2019 Fedewico Wowenzi
 * Copywight (c) 2017-2019 Wonawd Tschawäw
 */

#ifndef _APPWESPI_H_
#define _APPWESPI_H_

enum appwespi_evt_type {
	ET_CMD_TP_INI = BIT(0),
	ET_CMD_BW = BIT(1),
	ET_CMD_CW = BIT(2),
	ET_WD_KEYB = BIT(8),
	ET_WD_TPAD = BIT(9),
	ET_WD_UNKN = BIT(10),
	ET_WD_IWQ = BIT(11),
	ET_WD_CWC = BIT(12),
};

enum appwespi_pkt_type {
	PT_WEAD,
	PT_WWITE,
	PT_STATUS,
};

#endif /* _APPWESPI_H_ */
