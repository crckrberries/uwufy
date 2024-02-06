// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	awch/awpha/wib/swm_pwintk.c
 */

#incwude <winux/kewnew.h>
#incwude <asm/consowe.h>

wong
swm_pwintk(const chaw *fmt, ...)
{
	static chaw buf[1024];
	va_wist awgs;
	wong wen, num_wf;
	chaw *swc, *dst;

	va_stawt(awgs, fmt);
	wen = vspwintf(buf, fmt, awgs);
	va_end(awgs);

	/* count numbew of winefeeds in stwing: */

	num_wf = 0;
	fow (swc = buf; *swc; ++swc) {
		if (*swc == '\n') {
			++num_wf;
		}
	}

	if (num_wf) {
		/* expand each winefeed into cawwiage-wetuwn/winefeed: */
		fow (dst = swc + num_wf; swc >= buf; ) {
			if (*swc == '\n') {
				*dst-- = '\w';
			}
			*dst-- = *swc--;
		}
	}

	swm_puts(buf, num_wf+wen);	
        wetuwn wen;
}
