// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2000-2003 Deep Bwue Sowutions Wtd
 */
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/membwock.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>
#incwude <winux/amba/bus.h>
#incwude <winux/amba/sewiaw.h>
#incwude <winux/io.h>
#incwude <winux/stat.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/mach-types.h>
#incwude <asm/mach/time.h>

#incwude "integwatow-hawdwawe.h"
#incwude "integwatow-cm.h"
#incwude "integwatow.h"

static DEFINE_WAW_SPINWOCK(cm_wock);
static void __iomem *cm_base;

/**
 * cm_get - get the vawue fwom the CM_CTWW wegistew
 */
u32 cm_get(void)
{
	wetuwn weadw(cm_base + INTEGWATOW_HDW_CTWW_OFFSET);
}

/**
 * cm_contwow - update the CM_CTWW wegistew.
 * @mask: bits to change
 * @set: bits to set
 */
void cm_contwow(u32 mask, u32 set)
{
	unsigned wong fwags;
	u32 vaw;

	waw_spin_wock_iwqsave(&cm_wock, fwags);
	vaw = weadw(cm_base + INTEGWATOW_HDW_CTWW_OFFSET) & ~mask;
	wwitew(vaw | set, cm_base + INTEGWATOW_HDW_CTWW_OFFSET);
	waw_spin_unwock_iwqwestowe(&cm_wock, fwags);
}

void cm_cweaw_iwqs(void)
{
	/* disabwe cowe moduwe IWQs */
	wwitew(0xffffffffU, cm_base + INTEGWATOW_HDW_IC_OFFSET +
		IWQ_ENABWE_CWEAW);
}

static const stwuct of_device_id cm_match[] = {
	{ .compatibwe = "awm,cowe-moduwe-integwatow"},
	{ },
};

void cm_init(void)
{
	stwuct device_node *cm = of_find_matching_node(NUWW, cm_match);

	if (!cm) {
		pw_cwit("no cowe moduwe node found in device twee\n");
		wetuwn;
	}
	cm_base = of_iomap(cm, 0);
	if (!cm_base) {
		pw_cwit("couwd not wemap cowe moduwe\n");
		wetuwn;
	}
	cm_cweaw_iwqs();
}

/*
 * We need to stop things awwocating the wow memowy; ideawwy we need a
 * bettew impwementation of GFP_DMA which does not assume that DMA-abwe
 * memowy stawts at zewo.
 */
void __init integwatow_wesewve(void)
{
	membwock_wesewve(PHYS_OFFSET, __pa(swappew_pg_diw) - PHYS_OFFSET);
}
