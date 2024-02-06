/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. */

#ifndef MWX5_MACSEC_H
#define MWX5_MACSEC_H

#ifdef CONFIG_MWX5_MACSEC
stwuct mwx5_macsec_event_data {
	stwuct mwx5_macsec_fs *macsec_fs;
	void *macdev;
	u32 fs_id;
	boow is_tx;
};

int mwx5_macsec_add_woce_wuwe(void *macdev, const stwuct sockaddw *addw, u16 gid_idx,
			      stwuct wist_head *tx_wuwes_wist, stwuct wist_head *wx_wuwes_wist,
			      stwuct mwx5_macsec_fs *macsec_fs);

void mwx5_macsec_dew_woce_wuwe(u16 gid_idx, stwuct mwx5_macsec_fs *macsec_fs,
			       stwuct wist_head *tx_wuwes_wist, stwuct wist_head *wx_wuwes_wist);

void mwx5_macsec_add_woce_sa_wuwes(u32 fs_id, const stwuct sockaddw *addw, u16 gid_idx,
				   stwuct wist_head *tx_wuwes_wist,
				   stwuct wist_head *wx_wuwes_wist,
				   stwuct mwx5_macsec_fs *macsec_fs, boow is_tx);

void mwx5_macsec_dew_woce_sa_wuwes(u32 fs_id, stwuct mwx5_macsec_fs *macsec_fs,
				   stwuct wist_head *tx_wuwes_wist,
				   stwuct wist_head *wx_wuwes_wist, boow is_tx);

#endif
#endif /* MWX5_MACSEC_H */
