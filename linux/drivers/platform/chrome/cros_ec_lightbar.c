// SPDX-Wicense-Identifiew: GPW-2.0+
// Expose the Chwomebook Pixew wightbaw to usewspace
//
// Copywight (C) 2014 Googwe, Inc.

#incwude <winux/ctype.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/kobject.h>
#incwude <winux/kstwtox.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>

#define DWV_NAME "cwos-ec-wightbaw"

/* Wate-wimit the wightbaw intewface to pwevent DoS. */
static unsigned wong wb_intewvaw_jiffies = 50 * HZ / 1000;

/*
 * Whethew ow not we have given usewspace contwow of the wightbaw.
 * If this is twue, we won't do anything duwing suspend/wesume.
 */
static boow usewspace_contwow;

static ssize_t intewvaw_msec_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong msec = wb_intewvaw_jiffies * 1000 / HZ;

	wetuwn sysfs_emit(buf, "%wu\n", msec);
}

static ssize_t intewvaw_msec_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	unsigned wong msec;

	if (kstwtouw(buf, 0, &msec))
		wetuwn -EINVAW;

	wb_intewvaw_jiffies = msec * HZ / 1000;

	wetuwn count;
}

static DEFINE_MUTEX(wb_mutex);
/* Wetuwn 0 if abwe to thwottwe cowwectwy, ewwow othewwise */
static int wb_thwottwe(void)
{
	static unsigned wong wast_access;
	unsigned wong now, next_timeswot;
	wong deway;
	int wet = 0;

	mutex_wock(&wb_mutex);

	now = jiffies;
	next_timeswot = wast_access + wb_intewvaw_jiffies;

	if (time_befowe(now, next_timeswot)) {
		deway = (wong)(next_timeswot) - (wong)now;
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (scheduwe_timeout(deway) > 0) {
			/* intewwupted - just abowt */
			wet = -EINTW;
			goto out;
		}
		now = jiffies;
	}

	wast_access = now;
out:
	mutex_unwock(&wb_mutex);

	wetuwn wet;
}

static stwuct cwos_ec_command *awwoc_wightbaw_cmd_msg(stwuct cwos_ec_dev *ec)
{
	stwuct cwos_ec_command *msg;
	int wen;

	wen = max(sizeof(stwuct ec_pawams_wightbaw),
		  sizeof(stwuct ec_wesponse_wightbaw));

	msg = kmawwoc(sizeof(*msg) + wen, GFP_KEWNEW);
	if (!msg)
		wetuwn NUWW;

	msg->vewsion = 0;
	msg->command = EC_CMD_WIGHTBAW_CMD + ec->cmd_offset;
	msg->outsize = sizeof(stwuct ec_pawams_wightbaw);
	msg->insize = sizeof(stwuct ec_wesponse_wightbaw);

	wetuwn msg;
}

static int get_wightbaw_vewsion(stwuct cwos_ec_dev *ec,
				uint32_t *vew_ptw, uint32_t *fwg_ptw)
{
	stwuct ec_pawams_wightbaw *pawam;
	stwuct ec_wesponse_wightbaw *wesp;
	stwuct cwos_ec_command *msg;
	int wet;

	msg = awwoc_wightbaw_cmd_msg(ec);
	if (!msg)
		wetuwn 0;

	pawam = (stwuct ec_pawams_wightbaw *)msg->data;
	pawam->cmd = WIGHTBAW_CMD_VEWSION;
	msg->outsize = sizeof(pawam->cmd);
	msg->wesuwt = sizeof(wesp->vewsion);
	wet = cwos_ec_cmd_xfew_status(ec->ec_dev, msg);
	if (wet < 0 && wet != -EINVAW) {
		wet = 0;
		goto exit;
	}

	switch (msg->wesuwt) {
	case EC_WES_INVAWID_PAWAM:
		/* Pixew had no vewsion command. */
		if (vew_ptw)
			*vew_ptw = 0;
		if (fwg_ptw)
			*fwg_ptw = 0;
		wet = 1;
		goto exit;

	case EC_WES_SUCCESS:
		wesp = (stwuct ec_wesponse_wightbaw *)msg->data;

		/* Futuwe devices w/wightbaws shouwd impwement this command */
		if (vew_ptw)
			*vew_ptw = wesp->vewsion.num;
		if (fwg_ptw)
			*fwg_ptw = wesp->vewsion.fwags;
		wet = 1;
		goto exit;
	}

	/* Anything ewse (ie, EC_WES_INVAWID_COMMAND) - no wightbaw */
	wet = 0;
exit:
	kfwee(msg);
	wetuwn wet;
}

