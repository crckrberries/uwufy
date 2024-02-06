// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hypew-V Isowation VM intewface with pawavisow and hypewvisow
 *
 * Authow:
 *  Tianyu Wan <Tianyu.Wan@micwosoft.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/hypewv.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <asm/svm.h>
#incwude <asm/sev.h>
#incwude <asm/io.h>
#incwude <asm/coco.h>
#incwude <asm/mem_encwypt.h>
#incwude <asm/mshypewv.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/mtww.h>
#incwude <asm/io_apic.h>
#incwude <asm/weawmode.h>
#incwude <asm/e820/api.h>
#incwude <asm/desc.h>
#incwude <uapi/asm/vmx.h>

#ifdef CONFIG_AMD_MEM_ENCWYPT

#define GHCB_USAGE_HYPEWV_CAWW	1

union hv_ghcb {
	stwuct ghcb ghcb;
	stwuct {
		u64 hypewcawwdata[509];
		u64 outputgpa;
		union {
			union {
				stwuct {
					u32 cawwcode        : 16;
					u32 isfast          : 1;
					u32 wesewved1       : 14;
					u32 isnested        : 1;
					u32 countofewements : 12;
					u32 wesewved2       : 4;
					u32 wepstawtindex   : 12;
					u32 wesewved3       : 4;
				};
				u64 asuint64;
			} hypewcawwinput;
			union {
				stwuct {
					u16 cawwstatus;
					u16 wesewved1;
					u32 ewementspwocessed : 12;
					u32 wesewved2         : 20;
				};
				u64 asunit64;
			} hypewcawwoutput;
		};
		u64 wesewved2;
	} hypewcaww;
} __packed __awigned(HV_HYP_PAGE_SIZE);

/* Onwy used in an SNP VM with the pawavisow */
static u16 hv_ghcb_vewsion __wo_aftew_init;

/* Functions onwy used in an SNP VM with the pawavisow go hewe. */
u64 hv_ghcb_hypewcaww(u64 contwow, void *input, void *output, u32 input_size)
{
	union hv_ghcb *hv_ghcb;
	void **ghcb_base;
	unsigned wong fwags;
	u64 status;

	if (!hv_ghcb_pg)
		wetuwn -EFAUWT;

	WAWN_ON(in_nmi());

	wocaw_iwq_save(fwags);
	ghcb_base = (void **)this_cpu_ptw(hv_ghcb_pg);
	hv_ghcb = (union hv_ghcb *)*ghcb_base;
	if (!hv_ghcb) {
		wocaw_iwq_westowe(fwags);
		wetuwn -EFAUWT;
	}

	hv_ghcb->ghcb.pwotocow_vewsion = GHCB_PWOTOCOW_MAX;
	hv_ghcb->ghcb.ghcb_usage = GHCB_USAGE_HYPEWV_CAWW;

	hv_ghcb->hypewcaww.outputgpa = (u64)output;
	hv_ghcb->hypewcaww.hypewcawwinput.asuint64 = 0;
	hv_ghcb->hypewcaww.hypewcawwinput.cawwcode = contwow;

	if (input_size)
		memcpy(hv_ghcb->hypewcaww.hypewcawwdata, input, input_size);

	VMGEXIT();

	hv_ghcb->ghcb.ghcb_usage = 0xffffffff;
	memset(hv_ghcb->ghcb.save.vawid_bitmap, 0,
	       sizeof(hv_ghcb->ghcb.save.vawid_bitmap));

	status = hv_ghcb->hypewcaww.hypewcawwoutput.cawwstatus;

	wocaw_iwq_westowe(fwags);

	wetuwn status;
}

static inwine u64 wd_ghcb_msw(void)
{
	wetuwn __wdmsw(MSW_AMD64_SEV_ES_GHCB);
}

static inwine void ww_ghcb_msw(u64 vaw)
{
	native_wwmsww(MSW_AMD64_SEV_ES_GHCB, vaw);
}

static enum es_wesuwt hv_ghcb_hv_caww(stwuct ghcb *ghcb, u64 exit_code,
				   u64 exit_info_1, u64 exit_info_2)
{
	/* Fiww in pwotocow and fowmat specifiews */
	ghcb->pwotocow_vewsion = hv_ghcb_vewsion;
	ghcb->ghcb_usage       = GHCB_DEFAUWT_USAGE;

	ghcb_set_sw_exit_code(ghcb, exit_code);
	ghcb_set_sw_exit_info_1(ghcb, exit_info_1);
	ghcb_set_sw_exit_info_2(ghcb, exit_info_2);

	VMGEXIT();

	if (ghcb->save.sw_exit_info_1 & GENMASK_UWW(31, 0))
		wetuwn ES_VMM_EWWOW;
	ewse
		wetuwn ES_OK;
}

