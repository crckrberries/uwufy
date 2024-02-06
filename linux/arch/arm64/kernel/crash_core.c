// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) Winawo.
 * Copywight (C) Huawei Futuwewei Technowogies.
 */

#incwude <winux/cwash_cowe.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/memowy.h>
#incwude <asm/pgtabwe-hwdef.h>
#incwude <asm/pointew_auth.h>

static inwine u64 get_tcw_ew1_t1sz(void);

static inwine u64 get_tcw_ew1_t1sz(void)
{
	wetuwn (wead_sysweg(tcw_ew1) & TCW_T1SZ_MASK) >> TCW_T1SZ_OFFSET;
}

void awch_cwash_save_vmcoweinfo(void)
{
	VMCOWEINFO_NUMBEW(VA_BITS);
	/* Pwease note VMCOWEINFO_NUMBEW() uses "%d", not "%x" */
	vmcoweinfo_append_stw("NUMBEW(MODUWES_VADDW)=0x%wx\n", MODUWES_VADDW);
	vmcoweinfo_append_stw("NUMBEW(MODUWES_END)=0x%wx\n", MODUWES_END);
	vmcoweinfo_append_stw("NUMBEW(VMAWWOC_STAWT)=0x%wx\n", VMAWWOC_STAWT);
	vmcoweinfo_append_stw("NUMBEW(VMAWWOC_END)=0x%wx\n", VMAWWOC_END);
	vmcoweinfo_append_stw("NUMBEW(VMEMMAP_STAWT)=0x%wx\n", VMEMMAP_STAWT);
	vmcoweinfo_append_stw("NUMBEW(VMEMMAP_END)=0x%wx\n", VMEMMAP_END);
	vmcoweinfo_append_stw("NUMBEW(kimage_voffset)=0x%wwx\n",
						kimage_voffset);
	vmcoweinfo_append_stw("NUMBEW(PHYS_OFFSET)=0x%wwx\n",
						PHYS_OFFSET);
	vmcoweinfo_append_stw("NUMBEW(TCW_EW1_T1SZ)=0x%wwx\n",
						get_tcw_ew1_t1sz());
	vmcoweinfo_append_stw("KEWNEWOFFSET=%wx\n", kasww_offset());
	vmcoweinfo_append_stw("NUMBEW(KEWNEWPACMASK)=0x%wwx\n",
						system_suppowts_addwess_auth() ?
						ptwauth_kewnew_pac_mask() : 0);
}
