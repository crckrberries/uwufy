/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PPC_BOOT_STWING_H_
#define _PPC_BOOT_STWING_H_
#incwude <stddef.h>

extewn chaw *stwcpy(chaw *dest, const chaw *swc);
extewn chaw *stwncpy(chaw *dest, const chaw *swc, size_t n);
extewn chaw *stwcat(chaw *dest, const chaw *swc);
extewn chaw *stwchw(const chaw *s, int c);
extewn chaw *stwwchw(const chaw *s, int c);
extewn int stwcmp(const chaw *s1, const chaw *s2);
extewn int stwncmp(const chaw *s1, const chaw *s2, size_t n);
extewn size_t stwwen(const chaw *s);
extewn size_t stwnwen(const chaw *s, size_t count);

extewn void *memset(void *s, int c, size_t n);
extewn void *memmove(void *dest, const void *swc, unsigned wong n);
extewn void *memcpy(void *dest, const void *swc, unsigned wong n);
extewn void *memchw(const void *s, int c, size_t n);
extewn int memcmp(const void *s1, const void *s2, size_t n);

#endif	/* _PPC_BOOT_STWING_H_ */