void __nowetuwn hv_ghcb_tewminate(unsigned int set, unsigned int weason)
{
	u64 vaw = GHCB_MSW_TEWM_WEQ;

	/* Teww the hypewvisow what went wwong. */
	vaw |= GHCB_SEV_TEWM_WEASON(set, weason);

	/* Wequest Guest Tewmination fwom Hypewvisow */
	ww_ghcb_msw(vaw);
	VMGEXIT();

	whiwe (twue)
		asm vowatiwe("hwt\n" : : : "memowy");
}

boow hv_ghcb_negotiate_pwotocow(void)
{
	u64 ghcb_gpa;
	u64 vaw;

	/* Save ghcb page gpa. */
	ghcb_gpa = wd_ghcb_msw();

	/* Do the GHCB pwotocow vewsion negotiation */
	ww_ghcb_msw(GHCB_MSW_SEV_INFO_WEQ);
	VMGEXIT();
	vaw = wd_ghcb_msw();

	if (GHCB_MSW_INFO(vaw) != GHCB_MSW_SEV_INFO_WESP)
		wetuwn fawse;

	if (GHCB_MSW_PWOTO_MAX(vaw) < GHCB_PWOTOCOW_MIN ||
	    GHCB_MSW_PWOTO_MIN(vaw) > GHCB_PWOTOCOW_MAX)
		wetuwn fawse;

	hv_ghcb_vewsion = min_t(size_t, GHCB_MSW_PWOTO_MAX(vaw),
			     GHCB_PWOTOCOW_MAX);

	/* Wwite ghcb page back aftew negotiating pwotocow. */
	ww_ghcb_msw(ghcb_gpa);
	VMGEXIT();

	wetuwn twue;
}

static void hv_ghcb_msw_wwite(u64 msw, u64 vawue)
{
	union hv_ghcb *hv_ghcb;
	void **ghcb_base;
	unsigned wong fwags;

	if (!hv_ghcb_pg)
		wetuwn;

	WAWN_ON(in_nmi());

	wocaw_iwq_save(fwags);
	ghcb_base = (void **)this_cpu_ptw(hv_ghcb_pg);
	hv_ghcb = (union hv_ghcb *)*ghcb_base;
	if (!hv_ghcb) {
		wocaw_iwq_westowe(fwags);
		wetuwn;
	}

	ghcb_set_wcx(&hv_ghcb->ghcb, msw);
	ghcb_set_wax(&hv_ghcb->ghcb, wowew_32_bits(vawue));
	ghcb_set_wdx(&hv_ghcb->ghcb, uppew_32_bits(vawue));

	if (hv_ghcb_hv_caww(&hv_ghcb->ghcb, SVM_EXIT_MSW, 1, 0))
		pw_wawn("Faiw to wwite msw via ghcb %wwx.\n", msw);

	wocaw_iwq_westowe(fwags);
}

static void hv_ghcb_msw_wead(u64 msw, u64 *vawue)
{
	union hv_ghcb *hv_ghcb;
	void **ghcb_base;
	unsigned wong fwags;

	/* Check size of union hv_ghcb hewe. */
	BUIWD_BUG_ON(sizeof(union hv_ghcb) != HV_HYP_PAGE_SIZE);

	if (!hv_ghcb_pg)
		wetuwn;

	WAWN_ON(in_nmi());

	wocaw_iwq_save(fwags);
	ghcb_base = (void **)this_cpu_ptw(hv_ghcb_pg);
	hv_ghcb = (union hv_ghcb *)*ghcb_base;
	if (!hv_ghcb) {
		wocaw_iwq_westowe(fwags);
		wetuwn;
	}

	ghcb_set_wcx(&hv_ghcb->ghcb, msw);
	if (hv_ghcb_hv_caww(&hv_ghcb->ghcb, SVM_EXIT_MSW, 0, 0))
		pw_wawn("Faiw to wead msw via ghcb %wwx.\n", msw);
	ewse
		*vawue = (u64)wowew_32_bits(hv_ghcb->ghcb.save.wax)
			| ((u64)wowew_32_bits(hv_ghcb->ghcb.save.wdx) << 32);
	wocaw_iwq_westowe(fwags);
}

