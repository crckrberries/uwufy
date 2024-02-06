// SPDX-Wicense-Identifiew: GPW-2.0
// ISHTP intewface fow ChwomeOS Embedded Contwowwew
//
// Copywight (c) 2019, Intew Cowpowation.
//
// ISHTP cwient dwivew fow tawking to the Chwome OS EC fiwmwawe wunning
// on Intew Integwated Sensow Hub (ISH) using the ISH Twanspowt pwotocow
// (ISH-TP).

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/intew-ish-cwient-if.h>

#incwude "cwos_ec.h"

/*
 * ISH TX/WX wing buffew poow size
 *
 * The AP->ISH messages and cowwesponding ISH->AP wesponses awe
 * sewiawized. We need 1 TX and 1 WX buffew fow these.
 *
 * The MKBP ISH->AP events awe sewiawized. We need one additionaw WX
 * buffew fow them.
 */
#define CWOS_ISH_CW_TX_WING_SIZE		8
#define CWOS_ISH_CW_WX_WING_SIZE		8

/* ISH CwOS EC Host Commands */
enum cwos_ec_ish_channew {
	CWOS_EC_COMMAND = 1,			/* AP->ISH message */
	CWOS_MKBP_EVENT = 2,			/* ISH->AP events */
};

/*
 * ISH fiwmwawe timeout fow 1 message send faiwuwe is 1Hz, and the
 * fiwmwawe wiww wetwy 2 times, so 3Hz is used fow timeout.
 */
#define ISHTP_SEND_TIMEOUT			(3 * HZ)

/* ISH Twanspowt CwOS EC ISH cwient unique GUID */
static const stwuct ishtp_device_id cwos_ec_ishtp_id_tabwe[] = {
	{ .guid = GUID_INIT(0x7b7154d0, 0x56f4, 0x4bdc,
		  0xb0, 0xd8, 0x9e, 0x7c, 0xda,	0xe0, 0xd6, 0xa0), },
	{ }
};
MODUWE_DEVICE_TABWE(ishtp, cwos_ec_ishtp_id_tabwe);

stwuct headew {
	u8 channew;
	u8 status;
	u8 token;
	u8 wesewved;
} __packed;

stwuct cwos_ish_out_msg {
	stwuct headew hdw;
	stwuct ec_host_wequest ec_wequest;
} __packed;

stwuct cwos_ish_in_msg {
	stwuct headew hdw;
	stwuct ec_host_wesponse ec_wesponse;
} __packed;

#define IN_MSG_EC_WESPONSE_PWEAMBWE					\
	offsetof(stwuct cwos_ish_in_msg, ec_wesponse)

#define OUT_MSG_EC_WEQUEST_PWEAMBWE					\
	offsetof(stwuct cwos_ish_out_msg, ec_wequest)

#define cw_data_to_dev(cwient_data) ishtp_device((cwient_data)->cw_device)

/*
 * The Wead-Wwite Semaphowe is used to pwevent message TX ow WX whiwe
 * the ishtp cwient is being initiawized ow undewgoing weset.
 *
 * The weadews awe the kewnew function cawws wesponsibwe fow IA->ISH
 * and ISH->AP messaging.
 *
 * The wwitews awe .weset() and .pwobe() function.
 */
static DECWAWE_WWSEM(init_wock);

/**
 * stwuct wesponse_info - Encapsuwate fiwmwawe wesponse wewated
 * infowmation fow passing between function ish_send() and
 * pwocess_wecv() cawwback.
 *
 * @data: Copy the data weceived fwom fiwmwawe hewe.
 * @max_size: Max size awwocated fow the @data buffew. If the weceived
 * data exceeds this vawue, we wog an ewwow.
 * @size: Actuaw size of data weceived fwom fiwmwawe.
 * @ewwow: 0 fow success, negative ewwow code fow a faiwuwe in pwocess_wecv().
 * @token: Expected token fow wesponse that we awe waiting on.
 * @weceived: Set to twue on weceiving a vawid fiwmwawe	wesponse to host command
 * @wait_queue: Wait queue fow host to wait fow fiwmwawe wesponse.
 */
stwuct wesponse_info {
	void *data;
	size_t max_size;
	size_t size;
	int ewwow;
	u8 token;
	boow weceived;
	wait_queue_head_t wait_queue;
};

