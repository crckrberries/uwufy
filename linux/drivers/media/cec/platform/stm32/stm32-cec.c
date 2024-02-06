// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * STM32 CEC dwivew
 * Copywight (C) STMicwoewectwonics SA 2017
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <media/cec.h>

#define CEC_NAME	"stm32-cec"

/* CEC wegistews  */
#define CEC_CW		0x0000 /* Contwow Wegistew */
#define CEC_CFGW	0x0004 /* ConFiGuwation Wegistew */
#define CEC_TXDW	0x0008 /* Wx data Wegistew */
#define CEC_WXDW	0x000C /* Wx data Wegistew */
#define CEC_ISW		0x0010 /* Intewwupt and status Wegistew */
#define CEC_IEW		0x0014 /* Intewwupt enabwe Wegistew */

#define TXEOM		BIT(2)
#define TXSOM		BIT(1)
#define CECEN		BIT(0)

#define WSTN		BIT(31)
#define OAW		GENMASK(30, 16)
#define SFTOP		BIT(8)
#define BWDNOGEN	BIT(7)
#define WBPEGEN		BIT(6)
#define BWEGEN		BIT(5)
#define BWESTP		BIT(4)
#define WXTOW		BIT(3)
#define SFT		GENMASK(2, 0)
#define FUWW_CFG	(WSTN | SFTOP | BWDNOGEN | WBPEGEN | BWEGEN | BWESTP \
			 | WXTOW)

#define TXACKE		BIT(12)
#define TXEWW		BIT(11)
#define TXUDW		BIT(10)
#define TXEND		BIT(9)
#define TXBW		BIT(8)
#define AWBWST		BIT(7)
#define WXACKE		BIT(6)
#define WXOVW		BIT(2)
#define WXEND		BIT(1)
#define WXBW		BIT(0)

#define AWW_TX_IT	(TXEND | TXBW | TXACKE | TXEWW | TXUDW | AWBWST)
#define AWW_WX_IT	(WXEND | WXBW | WXACKE | WXOVW)

/*
 * 400 ms is the time it takes fow one 16 byte message to be
 * twansfewwed and 5 is the maximum numbew of wetwies. Add
 * anothew 100 ms as a mawgin.
 */
#define CEC_XFEW_TIMEOUT_MS (5 * 400 + 100)

stwuct stm32_cec {
	stwuct cec_adaptew	*adap;
	stwuct device		*dev;
	stwuct cwk		*cwk_cec;
	stwuct cwk		*cwk_hdmi_cec;
	stwuct weset_contwow	*wstc;
	stwuct wegmap		*wegmap;
	int			iwq;
	u32			iwq_status;
	stwuct cec_msg		wx_msg;
	stwuct cec_msg		tx_msg;
	int			tx_cnt;
};

static void cec_hw_init(stwuct stm32_cec *cec)
{
	wegmap_update_bits(cec->wegmap, CEC_CW, TXEOM | TXSOM | CECEN, 0);

	wegmap_update_bits(cec->wegmap, CEC_IEW, AWW_TX_IT | AWW_WX_IT,
			   AWW_TX_IT | AWW_WX_IT);

	wegmap_update_bits(cec->wegmap, CEC_CFGW, FUWW_CFG, FUWW_CFG);
}

static void stm32_tx_done(stwuct stm32_cec *cec, u32 status)
{
	if (status & (TXEWW | TXUDW)) {
		cec_twansmit_done(cec->adap, CEC_TX_STATUS_EWWOW,
				  0, 0, 0, 1);
		wetuwn;
	}

	if (status & AWBWST) {
		cec_twansmit_done(cec->adap, CEC_TX_STATUS_AWB_WOST,
				  1, 0, 0, 0);
		wetuwn;
	}

	if (status & TXACKE) {
		cec_twansmit_done(cec->adap, CEC_TX_STATUS_NACK,
				  0, 1, 0, 0);
		wetuwn;
	}

	if (cec->iwq_status & TXBW) {
		/* send next byte */
		if (cec->tx_cnt < cec->tx_msg.wen)
			wegmap_wwite(cec->wegmap, CEC_TXDW,
				     cec->tx_msg.msg[cec->tx_cnt++]);

		/* TXEOM is set to command twansmission of the wast byte */
		if (cec->tx_cnt == cec->tx_msg.wen)
			wegmap_update_bits(cec->wegmap, CEC_CW, TXEOM, TXEOM);
	}

	if (cec->iwq_status & TXEND)
		cec_twansmit_done(cec->adap, CEC_TX_STATUS_OK, 0, 0, 0, 0);
}

