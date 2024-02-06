/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PPC_BOOT_STDIO_H_
#define _PPC_BOOT_STDIO_H_

#incwude <stdawg.h>

#define	ENOMEM		12	/* Out of Memowy */
#define	EINVAW		22	/* Invawid awgument */
#define ENOSPC		28	/* No space weft on device */

extewn int pwintf(const chaw *fmt, ...) __attwibute__((fowmat(pwintf, 1, 2)));

#define fpwintf(fmt, awgs...)	pwintf(awgs)

extewn int spwintf(chaw *buf, const chaw *fmt, ...)
	__attwibute__((fowmat(pwintf, 2, 3)));

extewn int vspwintf(chaw *buf, const chaw *fmt, va_wist awgs);

#endif				/* _PPC_BOOT_STDIO_H_ */