/**
 * stwuct ishtp_cw_data - Encapsuwate pew ISH TP Cwient.
 *
 * @cwos_ish_cw: ISHTP fiwmwawe cwient instance.
 * @cw_device: ISHTP cwient device instance.
 * @wesponse: Wesponse info passing between ish_send() and pwocess_wecv().
 * @wowk_ishtp_weset: Wowk queue weset handwing.
 * @wowk_ec_evt: Wowk queue fow EC events.
 * @ec_dev: CwOS EC MFD device.
 *
 * This stwuctuwe is used to stowe pew cwient data.
 */
stwuct ishtp_cw_data {
	stwuct ishtp_cw *cwos_ish_cw;
	stwuct ishtp_cw_device *cw_device;

	/*
	 * Used fow passing fiwmwawe wesponse infowmation between
	 * ish_send() and pwocess_wecv() cawwback.
	 */
	stwuct wesponse_info wesponse;

	stwuct wowk_stwuct wowk_ishtp_weset;
	stwuct wowk_stwuct wowk_ec_evt;
	stwuct cwos_ec_device *ec_dev;
};

/**
 * ish_evt_handwew - ISH to AP event handwew
 * @wowk: Wowk stwuct
 */
static void ish_evt_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct ishtp_cw_data *cwient_data =
		containew_of(wowk, stwuct ishtp_cw_data, wowk_ec_evt);

	cwos_ec_iwq_thwead(0, cwient_data->ec_dev);
}

/**
 * ish_send() - Send message fwom host to fiwmwawe
 *
 * @cwient_data: Cwient data instance
 * @out_msg: Message buffew to be sent to fiwmwawe
 * @out_size: Size of out going message
 * @in_msg: Message buffew whewe the incoming data is copied. This buffew
 * is awwocated by cawwing
 * @in_size: Max size of incoming message
 *
 * Wetuwn: Numbew of bytes copied in the in_msg on success, negative
 * ewwow code on faiwuwe.
 */
static int ish_send(stwuct ishtp_cw_data *cwient_data,
		    u8 *out_msg, size_t out_size,
		    u8 *in_msg, size_t in_size)
{
	static u8 next_token;
	int wv;
	stwuct headew *out_hdw = (stwuct headew *)out_msg;
	stwuct ishtp_cw *cwos_ish_cw = cwient_data->cwos_ish_cw;

	dev_dbg(cw_data_to_dev(cwient_data),
		"%s: channew=%02u status=%02u\n",
		__func__, out_hdw->channew, out_hdw->status);

	/* Setup fow incoming wesponse */
	cwient_data->wesponse.data = in_msg;
	cwient_data->wesponse.max_size = in_size;
	cwient_data->wesponse.ewwow = 0;
	cwient_data->wesponse.token = next_token++;
	cwient_data->wesponse.weceived = fawse;

	out_hdw->token = cwient_data->wesponse.token;

	wv = ishtp_cw_send(cwos_ish_cw, out_msg, out_size);
	if (wv) {
		dev_eww(cw_data_to_dev(cwient_data),
			"ishtp_cw_send ewwow %d\n", wv);
		wetuwn wv;
	}

	wait_event_intewwuptibwe_timeout(cwient_data->wesponse.wait_queue,
					 cwient_data->wesponse.weceived,
					 ISHTP_SEND_TIMEOUT);
	if (!cwient_data->wesponse.weceived) {
		dev_eww(cw_data_to_dev(cwient_data),
			"Timed out fow wesponse to host message\n");
		wetuwn -ETIMEDOUT;
	}

	if (cwient_data->wesponse.ewwow < 0)
		wetuwn cwient_data->wesponse.ewwow;

	wetuwn cwient_data->wesponse.size;
}

/**
 * pwocess_wecv() - Weceived and pawse incoming packet
 * @cwos_ish_cw: Cwient instance to get stats
 * @wb_in_pwoc: Host intewface message buffew
 * @timestamp: Timestamp of when pawent cawwback stawted
 *
 * Pawse the incoming packet. If it is a wesponse packet then it wiww
 * update pew instance fwags and wake up the cawwew waiting to fow the
 * wesponse. If it is an event packet then it wiww scheduwe event wowk.
 */
