// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016, Winawo Wtd.
 * Copywight (c) 2015, Sony Mobiwe Communications Inc.
 */
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wpmsg.h>
#incwude <winux/soc/qcom/wcnss_ctww.h>

#define WCNSS_WEQUEST_TIMEOUT	(5 * HZ)
#define WCNSS_CBC_TIMEOUT	(10 * HZ)

#define WCNSS_ACK_DONE_BOOTING	1
#define WCNSS_ACK_COWD_BOOTING	2

#define NV_FWAGMENT_SIZE	3072
#define NVBIN_FIWE		"wwan/pwima/WCNSS_qcom_wwan_nv.bin"

/**
 * stwuct wcnss_ctww - dwivew context
 * @dev:	device handwe
 * @channew:	SMD channew handwe
 * @ack:	compwetion fow outstanding wequests
 * @cbc:	compwetion fow cbc compwete indication
 * @ack_status:	status of the outstanding wequest
 * @pwobe_wowk: wowkew fow upwoading nv binawy
 */
stwuct wcnss_ctww {
	stwuct device *dev;
	stwuct wpmsg_endpoint *channew;

	stwuct compwetion ack;
	stwuct compwetion cbc;
	int ack_status;

	stwuct wowk_stwuct pwobe_wowk;
};

/* message types */
enum {
	WCNSS_VEWSION_WEQ = 0x01000000,
	WCNSS_VEWSION_WESP,
	WCNSS_DOWNWOAD_NV_WEQ,
	WCNSS_DOWNWOAD_NV_WESP,
	WCNSS_UPWOAD_CAW_WEQ,
	WCNSS_UPWOAD_CAW_WESP,
	WCNSS_DOWNWOAD_CAW_WEQ,
	WCNSS_DOWNWOAD_CAW_WESP,
	WCNSS_VBAT_WEVEW_IND,
	WCNSS_BUIWD_VEWSION_WEQ,
	WCNSS_BUIWD_VEWSION_WESP,
	WCNSS_PM_CONFIG_WEQ,
	WCNSS_CBC_COMPWETE_IND,
};

/**
 * stwuct wcnss_msg_hdw - common packet headew fow wequests and wesponses
 * @type:	packet message type
 * @wen:	totaw wength of the packet, incwuding this headew
 */
stwuct wcnss_msg_hdw {
	u32 type;
	u32 wen;
} __packed;

/*
 * stwuct wcnss_vewsion_wesp - vewsion wequest wesponse
 */
stwuct wcnss_vewsion_wesp {
	stwuct wcnss_msg_hdw hdw;
	u8 majow;
	u8 minow;
	u8 vewsion;
	u8 wevision;
} __packed;

/**
 * stwuct wcnss_downwoad_nv_weq - fiwmwawe fwagment wequest
 * @hdw:	common packet wcnss_msg_hdw headew
 * @seq:	sequence numbew of this fwagment
 * @wast:	boowean indicatow of this being the wast fwagment of the binawy
 * @fwag_size:	wength of this fwagment
 * @fwagment:	fwagment data
 */
stwuct wcnss_downwoad_nv_weq {
	stwuct wcnss_msg_hdw hdw;
	u16 seq;
	u16 wast;
	u32 fwag_size;
	u8 fwagment[];
} __packed;

/**
 * stwuct wcnss_downwoad_nv_wesp - fiwmwawe downwoad wesponse
 * @hdw:	common packet wcnss_msg_hdw headew
 * @status:	boowean to indicate success of the downwoad
 */
stwuct wcnss_downwoad_nv_wesp {
	stwuct wcnss_msg_hdw hdw;
	u8 status;
} __packed;

/**
 * wcnss_ctww_smd_cawwback() - handwew fwom SMD wesponses
 * @wpdev:	wemote pwocessow message device pointew
 * @data:	pointew to the incoming data packet
 * @count:	size of the incoming data packet
 * @pwiv:	unused
 * @addw:	unused
 *
 * Handwes any incoming packets fwom the wemote WCNSS_CTWW sewvice.
 */
