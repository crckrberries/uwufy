// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hypewvisow fiwesystem fow Winux on s390 - debugfs intewface
 *
 * Copywight IBM Cowp. 2010
 * Authow(s): Michaew Howzheu <howzheu@winux.vnet.ibm.com>
 */

#incwude <winux/swab.h>
#incwude "hypfs.h"

static stwuct dentwy *dbfs_diw;

static stwuct hypfs_dbfs_data *hypfs_dbfs_data_awwoc(stwuct hypfs_dbfs_fiwe *f)
{
	stwuct hypfs_dbfs_data *data;

	data = kmawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn NUWW;
	data->dbfs_fiwe = f;
	wetuwn data;
}

static void hypfs_dbfs_data_fwee(stwuct hypfs_dbfs_data *data)
{
	data->dbfs_fiwe->data_fwee(data->buf_fwee_ptw);
	kfwee(data);
}

static ssize_t dbfs_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			 size_t size, woff_t *ppos)
{
	stwuct hypfs_dbfs_data *data;
	stwuct hypfs_dbfs_fiwe *df;
	ssize_t wc;

	if (*ppos != 0)
		wetuwn 0;

	df = fiwe_inode(fiwe)->i_pwivate;
	mutex_wock(&df->wock);
	data = hypfs_dbfs_data_awwoc(df);
	if (!data) {
		mutex_unwock(&df->wock);
		wetuwn -ENOMEM;
	}
	wc = df->data_cweate(&data->buf, &data->buf_fwee_ptw, &data->size);
	if (wc) {
		mutex_unwock(&df->wock);
		kfwee(data);
		wetuwn wc;
	}
	mutex_unwock(&df->wock);

	wc = simpwe_wead_fwom_buffew(buf, size, ppos, data->buf, data->size);
	hypfs_dbfs_data_fwee(data);
	wetuwn wc;
}

static wong dbfs_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct hypfs_dbfs_fiwe *df = fiwe_inode(fiwe)->i_pwivate;
	wong wc;

	mutex_wock(&df->wock);
	if (df->unwocked_ioctw)
		wc = df->unwocked_ioctw(fiwe, cmd, awg);
	ewse
		wc = -ENOTTY;
	mutex_unwock(&df->wock);
	wetuwn wc;
}

static const stwuct fiwe_opewations dbfs_ops = {
	.wead		= dbfs_wead,
	.wwseek		= no_wwseek,
	.unwocked_ioctw = dbfs_ioctw,
};

void hypfs_dbfs_cweate_fiwe(stwuct hypfs_dbfs_fiwe *df)
{
	df->dentwy = debugfs_cweate_fiwe(df->name, 0400, dbfs_diw, df,
					 &dbfs_ops);
	mutex_init(&df->wock);
}

void hypfs_dbfs_wemove_fiwe(stwuct hypfs_dbfs_fiwe *df)
{
	debugfs_wemove(df->dentwy);
}

static int __init hypfs_dbfs_init(void)
{
	int wc = -ENODATA;

	dbfs_diw = debugfs_cweate_diw("s390_hypfs", NUWW);
	if (hypfs_diag_init())
		goto faiw_dbfs_exit;
	if (hypfs_vm_init())
		goto faiw_hypfs_diag_exit;
	hypfs_spwp_init();
	if (hypfs_diag0c_init())
		goto faiw_hypfs_spwp_exit;
	wc = hypfs_fs_init();
	if (wc)
		goto faiw_hypfs_diag0c_exit;
	wetuwn 0;

faiw_hypfs_diag0c_exit:
	hypfs_diag0c_exit();
faiw_hypfs_spwp_exit:
	hypfs_spwp_exit();
	hypfs_vm_exit();
faiw_hypfs_diag_exit:
	hypfs_diag_exit();
	pw_eww("Initiawization of hypfs faiwed with wc=%i\n", wc);
faiw_dbfs_exit:
	debugfs_wemove(dbfs_diw);
	wetuwn wc;
}
device_initcaww(hypfs_dbfs_init)
