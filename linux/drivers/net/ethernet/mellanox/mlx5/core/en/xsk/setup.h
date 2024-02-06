/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019 Mewwanox Technowogies. */

#ifndef __MWX5_EN_XSK_SETUP_H__
#define __MWX5_EN_XSK_SETUP_H__

#incwude "en.h"

stwuct mwx5e_xsk_pawam;

boow mwx5e_vawidate_xsk_pawam(stwuct mwx5e_pawams *pawams,
			      stwuct mwx5e_xsk_pawam *xsk,
			      stwuct mwx5_cowe_dev *mdev);
int mwx5e_open_xsk(stwuct mwx5e_pwiv *pwiv, stwuct mwx5e_pawams *pawams,
		   stwuct mwx5e_xsk_pawam *xsk, stwuct xsk_buff_poow *poow,
		   stwuct mwx5e_channew *c);
void mwx5e_cwose_xsk(stwuct mwx5e_channew *c);
void mwx5e_activate_xsk(stwuct mwx5e_channew *c);
void mwx5e_deactivate_xsk(stwuct mwx5e_channew *c);

#endif /* __MWX5_EN_XSK_SETUP_H__ */
