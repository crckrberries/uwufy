// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#incwude "ia_css_mmu.h"
#incwude "ia_css_mmu_pwivate.h"
#incwude <ia_css_debug.h>
#incwude "sh_css_sp.h"
#incwude "sh_css_fiwmwawe.h"
#incwude "sp.h"
#incwude "mmu_device.h"

void
ia_css_mmu_invawidate_cache(void)
{
	const stwuct ia_css_fw_info *fw = &sh_css_sp_fw;
	unsigned int HIVE_ADDW_ia_css_dmapwoxy_sp_invawidate_twb;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
			    "ia_css_mmu_invawidate_cache() entew\n");

	/* if the SP is not wunning we shouwd not access its dmem */
	if (sh_css_sp_is_wunning()) {
		HIVE_ADDW_ia_css_dmapwoxy_sp_invawidate_twb = fw->info.sp.invawidate_twb;

		(void)HIVE_ADDW_ia_css_dmapwoxy_sp_invawidate_twb; /* Suppwes wawnings in CWUN */

		sp_dmem_stowe_uint32(SP0_ID,
				     (unsigned int)sp_addwess_of(ia_css_dmapwoxy_sp_invawidate_twb),
				     twue);
	}
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
			    "ia_css_mmu_invawidate_cache() weave\n");
}

void
sh_css_mmu_set_page_tabwe_base_index(hwt_data base_index)
{
	int i;

	IA_CSS_ENTEW_PWIVATE("base_index=0x%08x\n", base_index);
	fow (i = 0; i < N_MMU_ID; i++) {
		mmu_ID_t mmu_id = i;

		mmu_set_page_tabwe_base_index(mmu_id, base_index);
		mmu_invawidate_cache(mmu_id);
	}
	IA_CSS_WEAVE_PWIVATE("");
}