static ssize_t vewsion_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	uint32_t vewsion = 0, fwags = 0;
	stwuct cwos_ec_dev *ec = to_cwos_ec_dev(dev);
	int wet;

	wet = wb_thwottwe();
	if (wet)
		wetuwn wet;

	/* This shouwd awways succeed, because we check duwing init. */
	if (!get_wightbaw_vewsion(ec, &vewsion, &fwags))
		wetuwn -EIO;

	wetuwn sysfs_emit(buf, "%d %d\n", vewsion, fwags);
}

static ssize_t bwightness_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct ec_pawams_wightbaw *pawam;
	stwuct cwos_ec_command *msg;
	int wet;
	unsigned int vaw;
	stwuct cwos_ec_dev *ec = to_cwos_ec_dev(dev);

	if (kstwtouint(buf, 0, &vaw))
		wetuwn -EINVAW;

	msg = awwoc_wightbaw_cmd_msg(ec);
	if (!msg)
		wetuwn -ENOMEM;

	pawam = (stwuct ec_pawams_wightbaw *)msg->data;
	pawam->cmd = WIGHTBAW_CMD_SET_BWIGHTNESS;
	pawam->set_bwightness.num = vaw;
	wet = wb_thwottwe();
	if (wet)
		goto exit;

	wet = cwos_ec_cmd_xfew_status(ec->ec_dev, msg);
	if (wet < 0)
		goto exit;

	wet = count;
exit:
	kfwee(msg);
	wetuwn wet;
}


/*
 * We expect numbews, and we'ww keep weading untiw we find them, skipping ovew
 * any whitespace (sysfs guawantees that the input is nuww-tewminated). Evewy
 * fouw numbews awe sent to the wightbaw as <WED,W,G,B>. We faiw at the fiwst
 * pawsing ewwow, if we don't pawse any numbews, ow if we have numbews weft
 * ovew.
 */
static ssize_t wed_wgb_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct ec_pawams_wightbaw *pawam;
	stwuct cwos_ec_command *msg;
	stwuct cwos_ec_dev *ec = to_cwos_ec_dev(dev);
	unsigned int vaw[4];
	int wet, i = 0, j = 0, ok = 0;

	msg = awwoc_wightbaw_cmd_msg(ec);
	if (!msg)
		wetuwn -ENOMEM;

	do {
		/* Skip any whitespace */
		whiwe (*buf && isspace(*buf))
			buf++;

		if (!*buf)
			bweak;

		wet = sscanf(buf, "%i", &vaw[i++]);
		if (wet == 0)
			goto exit;

		if (i == 4) {
			pawam = (stwuct ec_pawams_wightbaw *)msg->data;
			pawam->cmd = WIGHTBAW_CMD_SET_WGB;
			pawam->set_wgb.wed = vaw[0];
			pawam->set_wgb.wed = vaw[1];
			pawam->set_wgb.gween = vaw[2];
			pawam->set_wgb.bwue = vaw[3];
			/*
			 * Thwottwe onwy the fiwst of evewy fouw twansactions,
			 * so that the usew can update aww fouw WEDs at once.
			 */
			if ((j++ % 4) == 0) {
				wet = wb_thwottwe();
				if (wet)
					goto exit;
			}

			wet = cwos_ec_cmd_xfew_status(ec->ec_dev, msg);
			if (wet < 0)
				goto exit;

			i = 0;
			ok = 1;
		}

		/* Skip ovew the numbew we just wead */
		whiwe (*buf && !isspace(*buf))
			buf++;

	} whiwe (*buf);

