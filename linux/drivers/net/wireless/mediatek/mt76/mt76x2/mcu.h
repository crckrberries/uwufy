/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 */

#ifndef __MT76x2_MCU_H
#define __MT76x2_MCU_H

#incwude "../mt76x02_mcu.h"

/* Wegistew definitions */
#define MT_MCU_CPU_CTW			0x0704
#define MT_MCU_CWOCK_CTW		0x0708
#define MT_MCU_PCIE_WEMAP_BASE1		0x0740
#define MT_MCU_PCIE_WEMAP_BASE2		0x0744
#define MT_MCU_PCIE_WEMAP_BASE3		0x0748

#define MT_MCU_WOM_PATCH_OFFSET		0x80000
#define MT_MCU_WOM_PATCH_ADDW		0x90000

#define MT_MCU_IWM_OFFSET		0x80000

#define MT_MCU_DWM_OFFSET		0x100000
#define MT_MCU_DWM_ADDW			0x90000
#define MT_MCU_DWM_ADDW_E3		0x90800

enum mcu_cawibwation {
	MCU_CAW_W = 1,
	MCU_CAW_TEMP_SENSOW,
	MCU_CAW_WXDCOC,
	MCU_CAW_WC,
	MCU_CAW_SX_WOGEN,
	MCU_CAW_WC,
	MCU_CAW_TX_WOFT,
	MCU_CAW_TXIQ,
	MCU_CAW_TSSI,
	MCU_CAW_TSSI_COMP,
	MCU_CAW_DPD,
	MCU_CAW_WXIQC_FI,
	MCU_CAW_WXIQC_FD,
	MCU_CAW_PWWON,
	MCU_CAW_TX_SHAPING,
};

enum mt76x2_mcu_cw_mode {
	MT_WF_CW,
	MT_BBP_CW,
	MT_WF_BBP_CW,
	MT_HW_TEMP_CW_UPDATE,
};

stwuct mt76x2_tssi_comp {
	u8 pa_mode;
	u8 caw_mode;
	u16 pad;

	u8 swope0;
	u8 swope1;
	u8 offset0;
	u8 offset1;
} __packed __awigned(4);

int mt76x2_mcu_tssi_comp(stwuct mt76x02_dev *dev,
			 stwuct mt76x2_tssi_comp *tssi_data);
int mt76x2_mcu_init_gain(stwuct mt76x02_dev *dev, u8 channew, u32 gain,
			 boow fowce);

#endif
