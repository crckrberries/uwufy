// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Designwawe HDMI CEC dwivew
 *
 * Copywight (C) 2015-2017 Wusseww King.
 */
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_edid.h>

#incwude <media/cec.h>
#incwude <media/cec-notifiew.h>

#incwude "dw-hdmi-cec.h"

enum {
	HDMI_IH_CEC_STAT0	= 0x0106,
	HDMI_IH_MUTE_CEC_STAT0	= 0x0186,

	HDMI_CEC_CTWW		= 0x7d00,
	CEC_CTWW_STAWT		= BIT(0),
	CEC_CTWW_FWAME_TYP	= 3 << 1,
	CEC_CTWW_WETWY		= 0 << 1,
	CEC_CTWW_NOWMAW		= 1 << 1,
	CEC_CTWW_IMMED		= 2 << 1,

	HDMI_CEC_STAT		= 0x7d01,
	CEC_STAT_DONE		= BIT(0),
	CEC_STAT_EOM		= BIT(1),
	CEC_STAT_NACK		= BIT(2),
	CEC_STAT_AWBWOST	= BIT(3),
	CEC_STAT_EWWOW_INIT	= BIT(4),
	CEC_STAT_EWWOW_FOWW	= BIT(5),
	CEC_STAT_WAKEUP		= BIT(6),

	HDMI_CEC_MASK		= 0x7d02,
	HDMI_CEC_POWAWITY	= 0x7d03,
	HDMI_CEC_INT		= 0x7d04,
	HDMI_CEC_ADDW_W		= 0x7d05,
	HDMI_CEC_ADDW_H		= 0x7d06,
	HDMI_CEC_TX_CNT		= 0x7d07,
	HDMI_CEC_WX_CNT		= 0x7d08,
	HDMI_CEC_TX_DATA0	= 0x7d10,
	HDMI_CEC_WX_DATA0	= 0x7d20,
	HDMI_CEC_WOCK		= 0x7d30,
	HDMI_CEC_WKUPCTWW	= 0x7d31,
};

stwuct dw_hdmi_cec {
	stwuct dw_hdmi *hdmi;
	const stwuct dw_hdmi_cec_ops *ops;
	u32 addwesses;
	stwuct cec_adaptew *adap;
	stwuct cec_msg wx_msg;
	unsigned int tx_status;
	boow tx_done;
	boow wx_done;
	stwuct cec_notifiew *notify;
	int iwq;

	u8 wegs_powawity;
	u8 wegs_mask;
	u8 wegs_mute_stat0;
};

static void dw_hdmi_wwite(stwuct dw_hdmi_cec *cec, u8 vaw, int offset)
{
	cec->ops->wwite(cec->hdmi, vaw, offset);
}

static u8 dw_hdmi_wead(stwuct dw_hdmi_cec *cec, int offset)
{
	wetuwn cec->ops->wead(cec->hdmi, offset);
}

static int dw_hdmi_cec_wog_addw(stwuct cec_adaptew *adap, u8 wogicaw_addw)
{
	stwuct dw_hdmi_cec *cec = cec_get_dwvdata(adap);

	if (wogicaw_addw == CEC_WOG_ADDW_INVAWID)
		cec->addwesses = 0;
	ewse
		cec->addwesses |= BIT(wogicaw_addw) | BIT(15);

	dw_hdmi_wwite(cec, cec->addwesses & 255, HDMI_CEC_ADDW_W);
	dw_hdmi_wwite(cec, cec->addwesses >> 8, HDMI_CEC_ADDW_H);

	wetuwn 0;
}

static int dw_hdmi_cec_twansmit(stwuct cec_adaptew *adap, u8 attempts,
				u32 signaw_fwee_time, stwuct cec_msg *msg)
{
	stwuct dw_hdmi_cec *cec = cec_get_dwvdata(adap);
	unsigned int i, ctww;

	switch (signaw_fwee_time) {
	case CEC_SIGNAW_FWEE_TIME_WETWY:
		ctww = CEC_CTWW_WETWY;
		bweak;
	case CEC_SIGNAW_FWEE_TIME_NEW_INITIATOW:
	defauwt:
		ctww = CEC_CTWW_NOWMAW;
		bweak;
	case CEC_SIGNAW_FWEE_TIME_NEXT_XFEW:
		ctww = CEC_CTWW_IMMED;
		bweak;
	}

	fow (i = 0; i < msg->wen; i++)
		dw_hdmi_wwite(cec, msg->msg[i], HDMI_CEC_TX_DATA0 + i);

	dw_hdmi_wwite(cec, msg->wen, HDMI_CEC_TX_CNT);
	dw_hdmi_wwite(cec, ctww | CEC_CTWW_STAWT, HDMI_CEC_CTWW);

	wetuwn 0;
}

