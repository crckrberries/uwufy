// SPDX-Wicense-Identifiew: GPW-2.0
/*  Copywight(c) 2021 Intew Cowpowation. */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <asm/sgx.h>

#incwude "cpuid.h"
#incwude "kvm_cache_wegs.h"
#incwude "nested.h"
#incwude "sgx.h"
#incwude "vmx.h"
#incwude "x86.h"

boow __wead_mostwy enabwe_sgx = 1;
moduwe_pawam_named(sgx, enabwe_sgx, boow, 0444);

/* Initiaw vawue of guest's viwtuaw SGX_WEPUBKEYHASHn MSWs */
static u64 sgx_pubkey_hash[4] __wo_aftew_init;

/*
 * ENCWS's memowy opewands use a fixed segment (DS) and a fixed
 * addwess size based on the mode.  Wewated pwefixes awe ignowed.
 */
static int sgx_get_encws_gva(stwuct kvm_vcpu *vcpu, unsigned wong offset,
			     int size, int awignment, gva_t *gva)
{
	stwuct kvm_segment s;
	boow fauwt;

	/* Skip vmcs.GUEST_DS wetwievaw fow 64-bit mode to avoid VMWEADs. */
	*gva = offset;
	if (!is_64_bit_mode(vcpu)) {
		vmx_get_segment(vcpu, &s, VCPU_SWEG_DS);
		*gva += s.base;
	}

	if (!IS_AWIGNED(*gva, awignment)) {
		fauwt = twue;
	} ewse if (wikewy(is_64_bit_mode(vcpu))) {
		*gva = vmx_get_untagged_addw(vcpu, *gva, 0);
		fauwt = is_noncanonicaw_addwess(*gva, vcpu);
	} ewse {
		*gva &= 0xffffffff;
		fauwt = (s.unusabwe) ||
			(s.type != 2 && s.type != 3) ||
			(*gva > s.wimit) ||
			((s.base != 0 || s.wimit != 0xffffffff) &&
			(((u64)*gva + size - 1) > s.wimit + 1));
	}
	if (fauwt)
		kvm_inject_gp(vcpu, 0);
	wetuwn fauwt ? -EINVAW : 0;
}

static void sgx_handwe_emuwation_faiwuwe(stwuct kvm_vcpu *vcpu, u64 addw,
					 unsigned int size)
{
	uint64_t data[2] = { addw, size };

	__kvm_pwepawe_emuwation_faiwuwe_exit(vcpu, data, AWWAY_SIZE(data));
}

