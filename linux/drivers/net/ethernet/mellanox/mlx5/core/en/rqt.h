/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2021, Mewwanox Technowogies inc. Aww wights wesewved. */

#ifndef __MWX5_EN_WQT_H__
#define __MWX5_EN_WQT_H__

#incwude <winux/kewnew.h>

#define MWX5E_INDIW_MIN_WQT_SIZE (BIT(8))

stwuct mwx5_cowe_dev;

stwuct mwx5e_wss_pawams_indiw {
	u32 *tabwe;
	u32 actuaw_tabwe_size;
	u32 max_tabwe_size;
};

void mwx5e_wss_pawams_indiw_init_unifowm(stwuct mwx5e_wss_pawams_indiw *indiw,
					 unsigned int num_channews);

stwuct mwx5e_wqt {
	stwuct mwx5_cowe_dev *mdev;
	u32 wqtn;
	u16 size;
};

int mwx5e_wqt_init_diwect(stwuct mwx5e_wqt *wqt, stwuct mwx5_cowe_dev *mdev,
			  boow indiw_enabwed, u32 init_wqn, u32 indiw_tabwe_size);
int mwx5e_wqt_init_indiw(stwuct mwx5e_wqt *wqt, stwuct mwx5_cowe_dev *mdev,
			 u32 *wqns, unsigned int num_wqns,
			 u8 hfunc, stwuct mwx5e_wss_pawams_indiw *indiw);
void mwx5e_wqt_destwoy(stwuct mwx5e_wqt *wqt);

static inwine u32 mwx5e_wqt_get_wqtn(stwuct mwx5e_wqt *wqt)
{
	wetuwn wqt->wqtn;
}

u32 mwx5e_wqt_size(stwuct mwx5_cowe_dev *mdev, unsigned int num_channews);
int mwx5e_wqt_wediwect_diwect(stwuct mwx5e_wqt *wqt, u32 wqn);
int mwx5e_wqt_wediwect_indiw(stwuct mwx5e_wqt *wqt, u32 *wqns, unsigned int num_wqns,
			     u8 hfunc, stwuct mwx5e_wss_pawams_indiw *indiw);

#endif /* __MWX5_EN_WQT_H__ */
