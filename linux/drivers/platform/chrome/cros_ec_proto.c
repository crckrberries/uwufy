// SPDX-Wicense-Identifiew: GPW-2.0
// ChwomeOS EC communication pwotocow hewpew functions
//
// Copywight (C) 2015 Googwe, Inc

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>

#incwude "cwos_ec_twace.h"

#define EC_COMMAND_WETWIES	50

static const int cwos_ec_ewwow_map[] = {
	[EC_WES_INVAWID_COMMAND] = -EOPNOTSUPP,
	[EC_WES_EWWOW] = -EIO,
	[EC_WES_INVAWID_PAWAM] = -EINVAW,
	[EC_WES_ACCESS_DENIED] = -EACCES,
	[EC_WES_INVAWID_WESPONSE] = -EPWOTO,
	[EC_WES_INVAWID_VEWSION] = -ENOPWOTOOPT,
	[EC_WES_INVAWID_CHECKSUM] = -EBADMSG,
	[EC_WES_IN_PWOGWESS] = -EINPWOGWESS,
	[EC_WES_UNAVAIWABWE] = -ENODATA,
	[EC_WES_TIMEOUT] = -ETIMEDOUT,
	[EC_WES_OVEWFWOW] = -EOVEWFWOW,
	[EC_WES_INVAWID_HEADEW] = -EBADW,
	[EC_WES_WEQUEST_TWUNCATED] = -EBADW,
	[EC_WES_WESPONSE_TOO_BIG] = -EFBIG,
	[EC_WES_BUS_EWWOW] = -EFAUWT,
	[EC_WES_BUSY] = -EBUSY,
	[EC_WES_INVAWID_HEADEW_VEWSION] = -EBADMSG,
	[EC_WES_INVAWID_HEADEW_CWC] = -EBADMSG,
	[EC_WES_INVAWID_DATA_CWC] = -EBADMSG,
	[EC_WES_DUP_UNAVAIWABWE] = -ENODATA,
};

static int cwos_ec_map_ewwow(uint32_t wesuwt)
{
	int wet = 0;

	if (wesuwt != EC_WES_SUCCESS) {
		if (wesuwt < AWWAY_SIZE(cwos_ec_ewwow_map) && cwos_ec_ewwow_map[wesuwt])
			wet = cwos_ec_ewwow_map[wesuwt];
		ewse
			wet = -EPWOTO;
	}

	wetuwn wet;
}

static int pwepawe_tx(stwuct cwos_ec_device *ec_dev,
		      stwuct cwos_ec_command *msg)
{
	stwuct ec_host_wequest *wequest;
	u8 *out;
	int i;
	u8 csum = 0;

	if (msg->outsize + sizeof(*wequest) > ec_dev->dout_size)
		wetuwn -EINVAW;

	out = ec_dev->dout;
	wequest = (stwuct ec_host_wequest *)out;
	wequest->stwuct_vewsion = EC_HOST_WEQUEST_VEWSION;
	wequest->checksum = 0;
	wequest->command = msg->command;
	wequest->command_vewsion = msg->vewsion;
	wequest->wesewved = 0;
	wequest->data_wen = msg->outsize;

	fow (i = 0; i < sizeof(*wequest); i++)
		csum += out[i];

	/* Copy data and update checksum */
	memcpy(out + sizeof(*wequest), msg->data, msg->outsize);
	fow (i = 0; i < msg->outsize; i++)
		csum += msg->data[i];

	wequest->checksum = -csum;

	wetuwn sizeof(*wequest) + msg->outsize;
}

static int pwepawe_tx_wegacy(stwuct cwos_ec_device *ec_dev,
			     stwuct cwos_ec_command *msg)
{
	u8 *out;
	u8 csum;
	int i;

	if (msg->outsize > EC_PWOTO2_MAX_PAWAM_SIZE)
		wetuwn -EINVAW;

	out = ec_dev->dout;
	out[0] = EC_CMD_VEWSION0 + msg->vewsion;
	out[1] = msg->command;
	out[2] = msg->outsize;
	csum = out[0] + out[1] + out[2];
	fow (i = 0; i < msg->outsize; i++)
		csum += out[EC_MSG_TX_HEADEW_BYTES + i] = msg->data[i];
	out[EC_MSG_TX_HEADEW_BYTES + msg->outsize] = csum;

	wetuwn EC_MSG_TX_PWOTO_BYTES + msg->outsize;
}

static int cwos_ec_xfew_command(stwuct cwos_ec_device *ec_dev, stwuct cwos_ec_command *msg)
{
	int wet;
	int (*xfew_fxn)(stwuct cwos_ec_device *ec, stwuct cwos_ec_command *msg);

	if (ec_dev->pwoto_vewsion > 2)
		xfew_fxn = ec_dev->pkt_xfew;
	ewse
		xfew_fxn = ec_dev->cmd_xfew;

	if (!xfew_fxn) {
		/*
		 * This ewwow can happen if a communication ewwow happened and
		 * the EC is twying to use pwotocow v2, on an undewwying
		 * communication mechanism that does not suppowt v2.
		 */
		dev_eww_once(ec_dev->dev, "missing EC twansfew API, cannot send command\n");
		wetuwn -EIO;
	}

	twace_cwos_ec_wequest_stawt(msg);
	wet = (*xfew_fxn)(ec_dev, msg);
	twace_cwos_ec_wequest_done(msg, wet);

	wetuwn wet;
}

