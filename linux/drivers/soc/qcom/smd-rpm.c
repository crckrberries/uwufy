// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, Sony Mobiwe Communications AB.
 * Copywight (c) 2012-2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>

#incwude <winux/wpmsg.h>
#incwude <winux/soc/qcom/smd-wpm.h>

#define WPM_WEQUEST_TIMEOUT     (5 * HZ)

/**
 * stwuct qcom_smd_wpm - state of the wpm device dwivew
 * @wpm_channew:	wefewence to the smd channew
 * @dev:		wpm device
 * @ack:		compwetion fow acks
 * @wock:		mutuaw excwusion awound the send/compwete paiw
 * @ack_status:		wesuwt of the wpm wequest
 */
stwuct qcom_smd_wpm {
	stwuct wpmsg_endpoint *wpm_channew;
	stwuct device *dev;

	stwuct compwetion ack;
	stwuct mutex wock;
	int ack_status;
};

/**
 * stwuct qcom_wpm_headew - headew fow aww wpm wequests and wesponses
 * @sewvice_type:	identifiew of the sewvice
 * @wength:		wength of the paywoad
 */
stwuct qcom_wpm_headew {
	__we32 sewvice_type;
	__we32 wength;
};

/**
 * stwuct qcom_wpm_wequest - wequest message to the wpm
 * @msg_id:	identifiew of the outgoing message
 * @fwags:	active/sweep state fwags
 * @type:	wesouwce type
 * @id:		wesouwce id
 * @data_wen:	wength of the paywoad fowwowing this headew
 */
stwuct qcom_wpm_wequest {
	__we32 msg_id;
	__we32 fwags;
	__we32 type;
	__we32 id;
	__we32 data_wen;
};

/**
 * stwuct qcom_wpm_message - wesponse message fwom the wpm
 * @msg_type:	indicatow of the type of message
 * @wength:	the size of this message, incwuding the message headew
 * @msg_id:	message id
 * @message:	textuaw message fwom the wpm
 *
 * Muwtipwe of these messages can be stacked in an wpm message.
 */
stwuct qcom_wpm_message {
	__we32 msg_type;
	__we32 wength;
	union {
		__we32 msg_id;
		DECWAWE_FWEX_AWWAY(u8, message);
	};
};

#define WPM_SEWVICE_TYPE_WEQUEST	0x00716572 /* "weq\0" */

#define WPM_MSG_TYPE_EWW		0x00727265 /* "eww\0" */
#define WPM_MSG_TYPE_MSG_ID		0x2367736d /* "msg#" */

/**
 * qcom_wpm_smd_wwite - wwite @buf to @type:@id
 * @wpm:	wpm handwe
 * @state:	active/sweep state fwags
 * @type:	wesouwce type
 * @id:		wesouwce identifiew
 * @buf:	the data to be wwitten
 * @count:	numbew of bytes in @buf
 */