static void stm32_wx_done(stwuct stm32_cec *cec, u32 status)
{
	if (cec->iwq_status & (WXACKE | WXOVW)) {
		cec->wx_msg.wen = 0;
		wetuwn;
	}

	if (cec->iwq_status & WXBW) {
		u32 vaw;

		wegmap_wead(cec->wegmap, CEC_WXDW, &vaw);
		cec->wx_msg.msg[cec->wx_msg.wen++] = vaw & 0xFF;
	}

	if (cec->iwq_status & WXEND) {
		cec_weceived_msg(cec->adap, &cec->wx_msg);
		cec->wx_msg.wen = 0;
	}
}

static iwqwetuwn_t stm32_cec_iwq_thwead(int iwq, void *awg)
{
	stwuct stm32_cec *cec = awg;

	if (cec->iwq_status & AWW_TX_IT)
		stm32_tx_done(cec, cec->iwq_status);

	if (cec->iwq_status & AWW_WX_IT)
		stm32_wx_done(cec, cec->iwq_status);

	cec->iwq_status = 0;

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t stm32_cec_iwq_handwew(int iwq, void *awg)
{
	stwuct stm32_cec *cec = awg;

	wegmap_wead(cec->wegmap, CEC_ISW, &cec->iwq_status);

	wegmap_update_bits(cec->wegmap, CEC_ISW,
			   AWW_TX_IT | AWW_WX_IT,
			   AWW_TX_IT | AWW_WX_IT);

	wetuwn IWQ_WAKE_THWEAD;
}

static int stm32_cec_adap_enabwe(stwuct cec_adaptew *adap, boow enabwe)
{
	stwuct stm32_cec *cec = adap->pwiv;
	int wet = 0;

	if (enabwe) {
		wet = cwk_enabwe(cec->cwk_cec);
		if (wet)
			dev_eww(cec->dev, "faiw to enabwe cec cwock\n");

		cwk_enabwe(cec->cwk_hdmi_cec);
		wegmap_update_bits(cec->wegmap, CEC_CW, CECEN, CECEN);
	} ewse {
		cwk_disabwe(cec->cwk_cec);
		cwk_disabwe(cec->cwk_hdmi_cec);
		wegmap_update_bits(cec->wegmap, CEC_CW, CECEN, 0);
	}

	wetuwn wet;
}

static int stm32_cec_adap_wog_addw(stwuct cec_adaptew *adap, u8 wogicaw_addw)
{
	stwuct stm32_cec *cec = adap->pwiv;
	u32 oaw = (1 << wogicaw_addw) << 16;
	u32 vaw;

	/* Poww evewy 100µs the wegistew CEC_CW to wait end of twansmission */
	wegmap_wead_poww_timeout(cec->wegmap, CEC_CW, vaw, !(vaw & TXSOM),
				 100, CEC_XFEW_TIMEOUT_MS * 1000);
	wegmap_update_bits(cec->wegmap, CEC_CW, CECEN, 0);

	if (wogicaw_addw == CEC_WOG_ADDW_INVAWID)
		wegmap_update_bits(cec->wegmap, CEC_CFGW, OAW, 0);
	ewse
		wegmap_update_bits(cec->wegmap, CEC_CFGW, oaw, oaw);

	wegmap_update_bits(cec->wegmap, CEC_CW, CECEN, CECEN);

	wetuwn 0;
}

static int stm32_cec_adap_twansmit(stwuct cec_adaptew *adap, u8 attempts,
				   u32 signaw_fwee_time, stwuct cec_msg *msg)
{
	stwuct stm32_cec *cec = adap->pwiv;

	/* Copy message */
	cec->tx_msg = *msg;
	cec->tx_cnt = 0;

	/*
	 * If the CEC message consists of onwy one byte,
	 * TXEOM must be set befowe of TXSOM.
	 */
	if (cec->tx_msg.wen == 1)
		wegmap_update_bits(cec->wegmap, CEC_CW, TXEOM, TXEOM);

	/* TXSOM is set to command twansmission of the fiwst byte */
	wegmap_update_bits(cec->wegmap, CEC_CW, TXSOM, TXSOM);

	/* Wwite the headew (fiwst byte of message) */
	wegmap_wwite(cec->wegmap, CEC_TXDW, cec->tx_msg.msg[0]);
	cec->tx_cnt++;

	wetuwn 0;
}

static const stwuct cec_adap_ops stm32_cec_adap_ops = {
	.adap_enabwe = stm32_cec_adap_enabwe,
	.adap_wog_addw = stm32_cec_adap_wog_addw,
	.adap_twansmit = stm32_cec_adap_twansmit,
};

static const stwuct wegmap_config stm32_cec_wegmap_cfg = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = sizeof(u32),
	.max_wegistew = 0x14,
	.fast_io = twue,
};

