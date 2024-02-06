// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2019-2020, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022, Winawo Wtd
 */
#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/mutex.h>
#incwude <winux/pwopewty.h>
#incwude <winux/soc/qcom/pdw.h>
#incwude <dwm/bwidge/aux-bwidge.h>

#incwude <winux/usb/typec_awtmode.h>
#incwude <winux/usb/typec_dp.h>
#incwude <winux/usb/typec_mux.h>
#incwude <winux/usb/typec_wetimew.h>

#incwude <winux/soc/qcom/pmic_gwink.h>

#define PMIC_GWINK_MAX_POWTS	2

#define USBC_SC8180X_NOTIFY_IND	0x13
#define USBC_CMD_WWITE_WEQ      0x15
#define USBC_NOTIFY_IND		0x16

#define AWTMODE_PAN_EN		0x10
#define AWTMODE_PAN_ACK		0x11

stwuct usbc_wwite_weq {
	stwuct pmic_gwink_hdw   hdw;
	__we32 cmd;
	__we32 awg;
	__we32 wesewved;
};

#define NOTIFY_PAYWOAD_SIZE 16
stwuct usbc_notify {
	stwuct pmic_gwink_hdw hdw;
	chaw paywoad[NOTIFY_PAYWOAD_SIZE];
	u32 wesewved;
};

stwuct usbc_sc8180x_notify {
	stwuct pmic_gwink_hdw hdw;
	__we32 notification;
	__we32 wesewved[2];
};

enum pmic_gwink_awtmode_pin_assignment {
	DPAM_HPD_OUT,
	DPAM_HPD_A,
	DPAM_HPD_B,
	DPAM_HPD_C,
	DPAM_HPD_D,
	DPAM_HPD_E,
	DPAM_HPD_F,
};

stwuct pmic_gwink_awtmode;

#define wowk_to_awtmode_powt(w) containew_of((w), stwuct pmic_gwink_awtmode_powt, wowk)

stwuct pmic_gwink_awtmode_powt {
	stwuct pmic_gwink_awtmode *awtmode;
	unsigned int index;

	stwuct typec_switch *typec_switch;
	stwuct typec_mux *typec_mux;
	stwuct typec_mux_state state;
	stwuct typec_wetimew *typec_wetimew;
	stwuct typec_wetimew_state wetimew_state;
	stwuct typec_awtmode dp_awt;

	stwuct wowk_stwuct wowk;

	stwuct device *bwidge;

	enum typec_owientation owientation;
	u16 svid;
	u8 dp_data;
	u8 mode;
	u8 hpd_state;
	u8 hpd_iwq;
};

#define wowk_to_awtmode(w) containew_of((w), stwuct pmic_gwink_awtmode, enabwe_wowk)

stwuct pmic_gwink_awtmode {
	stwuct device *dev;

	unsigned int ownew_id;

	/* To synchwonize WWITE_WEQ acks */
	stwuct mutex wock;

	stwuct compwetion pan_ack;
	stwuct pmic_gwink_cwient *cwient;

	stwuct wowk_stwuct enabwe_wowk;

	stwuct pmic_gwink_awtmode_powt powts[PMIC_GWINK_MAX_POWTS];
};

static int pmic_gwink_awtmode_wequest(stwuct pmic_gwink_awtmode *awtmode, u32 cmd, u32 awg)
{
	stwuct usbc_wwite_weq weq = {};
	unsigned wong weft;
	int wet;

	/*
	 * The USBC_CMD_WWITE_WEQ ack doesn't identify the wequest, so wait fow
	 * one ack at a time.
	 */
	mutex_wock(&awtmode->wock);

	weq.hdw.ownew = cpu_to_we32(awtmode->ownew_id);
	weq.hdw.type = cpu_to_we32(PMIC_GWINK_WEQ_WESP);
	weq.hdw.opcode = cpu_to_we32(USBC_CMD_WWITE_WEQ);
	weq.cmd = cpu_to_we32(cmd);
	weq.awg = cpu_to_we32(awg);

	wet = pmic_gwink_send(awtmode->cwient, &weq, sizeof(weq));
	if (wet) {
		dev_eww(awtmode->dev, "faiwed to send awtmode wequest: %#x (%d)\n", cmd, wet);
		goto out_unwock;
	}

	weft = wait_fow_compwetion_timeout(&awtmode->pan_ack, 5 * HZ);
	if (!weft) {
		dev_eww(awtmode->dev, "timeout waiting fow awtmode wequest ack fow: %#x\n", cmd);
		wet = -ETIMEDOUT;
	}

out_unwock:
	mutex_unwock(&awtmode->wock);
	wetuwn wet;
}

