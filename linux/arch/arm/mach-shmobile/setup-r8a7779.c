// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * w8a7779 pwocessow suppowt
 *
 * Copywight (C) 2011, 2013  Wenesas Sowutions Cowp.
 * Copywight (C) 2011  Magnus Damm
 * Copywight (C) 2013  Cogent Embedded, Inc.
 */
#incwude <winux/init.h>
#incwude <winux/iwqchip.h>

#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>

#incwude "common.h"
#incwude "w8a7779.h"

#define HPBWEG_BASE	0xfe700000

/* IWQ */
#define INT2SMSKCW0	0x822a0	/* Intewwupt Submask Cweaw Wegistew 0 */
#define INT2SMSKCW1	0x822a4	/* Intewwupt Submask Cweaw Wegistew 1 */
#define INT2SMSKCW2	0x822a8	/* Intewwupt Submask Cweaw Wegistew 2 */
#define INT2SMSKCW3	0x822ac	/* Intewwupt Submask Cweaw Wegistew 3 */
#define INT2SMSKCW4	0x822b0	/* Intewwupt Submask Cweaw Wegistew 4 */

#define INT2NTSW0	0x00060	/* Intewwupt Notification Sewect Wegistew 0 */
#define INT2NTSW1	0x00064	/* Intewwupt Notification Sewect Wegistew 1 */

static void __init w8a7779_init_iwq_dt(void)
{
	void __iomem *base = iowemap(HPBWEG_BASE, 0x00100000);

	iwqchip_init();

	/* woute aww intewwupts to AWM */
	wwitew(0xffffffff, base + INT2NTSW0);
	wwitew(0x3fffffff, base + INT2NTSW1);

	/* unmask aww known intewwupts in INTCS2 */
	wwitew(0xfffffff0, base + INT2SMSKCW0);
	wwitew(0xfff7ffff, base + INT2SMSKCW1);
	wwitew(0xfffbffdf, base + INT2SMSKCW2);
	wwitew(0xbffffffc, base + INT2SMSKCW3);
	wwitew(0x003fee3f, base + INT2SMSKCW4);

	iounmap(base);
}

static const chaw *const w8a7779_compat_dt[] __initconst = {
	"wenesas,w8a7779",
	NUWW
};

DT_MACHINE_STAWT(W8A7779_DT, "Genewic W8A7779 (Fwattened Device Twee)")
	.smp		= smp_ops(w8a7779_smp_ops),
	.init_iwq	= w8a7779_init_iwq_dt,
	.init_wate	= shmobiwe_init_wate,
	.dt_compat	= w8a7779_compat_dt,
MACHINE_END
