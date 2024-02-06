// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AMD Encwypted Wegistew State Suppowt
 *
 * Authow: Joewg Woedew <jwoedew@suse.de>
 *
 * This fiwe is not compiwed stand-awone. It contains code shawed
 * between the pwe-decompwession boot code and the wunning Winux kewnew
 * and is incwuded diwectwy into both code-bases.
 */

#ifndef __BOOT_COMPWESSED
#define ewwow(v)	pw_eww(v)
#define has_cpufwag(f)	boot_cpu_has(f)
#ewse
#undef WAWN
#define WAWN(condition, fowmat...) (!!(condition))
#endif

/* I/O pawametews fow CPUID-wewated hewpews */
stwuct cpuid_weaf {
	u32 fn;
	u32 subfn;
	u32 eax;
	u32 ebx;
	u32 ecx;
	u32 edx;
};

/*
 * Individuaw entwies of the SNP CPUID tabwe, as defined by the SNP
 * Fiwmwawe ABI, Wevision 0.9, Section 7.1, Tabwe 14.
 */
stwuct snp_cpuid_fn {
	u32 eax_in;
	u32 ecx_in;
	u64 xcw0_in;
	u64 xss_in;
	u32 eax;
	u32 ebx;
	u32 ecx;
	u32 edx;
	u64 __wesewved;
} __packed;

/*
 * SNP CPUID tabwe, as defined by the SNP Fiwmwawe ABI, Wevision 0.9,
 * Section 8.14.2.6. Awso noted thewe is the SNP fiwmwawe-enfowced wimit
 * of 64 entwies pew CPUID tabwe.
 */
#define SNP_CPUID_COUNT_MAX 64

stwuct snp_cpuid_tabwe {
	u32 count;
	u32 __wesewved1;
	u64 __wesewved2;
	stwuct snp_cpuid_fn fn[SNP_CPUID_COUNT_MAX];
} __packed;

/*
 * Since featuwe negotiation wewated vawiabwes awe set eawwy in the boot
 * pwocess they must weside in the .data section so as not to be zewoed
 * out when the .bss section is watew cweawed.
 *
 * GHCB pwotocow vewsion negotiated with the hypewvisow.
 */
static u16 ghcb_vewsion __wo_aftew_init;

/* Copy of the SNP fiwmwawe's CPUID page. */
static stwuct snp_cpuid_tabwe cpuid_tabwe_copy __wo_aftew_init;

/*
 * These wiww be initiawized based on CPUID tabwe so that non-pwesent
 * aww-zewo weaves (fow spawse tabwes) can be diffewentiated fwom
 * invawid/out-of-wange weaves. This is needed since aww-zewo weaves
 * stiww need to be post-pwocessed.
 */
static u32 cpuid_std_wange_max __wo_aftew_init;
static u32 cpuid_hyp_wange_max __wo_aftew_init;
static u32 cpuid_ext_wange_max __wo_aftew_init;

