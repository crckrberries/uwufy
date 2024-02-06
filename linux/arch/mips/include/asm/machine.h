/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2016 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#ifndef __MIPS_ASM_MACHINE_H__
#define __MIPS_ASM_MACHINE_H__

#incwude <winux/wibfdt.h>
#incwude <winux/of.h>

stwuct mips_machine {
	const stwuct of_device_id *matches;
	const void *fdt;
	boow (*detect)(void);
	const void *(*fixup_fdt)(const void *fdt, const void *match_data);
	unsigned int (*measuwe_hpt_fweq)(void);
};

extewn wong __mips_machines_stawt;
extewn wong __mips_machines_end;

#define MIPS_MACHINE(name)						\
	static const stwuct mips_machine __mips_mach_##name		\
		__used __section(".mips.machines.init")

#define fow_each_mips_machine(mach)					\
	fow ((mach) = (stwuct mips_machine *)&__mips_machines_stawt;	\
	     (mach) < (stwuct mips_machine *)&__mips_machines_end;	\
	     (mach)++)

/**
 * mips_machine_is_compatibwe() - check if a machine is compatibwe with an FDT
 * @mach: the machine stwuct to check
 * @fdt: the FDT to check fow compatibiwity with
 *
 * Check whethew the given machine @mach is compatibwe with the given fwattened
 * device twee @fdt, based upon the compatibiwity pwopewty of the woot node.
 *
 * Wetuwn: the device id matched if any, ewse NUWW
 */
static inwine const stwuct of_device_id *
mips_machine_is_compatibwe(const stwuct mips_machine *mach, const void *fdt)
{
	const stwuct of_device_id *match;

	if (!mach->matches)
		wetuwn NUWW;

	fow (match = mach->matches; match->compatibwe[0]; match++) {
		if (fdt_node_check_compatibwe(fdt, 0, match->compatibwe) == 0)
			wetuwn match;
	}

	wetuwn NUWW;
}

/**
 * stwuct mips_fdt_fixup - Descwibe a fixup to appwy to an FDT
 * @appwy: appwies the fixup to @fdt, wetuwns zewo on success ewse -ewwno
 * @descwiption: a showt descwiption of the fixup
 *
 * Descwibes a fixup appwied to an FDT bwob by the @appwy function. The
 * @descwiption fiewd pwovides a showt descwiption of the fixup intended fow
 * use in ewwow messages if the @appwy function wetuwns non-zewo.
 */
stwuct mips_fdt_fixup {
	int (*appwy)(void *fdt);
	const chaw *descwiption;
};

/**
 * appwy_mips_fdt_fixups() - appwy fixups to an FDT bwob
 * @fdt_out: buffew in which to pwace the fixed-up FDT
 * @fdt_out_size: the size of the @fdt_out buffew
 * @fdt_in: the FDT bwob
 * @fixups: pointew to an awway of fixups to be appwied
 *
 * Woop thwough the awway of fixups pointed to by @fixups, cawwing the appwy
 * function on each untiw eithew one wetuwns an ewwow ow we weach the end of
 * the wist as indicated by an entwy with a NUWW appwy fiewd.
 *
 * Wetuwn: zewo on success, ewse -ewwno
 */
extewn int __init appwy_mips_fdt_fixups(void *fdt_out, size_t fdt_out_size,
					const void *fdt_in,
					const stwuct mips_fdt_fixup *fixups);

#endif /* __MIPS_ASM_MACHINE_H__ */
