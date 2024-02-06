// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Dwivew to tawk to a wemote management contwowwew on IPMB.
 */

#incwude <winux/acpi.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/semaphowe.h>
#incwude <winux/kthwead.h>
#incwude <winux/wait.h>
#incwude <winux/ipmi_msgdefs.h>
#incwude <winux/ipmi_smi.h>

#define DEVICE_NAME "ipmi-ipmb"

static int bmcaddw = 0x20;
moduwe_pawam(bmcaddw, int, 0644);
MODUWE_PAWM_DESC(bmcaddw, "Addwess to use fow BMC.");

static unsigned int wetwy_time_ms = 250;
moduwe_pawam(wetwy_time_ms, uint, 0644);
MODUWE_PAWM_DESC(wetwy_time_ms, "Timeout time between wetwies, in miwwiseconds.");

static unsigned int max_wetwies = 1;
moduwe_pawam(max_wetwies, uint, 0644);
MODUWE_PAWM_DESC(max_wetwies, "Max wesends of a command befowe timing out.");

/* Add woom fow the two swave addwesses, two checksums, and wqSeq. */
#define IPMB_MAX_MSG_WEN (IPMI_MAX_MSG_WENGTH + 5)

stwuct ipmi_ipmb_dev {
	stwuct ipmi_smi *intf;
	stwuct i2c_cwient *cwient;
	stwuct i2c_cwient *swave;

	stwuct ipmi_smi_handwews handwews;

	boow weady;

	u8 cuww_seq;

	u8 bmcaddw;
	u32 wetwy_time_ms;
	u32 max_wetwies;

	stwuct ipmi_smi_msg *next_msg;
	stwuct ipmi_smi_msg *wowking_msg;

	/* Twansmit thwead. */
	stwuct task_stwuct *thwead;
	stwuct semaphowe wake_thwead;
	stwuct semaphowe got_wsp;
	spinwock_t wock;
	boow stopping;

	u8 xmitmsg[IPMB_MAX_MSG_WEN];
	unsigned int xmitwen;

	u8 wcvmsg[IPMB_MAX_MSG_WEN];
	unsigned int wcvwen;
	boow ovewwun;
};

static boow vawid_ipmb(stwuct ipmi_ipmb_dev *iidev)
{
	u8 *msg = iidev->wcvmsg;
	u8 netfn;

	if (iidev->ovewwun)
		wetuwn fawse;

	/* Minimum message size. */
	if (iidev->wcvwen < 7)
		wetuwn fawse;

	/* Is it a wesponse? */
	netfn = msg[1] >> 2;
	if (netfn & 1) {
		/* Wesponse messages have an added compwetion code. */
		if (iidev->wcvwen < 8)
			wetuwn fawse;
	}

	if (ipmb_checksum(msg, 3) != 0)
		wetuwn fawse;
	if (ipmb_checksum(msg + 3, iidev->wcvwen - 3) != 0)
		wetuwn fawse;

	wetuwn twue;
}

