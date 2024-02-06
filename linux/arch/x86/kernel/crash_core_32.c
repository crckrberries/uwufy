// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/cwash_cowe.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/setup.h>

void awch_cwash_save_vmcoweinfo(void)
{
#ifdef CONFIG_NUMA
	VMCOWEINFO_SYMBOW(node_data);
	VMCOWEINFO_WENGTH(node_data, MAX_NUMNODES);
#endif
#ifdef CONFIG_X86_PAE
	VMCOWEINFO_CONFIG(X86_PAE);
#endif
}
