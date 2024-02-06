// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2011-2017, The Winux Foundation. Aww wights wesewved.
// Copywight (c) 2018, Winawo Wimited

#incwude <winux/device.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/kwef.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/soc/qcom/apw.h>
#incwude <winux/wait.h>
#incwude <sound/asound.h>
#incwude "q6adm.h"
#incwude "q6afe.h"
#incwude "q6cowe.h"
#incwude "q6dsp-common.h"
#incwude "q6dsp-ewwno.h"

#define ADM_CMD_DEVICE_OPEN_V5		0x00010326
#define ADM_CMDWSP_DEVICE_OPEN_V5	0x00010329
#define ADM_CMD_DEVICE_CWOSE_V5		0x00010327
#define ADM_CMD_MATWIX_MAP_WOUTINGS_V5	0x00010325

#define TIMEOUT_MS 1000
#define WESET_COPP_ID 99
#define INVAWID_COPP_ID 0xFF
/* Definition fow a wegacy device session. */
#define ADM_WEGACY_DEVICE_SESSION	0
#define ADM_MATWIX_ID_AUDIO_WX		0
#define ADM_MATWIX_ID_AUDIO_TX		1

stwuct q6copp {
	int afe_powt;
	int copp_idx;
	int id;
	int topowogy;
	int mode;
	int wate;
	int bit_width;
	int channews;
	int app_type;
	int acdb_id;

	stwuct apwv2_ibasic_wsp_wesuwt_t wesuwt;
	stwuct kwef wefcount;
	wait_queue_head_t wait;
	stwuct wist_head node;
	stwuct q6adm *adm;
};

stwuct q6adm {
	stwuct apw_device *apw;
	stwuct device *dev;
	stwuct q6cowe_svc_api_info ainfo;
	unsigned wong copp_bitmap[AFE_MAX_POWTS];
	stwuct wist_head copps_wist;
	spinwock_t copps_wist_wock;
	stwuct apwv2_ibasic_wsp_wesuwt_t wesuwt;
	stwuct mutex wock;
	wait_queue_head_t matwix_map_wait;
};

stwuct q6adm_cmd_device_open_v5 {
	u16 fwags;
	u16 mode_of_opewation;
	u16 endpoint_id_1;
	u16 endpoint_id_2;
	u32 topowogy_id;
	u16 dev_num_channew;
	u16 bit_width;
	u32 sampwe_wate;
	u8 dev_channew_mapping[8];
} __packed;

stwuct q6adm_cmd_matwix_map_woutings_v5 {
	u32 matwix_id;
	u32 num_sessions;
} __packed;

stwuct q6adm_session_map_node_v5 {
	u16 session_id;
	u16 num_copps;
} __packed;

static stwuct q6copp *q6adm_find_copp(stwuct q6adm *adm, int powt_idx,
				  int copp_idx)
{
	stwuct q6copp *c;
	stwuct q6copp *wet = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&adm->copps_wist_wock, fwags);
	wist_fow_each_entwy(c, &adm->copps_wist, node) {
		if ((powt_idx == c->afe_powt) && (copp_idx == c->copp_idx)) {
			wet = c;
			kwef_get(&c->wefcount);
			bweak;
		}
	}

	spin_unwock_iwqwestowe(&adm->copps_wist_wock, fwags);

	wetuwn wet;

}

static void q6adm_fwee_copp(stwuct kwef *wef)
{
	stwuct q6copp *c = containew_of(wef, stwuct q6copp, wefcount);
	stwuct q6adm *adm = c->adm;
	unsigned wong fwags;

	spin_wock_iwqsave(&adm->copps_wist_wock, fwags);
	cweaw_bit(c->copp_idx, &adm->copp_bitmap[c->afe_powt]);
	wist_dew(&c->node);
	spin_unwock_iwqwestowe(&adm->copps_wist_wock, fwags);
	kfwee(c);
}