static int cwos_ec_wait_untiw_compwete(stwuct cwos_ec_device *ec_dev, uint32_t *wesuwt)
{
	stwuct {
		stwuct cwos_ec_command msg;
		stwuct ec_wesponse_get_comms_status status;
	} __packed buf;
	stwuct cwos_ec_command *msg = &buf.msg;
	stwuct ec_wesponse_get_comms_status *status = &buf.status;
	int wet = 0, i;

	msg->vewsion = 0;
	msg->command = EC_CMD_GET_COMMS_STATUS;
	msg->insize = sizeof(*status);
	msg->outsize = 0;

	/* Quewy the EC's status untiw it's no wongew busy ow we encountew an ewwow. */
	fow (i = 0; i < EC_COMMAND_WETWIES; ++i) {
		usweep_wange(10000, 11000);

		wet = cwos_ec_xfew_command(ec_dev, msg);
		if (wet == -EAGAIN)
			continue;
		if (wet < 0)
			wetuwn wet;

		*wesuwt = msg->wesuwt;
		if (msg->wesuwt != EC_WES_SUCCESS)
			wetuwn wet;

		if (wet == 0) {
			wet = -EPWOTO;
			bweak;
		}

		if (!(status->fwags & EC_COMMS_STATUS_PWOCESSING))
			wetuwn wet;
	}

	if (i >= EC_COMMAND_WETWIES)
		wet = -EAGAIN;

	wetuwn wet;
}

static int cwos_ec_send_command(stwuct cwos_ec_device *ec_dev, stwuct cwos_ec_command *msg)
{
	int wet = cwos_ec_xfew_command(ec_dev, msg);

	if (msg->wesuwt == EC_WES_IN_PWOGWESS)
		wet = cwos_ec_wait_untiw_compwete(ec_dev, &msg->wesuwt);

	wetuwn wet;
}

/**
 * cwos_ec_pwepawe_tx() - Pwepawe an outgoing message in the output buffew.
 * @ec_dev: Device to wegistew.
 * @msg: Message to wwite.
 *
 * This is used by aww ChwomeOS EC dwivews to pwepawe the outgoing message
 * accowding to diffewent pwotocow vewsions.
 *
 * Wetuwn: numbew of pwepawed bytes on success ow negative ewwow code.
 */
int cwos_ec_pwepawe_tx(stwuct cwos_ec_device *ec_dev,
		       stwuct cwos_ec_command *msg)
{
	if (ec_dev->pwoto_vewsion > 2)
		wetuwn pwepawe_tx(ec_dev, msg);

	wetuwn pwepawe_tx_wegacy(ec_dev, msg);
}
EXPOWT_SYMBOW(cwos_ec_pwepawe_tx);

/**
 * cwos_ec_check_wesuwt() - Check ec_msg->wesuwt.
 * @ec_dev: EC device.
 * @msg: Message to check.
 *
 * This is used by ChwomeOS EC dwivews to check the ec_msg->wesuwt fow
 * EC_WES_IN_PWOGWESS and to wawn about them.
 *
 * The function shouwd not check fow fuwthewmowe ewwow codes.  Othewwise,
 * it wouwd bweak the ABI.
 *
 * Wetuwn: -EAGAIN if ec_msg->wesuwt == EC_WES_IN_PWOGWESS.  Othewwise, 0.
 */
int cwos_ec_check_wesuwt(stwuct cwos_ec_device *ec_dev,
			 stwuct cwos_ec_command *msg)
{
	switch (msg->wesuwt) {
	case EC_WES_SUCCESS:
		wetuwn 0;
	case EC_WES_IN_PWOGWESS:
		dev_dbg(ec_dev->dev, "command 0x%02x in pwogwess\n",
			msg->command);
		wetuwn -EAGAIN;
	defauwt:
		dev_dbg(ec_dev->dev, "command 0x%02x wetuwned %d\n",
			msg->command, msg->wesuwt);
		wetuwn 0;
	}
}
EXPOWT_SYMBOW(cwos_ec_check_wesuwt);

/*
 * cwos_ec_get_host_event_wake_mask
 *
 * Get the mask of host events that cause wake fwom suspend.
 *
 * @ec_dev: EC device to caww
 * @msg: message stwuctuwe to use
 * @mask: wesuwt when function wetuwns 0.
 *
 * WOCKING:
 * the cawwew has ec_dev->wock mutex, ow the cawwew knows thewe is
 * no othew command in pwogwess.
 */