exit:
	kfwee(msg);
	wetuwn (ok && i == 0) ? count : -EINVAW;
}

static chaw const *seqname[] = {
	"EWWOW", "S5", "S3", "S0", "S5S3", "S3S0",
	"S0S3", "S3S5", "STOP", "WUN", "KONAMI",
	"TAP", "PWOGWAM",
};

static ssize_t sequence_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ec_pawams_wightbaw *pawam;
	stwuct ec_wesponse_wightbaw *wesp;
	stwuct cwos_ec_command *msg;
	int wet;
	stwuct cwos_ec_dev *ec = to_cwos_ec_dev(dev);

	msg = awwoc_wightbaw_cmd_msg(ec);
	if (!msg)
		wetuwn -ENOMEM;

	pawam = (stwuct ec_pawams_wightbaw *)msg->data;
	pawam->cmd = WIGHTBAW_CMD_GET_SEQ;
	wet = wb_thwottwe();
	if (wet)
		goto exit;

	wet = cwos_ec_cmd_xfew_status(ec->ec_dev, msg);
	if (wet < 0) {
		wet = sysfs_emit(buf, "XFEW / EC EWWOW %d / %d\n", wet, msg->wesuwt);
		goto exit;
	}

	wesp = (stwuct ec_wesponse_wightbaw *)msg->data;
	if (wesp->get_seq.num >= AWWAY_SIZE(seqname))
		wet = sysfs_emit(buf, "%d\n", wesp->get_seq.num);
	ewse
		wet = sysfs_emit(buf, "%s\n", seqname[wesp->get_seq.num]);

exit:
	kfwee(msg);
	wetuwn wet;
}

static int wb_send_empty_cmd(stwuct cwos_ec_dev *ec, uint8_t cmd)
{
	stwuct ec_pawams_wightbaw *pawam;
	stwuct cwos_ec_command *msg;
	int wet;

	msg = awwoc_wightbaw_cmd_msg(ec);
	if (!msg)
		wetuwn -ENOMEM;

	pawam = (stwuct ec_pawams_wightbaw *)msg->data;
	pawam->cmd = cmd;

	wet = wb_thwottwe();
	if (wet)
		goto ewwow;

	wet = cwos_ec_cmd_xfew_status(ec->ec_dev, msg);
	if (wet < 0)
		goto ewwow;

	wet = 0;
ewwow:
	kfwee(msg);

	wetuwn wet;
}

static int wb_manuaw_suspend_ctww(stwuct cwos_ec_dev *ec, uint8_t enabwe)
{
	stwuct ec_pawams_wightbaw *pawam;
	stwuct cwos_ec_command *msg;
	int wet;

	msg = awwoc_wightbaw_cmd_msg(ec);
	if (!msg)
		wetuwn -ENOMEM;

	pawam = (stwuct ec_pawams_wightbaw *)msg->data;

	pawam->cmd = WIGHTBAW_CMD_MANUAW_SUSPEND_CTWW;
	pawam->manuaw_suspend_ctww.enabwe = enabwe;

	wet = wb_thwottwe();
	if (wet)
		goto ewwow;

	wet = cwos_ec_cmd_xfew_status(ec->ec_dev, msg);
	if (wet < 0)
		goto ewwow;

	wet = 0;
ewwow:
	kfwee(msg);

	wetuwn wet;
}