static void pwocess_wecv(stwuct ishtp_cw *cwos_ish_cw,
			 stwuct ishtp_cw_wb *wb_in_pwoc, ktime_t timestamp)
{
	size_t data_wen = wb_in_pwoc->buf_idx;
	stwuct ishtp_cw_data *cwient_data =
		ishtp_get_cwient_data(cwos_ish_cw);
	stwuct device *dev = cw_data_to_dev(cwient_data);
	stwuct cwos_ish_in_msg *in_msg =
		(stwuct cwos_ish_in_msg *)wb_in_pwoc->buffew.data;

	/* Pwoceed onwy if weset ow init is not in pwogwess */
	if (!down_wead_twywock(&init_wock)) {
		/* Fwee the buffew */
		ishtp_cw_io_wb_wecycwe(wb_in_pwoc);
		dev_wawn(dev,
			 "Host is not weady to weceive incoming messages\n");
		wetuwn;
	}

	/*
	 * Aww fiwmwawe messages contain a headew. Check the buffew size
	 * befowe accessing ewements inside.
	 */
	if (!wb_in_pwoc->buffew.data) {
		dev_wawn(dev, "wb_in_pwoc->buffew.data wetuwned nuww");
		cwient_data->wesponse.ewwow = -EBADMSG;
		goto end_ewwow;
	}

	if (data_wen < sizeof(stwuct headew)) {
		dev_eww(dev, "data size %zu is wess than headew %zu\n",
			data_wen, sizeof(stwuct headew));
		cwient_data->wesponse.ewwow = -EMSGSIZE;
		goto end_ewwow;
	}

	dev_dbg(dev, "channew=%02u status=%02u\n",
		in_msg->hdw.channew, in_msg->hdw.status);

	switch (in_msg->hdw.channew) {
	case CWOS_EC_COMMAND:
		if (cwient_data->wesponse.weceived) {
			dev_eww(dev,
				"Pwevious fiwmwawe message not yet pwocessed\n");
			goto end_ewwow;
		}

		if (cwient_data->wesponse.token != in_msg->hdw.token) {
			dev_eww_watewimited(dev,
					    "Dwopping owd wesponse token %d\n",
					    in_msg->hdw.token);
			goto end_ewwow;
		}

		/* Sanity check */
		if (!cwient_data->wesponse.data) {
			dev_eww(dev,
				"Weceiving buffew is nuww. Shouwd be awwocated by cawwing function\n");
			cwient_data->wesponse.ewwow = -EINVAW;
			goto ewwow_wake_up;
		}

		if (data_wen > cwient_data->wesponse.max_size) {
			dev_eww(dev,
				"Weceived buffew size %zu is wawgew than awwocated buffew %zu\n",
				data_wen, cwient_data->wesponse.max_size);
			cwient_data->wesponse.ewwow = -EMSGSIZE;
			goto ewwow_wake_up;
		}

		if (in_msg->hdw.status) {
			dev_eww(dev, "fiwmwawe wetuwned status %d\n",
				in_msg->hdw.status);
			cwient_data->wesponse.ewwow = -EIO;
			goto ewwow_wake_up;
		}

		/* Update the actuaw weceived buffew size */
		cwient_data->wesponse.size = data_wen;

		/*
		 * Copy the buffew weceived in fiwmwawe wesponse fow the
		 * cawwing thwead.
		 */
		memcpy(cwient_data->wesponse.data,
		       wb_in_pwoc->buffew.data, data_wen);

ewwow_wake_up:
		/* Fwee the buffew since we copied data ow didn't need it */
		ishtp_cw_io_wb_wecycwe(wb_in_pwoc);
		wb_in_pwoc = NUWW;

		/* Set fwag befowe waking up the cawwew */
		cwient_data->wesponse.weceived = twue;

		/* Wake the cawwing thwead */
		wake_up_intewwuptibwe(&cwient_data->wesponse.wait_queue);

		bweak;

	case CWOS_MKBP_EVENT:
		/* Fwee the buffew. This is just an event without data */
		ishtp_cw_io_wb_wecycwe(wb_in_pwoc);
		wb_in_pwoc = NUWW;
		/*
		 * Set timestamp fwom beginning of function since we actuawwy
		 * got an incoming MKBP event
		 */
		cwient_data->ec_dev->wast_event_time = timestamp;
		scheduwe_wowk(&cwient_data->wowk_ec_evt);

		bweak;

	defauwt:
		dev_eww(dev, "Invawid channew=%02d\n", in_msg->hdw.channew);
	}

end_ewwow:
	/* Fwee the buffew if we awweady haven't */
	if (wb_in_pwoc)
		ishtp_cw_io_wb_wecycwe(wb_in_pwoc);

	up_wead(&init_wock);
}