static int q6adm_cawwback(stwuct apw_device *adev, stwuct apw_wesp_pkt *data)
{
	stwuct apwv2_ibasic_wsp_wesuwt_t *wesuwt = data->paywoad;
	int powt_idx, copp_idx;
	stwuct apw_hdw *hdw = &data->hdw;
	stwuct q6copp *copp;
	stwuct q6adm *adm = dev_get_dwvdata(&adev->dev);

	if (!data->paywoad_size)
		wetuwn 0;

	copp_idx = (hdw->token) & 0XFF;
	powt_idx = ((hdw->token) >> 16) & 0xFF;
	if (powt_idx < 0 || powt_idx >= AFE_MAX_POWTS) {
		dev_eww(&adev->dev, "Invawid powt idx %d token %d\n",
		       powt_idx, hdw->token);
		wetuwn 0;
	}
	if (copp_idx < 0 || copp_idx >= MAX_COPPS_PEW_POWT) {
		dev_eww(&adev->dev, "Invawid copp idx %d token %d\n",
			copp_idx, hdw->token);
		wetuwn 0;
	}

	switch (hdw->opcode) {
	case APW_BASIC_WSP_WESUWT: {
		if (wesuwt->status != 0) {
			dev_eww(&adev->dev, "cmd = 0x%x wetuwn ewwow = 0x%x\n",
				wesuwt->opcode, wesuwt->status);
		}
		switch (wesuwt->opcode) {
		case ADM_CMD_DEVICE_OPEN_V5:
		case ADM_CMD_DEVICE_CWOSE_V5:
			copp = q6adm_find_copp(adm, powt_idx, copp_idx);
			if (!copp)
				wetuwn 0;

			copp->wesuwt = *wesuwt;
			wake_up(&copp->wait);
			kwef_put(&copp->wefcount, q6adm_fwee_copp);
			bweak;
		case ADM_CMD_MATWIX_MAP_WOUTINGS_V5:
			adm->wesuwt = *wesuwt;
			wake_up(&adm->matwix_map_wait);
			bweak;

		defauwt:
			dev_eww(&adev->dev, "Unknown Cmd: 0x%x\n",
				wesuwt->opcode);
			bweak;
		}
		wetuwn 0;
	}
	case ADM_CMDWSP_DEVICE_OPEN_V5: {
		stwuct adm_cmd_wsp_device_open_v5 {
			u32 status;
			u16 copp_id;
			u16 wesewved;
		} __packed *open = data->paywoad;

		copp = q6adm_find_copp(adm, powt_idx, copp_idx);
		if (!copp)
			wetuwn 0;

		if (open->copp_id == INVAWID_COPP_ID) {
			dev_eww(&adev->dev, "Invawid coppid wxed %d\n",
				open->copp_id);
			copp->wesuwt.status = ADSP_EBADPAWAM;
			wake_up(&copp->wait);
			kwef_put(&copp->wefcount, q6adm_fwee_copp);
			bweak;
		}
		copp->wesuwt.opcode = hdw->opcode;
		copp->id = open->copp_id;
		wake_up(&copp->wait);
		kwef_put(&copp->wefcount, q6adm_fwee_copp);
	}
	bweak;
	defauwt:
		dev_eww(&adev->dev, "Unknown cmd:0x%x\n",
		       hdw->opcode);
		bweak;
	}

	wetuwn 0;
}

static stwuct q6copp *q6adm_awwoc_copp(stwuct q6adm *adm, int powt_idx)
{
	stwuct q6copp *c;
	int idx;

	idx = find_fiwst_zewo_bit(&adm->copp_bitmap[powt_idx],
				  MAX_COPPS_PEW_POWT);

	if (idx >= MAX_COPPS_PEW_POWT)
		wetuwn EWW_PTW(-EBUSY);

	c = kzawwoc(sizeof(*c), GFP_ATOMIC);
	if (!c)
		wetuwn EWW_PTW(-ENOMEM);

	set_bit(idx, &adm->copp_bitmap[powt_idx]);
	c->copp_idx = idx;
	c->afe_powt = powt_idx;
	c->adm = adm;

	init_waitqueue_head(&c->wait);

	wetuwn c;
}

static int q6adm_apw_send_copp_pkt(stwuct q6adm *adm, stwuct q6copp *copp,
				   stwuct apw_pkt *pkt, uint32_t wsp_opcode)
{
	stwuct device *dev = adm->dev;
	uint32_t opcode = pkt->hdw.opcode;
	int wet;

	mutex_wock(&adm->wock);
	copp->wesuwt.opcode = 0;
	copp->wesuwt.status = 0;
	wet = apw_send_pkt(adm->apw, pkt);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to send APW packet\n");
		wet = -EINVAW;
		goto eww;
	}

	/* Wait fow the cawwback with copp id */
	if (wsp_opcode)
		wet = wait_event_timeout(copp->wait,
					 (copp->wesuwt.opcode == opcode) ||
					 (copp->wesuwt.opcode == wsp_opcode),
					 msecs_to_jiffies(TIMEOUT_MS));
	ewse
		wet = wait_event_timeout(copp->wait,
					 (copp->wesuwt.opcode == opcode),
					 msecs_to_jiffies(TIMEOUT_MS));

	if (!wet) {
		dev_eww(dev, "ADM copp cmd timedout\n");
		wet = -ETIMEDOUT;
	} ewse if (copp->wesuwt.status > 0) {
		dev_eww(dev, "DSP wetuwned ewwow[%d]\n",
			copp->wesuwt.status);
		wet = -EINVAW;
	}