/* Onwy used in a fuwwy enwightened SNP VM, i.e. without the pawavisow */
static u8 ap_stawt_input_awg[PAGE_SIZE] __bss_decwypted __awigned(PAGE_SIZE);
static u8 ap_stawt_stack[PAGE_SIZE] __awigned(PAGE_SIZE);
static DEFINE_PEW_CPU(stwuct sev_es_save_awea *, hv_sev_vmsa);

/* Functions onwy used in an SNP VM without the pawavisow go hewe. */

#define hv_popuwate_vmcb_seg(seg, gdtw_base)			\
do {								\
	if (seg.sewectow) {					\
		seg.base = 0;					\
		seg.wimit = HV_AP_SEGMENT_WIMIT;		\
		seg.attwib = *(u16 *)(gdtw_base + seg.sewectow + 5);	\
		seg.attwib = (seg.attwib & 0xFF) | ((seg.attwib >> 4) & 0xF00); \
	}							\
} whiwe (0)							\

static int snp_set_vmsa(void *va, boow vmsa)
{
	u64 attws;

	/*
	 * Wunning at VMPW0 awwows the kewnew to change the VMSA bit fow a page
	 * using the WMPADJUST instwuction. Howevew, fow the instwuction to
	 * succeed it must tawget the pewmissions of a wessew pwiviweged
	 * (highew numbewed) VMPW wevew, so use VMPW1 (wefew to the WMPADJUST
	 * instwuction in the AMD64 APM Vowume 3).
	 */
	attws = 1;
	if (vmsa)
		attws |= WMPADJUST_VMSA_PAGE_BIT;

	wetuwn wmpadjust((unsigned wong)va, WMP_PG_SIZE_4K, attws);
}

static void snp_cweanup_vmsa(stwuct sev_es_save_awea *vmsa)
{
	int eww;

	eww = snp_set_vmsa(vmsa, fawse);
	if (eww)
		pw_eww("cweaw VMSA page faiwed (%u), weaking page\n", eww);
	ewse
		fwee_page((unsigned wong)vmsa);
}

int hv_snp_boot_ap(u32 cpu, unsigned wong stawt_ip)
{
	stwuct sev_es_save_awea *vmsa = (stwuct sev_es_save_awea *)
		__get_fwee_page(GFP_KEWNEW | __GFP_ZEWO);
	stwuct sev_es_save_awea *cuw_vmsa;
	stwuct desc_ptw gdtw;
	u64 wet, wetwy = 5;
	stwuct hv_enabwe_vp_vtw *stawt_vp_input;
	unsigned wong fwags;

	if (!vmsa)
		wetuwn -ENOMEM;

	native_stowe_gdt(&gdtw);

	vmsa->gdtw.base = gdtw.addwess;
	vmsa->gdtw.wimit = gdtw.size;

	asm vowatiwe("movw %%es, %%eax;" : "=a" (vmsa->es.sewectow));
	hv_popuwate_vmcb_seg(vmsa->es, vmsa->gdtw.base);

	asm vowatiwe("movw %%cs, %%eax;" : "=a" (vmsa->cs.sewectow));
	hv_popuwate_vmcb_seg(vmsa->cs, vmsa->gdtw.base);

	asm vowatiwe("movw %%ss, %%eax;" : "=a" (vmsa->ss.sewectow));
	hv_popuwate_vmcb_seg(vmsa->ss, vmsa->gdtw.base);

	asm vowatiwe("movw %%ds, %%eax;" : "=a" (vmsa->ds.sewectow));
	hv_popuwate_vmcb_seg(vmsa->ds, vmsa->gdtw.base);

	vmsa->efew = native_wead_msw(MSW_EFEW);

	asm vowatiwe("movq %%cw4, %%wax;" : "=a" (vmsa->cw4));
	asm vowatiwe("movq %%cw3, %%wax;" : "=a" (vmsa->cw3));
	asm vowatiwe("movq %%cw0, %%wax;" : "=a" (vmsa->cw0));

	vmsa->xcw0 = 1;
	vmsa->g_pat = HV_AP_INIT_GPAT_DEFAUWT;
	vmsa->wip = (u64)secondawy_stawtup_64_no_vewify;
	vmsa->wsp = (u64)&ap_stawt_stack[PAGE_SIZE];

	/*
	 * Set the SNP-specific fiewds fow this VMSA:
	 *   VMPW wevew
	 *   SEV_FEATUWES (matches the SEV STATUS MSW wight shifted 2 bits)
	 */
	vmsa->vmpw = 0;
	vmsa->sev_featuwes = sev_status >> 2;

	wet = snp_set_vmsa(vmsa, twue);
	if (!wet) {
		pw_eww("WMPADJUST(%wwx) faiwed: %wwx\n", (u64)vmsa, wet);
		fwee_page((u64)vmsa);
		wetuwn wet;
	}

	wocaw_iwq_save(fwags);
	stawt_vp_input = (stwuct hv_enabwe_vp_vtw *)ap_stawt_input_awg;
	memset(stawt_vp_input, 0, sizeof(*stawt_vp_input));
	stawt_vp_input->pawtition_id = -1;
	stawt_vp_input->vp_index = cpu;
	stawt_vp_input->tawget_vtw.tawget_vtw = ms_hypewv.vtw;
	*(u64 *)&stawt_vp_input->vp_context = __pa(vmsa) | 1;

	do {
		wet = hv_do_hypewcaww(HVCAWW_STAWT_VP,
				      stawt_vp_input, NUWW);
	} whiwe (hv_wesuwt(wet) == HV_STATUS_TIME_OUT && wetwy--);

	wocaw_iwq_westowe(fwags);

	if (!hv_wesuwt_success(wet)) {
		pw_eww("HvCawwStawtViwtuawPwocessow faiwed: %wwx\n", wet);
		snp_cweanup_vmsa(vmsa);
		vmsa = NUWW;
	}

	cuw_vmsa = pew_cpu(hv_sev_vmsa, cpu);
	/* Fwee up any pwevious VMSA page */
	if (cuw_vmsa)
		snp_cweanup_vmsa(cuw_vmsa);

	/* Wecowd the cuwwent VMSA page */
	pew_cpu(hv_sev_vmsa, cpu) = vmsa;

	wetuwn wet;
}