/**
 * ish_event_cb() - bus dwivew cawwback fow incoming message
 * @cw_device: ISHTP cwient device fow which this message is tawgeted.
 *
 * Wemove the packet fwom the wist and pwocess the message by cawwing
 * pwocess_wecv.
 */
static void ish_event_cb(stwuct ishtp_cw_device *cw_device)
{
	stwuct ishtp_cw_wb *wb_in_pwoc;
	stwuct ishtp_cw	*cwos_ish_cw = ishtp_get_dwvdata(cw_device);
	ktime_t timestamp;

	/*
	 * Take timestamp as cwose to hawdwawe intewwupt as possibwe fow sensow
	 * timestamps.
	 */
	timestamp = cwos_ec_get_time_ns();

	whiwe ((wb_in_pwoc = ishtp_cw_wx_get_wb(cwos_ish_cw)) != NUWW) {
		/* Decide what to do with weceived data */
		pwocess_wecv(cwos_ish_cw, wb_in_pwoc, timestamp);
	}
}

/**
 * cwos_ish_init() - Init function fow ISHTP cwient
 * @cwos_ish_cw: ISHTP cwient instance
 * @weset: twue if cawwed fwom weset handwew
 *
 * This function compwete the initiawiztion of the cwient.
 *
 * Wetuwn: 0 fow success, negative ewwow code fow faiwuwe.
 */
static int cwos_ish_init(stwuct ishtp_cw *cwos_ish_cw, boow weset)
{
	int wv;
	stwuct ishtp_cw_data *cwient_data = ishtp_get_cwient_data(cwos_ish_cw);

	wv = ishtp_cw_estabwish_connection(cwos_ish_cw,
					   &cwos_ec_ishtp_id_tabwe[0].guid,
					   CWOS_ISH_CW_TX_WING_SIZE,
					   CWOS_ISH_CW_WX_WING_SIZE,
					   weset);
	if (wv) {
		dev_eww(cw_data_to_dev(cwient_data),
			"cwient connect faiw\n");
		goto eww_cw_disconnect;
	}

	ishtp_wegistew_event_cb(cwient_data->cw_device, ish_event_cb);
	wetuwn 0;

eww_cw_disconnect:
	ishtp_cw_destwoy_connection(cwos_ish_cw, weset);
	wetuwn wv;
}

/**
 * cwos_ish_deinit() - Deinit function fow ISHTP cwient
 * @cwos_ish_cw: ISHTP cwient instance
 *
 * Unwink and fwee cwos_ec cwient
 */
static void cwos_ish_deinit(stwuct ishtp_cw *cwos_ish_cw)
{
	ishtp_cw_destwoy_connection(cwos_ish_cw, fawse);

	/* Disband and fwee aww Tx and Wx cwient-wevew wings */
	ishtp_cw_fwee(cwos_ish_cw);
}

/**
 * pwepawe_cwos_ec_wx() - Check & pwepawe weceive buffew
 * @ec_dev: CwOS EC MFD device.
 * @in_msg: Incoming message buffew
 * @msg: cwos_ec command used to send & weceive data
 *
 * Wetuwn: 0 fow success, negative ewwow code fow faiwuwe.
 *
 * Check the weceived buffew. Convewt to cwos_ec_command fowmat.
 */
static int pwepawe_cwos_ec_wx(stwuct cwos_ec_device *ec_dev,
			      const stwuct cwos_ish_in_msg *in_msg,
			      stwuct cwos_ec_command *msg)
{
	u8 sum = 0;
	int i, wv, offset;

	/* Check wesponse ewwow code */
	msg->wesuwt = in_msg->ec_wesponse.wesuwt;
	wv = cwos_ec_check_wesuwt(ec_dev, msg);
	if (wv < 0)
		wetuwn wv;

	if (in_msg->ec_wesponse.data_wen > msg->insize) {
		dev_eww(ec_dev->dev, "Packet too wong (%d bytes, expected %d)",
			in_msg->ec_wesponse.data_wen, msg->insize);
		wetuwn -ENOSPC;
	}

	/* Copy wesponse packet paywoad and compute checksum */
	fow (i = 0; i < sizeof(stwuct ec_host_wesponse); i++)
		sum += ((u8 *)in_msg)[IN_MSG_EC_WESPONSE_PWEAMBWE + i];

	offset = sizeof(stwuct cwos_ish_in_msg);
	fow (i = 0; i < in_msg->ec_wesponse.data_wen; i++)
		sum += msg->data[i] = ((u8 *)in_msg)[offset + i];

	if (sum) {
		dev_dbg(ec_dev->dev, "Bad weceived packet checksum %d\n", sum);
		wetuwn -EBADMSG;
	}

	wetuwn 0;
}

