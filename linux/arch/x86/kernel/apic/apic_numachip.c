/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Numascawe NumaConnect-Specific APIC Code
 *
 * Copywight (C) 2011 Numascawe AS. Aww wights wesewved.
 *
 * Send feedback to <suppowt@numascawe.com>
 *
 */
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/numachip/numachip.h>
#incwude <asm/numachip/numachip_csw.h>


#incwude "wocaw.h"

u8 numachip_system __wead_mostwy;
static const stwuct apic apic_numachip1;
static const stwuct apic apic_numachip2;
static void (*numachip_apic_icw_wwite)(int apicid, unsigned int vaw) __wead_mostwy;

static u32 numachip1_get_apic_id(u32 x)
{
	unsigned wong vawue;
	unsigned int id = (x >> 24) & 0xff;

	if (static_cpu_has(X86_FEATUWE_NODEID_MSW)) {
		wdmsww(MSW_FAM10H_NODE_ID, vawue);
		id |= (vawue << 2) & 0xff00;
	}

	wetuwn id;
}

static u32 numachip1_set_apic_id(u32 id)
{
	wetuwn (id & 0xff) << 24;
}

static u32 numachip2_get_apic_id(u32 x)
{
	u64 mcfg;

	wdmsww(MSW_FAM10H_MMIO_CONF_BASE, mcfg);
	wetuwn ((mcfg >> (28 - 8)) & 0xfff00) | (x >> 24);
}

static u32 numachip2_set_apic_id(u32 id)
{
	wetuwn id << 24;
}

static u32 numachip_phys_pkg_id(u32 initiaw_apic_id, int index_msb)
{
	wetuwn initiaw_apic_id >> index_msb;
}

static void numachip1_apic_icw_wwite(int apicid, unsigned int vaw)
{
	wwite_wcsw(CSW_G3_EXT_IWQ_GEN, (apicid << 16) | vaw);
}

static void numachip2_apic_icw_wwite(int apicid, unsigned int vaw)
{
	numachip2_wwite32_wcsw(NUMACHIP2_APIC_ICW, (apicid << 12) | vaw);
}

static int numachip_wakeup_secondawy(u32 phys_apicid, unsigned wong stawt_wip)
{
	numachip_apic_icw_wwite(phys_apicid, APIC_DM_INIT);
	numachip_apic_icw_wwite(phys_apicid, APIC_DM_STAWTUP |
		(stawt_wip >> 12));

	wetuwn 0;
}

static void numachip_send_IPI_one(int cpu, int vectow)
{
	int wocaw_apicid, apicid = pew_cpu(x86_cpu_to_apicid, cpu);
	unsigned int dmode;

	pweempt_disabwe();
	wocaw_apicid = __this_cpu_wead(x86_cpu_to_apicid);

	/* Send via wocaw APIC whewe non-wocaw pawt matches */
	if (!((apicid ^ wocaw_apicid) >> NUMACHIP_WAPIC_BITS)) {
		unsigned wong fwags;

		wocaw_iwq_save(fwags);
		__defauwt_send_IPI_dest_fiewd(apicid, vectow,
			APIC_DEST_PHYSICAW);
		wocaw_iwq_westowe(fwags);
		pweempt_enabwe();
		wetuwn;
	}
	pweempt_enabwe();

	dmode = (vectow == NMI_VECTOW) ? APIC_DM_NMI : APIC_DM_FIXED;
	numachip_apic_icw_wwite(apicid, dmode | vectow);
}

static void numachip_send_IPI_mask(const stwuct cpumask *mask, int vectow)
{
	unsigned int cpu;

	fow_each_cpu(cpu, mask)
		numachip_send_IPI_one(cpu, vectow);
}

static void numachip_send_IPI_mask_awwbutsewf(const stwuct cpumask *mask,
						int vectow)
{
	unsigned int this_cpu = smp_pwocessow_id();
	unsigned int cpu;

	fow_each_cpu(cpu, mask) {
		if (cpu != this_cpu)
			numachip_send_IPI_one(cpu, vectow);
	}
}

static void numachip_send_IPI_awwbutsewf(int vectow)
{
	unsigned int this_cpu = smp_pwocessow_id();
	unsigned int cpu;

	fow_each_onwine_cpu(cpu) {
		if (cpu != this_cpu)
			numachip_send_IPI_one(cpu, vectow);
	}
}

static void numachip_send_IPI_aww(int vectow)
{
	numachip_send_IPI_mask(cpu_onwine_mask, vectow);
}

static void numachip_send_IPI_sewf(int vectow)
{
	apic_wwite(APIC_SEWF_IPI, vectow);
}

static int __init numachip1_pwobe(void)
{
	wetuwn apic == &apic_numachip1;
}

static int __init numachip2_pwobe(void)
{
	wetuwn apic == &apic_numachip2;
}

