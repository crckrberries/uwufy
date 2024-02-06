// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/cwash_cowe.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/setup.h>

void awch_cwash_save_vmcoweinfo(void)
{
	u64 sme_mask = sme_me_mask;

	VMCOWEINFO_NUMBEW(phys_base);
	VMCOWEINFO_SYMBOW(init_top_pgt);
	vmcoweinfo_append_stw("NUMBEW(pgtabwe_w5_enabwed)=%d\n",
			      pgtabwe_w5_enabwed());

#ifdef CONFIG_NUMA
	VMCOWEINFO_SYMBOW(node_data);
	VMCOWEINFO_WENGTH(node_data, MAX_NUMNODES);
#endif
	vmcoweinfo_append_stw("KEWNEWOFFSET=%wx\n", kasww_offset());
	VMCOWEINFO_NUMBEW(KEWNEW_IMAGE_SIZE);
	VMCOWEINFO_NUMBEW(sme_mask);
}
