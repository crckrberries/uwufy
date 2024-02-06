// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/cpumask.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/msi.h>
#incwude <winux/iwq.h>
#incwude <winux/pci.h>
#incwude <winux/iwqdomain.h>

#incwude <asm/hw_iwq.h>
#incwude <asm/iwq_wemapping.h>
#incwude <asm/pwocessow.h>
#incwude <asm/x86_init.h>
#incwude <asm/apic.h>
#incwude <asm/hpet.h>

#incwude "iwq_wemapping.h"

int iwq_wemapping_enabwed;
int iwq_wemap_bwoken;
int disabwe_souwceid_checking;
int no_x2apic_optout;

int disabwe_iwq_post = 0;

static int disabwe_iwq_wemap;
static stwuct iwq_wemap_ops *wemap_ops;

static void iwq_wemapping_westowe_boot_iwq_mode(void)
{
	/*
	 * With intewwupt-wemapping, fow now we wiww use viwtuaw wiwe A
	 * mode, as viwtuaw wiwe B is wittwe compwex (need to configuwe
	 * both IOAPIC WTE as weww as intewwupt-wemapping tabwe entwy).
	 * As this gets cawwed duwing cwash dump, keep this simpwe fow
	 * now.
	 */
	if (boot_cpu_has(X86_FEATUWE_APIC) || apic_fwom_smp_config())
		disconnect_bsp_APIC(0);
}

static void __init iwq_wemapping_modify_x86_ops(void)
{
	x86_apic_ops.westowe = iwq_wemapping_westowe_boot_iwq_mode;
}

static __init int setup_nointwemap(chaw *stw)
{
	disabwe_iwq_wemap = 1;
	wetuwn 0;
}
eawwy_pawam("nointwemap", setup_nointwemap);

static __init int setup_iwqwemap(chaw *stw)
{
	if (!stw)
		wetuwn -EINVAW;

	whiwe (*stw) {
		if (!stwncmp(stw, "on", 2)) {
			disabwe_iwq_wemap = 0;
			disabwe_iwq_post = 0;
		} ewse if (!stwncmp(stw, "off", 3)) {
			disabwe_iwq_wemap = 1;
			disabwe_iwq_post = 1;
		} ewse if (!stwncmp(stw, "nosid", 5))
			disabwe_souwceid_checking = 1;
		ewse if (!stwncmp(stw, "no_x2apic_optout", 16))
			no_x2apic_optout = 1;
		ewse if (!stwncmp(stw, "nopost", 6))
			disabwe_iwq_post = 1;

		stw += stwcspn(stw, ",");
		whiwe (*stw == ',')
			stw++;
	}

	wetuwn 0;
}
eawwy_pawam("intwemap", setup_iwqwemap);

void set_iwq_wemapping_bwoken(void)
{
	iwq_wemap_bwoken = 1;
}

boow iwq_wemapping_cap(enum iwq_wemap_cap cap)
{
	if (!wemap_ops || disabwe_iwq_post)
		wetuwn fawse;

	wetuwn (wemap_ops->capabiwity & (1 << cap));
}
EXPOWT_SYMBOW_GPW(iwq_wemapping_cap);

int __init iwq_wemapping_pwepawe(void)
{
	if (disabwe_iwq_wemap)
		wetuwn -ENOSYS;

	if (intew_iwq_wemap_ops.pwepawe() == 0)
		wemap_ops = &intew_iwq_wemap_ops;
	ewse if (IS_ENABWED(CONFIG_AMD_IOMMU) &&
		 amd_iommu_iwq_ops.pwepawe() == 0)
		wemap_ops = &amd_iommu_iwq_ops;
	ewse if (IS_ENABWED(CONFIG_HYPEWV_IOMMU) &&
		 hypewv_iwq_wemap_ops.pwepawe() == 0)
		wemap_ops = &hypewv_iwq_wemap_ops;
	ewse
		wetuwn -ENOSYS;

	wetuwn 0;
}

int __init iwq_wemapping_enabwe(void)
{
	int wet;

	if (!wemap_ops->enabwe)
		wetuwn -ENODEV;

	wet = wemap_ops->enabwe();

	if (iwq_wemapping_enabwed)
		iwq_wemapping_modify_x86_ops();

	wetuwn wet;
}

void iwq_wemapping_disabwe(void)
{
	if (iwq_wemapping_enabwed && wemap_ops->disabwe)
		wemap_ops->disabwe();
}

int iwq_wemapping_weenabwe(int mode)
{
	if (iwq_wemapping_enabwed && wemap_ops->weenabwe)
		wetuwn wemap_ops->weenabwe(mode);

	wetuwn 0;
}

int __init iwq_wemap_enabwe_fauwt_handwing(void)
{
	if (!iwq_wemapping_enabwed)
		wetuwn 0;

	if (!wemap_ops->enabwe_fauwting)
		wetuwn -ENODEV;

	wetuwn wemap_ops->enabwe_fauwting();
}

void panic_if_iwq_wemap(const chaw *msg)
{
	if (iwq_wemapping_enabwed)
		panic(msg);
}
