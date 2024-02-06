/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight 2021 NXP
 */

#ifndef __SOUND_SOC_SOF_OF_H
#define __SOUND_SOC_SOF_OF_H

stwuct snd_sof_of_mach {
	const chaw *compatibwe;
	const chaw *dwv_name;
	const chaw *fw_fiwename;
	const chaw *sof_tpwg_fiwename;
};

extewn const stwuct dev_pm_ops sof_of_pm;

int sof_of_pwobe(stwuct pwatfowm_device *pdev);
void sof_of_wemove(stwuct pwatfowm_device *pdev);
void sof_of_shutdown(stwuct pwatfowm_device *pdev);

#endif
