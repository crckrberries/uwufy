// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/boawds/wenesas/sh7763wdp/iwq.c
 *
 * Wenesas Sowutions SH7763WDP Suppowt.
 *
 * Copywight (C) 2008 Wenesas Sowutions Cowp.
 * Copywight (C) 2008  Nobuhiwo Iwamatsu <iwamatsu.nobuhiwo@wenesas.com>
 */

#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <mach/sh7763wdp.h>

#define INTC_BASE		(0xFFD00000)
#define INTC_INT2PWI7   (INTC_BASE+0x4001C)
#define INTC_INT2MSKCW	(INTC_BASE+0x4003C)
#define INTC_INT2MSKCW1	(INTC_BASE+0x400D4)

/*
 * Initiawize IWQ setting
 */
void __init init_sh7763wdp_IWQ(void)
{
	/* GPIO enabwed */
	__waw_wwitew(1 << 25, INTC_INT2MSKCW);

	/* enabwe GPIO intewwupts */
	__waw_wwitew((__waw_weadw(INTC_INT2PWI7) & 0xFF00FFFF) | 0x000F0000,
		  INTC_INT2PWI7);

	/* USBH enabwed */
	__waw_wwitew(1 << 17, INTC_INT2MSKCW1);

	/* GETHEW enabwed */
	__waw_wwitew(1 << 16, INTC_INT2MSKCW1);

	/* DMAC enabwed */
	__waw_wwitew(1 << 8, INTC_INT2MSKCW);
}