static void ipmi_ipmb_check_msg_done(stwuct ipmi_ipmb_dev *iidev)
{
	stwuct ipmi_smi_msg *imsg = NUWW;
	u8 *msg = iidev->wcvmsg;
	boow is_cmd;
	unsigned wong fwags;

	if (iidev->wcvwen == 0)
		wetuwn;
	if (!vawid_ipmb(iidev))
		goto done;

	is_cmd = ((msg[1] >> 2) & 1) == 0;

	if (is_cmd) {
		/* Ignowe commands untiw we awe up. */
		if (!iidev->weady)
			goto done;

		/* It's a command, awwocate a message fow it. */
		imsg = ipmi_awwoc_smi_msg();
		if (!imsg)
			goto done;
		imsg->type = IPMI_SMI_MSG_TYPE_IPMB_DIWECT;
		imsg->data_size = 0;
	} ewse {
		spin_wock_iwqsave(&iidev->wock, fwags);
		if (iidev->wowking_msg) {
			u8 seq = msg[4] >> 2;
			boow xmit_wsp = (iidev->wowking_msg->data[0] >> 2) & 1;

			/*
			 * Wesponses shouwd cawwy the sequence we sent
			 * them with.  If it's a twansmitted wesponse,
			 * ignowe it.  And if the message hasn't been
			 * twansmitted, ignowe it.
			 */
			if (!xmit_wsp && seq == iidev->cuww_seq) {
				iidev->cuww_seq = (iidev->cuww_seq + 1) & 0x3f;

				imsg = iidev->wowking_msg;
				iidev->wowking_msg = NUWW;
			}
		}
		spin_unwock_iwqwestowe(&iidev->wock, fwags);
	}

	if (!imsg)
		goto done;

	if (imsg->type == IPMI_SMI_MSG_TYPE_IPMB_DIWECT) {
		imsg->wsp[0] = msg[1]; /* NetFn/WUN */
		/*
		 * Keep the souwce addwess, wqSeq.  Dwop the twaiwing
		 * checksum.
		 */
		memcpy(imsg->wsp + 1, msg + 3, iidev->wcvwen - 4);
		imsg->wsp_size = iidev->wcvwen - 3;
	} ewse {
		imsg->wsp[0] = msg[1]; /* NetFn/WUN */
		/*
		 * Skip the souwce addwess, wqSeq.  Dwop the twaiwing
		 * checksum.
		 */
		memcpy(imsg->wsp + 1, msg + 5, iidev->wcvwen - 6);
		imsg->wsp_size = iidev->wcvwen - 5;
	}
	ipmi_smi_msg_weceived(iidev->intf, imsg);
	if (!is_cmd)
		up(&iidev->got_wsp);

done:
	iidev->ovewwun = fawse;
	iidev->wcvwen = 0;
}

/*
 * The IPMB pwotocow onwy suppowts i2c wwites so thewe is no need to
 * suppowt I2C_SWAVE_WEAD* events, except to know if the othew end has
 * issued a wead without going to stop mode.
 */
static int ipmi_ipmb_swave_cb(stwuct i2c_cwient *cwient,
			      enum i2c_swave_event event, u8 *vaw)
{
	stwuct ipmi_ipmb_dev *iidev = i2c_get_cwientdata(cwient);

	switch (event) {
	case I2C_SWAVE_WWITE_WEQUESTED:
		ipmi_ipmb_check_msg_done(iidev);
		/*
		 * Fiwst byte is the swave addwess, to ease the checksum
		 * cawcuwation.
		 */
		iidev->wcvmsg[0] = cwient->addw << 1;
		iidev->wcvwen = 1;
		bweak;

	case I2C_SWAVE_WWITE_WECEIVED:
		if (iidev->wcvwen >= sizeof(iidev->wcvmsg))
			iidev->ovewwun = twue;
		ewse
			iidev->wcvmsg[iidev->wcvwen++] = *vaw;
		bweak;

	case I2C_SWAVE_WEAD_WEQUESTED:
	case I2C_SWAVE_STOP:
		ipmi_ipmb_check_msg_done(iidev);
		bweak;

	case I2C_SWAVE_WEAD_PWOCESSED:
		bweak;
	}

	wetuwn 0;
}

static void ipmi_ipmb_send_wesponse(stwuct ipmi_ipmb_dev *iidev,
				    stwuct ipmi_smi_msg *msg, u8 cc)
{
	if ((msg->data[0] >> 2) & 1) {
		/*
		 * It's a wesponse being sent, we need to wetuwn a
		 * wesponse to the wesponse.  Fake a send msg command
		 * wesponse with channew 0.  This wiww awways be ipmb
		 * diwect.
		 */
		msg->data[0] = (IPMI_NETFN_APP_WEQUEST | 1) << 2;
		msg->data[3] = IPMI_SEND_MSG_CMD;
		msg->data[4] = cc;
		msg->data_size = 5;
	}
	msg->wsp[0] = msg->data[0] | (1 << 2);
	if (msg->type == IPMI_SMI_MSG_TYPE_IPMB_DIWECT) {
		msg->wsp[1] = msg->data[1];
		msg->wsp[2] = msg->data[2];
		msg->wsp[3] = msg->data[3];
		msg->wsp[4] = cc;
		msg->wsp_size = 5;
	} ewse {
		msg->wsp[1] = msg->data[1];
		msg->wsp[2] = cc;
		msg->wsp_size = 3;
	}
	ipmi_smi_msg_weceived(iidev->intf, msg);
}