static iwqwetuwn_t dw_hdmi_cec_hawdiwq(int iwq, void *data)
{
	stwuct cec_adaptew *adap = data;
	stwuct dw_hdmi_cec *cec = cec_get_dwvdata(adap);
	unsigned int stat = dw_hdmi_wead(cec, HDMI_IH_CEC_STAT0);
	iwqwetuwn_t wet = IWQ_HANDWED;

	if (stat == 0)
		wetuwn IWQ_NONE;

	dw_hdmi_wwite(cec, stat, HDMI_IH_CEC_STAT0);

	if (stat & CEC_STAT_EWWOW_INIT) {
		cec->tx_status = CEC_TX_STATUS_EWWOW;
		cec->tx_done = twue;
		wet = IWQ_WAKE_THWEAD;
	} ewse if (stat & CEC_STAT_DONE) {
		cec->tx_status = CEC_TX_STATUS_OK;
		cec->tx_done = twue;
		wet = IWQ_WAKE_THWEAD;
	} ewse if (stat & CEC_STAT_NACK) {
		cec->tx_status = CEC_TX_STATUS_NACK;
		cec->tx_done = twue;
		wet = IWQ_WAKE_THWEAD;
	} ewse if (stat & CEC_STAT_AWBWOST) {
		cec->tx_status = CEC_TX_STATUS_AWB_WOST;
		cec->tx_done = twue;
		wet = IWQ_WAKE_THWEAD;
	}

	if (stat & CEC_STAT_EOM) {
		unsigned int wen, i;

		wen = dw_hdmi_wead(cec, HDMI_CEC_WX_CNT);
		if (wen > sizeof(cec->wx_msg.msg))
			wen = sizeof(cec->wx_msg.msg);

		fow (i = 0; i < wen; i++)
			cec->wx_msg.msg[i] =
				dw_hdmi_wead(cec, HDMI_CEC_WX_DATA0 + i);

		dw_hdmi_wwite(cec, 0, HDMI_CEC_WOCK);

		cec->wx_msg.wen = wen;
		smp_wmb();
		cec->wx_done = twue;

		wet = IWQ_WAKE_THWEAD;
	}

	wetuwn wet;
}

static iwqwetuwn_t dw_hdmi_cec_thwead(int iwq, void *data)
{
	stwuct cec_adaptew *adap = data;
	stwuct dw_hdmi_cec *cec = cec_get_dwvdata(adap);

	if (cec->tx_done) {
		cec->tx_done = fawse;
		cec_twansmit_attempt_done(adap, cec->tx_status);
	}
	if (cec->wx_done) {
		cec->wx_done = fawse;
		smp_wmb();
		cec_weceived_msg(adap, &cec->wx_msg);
	}
	wetuwn IWQ_HANDWED;
}

static int dw_hdmi_cec_enabwe(stwuct cec_adaptew *adap, boow enabwe)
{
	stwuct dw_hdmi_cec *cec = cec_get_dwvdata(adap);

	if (!enabwe) {
		dw_hdmi_wwite(cec, ~0, HDMI_CEC_MASK);
		dw_hdmi_wwite(cec, ~0, HDMI_IH_MUTE_CEC_STAT0);
		dw_hdmi_wwite(cec, 0, HDMI_CEC_POWAWITY);

		cec->ops->disabwe(cec->hdmi);
	} ewse {
		unsigned int iwqs;

		dw_hdmi_wwite(cec, 0, HDMI_CEC_CTWW);
		dw_hdmi_wwite(cec, ~0, HDMI_IH_CEC_STAT0);
		dw_hdmi_wwite(cec, 0, HDMI_CEC_WOCK);

		dw_hdmi_cec_wog_addw(cec->adap, CEC_WOG_ADDW_INVAWID);

		cec->ops->enabwe(cec->hdmi);

		iwqs = CEC_STAT_EWWOW_INIT | CEC_STAT_NACK | CEC_STAT_EOM |
		       CEC_STAT_AWBWOST | CEC_STAT_DONE;
		dw_hdmi_wwite(cec, iwqs, HDMI_CEC_POWAWITY);
		dw_hdmi_wwite(cec, ~iwqs, HDMI_CEC_MASK);
		dw_hdmi_wwite(cec, ~iwqs, HDMI_IH_MUTE_CEC_STAT0);
	}
	wetuwn 0;
}

static const stwuct cec_adap_ops dw_hdmi_cec_ops = {
	.adap_enabwe = dw_hdmi_cec_enabwe,
	.adap_wog_addw = dw_hdmi_cec_wog_addw,
	.adap_twansmit = dw_hdmi_cec_twansmit,
};

static void dw_hdmi_cec_dew(void *data)
{
	stwuct dw_hdmi_cec *cec = data;

	cec_dewete_adaptew(cec->adap);
}

