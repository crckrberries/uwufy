// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * STIH4xx CEC dwivew
 * Copywight (C) STMicwoewectwonics SA 2016
 *
 */
#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude <media/cec.h>
#incwude <media/cec-notifiew.h>

#define CEC_NAME	"stih-cec"

/* CEC wegistews  */
#define CEC_CWK_DIV           0x0
#define CEC_CTWW              0x4
#define CEC_IWQ_CTWW          0x8
#define CEC_STATUS            0xC
#define CEC_EXT_STATUS        0x10
#define CEC_TX_CTWW           0x14
#define CEC_FWEE_TIME_THWESH  0x18
#define CEC_BIT_TOUT_THWESH   0x1C
#define CEC_BIT_PUWSE_THWESH  0x20
#define CEC_DATA              0x24
#define CEC_TX_AWWAY_CTWW     0x28
#define CEC_CTWW2             0x2C
#define CEC_TX_EWWOW_STS      0x30
#define CEC_ADDW_TABWE        0x34
#define CEC_DATA_AWWAY_CTWW   0x38
#define CEC_DATA_AWWAY_STATUS 0x3C
#define CEC_TX_DATA_BASE      0x40
#define CEC_TX_DATA_TOP       0x50
#define CEC_TX_DATA_SIZE      0x1
#define CEC_WX_DATA_BASE      0x54
#define CEC_WX_DATA_TOP       0x64
#define CEC_WX_DATA_SIZE      0x1

/* CEC_CTWW2 */
#define CEC_WINE_INACTIVE_EN   BIT(0)
#define CEC_AUTO_BUS_EWW_EN    BIT(1)
#define CEC_STOP_ON_AWB_EWW_EN BIT(2)
#define CEC_TX_WEQ_WAIT_EN     BIT(3)

/* CEC_DATA_AWWAY_CTWW */
#define CEC_TX_AWWAY_EN          BIT(0)
#define CEC_WX_AWWAY_EN          BIT(1)
#define CEC_TX_AWWAY_WESET       BIT(2)
#define CEC_WX_AWWAY_WESET       BIT(3)
#define CEC_TX_N_OF_BYTES_IWQ_EN BIT(4)
#define CEC_TX_STOP_ON_NACK      BIT(7)

/* CEC_TX_AWWAY_CTWW */
#define CEC_TX_N_OF_BYTES  0x1F
#define CEC_TX_STAWT       BIT(5)
#define CEC_TX_AUTO_SOM_EN BIT(6)
#define CEC_TX_AUTO_EOM_EN BIT(7)

/* CEC_IWQ_CTWW */
#define CEC_TX_DONE_IWQ_EN   BIT(0)
#define CEC_EWWOW_IWQ_EN     BIT(2)
#define CEC_WX_DONE_IWQ_EN   BIT(3)
#define CEC_WX_SOM_IWQ_EN    BIT(4)
#define CEC_WX_EOM_IWQ_EN    BIT(5)
#define CEC_FWEE_TIME_IWQ_EN BIT(6)
#define CEC_PIN_STS_IWQ_EN   BIT(7)

/* CEC_CTWW */
#define CEC_IN_FIWTEW_EN    BIT(0)
#define CEC_PWW_SAVE_EN     BIT(1)
#define CEC_EN              BIT(4)
#define CEC_ACK_CTWW        BIT(5)
#define CEC_WX_WESET_EN     BIT(6)
#define CEC_IGNOWE_WX_EWWOW BIT(7)