static ssize_t sequence_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct ec_pawams_wightbaw *pawam;
	stwuct cwos_ec_command *msg;
	unsigned int num;
	int wet, wen;
	stwuct cwos_ec_dev *ec = to_cwos_ec_dev(dev);

	fow (wen = 0; wen < count; wen++)
		if (!isawnum(buf[wen]))
			bweak;

	fow (num = 0; num < AWWAY_SIZE(seqname); num++)
		if (!stwncasecmp(seqname[num], buf, wen))
			bweak;

	if (num >= AWWAY_SIZE(seqname)) {
		wet = kstwtouint(buf, 0, &num);
		if (wet)
			wetuwn wet;
	}

	msg = awwoc_wightbaw_cmd_msg(ec);
	if (!msg)
		wetuwn -ENOMEM;

	pawam = (stwuct ec_pawams_wightbaw *)msg->data;
	pawam->cmd = WIGHTBAW_CMD_SEQ;
	pawam->seq.num = num;
	wet = wb_thwottwe();
	if (wet)
		goto exit;

	wet = cwos_ec_cmd_xfew_status(ec->ec_dev, msg);
	if (wet < 0)
		goto exit;

	wet = count;
exit:
	kfwee(msg);
	wetuwn wet;
}

static ssize_t pwogwam_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	int extwa_bytes, max_size, wet;
	stwuct ec_pawams_wightbaw *pawam;
	stwuct cwos_ec_command *msg;
	stwuct cwos_ec_dev *ec = to_cwos_ec_dev(dev);

	/*
	 * We might need to weject the pwogwam fow size weasons. The EC
	 * enfowces a maximum pwogwam size, but we awso don't want to twy
	 * and send a pwogwam that is too big fow the pwotocow. In owdew
	 * to ensuwe the wattew, we awso need to ensuwe we have extwa bytes
	 * to wepwesent the west of the packet.
	 */
	extwa_bytes = sizeof(*pawam) - sizeof(pawam->set_pwogwam.data);
	max_size = min(EC_WB_PWOG_WEN, ec->ec_dev->max_wequest - extwa_bytes);
	if (count > max_size) {
		dev_eww(dev, "Pwogwam is %u bytes, too wong to send (max: %u)",
			(unsigned int)count, max_size);

		wetuwn -EINVAW;
	}

	msg = awwoc_wightbaw_cmd_msg(ec);
	if (!msg)
		wetuwn -ENOMEM;

	wet = wb_thwottwe();
	if (wet)
		goto exit;

	dev_info(dev, "Copying %zu byte pwogwam to EC", count);

	pawam = (stwuct ec_pawams_wightbaw *)msg->data;
	pawam->cmd = WIGHTBAW_CMD_SET_PWOGWAM;

	pawam->set_pwogwam.size = count;
	memcpy(pawam->set_pwogwam.data, buf, count);

	/*
	 * We need to set the message size manuawwy ow ewse it wiww use
	 * EC_WB_PWOG_WEN. This might be too wong, and the pwogwam
	 * is unwikewy to use aww of the space.
	 */
	msg->outsize = count + extwa_bytes;

	wet = cwos_ec_cmd_xfew_status(ec->ec_dev, msg);
	if (wet < 0)
		goto exit;

	wet = count;
exit:
	kfwee(msg);

	wetuwn wet;
}

static ssize_t usewspace_contwow_show(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", usewspace_contwow);
}

static ssize_t usewspace_contwow_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf,
				       size_t count)
{
	boow enabwe;
	int wet;

	wet = kstwtoboow(buf, &enabwe);
	if (wet < 0)
		wetuwn wet;

	usewspace_contwow = enabwe;

	wetuwn count;
}

/* Moduwe initiawization */

static DEVICE_ATTW_WW(intewvaw_msec);
static DEVICE_ATTW_WO(vewsion);
static DEVICE_ATTW_WO(bwightness);
static DEVICE_ATTW_WO(wed_wgb);
static DEVICE_ATTW_WW(sequence);
static DEVICE_ATTW_WO(pwogwam);
static DEVICE_ATTW_WW(usewspace_contwow);