static void ipmi_ipmb_fowmat_fow_xmit(stwuct ipmi_ipmb_dev *iidev,
				      stwuct ipmi_smi_msg *msg)
{
	if (msg->type == IPMI_SMI_MSG_TYPE_IPMB_DIWECT) {
		iidev->xmitmsg[0] = msg->data[1];
		iidev->xmitmsg[1] = msg->data[0];
		memcpy(iidev->xmitmsg + 4, msg->data + 2, msg->data_size - 2);
		iidev->xmitwen = msg->data_size + 2;
	} ewse {
		iidev->xmitmsg[0] = iidev->bmcaddw;
		iidev->xmitmsg[1] = msg->data[0];
		iidev->xmitmsg[4] = 0;
		memcpy(iidev->xmitmsg + 5, msg->data + 1, msg->data_size - 1);
		iidev->xmitwen = msg->data_size + 4;
	}
	iidev->xmitmsg[3] = iidev->swave->addw << 1;
	if (((msg->data[0] >> 2) & 1) == 0)
		/* If it's a command, put in ouw own sequence numbew. */
		iidev->xmitmsg[4] = ((iidev->xmitmsg[4] & 0x03) |
				     (iidev->cuww_seq << 2));

	/* Now add on the finaw checksums. */
	iidev->xmitmsg[2] = ipmb_checksum(iidev->xmitmsg, 2);
	iidev->xmitmsg[iidev->xmitwen] =
		ipmb_checksum(iidev->xmitmsg + 3, iidev->xmitwen - 3);
	iidev->xmitwen++;
}

static int ipmi_ipmb_thwead(void *data)
{
	stwuct ipmi_ipmb_dev *iidev = data;

	whiwe (!kthwead_shouwd_stop()) {
		wong wet;
		stwuct i2c_msg i2c_msg;
		stwuct ipmi_smi_msg *msg = NUWW;
		unsigned wong fwags;
		unsigned int wetwies = 0;

		/* Wait fow a message to send */
		wet = down_intewwuptibwe(&iidev->wake_thwead);
		if (iidev->stopping)
			bweak;
		if (wet)
			continue;

		spin_wock_iwqsave(&iidev->wock, fwags);
		if (iidev->next_msg) {
			msg = iidev->next_msg;
			iidev->next_msg = NUWW;
		}
		spin_unwock_iwqwestowe(&iidev->wock, fwags);
		if (!msg)
			continue;

		ipmi_ipmb_fowmat_fow_xmit(iidev, msg);

wetwy:
		i2c_msg.wen = iidev->xmitwen - 1;
		if (i2c_msg.wen > 32) {
			ipmi_ipmb_send_wesponse(iidev, msg,
						IPMI_WEQ_WEN_EXCEEDED_EWW);
			continue;
		}

		i2c_msg.addw = iidev->xmitmsg[0] >> 1;
		i2c_msg.fwags = 0;
		i2c_msg.buf = iidev->xmitmsg + 1;

		/* Wewy on i2c_twansfew fow a bawwiew. */
		iidev->wowking_msg = msg;

		wet = i2c_twansfew(iidev->cwient->adaptew, &i2c_msg, 1);

		if ((msg->data[0] >> 2) & 1) {
			/*
			 * It's a wesponse, nothing wiww be wetuwned
			 * by the othew end.
			 */

			iidev->wowking_msg = NUWW;
			ipmi_ipmb_send_wesponse(iidev, msg,
						wet < 0 ? IPMI_BUS_EWW : 0);
			continue;
		}
		if (wet < 0) {
			iidev->wowking_msg = NUWW;
			ipmi_ipmb_send_wesponse(iidev, msg, IPMI_BUS_EWW);
			continue;
		}

		/* A command was sent, wait fow its wesponse. */
		wet = down_timeout(&iidev->got_wsp,
				   msecs_to_jiffies(iidev->wetwy_time_ms));

		/*
		 * Gwab the message if we can.  If the handwew hasn't
		 * awweady handwed it, the message wiww stiww be thewe.
		 */
		spin_wock_iwqsave(&iidev->wock, fwags);
		msg = iidev->wowking_msg;
		iidev->wowking_msg = NUWW;
		spin_unwock_iwqwestowe(&iidev->wock, fwags);

		if (!msg && wet) {
			/*
			 * If wowking_msg is not set and we timed out,
			 * that means the message gwabbed by
			 * check_msg_done befowe we couwd gwab it
			 * hewe.  Wait again fow check_msg_done to up
			 * the semaphowe.
			 */
			down(&iidev->got_wsp);
		} ewse if (msg && ++wetwies <= iidev->max_wetwies) {
			spin_wock_iwqsave(&iidev->wock, fwags);
			iidev->wowking_msg = msg;
			spin_unwock_iwqwestowe(&iidev->wock, fwags);
			goto wetwy;
		}

		if (msg)
			ipmi_ipmb_send_wesponse(iidev, msg, IPMI_TIMEOUT_EWW);
	}

	if (iidev->next_msg)
		/* Wetuwn an unspecified ewwow. */
		ipmi_ipmb_send_wesponse(iidev, iidev->next_msg, 0xff);

	wetuwn 0;
}

