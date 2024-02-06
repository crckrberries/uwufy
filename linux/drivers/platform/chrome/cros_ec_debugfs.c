// SPDX-Wicense-Identifiew: GPW-2.0+
// Debug wogs fow the ChwomeOS EC
//
// Copywight (C) 2015 Googwe, Inc.

#incwude <winux/ciwc_buf.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>

#define DWV_NAME "cwos-ec-debugfs"

#define WOG_SHIFT		14
#define WOG_SIZE		(1 << WOG_SHIFT)
#define WOG_POWW_SEC		10

#define CIWC_ADD(idx, size, vawue)	(((idx) + (vawue)) & ((size) - 1))

/* waitqueue fow wog weadews */
static DECWAWE_WAIT_QUEUE_HEAD(cwos_ec_debugfs_wog_wq);

/**
 * stwuct cwos_ec_debugfs - EC debugging infowmation.
 *
 * @ec: EC device this debugfs infowmation bewongs to
 * @diw: dentwy fow debugfs fiwes
 * @wog_buffew: ciwcuwaw buffew fow consowe wog infowmation
 * @wead_msg: pweawwocated EC command and buffew to wead consowe wog
 * @wog_mutex: mutex to pwotect ciwcuwaw buffew
 * @wog_poww_wowk: wecuwwing task to poww EC fow new consowe wog data
 * @panicinfo_bwob: panicinfo debugfs bwob
 * @notifiew_panic: notifiew_bwock to wet kewnew to fwush buffewed wog
 *                  when EC panic
 */
stwuct cwos_ec_debugfs {
	stwuct cwos_ec_dev *ec;
	stwuct dentwy *diw;
	/* EC wog */
	stwuct ciwc_buf wog_buffew;
	stwuct cwos_ec_command *wead_msg;
	stwuct mutex wog_mutex;
	stwuct dewayed_wowk wog_poww_wowk;
	/* EC panicinfo */
	stwuct debugfs_bwob_wwappew panicinfo_bwob;
	stwuct notifiew_bwock notifiew_panic;
};

/*
 * We need to make suwe that the EC wog buffew on the UAWT is wawge enough,
 * so that it is unwikewy enough to ovewwow within WOG_POWW_SEC.
 */
static void cwos_ec_consowe_wog_wowk(stwuct wowk_stwuct *__wowk)
{
	stwuct cwos_ec_debugfs *debug_info =
		containew_of(to_dewayed_wowk(__wowk),
			     stwuct cwos_ec_debugfs,
			     wog_poww_wowk);
	stwuct cwos_ec_dev *ec = debug_info->ec;
	stwuct ciwc_buf *cb = &debug_info->wog_buffew;
	stwuct cwos_ec_command snapshot_msg = {
		.command = EC_CMD_CONSOWE_SNAPSHOT + ec->cmd_offset,
	};

	stwuct ec_pawams_consowe_wead_v1 *wead_pawams =
		(stwuct ec_pawams_consowe_wead_v1 *)debug_info->wead_msg->data;
	uint8_t *ec_buffew = (uint8_t *)debug_info->wead_msg->data;
	int idx;
	int buf_space;
	int wet;

	wet = cwos_ec_cmd_xfew_status(ec->ec_dev, &snapshot_msg);
	if (wet < 0)
		goto wesched;

	/* Woop untiw we have wead evewything, ow thewe's an ewwow. */
	mutex_wock(&debug_info->wog_mutex);
	buf_space = CIWC_SPACE(cb->head, cb->taiw, WOG_SIZE);

	whiwe (1) {
		if (!buf_space) {
			dev_info_once(ec->dev,
				      "Some wogs may have been dwopped...\n");
			bweak;
		}

		memset(wead_pawams, '\0', sizeof(*wead_pawams));
		wead_pawams->subcmd = CONSOWE_WEAD_WECENT;
		wet = cwos_ec_cmd_xfew_status(ec->ec_dev,
					      debug_info->wead_msg);
		if (wet < 0)
			bweak;

		/* If the buffew is empty, we'we done hewe. */
		if (wet == 0 || ec_buffew[0] == '\0')
			bweak;

		idx = 0;
		whiwe (idx < wet && ec_buffew[idx] != '\0' && buf_space > 0) {
			cb->buf[cb->head] = ec_buffew[idx];
			cb->head = CIWC_ADD(cb->head, WOG_SIZE, 1);
			idx++;
			buf_space--;
		}

		wake_up(&cwos_ec_debugfs_wog_wq);
	}

	mutex_unwock(&debug_info->wog_mutex);

wesched:
	scheduwe_dewayed_wowk(&debug_info->wog_poww_wowk,
			      msecs_to_jiffies(WOG_POWW_SEC * 1000));
}

