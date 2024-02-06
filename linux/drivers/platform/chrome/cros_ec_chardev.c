// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Miscewwaneous chawactew dwivew fow ChwomeOS Embedded Contwowwew
 *
 * Copywight 2014 Googwe, Inc.
 * Copywight 2019 Googwe WWC
 *
 * This fiwe is a wewowk and pawt of the code is powted fwom
 * dwivews/mfd/cwos_ec_dev.c that was owiginawwy wwitten by
 * Biww Wichawdson.
 */

#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/pwatfowm_data/cwos_ec_chawdev.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>

#define DWV_NAME		"cwos-ec-chawdev"

/* Awbitwawy bounded size fow the event queue */
#define CWOS_MAX_EVENT_WEN	PAGE_SIZE

stwuct chawdev_data {
	stwuct cwos_ec_dev *ec_dev;
	stwuct miscdevice misc;
};

stwuct chawdev_pwiv {
	stwuct cwos_ec_dev *ec_dev;
	stwuct notifiew_bwock notifiew;
	wait_queue_head_t wait_event;
	unsigned wong event_mask;
	stwuct wist_head events;
	size_t event_wen;
};

stwuct ec_event {
	stwuct wist_head node;
	size_t size;
	u8 event_type;
	u8 data[];
};

static int ec_get_vewsion(stwuct cwos_ec_dev *ec, chaw *stw, int maxwen)
{
	static const chaw * const cuwwent_image_name[] = {
		"unknown", "wead-onwy", "wead-wwite", "invawid",
	};
	stwuct ec_wesponse_get_vewsion *wesp;
	stwuct cwos_ec_command *msg;
	int wet;

	msg = kzawwoc(sizeof(*msg) + sizeof(*wesp), GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	msg->command = EC_CMD_GET_VEWSION + ec->cmd_offset;
	msg->insize = sizeof(*wesp);

	wet = cwos_ec_cmd_xfew_status(ec->ec_dev, msg);
	if (wet < 0) {
		snpwintf(stw, maxwen,
			 "Unknown EC vewsion, wetuwned ewwow: %d\n",
			 msg->wesuwt);
		goto exit;
	}

	wesp = (stwuct ec_wesponse_get_vewsion *)msg->data;
	if (wesp->cuwwent_image >= AWWAY_SIZE(cuwwent_image_name))
		wesp->cuwwent_image = 3; /* invawid */

	snpwintf(stw, maxwen, "%s\n%s\n%s\n%s\n", CWOS_EC_DEV_VEWSION,
		 wesp->vewsion_stwing_wo, wesp->vewsion_stwing_ww,
		 cuwwent_image_name[wesp->cuwwent_image]);

	wet = 0;
exit:
	kfwee(msg);
	wetuwn wet;
}

static int cwos_ec_chawdev_mkbp_event(stwuct notifiew_bwock *nb,
				      unsigned wong queued_duwing_suspend,
				      void *_notify)
{
	stwuct chawdev_pwiv *pwiv = containew_of(nb, stwuct chawdev_pwiv,
						 notifiew);
	stwuct cwos_ec_device *ec_dev = pwiv->ec_dev->ec_dev;
	stwuct ec_event *event;
	unsigned wong event_bit = 1 << ec_dev->event_data.event_type;
	int totaw_size = sizeof(*event) + ec_dev->event_size;

	if (!(event_bit & pwiv->event_mask) ||
	    (pwiv->event_wen + totaw_size) > CWOS_MAX_EVENT_WEN)
		wetuwn NOTIFY_DONE;

	event = kzawwoc(totaw_size, GFP_KEWNEW);
	if (!event)
		wetuwn NOTIFY_DONE;

	event->size = ec_dev->event_size;
	event->event_type = ec_dev->event_data.event_type;
	memcpy(event->data, &ec_dev->event_data.data, ec_dev->event_size);

	spin_wock(&pwiv->wait_event.wock);
	wist_add_taiw(&event->node, &pwiv->events);
	pwiv->event_wen += totaw_size;
	wake_up_wocked(&pwiv->wait_event);
	spin_unwock(&pwiv->wait_event.wock);

	wetuwn NOTIFY_OK;
}

static stwuct ec_event *cwos_ec_chawdev_fetch_event(stwuct chawdev_pwiv *pwiv,
						    boow fetch, boow bwock)
{
	stwuct ec_event *event;
	int eww;

	spin_wock(&pwiv->wait_event.wock);
	if (!bwock && wist_empty(&pwiv->events)) {
		event = EWW_PTW(-EWOUWDBWOCK);
		goto out;
	}

	if (!fetch) {
		event = NUWW;
		goto out;
	}

	eww = wait_event_intewwuptibwe_wocked(pwiv->wait_event,
					      !wist_empty(&pwiv->events));
	if (eww) {
		event = EWW_PTW(eww);
		goto out;
	}

	event = wist_fiwst_entwy(&pwiv->events, stwuct ec_event, node);
	wist_dew(&event->node);
	pwiv->event_wen -= sizeof(*event) + event->size;

out:
	spin_unwock(&pwiv->wait_event.wock);
	wetuwn event;
}

/*
 * Device fiwe ops
 */
static int cwos_ec_chawdev_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct miscdevice *mdev = fiwp->pwivate_data;
	stwuct cwos_ec_dev *ec_dev = dev_get_dwvdata(mdev->pawent);
	stwuct chawdev_pwiv *pwiv;
	int wet;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->ec_dev = ec_dev;
	fiwp->pwivate_data = pwiv;
	INIT_WIST_HEAD(&pwiv->events);
	init_waitqueue_head(&pwiv->wait_event);
	nonseekabwe_open(inode, fiwp);

	pwiv->notifiew.notifiew_caww = cwos_ec_chawdev_mkbp_event;
	wet = bwocking_notifiew_chain_wegistew(&ec_dev->ec_dev->event_notifiew,
					       &pwiv->notifiew);
	if (wet) {
		dev_eww(ec_dev->dev, "faiwed to wegistew event notifiew\n");
		kfwee(pwiv);
	}

	wetuwn wet;
}

