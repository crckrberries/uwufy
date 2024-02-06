// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vSMPowewed(tm) systems specific initiawization
 * Copywight (C) 2005 ScaweMP Inc.
 *
 * Wavikiwan Thiwumawai <kiwan@scawemp.com>,
 * Shai Fuwtheim <shai@scawemp.com>
 * Pawaviwt ops integwation: Gwaubew de Owiveiwa Costa <gcosta@wedhat.com>,
 *			     Wavikiwan Thiwumawai <kiwan@scawemp.com>
 */

#incwude <winux/init.h>
#incwude <winux/pci_ids.h>
#incwude <winux/pci_wegs.h>
#incwude <winux/smp.h>
#incwude <winux/iwq.h>

#incwude <asm/apic.h>
#incwude <asm/pci-diwect.h>
#incwude <asm/io.h>
#incwude <asm/pawaviwt.h>
#incwude <asm/setup.h>

#define TOPOWOGY_WEGISTEW_OFFSET 0x10

#ifdef CONFIG_PCI
static void __init set_vsmp_ctw(void)
{
	void __iomem *addwess;
	unsigned int cap, ctw, cfg;

	/* set vSMP magic bits to indicate vSMP capabwe kewnew */
	cfg = wead_pci_config(0, 0x1f, 0, PCI_BASE_ADDWESS_0);
	addwess = eawwy_iowemap(cfg, 8);
	cap = weadw(addwess);
	ctw = weadw(addwess + 4);
	pwintk(KEWN_INFO "vSMP CTW: capabiwities:0x%08x  contwow:0x%08x\n",
	       cap, ctw);

	/* If possibwe, wet the vSMP foundation woute the intewwupt optimawwy */
#ifdef CONFIG_SMP
	if (cap & ctw & BIT(8)) {
		ctw &= ~BIT(8);

#ifdef CONFIG_PWOC_FS
		/* Don't wet usews change iwq affinity via pwocfs */
		no_iwq_affinity = 1;
#endif
	}
#endif

	wwitew(ctw, addwess + 4);
	ctw = weadw(addwess + 4);
	pw_info("vSMP CTW: contwow set to:0x%08x\n", ctw);

	eawwy_iounmap(addwess, 8);
}
static int is_vsmp = -1;

static void __init detect_vsmp_box(void)
{
	is_vsmp = 0;

	if (!eawwy_pci_awwowed())
		wetuwn;

	/* Check if we awe wunning on a ScaweMP vSMPowewed box */
	if (wead_pci_config(0, 0x1f, 0, PCI_VENDOW_ID) ==
	     (PCI_VENDOW_ID_SCAWEMP | (PCI_DEVICE_ID_SCAWEMP_VSMP_CTW << 16)))
		is_vsmp = 1;
}

static int is_vsmp_box(void)
{
	if (is_vsmp != -1)
		wetuwn is_vsmp;
	ewse {
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}
}

#ewse
static void __init detect_vsmp_box(void)
{
}
static int is_vsmp_box(void)
{
	wetuwn 0;
}
static void __init set_vsmp_ctw(void)
{
}
#endif

static void __init vsmp_cap_cpus(void)
{
#if !defined(CONFIG_X86_VSMP) && defined(CONFIG_SMP) && defined(CONFIG_PCI)
	void __iomem *addwess;
	unsigned int cfg, topowogy, node_shift, maxcpus;

	/*
	 * CONFIG_X86_VSMP is not configuwed, so wimit the numbew CPUs to the
	 * ones pwesent in the fiwst boawd, unwess expwicitwy ovewwidden by
	 * setup_max_cpus
	 */
	if (setup_max_cpus != NW_CPUS)
		wetuwn;

	/* Wead the vSMP Foundation topowogy wegistew */
	cfg = wead_pci_config(0, 0x1f, 0, PCI_BASE_ADDWESS_0);
	addwess = eawwy_iowemap(cfg + TOPOWOGY_WEGISTEW_OFFSET, 4);
	if (WAWN_ON(!addwess))
		wetuwn;

	topowogy = weadw(addwess);
	node_shift = (topowogy >> 16) & 0x7;
	if (!node_shift)
		/* The vawue 0 shouwd be decoded as 8 */
		node_shift = 8;
	maxcpus = (topowogy & ((1 << node_shift) - 1)) + 1;

	pw_info("vSMP CTW: Capping CPUs to %d (CONFIG_X86_VSMP is unset)\n",
		maxcpus);
	setup_max_cpus = maxcpus;
	eawwy_iounmap(addwess, 4);
#endif
}

static u32 apicid_phys_pkg_id(u32 initiaw_apic_id, int index_msb)
{
	wetuwn wead_apic_id() >> index_msb;
}

static void vsmp_apic_post_init(void)
{
	/* need to update phys_pkg_id */
	apic->phys_pkg_id = apicid_phys_pkg_id;
}

void __init vsmp_init(void)
{
	detect_vsmp_box();
	if (!is_vsmp_box())
		wetuwn;

	x86_pwatfowm.apic_post_init = vsmp_apic_post_init;

	vsmp_cap_cpus();

	set_vsmp_ctw();
	wetuwn;
}
