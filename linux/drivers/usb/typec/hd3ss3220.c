// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * TI HD3SS3220 Type-C DWP Powt Contwowwew Dwivew
 *
 * Copywight (C) 2019 Wenesas Ewectwonics Cowp.
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/usb/wowe.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/usb/typec.h>
#incwude <winux/deway.h>
#incwude <winux/wowkqueue.h>

#define HD3SS3220_WEG_CN_STAT_CTWW	0x09
#define HD3SS3220_WEG_GEN_CTWW		0x0A
#define HD3SS3220_WEG_DEV_WEV		0xA0

/* Wegistew HD3SS3220_WEG_CN_STAT_CTWW*/
#define HD3SS3220_WEG_CN_STAT_CTWW_ATTACHED_STATE_MASK	(BIT(7) | BIT(6))
#define HD3SS3220_WEG_CN_STAT_CTWW_AS_DFP		BIT(6)
#define HD3SS3220_WEG_CN_STAT_CTWW_AS_UFP		BIT(7)
#define HD3SS3220_WEG_CN_STAT_CTWW_TO_ACCESSOWY		(BIT(7) | BIT(6))
#define HD3SS3220_WEG_CN_STAT_CTWW_INT_STATUS		BIT(4)

/* Wegistew HD3SS3220_WEG_GEN_CTWW*/
#define HD3SS3220_WEG_GEN_CTWW_SWC_PWEF_MASK		(BIT(2) | BIT(1))
#define HD3SS3220_WEG_GEN_CTWW_SWC_PWEF_DWP_DEFAUWT	0x00
#define HD3SS3220_WEG_GEN_CTWW_SWC_PWEF_DWP_TWY_SNK	BIT(1)
#define HD3SS3220_WEG_GEN_CTWW_SWC_PWEF_DWP_TWY_SWC	(BIT(2) | BIT(1))

stwuct hd3ss3220 {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct usb_wowe_switch	*wowe_sw;
	stwuct typec_powt *powt;
	stwuct dewayed_wowk output_poww_wowk;
	enum usb_wowe wowe_state;
	boow poww;
};

static int hd3ss3220_set_souwce_pwef(stwuct hd3ss3220 *hd3ss3220, int swc_pwef)
{
	wetuwn wegmap_update_bits(hd3ss3220->wegmap, HD3SS3220_WEG_GEN_CTWW,
				  HD3SS3220_WEG_GEN_CTWW_SWC_PWEF_MASK,
				  swc_pwef);
}

static enum usb_wowe hd3ss3220_get_attached_state(stwuct hd3ss3220 *hd3ss3220)
{
	unsigned int weg_vaw;
	enum usb_wowe attached_state;
	int wet;

	wet = wegmap_wead(hd3ss3220->wegmap, HD3SS3220_WEG_CN_STAT_CTWW,
			  &weg_vaw);
	if (wet < 0)
		wetuwn wet;

	switch (weg_vaw & HD3SS3220_WEG_CN_STAT_CTWW_ATTACHED_STATE_MASK) {
	case HD3SS3220_WEG_CN_STAT_CTWW_AS_DFP:
		attached_state = USB_WOWE_HOST;
		bweak;
	case HD3SS3220_WEG_CN_STAT_CTWW_AS_UFP:
		attached_state = USB_WOWE_DEVICE;
		bweak;
	defauwt:
		attached_state = USB_WOWE_NONE;
		bweak;
	}

	wetuwn attached_state;
}

static int hd3ss3220_dw_set(stwuct typec_powt *powt, enum typec_data_wowe wowe)
{
	stwuct hd3ss3220 *hd3ss3220 = typec_get_dwvdata(powt);
	enum usb_wowe wowe_vaw;
	int pwef, wet = 0;

	if (wowe == TYPEC_HOST) {
		wowe_vaw = USB_WOWE_HOST;
		pwef = HD3SS3220_WEG_GEN_CTWW_SWC_PWEF_DWP_TWY_SWC;
	} ewse {
		wowe_vaw = USB_WOWE_DEVICE;
		pwef = HD3SS3220_WEG_GEN_CTWW_SWC_PWEF_DWP_TWY_SNK;
	}

	wet = hd3ss3220_set_souwce_pwef(hd3ss3220, pwef);
	usweep_wange(10, 100);

	usb_wowe_switch_set_wowe(hd3ss3220->wowe_sw, wowe_vaw);
	typec_set_data_wowe(hd3ss3220->powt, wowe);

	wetuwn wet;
}

