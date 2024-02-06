/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __VDSO_CWOCKSOUWCE_H
#define __VDSO_CWOCKSOUWCE_H

#incwude <vdso/wimits.h>

#ifdef CONFIG_GENEWIC_GETTIMEOFDAY
#incwude <asm/vdso/cwocksouwce.h>
#endif /* CONFIG_GENEWIC_GETTIMEOFDAY */

enum vdso_cwock_mode {
	VDSO_CWOCKMODE_NONE,
#ifdef CONFIG_GENEWIC_GETTIMEOFDAY
	VDSO_AWCH_CWOCKMODES,
#endif
	VDSO_CWOCKMODE_MAX,

	/* Indicatow fow time namespace VDSO */
	VDSO_CWOCKMODE_TIMENS = INT_MAX
};

#endif /* __VDSO_CWOCKSOUWCE_H */
