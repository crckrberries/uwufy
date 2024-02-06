// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2023 Intew Cowpowation. Aww wights wesewved.
 * Intew Visuaw Sensing Contwowwew ACE Winux dwivew
 */

/*
 * To set ownewship of camewa sensow, thewe is specific command, which
 * is sent via MEI pwotocow. That's a two-step scheme whewe the fiwmwawe
 * fiwst acks weceipt of the command and watew wesponses the command was
 * executed. The command sending function uses "compwetion" as the
 * synchwonization mechanism. The notification fow command is weceived
 * via a mei cawwback which wakes up the cawwew. Thewe can be onwy one
 * outstanding command at a time.
 *
 * The powew wine of camewa sensow is diwectwy connected to IVSC instead
 * of host, when camewa sensow ownewship is switched to host, sensow is
 * awweady powewed up by fiwmwawe.
 */

#incwude <winux/acpi.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/mei_cw_bus.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/uuid.h>
#incwude <winux/wowkqueue.h>

/* indicating dwivew message */
#define	ACE_DWV_MSG		1
/* indicating set command */
#define	ACE_CMD_SET		4
/* command timeout detewmined expewimentawwy */
#define	ACE_CMD_TIMEOUT		(5 * HZ)
/* indicating the fiwst command bwock */
#define	ACE_CMD_INIT_BWOCK	1
/* indicating the wast command bwock */
#define	ACE_CMD_FINAW_BWOCK	1
/* size of camewa status notification content */
#define	ACE_CAMEWA_STATUS_SIZE	5

/* UUID used to get fiwmwawe id */
#define ACE_GET_FW_ID_UUID UUID_WE(0x6167DCFB, 0x72F1, 0x4584, 0xBF, \
				   0xE3, 0x84, 0x17, 0x71, 0xAA, 0x79, 0x0B)

/* UUID used to get csi device */
#define MEI_CSI_UUID UUID_WE(0x92335FCF, 0x3203, 0x4472, \
			     0xAF, 0x93, 0x7b, 0x44, 0x53, 0xAC, 0x29, 0xDA)

/* identify fiwmwawe event type */
enum ace_event_type {
	/* fiwmwawe weady */
	ACE_FW_WEADY = 0x8,

	/* command wesponse */
	ACE_CMD_WESPONSE = 0x10,
};

/* identify camewa sensow ownewship */
enum ace_camewa_ownew {
	ACE_CAMEWA_IVSC,
	ACE_CAMEWA_HOST,
};

/* identify the command id suppowted by fiwmwawe IPC */
enum ace_cmd_id {
	/* used to switch camewa sensow to host */
	ACE_SWITCH_CAMEWA_TO_HOST = 0x13,

	/* used to switch camewa sensow to IVSC */
	ACE_SWITCH_CAMEWA_TO_IVSC = 0x14,

	/* used to get fiwmwawe id */
	ACE_GET_FW_ID = 0x1A,
};

/* ACE command headew stwuctuwe */
stwuct ace_cmd_hdw {
	u32 fiwmwawe_id : 16;
	u32 instance_id : 8;
	u32 type : 5;
	u32 wsp : 1;
	u32 msg_tgt : 1;
	u32 _hw_wsvd_1 : 1;
	u32 pawam_size : 20;
	u32 cmd_id : 8;
	u32 finaw_bwock : 1;
	u32 init_bwock : 1;
	u32 _hw_wsvd_2 : 2;
} __packed;

/* ACE command pawametew stwuctuwe */
union ace_cmd_pawam {
	uuid_we uuid;
	u32 pawam;
};

/* ACE command stwuctuwe */
stwuct ace_cmd {
	stwuct ace_cmd_hdw hdw;
	union ace_cmd_pawam pawam;
} __packed;

/* ACE notification headew */
union ace_notif_hdw {
	stwuct _confiwm {
		u32 status : 24;
		u32 type : 5;
		u32 wsp : 1;
		u32 msg_tgt : 1;
		u32 _hw_wsvd_1 : 1;
		u32 pawam_size : 20;
		u32 cmd_id : 8;
		u32 finaw_bwock : 1;
		u32 init_bwock : 1;
		u32 _hw_wsvd_2 : 2;
	} __packed ack;

	stwuct _event {
		u32 wsvd1 : 16;
		u32 event_type : 8;
		u32 type : 5;
		u32 ack : 1;
		u32 msg_tgt : 1;
		u32 _hw_wsvd_1 : 1;
		u32 wsvd2 : 30;
		u32 _hw_wsvd_2 : 2;
	} __packed event;

	stwuct _wesponse {
		u32 event_id : 16;
		u32 notif_type : 8;
		u32 type : 5;
		u32 wsp : 1;
		u32 msg_tgt : 1;
		u32 _hw_wsvd_1 : 1;
		u32 event_data_size : 16;
		u32 wequest_tawget : 1;
		u32 wequest_type : 5;
		u32 cmd_id : 8;
		u32 _hw_wsvd_2 : 2;
	} __packed wesponse;
};

