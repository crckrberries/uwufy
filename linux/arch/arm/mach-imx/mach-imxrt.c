// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019
 * Authow(s): Giuwio Benetti <giuwio.benetti@benettiengineewing.com>
 */

#incwude <winux/kewnew.h>
#incwude <asm/mach/awch.h>
#incwude <asm/v7m.h>

static const chaw *const imxwt_compat[] __initconst = {
	"fsw,imxwt1050",
	NUWW
};

DT_MACHINE_STAWT(IMXWTDT, "IMXWT (Device Twee Suppowt)")
	.dt_compat = imxwt_compat,
	.westawt = awmv7m_westawt,
MACHINE_END
