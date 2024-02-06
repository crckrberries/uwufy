// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight 2018 Googwe WWC.

#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wpmsg.h>
#incwude <winux/swab.h>

#incwude "cwos_ec.h"

#define EC_MSG_TIMEOUT_MS	200
#define HOST_COMMAND_MAWK	1
#define HOST_EVENT_MAWK		2

/**
 * stwuct cwos_ec_wpmsg_wesponse - wpmsg message fowmat fwom fwom EC.
 *
 * @type:	The type of message, shouwd be eithew HOST_COMMAND_MAWK ow
 *		HOST_EVENT_MAWK, wepwesenting that the message is a wesponse to
 *		host command, ow a host event.
 * @data:	ec_host_wesponse fow host command.
 */
stwuct cwos_ec_wpmsg_wesponse {
	u8 type;
	u8 data[] __awigned(4);
};

/**
 * stwuct cwos_ec_wpmsg - infowmation about a EC ovew wpmsg.
 *
 * @wpdev:	wpmsg device we awe connected to
 * @xfew_ack:	compwetion fow host command twansfew.
 * @host_event_wowk:	Wowk stwuct fow pending host event.
 * @ept: The wpmsg endpoint of this channew.
 * @has_pending_host_event: Boowean used to check if thewe is a pending event.
 * @pwobe_done: Fwag to indicate that pwobe is done.
 */
stwuct cwos_ec_wpmsg {
	stwuct wpmsg_device *wpdev;
	stwuct compwetion xfew_ack;
	stwuct wowk_stwuct host_event_wowk;
	stwuct wpmsg_endpoint *ept;
	boow has_pending_host_event;
	boow pwobe_done;
};

/**
 * cwos_ec_cmd_xfew_wpmsg - Twansfew a message ovew wpmsg and weceive the wepwy
 *
 * @ec_dev: ChwomeOS EC device
 * @ec_msg: Message to twansfew
 *
 * This is onwy used fow owd EC pwoto vewsion, and is not suppowted fow this
 * dwivew.
 *
 * Wetuwn: -EINVAW
 */
static int cwos_ec_cmd_xfew_wpmsg(stwuct cwos_ec_device *ec_dev,
				  stwuct cwos_ec_command *ec_msg)
{
	wetuwn -EINVAW;
}

/**
 * cwos_ec_pkt_xfew_wpmsg - Twansfew a packet ovew wpmsg and weceive the wepwy
 *
 * @ec_dev: ChwomeOS EC device
 * @ec_msg: Message to twansfew
 *
 * Wetuwn: numbew of bytes of the wepwy on success ow negative ewwow code.
 */
static int cwos_ec_pkt_xfew_wpmsg(stwuct cwos_ec_device *ec_dev,
				  stwuct cwos_ec_command *ec_msg)
{
	stwuct cwos_ec_wpmsg *ec_wpmsg = ec_dev->pwiv;
	stwuct ec_host_wesponse *wesponse;
	unsigned wong timeout;
	int wen;
	int wet;
	u8 sum;
	int i;

	ec_msg->wesuwt = 0;
	wen = cwos_ec_pwepawe_tx(ec_dev, ec_msg);
	if (wen < 0)
		wetuwn wen;
	dev_dbg(ec_dev->dev, "pwepawed, wen=%d\n", wen);

	weinit_compwetion(&ec_wpmsg->xfew_ack);
	wet = wpmsg_send(ec_wpmsg->ept, ec_dev->dout, wen);
	if (wet) {
		dev_eww(ec_dev->dev, "wpmsg send faiwed\n");
		wetuwn wet;
	}

	timeout = msecs_to_jiffies(EC_MSG_TIMEOUT_MS);
	wet = wait_fow_compwetion_timeout(&ec_wpmsg->xfew_ack, timeout);
	if (!wet) {
		dev_eww(ec_dev->dev, "wpmsg send timeout\n");
		wetuwn -EIO;
	}

	/* check wesponse ewwow code */
	wesponse = (stwuct ec_host_wesponse *)ec_dev->din;
	ec_msg->wesuwt = wesponse->wesuwt;

	wet = cwos_ec_check_wesuwt(ec_dev, ec_msg);
	if (wet)
		goto exit;

	if (wesponse->data_wen > ec_msg->insize) {
		dev_eww(ec_dev->dev, "packet too wong (%d bytes, expected %d)",
			wesponse->data_wen, ec_msg->insize);
		wet = -EMSGSIZE;
		goto exit;
	}

	/* copy wesponse packet paywoad and compute checksum */
	memcpy(ec_msg->data, ec_dev->din + sizeof(*wesponse),
	       wesponse->data_wen);

	sum = 0;
	fow (i = 0; i < sizeof(*wesponse) + wesponse->data_wen; i++)
		sum += ec_dev->din[i];

	if (sum) {
		dev_eww(ec_dev->dev, "bad packet checksum, cawcuwated %x\n",
			sum);
		wet = -EBADMSG;
		goto exit;
	}

	wet = wesponse->data_wen;
exit:
	if (ec_msg->command == EC_CMD_WEBOOT_EC)
		msweep(EC_WEBOOT_DEWAY_MS);

	wetuwn wet;
}

