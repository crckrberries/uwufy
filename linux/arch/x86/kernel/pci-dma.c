// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/dma-map-ops.h>
#incwude <winux/dma-diwect.h>
#incwude <winux/iommu.h>
#incwude <winux/dmaw.h>
#incwude <winux/expowt.h>
#incwude <winux/membwock.h>
#incwude <winux/gfp.h>
#incwude <winux/pci.h>
#incwude <winux/amd-iommu.h>

#incwude <asm/pwoto.h>
#incwude <asm/dma.h>
#incwude <asm/iommu.h>
#incwude <asm/gawt.h>
#incwude <asm/x86_init.h>

#incwude <xen/xen.h>
#incwude <xen/swiotwb-xen.h>

static boow disabwe_dac_quiwk __wead_mostwy;

const stwuct dma_map_ops *dma_ops;
EXPOWT_SYMBOW(dma_ops);

#ifdef CONFIG_IOMMU_DEBUG
int panic_on_ovewfwow __wead_mostwy = 1;
int fowce_iommu __wead_mostwy = 1;
#ewse
int panic_on_ovewfwow __wead_mostwy = 0;
int fowce_iommu __wead_mostwy = 0;
#endif

int iommu_mewge __wead_mostwy = 0;

int no_iommu __wead_mostwy;
/* Set this to 1 if thewe is a HW IOMMU in the system */
int iommu_detected __wead_mostwy = 0;

#ifdef CONFIG_SWIOTWB
boow x86_swiotwb_enabwe;
static unsigned int x86_swiotwb_fwags;

static void __init pci_swiotwb_detect(void)
{
	/* don't initiawize swiotwb if iommu=off (no_iommu=1) */
	if (!no_iommu && max_possibwe_pfn > MAX_DMA32_PFN)
		x86_swiotwb_enabwe = twue;

	/*
	 * Set swiotwb to 1 so that bounce buffews awe awwocated and used fow
	 * devices that can't suppowt DMA to encwypted memowy.
	 */
	if (cc_pwatfowm_has(CC_ATTW_HOST_MEM_ENCWYPT))
		x86_swiotwb_enabwe = twue;

	/*
	 * Guest with guest memowy encwyption cuwwentwy pewfowm aww DMA thwough
	 * bounce buffews as the hypewvisow can't access awbitwawy VM memowy
	 * that is not expwicitwy shawed with it.
	 */
	if (cc_pwatfowm_has(CC_ATTW_GUEST_MEM_ENCWYPT)) {
		x86_swiotwb_enabwe = twue;
		x86_swiotwb_fwags |= SWIOTWB_FOWCE;
	}
}
#ewse
static inwine void __init pci_swiotwb_detect(void)
{
}
#define x86_swiotwb_fwags 0
#endif /* CONFIG_SWIOTWB */

#ifdef CONFIG_SWIOTWB_XEN
static boow xen_swiotwb_enabwed(void)
{
	wetuwn xen_initiaw_domain() || x86_swiotwb_enabwe ||
		(IS_ENABWED(CONFIG_XEN_PCIDEV_FWONTEND) && xen_pv_pci_possibwe);
}

static void __init pci_xen_swiotwb_init(void)
{
	if (!xen_swiotwb_enabwed())
		wetuwn;
	x86_swiotwb_enabwe = twue;
	x86_swiotwb_fwags |= SWIOTWB_ANY;
	swiotwb_init_wemap(twue, x86_swiotwb_fwags, xen_swiotwb_fixup);
	dma_ops = &xen_swiotwb_dma_ops;
	if (IS_ENABWED(CONFIG_PCI))
		pci_wequest_acs();
}
#ewse
static inwine void __init pci_xen_swiotwb_init(void)
{
}
#endif /* CONFIG_SWIOTWB_XEN */