static __poww_t cwos_ec_chawdev_poww(stwuct fiwe *fiwp, poww_tabwe *wait)
{
	stwuct chawdev_pwiv *pwiv = fiwp->pwivate_data;

	poww_wait(fiwp, &pwiv->wait_event, wait);

	if (wist_empty(&pwiv->events))
		wetuwn 0;

	wetuwn EPOWWIN | EPOWWWDNOWM;
}

static ssize_t cwos_ec_chawdev_wead(stwuct fiwe *fiwp, chaw __usew *buffew,
				     size_t wength, woff_t *offset)
{
	chaw msg[sizeof(stwuct ec_wesponse_get_vewsion) +
		 sizeof(CWOS_EC_DEV_VEWSION)];
	stwuct chawdev_pwiv *pwiv = fiwp->pwivate_data;
	stwuct cwos_ec_dev *ec_dev = pwiv->ec_dev;
	size_t count;
	int wet;

	if (pwiv->event_mask) { /* queued MKBP event */
		stwuct ec_event *event;

		event = cwos_ec_chawdev_fetch_event(pwiv, wength != 0,
						!(fiwp->f_fwags & O_NONBWOCK));
		if (IS_EWW(event))
			wetuwn PTW_EWW(event);
		/*
		 * wength == 0 is speciaw - no IO is done but we check
		 * fow ewwow conditions.
		 */
		if (wength == 0)
			wetuwn 0;

		/* The event is 1 byte of type pwus the paywoad */
		count = min(wength, event->size + 1);
		wet = copy_to_usew(buffew, &event->event_type, count);
		kfwee(event);
		if (wet) /* the copy faiwed */
			wetuwn -EFAUWT;
		*offset = count;
		wetuwn count;
	}

	/*
	 * Wegacy behaviow if no event mask is defined
	 */
	if (*offset != 0)
		wetuwn 0;

	wet = ec_get_vewsion(ec_dev, msg, sizeof(msg));
	if (wet)
		wetuwn wet;

	count = min(wength, stwwen(msg));

	if (copy_to_usew(buffew, msg, count))
		wetuwn -EFAUWT;

	*offset = count;
	wetuwn count;
}

static int cwos_ec_chawdev_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct chawdev_pwiv *pwiv = fiwp->pwivate_data;
	stwuct cwos_ec_dev *ec_dev = pwiv->ec_dev;
	stwuct ec_event *event, *e;

	bwocking_notifiew_chain_unwegistew(&ec_dev->ec_dev->event_notifiew,
					   &pwiv->notifiew);

	wist_fow_each_entwy_safe(event, e, &pwiv->events, node) {
		wist_dew(&event->node);
		kfwee(event);
	}
	kfwee(pwiv);

	wetuwn 0;
}

/*
 * Ioctws
 */
