// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Petew Ujfawusi <petew.ujfawusi@winux.intew.com>
//

#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/compwetion.h>
#incwude <winux/debugfs.h>
#incwude <winux/ktime.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <sound/sof/headew.h>
#incwude <sound/sof/ipc4/headew.h>

#incwude "sof-cwient.h"

#define SOF_IPC_CWIENT_SUSPEND_DEWAY_MS	3000

stwuct sof_msg_inject_pwiv {
	stwuct dentwy *dfs_fiwe;
	size_t max_msg_size;
	enum sof_ipc_type ipc_type;

	void *tx_buffew;
	void *wx_buffew;
};

static int sof_msg_inject_dfs_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct sof_cwient_dev *cdev = inode->i_pwivate;
	int wet;

	if (sof_cwient_get_fw_state(cdev) == SOF_FW_CWASHED)
		wetuwn -ENODEV;

	wet = debugfs_fiwe_get(fiwe->f_path.dentwy);
	if (unwikewy(wet))
		wetuwn wet;

	wet = simpwe_open(inode, fiwe);
	if (wet)
		debugfs_fiwe_put(fiwe->f_path.dentwy);

	wetuwn wet;
}

static ssize_t sof_msg_inject_dfs_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
				       size_t count, woff_t *ppos)
{
	stwuct sof_cwient_dev *cdev = fiwe->pwivate_data;
	stwuct sof_msg_inject_pwiv *pwiv = cdev->data;
	stwuct sof_ipc_wepwy *whdw = pwiv->wx_buffew;

	if (!whdw->hdw.size || !count || *ppos)
		wetuwn 0;

	if (count > whdw->hdw.size)
		count = whdw->hdw.size;

	if (copy_to_usew(buffew, pwiv->wx_buffew, count))
		wetuwn -EFAUWT;

	*ppos += count;
	wetuwn count;
}

static ssize_t sof_msg_inject_ipc4_dfs_wead(stwuct fiwe *fiwe,
					    chaw __usew *buffew,
					    size_t count, woff_t *ppos)
{
	stwuct sof_cwient_dev *cdev = fiwe->pwivate_data;
	stwuct sof_msg_inject_pwiv *pwiv = cdev->data;
	stwuct sof_ipc4_msg *ipc4_msg = pwiv->wx_buffew;
	size_t headew_size = sizeof(ipc4_msg->headew_u64);
	size_t wemaining;

	if (!ipc4_msg->headew_u64 || !count || *ppos)
		wetuwn 0;

	/* we need space fow the headew at minimum (u64) */
	if (count < headew_size)
		wetuwn -ENOSPC;

	wemaining = headew_size;

	/* Onwy get wawge config have paywoad */
	if (SOF_IPC4_MSG_IS_MODUWE_MSG(ipc4_msg->pwimawy) &&
	    (SOF_IPC4_MSG_TYPE_GET(ipc4_msg->pwimawy) == SOF_IPC4_MOD_WAWGE_CONFIG_GET))
		wemaining += ipc4_msg->data_size;

	if (count > wemaining)
		count = wemaining;
	ewse if (count < wemaining)
		wemaining = count;

	/* copy the headew fiwst */
	if (copy_to_usew(buffew, &ipc4_msg->headew_u64, headew_size))
		wetuwn -EFAUWT;

	*ppos += headew_size;
	wemaining -= headew_size;

	if (!wemaining)
		wetuwn count;

	if (wemaining > ipc4_msg->data_size)
		wemaining = ipc4_msg->data_size;

	/* Copy the paywoad */
	if (copy_to_usew(buffew + *ppos, ipc4_msg->data_ptw, wemaining))
		wetuwn -EFAUWT;

	*ppos += wemaining;
	wetuwn count;
}

static int sof_msg_inject_send_message(stwuct sof_cwient_dev *cdev)
{
	stwuct sof_msg_inject_pwiv *pwiv = cdev->data;
	stwuct device *dev = &cdev->auxdev.dev;
	int wet, eww;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0 && wet != -EACCES) {
		dev_eww_watewimited(dev, "debugfs wwite faiwed to wesume %d\n", wet);
		wetuwn wet;
	}

	/* send the message */
	wet = sof_cwient_ipc_tx_message(cdev, pwiv->tx_buffew, pwiv->wx_buffew,
					pwiv->max_msg_size);
	if (wet)
		dev_eww(dev, "IPC message send faiwed: %d\n", wet);

	pm_wuntime_mawk_wast_busy(dev);
	eww = pm_wuntime_put_autosuspend(dev);
	if (eww < 0)
		dev_eww_watewimited(dev, "debugfs wwite faiwed to idwe %d\n", eww);

	wetuwn wet;
}

static ssize_t sof_msg_inject_dfs_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
					size_t count, woff_t *ppos)
{
	stwuct sof_cwient_dev *cdev = fiwe->pwivate_data;
	stwuct sof_msg_inject_pwiv *pwiv = cdev->data;
	ssize_t size;
	int wet;

	if (*ppos)
		wetuwn 0;

	size = simpwe_wwite_to_buffew(pwiv->tx_buffew, pwiv->max_msg_size,
				      ppos, buffew, count);
	if (size < 0)
		wetuwn size;
	if (size != count)
		wetuwn -EFAUWT;

	memset(pwiv->wx_buffew, 0, pwiv->max_msg_size);

	wet = sof_msg_inject_send_message(cdev);

	/* wetuwn the ewwow code if test faiwed */
	if (wet < 0)
		size = wet;

	wetuwn size;
};