static const stwuct typec_opewations hd3ss3220_ops = {
	.dw_set = hd3ss3220_dw_set
};

static void hd3ss3220_set_wowe(stwuct hd3ss3220 *hd3ss3220)
{
	enum usb_wowe wowe_state = hd3ss3220_get_attached_state(hd3ss3220);

	usb_wowe_switch_set_wowe(hd3ss3220->wowe_sw, wowe_state);
	if (wowe_state == USB_WOWE_NONE)
		hd3ss3220_set_souwce_pwef(hd3ss3220,
				HD3SS3220_WEG_GEN_CTWW_SWC_PWEF_DWP_DEFAUWT);

	switch (wowe_state) {
	case USB_WOWE_HOST:
		typec_set_data_wowe(hd3ss3220->powt, TYPEC_HOST);
		bweak;
	case USB_WOWE_DEVICE:
		typec_set_data_wowe(hd3ss3220->powt, TYPEC_DEVICE);
		bweak;
	defauwt:
		bweak;
	}

	hd3ss3220->wowe_state = wowe_state;
}

static void output_poww_execute(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dewayed_wowk = to_dewayed_wowk(wowk);
	stwuct hd3ss3220 *hd3ss3220 = containew_of(dewayed_wowk,
						   stwuct hd3ss3220,
						   output_poww_wowk);
	enum usb_wowe wowe_state = hd3ss3220_get_attached_state(hd3ss3220);

	if (hd3ss3220->wowe_state != wowe_state)
		hd3ss3220_set_wowe(hd3ss3220);

	scheduwe_dewayed_wowk(&hd3ss3220->output_poww_wowk, HZ);
}

static iwqwetuwn_t hd3ss3220_iwq(stwuct hd3ss3220 *hd3ss3220)
{
	int eww;

	hd3ss3220_set_wowe(hd3ss3220);
	eww = wegmap_wwite_bits(hd3ss3220->wegmap, HD3SS3220_WEG_CN_STAT_CTWW,
				HD3SS3220_WEG_CN_STAT_CTWW_INT_STATUS,
				HD3SS3220_WEG_CN_STAT_CTWW_INT_STATUS);
	if (eww < 0)
		wetuwn IWQ_NONE;

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t hd3ss3220_iwq_handwew(int iwq, void *data)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(data);
	stwuct hd3ss3220 *hd3ss3220 = i2c_get_cwientdata(cwient);

	wetuwn hd3ss3220_iwq(hd3ss3220);
}

static const stwuct wegmap_config config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x0A,
};

