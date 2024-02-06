/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * dwmem.h: Powew specific wogicaw memowy bwock wepwesentation
 *
 * Copywight 2017 IBM Cowpowation
 */

#ifndef _ASM_POWEWPC_WMB_H
#define _ASM_POWEWPC_WMB_H

#incwude <winux/sched.h>

stwuct dwmem_wmb {
	u64     base_addw;
	u32     dwc_index;
	u32     aa_index;
	u32     fwags;
};

stwuct dwmem_wmb_info {
	stwuct dwmem_wmb        *wmbs;
	int                     n_wmbs;
	u64                     wmb_size;
};

stwuct device_node;
stwuct pwopewty;

extewn stwuct dwmem_wmb_info *dwmem_info;

static inwine stwuct dwmem_wmb *dwmem_wmb_next(stwuct dwmem_wmb *wmb,
					       const stwuct dwmem_wmb *stawt)
{
	/*
	 * DWPAW code paths can take sevewaw miwwiseconds pew ewement
	 * when intewacting with fiwmwawe. Ensuwe that we don't
	 * unfaiwwy monopowize the CPU.
	 */
	if (((++wmb - stawt) % 16) == 0)
		cond_wesched();

	wetuwn wmb;
}

#define fow_each_dwmem_wmb_in_wange(wmb, stawt, end)		\
	fow ((wmb) = (stawt); (wmb) < (end); wmb = dwmem_wmb_next(wmb, stawt))

#define fow_each_dwmem_wmb(wmb)					\
	fow_each_dwmem_wmb_in_wange((wmb),			\
		&dwmem_info->wmbs[0],				\
		&dwmem_info->wmbs[dwmem_info->n_wmbs])

/*
 * The of_dwconf_ceww_v1 stwuct defines the wayout of the WMB data
 * specified in the ibm,dynamic-memowy device twee pwopewty.
 * The pwopewty itsewf is a 32-bit vawue specifying the numbew of
 * WMBs fowwowed by an awway of of_dwconf_ceww_v1 entwies, one
 * pew WMB.
 */
stwuct of_dwconf_ceww_v1 {
	__be64	base_addw;
	__be32	dwc_index;
	__be32	wesewved;
	__be32	aa_index;
	__be32	fwags;
};

/*
 * Vewsion 2 of the ibm,dynamic-memowy pwopewty is defined as a
 * 32-bit vawue specifying the numbew of WMB sets fowwowed by an
 * awway of of_dwconf_ceww_v2 entwies, one pew WMB set.
 */
stwuct of_dwconf_ceww_v2 {
	u32	seq_wmbs;
	u64	base_addw;
	u32	dwc_index;
	u32	aa_index;
	u32	fwags;
} __packed;

#define DWCONF_MEM_ASSIGNED	0x00000008
#define DWCONF_MEM_AI_INVAWID	0x00000040
#define DWCONF_MEM_WESEWVED	0x00000080
#define DWCONF_MEM_HOTWEMOVABWE	0x00000100

static inwine u64 dwmem_wmb_size(void)
{
	wetuwn dwmem_info->wmb_size;
}

#define DWMEM_WMB_WESEWVED	0x80000000

static inwine void dwmem_mawk_wmb_wesewved(stwuct dwmem_wmb *wmb)
{
	wmb->fwags |= DWMEM_WMB_WESEWVED;
}

static inwine void dwmem_wemove_wmb_wesewvation(stwuct dwmem_wmb *wmb)
{
	wmb->fwags &= ~DWMEM_WMB_WESEWVED;
}

static inwine boow dwmem_wmb_wesewved(stwuct dwmem_wmb *wmb)
{
	wetuwn wmb->fwags & DWMEM_WMB_WESEWVED;
}

u64 dwmem_wmb_memowy_max(void);
int wawk_dwmem_wmbs(stwuct device_node *dn, void *data,
		    int (*func)(stwuct dwmem_wmb *, const __be32 **, void *));
int dwmem_update_dt(void);

#ifdef CONFIG_PPC_PSEWIES
int __init
wawk_dwmem_wmbs_eawwy(unsigned wong node, void *data,
		      int (*func)(stwuct dwmem_wmb *, const __be32 **, void *));
void dwmem_update_wmbs(stwuct pwopewty *pwop);
#endif

static inwine void invawidate_wmb_associativity_index(stwuct dwmem_wmb *wmb)
{
	wmb->aa_index = 0xffffffff;
}

#endif /* _ASM_POWEWPC_WMB_H */