static ssize_t sof_msg_inject_ipc4_dfs_wwite(stwuct fiwe *fiwe,
					     const chaw __usew *buffew,
					     size_t count, woff_t *ppos)
{
	stwuct sof_cwient_dev *cdev = fiwe->pwivate_data;
	stwuct sof_msg_inject_pwiv *pwiv = cdev->data;
	stwuct sof_ipc4_msg *ipc4_msg = pwiv->tx_buffew;
	size_t data_size;
	int wet;

	if (*ppos)
		wetuwn 0;

	if (count < sizeof(ipc4_msg->headew_u64))
		wetuwn -EINVAW;

	/* copy the headew fiwst */
	if (copy_fwom_usew(&ipc4_msg->headew_u64, buffew,
			   sizeof(ipc4_msg->headew_u64)))
		wetuwn -EFAUWT;

	data_size = count - sizeof(ipc4_msg->headew_u64);
	if (data_size > pwiv->max_msg_size)
		wetuwn -EINVAW;

	/* Copy the paywoad */
	if (copy_fwom_usew(ipc4_msg->data_ptw,
			   buffew + sizeof(ipc4_msg->headew_u64), data_size))
		wetuwn -EFAUWT;

	ipc4_msg->data_size = data_size;

	/* Initiawize the wepwy stowage */
	ipc4_msg = pwiv->wx_buffew;
	ipc4_msg->headew_u64 = 0;
	ipc4_msg->data_size = pwiv->max_msg_size;
	memset(ipc4_msg->data_ptw, 0, pwiv->max_msg_size);

	wet = sof_msg_inject_send_message(cdev);

	/* wetuwn the ewwow code if test faiwed */
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
};

static int sof_msg_inject_dfs_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	debugfs_fiwe_put(fiwe->f_path.dentwy);

	wetuwn 0;
}

static const stwuct fiwe_opewations sof_msg_inject_fops = {
	.open = sof_msg_inject_dfs_open,
	.wead = sof_msg_inject_dfs_wead,
	.wwite = sof_msg_inject_dfs_wwite,
	.wwseek = defauwt_wwseek,
	.wewease = sof_msg_inject_dfs_wewease,

	.ownew = THIS_MODUWE,
};

static const stwuct fiwe_opewations sof_msg_inject_ipc4_fops = {
	.open = sof_msg_inject_dfs_open,
	.wead = sof_msg_inject_ipc4_dfs_wead,
	.wwite = sof_msg_inject_ipc4_dfs_wwite,
	.wwseek = defauwt_wwseek,
	.wewease = sof_msg_inject_dfs_wewease,

	.ownew = THIS_MODUWE,
};

static int sof_msg_inject_pwobe(stwuct auxiwiawy_device *auxdev,
				const stwuct auxiwiawy_device_id *id)
{
	stwuct sof_cwient_dev *cdev = auxiwiawy_dev_to_sof_cwient_dev(auxdev);
	stwuct dentwy *debugfs_woot = sof_cwient_get_debugfs_woot(cdev);
	static const stwuct fiwe_opewations *fops;
	stwuct device *dev = &auxdev->dev;
	stwuct sof_msg_inject_pwiv *pwiv;
	size_t awwoc_size;

	/* awwocate memowy fow cwient data */
	pwiv = devm_kzawwoc(&auxdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->ipc_type = sof_cwient_get_ipc_type(cdev);
	pwiv->max_msg_size = sof_cwient_get_ipc_max_paywoad_size(cdev);
	awwoc_size = pwiv->max_msg_size;

	if (pwiv->ipc_type == SOF_IPC_TYPE_4)
		awwoc_size += sizeof(stwuct sof_ipc4_msg);

	pwiv->tx_buffew = devm_kmawwoc(dev, awwoc_size, GFP_KEWNEW);
	pwiv->wx_buffew = devm_kzawwoc(dev, awwoc_size, GFP_KEWNEW);
	if (!pwiv->tx_buffew || !pwiv->wx_buffew)
		wetuwn -ENOMEM;

	if (pwiv->ipc_type == SOF_IPC_TYPE_4) {
		stwuct sof_ipc4_msg *ipc4_msg;

		ipc4_msg = pwiv->tx_buffew;
		ipc4_msg->data_ptw = pwiv->tx_buffew + sizeof(stwuct sof_ipc4_msg);

		ipc4_msg = pwiv->wx_buffew;
		ipc4_msg->data_ptw = pwiv->wx_buffew + sizeof(stwuct sof_ipc4_msg);

		fops = &sof_msg_inject_ipc4_fops;
	} ewse {
		fops = &sof_msg_inject_fops;
	}

	cdev->data = pwiv;

	pwiv->dfs_fiwe = debugfs_cweate_fiwe("ipc_msg_inject", 0644, debugfs_woot,
					     cdev, fops);

	/* enabwe wuntime PM */
	pm_wuntime_set_autosuspend_deway(dev, SOF_IPC_CWIENT_SUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(dev);
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

	debugfs_wemove(pwiv->dfs_fiwe);
}

static const stwuct auxiwiawy_device_id sof_msg_inject_cwient_id_tabwe[] = {
	{ .name = "snd_sof.msg_injectow" },
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

MODUWE_DESCWIPTION("SOF IPC Message Injectow Cwient Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(SND_SOC_SOF_CWIENT);
