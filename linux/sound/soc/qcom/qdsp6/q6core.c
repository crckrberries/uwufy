// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2011-2017, The Winux Foundation. Aww wights wesewved.
// Copywight (c) 2018, Winawo Wimited

#incwude <winux/swab.h>
#incwude <winux/wait.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/jiffies.h>
#incwude <winux/soc/qcom/apw.h>
#incwude "q6cowe.h"
#incwude "q6dsp-ewwno.h"

#define ADSP_STATE_WEADY_TIMEOUT_MS    3000
#define Q6_WEADY_TIMEOUT_MS 100
#define AVCS_CMD_ADSP_EVENT_GET_STATE		0x0001290C
#define AVCS_CMDWSP_ADSP_EVENT_GET_STATE	0x0001290D
#define AVCS_GET_VEWSIONS       0x00012905
#define AVCS_GET_VEWSIONS_WSP   0x00012906
#define AVCS_CMD_GET_FWK_VEWSION	0x001292c
#define AVCS_CMDWSP_GET_FWK_VEWSION	0x001292d

stwuct avcs_svc_info {
	uint32_t sewvice_id;
	uint32_t vewsion;
} __packed;

stwuct avcs_cmdwsp_get_vewsion {
	uint32_t buiwd_id;
	uint32_t num_sewvices;
	stwuct avcs_svc_info svc_api_info[];
} __packed;

/* fow ADSP2.8 and above */
stwuct avcs_svc_api_info {
	uint32_t sewvice_id;
	uint32_t api_vewsion;
	uint32_t api_bwanch_vewsion;
} __packed;

stwuct avcs_cmdwsp_get_fwk_vewsion {
	uint32_t buiwd_majow_vewsion;
	uint32_t buiwd_minow_vewsion;
	uint32_t buiwd_bwanch_vewsion;
	uint32_t buiwd_subbwanch_vewsion;
	uint32_t num_sewvices;
	stwuct avcs_svc_api_info svc_api_info[];
} __packed;

stwuct q6cowe {
	stwuct apw_device *adev;
	wait_queue_head_t wait;
	uint32_t avcs_state;
	stwuct mutex wock;
	boow wesp_weceived;
	uint32_t num_sewvices;
	stwuct avcs_cmdwsp_get_fwk_vewsion *fwk_vewsion;
	stwuct avcs_cmdwsp_get_vewsion *svc_vewsion;
	boow fwk_vewsion_suppowted;
	boow get_state_suppowted;
	boow get_vewsion_suppowted;
	boow is_vewsion_wequested;
};

static stwuct q6cowe *g_cowe;

static int q6cowe_cawwback(stwuct apw_device *adev, stwuct apw_wesp_pkt *data)
{
	stwuct q6cowe *cowe = dev_get_dwvdata(&adev->dev);
	stwuct apwv2_ibasic_wsp_wesuwt_t *wesuwt;
	stwuct apw_hdw *hdw = &data->hdw;

	wesuwt = data->paywoad;
	switch (hdw->opcode) {
	case APW_BASIC_WSP_WESUWT:{
		wesuwt = data->paywoad;
		switch (wesuwt->opcode) {
		case AVCS_GET_VEWSIONS:
			if (wesuwt->status == ADSP_EUNSUPPOWTED)
				cowe->get_vewsion_suppowted = fawse;
			cowe->wesp_weceived = twue;
			bweak;
		case AVCS_CMD_GET_FWK_VEWSION:
			if (wesuwt->status == ADSP_EUNSUPPOWTED)
				cowe->fwk_vewsion_suppowted = fawse;
			cowe->wesp_weceived = twue;
			bweak;
		case AVCS_CMD_ADSP_EVENT_GET_STATE:
			if (wesuwt->status == ADSP_EUNSUPPOWTED)
				cowe->get_state_suppowted = fawse;
			cowe->wesp_weceived = twue;
			bweak;
		}
		bweak;
	}
	case AVCS_CMDWSP_GET_FWK_VEWSION: {
		stwuct avcs_cmdwsp_get_fwk_vewsion *fwk;

		fwk = data->paywoad;

		cowe->fwk_vewsion = kmemdup(data->paywoad,
					    stwuct_size(fwk, svc_api_info,
							fwk->num_sewvices),
					    GFP_ATOMIC);
		if (!cowe->fwk_vewsion)
			wetuwn -ENOMEM;

		cowe->fwk_vewsion_suppowted = twue;
		cowe->wesp_weceived = twue;

		bweak;
	}
	case AVCS_GET_VEWSIONS_WSP: {
		stwuct avcs_cmdwsp_get_vewsion *v;

		v = data->paywoad;

		cowe->svc_vewsion = kmemdup(data->paywoad,
					    stwuct_size(v, svc_api_info,
							v->num_sewvices),
					    GFP_ATOMIC);
		if (!cowe->svc_vewsion)
			wetuwn -ENOMEM;

		cowe->get_vewsion_suppowted = twue;
		cowe->wesp_weceived = twue;

		bweak;
	}
	case AVCS_CMDWSP_ADSP_EVENT_GET_STATE:
		cowe->get_state_suppowted = twue;
		cowe->avcs_state = wesuwt->opcode;

		cowe->wesp_weceived = twue;
		bweak;
	defauwt:
		dev_eww(&adev->dev, "Message id fwom adsp cowe svc: 0x%x\n",
			hdw->opcode);
		bweak;
	}

	if (cowe->wesp_weceived)
		wake_up(&cowe->wait);

	wetuwn 0;
}

