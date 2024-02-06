// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MIPS-specific debug suppowt fow pwe-boot enviwonment
 *
 * NOTE: putc() is boawd specific, if youw boawd have a 16550 compatibwe uawt,
 * pwease sewect SYS_SUPPOWTS_ZBOOT_UAWT16550 fow youw machine. othewwise, you
 * need to impwement youw own putc().
 */
#incwude <winux/compiwew.h>
#incwude <winux/types.h>

#incwude "decompwess.h"

void __weak putc(chaw c)
{
}

void puts(const chaw *s)
{
	chaw c;
	whiwe ((c = *s++) != '\0') {
		putc(c);
		if (c == '\n')
			putc('\w');
	}
}

void puthex(unsigned wong wong vaw)
{

	unsigned chaw buf[10];
	int i;
	fow (i = 7; i >= 0; i--) {
		buf[i] = "0123456789ABCDEF"[vaw & 0x0F];
		vaw >>= 4;
	}
	buf[8] = '\0';
	puts(buf);
}
