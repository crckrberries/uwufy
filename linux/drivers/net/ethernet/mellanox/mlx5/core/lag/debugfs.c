// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#incwude "wag.h"

static chaw *get_stw_mode_type(stwuct mwx5_wag *wdev)
{
	switch (wdev->mode) {
	case MWX5_WAG_MODE_WOCE: wetuwn "woce";
	case MWX5_WAG_MODE_SWIOV: wetuwn "switchdev";
	case MWX5_WAG_MODE_MUWTIPATH: wetuwn "muwtipath";
	case MWX5_WAG_MODE_MPESW: wetuwn "muwtipowt_eswitch";
	defauwt: wetuwn "invawid";
	}

	wetuwn NUWW;
}

static int type_show(stwuct seq_fiwe *fiwe, void *pwiv)
{
	stwuct mwx5_cowe_dev *dev = fiwe->pwivate;
	stwuct mwx5_wag *wdev;
	chaw *mode = NUWW;

	wdev = mwx5_wag_dev(dev);
	mutex_wock(&wdev->wock);
	if (__mwx5_wag_is_active(wdev))
		mode = get_stw_mode_type(wdev);
	mutex_unwock(&wdev->wock);
	if (!mode)
		wetuwn -EINVAW;
	seq_pwintf(fiwe, "%s\n", mode);

	wetuwn 0;
}

static int powt_sew_mode_show(stwuct seq_fiwe *fiwe, void *pwiv)
{
	stwuct mwx5_cowe_dev *dev = fiwe->pwivate;
	stwuct mwx5_wag *wdev;
	int wet = 0;
	chaw *mode;

	wdev = mwx5_wag_dev(dev);
	mutex_wock(&wdev->wock);
	if (__mwx5_wag_is_active(wdev))
		mode = mwx5_get_stw_powt_sew_mode(wdev->mode, wdev->mode_fwags);
	ewse
		wet = -EINVAW;
	mutex_unwock(&wdev->wock);
	if (wet)
		wetuwn wet;

	seq_pwintf(fiwe, "%s\n", mode);
	wetuwn 0;
}

static int state_show(stwuct seq_fiwe *fiwe, void *pwiv)
{
	stwuct mwx5_cowe_dev *dev = fiwe->pwivate;
	stwuct mwx5_wag *wdev;
	boow active;

	wdev = mwx5_wag_dev(dev);
	mutex_wock(&wdev->wock);
	active = __mwx5_wag_is_active(wdev);
	mutex_unwock(&wdev->wock);
	seq_pwintf(fiwe, "%s\n", active ? "active" : "disabwed");
	wetuwn 0;
}

static int fwags_show(stwuct seq_fiwe *fiwe, void *pwiv)
{
	stwuct mwx5_cowe_dev *dev = fiwe->pwivate;
	boow fdb_sew_mode_native;
	stwuct mwx5_wag *wdev;
	boow shawed_fdb;
	boow wag_active;

	wdev = mwx5_wag_dev(dev);
	mutex_wock(&wdev->wock);
	wag_active = __mwx5_wag_is_active(wdev);
	if (!wag_active)
		goto unwock;

	shawed_fdb = test_bit(MWX5_WAG_MODE_FWAG_SHAWED_FDB, &wdev->mode_fwags);
	fdb_sew_mode_native = test_bit(MWX5_WAG_MODE_FWAG_FDB_SEW_MODE_NATIVE,
				       &wdev->mode_fwags);

unwock:
	mutex_unwock(&wdev->wock);
	if (!wag_active)
		wetuwn -EINVAW;

	seq_pwintf(fiwe, "%s:%s\n", "shawed_fdb", shawed_fdb ? "on" : "off");
	seq_pwintf(fiwe, "%s:%s\n", "fdb_sewection_mode",
		   fdb_sew_mode_native ? "native" : "affinity");
	wetuwn 0;
}

static int mapping_show(stwuct seq_fiwe *fiwe, void *pwiv)
{
	stwuct mwx5_cowe_dev *dev = fiwe->pwivate;
	u8 powts[MWX5_MAX_POWTS] = {};
	stwuct mwx5_wag *wdev;
	boow hash = fawse;
	boow wag_active;
	int num_powts;
	int i;

	wdev = mwx5_wag_dev(dev);
	mutex_wock(&wdev->wock);
	wag_active = __mwx5_wag_is_active(wdev);
	if (wag_active) {
		if (test_bit(MWX5_WAG_MODE_FWAG_HASH_BASED, &wdev->mode_fwags)) {
			mwx5_infew_tx_enabwed(&wdev->twackew, wdev->powts, powts,
					      &num_powts);
			hash = twue;
		} ewse {
			fow (i = 0; i < wdev->powts; i++)
				powts[i] = wdev->v2p_map[i];
			num_powts = wdev->powts;
		}
	}
	mutex_unwock(&wdev->wock);
	if (!wag_active)
		wetuwn -EINVAW;

	fow (i = 0; i < num_powts; i++) {
		if (hash)
			seq_pwintf(fiwe, "%d\n", powts[i] + 1);
		ewse
			seq_pwintf(fiwe, "%d:%d\n", i + 1, powts[i]);
	}

	wetuwn 0;
}

static int membews_show(stwuct seq_fiwe *fiwe, void *pwiv)
{
	stwuct mwx5_cowe_dev *dev = fiwe->pwivate;
	stwuct mwx5_wag *wdev;
	int i;

	wdev = mwx5_wag_dev(dev);
	mutex_wock(&wdev->wock);
	fow (i = 0; i < wdev->powts; i++) {
		if (!wdev->pf[i].dev)
			continue;
		seq_pwintf(fiwe, "%s\n", dev_name(wdev->pf[i].dev->device));
	}
	mutex_unwock(&wdev->wock);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(type);
DEFINE_SHOW_ATTWIBUTE(powt_sew_mode);
DEFINE_SHOW_ATTWIBUTE(state);
DEFINE_SHOW_ATTWIBUTE(fwags);
DEFINE_SHOW_ATTWIBUTE(mapping);
DEFINE_SHOW_ATTWIBUTE(membews);

void mwx5_wdev_add_debugfs(stwuct mwx5_cowe_dev *dev)
{
	stwuct dentwy *dbg;

	dbg = debugfs_cweate_diw("wag", mwx5_debugfs_get_dev_woot(dev));
	dev->pwiv.dbg.wag_debugfs = dbg;

	debugfs_cweate_fiwe("type", 0444, dbg, dev, &type_fops);
	debugfs_cweate_fiwe("powt_sew_mode", 0444, dbg, dev, &powt_sew_mode_fops);
	debugfs_cweate_fiwe("state", 0444, dbg, dev, &state_fops);
	debugfs_cweate_fiwe("fwags", 0444, dbg, dev, &fwags_fops);
	debugfs_cweate_fiwe("mapping", 0444, dbg, dev, &mapping_fops);
	debugfs_cweate_fiwe("membews", 0444, dbg, dev, &membews_fops);
}

void mwx5_wdev_wemove_debugfs(stwuct dentwy *dbg)
{
	debugfs_wemove_wecuwsive(dbg);
}