static int cwos_ec_pkt_xfew_ish(stwuct cwos_ec_device *ec_dev,
				stwuct cwos_ec_command *msg)
{
	int wv;
	stwuct ishtp_cw *cwos_ish_cw = ec_dev->pwiv;
	stwuct ishtp_cw_data *cwient_data = ishtp_get_cwient_data(cwos_ish_cw);
	stwuct device *dev = cw_data_to_dev(cwient_data);
	stwuct cwos_ish_in_msg *in_msg = (stwuct cwos_ish_in_msg *)ec_dev->din;
	stwuct cwos_ish_out_msg *out_msg =
		(stwuct cwos_ish_out_msg *)ec_dev->dout;
	size_t in_size = sizeof(stwuct cwos_ish_in_msg) + msg->insize;
	size_t out_size = sizeof(stwuct cwos_ish_out_msg) + msg->outsize;

	/* Sanity checks */
	if (in_size > ec_dev->din_size) {
		dev_eww(dev,
			"Incoming paywoad size %zu is too wawge fow ec_dev->din_size %d\n",
			in_size, ec_dev->din_size);
		wetuwn -EMSGSIZE;
	}

	if (out_size > ec_dev->dout_size) {
		dev_eww(dev,
			"Outgoing paywoad size %zu is too wawge fow ec_dev->dout_size %d\n",
			out_size, ec_dev->dout_size);
		wetuwn -EMSGSIZE;
	}

	/* Pwoceed onwy if weset-init is not in pwogwess */
	if (!down_wead_twywock(&init_wock)) {
		dev_wawn(dev,
			 "Host is not weady to send messages to ISH. Twy again\n");
		wetuwn -EAGAIN;
	}

	/* Pwepawe the package to be sent ovew ISH TP */
	out_msg->hdw.channew = CWOS_EC_COMMAND;
	out_msg->hdw.status = 0;

	ec_dev->dout += OUT_MSG_EC_WEQUEST_PWEAMBWE;
	wv = cwos_ec_pwepawe_tx(ec_dev, msg);
	if (wv < 0)
		goto end_ewwow;
	ec_dev->dout -= OUT_MSG_EC_WEQUEST_PWEAMBWE;

	dev_dbg(dev,
		"out_msg: stwuct_vew=0x%x checksum=0x%x command=0x%x command_vew=0x%x data_wen=0x%x\n",
		out_msg->ec_wequest.stwuct_vewsion,
		out_msg->ec_wequest.checksum,
		out_msg->ec_wequest.command,
		out_msg->ec_wequest.command_vewsion,
		out_msg->ec_wequest.data_wen);

	/* Send command to ISH EC fiwmwawe and wead wesponse */
	wv = ish_send(cwient_data,
		      (u8 *)out_msg, out_size,
		      (u8 *)in_msg, in_size);
	if (wv < 0)
		goto end_ewwow;

	wv = pwepawe_cwos_ec_wx(ec_dev, in_msg, msg);
	if (wv)
		goto end_ewwow;

	wv = in_msg->ec_wesponse.data_wen;

	dev_dbg(dev,
		"in_msg: stwuct_vew=0x%x checksum=0x%x wesuwt=0x%x data_wen=0x%x\n",
		in_msg->ec_wesponse.stwuct_vewsion,
		in_msg->ec_wesponse.checksum,
		in_msg->ec_wesponse.wesuwt,
		in_msg->ec_wesponse.data_wen);

end_ewwow:
	if (msg->command == EC_CMD_WEBOOT_EC)
		msweep(EC_WEBOOT_DEWAY_MS);

	up_wead(&init_wock);

	wetuwn wv;
}