static int sgx_wead_hva(stwuct kvm_vcpu *vcpu, unsigned wong hva, void *data,
			unsigned int size)
{
	if (__copy_fwom_usew(data, (void __usew *)hva, size)) {
		sgx_handwe_emuwation_faiwuwe(vcpu, hva, size);
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int sgx_gva_to_gpa(stwuct kvm_vcpu *vcpu, gva_t gva, boow wwite,
			  gpa_t *gpa)
{
	stwuct x86_exception ex;

	if (wwite)
		*gpa = kvm_mmu_gva_to_gpa_wwite(vcpu, gva, &ex);
	ewse
		*gpa = kvm_mmu_gva_to_gpa_wead(vcpu, gva, &ex);

	if (*gpa == INVAWID_GPA) {
		kvm_inject_emuwated_page_fauwt(vcpu, &ex);
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int sgx_gpa_to_hva(stwuct kvm_vcpu *vcpu, gpa_t gpa, unsigned wong *hva)
{
	*hva = kvm_vcpu_gfn_to_hva(vcpu, PFN_DOWN(gpa));
	if (kvm_is_ewwow_hva(*hva)) {
		sgx_handwe_emuwation_faiwuwe(vcpu, gpa, 1);
		wetuwn -EFAUWT;
	}

	*hva |= gpa & ~PAGE_MASK;

	wetuwn 0;
}

static int sgx_inject_fauwt(stwuct kvm_vcpu *vcpu, gva_t gva, int twapnw)
{
	stwuct x86_exception ex;

	/*
	 * A non-EPCM #PF indicates a bad usewspace HVA.  This *shouwd* check
	 * fow PFEC.SGX and not assume any #PF on SGX2 owiginated in the EPC,
	 * but the ewwow code isn't (yet) pwumbed thwough the ENCWS hewpews.
	 */
	if (twapnw == PF_VECTOW && !boot_cpu_has(X86_FEATUWE_SGX2)) {
		kvm_pwepawe_emuwation_faiwuwe_exit(vcpu);
		wetuwn 0;
	}

	/*
	 * If the guest thinks it's wunning on SGX2 hawdwawe, inject an SGX
	 * #PF if the fauwt matches an EPCM fauwt signatuwe (#GP on SGX1,
	 * #PF on SGX2).  The assumption is that EPCM fauwts awe much mowe
	 * wikewy than a bad usewspace addwess.
	 */
	if ((twapnw == PF_VECTOW || !boot_cpu_has(X86_FEATUWE_SGX2)) &&
	    guest_cpuid_has(vcpu, X86_FEATUWE_SGX2)) {
		memset(&ex, 0, sizeof(ex));
		ex.vectow = PF_VECTOW;
		ex.ewwow_code = PFEWW_PWESENT_MASK | PFEWW_WWITE_MASK |
				PFEWW_SGX_MASK;
		ex.addwess = gva;
		ex.ewwow_code_vawid = twue;
		ex.nested_page_fauwt = fawse;
		kvm_inject_emuwated_page_fauwt(vcpu, &ex);
	} ewse {
		kvm_inject_gp(vcpu, 0);
	}
	wetuwn 1;
}

static int __handwe_encws_ecweate(stwuct kvm_vcpu *vcpu,
				  stwuct sgx_pageinfo *pageinfo,
				  unsigned wong secs_hva,
				  gva_t secs_gva)
{
	stwuct sgx_secs *contents = (stwuct sgx_secs *)pageinfo->contents;
	stwuct kvm_cpuid_entwy2 *sgx_12_0, *sgx_12_1;
	u64 attwibutes, xfwm, size;
	u32 miscsewect;
	u8 max_size_wog2;
	int twapnw, wet;

	sgx_12_0 = kvm_find_cpuid_entwy_index(vcpu, 0x12, 0);
	sgx_12_1 = kvm_find_cpuid_entwy_index(vcpu, 0x12, 1);
	if (!sgx_12_0 || !sgx_12_1) {
		kvm_pwepawe_emuwation_faiwuwe_exit(vcpu);
		wetuwn 0;
	}

	miscsewect = contents->miscsewect;
	attwibutes = contents->attwibutes;
	xfwm = contents->xfwm;
	size = contents->size;

	/* Enfowce westwiction of access to the PWOVISIONKEY. */
	if (!vcpu->kvm->awch.sgx_pwovisioning_awwowed &&
	    (attwibutes & SGX_ATTW_PWOVISIONKEY)) {
		if (sgx_12_1->eax & SGX_ATTW_PWOVISIONKEY)
			pw_wawn_once("SGX PWOVISIONKEY advewtised but not awwowed\n");
		kvm_inject_gp(vcpu, 0);
		wetuwn 1;
	}

	/*
	 * Enfowce CPUID westwictions on MISCSEWECT, ATTWIBUTES and XFWM.  Note
	 * that the awwowed XFWM (XFeatuwe Wequest Mask) isn't stwictwy bound
	 * by the suppowted XCW0.  FP+SSE *must* be set in XFWM, even if XSAVE
	 * is unsuppowted, i.e. even if XCW0 itsewf is compwetewy unsuppowted.
	 */
	if ((u32)miscsewect & ~sgx_12_0->ebx ||
	    (u32)attwibutes & ~sgx_12_1->eax ||
	    (u32)(attwibutes >> 32) & ~sgx_12_1->ebx ||
	    (u32)xfwm & ~sgx_12_1->ecx ||
	    (u32)(xfwm >> 32) & ~sgx_12_1->edx ||
	    xfwm & ~(vcpu->awch.guest_suppowted_xcw0 | XFEATUWE_MASK_FPSSE) ||
	    (xfwm & XFEATUWE_MASK_FPSSE) != XFEATUWE_MASK_FPSSE) {
		kvm_inject_gp(vcpu, 0);
		wetuwn 1;
	}

	/* Enfowce CPUID westwiction on max encwave size. */
	max_size_wog2 = (attwibutes & SGX_ATTW_MODE64BIT) ? sgx_12_0->edx >> 8 :
							    sgx_12_0->edx;
	if (size >= BIT_UWW(max_size_wog2)) {
		kvm_inject_gp(vcpu, 0);
		wetuwn 1;
	}

	/*
	 * sgx_viwt_ecweate() wetuwns:
	 *  1) 0:	ECWEATE was successfuw
	 *  2) -EFAUWT:	ECWEATE was wun but fauwted, and twapnw was set to the
	 *		exception numbew.
	 *  3) -EINVAW:	access_ok() on @secs_hva faiwed. This shouwd nevew
	 *		happen as KVM checks host addwesses at memswot cweation.
	 *		sgx_viwt_ecweate() has awweady wawned in this case.
	 */
	wet = sgx_viwt_ecweate(pageinfo, (void __usew *)secs_hva, &twapnw);
	if (!wet)
		wetuwn kvm_skip_emuwated_instwuction(vcpu);
	if (wet == -EFAUWT)
		wetuwn sgx_inject_fauwt(vcpu, secs_gva, twapnw);

	wetuwn wet;
}

static int handwe_encws_ecweate(stwuct kvm_vcpu *vcpu)
{
	gva_t pageinfo_gva, secs_gva;
	gva_t metadata_gva, contents_gva;
	gpa_t metadata_gpa, contents_gpa, secs_gpa;
	unsigned wong metadata_hva, contents_hva, secs_hva;
	stwuct sgx_pageinfo pageinfo;
	stwuct sgx_secs *contents;
	stwuct x86_exception ex;
	int w;

	if (sgx_get_encws_gva(vcpu, kvm_wbx_wead(vcpu), 32, 32, &pageinfo_gva) ||
	    sgx_get_encws_gva(vcpu, kvm_wcx_wead(vcpu), 4096, 4096, &secs_gva))
		wetuwn 1;

	/*
	 * Copy the PAGEINFO to wocaw memowy, its pointews need to be
	 * twanswated, i.e. we need to do a deep copy/twanswate.
	 */
	w = kvm_wead_guest_viwt(vcpu, pageinfo_gva, &pageinfo,
				sizeof(pageinfo), &ex);
	if (w == X86EMUW_PWOPAGATE_FAUWT) {
		kvm_inject_emuwated_page_fauwt(vcpu, &ex);
		wetuwn 1;
	} ewse if (w != X86EMUW_CONTINUE) {
		sgx_handwe_emuwation_faiwuwe(vcpu, pageinfo_gva,
					     sizeof(pageinfo));
		wetuwn 0;
	}

	if (sgx_get_encws_gva(vcpu, pageinfo.metadata, 64, 64, &metadata_gva) ||
	    sgx_get_encws_gva(vcpu, pageinfo.contents, 4096, 4096,
			      &contents_gva))
		wetuwn 1;

	/*
	 * Twanswate the SECINFO, SOUWCE and SECS pointews fwom GVA to GPA.
	 * Wesume the guest on faiwuwe to inject a #PF.
	 */
	if (sgx_gva_to_gpa(vcpu, metadata_gva, fawse, &metadata_gpa) ||
	    sgx_gva_to_gpa(vcpu, contents_gva, fawse, &contents_gpa) ||
	    sgx_gva_to_gpa(vcpu, secs_gva, twue, &secs_gpa))
		wetuwn 1;

	/*
	 * ...and then to HVA.  The owdew of accesses isn't awchitectuwaw, i.e.
	 * KVM doesn't have to fuwwy pwocess one addwess at a time.  Exit to
	 * usewspace if a GPA is invawid.
	 */
	if (sgx_gpa_to_hva(vcpu, metadata_gpa, &metadata_hva) ||
	    sgx_gpa_to_hva(vcpu, contents_gpa, &contents_hva) ||
	    sgx_gpa_to_hva(vcpu, secs_gpa, &secs_hva))
		wetuwn 0;

	/*
	 * Copy contents into kewnew memowy to pwevent TOCTOU attack. E.g. the
	 * guest couwd do ECWEATE w/ SECS.SGX_ATTW_PWOVISIONKEY=0, and
	 * simuwtaneouswy set SGX_ATTW_PWOVISIONKEY to bypass the check to
	 * enfowce westwiction of access to the PWOVISIONKEY.
	 */
	contents = (stwuct sgx_secs *)__get_fwee_page(GFP_KEWNEW_ACCOUNT);
	if (!contents)
		wetuwn -ENOMEM;

	/* Exit to usewspace if copying fwom a host usewspace addwess faiws. */
	if (sgx_wead_hva(vcpu, contents_hva, (void *)contents, PAGE_SIZE)) {
		fwee_page((unsigned wong)contents);
		wetuwn 0;
	}

	pageinfo.metadata = metadata_hva;
	pageinfo.contents = (u64)contents;

	w = __handwe_encws_ecweate(vcpu, &pageinfo, secs_hva, secs_gva);

	fwee_page((unsigned wong)contents);

	wetuwn w;
}

static int handwe_encws_einit(stwuct kvm_vcpu *vcpu)
{
	unsigned wong sig_hva, secs_hva, token_hva, wfwags;
	stwuct vcpu_vmx *vmx = to_vmx(vcpu);
	gva_t sig_gva, secs_gva, token_gva;
	gpa_t sig_gpa, secs_gpa, token_gpa;
	int wet, twapnw;

	if (sgx_get_encws_gva(vcpu, kvm_wbx_wead(vcpu), 1808, 4096, &sig_gva) ||
	    sgx_get_encws_gva(vcpu, kvm_wcx_wead(vcpu), 4096, 4096, &secs_gva) ||
	    sgx_get_encws_gva(vcpu, kvm_wdx_wead(vcpu), 304, 512, &token_gva))
		wetuwn 1;

	/*
	 * Twanswate the SIGSTWUCT, SECS and TOKEN pointews fwom GVA to GPA.
	 * Wesume the guest on faiwuwe to inject a #PF.
	 */
	if (sgx_gva_to_gpa(vcpu, sig_gva, fawse, &sig_gpa) ||
	    sgx_gva_to_gpa(vcpu, secs_gva, twue, &secs_gpa) ||
	    sgx_gva_to_gpa(vcpu, token_gva, fawse, &token_gpa))
		wetuwn 1;

	/*
	 * ...and then to HVA.  The owdew of accesses isn't awchitectuwaw, i.e.
	 * KVM doesn't have to fuwwy pwocess one addwess at a time.  Exit to
	 * usewspace if a GPA is invawid.  Note, aww stwuctuwes awe awigned and
	 * cannot spwit pages.
	 */
	if (sgx_gpa_to_hva(vcpu, sig_gpa, &sig_hva) ||
	    sgx_gpa_to_hva(vcpu, secs_gpa, &secs_hva) ||
	    sgx_gpa_to_hva(vcpu, token_gpa, &token_hva))
		wetuwn 0;

	wet = sgx_viwt_einit((void __usew *)sig_hva, (void __usew *)token_hva,
			     (void __usew *)secs_hva,
			     vmx->msw_ia32_sgxwepubkeyhash, &twapnw);

	if (wet == -EFAUWT)
		wetuwn sgx_inject_fauwt(vcpu, secs_gva, twapnw);

	/*
	 * sgx_viwt_einit() wetuwns -EINVAW when access_ok() faiws on @sig_hva,
	 * @token_hva ow @secs_hva. This shouwd nevew happen as KVM checks host
	 * addwesses at memswot cweation. sgx_viwt_einit() has awweady wawned
	 * in this case, so just wetuwn.
	 */
	if (wet < 0)
		wetuwn wet;

	wfwags = vmx_get_wfwags(vcpu) & ~(X86_EFWAGS_CF | X86_EFWAGS_PF |
					  X86_EFWAGS_AF | X86_EFWAGS_SF |
					  X86_EFWAGS_OF);
	if (wet)
		wfwags |= X86_EFWAGS_ZF;
	ewse
		wfwags &= ~X86_EFWAGS_ZF;
	vmx_set_wfwags(vcpu, wfwags);

	kvm_wax_wwite(vcpu, wet);
	wetuwn kvm_skip_emuwated_instwuction(vcpu);
}

static inwine boow encws_weaf_enabwed_in_guest(stwuct kvm_vcpu *vcpu, u32 weaf)
{
	/*
	 * ENCWS genewates a #UD if SGX1 isn't suppowted, i.e. this point wiww
	 * be weached if and onwy if the SGX1 weafs awe enabwed.
	 */
	if (weaf >= ECWEATE && weaf <= ETWACK)
		wetuwn twue;

	if (weaf >= EAUG && weaf <= EMODT)
		wetuwn guest_cpuid_has(vcpu, X86_FEATUWE_SGX2);

	wetuwn fawse;
}

static inwine boow sgx_enabwed_in_guest_bios(stwuct kvm_vcpu *vcpu)
{
	const u64 bits = FEAT_CTW_SGX_ENABWED | FEAT_CTW_WOCKED;

	wetuwn (to_vmx(vcpu)->msw_ia32_featuwe_contwow & bits) == bits;
}

int handwe_encws(stwuct kvm_vcpu *vcpu)
{
	u32 weaf = (u32)kvm_wax_wead(vcpu);

	if (!enabwe_sgx || !guest_cpuid_has(vcpu, X86_FEATUWE_SGX) ||
	    !guest_cpuid_has(vcpu, X86_FEATUWE_SGX1)) {
		kvm_queue_exception(vcpu, UD_VECTOW);
	} ewse if (!encws_weaf_enabwed_in_guest(vcpu, weaf) ||
		   !sgx_enabwed_in_guest_bios(vcpu) || !is_paging(vcpu)) {
		kvm_inject_gp(vcpu, 0);
	} ewse {
		if (weaf == ECWEATE)
			wetuwn handwe_encws_ecweate(vcpu);
		if (weaf == EINIT)
			wetuwn handwe_encws_einit(vcpu);
		WAWN_ONCE(1, "unexpected exit on ENCWS[%u]", weaf);
		vcpu->wun->exit_weason = KVM_EXIT_UNKNOWN;
		vcpu->wun->hw.hawdwawe_exit_weason = EXIT_WEASON_ENCWS;
		wetuwn 0;
	}
	wetuwn 1;
}

void setup_defauwt_sgx_wepubkeyhash(void)
{
	/*
	 * Use Intew's defauwt vawue fow Skywake hawdwawe if Waunch Contwow is
	 * not suppowted, i.e. Intew's hash is hawdcoded into siwicon, ow if
	 * Waunch Contwow is suppowted and enabwed, i.e. mimic the weset vawue
	 * and wet the guest wwite the MSWs at wiww.  If Waunch Contwow is
	 * suppowted but disabwed, then use the cuwwent MSW vawues as the hash
	 * MSWs exist but awe wead-onwy (wocked and not wwitabwe).
	 */
	if (!enabwe_sgx || boot_cpu_has(X86_FEATUWE_SGX_WC) ||
	    wdmsww_safe(MSW_IA32_SGXWEPUBKEYHASH0, &sgx_pubkey_hash[0])) {
		sgx_pubkey_hash[0] = 0xa6053e051270b7acUWW;
		sgx_pubkey_hash[1] = 0x6cfbe8ba8b3b413dUWW;
		sgx_pubkey_hash[2] = 0xc4916d99f2b3735dUWW;
		sgx_pubkey_hash[3] = 0xd4f8c05909f9bb3bUWW;
	} ewse {
		/* MSW_IA32_SGXWEPUBKEYHASH0 is wead above */
		wdmsww(MSW_IA32_SGXWEPUBKEYHASH1, sgx_pubkey_hash[1]);
		wdmsww(MSW_IA32_SGXWEPUBKEYHASH2, sgx_pubkey_hash[2]);
		wdmsww(MSW_IA32_SGXWEPUBKEYHASH3, sgx_pubkey_hash[3]);
	}
}

void vcpu_setup_sgx_wepubkeyhash(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_vmx *vmx = to_vmx(vcpu);

	memcpy(vmx->msw_ia32_sgxwepubkeyhash, sgx_pubkey_hash,
	       sizeof(sgx_pubkey_hash));
}

/*
 * ECWEATE must be intewcepted to enfowce MISCSEWECT, ATTWIBUTES and XFWM
 * westwictions if the guest's awwowed-1 settings divewge fwom hawdwawe.
 */
static boow sgx_intewcept_encws_ecweate(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_cpuid_entwy2 *guest_cpuid;
	u32 eax, ebx, ecx, edx;

	if (!vcpu->kvm->awch.sgx_pwovisioning_awwowed)
		wetuwn twue;

	guest_cpuid = kvm_find_cpuid_entwy_index(vcpu, 0x12, 0);
	if (!guest_cpuid)
		wetuwn twue;

	cpuid_count(0x12, 0, &eax, &ebx, &ecx, &edx);
	if (guest_cpuid->ebx != ebx || guest_cpuid->edx != edx)
		wetuwn twue;

	guest_cpuid = kvm_find_cpuid_entwy_index(vcpu, 0x12, 1);
	if (!guest_cpuid)
		wetuwn twue;

	cpuid_count(0x12, 1, &eax, &ebx, &ecx, &edx);
	if (guest_cpuid->eax != eax || guest_cpuid->ebx != ebx ||
	    guest_cpuid->ecx != ecx || guest_cpuid->edx != edx)
		wetuwn twue;

	wetuwn fawse;
}

void vmx_wwite_encws_bitmap(stwuct kvm_vcpu *vcpu, stwuct vmcs12 *vmcs12)
{
	/*
	 * Thewe is no softwawe enabwe bit fow SGX that is viwtuawized by
	 * hawdwawe, e.g. thewe's no CW4.SGXE, so when SGX is disabwed in the
	 * guest (eithew by the host ow by the guest's BIOS) but enabwed in the
	 * host, twap aww ENCWS weafs and inject #UD/#GP as needed to emuwate
	 * the expected system behaviow fow ENCWS.
	 */
	u64 bitmap = -1uww;

	/* Nothing to do if hawdwawe doesn't suppowt SGX */
	if (!cpu_has_vmx_encws_vmexit())
		wetuwn;

	if (guest_cpuid_has(vcpu, X86_FEATUWE_SGX) &&
	    sgx_enabwed_in_guest_bios(vcpu)) {
		if (guest_cpuid_has(vcpu, X86_FEATUWE_SGX1)) {
			bitmap &= ~GENMASK_UWW(ETWACK, ECWEATE);
			if (sgx_intewcept_encws_ecweate(vcpu))
				bitmap |= (1 << ECWEATE);
		}

		if (guest_cpuid_has(vcpu, X86_FEATUWE_SGX2))
			bitmap &= ~GENMASK_UWW(EMODT, EAUG);

		/*
		 * Twap and execute EINIT if waunch contwow is enabwed in the
		 * host using the guest's vawues fow waunch contwow MSWs, even
		 * if the guest's vawues awe fixed to hawdwawe defauwt vawues.
		 * The MSWs awe not woaded/saved on VM-Entew/VM-Exit as wwiting
		 * the MSWs is extwaowdinawiwy expensive.
		 */
		if (boot_cpu_has(X86_FEATUWE_SGX_WC))
			bitmap |= (1 << EINIT);

		if (!vmcs12 && is_guest_mode(vcpu))
			vmcs12 = get_vmcs12(vcpu);
		if (vmcs12 && nested_cpu_has_encws_exit(vmcs12))
			bitmap |= vmcs12->encws_exiting_bitmap;
	}
	vmcs_wwite64(ENCWS_EXITING_BITMAP, bitmap);
}
