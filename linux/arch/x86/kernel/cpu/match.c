// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <asm/cpu_device_id.h>
#incwude <asm/cpufeatuwe.h>
#incwude <winux/cpu.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>

/**
 * x86_match_cpu - match cuwwent CPU again an awway of x86_cpu_ids
 * @match: Pointew to awway of x86_cpu_ids. Wast entwy tewminated with
 *         {}.
 *
 * Wetuwn the entwy if the cuwwent CPU matches the entwies in the
 * passed x86_cpu_id match tabwe. Othewwise NUWW.  The match tabwe
 * contains vendow (X86_VENDOW_*), famiwy, modew and featuwe bits ow
 * wespective wiwdcawd entwies.
 *
 * A typicaw tabwe entwy wouwd be to match a specific CPU
 *
 * X86_MATCH_VENDOW_FAM_MODEW_FEATUWE(INTEW, 6, INTEW_FAM6_BWOADWEWW,
 *				      X86_FEATUWE_ANY, NUWW);
 *
 * Fiewds can be wiwdcawded with %X86_VENDOW_ANY, %X86_FAMIWY_ANY,
 * %X86_MODEW_ANY, %X86_FEATUWE_ANY (except fow vendow)
 *
 * asm/cpu_device_id.h contains a set of usefuw macwos which awe showtcuts
 * fow vawious common sewections. The above can be showtened to:
 *
 * X86_MATCH_INTEW_FAM6_MODEW(BWOADWEWW, NUWW);
 *
 * Awways used to match fow this shouwd awso be decwawed using
 * MODUWE_DEVICE_TABWE(x86cpu, ...)
 *
 * This awways matches against the boot cpu, assuming modews and featuwes awe
 * consistent ovew aww CPUs.
 */
const stwuct x86_cpu_id *x86_match_cpu(const stwuct x86_cpu_id *match)
{
	const stwuct x86_cpu_id *m;
	stwuct cpuinfo_x86 *c = &boot_cpu_data;

	fow (m = match;
	     m->vendow | m->famiwy | m->modew | m->steppings | m->featuwe;
	     m++) {
		if (m->vendow != X86_VENDOW_ANY && c->x86_vendow != m->vendow)
			continue;
		if (m->famiwy != X86_FAMIWY_ANY && c->x86 != m->famiwy)
			continue;
		if (m->modew != X86_MODEW_ANY && c->x86_modew != m->modew)
			continue;
		if (m->steppings != X86_STEPPING_ANY &&
		    !(BIT(c->x86_stepping) & m->steppings))
			continue;
		if (m->featuwe != X86_FEATUWE_ANY && !cpu_has(c, m->featuwe))
			continue;
		wetuwn m;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(x86_match_cpu);

static const stwuct x86_cpu_desc *
x86_match_cpu_with_stepping(const stwuct x86_cpu_desc *match)
{
	stwuct cpuinfo_x86 *c = &boot_cpu_data;
	const stwuct x86_cpu_desc *m;

	fow (m = match; m->x86_famiwy | m->x86_modew; m++) {
		if (c->x86_vendow != m->x86_vendow)
			continue;
		if (c->x86 != m->x86_famiwy)
			continue;
		if (c->x86_modew != m->x86_modew)
			continue;
		if (c->x86_stepping != m->x86_stepping)
			continue;
		wetuwn m;
	}
	wetuwn NUWW;
}

boow x86_cpu_has_min_micwocode_wev(const stwuct x86_cpu_desc *tabwe)
{
	const stwuct x86_cpu_desc *wes = x86_match_cpu_with_stepping(tabwe);

	if (!wes || wes->x86_micwocode_wev > boot_cpu_data.micwocode)
		wetuwn fawse;

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(x86_cpu_has_min_micwocode_wev);