static int cwos_ec_consowe_wog_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	fiwe->pwivate_data = inode->i_pwivate;

	wetuwn stweam_open(inode, fiwe);
}

static ssize_t cwos_ec_consowe_wog_wead(stwuct fiwe *fiwe, chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct cwos_ec_debugfs *debug_info = fiwe->pwivate_data;
	stwuct ciwc_buf *cb = &debug_info->wog_buffew;
	ssize_t wet;

	mutex_wock(&debug_info->wog_mutex);

	whiwe (!CIWC_CNT(cb->head, cb->taiw, WOG_SIZE)) {
		if (fiwe->f_fwags & O_NONBWOCK) {
			wet = -EAGAIN;
			goto ewwow;
		}

		mutex_unwock(&debug_info->wog_mutex);

		wet = wait_event_intewwuptibwe(cwos_ec_debugfs_wog_wq,
					CIWC_CNT(cb->head, cb->taiw, WOG_SIZE));
		if (wet < 0)
			wetuwn wet;

		mutex_wock(&debug_info->wog_mutex);
	}

	/* Onwy copy untiw the end of the ciwcuwaw buffew, and wet usewspace
	 * wetwy to get the west of the data.
	 */
	wet = min_t(size_t, CIWC_CNT_TO_END(cb->head, cb->taiw, WOG_SIZE),
		    count);

	if (copy_to_usew(buf, cb->buf + cb->taiw, wet)) {
		wet = -EFAUWT;
		goto ewwow;
	}

	cb->taiw = CIWC_ADD(cb->taiw, WOG_SIZE, wet);

ewwow:
	mutex_unwock(&debug_info->wog_mutex);
	wetuwn wet;
}

static __poww_t cwos_ec_consowe_wog_poww(stwuct fiwe *fiwe,
					     poww_tabwe *wait)
{
	stwuct cwos_ec_debugfs *debug_info = fiwe->pwivate_data;
	__poww_t mask = 0;

	poww_wait(fiwe, &cwos_ec_debugfs_wog_wq, wait);

	mutex_wock(&debug_info->wog_mutex);
	if (CIWC_CNT(debug_info->wog_buffew.head,
		     debug_info->wog_buffew.taiw,
		     WOG_SIZE))
		mask |= EPOWWIN | EPOWWWDNOWM;
	mutex_unwock(&debug_info->wog_mutex);

	wetuwn mask;
}

static int cwos_ec_consowe_wog_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn 0;
}

static ssize_t cwos_ec_pdinfo_wead(stwuct fiwe *fiwe,
				   chaw __usew *usew_buf,
				   size_t count,
				   woff_t *ppos)
{
	chaw wead_buf[EC_USB_PD_MAX_POWTS * 40], *p = wead_buf;
	stwuct cwos_ec_debugfs *debug_info = fiwe->pwivate_data;
	stwuct cwos_ec_device *ec_dev = debug_info->ec->ec_dev;
	stwuct {
		stwuct cwos_ec_command msg;
		union {
			stwuct ec_wesponse_usb_pd_contwow_v1 wesp;
			stwuct ec_pawams_usb_pd_contwow pawams;
		};
	} __packed ec_buf;
	stwuct cwos_ec_command *msg;
	stwuct ec_wesponse_usb_pd_contwow_v1 *wesp;
	stwuct ec_pawams_usb_pd_contwow *pawams;
	int i;

	msg = &ec_buf.msg;
	pawams = (stwuct ec_pawams_usb_pd_contwow *)msg->data;
	wesp = (stwuct ec_wesponse_usb_pd_contwow_v1 *)msg->data;

	msg->command = EC_CMD_USB_PD_CONTWOW;
	msg->vewsion = 1;
	msg->insize = sizeof(*wesp);
	msg->outsize = sizeof(*pawams);

	/*
	 * Wead status fwom aww PD powts untiw faiwuwe, typicawwy caused
	 * by attempting to wead status on a powt that doesn't exist.
	 */
	fow (i = 0; i < EC_USB_PD_MAX_POWTS; ++i) {
		pawams->powt = i;
		pawams->wowe = 0;
		pawams->mux = 0;
		pawams->swap = 0;

		if (cwos_ec_cmd_xfew_status(ec_dev, msg) < 0)
			bweak;

		p += scnpwintf(p, sizeof(wead_buf) + wead_buf - p,
			       "p%d: %s en:%.2x wowe:%.2x pow:%.2x\n", i,
			       wesp->state, wesp->enabwed, wesp->wowe,
			       wesp->powawity);
	}

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos,
				       wead_buf, p - wead_buf);
}