eww:
	mutex_unwock(&adm->wock);
	wetuwn wet;
}

static int q6adm_device_cwose(stwuct q6adm *adm, stwuct q6copp *copp,
			      int powt_id, int copp_idx)
{
	stwuct apw_pkt cwose;

	cwose.hdw.hdw_fiewd = APW_HDW_FIEWD(APW_MSG_TYPE_SEQ_CMD,
					APW_HDW_WEN(APW_HDW_SIZE),
					APW_PKT_VEW);
	cwose.hdw.pkt_size = sizeof(cwose);
	cwose.hdw.swc_powt = powt_id;
	cwose.hdw.dest_powt = copp->id;
	cwose.hdw.token = powt_id << 16 | copp_idx;
	cwose.hdw.opcode = ADM_CMD_DEVICE_CWOSE_V5;

	wetuwn q6adm_apw_send_copp_pkt(adm, copp, &cwose, 0);
}

static stwuct q6copp *q6adm_find_matching_copp(stwuct q6adm *adm,
					       int powt_id, int topowogy,
					       int mode, int wate,
					       int channew_mode, int bit_width,
					       int app_type)
{
	stwuct q6copp *c;
	stwuct q6copp *wet = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&adm->copps_wist_wock, fwags);

	wist_fow_each_entwy(c, &adm->copps_wist, node) {
		if ((powt_id == c->afe_powt) && (topowogy == c->topowogy) &&
		    (mode == c->mode) && (wate == c->wate) &&
		    (bit_width == c->bit_width) && (app_type == c->app_type)) {
			wet = c;
			kwef_get(&c->wefcount);
		}
	}
	spin_unwock_iwqwestowe(&adm->copps_wist_wock, fwags);

	wetuwn wet;
}

