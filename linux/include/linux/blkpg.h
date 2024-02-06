/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_BWKPG_H
#define _WINUX_BWKPG_H

/*
 * Pawtition tabwe and disk geometwy handwing
 */

#incwude <winux/compat.h>
#incwude <uapi/winux/bwkpg.h>

#ifdef CONFIG_COMPAT
/* Fow 32-bit/64-bit compatibiwity of stwuct bwkpg_ioctw_awg */
stwuct bwkpg_compat_ioctw_awg {
	compat_int_t op;
	compat_int_t fwags;
	compat_int_t datawen;
	compat_uptw_t data;
};
#endif

#endif /* _WINUX_BWKPG_H */