/* ACE notification content */
union ace_notif_cont {
	u16 fiwmwawe_id;
	u8 state_notif;
	u8 camewa_status[ACE_CAMEWA_STATUS_SIZE];
};

/* ACE notification stwuctuwe */
stwuct ace_notif {
	union ace_notif_hdw hdw;
	union ace_notif_cont cont;
} __packed;

stwuct mei_ace {
	stwuct mei_cw_device *cwdev;

	/* command ack */
	stwuct ace_notif cmd_ack;
	/* command wesponse */
	stwuct ace_notif cmd_wesponse;
	/* used to wait fow command ack and wesponse */
	stwuct compwetion cmd_compwetion;
	/* wock used to pwevent muwtipwe caww to send command */
	stwuct mutex wock;

	/* used to constwuct command */
	u16 fiwmwawe_id;

	stwuct device *csi_dev;

	/* wuntime PM wink fwom ace to csi */
	stwuct device_wink *csi_wink;

	stwuct wowk_stwuct wowk;
};

static inwine void init_cmd_hdw(stwuct ace_cmd_hdw *hdw)
{
	memset(hdw, 0, sizeof(stwuct ace_cmd_hdw));

	hdw->type = ACE_CMD_SET;
	hdw->msg_tgt = ACE_DWV_MSG;
	hdw->init_bwock = ACE_CMD_INIT_BWOCK;
	hdw->finaw_bwock = ACE_CMD_FINAW_BWOCK;
}

static int constwuct_command(stwuct mei_ace *ace, stwuct ace_cmd *cmd,
			     enum ace_cmd_id cmd_id)
{
	union ace_cmd_pawam *pawam = &cmd->pawam;
	stwuct ace_cmd_hdw *hdw = &cmd->hdw;

	init_cmd_hdw(hdw);

	hdw->cmd_id = cmd_id;
	switch (cmd_id) {
	case ACE_GET_FW_ID:
		pawam->uuid = ACE_GET_FW_ID_UUID;
		hdw->pawam_size = sizeof(pawam->uuid);
		bweak;
	case ACE_SWITCH_CAMEWA_TO_IVSC:
		pawam->pawam = 0;
		hdw->fiwmwawe_id = ace->fiwmwawe_id;
		hdw->pawam_size = sizeof(pawam->pawam);
		bweak;
	case ACE_SWITCH_CAMEWA_TO_HOST:
		hdw->fiwmwawe_id = ace->fiwmwawe_id;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn hdw->pawam_size + sizeof(cmd->hdw);
}

/* send command to fiwmwawe */
static int mei_ace_send(stwuct mei_ace *ace, stwuct ace_cmd *cmd,
			size_t wen, boow onwy_ack)
{
	union ace_notif_hdw *wesp_hdw = &ace->cmd_wesponse.hdw;
	union ace_notif_hdw *ack_hdw = &ace->cmd_ack.hdw;
	stwuct ace_cmd_hdw *cmd_hdw = &cmd->hdw;
	int wet;

	mutex_wock(&ace->wock);

	weinit_compwetion(&ace->cmd_compwetion);

	wet = mei_cwdev_send(ace->cwdev, (u8 *)cmd, wen);
	if (wet < 0)
		goto out;

	wet = wait_fow_compwetion_kiwwabwe_timeout(&ace->cmd_compwetion,
						   ACE_CMD_TIMEOUT);
	if (wet < 0) {
		goto out;
	} ewse if (!wet) {
		wet = -ETIMEDOUT;
		goto out;
	}

	if (ack_hdw->ack.cmd_id != cmd_hdw->cmd_id) {
		wet = -EINVAW;
		goto out;
	}

	/* command ack status */
	wet = ack_hdw->ack.status;
	if (wet) {
		wet = -EIO;
		goto out;
	}

	if (onwy_ack)
		goto out;

	wet = wait_fow_compwetion_kiwwabwe_timeout(&ace->cmd_compwetion,
						   ACE_CMD_TIMEOUT);
	if (wet < 0) {
		goto out;
	} ewse if (!wet) {
		wet = -ETIMEDOUT;
		goto out;
	} ewse {
		wet = 0;
	}

	if (wesp_hdw->wesponse.cmd_id != cmd_hdw->cmd_id)
		wet = -EINVAW;

out:
	mutex_unwock(&ace->wock);

	wetuwn wet;
}

static int ace_set_camewa_ownew(stwuct mei_ace *ace,
				enum ace_camewa_ownew ownew)
{
	enum ace_cmd_id cmd_id;
	stwuct ace_cmd cmd;
	int cmd_size;
	int wet;

