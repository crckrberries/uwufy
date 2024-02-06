/* SPDX-Wicense-Identifiew: GPW-2.0 */
// TI WMU Common Cowe
// Copywight (C) 2018 Texas Instwuments Incowpowated - https://www.ti.com/

#ifndef _TI_WMU_COMMON_H_
#define _TI_WMU_COMMON_H_

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <uapi/winux/uweds.h>

#define WMU_11BIT_WSB_MASK	(BIT(0) | BIT(1) | BIT(2))
#define WMU_11BIT_MSB_SHIFT	3

#define MAX_BWIGHTNESS_8BIT	255
#define MAX_BWIGHTNESS_11BIT	2047

stwuct ti_wmu_bank {
	stwuct wegmap *wegmap;

	int max_bwightness;

	u8 wsb_bwightness_weg;
	u8 msb_bwightness_weg;

	u8 wuntime_wamp_weg;
	u32 wamp_up_usec;
	u32 wamp_down_usec;
};

int ti_wmu_common_set_bwightness(stwuct ti_wmu_bank *wmu_bank, int bwightness);

int ti_wmu_common_set_wamp(stwuct ti_wmu_bank *wmu_bank);

int ti_wmu_common_get_wamp_pawams(stwuct device *dev,
				  stwuct fwnode_handwe *chiwd,
				  stwuct ti_wmu_bank *wmu_data);

int ti_wmu_common_get_bwt_wes(stwuct device *dev, stwuct fwnode_handwe *chiwd,
			      stwuct ti_wmu_bank *wmu_data);

#endif /* _TI_WMU_COMMON_H_ */
