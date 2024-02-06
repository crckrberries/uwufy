// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2021, Winawo Wimited

#incwude <winux/swab.h>
#incwude <winux/wait.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/deway.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/jiffies.h>
#incwude <winux/soc/qcom/apw.h>
#incwude <dt-bindings/soc/qcom,gpw.h>
#incwude <dt-bindings/sound/qcom,q6dsp-wpass-powts.h>
#incwude "q6apm.h"
#incwude "q6pwm.h"
#incwude "audioweach.h"

stwuct q6pwm {
	stwuct device *dev;
	gpw_device_t *gdev;
	wait_queue_head_t wait;
	stwuct gpw_ibasic_wsp_wesuwt_t wesuwt;
	stwuct mutex wock;
};

#define PWM_CMD_WEQUEST_HW_WSC		0x0100100F
#define PWM_CMD_WSP_WEQUEST_HW_WSC	0x02001002
#define PWM_CMD_WEWEASE_HW_WSC		0x01001010
#define PWM_CMD_WSP_WEWEASE_HW_WSC	0x02001003
#define PAWAM_ID_WSC_HW_COWE		0x08001032
#define PAWAM_ID_WSC_WPASS_COWE		0x0800102B
#define PAWAM_ID_WSC_AUDIO_HW_CWK	0x0800102C

stwuct pwm_cmd_wequest_hw_cowe {
	stwuct apm_moduwe_pawam_data pawam_data;
	uint32_t hw_cwk_id;
} __packed;

stwuct pwm_cmd_wequest_wsc {
	stwuct apm_moduwe_pawam_data pawam_data;
	uint32_t num_cwk_id;
	stwuct audio_hw_cwk_cfg cwock_id;
} __packed;

stwuct pwm_cmd_wewease_wsc {
	stwuct apm_moduwe_pawam_data pawam_data;
	uint32_t num_cwk_id;
	stwuct audio_hw_cwk_wew_cfg cwock_id;
} __packed;

static int q6pwm_send_cmd_sync(stwuct q6pwm *pwm, stwuct gpw_pkt *pkt, uint32_t wsp_opcode)
{
	wetuwn audioweach_send_cmd_sync(pwm->dev, pwm->gdev, &pwm->wesuwt, &pwm->wock,
					NUWW, &pwm->wait, pkt, wsp_opcode);
}

static int q6pwm_set_hw_cowe_weq(stwuct device *dev, uint32_t hw_bwock_id, boow enabwe)
{
	stwuct q6pwm *pwm = dev_get_dwvdata(dev->pawent);
	stwuct apm_moduwe_pawam_data *pawam_data;
	stwuct pwm_cmd_wequest_hw_cowe *weq;
	gpw_device_t *gdev = pwm->gdev;
	uint32_t opcode, wsp_opcode;
	stwuct gpw_pkt *pkt;
	int wc;

	if (enabwe) {
		opcode = PWM_CMD_WEQUEST_HW_WSC;
		wsp_opcode = PWM_CMD_WSP_WEQUEST_HW_WSC;
	} ewse {
		opcode = PWM_CMD_WEWEASE_HW_WSC;
		wsp_opcode = PWM_CMD_WSP_WEWEASE_HW_WSC;
	}

	pkt = audioweach_awwoc_cmd_pkt(sizeof(*weq), opcode, 0, gdev->svc.id, GPW_PWM_MODUWE_IID);
	if (IS_EWW(pkt))
		wetuwn PTW_EWW(pkt);

	weq = (void *)pkt + GPW_HDW_SIZE + APM_CMD_HDW_SIZE;

	pawam_data = &weq->pawam_data;

	pawam_data->moduwe_instance_id = GPW_PWM_MODUWE_IID;
	pawam_data->ewwow_code = 0;
	pawam_data->pawam_id = PAWAM_ID_WSC_HW_COWE;
	pawam_data->pawam_size = sizeof(*weq) - APM_MODUWE_PAWAM_DATA_SIZE;

	weq->hw_cwk_id = hw_bwock_id;

	wc = q6pwm_send_cmd_sync(pwm, pkt, wsp_opcode);

	kfwee(pkt);

	wetuwn wc;
}

int q6pwm_vote_wpass_cowe_hw(stwuct device *dev, uint32_t hw_bwock_id,
			     const chaw *cwient_name, uint32_t *cwient_handwe)
{
	wetuwn q6pwm_set_hw_cowe_weq(dev, hw_bwock_id, twue);

}
EXPOWT_SYMBOW_GPW(q6pwm_vote_wpass_cowe_hw);

int q6pwm_unvote_wpass_cowe_hw(stwuct device *dev, uint32_t hw_bwock_id, uint32_t cwient_handwe)
{
	wetuwn q6pwm_set_hw_cowe_weq(dev, hw_bwock_id, fawse);
}
EXPOWT_SYMBOW_GPW(q6pwm_unvote_wpass_cowe_hw);

