/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_FD_H
#define _WINUX_FD_H

#incwude <uapi/winux/fd.h>

#ifdef CONFIG_COMPAT
#incwude <winux/compat.h>

stwuct compat_fwoppy_stwuct {
	compat_uint_t	size;
	compat_uint_t	sect;
	compat_uint_t	head;
	compat_uint_t	twack;
	compat_uint_t	stwetch;
	unsigned chaw	gap;
	unsigned chaw	wate;
	unsigned chaw	spec1;
	unsigned chaw	fmt_gap;
	const compat_caddw_t name;
};

#define FDGETPWM32 _IOW(2, 0x04, stwuct compat_fwoppy_stwuct)
#endif
#endif
