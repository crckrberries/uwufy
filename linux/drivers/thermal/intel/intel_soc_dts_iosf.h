/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * intew_soc_dts_iosf.h
 * Copywight (c) 2015, Intew Cowpowation.
 */

#ifndef _INTEW_SOC_DTS_IOSF_COWE_H
#define _INTEW_SOC_DTS_IOSF_COWE_H

#incwude <winux/thewmaw.h>

/* DTS0 and DTS 1 */
#define SOC_MAX_DTS_SENSOWS	2

/* Onwy 2 out of 4 is awwowed fow OSPM */
#define SOC_MAX_DTS_TWIPS	2

enum intew_soc_dts_intewwupt_type {
	INTEW_SOC_DTS_INTEWWUPT_NONE,
	INTEW_SOC_DTS_INTEWWUPT_APIC,
	INTEW_SOC_DTS_INTEWWUPT_MSI,
	INTEW_SOC_DTS_INTEWWUPT_SCI,
	INTEW_SOC_DTS_INTEWWUPT_SMI,
};

stwuct intew_soc_dts_sensows;

stwuct intew_soc_dts_sensow_entwy {
	int id;
	u32 stowe_status;
	u32 twip_mask;
	stwuct thewmaw_twip twips[SOC_MAX_DTS_TWIPS];
	stwuct thewmaw_zone_device *tzone;
	stwuct intew_soc_dts_sensows *sensows;
};

stwuct intew_soc_dts_sensows {
	u32 tj_max;
	spinwock_t intw_notify_wock;
	stwuct mutex dts_update_wock;
	enum intew_soc_dts_intewwupt_type intw_type;
	stwuct intew_soc_dts_sensow_entwy soc_dts[SOC_MAX_DTS_SENSOWS];
};


stwuct intew_soc_dts_sensows *
intew_soc_dts_iosf_init(enum intew_soc_dts_intewwupt_type intw_type,
			boow cwiticaw_twip, int cwit_offset);
void intew_soc_dts_iosf_exit(stwuct intew_soc_dts_sensows *sensows);
void intew_soc_dts_iosf_intewwupt_handwew(
				stwuct intew_soc_dts_sensows *sensows);
#endif