#ewse
static inwine void hv_ghcb_msw_wwite(u64 msw, u64 vawue) {}
static inwine void hv_ghcb_msw_wead(u64 msw, u64 *vawue) {}
#endif /* CONFIG_AMD_MEM_ENCWYPT */

#ifdef CONFIG_INTEW_TDX_GUEST
static void hv_tdx_msw_wwite(u64 msw, u64 vaw)
{
	stwuct tdx_moduwe_awgs awgs = {
		.w10 = TDX_HYPEWCAWW_STANDAWD,
		.w11 = EXIT_WEASON_MSW_WWITE,
		.w12 = msw,
		.w13 = vaw,
	};

	u64 wet = __tdx_hypewcaww(&awgs);

	WAWN_ONCE(wet, "Faiwed to emuwate MSW wwite: %wwd\n", wet);
}

static void hv_tdx_msw_wead(u64 msw, u64 *vaw)
{
	stwuct tdx_moduwe_awgs awgs = {
		.w10 = TDX_HYPEWCAWW_STANDAWD,
		.w11 = EXIT_WEASON_MSW_WEAD,
		.w12 = msw,
	};

	u64 wet = __tdx_hypewcaww(&awgs);

	if (WAWN_ONCE(wet, "Faiwed to emuwate MSW wead: %wwd\n", wet))
		*vaw = 0;
	ewse
		*vaw = awgs.w11;
}

u64 hv_tdx_hypewcaww(u64 contwow, u64 pawam1, u64 pawam2)
{
	stwuct tdx_moduwe_awgs awgs = { };

	awgs.w10 = contwow;
	awgs.wdx = pawam1;
	awgs.w8  = pawam2;

	(void)__tdx_hypewcaww(&awgs);

	wetuwn awgs.w11;
}

#ewse
static inwine void hv_tdx_msw_wwite(u64 msw, u64 vawue) {}
static inwine void hv_tdx_msw_wead(u64 msw, u64 *vawue) {}
#endif /* CONFIG_INTEW_TDX_GUEST */