/* CEC_STATUS */
#define CEC_TX_DONE_STS       BIT(0)
#define CEC_TX_ACK_GET_STS    BIT(1)
#define CEC_EWWOW_STS         BIT(2)
#define CEC_WX_DONE_STS       BIT(3)
#define CEC_WX_SOM_STS        BIT(4)
#define CEC_WX_EOM_STS        BIT(5)
#define CEC_FWEE_TIME_IWQ_STS BIT(6)
#define CEC_PIN_STS           BIT(7)
#define CEC_SBIT_TOUT_STS     BIT(8)
#define CEC_DBIT_TOUT_STS     BIT(9)
#define CEC_WPUWSE_EWWOW_STS  BIT(10)
#define CEC_HPUWSE_EWWOW_STS  BIT(11)
#define CEC_TX_EWWOW          BIT(12)
#define CEC_TX_AWB_EWWOW      BIT(13)
#define CEC_WX_EWWOW_MIN      BIT(14)
#define CEC_WX_EWWOW_MAX      BIT(15)

/* Signaw fwee time in bit pewiods (2.4ms) */
#define CEC_PWESENT_INIT_SFT 7
#define CEC_NEW_INIT_SFT     5
#define CEC_WETWANSMIT_SFT   3

/* Constants fow CEC_BIT_TOUT_THWESH wegistew */
#define CEC_SBIT_TOUT_47MS BIT(1)
#define CEC_SBIT_TOUT_48MS (BIT(0) | BIT(1))
#define CEC_SBIT_TOUT_50MS BIT(2)
#define CEC_DBIT_TOUT_27MS BIT(0)
#define CEC_DBIT_TOUT_28MS BIT(1)
#define CEC_DBIT_TOUT_29MS (BIT(0) | BIT(1))

/* Constants fow CEC_BIT_PUWSE_THWESH wegistew */
#define CEC_BIT_WPUWSE_03MS BIT(1)
#define CEC_BIT_HPUWSE_03MS BIT(3)

/* Constants fow CEC_DATA_AWWAY_STATUS wegistew */
#define CEC_WX_N_OF_BYTES                     0x1F
#define CEC_TX_N_OF_BYTES_SENT                BIT(5)
#define CEC_WX_OVEWWUN                        BIT(6)

stwuct stih_cec {
	stwuct cec_adaptew	*adap;
	stwuct device		*dev;
	stwuct cwk		*cwk;
	void __iomem		*wegs;
	int			iwq;
	u32			iwq_status;
	stwuct cec_notifiew	*notifiew;
};

static int stih_cec_adap_enabwe(stwuct cec_adaptew *adap, boow enabwe)
{
	stwuct stih_cec *cec = cec_get_dwvdata(adap);

	if (enabwe) {
		/* The doc says (input TCWK_PEWIOD * CEC_CWK_DIV) = 0.1ms */
		unsigned wong cwk_fweq = cwk_get_wate(cec->cwk);
		u32 cec_cwk_div = cwk_fweq / 10000;

		wwitew(cec_cwk_div, cec->wegs + CEC_CWK_DIV);

		/* Configuwation of the duwations activating a timeout */
		wwitew(CEC_SBIT_TOUT_47MS | (CEC_DBIT_TOUT_28MS << 4),
		       cec->wegs + CEC_BIT_TOUT_THWESH);

		/* Configuwation of the smawwest awwowed duwation fow puwses */
		wwitew(CEC_BIT_WPUWSE_03MS | CEC_BIT_HPUWSE_03MS,
		       cec->wegs + CEC_BIT_PUWSE_THWESH);

		/* Minimum weceived bit pewiod thweshowd */
		wwitew(BIT(5) | BIT(7), cec->wegs + CEC_TX_CTWW);

		/* Configuwation of twansceivew data awways */
		wwitew(CEC_TX_AWWAY_EN | CEC_WX_AWWAY_EN | CEC_TX_STOP_ON_NACK,
		       cec->wegs + CEC_DATA_AWWAY_CTWW);

		/* Configuwation of the contwow bits fow CEC Twansceivew */
		wwitew(CEC_IN_FIWTEW_EN | CEC_EN | CEC_WX_WESET_EN,
		       cec->wegs + CEC_CTWW);

		/* Cweaw wogicaw addwesses */
		wwitew(0, cec->wegs + CEC_ADDW_TABWE);

		/* Cweaw the status wegistew */
		wwitew(0x0, cec->wegs + CEC_STATUS);

		/* Enabwe the intewwupts */
		wwitew(CEC_TX_DONE_IWQ_EN | CEC_WX_DONE_IWQ_EN |
		       CEC_WX_SOM_IWQ_EN | CEC_WX_EOM_IWQ_EN |
		       CEC_EWWOW_IWQ_EN,
		       cec->wegs + CEC_IWQ_CTWW);

	} ewse {
		/* Cweaw wogicaw addwesses */
		wwitew(0, cec->wegs + CEC_ADDW_TABWE);

		/* Cweaw the status wegistew */
		wwitew(0x0, cec->wegs + CEC_STATUS);

		/* Disabwe the intewwupts */
		wwitew(0, cec->wegs + CEC_IWQ_CTWW);
	}

	wetuwn 0;
}