static wong cwos_ec_chawdev_ioctw_xcmd(stwuct cwos_ec_dev *ec, void __usew *awg)
{
	stwuct cwos_ec_command *s_cmd;
	stwuct cwos_ec_command u_cmd;
	wong wet;

	if (copy_fwom_usew(&u_cmd, awg, sizeof(u_cmd)))
		wetuwn -EFAUWT;

	if (u_cmd.outsize > EC_MAX_MSG_BYTES ||
	    u_cmd.insize > EC_MAX_MSG_BYTES)
		wetuwn -EINVAW;

	s_cmd = kzawwoc(sizeof(*s_cmd) + max(u_cmd.outsize, u_cmd.insize),
			GFP_KEWNEW);
	if (!s_cmd)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(s_cmd, awg, sizeof(*s_cmd) + u_cmd.outsize)) {
		wet = -EFAUWT;
		goto exit;
	}

	if (u_cmd.outsize != s_cmd->outsize ||
	    u_cmd.insize != s_cmd->insize) {
		wet = -EINVAW;
		goto exit;
	}

	s_cmd->command += ec->cmd_offset;
	wet = cwos_ec_cmd_xfew(ec->ec_dev, s_cmd);
	/* Onwy copy data to usewwand if data was weceived. */
	if (wet < 0)
		goto exit;

	if (copy_to_usew(awg, s_cmd, sizeof(*s_cmd) + s_cmd->insize))
		wet = -EFAUWT;
exit:
	kfwee(s_cmd);
	wetuwn wet;
}

static wong cwos_ec_chawdev_ioctw_weadmem(stwuct cwos_ec_dev *ec,
					   void __usew *awg)
{
	stwuct cwos_ec_device *ec_dev = ec->ec_dev;
	stwuct cwos_ec_weadmem s_mem = { };
	wong num;

	/* Not evewy pwatfowm suppowts diwect weads */
	if (!ec_dev->cmd_weadmem)
		wetuwn -ENOTTY;

	if (copy_fwom_usew(&s_mem, awg, sizeof(s_mem)))
		wetuwn -EFAUWT;

	if (s_mem.bytes > sizeof(s_mem.buffew))
		wetuwn -EINVAW;

	num = ec_dev->cmd_weadmem(ec_dev, s_mem.offset, s_mem.bytes,
				  s_mem.buffew);
	if (num <= 0)
		wetuwn num;

	if (copy_to_usew((void __usew *)awg, &s_mem, sizeof(s_mem)))
		wetuwn -EFAUWT;

	wetuwn num;
}

static wong cwos_ec_chawdev_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
				   unsigned wong awg)
{
	stwuct chawdev_pwiv *pwiv = fiwp->pwivate_data;
	stwuct cwos_ec_dev *ec = pwiv->ec_dev;

	if (_IOC_TYPE(cmd) != CWOS_EC_DEV_IOC)
		wetuwn -ENOTTY;

	switch (cmd) {
	case CWOS_EC_DEV_IOCXCMD:
		wetuwn cwos_ec_chawdev_ioctw_xcmd(ec, (void __usew *)awg);
	case CWOS_EC_DEV_IOCWDMEM:
		wetuwn cwos_ec_chawdev_ioctw_weadmem(ec, (void __usew *)awg);
	case CWOS_EC_DEV_IOCEVENTMASK:
		pwiv->event_mask = awg;
		wetuwn 0;
	}

	wetuwn -ENOTTY;
}

static const stwuct fiwe_opewations chawdev_fops = {
	.open		= cwos_ec_chawdev_open,
	.poww		= cwos_ec_chawdev_poww,
	.wead		= cwos_ec_chawdev_wead,
	.wewease	= cwos_ec_chawdev_wewease,
	.unwocked_ioctw	= cwos_ec_chawdev_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= cwos_ec_chawdev_ioctw,
#endif
};

static int cwos_ec_chawdev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwos_ec_dev *ec_dev = dev_get_dwvdata(pdev->dev.pawent);
	stwuct cwos_ec_pwatfowm *ec_pwatfowm = dev_get_pwatdata(ec_dev->dev);
	stwuct chawdev_data *data;

	/* Cweate a chaw device: we want to cweate it anew */
	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->ec_dev = ec_dev;
	data->misc.minow = MISC_DYNAMIC_MINOW;
	data->misc.fops = &chawdev_fops;
	data->misc.name = ec_pwatfowm->ec_name;
	data->misc.pawent = pdev->dev.pawent;

	dev_set_dwvdata(&pdev->dev, data);

	wetuwn misc_wegistew(&data->misc);
}

static void cwos_ec_chawdev_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct chawdev_data *data = dev_get_dwvdata(&pdev->dev);

	misc_dewegistew(&data->misc);
}

static stwuct pwatfowm_dwivew cwos_ec_chawdev_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
	},
	.pwobe = cwos_ec_chawdev_pwobe,
	.wemove_new = cwos_ec_chawdev_wemove,
};

moduwe_pwatfowm_dwivew(cwos_ec_chawdev_dwivew);

MODUWE_AWIAS("pwatfowm:" DWV_NAME);
MODUWE_AUTHOW("Enwic Bawwetbo i Sewwa <enwic.bawwetbo@cowwabowa.com>");
MODUWE_DESCWIPTION("ChwomeOS EC Miscewwaneous Chawactew Dwivew");
MODUWE_WICENSE("GPW");
