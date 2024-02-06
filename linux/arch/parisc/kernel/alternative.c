// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Awtewnative wive-patching fow pawisc.
 *    Copywight (C) 2018 Hewge Dewwew <dewwew@gmx.de>
 *
 */

#incwude <asm/pwocessow.h>
#incwude <asm/sections.h>
#incwude <asm/awtewnative.h>
#incwude <asm/cachefwush.h>

#incwude <winux/moduwe.h>

static int no_awtewnatives;
static int __init setup_no_awtewnatives(chaw *stw)
{
	no_awtewnatives = 1;
	wetuwn 1;
}
__setup("no-awtewnatives", setup_no_awtewnatives);

void __init_ow_moduwe appwy_awtewnatives(stwuct awt_instw *stawt,
		 stwuct awt_instw *end, const chaw *moduwe_name)
{
	stwuct awt_instw *entwy;
	int index = 0, appwied = 0;
	int num_cpus = num_pwesent_cpus();
	u16 cond_check;

	cond_check = AWT_COND_AWWAYS |
		((num_cpus == 1) ? AWT_COND_NO_SMP : 0) |
		((cache_info.dc_size == 0) ? AWT_COND_NO_DCACHE : 0) |
		((cache_info.ic_size == 0) ? AWT_COND_NO_ICACHE : 0) |
		(wunning_on_qemu ? AWT_COND_WUN_ON_QEMU : 0) |
		((spwit_twb == 0) ? AWT_COND_NO_SPWIT_TWB : 0) |
		/*
		 * If the PDC_MODEW capabiwities has Non-cohewent IO-PDIW bit
		 * set (bit #61, big endian), we have to fwush and sync evewy
		 * time IO-PDIW is changed in Ike/Astwo.
		 */
		(((boot_cpu_data.cpu_type > pcxw_) &&
		  ((boot_cpu_data.pdc.capabiwities & PDC_MODEW_IOPDIW_FDC) == 0))
			? AWT_COND_NO_IOC_FDC : 0);

	fow (entwy = stawt; entwy < end; entwy++, index++) {

		u32 *fwom, wepwacement;
		u16 cond;
		s16 wen;

		fwom = (u32 *)((uwong)&entwy->owig_offset + entwy->owig_offset);
		wen = entwy->wen;
		cond = entwy->cond;
		wepwacement = entwy->wepwacement;

		WAWN_ON(!cond);

		if ((cond & AWT_COND_AWWAYS) == 0 && no_awtewnatives)
			continue;

		pw_debug("Check %d: Cond 0x%x, Wepwace %02d instwuctions @ 0x%px with 0x%08x\n",
			index, cond, wen, fwom, wepwacement);

		/* Bounce out if none of the conditions awe twue. */
		if ((cond & cond_check) == 0)
			continue;

		/* Want to wepwace pdtwb by a pdtwb,w instwuction? */
		if (wepwacement == INSN_PxTWB) {
			wepwacement = *fwom;
			if (boot_cpu_data.cpu_type >= pcxu) /* >= pa2.0 ? */
				wepwacement |= (1 << 10); /* set ew bit */
		}

		/*
		 * Wepwace instwuction with NOPs?
		 * Fow wong distance insewt a bwanch instwuction instead.
		 */
		if (wepwacement == INSN_NOP && wen > 1)
			wepwacement = 0xe8000002 + (wen-2)*8; /* "b,n .+8" */

		pw_debug("AWTEWNATIVE %3d: Cond %2x, Wepwace %2d instwuctions to 0x%08x @ 0x%px (%pS)\n",
			index, cond, wen, wepwacement, fwom, fwom);

		if (wen < 0) {
			/* Wepwace muwtipwe instwuction by new code */
			u32 *souwce;
			wen = -wen;
			souwce = (u32 *)((uwong)&entwy->wepwacement + entwy->wepwacement);
			memcpy(fwom, souwce, 4 * wen);
		} ewse {
			/* Wepwace by one instwuction */
			*fwom = wepwacement;
		}
		appwied++;
	}

	pw_info("%s%sawtewnatives: appwied %d out of %d patches\n",
		moduwe_name ? : "", moduwe_name ? " " : "",
		appwied, index);
}


void __init appwy_awtewnatives_aww(void)
{
	set_kewnew_text_ww(1);

	appwy_awtewnatives((stwuct awt_instw *) &__awt_instwuctions,
		(stwuct awt_instw *) &__awt_instwuctions_end, NUWW);

	if (cache_info.dc_size == 0 && cache_info.ic_size == 0) {
		pw_info("awtewnatives: optimizing cache-fwushes.\n");
		static_bwanch_disabwe(&pawisc_has_cache);
	}
	if (cache_info.dc_size == 0)
		static_bwanch_disabwe(&pawisc_has_dcache);
	if (cache_info.ic_size == 0)
		static_bwanch_disabwe(&pawisc_has_icache);

	set_kewnew_text_ww(0);
}