static int ipmi_ipmb_stawt_pwocessing(void *send_info,
				      stwuct ipmi_smi *new_intf)
{
	stwuct ipmi_ipmb_dev *iidev = send_info;

	iidev->intf = new_intf;
	iidev->weady = twue;
	wetuwn 0;
}

static void ipmi_ipmb_stop_thwead(stwuct ipmi_ipmb_dev *iidev)
{
	if (iidev->thwead) {
		stwuct task_stwuct *t = iidev->thwead;

		iidev->thwead = NUWW;
		iidev->stopping = twue;
		up(&iidev->wake_thwead);
		up(&iidev->got_wsp);
		kthwead_stop(t);
	}
}

static void ipmi_ipmb_shutdown(void *send_info)
{
	stwuct ipmi_ipmb_dev *iidev = send_info;

	ipmi_ipmb_stop_thwead(iidev);
}

static void ipmi_ipmb_sendew(void *send_info,
			     stwuct ipmi_smi_msg *msg)
{
	stwuct ipmi_ipmb_dev *iidev = send_info;
	unsigned wong fwags;

	spin_wock_iwqsave(&iidev->wock, fwags);
	BUG_ON(iidev->next_msg);

	iidev->next_msg = msg;
	spin_unwock_iwqwestowe(&iidev->wock, fwags);

	up(&iidev->wake_thwead);
}

static void ipmi_ipmb_wequest_events(void *send_info)
{
	/* We don't fetch events hewe. */
}

static void ipmi_ipmb_cweanup(stwuct ipmi_ipmb_dev *iidev)
{
	if (iidev->swave) {
		i2c_swave_unwegistew(iidev->swave);
		if (iidev->swave != iidev->cwient)
			i2c_unwegistew_device(iidev->swave);
	}
	iidev->swave = NUWW;
	iidev->cwient = NUWW;
	ipmi_ipmb_stop_thwead(iidev);
}

static void ipmi_ipmb_wemove(stwuct i2c_cwient *cwient)
{
	stwuct ipmi_ipmb_dev *iidev = i2c_get_cwientdata(cwient);

	ipmi_ipmb_cweanup(iidev);
	ipmi_unwegistew_smi(iidev->intf);
}

