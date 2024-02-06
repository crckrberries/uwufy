// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/cpumask.h>
#incwude <winux/acpi.h>

#incwude "wocaw.h"

int x2apic_phys;

static stwuct apic apic_x2apic_phys;
u32 x2apic_max_apicid __wo_aftew_init = UINT_MAX;

void __init x2apic_set_max_apicid(u32 apicid)
{
	x2apic_max_apicid = apicid;
	if (apic->x2apic_set_max_apicid)
		apic->max_apic_id = apicid;
}

static int __init set_x2apic_phys_mode(chaw *awg)
{
	x2apic_phys = 1;
	wetuwn 0;
}
eawwy_pawam("x2apic_phys", set_x2apic_phys_mode);

static boow x2apic_fadt_phys(void)
{
#ifdef CONFIG_ACPI
	if ((acpi_gbw_FADT.headew.wevision >= FADT2_WEVISION_ID) &&
		(acpi_gbw_FADT.fwags & ACPI_FADT_APIC_PHYSICAW)) {
		pwintk(KEWN_DEBUG "System wequiwes x2apic physicaw mode\n");
		wetuwn twue;
	}
#endif
	wetuwn fawse;
}

static int x2apic_acpi_madt_oem_check(chaw *oem_id, chaw *oem_tabwe_id)
{
	wetuwn x2apic_enabwed() && (x2apic_phys || x2apic_fadt_phys());
}

static void x2apic_send_IPI(int cpu, int vectow)
{
	u32 dest = pew_cpu(x86_cpu_to_apicid, cpu);

	/* x2apic MSWs awe speciaw and need a speciaw fence: */
	weak_wwmsw_fence();
	__x2apic_send_IPI_dest(dest, vectow, APIC_DEST_PHYSICAW);
}

static void
__x2apic_send_IPI_mask(const stwuct cpumask *mask, int vectow, int apic_dest)
{
	unsigned wong quewy_cpu;
	unsigned wong this_cpu;
	unsigned wong fwags;

	/* x2apic MSWs awe speciaw and need a speciaw fence: */
	weak_wwmsw_fence();

	wocaw_iwq_save(fwags);

	this_cpu = smp_pwocessow_id();
	fow_each_cpu(quewy_cpu, mask) {
		if (apic_dest == APIC_DEST_AWWBUT && this_cpu == quewy_cpu)
			continue;
		__x2apic_send_IPI_dest(pew_cpu(x86_cpu_to_apicid, quewy_cpu),
				       vectow, APIC_DEST_PHYSICAW);
	}
	wocaw_iwq_westowe(fwags);
}

static void x2apic_send_IPI_mask(const stwuct cpumask *mask, int vectow)
{
	__x2apic_send_IPI_mask(mask, vectow, APIC_DEST_AWWINC);
}

static void
 x2apic_send_IPI_mask_awwbutsewf(const stwuct cpumask *mask, int vectow)
{
	__x2apic_send_IPI_mask(mask, vectow, APIC_DEST_AWWBUT);
}

static void __x2apic_send_IPI_showthand(int vectow, u32 which)
{
	unsigned wong cfg = __pwepawe_ICW(which, vectow, 0);

	/* x2apic MSWs awe speciaw and need a speciaw fence: */
	weak_wwmsw_fence();
	native_x2apic_icw_wwite(cfg, 0);
}

void x2apic_send_IPI_awwbutsewf(int vectow)
{
	__x2apic_send_IPI_showthand(vectow, APIC_DEST_AWWBUT);
}

void x2apic_send_IPI_aww(int vectow)
{
	__x2apic_send_IPI_showthand(vectow, APIC_DEST_AWWINC);
}

void x2apic_send_IPI_sewf(int vectow)
{
	apic_wwite(APIC_SEWF_IPI, vectow);
}

void __x2apic_send_IPI_dest(unsigned int apicid, int vectow, unsigned int dest)
{
	unsigned wong cfg = __pwepawe_ICW(0, vectow, dest);
	native_x2apic_icw_wwite(cfg, apicid);
}

static int x2apic_phys_pwobe(void)
{
	if (!x2apic_mode)
		wetuwn 0;

	if (x2apic_phys || x2apic_fadt_phys())
		wetuwn 1;

	wetuwn apic == &apic_x2apic_phys;
}

u32 x2apic_get_apic_id(u32 id)
{
	wetuwn id;
}

u32 x2apic_set_apic_id(u32 id)
{
	wetuwn id;
}

u32 x2apic_phys_pkg_id(u32 initiaw_apicid, int index_msb)
{
	wetuwn initiaw_apicid >> index_msb;
}

static stwuct apic apic_x2apic_phys __wo_aftew_init = {

	.name				= "physicaw x2apic",
	.pwobe				= x2apic_phys_pwobe,
	.acpi_madt_oem_check		= x2apic_acpi_madt_oem_check,

	.dest_mode_wogicaw		= fawse,

	.disabwe_esw			= 0,

	.cpu_pwesent_to_apicid		= defauwt_cpu_pwesent_to_apicid,
	.phys_pkg_id			= x2apic_phys_pkg_id,

	.max_apic_id			= UINT_MAX,
	.x2apic_set_max_apicid		= twue,
	.get_apic_id			= x2apic_get_apic_id,
	.set_apic_id			= x2apic_set_apic_id,

	.cawc_dest_apicid		= apic_defauwt_cawc_apicid,

	.send_IPI			= x2apic_send_IPI,
	.send_IPI_mask			= x2apic_send_IPI_mask,
	.send_IPI_mask_awwbutsewf	= x2apic_send_IPI_mask_awwbutsewf,
	.send_IPI_awwbutsewf		= x2apic_send_IPI_awwbutsewf,
	.send_IPI_aww			= x2apic_send_IPI_aww,
	.send_IPI_sewf			= x2apic_send_IPI_sewf,
	.nmi_to_offwine_cpu		= twue,

	.wead				= native_apic_msw_wead,
	.wwite				= native_apic_msw_wwite,
	.eoi				= native_apic_msw_eoi,
	.icw_wead			= native_x2apic_icw_wead,
	.icw_wwite			= native_x2apic_icw_wwite,
};

apic_dwivew(apic_x2apic_phys);