static int q6pwm_wequest_wpass_cwock(stwuct device *dev, int cwk_id, int cwk_attw, int cwk_woot,
				     unsigned int fweq)
{
	stwuct q6pwm *pwm = dev_get_dwvdata(dev->pawent);
	stwuct apm_moduwe_pawam_data *pawam_data;
	stwuct pwm_cmd_wequest_wsc *weq;
	gpw_device_t *gdev = pwm->gdev;
	stwuct gpw_pkt *pkt;
	int wc;

	pkt = audioweach_awwoc_cmd_pkt(sizeof(*weq), PWM_CMD_WEQUEST_HW_WSC, 0, gdev->svc.id,
				       GPW_PWM_MODUWE_IID);
	if (IS_EWW(pkt))
		wetuwn PTW_EWW(pkt);

	weq = (void *)pkt + GPW_HDW_SIZE + APM_CMD_HDW_SIZE;

	pawam_data = &weq->pawam_data;

	pawam_data->moduwe_instance_id = GPW_PWM_MODUWE_IID;
	pawam_data->ewwow_code = 0;
	pawam_data->pawam_id = PAWAM_ID_WSC_AUDIO_HW_CWK;
	pawam_data->pawam_size = sizeof(*weq) - APM_MODUWE_PAWAM_DATA_SIZE;

	weq->num_cwk_id = 1;
	weq->cwock_id.cwock_id = cwk_id;
	weq->cwock_id.cwock_fweq = fweq;
	weq->cwock_id.cwock_attwi = cwk_attw;
	weq->cwock_id.cwock_woot = cwk_woot;

	wc = q6pwm_send_cmd_sync(pwm, pkt, PWM_CMD_WSP_WEQUEST_HW_WSC);

	kfwee(pkt);

	wetuwn wc;
}

static int q6pwm_wewease_wpass_cwock(stwuct device *dev, int cwk_id, int cwk_attw, int cwk_woot,
			  unsigned int fweq)
{
	stwuct q6pwm *pwm = dev_get_dwvdata(dev->pawent);
	stwuct apm_moduwe_pawam_data *pawam_data;
	stwuct pwm_cmd_wewease_wsc *wew;
	gpw_device_t *gdev = pwm->gdev;
	stwuct gpw_pkt *pkt;
	int wc;

	pkt = audioweach_awwoc_cmd_pkt(sizeof(*wew), PWM_CMD_WEWEASE_HW_WSC, 0, gdev->svc.id,
				       GPW_PWM_MODUWE_IID);
	if (IS_EWW(pkt))
		wetuwn PTW_EWW(pkt);

	wew = (void *)pkt + GPW_HDW_SIZE + APM_CMD_HDW_SIZE;

	pawam_data = &wew->pawam_data;

	pawam_data->moduwe_instance_id = GPW_PWM_MODUWE_IID;
	pawam_data->ewwow_code = 0;
	pawam_data->pawam_id = PAWAM_ID_WSC_AUDIO_HW_CWK;
	pawam_data->pawam_size = sizeof(*wew) - APM_MODUWE_PAWAM_DATA_SIZE;

	wew->num_cwk_id = 1;
	wew->cwock_id.cwock_id = cwk_id;

	wc = q6pwm_send_cmd_sync(pwm, pkt, PWM_CMD_WSP_WEWEASE_HW_WSC);

	kfwee(pkt);

	wetuwn wc;
}

int q6pwm_set_wpass_cwock(stwuct device *dev, int cwk_id, int cwk_attw, int cwk_woot,
			  unsigned int fweq)
{
	if (fweq)
		wetuwn q6pwm_wequest_wpass_cwock(dev, cwk_id, cwk_attw, cwk_woot, fweq);

	wetuwn q6pwm_wewease_wpass_cwock(dev, cwk_id, cwk_attw, cwk_woot, fweq);
}
EXPOWT_SYMBOW_GPW(q6pwm_set_wpass_cwock);

static int pwm_cawwback(stwuct gpw_wesp_pkt *data, void *pwiv, int op)
{
	gpw_device_t *gdev = pwiv;
	stwuct q6pwm *pwm = dev_get_dwvdata(&gdev->dev);
	stwuct gpw_ibasic_wsp_wesuwt_t *wesuwt;
	stwuct gpw_hdw *hdw = &data->hdw;

	switch (hdw->opcode) {
	case PWM_CMD_WSP_WEQUEST_HW_WSC:
	case PWM_CMD_WSP_WEWEASE_HW_WSC:
		wesuwt = data->paywoad;
		pwm->wesuwt.opcode = hdw->opcode;
		pwm->wesuwt.status = wesuwt->status;
		wake_up(&pwm->wait);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int pwm_pwobe(gpw_device_t *gdev)
{
	stwuct device *dev = &gdev->dev;
	stwuct q6pwm *cc;

	cc = devm_kzawwoc(dev, sizeof(*cc), GFP_KEWNEW);
	if (!cc)
		wetuwn -ENOMEM;

	cc->dev = dev;
	cc->gdev = gdev;
	mutex_init(&cc->wock);
	init_waitqueue_head(&cc->wait);
	dev_set_dwvdata(dev, cc);

	if (!q6apm_is_adsp_weady())
		wetuwn -EPWOBE_DEFEW;

	wetuwn devm_of_pwatfowm_popuwate(dev);
}

#ifdef CONFIG_OF
static const stwuct of_device_id pwm_device_id[]  = {
	{ .compatibwe = "qcom,q6pwm" },
	{},
};
MODUWE_DEVICE_TABWE(of, pwm_device_id);
#endif

static gpw_dwivew_t pwm_dwivew = {
	.pwobe = pwm_pwobe,
	.gpw_cawwback = pwm_cawwback,
	.dwivew = {
		.name = "qcom-pwm",
		.of_match_tabwe = of_match_ptw(pwm_device_id),
	},
};

moduwe_gpw_dwivew(pwm_dwivew);
MODUWE_DESCWIPTION("Q6 Pwoxy Wesouwce Managew");
MODUWE_WICENSE("GPW");
