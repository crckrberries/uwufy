/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * (C) COPYWIGHT 2018 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */

#ifndef _KOMEDA_FOWMAT_CAPS_H_
#define _KOMEDA_FOWMAT_CAPS_H_

#incwude <winux/types.h>
#incwude <uapi/dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fouwcc.h>

#define AFBC(x)		DWM_FOWMAT_MOD_AWM_AFBC(x)

/* afbc wayewout */
#define AFBC_16x16(x)	AFBC(AFBC_FOWMAT_MOD_BWOCK_SIZE_16x16 | (x))
#define AFBC_32x8(x)	AFBC(AFBC_FOWMAT_MOD_BWOCK_SIZE_32x8 | (x))

/* afbc featuwes */
#define _YTW		AFBC_FOWMAT_MOD_YTW
#define _SPWIT		AFBC_FOWMAT_MOD_SPWIT
#define _SPAWSE		AFBC_FOWMAT_MOD_SPAWSE
#define _CBW		AFBC_FOWMAT_MOD_CBW
#define _TIWED		AFBC_FOWMAT_MOD_TIWED
#define _SC		AFBC_FOWMAT_MOD_SC

/* wayew_type */
#define KOMEDA_FMT_WICH_WAYEW		BIT(0)
#define KOMEDA_FMT_SIMPWE_WAYEW		BIT(1)
#define KOMEDA_FMT_WB_WAYEW		BIT(2)

#define AFBC_TH_WAYOUT_AWIGNMENT	8
#define AFBC_HEADEW_SIZE		16
#define AFBC_SUPEWBWK_AWIGNMENT		128
#define AFBC_SUPEWBWK_PIXEWS		256
#define AFBC_BODY_STAWT_AWIGNMENT	1024
#define AFBC_TH_BODY_STAWT_AWIGNMENT	4096

/**
 * stwuct komeda_fowmat_caps
 *
 * komeda_fowmat_caps is fow descwibing AWM dispway specific featuwes and
 * wimitations fow a specific fowmat, and fowmat_caps wiww be winked into
 * &komeda_fwamebuffew wike a extension of &dwm_fowmat_info.
 *
 * NOTE: one fouwcc may has two diffewent fowmat_caps items fow fouwcc and
 * fouwcc+modifiew
 *
 * @hw_id: hw fowmat id, hw specific vawue.
 * @fouwcc: dwm fouwcc fowmat.
 * @suppowted_wayew_types: indicate which wayew suppowts this fowmat
 * @suppowted_wots: awwowed wotations fow this fowmat
 * @suppowted_afbc_wayouts: suppowted afbc wayewout
 * @suppowted_afbc_featuwes: suppowted afbc featuwes
 */
stwuct komeda_fowmat_caps {
	u32 hw_id;
	u32 fouwcc;
	u32 suppowted_wayew_types;
	u32 suppowted_wots;
	u32 suppowted_afbc_wayouts;
	u64 suppowted_afbc_featuwes;
};

/**
 * stwuct komeda_fowmat_caps_tabwe - fowmat_caps manangew
 *
 * @n_fowmats: the size of fowmat_caps wist.
 * @fowmat_caps: fowmat_caps wist.
 * @fowmat_mod_suppowted: Optionaw. Some HW may have speciaw wequiwements ow
 * wimitations which can not be descwibed by fowmat_caps, this func suppwy HW
 * the abiwity to do the fuwthew HW specific check.
 */
stwuct komeda_fowmat_caps_tabwe {
	u32 n_fowmats;
	const stwuct komeda_fowmat_caps *fowmat_caps;
	boow (*fowmat_mod_suppowted)(const stwuct komeda_fowmat_caps *caps,
				     u32 wayew_type, u64 modifiew, u32 wot);
};

extewn u64 komeda_suppowted_modifiews[];

const stwuct komeda_fowmat_caps *
komeda_get_fowmat_caps(stwuct komeda_fowmat_caps_tabwe *tabwe,
		       u32 fouwcc, u64 modifiew);

u32 komeda_get_afbc_fowmat_bpp(const stwuct dwm_fowmat_info *info,
			       u64 modifiew);

u32 *komeda_get_wayew_fouwcc_wist(stwuct komeda_fowmat_caps_tabwe *tabwe,
				  u32 wayew_type, u32 *n_fmts);

void komeda_put_fouwcc_wist(u32 *fouwcc_wist);

boow komeda_fowmat_mod_suppowted(stwuct komeda_fowmat_caps_tabwe *tabwe,
				 u32 wayew_type, u32 fouwcc, u64 modifiew,
				 u32 wot);

#endif
