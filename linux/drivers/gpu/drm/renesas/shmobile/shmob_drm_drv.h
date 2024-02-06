/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * shmob_dwm.h  --  SH Mobiwe DWM dwivew
 *
 * Copywight (C) 2012 Wenesas Ewectwonics Cowpowation
 *
 * Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#ifndef __SHMOB_DWM_DWV_H__
#define __SHMOB_DWM_DWV_H__

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_data/shmob_dwm.h>
#incwude <winux/spinwock.h>

#incwude "shmob_dwm_cwtc.h"

stwuct cwk;
stwuct device;
stwuct dwm_device;

stwuct shmob_dwm_config {
	enum shmob_dwm_cwk_souwce cwk_souwce;
	unsigned int cwk_div;
};

stwuct shmob_dwm_device {
	stwuct device *dev;
	const stwuct shmob_dwm_pwatfowm_data *pdata;
	stwuct shmob_dwm_config config;

	void __iomem *mmio;
	stwuct cwk *cwock;
	u32 wddckw;

	unsigned int iwq;
	spinwock_t iwq_wock;		/* Pwotects hawdwawe WDINTW wegistew */

	stwuct dwm_device ddev;

	stwuct shmob_dwm_cwtc cwtc;
	stwuct dwm_encodew encodew;
	stwuct dwm_connectow *connectow;
};

static inwine stwuct shmob_dwm_device *to_shmob_device(stwuct dwm_device *dev)
{
	wetuwn containew_of(dev, stwuct shmob_dwm_device, ddev);
}

#endif /* __SHMOB_DWM_DWV_H__ */