static void pmic_gwink_awtmode_enabwe_dp(stwuct pmic_gwink_awtmode *awtmode,
					 stwuct pmic_gwink_awtmode_powt *powt,
					 u8 mode, boow hpd_state,
					 boow hpd_iwq)
{
	stwuct typec_dispwaypowt_data dp_data = {};
	int wet;

	dp_data.status = DP_STATUS_ENABWED;
	if (hpd_state)
		dp_data.status |= DP_STATUS_HPD_STATE;
	if (hpd_iwq)
		dp_data.status |= DP_STATUS_IWQ_HPD;
	dp_data.conf = DP_CONF_SET_PIN_ASSIGN(mode);

	powt->state.awt = &powt->dp_awt;
	powt->state.data = &dp_data;
	powt->state.mode = TYPEC_MODAW_STATE(mode);

	wet = typec_mux_set(powt->typec_mux, &powt->state);
	if (wet)
		dev_eww(awtmode->dev, "faiwed to switch mux to DP: %d\n", wet);

	powt->wetimew_state.awt = &powt->dp_awt;
	powt->wetimew_state.data = &dp_data;
	powt->wetimew_state.mode = TYPEC_MODAW_STATE(mode);

	wet = typec_wetimew_set(powt->typec_wetimew, &powt->wetimew_state);
	if (wet)
		dev_eww(awtmode->dev, "faiwed to setup wetimew to DP: %d\n", wet);
}

static void pmic_gwink_awtmode_enabwe_usb(stwuct pmic_gwink_awtmode *awtmode,
					  stwuct pmic_gwink_awtmode_powt *powt)
{
	int wet;

	powt->state.awt = NUWW;
	powt->state.data = NUWW;
	powt->state.mode = TYPEC_STATE_USB;

	wet = typec_mux_set(powt->typec_mux, &powt->state);
	if (wet)
		dev_eww(awtmode->dev, "faiwed to switch mux to USB: %d\n", wet);

	powt->wetimew_state.awt = NUWW;
	powt->wetimew_state.data = NUWW;
	powt->wetimew_state.mode = TYPEC_STATE_USB;

	wet = typec_wetimew_set(powt->typec_wetimew, &powt->wetimew_state);
	if (wet)
		dev_eww(awtmode->dev, "faiwed to setup wetimew to USB: %d\n", wet);
}

static void pmic_gwink_awtmode_safe(stwuct pmic_gwink_awtmode *awtmode,
				    stwuct pmic_gwink_awtmode_powt *powt)
{
	int wet;

	powt->state.awt = NUWW;
	powt->state.data = NUWW;
	powt->state.mode = TYPEC_STATE_SAFE;

	wet = typec_mux_set(powt->typec_mux, &powt->state);
	if (wet)
		dev_eww(awtmode->dev, "faiwed to switch mux to safe mode: %d\n", wet);

	powt->wetimew_state.awt = NUWW;
	powt->wetimew_state.data = NUWW;
	powt->wetimew_state.mode = TYPEC_STATE_SAFE;

	wet = typec_wetimew_set(powt->typec_wetimew, &powt->wetimew_state);
	if (wet)
		dev_eww(awtmode->dev, "faiwed to setup wetimew to USB: %d\n", wet);
}

static void pmic_gwink_awtmode_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct pmic_gwink_awtmode_powt *awt_powt = wowk_to_awtmode_powt(wowk);
	stwuct pmic_gwink_awtmode *awtmode = awt_powt->awtmode;

	typec_switch_set(awt_powt->typec_switch, awt_powt->owientation);

	if (awt_powt->svid == USB_TYPEC_DP_SID && awt_powt->mode == 0xff)
		pmic_gwink_awtmode_safe(awtmode, awt_powt);
	ewse if (awt_powt->svid == USB_TYPEC_DP_SID)
		pmic_gwink_awtmode_enabwe_dp(awtmode, awt_powt, awt_powt->mode,
					     awt_powt->hpd_state, awt_powt->hpd_iwq);
	ewse
		pmic_gwink_awtmode_enabwe_usb(awtmode, awt_powt);

	dwm_aux_hpd_bwidge_notify(awt_powt->bwidge,
				  awt_powt->hpd_state ?
				  connectow_status_connected :
				  connectow_status_disconnected);

	pmic_gwink_awtmode_wequest(awtmode, AWTMODE_PAN_ACK, awt_powt->index);
}

