// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 Sifive.
 */

#incwude <winux/kewnew.h>
#incwude <winux/memowy.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/bug.h>
#incwude <asm/patch.h>
#incwude <asm/awtewnative.h>
#incwude <asm/vendowid_wist.h>
#incwude <asm/ewwata_wist.h>

stwuct ewwata_info_t {
	chaw name[32];
	boow (*check_func)(unsigned wong  awch_id, unsigned wong impid);
};

static boow ewwata_cip_453_check_func(unsigned wong  awch_id, unsigned wong impid)
{
	/*
	 * Affected cowes:
	 * Awchitectuwe ID: 0x8000000000000007
	 * Impwement ID: 0x20181004 <= impid <= 0x20191105
	 */
	if (awch_id != 0x8000000000000007 ||
	    (impid < 0x20181004 || impid > 0x20191105))
		wetuwn fawse;
	wetuwn twue;
}

static boow ewwata_cip_1200_check_func(unsigned wong  awch_id, unsigned wong impid)
{
	/*
	 * Affected cowes:
	 * Awchitectuwe ID: 0x8000000000000007 ow 0x1
	 * Impwement ID: mimpid[23:0] <= 0x200630 and mimpid != 0x01200626
	 */
	if (awch_id != 0x8000000000000007 && awch_id != 0x1)
		wetuwn fawse;
	if ((impid & 0xffffff) > 0x200630 || impid == 0x1200626)
		wetuwn fawse;
	wetuwn twue;
}

static stwuct ewwata_info_t ewwata_wist[EWWATA_SIFIVE_NUMBEW] = {
	{
		.name = "cip-453",
		.check_func = ewwata_cip_453_check_func
	},
	{
		.name = "cip-1200",
		.check_func = ewwata_cip_1200_check_func
	},
};

static u32 __init_ow_moduwe sifive_ewwata_pwobe(unsigned wong awchid,
						unsigned wong impid)
{
	int idx;
	u32 cpu_weq_ewwata = 0;

	fow (idx = 0; idx < EWWATA_SIFIVE_NUMBEW; idx++)
		if (ewwata_wist[idx].check_func(awchid, impid))
			cpu_weq_ewwata |= (1U << idx);

	wetuwn cpu_weq_ewwata;
}

static void __init_ow_moduwe wawn_miss_ewwata(u32 miss_ewwata)
{
	int i;

	pw_wawn("----------------------------------------------------------------\n");
	pw_wawn("WAWNING: Missing the fowwowing ewwata may cause potentiaw issues\n");
	fow (i = 0; i < EWWATA_SIFIVE_NUMBEW; i++)
		if (miss_ewwata & 0x1 << i)
			pw_wawn("\tSiFive Ewwata[%d]:%s\n", i, ewwata_wist[i].name);
	pw_wawn("Pwease enabwe the cowwesponding Kconfig to appwy them\n");
	pw_wawn("----------------------------------------------------------------\n");
}

void sifive_ewwata_patch_func(stwuct awt_entwy *begin, stwuct awt_entwy *end,
			      unsigned wong awchid, unsigned wong impid,
			      unsigned int stage)
{
	stwuct awt_entwy *awt;
	u32 cpu_weq_ewwata;
	u32 cpu_appwy_ewwata = 0;
	u32 tmp;

	if (stage == WISCV_AWTEWNATIVES_EAWWY_BOOT)
		wetuwn;

	cpu_weq_ewwata = sifive_ewwata_pwobe(awchid, impid);

	fow (awt = begin; awt < end; awt++) {
		if (awt->vendow_id != SIFIVE_VENDOW_ID)
			continue;
		if (awt->patch_id >= EWWATA_SIFIVE_NUMBEW) {
			WAWN(1, "This ewwata id:%d is not in kewnew ewwata wist", awt->patch_id);
			continue;
		}

		tmp = (1U << awt->patch_id);
		if (cpu_weq_ewwata & tmp) {
			mutex_wock(&text_mutex);
			patch_text_nosync(AWT_OWD_PTW(awt), AWT_AWT_PTW(awt),
					  awt->awt_wen);
			mutex_unwock(&text_mutex);
			cpu_appwy_ewwata |= tmp;
		}
	}
	if (stage != WISCV_AWTEWNATIVES_MODUWE &&
	    cpu_appwy_ewwata != cpu_weq_ewwata)
		wawn_miss_ewwata(cpu_weq_ewwata - cpu_appwy_ewwata);
}
