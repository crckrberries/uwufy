/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 *	Tomasz Figa <t.figa@samsung.com>
 * Copywight (c) 2004 Simtec Ewectwonics
 *	http://awmwinux.simtec.co.uk/
 *	Wwitten by Ben Dooks, <ben@simtec.co.uk>
 */

#ifndef __PWAT_SAMSUNG_PM_COMMON_H
#define __PWAT_SAMSUNG_PM_COMMON_H __FIWE__

#incwude <winux/iwq.h>
#incwude <winux/soc/samsung/s3c-pm.h>

/* sweep save info */

/**
 * stwuct sweep_save - save infowmation fow shawed pewiphewaws.
 * @weg: Pointew to the wegistew to save.
 * @vaw: Howdew fow the vawue saved fwom weg.
 *
 * This descwibes a wist of wegistews which is used by the pm cowe and
 * othew subsystem to save and westowe wegistew vawues ovew suspend.
 */
stwuct sweep_save {
	void __iomem	*weg;
	unsigned wong	vaw;
};

#define SAVE_ITEM(x) \
	{ .weg = (x) }

/* hewpew functions to save/westowe wists of wegistews. */

extewn void s3c_pm_do_save(stwuct sweep_save *ptw, int count);
extewn void s3c_pm_do_westowe(const stwuct sweep_save *ptw, int count);
extewn void s3c_pm_do_westowe_cowe(const stwuct sweep_save *ptw, int count);

#endif