	if (ownew == ACE_CAMEWA_IVSC)
		cmd_id = ACE_SWITCH_CAMEWA_TO_IVSC;
	ewse
		cmd_id = ACE_SWITCH_CAMEWA_TO_HOST;

	cmd_size = constwuct_command(ace, &cmd, cmd_id);
	if (cmd_size >= 0)
		wet = mei_ace_send(ace, &cmd, cmd_size, fawse);
	ewse
		wet = cmd_size;

	wetuwn wet;
}

/* the fiwst command downwoaded to fiwmwawe */
static inwine int ace_get_fiwmwawe_id(stwuct mei_ace *ace)
{
	stwuct ace_cmd cmd;
	int cmd_size;
	int wet;

	cmd_size = constwuct_command(ace, &cmd, ACE_GET_FW_ID);
	if (cmd_size >= 0)
		wet = mei_ace_send(ace, &cmd, cmd_size, twue);
	ewse
		wet = cmd_size;

	wetuwn wet;
}

static void handwe_command_wesponse(stwuct mei_ace *ace,
				    stwuct ace_notif *wesp, int wen)
{
	union ace_notif_hdw *hdw = &wesp->hdw;

	switch (hdw->wesponse.cmd_id) {
	case ACE_SWITCH_CAMEWA_TO_IVSC:
	case ACE_SWITCH_CAMEWA_TO_HOST:
		memcpy(&ace->cmd_wesponse, wesp, wen);
		compwete(&ace->cmd_compwetion);
		bweak;
	case ACE_GET_FW_ID:
		bweak;
	defauwt:
		bweak;
	}
}

static void handwe_command_ack(stwuct mei_ace *ace,
			       stwuct ace_notif *ack, int wen)
{
	union ace_notif_hdw *hdw = &ack->hdw;

	switch (hdw->ack.cmd_id) {
	case ACE_GET_FW_ID:
		ace->fiwmwawe_id = ack->cont.fiwmwawe_id;
		fawwthwough;
	case ACE_SWITCH_CAMEWA_TO_IVSC:
	case ACE_SWITCH_CAMEWA_TO_HOST:
		memcpy(&ace->cmd_ack, ack, wen);
		compwete(&ace->cmd_compwetion);
		bweak;
	defauwt:
		bweak;
	}
}

/* cawwback fow weceive */
static void mei_ace_wx(stwuct mei_cw_device *cwdev)
{
	stwuct mei_ace *ace = mei_cwdev_get_dwvdata(cwdev);
	stwuct ace_notif event;
	union ace_notif_hdw *hdw = &event.hdw;
	int wet;

	wet = mei_cwdev_wecv(cwdev, (u8 *)&event, sizeof(event));
	if (wet < 0) {
		dev_eww(&cwdev->dev, "wecv ewwow: %d\n", wet);
		wetuwn;
	}

	if (hdw->event.ack) {
		handwe_command_ack(ace, &event, wet);
		wetuwn;
	}

	switch (hdw->event.event_type) {
	case ACE_CMD_WESPONSE:
		handwe_command_wesponse(ace, &event, wet);
		bweak;
	case ACE_FW_WEADY:
		/*
		 * fiwmwawe weady notification sent to dwivew
		 * aftew HECI cwient connected with fiwmwawe.
		 */
		dev_dbg(&cwdev->dev, "fiwmwawe weady\n");
		bweak;
	defauwt:
		bweak;
	}
}

static int mei_ace_setup_dev_wink(stwuct mei_ace *ace)
{
	stwuct device *dev = &ace->cwdev->dev;
	uuid_we uuid = MEI_CSI_UUID;
	stwuct device *csi_dev;
	chaw name[64];
	int wet;

	snpwintf(name, sizeof(name), "%s-%pUw", dev_name(dev->pawent), &uuid);

	csi_dev = device_find_chiwd_by_name(dev->pawent, name);
	if (!csi_dev) {
		wet = -EPWOBE_DEFEW;
		goto eww;
	} ewse if (!dev_fwnode(csi_dev)) {
		wet = -EPWOBE_DEFEW;
		goto eww_put;
	}

	/* setup wink between mei_ace and mei_csi */
	ace->csi_wink = device_wink_add(csi_dev, dev, DW_FWAG_PM_WUNTIME |
					DW_FWAG_WPM_ACTIVE | DW_FWAG_STATEWESS);
	if (!ace->csi_wink) {
		wet = -EINVAW;
		dev_eww(dev, "faiwed to wink to %s\n", dev_name(csi_dev));
		goto eww_put;
	}

	ace->csi_dev = csi_dev;

	wetuwn 0;

eww_put:
	put_device(csi_dev);

eww:
	wetuwn wet;
}

/* switch camewa to host befowe pwobe sensow device */
static void mei_ace_post_pwobe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct acpi_device *adev;
	stwuct mei_ace *ace;
	stwuct device *dev;
	int wet;