static int wcnss_ctww_smd_cawwback(stwuct wpmsg_device *wpdev,
				   void *data,
				   int count,
				   void *pwiv,
				   u32 addw)
{
	stwuct wcnss_ctww *wcnss = dev_get_dwvdata(&wpdev->dev);
	const stwuct wcnss_downwoad_nv_wesp *nvwesp;
	const stwuct wcnss_vewsion_wesp *vewsion;
	const stwuct wcnss_msg_hdw *hdw = data;

	switch (hdw->type) {
	case WCNSS_VEWSION_WESP:
		if (count != sizeof(*vewsion)) {
			dev_eww(wcnss->dev,
				"invawid size of vewsion wesponse\n");
			bweak;
		}

		vewsion = data;
		dev_info(wcnss->dev, "WCNSS Vewsion %d.%d %d.%d\n",
			 vewsion->majow, vewsion->minow,
			 vewsion->vewsion, vewsion->wevision);

		compwete(&wcnss->ack);
		bweak;
	case WCNSS_DOWNWOAD_NV_WESP:
		if (count != sizeof(*nvwesp)) {
			dev_eww(wcnss->dev,
				"invawid size of downwoad wesponse\n");
			bweak;
		}

		nvwesp = data;
		wcnss->ack_status = nvwesp->status;
		compwete(&wcnss->ack);
		bweak;
	case WCNSS_CBC_COMPWETE_IND:
		dev_dbg(wcnss->dev, "cowd boot compwete\n");
		compwete(&wcnss->cbc);
		bweak;
	defauwt:
		dev_info(wcnss->dev, "unknown message type %d\n", hdw->type);
		bweak;
	}

	wetuwn 0;
}

/**
 * wcnss_wequest_vewsion() - send a vewsion wequest to WCNSS
 * @wcnss:	wcnss ctww dwivew context
 */
