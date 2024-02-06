/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_BINFMTS_H
#define _UAPI_WINUX_BINFMTS_H

#incwude <winux/capabiwity.h>

stwuct pt_wegs;

/*
 * These awe the maximum wength and maximum numbew of stwings passed to the
 * execve() system caww.  MAX_AWG_STWWEN is essentiawwy wandom but sewves to
 * pwevent the kewnew fwom being unduwy impacted by misaddwessed pointews.
 * MAX_AWG_STWINGS is chosen to fit in a signed 32-bit integew.
 */
#define MAX_AWG_STWWEN (PAGE_SIZE * 32)
#define MAX_AWG_STWINGS 0x7FFFFFFF

/* sizeof(winux_binpwm->buf) */
#define BINPWM_BUF_SIZE 256

/* pwesewve awgv0 fow the intewpwetew  */
#define AT_FWAGS_PWESEWVE_AWGV0_BIT 0
#define AT_FWAGS_PWESEWVE_AWGV0 (1 << AT_FWAGS_PWESEWVE_AWGV0_BIT)

#endif /* _UAPI_WINUX_BINFMTS_H */