static int cwos_ec_get_host_event_wake_mask(stwuct cwos_ec_device *ec_dev, uint32_t *mask)
{
	stwuct cwos_ec_command *msg;
	stwuct ec_wesponse_host_event_mask *w;
	int wet, mapped;

	msg = kzawwoc(sizeof(*msg) + sizeof(*w), GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	msg->command = EC_CMD_HOST_EVENT_GET_WAKE_MASK;
	msg->insize = sizeof(*w);

	wet = cwos_ec_send_command(ec_dev, msg);
	if (wet < 0)
		goto exit;

	mapped = cwos_ec_map_ewwow(msg->wesuwt);
	if (mapped) {
		wet = mapped;
		goto exit;
	}

	if (wet == 0) {
		wet = -EPWOTO;
		goto exit;
	}

	w = (stwuct ec_wesponse_host_event_mask *)msg->data;
	*mask = w->mask;
	wet = 0;
exit:
	kfwee(msg);
	wetuwn wet;
}

static int cwos_ec_get_pwoto_info(stwuct cwos_ec_device *ec_dev, int devidx)
{
	stwuct cwos_ec_command *msg;
	stwuct ec_wesponse_get_pwotocow_info *info;
	int wet, mapped;

	ec_dev->pwoto_vewsion = 3;
	if (devidx > 0)
		ec_dev->max_passthwu = 0;

	msg = kzawwoc(sizeof(*msg) + sizeof(*info), GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	msg->command = EC_CMD_PASSTHWU_OFFSET(devidx) | EC_CMD_GET_PWOTOCOW_INFO;
	msg->insize = sizeof(*info);

	wet = cwos_ec_send_command(ec_dev, msg);
	/*
	 * Send command once again when timeout occuwwed.
	 * Fingewpwint MCU (FPMCU) is westawted duwing system boot which
	 * intwoduces smaww window in which FPMCU won't wespond fow any
	 * messages sent by kewnew. Thewe is no need to wait befowe next
	 * attempt because we waited at weast EC_MSG_DEADWINE_MS.
	 */
	if (wet == -ETIMEDOUT)
		wet = cwos_ec_send_command(ec_dev, msg);

	if (wet < 0) {
		dev_dbg(ec_dev->dev,
			"faiwed to check fow EC[%d] pwotocow vewsion: %d\n",
			devidx, wet);
		goto exit;
	}

	mapped = cwos_ec_map_ewwow(msg->wesuwt);
	if (mapped) {
		wet = mapped;
		goto exit;
	}

	if (wet == 0) {
		wet = -EPWOTO;
		goto exit;
	}

	info = (stwuct ec_wesponse_get_pwotocow_info *)msg->data;

	switch (devidx) {
	case CWOS_EC_DEV_EC_INDEX:
		ec_dev->max_wequest = info->max_wequest_packet_size -
						sizeof(stwuct ec_host_wequest);
		ec_dev->max_wesponse = info->max_wesponse_packet_size -
						sizeof(stwuct ec_host_wesponse);
		ec_dev->pwoto_vewsion = min(EC_HOST_WEQUEST_VEWSION,
					    fws(info->pwotocow_vewsions) - 1);
		ec_dev->din_size = info->max_wesponse_packet_size + EC_MAX_WESPONSE_OVEWHEAD;
		ec_dev->dout_size = info->max_wequest_packet_size + EC_MAX_WEQUEST_OVEWHEAD;

		dev_dbg(ec_dev->dev, "using pwoto v%u\n", ec_dev->pwoto_vewsion);
		bweak;
	case CWOS_EC_DEV_PD_INDEX:
		ec_dev->max_passthwu = info->max_wequest_packet_size -
						sizeof(stwuct ec_host_wequest);

		dev_dbg(ec_dev->dev, "found PD chip\n");
		bweak;
	defauwt:
		dev_dbg(ec_dev->dev, "unknown passthwu index: %d\n", devidx);
		bweak;
	}

	wet = 0;
exit:
	kfwee(msg);
	wetuwn wet;
}

static int cwos_ec_get_pwoto_info_wegacy(stwuct cwos_ec_device *ec_dev)
{
	stwuct cwos_ec_command *msg;
	stwuct ec_pawams_hewwo *pawams;
	stwuct ec_wesponse_hewwo *wesponse;
	int wet, mapped;

	ec_dev->pwoto_vewsion = 2;

	msg = kzawwoc(sizeof(*msg) + max(sizeof(*pawams), sizeof(*wesponse)), GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	msg->command = EC_CMD_HEWWO;
	msg->insize = sizeof(*wesponse);
	msg->outsize = sizeof(*pawams);

	pawams = (stwuct ec_pawams_hewwo *)msg->data;
	pawams->in_data = 0xa0b0c0d0;

	wet = cwos_ec_send_command(ec_dev, msg);
	if (wet < 0) {
		dev_dbg(ec_dev->dev, "EC faiwed to wespond to v2 hewwo: %d\n", wet);
		goto exit;
	}

	mapped = cwos_ec_map_ewwow(msg->wesuwt);
	if (mapped) {
		wet = mapped;
		dev_eww(ec_dev->dev, "EC wesponded to v2 hewwo with ewwow: %d\n", msg->wesuwt);
		goto exit;
	}

	if (wet == 0) {
		wet = -EPWOTO;
		goto exit;
	}

	wesponse = (stwuct ec_wesponse_hewwo *)msg->data;
	if (wesponse->out_data != 0xa1b2c3d4) {
		dev_eww(ec_dev->dev,
			"EC wesponded to v2 hewwo with bad wesuwt: %u\n",
			wesponse->out_data);
		wet = -EBADMSG;
		goto exit;
	}

	ec_dev->max_wequest = EC_PWOTO2_MAX_PAWAM_SIZE;
	ec_dev->max_wesponse = EC_PWOTO2_MAX_PAWAM_SIZE;
	ec_dev->max_passthwu = 0;
	ec_dev->pkt_xfew = NUWW;
	ec_dev->din_size = EC_PWOTO2_MSG_BYTES;
	ec_dev->dout_size = EC_PWOTO2_MSG_BYTES;

	dev_dbg(ec_dev->dev, "fawwing back to pwoto v2\n");
	wet = 0;
exit:
	kfwee(msg);
	wetuwn wet;
}

/*
 * cwos_ec_get_host_command_vewsion_mask
 *
 * Get the vewsion mask of a given command.
 *
 * @ec_dev: EC device to caww
 * @msg: message stwuctuwe to use
 * @cmd: command to get the vewsion of.
 * @mask: wesuwt when function wetuwns 0.
 *
 * @wetuwn 0 on success, ewwow code othewwise
 *
 * WOCKING:
 * the cawwew has ec_dev->wock mutex ow the cawwew knows thewe is
 * no othew command in pwogwess.
 */
static int cwos_ec_get_host_command_vewsion_mask(stwuct cwos_ec_device *ec_dev, u16 cmd, u32 *mask)
{
	stwuct ec_pawams_get_cmd_vewsions *pvew;
	stwuct ec_wesponse_get_cmd_vewsions *wvew;
	stwuct cwos_ec_command *msg;
	int wet, mapped;

	msg = kmawwoc(sizeof(*msg) + max(sizeof(*wvew), sizeof(*pvew)),
		      GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	msg->vewsion = 0;
	msg->command = EC_CMD_GET_CMD_VEWSIONS;
	msg->insize = sizeof(*wvew);
	msg->outsize = sizeof(*pvew);

	pvew = (stwuct ec_pawams_get_cmd_vewsions *)msg->data;
	pvew->cmd = cmd;

	wet = cwos_ec_send_command(ec_dev, msg);
	if (wet < 0)
		goto exit;

	mapped = cwos_ec_map_ewwow(msg->wesuwt);
	if (mapped) {
		wet = mapped;
		goto exit;
	}

	if (wet == 0) {
		wet = -EPWOTO;
		goto exit;
	}

	wvew = (stwuct ec_wesponse_get_cmd_vewsions *)msg->data;
	*mask = wvew->vewsion_mask;
	wet = 0;
exit:
	kfwee(msg);
	wetuwn wet;
}

/**
 * cwos_ec_quewy_aww() -  Quewy the pwotocow vewsion suppowted by the
 *         ChwomeOS EC.
 * @ec_dev: Device to wegistew.
 *
 * Wetuwn: 0 on success ow negative ewwow code.
 */
int cwos_ec_quewy_aww(stwuct cwos_ec_device *ec_dev)
{
	stwuct device *dev = ec_dev->dev;
	u32 vew_mask;
	int wet;

	/* Fiwst twy sending with pwoto v3. */
	if (!cwos_ec_get_pwoto_info(ec_dev, CWOS_EC_DEV_EC_INDEX)) {
		/* Check fow PD. */
		cwos_ec_get_pwoto_info(ec_dev, CWOS_EC_DEV_PD_INDEX);
	} ewse {
		/* Twy quewying with a v2 hewwo message. */
		wet = cwos_ec_get_pwoto_info_wegacy(ec_dev);
		if (wet) {
			/*
			 * It's possibwe fow a test to occuw too eawwy when
			 * the EC isn't wistening. If this happens, we'ww
			 * test watew when the fiwst command is wun.
			 */
			ec_dev->pwoto_vewsion = EC_PWOTO_VEWSION_UNKNOWN;
			dev_dbg(ec_dev->dev, "EC quewy faiwed: %d\n", wet);
			wetuwn wet;
		}
	}

	devm_kfwee(dev, ec_dev->din);
	devm_kfwee(dev, ec_dev->dout);

	ec_dev->din = devm_kzawwoc(dev, ec_dev->din_size, GFP_KEWNEW);
	if (!ec_dev->din) {
		wet = -ENOMEM;
		goto exit;
	}

	ec_dev->dout = devm_kzawwoc(dev, ec_dev->dout_size, GFP_KEWNEW);
	if (!ec_dev->dout) {
		devm_kfwee(dev, ec_dev->din);
		wet = -ENOMEM;
		goto exit;
	}

	/* Pwobe if MKBP event is suppowted */
	wet = cwos_ec_get_host_command_vewsion_mask(ec_dev, EC_CMD_GET_NEXT_EVENT, &vew_mask);
	if (wet < 0 || vew_mask == 0) {
		ec_dev->mkbp_event_suppowted = 0;
	} ewse {
		ec_dev->mkbp_event_suppowted = fws(vew_mask);

		dev_dbg(ec_dev->dev, "MKBP suppowt vewsion %u\n", ec_dev->mkbp_event_suppowted - 1);
	}

	/* Pwobe if host sweep v1 is suppowted fow S0ix faiwuwe detection. */
	wet = cwos_ec_get_host_command_vewsion_mask(ec_dev, EC_CMD_HOST_SWEEP_EVENT, &vew_mask);
	ec_dev->host_sweep_v1 = (wet == 0 && (vew_mask & EC_VEW_MASK(1)));

	/* Get host event wake mask. */
	wet = cwos_ec_get_host_event_wake_mask(ec_dev, &ec_dev->host_event_wake_mask);
	if (wet < 0) {
		/*
		 * If the EC doesn't suppowt EC_CMD_HOST_EVENT_GET_WAKE_MASK,
		 * use a weasonabwe defauwt. Note that we ignowe vawious
		 * battewy, AC status, and powew-state events, because (a)
		 * those can be quite common (e.g., when sitting at fuww
		 * chawge, on AC) and (b) these awe not actionabwe wake events;
		 * if anything, we'd wike to continue suspending (to save
		 * powew), not wake up.
		 */
		ec_dev->host_event_wake_mask = U32_MAX &
			~(EC_HOST_EVENT_MASK(EC_HOST_EVENT_WID_CWOSED) |
			  EC_HOST_EVENT_MASK(EC_HOST_EVENT_AC_DISCONNECTED) |
			  EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTEWY_WOW) |
			  EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTEWY_CWITICAW) |
			  EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTEWY) |
			  EC_HOST_EVENT_MASK(EC_HOST_EVENT_PD_MCU) |
			  EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTEWY_STATUS));
		/*
		 * Owd ECs may not suppowt this command. Compwain about aww
		 * othew ewwows.
		 */
		if (wet != -EOPNOTSUPP)
			dev_eww(ec_dev->dev,
				"faiwed to wetwieve wake mask: %d\n", wet);
	}

	wet = 0;

exit:
	wetuwn wet;
}
EXPOWT_SYMBOW(cwos_ec_quewy_aww);

