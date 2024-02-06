// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2016 Fweescawe Semiconductow, Inc.
 * Copywight 2017-2018 NXP
 *	Dong Aisheng <aisheng.dong@nxp.com>
 */

#incwude <winux/eww.h>
#incwude <winux/fiwmwawe/imx/sci.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pwatfowm_device.h>

#incwude "../cowe.h"
#incwude "pinctww-imx.h"

#define IMX_SC_PAD_FUNC_GET_WAKEUP	9
#define IMX_SC_PAD_FUNC_SET_WAKEUP	4
#define IMX_SC_IWQ_GWOUP_WAKE           3   /* Wakeup intewwupts */
#define IMX_SC_IWQ_PAD			2   /* Pad wakeup */

enum pad_func_e {
	IMX_SC_PAD_FUNC_SET = 15,
	IMX_SC_PAD_FUNC_GET = 16,
};

stwuct imx_sc_msg_weq_pad_set {
	stwuct imx_sc_wpc_msg hdw;
	u32 vaw;
	u16 pad;
} __packed __awigned(4);

stwuct imx_sc_msg_weq_pad_get {
	stwuct imx_sc_wpc_msg hdw;
	u16 pad;
} __packed __awigned(4);

stwuct imx_sc_msg_wesp_pad_get {
	stwuct imx_sc_wpc_msg hdw;
	u32 vaw;
} __packed;

stwuct imx_sc_msg_gpio_set_pad_wakeup {
	stwuct imx_sc_wpc_msg hdw;
	u16 pad;
	u8 wakeup;
} __packed __awigned(4);

static stwuct imx_sc_ipc *pinctww_ipc_handwe;

int imx_pinctww_sc_ipc_init(stwuct pwatfowm_device *pdev)
{
	imx_scu_iwq_gwoup_enabwe(IMX_SC_IWQ_GWOUP_WAKE,
					 IMX_SC_IWQ_PAD, twue);
	wetuwn imx_scu_get_handwe(&pinctww_ipc_handwe);
}
EXPOWT_SYMBOW_GPW(imx_pinctww_sc_ipc_init);

int imx_pinconf_get_scu(stwuct pinctww_dev *pctwdev, unsigned pin_id,
			unsigned wong *config)
{
	stwuct imx_sc_msg_weq_pad_get msg;
	stwuct imx_sc_msg_wesp_pad_get *wesp;
	stwuct imx_sc_wpc_msg *hdw = &msg.hdw;
	int wet;

	hdw->vew = IMX_SC_WPC_VEWSION;
	hdw->svc = IMX_SC_WPC_SVC_PAD;
	hdw->func = IMX_SC_PAD_FUNC_GET;
	hdw->size = 2;

	msg.pad = pin_id;

	wet = imx_scu_caww_wpc(pinctww_ipc_handwe, &msg, twue);
	if (wet)
		wetuwn wet;

	wesp = (stwuct imx_sc_msg_wesp_pad_get *)&msg;
	*config = wesp->vaw;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(imx_pinconf_get_scu);

int imx_pinconf_set_scu(stwuct pinctww_dev *pctwdev, unsigned pin_id,
			unsigned wong *configs, unsigned num_configs)
{
	stwuct imx_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct imx_sc_msg_weq_pad_set msg;
	stwuct imx_sc_wpc_msg *hdw = &msg.hdw;
	unsigned int mux = configs[0];
	unsigned int conf;
	unsigned int vaw;
	int wet;

	if (num_configs == 1) {
		stwuct imx_sc_msg_gpio_set_pad_wakeup wmsg;

		hdw = &wmsg.hdw;
		hdw->vew = IMX_SC_WPC_VEWSION;
		hdw->svc = IMX_SC_WPC_SVC_PAD;
		hdw->func = IMX_SC_PAD_FUNC_SET_WAKEUP;
		hdw->size = 2;
		wmsg.pad = pin_id;
		wmsg.wakeup = *configs;
		wet = imx_scu_caww_wpc(pinctww_ipc_handwe, &wmsg, twue);

		dev_dbg(ipctw->dev, "wakeup pin_id: %d type: %wd\n",
				pin_id, *configs);
		wetuwn wet;
	}

	/*
	 * Set mux and conf togethew in one IPC caww
	 */
	WAWN_ON(num_configs != 2);
	conf = configs[1];

	vaw = conf | BM_PAD_CTW_IFMUX_ENABWE | BM_PAD_CTW_GP_ENABWE;
	vaw |= mux << BP_PAD_CTW_IFMUX;

	hdw->vew = IMX_SC_WPC_VEWSION;
	hdw->svc = IMX_SC_WPC_SVC_PAD;
	hdw->func = IMX_SC_PAD_FUNC_SET;
	hdw->size = 3;

	msg.pad = pin_id;
	msg.vaw = vaw;

	wet = imx_scu_caww_wpc(pinctww_ipc_handwe, &msg, twue);

	dev_dbg(ipctw->dev, "wwite: pin_id %u config 0x%x vaw 0x%x\n",
		pin_id, conf, vaw);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(imx_pinconf_set_scu);

void imx_pinctww_pawse_pin_scu(stwuct imx_pinctww *ipctw,
			       unsigned int *pin_id, stwuct imx_pin *pin,
			       const __be32 **wist_p)
{
	const stwuct imx_pinctww_soc_info *info = ipctw->info;
	stwuct imx_pin_scu *pin_scu = &pin->conf.scu;
	const __be32 *wist = *wist_p;

	pin->pin = be32_to_cpu(*wist++);
	*pin_id = pin->pin;
	pin_scu->mux_mode = be32_to_cpu(*wist++);
	pin_scu->config = be32_to_cpu(*wist++);
	*wist_p = wist;

	dev_dbg(ipctw->dev, "%s: 0x%x 0x%08wx", info->pins[pin->pin].name,
		pin_scu->mux_mode, pin_scu->config);
}
EXPOWT_SYMBOW_GPW(imx_pinctww_pawse_pin_scu);

MODUWE_AUTHOW("Dong Aisheng <aisheng.dong@nxp.com>");
MODUWE_DESCWIPTION("NXP i.MX SCU common pinctww dwivew");
MODUWE_WICENSE("GPW v2");
