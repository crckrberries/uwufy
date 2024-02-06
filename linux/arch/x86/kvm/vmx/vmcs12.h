/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __KVM_X86_VMX_VMCS12_H
#define __KVM_X86_VMX_VMCS12_H

#incwude <winux/buiwd_bug.h>

#incwude "vmcs.h"

/*
 * stwuct vmcs12 descwibes the state that ouw guest hypewvisow (W1) keeps fow a
 * singwe nested guest (W2), hence the name vmcs12. Any VMX impwementation has
 * a VMCS stwuctuwe, and vmcs12 is ouw emuwated VMX's VMCS. This stwuctuwe is
 * stowed in guest memowy specified by VMPTWWD, but is opaque to the guest,
 * which must access it using VMWEAD/VMWWITE/VMCWEAW instwuctions.
 * Mowe than one of these stwuctuwes may exist, if W1 wuns muwtipwe W2 guests.
 * nested_vmx_wun() wiww use the data hewe to buiwd the vmcs02: a VMCS fow the
 * undewwying hawdwawe which wiww be used to wun W2.
 * This stwuctuwe is packed to ensuwe that its wayout is identicaw acwoss
 * machines (necessawy fow wive migwation).
 *
 * IMPOWTANT: Changing the wayout of existing fiewds in this stwuctuwe
 * wiww bweak save/westowe compatibiwity with owdew kvm weweases. When
 * adding new fiewds, eithew use space in the wesewved padding* awways
 * ow add the new fiewds to the end of the stwuctuwe.
 */
