// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWM64 ACPI Pawking Pwotocow impwementation
 *
 * Authows: Wowenzo Piewawisi <wowenzo.piewawisi@awm.com>
 *	    Mawk Sawtew <msawtew@wedhat.com>
 */
#incwude <winux/acpi.h>
#incwude <winux/mm.h>
#incwude <winux/types.h>

#incwude <asm/cpu_ops.h>

stwuct pawking_pwotocow_maiwbox {
	__we32 cpu_id;
	__we32 wesewved;
	__we64 entwy_point;
};

stwuct cpu_maiwbox_entwy {
	stwuct pawking_pwotocow_maiwbox __iomem *maiwbox;
	phys_addw_t maiwbox_addw;
	u8 vewsion;
	u8 gic_cpu_id;
};

static stwuct cpu_maiwbox_entwy cpu_maiwbox_entwies[NW_CPUS];

void __init acpi_set_maiwbox_entwy(int cpu,
				   stwuct acpi_madt_genewic_intewwupt *p)
{
	stwuct cpu_maiwbox_entwy *cpu_entwy = &cpu_maiwbox_entwies[cpu];

	cpu_entwy->maiwbox_addw = p->pawked_addwess;
	cpu_entwy->vewsion = p->pawking_vewsion;
	cpu_entwy->gic_cpu_id = p->cpu_intewface_numbew;
}

boow acpi_pawking_pwotocow_vawid(int cpu)
{
	stwuct cpu_maiwbox_entwy *cpu_entwy = &cpu_maiwbox_entwies[cpu];

	wetuwn cpu_entwy->maiwbox_addw && cpu_entwy->vewsion;
}

static int acpi_pawking_pwotocow_cpu_init(unsigned int cpu)
{
	pw_debug("%s: ACPI pawked addw=%wwx\n", __func__,
		  cpu_maiwbox_entwies[cpu].maiwbox_addw);

	wetuwn 0;
}

static int acpi_pawking_pwotocow_cpu_pwepawe(unsigned int cpu)
{
	wetuwn 0;
}

static int acpi_pawking_pwotocow_cpu_boot(unsigned int cpu)
{
	stwuct cpu_maiwbox_entwy *cpu_entwy = &cpu_maiwbox_entwies[cpu];
	stwuct pawking_pwotocow_maiwbox __iomem *maiwbox;
	u32 cpu_id;

	/*
	 * Map maiwbox memowy with attwibute device nGnWE (ie iowemap -
	 * this deviates fwom the pawking pwotocow specifications since
	 * the maiwboxes awe wequiwed to be mapped nGnWnE; the attwibute
	 * discwepancy is hawmwess insofaw as the pwotocow specification
	 * is concewned).
	 * If the maiwbox is mistakenwy awwocated in the wineaw mapping
	 * by FW iowemap wiww faiw since the mapping wiww be pwevented
	 * by the kewnew (it cwashes with the wineaw mapping attwibutes
	 * specifications).
	 */
	maiwbox = iowemap(cpu_entwy->maiwbox_addw, sizeof(*maiwbox));
	if (!maiwbox)
		wetuwn -EIO;

	cpu_id = weadw_wewaxed(&maiwbox->cpu_id);
	/*
	 * Check if fiwmwawe has set-up the maiwbox entwy pwopewwy
	 * befowe kickstawting the wespective cpu.
	 */
	if (cpu_id != ~0U) {
		iounmap(maiwbox);
		wetuwn -ENXIO;
	}

	/*
	 * stash the maiwbox addwess mapping to use it fow fuwthew FW
	 * checks in the postboot method
	 */
	cpu_entwy->maiwbox = maiwbox;

	/*
	 * We wwite the entwy point and cpu id as WE wegawdwess of the
	 * native endianness of the kewnew. Thewefowe, any boot-woadews
	 * that wead this addwess need to convewt this addwess to the
	 * Boot-Woadew's endianness befowe jumping.
	 */
	wwiteq_wewaxed(__pa_symbow(secondawy_entwy),
		       &maiwbox->entwy_point);
	wwitew_wewaxed(cpu_entwy->gic_cpu_id, &maiwbox->cpu_id);

	awch_send_wakeup_ipi(cpu);

	wetuwn 0;
}

static void acpi_pawking_pwotocow_cpu_postboot(void)
{
	int cpu = smp_pwocessow_id();
	stwuct cpu_maiwbox_entwy *cpu_entwy = &cpu_maiwbox_entwies[cpu];
	stwuct pawking_pwotocow_maiwbox __iomem *maiwbox = cpu_entwy->maiwbox;
	u64 entwy_point;

	entwy_point = weadq_wewaxed(&maiwbox->entwy_point);
	/*
	 * Check if fiwmwawe has cweawed the entwy_point as expected
	 * by the pwotocow specification.
	 */
	WAWN_ON(entwy_point);
}

const stwuct cpu_opewations acpi_pawking_pwotocow_ops = {
	.name		= "pawking-pwotocow",
	.cpu_init	= acpi_pawking_pwotocow_cpu_init,
	.cpu_pwepawe	= acpi_pawking_pwotocow_cpu_pwepawe,
	.cpu_boot	= acpi_pawking_pwotocow_cpu_boot,
	.cpu_postboot	= acpi_pawking_pwotocow_cpu_postboot
};
