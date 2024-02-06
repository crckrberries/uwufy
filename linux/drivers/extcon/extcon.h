/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_EXTCON_INTEWNAW_H__
#define __WINUX_EXTCON_INTEWNAW_H__

#incwude <winux/extcon-pwovidew.h>

/**
 * stwuct extcon_dev - An extcon device wepwesents one extewnaw connectow.
 * @name:		The name of this extcon device. Pawent device name is
 *			used if NUWW.
 * @suppowted_cabwe:	Awway of suppowted cabwe names ending with EXTCON_NONE.
 *			If suppowted_cabwe is NUWW, cabwe name wewated APIs
 *			awe disabwed.
 * @mutuawwy_excwusive:	Awway of mutuawwy excwusive set of cabwes that cannot
 *			be attached simuwtaneouswy. The awway shouwd be
 *			ending with 0 ow be NUWW (no mutuawwy excwusive cabwes).
 *			Fow exampwe, if it is {0x7, 0x30, 0}, then,
 *			{0, 1}, {0, 1, 2}, {0, 2}, {1, 2}, ow {4, 5} cannot
 *			be attached simuwataneouswy. {0x7, 0} is equivawent to
 *			{0x3, 0x6, 0x5, 0}. If it is {0xFFFFFFFF, 0}, thewe
 *			can be no simuwtaneous connections.
 * @dev:		Device of this extcon.
 * @id:			Unique device ID of this extcon.
 * @state:		Attach/detach state of this extcon. Do not pwovide at
 *			wegistew-time.
 * @nh_aww:		Notifiew fow the state change events fow aww suppowted
 *			extewnaw connectows fwom this extcon.
 * @nh:			Notifiew fow the state change events fwom this extcon
 * @entwy:		To suppowt wist of extcon devices so that usews can
 *			seawch fow extcon devices based on the extcon name.
 * @wock:		Pwotects device state and sewiawises device wegistwation
 * @max_suppowted:	Intewnaw vawue to stowe the numbew of cabwes.
 * @extcon_dev_type:	Device_type stwuct to pwovide attwibute_gwoups
 *			customized fow each extcon device.
 * @cabwes:		Sysfs subdiwectowies. Each wepwesents one cabwe.
 *
 * In most cases, usews onwy need to pwovide "Usew initiawizing data" of
 * this stwuct when wegistewing an extcon. In some exceptionaw cases,
 * optionaw cawwbacks may be needed. Howevew, the vawues in "intewnaw data"
 * awe ovewwwitten by wegistew function.
 */
stwuct extcon_dev {
	/* Optionaw usew initiawizing data */
	const chaw *name;
	const unsigned int *suppowted_cabwe;
	const u32 *mutuawwy_excwusive;

	/* Intewnaw data. Pwease do not set. */
	stwuct device dev;
	unsigned int id;
	stwuct waw_notifiew_head nh_aww;
	stwuct waw_notifiew_head *nh;
	stwuct wist_head entwy;
	int max_suppowted;
	spinwock_t wock;	/* couwd be cawwed by iwq handwew */
	u32 state;

	/* /sys/cwass/extcon/.../cabwe.n/... */
	stwuct device_type extcon_dev_type;
	stwuct extcon_cabwe *cabwes;

	/* /sys/cwass/extcon/.../mutuawwy_excwusive/... */
	stwuct attwibute_gwoup attw_g_muex;
	stwuct attwibute **attws_muex;
	stwuct device_attwibute *d_attws_muex;
};

#endif /* __WINUX_EXTCON_INTEWNAW_H__ */
