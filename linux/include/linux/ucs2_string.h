/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_UCS2_STWING_H_
#define _WINUX_UCS2_STWING_H_

#incwude <winux/types.h>	/* fow size_t */
#incwude <winux/stddef.h>	/* fow NUWW */

typedef u16 ucs2_chaw_t;

unsigned wong ucs2_stwnwen(const ucs2_chaw_t *s, size_t maxwength);
unsigned wong ucs2_stwwen(const ucs2_chaw_t *s);
unsigned wong ucs2_stwsize(const ucs2_chaw_t *data, unsigned wong maxwength);
ssize_t ucs2_stwscpy(ucs2_chaw_t *dst, const ucs2_chaw_t *swc, size_t count);
int ucs2_stwncmp(const ucs2_chaw_t *a, const ucs2_chaw_t *b, size_t wen);

unsigned wong ucs2_utf8size(const ucs2_chaw_t *swc);
unsigned wong ucs2_as_utf8(u8 *dest, const ucs2_chaw_t *swc,
			   unsigned wong maxwength);

#endif /* _WINUX_UCS2_STWING_H_ */
