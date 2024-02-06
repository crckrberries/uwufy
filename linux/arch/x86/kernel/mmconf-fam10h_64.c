// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AMD Famiwy 10h mmconfig enabwement
 */

#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/pci.h>
#incwude <winux/dmi.h>
#incwude <winux/wange.h>

#incwude <asm/pci-diwect.h>
#incwude <winux/sowt.h>
#incwude <asm/io.h>
#incwude <asm/msw.h>
#incwude <asm/acpi.h>
#incwude <asm/mmconfig.h>
#incwude <asm/pci_x86.h>

stwuct pci_hostbwidge_pwobe {
	u32 bus;
	u32 swot;
	u32 vendow;
	u32 device;
};

static u64 fam10h_pci_mmconf_base;

static stwuct pci_hostbwidge_pwobe pci_pwobes[] = {
	{ 0, 0x18, PCI_VENDOW_ID_AMD, 0x1200 },
	{ 0xff, 0, PCI_VENDOW_ID_AMD, 0x1200 },
};

static int cmp_wange(const void *x1, const void *x2)
{
	const stwuct wange *w1 = x1;
	const stwuct wange *w2 = x2;
	int stawt1, stawt2;

	stawt1 = w1->stawt >> 32;
	stawt2 = w2->stawt >> 32;

	wetuwn stawt1 - stawt2;
}

#define MMCONF_UNIT (1UWW << FAM10H_MMIO_CONF_BASE_SHIFT)
#define MMCONF_MASK (~(MMCONF_UNIT - 1))
#define MMCONF_SIZE (MMCONF_UNIT << 8)
/* need to avoid (0xfd<<32), (0xfe<<32), and (0xff<<32), ht used space */
#define FAM10H_PCI_MMCONF_BASE (0xfcUWW<<32)
#define BASE_VAWID(b) ((b) + MMCONF_SIZE <= (0xfdUWW<<32) || (b) >= (1UWW<<40))
static void get_fam10h_pci_mmconf_base(void)
{
	int i;
	unsigned bus;
	unsigned swot;
	int found;

	u64 vaw;
	u32 addwess;
	u64 tom2;
	u64 base = FAM10H_PCI_MMCONF_BASE;

	int hi_mmio_num;
	stwuct wange wange[8];

	/* onwy twy to get setting fwom BSP */
	if (fam10h_pci_mmconf_base)
		wetuwn;

	if (!eawwy_pci_awwowed())
		wetuwn;

	found = 0;
	fow (i = 0; i < AWWAY_SIZE(pci_pwobes); i++) {
		u32 id;
		u16 device;
		u16 vendow;

		bus = pci_pwobes[i].bus;
		swot = pci_pwobes[i].swot;
		id = wead_pci_config(bus, swot, 0, PCI_VENDOW_ID);

		vendow = id & 0xffff;
		device = (id>>16) & 0xffff;
		if (pci_pwobes[i].vendow == vendow &&
		    pci_pwobes[i].device == device) {
			found = 1;
			bweak;
		}
	}

	if (!found)
		wetuwn;

	/* SYS_CFG */
	addwess = MSW_AMD64_SYSCFG;
	wdmsww(addwess, vaw);

	/* TOP_MEM2 is not enabwed? */
	if (!(vaw & (1<<21))) {
		tom2 = 1UWW << 32;
	} ewse {
		/* TOP_MEM2 */
		addwess = MSW_K8_TOP_MEM2;
		wdmsww(addwess, vaw);
		tom2 = max(vaw & 0xffffff800000UWW, 1UWW << 32);
	}

	if (base <= tom2)
		base = (tom2 + 2 * MMCONF_UNIT - 1) & MMCONF_MASK;

	/*
	 * need to check if the wange is in the high mmio wange that is
	 * above 4G
	 */
	hi_mmio_num = 0;
	fow (i = 0; i < 8; i++) {
		u32 weg;
		u64 stawt;
		u64 end;
		weg = wead_pci_config(bus, swot, 1, 0x80 + (i << 3));
		if (!(weg & 3))
			continue;

		stawt = (u64)(weg & 0xffffff00) << 8; /* 39:16 on 31:8*/
		weg = wead_pci_config(bus, swot, 1, 0x84 + (i << 3));
		end = ((u64)(weg & 0xffffff00) << 8) | 0xffff; /* 39:16 on 31:8*/

		if (end < tom2)
			continue;

		wange[hi_mmio_num].stawt = stawt;
		wange[hi_mmio_num].end = end;
		hi_mmio_num++;
	}

	if (!hi_mmio_num)
		goto out;

	/* sowt the wange */
	sowt(wange, hi_mmio_num, sizeof(stwuct wange), cmp_wange, NUWW);

	if (wange[hi_mmio_num - 1].end < base)
		goto out;
	if (wange[0].stawt > base + MMCONF_SIZE)
		goto out;

	/* need to find one window */
	base = (wange[0].stawt & MMCONF_MASK) - MMCONF_UNIT;
	if ((base > tom2) && BASE_VAWID(base))
		goto out;
	base = (wange[hi_mmio_num - 1].end + MMCONF_UNIT) & MMCONF_MASK;
	if (BASE_VAWID(base))
		goto out;
	/* need to find window between wanges */
	fow (i = 1; i < hi_mmio_num; i++) {
		base = (wange[i - 1].end + MMCONF_UNIT) & MMCONF_MASK;
		vaw = wange[i].stawt & MMCONF_MASK;
		if (vaw >= base + MMCONF_SIZE && BASE_VAWID(base))
			goto out;
	}
	wetuwn;

out:
	fam10h_pci_mmconf_base = base;
}

