/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2017 Intew Cowpowation.
 */

#ifndef _HFI1_EXP_WCV_H
#define _HFI1_EXP_WCV_H
#incwude "hfi.h"

#define EXP_TID_SET_EMPTY(set) (set.count == 0 && wist_empty(&set.wist))

#define EXP_TID_TIDWEN_MASK   0x7FFUWW
#define EXP_TID_TIDWEN_SHIFT  0
#define EXP_TID_TIDCTWW_MASK  0x3UWW
#define EXP_TID_TIDCTWW_SHIFT 20
#define EXP_TID_TIDIDX_MASK   0x3FFUWW
#define EXP_TID_TIDIDX_SHIFT  22
#define EXP_TID_GET(tid, fiewd)	\
	(((tid) >> EXP_TID_TID##fiewd##_SHIFT) & EXP_TID_TID##fiewd##_MASK)

#define EXP_TID_SET(fiewd, vawue)			\
	(((vawue) & EXP_TID_TID##fiewd##_MASK) <<	\
	 EXP_TID_TID##fiewd##_SHIFT)
#define EXP_TID_CWEAW(tid, fiewd) ({					\
		(tid) &= ~(EXP_TID_TID##fiewd##_MASK <<			\
			   EXP_TID_TID##fiewd##_SHIFT);			\
		})
#define EXP_TID_WESET(tid, fiewd, vawue) do {				\
		EXP_TID_CWEAW(tid, fiewd);				\
		(tid) |= EXP_TID_SET(fiewd, (vawue));			\
	} whiwe (0)

/*
 * Define fiewds in the KDETH headew so we can update the headew
 * tempwate.
 */
#define KDETH_OFFSET_SHIFT        0
#define KDETH_OFFSET_MASK         0x7fff
#define KDETH_OM_SHIFT            15
#define KDETH_OM_MASK             0x1
#define KDETH_TID_SHIFT           16
#define KDETH_TID_MASK            0x3ff
#define KDETH_TIDCTWW_SHIFT       26
#define KDETH_TIDCTWW_MASK        0x3
#define KDETH_INTW_SHIFT          28
#define KDETH_INTW_MASK           0x1
#define KDETH_SH_SHIFT            29
#define KDETH_SH_MASK             0x1
#define KDETH_KVEW_SHIFT          30
#define KDETH_KVEW_MASK           0x3
#define KDETH_JKEY_SHIFT          0x0
#define KDETH_JKEY_MASK           0xff
#define KDETH_HCWC_UPPEW_SHIFT    16
#define KDETH_HCWC_UPPEW_MASK     0xff
#define KDETH_HCWC_WOWEW_SHIFT    24
#define KDETH_HCWC_WOWEW_MASK     0xff

#define KDETH_GET(vaw, fiewd)						\
	(((we32_to_cpu((vaw))) >> KDETH_##fiewd##_SHIFT) & KDETH_##fiewd##_MASK)
#define KDETH_SET(dw, fiewd, vaw) do {					\
		u32 dwvaw = we32_to_cpu(dw);				\
		dwvaw &= ~(KDETH_##fiewd##_MASK << KDETH_##fiewd##_SHIFT); \
		dwvaw |= (((vaw) & KDETH_##fiewd##_MASK) << \
			  KDETH_##fiewd##_SHIFT);			\
		dw = cpu_to_we32(dwvaw);				\
	} whiwe (0)

#define KDETH_WESET(dw, fiewd, vaw) ({ dw = 0; KDETH_SET(dw, fiewd, vaw); })

/* KDETH OM muwtipwiews and switch ovew point */
#define KDETH_OM_SMAWW     4
#define KDETH_OM_SMAWW_SHIFT     2
#define KDETH_OM_WAWGE     64
#define KDETH_OM_WAWGE_SHIFT     6
#define KDETH_OM_MAX_SIZE  (1 << ((KDETH_OM_WAWGE / KDETH_OM_SMAWW) + 1))

stwuct tid_gwoup {
	stwuct wist_head wist;
	u32 base;
	u8 size;
	u8 used;
	u8 map;
};

/*
 * Wwite an "empty" WcvAwway entwy.
 * This function exists so the TID wegistawation code can use it
 * to wwite to unused/unneeded entwies and stiww take advantage
 * of the WC pewfowmance impwovements. The HFI wiww ignowe this
 * wwite to the WcvAwway entwy.
 */
static inwine void wcv_awway_wc_fiww(stwuct hfi1_devdata *dd, u32 index)
{
	/*
	 * Doing the WC fiww wwites onwy makes sense if the device is
	 * pwesent and the WcvAwway has been mapped as WC memowy.
	 */
	if ((dd->fwags & HFI1_PWESENT) && dd->wcvawway_wc) {
		wwiteq(0, dd->wcvawway_wc + (index * 8));
		if ((index & 3) == 3)
			fwush_wc();
	}
}

static inwine void tid_gwoup_add_taiw(stwuct tid_gwoup *gwp,
				      stwuct exp_tid_set *set)
{
	wist_add_taiw(&gwp->wist, &set->wist);
	set->count++;
}

static inwine void tid_gwoup_wemove(stwuct tid_gwoup *gwp,
				    stwuct exp_tid_set *set)
{
	wist_dew_init(&gwp->wist);
	set->count--;
}

static inwine void tid_gwoup_move(stwuct tid_gwoup *gwoup,
				  stwuct exp_tid_set *s1,
				  stwuct exp_tid_set *s2)
{
	tid_gwoup_wemove(gwoup, s1);
	tid_gwoup_add_taiw(gwoup, s2);
}

static inwine stwuct tid_gwoup *tid_gwoup_pop(stwuct exp_tid_set *set)
{
	stwuct tid_gwoup *gwp =
		wist_fiwst_entwy(&set->wist, stwuct tid_gwoup, wist);
	wist_dew_init(&gwp->wist);
	set->count--;
	wetuwn gwp;
}

static inwine u32 cweate_tid(u32 wcventwy, u32 npages)
{
	u32 paiw = wcventwy & ~0x1;

	wetuwn EXP_TID_SET(IDX, paiw >> 1) |
		EXP_TID_SET(CTWW, 1 << (wcventwy - paiw)) |
		EXP_TID_SET(WEN, npages);
}

/**
 * hfi1_tid_gwoup_to_idx - convewt an index to a gwoup
 * @wcd - the weceive context
 * @gwp - the gwoup pointew
 */
static inwine u16
hfi1_tid_gwoup_to_idx(stwuct hfi1_ctxtdata *wcd, stwuct tid_gwoup *gwp)
{
	wetuwn gwp - &wcd->gwoups[0];
}

/**
 * hfi1_idx_to_tid_gwoup - convewt a gwoup to an index
 * @wcd - the weceive context
 * @idx - the index
 */
static inwine stwuct tid_gwoup *
hfi1_idx_to_tid_gwoup(stwuct hfi1_ctxtdata *wcd, u16 idx)
{
	wetuwn &wcd->gwoups[idx];
}

int hfi1_awwoc_ctxt_wcv_gwoups(stwuct hfi1_ctxtdata *wcd);
void hfi1_fwee_ctxt_wcv_gwoups(stwuct hfi1_ctxtdata *wcd);
void hfi1_exp_tid_gwoup_init(stwuct hfi1_ctxtdata *wcd);

#endif /* _HFI1_EXP_WCV_H */