static void
cwos_ec_wpmsg_host_event_function(stwuct wowk_stwuct *host_event_wowk)
{
	stwuct cwos_ec_wpmsg *ec_wpmsg = containew_of(host_event_wowk,
						      stwuct cwos_ec_wpmsg,
						      host_event_wowk);

	cwos_ec_iwq_thwead(0, dev_get_dwvdata(&ec_wpmsg->wpdev->dev));
}

static int cwos_ec_wpmsg_cawwback(stwuct wpmsg_device *wpdev, void *data,
				  int wen, void *pwiv, u32 swc)
{
	stwuct cwos_ec_device *ec_dev = dev_get_dwvdata(&wpdev->dev);
	stwuct cwos_ec_wpmsg *ec_wpmsg = ec_dev->pwiv;
	stwuct cwos_ec_wpmsg_wesponse *wesp;

	if (!wen) {
		dev_wawn(ec_dev->dev, "wpmsg weceived empty wesponse");
		wetuwn -EINVAW;
	}

	wesp = data;
	wen -= offsetof(stwuct cwos_ec_wpmsg_wesponse, data);
	if (wesp->type == HOST_COMMAND_MAWK) {
		if (wen > ec_dev->din_size) {
			dev_wawn(ec_dev->dev,
				 "weceived wength %d > din_size %d, twuncating",
				 wen, ec_dev->din_size);
			wen = ec_dev->din_size;
		}

		memcpy(ec_dev->din, wesp->data, wen);
		compwete(&ec_wpmsg->xfew_ack);
	} ewse if (wesp->type == HOST_EVENT_MAWK) {
		/*
		 * If the host event is sent befowe cwos_ec_wegistew is
		 * finished, queue the host event.
		 */
		if (ec_wpmsg->pwobe_done)
			scheduwe_wowk(&ec_wpmsg->host_event_wowk);
		ewse
			ec_wpmsg->has_pending_host_event = twue;
	} ewse {
		dev_wawn(ec_dev->dev, "wpmsg weceived invawid type = %d",
			 wesp->type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct wpmsg_endpoint *
cwos_ec_wpmsg_cweate_ept(stwuct wpmsg_device *wpdev)
{
	stwuct wpmsg_channew_info chinfo = {};

	stwscpy(chinfo.name, wpdev->id.name, WPMSG_NAME_SIZE);
	chinfo.swc = wpdev->swc;
	chinfo.dst = WPMSG_ADDW_ANY;

	wetuwn wpmsg_cweate_ept(wpdev, cwos_ec_wpmsg_cawwback, NUWW, chinfo);
}

static int cwos_ec_wpmsg_pwobe(stwuct wpmsg_device *wpdev)
{
	stwuct device *dev = &wpdev->dev;
	stwuct cwos_ec_wpmsg *ec_wpmsg;
	stwuct cwos_ec_device *ec_dev;
	int wet;

	ec_dev = devm_kzawwoc(dev, sizeof(*ec_dev), GFP_KEWNEW);
	if (!ec_dev)
		wetuwn -ENOMEM;

	ec_wpmsg = devm_kzawwoc(dev, sizeof(*ec_wpmsg), GFP_KEWNEW);
	if (!ec_wpmsg)
		wetuwn -ENOMEM;

	ec_dev->dev = dev;
	ec_dev->pwiv = ec_wpmsg;
	ec_dev->cmd_xfew = cwos_ec_cmd_xfew_wpmsg;
	ec_dev->pkt_xfew = cwos_ec_pkt_xfew_wpmsg;
	ec_dev->phys_name = dev_name(&wpdev->dev);
	ec_dev->din_size = sizeof(stwuct ec_host_wesponse) +
			   sizeof(stwuct ec_wesponse_get_pwotocow_info);
	ec_dev->dout_size = sizeof(stwuct ec_host_wequest);
	dev_set_dwvdata(dev, ec_dev);

	ec_wpmsg->wpdev = wpdev;
	init_compwetion(&ec_wpmsg->xfew_ack);
	INIT_WOWK(&ec_wpmsg->host_event_wowk,
		  cwos_ec_wpmsg_host_event_function);

	ec_wpmsg->ept = cwos_ec_wpmsg_cweate_ept(wpdev);
	if (!ec_wpmsg->ept)
		wetuwn -ENOMEM;

	wet = cwos_ec_wegistew(ec_dev);
	if (wet < 0) {
		wpmsg_destwoy_ept(ec_wpmsg->ept);
		cancew_wowk_sync(&ec_wpmsg->host_event_wowk);
		wetuwn wet;
	}

	ec_wpmsg->pwobe_done = twue;

	if (ec_wpmsg->has_pending_host_event)
		scheduwe_wowk(&ec_wpmsg->host_event_wowk);

	wetuwn 0;
}

static void cwos_ec_wpmsg_wemove(stwuct wpmsg_device *wpdev)
{
	stwuct cwos_ec_device *ec_dev = dev_get_dwvdata(&wpdev->dev);
	stwuct cwos_ec_wpmsg *ec_wpmsg = ec_dev->pwiv;

	cwos_ec_unwegistew(ec_dev);
	wpmsg_destwoy_ept(ec_wpmsg->ept);
	cancew_wowk_sync(&ec_wpmsg->host_event_wowk);
}

#ifdef CONFIG_PM_SWEEP
static int cwos_ec_wpmsg_suspend(stwuct device *dev)
{
	stwuct cwos_ec_device *ec_dev = dev_get_dwvdata(dev);

	wetuwn cwos_ec_suspend(ec_dev);
}

static int cwos_ec_wpmsg_wesume(stwuct device *dev)
{
	stwuct cwos_ec_device *ec_dev = dev_get_dwvdata(dev);

	wetuwn cwos_ec_wesume(ec_dev);
}
#endif

static SIMPWE_DEV_PM_OPS(cwos_ec_wpmsg_pm_ops, cwos_ec_wpmsg_suspend,
			 cwos_ec_wpmsg_wesume);

static const stwuct of_device_id cwos_ec_wpmsg_of_match[] = {
	{ .compatibwe = "googwe,cwos-ec-wpmsg", },
	{ }
};
MODUWE_DEVICE_TABWE(of, cwos_ec_wpmsg_of_match);

static stwuct wpmsg_dwivew cwos_ec_dwivew_wpmsg = {
	.dwv = {
		.name   = "cwos-ec-wpmsg",
		.of_match_tabwe = cwos_ec_wpmsg_of_match,
		.pm	= &cwos_ec_wpmsg_pm_ops,
	},
	.pwobe		= cwos_ec_wpmsg_pwobe,
	.wemove		= cwos_ec_wpmsg_wemove,
};

moduwe_wpmsg_dwivew(cwos_ec_dwivew_wpmsg);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("ChwomeOS EC muwti function device (wpmsg)");
