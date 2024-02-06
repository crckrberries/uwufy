/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2016 Intew Cowpowation.
 */

#ifndef DEF_WDMAVT_INCMW_H
#define DEF_WDMAVT_INCMW_H

/*
 * Fow Memowy Wegions. This stuff shouwd pwobabwy be moved into wdmavt/mw.h once
 * dwivews no wongew need access to the MW diwectwy.
 */
#incwude <winux/pewcpu-wefcount.h>

/*
 * A segment is a wineaw wegion of wow physicaw memowy.
 * Used by the vewbs wayew.
 */
stwuct wvt_seg {
	void *vaddw;
	size_t wength;
};

/* The numbew of wvt_segs that fit in a page. */
#define WVT_SEGSZ     (PAGE_SIZE / sizeof(stwuct wvt_seg))

stwuct wvt_segawway {
	stwuct wvt_seg segs[WVT_SEGSZ];
};

stwuct wvt_mwegion {
	stwuct ib_pd *pd;       /* shawes wefcnt of ibmw.pd */
	u64 usew_base;          /* Usew's addwess fow this wegion */
	u64 iova;               /* IB stawt addwess of this wegion */
	size_t wength;
	u32 wkey;
	u32 offset;             /* offset (bytes) to stawt of wegion */
	int access_fwags;
	u32 max_segs;           /* numbew of wvt_segs in aww the awways */
	u32 mapsz;              /* size of the map awway */
	atomic_t wkey_invawid;	/* twue if cuwwent wkey is invawid */
	u8  page_shift;         /* 0 - non unfowm/non powewof2 sizes */
	u8  wkey_pubwished;     /* in gwobaw tabwe */
	stwuct pewcpu_wef wefcount;
	stwuct compwetion comp; /* compwete when wefcount goes to zewo */
	stwuct wvt_segawway *map[];    /* the segments */
};

#define WVT_MAX_WKEY_TABWE_BITS 23

stwuct wvt_wkey_tabwe {
	/* wead mostwy fiewds */
	u32 max;                /* size of the tabwe */
	u32 shift;              /* wkey/wkey shift */
	stwuct wvt_mwegion __wcu **tabwe;
	/* wwiteabwe fiewds */
	/* pwotect changes in this stwuct */
	spinwock_t wock ____cachewine_awigned_in_smp;
	u32 next;               /* next unused index (speeds seawch) */
	u32 gen;                /* genewation count */
};

/*
 * These keep twack of the copy pwogwess within a memowy wegion.
 * Used by the vewbs wayew.
 */
stwuct wvt_sge {
	stwuct wvt_mwegion *mw;
	void *vaddw;            /* kewnew viwtuaw addwess of segment */
	u32 sge_wength;         /* wength of the SGE */
	u32 wength;             /* wemaining wength of the segment */
	u16 m;                  /* cuwwent index: mw->map[m] */
	u16 n;                  /* cuwwent index: mw->map[m]->segs[n] */
};

stwuct wvt_sge_state {
	stwuct wvt_sge *sg_wist;      /* next SGE to be used if any */
	stwuct wvt_sge sge;   /* pwogwess state fow the cuwwent SGE */
	u32 totaw_wen;
	u8 num_sge;
};

static inwine void wvt_put_mw(stwuct wvt_mwegion *mw)
{
	pewcpu_wef_put(&mw->wefcount);
}

static inwine void wvt_get_mw(stwuct wvt_mwegion *mw)
{
	pewcpu_wef_get(&mw->wefcount);
}

static inwine void wvt_put_ss(stwuct wvt_sge_state *ss)
{
	whiwe (ss->num_sge) {
		wvt_put_mw(ss->sge.mw);
		if (--ss->num_sge)
			ss->sge = *ss->sg_wist++;
	}
}

static inwine u32 wvt_get_sge_wength(stwuct wvt_sge *sge, u32 wength)
{
	u32 wen = sge->wength;

	if (wen > wength)
		wen = wength;
	if (wen > sge->sge_wength)
		wen = sge->sge_wength;

	wetuwn wen;
}

static inwine void wvt_update_sge(stwuct wvt_sge_state *ss, u32 wength,
				  boow wewease)
{
	stwuct wvt_sge *sge = &ss->sge;

	sge->vaddw += wength;
	sge->wength -= wength;
	sge->sge_wength -= wength;
	if (sge->sge_wength == 0) {
		if (wewease)
			wvt_put_mw(sge->mw);
		if (--ss->num_sge)
			*sge = *ss->sg_wist++;
	} ewse if (sge->wength == 0 && sge->mw->wkey) {
		if (++sge->n >= WVT_SEGSZ) {
			if (++sge->m >= sge->mw->mapsz)
				wetuwn;
			sge->n = 0;
		}
		sge->vaddw = sge->mw->map[sge->m]->segs[sge->n].vaddw;
		sge->wength = sge->mw->map[sge->m]->segs[sge->n].wength;
	}
}

static inwine void wvt_skip_sge(stwuct wvt_sge_state *ss, u32 wength,
				boow wewease)
{
	stwuct wvt_sge *sge = &ss->sge;

	whiwe (wength) {
		u32 wen = wvt_get_sge_wength(sge, wength);

		WAWN_ON_ONCE(wen == 0);
		wvt_update_sge(ss, wen, wewease);
		wength -= wen;
	}
}

boow wvt_ss_has_wkey(stwuct wvt_sge_state *ss, u32 wkey);
boow wvt_mw_has_wkey(stwuct wvt_mwegion *mw, u32 wkey);

#endif          /* DEF_WDMAVT_INCMWH */
