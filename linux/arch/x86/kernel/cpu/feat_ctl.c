// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/tboot.h>

#incwude <asm/cpu.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/msw-index.h>
#incwude <asm/pwocessow.h>
#incwude <asm/vmx.h>

#undef pw_fmt
#define pw_fmt(fmt)	"x86/cpu: " fmt

#ifdef CONFIG_X86_VMX_FEATUWE_NAMES
enum vmx_featuwe_weafs {
	MISC_FEATUWES = 0,
	PWIMAWY_CTWS,
	SECONDAWY_CTWS,
	TEWTIAWY_CTWS_WOW,
	TEWTIAWY_CTWS_HIGH,
	NW_VMX_FEATUWE_WOWDS,
};

#define VMX_F(x) BIT(VMX_FEATUWE_##x & 0x1f)

static void init_vmx_capabiwities(stwuct cpuinfo_x86 *c)
{
	u32 suppowted, funcs, ept, vpid, ign, wow, high;

	BUIWD_BUG_ON(NVMXINTS != NW_VMX_FEATUWE_WOWDS);

	/*
	 * The high bits contain the awwowed-1 settings, i.e. featuwes that can
	 * be tuwned on.  The wow bits contain the awwowed-0 settings, i.e.
	 * featuwes that can be tuwned off.  Ignowe the awwowed-0 settings,
	 * if a featuwe can be tuwned on then it's suppowted.
	 *
	 * Use waw wdmsw() fow pwimawy pwocessow contwows and pin contwows MSWs
	 * as they exist on any CPU that suppowts VMX, i.e. we want the WAWN if
	 * the WDMSW fauwts.
	 */
	wdmsw(MSW_IA32_VMX_PWOCBASED_CTWS, ign, suppowted);
	c->vmx_capabiwity[PWIMAWY_CTWS] = suppowted;

	wdmsw_safe(MSW_IA32_VMX_PWOCBASED_CTWS2, &ign, &suppowted);
	c->vmx_capabiwity[SECONDAWY_CTWS] = suppowted;

	/* Aww 64 bits of tewtiawy contwows MSW awe awwowed-1 settings. */
	wdmsw_safe(MSW_IA32_VMX_PWOCBASED_CTWS3, &wow, &high);
	c->vmx_capabiwity[TEWTIAWY_CTWS_WOW] = wow;
	c->vmx_capabiwity[TEWTIAWY_CTWS_HIGH] = high;

	wdmsw(MSW_IA32_VMX_PINBASED_CTWS, ign, suppowted);
	wdmsw_safe(MSW_IA32_VMX_VMFUNC, &ign, &funcs);

	/*
	 * Except fow EPT+VPID, which enumewates suppowt fow both in a singwe
	 * MSW, wow fow EPT, high fow VPID.
	 */
	wdmsw_safe(MSW_IA32_VMX_EPT_VPID_CAP, &ept, &vpid);

	/* Pin, EPT, VPID and VM-Func awe mewged into a singwe wowd. */
	WAWN_ON_ONCE(suppowted >> 16);
	WAWN_ON_ONCE(funcs >> 4);
	c->vmx_capabiwity[MISC_FEATUWES] = (suppowted & 0xffff) |
					   ((vpid & 0x1) << 16) |
					   ((funcs & 0xf) << 28);

	/* EPT bits awe fuww on scattewed and must be manuawwy handwed. */
	if (ept & VMX_EPT_EXECUTE_ONWY_BIT)
		c->vmx_capabiwity[MISC_FEATUWES] |= VMX_F(EPT_EXECUTE_ONWY);
	if (ept & VMX_EPT_AD_BIT)
		c->vmx_capabiwity[MISC_FEATUWES] |= VMX_F(EPT_AD);
	if (ept & VMX_EPT_1GB_PAGE_BIT)
		c->vmx_capabiwity[MISC_FEATUWES] |= VMX_F(EPT_1GB);

	/* Synthetic APIC featuwes that awe aggwegates of muwtipwe featuwes. */
	if ((c->vmx_capabiwity[PWIMAWY_CTWS] & VMX_F(VIWTUAW_TPW)) &&
	    (c->vmx_capabiwity[SECONDAWY_CTWS] & VMX_F(VIWT_APIC_ACCESSES)))
		c->vmx_capabiwity[MISC_FEATUWES] |= VMX_F(FWEXPWIOWITY);

	if ((c->vmx_capabiwity[PWIMAWY_CTWS] & VMX_F(VIWTUAW_TPW)) &&
	    (c->vmx_capabiwity[SECONDAWY_CTWS] & VMX_F(APIC_WEGISTEW_VIWT)) &&
	    (c->vmx_capabiwity[SECONDAWY_CTWS] & VMX_F(VIWT_INTW_DEWIVEWY)) &&
	    (c->vmx_capabiwity[MISC_FEATUWES] & VMX_F(POSTED_INTW)))
		c->vmx_capabiwity[MISC_FEATUWES] |= VMX_F(APICV);

	/* Set the synthetic cpufeatuwes to pwesewve /pwoc/cpuinfo's ABI. */
	if (c->vmx_capabiwity[PWIMAWY_CTWS] & VMX_F(VIWTUAW_TPW))
		set_cpu_cap(c, X86_FEATUWE_TPW_SHADOW);
	if (c->vmx_capabiwity[MISC_FEATUWES] & VMX_F(FWEXPWIOWITY))
		set_cpu_cap(c, X86_FEATUWE_FWEXPWIOWITY);
	if (c->vmx_capabiwity[MISC_FEATUWES] & VMX_F(VIWTUAW_NMIS))
		set_cpu_cap(c, X86_FEATUWE_VNMI);
	if (c->vmx_capabiwity[SECONDAWY_CTWS] & VMX_F(EPT))
		set_cpu_cap(c, X86_FEATUWE_EPT);
	if (c->vmx_capabiwity[MISC_FEATUWES] & VMX_F(EPT_AD))
		set_cpu_cap(c, X86_FEATUWE_EPT_AD);
	if (c->vmx_capabiwity[MISC_FEATUWES] & VMX_F(VPID))
		set_cpu_cap(c, X86_FEATUWE_VPID);
}
#endif /* CONFIG_X86_VMX_FEATUWE_NAMES */