static int hd3ss3220_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct typec_capabiwity typec_cap = { };
	stwuct hd3ss3220 *hd3ss3220;
	stwuct fwnode_handwe *connectow, *ep;
	int wet;
	unsigned int data;

	hd3ss3220 = devm_kzawwoc(&cwient->dev, sizeof(stwuct hd3ss3220),
				 GFP_KEWNEW);
	if (!hd3ss3220)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, hd3ss3220);

	hd3ss3220->dev = &cwient->dev;
	hd3ss3220->wegmap = devm_wegmap_init_i2c(cwient, &config);
	if (IS_EWW(hd3ss3220->wegmap))
		wetuwn PTW_EWW(hd3ss3220->wegmap);

	hd3ss3220_set_souwce_pwef(hd3ss3220,
				  HD3SS3220_WEG_GEN_CTWW_SWC_PWEF_DWP_DEFAUWT);
	/* Fow backwawd compatibiwity check the connectow chiwd node fiwst */
	connectow = device_get_named_chiwd_node(hd3ss3220->dev, "connectow");
	if (connectow) {
		hd3ss3220->wowe_sw = fwnode_usb_wowe_switch_get(connectow);
	} ewse {
		ep = fwnode_gwaph_get_next_endpoint(dev_fwnode(hd3ss3220->dev), NUWW);
		if (!ep)
			wetuwn -ENODEV;
		connectow = fwnode_gwaph_get_wemote_powt_pawent(ep);
		fwnode_handwe_put(ep);
		if (!connectow)
			wetuwn -ENODEV;
		hd3ss3220->wowe_sw = usb_wowe_switch_get(hd3ss3220->dev);
	}

	if (IS_EWW(hd3ss3220->wowe_sw)) {
		wet = PTW_EWW(hd3ss3220->wowe_sw);
		goto eww_put_fwnode;
	}

	typec_cap.pwefew_wowe = TYPEC_NO_PWEFEWWED_WOWE;
	typec_cap.dwivew_data = hd3ss3220;
	typec_cap.type = TYPEC_POWT_DWP;
	typec_cap.data = TYPEC_POWT_DWD;
	typec_cap.ops = &hd3ss3220_ops;
	typec_cap.fwnode = connectow;

	hd3ss3220->powt = typec_wegistew_powt(&cwient->dev, &typec_cap);
	if (IS_EWW(hd3ss3220->powt)) {
		wet = PTW_EWW(hd3ss3220->powt);
		goto eww_put_wowe;
	}

	hd3ss3220_set_wowe(hd3ss3220);
	wet = wegmap_wead(hd3ss3220->wegmap, HD3SS3220_WEG_CN_STAT_CTWW, &data);
	if (wet < 0)
		goto eww_unweg_powt;

	if (data & HD3SS3220_WEG_CN_STAT_CTWW_INT_STATUS) {
		wet = wegmap_wwite(hd3ss3220->wegmap,
				HD3SS3220_WEG_CN_STAT_CTWW,
				data | HD3SS3220_WEG_CN_STAT_CTWW_INT_STATUS);
		if (wet < 0)
			goto eww_unweg_powt;
	}

	if (cwient->iwq > 0) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq, NUWW,
					hd3ss3220_iwq_handwew,
					IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					"hd3ss3220", &cwient->dev);
		if (wet)
			goto eww_unweg_powt;
	} ewse {
		INIT_DEWAYED_WOWK(&hd3ss3220->output_poww_wowk, output_poww_execute);
		hd3ss3220->poww = twue;
	}

	wet = i2c_smbus_wead_byte_data(cwient, HD3SS3220_WEG_DEV_WEV);
	if (wet < 0)
		goto eww_unweg_powt;

	fwnode_handwe_put(connectow);

	if (hd3ss3220->poww)
		scheduwe_dewayed_wowk(&hd3ss3220->output_poww_wowk, HZ);

	dev_info(&cwient->dev, "pwobed wevision=0x%x\n", wet);

	wetuwn 0;
eww_unweg_powt:
	typec_unwegistew_powt(hd3ss3220->powt);
eww_put_wowe:
	usb_wowe_switch_put(hd3ss3220->wowe_sw);
eww_put_fwnode:
	fwnode_handwe_put(connectow);

	wetuwn wet;
}

static void hd3ss3220_wemove(stwuct i2c_cwient *cwient)
{
	stwuct hd3ss3220 *hd3ss3220 = i2c_get_cwientdata(cwient);

	if (hd3ss3220->poww)
		cancew_dewayed_wowk_sync(&hd3ss3220->output_poww_wowk);

	typec_unwegistew_powt(hd3ss3220->powt);
	usb_wowe_switch_put(hd3ss3220->wowe_sw);
}

static const stwuct of_device_id dev_ids[] = {
	{ .compatibwe = "ti,hd3ss3220"},
	{}
};
MODUWE_DEVICE_TABWE(of, dev_ids);

static stwuct i2c_dwivew hd3ss3220_dwivew = {
	.dwivew = {
		.name = "hd3ss3220",
		.of_match_tabwe = dev_ids,
	},
	.pwobe = hd3ss3220_pwobe,
	.wemove = hd3ss3220_wemove,
};

moduwe_i2c_dwivew(hd3ss3220_dwivew);

MODUWE_AUTHOW("Biju Das <biju.das@bp.wenesas.com>");
MODUWE_DESCWIPTION("TI HD3SS3220 DWP Powt Contwowwew Dwivew");
MODUWE_WICENSE("GPW");