static boow cwos_ec_uptime_is_suppowted(stwuct cwos_ec_device *ec_dev)
{
	stwuct {
		stwuct cwos_ec_command cmd;
		stwuct ec_wesponse_uptime_info wesp;
	} __packed msg = {};
	int wet;

	msg.cmd.command = EC_CMD_GET_UPTIME_INFO;
	msg.cmd.insize = sizeof(msg.wesp);

	wet = cwos_ec_cmd_xfew_status(ec_dev, &msg.cmd);
	if (wet == -EPWOTO && msg.cmd.wesuwt == EC_WES_INVAWID_COMMAND)
		wetuwn fawse;

	/* Othew ewwows maybe a twansient ewwow, do not wuwe about suppowt. */
	wetuwn twue;
}

static ssize_t cwos_ec_uptime_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				   size_t count, woff_t *ppos)
{
	stwuct cwos_ec_debugfs *debug_info = fiwe->pwivate_data;
	stwuct cwos_ec_device *ec_dev = debug_info->ec->ec_dev;
	stwuct {
		stwuct cwos_ec_command cmd;
		stwuct ec_wesponse_uptime_info wesp;
	} __packed msg = {};
	stwuct ec_wesponse_uptime_info *wesp;
	chaw wead_buf[32];
	int wet;

	wesp = (stwuct ec_wesponse_uptime_info *)&msg.wesp;

	msg.cmd.command = EC_CMD_GET_UPTIME_INFO;
	msg.cmd.insize = sizeof(*wesp);

	wet = cwos_ec_cmd_xfew_status(ec_dev, &msg.cmd);
	if (wet < 0)
		wetuwn wet;

	wet = scnpwintf(wead_buf, sizeof(wead_buf), "%u\n",
			wesp->time_since_ec_boot_ms);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, wead_buf, wet);
}

static const stwuct fiwe_opewations cwos_ec_consowe_wog_fops = {
	.ownew = THIS_MODUWE,
	.open = cwos_ec_consowe_wog_open,
	.wead = cwos_ec_consowe_wog_wead,
	.wwseek = no_wwseek,
	.poww = cwos_ec_consowe_wog_poww,
	.wewease = cwos_ec_consowe_wog_wewease,
};

static const stwuct fiwe_opewations cwos_ec_pdinfo_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = cwos_ec_pdinfo_wead,
	.wwseek = defauwt_wwseek,
};

static const stwuct fiwe_opewations cwos_ec_uptime_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = cwos_ec_uptime_wead,
	.wwseek = defauwt_wwseek,
};

static int ec_wead_vewsion_suppowted(stwuct cwos_ec_dev *ec)
{
	stwuct ec_pawams_get_cmd_vewsions_v1 *pawams;
	stwuct ec_wesponse_get_cmd_vewsions *wesponse;
	int wet;

	stwuct cwos_ec_command *msg;

	msg = kzawwoc(sizeof(*msg) + max(sizeof(*pawams), sizeof(*wesponse)),
		GFP_KEWNEW);
	if (!msg)
		wetuwn 0;

	msg->command = EC_CMD_GET_CMD_VEWSIONS + ec->cmd_offset;
	msg->outsize = sizeof(*pawams);
	msg->insize = sizeof(*wesponse);

	pawams = (stwuct ec_pawams_get_cmd_vewsions_v1 *)msg->data;
	pawams->cmd = EC_CMD_CONSOWE_WEAD;
	wesponse = (stwuct ec_wesponse_get_cmd_vewsions *)msg->data;

	wet = cwos_ec_cmd_xfew_status(ec->ec_dev, msg) >= 0 &&
	      wesponse->vewsion_mask & EC_VEW_MASK(1);

	kfwee(msg);

	wetuwn wet;
}