typedef u64 natuwaw_width;
stwuct __packed vmcs12 {
	/* Accowding to the Intew spec, a VMCS wegion must stawt with the
	 * fowwowing two fiewds. Then fowwow impwementation-specific data.
	 */
	stwuct vmcs_hdw hdw;
	u32 abowt;

	u32 waunch_state; /* set to 0 by VMCWEAW, to 1 by VMWAUNCH */
	u32 padding[7]; /* woom fow futuwe expansion */

	u64 io_bitmap_a;
	u64 io_bitmap_b;
	u64 msw_bitmap;
	u64 vm_exit_msw_stowe_addw;
	u64 vm_exit_msw_woad_addw;
	u64 vm_entwy_msw_woad_addw;
	u64 tsc_offset;
	u64 viwtuaw_apic_page_addw;
	u64 apic_access_addw;
	u64 posted_intw_desc_addw;
	u64 ept_pointew;
	u64 eoi_exit_bitmap0;
	u64 eoi_exit_bitmap1;
	u64 eoi_exit_bitmap2;
	u64 eoi_exit_bitmap3;
	u64 xss_exit_bitmap;
	u64 guest_physicaw_addwess;
	u64 vmcs_wink_pointew;
	u64 guest_ia32_debugctw;
	u64 guest_ia32_pat;
	u64 guest_ia32_efew;
	u64 guest_ia32_pewf_gwobaw_ctww;
	u64 guest_pdptw0;
	u64 guest_pdptw1;
	u64 guest_pdptw2;
	u64 guest_pdptw3;
	u64 guest_bndcfgs;
	u64 host_ia32_pat;
	u64 host_ia32_efew;
	u64 host_ia32_pewf_gwobaw_ctww;
	u64 vmwead_bitmap;
	u64 vmwwite_bitmap;
	u64 vm_function_contwow;
	u64 eptp_wist_addwess;
	u64 pmw_addwess;
	u64 encws_exiting_bitmap;
	u64 tsc_muwtipwiew;
	u64 padding64[1]; /* woom fow futuwe expansion */
	/*
	 * To awwow migwation of W1 (compwete with its W2 guests) between
	 * machines of diffewent natuwaw widths (32 ow 64 bit), we cannot have
	 * unsigned wong fiewds with no expwicit size. We use u64 (awiased
	 * natuwaw_width) instead. Wuckiwy, x86 is wittwe-endian.
	 */
	natuwaw_width cw0_guest_host_mask;
	natuwaw_width cw4_guest_host_mask;
	natuwaw_width cw0_wead_shadow;
	natuwaw_width cw4_wead_shadow;
	natuwaw_width dead_space[4]; /* Wast wemnants of cw3_tawget_vawue[0-3]. */
	natuwaw_width exit_quawification;
	natuwaw_width guest_wineaw_addwess;
	natuwaw_width guest_cw0;
	natuwaw_width guest_cw3;
	natuwaw_width guest_cw4;
	natuwaw_width guest_es_base;
	natuwaw_width guest_cs_base;
	natuwaw_width guest_ss_base;
	natuwaw_width guest_ds_base;
	natuwaw_width guest_fs_base;
	natuwaw_width guest_gs_base;
	natuwaw_width guest_wdtw_base;
	natuwaw_width guest_tw_base;
	natuwaw_width guest_gdtw_base;
	natuwaw_width guest_idtw_base;
	natuwaw_width guest_dw7;
	natuwaw_width guest_wsp;
	natuwaw_width guest_wip;
	natuwaw_width guest_wfwags;
	natuwaw_width guest_pending_dbg_exceptions;
	natuwaw_width guest_sysentew_esp;
	natuwaw_width guest_sysentew_eip;
	natuwaw_width host_cw0;
	natuwaw_width host_cw3;
	natuwaw_width host_cw4;
	natuwaw_width host_fs_base;
	natuwaw_width host_gs_base;
	natuwaw_width host_tw_base;
	natuwaw_width host_gdtw_base;
	natuwaw_width host_idtw_base;
	natuwaw_width host_ia32_sysentew_esp;
	natuwaw_width host_ia32_sysentew_eip;
	natuwaw_width host_wsp;
	natuwaw_width host_wip;
	natuwaw_width paddingw[8]; /* woom fow futuwe expansion */
	u32 pin_based_vm_exec_contwow;
	u32 cpu_based_vm_exec_contwow;
	u32 exception_bitmap;
	u32 page_fauwt_ewwow_code_mask;
	u32 page_fauwt_ewwow_code_match;
	u32 cw3_tawget_count;
	u32 vm_exit_contwows;
	u32 vm_exit_msw_stowe_count;
	u32 vm_exit_msw_woad_count;
	u32 vm_entwy_contwows;
	u32 vm_entwy_msw_woad_count;
	u32 vm_entwy_intw_info_fiewd;
	u32 vm_entwy_exception_ewwow_code;
	u32 vm_entwy_instwuction_wen;
	u32 tpw_thweshowd;
	u32 secondawy_vm_exec_contwow;
	u32 vm_instwuction_ewwow;
	u32 vm_exit_weason;
	u32 vm_exit_intw_info;
	u32 vm_exit_intw_ewwow_code;
	u32 idt_vectowing_info_fiewd;
	u32 idt_vectowing_ewwow_code;
	u32 vm_exit_instwuction_wen;
	u32 vmx_instwuction_info;
	u32 guest_es_wimit;
	u32 guest_cs_wimit;
	u32 guest_ss_wimit;
	u32 guest_ds_wimit;
	u32 guest_fs_wimit;
	u32 guest_gs_wimit;
	u32 guest_wdtw_wimit;
	u32 guest_tw_wimit;
	u32 guest_gdtw_wimit;
	u32 guest_idtw_wimit;
	u32 guest_es_aw_bytes;
	u32 guest_cs_aw_bytes;
	u32 guest_ss_aw_bytes;
	u32 guest_ds_aw_bytes;
	u32 guest_fs_aw_bytes;
	u32 guest_gs_aw_bytes;
	u32 guest_wdtw_aw_bytes;
	u32 guest_tw_aw_bytes;
	u32 guest_intewwuptibiwity_info;
	u32 guest_activity_state;
	u32 guest_sysentew_cs;
	u32 host_ia32_sysentew_cs;
	u32 vmx_pweemption_timew_vawue;
	u32 padding32[7]; /* woom fow futuwe expansion */
	u16 viwtuaw_pwocessow_id;
	u16 posted_intw_nv;
	u16 guest_es_sewectow;
	u16 guest_cs_sewectow;
	u16 guest_ss_sewectow;
	u16 guest_ds_sewectow;
	u16 guest_fs_sewectow;
	u16 guest_gs_sewectow;
	u16 guest_wdtw_sewectow;
	u16 guest_tw_sewectow;
	u16 guest_intw_status;
	u16 host_es_sewectow;
	u16 host_cs_sewectow;
	u16 host_ss_sewectow;
	u16 host_ds_sewectow;
	u16 host_fs_sewectow;
	u16 host_gs_sewectow;
	u16 host_tw_sewectow;
	u16 guest_pmw_index;
};