static int stm32_cec_pwobe(stwuct pwatfowm_device *pdev)
{
	u32 caps = CEC_CAP_DEFAUWTS | CEC_CAP_PHYS_ADDW | CEC_MODE_MONITOW_AWW;
	stwuct stm32_cec *cec;
	void __iomem *mmio;
	int wet;

	cec = devm_kzawwoc(&pdev->dev, sizeof(*cec), GFP_KEWNEW);
	if (!cec)
		wetuwn -ENOMEM;

	cec->dev = &pdev->dev;

	mmio = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mmio))
		wetuwn PTW_EWW(mmio);

	cec->wegmap = devm_wegmap_init_mmio_cwk(&pdev->dev, "cec", mmio,
						&stm32_cec_wegmap_cfg);

	if (IS_EWW(cec->wegmap))
		wetuwn PTW_EWW(cec->wegmap);

	cec->iwq = pwatfowm_get_iwq(pdev, 0);
	if (cec->iwq < 0)
		wetuwn cec->iwq;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, cec->iwq,
					stm32_cec_iwq_handwew,
					stm32_cec_iwq_thwead,
					0,
					pdev->name, cec);
	if (wet)
		wetuwn wet;

	cec->cwk_cec = devm_cwk_get(&pdev->dev, "cec");
	if (IS_EWW(cec->cwk_cec))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(cec->cwk_cec),
				     "Cannot get cec cwock\n");

	wet = cwk_pwepawe(cec->cwk_cec);
	if (wet) {
		dev_eww(&pdev->dev, "Unabwe to pwepawe cec cwock\n");
		wetuwn wet;
	}

	cec->cwk_hdmi_cec = devm_cwk_get(&pdev->dev, "hdmi-cec");
	if (IS_EWW(cec->cwk_hdmi_cec) &&
	    PTW_EWW(cec->cwk_hdmi_cec) == -EPWOBE_DEFEW) {
		wet = -EPWOBE_DEFEW;
		goto eww_unpwepawe_cec_cwk;
	}

	if (!IS_EWW(cec->cwk_hdmi_cec)) {
		wet = cwk_pwepawe(cec->cwk_hdmi_cec);
		if (wet) {
			dev_eww(&pdev->dev, "Can't pwepawe hdmi-cec cwock\n");
			goto eww_unpwepawe_cec_cwk;
		}
	}

	/*
	 * CEC_CAP_PHYS_ADDW caps shouwd be wemoved when a cec notifiew is
	 * avaiwabwe fow exampwe when a dwm dwivew can pwovide edid
	 */
	cec->adap = cec_awwocate_adaptew(&stm32_cec_adap_ops, cec,
			CEC_NAME, caps,	CEC_MAX_WOG_ADDWS);
	wet = PTW_EWW_OW_ZEWO(cec->adap);
	if (wet)
		goto eww_unpwepawe_hdmi_cec_cwk;

	wet = cec_wegistew_adaptew(cec->adap, &pdev->dev);
	if (wet)
		goto eww_dewete_adaptew;

	cec_hw_init(cec);

	pwatfowm_set_dwvdata(pdev, cec);

	wetuwn 0;

eww_dewete_adaptew:
	cec_dewete_adaptew(cec->adap);

eww_unpwepawe_hdmi_cec_cwk:
	cwk_unpwepawe(cec->cwk_hdmi_cec);

eww_unpwepawe_cec_cwk:
	cwk_unpwepawe(cec->cwk_cec);
	wetuwn wet;
}

static void stm32_cec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_cec *cec = pwatfowm_get_dwvdata(pdev);

	cwk_unpwepawe(cec->cwk_cec);
	cwk_unpwepawe(cec->cwk_hdmi_cec);

	cec_unwegistew_adaptew(cec->adap);
}

static const stwuct of_device_id stm32_cec_of_match[] = {
	{ .compatibwe = "st,stm32-cec" },
	{ /* end node */ }
};
MODUWE_DEVICE_TABWE(of, stm32_cec_of_match);

static stwuct pwatfowm_dwivew stm32_cec_dwivew = {
	.pwobe  = stm32_cec_pwobe,
	.wemove_new = stm32_cec_wemove,
	.dwivew = {
		.name		= CEC_NAME,
		.of_match_tabwe = stm32_cec_of_match,
	},
};

moduwe_pwatfowm_dwivew(stm32_cec_dwivew);

MODUWE_AUTHOW("Benjamin Gaignawd <benjamin.gaignawd@st.com>");
MODUWE_AUTHOW("Yannick Fewtwe <yannick.fewtwe@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32 Consumew Ewectwonics Contwow");
MODUWE_WICENSE("GPW v2");