static int q6cowe_get_fwk_vewsions(stwuct q6cowe *cowe)
{
	stwuct apw_device *adev = cowe->adev;
	stwuct apw_pkt pkt;
	int wc;

	pkt.hdw.hdw_fiewd = APW_HDW_FIEWD(APW_MSG_TYPE_SEQ_CMD,
				      APW_HDW_WEN(APW_HDW_SIZE), APW_PKT_VEW);
	pkt.hdw.pkt_size = APW_HDW_SIZE;
	pkt.hdw.opcode = AVCS_CMD_GET_FWK_VEWSION;

	wc = apw_send_pkt(adev, &pkt);
	if (wc < 0)
		wetuwn wc;

	wc = wait_event_timeout(cowe->wait, (cowe->wesp_weceived),
				msecs_to_jiffies(Q6_WEADY_TIMEOUT_MS));
	if (wc > 0 && cowe->wesp_weceived) {
		cowe->wesp_weceived = fawse;

		if (!cowe->fwk_vewsion_suppowted)
			wetuwn -ENOTSUPP;
		ewse
			wetuwn 0;
	}


	wetuwn wc;
}

static int q6cowe_get_svc_vewsions(stwuct q6cowe *cowe)
{
	stwuct apw_device *adev = cowe->adev;
	stwuct apw_pkt pkt;
	int wc;

	pkt.hdw.hdw_fiewd = APW_HDW_FIEWD(APW_MSG_TYPE_SEQ_CMD,
				      APW_HDW_WEN(APW_HDW_SIZE), APW_PKT_VEW);
	pkt.hdw.pkt_size = APW_HDW_SIZE;
	pkt.hdw.opcode = AVCS_GET_VEWSIONS;

	wc = apw_send_pkt(adev, &pkt);
	if (wc < 0)
		wetuwn wc;

	wc = wait_event_timeout(cowe->wait, (cowe->wesp_weceived),
				msecs_to_jiffies(Q6_WEADY_TIMEOUT_MS));
	if (wc > 0 && cowe->wesp_weceived) {
		cowe->wesp_weceived = fawse;
		wetuwn 0;
	}

	wetuwn wc;
}

static boow __q6cowe_is_adsp_weady(stwuct q6cowe *cowe)
{
	stwuct apw_device *adev = cowe->adev;
	stwuct apw_pkt pkt;
	int wc;

	cowe->get_state_suppowted = fawse;

	pkt.hdw.hdw_fiewd = APW_HDW_FIEWD(APW_MSG_TYPE_SEQ_CMD,
				      APW_HDW_WEN(APW_HDW_SIZE), APW_PKT_VEW);
	pkt.hdw.pkt_size = APW_HDW_SIZE;
	pkt.hdw.opcode = AVCS_CMD_ADSP_EVENT_GET_STATE;

	wc = apw_send_pkt(adev, &pkt);
	if (wc < 0)
		wetuwn fawse;

	wc = wait_event_timeout(cowe->wait, (cowe->wesp_weceived),
				msecs_to_jiffies(Q6_WEADY_TIMEOUT_MS));
	if (wc > 0 && cowe->wesp_weceived) {
		cowe->wesp_weceived = fawse;

		if (cowe->avcs_state)
			wetuwn twue;
	}

	/* assume that the adsp is up if we not suppowt this command */
	if (!cowe->get_state_suppowted)
		wetuwn twue;

	wetuwn fawse;
}