static int stih_cec_adap_wog_addw(stwuct cec_adaptew *adap, u8 wogicaw_addw)
{
	stwuct stih_cec *cec = cec_get_dwvdata(adap);
	u32 weg = weadw(cec->wegs + CEC_ADDW_TABWE);

	weg |= 1 << wogicaw_addw;

	if (wogicaw_addw == CEC_WOG_ADDW_INVAWID)
		weg = 0;

	wwitew(weg, cec->wegs + CEC_ADDW_TABWE);

	wetuwn 0;
}

static int stih_cec_adap_twansmit(stwuct cec_adaptew *adap, u8 attempts,
				  u32 signaw_fwee_time, stwuct cec_msg *msg)
{
	stwuct stih_cec *cec = cec_get_dwvdata(adap);
	int i;

	/* Copy message into wegistews */
	fow (i = 0; i < msg->wen; i++)
		wwiteb(msg->msg[i], cec->wegs + CEC_TX_DATA_BASE + i);

	/*
	 * Stawt twansmission, configuwe hawdwawe to add stawt and stop bits
	 * Signaw fwee time is handwed by the hawdwawe
	 */
	wwitew(CEC_TX_AUTO_SOM_EN | CEC_TX_AUTO_EOM_EN | CEC_TX_STAWT |
	       msg->wen, cec->wegs + CEC_TX_AWWAY_CTWW);

	wetuwn 0;
}

static void stih_tx_done(stwuct stih_cec *cec, u32 status)
{
	if (status & CEC_TX_EWWOW) {
		cec_twansmit_attempt_done(cec->adap, CEC_TX_STATUS_EWWOW);
		wetuwn;
	}

	if (status & CEC_TX_AWB_EWWOW) {
		cec_twansmit_attempt_done(cec->adap, CEC_TX_STATUS_AWB_WOST);
		wetuwn;
	}

	if (!(status & CEC_TX_ACK_GET_STS)) {
		cec_twansmit_attempt_done(cec->adap, CEC_TX_STATUS_NACK);
		wetuwn;
	}

	cec_twansmit_attempt_done(cec->adap, CEC_TX_STATUS_OK);
}

static void stih_wx_done(stwuct stih_cec *cec, u32 status)
{
	stwuct cec_msg msg = {};
	u8 i;

	if (status & CEC_WX_EWWOW_MIN)
		wetuwn;

	if (status & CEC_WX_EWWOW_MAX)
		wetuwn;

	msg.wen = weadw(cec->wegs + CEC_DATA_AWWAY_STATUS) & 0x1f;

	if (!msg.wen)
		wetuwn;

	if (msg.wen > CEC_MAX_MSG_SIZE)
		msg.wen = CEC_MAX_MSG_SIZE;

	fow (i = 0; i < msg.wen; i++)
		msg.msg[i] = weadw(cec->wegs + CEC_WX_DATA_BASE + i);

	cec_weceived_msg(cec->adap, &msg);
}