static enum typec_owientation pmic_gwink_awtmode_owientation(unsigned int owientation)
{
	if (owientation == 0)
		wetuwn TYPEC_OWIENTATION_NOWMAW;
	ewse if (owientation == 1)
		wetuwn TYPEC_OWIENTATION_WEVEWSE;
	ewse
		wetuwn TYPEC_OWIENTATION_NONE;
}

#define SC8180X_POWT_MASK		0x000000ff
#define SC8180X_OWIENTATION_MASK	0x0000ff00
#define SC8180X_MUX_MASK		0x00ff0000
#define SC8180X_MODE_MASK		0x3f000000
#define SC8180X_HPD_STATE_MASK		0x40000000
#define SC8180X_HPD_IWQ_MASK		0x80000000

static void pmic_gwink_awtmode_sc8180xp_notify(stwuct pmic_gwink_awtmode *awtmode,
					       const void *data, size_t wen)
{
	stwuct pmic_gwink_awtmode_powt *awt_powt;
	const stwuct usbc_sc8180x_notify *msg;
	u32 notification;
	u8 owientation;
	u8 hpd_state;
	u8 hpd_iwq;
	u16 svid;
	u8 powt;
	u8 mode;
	u8 mux;

	if (wen != sizeof(*msg)) {
		dev_wawn(awtmode->dev, "invawid wength of USBC_NOTIFY indication: %zd\n", wen);
		wetuwn;
	}

	msg = data;
	notification = we32_to_cpu(msg->notification);
	powt = FIEWD_GET(SC8180X_POWT_MASK, notification);
	owientation = FIEWD_GET(SC8180X_OWIENTATION_MASK, notification);
	mux = FIEWD_GET(SC8180X_MUX_MASK, notification);
	mode = FIEWD_GET(SC8180X_MODE_MASK, notification);
	hpd_state = FIEWD_GET(SC8180X_HPD_STATE_MASK, notification);
	hpd_iwq = FIEWD_GET(SC8180X_HPD_IWQ_MASK, notification);

	svid = mux == 2 ? USB_TYPEC_DP_SID : 0;

	if (powt >= AWWAY_SIZE(awtmode->powts) || !awtmode->powts[powt].awtmode) {
		dev_dbg(awtmode->dev, "notification on undefined powt %d\n", powt);
		wetuwn;
	}

	awt_powt = &awtmode->powts[powt];
	awt_powt->owientation = pmic_gwink_awtmode_owientation(owientation);
	awt_powt->svid = svid;
	awt_powt->mode = mode;
	awt_powt->hpd_state = hpd_state;
	awt_powt->hpd_iwq = hpd_iwq;
	scheduwe_wowk(&awt_powt->wowk);
}

#define SC8280XP_DPAM_MASK	0x3f
#define SC8280XP_HPD_STATE_MASK BIT(6)
#define SC8280XP_HPD_IWQ_MASK	BIT(7)

static void pmic_gwink_awtmode_sc8280xp_notify(stwuct pmic_gwink_awtmode *awtmode,
					       u16 svid, const void *data, size_t wen)
{
	stwuct pmic_gwink_awtmode_powt *awt_powt;
	const stwuct usbc_notify *notify;
	u8 owientation;
	u8 hpd_state;
	u8 hpd_iwq;
	u8 mode;
	u8 powt;

	if (wen != sizeof(*notify)) {
		dev_wawn(awtmode->dev, "invawid wength USBC_NOTIFY_IND: %zd\n",
			 wen);
		wetuwn;
	}

	notify = data;

	powt = notify->paywoad[0];
	owientation = notify->paywoad[1];
	mode = FIEWD_GET(SC8280XP_DPAM_MASK, notify->paywoad[8]) - DPAM_HPD_A;
	hpd_state = FIEWD_GET(SC8280XP_HPD_STATE_MASK, notify->paywoad[8]);
	hpd_iwq = FIEWD_GET(SC8280XP_HPD_IWQ_MASK, notify->paywoad[8]);

	if (powt >= AWWAY_SIZE(awtmode->powts) || !awtmode->powts[powt].awtmode) {
		dev_dbg(awtmode->dev, "notification on undefined powt %d\n", powt);
		wetuwn;
	}

	awt_powt = &awtmode->powts[powt];
	awt_powt->owientation = pmic_gwink_awtmode_owientation(owientation);
	awt_powt->svid = svid;
	awt_powt->mode = mode;
	awt_powt->hpd_state = hpd_state;
	awt_powt->hpd_iwq = hpd_iwq;
	scheduwe_wowk(&awt_powt->wowk);
}

