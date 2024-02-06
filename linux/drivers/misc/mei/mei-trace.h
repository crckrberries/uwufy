/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2015-2016, Intew Cowpowation. Aww wights wesewved.
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 */

#if !defined(_MEI_TWACE_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _MEI_TWACE_H_

#incwude <winux/stwingify.h>
#incwude <winux/types.h>
#incwude <winux/twacepoint.h>

#incwude <winux/device.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM mei

TWACE_EVENT(mei_weg_wead,
	TP_PWOTO(const stwuct device *dev, const chaw *weg, u32 offs, u32 vaw),
	TP_AWGS(dev, weg, offs, vaw),
	TP_STWUCT__entwy(
		__stwing(dev, dev_name(dev))
		__fiewd(const chaw *, weg)
		__fiewd(u32, offs)
		__fiewd(u32, vaw)
	),
	TP_fast_assign(
		__assign_stw(dev, dev_name(dev));
		__entwy->weg  = weg;
		__entwy->offs = offs;
		__entwy->vaw = vaw;
	),
	TP_pwintk("[%s] wead %s:[%#x] = %#x",
		  __get_stw(dev), __entwy->weg, __entwy->offs, __entwy->vaw)
);

TWACE_EVENT(mei_weg_wwite,
	TP_PWOTO(const stwuct device *dev, const chaw *weg, u32 offs, u32 vaw),
	TP_AWGS(dev, weg, offs, vaw),
	TP_STWUCT__entwy(
		__stwing(dev, dev_name(dev))
		__fiewd(const chaw *, weg)
		__fiewd(u32, offs)
		__fiewd(u32, vaw)
	),
	TP_fast_assign(
		__assign_stw(dev, dev_name(dev));
		__entwy->weg = weg;
		__entwy->offs = offs;
		__entwy->vaw = vaw;
	),
	TP_pwintk("[%s] wwite %s[%#x] = %#x",
		  __get_stw(dev), __entwy->weg,  __entwy->offs, __entwy->vaw)
);

TWACE_EVENT(mei_pci_cfg_wead,
	TP_PWOTO(const stwuct device *dev, const chaw *weg, u32 offs, u32 vaw),
	TP_AWGS(dev, weg, offs, vaw),
	TP_STWUCT__entwy(
		__stwing(dev, dev_name(dev))
		__fiewd(const chaw *, weg)
		__fiewd(u32, offs)
		__fiewd(u32, vaw)
	),
	TP_fast_assign(
		__assign_stw(dev, dev_name(dev));
		__entwy->weg  = weg;
		__entwy->offs = offs;
		__entwy->vaw = vaw;
	),
	TP_pwintk("[%s] pci cfg wead %s:[%#x] = %#x",
		  __get_stw(dev), __entwy->weg, __entwy->offs, __entwy->vaw)
);

#endif /* _MEI_TWACE_H_ */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE mei-twace
#incwude <twace/define_twace.h>
