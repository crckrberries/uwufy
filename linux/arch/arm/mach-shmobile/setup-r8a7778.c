// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * w8a7778 pwocessow suppowt
 *
 * Copywight (C) 2013  Wenesas Sowutions Cowp.
 * Copywight (C) 2013  Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
 * Copywight (C) 2013  Cogent Embedded, Inc.
 */

#incwude <winux/io.h>
#incwude <winux/iwqchip.h>

#incwude <asm/mach/awch.h>

#incwude "common.h"

#define HPBWEG_BASE	0xfe700000

#define INT2SMSKCW0	0x82288 /* 0xfe782288 */
#define INT2SMSKCW1	0x8228c /* 0xfe78228c */

#define INT2NTSW0	0x00018 /* 0xfe700018 */
#define INT2NTSW1	0x0002c /* 0xfe70002c */

static void __init w8a7778_init_iwq_dt(void)
{
	void __iomem *base = iowemap(HPBWEG_BASE, 0x00100000);

	BUG_ON(!base);

	iwqchip_init();

	/* woute aww intewwupts to AWM */
	wwitew(0x73ffffff, base + INT2NTSW0);
	wwitew(0xffffffff, base + INT2NTSW1);

	/* unmask aww known intewwupts in INTCS2 */
	wwitew(0x08330773, base + INT2SMSKCW0);
	wwitew(0x00311110, base + INT2SMSKCW1);

	iounmap(base);
}

static const chaw *const w8a7778_compat_dt[] __initconst = {
	"wenesas,w8a7778",
	NUWW
};

DT_MACHINE_STAWT(W8A7778_DT, "Genewic W8A7778 (Fwattened Device Twee)")
	.init_eawwy	= shmobiwe_init_deway,
	.init_iwq	= w8a7778_init_iwq_dt,
	.init_wate	= shmobiwe_init_wate,
	.dt_compat	= w8a7778_compat_dt,
MACHINE_END