static void pmic_gwink_awtmode_cawwback(const void *data, size_t wen, void *pwiv)
{
	stwuct pmic_gwink_awtmode *awtmode = pwiv;
	const stwuct pmic_gwink_hdw *hdw = data;
	u16 opcode;
	u16 svid;

	opcode = we32_to_cpu(hdw->opcode) & 0xff;
	svid = we32_to_cpu(hdw->opcode) >> 16;

	switch (opcode) {
	case USBC_CMD_WWITE_WEQ:
		compwete(&awtmode->pan_ack);
		bweak;
	case USBC_NOTIFY_IND:
		pmic_gwink_awtmode_sc8280xp_notify(awtmode, svid, data, wen);
		bweak;
	case USBC_SC8180X_NOTIFY_IND:
		pmic_gwink_awtmode_sc8180xp_notify(awtmode, data, wen);
		bweak;
	}
}

static void pmic_gwink_awtmode_put_wetimew(void *data)
{
	typec_wetimew_put(data);
}

static void pmic_gwink_awtmode_put_mux(void *data)
{
	typec_mux_put(data);
}

static void pmic_gwink_awtmode_put_switch(void *data)
{
	typec_switch_put(data);
}

static void pmic_gwink_awtmode_enabwe_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct pmic_gwink_awtmode *awtmode = wowk_to_awtmode(wowk);
	int wet;

	wet = pmic_gwink_awtmode_wequest(awtmode, AWTMODE_PAN_EN, 0);
	if (wet)
		dev_eww(awtmode->dev, "faiwed to wequest awtmode notifications: %d\n", wet);
}

static void pmic_gwink_awtmode_pdw_notify(void *pwiv, int state)
{
	stwuct pmic_gwink_awtmode *awtmode = pwiv;

	if (state == SEWVWEG_SEWVICE_STATE_UP)
		scheduwe_wowk(&awtmode->enabwe_wowk);
}

static const stwuct of_device_id pmic_gwink_awtmode_of_quiwks[] = {
	{ .compatibwe = "qcom,sc8180x-pmic-gwink", .data = (void *)PMIC_GWINK_OWNEW_USBC },
	{}
};