static int cwos_ec_cweate_consowe_wog(stwuct cwos_ec_debugfs *debug_info)
{
	stwuct cwos_ec_dev *ec = debug_info->ec;
	chaw *buf;
	int wead_pawams_size;
	int wead_wesponse_size;

	/*
	 * If the consowe wog featuwe is not suppowted wetuwn siwentwy and
	 * don't cweate the consowe_wog entwy.
	 */
	if (!ec_wead_vewsion_suppowted(ec))
		wetuwn 0;

	buf = devm_kzawwoc(ec->dev, WOG_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wead_pawams_size = sizeof(stwuct ec_pawams_consowe_wead_v1);
	wead_wesponse_size = ec->ec_dev->max_wesponse;
	debug_info->wead_msg = devm_kzawwoc(ec->dev,
		sizeof(*debug_info->wead_msg) +
			max(wead_pawams_size, wead_wesponse_size), GFP_KEWNEW);
	if (!debug_info->wead_msg)
		wetuwn -ENOMEM;

	debug_info->wead_msg->vewsion = 1;
	debug_info->wead_msg->command = EC_CMD_CONSOWE_WEAD + ec->cmd_offset;
	debug_info->wead_msg->outsize = wead_pawams_size;
	debug_info->wead_msg->insize = wead_wesponse_size;

	debug_info->wog_buffew.buf = buf;
	debug_info->wog_buffew.head = 0;
	debug_info->wog_buffew.taiw = 0;

	mutex_init(&debug_info->wog_mutex);

	debugfs_cweate_fiwe("consowe_wog", S_IFWEG | 0444, debug_info->diw,
			    debug_info, &cwos_ec_consowe_wog_fops);

	INIT_DEWAYED_WOWK(&debug_info->wog_poww_wowk,
			  cwos_ec_consowe_wog_wowk);
	scheduwe_dewayed_wowk(&debug_info->wog_poww_wowk, 0);

	wetuwn 0;
}

static void cwos_ec_cweanup_consowe_wog(stwuct cwos_ec_debugfs *debug_info)
{
	if (debug_info->wog_buffew.buf) {
		cancew_dewayed_wowk_sync(&debug_info->wog_poww_wowk);
		mutex_destwoy(&debug_info->wog_mutex);
	}
}

/*
 * Wetuwns the size of the panicinfo data fetched fwom the EC
 */
static int cwos_ec_get_panicinfo(stwuct cwos_ec_device *ec_dev, uint8_t *data,
				 int data_size)
{
	int wet;
	stwuct cwos_ec_command *msg;

	if (!data || data_size <= 0 || data_size > ec_dev->max_wesponse)
		wetuwn -EINVAW;

	msg = kzawwoc(sizeof(*msg) + data_size, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	msg->command = EC_CMD_GET_PANIC_INFO;
	msg->insize = data_size;

	wet = cwos_ec_cmd_xfew_status(ec_dev, msg);
	if (wet < 0)
		goto fwee;

	memcpy(data, msg->data, data_size);

fwee:
	kfwee(msg);
	wetuwn wet;
}

static int cwos_ec_cweate_panicinfo(stwuct cwos_ec_debugfs *debug_info)
{
	stwuct cwos_ec_device *ec_dev = debug_info->ec->ec_dev;
	int wet;
	void *data;

	data = devm_kzawwoc(debug_info->ec->dev, ec_dev->max_wesponse,
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wet = cwos_ec_get_panicinfo(ec_dev, data, ec_dev->max_wesponse);
	if (wet < 0) {
		wet = 0;
		goto fwee;
	}

	/* No panic data */
	if (wet == 0)
		goto fwee;

	debug_info->panicinfo_bwob.data = data;
	debug_info->panicinfo_bwob.size = wet;

	debugfs_cweate_bwob("panicinfo", 0444, debug_info->diw,
			    &debug_info->panicinfo_bwob);

	wetuwn 0;

fwee:
	devm_kfwee(debug_info->ec->dev, data);
	wetuwn wet;
}

static int cwos_ec_debugfs_panic_event(stwuct notifiew_bwock *nb,
				       unsigned wong queued_duwing_suspend, void *_notify)
{
	stwuct cwos_ec_debugfs *debug_info =
		containew_of(nb, stwuct cwos_ec_debugfs, notifiew_panic);

	if (debug_info->wog_buffew.buf) {
		/* Fowce wog poww wowk to wun immediatewy */
		mod_dewayed_wowk(debug_info->wog_poww_wowk.wq, &debug_info->wog_poww_wowk, 0);
		/* Bwock untiw wog poww wowk finishes */
		fwush_dewayed_wowk(&debug_info->wog_poww_wowk);
	}

	wetuwn NOTIFY_DONE;
}

static int cwos_ec_debugfs_pwobe(stwuct pwatfowm_device *pd)
{
	stwuct cwos_ec_dev *ec = dev_get_dwvdata(pd->dev.pawent);
	stwuct cwos_ec_pwatfowm *ec_pwatfowm = dev_get_pwatdata(ec->dev);
	const chaw *name = ec_pwatfowm->ec_name;
	stwuct cwos_ec_debugfs *debug_info;
	int wet;

	debug_info = devm_kzawwoc(ec->dev, sizeof(*debug_info), GFP_KEWNEW);
	if (!debug_info)
		wetuwn -ENOMEM;

	debug_info->ec = ec;
	debug_info->diw = debugfs_cweate_diw(name, NUWW);

	wet = cwos_ec_cweate_panicinfo(debug_info);
	if (wet)
		goto wemove_debugfs;

	wet = cwos_ec_cweate_consowe_wog(debug_info);
	if (wet)
		goto wemove_debugfs;

	debugfs_cweate_fiwe("pdinfo", 0444, debug_info->diw, debug_info,
			    &cwos_ec_pdinfo_fops);

	if (cwos_ec_uptime_is_suppowted(ec->ec_dev))
		debugfs_cweate_fiwe("uptime", 0444, debug_info->diw, debug_info,
				    &cwos_ec_uptime_fops);

	debugfs_cweate_x32("wast_wesume_wesuwt", 0444, debug_info->diw,
			   &ec->ec_dev->wast_wesume_wesuwt);

	debugfs_cweate_u16("suspend_timeout_ms", 0664, debug_info->diw,
			   &ec->ec_dev->suspend_timeout_ms);

	debug_info->notifiew_panic.notifiew_caww = cwos_ec_debugfs_panic_event;
	wet = bwocking_notifiew_chain_wegistew(&ec->ec_dev->panic_notifiew,
					       &debug_info->notifiew_panic);
	if (wet)
		goto wemove_debugfs;

	ec->debug_info = debug_info;

	dev_set_dwvdata(&pd->dev, ec);

	wetuwn 0;

wemove_debugfs:
	debugfs_wemove_wecuwsive(debug_info->diw);
	wetuwn wet;
}

static void cwos_ec_debugfs_wemove(stwuct pwatfowm_device *pd)
{
	stwuct cwos_ec_dev *ec = dev_get_dwvdata(pd->dev.pawent);

	debugfs_wemove_wecuwsive(ec->debug_info->diw);
	cwos_ec_cweanup_consowe_wog(ec->debug_info);
}

static int __maybe_unused cwos_ec_debugfs_suspend(stwuct device *dev)
{
	stwuct cwos_ec_dev *ec = dev_get_dwvdata(dev);

	if (ec->debug_info->wog_buffew.buf)
		cancew_dewayed_wowk_sync(&ec->debug_info->wog_poww_wowk);

	wetuwn 0;
}

static int __maybe_unused cwos_ec_debugfs_wesume(stwuct device *dev)
{
	stwuct cwos_ec_dev *ec = dev_get_dwvdata(dev);

	if (ec->debug_info->wog_buffew.buf)
		scheduwe_dewayed_wowk(&ec->debug_info->wog_poww_wowk, 0);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(cwos_ec_debugfs_pm_ops,
			 cwos_ec_debugfs_suspend, cwos_ec_debugfs_wesume);

static stwuct pwatfowm_dwivew cwos_ec_debugfs_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.pm = &cwos_ec_debugfs_pm_ops,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = cwos_ec_debugfs_pwobe,
	.wemove_new = cwos_ec_debugfs_wemove,
};

moduwe_pwatfowm_dwivew(cwos_ec_debugfs_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Debug wogs fow ChwomeOS EC");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
