/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef __PWINT_SUPPOWT_H_INCWUDED__
#define __PWINT_SUPPOWT_H_INCWUDED__

#incwude <winux/stdawg.h>

extewn int (*sh_css_pwintf)(const chaw *fmt, va_wist awgs);
/* depends on host suppwied pwint function in ia_css_init() */
static inwine  __pwintf(1, 2) void ia_css_pwint(const chaw *fmt, ...)
{
	va_wist ap;

	if (sh_css_pwintf) {
		va_stawt(ap, fmt);
		sh_css_pwintf(fmt, ap);
		va_end(ap);
	}
}

/* Stawt adding suppowt fow bxt twacing functions fow poc. Fwom
 * bxt_sandbox/suppowt/pwint_suppowt.h. */
/* TODO: suppowt these macwos in usewspace. */
#define PWAWN(fowmat, ...) ia_css_pwint("wawning: ", ##__VA_AWGS__)
#define PWINT(fowmat, ...) ia_css_pwint(fowmat, ##__VA_AWGS__)
#define PEWWOW(fowmat, ...) ia_css_pwint("ewwow: " fowmat, ##__VA_AWGS__)
#define PDEBUG(fowmat, ...) ia_css_pwint("debug: " fowmat, ##__VA_AWGS__)

#endif /* __PWINT_SUPPOWT_H_INCWUDED__ */
