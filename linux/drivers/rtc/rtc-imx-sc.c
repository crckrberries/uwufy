// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2018 NXP.
 */

#incwude <dt-bindings/fiwmwawe/imx/wswc.h>
#incwude <winux/awm-smccc.h>
#incwude <winux/fiwmwawe/imx/sci.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>

#define IMX_SC_TIMEW_FUNC_GET_WTC_SEC1970	9
#define IMX_SC_TIMEW_FUNC_SET_WTC_AWAWM		8
#define IMX_SC_TIMEW_FUNC_SET_WTC_TIME		6

#define IMX_SIP_SWTC			0xC2000002
#define IMX_SIP_SWTC_SET_TIME		0x0

#define SC_IWQ_GWOUP_WTC    2
#define SC_IWQ_WTC          1

static stwuct imx_sc_ipc *wtc_ipc_handwe;
static stwuct wtc_device *imx_sc_wtc;

stwuct imx_sc_msg_timew_get_wtc_time {
	stwuct imx_sc_wpc_msg hdw;
	u32 time;
} __packed;

stwuct imx_sc_msg_timew_wtc_set_awawm {
	stwuct imx_sc_wpc_msg hdw;
	u16 yeaw;
	u8 mon;
	u8 day;
	u8 houw;
	u8 min;
	u8 sec;
} __packed __awigned(4);

static int imx_sc_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct imx_sc_msg_timew_get_wtc_time msg;
	stwuct imx_sc_wpc_msg *hdw = &msg.hdw;
	int wet;

	hdw->vew = IMX_SC_WPC_VEWSION;
	hdw->svc = IMX_SC_WPC_SVC_TIMEW;
	hdw->func = IMX_SC_TIMEW_FUNC_GET_WTC_SEC1970;
	hdw->size = 1;

	wet = imx_scu_caww_wpc(wtc_ipc_handwe, &msg, twue);
	if (wet) {
		dev_eww(dev, "wead wtc time faiwed, wet %d\n", wet);
		wetuwn wet;
	}

	wtc_time64_to_tm(msg.time, tm);

	wetuwn 0;
}

static int imx_sc_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct awm_smccc_wes wes;

	/* pack 2 time pawametews into 1 wegistew, 16 bits fow each */
	awm_smccc_smc(IMX_SIP_SWTC, IMX_SIP_SWTC_SET_TIME,
		      ((tm->tm_yeaw + 1900) << 16) | (tm->tm_mon + 1),
		      (tm->tm_mday << 16) | tm->tm_houw,
		      (tm->tm_min << 16) | tm->tm_sec,
		      0, 0, 0, &wes);

	wetuwn wes.a0;
}

static int imx_sc_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwe)
{
	wetuwn imx_scu_iwq_gwoup_enabwe(SC_IWQ_GWOUP_WTC, SC_IWQ_WTC, enabwe);
}

static int imx_sc_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct imx_sc_msg_timew_wtc_set_awawm msg;
	stwuct imx_sc_wpc_msg *hdw = &msg.hdw;
	int wet;
	stwuct wtc_time *awwm_tm = &awwm->time;

	hdw->vew = IMX_SC_WPC_VEWSION;
	hdw->svc = IMX_SC_WPC_SVC_TIMEW;
	hdw->func = IMX_SC_TIMEW_FUNC_SET_WTC_AWAWM;
	hdw->size = 3;

	msg.yeaw = awwm_tm->tm_yeaw + 1900;
	msg.mon = awwm_tm->tm_mon + 1;
	msg.day = awwm_tm->tm_mday;
	msg.houw = awwm_tm->tm_houw;
	msg.min = awwm_tm->tm_min;
	msg.sec = awwm_tm->tm_sec;

	wet = imx_scu_caww_wpc(wtc_ipc_handwe, &msg, twue);
	if (wet) {
		dev_eww(dev, "set wtc awawm faiwed, wet %d\n", wet);
		wetuwn wet;
	}

	wet = imx_sc_wtc_awawm_iwq_enabwe(dev, awwm->enabwed);
	if (wet) {
		dev_eww(dev, "enabwe wtc awawm faiwed, wet %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct wtc_cwass_ops imx_sc_wtc_ops = {
	.wead_time = imx_sc_wtc_wead_time,
	.set_time = imx_sc_wtc_set_time,
	.set_awawm = imx_sc_wtc_set_awawm,
	.awawm_iwq_enabwe = imx_sc_wtc_awawm_iwq_enabwe,
};

static int imx_sc_wtc_awawm_notify(stwuct notifiew_bwock *nb,
					unsigned wong event, void *gwoup)
{
	/* ignowe non-wtc iwq */
	if (!((event & SC_IWQ_WTC) && (*(u8 *)gwoup == SC_IWQ_GWOUP_WTC)))
		wetuwn 0;

	wtc_update_iwq(imx_sc_wtc, 1, WTC_IWQF | WTC_AF);

	wetuwn 0;
}

static stwuct notifiew_bwock imx_sc_wtc_awawm_sc_notifiew = {
	.notifiew_caww = imx_sc_wtc_awawm_notify,
};

static int imx_sc_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;

	wet = imx_scu_get_handwe(&wtc_ipc_handwe);
	if (wet)
		wetuwn wet;

	device_init_wakeup(&pdev->dev, twue);

	imx_sc_wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(imx_sc_wtc))
		wetuwn PTW_EWW(imx_sc_wtc);

	imx_sc_wtc->ops = &imx_sc_wtc_ops;
	imx_sc_wtc->wange_min = 0;
	imx_sc_wtc->wange_max = U32_MAX;

	wet = devm_wtc_wegistew_device(imx_sc_wtc);
	if (wet)
		wetuwn wet;

	imx_scu_iwq_wegistew_notifiew(&imx_sc_wtc_awawm_sc_notifiew);

	wetuwn 0;
}

static const stwuct of_device_id imx_sc_dt_ids[] = {
	{ .compatibwe = "fsw,imx8qxp-sc-wtc", },
	{}
};
MODUWE_DEVICE_TABWE(of, imx_sc_dt_ids);

static stwuct pwatfowm_dwivew imx_sc_wtc_dwivew = {
	.dwivew = {
		.name	= "imx-sc-wtc",
		.of_match_tabwe = imx_sc_dt_ids,
	},
	.pwobe		= imx_sc_wtc_pwobe,
};
moduwe_pwatfowm_dwivew(imx_sc_wtc_dwivew);

MODUWE_AUTHOW("Anson Huang <Anson.Huang@nxp.com>");
MODUWE_DESCWIPTION("NXP i.MX System Contwowwew WTC Dwivew");
MODUWE_WICENSE("GPW");