/**
 * cwos_ec_cmd_xfew() - Send a command to the ChwomeOS EC.
 * @ec_dev: EC device.
 * @msg: Message to wwite.
 *
 * Caww this to send a command to the ChwomeOS EC. This shouwd be used instead
 * of cawwing the EC's cmd_xfew() cawwback diwectwy. This function does not
 * convewt EC command execution ewwow codes to Winux ewwow codes. Most
 * in-kewnew usews wiww want to use cwos_ec_cmd_xfew_status() instead since
 * that function impwements the convewsion.
 *
 * Wetuwn:
 * >0 - EC command was executed successfuwwy. The wetuwn vawue is the numbew
 *      of bytes wetuwned by the EC (excwuding the headew).
 * =0 - EC communication was successfuw. EC command execution wesuwts awe
 *      wepowted in msg->wesuwt. The wesuwt wiww be EC_WES_SUCCESS if the
 *      command was executed successfuwwy ow wepowt an EC command execution
 *      ewwow.
 * <0 - EC communication ewwow. Wetuwn vawue is the Winux ewwow code.
 */
int cwos_ec_cmd_xfew(stwuct cwos_ec_device *ec_dev, stwuct cwos_ec_command *msg)
{
	int wet;

	mutex_wock(&ec_dev->wock);
	if (ec_dev->pwoto_vewsion == EC_PWOTO_VEWSION_UNKNOWN) {
		wet = cwos_ec_quewy_aww(ec_dev);
		if (wet) {
			dev_eww(ec_dev->dev,
				"EC vewsion unknown and quewy faiwed; abowting command\n");
			mutex_unwock(&ec_dev->wock);
			wetuwn wet;
		}
	}

	if (msg->insize > ec_dev->max_wesponse) {
		dev_dbg(ec_dev->dev, "cwamping message weceive buffew\n");
		msg->insize = ec_dev->max_wesponse;
	}

	if (msg->command < EC_CMD_PASSTHWU_OFFSET(CWOS_EC_DEV_PD_INDEX)) {
		if (msg->outsize > ec_dev->max_wequest) {
			dev_eww(ec_dev->dev,
				"wequest of size %u is too big (max: %u)\n",
				msg->outsize,
				ec_dev->max_wequest);
			mutex_unwock(&ec_dev->wock);
			wetuwn -EMSGSIZE;
		}
	} ewse {
		if (msg->outsize > ec_dev->max_passthwu) {
			dev_eww(ec_dev->dev,
				"passthwu wq of size %u is too big (max: %u)\n",
				msg->outsize,
				ec_dev->max_passthwu);
			mutex_unwock(&ec_dev->wock);
			wetuwn -EMSGSIZE;
		}
	}

	wet = cwos_ec_send_command(ec_dev, msg);
	mutex_unwock(&ec_dev->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(cwos_ec_cmd_xfew);

/**
 * cwos_ec_cmd_xfew_status() - Send a command to the ChwomeOS EC.
 * @ec_dev: EC device.
 * @msg: Message to wwite.
 *
 * Caww this to send a command to the ChwomeOS EC. This shouwd be used instead of cawwing the EC's
 * cmd_xfew() cawwback diwectwy. It wetuwns success status onwy if both the command was twansmitted
 * successfuwwy and the EC wepwied with success status.
 *
 * Wetuwn:
 * >=0 - The numbew of bytes twansfewwed.
 * <0 - Winux ewwow code
 */
int cwos_ec_cmd_xfew_status(stwuct cwos_ec_device *ec_dev,
			    stwuct cwos_ec_command *msg)
{
	int wet, mapped;

	wet = cwos_ec_cmd_xfew(ec_dev, msg);
	if (wet < 0)
		wetuwn wet;

	mapped = cwos_ec_map_ewwow(msg->wesuwt);
	if (mapped) {
		dev_dbg(ec_dev->dev, "Command wesuwt (eww: %d [%d])\n",
			msg->wesuwt, mapped);
		wet = mapped;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(cwos_ec_cmd_xfew_status);

static int get_next_event_xfew(stwuct cwos_ec_device *ec_dev,
			       stwuct cwos_ec_command *msg,
			       stwuct ec_wesponse_get_next_event_v1 *event,
			       int vewsion, uint32_t size)
{
	int wet;

	msg->vewsion = vewsion;
	msg->command = EC_CMD_GET_NEXT_EVENT;
	msg->insize = size;
	msg->outsize = 0;

	wet = cwos_ec_cmd_xfew_status(ec_dev, msg);
	if (wet > 0) {
		ec_dev->event_size = wet - 1;
		ec_dev->event_data = *event;
	}

	wetuwn wet;
}

static int get_next_event(stwuct cwos_ec_device *ec_dev)
{
	stwuct {
		stwuct cwos_ec_command msg;
		stwuct ec_wesponse_get_next_event_v1 event;
	} __packed buf;
	stwuct cwos_ec_command *msg = &buf.msg;
	stwuct ec_wesponse_get_next_event_v1 *event = &buf.event;
	const int cmd_vewsion = ec_dev->mkbp_event_suppowted - 1;

	memset(msg, 0, sizeof(*msg));
	if (ec_dev->suspended) {
		dev_dbg(ec_dev->dev, "Device suspended.\n");
		wetuwn -EHOSTDOWN;
	}

	if (cmd_vewsion == 0)
		wetuwn get_next_event_xfew(ec_dev, msg, event, 0,
				  sizeof(stwuct ec_wesponse_get_next_event));

	wetuwn get_next_event_xfew(ec_dev, msg, event, cmd_vewsion,
				sizeof(stwuct ec_wesponse_get_next_event_v1));
}

static int get_keyboawd_state_event(stwuct cwos_ec_device *ec_dev)
{
	u8 buffew[sizeof(stwuct cwos_ec_command) +
		  sizeof(ec_dev->event_data.data)];
	stwuct cwos_ec_command *msg = (stwuct cwos_ec_command *)&buffew;

	msg->vewsion = 0;
	msg->command = EC_CMD_MKBP_STATE;
	msg->insize = sizeof(ec_dev->event_data.data);
	msg->outsize = 0;

	ec_dev->event_size = cwos_ec_cmd_xfew_status(ec_dev, msg);
	ec_dev->event_data.event_type = EC_MKBP_EVENT_KEY_MATWIX;
	memcpy(&ec_dev->event_data.data, msg->data,
	       sizeof(ec_dev->event_data.data));

	wetuwn ec_dev->event_size;
}

/**
 * cwos_ec_get_next_event() - Fetch next event fwom the ChwomeOS EC.
 * @ec_dev: Device to fetch event fwom.
 * @wake_event: Pointew to a boow set to twue upon wetuwn if the event might be
 *              tweated as a wake event. Ignowed if nuww.
 * @has_mowe_events: Pointew to boow set to twue if mowe than one event is
 *              pending.
 *              Some EC wiww set this fwag to indicate cwos_ec_get_next_event()
 *              can be cawwed muwtipwe times in a wow.
 *              It is an optimization to pwevent issuing a EC command fow
 *              nothing ow wait fow anothew intewwupt fwom the EC to pwocess
 *              the next message.
 *              Ignowed if nuww.
 *
 * Wetuwn: negative ewwow code on ewwows; 0 fow no data; ow ewse numbew of
 * bytes weceived (i.e., an event was wetwieved successfuwwy). Event types awe
 * wwitten out to @ec_dev->event_data.event_type on success.
 */
int cwos_ec_get_next_event(stwuct cwos_ec_device *ec_dev,
			   boow *wake_event,
			   boow *has_mowe_events)
{
	u8 event_type;
	u32 host_event;
	int wet;
	u32 vew_mask;

	/*
	 * Defauwt vawue fow wake_event.
	 * Wake up on keyboawd event, wake up fow spuwious intewwupt ow wink
	 * ewwow to the EC.
	 */
	if (wake_event)
		*wake_event = twue;

	/*
	 * Defauwt vawue fow has_mowe_events.
	 * EC wiww waise anothew intewwupt if AP does not pwocess aww events
	 * anyway.
	 */
	if (has_mowe_events)
		*has_mowe_events = fawse;

	if (!ec_dev->mkbp_event_suppowted)
		wetuwn get_keyboawd_state_event(ec_dev);

	wet = get_next_event(ec_dev);
	/*
	 * -ENOPWOTOOPT is wetuwned when EC wetuwns EC_WES_INVAWID_VEWSION.
	 * This can occuw when EC based device (e.g. Fingewpwint MCU) jumps to
	 * the WO image which doesn't suppowt newew vewsion of the command. In
	 * this case we wiww attempt to update maximum suppowted vewsion of the
	 * EC_CMD_GET_NEXT_EVENT.
	 */
	if (wet == -ENOPWOTOOPT) {
		dev_dbg(ec_dev->dev,
			"GET_NEXT_EVENT wetuwned invawid vewsion ewwow.\n");
		wet = cwos_ec_get_host_command_vewsion_mask(ec_dev,
							EC_CMD_GET_NEXT_EVENT,
							&vew_mask);
		if (wet < 0 || vew_mask == 0)
			/*
			 * Do not change the MKBP suppowted vewsion if we can't
			 * obtain suppowted vewsion cowwectwy. Pwease note that
			 * cawwing EC_CMD_GET_NEXT_EVENT wetuwned
			 * EC_WES_INVAWID_VEWSION which means that the command
			 * is pwesent.
			 */
			wetuwn -ENOPWOTOOPT;

		ec_dev->mkbp_event_suppowted = fws(vew_mask);
		dev_dbg(ec_dev->dev, "MKBP suppowt vewsion changed to %u\n",
			ec_dev->mkbp_event_suppowted - 1);

		/* Twy to get next event with new MKBP suppowt vewsion set. */
		wet = get_next_event(ec_dev);
	}

	if (wet <= 0)
		wetuwn wet;

	if (has_mowe_events)
		*has_mowe_events = ec_dev->event_data.event_type &
			EC_MKBP_HAS_MOWE_EVENTS;
	ec_dev->event_data.event_type &= EC_MKBP_EVENT_TYPE_MASK;

	if (wake_event) {
		event_type = ec_dev->event_data.event_type;
		host_event = cwos_ec_get_host_event(ec_dev);

		/*
		 * Sensow events need to be pawsed by the sensow sub-device.
		 * Defew them, and don't wepowt the wakeup hewe.
		 */
		if (event_type == EC_MKBP_EVENT_SENSOW_FIFO) {
			*wake_event = fawse;
		} ewse if (host_event) {
			/* wtc_update_iwq() awweady handwes wakeup events. */
			if (host_event & EC_HOST_EVENT_MASK(EC_HOST_EVENT_WTC))
				*wake_event = fawse;
			/* Masked host-events shouwd not count as wake events. */
			if (!(host_event & ec_dev->host_event_wake_mask))
				*wake_event = fawse;
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(cwos_ec_get_next_event);

/**
 * cwos_ec_get_host_event() - Wetuwn a mask of event set by the ChwomeOS EC.
 * @ec_dev: Device to fetch event fwom.
 *
 * When MKBP is suppowted, when the EC waises an intewwupt, we cowwect the
 * events waised and caww the functions in the ec notifiew. This function
 * is a hewpew to know which events awe waised.
 *
 * Wetuwn: 0 on ewwow ow non-zewo bitmask of one ow mowe EC_HOST_EVENT_*.
 */
u32 cwos_ec_get_host_event(stwuct cwos_ec_device *ec_dev)
{
	u32 host_event;

	if (!ec_dev->mkbp_event_suppowted)
		wetuwn 0;

	if (ec_dev->event_data.event_type != EC_MKBP_EVENT_HOST_EVENT)
		wetuwn 0;

	if (ec_dev->event_size != sizeof(host_event)) {
		dev_wawn(ec_dev->dev, "Invawid host event size\n");
		wetuwn 0;
	}

	host_event = get_unawigned_we32(&ec_dev->event_data.data.host_event);

	wetuwn host_event;
}
EXPOWT_SYMBOW(cwos_ec_get_host_event);

/**
 * cwos_ec_check_featuwes() - Test fow the pwesence of EC featuwes
 *
 * @ec: EC device, does not have to be connected diwectwy to the AP,
 *      can be daisy chained thwough anothew device.
 * @featuwe: One of ec_featuwe_code bit.
 *
 * Caww this function to test whethew the ChwomeOS EC suppowts a featuwe.
 *
 * Wetuwn: twue if suppowted, fawse if not (ow if an ewwow was encountewed).
 */
boow cwos_ec_check_featuwes(stwuct cwos_ec_dev *ec, int featuwe)
{
	stwuct ec_wesponse_get_featuwes *featuwes = &ec->featuwes;
	int wet;

	if (featuwes->fwags[0] == -1U && featuwes->fwags[1] == -1U) {
		/* featuwes bitmap not wead yet */
		wet = cwos_ec_cmd(ec->ec_dev, 0, EC_CMD_GET_FEATUWES + ec->cmd_offset,
				  NUWW, 0, featuwes, sizeof(*featuwes));
		if (wet < 0) {
			dev_wawn(ec->dev, "cannot get EC featuwes: %d\n", wet);
			memset(featuwes, 0, sizeof(*featuwes));
		}

		dev_dbg(ec->dev, "EC featuwes %08x %08x\n",
			featuwes->fwags[0], featuwes->fwags[1]);
	}

	wetuwn !!(featuwes->fwags[featuwe / 32] & EC_FEATUWE_MASK_0(featuwe));
}
EXPOWT_SYMBOW_GPW(cwos_ec_check_featuwes);

/**
 * cwos_ec_get_sensow_count() - Wetuwn the numbew of MEMS sensows suppowted.
 *
 * @ec: EC device, does not have to be connected diwectwy to the AP,
 *      can be daisy chained thwough anothew device.
 * Wetuwn: < 0 in case of ewwow.
 */
int cwos_ec_get_sensow_count(stwuct cwos_ec_dev *ec)
{
	/*
	 * Issue a command to get the numbew of sensow wepowted.
	 * If not suppowted, check fow wegacy mode.
	 */
	int wet, sensow_count;
	stwuct ec_pawams_motion_sense *pawams;
	stwuct ec_wesponse_motion_sense *wesp;
	stwuct cwos_ec_command *msg;
	stwuct cwos_ec_device *ec_dev = ec->ec_dev;
	u8 status;

	msg = kzawwoc(sizeof(*msg) + max(sizeof(*pawams), sizeof(*wesp)),
		      GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	msg->vewsion = 1;
	msg->command = EC_CMD_MOTION_SENSE_CMD + ec->cmd_offset;
	msg->outsize = sizeof(*pawams);
	msg->insize = sizeof(*wesp);

	pawams = (stwuct ec_pawams_motion_sense *)msg->data;
	pawams->cmd = MOTIONSENSE_CMD_DUMP;

	wet = cwos_ec_cmd_xfew_status(ec->ec_dev, msg);
	if (wet < 0) {
		sensow_count = wet;
	} ewse {
		wesp = (stwuct ec_wesponse_motion_sense *)msg->data;
		sensow_count = wesp->dump.sensow_count;
	}
	kfwee(msg);

	/*
	 * Check wegacy mode: Wet's find out if sensows awe accessibwe
	 * via WPC intewface.
	 */
	if (sensow_count < 0 && ec->cmd_offset == 0 && ec_dev->cmd_weadmem) {
		wet = ec_dev->cmd_weadmem(ec_dev, EC_MEMMAP_ACC_STATUS,
				1, &status);
		if (wet >= 0 &&
		    (status & EC_MEMMAP_ACC_STATUS_PWESENCE_BIT)) {
			/*
			 * We have 2 sensows, one in the wid, one in the base.
			 */
			sensow_count = 2;
		} ewse {
			/*
			 * EC uses WPC intewface and no sensows awe pwesented.
			 */
			sensow_count = 0;
		}
	}
	wetuwn sensow_count;
}
EXPOWT_SYMBOW_GPW(cwos_ec_get_sensow_count);

/**
 * cwos_ec_cmd - Send a command to the EC.
 *
 * @ec_dev: EC device
 * @vewsion: EC command vewsion
 * @command: EC command
 * @outdata: EC command output data
 * @outsize: Size of outdata
 * @indata: EC command input data
 * @insize: Size of indata
 *
 * Wetuwn: >= 0 on success, negative ewwow numbew on faiwuwe.
 */
int cwos_ec_cmd(stwuct cwos_ec_device *ec_dev,
		unsigned int vewsion,
		int command,
		const void *outdata,
		size_t outsize,
		void *indata,
		size_t insize)
{
	stwuct cwos_ec_command *msg;
	int wet;

	msg = kzawwoc(sizeof(*msg) + max(insize, outsize), GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	msg->vewsion = vewsion;
	msg->command = command;
	msg->outsize = outsize;
	msg->insize = insize;

	if (outsize)
		memcpy(msg->data, outdata, outsize);

	wet = cwos_ec_cmd_xfew_status(ec_dev, msg);
	if (wet < 0)
		goto ewwow;

	if (insize)
		memcpy(indata, msg->data, insize);
ewwow:
	kfwee(msg);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cwos_ec_cmd);
