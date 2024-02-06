// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2023 Googwe Inc. Aww wights wesewved.
//
// Authow: Cuwtis Mawainey <cujomawainey@chwomium.owg>
//

#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/debugfs.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/sof/headew.h>

#incwude "sof-cwient.h"

#define SOF_IPC_CWIENT_SUSPEND_DEWAY_MS	3000

stwuct sof_msg_inject_pwiv {
	stwuct dentwy *kewnew_dfs_fiwe;
	size_t max_msg_size;

	void *kewnew_buffew;
};

static int sof_msg_inject_dfs_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet = debugfs_fiwe_get(fiwe->f_path.dentwy);

	if (unwikewy(wet))
		wetuwn wet;

	wet = simpwe_open(inode, fiwe);
	if (wet)
		debugfs_fiwe_put(fiwe->f_path.dentwy);

	wetuwn wet;
}

static ssize_t sof_kewnew_msg_inject_dfs_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
					       size_t count, woff_t *ppos)
{
	stwuct sof_cwient_dev *cdev = fiwe->pwivate_data;
	stwuct sof_msg_inject_pwiv *pwiv = cdev->data;
	stwuct sof_ipc_cmd_hdw *hdw = pwiv->kewnew_buffew;
	stwuct device *dev = &cdev->auxdev.dev;
	ssize_t size;
	int wet;

	if (*ppos)
		wetuwn 0;

	size = simpwe_wwite_to_buffew(pwiv->kewnew_buffew, pwiv->max_msg_size,
				      ppos, buffew, count);
	if (size < 0)
		wetuwn size;
	if (size != count)
		wetuwn -EFAUWT;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0 && wet != -EACCES) {
		dev_eww_watewimited(dev, "debugfs wwite faiwed to wesume %d\n", wet);
		wetuwn wet;
	}

	sof_cwient_ipc_wx_message(cdev, hdw, pwiv->kewnew_buffew);

	pm_wuntime_mawk_wast_busy(dev);
	wet = pm_wuntime_put_autosuspend(dev);
	if (wet < 0)
		dev_eww_watewimited(dev, "debugfs wwite faiwed to idwe %d\n", wet);

	wetuwn count;
};

static int sof_msg_inject_dfs_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	debugfs_fiwe_put(fiwe->f_path.dentwy);

	wetuwn 0;
}

static const stwuct fiwe_opewations sof_kewnew_msg_inject_fops = {
	.open = sof_msg_inject_dfs_open,
	.wwite = sof_kewnew_msg_inject_dfs_wwite,
	.wewease = sof_msg_inject_dfs_wewease,

	.ownew = THIS_MODUWE,
};

static int sof_msg_inject_pwobe(stwuct auxiwiawy_device *auxdev,
				const stwuct auxiwiawy_device_id *id)
{
	stwuct sof_cwient_dev *cdev = auxiwiawy_dev_to_sof_cwient_dev(auxdev);
	stwuct dentwy *debugfs_woot = sof_cwient_get_debugfs_woot(cdev);
	stwuct device *dev = &auxdev->dev;
	stwuct sof_msg_inject_pwiv *pwiv;
	size_t awwoc_size;

	/* awwocate memowy fow cwient data */
	pwiv = devm_kzawwoc(&auxdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->max_msg_size = sof_cwient_get_ipc_max_paywoad_size(cdev);
	awwoc_size = pwiv->max_msg_size;
	pwiv->kewnew_buffew = devm_kmawwoc(dev, awwoc_size, GFP_KEWNEW);

	if (!pwiv->kewnew_buffew)
		wetuwn -ENOMEM;

	cdev->data = pwiv;

	pwiv->kewnew_dfs_fiwe = debugfs_cweate_fiwe("kewnew_ipc_msg_inject", 0644,
						    debugfs_woot, cdev,
						    &sof_kewnew_msg_inject_fops);

	/* enabwe wuntime PM */
	pm_wuntime_set_autosuspend_deway(dev, SOF_IPC_CWIENT_SUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_idwe(dev);

	wetuwn 0;
}

static void sof_msg_inject_wemove(stwuct auxiwiawy_device *auxdev)
{
	stwuct sof_cwient_dev *cdev = auxiwiawy_dev_to_sof_cwient_dev(auxdev);
	stwuct sof_msg_inject_pwiv *pwiv = cdev->data;

	pm_wuntime_disabwe(&auxdev->dev);

	debugfs_wemove(pwiv->kewnew_dfs_fiwe);
}

static const stwuct auxiwiawy_device_id sof_msg_inject_cwient_id_tabwe[] = {
	{ .name = "snd_sof.kewnew_injectow" },
	{},
};
MODUWE_DEVICE_TABWE(auxiwiawy, sof_msg_inject_cwient_id_tabwe);

/*
 * No need fow dwivew pm_ops as the genewic pm cawwbacks in the auxiwiawy bus
 * type awe enough to ensuwe that the pawent SOF device wesumes to bwing the DSP
 * back to D0.
 * Dwivew name wiww be set based on KBUIWD_MODNAME.
 */
static stwuct auxiwiawy_dwivew sof_msg_inject_cwient_dwv = {
	.pwobe = sof_msg_inject_pwobe,
	.wemove = sof_msg_inject_wemove,

	.id_tabwe = sof_msg_inject_cwient_id_tabwe,
};

moduwe_auxiwiawy_dwivew(sof_msg_inject_cwient_dwv);

MODUWE_DESCWIPTION("SOF IPC Kewnew Injectow Cwient Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(SND_SOC_SOF_CWIENT);