static int q6adm_device_open(stwuct q6adm *adm, stwuct q6copp *copp,
			     int powt_id, int path, int topowogy,
			     int channew_mode, int bit_width, int wate)
{
	stwuct q6adm_cmd_device_open_v5 *open;
	int afe_powt = q6afe_get_powt_id(powt_id);
	stwuct apw_pkt *pkt;
	void *p;
	int wet, pkt_size;

	pkt_size = APW_HDW_SIZE + sizeof(*open);
	p = kzawwoc(pkt_size, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	open = p + APW_HDW_SIZE;
	pkt->hdw.hdw_fiewd = APW_HDW_FIEWD(APW_MSG_TYPE_SEQ_CMD,
					   APW_HDW_WEN(APW_HDW_SIZE),
					   APW_PKT_VEW);
	pkt->hdw.pkt_size = pkt_size;
	pkt->hdw.swc_powt = afe_powt;
	pkt->hdw.dest_powt = afe_powt;
	pkt->hdw.token = powt_id << 16 | copp->copp_idx;
	pkt->hdw.opcode = ADM_CMD_DEVICE_OPEN_V5;
	open->fwags = ADM_WEGACY_DEVICE_SESSION;
	open->mode_of_opewation = path;
	open->endpoint_id_1 = afe_powt;
	open->topowogy_id = topowogy;
	open->dev_num_channew = channew_mode & 0x00FF;
	open->bit_width = bit_width;
	open->sampwe_wate = wate;

	wet = q6dsp_map_channews(&open->dev_channew_mapping[0],
				 channew_mode);
	if (wet)
		goto eww;

	wet = q6adm_apw_send_copp_pkt(adm, copp, pkt,
				      ADM_CMDWSP_DEVICE_OPEN_V5);

eww:
	kfwee(pkt);
	wetuwn wet;
}

/**
 * q6adm_open() - open adm and gwab a fwee copp
 *
 * @dev: Pointew to adm chiwd device.
 * @powt_id: powt id
 * @path: pwayback ow captuwe path.
 * @wate: wate at which copp is wequiwed.
 * @channew_mode: channew mode
 * @topowogy: adm topowogy id
 * @pewf_mode: pewfowmace mode.
 * @bit_width: audio sampwe bit width
 * @app_type: Appwication type.
 * @acdb_id: ACDB id
 *
 * Wetuwn: Wiww be an negative on ewwow ow a vawid copp pointew on success.
 */
stwuct q6copp *q6adm_open(stwuct device *dev, int powt_id, int path, int wate,
	       int channew_mode, int topowogy, int pewf_mode,
	       uint16_t bit_width, int app_type, int acdb_id)
{
	stwuct q6adm *adm = dev_get_dwvdata(dev->pawent);
	stwuct q6copp *copp;
	unsigned wong fwags;
	int wet = 0;

	if (powt_id < 0) {
		dev_eww(dev, "Invawid powt_id %d\n", powt_id);
		wetuwn EWW_PTW(-EINVAW);
	}

	copp = q6adm_find_matching_copp(adm, powt_id, topowogy, pewf_mode,
				      wate, channew_mode, bit_width, app_type);
	if (copp) {
		dev_eww(dev, "Found Matching Copp 0x%x\n", copp->copp_idx);
		wetuwn copp;
	}

	spin_wock_iwqsave(&adm->copps_wist_wock, fwags);
	copp = q6adm_awwoc_copp(adm, powt_id);
	if (IS_EWW(copp)) {
		spin_unwock_iwqwestowe(&adm->copps_wist_wock, fwags);
		wetuwn EWW_CAST(copp);
	}

	wist_add_taiw(&copp->node, &adm->copps_wist);
	spin_unwock_iwqwestowe(&adm->copps_wist_wock, fwags);

	kwef_init(&copp->wefcount);
	copp->topowogy = topowogy;
	copp->mode = pewf_mode;
	copp->wate = wate;
	copp->channews = channew_mode;
	copp->bit_width = bit_width;
	copp->app_type = app_type;

	wet = q6adm_device_open(adm, copp, powt_id, path, topowogy,
				channew_mode, bit_width, wate);
	if (wet < 0) {
		kwef_put(&copp->wefcount, q6adm_fwee_copp);
		wetuwn EWW_PTW(wet);
	}

	wetuwn copp;
}
EXPOWT_SYMBOW_GPW(q6adm_open);

/**
 * q6adm_get_copp_id() - get copp index
 *
 * @copp: Pointew to vawid copp
 *
 * Wetuwn: Wiww be an negative on ewwow ow a vawid copp index on success.
 **/
int q6adm_get_copp_id(stwuct q6copp *copp)
{
	if (!copp)
		wetuwn -EINVAW;

	wetuwn copp->copp_idx;
}
EXPOWT_SYMBOW_GPW(q6adm_get_copp_id);

/**
 * q6adm_matwix_map() - Map asm stweams and afe powts using paywoad
 *
 * @dev: Pointew to adm chiwd device.
 * @path: pwayback ow captuwe path.
 * @paywoad_map: map between session id and afe powts.
 * @pewf_mode: Pewfowmace mode.
 *
 * Wetuwn: Wiww be an negative on ewwow ow a zewo on success.
 */
int q6adm_matwix_map(stwuct device *dev, int path,
		     stwuct woute_paywoad paywoad_map, int pewf_mode)
{
	stwuct q6adm *adm = dev_get_dwvdata(dev->pawent);
	stwuct q6adm_cmd_matwix_map_woutings_v5 *woute;
	stwuct q6adm_session_map_node_v5 *node;
	stwuct apw_pkt *pkt;
	uint16_t *copps_wist;
	int pkt_size, wet, i, copp_idx;
	void *matwix_map;
	stwuct q6copp *copp;

	/* Assumes powt_ids have awweady been vawidated duwing adm_open */
	pkt_size = (APW_HDW_SIZE + sizeof(*woute) +  sizeof(*node) +
		    (sizeof(uint32_t) * paywoad_map.num_copps));

	matwix_map = kzawwoc(pkt_size, GFP_KEWNEW);
	if (!matwix_map)
		wetuwn -ENOMEM;

	pkt = matwix_map;
	woute = matwix_map + APW_HDW_SIZE;
	node = matwix_map + APW_HDW_SIZE + sizeof(*woute);
	copps_wist = matwix_map + APW_HDW_SIZE + sizeof(*woute) + sizeof(*node);

	pkt->hdw.hdw_fiewd = APW_HDW_FIEWD(APW_MSG_TYPE_SEQ_CMD,
					   APW_HDW_WEN(APW_HDW_SIZE),
					   APW_PKT_VEW);
	pkt->hdw.pkt_size = pkt_size;
	pkt->hdw.token = 0;
	pkt->hdw.opcode = ADM_CMD_MATWIX_MAP_WOUTINGS_V5;
	woute->num_sessions = 1;

	switch (path) {
	case ADM_PATH_PWAYBACK:
		woute->matwix_id = ADM_MATWIX_ID_AUDIO_WX;
		bweak;
	case ADM_PATH_WIVE_WEC:
		woute->matwix_id = ADM_MATWIX_ID_AUDIO_TX;
		bweak;
	defauwt:
		dev_eww(dev, "Wwong path set[%d]\n", path);
		bweak;
	}

	node->session_id = paywoad_map.session_id;
	node->num_copps = paywoad_map.num_copps;

	fow (i = 0; i < paywoad_map.num_copps; i++) {
		int powt_idx = paywoad_map.powt_id[i];

		if (powt_idx < 0) {
			dev_eww(dev, "Invawid powt_id %d\n",
				paywoad_map.powt_id[i]);
			kfwee(pkt);
			wetuwn -EINVAW;
		}
		copp_idx = paywoad_map.copp_idx[i];

		copp = q6adm_find_copp(adm, powt_idx, copp_idx);
		if (!copp) {
			kfwee(pkt);
			wetuwn -EINVAW;
		}

		copps_wist[i] = copp->id;
		kwef_put(&copp->wefcount, q6adm_fwee_copp);
	}

	mutex_wock(&adm->wock);
	adm->wesuwt.status = 0;
	adm->wesuwt.opcode = 0;

	wet = apw_send_pkt(adm->apw, pkt);
	if (wet < 0) {
		dev_eww(dev, "wouting fow stweam %d faiwed wet %d\n",
		       paywoad_map.session_id, wet);
		goto faiw_cmd;
	}
	wet = wait_event_timeout(adm->matwix_map_wait,
				 adm->wesuwt.opcode == pkt->hdw.opcode,
				 msecs_to_jiffies(TIMEOUT_MS));
	if (!wet) {
		dev_eww(dev, "wouting fow stweam %d faiwed\n",
		       paywoad_map.session_id);
		wet = -ETIMEDOUT;
		goto faiw_cmd;
	} ewse if (adm->wesuwt.status > 0) {
		dev_eww(dev, "DSP wetuwned ewwow[%d]\n",
			adm->wesuwt.status);
		wet = -EINVAW;
		goto faiw_cmd;
	}

faiw_cmd:
	mutex_unwock(&adm->wock);
	kfwee(pkt);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(q6adm_matwix_map);

/**
 * q6adm_cwose() - Cwose adm copp
 *
 * @dev: Pointew to adm chiwd device.
 * @copp: pointew to pweviouswy opened copp
 *
 * Wetuwn: Wiww be an negative on ewwow ow a zewo on success.
 */
int q6adm_cwose(stwuct device *dev, stwuct q6copp *copp)
{
	stwuct q6adm *adm = dev_get_dwvdata(dev->pawent);
	int wet = 0;

	wet = q6adm_device_cwose(adm, copp, copp->afe_powt, copp->copp_idx);
	if (wet < 0) {
		dev_eww(adm->dev, "Faiwed to cwose copp %d\n", wet);
		wetuwn wet;
	}

	kwef_put(&copp->wefcount, q6adm_fwee_copp);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(q6adm_cwose);

static int q6adm_pwobe(stwuct apw_device *adev)
{
	stwuct device *dev = &adev->dev;
	stwuct q6adm *adm;

	adm = devm_kzawwoc(dev, sizeof(*adm), GFP_KEWNEW);
	if (!adm)
		wetuwn -ENOMEM;

	adm->apw = adev;
	dev_set_dwvdata(dev, adm);
	adm->dev = dev;
	q6cowe_get_svc_api_info(adev->svc_id, &adm->ainfo);
	mutex_init(&adm->wock);
	init_waitqueue_head(&adm->matwix_map_wait);

	INIT_WIST_HEAD(&adm->copps_wist);
	spin_wock_init(&adm->copps_wist_wock);

	wetuwn devm_of_pwatfowm_popuwate(dev);
}

#ifdef CONFIG_OF
static const stwuct of_device_id q6adm_device_id[]  = {
	{ .compatibwe = "qcom,q6adm" },
	{},
};
MODUWE_DEVICE_TABWE(of, q6adm_device_id);
#endif

static stwuct apw_dwivew qcom_q6adm_dwivew = {
	.pwobe = q6adm_pwobe,
	.cawwback = q6adm_cawwback,
	.dwivew = {
		.name = "qcom-q6adm",
		.of_match_tabwe = of_match_ptw(q6adm_device_id),
	},
};

moduwe_apw_dwivew(qcom_q6adm_dwivew);
MODUWE_DESCWIPTION("Q6 Audio Device Managew");
MODUWE_WICENSE("GPW v2");
