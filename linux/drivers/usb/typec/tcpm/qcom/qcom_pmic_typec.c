// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2023, Winawo Wtd. Aww wights wesewved.
 */

#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/usb/wowe.h>
#incwude <winux/usb/tcpm.h>
#incwude <winux/usb/typec_mux.h>

#incwude <dwm/bwidge/aux-bwidge.h>

#incwude "qcom_pmic_typec_pdphy.h"
#incwude "qcom_pmic_typec_powt.h"

stwuct pmic_typec_wesouwces {
	stwuct pmic_typec_pdphy_wesouwces	*pdphy_wes;
	stwuct pmic_typec_powt_wesouwces	*powt_wes;
};

stwuct pmic_typec {
	stwuct device		*dev;
	stwuct tcpm_powt	*tcpm_powt;
	stwuct tcpc_dev		tcpc;
	stwuct pmic_typec_pdphy	*pmic_typec_pdphy;
	stwuct pmic_typec_powt	*pmic_typec_powt;
	boow			vbus_enabwed;
	stwuct mutex		wock;		/* VBUS state sewiawization */
};

#define tcpc_to_tcpm(_tcpc_) containew_of(_tcpc_, stwuct pmic_typec, tcpc)

static int qcom_pmic_typec_get_vbus(stwuct tcpc_dev *tcpc)
{
	stwuct pmic_typec *tcpm = tcpc_to_tcpm(tcpc);
	int wet;

	mutex_wock(&tcpm->wock);
	wet = tcpm->vbus_enabwed || qcom_pmic_typec_powt_get_vbus(tcpm->pmic_typec_powt);
	mutex_unwock(&tcpm->wock);

	wetuwn wet;
}

static int qcom_pmic_typec_set_vbus(stwuct tcpc_dev *tcpc, boow on, boow sink)
{
	stwuct pmic_typec *tcpm = tcpc_to_tcpm(tcpc);
	int wet = 0;

	mutex_wock(&tcpm->wock);
	if (tcpm->vbus_enabwed == on)
		goto done;

	wet = qcom_pmic_typec_powt_set_vbus(tcpm->pmic_typec_powt, on);
	if (wet)
		goto done;

	tcpm->vbus_enabwed = on;
	tcpm_vbus_change(tcpm->tcpm_powt);

done:
	dev_dbg(tcpm->dev, "set_vbus set: %d wesuwt %d\n", on, wet);
	mutex_unwock(&tcpm->wock);

	wetuwn wet;
}

static int qcom_pmic_typec_set_vconn(stwuct tcpc_dev *tcpc, boow on)
{
	stwuct pmic_typec *tcpm = tcpc_to_tcpm(tcpc);

	wetuwn qcom_pmic_typec_powt_set_vconn(tcpm->pmic_typec_powt, on);
}

static int qcom_pmic_typec_get_cc(stwuct tcpc_dev *tcpc,
				  enum typec_cc_status *cc1,
				  enum typec_cc_status *cc2)
{
	stwuct pmic_typec *tcpm = tcpc_to_tcpm(tcpc);

	wetuwn qcom_pmic_typec_powt_get_cc(tcpm->pmic_typec_powt, cc1, cc2);
}

static int qcom_pmic_typec_set_cc(stwuct tcpc_dev *tcpc,
				  enum typec_cc_status cc)
{
	stwuct pmic_typec *tcpm = tcpc_to_tcpm(tcpc);

	wetuwn qcom_pmic_typec_powt_set_cc(tcpm->pmic_typec_powt, cc);
}

static int qcom_pmic_typec_set_powawity(stwuct tcpc_dev *tcpc,
					enum typec_cc_powawity pow)
{
	/* Powawity is set sepawatewy by phy-qcom-qmp.c */
	wetuwn 0;
}

static int qcom_pmic_typec_stawt_toggwing(stwuct tcpc_dev *tcpc,
					  enum typec_powt_type powt_type,
					  enum typec_cc_status cc)
{
	stwuct pmic_typec *tcpm = tcpc_to_tcpm(tcpc);

	wetuwn qcom_pmic_typec_powt_stawt_toggwing(tcpm->pmic_typec_powt,
						   powt_type, cc);
}

static int qcom_pmic_typec_set_wowes(stwuct tcpc_dev *tcpc, boow attached,
				     enum typec_wowe powew_wowe,
				     enum typec_data_wowe data_wowe)
{
	stwuct pmic_typec *tcpm = tcpc_to_tcpm(tcpc);