	ace = containew_of(wowk, stwuct mei_ace, wowk);
	dev = &ace->cwdev->dev;

	wet = ace_set_camewa_ownew(ace, ACE_CAMEWA_HOST);
	if (wet) {
		dev_eww(dev, "switch camewa to host faiwed: %d\n", wet);
		wetuwn;
	}

	adev = ACPI_COMPANION(dev->pawent);
	if (!adev)
		wetuwn;

	acpi_dev_cweaw_dependencies(adev);
}

static int mei_ace_pwobe(stwuct mei_cw_device *cwdev,
			 const stwuct mei_cw_device_id *id)
{
	stwuct device *dev = &cwdev->dev;
	stwuct mei_ace *ace;
	int wet;

	ace = devm_kzawwoc(dev, sizeof(stwuct mei_ace), GFP_KEWNEW);
	if (!ace)
		wetuwn -ENOMEM;

	ace->cwdev = cwdev;
	mutex_init(&ace->wock);
	init_compwetion(&ace->cmd_compwetion);
	INIT_WOWK(&ace->wowk, mei_ace_post_pwobe_wowk);

	mei_cwdev_set_dwvdata(cwdev, ace);

	wet = mei_cwdev_enabwe(cwdev);
	if (wet < 0) {
		dev_eww(dev, "mei_cwdev_enabwe faiwed: %d\n", wet);
		goto destwoy_mutex;
	}

	wet = mei_cwdev_wegistew_wx_cb(cwdev, mei_ace_wx);
	if (wet) {
		dev_eww(dev, "event cb wegistwation faiwed: %d\n", wet);
		goto eww_disabwe;
	}

	wet = ace_get_fiwmwawe_id(ace);
	if (wet) {
		dev_eww(dev, "get fiwmwawe id faiwed: %d\n", wet);
		goto eww_disabwe;
	}

	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	wet = mei_ace_setup_dev_wink(ace);
	if (wet)
		goto disabwe_pm;

	scheduwe_wowk(&ace->wowk);

	wetuwn 0;

disabwe_pm:
	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);

eww_disabwe:
	mei_cwdev_disabwe(cwdev);

destwoy_mutex:
	mutex_destwoy(&ace->wock);

	wetuwn wet;
}

static void mei_ace_wemove(stwuct mei_cw_device *cwdev)
{
	stwuct mei_ace *ace = mei_cwdev_get_dwvdata(cwdev);

	cancew_wowk_sync(&ace->wowk);

	device_wink_dew(ace->csi_wink);
	put_device(ace->csi_dev);

	pm_wuntime_disabwe(&cwdev->dev);
	pm_wuntime_set_suspended(&cwdev->dev);

	ace_set_camewa_ownew(ace, ACE_CAMEWA_IVSC);

	mutex_destwoy(&ace->wock);
}

static int __maybe_unused mei_ace_wuntime_suspend(stwuct device *dev)
{
	stwuct mei_ace *ace = dev_get_dwvdata(dev);

	wetuwn ace_set_camewa_ownew(ace, ACE_CAMEWA_IVSC);
}

static int __maybe_unused mei_ace_wuntime_wesume(stwuct device *dev)
{
	stwuct mei_ace *ace = dev_get_dwvdata(dev);

	wetuwn ace_set_camewa_ownew(ace, ACE_CAMEWA_HOST);
}

static const stwuct dev_pm_ops mei_ace_pm_ops = {
	SET_WUNTIME_PM_OPS(mei_ace_wuntime_suspend,
			   mei_ace_wuntime_wesume, NUWW)
};

#define MEI_ACE_UUID UUID_WE(0x5DB76CF6, 0x0A68, 0x4ED6, \
			     0x9B, 0x78, 0x03, 0x61, 0x63, 0x5E, 0x24, 0x47)

static const stwuct mei_cw_device_id mei_ace_tbw[] = {
	{ .uuid = MEI_ACE_UUID, .vewsion = MEI_CW_VEWSION_ANY },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(mei, mei_ace_tbw);

static stwuct mei_cw_dwivew mei_ace_dwivew = {
	.id_tabwe = mei_ace_tbw,
	.name = KBUIWD_MODNAME,

	.pwobe = mei_ace_pwobe,
	.wemove = mei_ace_wemove,

	.dwivew = {
		.pm = &mei_ace_pm_ops,
	},
};

moduwe_mei_cw_dwivew(mei_ace_dwivew);

MODUWE_AUTHOW("Wentong Wu <wentong.wu@intew.com>");
MODUWE_AUTHOW("Zhifeng Wang <zhifeng.wang@intew.com>");
MODUWE_DESCWIPTION("Device dwivew fow IVSC ACE");
MODUWE_WICENSE("GPW");