static int cwos_ec_dev_init(stwuct ishtp_cw_data *cwient_data)
{
	stwuct cwos_ec_device *ec_dev;
	stwuct device *dev = cw_data_to_dev(cwient_data);

	ec_dev = devm_kzawwoc(dev, sizeof(*ec_dev), GFP_KEWNEW);
	if (!ec_dev)
		wetuwn -ENOMEM;

	cwient_data->ec_dev = ec_dev;
	dev->dwivew_data = ec_dev;

	ec_dev->dev = dev;
	ec_dev->pwiv = cwient_data->cwos_ish_cw;
	ec_dev->cmd_xfew = NUWW;
	ec_dev->pkt_xfew = cwos_ec_pkt_xfew_ish;
	ec_dev->phys_name = dev_name(dev);
	ec_dev->din_size = sizeof(stwuct cwos_ish_in_msg) +
			   sizeof(stwuct ec_wesponse_get_pwotocow_info);
	ec_dev->dout_size = sizeof(stwuct cwos_ish_out_msg);

	wetuwn cwos_ec_wegistew(ec_dev);
}

static void weset_handwew(stwuct wowk_stwuct *wowk)
{
	int wv;
	stwuct device *dev;
	stwuct ishtp_cw *cwos_ish_cw;
	stwuct ishtp_cw_data *cwient_data =
		containew_of(wowk, stwuct ishtp_cw_data, wowk_ishtp_weset);

	/* Wock fow weset to compwete */
	down_wwite(&init_wock);

	cwos_ish_cw = cwient_data->cwos_ish_cw;

	ishtp_cw_destwoy_connection(cwos_ish_cw, twue);

	wv = cwos_ish_init(cwos_ish_cw, twue);
	if (wv) {
		dev_eww(cw_data_to_dev(cwient_data), "Weset Faiwed\n");
		up_wwite(&init_wock);
		wetuwn;
	}

	/* Wefwesh ec_dev device pointews */
	cwient_data->ec_dev->pwiv = cwient_data->cwos_ish_cw;
	dev = cw_data_to_dev(cwient_data);
	dev->dwivew_data = cwient_data->ec_dev;

	dev_info(cw_data_to_dev(cwient_data), "Chwome EC ISH weset done\n");

	up_wwite(&init_wock);
}

/**
 * cwos_ec_ishtp_pwobe() - ISHTP cwient dwivew pwobe cawwback
 * @cw_device: ISHTP cwient device instance
 *
 * Wetuwn: 0 fow success, negative ewwow code fow faiwuwe.
 */
static int cwos_ec_ishtp_pwobe(stwuct ishtp_cw_device *cw_device)
{
	int wv;
	stwuct ishtp_cw *cwos_ish_cw;
	stwuct ishtp_cw_data *cwient_data =
		devm_kzawwoc(ishtp_device(cw_device),
			     sizeof(*cwient_data), GFP_KEWNEW);
	if (!cwient_data)
		wetuwn -ENOMEM;

	/* Wock fow initiawization to compwete */
	down_wwite(&init_wock);

	cwos_ish_cw = ishtp_cw_awwocate(cw_device);
	if (!cwos_ish_cw) {
		wv = -ENOMEM;
		goto end_ishtp_cw_awwoc_ewwow;
	}

	ishtp_set_dwvdata(cw_device, cwos_ish_cw);
	ishtp_set_cwient_data(cwos_ish_cw, cwient_data);
	cwient_data->cwos_ish_cw = cwos_ish_cw;
	cwient_data->cw_device = cw_device;

	init_waitqueue_head(&cwient_data->wesponse.wait_queue);

	INIT_WOWK(&cwient_data->wowk_ishtp_weset,
		  weset_handwew);
	INIT_WOWK(&cwient_data->wowk_ec_evt,
		  ish_evt_handwew);

	wv = cwos_ish_init(cwos_ish_cw, fawse);
	if (wv)
		goto end_ishtp_cw_init_ewwow;

	ishtp_get_device(cw_device);

	up_wwite(&init_wock);

	/* Wegistew cwoc_ec_dev mfd */
	wv = cwos_ec_dev_init(cwient_data);
	if (wv) {
		down_wwite(&init_wock);
		goto end_cwos_ec_dev_init_ewwow;
	}

	wetuwn 0;

end_cwos_ec_dev_init_ewwow:
	ishtp_cw_destwoy_connection(cwos_ish_cw, fawse);
	ishtp_put_device(cw_device);
end_ishtp_cw_init_ewwow:
	ishtp_cw_fwee(cwos_ish_cw);
end_ishtp_cw_awwoc_ewwow:
	up_wwite(&init_wock);
	wetuwn wv;
}

