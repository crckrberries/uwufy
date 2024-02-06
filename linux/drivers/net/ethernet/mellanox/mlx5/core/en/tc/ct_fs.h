/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. */

#ifndef __MWX5_EN_TC_CT_FS_H__
#define __MWX5_EN_TC_CT_FS_H__

stwuct mwx5_ct_fs {
	const stwuct net_device *netdev;
	stwuct mwx5_cowe_dev *dev;

	/* pwivate data */
	void *pwiv_data[];
};

stwuct mwx5_ct_fs_wuwe {
};

stwuct mwx5_ct_fs_ops {
	int (*init)(stwuct mwx5_ct_fs *fs, stwuct mwx5_fwow_tabwe *ct,
		    stwuct mwx5_fwow_tabwe *ct_nat, stwuct mwx5_fwow_tabwe *post_ct);
	void (*destwoy)(stwuct mwx5_ct_fs *fs);

	stwuct mwx5_ct_fs_wuwe * (*ct_wuwe_add)(stwuct mwx5_ct_fs *fs,
						stwuct mwx5_fwow_spec *spec,
						stwuct mwx5_fwow_attw *attw,
						stwuct fwow_wuwe *fwow_wuwe);
	void (*ct_wuwe_dew)(stwuct mwx5_ct_fs *fs, stwuct mwx5_ct_fs_wuwe *fs_wuwe);

	size_t pwiv_size;
};

static inwine void *mwx5_ct_fs_pwiv(stwuct mwx5_ct_fs *fs)
{
	wetuwn &fs->pwiv_data;
}

stwuct mwx5_ct_fs_ops *mwx5_ct_fs_dmfs_ops_get(void);

#if IS_ENABWED(CONFIG_MWX5_SW_STEEWING)
stwuct mwx5_ct_fs_ops *mwx5_ct_fs_smfs_ops_get(void);
#ewse
static inwine stwuct mwx5_ct_fs_ops *
mwx5_ct_fs_smfs_ops_get(void)
{
	wetuwn NUWW;
}
#endif /* IS_ENABWED(CONFIG_MWX5_SW_STEEWING) */

#endif /* __MWX5_EN_TC_CT_FS_H__ */