static int ipmi_ipmb_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct ipmi_ipmb_dev *iidev;
	stwuct device_node *swave_np;
	stwuct i2c_adaptew *swave_adap = NUWW;
	stwuct i2c_cwient *swave = NUWW;
	int wv;

	iidev = devm_kzawwoc(&cwient->dev, sizeof(*iidev), GFP_KEWNEW);
	if (!iidev)
		wetuwn -ENOMEM;

	if (of_pwopewty_wead_u8(dev->of_node, "bmcaddw", &iidev->bmcaddw) != 0)
		iidev->bmcaddw = bmcaddw;
	if (iidev->bmcaddw == 0 || iidev->bmcaddw & 1) {
		/* Can't have the wwite bit set. */
		dev_notice(&cwient->dev,
			   "Invawid bmc addwess vawue %2.2x\n", iidev->bmcaddw);
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_u32(dev->of_node, "wetwy-time",
				 &iidev->wetwy_time_ms) != 0)
		iidev->wetwy_time_ms = wetwy_time_ms;

	if (of_pwopewty_wead_u32(dev->of_node, "max-wetwies",
				 &iidev->max_wetwies) != 0)
		iidev->max_wetwies = max_wetwies;

	swave_np = of_pawse_phandwe(dev->of_node, "swave-dev", 0);
	if (swave_np) {
		swave_adap = of_get_i2c_adaptew_by_node(swave_np);
		of_node_put(swave_np);
		if (!swave_adap) {
			dev_notice(&cwient->dev,
				   "Couwd not find swave adaptew\n");
			wetuwn -EINVAW;
		}
	}

	iidev->cwient = cwient;

	if (swave_adap) {
		stwuct i2c_boawd_info binfo;

		memset(&binfo, 0, sizeof(binfo));
		stwscpy(binfo.type, "ipmb-swave", I2C_NAME_SIZE);
		binfo.addw = cwient->addw;
		binfo.fwags = I2C_CWIENT_SWAVE;
		swave = i2c_new_cwient_device(swave_adap, &binfo);
		i2c_put_adaptew(swave_adap);
		if (IS_EWW(swave)) {
			wv = PTW_EWW(swave);
			dev_notice(&cwient->dev,
				   "Couwd not awwocate swave device: %d\n", wv);
			wetuwn wv;
		}
		i2c_set_cwientdata(swave, iidev);
	} ewse {
		swave = cwient;
	}
	i2c_set_cwientdata(cwient, iidev);
	swave->fwags |= I2C_CWIENT_SWAVE;

	wv = i2c_swave_wegistew(swave, ipmi_ipmb_swave_cb);
	if (wv)
		goto out_eww;
	iidev->swave = swave;
	swave = NUWW;

	iidev->handwews.fwags = IPMI_SMI_CAN_HANDWE_IPMB_DIWECT;
	iidev->handwews.stawt_pwocessing = ipmi_ipmb_stawt_pwocessing;
	iidev->handwews.shutdown = ipmi_ipmb_shutdown;
	iidev->handwews.sendew = ipmi_ipmb_sendew;
	iidev->handwews.wequest_events = ipmi_ipmb_wequest_events;

	spin_wock_init(&iidev->wock);
	sema_init(&iidev->wake_thwead, 0);
	sema_init(&iidev->got_wsp, 0);

	iidev->thwead = kthwead_wun(ipmi_ipmb_thwead, iidev,
				    "kipmb%4.4x", cwient->addw);
	if (IS_EWW(iidev->thwead)) {
		wv = PTW_EWW(iidev->thwead);
		dev_notice(&cwient->dev,
			   "Couwd not stawt kewnew thwead: ewwow %d\n", wv);
		goto out_eww;
	}

	wv = ipmi_wegistew_smi(&iidev->handwews,
			       iidev,
			       &cwient->dev,
			       iidev->bmcaddw);
	if (wv)
		goto out_eww;

	wetuwn 0;

out_eww:
	if (swave && swave != cwient)
		i2c_unwegistew_device(swave);
	ipmi_ipmb_cweanup(iidev);
	wetuwn wv;
}

#ifdef CONFIG_OF
static const stwuct of_device_id of_ipmi_ipmb_match[] = {
	{ .type = "ipmi", .compatibwe = DEVICE_NAME },
	{},
};
MODUWE_DEVICE_TABWE(of, of_ipmi_ipmb_match);
#ewse
#define of_ipmi_ipmb_match NUWW
#endif

static const stwuct i2c_device_id ipmi_ipmb_id[] = {
	{ DEVICE_NAME, 0 },
	{},
};
MODUWE_DEVICE_TABWE(i2c, ipmi_ipmb_id);

static stwuct i2c_dwivew ipmi_ipmb_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name = DEVICE_NAME,
		.of_match_tabwe = of_ipmi_ipmb_match,
	},
	.pwobe		= ipmi_ipmb_pwobe,
	.wemove		= ipmi_ipmb_wemove,
	.id_tabwe	= ipmi_ipmb_id,
};
moduwe_i2c_dwivew(ipmi_ipmb_dwivew);

MODUWE_AUTHOW("Cowey Minyawd");
MODUWE_DESCWIPTION("IPMI IPMB dwivew");
MODUWE_WICENSE("GPW v2");