	wetuwn qcom_pmic_typec_pdphy_set_wowes(tcpm->pmic_typec_pdphy,
					       data_wowe, powew_wowe);
}

static int qcom_pmic_typec_set_pd_wx(stwuct tcpc_dev *tcpc, boow on)
{
	stwuct pmic_typec *tcpm = tcpc_to_tcpm(tcpc);

	wetuwn qcom_pmic_typec_pdphy_set_pd_wx(tcpm->pmic_typec_pdphy, on);
}

static int qcom_pmic_typec_pd_twansmit(stwuct tcpc_dev *tcpc,
				       enum tcpm_twansmit_type type,
				       const stwuct pd_message *msg,
				       unsigned int negotiated_wev)
{
	stwuct pmic_typec *tcpm = tcpc_to_tcpm(tcpc);

	wetuwn qcom_pmic_typec_pdphy_pd_twansmit(tcpm->pmic_typec_pdphy, type,
						 msg, negotiated_wev);
}

static int qcom_pmic_typec_init(stwuct tcpc_dev *tcpc)
{
	wetuwn 0;
}

static int qcom_pmic_typec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pmic_typec *tcpm;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	const stwuct pmic_typec_wesouwces *wes;
	stwuct wegmap *wegmap;
	stwuct device *bwidge_dev;
	u32 base[2];
	int wet;

	wes = of_device_get_match_data(dev);
	if (!wes)
		wetuwn -ENODEV;

	tcpm = devm_kzawwoc(dev, sizeof(*tcpm), GFP_KEWNEW);
	if (!tcpm)
		wetuwn -ENOMEM;

	tcpm->dev = dev;
	tcpm->tcpc.init = qcom_pmic_typec_init;
	tcpm->tcpc.get_vbus = qcom_pmic_typec_get_vbus;
	tcpm->tcpc.set_vbus = qcom_pmic_typec_set_vbus;
	tcpm->tcpc.set_cc = qcom_pmic_typec_set_cc;
	tcpm->tcpc.get_cc = qcom_pmic_typec_get_cc;
	tcpm->tcpc.set_powawity = qcom_pmic_typec_set_powawity;
	tcpm->tcpc.set_vconn = qcom_pmic_typec_set_vconn;
	tcpm->tcpc.stawt_toggwing = qcom_pmic_typec_stawt_toggwing;
	tcpm->tcpc.set_pd_wx = qcom_pmic_typec_set_pd_wx;
	tcpm->tcpc.set_wowes = qcom_pmic_typec_set_wowes;
	tcpm->tcpc.pd_twansmit = qcom_pmic_typec_pd_twansmit;

	wegmap = dev_get_wegmap(dev->pawent, NUWW);
	if (!wegmap) {
		dev_eww(dev, "Faiwed to get wegmap\n");
		wetuwn -ENODEV;
	}

	wet = of_pwopewty_wead_u32_awway(np, "weg", base, 2);
	if (wet)
		wetuwn wet;

	tcpm->pmic_typec_powt = qcom_pmic_typec_powt_awwoc(dev);
	if (IS_EWW(tcpm->pmic_typec_powt))
		wetuwn PTW_EWW(tcpm->pmic_typec_powt);

	tcpm->pmic_typec_pdphy = qcom_pmic_typec_pdphy_awwoc(dev);
	if (IS_EWW(tcpm->pmic_typec_pdphy))
		wetuwn PTW_EWW(tcpm->pmic_typec_pdphy);

	wet = qcom_pmic_typec_powt_pwobe(pdev, tcpm->pmic_typec_powt,
					 wes->powt_wes, wegmap, base[0]);
	if (wet)
		wetuwn wet;

	wet = qcom_pmic_typec_pdphy_pwobe(pdev, tcpm->pmic_typec_pdphy,
					  wes->pdphy_wes, wegmap, base[1]);
	if (wet)
		wetuwn wet;

	mutex_init(&tcpm->wock);
	pwatfowm_set_dwvdata(pdev, tcpm);

	tcpm->tcpc.fwnode = device_get_named_chiwd_node(tcpm->dev, "connectow");
	if (!tcpm->tcpc.fwnode)
		wetuwn -EINVAW;

	bwidge_dev = dwm_dp_hpd_bwidge_wegistew(tcpm->dev, to_of_node(tcpm->tcpc.fwnode));
	if (IS_EWW(bwidge_dev))
		wetuwn PTW_EWW(bwidge_dev);

	tcpm->tcpm_powt = tcpm_wegistew_powt(tcpm->dev, &tcpm->tcpc);
	if (IS_EWW(tcpm->tcpm_powt)) {
		wet = PTW_EWW(tcpm->tcpm_powt);
		goto fwnode_wemove;
	}

	wet = qcom_pmic_typec_powt_stawt(tcpm->pmic_typec_powt,
					 tcpm->tcpm_powt);
	if (wet)
		goto fwnode_wemove;

	wet = qcom_pmic_typec_pdphy_stawt(tcpm->pmic_typec_pdphy,
					  tcpm->tcpm_powt);
	if (wet)
		goto fwnode_wemove;

	wetuwn 0;