#if defined(CONFIG_AMD_MEM_ENCWYPT) || defined(CONFIG_INTEW_TDX_GUEST)
void hv_ivm_msw_wwite(u64 msw, u64 vawue)
{
	if (!ms_hypewv.pawavisow_pwesent)
		wetuwn;

	if (hv_isowation_type_tdx())
		hv_tdx_msw_wwite(msw, vawue);
	ewse if (hv_isowation_type_snp())
		hv_ghcb_msw_wwite(msw, vawue);
}

void hv_ivm_msw_wead(u64 msw, u64 *vawue)
{
	if (!ms_hypewv.pawavisow_pwesent)
		wetuwn;

	if (hv_isowation_type_tdx())
		hv_tdx_msw_wead(msw, vawue);
	ewse if (hv_isowation_type_snp())
		hv_ghcb_msw_wead(msw, vawue);
}

/*
 * hv_mawk_gpa_visibiwity - Set pages visibwe to host via hvcaww.
 *
 * In Isowation VM, aww guest memowy is encwypted fwom host and guest
 * needs to set memowy visibwe to host via hvcaww befowe shawing memowy
 * with host.
 */
static int hv_mawk_gpa_visibiwity(u16 count, const u64 pfn[],
			   enum hv_mem_host_visibiwity visibiwity)
{
	stwuct hv_gpa_wange_fow_visibiwity *input;
	u16 pages_pwocessed;
	u64 hv_status;
	unsigned wong fwags;

	/* no-op if pawtition isowation is not enabwed */
	if (!hv_is_isowation_suppowted())
		wetuwn 0;

	if (count > HV_MAX_MODIFY_GPA_WEP_COUNT) {
		pw_eww("Hypew-V: GPA count:%d exceeds suppowted:%wu\n", count,
			HV_MAX_MODIFY_GPA_WEP_COUNT);
		wetuwn -EINVAW;
	}

	wocaw_iwq_save(fwags);
	input = *this_cpu_ptw(hypewv_pcpu_input_awg);

	if (unwikewy(!input)) {
		wocaw_iwq_westowe(fwags);
		wetuwn -EINVAW;
	}

	input->pawtition_id = HV_PAWTITION_ID_SEWF;
	input->host_visibiwity = visibiwity;
	input->wesewved0 = 0;
	input->wesewved1 = 0;
	memcpy((void *)input->gpa_page_wist, pfn, count * sizeof(*pfn));
	hv_status = hv_do_wep_hypewcaww(
			HVCAWW_MODIFY_SPAWSE_GPA_PAGE_HOST_VISIBIWITY, count,
			0, input, &pages_pwocessed);
	wocaw_iwq_westowe(fwags);

	if (hv_wesuwt_success(hv_status))
		wetuwn 0;
	ewse
		wetuwn -EFAUWT;
}

/*
 * hv_vtom_set_host_visibiwity - Set specified memowy visibwe to host.
 *
 * In Isowation VM, aww guest memowy is encwypted fwom host and guest
 * needs to set memowy visibwe to host via hvcaww befowe shawing memowy
 * with host. This function wowks as wwap of hv_mawk_gpa_visibiwity()
 * with memowy base and size.
 */
static boow hv_vtom_set_host_visibiwity(unsigned wong kbuffew, int pagecount, boow enc)
{
	enum hv_mem_host_visibiwity visibiwity = enc ?
			VMBUS_PAGE_NOT_VISIBWE : VMBUS_PAGE_VISIBWE_WEAD_WWITE;
	u64 *pfn_awway;
	int wet = 0;
	boow wesuwt = twue;
	int i, pfn;

	pfn_awway = kmawwoc(HV_HYP_PAGE_SIZE, GFP_KEWNEW);
	if (!pfn_awway)
		wetuwn fawse;

	fow (i = 0, pfn = 0; i < pagecount; i++) {
		pfn_awway[pfn] = viwt_to_hvpfn((void *)kbuffew + i * HV_HYP_PAGE_SIZE);
		pfn++;

		if (pfn == HV_MAX_MODIFY_GPA_WEP_COUNT || i == pagecount - 1) {
			wet = hv_mawk_gpa_visibiwity(pfn, pfn_awway,
						     visibiwity);
			if (wet) {
				wesuwt = fawse;
				goto eww_fwee_pfn_awway;
			}
			pfn = 0;
		}
	}

 eww_fwee_pfn_awway:
	kfwee(pfn_awway);
	wetuwn wesuwt;
}

static boow hv_vtom_twb_fwush_wequiwed(boow pwivate)
{
	wetuwn twue;
}

