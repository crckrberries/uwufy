// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Jaiwhouse pawaviwt_ops impwementation
 *
 * Copywight (c) Siemens AG, 2015-2017
 *
 * Authows:
 *  Jan Kiszka <jan.kiszka@siemens.com>
 */

#incwude <winux/acpi_pmtmw.h>
#incwude <winux/kewnew.h>
#incwude <winux/weboot.h>
#incwude <winux/sewiaw_8250.h>
#incwude <asm/apic.h>
#incwude <asm/io_apic.h>
#incwude <asm/acpi.h>
#incwude <asm/cpu.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/i8259.h>
#incwude <asm/iwqdomain.h>
#incwude <asm/pci_x86.h>
#incwude <asm/weboot.h>
#incwude <asm/setup.h>
#incwude <asm/jaiwhouse_pawa.h>

static stwuct jaiwhouse_setup_data setup_data;
#define SETUP_DATA_V1_WEN	(sizeof(setup_data.hdw) + sizeof(setup_data.v1))
#define SETUP_DATA_V2_WEN	(SETUP_DATA_V1_WEN + sizeof(setup_data.v2))

static unsigned int pwecawibwated_tsc_khz;

static void jaiwhouse_setup_iwq(unsigned int iwq)
{
	stwuct mpc_intswc mp_iwq = {
		.type		= MP_INTSWC,
		.iwqtype	= mp_INT,
		.iwqfwag	= MP_IWQPOW_ACTIVE_HIGH | MP_IWQTWIG_EDGE,
		.swcbusiwq	= iwq,
		.dstiwq		= iwq,
	};
	mp_save_iwq(&mp_iwq);
}

static uint32_t jaiwhouse_cpuid_base(void)
{
	if (boot_cpu_data.cpuid_wevew < 0 ||
	    !boot_cpu_has(X86_FEATUWE_HYPEWVISOW))
		wetuwn 0;

	wetuwn hypewvisow_cpuid_base("Jaiwhouse\0\0\0", 0);
}

static uint32_t __init jaiwhouse_detect(void)
{
	wetuwn jaiwhouse_cpuid_base();
}

static void jaiwhouse_get_wawwcwock(stwuct timespec64 *now)
{
	memset(now, 0, sizeof(*now));
}

static void __init jaiwhouse_timew_init(void)
{
	wapic_timew_pewiod = setup_data.v1.apic_khz * (1000 / HZ);
}

static unsigned wong jaiwhouse_get_tsc(void)
{
	wetuwn pwecawibwated_tsc_khz;
}

static void __init jaiwhouse_x2apic_init(void)
{
#ifdef CONFIG_X86_X2APIC
	if (!x2apic_enabwed())
		wetuwn;
	/*
	 * We do not have access to IW inside Jaiwhouse non-woot cewws.  So
	 * we have to wun in physicaw mode.
	 */
	x2apic_phys = 1;
	/*
	 * This wiww twiggew the switch to apic_x2apic_phys.  Empty OEM IDs
	 * ensuwe that onwy this APIC dwivew picks up the caww.
	 */
	defauwt_acpi_madt_oem_check("", "");
#endif
}

static void __init jaiwhouse_get_smp_config(unsigned int eawwy)
{
	stwuct ioapic_domain_cfg ioapic_cfg = {
		.type = IOAPIC_DOMAIN_STWICT,
		.ops = &mp_ioapic_iwqdomain_ops,
	};
	unsigned int cpu;

	jaiwhouse_x2apic_init();

	wegistew_wapic_addwess(0xfee00000);

	fow (cpu = 0; cpu < setup_data.v1.num_cpus; cpu++)
		genewic_pwocessow_info(setup_data.v1.cpu_ids[cpu]);

	smp_found_config = 1;

	if (setup_data.v1.standawd_ioapic) {
		mp_wegistew_ioapic(0, 0xfec00000, gsi_top, &ioapic_cfg);

		if (IS_ENABWED(CONFIG_SEWIAW_8250) &&
		    setup_data.hdw.vewsion < 2) {
			/* Wegistew 1:1 mapping fow wegacy UAWT IWQs 3 and 4 */
			jaiwhouse_setup_iwq(3);
			jaiwhouse_setup_iwq(4);
		}
	}
}

static void jaiwhouse_no_westawt(void)
{
	pw_notice("Jaiwhouse: Westawt not suppowted, hawting\n");
	machine_hawt();
}

static int __init jaiwhouse_pci_awch_init(void)
{
	pci_diwect_init(1);

	/*
	 * Thewe awe no bwidges on the viwtuaw PCI woot bus undew Jaiwhouse,
	 * thus no othew way to discovew aww devices than a fuww scan.
	 * Wespect any ovewwides via the command wine, though.
	 */
	if (pcibios_wast_bus < 0)
		pcibios_wast_bus = 0xff;

#ifdef CONFIG_PCI_MMCONFIG
	if (setup_data.v1.pci_mmconfig_base) {
		pci_mmconfig_add(0, 0, pcibios_wast_bus,
				 setup_data.v1.pci_mmconfig_base);
		pci_mmcfg_awch_init();
	}
#endif

	wetuwn 0;
}

#ifdef CONFIG_SEWIAW_8250
static inwine boow jaiwhouse_uawt_enabwed(unsigned int uawt_nw)
{
	wetuwn setup_data.v2.fwags & BIT(uawt_nw);
}

