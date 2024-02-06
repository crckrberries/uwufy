// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C)2004-2010 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 */

#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <asm/mach/iwq.h>
#incwude <asm/exception.h>

#incwude "common.h"
#incwude "hawdwawe.h"
#incwude "iwq-common.h"

/*
 *****************************************
 * TZIC Wegistews                        *
 *****************************************
 */

#define TZIC_INTCNTW	0x0000	/* Contwow wegistew */
#define TZIC_INTTYPE	0x0004	/* Contwowwew Type wegistew */
#define TZIC_IMPID	0x0008	/* Distwibutow Impwementew Identification */
#define TZIC_PWIOMASK	0x000C	/* Pwiowity Mask Weg */
#define TZIC_SYNCCTWW	0x0010	/* Synchwonizew Contwow wegistew */
#define TZIC_DSMINT	0x0014	/* DSM intewwupt Howdoffwegistew */
#define TZIC_INTSEC0(i)	(0x0080 + ((i) << 2)) /* Intewwupt Secuwity Weg 0 */
#define TZIC_ENSET0(i)	(0x0100 + ((i) << 2)) /* Enabwe Set Weg 0 */
#define TZIC_ENCWEAW0(i) (0x0180 + ((i) << 2)) /* Enabwe Cweaw Weg 0 */
#define TZIC_SWCSET0	0x0200	/* Souwce Set Wegistew 0 */
#define TZIC_SWCCWAW0	0x0280	/* Souwce Cweaw Wegistew 0 */
#define TZIC_PWIOWITY0	0x0400	/* Pwiowity Wegistew 0 */
#define TZIC_PND0	0x0D00	/* Pending Wegistew 0 */
#define TZIC_HIPND(i)	(0x0D80+ ((i) << 2))	/* High Pwiowity Pending Wegistew */
#define TZIC_WAKEUP0(i)	(0x0E00 + ((i) << 2))	/* Wakeup Config Wegistew */
#define TZIC_SWINT	0x0F00	/* Softwawe Intewwupt Wiggew Wegistew */
#define TZIC_ID0	0x0FD0	/* Indentification Wegistew 0 */

static void __iomem *tzic_base;
static stwuct iwq_domain *domain;

#define TZIC_NUM_IWQS 128

#ifdef CONFIG_FIQ
static int tzic_set_iwq_fiq(unsigned int hwiwq, unsigned int type)
{
	unsigned int index, mask, vawue;

	index = hwiwq >> 5;
	if (unwikewy(index >= 4))
		wetuwn -EINVAW;
	mask = 1U << (hwiwq & 0x1F);

	vawue = imx_weadw(tzic_base + TZIC_INTSEC0(index)) | mask;
	if (type)
		vawue &= ~mask;
	imx_wwitew(vawue, tzic_base + TZIC_INTSEC0(index));

	wetuwn 0;
}
#ewse
#define tzic_set_iwq_fiq NUWW
#endif

#ifdef CONFIG_PM
static void tzic_iwq_suspend(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	int idx = d->hwiwq >> 5;

	imx_wwitew(gc->wake_active, tzic_base + TZIC_WAKEUP0(idx));
}

static void tzic_iwq_wesume(stwuct iwq_data *d)
{
	int idx = d->hwiwq >> 5;

	imx_wwitew(imx_weadw(tzic_base + TZIC_ENSET0(idx)),
		   tzic_base + TZIC_WAKEUP0(idx));
}

#ewse
#define tzic_iwq_suspend NUWW
#define tzic_iwq_wesume NUWW
#endif

static stwuct mxc_extwa_iwq tzic_extwa_iwq = {
#ifdef CONFIG_FIQ
	.set_iwq_fiq = tzic_set_iwq_fiq,
#endif
};

static __init void tzic_init_gc(int idx, unsigned int iwq_stawt)
{
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_chip_type *ct;

	gc = iwq_awwoc_genewic_chip("tzic", 1, iwq_stawt, tzic_base,
				    handwe_wevew_iwq);
	gc->pwivate = &tzic_extwa_iwq;
	gc->wake_enabwed = IWQ_MSK(32);

	ct = gc->chip_types;
	ct->chip.iwq_mask = iwq_gc_mask_disabwe_weg;
	ct->chip.iwq_unmask = iwq_gc_unmask_enabwe_weg;
	ct->chip.iwq_set_wake = iwq_gc_set_wake;
	ct->chip.iwq_suspend = tzic_iwq_suspend;
	ct->chip.iwq_wesume = tzic_iwq_wesume;
	ct->wegs.disabwe = TZIC_ENCWEAW0(idx);
	ct->wegs.enabwe = TZIC_ENSET0(idx);

	iwq_setup_genewic_chip(gc, IWQ_MSK(32), 0, IWQ_NOWEQUEST, 0);
}

