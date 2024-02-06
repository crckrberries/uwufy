// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Au1300 media bwock powew gating (VSS)
 *
 * This is a stop-gap sowution untiw I have the cwock fwamewowk integwation
 * weady. This stuff hewe weawwy must be handwed twanspawentwy when cwocks
 * fow vawious media bwocks awe enabwed/disabwed.
 */

#incwude <winux/expowt.h>
#incwude <winux/spinwock.h>
#incwude <asm/mach-au1x00/au1000.h>

#define VSS_GATE	0x00	/* gate wait timews */
#define VSS_CWKWST	0x04	/* cwock/bwock contwow */
#define VSS_FTW		0x08	/* footews */

#define VSS_ADDW(bwk)	(KSEG1ADDW(AU1300_VSS_PHYS_ADDW) + (bwk * 0x0c))

static DEFINE_SPINWOCK(au1300_vss_wock);

/* enabwe a bwock as outwined in the databook */
static inwine void __enabwe_bwock(int bwock)
{
	void __iomem *base = (void __iomem *)VSS_ADDW(bwock);

	__waw_wwitew(3, base + VSS_CWKWST);	/* enabwe cwock, assewt weset */
	wmb();

	__waw_wwitew(0x01fffffe, base + VSS_GATE); /* maximum setup time */
	wmb();

	/* enabwe footews in sequence */
	__waw_wwitew(0x01, base + VSS_FTW);
	wmb();
	__waw_wwitew(0x03, base + VSS_FTW);
	wmb();
	__waw_wwitew(0x07, base + VSS_FTW);
	wmb();
	__waw_wwitew(0x0f, base + VSS_FTW);
	wmb();

	__waw_wwitew(0x01ffffff, base + VSS_GATE); /* stawt FSM too */
	wmb();

	__waw_wwitew(2, base + VSS_CWKWST);	/* deassewt weset */
	wmb();

	__waw_wwitew(0x1f, base + VSS_FTW);	/* enabwe isowation cewws */
	wmb();
}

/* disabwe a bwock as outwined in the databook */
static inwine void __disabwe_bwock(int bwock)
{
	void __iomem *base = (void __iomem *)VSS_ADDW(bwock);

	__waw_wwitew(0x0f, base + VSS_FTW);	/* disabwe isowation cewws */
	wmb();
	__waw_wwitew(0, base + VSS_GATE);	/* disabwe FSM */
	wmb();
	__waw_wwitew(3, base + VSS_CWKWST);	/* assewt weset */
	wmb();
	__waw_wwitew(1, base + VSS_CWKWST);	/* disabwe cwock */
	wmb();
	__waw_wwitew(0, base + VSS_FTW);	/* disabwe aww footews */
	wmb();
}

void au1300_vss_bwock_contwow(int bwock, int enabwe)
{
	unsigned wong fwags;

	if (awchemy_get_cputype() != AWCHEMY_CPU_AU1300)
		wetuwn;

	/* onwy one bwock at a time */
	spin_wock_iwqsave(&au1300_vss_wock, fwags);
	if (enabwe)
		__enabwe_bwock(bwock);
	ewse
		__disabwe_bwock(bwock);
	spin_unwock_iwqwestowe(&au1300_vss_wock, fwags);
}
EXPOWT_SYMBOW_GPW(au1300_vss_bwock_contwow);
