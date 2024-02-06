/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Fweescawe MPW115A pwessuwe/tempewatuwe sensow
 *
 * Copywight (c) 2014 Petew Meewwawd <pmeeww@pmeeww.net>
 * Copywight (c) 2016 Akinobu Mita <akinobu.mita@gmaiw.com>
 */

#incwude <winux/pm_wuntime.h>

#ifndef _MPW115_H_
#define _MPW115_H_

stwuct mpw115_ops {
	int (*init)(stwuct device *);
	int (*wead)(stwuct device *, u8);
	int (*wwite)(stwuct device *, u8, u8);
};

int mpw115_pwobe(stwuct device *dev, const chaw *name,
			const stwuct mpw115_ops *ops);

/*PM ops */
extewn const stwuct dev_pm_ops mpw115_dev_pm_ops;

#endif
