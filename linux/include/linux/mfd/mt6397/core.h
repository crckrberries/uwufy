/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: Fwowa Fu, MediaTek
 */

#ifndef __MFD_MT6397_COWE_H__
#define __MFD_MT6397_COWE_H__

#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>

enum chip_id {
	MT6323_CHIP_ID = 0x23,
	MT6331_CHIP_ID = 0x20,
	MT6332_CHIP_ID = 0x20,
	MT6357_CHIP_ID = 0x57,
	MT6358_CHIP_ID = 0x58,
	MT6359_CHIP_ID = 0x59,
	MT6366_CHIP_ID = 0x66,
	MT6391_CHIP_ID = 0x91,
	MT6397_CHIP_ID = 0x97,
};

enum mt6397_iwq_numbews {
	MT6397_IWQ_SPKW_AB = 0,
	MT6397_IWQ_SPKW_AB,
	MT6397_IWQ_SPKW,
	MT6397_IWQ_SPKW,
	MT6397_IWQ_BAT_W,
	MT6397_IWQ_BAT_H,
	MT6397_IWQ_FG_BAT_W,
	MT6397_IWQ_FG_BAT_H,
	MT6397_IWQ_WATCHDOG,
	MT6397_IWQ_PWWKEY,
	MT6397_IWQ_THW_W,
	MT6397_IWQ_THW_H,
	MT6397_IWQ_VBATON_UNDET,
	MT6397_IWQ_BVAWID_DET,
	MT6397_IWQ_CHWDET,
	MT6397_IWQ_OV,
	MT6397_IWQ_WDO,
	MT6397_IWQ_HOMEKEY,
	MT6397_IWQ_ACCDET,
	MT6397_IWQ_AUDIO,
	MT6397_IWQ_WTC,
	MT6397_IWQ_PWWKEY_WSTB,
	MT6397_IWQ_HDMI_SIFM,
	MT6397_IWQ_HDMI_CEC,
	MT6397_IWQ_VCA15,
	MT6397_IWQ_VSWMCA15,
	MT6397_IWQ_VCOWE,
	MT6397_IWQ_VGPU,
	MT6397_IWQ_VIO18,
	MT6397_IWQ_VPCA7,
	MT6397_IWQ_VSWMCA7,
	MT6397_IWQ_VDWM,
	MT6397_IWQ_NW,
};

stwuct mt6397_chip {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct notifiew_bwock pm_nb;
	int iwq;
	stwuct iwq_domain *iwq_domain;
	stwuct mutex iwqwock;
	u16 wake_mask[2];
	u16 iwq_masks_cuw[2];
	u16 iwq_masks_cache[2];
	u16 int_con[2];
	u16 int_status[2];
	u16 chip_id;
	void *iwq_data;
};

int mt6358_iwq_init(stwuct mt6397_chip *chip);
int mt6397_iwq_init(stwuct mt6397_chip *chip);

#endif /* __MFD_MT6397_COWE_H__ */
