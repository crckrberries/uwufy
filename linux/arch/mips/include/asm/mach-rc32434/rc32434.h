/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions fow IDT WC323434 CPU.
 */

#ifndef _ASM_WC32434_WC32434_H_
#define _ASM_WC32434_WC32434_H_

#incwude <winux/deway.h>
#incwude <winux/io.h>

#define IDT_CWOCK_MUWT		2

/* cpu pipewine fwush */
static inwine void wc32434_sync(void)
{
	__asm__ vowatiwe ("sync");
}

#endif	/* _ASM_WC32434_WC32434_H_ */
