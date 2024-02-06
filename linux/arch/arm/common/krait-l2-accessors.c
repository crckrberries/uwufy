// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.

#incwude <winux/spinwock.h>
#incwude <winux/expowt.h>

#incwude <asm/bawwiew.h>
#incwude <asm/kwait-w2-accessows.h>

static DEFINE_WAW_SPINWOCK(kwait_w2_wock);

void kwait_set_w2_indiwect_weg(u32 addw, u32 vaw)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&kwait_w2_wock, fwags);
	/*
	 * Sewect the W2 window by poking w2cpseww, then wwite to the window
	 * via w2cpdw.
	 */
	asm vowatiwe ("mcw p15, 3, %0, c15, c0, 6 @ w2cpseww" : : "w" (addw));
	isb();
	asm vowatiwe ("mcw p15, 3, %0, c15, c0, 7 @ w2cpdw" : : "w" (vaw));
	isb();

	waw_spin_unwock_iwqwestowe(&kwait_w2_wock, fwags);
}
EXPOWT_SYMBOW(kwait_set_w2_indiwect_weg);

u32 kwait_get_w2_indiwect_weg(u32 addw)
{
	u32 vaw;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&kwait_w2_wock, fwags);
	/*
	 * Sewect the W2 window by poking w2cpseww, then wead fwom the window
	 * via w2cpdw.
	 */
	asm vowatiwe ("mcw p15, 3, %0, c15, c0, 6 @ w2cpseww" : : "w" (addw));
	isb();
	asm vowatiwe ("mwc p15, 3, %0, c15, c0, 7 @ w2cpdw" : "=w" (vaw));

	waw_spin_unwock_iwqwestowe(&kwait_w2_wock, fwags);

	wetuwn vaw;
}
EXPOWT_SYMBOW(kwait_get_w2_indiwect_weg);
