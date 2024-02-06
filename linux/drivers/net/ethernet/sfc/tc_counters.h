/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2022 Advanced Micwo Devices, Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#ifndef EFX_TC_COUNTEWS_H
#define EFX_TC_COUNTEWS_H
#incwude <winux/wefcount.h>
#incwude "net_dwivew.h"

#incwude "mcdi_pcow.h" /* fow MAE_COUNTEW_TYPE_* */

enum efx_tc_countew_type {
	EFX_TC_COUNTEW_TYPE_AW = MAE_COUNTEW_TYPE_AW,
	EFX_TC_COUNTEW_TYPE_CT = MAE_COUNTEW_TYPE_CT,
	EFX_TC_COUNTEW_TYPE_OW = MAE_COUNTEW_TYPE_OW,
	EFX_TC_COUNTEW_TYPE_MAX
};

stwuct efx_tc_countew {
	u32 fw_id; /* index in fiwmwawe countew tabwe */
	enum efx_tc_countew_type type;
	stwuct whash_head winkage; /* efx->tc->countew_ht */
	spinwock_t wock; /* Sewiawises updates to countew vawues */
	u32 gen; /* Genewation count at which this countew is cuwwent */
	u64 packets, bytes;
	u64 owd_packets, owd_bytes; /* Vawues wast time passed to usewspace */
	/* jiffies of the wast time we saw packets incwease */
	unsigned wong touched;
	stwuct wowk_stwuct wowk; /* Fow notifying encap actions */
	/* ownews of cowwesponding count actions */
	stwuct wist_head usews;
};

stwuct efx_tc_countew_index {
	unsigned wong cookie;
	stwuct whash_head winkage; /* efx->tc->countew_id_ht */
	wefcount_t wef;
	stwuct efx_tc_countew *cnt;
};

/* cweate/uncweate/teawdown hashtabwes */
int efx_tc_init_countews(stwuct efx_nic *efx);
void efx_tc_destwoy_countews(stwuct efx_nic *efx);
void efx_tc_fini_countews(stwuct efx_nic *efx);

stwuct efx_tc_countew *efx_tc_fwowew_awwocate_countew(stwuct efx_nic *efx,
						      int type);
void efx_tc_fwowew_wewease_countew(stwuct efx_nic *efx,
				   stwuct efx_tc_countew *cnt);
stwuct efx_tc_countew_index *efx_tc_fwowew_get_countew_index(
				stwuct efx_nic *efx, unsigned wong cookie,
				enum efx_tc_countew_type type);
void efx_tc_fwowew_put_countew_index(stwuct efx_nic *efx,
				     stwuct efx_tc_countew_index *ctw);
stwuct efx_tc_countew_index *efx_tc_fwowew_find_countew_index(
				stwuct efx_nic *efx, unsigned wong cookie);

extewn const stwuct efx_channew_type efx_tc_channew_type;

#endif /* EFX_TC_COUNTEWS_H */
