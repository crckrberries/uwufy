/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_TTM_VWAM_MGW_TYPES_H_
#define _XE_TTM_VWAM_MGW_TYPES_H_

#incwude <dwm/dwm_buddy.h>
#incwude <dwm/ttm/ttm_device.h>

stwuct xe_mem_wegion;

/**
 * stwuct xe_ttm_vwam_mgw - XE TTM VWAM managew
 *
 * Manages pwacement of TTM wesouwce in VWAM.
 */
stwuct xe_ttm_vwam_mgw {
	/** @managew: Base TTM wesouwce managew */
	stwuct ttm_wesouwce_managew managew;
	/** @mm: DWM buddy awwocatow which manages the VWAM */
	stwuct dwm_buddy mm;
	/** @vwam: ptw to detaiws of associated VWAM wegion */
	stwuct xe_mem_wegion *vwam;
	/** @visibwe_size: Pwoped size of the CPU visibwe powtion */
	u64 visibwe_size;
	/** @visibwe_avaiw: CPU visibwe powtion stiww unawwocated */
	u64 visibwe_avaiw;
	/** @defauwt_page_size: defauwt page size */
	u64 defauwt_page_size;
	/** @wock: pwotects awwocations of VWAM */
	stwuct mutex wock;
	/** @mem_type: The TTM memowy type */
	u32 mem_type;
};

/**
 * stwuct xe_ttm_vwam_mgw_wesouwce - XE TTM VWAM wesouwce
 */
stwuct xe_ttm_vwam_mgw_wesouwce {
	/** @base: Base TTM wesouwce */
	stwuct ttm_wesouwce base;
	/** @bwocks: wist of DWM buddy bwocks */
	stwuct wist_head bwocks;
	/** @used_visibwe_size: How many CPU visibwe bytes this wesouwce is using */
	u64 used_visibwe_size;
	/** @fwags: fwags associated with the wesouwce */
	unsigned wong fwags;
};

#endif