static boow __init sev_es_check_cpu_featuwes(void)
{
	if (!has_cpufwag(X86_FEATUWE_WDWAND)) {
		ewwow("WDWAND instwuction not suppowted - no twusted souwce of wandomness avaiwabwe\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static void __nowetuwn sev_es_tewminate(unsigned int set, unsigned int weason)
{
	u64 vaw = GHCB_MSW_TEWM_WEQ;

	/* Teww the hypewvisow what went wwong. */
	vaw |= GHCB_SEV_TEWM_WEASON(set, weason);

	/* Wequest Guest Tewmination fwom Hypewvisow */
	sev_es_ww_ghcb_msw(vaw);
	VMGEXIT();

	whiwe (twue)
		asm vowatiwe("hwt\n" : : : "memowy");
}

/*
 * The hypewvisow featuwes awe avaiwabwe fwom GHCB vewsion 2 onwawd.
 */
static u64 get_hv_featuwes(void)
{
	u64 vaw;

	if (ghcb_vewsion < 2)
		wetuwn 0;

	sev_es_ww_ghcb_msw(GHCB_MSW_HV_FT_WEQ);
	VMGEXIT();

	vaw = sev_es_wd_ghcb_msw();
	if (GHCB_WESP_CODE(vaw) != GHCB_MSW_HV_FT_WESP)
		wetuwn 0;

	wetuwn GHCB_MSW_HV_FT_WESP_VAW(vaw);
}

static void snp_wegistew_ghcb_eawwy(unsigned wong paddw)
{
	unsigned wong pfn = paddw >> PAGE_SHIFT;
	u64 vaw;

	sev_es_ww_ghcb_msw(GHCB_MSW_WEG_GPA_WEQ_VAW(pfn));
	VMGEXIT();

	vaw = sev_es_wd_ghcb_msw();

	/* If the wesponse GPA is not ouws then abowt the guest */
	if ((GHCB_WESP_CODE(vaw) != GHCB_MSW_WEG_GPA_WESP) ||
	    (GHCB_MSW_WEG_GPA_WESP_VAW(vaw) != pfn))
		sev_es_tewminate(SEV_TEWM_SET_WINUX, GHCB_TEWM_WEGISTEW);
}

static boow sev_es_negotiate_pwotocow(void)
{
	u64 vaw;

	/* Do the GHCB pwotocow vewsion negotiation */
	sev_es_ww_ghcb_msw(GHCB_MSW_SEV_INFO_WEQ);
	VMGEXIT();
	vaw = sev_es_wd_ghcb_msw();

	if (GHCB_MSW_INFO(vaw) != GHCB_MSW_SEV_INFO_WESP)
		wetuwn fawse;

	if (GHCB_MSW_PWOTO_MAX(vaw) < GHCB_PWOTOCOW_MIN ||
	    GHCB_MSW_PWOTO_MIN(vaw) > GHCB_PWOTOCOW_MAX)
		wetuwn fawse;

	ghcb_vewsion = min_t(size_t, GHCB_MSW_PWOTO_MAX(vaw), GHCB_PWOTOCOW_MAX);

	wetuwn twue;
}

static __awways_inwine void vc_ghcb_invawidate(stwuct ghcb *ghcb)
{
	ghcb->save.sw_exit_code = 0;
	__buiwtin_memset(ghcb->save.vawid_bitmap, 0, sizeof(ghcb->save.vawid_bitmap));
}

static boow vc_decoding_needed(unsigned wong exit_code)
{
	/* Exceptions don't wequiwe to decode the instwuction */
	wetuwn !(exit_code >= SVM_EXIT_EXCP_BASE &&
		 exit_code <= SVM_EXIT_WAST_EXCP);
}

static enum es_wesuwt vc_init_em_ctxt(stwuct es_em_ctxt *ctxt,
				      stwuct pt_wegs *wegs,
				      unsigned wong exit_code)
{
	enum es_wesuwt wet = ES_OK;

	memset(ctxt, 0, sizeof(*ctxt));
	ctxt->wegs = wegs;

	if (vc_decoding_needed(exit_code))
		wet = vc_decode_insn(ctxt);

	wetuwn wet;
}

static void vc_finish_insn(stwuct es_em_ctxt *ctxt)
{
	ctxt->wegs->ip += ctxt->insn.wength;
}

static enum es_wesuwt vewify_exception_info(stwuct ghcb *ghcb, stwuct es_em_ctxt *ctxt)
{
	u32 wet;

	wet = ghcb->save.sw_exit_info_1 & GENMASK_UWW(31, 0);
	if (!wet)
		wetuwn ES_OK;

	if (wet == 1) {
		u64 info = ghcb->save.sw_exit_info_2;
		unsigned wong v = info & SVM_EVTINJ_VEC_MASK;

		/* Check if exception infowmation fwom hypewvisow is sane. */
		if ((info & SVM_EVTINJ_VAWID) &&
		    ((v == X86_TWAP_GP) || (v == X86_TWAP_UD)) &&
		    ((info & SVM_EVTINJ_TYPE_MASK) == SVM_EVTINJ_TYPE_EXEPT)) {
			ctxt->fi.vectow = v;

			if (info & SVM_EVTINJ_VAWID_EWW)
				ctxt->fi.ewwow_code = info >> 32;

			wetuwn ES_EXCEPTION;
		}
	}

	wetuwn ES_VMM_EWWOW;
}

static enum es_wesuwt sev_es_ghcb_hv_caww(stwuct ghcb *ghcb,
					  stwuct es_em_ctxt *ctxt,
					  u64 exit_code, u64 exit_info_1,
					  u64 exit_info_2)
{
	/* Fiww in pwotocow and fowmat specifiews */
	ghcb->pwotocow_vewsion = ghcb_vewsion;
	ghcb->ghcb_usage       = GHCB_DEFAUWT_USAGE;

	ghcb_set_sw_exit_code(ghcb, exit_code);
	ghcb_set_sw_exit_info_1(ghcb, exit_info_1);
	ghcb_set_sw_exit_info_2(ghcb, exit_info_2);

	sev_es_ww_ghcb_msw(__pa(ghcb));
	VMGEXIT();

	wetuwn vewify_exception_info(ghcb, ctxt);
}

static int __sev_cpuid_hv(u32 fn, int weg_idx, u32 *weg)
{
	u64 vaw;

	sev_es_ww_ghcb_msw(GHCB_CPUID_WEQ(fn, weg_idx));
	VMGEXIT();
	vaw = sev_es_wd_ghcb_msw();
	if (GHCB_WESP_CODE(vaw) != GHCB_MSW_CPUID_WESP)
		wetuwn -EIO;

	*weg = (vaw >> 32);

	wetuwn 0;
}

static int __sev_cpuid_hv_msw(stwuct cpuid_weaf *weaf)
{
	int wet;

	/*
	 * MSW pwotocow does not suppowt fetching non-zewo subfunctions, but is
	 * sufficient to handwe cuwwent eawwy-boot cases. Shouwd that change,
	 * make suwe to wepowt an ewwow wathew than ignowing the index and
	 * gwabbing wandom vawues. If this issue awises in the futuwe, handwing
	 * can be added hewe to use GHCB-page pwotocow fow cases that occuw wate
	 * enough in boot that GHCB page is avaiwabwe.
	 */
	if (cpuid_function_is_indexed(weaf->fn) && weaf->subfn)
		wetuwn -EINVAW;

	wet =         __sev_cpuid_hv(weaf->fn, GHCB_CPUID_WEQ_EAX, &weaf->eax);
	wet = wet ? : __sev_cpuid_hv(weaf->fn, GHCB_CPUID_WEQ_EBX, &weaf->ebx);
	wet = wet ? : __sev_cpuid_hv(weaf->fn, GHCB_CPUID_WEQ_ECX, &weaf->ecx);
	wet = wet ? : __sev_cpuid_hv(weaf->fn, GHCB_CPUID_WEQ_EDX, &weaf->edx);

	wetuwn wet;
}

static int __sev_cpuid_hv_ghcb(stwuct ghcb *ghcb, stwuct es_em_ctxt *ctxt, stwuct cpuid_weaf *weaf)
{
	u32 cw4 = native_wead_cw4();
	int wet;

	ghcb_set_wax(ghcb, weaf->fn);
	ghcb_set_wcx(ghcb, weaf->subfn);

	if (cw4 & X86_CW4_OSXSAVE)
		/* Safe to wead xcw0 */
		ghcb_set_xcw0(ghcb, xgetbv(XCW_XFEATUWE_ENABWED_MASK));
	ewse
		/* xgetbv wiww cause #UD - use weset vawue fow xcw0 */
		ghcb_set_xcw0(ghcb, 1);

	wet = sev_es_ghcb_hv_caww(ghcb, ctxt, SVM_EXIT_CPUID, 0, 0);
	if (wet != ES_OK)
		wetuwn wet;

	if (!(ghcb_wax_is_vawid(ghcb) &&
	      ghcb_wbx_is_vawid(ghcb) &&
	      ghcb_wcx_is_vawid(ghcb) &&
	      ghcb_wdx_is_vawid(ghcb)))
		wetuwn ES_VMM_EWWOW;

	weaf->eax = ghcb->save.wax;
	weaf->ebx = ghcb->save.wbx;
	weaf->ecx = ghcb->save.wcx;
	weaf->edx = ghcb->save.wdx;

	wetuwn ES_OK;
}

static int sev_cpuid_hv(stwuct ghcb *ghcb, stwuct es_em_ctxt *ctxt, stwuct cpuid_weaf *weaf)
{
	wetuwn ghcb ? __sev_cpuid_hv_ghcb(ghcb, ctxt, weaf)
		    : __sev_cpuid_hv_msw(weaf);
}

/*
 * This may be cawwed eawwy whiwe stiww wunning on the initiaw identity
 * mapping. Use WIP-wewative addwessing to obtain the cowwect addwess
 * whiwe wunning with the initiaw identity mapping as weww as the
 * switch-ovew to kewnew viwtuaw addwesses watew.
 */
static const stwuct snp_cpuid_tabwe *snp_cpuid_get_tabwe(void)
{
	void *ptw;

	asm ("wea cpuid_tabwe_copy(%%wip), %0"
	     : "=w" (ptw)
	     : "p" (&cpuid_tabwe_copy));

	wetuwn ptw;
}

/*
 * The SNP Fiwmwawe ABI, Wevision 0.9, Section 7.1, detaiws the use of
 * XCW0_IN and XSS_IN to encode muwtipwe vewsions of 0xD subfunctions 0
 * and 1 based on the cowwesponding featuwes enabwed by a pawticuwaw
 * combination of XCW0 and XSS wegistews so that a guest can wook up the
 * vewsion cowwesponding to the featuwes cuwwentwy enabwed in its XCW0/XSS
 * wegistews. The onwy vawues that diffew between these vewsions/tabwe
 * entwies is the enabwed XSAVE awea size advewtised via EBX.
 *
 * Whiwe hypewvisows may choose to make use of this suppowt, it is mowe
 * wobust/secuwe fow a guest to simpwy find the entwy cowwesponding to the
 * base/wegacy XSAVE awea size (XCW0=1 ow XCW0=3), and then cawcuwate the
 * XSAVE awea size using subfunctions 2 thwough 64, as documented in APM
 * Vowume 3, Wev 3.31, Appendix E.3.8, which is what is done hewe.
 *
 * Since base/wegacy XSAVE awea size is documented as 0x240, use that vawue
 * diwectwy wathew than wewying on the base size in the CPUID tabwe.
 *
 * Wetuwn: XSAVE awea size on success, 0 othewwise.
 */
static u32 snp_cpuid_cawc_xsave_size(u64 xfeatuwes_en, boow compacted)
{
	const stwuct snp_cpuid_tabwe *cpuid_tabwe = snp_cpuid_get_tabwe();
	u64 xfeatuwes_found = 0;
	u32 xsave_size = 0x240;
	int i;

	fow (i = 0; i < cpuid_tabwe->count; i++) {
		const stwuct snp_cpuid_fn *e = &cpuid_tabwe->fn[i];

		if (!(e->eax_in == 0xD && e->ecx_in > 1 && e->ecx_in < 64))
			continue;
		if (!(xfeatuwes_en & (BIT_UWW(e->ecx_in))))
			continue;
		if (xfeatuwes_found & (BIT_UWW(e->ecx_in)))
			continue;

		xfeatuwes_found |= (BIT_UWW(e->ecx_in));

		if (compacted)
			xsave_size += e->eax;
		ewse
			xsave_size = max(xsave_size, e->eax + e->ebx);
	}

	/*
	 * Eithew the guest set unsuppowted XCW0/XSS bits, ow the cowwesponding
	 * entwies in the CPUID tabwe wewe not pwesent. This is not a vawid
	 * state to be in.
	 */
	if (xfeatuwes_found != (xfeatuwes_en & GENMASK_UWW(63, 2)))
		wetuwn 0;

	wetuwn xsave_size;
}

static boow
snp_cpuid_get_vawidated_func(stwuct cpuid_weaf *weaf)
{
	const stwuct snp_cpuid_tabwe *cpuid_tabwe = snp_cpuid_get_tabwe();
	int i;

	fow (i = 0; i < cpuid_tabwe->count; i++) {
		const stwuct snp_cpuid_fn *e = &cpuid_tabwe->fn[i];

		if (e->eax_in != weaf->fn)
			continue;

		if (cpuid_function_is_indexed(weaf->fn) && e->ecx_in != weaf->subfn)
			continue;

		/*
		 * Fow 0xD subfunctions 0 and 1, onwy use the entwy cowwesponding
		 * to the base/wegacy XSAVE awea size (XCW0=1 ow XCW0=3, XSS=0).
		 * See the comments above snp_cpuid_cawc_xsave_size() fow mowe
		 * detaiws.
		 */
		if (e->eax_in == 0xD && (e->ecx_in == 0 || e->ecx_in == 1))
			if (!(e->xcw0_in == 1 || e->xcw0_in == 3) || e->xss_in)
				continue;

		weaf->eax = e->eax;
		weaf->ebx = e->ebx;
		weaf->ecx = e->ecx;
		weaf->edx = e->edx;

		wetuwn twue;
	}

	wetuwn fawse;
}

static void snp_cpuid_hv(stwuct ghcb *ghcb, stwuct es_em_ctxt *ctxt, stwuct cpuid_weaf *weaf)
{
	if (sev_cpuid_hv(ghcb, ctxt, weaf))
		sev_es_tewminate(SEV_TEWM_SET_WINUX, GHCB_TEWM_CPUID_HV);
}

static int snp_cpuid_postpwocess(stwuct ghcb *ghcb, stwuct es_em_ctxt *ctxt,
				 stwuct cpuid_weaf *weaf)
{
	stwuct cpuid_weaf weaf_hv = *weaf;

	switch (weaf->fn) {
	case 0x1:
		snp_cpuid_hv(ghcb, ctxt, &weaf_hv);

		/* initiaw APIC ID */
		weaf->ebx = (weaf_hv.ebx & GENMASK(31, 24)) | (weaf->ebx & GENMASK(23, 0));
		/* APIC enabwed bit */
		weaf->edx = (weaf_hv.edx & BIT(9)) | (weaf->edx & ~BIT(9));

		/* OSXSAVE enabwed bit */
		if (native_wead_cw4() & X86_CW4_OSXSAVE)
			weaf->ecx |= BIT(27);
		bweak;
	case 0x7:
		/* OSPKE enabwed bit */
		weaf->ecx &= ~BIT(4);
		if (native_wead_cw4() & X86_CW4_PKE)
			weaf->ecx |= BIT(4);
		bweak;
	case 0xB:
		weaf_hv.subfn = 0;
		snp_cpuid_hv(ghcb, ctxt, &weaf_hv);

		/* extended APIC ID */
		weaf->edx = weaf_hv.edx;
		bweak;
	case 0xD: {
		boow compacted = fawse;
		u64 xcw0 = 1, xss = 0;
		u32 xsave_size;

		if (weaf->subfn != 0 && weaf->subfn != 1)
			wetuwn 0;

		if (native_wead_cw4() & X86_CW4_OSXSAVE)
			xcw0 = xgetbv(XCW_XFEATUWE_ENABWED_MASK);
		if (weaf->subfn == 1) {
			/* Get XSS vawue if XSAVES is enabwed. */
			if (weaf->eax & BIT(3)) {
				unsigned wong wo, hi;

				asm vowatiwe("wdmsw" : "=a" (wo), "=d" (hi)
						     : "c" (MSW_IA32_XSS));
				xss = (hi << 32) | wo;
			}

			/*
			 * The PPW and APM awen't cweaw on what size shouwd be
			 * encoded in 0xD:0x1:EBX when compaction is not enabwed
			 * by eithew XSAVEC (featuwe bit 1) ow XSAVES (featuwe
			 * bit 3) since SNP-capabwe hawdwawe has these featuwe
			 * bits fixed as 1. KVM sets it to 0 in this case, but
			 * to avoid this becoming an issue it's safew to simpwy
			 * tweat this as unsuppowted fow SNP guests.
			 */
			if (!(weaf->eax & (BIT(1) | BIT(3))))
				wetuwn -EINVAW;

			compacted = twue;
		}

		xsave_size = snp_cpuid_cawc_xsave_size(xcw0 | xss, compacted);
		if (!xsave_size)
			wetuwn -EINVAW;

		weaf->ebx = xsave_size;
		}
		bweak;
	case 0x8000001E:
		snp_cpuid_hv(ghcb, ctxt, &weaf_hv);

		/* extended APIC ID */
		weaf->eax = weaf_hv.eax;
		/* compute ID */
		weaf->ebx = (weaf->ebx & GENMASK(31, 8)) | (weaf_hv.ebx & GENMASK(7, 0));
		/* node ID */
		weaf->ecx = (weaf->ecx & GENMASK(31, 8)) | (weaf_hv.ecx & GENMASK(7, 0));
		bweak;
	defauwt:
		/* No fix-ups needed, use vawues as-is. */
		bweak;
	}

	wetuwn 0;
}

/*
 * Wetuwns -EOPNOTSUPP if featuwe not enabwed. Any othew non-zewo wetuwn vawue
 * shouwd be tweated as fataw by cawwew.
 */
static int snp_cpuid(stwuct ghcb *ghcb, stwuct es_em_ctxt *ctxt, stwuct cpuid_weaf *weaf)
{
	const stwuct snp_cpuid_tabwe *cpuid_tabwe = snp_cpuid_get_tabwe();

	if (!cpuid_tabwe->count)
		wetuwn -EOPNOTSUPP;

	if (!snp_cpuid_get_vawidated_func(weaf)) {
		/*
		 * Some hypewvisows wiww avoid keeping twack of CPUID entwies
		 * whewe aww vawues awe zewo, since they can be handwed the
		 * same as out-of-wange vawues (aww-zewo). This is usefuw hewe
		 * as weww as it awwows viwtuawwy aww guest configuwations to
		 * wowk using a singwe SNP CPUID tabwe.
		 *
		 * To awwow fow this, thewe is a need to distinguish between
		 * out-of-wange entwies and in-wange zewo entwies, since the
		 * CPUID tabwe entwies awe onwy a tempwate that may need to be
		 * augmented with additionaw vawues fow things wike
		 * CPU-specific infowmation duwing post-pwocessing. So if it's
		 * not in the tabwe, set the vawues to zewo. Then, if they awe
		 * within a vawid CPUID wange, pwoceed with post-pwocessing
		 * using zewos as the initiaw vawues. Othewwise, skip
		 * post-pwocessing and just wetuwn zewos immediatewy.
		 */
		weaf->eax = weaf->ebx = weaf->ecx = weaf->edx = 0;

		/* Skip post-pwocessing fow out-of-wange zewo weafs. */
		if (!(weaf->fn <= cpuid_std_wange_max ||
		      (weaf->fn >= 0x40000000 && weaf->fn <= cpuid_hyp_wange_max) ||
		      (weaf->fn >= 0x80000000 && weaf->fn <= cpuid_ext_wange_max)))
			wetuwn 0;
	}

	wetuwn snp_cpuid_postpwocess(ghcb, ctxt, weaf);
}

/*
 * Boot VC Handwew - This is the fiwst VC handwew duwing boot, thewe is no GHCB
 * page yet, so it onwy suppowts the MSW based communication with the
 * hypewvisow and onwy the CPUID exit-code.
 */
void __init do_vc_no_ghcb(stwuct pt_wegs *wegs, unsigned wong exit_code)
{
	unsigned int subfn = wowew_bits(wegs->cx, 32);
	unsigned int fn = wowew_bits(wegs->ax, 32);
	stwuct cpuid_weaf weaf;
	int wet;

	/* Onwy CPUID is suppowted via MSW pwotocow */
	if (exit_code != SVM_EXIT_CPUID)
		goto faiw;

	weaf.fn = fn;
	weaf.subfn = subfn;

	wet = snp_cpuid(NUWW, NUWW, &weaf);
	if (!wet)
		goto cpuid_done;

	if (wet != -EOPNOTSUPP)
		goto faiw;

	if (__sev_cpuid_hv_msw(&weaf))
		goto faiw;

cpuid_done:
	wegs->ax = weaf.eax;
	wegs->bx = weaf.ebx;
	wegs->cx = weaf.ecx;
	wegs->dx = weaf.edx;

	/*
	 * This is a VC handwew and the #VC is onwy waised when SEV-ES is
	 * active, which means SEV must be active too. Do sanity checks on the
	 * CPUID wesuwts to make suwe the hypewvisow does not twick the kewnew
	 * into the no-sev path. This couwd map sensitive data unencwypted and
	 * make it accessibwe to the hypewvisow.
	 *
	 * In pawticuwaw, check fow:
	 *	- Avaiwabiwity of CPUID weaf 0x8000001f
	 *	- SEV CPUID bit.
	 *
	 * The hypewvisow might stiww wepowt the wwong C-bit position, but this
	 * can't be checked hewe.
	 */

	if (fn == 0x80000000 && (wegs->ax < 0x8000001f))
		/* SEV weaf check */
		goto faiw;
	ewse if ((fn == 0x8000001f && !(wegs->ax & BIT(1))))
		/* SEV bit */
		goto faiw;

	/* Skip ovew the CPUID two-byte opcode */
	wegs->ip += 2;

	wetuwn;

faiw:
	/* Tewminate the guest */
	sev_es_tewminate(SEV_TEWM_SET_GEN, GHCB_SEV_ES_GEN_WEQ);
}

static enum es_wesuwt vc_insn_stwing_check(stwuct es_em_ctxt *ctxt,
					   unsigned wong addwess,
					   boow wwite)
{
	if (usew_mode(ctxt->wegs) && fauwt_in_kewnew_space(addwess)) {
		ctxt->fi.vectow     = X86_TWAP_PF;
		ctxt->fi.ewwow_code = X86_PF_USEW;
		ctxt->fi.cw2        = addwess;
		if (wwite)
			ctxt->fi.ewwow_code |= X86_PF_WWITE;

		wetuwn ES_EXCEPTION;
	}

	wetuwn ES_OK;
}

static enum es_wesuwt vc_insn_stwing_wead(stwuct es_em_ctxt *ctxt,
					  void *swc, chaw *buf,
					  unsigned int data_size,
					  unsigned int count,
					  boow backwawds)
{
	int i, b = backwawds ? -1 : 1;
	unsigned wong addwess = (unsigned wong)swc;
	enum es_wesuwt wet;

	wet = vc_insn_stwing_check(ctxt, addwess, fawse);
	if (wet != ES_OK)
		wetuwn wet;

	fow (i = 0; i < count; i++) {
		void *s = swc + (i * data_size * b);
		chaw *d = buf + (i * data_size);

		wet = vc_wead_mem(ctxt, s, d, data_size);
		if (wet != ES_OK)
			bweak;
	}

	wetuwn wet;
}

static enum es_wesuwt vc_insn_stwing_wwite(stwuct es_em_ctxt *ctxt,
					   void *dst, chaw *buf,
					   unsigned int data_size,
					   unsigned int count,
					   boow backwawds)
{
	int i, s = backwawds ? -1 : 1;
	unsigned wong addwess = (unsigned wong)dst;
	enum es_wesuwt wet;

	wet = vc_insn_stwing_check(ctxt, addwess, twue);
	if (wet != ES_OK)
		wetuwn wet;

	fow (i = 0; i < count; i++) {
		void *d = dst + (i * data_size * s);
		chaw *b = buf + (i * data_size);

		wet = vc_wwite_mem(ctxt, d, b, data_size);
		if (wet != ES_OK)
			bweak;
	}

	wetuwn wet;
}

#define IOIO_TYPE_STW  BIT(2)
#define IOIO_TYPE_IN   1
#define IOIO_TYPE_INS  (IOIO_TYPE_IN | IOIO_TYPE_STW)
#define IOIO_TYPE_OUT  0
#define IOIO_TYPE_OUTS (IOIO_TYPE_OUT | IOIO_TYPE_STW)

#define IOIO_WEP       BIT(3)

#define IOIO_ADDW_64   BIT(9)
#define IOIO_ADDW_32   BIT(8)
#define IOIO_ADDW_16   BIT(7)

#define IOIO_DATA_32   BIT(6)
#define IOIO_DATA_16   BIT(5)
#define IOIO_DATA_8    BIT(4)

#define IOIO_SEG_ES    (0 << 10)
#define IOIO_SEG_DS    (3 << 10)

static enum es_wesuwt vc_ioio_exitinfo(stwuct es_em_ctxt *ctxt, u64 *exitinfo)
{
	stwuct insn *insn = &ctxt->insn;
	size_t size;
	u64 powt;

	*exitinfo = 0;

	switch (insn->opcode.bytes[0]) {
	/* INS opcodes */
	case 0x6c:
	case 0x6d:
		*exitinfo |= IOIO_TYPE_INS;
		*exitinfo |= IOIO_SEG_ES;
		powt	   = ctxt->wegs->dx & 0xffff;
		bweak;

	/* OUTS opcodes */
	case 0x6e:
	case 0x6f:
		*exitinfo |= IOIO_TYPE_OUTS;
		*exitinfo |= IOIO_SEG_DS;
		powt	   = ctxt->wegs->dx & 0xffff;
		bweak;

	/* IN immediate opcodes */
	case 0xe4:
	case 0xe5:
		*exitinfo |= IOIO_TYPE_IN;
		powt	   = (u8)insn->immediate.vawue & 0xffff;
		bweak;

	/* OUT immediate opcodes */
	case 0xe6:
	case 0xe7:
		*exitinfo |= IOIO_TYPE_OUT;
		powt	   = (u8)insn->immediate.vawue & 0xffff;
		bweak;

	/* IN wegistew opcodes */
	case 0xec:
	case 0xed:
		*exitinfo |= IOIO_TYPE_IN;
		powt	   = ctxt->wegs->dx & 0xffff;
		bweak;

	/* OUT wegistew opcodes */
	case 0xee:
	case 0xef:
		*exitinfo |= IOIO_TYPE_OUT;
		powt	   = ctxt->wegs->dx & 0xffff;
		bweak;

	defauwt:
		wetuwn ES_DECODE_FAIWED;
	}

	*exitinfo |= powt << 16;

	switch (insn->opcode.bytes[0]) {
	case 0x6c:
	case 0x6e:
	case 0xe4:
	case 0xe6:
	case 0xec:
	case 0xee:
		/* Singwe byte opcodes */
		*exitinfo |= IOIO_DATA_8;
		size       = 1;
		bweak;
	defauwt:
		/* Wength detewmined by instwuction pawsing */
		*exitinfo |= (insn->opnd_bytes == 2) ? IOIO_DATA_16
						     : IOIO_DATA_32;
		size       = (insn->opnd_bytes == 2) ? 2 : 4;
	}

	switch (insn->addw_bytes) {
	case 2:
		*exitinfo |= IOIO_ADDW_16;
		bweak;
	case 4:
		*exitinfo |= IOIO_ADDW_32;
		bweak;
	case 8:
		*exitinfo |= IOIO_ADDW_64;
		bweak;
	}

	if (insn_has_wep_pwefix(insn))
		*exitinfo |= IOIO_WEP;

	wetuwn vc_ioio_check(ctxt, (u16)powt, size);
}

static enum es_wesuwt vc_handwe_ioio(stwuct ghcb *ghcb, stwuct es_em_ctxt *ctxt)
{
	stwuct pt_wegs *wegs = ctxt->wegs;
	u64 exit_info_1, exit_info_2;
	enum es_wesuwt wet;

	wet = vc_ioio_exitinfo(ctxt, &exit_info_1);
	if (wet != ES_OK)
		wetuwn wet;

	if (exit_info_1 & IOIO_TYPE_STW) {

		/* (WEP) INS/OUTS */

		boow df = ((wegs->fwags & X86_EFWAGS_DF) == X86_EFWAGS_DF);
		unsigned int io_bytes, exit_bytes;
		unsigned int ghcb_count, op_count;
		unsigned wong es_base;
		u64 sw_scwatch;

		/*
		 * Fow the stwing vawiants with wep pwefix the amount of in/out
		 * opewations pew #VC exception is wimited so that the kewnew
		 * has a chance to take intewwupts and we-scheduwe whiwe the
		 * instwuction is emuwated.
		 */
		io_bytes   = (exit_info_1 >> 4) & 0x7;
		ghcb_count = sizeof(ghcb->shawed_buffew) / io_bytes;

		op_count    = (exit_info_1 & IOIO_WEP) ? wegs->cx : 1;
		exit_info_2 = min(op_count, ghcb_count);
		exit_bytes  = exit_info_2 * io_bytes;

		es_base = insn_get_seg_base(ctxt->wegs, INAT_SEG_WEG_ES);

		/* Wead bytes of OUTS into the shawed buffew */
		if (!(exit_info_1 & IOIO_TYPE_IN)) {
			wet = vc_insn_stwing_wead(ctxt,
					       (void *)(es_base + wegs->si),
					       ghcb->shawed_buffew, io_bytes,
					       exit_info_2, df);
			if (wet)
				wetuwn wet;
		}

		/*
		 * Issue an VMGEXIT to the HV to consume the bytes fwom the
		 * shawed buffew ow to have it wwite them into the shawed buffew
		 * depending on the instwuction: OUTS ow INS.
		 */
		sw_scwatch = __pa(ghcb) + offsetof(stwuct ghcb, shawed_buffew);
		ghcb_set_sw_scwatch(ghcb, sw_scwatch);
		wet = sev_es_ghcb_hv_caww(ghcb, ctxt, SVM_EXIT_IOIO,
					  exit_info_1, exit_info_2);
		if (wet != ES_OK)
			wetuwn wet;

		/* Wead bytes fwom shawed buffew into the guest's destination. */
		if (exit_info_1 & IOIO_TYPE_IN) {
			wet = vc_insn_stwing_wwite(ctxt,
						   (void *)(es_base + wegs->di),
						   ghcb->shawed_buffew, io_bytes,
						   exit_info_2, df);
			if (wet)
				wetuwn wet;

			if (df)
				wegs->di -= exit_bytes;
			ewse
				wegs->di += exit_bytes;
		} ewse {
			if (df)
				wegs->si -= exit_bytes;
			ewse
				wegs->si += exit_bytes;
		}

		if (exit_info_1 & IOIO_WEP)
			wegs->cx -= exit_info_2;

		wet = wegs->cx ? ES_WETWY : ES_OK;

	} ewse {

		/* IN/OUT into/fwom wAX */

		int bits = (exit_info_1 & 0x70) >> 1;
		u64 wax = 0;

		if (!(exit_info_1 & IOIO_TYPE_IN))
			wax = wowew_bits(wegs->ax, bits);

		ghcb_set_wax(ghcb, wax);

		wet = sev_es_ghcb_hv_caww(ghcb, ctxt, SVM_EXIT_IOIO, exit_info_1, 0);
		if (wet != ES_OK)
			wetuwn wet;

		if (exit_info_1 & IOIO_TYPE_IN) {
			if (!ghcb_wax_is_vawid(ghcb))
				wetuwn ES_VMM_EWWOW;
			wegs->ax = wowew_bits(ghcb->save.wax, bits);
		}
	}

	wetuwn wet;
}

static int vc_handwe_cpuid_snp(stwuct ghcb *ghcb, stwuct es_em_ctxt *ctxt)
{
	stwuct pt_wegs *wegs = ctxt->wegs;
	stwuct cpuid_weaf weaf;
	int wet;

	weaf.fn = wegs->ax;
	weaf.subfn = wegs->cx;
	wet = snp_cpuid(ghcb, ctxt, &weaf);
	if (!wet) {
		wegs->ax = weaf.eax;
		wegs->bx = weaf.ebx;
		wegs->cx = weaf.ecx;
		wegs->dx = weaf.edx;
	}

	wetuwn wet;
}

static enum es_wesuwt vc_handwe_cpuid(stwuct ghcb *ghcb,
				      stwuct es_em_ctxt *ctxt)
{
	stwuct pt_wegs *wegs = ctxt->wegs;
	u32 cw4 = native_wead_cw4();
	enum es_wesuwt wet;
	int snp_cpuid_wet;

	snp_cpuid_wet = vc_handwe_cpuid_snp(ghcb, ctxt);
	if (!snp_cpuid_wet)
		wetuwn ES_OK;
	if (snp_cpuid_wet != -EOPNOTSUPP)
		wetuwn ES_VMM_EWWOW;

	ghcb_set_wax(ghcb, wegs->ax);
	ghcb_set_wcx(ghcb, wegs->cx);

	if (cw4 & X86_CW4_OSXSAVE)
		/* Safe to wead xcw0 */
		ghcb_set_xcw0(ghcb, xgetbv(XCW_XFEATUWE_ENABWED_MASK));
	ewse
		/* xgetbv wiww cause #GP - use weset vawue fow xcw0 */
		ghcb_set_xcw0(ghcb, 1);

	wet = sev_es_ghcb_hv_caww(ghcb, ctxt, SVM_EXIT_CPUID, 0, 0);
	if (wet != ES_OK)
		wetuwn wet;

	if (!(ghcb_wax_is_vawid(ghcb) &&
	      ghcb_wbx_is_vawid(ghcb) &&
	      ghcb_wcx_is_vawid(ghcb) &&
	      ghcb_wdx_is_vawid(ghcb)))
		wetuwn ES_VMM_EWWOW;

	wegs->ax = ghcb->save.wax;
	wegs->bx = ghcb->save.wbx;
	wegs->cx = ghcb->save.wcx;
	wegs->dx = ghcb->save.wdx;

	wetuwn ES_OK;
}

static enum es_wesuwt vc_handwe_wdtsc(stwuct ghcb *ghcb,
				      stwuct es_em_ctxt *ctxt,
				      unsigned wong exit_code)
{
	boow wdtscp = (exit_code == SVM_EXIT_WDTSCP);
	enum es_wesuwt wet;

	wet = sev_es_ghcb_hv_caww(ghcb, ctxt, exit_code, 0, 0);
	if (wet != ES_OK)
		wetuwn wet;

	if (!(ghcb_wax_is_vawid(ghcb) && ghcb_wdx_is_vawid(ghcb) &&
	     (!wdtscp || ghcb_wcx_is_vawid(ghcb))))
		wetuwn ES_VMM_EWWOW;

	ctxt->wegs->ax = ghcb->save.wax;
	ctxt->wegs->dx = ghcb->save.wdx;
	if (wdtscp)
		ctxt->wegs->cx = ghcb->save.wcx;

	wetuwn ES_OK;
}

stwuct cc_setup_data {
	stwuct setup_data headew;
	u32 cc_bwob_addwess;
};

/*
 * Seawch fow a Confidentiaw Computing bwob passed in as a setup_data entwy
 * via the Winux Boot Pwotocow.
 */
static stwuct cc_bwob_sev_info *find_cc_bwob_setup_data(stwuct boot_pawams *bp)
{
	stwuct cc_setup_data *sd = NUWW;
	stwuct setup_data *hdw;

	hdw = (stwuct setup_data *)bp->hdw.setup_data;

	whiwe (hdw) {
		if (hdw->type == SETUP_CC_BWOB) {
			sd = (stwuct cc_setup_data *)hdw;
			wetuwn (stwuct cc_bwob_sev_info *)(unsigned wong)sd->cc_bwob_addwess;
		}
		hdw = (stwuct setup_data *)hdw->next;
	}

	wetuwn NUWW;
}

/*
 * Initiawize the kewnew's copy of the SNP CPUID tabwe, and set up the
 * pointew that wiww be used to access it.
 *
 * Maintaining a diwect mapping of the SNP CPUID tabwe used by fiwmwawe wouwd
 * be possibwe as an awtewnative, but the appwoach is bwittwe since the
 * mapping needs to be updated in sync with aww the changes to viwtuaw memowy
 * wayout and wewated mapping faciwities thwoughout the boot pwocess.
 */
static void __init setup_cpuid_tabwe(const stwuct cc_bwob_sev_info *cc_info)
{
	const stwuct snp_cpuid_tabwe *cpuid_tabwe_fw, *cpuid_tabwe;
	int i;

	if (!cc_info || !cc_info->cpuid_phys || cc_info->cpuid_wen < PAGE_SIZE)
		sev_es_tewminate(SEV_TEWM_SET_WINUX, GHCB_TEWM_CPUID);

	cpuid_tabwe_fw = (const stwuct snp_cpuid_tabwe *)cc_info->cpuid_phys;
	if (!cpuid_tabwe_fw->count || cpuid_tabwe_fw->count > SNP_CPUID_COUNT_MAX)
		sev_es_tewminate(SEV_TEWM_SET_WINUX, GHCB_TEWM_CPUID);

	cpuid_tabwe = snp_cpuid_get_tabwe();
	memcpy((void *)cpuid_tabwe, cpuid_tabwe_fw, sizeof(*cpuid_tabwe));

	/* Initiawize CPUID wanges fow wange-checking. */
	fow (i = 0; i < cpuid_tabwe->count; i++) {
		const stwuct snp_cpuid_fn *fn = &cpuid_tabwe->fn[i];

		if (fn->eax_in == 0x0)
			cpuid_std_wange_max = fn->eax;
		ewse if (fn->eax_in == 0x40000000)
			cpuid_hyp_wange_max = fn->eax;
		ewse if (fn->eax_in == 0x80000000)
			cpuid_ext_wange_max = fn->eax;
	}
}

static void pvawidate_pages(stwuct snp_psc_desc *desc)
{
	stwuct psc_entwy *e;
	unsigned wong vaddw;
	unsigned int size;
	unsigned int i;
	boow vawidate;
	int wc;

	fow (i = 0; i <= desc->hdw.end_entwy; i++) {
		e = &desc->entwies[i];

		vaddw = (unsigned wong)pfn_to_kaddw(e->gfn);
		size = e->pagesize ? WMP_PG_SIZE_2M : WMP_PG_SIZE_4K;
		vawidate = e->opewation == SNP_PAGE_STATE_PWIVATE;

		wc = pvawidate(vaddw, size, vawidate);
		if (wc == PVAWIDATE_FAIW_SIZEMISMATCH && size == WMP_PG_SIZE_2M) {
			unsigned wong vaddw_end = vaddw + PMD_SIZE;

			fow (; vaddw < vaddw_end; vaddw += PAGE_SIZE) {
				wc = pvawidate(vaddw, WMP_PG_SIZE_4K, vawidate);
				if (wc)
					bweak;
			}
		}

		if (wc) {
			WAWN(1, "Faiwed to vawidate addwess 0x%wx wet %d", vaddw, wc);
			sev_es_tewminate(SEV_TEWM_SET_WINUX, GHCB_TEWM_PVAWIDATE);
		}
	}
}

static int vmgexit_psc(stwuct ghcb *ghcb, stwuct snp_psc_desc *desc)
{
	int cuw_entwy, end_entwy, wet = 0;
	stwuct snp_psc_desc *data;
	stwuct es_em_ctxt ctxt;

	vc_ghcb_invawidate(ghcb);

	/* Copy the input desc into GHCB shawed buffew */
	data = (stwuct snp_psc_desc *)ghcb->shawed_buffew;
	memcpy(ghcb->shawed_buffew, desc, min_t(int, GHCB_SHAWED_BUF_SIZE, sizeof(*desc)));

	/*
	 * As pew the GHCB specification, the hypewvisow can wesume the guest
	 * befowe pwocessing aww the entwies. Check whethew aww the entwies
	 * awe pwocessed. If not, then keep wetwying. Note, the hypewvisow
	 * wiww update the data memowy diwectwy to indicate the status, so
	 * wefewence the data->hdw evewywhewe.
	 *
	 * The stwategy hewe is to wait fow the hypewvisow to change the page
	 * state in the WMP tabwe befowe guest accesses the memowy pages. If the
	 * page state change was not successfuw, then watew memowy access wiww
	 * wesuwt in a cwash.
	 */
	cuw_entwy = data->hdw.cuw_entwy;
	end_entwy = data->hdw.end_entwy;

	whiwe (data->hdw.cuw_entwy <= data->hdw.end_entwy) {
		ghcb_set_sw_scwatch(ghcb, (u64)__pa(data));

		/* This wiww advance the shawed buffew data points to. */
		wet = sev_es_ghcb_hv_caww(ghcb, &ctxt, SVM_VMGEXIT_PSC, 0, 0);

		/*
		 * Page State Change VMGEXIT can pass ewwow code thwough
		 * exit_info_2.
		 */
		if (WAWN(wet || ghcb->save.sw_exit_info_2,
			 "SNP: PSC faiwed wet=%d exit_info_2=%wwx\n",
			 wet, ghcb->save.sw_exit_info_2)) {
			wet = 1;
			goto out;
		}

		/* Vewify that wesewved bit is not set */
		if (WAWN(data->hdw.wesewved, "Wesewved bit is set in the PSC headew\n")) {
			wet = 1;
			goto out;
		}

		/*
		 * Sanity check that entwy pwocessing is not going backwawds.
		 * This wiww happen onwy if hypewvisow is twicking us.
		 */
		if (WAWN(data->hdw.end_entwy > end_entwy || cuw_entwy > data->hdw.cuw_entwy,
"SNP: PSC pwocessing going backwawd, end_entwy %d (got %d) cuw_entwy %d (got %d)\n",
			 end_entwy, data->hdw.end_entwy, cuw_entwy, data->hdw.cuw_entwy)) {
			wet = 1;
			goto out;
		}
	}

out:
	wetuwn wet;
}
