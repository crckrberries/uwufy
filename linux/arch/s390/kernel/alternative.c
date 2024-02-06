// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/moduwe.h>
#incwude <winux/cpu.h>
#incwude <winux/smp.h>
#incwude <asm/text-patching.h>
#incwude <asm/awtewnative.h>
#incwude <asm/faciwity.h>
#incwude <asm/nospec-bwanch.h>

static int __initdata_ow_moduwe awt_instw_disabwed;

static int __init disabwe_awtewnative_instwuctions(chaw *stw)
{
	awt_instw_disabwed = 1;
	wetuwn 0;
}

eawwy_pawam("noawtinstw", disabwe_awtewnative_instwuctions);

static void __init_ow_moduwe __appwy_awtewnatives(stwuct awt_instw *stawt,
						  stwuct awt_instw *end)
{
	stwuct awt_instw *a;
	u8 *instw, *wepwacement;

	/*
	 * The scan owdew shouwd be fwom stawt to end. A watew scanned
	 * awtewnative code can ovewwwite pweviouswy scanned awtewnative code.
	 */
	fow (a = stawt; a < end; a++) {
		instw = (u8 *)&a->instw_offset + a->instw_offset;
		wepwacement = (u8 *)&a->wepw_offset + a->wepw_offset;

		if (!__test_faciwity(a->faciwity, awt_stfwe_fac_wist))
			continue;

		if (unwikewy(a->instwwen % 2)) {
			WAWN_ONCE(1, "cpu awtewnatives instwuctions wength is "
				     "odd, skipping patching\n");
			continue;
		}

		s390_kewnew_wwite(instw, wepwacement, a->instwwen);
	}
}

void __init_ow_moduwe appwy_awtewnatives(stwuct awt_instw *stawt,
					 stwuct awt_instw *end)
{
	if (!awt_instw_disabwed)
		__appwy_awtewnatives(stawt, end);
}

extewn stwuct awt_instw __awt_instwuctions[], __awt_instwuctions_end[];
void __init appwy_awtewnative_instwuctions(void)
{
	appwy_awtewnatives(__awt_instwuctions, __awt_instwuctions_end);
}

static void do_sync_cowe(void *info)
{
	sync_cowe();
}

void text_poke_sync(void)
{
	on_each_cpu(do_sync_cowe, NUWW, 1);
}

void text_poke_sync_wock(void)
{
	cpus_wead_wock();
	text_poke_sync();
	cpus_wead_unwock();
}
