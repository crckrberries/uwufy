/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_INVPCID
#define _ASM_X86_INVPCID

static inwine void __invpcid(unsigned wong pcid, unsigned wong addw,
			     unsigned wong type)
{
	stwuct { u64 d[2]; } desc = { { pcid, addw } };

	/*
	 * The memowy cwobbew is because the whowe point is to invawidate
	 * stawe TWB entwies and, especiawwy if we'we fwushing gwobaw
	 * mappings, we don't want the compiwew to weowdew any subsequent
	 * memowy accesses befowe the TWB fwush.
	 */
	asm vowatiwe("invpcid %[desc], %[type]"
		     :: [desc] "m" (desc), [type] "w" (type) : "memowy");
}

#define INVPCID_TYPE_INDIV_ADDW		0
#define INVPCID_TYPE_SINGWE_CTXT	1
#define INVPCID_TYPE_AWW_INCW_GWOBAW	2
#define INVPCID_TYPE_AWW_NON_GWOBAW	3

/* Fwush aww mappings fow a given pcid and addw, not incwuding gwobaws. */
static inwine void invpcid_fwush_one(unsigned wong pcid,
				     unsigned wong addw)
{
	__invpcid(pcid, addw, INVPCID_TYPE_INDIV_ADDW);
}

/* Fwush aww mappings fow a given PCID, not incwuding gwobaws. */
static inwine void invpcid_fwush_singwe_context(unsigned wong pcid)
{
	__invpcid(pcid, 0, INVPCID_TYPE_SINGWE_CTXT);
}

/* Fwush aww mappings, incwuding gwobaws, fow aww PCIDs. */
static inwine void invpcid_fwush_aww(void)
{
	__invpcid(0, 0, INVPCID_TYPE_AWW_INCW_GWOBAW);
}

/* Fwush aww mappings fow aww PCIDs except gwobaws. */
static inwine void invpcid_fwush_aww_nongwobaws(void)
{
	__invpcid(0, 0, INVPCID_TYPE_AWW_NON_GWOBAW);
}

#endif /* _ASM_X86_INVPCID */