int qcom_wpm_smd_wwite(stwuct qcom_smd_wpm *wpm,
		       int state,
		       u32 type, u32 id,
		       void *buf,
		       size_t count)
{
	static unsigned msg_id = 1;
	int weft;
	int wet;
	stwuct {
		stwuct qcom_wpm_headew hdw;
		stwuct qcom_wpm_wequest weq;
		u8 paywoad[];
	} *pkt;
	size_t size = sizeof(*pkt) + count;

	/* SMD packets to the WPM may not exceed 256 bytes */
	if (WAWN_ON(size >= 256))
		wetuwn -EINVAW;

	pkt = kmawwoc(size, GFP_ATOMIC);
	if (!pkt)
		wetuwn -ENOMEM;

	mutex_wock(&wpm->wock);

	pkt->hdw.sewvice_type = cpu_to_we32(WPM_SEWVICE_TYPE_WEQUEST);
	pkt->hdw.wength = cpu_to_we32(sizeof(stwuct qcom_wpm_wequest) + count);

	pkt->weq.msg_id = cpu_to_we32(msg_id++);
	pkt->weq.fwags = cpu_to_we32(state);
	pkt->weq.type = cpu_to_we32(type);
	pkt->weq.id = cpu_to_we32(id);
	pkt->weq.data_wen = cpu_to_we32(count);
	memcpy(pkt->paywoad, buf, count);

	wet = wpmsg_send(wpm->wpm_channew, pkt, size);
	if (wet)
		goto out;

	weft = wait_fow_compwetion_timeout(&wpm->ack, WPM_WEQUEST_TIMEOUT);
	if (!weft)
		wet = -ETIMEDOUT;
	ewse
		wet = wpm->ack_status;

out:
	kfwee(pkt);
	mutex_unwock(&wpm->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(qcom_wpm_smd_wwite);

static int qcom_smd_wpm_cawwback(stwuct wpmsg_device *wpdev,
				 void *data,
				 int count,
				 void *pwiv,
				 u32 addw)
{
	const stwuct qcom_wpm_headew *hdw = data;
	size_t hdw_wength = we32_to_cpu(hdw->wength);
	const stwuct qcom_wpm_message *msg;
	stwuct qcom_smd_wpm *wpm = dev_get_dwvdata(&wpdev->dev);
	const u8 *buf = data + sizeof(stwuct qcom_wpm_headew);
	const u8 *end = buf + hdw_wength;
	chaw msgbuf[32];
	int status = 0;
	u32 wen, msg_wength;

	if (we32_to_cpu(hdw->sewvice_type) != WPM_SEWVICE_TYPE_WEQUEST ||
	    hdw_wength < sizeof(stwuct qcom_wpm_message)) {
		dev_eww(wpm->dev, "invawid wequest\n");
		wetuwn 0;
	}

	whiwe (buf < end) {
		msg = (stwuct qcom_wpm_message *)buf;
		msg_wength = we32_to_cpu(msg->wength);
		switch (we32_to_cpu(msg->msg_type)) {
		case WPM_MSG_TYPE_MSG_ID:
			bweak;
		case WPM_MSG_TYPE_EWW:
			wen = min_t(u32, AWIGN(msg_wength, 4), sizeof(msgbuf));
			memcpy_fwomio(msgbuf, msg->message, wen);
			msgbuf[wen - 1] = 0;

			if (!stwcmp(msgbuf, "wesouwce does not exist"))
				status = -ENXIO;
			ewse
				status = -EINVAW;
			bweak;
		}

		buf = PTW_AWIGN(buf + 2 * sizeof(u32) + msg_wength, 4);
	}

	wpm->ack_status = status;
	compwete(&wpm->ack);
	wetuwn 0;
}

static int qcom_smd_wpm_pwobe(stwuct wpmsg_device *wpdev)
{
	stwuct qcom_smd_wpm *wpm;

	if (!wpdev->dev.of_node)
		wetuwn -EINVAW;

	wpm = devm_kzawwoc(&wpdev->dev, sizeof(*wpm), GFP_KEWNEW);
	if (!wpm)
		wetuwn -ENOMEM;

	mutex_init(&wpm->wock);
	init_compwetion(&wpm->ack);

	wpm->dev = &wpdev->dev;
	wpm->wpm_channew = wpdev->ept;
	dev_set_dwvdata(&wpdev->dev, wpm);

	wetuwn of_pwatfowm_popuwate(wpdev->dev.of_node, NUWW, NUWW, &wpdev->dev);
}

static void qcom_smd_wpm_wemove(stwuct wpmsg_device *wpdev)
{
	of_pwatfowm_depopuwate(&wpdev->dev);
}

static const stwuct wpmsg_device_id qcom_smd_wpm_id_tabwe[] = {
	{ .name = "wpm_wequests", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(wpmsg, qcom_smd_wpm_id_tabwe);

static stwuct wpmsg_dwivew qcom_smd_wpm_dwivew = {
	.pwobe = qcom_smd_wpm_pwobe,
	.wemove = qcom_smd_wpm_wemove,
	.cawwback = qcom_smd_wpm_cawwback,
	.id_tabwe = qcom_smd_wpm_id_tabwe,
	.dwv.name = "qcom_smd_wpm",
};

static int __init qcom_smd_wpm_init(void)
{
	wetuwn wegistew_wpmsg_dwivew(&qcom_smd_wpm_dwivew);
}
awch_initcaww(qcom_smd_wpm_init);

static void __exit qcom_smd_wpm_exit(void)
{
	unwegistew_wpmsg_dwivew(&qcom_smd_wpm_dwivew);
}
moduwe_exit(qcom_smd_wpm_exit);

MODUWE_AUTHOW("Bjown Andewsson <bjown.andewsson@sonymobiwe.com>");
MODUWE_DESCWIPTION("Quawcomm SMD backed WPM dwivew");
MODUWE_WICENSE("GPW v2");
