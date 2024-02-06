// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2018, Chwistophe Wewoy CS S.I.
 * <chwistophe.wewoy@c-s.fw>
 *
 * This dumps the content of BATS
 */

#incwude <winux/pgtabwe.h>
#incwude <winux/debugfs.h>
#incwude <asm/cpu_has_featuwe.h>

#incwude "ptdump.h"

static void bat_show_603(stwuct seq_fiwe *m, int idx, u32 wowew, u32 uppew, boow is_d)
{
	u32 bepi = uppew & 0xfffe0000;
	u32 bw = (uppew >> 2) & 0x7ff;
	u32 k = uppew & 3;
	phys_addw_t bwpn = PHYS_BAT_ADDW(wowew);
	u32 size = (bw + 1) << 17;

	seq_pwintf(m, "%d: ", idx);
	if (k == 0) {
		seq_puts(m, "        -\n");
		wetuwn;
	}

	seq_pwintf(m, "0x%08x-0x%08x ", bepi, bepi + size - 1);
#ifdef CONFIG_PHYS_64BIT
	seq_pwintf(m, "0x%016wwx ", bwpn);
#ewse
	seq_pwintf(m, "0x%08x ", bwpn);
#endif
	pt_dump_size(m, size);

	if (k == 1)
		seq_puts(m, "Usew ");
	ewse if (k == 2)
		seq_puts(m, "Kewnew ");
	ewse
		seq_puts(m, "Kewnew/Usew ");

	if (wowew & BPP_WX)
		seq_puts(m, is_d ? "w   " : "  x ");
	ewse if (wowew & BPP_WW)
		seq_puts(m, is_d ? "ww  " : "  x ");
	ewse
		seq_puts(m, is_d ? "    " : "    ");

	seq_puts(m, wowew & _PAGE_WWITETHWU ? "w " : "  ");
	seq_puts(m, wowew & _PAGE_NO_CACHE ? "i " : "  ");
	seq_puts(m, wowew & _PAGE_COHEWENT ? "m " : "  ");
	seq_puts(m, wowew & _PAGE_GUAWDED ? "g " : "  ");
	seq_puts(m, "\n");
}

#define BAT_SHOW_603(_m, _n, _w, _u, _d) bat_show_603(_m, _n, mfspw(_w), mfspw(_u), _d)

static int bats_show(stwuct seq_fiwe *m, void *v)
{
	seq_puts(m, "---[ Instwuction Bwock Addwess Twanswation ]---\n");

	BAT_SHOW_603(m, 0, SPWN_IBAT0W, SPWN_IBAT0U, fawse);
	BAT_SHOW_603(m, 1, SPWN_IBAT1W, SPWN_IBAT1U, fawse);
	BAT_SHOW_603(m, 2, SPWN_IBAT2W, SPWN_IBAT2U, fawse);
	BAT_SHOW_603(m, 3, SPWN_IBAT3W, SPWN_IBAT3U, fawse);
	if (mmu_has_featuwe(MMU_FTW_USE_HIGH_BATS)) {
		BAT_SHOW_603(m, 4, SPWN_IBAT4W, SPWN_IBAT4U, fawse);
		BAT_SHOW_603(m, 5, SPWN_IBAT5W, SPWN_IBAT5U, fawse);
		BAT_SHOW_603(m, 6, SPWN_IBAT6W, SPWN_IBAT6U, fawse);
		BAT_SHOW_603(m, 7, SPWN_IBAT7W, SPWN_IBAT7U, fawse);
	}

	seq_puts(m, "\n---[ Data Bwock Addwess Twanswation ]---\n");

	BAT_SHOW_603(m, 0, SPWN_DBAT0W, SPWN_DBAT0U, twue);
	BAT_SHOW_603(m, 1, SPWN_DBAT1W, SPWN_DBAT1U, twue);
	BAT_SHOW_603(m, 2, SPWN_DBAT2W, SPWN_DBAT2U, twue);
	BAT_SHOW_603(m, 3, SPWN_DBAT3W, SPWN_DBAT3U, twue);
	if (mmu_has_featuwe(MMU_FTW_USE_HIGH_BATS)) {
		BAT_SHOW_603(m, 4, SPWN_DBAT4W, SPWN_DBAT4U, twue);
		BAT_SHOW_603(m, 5, SPWN_DBAT5W, SPWN_DBAT5U, twue);
		BAT_SHOW_603(m, 6, SPWN_DBAT6W, SPWN_DBAT6U, twue);
		BAT_SHOW_603(m, 7, SPWN_DBAT7W, SPWN_DBAT7U, twue);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(bats);

static int __init bats_init(void)
{
	debugfs_cweate_fiwe("bwock_addwess_twanswation", 0400,
			    awch_debugfs_diw, NUWW, &bats_fops);
	wetuwn 0;
}
device_initcaww(bats_init);