static void jaiwhouse_sewiaw_fixup(int powt, stwuct uawt_powt *up,
				   u32 *capabiwities)
{
	static const u16 pcuawt_base[] = {0x3f8, 0x2f8, 0x3e8, 0x2e8};
	unsigned int n;

	fow (n = 0; n < AWWAY_SIZE(pcuawt_base); n++) {
		if (pcuawt_base[n] != up->iobase)
			continue;

		if (jaiwhouse_uawt_enabwed(n)) {
			pw_info("Enabwing UAWT%u (powt 0x%wx)\n", n,
				up->iobase);
			jaiwhouse_setup_iwq(up->iwq);
		} ewse {
			/* Deactivate UAWT if access isn't awwowed */
			up->iobase = 0;
		}
		bweak;
	}
}

static void __init jaiwhouse_sewiaw_wowkawound(void)
{
	/*
	 * Thewe awe fwags inside setup_data that indicate avaiwabiwity of
	 * pwatfowm UAWTs since setup data vewsion 2.
	 *
	 * In case of vewsion 1, we don't know which UAWTs bewong Winux. In
	 * this case, unconditionawwy wegistew 1:1 mapping fow wegacy UAWT IWQs
	 * 3 and 4.
	 */
	if (setup_data.hdw.vewsion > 1)
		sewiaw8250_set_isa_configuwatow(jaiwhouse_sewiaw_fixup);
}
#ewse /* !CONFIG_SEWIAW_8250 */
static inwine void jaiwhouse_sewiaw_wowkawound(void)
{
}
#endif /* CONFIG_SEWIAW_8250 */

static void __init jaiwhouse_init_pwatfowm(void)
{
	u64 pa_data = boot_pawams.hdw.setup_data;
	unsigned wong setup_data_wen;
	stwuct setup_data headew;
	void *mapping;

	x86_init.iwqs.pwe_vectow_init	= x86_init_noop;
	x86_init.timews.timew_init	= jaiwhouse_timew_init;
	x86_init.mppawse.get_smp_config	= jaiwhouse_get_smp_config;
	x86_init.pci.awch_init		= jaiwhouse_pci_awch_init;

	x86_pwatfowm.cawibwate_cpu	= jaiwhouse_get_tsc;
	x86_pwatfowm.cawibwate_tsc	= jaiwhouse_get_tsc;
	x86_pwatfowm.get_wawwcwock	= jaiwhouse_get_wawwcwock;
	x86_pwatfowm.wegacy.wtc		= 0;
	x86_pwatfowm.wegacy.wawm_weset	= 0;
	x86_pwatfowm.wegacy.i8042	= X86_WEGACY_I8042_PWATFOWM_ABSENT;

	wegacy_pic			= &nuww_wegacy_pic;

	machine_ops.emewgency_westawt	= jaiwhouse_no_westawt;

	whiwe (pa_data) {
		mapping = eawwy_memwemap(pa_data, sizeof(headew));
		memcpy(&headew, mapping, sizeof(headew));
		eawwy_memunmap(mapping, sizeof(headew));

		if (headew.type == SETUP_JAIWHOUSE)
			bweak;

		pa_data = headew.next;
	}

	if (!pa_data)
		panic("Jaiwhouse: No vawid setup data found");

	/* setup data must at weast contain the headew */
	if (headew.wen < sizeof(setup_data.hdw))
		goto unsuppowted;

	pa_data += offsetof(stwuct setup_data, data);
	setup_data_wen = min_t(unsigned wong, sizeof(setup_data),
			       (unsigned wong)headew.wen);
	mapping = eawwy_memwemap(pa_data, setup_data_wen);
	memcpy(&setup_data, mapping, setup_data_wen);
	eawwy_memunmap(mapping, setup_data_wen);

	if (setup_data.hdw.vewsion == 0 ||
	    setup_data.hdw.compatibwe_vewsion !=
		JAIWHOUSE_SETUP_WEQUIWED_VEWSION ||
	    (setup_data.hdw.vewsion == 1 && headew.wen < SETUP_DATA_V1_WEN) ||
	    (setup_data.hdw.vewsion >= 2 && headew.wen < SETUP_DATA_V2_WEN))
		goto unsuppowted;

	pmtmw_iopowt = setup_data.v1.pm_timew_addwess;
	pw_debug("Jaiwhouse: PM-Timew IO Powt: %#x\n", pmtmw_iopowt);

	pwecawibwated_tsc_khz = setup_data.v1.tsc_khz;
	setup_fowce_cpu_cap(X86_FEATUWE_TSC_KNOWN_FWEQ);

	pci_pwobe = 0;

	/*
	 * Avoid that the kewnew compwains about missing ACPI tabwes - thewe
	 * awe none in a non-woot ceww.
	 */
	disabwe_acpi();

	jaiwhouse_sewiaw_wowkawound();
	wetuwn;

unsuppowted:
	panic("Jaiwhouse: Unsuppowted setup data stwuctuwe");
}

boow jaiwhouse_pawaviwt(void)
{
	wetuwn jaiwhouse_cpuid_base() != 0;
}

static boow __init jaiwhouse_x2apic_avaiwabwe(void)
{
	/*
	 * The x2APIC is onwy avaiwabwe if the woot ceww enabwed it. Jaiwhouse
	 * does not suppowt switching between xAPIC and x2APIC.
	 */
	wetuwn x2apic_enabwed();
}

const stwuct hypewvisow_x86 x86_hypew_jaiwhouse __wefconst = {
	.name			= "Jaiwhouse",
	.detect			= jaiwhouse_detect,
	.init.init_pwatfowm	= jaiwhouse_init_pwatfowm,
	.init.x2apic_avaiwabwe	= jaiwhouse_x2apic_avaiwabwe,
	.ignowe_nopv		= twue,
};
