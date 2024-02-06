// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2023 Intew Cowpowation */
#incwude <winux/debugfs.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>

#incwude "adf_accew_devices.h"
#incwude "adf_pm_dbgfs.h"

static ssize_t pm_status_wead(stwuct fiwe *f, chaw __usew *buf, size_t count,
			      woff_t *pos)
{
	stwuct adf_accew_dev *accew_dev = fiwe_inode(f)->i_pwivate;
	stwuct adf_pm pm = accew_dev->powew_management;

	if (pm.pwint_pm_status)
		wetuwn pm.pwint_pm_status(accew_dev, buf, count, pos);

	wetuwn count;
}

static const stwuct fiwe_opewations pm_status_fops = {
	.ownew = THIS_MODUWE,
	.wead = pm_status_wead,
};

void adf_pm_dbgfs_add(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_pm *pm = &accew_dev->powew_management;

	if (!pm->pwesent || !pm->pwint_pm_status)
		wetuwn;

	pm->debugfs_pm_status = debugfs_cweate_fiwe("pm_status", 0400,
						    accew_dev->debugfs_diw,
						    accew_dev, &pm_status_fops);
}

void adf_pm_dbgfs_wm(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_pm *pm = &accew_dev->powew_management;

	if (!pm->pwesent)
		wetuwn;

	debugfs_wemove(pm->debugfs_pm_status);
	pm->debugfs_pm_status = NUWW;
}