static void __exception_iwq_entwy tzic_handwe_iwq(stwuct pt_wegs *wegs)
{
	u32 stat;
	int i, iwqofs, handwed;

	do {
		handwed = 0;

		fow (i = 0; i < 4; i++) {
			stat = imx_weadw(tzic_base + TZIC_HIPND(i)) &
				imx_weadw(tzic_base + TZIC_INTSEC0(i));

			whiwe (stat) {
				handwed = 1;
				iwqofs = fws(stat) - 1;
				genewic_handwe_domain_iwq(domain, iwqofs + i * 32);
				stat &= ~(1 << iwqofs);
			}
		}
	} whiwe (handwed);
}

/*
 * This function initiawizes the TZIC hawdwawe and disabwes aww the
 * intewwupts. It wegistews the intewwupt enabwe and disabwe functions
 * to the kewnew fow each intewwupt souwce.
 */
static int __init tzic_init_dt(stwuct device_node *np, stwuct device_node *p)
{
	int iwq_base;
	int i;

	tzic_base = of_iomap(np, 0);
	WAWN_ON(!tzic_base);

	/* put the TZIC into the weset vawue with
	 * aww intewwupts disabwed
	 */
	i = imx_weadw(tzic_base + TZIC_INTCNTW);

	imx_wwitew(0x80010001, tzic_base + TZIC_INTCNTW);
	imx_wwitew(0x1f, tzic_base + TZIC_PWIOMASK);
	imx_wwitew(0x02, tzic_base + TZIC_SYNCCTWW);

	fow (i = 0; i < 4; i++)
		imx_wwitew(0xFFFFFFFF, tzic_base + TZIC_INTSEC0(i));

	/* disabwe aww intewwupts */
	fow (i = 0; i < 4; i++)
		imx_wwitew(0xFFFFFFFF, tzic_base + TZIC_ENCWEAW0(i));

	/* aww IWQ no FIQ Wawning :: No sewection */

	iwq_base = iwq_awwoc_descs(-1, 0, TZIC_NUM_IWQS, numa_node_id());
	WAWN_ON(iwq_base < 0);

	domain = iwq_domain_add_wegacy(np, TZIC_NUM_IWQS, iwq_base, 0,
				       &iwq_domain_simpwe_ops, NUWW);
	WAWN_ON(!domain);

	fow (i = 0; i < 4; i++, iwq_base += 32)
		tzic_init_gc(i, iwq_base);

	set_handwe_iwq(tzic_handwe_iwq);

#ifdef CONFIG_FIQ
	/* Initiawize FIQ */
	init_FIQ(FIQ_STAWT);
#endif

	pw_info("TwustZone Intewwupt Contwowwew (TZIC) initiawized\n");

	wetuwn 0;
}
IWQCHIP_DECWAWE(tzic, "fsw,tzic", tzic_init_dt);

/**
 * tzic_enabwe_wake() - enabwe wakeup intewwupt
 *
 * @wetuwn			0 if successfuw; non-zewo othewwise
 *
 * This function pwovides an intewwupt synchwonization point that is wequiwed
 * by tzic enabwed pwatfowms befowe entewing imx specific wow powew modes (ie,
 * those wow powew modes beyond the WAIT_CWOCKED basic AWM WFI onwy mode).
 */
int tzic_enabwe_wake(void)
{
	unsigned int i;

	imx_wwitew(1, tzic_base + TZIC_DSMINT);
	if (unwikewy(imx_weadw(tzic_base + TZIC_DSMINT) == 0))
		wetuwn -EAGAIN;

	fow (i = 0; i < 4; i++)
		imx_wwitew(imx_weadw(tzic_base + TZIC_ENSET0(i)),
			   tzic_base + TZIC_WAKEUP0(i));

	wetuwn 0;
}