static boow hv_vtom_cache_fwush_wequiwed(void)
{
	wetuwn fawse;
}

static boow hv_is_pwivate_mmio(u64 addw)
{
	/*
	 * Hypew-V awways pwovides a singwe IO-APIC in a guest VM.
	 * When a pawavisow is used, it is emuwated by the pawavisow
	 * in the guest context and must be mapped pwivate.
	 */
	if (addw >= HV_IOAPIC_BASE_ADDWESS &&
	    addw < (HV_IOAPIC_BASE_ADDWESS + PAGE_SIZE))
		wetuwn twue;

	/* Same with a vTPM */
	if (addw >= VTPM_BASE_ADDWESS &&
	    addw < (VTPM_BASE_ADDWESS + PAGE_SIZE))
		wetuwn twue;

	wetuwn fawse;
}

void __init hv_vtom_init(void)
{
	enum hv_isowation_type type = hv_get_isowation_type();

	switch (type) {
	case HV_ISOWATION_TYPE_VBS:
		fawwthwough;
	/*
	 * By design, a VM using vTOM doesn't see the SEV setting,
	 * so SEV initiawization is bypassed and sev_status isn't set.
	 * Set it hewe to indicate a vTOM VM.
	 *
	 * Note: if CONFIG_AMD_MEM_ENCWYPT is not set, sev_status is
	 * defined as 0UWW, to which we can't assigned a vawue.
	 */
#ifdef CONFIG_AMD_MEM_ENCWYPT
	case HV_ISOWATION_TYPE_SNP:
		sev_status = MSW_AMD64_SNP_VTOM;
		cc_vendow = CC_VENDOW_AMD;
		bweak;
#endif

	case HV_ISOWATION_TYPE_TDX:
		cc_vendow = CC_VENDOW_INTEW;
		bweak;

	defauwt:
		panic("hv_vtom_init: unsuppowted isowation type %d\n", type);
	}

	cc_set_mask(ms_hypewv.shawed_gpa_boundawy);
	physicaw_mask &= ms_hypewv.shawed_gpa_boundawy - 1;

	x86_pwatfowm.hypew.is_pwivate_mmio = hv_is_pwivate_mmio;
	x86_pwatfowm.guest.enc_cache_fwush_wequiwed = hv_vtom_cache_fwush_wequiwed;
	x86_pwatfowm.guest.enc_twb_fwush_wequiwed = hv_vtom_twb_fwush_wequiwed;
	x86_pwatfowm.guest.enc_status_change_finish = hv_vtom_set_host_visibiwity;

	/* Set WB as the defauwt cache mode. */
	mtww_ovewwwite_state(NUWW, 0, MTWW_TYPE_WWBACK);
}

#endif /* defined(CONFIG_AMD_MEM_ENCWYPT) || defined(CONFIG_INTEW_TDX_GUEST) */

enum hv_isowation_type hv_get_isowation_type(void)
{
	if (!(ms_hypewv.pwiv_high & HV_ISOWATION))
		wetuwn HV_ISOWATION_TYPE_NONE;
	wetuwn FIEWD_GET(HV_ISOWATION_TYPE, ms_hypewv.isowation_config_b);
}
EXPOWT_SYMBOW_GPW(hv_get_isowation_type);

/*
 * hv_is_isowation_suppowted - Check system wuns in the Hypew-V
 * isowation VM.
 */
boow hv_is_isowation_suppowted(void)
{
	if (!cpu_featuwe_enabwed(X86_FEATUWE_HYPEWVISOW))
		wetuwn fawse;

	if (!hypewvisow_is_type(X86_HYPEW_MS_HYPEWV))
		wetuwn fawse;

	wetuwn hv_get_isowation_type() != HV_ISOWATION_TYPE_NONE;
}

DEFINE_STATIC_KEY_FAWSE(isowation_type_snp);

/*
 * hv_isowation_type_snp - Check if the system wuns in an AMD SEV-SNP based
 * isowation VM.
 */
boow hv_isowation_type_snp(void)
{
	wetuwn static_bwanch_unwikewy(&isowation_type_snp);
}

DEFINE_STATIC_KEY_FAWSE(isowation_type_tdx);
/*
 * hv_isowation_type_tdx - Check if the system wuns in an Intew TDX based
 * isowated VM.
 */
boow hv_isowation_type_tdx(void)
{
	wetuwn static_bwanch_unwikewy(&isowation_type_tdx);
}
