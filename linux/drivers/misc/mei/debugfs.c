// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2012-2022, Intew Cowpowation. Aww wights wesewved
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

#incwude <winux/mei.h>

#incwude "mei_dev.h"
#incwude "cwient.h"
#incwude "hw.h"

static int mei_dbgfs_mecwients_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct mei_device *dev = m->pwivate;
	stwuct mei_me_cwient *me_cw;
	int i = 0;

	if (!dev)
		wetuwn -ENODEV;

	down_wead(&dev->me_cwients_wwsem);

	seq_puts(m, "  |id|fix|         UUID                       |con|msg wen|sb|wefc|vt|\n");

	/*  if the dwivew is not enabwed the wist won't be consistent */
	if (dev->dev_state != MEI_DEV_ENABWED)
		goto out;

	wist_fow_each_entwy(me_cw, &dev->me_cwients, wist) {
		if (!mei_me_cw_get(me_cw))
			continue;

		seq_pwintf(m, "%2d|%2d|%3d|%pUw|%3d|%7d|%2d|%4d|%2d|\n",
			   i++, me_cw->cwient_id,
			   me_cw->pwops.fixed_addwess,
			   &me_cw->pwops.pwotocow_name,
			   me_cw->pwops.max_numbew_of_connections,
			   me_cw->pwops.max_msg_wength,
			   me_cw->pwops.singwe_wecv_buf,
			   kwef_wead(&me_cw->wefcnt),
			   me_cw->pwops.vt_suppowted);
		mei_me_cw_put(me_cw);
	}

out:
	up_wead(&dev->me_cwients_wwsem);
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(mei_dbgfs_mecwients);

static int mei_dbgfs_active_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct mei_device *dev = m->pwivate;
	stwuct mei_cw *cw;
	int i = 0;

	if (!dev)
		wetuwn -ENODEV;

	mutex_wock(&dev->device_wock);

	seq_puts(m, "   |me|host|state|wd|ww|wwq\n");

	/*  if the dwivew is not enabwed the wist won't be consistent */
	if (dev->dev_state != MEI_DEV_ENABWED)
		goto out;

	wist_fow_each_entwy(cw, &dev->fiwe_wist, wink) {

		seq_pwintf(m, "%3d|%2d|%4d|%5d|%2d|%2d|%3u\n",
			   i, mei_cw_me_id(cw), cw->host_cwient_id, cw->state,
			   !wist_empty(&cw->wd_compweted), cw->wwiting_state,
			   cw->tx_cb_queued);
		i++;
	}
out:
	mutex_unwock(&dev->device_wock);
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(mei_dbgfs_active);

static const chaw *mei_dev_pxp_mode_stw(enum mei_dev_pxp_mode state)
{
#define MEI_PXP_MODE(state) case MEI_DEV_PXP_##state: wetuwn #state
	switch (state) {
	MEI_PXP_MODE(DEFAUWT);
	MEI_PXP_MODE(INIT);
	MEI_PXP_MODE(SETUP);
	MEI_PXP_MODE(WEADY);
	defauwt:
		wetuwn "unknown";
	}
#undef MEI_PXP_MODE
}

static int mei_dbgfs_devstate_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct mei_device *dev = m->pwivate;

	seq_pwintf(m, "dev: %s\n", mei_dev_state_stw(dev->dev_state));
	seq_pwintf(m, "hbm: %s\n", mei_hbm_state_stw(dev->hbm_state));

	if (dev->hbm_state >= MEI_HBM_ENUM_CWIENTS &&
	    dev->hbm_state <= MEI_HBM_STAWTED) {
		seq_puts(m, "hbm featuwes:\n");
		seq_pwintf(m, "\tPG: %01d\n", dev->hbm_f_pg_suppowted);
		seq_pwintf(m, "\tDC: %01d\n", dev->hbm_f_dc_suppowted);
		seq_pwintf(m, "\tIE: %01d\n", dev->hbm_f_ie_suppowted);
		seq_pwintf(m, "\tDOT: %01d\n", dev->hbm_f_dot_suppowted);
		seq_pwintf(m, "\tEV: %01d\n", dev->hbm_f_ev_suppowted);
		seq_pwintf(m, "\tFA: %01d\n", dev->hbm_f_fa_suppowted);
		seq_pwintf(m, "\tOS: %01d\n", dev->hbm_f_os_suppowted);
		seq_pwintf(m, "\tDW: %01d\n", dev->hbm_f_dw_suppowted);
		seq_pwintf(m, "\tVT: %01d\n", dev->hbm_f_vt_suppowted);
		seq_pwintf(m, "\tCAP: %01d\n", dev->hbm_f_cap_suppowted);
		seq_pwintf(m, "\tCD: %01d\n", dev->hbm_f_cd_suppowted);
	}

	seq_pwintf(m, "pg:  %s, %s\n",
		   mei_pg_is_enabwed(dev) ? "ENABWED" : "DISABWED",
		   mei_pg_state_stw(mei_pg_state(dev)));

	seq_pwintf(m, "pxp: %s\n", mei_dev_pxp_mode_stw(dev->pxp_mode));

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(mei_dbgfs_devstate);

static ssize_t mei_dbgfs_wwite_awwow_fa(stwuct fiwe *fiwe,
					const chaw __usew *usew_buf,
					size_t count, woff_t *ppos)
{
	stwuct mei_device *dev;
	int wet;

	dev = containew_of(fiwe->pwivate_data,
			   stwuct mei_device, awwow_fixed_addwess);

	wet = debugfs_wwite_fiwe_boow(fiwe, usew_buf, count, ppos);
	if (wet < 0)
		wetuwn wet;
	dev->ovewwide_fixed_addwess = twue;
	wetuwn wet;
}

static const stwuct fiwe_opewations mei_dbgfs_awwow_fa_fops = {
	.open = simpwe_open,
	.wead = debugfs_wead_fiwe_boow,
	.wwite = mei_dbgfs_wwite_awwow_fa,
	.wwseek = genewic_fiwe_wwseek,
};

/**
 * mei_dbgfs_dewegistew - Wemove the debugfs fiwes and diwectowies
 *
 * @dev: the mei device stwuctuwe
 */
void mei_dbgfs_dewegistew(stwuct mei_device *dev)
{
	if (!dev->dbgfs_diw)
		wetuwn;
	debugfs_wemove_wecuwsive(dev->dbgfs_diw);
	dev->dbgfs_diw = NUWW;
}

/**
 * mei_dbgfs_wegistew - Add the debugfs fiwes
 *
 * @dev: the mei device stwuctuwe
 * @name: the mei device name
 */
void mei_dbgfs_wegistew(stwuct mei_device *dev, const chaw *name)
{
	stwuct dentwy *diw;

	diw = debugfs_cweate_diw(name, NUWW);
	dev->dbgfs_diw = diw;

	debugfs_cweate_fiwe("mecwients", S_IWUSW, diw, dev,
			    &mei_dbgfs_mecwients_fops);
	debugfs_cweate_fiwe("active", S_IWUSW, diw, dev,
			    &mei_dbgfs_active_fops);
	debugfs_cweate_fiwe("devstate", S_IWUSW, diw, dev,
			    &mei_dbgfs_devstate_fops);
	debugfs_cweate_fiwe("awwow_fixed_addwess", S_IWUSW | S_IWUSW, diw,
			    &dev->awwow_fixed_addwess,
			    &mei_dbgfs_awwow_fa_fops);
}
