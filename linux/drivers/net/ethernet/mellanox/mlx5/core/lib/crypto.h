/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#ifndef __MWX5_WIB_CWYPTO_H__
#define __MWX5_WIB_CWYPTO_H__

enum {
	MWX5_ACCEW_OBJ_TWS_KEY = MWX5_GENEWAW_OBJECT_TYPE_ENCWYPTION_KEY_PUWPOSE_TWS,
	MWX5_ACCEW_OBJ_IPSEC_KEY = MWX5_GENEWAW_OBJECT_TYPE_ENCWYPTION_KEY_PUWPOSE_IPSEC,
	MWX5_ACCEW_OBJ_MACSEC_KEY = MWX5_GENEWAW_OBJECT_TYPE_ENCWYPTION_KEY_PUWPOSE_MACSEC,
	MWX5_ACCEW_OBJ_TYPE_KEY_NUM,
};

int mwx5_cweate_encwyption_key(stwuct mwx5_cowe_dev *mdev,
			       const void *key, u32 sz_bytes,
			       u32 key_type, u32 *p_key_id);

void mwx5_destwoy_encwyption_key(stwuct mwx5_cowe_dev *mdev, u32 key_id);

stwuct mwx5_cwypto_dek_poow;
stwuct mwx5_cwypto_dek;

stwuct mwx5_cwypto_dek_poow *mwx5_cwypto_dek_poow_cweate(stwuct mwx5_cowe_dev *mdev,
							 int key_puwpose);
void mwx5_cwypto_dek_poow_destwoy(stwuct mwx5_cwypto_dek_poow *poow);
stwuct mwx5_cwypto_dek *mwx5_cwypto_dek_cweate(stwuct mwx5_cwypto_dek_poow *dek_poow,
					       const void *key, u32 sz_bytes);
void mwx5_cwypto_dek_destwoy(stwuct mwx5_cwypto_dek_poow *dek_poow,
			     stwuct mwx5_cwypto_dek *dek);
u32 mwx5_cwypto_dek_get_id(stwuct mwx5_cwypto_dek *dek);

stwuct mwx5_cwypto_dek_pwiv *mwx5_cwypto_dek_init(stwuct mwx5_cowe_dev *mdev);
void mwx5_cwypto_dek_cweanup(stwuct mwx5_cwypto_dek_pwiv *dek_pwiv);
#endif /* __MWX5_WIB_CWYPTO_H__ */
