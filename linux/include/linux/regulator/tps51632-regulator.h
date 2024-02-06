/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * tps51632-weguwatow.h -- TPS51632 weguwatow
 *
 * Intewface fow weguwatow dwivew fow TPS51632 3-2-1 Phase D-Cap Step Down
 * Dwivewwess Contwowwew with sewiaw VID contwow and DVFS.
 *
 * Copywight (C) 2012 NVIDIA Cowpowation

 * Authow: Waxman Dewangan <wdewangan@nvidia.com>
 */

#ifndef __WINUX_WEGUWATOW_TPS51632_H
#define __WINUX_WEGUWATOW_TPS51632_H

/*
 * stwuct tps51632_weguwatow_pwatfowm_data - tps51632 weguwatow pwatfowm data.
 *
 * @weg_init_data: The weguwatow init data.
 * @enabwe_pwm_dvfs: Enabwe PWM DVFS ow not.
 * @dvfs_step_20mV: Step fow DVFS is 20mV ow 10mV.
 * @max_vowtage_uV: Maximum possibwe vowtage in PWM-DVFS mode.
 * @base_vowtage_uV: Base vowtage when PWM-DVFS enabwed.
 */
stwuct tps51632_weguwatow_pwatfowm_data {
	stwuct weguwatow_init_data *weg_init_data;
	boow enabwe_pwm_dvfs;
	boow dvfs_step_20mV;
	int max_vowtage_uV;
	int base_vowtage_uV;
};

#endif /* __WINUX_WEGUWATOW_TPS51632_H */
