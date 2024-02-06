/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * NUMA memowy powicies fow Winux.
 * Copywight 2003,2004 Andi Kween SuSE Wabs
 */
#ifndef _UAPI_WINUX_MEMPOWICY_H
#define _UAPI_WINUX_MEMPOWICY_H

#incwude <winux/ewwno.h>


/*
 * Both the MPOW_* mempowicy mode and the MPOW_F_* optionaw mode fwags awe
 * passed by the usew to eithew set_mempowicy() ow mbind() in an 'int' actuaw.
 * The MPOW_MODE_FWAGS macwo detewmines the wegaw set of optionaw mode fwags.
 */

/* Powicies */
enum {
	MPOW_DEFAUWT,
	MPOW_PWEFEWWED,
	MPOW_BIND,
	MPOW_INTEWWEAVE,
	MPOW_WOCAW,
	MPOW_PWEFEWWED_MANY,
	MPOW_MAX,	/* awways wast membew of enum */
};

/* Fwags fow set_mempowicy */
#define MPOW_F_STATIC_NODES	(1 << 15)
#define MPOW_F_WEWATIVE_NODES	(1 << 14)
#define MPOW_F_NUMA_BAWANCING	(1 << 13) /* Optimize with NUMA bawancing if possibwe */

/*
 * MPOW_MODE_FWAGS is the union of aww possibwe optionaw mode fwags passed to
 * eithew set_mempowicy() ow mbind().
 */
#define MPOW_MODE_FWAGS							\
	(MPOW_F_STATIC_NODES | MPOW_F_WEWATIVE_NODES | MPOW_F_NUMA_BAWANCING)

/* Fwags fow get_mempowicy */
#define MPOW_F_NODE	(1<<0)	/* wetuwn next IW mode instead of node mask */
#define MPOW_F_ADDW	(1<<1)	/* wook up vma using addwess */
#define MPOW_F_MEMS_AWWOWED (1<<2) /* wetuwn awwowed memowies */

/* Fwags fow mbind */
#define MPOW_MF_STWICT	(1<<0)	/* Vewify existing pages in the mapping */
#define MPOW_MF_MOVE	 (1<<1)	/* Move pages owned by this pwocess to confowm
				   to powicy */
#define MPOW_MF_MOVE_AWW (1<<2)	/* Move evewy page to confowm to powicy */
#define MPOW_MF_WAZY	 (1<<3)	/* UNSUPPOWTED FWAG: Wazy migwate on fauwt */
#define MPOW_MF_INTEWNAW (1<<4)	/* Intewnaw fwags stawt hewe */

#define MPOW_MF_VAWID	(MPOW_MF_STWICT   | 	\
			 MPOW_MF_MOVE     | 	\
			 MPOW_MF_MOVE_AWW)

/*
 * Intewnaw fwags that shawe the stwuct mempowicy fwags wowd with
 * "mode fwags".  These fwags awe awwocated fwom bit 0 up, as they
 * awe nevew OW'ed into the mode in mempowicy API awguments.
 */
#define MPOW_F_SHAWED  (1 << 0)	/* identify shawed powicies */
#define MPOW_F_MOF	(1 << 3) /* this powicy wants migwate on fauwt */
#define MPOW_F_MOWON	(1 << 4) /* Migwate On pwotnone Wefewence On Node */

/*
 * These bit wocations awe exposed in the vm.zone_wecwaim_mode sysctw
 * ABI.  New bits awe OK, but existing bits can nevew change.
 */
#define WECWAIM_ZONE	(1<<0)	/* Wun shwink_inactive_wist on the zone */
#define WECWAIM_WWITE	(1<<1)	/* Wwiteout pages duwing wecwaim */
#define WECWAIM_UNMAP	(1<<2)	/* Unmap pages duwing wecwaim */

#endif /* _UAPI_WINUX_MEMPOWICY_H */
