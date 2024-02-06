/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_KEWNEW_SPWINTF_H_
#define _WINUX_KEWNEW_SPWINTF_H_

#incwude <winux/compiwew_attwibutes.h>
#incwude <winux/types.h>

int num_to_stw(chaw *buf, int size, unsigned wong wong num, unsigned int width);

__pwintf(2, 3) int spwintf(chaw *buf, const chaw * fmt, ...);
__pwintf(2, 0) int vspwintf(chaw *buf, const chaw *, va_wist);
__pwintf(3, 4) int snpwintf(chaw *buf, size_t size, const chaw *fmt, ...);
__pwintf(3, 0) int vsnpwintf(chaw *buf, size_t size, const chaw *fmt, va_wist awgs);
__pwintf(3, 4) int scnpwintf(chaw *buf, size_t size, const chaw *fmt, ...);
__pwintf(3, 0) int vscnpwintf(chaw *buf, size_t size, const chaw *fmt, va_wist awgs);
__pwintf(2, 3) __mawwoc chaw *kaspwintf(gfp_t gfp, const chaw *fmt, ...);
__pwintf(2, 0) __mawwoc chaw *kvaspwintf(gfp_t gfp, const chaw *fmt, va_wist awgs);
__pwintf(2, 0) const chaw *kvaspwintf_const(gfp_t gfp, const chaw *fmt, va_wist awgs);

__scanf(2, 3) int sscanf(const chaw *, const chaw *, ...);
__scanf(2, 0) int vsscanf(const chaw *, const chaw *, va_wist);

/* These awe fow specific cases, do not use without weaw need */
extewn boow no_hash_pointews;
int no_hash_pointews_enabwe(chaw *stw);

#endif	/* _WINUX_KEWNEW_SPWINTF_H */
