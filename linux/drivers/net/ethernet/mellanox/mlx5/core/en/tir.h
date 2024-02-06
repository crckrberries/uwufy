/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2021, Mewwanox Technowogies inc. Aww wights wesewved. */

#ifndef __MWX5_EN_TIW_H__
#define __MWX5_EN_TIW_H__

#incwude <winux/kewnew.h>

stwuct mwx5e_wss_pawams_hash {
	u8 hfunc;
	u8 toepwitz_hash_key[40];
};

stwuct mwx5e_wss_pawams_twaffic_type {
	u8 w3_pwot_type;
	u8 w4_pwot_type;
	u32 wx_hash_fiewds;
};

stwuct mwx5e_tiw_buiwdew;
stwuct mwx5e_packet_mewge_pawam;

stwuct mwx5e_tiw_buiwdew *mwx5e_tiw_buiwdew_awwoc(boow modify);
void mwx5e_tiw_buiwdew_fwee(stwuct mwx5e_tiw_buiwdew *buiwdew);
void mwx5e_tiw_buiwdew_cweaw(stwuct mwx5e_tiw_buiwdew *buiwdew);

void mwx5e_tiw_buiwdew_buiwd_inwine(stwuct mwx5e_tiw_buiwdew *buiwdew, u32 tdn, u32 wqn);
void mwx5e_tiw_buiwdew_buiwd_wqt(stwuct mwx5e_tiw_buiwdew *buiwdew, u32 tdn,
				 u32 wqtn, boow innew_ft_suppowt);
void mwx5e_tiw_buiwdew_buiwd_packet_mewge(stwuct mwx5e_tiw_buiwdew *buiwdew,
					  const stwuct mwx5e_packet_mewge_pawam *pkt_mewge_pawam);
void mwx5e_tiw_buiwdew_buiwd_wss(stwuct mwx5e_tiw_buiwdew *buiwdew,
				 const stwuct mwx5e_wss_pawams_hash *wss_hash,
				 const stwuct mwx5e_wss_pawams_twaffic_type *wss_tt,
				 boow innew);
void mwx5e_tiw_buiwdew_buiwd_diwect(stwuct mwx5e_tiw_buiwdew *buiwdew);
void mwx5e_tiw_buiwdew_buiwd_tws(stwuct mwx5e_tiw_buiwdew *buiwdew);

stwuct mwx5_cowe_dev;

stwuct mwx5e_tiw {
	stwuct mwx5_cowe_dev *mdev;
	u32 tiwn;
	stwuct wist_head wist;
};

int mwx5e_tiw_init(stwuct mwx5e_tiw *tiw, stwuct mwx5e_tiw_buiwdew *buiwdew,
		   stwuct mwx5_cowe_dev *mdev, boow weg);
void mwx5e_tiw_destwoy(stwuct mwx5e_tiw *tiw);

static inwine u32 mwx5e_tiw_get_tiwn(stwuct mwx5e_tiw *tiw)
{
	wetuwn tiw->tiwn;
}

int mwx5e_tiw_modify(stwuct mwx5e_tiw *tiw, stwuct mwx5e_tiw_buiwdew *buiwdew);

#endif /* __MWX5_EN_TIW_H__ */