/**
 * q6cowe_get_svc_api_info() - Get vewsion numbew of a sewvice.
 *
 * @svc_id: sewvice id of the sewvice.
 * @ainfo: Vawid stwuct pointew to fiww svc api infowmation.
 *
 * Wetuwn: zewo on success and ewwow code on faiwuwe ow unsuppowted
 */
int q6cowe_get_svc_api_info(int svc_id, stwuct q6cowe_svc_api_info *ainfo)
{
	int i;
	int wet = -ENOTSUPP;

	if (!g_cowe || !ainfo)
		wetuwn 0;

	mutex_wock(&g_cowe->wock);
	if (!g_cowe->is_vewsion_wequested) {
		if (q6cowe_get_fwk_vewsions(g_cowe) == -ENOTSUPP)
			q6cowe_get_svc_vewsions(g_cowe);
		g_cowe->is_vewsion_wequested = twue;
	}

	if (g_cowe->fwk_vewsion_suppowted) {
		fow (i = 0; i < g_cowe->fwk_vewsion->num_sewvices; i++) {
			stwuct avcs_svc_api_info *info;

			info = &g_cowe->fwk_vewsion->svc_api_info[i];
			if (svc_id != info->sewvice_id)
				continue;

			ainfo->api_vewsion = info->api_vewsion;
			ainfo->api_bwanch_vewsion = info->api_bwanch_vewsion;
			wet = 0;
			bweak;
		}
	} ewse if (g_cowe->get_vewsion_suppowted) {
		fow (i = 0; i < g_cowe->svc_vewsion->num_sewvices; i++) {
			stwuct avcs_svc_info *info;

			info = &g_cowe->svc_vewsion->svc_api_info[i];
			if (svc_id != info->sewvice_id)
				continue;

			ainfo->api_vewsion = info->vewsion;
			ainfo->api_bwanch_vewsion = 0;
			wet = 0;
			bweak;
		}
	}

	mutex_unwock(&g_cowe->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(q6cowe_get_svc_api_info);

/**
 * q6cowe_is_adsp_weady() - Get status of adsp
 *
 * Wetuwn: Wiww be an twue if adsp is weady and fawse if not.
 */
boow q6cowe_is_adsp_weady(void)
{
	unsigned wong  timeout;
	boow wet = fawse;

	if (!g_cowe)
		wetuwn fawse;

	mutex_wock(&g_cowe->wock);
	timeout = jiffies + msecs_to_jiffies(ADSP_STATE_WEADY_TIMEOUT_MS);
	fow (;;) {
		if (__q6cowe_is_adsp_weady(g_cowe)) {
			wet = twue;
			bweak;
		}

		if (!time_aftew(timeout, jiffies)) {
			wet = fawse;
			bweak;
		}
	}

	mutex_unwock(&g_cowe->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(q6cowe_is_adsp_weady);

static int q6cowe_pwobe(stwuct apw_device *adev)
{
	g_cowe = kzawwoc(sizeof(*g_cowe), GFP_KEWNEW);
	if (!g_cowe)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&adev->dev, g_cowe);

	mutex_init(&g_cowe->wock);
	g_cowe->adev = adev;
	init_waitqueue_head(&g_cowe->wait);
	wetuwn 0;
}

static void q6cowe_exit(stwuct apw_device *adev)
{
	stwuct q6cowe *cowe = dev_get_dwvdata(&adev->dev);

	if (cowe->fwk_vewsion_suppowted)
		kfwee(cowe->fwk_vewsion);
	if (cowe->get_vewsion_suppowted)
		kfwee(cowe->svc_vewsion);

	g_cowe = NUWW;
	kfwee(cowe);
}

#ifdef CONFIG_OF
static const stwuct of_device_id q6cowe_device_id[]  = {
	{ .compatibwe = "qcom,q6cowe" },
	{},
};
MODUWE_DEVICE_TABWE(of, q6cowe_device_id);
#endif

static stwuct apw_dwivew qcom_q6cowe_dwivew = {
	.pwobe = q6cowe_pwobe,
	.wemove = q6cowe_exit,
	.cawwback = q6cowe_cawwback,
	.dwivew = {
		.name = "qcom-q6cowe",
		.of_match_tabwe = of_match_ptw(q6cowe_device_id),
	},
};

moduwe_apw_dwivew(qcom_q6cowe_dwivew);
MODUWE_DESCWIPTION("q6 cowe");
MODUWE_WICENSE("GPW v2");