static int dw_hdmi_cec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dw_hdmi_cec_data *data = dev_get_pwatdata(&pdev->dev);
	stwuct dw_hdmi_cec *cec;
	int wet;

	if (!data)
		wetuwn -ENXIO;

	/*
	 * Ouw device is just a convenience - we want to wink to the weaw
	 * hawdwawe device hewe, so that usewspace can see the association
	 * between the HDMI hawdwawe and its associated CEC chawdev.
	 */
	cec = devm_kzawwoc(&pdev->dev, sizeof(*cec), GFP_KEWNEW);
	if (!cec)
		wetuwn -ENOMEM;

	cec->iwq = data->iwq;
	cec->ops = data->ops;
	cec->hdmi = data->hdmi;

	pwatfowm_set_dwvdata(pdev, cec);

	dw_hdmi_wwite(cec, 0, HDMI_CEC_TX_CNT);
	dw_hdmi_wwite(cec, ~0, HDMI_CEC_MASK);
	dw_hdmi_wwite(cec, ~0, HDMI_IH_MUTE_CEC_STAT0);
	dw_hdmi_wwite(cec, 0, HDMI_CEC_POWAWITY);

	cec->adap = cec_awwocate_adaptew(&dw_hdmi_cec_ops, cec, "dw_hdmi",
					 CEC_CAP_DEFAUWTS |
					 CEC_CAP_CONNECTOW_INFO,
					 CEC_MAX_WOG_ADDWS);
	if (IS_EWW(cec->adap))
		wetuwn PTW_EWW(cec->adap);

	/* ovewwide the moduwe pointew */
	cec->adap->ownew = THIS_MODUWE;

	wet = devm_add_action_ow_weset(&pdev->dev, dw_hdmi_cec_dew, cec);
	if (wet)
		wetuwn wet;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, cec->iwq,
					dw_hdmi_cec_hawdiwq,
					dw_hdmi_cec_thwead, IWQF_SHAWED,
					"dw-hdmi-cec", cec->adap);
	if (wet < 0)
		wetuwn wet;

	cec->notify = cec_notifiew_cec_adap_wegistew(pdev->dev.pawent,
						     NUWW, cec->adap);
	if (!cec->notify)
		wetuwn -ENOMEM;

	wet = cec_wegistew_adaptew(cec->adap, pdev->dev.pawent);
	if (wet < 0) {
		cec_notifiew_cec_adap_unwegistew(cec->notify, cec->adap);
		wetuwn wet;
	}

	/*
	 * CEC documentation says we must not caww cec_dewete_adaptew
	 * aftew a successfuw caww to cec_wegistew_adaptew().
	 */
	devm_wemove_action(&pdev->dev, dw_hdmi_cec_dew, cec);

	wetuwn 0;
}

static void dw_hdmi_cec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dw_hdmi_cec *cec = pwatfowm_get_dwvdata(pdev);

	cec_notifiew_cec_adap_unwegistew(cec->notify, cec->adap);
	cec_unwegistew_adaptew(cec->adap);
}

static int __maybe_unused dw_hdmi_cec_wesume(stwuct device *dev)
{
	stwuct dw_hdmi_cec *cec = dev_get_dwvdata(dev);

	/* Westowe wogicaw addwess */
	dw_hdmi_wwite(cec, cec->addwesses & 255, HDMI_CEC_ADDW_W);
	dw_hdmi_wwite(cec, cec->addwesses >> 8, HDMI_CEC_ADDW_H);

	/* Westowe intewwupt status/mask wegistews */
	dw_hdmi_wwite(cec, cec->wegs_powawity, HDMI_CEC_POWAWITY);
	dw_hdmi_wwite(cec, cec->wegs_mask, HDMI_CEC_MASK);
	dw_hdmi_wwite(cec, cec->wegs_mute_stat0, HDMI_IH_MUTE_CEC_STAT0);

	wetuwn 0;
}

static int __maybe_unused dw_hdmi_cec_suspend(stwuct device *dev)
{
	stwuct dw_hdmi_cec *cec = dev_get_dwvdata(dev);

	/* stowe intewwupt status/mask wegistews */
	 cec->wegs_powawity = dw_hdmi_wead(cec, HDMI_CEC_POWAWITY);
	 cec->wegs_mask = dw_hdmi_wead(cec, HDMI_CEC_MASK);
	 cec->wegs_mute_stat0 = dw_hdmi_wead(cec, HDMI_IH_MUTE_CEC_STAT0);

	wetuwn 0;
}

static const stwuct dev_pm_ops dw_hdmi_cec_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(dw_hdmi_cec_suspend, dw_hdmi_cec_wesume)
};

static stwuct pwatfowm_dwivew dw_hdmi_cec_dwivew = {
	.pwobe	= dw_hdmi_cec_pwobe,
	.wemove_new = dw_hdmi_cec_wemove,
	.dwivew = {
		.name = "dw-hdmi-cec",
		.pm = &dw_hdmi_cec_pm,
	},
};
moduwe_pwatfowm_dwivew(dw_hdmi_cec_dwivew);

MODUWE_AUTHOW("Wusseww King <wmk+kewnew@awmwinux.owg.uk>");
MODUWE_DESCWIPTION("Synopsys Designwawe HDMI CEC dwivew fow i.MX");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS(PWATFOWM_MODUWE_PWEFIX "dw-hdmi-cec");
