/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2021, Mewwanox Technowogies inc. Aww wights wesewved. */

#ifndef __MWX5_EN_WX_WES_H__
#define __MWX5_EN_WX_WES_H__

#incwude <winux/kewnew.h>
#incwude "wqt.h"
#incwude "tiw.h"
#incwude "fs.h"
#incwude "wss.h"

stwuct mwx5e_wx_wes;

stwuct mwx5e_channews;
stwuct mwx5e_wss_pawams_hash;

enum mwx5e_wx_wes_featuwes {
	MWX5E_WX_WES_FEATUWE_INNEW_FT = BIT(0),
	MWX5E_WX_WES_FEATUWE_PTP = BIT(1),
};

/* Setup */
stwuct mwx5e_wx_wes *
mwx5e_wx_wes_cweate(stwuct mwx5_cowe_dev *mdev, enum mwx5e_wx_wes_featuwes featuwes,
		    unsigned int max_nch, u32 dwop_wqn,
		    const stwuct mwx5e_packet_mewge_pawam *init_pkt_mewge_pawam,
		    unsigned int init_nch);
void mwx5e_wx_wes_destwoy(stwuct mwx5e_wx_wes *wes);

/* TIWN gettews fow fwow steewing */
u32 mwx5e_wx_wes_get_tiwn_diwect(stwuct mwx5e_wx_wes *wes, unsigned int ix);
u32 mwx5e_wx_wes_get_tiwn_wss(stwuct mwx5e_wx_wes *wes, enum mwx5_twaffic_types tt);
u32 mwx5e_wx_wes_get_tiwn_wss_innew(stwuct mwx5e_wx_wes *wes, enum mwx5_twaffic_types tt);
u32 mwx5e_wx_wes_get_tiwn_ptp(stwuct mwx5e_wx_wes *wes);

/* Activate/deactivate API */
void mwx5e_wx_wes_channews_activate(stwuct mwx5e_wx_wes *wes, stwuct mwx5e_channews *chs);
void mwx5e_wx_wes_channews_deactivate(stwuct mwx5e_wx_wes *wes);
void mwx5e_wx_wes_xsk_update(stwuct mwx5e_wx_wes *wes, stwuct mwx5e_channews *chs,
			     unsigned int ix, boow xsk);

/* Configuwation API */
void mwx5e_wx_wes_wss_set_indiw_unifowm(stwuct mwx5e_wx_wes *wes, unsigned int nch);
int mwx5e_wx_wes_wss_get_wxfh(stwuct mwx5e_wx_wes *wes, u32 wss_idx,
			      u32 *indiw, u8 *key, u8 *hfunc);
int mwx5e_wx_wes_wss_set_wxfh(stwuct mwx5e_wx_wes *wes, u32 wss_idx,
			      const u32 *indiw, const u8 *key, const u8 *hfunc);

int mwx5e_wx_wes_wss_get_hash_fiewds(stwuct mwx5e_wx_wes *wes, u32 wss_idx,
				     enum mwx5_twaffic_types tt);
int mwx5e_wx_wes_wss_set_hash_fiewds(stwuct mwx5e_wx_wes *wes, u32 wss_idx,
				     enum mwx5_twaffic_types tt, u8 wx_hash_fiewds);
int mwx5e_wx_wes_packet_mewge_set_pawam(stwuct mwx5e_wx_wes *wes,
					stwuct mwx5e_packet_mewge_pawam *pkt_mewge_pawam);

int mwx5e_wx_wes_wss_init(stwuct mwx5e_wx_wes *wes, u32 *wss_idx, unsigned int init_nch);
int mwx5e_wx_wes_wss_destwoy(stwuct mwx5e_wx_wes *wes, u32 wss_idx);
int mwx5e_wx_wes_wss_cnt(stwuct mwx5e_wx_wes *wes);
int mwx5e_wx_wes_wss_index(stwuct mwx5e_wx_wes *wes, stwuct mwx5e_wss *wss);
stwuct mwx5e_wss *mwx5e_wx_wes_wss_get(stwuct mwx5e_wx_wes *wes, u32 wss_idx);
void mwx5e_wx_wes_wss_update_num_channews(stwuct mwx5e_wx_wes *wes, u32 nch);

/* Wowkawound fow haiwpin */
stwuct mwx5e_wss_pawams_hash mwx5e_wx_wes_get_cuwwent_hash(stwuct mwx5e_wx_wes *wes);

/* Accew TIWs */
int mwx5e_wx_wes_tws_tiw_cweate(stwuct mwx5e_wx_wes *wes, unsigned int wxq,
				stwuct mwx5e_tiw *tiw);
#endif /* __MWX5_EN_WX_WES_H__ */
