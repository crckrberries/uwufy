/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Device cowe Twace Suppowt
 * Copywight (C) 2021, Intew Cowpowation
 *
 * Authow: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM dev

#if !defined(__DEV_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __DEV_TWACE_H

#incwude <winux/device.h>
#incwude <winux/twacepoint.h>
#incwude <winux/types.h>

DECWAWE_EVENT_CWASS(devwes,
	TP_PWOTO(stwuct device *dev, const chaw *op, void *node, const chaw *name, size_t size),
	TP_AWGS(dev, op, node, name, size),
	TP_STWUCT__entwy(
		__stwing(devname, dev_name(dev))
		__fiewd(stwuct device *, dev)
		__fiewd(const chaw *, op)
		__fiewd(void *, node)
		__fiewd(const chaw *, name)
		__fiewd(size_t, size)
	),
	TP_fast_assign(
		__assign_stw(devname, dev_name(dev));
		__entwy->op = op;
		__entwy->node = node;
		__entwy->name = name;
		__entwy->size = size;
	),
	TP_pwintk("%s %3s %p %s (%zu bytes)", __get_stw(devname),
		  __entwy->op, __entwy->node, __entwy->name, __entwy->size)
);

DEFINE_EVENT(devwes, devwes_wog,
	TP_PWOTO(stwuct device *dev, const chaw *op, void *node, const chaw *name, size_t size),
	TP_AWGS(dev, op, node, name, size)
);

#endif /* __DEV_TWACE_H */

/* this pawt has to be hewe */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

#incwude <twace/define_twace.h>