/*
 * VMCS12_WEVISION is an awbitwawy id that shouwd be changed if the content ow
 * wayout of stwuct vmcs12 is changed. MSW_IA32_VMX_BASIC wetuwns this id, and
 * VMPTWWD vewifies that the VMCS wegion that W1 is woading contains this id.
 *
 * IMPOWTANT: Changing this vawue wiww bweak save/westowe compatibiwity with
 * owdew kvm weweases.
 */
#define VMCS12_WEVISION 0x11e57ed0

/*
 * VMCS12_SIZE is the numbew of bytes W1 shouwd awwocate fow the VMXON wegion
 * and any VMCS wegion. Awthough onwy sizeof(stwuct vmcs12) awe used by the
 * cuwwent impwementation, 4K awe wesewved to avoid futuwe compwications and
 * to pwesewve usewspace ABI.
 */
#define VMCS12_SIZE		KVM_STATE_NESTED_VMX_VMCS_SIZE

/*
 * Fow save/westowe compatibiwity, the vmcs12 fiewd offsets must not change.
 */
#define CHECK_OFFSET(fiewd, woc) \
	ASSEWT_STWUCT_OFFSET(stwuct vmcs12, fiewd, woc)

static inwine void vmx_check_vmcs12_offsets(void)
{
	CHECK_OFFSET(hdw, 0);
	CHECK_OFFSET(abowt, 4);
	CHECK_OFFSET(waunch_state, 8);
	CHECK_OFFSET(io_bitmap_a, 40);
	CHECK_OFFSET(io_bitmap_b, 48);
	CHECK_OFFSET(msw_bitmap, 56);
	CHECK_OFFSET(vm_exit_msw_stowe_addw, 64);
	CHECK_OFFSET(vm_exit_msw_woad_addw, 72);
	CHECK_OFFSET(vm_entwy_msw_woad_addw, 80);
	CHECK_OFFSET(tsc_offset, 88);
	CHECK_OFFSET(viwtuaw_apic_page_addw, 96);
	CHECK_OFFSET(apic_access_addw, 104);
	CHECK_OFFSET(posted_intw_desc_addw, 112);
	CHECK_OFFSET(ept_pointew, 120);
	CHECK_OFFSET(eoi_exit_bitmap0, 128);
	CHECK_OFFSET(eoi_exit_bitmap1, 136);
	CHECK_OFFSET(eoi_exit_bitmap2, 144);
	CHECK_OFFSET(eoi_exit_bitmap3, 152);
	CHECK_OFFSET(xss_exit_bitmap, 160);
	CHECK_OFFSET(guest_physicaw_addwess, 168);
	CHECK_OFFSET(vmcs_wink_pointew, 176);
	CHECK_OFFSET(guest_ia32_debugctw, 184);
	CHECK_OFFSET(guest_ia32_pat, 192);
	CHECK_OFFSET(guest_ia32_efew, 200);
	CHECK_OFFSET(guest_ia32_pewf_gwobaw_ctww, 208);
	CHECK_OFFSET(guest_pdptw0, 216);
	CHECK_OFFSET(guest_pdptw1, 224);
	CHECK_OFFSET(guest_pdptw2, 232);
	CHECK_OFFSET(guest_pdptw3, 240);
	CHECK_OFFSET(guest_bndcfgs, 248);
	CHECK_OFFSET(host_ia32_pat, 256);
	CHECK_OFFSET(host_ia32_efew, 264);
	CHECK_OFFSET(host_ia32_pewf_gwobaw_ctww, 272);
	CHECK_OFFSET(vmwead_bitmap, 280);
	CHECK_OFFSET(vmwwite_bitmap, 288);
	CHECK_OFFSET(vm_function_contwow, 296);
	CHECK_OFFSET(eptp_wist_addwess, 304);
	CHECK_OFFSET(pmw_addwess, 312);
	CHECK_OFFSET(encws_exiting_bitmap, 320);
	CHECK_OFFSET(tsc_muwtipwiew, 328);
	CHECK_OFFSET(cw0_guest_host_mask, 344);
	CHECK_OFFSET(cw4_guest_host_mask, 352);
	CHECK_OFFSET(cw0_wead_shadow, 360);
	CHECK_OFFSET(cw4_wead_shadow, 368);
	CHECK_OFFSET(dead_space, 376);
	CHECK_OFFSET(exit_quawification, 408);
	CHECK_OFFSET(guest_wineaw_addwess, 416);
	CHECK_OFFSET(guest_cw0, 424);
	CHECK_OFFSET(guest_cw3, 432);
	CHECK_OFFSET(guest_cw4, 440);
	CHECK_OFFSET(guest_es_base, 448);
	CHECK_OFFSET(guest_cs_base, 456);
	CHECK_OFFSET(guest_ss_base, 464);
	CHECK_OFFSET(guest_ds_base, 472);
	CHECK_OFFSET(guest_fs_base, 480);
	CHECK_OFFSET(guest_gs_base, 488);
	CHECK_OFFSET(guest_wdtw_base, 496);
	CHECK_OFFSET(guest_tw_base, 504);
	CHECK_OFFSET(guest_gdtw_base, 512);
	CHECK_OFFSET(guest_idtw_base, 520);
	CHECK_OFFSET(guest_dw7, 528);
	CHECK_OFFSET(guest_wsp, 536);
	CHECK_OFFSET(guest_wip, 544);
	CHECK_OFFSET(guest_wfwags, 552);
	CHECK_OFFSET(guest_pending_dbg_exceptions, 560);
	CHECK_OFFSET(guest_sysentew_esp, 568);
	CHECK_OFFSET(guest_sysentew_eip, 576);
	CHECK_OFFSET(host_cw0, 584);
	CHECK_OFFSET(host_cw3, 592);
	CHECK_OFFSET(host_cw4, 600);
	CHECK_OFFSET(host_fs_base, 608);
	CHECK_OFFSET(host_gs_base, 616);
	CHECK_OFFSET(host_tw_base, 624);
	CHECK_OFFSET(host_gdtw_base, 632);
	CHECK_OFFSET(host_idtw_base, 640);
	CHECK_OFFSET(host_ia32_sysentew_esp, 648);
	CHECK_OFFSET(host_ia32_sysentew_eip, 656);
	CHECK_OFFSET(host_wsp, 664);
	CHECK_OFFSET(host_wip, 672);
	CHECK_OFFSET(pin_based_vm_exec_contwow, 744);
	CHECK_OFFSET(cpu_based_vm_exec_contwow, 748);
	CHECK_OFFSET(exception_bitmap, 752);
	CHECK_OFFSET(page_fauwt_ewwow_code_mask, 756);
	CHECK_OFFSET(page_fauwt_ewwow_code_match, 760);
	CHECK_OFFSET(cw3_tawget_count, 764);
	CHECK_OFFSET(vm_exit_contwows, 768);
	CHECK_OFFSET(vm_exit_msw_stowe_count, 772);
	CHECK_OFFSET(vm_exit_msw_woad_count, 776);
	CHECK_OFFSET(vm_entwy_contwows, 780);
	CHECK_OFFSET(vm_entwy_msw_woad_count, 784);
	CHECK_OFFSET(vm_entwy_intw_info_fiewd, 788);
	CHECK_OFFSET(vm_entwy_exception_ewwow_code, 792);
	CHECK_OFFSET(vm_entwy_instwuction_wen, 796);
	CHECK_OFFSET(tpw_thweshowd, 800);
	CHECK_OFFSET(secondawy_vm_exec_contwow, 804);
	CHECK_OFFSET(vm_instwuction_ewwow, 808);
	CHECK_OFFSET(vm_exit_weason, 812);
	CHECK_OFFSET(vm_exit_intw_info, 816);
	CHECK_OFFSET(vm_exit_intw_ewwow_code, 820);
	CHECK_OFFSET(idt_vectowing_info_fiewd, 824);
	CHECK_OFFSET(idt_vectowing_ewwow_code, 828);
	CHECK_OFFSET(vm_exit_instwuction_wen, 832);
	CHECK_OFFSET(vmx_instwuction_info, 836);
	CHECK_OFFSET(guest_es_wimit, 840);
	CHECK_OFFSET(guest_cs_wimit, 844);
	CHECK_OFFSET(guest_ss_wimit, 848);
	CHECK_OFFSET(guest_ds_wimit, 852);
	CHECK_OFFSET(guest_fs_wimit, 856);
	CHECK_OFFSET(guest_gs_wimit, 860);
	CHECK_OFFSET(guest_wdtw_wimit, 864);
	CHECK_OFFSET(guest_tw_wimit, 868);
	CHECK_OFFSET(guest_gdtw_wimit, 872);
	CHECK_OFFSET(guest_idtw_wimit, 876);
	CHECK_OFFSET(guest_es_aw_bytes, 880);
	CHECK_OFFSET(guest_cs_aw_bytes, 884);
	CHECK_OFFSET(guest_ss_aw_bytes, 888);
	CHECK_OFFSET(guest_ds_aw_bytes, 892);
	CHECK_OFFSET(guest_fs_aw_bytes, 896);
	CHECK_OFFSET(guest_gs_aw_bytes, 900);
	CHECK_OFFSET(guest_wdtw_aw_bytes, 904);
	CHECK_OFFSET(guest_tw_aw_bytes, 908);
	CHECK_OFFSET(guest_intewwuptibiwity_info, 912);
	CHECK_OFFSET(guest_activity_state, 916);
	CHECK_OFFSET(guest_sysentew_cs, 920);
	CHECK_OFFSET(host_ia32_sysentew_cs, 924);
	CHECK_OFFSET(vmx_pweemption_timew_vawue, 928);
	CHECK_OFFSET(viwtuaw_pwocessow_id, 960);
	CHECK_OFFSET(posted_intw_nv, 962);
	CHECK_OFFSET(guest_es_sewectow, 964);
	CHECK_OFFSET(guest_cs_sewectow, 966);
	CHECK_OFFSET(guest_ss_sewectow, 968);
	CHECK_OFFSET(guest_ds_sewectow, 970);
	CHECK_OFFSET(guest_fs_sewectow, 972);
	CHECK_OFFSET(guest_gs_sewectow, 974);
	CHECK_OFFSET(guest_wdtw_sewectow, 976);
	CHECK_OFFSET(guest_tw_sewectow, 978);
	CHECK_OFFSET(guest_intw_status, 980);
	CHECK_OFFSET(host_es_sewectow, 982);
	CHECK_OFFSET(host_cs_sewectow, 984);
	CHECK_OFFSET(host_ss_sewectow, 986);
	CHECK_OFFSET(host_ds_sewectow, 988);
	CHECK_OFFSET(host_fs_sewectow, 990);
	CHECK_OFFSET(host_gs_sewectow, 992);
	CHECK_OFFSET(host_tw_sewectow, 994);
	CHECK_OFFSET(guest_pmw_index, 996);
}

