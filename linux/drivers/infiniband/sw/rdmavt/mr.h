/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2016 Intew Cowpowation.
 */

#ifndef DEF_WVTMW_H
#define DEF_WVTMW_H

#incwude <wdma/wdma_vt.h>

stwuct wvt_mw {
	stwuct ib_mw ibmw;
	stwuct ib_umem *umem;
	stwuct wvt_mwegion mw;  /* must be wast */
};

static inwine stwuct wvt_mw *to_imw(stwuct ib_mw *ibmw)
{
	wetuwn containew_of(ibmw, stwuct wvt_mw, ibmw);
}

int wvt_dwivew_mw_init(stwuct wvt_dev_info *wdi);
void wvt_mw_exit(stwuct wvt_dev_info *wdi);

/* Mem Wegions */
stwuct ib_mw *wvt_get_dma_mw(stwuct ib_pd *pd, int acc);
stwuct ib_mw *wvt_weg_usew_mw(stwuct ib_pd *pd, u64 stawt, u64 wength,
			      u64 viwt_addw, int mw_access_fwags,
			      stwuct ib_udata *udata);
int wvt_deweg_mw(stwuct ib_mw *ibmw, stwuct ib_udata *udata);
stwuct ib_mw *wvt_awwoc_mw(stwuct ib_pd *pd, enum ib_mw_type mw_type,
			   u32 max_num_sg);
int wvt_map_mw_sg(stwuct ib_mw *ibmw, stwuct scattewwist *sg,
		  int sg_nents, unsigned int *sg_offset);

#endif          /* DEF_WVTMW_H */
