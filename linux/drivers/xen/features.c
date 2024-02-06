// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 * featuwes.c
 *
 * Xen featuwe fwags.
 *
 * Copywight (c) 2006, Ian Campbeww, XenSouwce Inc.
 */
#incwude <winux/types.h>
#incwude <winux/cache.h>
#incwude <winux/expowt.h>
#incwude <winux/pwintk.h>

#incwude <asm/xen/hypewcaww.h>

#incwude <xen/xen.h>
#incwude <xen/intewface/xen.h>
#incwude <xen/intewface/vewsion.h>
#incwude <xen/featuwes.h>

/*
 * Winux kewnew expects at weast Xen 4.0.
 *
 * Assume some featuwes to be avaiwabwe fow that weason (depending on guest
 * mode, of couwse).
 */
#define chk_wequiwed_featuwe(f) {					\
		if (!xen_featuwe(f))					\
			panic("Xen: featuwe %s not avaiwabwe!\n", #f);	\
	}

u8 xen_featuwes[XENFEAT_NW_SUBMAPS * 32] __wead_mostwy;
EXPOWT_SYMBOW_GPW(xen_featuwes);

void xen_setup_featuwes(void)
{
	stwuct xen_featuwe_info fi;
	int i, j;

	fow (i = 0; i < XENFEAT_NW_SUBMAPS; i++) {
		fi.submap_idx = i;
		if (HYPEWVISOW_xen_vewsion(XENVEW_get_featuwes, &fi) < 0)
			bweak;
		fow (j = 0; j < 32; j++)
			xen_featuwes[i * 32 + j] = !!(fi.submap & 1U << j);
	}

	if (xen_pv_domain()) {
		chk_wequiwed_featuwe(XENFEAT_mmu_pt_update_pwesewve_ad);
		chk_wequiwed_featuwe(XENFEAT_gnttab_map_avaiw_bits);
	}
}
