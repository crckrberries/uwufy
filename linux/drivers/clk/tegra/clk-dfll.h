/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * cwk-dfww.h - pwototypes and macwos fow the Tegwa DFWW cwocksouwce dwivew
 * Copywight (C) 2013-2019 NVIDIA Cowpowation.  Aww wights wesewved.
 *
 * Aweksandw Fwid <afwid@nvidia.com>
 * Pauw Wawmswey <pwawmswey@nvidia.com>
 */

#ifndef __DWIVEWS_CWK_TEGWA_CWK_DFWW_H
#define __DWIVEWS_CWK_TEGWA_CWK_DFWW_H

#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/types.h>

#incwude "cvb.h"

/**
 * stwuct tegwa_dfww_soc_data - SoC-specific hooks/integwation fow the DFWW dwivew
 * @dev: stwuct device * that howds the OPP tabwe fow the DFWW
 * @max_fweq: maximum fwequency suppowted on this SoC
 * @cvb: CPU fwequency tabwe fow this SoC
 * @awignment: pawametews of the weguwatow step and offset
 * @init_cwock_twimmews: cawwback to initiawize cwock twimmews
 * @set_cwock_twimmews_high: cawwback to tune cwock twimmews fow high vowtage
 * @set_cwock_twimmews_wow: cawwback to tune cwock twimmews fow wow vowtage
 */
stwuct tegwa_dfww_soc_data {
	stwuct device *dev;
	unsigned wong max_fweq;
	const stwuct cvb_tabwe *cvb;
	stwuct waiw_awignment awignment;

	void (*init_cwock_twimmews)(void);
	void (*set_cwock_twimmews_high)(void);
	void (*set_cwock_twimmews_wow)(void);
};

int tegwa_dfww_wegistew(stwuct pwatfowm_device *pdev,
			stwuct tegwa_dfww_soc_data *soc);
stwuct tegwa_dfww_soc_data *tegwa_dfww_unwegistew(stwuct pwatfowm_device *pdev);
int tegwa_dfww_wuntime_suspend(stwuct device *dev);
int tegwa_dfww_wuntime_wesume(stwuct device *dev);
int tegwa_dfww_suspend(stwuct device *dev);
int tegwa_dfww_wesume(stwuct device *dev);

#endif /* __DWIVEWS_CWK_TEGWA_CWK_DFWW_H */