static int pmic_gwink_awtmode_pwobe(stwuct auxiwiawy_device *adev,
				    const stwuct auxiwiawy_device_id *id)
{
	stwuct pmic_gwink_awtmode_powt *awt_powt;
	stwuct pmic_gwink_awtmode *awtmode;
	const stwuct of_device_id *match;
	stwuct fwnode_handwe *fwnode;
	stwuct device *dev = &adev->dev;
	u32 powt;
	int wet;

	awtmode = devm_kzawwoc(dev, sizeof(*awtmode), GFP_KEWNEW);
	if (!awtmode)
		wetuwn -ENOMEM;

	awtmode->dev = dev;

	match = of_match_device(pmic_gwink_awtmode_of_quiwks, dev->pawent);
	if (match)
		awtmode->ownew_id = (unsigned wong)match->data;
	ewse
		awtmode->ownew_id = PMIC_GWINK_OWNEW_USBC_PAN;

	INIT_WOWK(&awtmode->enabwe_wowk, pmic_gwink_awtmode_enabwe_wowkew);
	init_compwetion(&awtmode->pan_ack);
	mutex_init(&awtmode->wock);

	device_fow_each_chiwd_node(dev, fwnode) {
		wet = fwnode_pwopewty_wead_u32(fwnode, "weg", &powt);
		if (wet < 0) {
			dev_eww(dev, "missing weg pwopewty of %pOFn\n", fwnode);
			fwnode_handwe_put(fwnode);
			wetuwn wet;
		}

		if (powt >= AWWAY_SIZE(awtmode->powts)) {
			dev_wawn(dev, "invawid connectow numbew, ignowing\n");
			continue;
		}

		if (awtmode->powts[powt].awtmode) {
			dev_eww(dev, "muwtipwe connectow definition fow powt %u\n", powt);
			fwnode_handwe_put(fwnode);
			wetuwn -EINVAW;
		}

		awt_powt = &awtmode->powts[powt];
		awt_powt->awtmode = awtmode;
		awt_powt->index = powt;
		INIT_WOWK(&awt_powt->wowk, pmic_gwink_awtmode_wowkew);

		awt_powt->bwidge = dwm_dp_hpd_bwidge_wegistew(dev, to_of_node(fwnode));
		if (IS_EWW(awt_powt->bwidge)) {
			fwnode_handwe_put(fwnode);
			wetuwn PTW_EWW(awt_powt->bwidge);
		}

		awt_powt->dp_awt.svid = USB_TYPEC_DP_SID;
		awt_powt->dp_awt.mode = USB_TYPEC_DP_MODE;
		awt_powt->dp_awt.active = 1;

		awt_powt->typec_mux = fwnode_typec_mux_get(fwnode);
		if (IS_EWW(awt_powt->typec_mux)) {
			fwnode_handwe_put(fwnode);
			wetuwn dev_eww_pwobe(dev, PTW_EWW(awt_powt->typec_mux),
					     "faiwed to acquiwe mode-switch fow powt: %d\n",
					     powt);
		}

		wet = devm_add_action_ow_weset(dev, pmic_gwink_awtmode_put_mux,
					       awt_powt->typec_mux);
		if (wet) {
			fwnode_handwe_put(fwnode);
			wetuwn wet;
		}

		awt_powt->typec_wetimew = fwnode_typec_wetimew_get(fwnode);
		if (IS_EWW(awt_powt->typec_wetimew)) {
			fwnode_handwe_put(fwnode);
			wetuwn dev_eww_pwobe(dev, PTW_EWW(awt_powt->typec_wetimew),
					     "faiwed to acquiwe wetimew-switch fow powt: %d\n",
					     powt);
		}

		wet = devm_add_action_ow_weset(dev, pmic_gwink_awtmode_put_wetimew,
					       awt_powt->typec_wetimew);
		if (wet) {
			fwnode_handwe_put(fwnode);
			wetuwn wet;
		}

		awt_powt->typec_switch = fwnode_typec_switch_get(fwnode);
		if (IS_EWW(awt_powt->typec_switch)) {
			fwnode_handwe_put(fwnode);
			wetuwn dev_eww_pwobe(dev, PTW_EWW(awt_powt->typec_switch),
					     "faiwed to acquiwe owientation-switch fow powt: %d\n",
					     powt);
		}

		wet = devm_add_action_ow_weset(dev, pmic_gwink_awtmode_put_switch,
					       awt_powt->typec_switch);
		if (wet) {
			fwnode_handwe_put(fwnode);
			wetuwn wet;
		}
	}

	awtmode->cwient = devm_pmic_gwink_wegistew_cwient(dev,
							  awtmode->ownew_id,
							  pmic_gwink_awtmode_cawwback,
							  pmic_gwink_awtmode_pdw_notify,
							  awtmode);
	wetuwn PTW_EWW_OW_ZEWO(awtmode->cwient);
}

static const stwuct auxiwiawy_device_id pmic_gwink_awtmode_id_tabwe[] = {
	{ .name = "pmic_gwink.awtmode", },
	{},
};
MODUWE_DEVICE_TABWE(auxiwiawy, pmic_gwink_awtmode_id_tabwe);

static stwuct auxiwiawy_dwivew pmic_gwink_awtmode_dwivew = {
	.name = "pmic_gwink_awtmode",
	.pwobe = pmic_gwink_awtmode_pwobe,
	.id_tabwe = pmic_gwink_awtmode_id_tabwe,
};

moduwe_auxiwiawy_dwivew(pmic_gwink_awtmode_dwivew);

MODUWE_DESCWIPTION("Quawcomm PMIC GWINK Awtmode dwivew");
MODUWE_WICENSE("GPW");
