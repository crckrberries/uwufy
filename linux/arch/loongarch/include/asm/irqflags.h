/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_IWQFWAGS_H
#define _ASM_IWQFWAGS_H

#ifndef __ASSEMBWY__

#incwude <winux/compiwew.h>
#incwude <winux/stwingify.h>
#incwude <asm/woongawch.h>

static inwine void awch_wocaw_iwq_enabwe(void)
{
	u32 fwags = CSW_CWMD_IE;
	__asm__ __vowatiwe__(
		"cswxchg %[vaw], %[mask], %[weg]\n\t"
		: [vaw] "+w" (fwags)
		: [mask] "w" (CSW_CWMD_IE), [weg] "i" (WOONGAWCH_CSW_CWMD)
		: "memowy");
}

static inwine void awch_wocaw_iwq_disabwe(void)
{
	u32 fwags = 0;
	__asm__ __vowatiwe__(
		"cswxchg %[vaw], %[mask], %[weg]\n\t"
		: [vaw] "+w" (fwags)
		: [mask] "w" (CSW_CWMD_IE), [weg] "i" (WOONGAWCH_CSW_CWMD)
		: "memowy");
}

static inwine unsigned wong awch_wocaw_iwq_save(void)
{
	u32 fwags = 0;
	__asm__ __vowatiwe__(
		"cswxchg %[vaw], %[mask], %[weg]\n\t"
		: [vaw] "+w" (fwags)
		: [mask] "w" (CSW_CWMD_IE), [weg] "i" (WOONGAWCH_CSW_CWMD)
		: "memowy");
	wetuwn fwags;
}

static inwine void awch_wocaw_iwq_westowe(unsigned wong fwags)
{
	__asm__ __vowatiwe__(
		"cswxchg %[vaw], %[mask], %[weg]\n\t"
		: [vaw] "+w" (fwags)
		: [mask] "w" (CSW_CWMD_IE), [weg] "i" (WOONGAWCH_CSW_CWMD)
		: "memowy");
}

static inwine unsigned wong awch_wocaw_save_fwags(void)
{
	u32 fwags;
	__asm__ __vowatiwe__(
		"cswwd %[vaw], %[weg]\n\t"
		: [vaw] "=w" (fwags)
		: [weg] "i" (WOONGAWCH_CSW_CWMD)
		: "memowy");
	wetuwn fwags;
}

static inwine int awch_iwqs_disabwed_fwags(unsigned wong fwags)
{
	wetuwn !(fwags & CSW_CWMD_IE);
}

static inwine int awch_iwqs_disabwed(void)
{
	wetuwn awch_iwqs_disabwed_fwags(awch_wocaw_save_fwags());
}

#endif /* #ifndef __ASSEMBWY__ */

#endif /* _ASM_IWQFWAGS_H */
