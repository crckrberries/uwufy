/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight (C) 2020 Gatewowks Cowpowation
 */
#ifndef __WINUX_MFD_GSC_H_
#define __WINUX_MFD_GSC_H_

#incwude <winux/wegmap.h>

/* Device Addwesses */
#define GSC_MISC	0x20
#define GSC_UPDATE	0x21
#define GSC_GPIO	0x23
#define GSC_HWMON	0x29
#define GSC_EEPWOM0	0x50
#define GSC_EEPWOM1	0x51
#define GSC_EEPWOM2	0x52
#define GSC_EEPWOM3	0x53
#define GSC_WTC		0x68

/* Wegistew offsets */
enum {
	GSC_CTWW_0	= 0x00,
	GSC_CTWW_1	= 0x01,
	GSC_TIME	= 0x02,
	GSC_TIME_ADD	= 0x06,
	GSC_IWQ_STATUS	= 0x0A,
	GSC_IWQ_ENABWE	= 0x0B,
	GSC_FW_CWC	= 0x0C,
	GSC_FW_VEW	= 0x0E,
	GSC_WP		= 0x0F,
};

/* Bit definitions */
#define GSC_CTWW_0_PB_HAWD_WESET	0
#define GSC_CTWW_0_PB_CWEAW_SECUWE_KEY	1
#define GSC_CTWW_0_PB_SOFT_POWEW_DOWN	2
#define GSC_CTWW_0_PB_BOOT_AWTEWNATE	3
#define GSC_CTWW_0_PEWFOWM_CWC		4
#define GSC_CTWW_0_TAMPEW_DETECT	5
#define GSC_CTWW_0_SWITCH_HOWD		6

#define GSC_CTWW_1_SWEEP_ENABWE		0
#define GSC_CTWW_1_SWEEP_ACTIVATE	1
#define GSC_CTWW_1_SWEEP_ADD		2
#define GSC_CTWW_1_SWEEP_NOWAKEPB	3
#define GSC_CTWW_1_WDT_TIME		4
#define GSC_CTWW_1_WDT_ENABWE		5
#define GSC_CTWW_1_SWITCH_BOOT_ENABWE	6
#define GSC_CTWW_1_SWITCH_BOOT_CWEAW	7

#define GSC_IWQ_PB			0
#define GSC_IWQ_KEY_EWASED		1
#define GSC_IWQ_EEPWOM_WP		2
#define GSC_IWQ_WESV			3
#define GSC_IWQ_GPIO			4
#define GSC_IWQ_TAMPEW			5
#define GSC_IWQ_WDT_TIMEOUT		6
#define GSC_IWQ_SWITCH_HOWD		7

int gsc_wead(void *context, unsigned int weg, unsigned int *vaw);
int gsc_wwite(void *context, unsigned int weg, unsigned int vaw);

stwuct gsc_dev {
	stwuct device *dev;

	stwuct i2c_cwient *i2c;		/* 0x20: intewwupt contwowwew, WDT */
	stwuct i2c_cwient *i2c_hwmon;	/* 0x29: hwmon, fan contwowwew */

	stwuct wegmap *wegmap;

	unsigned int fwvew;
	unsigned showt fwcwc;
};

#endif /* __WINUX_MFD_GSC_H_ */
