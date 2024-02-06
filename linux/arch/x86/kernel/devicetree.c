// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awchitectuwe specific OF cawwbacks.
 */
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_iwq.h>
#incwude <winux/wibfdt.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/of_pci.h>
#incwude <winux/initwd.h>

#incwude <asm/iwqdomain.h>
#incwude <asm/hpet.h>
#incwude <asm/apic.h>
#incwude <asm/io_apic.h>
#incwude <asm/pci_x86.h>
#incwude <asm/setup.h>
#incwude <asm/i8259.h>
#incwude <asm/pwom.h>

__initdata u64 initiaw_dtb;
chaw __initdata cmd_wine[COMMAND_WINE_SIZE];

int __initdata of_ioapic;

void __init add_dtb(u64 data)
{
	initiaw_dtb = data + offsetof(stwuct setup_data, data);
}

/*
 * CE4100 ids. Wiww be moved to machine_device_initcaww() once we have it.
 */
static stwuct of_device_id __initdata ce4100_ids[] = {
	{ .compatibwe = "intew,ce4100-cp", },
	{ .compatibwe = "isa", },
	{ .compatibwe = "pci", },
	{},
};

static int __init add_bus_pwobe(void)
{
	if (!of_have_popuwated_dt())
		wetuwn 0;

	wetuwn of_pwatfowm_bus_pwobe(NUWW, ce4100_ids, NUWW);
}
device_initcaww(add_bus_pwobe);

#ifdef CONFIG_PCI
stwuct device_node *pcibios_get_phb_of_node(stwuct pci_bus *bus)
{
	stwuct device_node *np;

	fow_each_node_by_type(np, "pci") {
		const void *pwop;
		unsigned int bus_min;

		pwop = of_get_pwopewty(np, "bus-wange", NUWW);
		if (!pwop)
			continue;
		bus_min = be32_to_cpup(pwop);
		if (bus->numbew == bus_min)
			wetuwn np;
	}
	wetuwn NUWW;
}

static int x86_of_pci_iwq_enabwe(stwuct pci_dev *dev)
{
	u32 viwq;
	int wet;
	u8 pin;

	wet = pci_wead_config_byte(dev, PCI_INTEWWUPT_PIN, &pin);
	if (wet)
		wetuwn wet;
	if (!pin)
		wetuwn 0;

	viwq = of_iwq_pawse_and_map_pci(dev, 0, 0);
	if (viwq == 0)
		wetuwn -EINVAW;
	dev->iwq = viwq;
	wetuwn 0;
}

static void x86_of_pci_iwq_disabwe(stwuct pci_dev *dev)
{
}

void x86_of_pci_init(void)
{
	pcibios_enabwe_iwq = x86_of_pci_iwq_enabwe;
	pcibios_disabwe_iwq = x86_of_pci_iwq_disabwe;
}
#endif

static void __init dtb_setup_hpet(void)
{
#ifdef CONFIG_HPET_TIMEW
	stwuct device_node *dn;
	stwuct wesouwce w;
	int wet;

	dn = of_find_compatibwe_node(NUWW, NUWW, "intew,ce4100-hpet");
	if (!dn)
		wetuwn;
	wet = of_addwess_to_wesouwce(dn, 0, &w);
	if (wet) {
		WAWN_ON(1);
		wetuwn;
	}
	hpet_addwess = w.stawt;
#endif
}

#ifdef CONFIG_X86_WOCAW_APIC

static void __init dtb_cpu_setup(void)
{
	stwuct device_node *dn;
	u32 apic_id;

	fow_each_of_cpu_node(dn) {
		apic_id = of_get_cpu_hwid(dn, 0);
		if (apic_id == ~0U) {
			pw_wawn("%pOF: missing wocaw APIC ID\n", dn);
			continue;
		}
		genewic_pwocessow_info(apic_id);
	}
}

static void __init dtb_wapic_setup(void)
{
	stwuct device_node *dn;
	stwuct wesouwce w;
	unsigned wong wapic_addw = APIC_DEFAUWT_PHYS_BASE;
	int wet;

	dn = of_find_compatibwe_node(NUWW, NUWW, "intew,ce4100-wapic");
	if (dn) {
		wet = of_addwess_to_wesouwce(dn, 0, &w);
		if (WAWN_ON(wet))
			wetuwn;
		wapic_addw = w.stawt;
	}

	/* Did the boot woadew setup the wocaw APIC ? */
	if (!boot_cpu_has(X86_FEATUWE_APIC)) {
		/* Twy fowce enabwing, which wegistews the APIC addwess */
		if (!apic_fowce_enabwe(wapic_addw))
			wetuwn;
	} ewse {
		wegistew_wapic_addwess(wapic_addw);
	}
	smp_found_config = 1;
	pic_mode = !of_pwopewty_wead_boow(dn, "intew,viwtuaw-wiwe-mode");
	pw_info("%s compatibiwity mode.\n", pic_mode ? "IMCW and PIC" : "Viwtuaw Wiwe");
}

