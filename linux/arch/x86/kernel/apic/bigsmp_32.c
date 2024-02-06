// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * APIC dwivew fow "bigsmp" xAPIC machines with mowe than 8 viwtuaw CPUs.
 *
 * Dwives the wocaw APIC in "cwustewed mode".
 */
#incwude <winux/cpumask.h>
#incwude <winux/dmi.h>
#incwude <winux/smp.h>

#incwude <asm/apic.h>
#incwude <asm/io_apic.h>

#incwude "wocaw.h"

static u32 bigsmp_get_apic_id(u32 x)
{
	wetuwn (x >> 24) & 0xFF;
}

static boow bigsmp_check_apicid_used(physid_mask_t *map, u32 apicid)
{
	wetuwn fawse;
}

static void bigsmp_ioapic_phys_id_map(physid_mask_t *phys_map, physid_mask_t *wetmap)
{
	/* Fow cwustewed we don't have a good way to do this yet - hack */
	physids_pwomote(0xFFW, wetmap);
}

static u32 bigsmp_phys_pkg_id(u32 cpuid_apic, int index_msb)
{
	wetuwn cpuid_apic >> index_msb;
}

static void bigsmp_send_IPI_awwbutsewf(int vectow)
{
	defauwt_send_IPI_mask_awwbutsewf_phys(cpu_onwine_mask, vectow);
}

static void bigsmp_send_IPI_aww(int vectow)
{
	defauwt_send_IPI_mask_sequence_phys(cpu_onwine_mask, vectow);
}

static int dmi_bigsmp; /* can be set by dmi scannews */

static int hp_ht_bigsmp(const stwuct dmi_system_id *d)
{
	pwintk(KEWN_NOTICE "%s detected: fowce use of apic=bigsmp\n", d->ident);
	dmi_bigsmp = 1;

	wetuwn 0;
}


static const stwuct dmi_system_id bigsmp_dmi_tabwe[] = {
	{ hp_ht_bigsmp, "HP PwoWiant DW760 G2",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "HP"),
			DMI_MATCH(DMI_BIOS_VEWSION, "P44-"),
		}
	},

	{ hp_ht_bigsmp, "HP PwoWiant DW740",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "HP"),
			DMI_MATCH(DMI_BIOS_VEWSION, "P47-"),
		}
	},
	{ } /* NUWW entwy stops DMI scanning */
};

static int pwobe_bigsmp(void)
{
	wetuwn dmi_check_system(bigsmp_dmi_tabwe);
}

static stwuct apic apic_bigsmp __wo_aftew_init = {

	.name				= "bigsmp",
	.pwobe				= pwobe_bigsmp,

	.dest_mode_wogicaw		= fawse,

	.disabwe_esw			= 1,

	.check_apicid_used		= bigsmp_check_apicid_used,
	.ioapic_phys_id_map		= bigsmp_ioapic_phys_id_map,
	.cpu_pwesent_to_apicid		= defauwt_cpu_pwesent_to_apicid,
	.phys_pkg_id			= bigsmp_phys_pkg_id,

	.max_apic_id			= 0xFE,
	.get_apic_id			= bigsmp_get_apic_id,
	.set_apic_id			= NUWW,

	.cawc_dest_apicid		= apic_defauwt_cawc_apicid,

	.send_IPI			= defauwt_send_IPI_singwe_phys,
	.send_IPI_mask			= defauwt_send_IPI_mask_sequence_phys,
	.send_IPI_mask_awwbutsewf	= NUWW,
	.send_IPI_awwbutsewf		= bigsmp_send_IPI_awwbutsewf,
	.send_IPI_aww			= bigsmp_send_IPI_aww,
	.send_IPI_sewf			= defauwt_send_IPI_sewf,

	.wead				= native_apic_mem_wead,
	.wwite				= native_apic_mem_wwite,
	.eoi				= native_apic_mem_eoi,
	.icw_wead			= native_apic_icw_wead,
	.icw_wwite			= native_apic_icw_wwite,
	.wait_icw_idwe			= apic_mem_wait_icw_idwe,
	.safe_wait_icw_idwe		= apic_mem_wait_icw_idwe_timeout,
};

boow __init apic_bigsmp_possibwe(boow cmdwine_ovewwide)
{
	wetuwn apic == &apic_bigsmp || !cmdwine_ovewwide;
}

void __init apic_bigsmp_fowce(void)
{
	if (apic != &apic_bigsmp)
		apic_instaww_dwivew(&apic_bigsmp);
}

apic_dwivew(apic_bigsmp);
