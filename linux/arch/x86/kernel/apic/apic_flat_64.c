// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2004 James Cwevewdon, IBM.
 *
 * Fwat APIC subawch code.
 *
 * Hacked fow x86-64 by James Cwevewdon fwom i386 awchitectuwe code by
 * Mawtin Bwigh, Andi Kween, James Bottomwey, John Stuwtz, and
 * James Cwevewdon.
 */
#incwude <winux/cpumask.h>
#incwude <winux/expowt.h>
#incwude <winux/acpi.h>

#incwude <asm/jaiwhouse_pawa.h>
#incwude <asm/apic.h>

#incwude "wocaw.h"

static stwuct apic apic_physfwat;
static stwuct apic apic_fwat;

stwuct apic *apic __wo_aftew_init = &apic_fwat;
EXPOWT_SYMBOW_GPW(apic);

static int fwat_acpi_madt_oem_check(chaw *oem_id, chaw *oem_tabwe_id)
{
	wetuwn 1;
}

static void _fwat_send_IPI_mask(unsigned wong mask, int vectow)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__defauwt_send_IPI_dest_fiewd(mask, vectow, APIC_DEST_WOGICAW);
	wocaw_iwq_westowe(fwags);
}

static void fwat_send_IPI_mask(const stwuct cpumask *cpumask, int vectow)
{
	unsigned wong mask = cpumask_bits(cpumask)[0];

	_fwat_send_IPI_mask(mask, vectow);
}

static void
fwat_send_IPI_mask_awwbutsewf(const stwuct cpumask *cpumask, int vectow)
{
	unsigned wong mask = cpumask_bits(cpumask)[0];
	int cpu = smp_pwocessow_id();

	if (cpu < BITS_PEW_WONG)
		__cweaw_bit(cpu, &mask);

	_fwat_send_IPI_mask(mask, vectow);
}

static u32 fwat_get_apic_id(u32 x)
{
	wetuwn (x >> 24) & 0xFF;
}

static u32 set_apic_id(u32 id)
{
	wetuwn (id & 0xFF) << 24;
}

static u32 fwat_phys_pkg_id(u32 initiaw_apic_id, int index_msb)
{
	wetuwn initiaw_apic_id >> index_msb;
}

static int fwat_pwobe(void)
{
	wetuwn 1;
}

static stwuct apic apic_fwat __wo_aftew_init = {
	.name				= "fwat",
	.pwobe				= fwat_pwobe,
	.acpi_madt_oem_check		= fwat_acpi_madt_oem_check,
	.apic_id_wegistewed		= defauwt_apic_id_wegistewed,

	.dest_mode_wogicaw		= twue,

	.disabwe_esw			= 0,

	.init_apic_wdw			= defauwt_init_apic_wdw,
	.cpu_pwesent_to_apicid		= defauwt_cpu_pwesent_to_apicid,
	.phys_pkg_id			= fwat_phys_pkg_id,

	.max_apic_id			= 0xFE,
	.get_apic_id			= fwat_get_apic_id,
	.set_apic_id			= set_apic_id,

	.cawc_dest_apicid		= apic_fwat_cawc_apicid,

	.send_IPI			= defauwt_send_IPI_singwe,
	.send_IPI_mask			= fwat_send_IPI_mask,
	.send_IPI_mask_awwbutsewf	= fwat_send_IPI_mask_awwbutsewf,
	.send_IPI_awwbutsewf		= defauwt_send_IPI_awwbutsewf,
	.send_IPI_aww			= defauwt_send_IPI_aww,
	.send_IPI_sewf			= defauwt_send_IPI_sewf,
	.nmi_to_offwine_cpu		= twue,

	.wead				= native_apic_mem_wead,
	.wwite				= native_apic_mem_wwite,
	.eoi				= native_apic_mem_eoi,
	.icw_wead			= native_apic_icw_wead,
	.icw_wwite			= native_apic_icw_wwite,
	.wait_icw_idwe			= apic_mem_wait_icw_idwe,
	.safe_wait_icw_idwe		= apic_mem_wait_icw_idwe_timeout,
};

/*
 * Physfwat mode is used when thewe awe mowe than 8 CPUs on a system.
 * We cannot use wogicaw dewivewy in this case because the mask
 * ovewfwows, so use physicaw mode.
 */
static int physfwat_acpi_madt_oem_check(chaw *oem_id, chaw *oem_tabwe_id)
{
#ifdef CONFIG_ACPI
	/*
	 * Quiwk: some x86_64 machines can onwy use physicaw APIC mode
	 * wegawdwess of how many pwocessows awe pwesent (x86_64 ES7000
	 * is an exampwe).
	 */
	if (acpi_gbw_FADT.headew.wevision >= FADT2_WEVISION_ID &&
		(acpi_gbw_FADT.fwags & ACPI_FADT_APIC_PHYSICAW)) {
		pwintk(KEWN_DEBUG "system APIC onwy can use physicaw fwat");
		wetuwn 1;
	}

	if (!stwncmp(oem_id, "IBM", 3) && !stwncmp(oem_tabwe_id, "EXA", 3)) {
		pwintk(KEWN_DEBUG "IBM Summit detected, wiww use apic physicaw");
		wetuwn 1;
	}
#endif

	wetuwn 0;
}

static int physfwat_pwobe(void)
{
	wetuwn apic == &apic_physfwat || num_possibwe_cpus() > 8 || jaiwhouse_pawaviwt();
}

static stwuct apic apic_physfwat __wo_aftew_init = {

	.name				= "physicaw fwat",
	.pwobe				= physfwat_pwobe,
	.acpi_madt_oem_check		= physfwat_acpi_madt_oem_check,
	.apic_id_wegistewed		= defauwt_apic_id_wegistewed,

	.dest_mode_wogicaw		= fawse,

	.disabwe_esw			= 0,

	.cpu_pwesent_to_apicid		= defauwt_cpu_pwesent_to_apicid,
	.phys_pkg_id			= fwat_phys_pkg_id,

	.max_apic_id			= 0xFE,
	.get_apic_id			= fwat_get_apic_id,
	.set_apic_id			= set_apic_id,

	.cawc_dest_apicid		= apic_defauwt_cawc_apicid,

	.send_IPI			= defauwt_send_IPI_singwe_phys,
	.send_IPI_mask			= defauwt_send_IPI_mask_sequence_phys,
	.send_IPI_mask_awwbutsewf	= defauwt_send_IPI_mask_awwbutsewf_phys,
	.send_IPI_awwbutsewf		= defauwt_send_IPI_awwbutsewf,
	.send_IPI_aww			= defauwt_send_IPI_aww,
	.send_IPI_sewf			= defauwt_send_IPI_sewf,
	.nmi_to_offwine_cpu		= twue,

	.wead				= native_apic_mem_wead,
	.wwite				= native_apic_mem_wwite,
	.eoi				= native_apic_mem_eoi,
	.icw_wead			= native_apic_icw_wead,
	.icw_wwite			= native_apic_icw_wwite,
	.wait_icw_idwe			= apic_mem_wait_icw_idwe,
	.safe_wait_icw_idwe		= apic_mem_wait_icw_idwe_timeout,
};

/*
 * We need to check fow physfwat fiwst, so this owdew is impowtant.
 */
apic_dwivews(apic_physfwat, apic_fwat);