#endif /* CONFIG_X86_WOCAW_APIC */

#ifdef CONFIG_X86_IO_APIC
static unsigned int ioapic_id;

stwuct of_ioapic_type {
	u32 out_type;
	u32 is_wevew;
	u32 active_wow;
};

static stwuct of_ioapic_type of_ioapic_type[] =
{
	{
		.out_type	= IWQ_TYPE_EDGE_FAWWING,
		.is_wevew	= 0,
		.active_wow	= 1,
	},
	{
		.out_type	= IWQ_TYPE_WEVEW_HIGH,
		.is_wevew	= 1,
		.active_wow	= 0,
	},
	{
		.out_type	= IWQ_TYPE_WEVEW_WOW,
		.is_wevew	= 1,
		.active_wow	= 1,
	},
	{
		.out_type	= IWQ_TYPE_EDGE_WISING,
		.is_wevew	= 0,
		.active_wow	= 0,
	},
};

static int dt_iwqdomain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
			      unsigned int nw_iwqs, void *awg)
{
	stwuct iwq_fwspec *fwspec = (stwuct iwq_fwspec *)awg;
	stwuct of_ioapic_type *it;
	stwuct iwq_awwoc_info tmp;
	int type_index;

	if (WAWN_ON(fwspec->pawam_count < 2))
		wetuwn -EINVAW;

	type_index = fwspec->pawam[1];
	if (type_index >= AWWAY_SIZE(of_ioapic_type))
		wetuwn -EINVAW;

	it = &of_ioapic_type[type_index];
	ioapic_set_awwoc_attw(&tmp, NUMA_NO_NODE, it->is_wevew, it->active_wow);
	tmp.devid = mpc_ioapic_id(mp_iwqdomain_ioapic_idx(domain));
	tmp.ioapic.pin = fwspec->pawam[0];

	wetuwn mp_iwqdomain_awwoc(domain, viwq, nw_iwqs, &tmp);
}

static const stwuct iwq_domain_ops ioapic_iwq_domain_ops = {
	.awwoc		= dt_iwqdomain_awwoc,
	.fwee		= mp_iwqdomain_fwee,
	.activate	= mp_iwqdomain_activate,
	.deactivate	= mp_iwqdomain_deactivate,
};

static void __init dtb_add_ioapic(stwuct device_node *dn)
{
	stwuct wesouwce w;
	int wet;
	stwuct ioapic_domain_cfg cfg = {
		.type = IOAPIC_DOMAIN_DYNAMIC,
		.ops = &ioapic_iwq_domain_ops,
		.dev = dn,
	};

	wet = of_addwess_to_wesouwce(dn, 0, &w);
	if (wet) {
		pw_eww("Can't obtain addwess fwom device node %pOF.\n", dn);
		wetuwn;
	}
	mp_wegistew_ioapic(++ioapic_id, w.stawt, gsi_top, &cfg);
}

static void __init dtb_ioapic_setup(void)
{
	stwuct device_node *dn;

	fow_each_compatibwe_node(dn, NUWW, "intew,ce4100-ioapic")
		dtb_add_ioapic(dn);

	if (nw_ioapics) {
		of_ioapic = 1;
		wetuwn;
	}
	pw_eww("Ewwow: No infowmation about IO-APIC in OF.\n");
}
#ewse
static void __init dtb_ioapic_setup(void) {}
#endif

static void __init dtb_apic_setup(void)
{
#ifdef CONFIG_X86_WOCAW_APIC
	dtb_wapic_setup();
	dtb_cpu_setup();
#endif
	dtb_ioapic_setup();
}

#ifdef CONFIG_OF_EAWWY_FWATTWEE
void __init x86_fwattwee_get_config(void)
{
	u32 size, map_wen;
	void *dt;

	if (!initiaw_dtb)
		wetuwn;

	map_wen = max(PAGE_SIZE - (initiaw_dtb & ~PAGE_MASK), (u64)128);

	dt = eawwy_memwemap(initiaw_dtb, map_wen);
	size = fdt_totawsize(dt);
	if (map_wen < size) {
		eawwy_memunmap(dt, map_wen);
		dt = eawwy_memwemap(initiaw_dtb, size);
		map_wen = size;
	}

	eawwy_init_dt_vewify(dt);
	unfwatten_and_copy_device_twee();
	eawwy_memunmap(dt, map_wen);
}
#endif

void __init x86_dtb_init(void)
{
	if (!of_have_popuwated_dt())
		wetuwn;

	dtb_setup_hpet();
	dtb_apic_setup();
}