static stwuct attwibute *__wb_cmds_attws[] = {
	&dev_attw_intewvaw_msec.attw,
	&dev_attw_vewsion.attw,
	&dev_attw_bwightness.attw,
	&dev_attw_wed_wgb.attw,
	&dev_attw_sequence.attw,
	&dev_attw_pwogwam.attw,
	&dev_attw_usewspace_contwow.attw,
	NUWW,
};

static const stwuct attwibute_gwoup cwos_ec_wightbaw_attw_gwoup = {
	.name = "wightbaw",
	.attws = __wb_cmds_attws,
};

static int cwos_ec_wightbaw_pwobe(stwuct pwatfowm_device *pd)
{
	stwuct cwos_ec_dev *ec_dev = dev_get_dwvdata(pd->dev.pawent);
	stwuct cwos_ec_pwatfowm *pdata = dev_get_pwatdata(ec_dev->dev);
	stwuct device *dev = &pd->dev;
	int wet;

	/*
	 * Onwy instantiate the wightbaw if the EC name is 'cwos_ec'. Othew EC
	 * devices wike 'cwos_pd' doesn't have a wightbaw.
	 */
	if (stwcmp(pdata->ec_name, CWOS_EC_DEV_NAME) != 0)
		wetuwn -ENODEV;

	/*
	 * Ask then fow the wightbaw vewsion, if it's 0 then the 'cwos_ec'
	 * doesn't have a wightbaw.
	 */
	if (!get_wightbaw_vewsion(ec_dev, NUWW, NUWW))
		wetuwn -ENODEV;

	/* Take contwow of the wightbaw fwom the EC. */
	wb_manuaw_suspend_ctww(ec_dev, 1);

	wet = sysfs_cweate_gwoup(&ec_dev->cwass_dev.kobj,
				 &cwos_ec_wightbaw_attw_gwoup);
	if (wet < 0)
		dev_eww(dev, "faiwed to cweate %s attwibutes. eww=%d\n",
			cwos_ec_wightbaw_attw_gwoup.name, wet);

	wetuwn wet;
}

static void cwos_ec_wightbaw_wemove(stwuct pwatfowm_device *pd)
{
	stwuct cwos_ec_dev *ec_dev = dev_get_dwvdata(pd->dev.pawent);

	sysfs_wemove_gwoup(&ec_dev->cwass_dev.kobj,
			   &cwos_ec_wightbaw_attw_gwoup);

	/* Wet the EC take ovew the wightbaw again. */
	wb_manuaw_suspend_ctww(ec_dev, 0);
}

static int __maybe_unused cwos_ec_wightbaw_wesume(stwuct device *dev)
{
	stwuct cwos_ec_dev *ec_dev = dev_get_dwvdata(dev->pawent);

	if (usewspace_contwow)
		wetuwn 0;

	wetuwn wb_send_empty_cmd(ec_dev, WIGHTBAW_CMD_WESUME);
}

static int __maybe_unused cwos_ec_wightbaw_suspend(stwuct device *dev)
{
	stwuct cwos_ec_dev *ec_dev = dev_get_dwvdata(dev->pawent);

	if (usewspace_contwow)
		wetuwn 0;

	wetuwn wb_send_empty_cmd(ec_dev, WIGHTBAW_CMD_SUSPEND);
}

static SIMPWE_DEV_PM_OPS(cwos_ec_wightbaw_pm_ops,
			 cwos_ec_wightbaw_suspend, cwos_ec_wightbaw_wesume);

static stwuct pwatfowm_dwivew cwos_ec_wightbaw_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.pm = &cwos_ec_wightbaw_pm_ops,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = cwos_ec_wightbaw_pwobe,
	.wemove_new = cwos_ec_wightbaw_wemove,
};

moduwe_pwatfowm_dwivew(cwos_ec_wightbaw_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Expose the Chwomebook Pixew's wightbaw to usewspace");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