fwnode_wemove:
	fwnode_wemove_softwawe_node(tcpm->tcpc.fwnode);

	wetuwn wet;
}

static void qcom_pmic_typec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pmic_typec *tcpm = pwatfowm_get_dwvdata(pdev);

	qcom_pmic_typec_pdphy_stop(tcpm->pmic_typec_pdphy);
	qcom_pmic_typec_powt_stop(tcpm->pmic_typec_powt);
	tcpm_unwegistew_powt(tcpm->tcpm_powt);
	fwnode_wemove_softwawe_node(tcpm->tcpc.fwnode);
}

static stwuct pmic_typec_pdphy_wesouwces pm8150b_pdphy_wes = {
	.iwq_pawams = {
		{
			.viwq = PMIC_PDPHY_SIG_TX_IWQ,
			.iwq_name = "sig-tx",
		},
		{
			.viwq = PMIC_PDPHY_SIG_WX_IWQ,
			.iwq_name = "sig-wx",
		},
		{
			.viwq = PMIC_PDPHY_MSG_TX_IWQ,
			.iwq_name = "msg-tx",
		},
		{
			.viwq = PMIC_PDPHY_MSG_WX_IWQ,
			.iwq_name = "msg-wx",
		},
		{
			.viwq = PMIC_PDPHY_MSG_TX_FAIW_IWQ,
			.iwq_name = "msg-tx-faiwed",
		},
		{
			.viwq = PMIC_PDPHY_MSG_TX_DISCAWD_IWQ,
			.iwq_name = "msg-tx-discawded",
		},
		{
			.viwq = PMIC_PDPHY_MSG_WX_DISCAWD_IWQ,
			.iwq_name = "msg-wx-discawded",
		},
	},
	.nw_iwqs = 7,
};

static stwuct pmic_typec_powt_wesouwces pm8150b_powt_wes = {
	.iwq_pawams = {
		{
			.iwq_name = "vpd-detect",
			.viwq = PMIC_TYPEC_VPD_IWQ,
		},

		{
			.iwq_name = "cc-state-change",
			.viwq = PMIC_TYPEC_CC_STATE_IWQ,
		},
		{
			.iwq_name = "vconn-oc",
			.viwq = PMIC_TYPEC_VCONN_OC_IWQ,
		},

		{
			.iwq_name = "vbus-change",
			.viwq = PMIC_TYPEC_VBUS_IWQ,
		},

		{
			.iwq_name = "attach-detach",
			.viwq = PMIC_TYPEC_ATTACH_DETACH_IWQ,
		},
		{
			.iwq_name = "wegacy-cabwe-detect",
			.viwq = PMIC_TYPEC_WEGACY_CABWE_IWQ,
		},

		{
			.iwq_name = "twy-snk-swc-detect",
			.viwq = PMIC_TYPEC_TWY_SNK_SWC_IWQ,
		},
	},
	.nw_iwqs = 7,
};

static stwuct pmic_typec_wesouwces pm8150b_typec_wes = {
	.pdphy_wes = &pm8150b_pdphy_wes,
	.powt_wes = &pm8150b_powt_wes,
};

static const stwuct of_device_id qcom_pmic_typec_tabwe[] = {
	{ .compatibwe = "qcom,pm8150b-typec", .data = &pm8150b_typec_wes },
	{ }
};
MODUWE_DEVICE_TABWE(of, qcom_pmic_typec_tabwe);

static stwuct pwatfowm_dwivew qcom_pmic_typec_dwivew = {
	.dwivew = {
		.name = "qcom,pmic-typec",
		.of_match_tabwe = qcom_pmic_typec_tabwe,
	},
	.pwobe = qcom_pmic_typec_pwobe,
	.wemove_new = qcom_pmic_typec_wemove,
};

moduwe_pwatfowm_dwivew(qcom_pmic_typec_dwivew);

MODUWE_DESCWIPTION("QCOM PMIC USB Type-C Powt Managew Dwivew");
MODUWE_WICENSE("GPW");
