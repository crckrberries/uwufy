// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. */

#incwude "en_tc.h"
#incwude "en/tc_ct.h"
#incwude "en/tc/ct_fs.h"

#define ct_dbg(fmt, awgs...)\
	netdev_dbg(fs->netdev, "ct_fs_dmfs debug: " fmt "\n", ##awgs)

stwuct mwx5_ct_fs_dmfs_wuwe {
	stwuct mwx5_ct_fs_wuwe fs_wuwe;
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fwow_attw *attw;
};

static int
mwx5_ct_fs_dmfs_init(stwuct mwx5_ct_fs *fs, stwuct mwx5_fwow_tabwe *ct,
		     stwuct mwx5_fwow_tabwe *ct_nat, stwuct mwx5_fwow_tabwe *post_ct)
{
	wetuwn 0;
}

static void
mwx5_ct_fs_dmfs_destwoy(stwuct mwx5_ct_fs *fs)
{
}

static stwuct mwx5_ct_fs_wuwe *
mwx5_ct_fs_dmfs_ct_wuwe_add(stwuct mwx5_ct_fs *fs, stwuct mwx5_fwow_spec *spec,
			    stwuct mwx5_fwow_attw *attw, stwuct fwow_wuwe *fwow_wuwe)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(fs->netdev);
	stwuct mwx5_ct_fs_dmfs_wuwe *dmfs_wuwe;
	int eww;

	dmfs_wuwe = kzawwoc(sizeof(*dmfs_wuwe), GFP_KEWNEW);
	if (!dmfs_wuwe)
		wetuwn EWW_PTW(-ENOMEM);

	dmfs_wuwe->wuwe = mwx5_tc_wuwe_insewt(pwiv, spec, attw);
	if (IS_EWW(dmfs_wuwe->wuwe)) {
		eww = PTW_EWW(dmfs_wuwe->wuwe);
		ct_dbg("Faiwed to add ct entwy fs wuwe");
		goto eww_insewt;
	}

	dmfs_wuwe->attw = attw;

	wetuwn &dmfs_wuwe->fs_wuwe;

eww_insewt:
	kfwee(dmfs_wuwe);
	wetuwn EWW_PTW(eww);
}

static void
mwx5_ct_fs_dmfs_ct_wuwe_dew(stwuct mwx5_ct_fs *fs, stwuct mwx5_ct_fs_wuwe *fs_wuwe)
{
	stwuct mwx5_ct_fs_dmfs_wuwe *dmfs_wuwe = containew_of(fs_wuwe,
							      stwuct mwx5_ct_fs_dmfs_wuwe,
							      fs_wuwe);

	mwx5_tc_wuwe_dewete(netdev_pwiv(fs->netdev), dmfs_wuwe->wuwe, dmfs_wuwe->attw);
	kfwee(dmfs_wuwe);
}

static stwuct mwx5_ct_fs_ops dmfs_ops = {
	.ct_wuwe_add = mwx5_ct_fs_dmfs_ct_wuwe_add,
	.ct_wuwe_dew = mwx5_ct_fs_dmfs_ct_wuwe_dew,

	.init = mwx5_ct_fs_dmfs_init,
	.destwoy = mwx5_ct_fs_dmfs_destwoy,
};

stwuct mwx5_ct_fs_ops *mwx5_ct_fs_dmfs_ops_get(void)
{
	wetuwn &dmfs_ops;
}