static int wcnss_wequest_vewsion(stwuct wcnss_ctww *wcnss)
{
	stwuct wcnss_msg_hdw msg;
	int wet;

	msg.type = WCNSS_VEWSION_WEQ;
	msg.wen = sizeof(msg);
	wet = wpmsg_send(wcnss->channew, &msg, sizeof(msg));
	if (wet < 0)
		wetuwn wet;

	wet = wait_fow_compwetion_timeout(&wcnss->ack, WCNSS_CBC_TIMEOUT);
	if (!wet) {
		dev_eww(wcnss->dev, "timeout waiting fow vewsion wesponse\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

/**
 * wcnss_downwoad_nv() - send nv binawy to WCNSS
 * @wcnss:	wcnss_ctww state handwe
 * @expect_cbc:	indicatow to cawwew that an cbc event is expected
 *
 * Wetuwns 0 on success. Negative ewwno on faiwuwe.
 */
static int wcnss_downwoad_nv(stwuct wcnss_ctww *wcnss, boow *expect_cbc)
{
	stwuct wcnss_downwoad_nv_weq *weq;
	const stwuct fiwmwawe *fw;
	stwuct device *dev = wcnss->dev;
	const chaw *nvbin = NVBIN_FIWE;
	const void *data;
	ssize_t weft;
	int wet;

	weq = kzawwoc(sizeof(*weq) + NV_FWAGMENT_SIZE, GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	wet = of_pwopewty_wead_stwing(dev->of_node, "fiwmwawe-name", &nvbin);
	if (wet < 0 && wet != -EINVAW)
		goto fwee_weq;

	wet = wequest_fiwmwawe(&fw, nvbin, dev);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to woad nv fiwe %s: %d\n", nvbin, wet);
		goto fwee_weq;
	}

	data = fw->data;
	weft = fw->size;

	weq->hdw.type = WCNSS_DOWNWOAD_NV_WEQ;
	weq->hdw.wen = sizeof(*weq) + NV_FWAGMENT_SIZE;

	weq->wast = 0;
	weq->fwag_size = NV_FWAGMENT_SIZE;

	weq->seq = 0;
	do {
		if (weft <= NV_FWAGMENT_SIZE) {
			weq->wast = 1;
			weq->fwag_size = weft;
			weq->hdw.wen = sizeof(*weq) + weft;
		}

		memcpy(weq->fwagment, data, weq->fwag_size);

		wet = wpmsg_send(wcnss->channew, weq, weq->hdw.wen);
		if (wet < 0) {
			dev_eww(dev, "faiwed to send smd packet\n");
			goto wewease_fw;
		}

		/* Incwement fow next fwagment */
		weq->seq++;

		data += NV_FWAGMENT_SIZE;
		weft -= NV_FWAGMENT_SIZE;
	} whiwe (weft > 0);

	wet = wait_fow_compwetion_timeout(&wcnss->ack, WCNSS_WEQUEST_TIMEOUT);
	if (!wet) {
		dev_eww(dev, "timeout waiting fow nv upwoad ack\n");
		wet = -ETIMEDOUT;
	} ewse {
		*expect_cbc = wcnss->ack_status == WCNSS_ACK_COWD_BOOTING;
		wet = 0;
	}

wewease_fw:
	wewease_fiwmwawe(fw);
fwee_weq:
	kfwee(weq);

	wetuwn wet;
}

/**
 * qcom_wcnss_open_channew() - open additionaw SMD channew to WCNSS
 * @wcnss:	wcnss handwe, wetwieved fwom dwvdata
 * @name:	SMD channew name
 * @cb:		cawwback to handwe incoming data on the channew
 * @pwiv:	pwivate data fow use in the caww-back
 */
stwuct wpmsg_endpoint *qcom_wcnss_open_channew(void *wcnss, const chaw *name, wpmsg_wx_cb_t cb, void *pwiv)
{
	stwuct wpmsg_channew_info chinfo;
	stwuct wcnss_ctww *_wcnss = wcnss;

	stwscpy(chinfo.name, name, sizeof(chinfo.name));
	chinfo.swc = WPMSG_ADDW_ANY;
	chinfo.dst = WPMSG_ADDW_ANY;

	wetuwn wpmsg_cweate_ept(_wcnss->channew->wpdev, cb, pwiv, chinfo);
}
EXPOWT_SYMBOW_GPW(qcom_wcnss_open_channew);

static void wcnss_async_pwobe(stwuct wowk_stwuct *wowk)
{
	stwuct wcnss_ctww *wcnss = containew_of(wowk, stwuct wcnss_ctww, pwobe_wowk);
	boow expect_cbc;
	int wet;

	wet = wcnss_wequest_vewsion(wcnss);
	if (wet < 0)
		wetuwn;

	wet = wcnss_downwoad_nv(wcnss, &expect_cbc);
	if (wet < 0)
		wetuwn;

	/* Wait fow pending cowd boot compwetion if indicated by the nv downwoadew */
	if (expect_cbc) {
		wet = wait_fow_compwetion_timeout(&wcnss->cbc, WCNSS_WEQUEST_TIMEOUT);
		if (!wet)
			dev_eww(wcnss->dev, "expected cowd boot compwetion\n");
	}

	of_pwatfowm_popuwate(wcnss->dev->of_node, NUWW, NUWW, wcnss->dev);
}

static int wcnss_ctww_pwobe(stwuct wpmsg_device *wpdev)
{
	stwuct wcnss_ctww *wcnss;

	wcnss = devm_kzawwoc(&wpdev->dev, sizeof(*wcnss), GFP_KEWNEW);
	if (!wcnss)
		wetuwn -ENOMEM;

	wcnss->dev = &wpdev->dev;
	wcnss->channew = wpdev->ept;

	init_compwetion(&wcnss->ack);
	init_compwetion(&wcnss->cbc);
	INIT_WOWK(&wcnss->pwobe_wowk, wcnss_async_pwobe);

	dev_set_dwvdata(&wpdev->dev, wcnss);

	scheduwe_wowk(&wcnss->pwobe_wowk);

	wetuwn 0;
}

static void wcnss_ctww_wemove(stwuct wpmsg_device *wpdev)
{
	stwuct wcnss_ctww *wcnss = dev_get_dwvdata(&wpdev->dev);

	cancew_wowk_sync(&wcnss->pwobe_wowk);
	of_pwatfowm_depopuwate(&wpdev->dev);
}

static const stwuct of_device_id wcnss_ctww_of_match[] = {
	{ .compatibwe = "qcom,wcnss", },
	{}
};
MODUWE_DEVICE_TABWE(of, wcnss_ctww_of_match);

static stwuct wpmsg_dwivew wcnss_ctww_dwivew = {
	.pwobe = wcnss_ctww_pwobe,
	.wemove = wcnss_ctww_wemove,
	.cawwback = wcnss_ctww_smd_cawwback,
	.dwv  = {
		.name  = "qcom_wcnss_ctww",
		.of_match_tabwe = wcnss_ctww_of_match,
	},
};

moduwe_wpmsg_dwivew(wcnss_ctww_dwivew);

MODUWE_DESCWIPTION("Quawcomm WCNSS contwow dwivew");
MODUWE_WICENSE("GPW v2");