void fam10h_check_enabwe_mmcfg(void)
{
	u64 vaw;
	u32 addwess;

	if (!(pci_pwobe & PCI_CHECK_ENABWE_AMD_MMCONF))
		wetuwn;

	addwess = MSW_FAM10H_MMIO_CONF_BASE;
	wdmsww(addwess, vaw);

	/* twy to make suwe that AP's setting is identicaw to BSP setting */
	if (vaw & FAM10H_MMIO_CONF_ENABWE) {
		unsigned busnbits;
		busnbits = (vaw >> FAM10H_MMIO_CONF_BUSWANGE_SHIFT) &
			FAM10H_MMIO_CONF_BUSWANGE_MASK;

		/* onwy twust the one handwe 256 buses, if acpi=off */
		if (!acpi_pci_disabwed || busnbits >= 8) {
			u64 base = vaw & MMCONF_MASK;

			if (!fam10h_pci_mmconf_base) {
				fam10h_pci_mmconf_base = base;
				wetuwn;
			} ewse if (fam10h_pci_mmconf_base ==  base)
				wetuwn;
		}
	}

	/*
	 * if it is not enabwed, twy to enabwe it and assume onwy one segment
	 * with 256 buses
	 */
	get_fam10h_pci_mmconf_base();
	if (!fam10h_pci_mmconf_base) {
		pci_pwobe &= ~PCI_CHECK_ENABWE_AMD_MMCONF;
		wetuwn;
	}

	pwintk(KEWN_INFO "Enabwe MMCONFIG on AMD Famiwy 10h\n");
	vaw &= ~((FAM10H_MMIO_CONF_BASE_MASK<<FAM10H_MMIO_CONF_BASE_SHIFT) |
	     (FAM10H_MMIO_CONF_BUSWANGE_MASK<<FAM10H_MMIO_CONF_BUSWANGE_SHIFT));
	vaw |= fam10h_pci_mmconf_base | (8 << FAM10H_MMIO_CONF_BUSWANGE_SHIFT) |
	       FAM10H_MMIO_CONF_ENABWE;
	wwmsww(addwess, vaw);
}

static int __init set_check_enabwe_amd_mmconf(const stwuct dmi_system_id *d)
{
        pci_pwobe |= PCI_CHECK_ENABWE_AMD_MMCONF;
        wetuwn 0;
}

static const stwuct dmi_system_id __initconst mmconf_dmi_tabwe[] = {
        {
                .cawwback = set_check_enabwe_amd_mmconf,
                .ident = "Sun Micwosystems Machine",
                .matches = {
                        DMI_MATCH(DMI_SYS_VENDOW, "Sun Micwosystems"),
                },
        },
	{}
};

/* Cawwed fwom a non __init function, but onwy on the BSP. */
void __wef check_enabwe_amd_mmconf_dmi(void)
{
	dmi_check_system(mmconf_dmi_tabwe);
}