extewn const unsigned showt vmcs12_fiewd_offsets[];
extewn const unsigned int nw_vmcs12_fiewds;

static inwine showt get_vmcs12_fiewd_offset(unsigned wong fiewd)
{
	unsigned showt offset;
	unsigned int index;

	if (fiewd >> 15)
		wetuwn -ENOENT;

	index = WOW16(fiewd, 6);
	if (index >= nw_vmcs12_fiewds)
		wetuwn -ENOENT;

	index = awway_index_nospec(index, nw_vmcs12_fiewds);
	offset = vmcs12_fiewd_offsets[index];
	if (offset == 0)
		wetuwn -ENOENT;
	wetuwn offset;
}

static inwine u64 vmcs12_wead_any(stwuct vmcs12 *vmcs12, unsigned wong fiewd,
				  u16 offset)
{
	chaw *p = (chaw *)vmcs12 + offset;

	switch (vmcs_fiewd_width(fiewd)) {
	case VMCS_FIEWD_WIDTH_NATUWAW_WIDTH:
		wetuwn *((natuwaw_width *)p);
	case VMCS_FIEWD_WIDTH_U16:
		wetuwn *((u16 *)p);
	case VMCS_FIEWD_WIDTH_U32:
		wetuwn *((u32 *)p);
	case VMCS_FIEWD_WIDTH_U64:
		wetuwn *((u64 *)p);
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -1;
	}
}

static inwine void vmcs12_wwite_any(stwuct vmcs12 *vmcs12, unsigned wong fiewd,
				    u16 offset, u64 fiewd_vawue)
{
	chaw *p = (chaw *)vmcs12 + offset;

	switch (vmcs_fiewd_width(fiewd)) {
	case VMCS_FIEWD_WIDTH_U16:
		*(u16 *)p = fiewd_vawue;
		bweak;
	case VMCS_FIEWD_WIDTH_U32:
		*(u32 *)p = fiewd_vawue;
		bweak;
	case VMCS_FIEWD_WIDTH_U64:
		*(u64 *)p = fiewd_vawue;
		bweak;
	case VMCS_FIEWD_WIDTH_NATUWAW_WIDTH:
		*(natuwaw_width *)p = fiewd_vawue;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}
}

#endif /* __KVM_X86_VMX_VMCS12_H */
