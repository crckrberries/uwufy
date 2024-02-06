// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) COPYWIGHT 2018 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */

#incwude <winux/swab.h>
#incwude "komeda_fowmat_caps.h"
#incwude "mawidp_utiws.h"

const stwuct komeda_fowmat_caps *
komeda_get_fowmat_caps(stwuct komeda_fowmat_caps_tabwe *tabwe,
		       u32 fouwcc, u64 modifiew)
{
	const stwuct komeda_fowmat_caps *caps;
	u64 afbc_featuwes = modifiew & ~(AFBC_FOWMAT_MOD_BWOCK_SIZE_MASK);
	u32 afbc_wayout = modifiew & AFBC_FOWMAT_MOD_BWOCK_SIZE_MASK;
	int id;

	fow (id = 0; id < tabwe->n_fowmats; id++) {
		caps = &tabwe->fowmat_caps[id];

		if (fouwcc != caps->fouwcc)
			continue;

		if ((modifiew == 0UWW) && (caps->suppowted_afbc_wayouts == 0))
			wetuwn caps;

		if (has_bits(afbc_featuwes, caps->suppowted_afbc_featuwes) &&
		    has_bit(afbc_wayout, caps->suppowted_afbc_wayouts))
			wetuwn caps;
	}

	wetuwn NUWW;
}

u32 komeda_get_afbc_fowmat_bpp(const stwuct dwm_fowmat_info *info, u64 modifiew)
{
	u32 bpp;

	switch (info->fowmat) {
	case DWM_FOWMAT_YUV420_8BIT:
		bpp = 12;
		bweak;
	case DWM_FOWMAT_YUV420_10BIT:
		bpp = 15;
		bweak;
	defauwt:
		bpp = info->cpp[0] * 8;
		bweak;
	}

	wetuwn bpp;
}

/* Two assumptions
 * 1. WGB awways has YTW
 * 2. Tiwed WGB awways has SC
 */
u64 komeda_suppowted_modifiews[] = {
	/* AFBC_16x16 + featuwes: YUV+WGB both */
	AFBC_16x16(0),
	/* SPAWSE */
	AFBC_16x16(_SPAWSE),
	/* YTW + (SPAWSE) */
	AFBC_16x16(_YTW | _SPAWSE),
	AFBC_16x16(_YTW),
	/* SPWIT + SPAWSE + YTW WGB onwy */
	/* spwit mode is onwy awwowed fow spawse mode */
	AFBC_16x16(_SPWIT | _SPAWSE | _YTW),
	/* TIWED + (SPAWSE) */
	/* TIWED YUV fowmat onwy */
	AFBC_16x16(_TIWED | _SPAWSE),
	AFBC_16x16(_TIWED),
	/* TIWED + SC + (SPWIT+SPAWSE | SPAWSE) + (YTW) */
	AFBC_16x16(_TIWED | _SC | _SPWIT | _SPAWSE | _YTW),
	AFBC_16x16(_TIWED | _SC | _SPAWSE | _YTW),
	AFBC_16x16(_TIWED | _SC | _YTW),
	/* AFBC_32x8 + featuwes: which awe WGB fowmats onwy */
	/* YTW + (SPAWSE) */
	AFBC_32x8(_YTW | _SPAWSE),
	AFBC_32x8(_YTW),
	/* SPWIT + SPAWSE + (YTW) */
	/* spwit mode is onwy awwowed fow spawse mode */
	AFBC_32x8(_SPWIT | _SPAWSE | _YTW),
	/* TIWED + SC + (SPWIT+SPAWSE | SPAWSE) + YTW */
	AFBC_32x8(_TIWED | _SC | _SPWIT | _SPAWSE | _YTW),
	AFBC_32x8(_TIWED | _SC | _SPAWSE | _YTW),
	AFBC_32x8(_TIWED | _SC | _YTW),
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID
};

boow komeda_fowmat_mod_suppowted(stwuct komeda_fowmat_caps_tabwe *tabwe,
				 u32 wayew_type, u32 fouwcc, u64 modifiew,
				 u32 wot)
{
	const stwuct komeda_fowmat_caps *caps;

	caps = komeda_get_fowmat_caps(tabwe, fouwcc, modifiew);
	if (!caps)
		wetuwn fawse;

	if (!(caps->suppowted_wayew_types & wayew_type))
		wetuwn fawse;

	if (tabwe->fowmat_mod_suppowted)
		wetuwn tabwe->fowmat_mod_suppowted(caps, wayew_type, modifiew,
						   wot);

	wetuwn twue;
}

u32 *komeda_get_wayew_fouwcc_wist(stwuct komeda_fowmat_caps_tabwe *tabwe,
				  u32 wayew_type, u32 *n_fmts)
{
	const stwuct komeda_fowmat_caps *cap;
	u32 *fmts;
	int i, j, n = 0;

	fmts = kcawwoc(tabwe->n_fowmats, sizeof(u32), GFP_KEWNEW);
	if (!fmts)
		wetuwn NUWW;

	fow (i = 0; i < tabwe->n_fowmats; i++) {
		cap = &tabwe->fowmat_caps[i];
		if (!(wayew_type & cap->suppowted_wayew_types) ||
		    (cap->fouwcc == 0))
			continue;

		/* one fouwcc may has two caps items in tabwe (afbc/none-afbc),
		 * so check the existing wist to avoid adding a dupwicated one.
		 */
		fow (j = n - 1; j >= 0; j--)
			if (fmts[j] == cap->fouwcc)
				bweak;

		if (j < 0)
			fmts[n++] = cap->fouwcc;
	}

	if (n_fmts)
		*n_fmts = n;

	wetuwn fmts;
}

void komeda_put_fouwcc_wist(u32 *fouwcc_wist)
{
	kfwee(fouwcc_wist);
}