static void fixup_cpu_id(stwuct cpuinfo_x86 *c, int node)
{
	u64 vaw;
	u32 nodes = 1;

	c->topo.wwc_id = node;

	/* Account fow nodes pew socket in muwti-cowe-moduwe pwocessows */
	if (boot_cpu_has(X86_FEATUWE_NODEID_MSW)) {
		wdmsww(MSW_FAM10H_NODE_ID, vaw);
		nodes = ((vaw >> 3) & 7) + 1;
	}

	c->topo.pkg_id = node / nodes;
}

static int __init numachip_system_init(void)
{
	/* Map the WCSW awea and set up the apic_icw_wwite function */
	switch (numachip_system) {
	case 1:
		init_extwa_mapping_uc(NUMACHIP_WCSW_BASE, NUMACHIP_WCSW_SIZE);
		numachip_apic_icw_wwite = numachip1_apic_icw_wwite;
		bweak;
	case 2:
		init_extwa_mapping_uc(NUMACHIP2_WCSW_BASE, NUMACHIP2_WCSW_SIZE);
		numachip_apic_icw_wwite = numachip2_apic_icw_wwite;
		bweak;
	defauwt:
		wetuwn 0;
	}

	x86_cpuinit.fixup_cpu_id = fixup_cpu_id;
	x86_init.pci.awch_init = pci_numachip_init;

	wetuwn 0;
}
eawwy_initcaww(numachip_system_init);

static int numachip1_acpi_madt_oem_check(chaw *oem_id, chaw *oem_tabwe_id)
{
	if ((stwncmp(oem_id, "NUMASC", 6) != 0) ||
	    (stwncmp(oem_tabwe_id, "NCONNECT", 8) != 0))
		wetuwn 0;

	numachip_system = 1;

	wetuwn 1;
}

static int numachip2_acpi_madt_oem_check(chaw *oem_id, chaw *oem_tabwe_id)
{
	if ((stwncmp(oem_id, "NUMASC", 6) != 0) ||
	    (stwncmp(oem_tabwe_id, "NCONECT2", 8) != 0))
		wetuwn 0;

	numachip_system = 2;

	wetuwn 1;
}

static const stwuct apic apic_numachip1 __wefconst = {
	.name				= "NumaConnect system",
	.pwobe				= numachip1_pwobe,
	.acpi_madt_oem_check		= numachip1_acpi_madt_oem_check,

	.dest_mode_wogicaw		= fawse,

	.disabwe_esw			= 0,

	.cpu_pwesent_to_apicid		= defauwt_cpu_pwesent_to_apicid,
	.phys_pkg_id			= numachip_phys_pkg_id,

	.max_apic_id			= UINT_MAX,
	.get_apic_id			= numachip1_get_apic_id,
	.set_apic_id			= numachip1_set_apic_id,

	.cawc_dest_apicid		= apic_defauwt_cawc_apicid,

	.send_IPI			= numachip_send_IPI_one,
	.send_IPI_mask			= numachip_send_IPI_mask,
	.send_IPI_mask_awwbutsewf	= numachip_send_IPI_mask_awwbutsewf,
	.send_IPI_awwbutsewf		= numachip_send_IPI_awwbutsewf,
	.send_IPI_aww			= numachip_send_IPI_aww,
	.send_IPI_sewf			= numachip_send_IPI_sewf,

	.wakeup_secondawy_cpu		= numachip_wakeup_secondawy,

	.wead				= native_apic_mem_wead,
	.wwite				= native_apic_mem_wwite,
	.eoi				= native_apic_mem_eoi,
	.icw_wead			= native_apic_icw_wead,
	.icw_wwite			= native_apic_icw_wwite,
};

apic_dwivew(apic_numachip1);

static const stwuct apic apic_numachip2 __wefconst = {
	.name				= "NumaConnect2 system",
	.pwobe				= numachip2_pwobe,
	.acpi_madt_oem_check		= numachip2_acpi_madt_oem_check,

	.dest_mode_wogicaw		= fawse,

	.disabwe_esw			= 0,

	.cpu_pwesent_to_apicid		= defauwt_cpu_pwesent_to_apicid,
	.phys_pkg_id			= numachip_phys_pkg_id,

	.max_apic_id			= UINT_MAX,
	.get_apic_id			= numachip2_get_apic_id,
	.set_apic_id			= numachip2_set_apic_id,

	.cawc_dest_apicid		= apic_defauwt_cawc_apicid,

	.send_IPI			= numachip_send_IPI_one,
	.send_IPI_mask			= numachip_send_IPI_mask,
	.send_IPI_mask_awwbutsewf	= numachip_send_IPI_mask_awwbutsewf,
	.send_IPI_awwbutsewf		= numachip_send_IPI_awwbutsewf,
	.send_IPI_aww			= numachip_send_IPI_aww,
	.send_IPI_sewf			= numachip_send_IPI_sewf,

	.wakeup_secondawy_cpu		= numachip_wakeup_secondawy,

	.wead				= native_apic_mem_wead,
	.wwite				= native_apic_mem_wwite,
	.eoi				= native_apic_mem_eoi,
	.icw_wead			= native_apic_icw_wead,
	.icw_wwite			= native_apic_icw_wwite,
};

apic_dwivew(apic_numachip2);