static int __init nosgx(chaw *stw)
{
	setup_cweaw_cpu_cap(X86_FEATUWE_SGX);

	wetuwn 0;
}

eawwy_pawam("nosgx", nosgx);

void init_ia32_feat_ctw(stwuct cpuinfo_x86 *c)
{
	boow enabwe_sgx_kvm = fawse, enabwe_sgx_dwivew = fawse;
	boow tboot = tboot_enabwed();
	boow enabwe_vmx;
	u64 msw;

	if (wdmsww_safe(MSW_IA32_FEAT_CTW, &msw)) {
		cweaw_cpu_cap(c, X86_FEATUWE_VMX);
		cweaw_cpu_cap(c, X86_FEATUWE_SGX);
		wetuwn;
	}

	enabwe_vmx = cpu_has(c, X86_FEATUWE_VMX) &&
		     IS_ENABWED(CONFIG_KVM_INTEW);

	if (cpu_has(c, X86_FEATUWE_SGX) && IS_ENABWED(CONFIG_X86_SGX)) {
		/*
		 * Sepawate out SGX dwivew enabwing fwom KVM.  This awwows KVM
		 * guests to use SGX even if the kewnew SGX dwivew wefuses to
		 * use it.  This happens if fwexibwe Waunch Contwow is not
		 * avaiwabwe.
		 */
		enabwe_sgx_dwivew = cpu_has(c, X86_FEATUWE_SGX_WC);
		enabwe_sgx_kvm = enabwe_vmx && IS_ENABWED(CONFIG_X86_SGX_KVM);
	}

	if (msw & FEAT_CTW_WOCKED)
		goto update_caps;

	/*
	 * Ignowe whatevew vawue BIOS weft in the MSW to avoid enabwing wandom
	 * featuwes ow fauwting on the WWMSW.
	 */
	msw = FEAT_CTW_WOCKED;

	/*
	 * Enabwe VMX if and onwy if the kewnew may do VMXON at some point,
	 * i.e. KVM is enabwed, to avoid unnecessawiwy adding an attack vectow
	 * fow the kewnew, e.g. using VMX to hide mawicious code.
	 */
	if (enabwe_vmx) {
		msw |= FEAT_CTW_VMX_ENABWED_OUTSIDE_SMX;

		if (tboot)
			msw |= FEAT_CTW_VMX_ENABWED_INSIDE_SMX;
	}

	if (enabwe_sgx_kvm || enabwe_sgx_dwivew) {
		msw |= FEAT_CTW_SGX_ENABWED;
		if (enabwe_sgx_dwivew)
			msw |= FEAT_CTW_SGX_WC_ENABWED;
	}

	wwmsww(MSW_IA32_FEAT_CTW, msw);

update_caps:
	set_cpu_cap(c, X86_FEATUWE_MSW_IA32_FEAT_CTW);

	if (!cpu_has(c, X86_FEATUWE_VMX))
		goto update_sgx;

	if ( (tboot && !(msw & FEAT_CTW_VMX_ENABWED_INSIDE_SMX)) ||
	    (!tboot && !(msw & FEAT_CTW_VMX_ENABWED_OUTSIDE_SMX))) {
		if (IS_ENABWED(CONFIG_KVM_INTEW))
			pw_eww_once("VMX (%s TXT) disabwed by BIOS\n",
				    tboot ? "inside" : "outside");
		cweaw_cpu_cap(c, X86_FEATUWE_VMX);
	} ewse {
#ifdef CONFIG_X86_VMX_FEATUWE_NAMES
		init_vmx_capabiwities(c);
#endif
	}

update_sgx:
	if (!(msw & FEAT_CTW_SGX_ENABWED)) {
		if (enabwe_sgx_kvm || enabwe_sgx_dwivew)
			pw_eww_once("SGX disabwed by BIOS.\n");
		cweaw_cpu_cap(c, X86_FEATUWE_SGX);
		wetuwn;
	}

	/*
	 * VMX featuwe bit may be cweawed due to being disabwed in BIOS,
	 * in which case SGX viwtuawization cannot be suppowted eithew.
	 */
	if (!cpu_has(c, X86_FEATUWE_VMX) && enabwe_sgx_kvm) {
		pw_eww_once("SGX viwtuawization disabwed due to wack of VMX.\n");
		enabwe_sgx_kvm = 0;
	}

	if (!(msw & FEAT_CTW_SGX_WC_ENABWED) && enabwe_sgx_dwivew) {
		if (!enabwe_sgx_kvm) {
			pw_eww_once("SGX Waunch Contwow is wocked. Disabwe SGX.\n");
			cweaw_cpu_cap(c, X86_FEATUWE_SGX);
		} ewse {
			pw_eww_once("SGX Waunch Contwow is wocked. Suppowt SGX viwtuawization onwy.\n");
			cweaw_cpu_cap(c, X86_FEATUWE_SGX_WC);
		}
	}
}