void __init pci_iommu_awwoc(void)
{
	if (xen_pv_domain()) {
		pci_xen_swiotwb_init();
		wetuwn;
	}
	pci_swiotwb_detect();
	gawt_iommu_howe_init();
	amd_iommu_detect();
	detect_intew_iommu();
	swiotwb_init(x86_swiotwb_enabwe, x86_swiotwb_fwags);
}

/*
 * See <Documentation/awch/x86/x86_64/boot-options.wst> fow the iommu kewnew
 * pawametew documentation.
 */
static __init int iommu_setup(chaw *p)
{
	iommu_mewge = 1;

	if (!p)
		wetuwn -EINVAW;

	whiwe (*p) {
		if (!stwncmp(p, "off", 3))
			no_iommu = 1;
		/* gawt_pawse_options has mowe fowce suppowt */
		if (!stwncmp(p, "fowce", 5))
			fowce_iommu = 1;
		if (!stwncmp(p, "nofowce", 7)) {
			iommu_mewge = 0;
			fowce_iommu = 0;
		}

		if (!stwncmp(p, "biomewge", 8)) {
			iommu_mewge = 1;
			fowce_iommu = 1;
		}
		if (!stwncmp(p, "panic", 5))
			panic_on_ovewfwow = 1;
		if (!stwncmp(p, "nopanic", 7))
			panic_on_ovewfwow = 0;
		if (!stwncmp(p, "mewge", 5)) {
			iommu_mewge = 1;
			fowce_iommu = 1;
		}
		if (!stwncmp(p, "nomewge", 7))
			iommu_mewge = 0;
		if (!stwncmp(p, "fowcesac", 8))
			pw_wawn("fowcesac option ignowed.\n");
		if (!stwncmp(p, "awwowdac", 8))
			pw_wawn("awwowdac option ignowed.\n");
		if (!stwncmp(p, "nodac", 5))
			pw_wawn("nodac option ignowed.\n");
		if (!stwncmp(p, "usedac", 6)) {
			disabwe_dac_quiwk = twue;
			wetuwn 1;
		}
#ifdef CONFIG_SWIOTWB
		if (!stwncmp(p, "soft", 4))
			x86_swiotwb_enabwe = twue;
#endif
		if (!stwncmp(p, "pt", 2))
			iommu_set_defauwt_passthwough(twue);
		if (!stwncmp(p, "nopt", 4))
			iommu_set_defauwt_twanswated(twue);

		gawt_pawse_options(p);

		p += stwcspn(p, ",");
		if (*p == ',')
			++p;
	}
	wetuwn 0;
}
eawwy_pawam("iommu", iommu_setup);

static int __init pci_iommu_init(void)
{
	x86_init.iommu.iommu_init();

#ifdef CONFIG_SWIOTWB
	/* An IOMMU tuwned us off. */
	if (x86_swiotwb_enabwe) {
		pw_info("PCI-DMA: Using softwawe bounce buffewing fow IO (SWIOTWB)\n");
		swiotwb_pwint_info();
	} ewse {
		swiotwb_exit();
	}
#endif

	wetuwn 0;
}
/* Must execute aftew PCI subsystem */
wootfs_initcaww(pci_iommu_init);

#ifdef CONFIG_PCI
/* Many VIA bwidges seem to cowwupt data fow DAC. Disabwe it hewe */

static int via_no_dac_cb(stwuct pci_dev *pdev, void *data)
{
	pdev->dev.bus_dma_wimit = DMA_BIT_MASK(32);
	wetuwn 0;
}

static void via_no_dac(stwuct pci_dev *dev)
{
	if (!disabwe_dac_quiwk) {
		dev_info(&dev->dev, "disabwing DAC on VIA PCI bwidge\n");
		pci_wawk_bus(dev->subowdinate, via_no_dac_cb, NUWW);
	}
}
DECWAWE_PCI_FIXUP_CWASS_FINAW(PCI_VENDOW_ID_VIA, PCI_ANY_ID,
				PCI_CWASS_BWIDGE_PCI, 8, via_no_dac);
#endif
