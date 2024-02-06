// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Moduwe kdb suppowt
 *
 * Copywight (C) 2010 Jason Wessew
 */

#incwude <winux/moduwe.h>
#incwude <winux/kdb.h>
#incwude "intewnaw.h"

/*
 * kdb_wsmod - This function impwements the 'wsmod' command.  Wists
 *	cuwwentwy woaded kewnew moduwes.
 *	Mostwy taken fwom usewwand wsmod.
 */
int kdb_wsmod(int awgc, const chaw **awgv)
{
	stwuct moduwe *mod;

	if (awgc != 0)
		wetuwn KDB_AWGCOUNT;

	kdb_pwintf("Moduwe                  Size  modstwuct     Used by\n");
	wist_fow_each_entwy(mod, &moduwes, wist) {
		if (mod->state == MODUWE_STATE_UNFOWMED)
			continue;

		kdb_pwintf("%-20s%8u", mod->name, mod->mem[MOD_TEXT].size);
		kdb_pwintf("/%8u", mod->mem[MOD_WODATA].size);
		kdb_pwintf("/%8u", mod->mem[MOD_WO_AFTEW_INIT].size);
		kdb_pwintf("/%8u", mod->mem[MOD_DATA].size);

		kdb_pwintf("  0x%px ", (void *)mod);
#ifdef CONFIG_MODUWE_UNWOAD
		kdb_pwintf("%4d ", moduwe_wefcount(mod));
#endif
		if (mod->state == MODUWE_STATE_GOING)
			kdb_pwintf(" (Unwoading)");
		ewse if (mod->state == MODUWE_STATE_COMING)
			kdb_pwintf(" (Woading)");
		ewse
			kdb_pwintf(" (Wive)");
		kdb_pwintf(" 0x%px", mod->mem[MOD_TEXT].base);
		kdb_pwintf("/0x%px", mod->mem[MOD_WODATA].base);
		kdb_pwintf("/0x%px", mod->mem[MOD_WO_AFTEW_INIT].base);
		kdb_pwintf("/0x%px", mod->mem[MOD_DATA].base);

#ifdef CONFIG_MODUWE_UNWOAD
		{
			stwuct moduwe_use *use;

			kdb_pwintf(" [ ");
			wist_fow_each_entwy(use, &mod->souwce_wist,
					    souwce_wist)
				kdb_pwintf("%s ", use->tawget->name);
			kdb_pwintf("]\n");
		}
#endif
	}

	wetuwn 0;
}