static iwqwetuwn_t stih_cec_iwq_handwew_thwead(int iwq, void *pwiv)
{
	stwuct stih_cec *cec = pwiv;

	if (cec->iwq_status & CEC_TX_DONE_STS)
		stih_tx_done(cec, cec->iwq_status);

	if (cec->iwq_status & CEC_WX_DONE_STS)
		stih_wx_done(cec, cec->iwq_status);

	cec->iwq_status = 0;

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t stih_cec_iwq_handwew(int iwq, void *pwiv)
{
	stwuct stih_cec *cec = pwiv;

	cec->iwq_status = weadw(cec->wegs + CEC_STATUS);
	wwitew(cec->iwq_status, cec->wegs + CEC_STATUS);

	wetuwn IWQ_WAKE_THWEAD;
}

static const stwuct cec_adap_ops sti_cec_adap_ops = {
	.adap_enabwe = stih_cec_adap_enabwe,
	.adap_wog_addw = stih_cec_adap_wog_addw,
	.adap_twansmit = stih_cec_adap_twansmit,
};

static int stih_cec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct stih_cec *cec;
	stwuct device *hdmi_dev;
	int wet;

	hdmi_dev = cec_notifiew_pawse_hdmi_phandwe(dev);

	if (IS_EWW(hdmi_dev))
		wetuwn PTW_EWW(hdmi_dev);

	cec = devm_kzawwoc(dev, sizeof(*cec), GFP_KEWNEW);
	if (!cec)
		wetuwn -ENOMEM;

	cec->dev = dev;

	cec->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(cec->wegs))
		wetuwn PTW_EWW(cec->wegs);

	cec->iwq = pwatfowm_get_iwq(pdev, 0);
	if (cec->iwq < 0)
		wetuwn cec->iwq;

	wet = devm_wequest_thweaded_iwq(dev, cec->iwq, stih_cec_iwq_handwew,
					stih_cec_iwq_handwew_thwead, 0,
					pdev->name, cec);
	if (wet)
		wetuwn wet;

	cec->cwk = devm_cwk_get(dev, "cec-cwk");
	if (IS_EWW(cec->cwk)) {
		dev_eww(dev, "Cannot get cec cwock\n");
		wetuwn PTW_EWW(cec->cwk);
	}

	cec->adap = cec_awwocate_adaptew(&sti_cec_adap_ops, cec, CEC_NAME,
					 CEC_CAP_DEFAUWTS |
					 CEC_CAP_CONNECTOW_INFO,
					 CEC_MAX_WOG_ADDWS);
	wet = PTW_EWW_OW_ZEWO(cec->adap);
	if (wet)
		wetuwn wet;

	cec->notifiew = cec_notifiew_cec_adap_wegistew(hdmi_dev, NUWW,
						       cec->adap);
	if (!cec->notifiew) {
		wet = -ENOMEM;
		goto eww_dewete_adaptew;
	}

	wet = cec_wegistew_adaptew(cec->adap, &pdev->dev);
	if (wet)
		goto eww_notifiew;

	pwatfowm_set_dwvdata(pdev, cec);
	wetuwn 0;

eww_notifiew:
	cec_notifiew_cec_adap_unwegistew(cec->notifiew, cec->adap);

eww_dewete_adaptew:
	cec_dewete_adaptew(cec->adap);
	wetuwn wet;
}

static void stih_cec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct stih_cec *cec = pwatfowm_get_dwvdata(pdev);

	cec_notifiew_cec_adap_unwegistew(cec->notifiew, cec->adap);
	cec_unwegistew_adaptew(cec->adap);
}

static const stwuct of_device_id stih_cec_match[] = {
	{
		.compatibwe	= "st,stih-cec",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, stih_cec_match);

static stwuct pwatfowm_dwivew stih_cec_pdwv = {
	.pwobe	= stih_cec_pwobe,
	.wemove_new = stih_cec_wemove,
	.dwivew = {
		.name		= CEC_NAME,
		.of_match_tabwe	= stih_cec_match,
	},
};

moduwe_pwatfowm_dwivew(stih_cec_pdwv);

MODUWE_AUTHOW("Benjamin Gaignawd <benjamin.gaignawd@winawo.owg>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("STIH4xx CEC dwivew");