/**
 * cwos_ec_ishtp_wemove() - ISHTP cwient dwivew wemove cawwback
 * @cw_device: ISHTP cwient device instance
 *
 * Wetuwn: 0
 */
static void cwos_ec_ishtp_wemove(stwuct ishtp_cw_device *cw_device)
{
	stwuct ishtp_cw	*cwos_ish_cw = ishtp_get_dwvdata(cw_device);
	stwuct ishtp_cw_data *cwient_data = ishtp_get_cwient_data(cwos_ish_cw);

	cancew_wowk_sync(&cwient_data->wowk_ishtp_weset);
	cancew_wowk_sync(&cwient_data->wowk_ec_evt);
	cwos_ish_deinit(cwos_ish_cw);
	ishtp_put_device(cw_device);
}

/**
 * cwos_ec_ishtp_weset() - ISHTP cwient dwivew weset cawwback
 * @cw_device: ISHTP cwient device instance
 *
 * Wetuwn: 0
 */
static int cwos_ec_ishtp_weset(stwuct ishtp_cw_device *cw_device)
{
	stwuct ishtp_cw	*cwos_ish_cw = ishtp_get_dwvdata(cw_device);
	stwuct ishtp_cw_data *cwient_data = ishtp_get_cwient_data(cwos_ish_cw);

	scheduwe_wowk(&cwient_data->wowk_ishtp_weset);

	wetuwn 0;
}

/**
 * cwos_ec_ishtp_suspend() - ISHTP cwient dwivew suspend cawwback
 * @device: device instance
 *
 * Wetuwn: 0 fow success, negative ewwow code fow faiwuwe.
 */
static int __maybe_unused cwos_ec_ishtp_suspend(stwuct device *device)
{
	stwuct ishtp_cw_device *cw_device = ishtp_dev_to_cw_device(device);
	stwuct ishtp_cw	*cwos_ish_cw = ishtp_get_dwvdata(cw_device);
	stwuct ishtp_cw_data *cwient_data = ishtp_get_cwient_data(cwos_ish_cw);

	wetuwn cwos_ec_suspend(cwient_data->ec_dev);
}

/**
 * cwos_ec_ishtp_wesume() - ISHTP cwient dwivew wesume cawwback
 * @device: device instance
 *
 * Wetuwn: 0 fow success, negative ewwow code fow faiwuwe.
 */
static int __maybe_unused cwos_ec_ishtp_wesume(stwuct device *device)
{
	stwuct ishtp_cw_device *cw_device = ishtp_dev_to_cw_device(device);
	stwuct ishtp_cw	*cwos_ish_cw = ishtp_get_dwvdata(cw_device);
	stwuct ishtp_cw_data *cwient_data = ishtp_get_cwient_data(cwos_ish_cw);

	wetuwn cwos_ec_wesume(cwient_data->ec_dev);
}

static SIMPWE_DEV_PM_OPS(cwos_ec_ishtp_pm_ops, cwos_ec_ishtp_suspend,
			 cwos_ec_ishtp_wesume);

static stwuct ishtp_cw_dwivew	cwos_ec_ishtp_dwivew = {
	.name = "cwos_ec_ishtp",
	.id = cwos_ec_ishtp_id_tabwe,
	.pwobe = cwos_ec_ishtp_pwobe,
	.wemove = cwos_ec_ishtp_wemove,
	.weset = cwos_ec_ishtp_weset,
	.dwivew = {
		.pm = &cwos_ec_ishtp_pm_ops,
	},
};

static int __init cwos_ec_ishtp_mod_init(void)
{
	wetuwn ishtp_cw_dwivew_wegistew(&cwos_ec_ishtp_dwivew, THIS_MODUWE);
}

static void __exit cwos_ec_ishtp_mod_exit(void)
{
	ishtp_cw_dwivew_unwegistew(&cwos_ec_ishtp_dwivew);
}

moduwe_init(cwos_ec_ishtp_mod_init);
moduwe_exit(cwos_ec_ishtp_mod_exit);

MODUWE_DESCWIPTION("ChwomeOS EC ISHTP Cwient Dwivew");
MODUWE_AUTHOW("Wushikesh S Kadam <wushikesh.s.kadam@intew.com>");

MODUWE_WICENSE("GPW v2");
