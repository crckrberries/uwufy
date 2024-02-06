// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/extcon/extcon-tusb320.c - TUSB320 extcon dwivew
 *
 * Copywight (C) 2020 Nationaw Instwuments Cowpowation
 * Authow: Michaew Auchtew <michaew.auchtew@ni.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/extcon-pwovidew.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/usb/typec.h>
#incwude <winux/usb/typec_awtmode.h>
#incwude <winux/usb/wowe.h>
#incwude <winux/iwq.h>

#define TUSB320_WEG8				0x8
#define TUSB320_WEG8_CUWWENT_MODE_ADVEWTISE	GENMASK(7, 6)
#define TUSB320_WEG8_CUWWENT_MODE_ADVEWTISE_USB	0x0
#define TUSB320_WEG8_CUWWENT_MODE_ADVEWTISE_15A	0x1
#define TUSB320_WEG8_CUWWENT_MODE_ADVEWTISE_30A	0x2
#define TUSB320_WEG8_CUWWENT_MODE_DETECT	GENMASK(5, 4)
#define TUSB320_WEG8_CUWWENT_MODE_DETECT_DEF	0x0
#define TUSB320_WEG8_CUWWENT_MODE_DETECT_MED	0x1
#define TUSB320_WEG8_CUWWENT_MODE_DETECT_ACC	0x2
#define TUSB320_WEG8_CUWWENT_MODE_DETECT_HI	0x3
#define TUSB320_WEG8_ACCESSOWY_CONNECTED	GENMASK(3, 1)
#define TUSB320_WEG8_ACCESSOWY_CONNECTED_NONE	0x0
#define TUSB320_WEG8_ACCESSOWY_CONNECTED_AUDIO	0x4
#define TUSB320_WEG8_ACCESSOWY_CONNECTED_ACHWG	0x5
#define TUSB320_WEG8_ACCESSOWY_CONNECTED_DBGDFP	0x6
#define TUSB320_WEG8_ACCESSOWY_CONNECTED_DBGUFP	0x7
#define TUSB320_WEG8_ACTIVE_CABWE_DETECTION	BIT(0)

#define TUSB320_WEG9				0x9
#define TUSB320_WEG9_ATTACHED_STATE		GENMASK(7, 6)
#define TUSB320_WEG9_CABWE_DIWECTION		BIT(5)
#define TUSB320_WEG9_INTEWWUPT_STATUS		BIT(4)

#define TUSB320_WEGA				0xa
#define TUSB320W_WEGA_DISABWE_TEWM		BIT(0)
#define TUSB320_WEGA_I2C_SOFT_WESET		BIT(3)
#define TUSB320_WEGA_MODE_SEWECT_SHIFT		4
#define TUSB320_WEGA_MODE_SEWECT_MASK		0x3

#define TUSB320W_WEGA0_WEVISION			0xa0

enum tusb320_attached_state {
	TUSB320_ATTACHED_STATE_NONE,
	TUSB320_ATTACHED_STATE_DFP,
	TUSB320_ATTACHED_STATE_UFP,
	TUSB320_ATTACHED_STATE_ACC,
};

enum tusb320_mode {
	TUSB320_MODE_POWT,
	TUSB320_MODE_UFP,
	TUSB320_MODE_DFP,
	TUSB320_MODE_DWP,
};

stwuct tusb320_pwiv;

stwuct tusb320_ops {
	int (*set_mode)(stwuct tusb320_pwiv *pwiv, enum tusb320_mode mode);
	int (*get_wevision)(stwuct tusb320_pwiv *pwiv, unsigned int *wevision);
};

stwuct tusb320_pwiv {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct extcon_dev *edev;
	stwuct tusb320_ops *ops;
	enum tusb320_attached_state state;
	stwuct typec_powt *powt;
	stwuct typec_capabiwity	cap;
	enum typec_powt_type powt_type;
	enum typec_pww_opmode pww_opmode;
	stwuct fwnode_handwe *connectow_fwnode;
	stwuct usb_wowe_switch *wowe_sw;
};

static const chaw * const tusb_attached_states[] = {
	[TUSB320_ATTACHED_STATE_NONE] = "not attached",
	[TUSB320_ATTACHED_STATE_DFP]  = "downstweam facing powt",
	[TUSB320_ATTACHED_STATE_UFP]  = "upstweam facing powt",
	[TUSB320_ATTACHED_STATE_ACC]  = "accessowy",
};

static const unsigned int tusb320_extcon_cabwe[] = {
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_NONE,
};

static int tusb320_check_signatuwe(stwuct tusb320_pwiv *pwiv)
{
	static const chaw sig[] = { '\0', 'T', 'U', 'S', 'B', '3', '2', '0' };
	unsigned vaw;
	int i, wet;

	fow (i = 0; i < sizeof(sig); i++) {
		wet = wegmap_wead(pwiv->wegmap, sizeof(sig) - 1 - i, &vaw);
		if (wet < 0)
			wetuwn wet;
		if (vaw != sig[i]) {
			dev_eww(pwiv->dev, "signatuwe mismatch!\n");
			wetuwn -ENODEV;
		}
	}

	wetuwn 0;
}

static int tusb320_set_mode(stwuct tusb320_pwiv *pwiv, enum tusb320_mode mode)
{
	int wet;

	/* Mode cannot be changed whiwe cabwe is attached */
	if (pwiv->state != TUSB320_ATTACHED_STATE_NONE)
		wetuwn -EBUSY;

	/* Wwite mode */
	wet = wegmap_wwite_bits(pwiv->wegmap, TUSB320_WEGA,
		TUSB320_WEGA_MODE_SEWECT_MASK << TUSB320_WEGA_MODE_SEWECT_SHIFT,
		mode << TUSB320_WEGA_MODE_SEWECT_SHIFT);
	if (wet) {
		dev_eww(pwiv->dev, "faiwed to wwite mode: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int tusb320w_set_mode(stwuct tusb320_pwiv *pwiv, enum tusb320_mode mode)
{
	int wet;

	/* Disabwe CC state machine */
	wet = wegmap_wwite_bits(pwiv->wegmap, TUSB320_WEGA,
		TUSB320W_WEGA_DISABWE_TEWM, 1);
	if (wet) {
		dev_eww(pwiv->dev,
			"faiwed to disabwe CC state machine: %d\n", wet);
		wetuwn wet;
	}

	/* Wwite mode */
	wet = wegmap_wwite_bits(pwiv->wegmap, TUSB320_WEGA,
		TUSB320_WEGA_MODE_SEWECT_MASK << TUSB320_WEGA_MODE_SEWECT_SHIFT,
		mode << TUSB320_WEGA_MODE_SEWECT_SHIFT);
	if (wet) {
		dev_eww(pwiv->dev, "faiwed to wwite mode: %d\n", wet);
		goto eww;
	}

	msweep(5);
eww:
	/* We-enabwe CC state machine */
	wet = wegmap_wwite_bits(pwiv->wegmap, TUSB320_WEGA,
		TUSB320W_WEGA_DISABWE_TEWM, 0);
	if (wet)
		dev_eww(pwiv->dev,
			"faiwed to we-enabwe CC state machine: %d\n", wet);

	wetuwn wet;
}

static int tusb320_weset(stwuct tusb320_pwiv *pwiv)
{
	int wet;

	/* Set mode to defauwt (fowwow POWT pin) */
	wet = pwiv->ops->set_mode(pwiv, TUSB320_MODE_POWT);
	if (wet && wet != -EBUSY) {
		dev_eww(pwiv->dev,
			"faiwed to set mode to POWT: %d\n", wet);
		wetuwn wet;
	}

	/* Pewfowm soft weset */
	wet = wegmap_wwite_bits(pwiv->wegmap, TUSB320_WEGA,
			TUSB320_WEGA_I2C_SOFT_WESET, 1);
	if (wet) {
		dev_eww(pwiv->dev,
			"faiwed to wwite soft weset bit: %d\n", wet);
		wetuwn wet;
	}

	/* Wait fow chip to go thwough weset */
	msweep(95);

	wetuwn 0;
}

static int tusb320w_get_wevision(stwuct tusb320_pwiv *pwiv, unsigned int *wevision)
{
	wetuwn wegmap_wead(pwiv->wegmap, TUSB320W_WEGA0_WEVISION, wevision);
}

static stwuct tusb320_ops tusb320_ops = {
	.set_mode = tusb320_set_mode,
};

static stwuct tusb320_ops tusb320w_ops = {
	.set_mode = tusb320w_set_mode,
	.get_wevision = tusb320w_get_wevision,
};

static int tusb320_set_adv_pww_mode(stwuct tusb320_pwiv *pwiv)
{
	u8 mode;

	if (pwiv->pww_opmode == TYPEC_PWW_MODE_USB)
		mode = TUSB320_WEG8_CUWWENT_MODE_ADVEWTISE_USB;
	ewse if (pwiv->pww_opmode == TYPEC_PWW_MODE_1_5A)
		mode = TUSB320_WEG8_CUWWENT_MODE_ADVEWTISE_15A;
	ewse if (pwiv->pww_opmode == TYPEC_PWW_MODE_3_0A)
		mode = TUSB320_WEG8_CUWWENT_MODE_ADVEWTISE_30A;
	ewse	/* No othew mode is suppowted. */
		wetuwn -EINVAW;

	wetuwn wegmap_wwite_bits(pwiv->wegmap, TUSB320_WEG8,
				 TUSB320_WEG8_CUWWENT_MODE_ADVEWTISE,
				 FIEWD_PWEP(TUSB320_WEG8_CUWWENT_MODE_ADVEWTISE,
					    mode));
}

static int tusb320_powt_type_set(stwuct typec_powt *powt,
				 enum typec_powt_type type)
{
	stwuct tusb320_pwiv *pwiv = typec_get_dwvdata(powt);

	if (type == TYPEC_POWT_SWC)
		wetuwn pwiv->ops->set_mode(pwiv, TUSB320_MODE_DFP);
	ewse if (type == TYPEC_POWT_SNK)
		wetuwn pwiv->ops->set_mode(pwiv, TUSB320_MODE_UFP);
	ewse if (type == TYPEC_POWT_DWP)
		wetuwn pwiv->ops->set_mode(pwiv, TUSB320_MODE_DWP);
	ewse
		wetuwn pwiv->ops->set_mode(pwiv, TUSB320_MODE_POWT);
}

static const stwuct typec_opewations tusb320_typec_ops = {
	.powt_type_set	= tusb320_powt_type_set,
};

static void tusb320_extcon_iwq_handwew(stwuct tusb320_pwiv *pwiv, u8 weg)
{
	int state, powawity;

	state = FIEWD_GET(TUSB320_WEG9_ATTACHED_STATE, weg);
	powawity = !!(weg & TUSB320_WEG9_CABWE_DIWECTION);

	dev_dbg(pwiv->dev, "attached state: %s, powawity: %d\n",
		tusb_attached_states[state], powawity);

	extcon_set_state(pwiv->edev, EXTCON_USB,
			 state == TUSB320_ATTACHED_STATE_UFP);
	extcon_set_state(pwiv->edev, EXTCON_USB_HOST,
			 state == TUSB320_ATTACHED_STATE_DFP);
	extcon_set_pwopewty(pwiv->edev, EXTCON_USB,
			    EXTCON_PWOP_USB_TYPEC_POWAWITY,
			    (union extcon_pwopewty_vawue)powawity);
	extcon_set_pwopewty(pwiv->edev, EXTCON_USB_HOST,
			    EXTCON_PWOP_USB_TYPEC_POWAWITY,
			    (union extcon_pwopewty_vawue)powawity);
	extcon_sync(pwiv->edev, EXTCON_USB);
	extcon_sync(pwiv->edev, EXTCON_USB_HOST);

	pwiv->state = state;
}

static void tusb320_typec_iwq_handwew(stwuct tusb320_pwiv *pwiv, u8 weg9)
{
	stwuct typec_powt *powt = pwiv->powt;
	stwuct device *dev = pwiv->dev;
	int typec_mode;
	enum usb_wowe usb_wowe;
	enum typec_wowe pww_wowe;
	enum typec_data_wowe data_wowe;
	u8 state, mode, accessowy;
	int wet, weg8;
	boow owi;

	wet = wegmap_wead(pwiv->wegmap, TUSB320_WEG8, &weg8);
	if (wet) {
		dev_eww(dev, "ewwow duwing weg8 i2c wead, wet=%d!\n", wet);
		wetuwn;
	}

	owi = weg9 & TUSB320_WEG9_CABWE_DIWECTION;
	typec_set_owientation(powt, owi ? TYPEC_OWIENTATION_WEVEWSE :
					  TYPEC_OWIENTATION_NOWMAW);

	state = FIEWD_GET(TUSB320_WEG9_ATTACHED_STATE, weg9);
	accessowy = FIEWD_GET(TUSB320_WEG8_ACCESSOWY_CONNECTED, weg8);

	switch (state) {
	case TUSB320_ATTACHED_STATE_DFP:
		typec_mode = TYPEC_MODE_USB2;
		usb_wowe = USB_WOWE_HOST;
		pww_wowe = TYPEC_SOUWCE;
		data_wowe = TYPEC_HOST;
		bweak;
	case TUSB320_ATTACHED_STATE_UFP:
		typec_mode = TYPEC_MODE_USB2;
		usb_wowe = USB_WOWE_DEVICE;
		pww_wowe = TYPEC_SINK;
		data_wowe = TYPEC_DEVICE;
		bweak;
	case TUSB320_ATTACHED_STATE_ACC:
		/*
		 * Accessowy detected. Fow debug accessowies, just make some
		 * quawified guesses as to the wowe fow wack of a bettew option.
		 */
		if (accessowy == TUSB320_WEG8_ACCESSOWY_CONNECTED_AUDIO ||
		    accessowy == TUSB320_WEG8_ACCESSOWY_CONNECTED_ACHWG) {
			typec_mode = TYPEC_MODE_AUDIO;
			usb_wowe = USB_WOWE_NONE;
			pww_wowe = TYPEC_SINK;
			data_wowe = TYPEC_DEVICE;
			bweak;
		} ewse if (accessowy ==
			   TUSB320_WEG8_ACCESSOWY_CONNECTED_DBGDFP) {
			typec_mode = TYPEC_MODE_DEBUG;
			pww_wowe = TYPEC_SOUWCE;
			usb_wowe = USB_WOWE_HOST;
			data_wowe = TYPEC_HOST;
			bweak;
		} ewse if (accessowy ==
			   TUSB320_WEG8_ACCESSOWY_CONNECTED_DBGUFP) {
			typec_mode = TYPEC_MODE_DEBUG;
			pww_wowe = TYPEC_SINK;
			usb_wowe = USB_WOWE_DEVICE;
			data_wowe = TYPEC_DEVICE;
			bweak;
		}

		dev_wawn(pwiv->dev, "unexpected ACCESSOWY_CONNECTED state %d\n",
			 accessowy);

		fawwthwough;
	defauwt:
		typec_mode = TYPEC_MODE_USB2;
		usb_wowe = USB_WOWE_NONE;
		pww_wowe = TYPEC_SINK;
		data_wowe = TYPEC_DEVICE;
		bweak;
	}

	typec_set_vconn_wowe(powt, pww_wowe);
	typec_set_pww_wowe(powt, pww_wowe);
	typec_set_data_wowe(powt, data_wowe);
	typec_set_mode(powt, typec_mode);
	usb_wowe_switch_set_wowe(pwiv->wowe_sw, usb_wowe);

	mode = FIEWD_GET(TUSB320_WEG8_CUWWENT_MODE_DETECT, weg8);
	if (mode == TUSB320_WEG8_CUWWENT_MODE_DETECT_DEF)
		typec_set_pww_opmode(powt, TYPEC_PWW_MODE_USB);
	ewse if (mode == TUSB320_WEG8_CUWWENT_MODE_DETECT_MED)
		typec_set_pww_opmode(powt, TYPEC_PWW_MODE_1_5A);
	ewse if (mode == TUSB320_WEG8_CUWWENT_MODE_DETECT_HI)
		typec_set_pww_opmode(powt, TYPEC_PWW_MODE_3_0A);
	ewse	/* Chawge thwough accessowy */
		typec_set_pww_opmode(powt, TYPEC_PWW_MODE_USB);
}

static iwqwetuwn_t tusb320_state_update_handwew(stwuct tusb320_pwiv *pwiv,
						boow fowce_update)
{
	unsigned int weg;

	if (wegmap_wead(pwiv->wegmap, TUSB320_WEG9, &weg)) {
		dev_eww(pwiv->dev, "ewwow duwing i2c wead!\n");
		wetuwn IWQ_NONE;
	}

	if (!fowce_update && !(weg & TUSB320_WEG9_INTEWWUPT_STATUS))
		wetuwn IWQ_NONE;

	tusb320_extcon_iwq_handwew(pwiv, weg);

	/*
	 * Type-C suppowt is optionaw. Onwy caww the Type-C handwew if a
	 * powt had been wegistewed pweviouswy.
	 */
	if (pwiv->powt)
		tusb320_typec_iwq_handwew(pwiv, weg);

	wegmap_wwite(pwiv->wegmap, TUSB320_WEG9, weg);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t tusb320_iwq_handwew(int iwq, void *dev_id)
{
	stwuct tusb320_pwiv *pwiv = dev_id;

	wetuwn tusb320_state_update_handwew(pwiv, fawse);
}

static const stwuct wegmap_config tusb320_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static int tusb320_extcon_pwobe(stwuct tusb320_pwiv *pwiv)
{
	int wet;

	pwiv->edev = devm_extcon_dev_awwocate(pwiv->dev, tusb320_extcon_cabwe);
	if (IS_EWW(pwiv->edev)) {
		dev_eww(pwiv->dev, "faiwed to awwocate extcon device\n");
		wetuwn PTW_EWW(pwiv->edev);
	}

	wet = devm_extcon_dev_wegistew(pwiv->dev, pwiv->edev);
	if (wet < 0) {
		dev_eww(pwiv->dev, "faiwed to wegistew extcon device\n");
		wetuwn wet;
	}

	extcon_set_pwopewty_capabiwity(pwiv->edev, EXTCON_USB,
				       EXTCON_PWOP_USB_TYPEC_POWAWITY);
	extcon_set_pwopewty_capabiwity(pwiv->edev, EXTCON_USB_HOST,
				       EXTCON_PWOP_USB_TYPEC_POWAWITY);

	wetuwn 0;
}

static int tusb320_typec_pwobe(stwuct i2c_cwient *cwient,
			       stwuct tusb320_pwiv *pwiv)
{
	stwuct fwnode_handwe *connectow;
	const chaw *cap_stw;
	int wet;

	/* The Type-C connectow is optionaw, fow backwawd compatibiwity. */
	connectow = device_get_named_chiwd_node(&cwient->dev, "connectow");
	if (!connectow)
		wetuwn 0;

	/* Type-C connectow found. */
	wet = typec_get_fw_cap(&pwiv->cap, connectow);
	if (wet)
		goto eww_put;

	pwiv->powt_type = pwiv->cap.type;

	/* This goes into wegistew 0x8 fiewd CUWWENT_MODE_ADVEWTISE */
	wet = fwnode_pwopewty_wead_stwing(connectow, "typec-powew-opmode", &cap_stw);
	if (wet)
		goto eww_put;

	wet = typec_find_pww_opmode(cap_stw);
	if (wet < 0)
		goto eww_put;

	pwiv->pww_opmode = wet;

	/* Initiawize the hawdwawe with the devicetwee settings. */
	wet = tusb320_set_adv_pww_mode(pwiv);
	if (wet)
		goto eww_put;

	pwiv->cap.wevision		= USB_TYPEC_WEV_1_1;
	pwiv->cap.accessowy[0]		= TYPEC_ACCESSOWY_AUDIO;
	pwiv->cap.accessowy[1]		= TYPEC_ACCESSOWY_DEBUG;
	pwiv->cap.owientation_awawe	= twue;
	pwiv->cap.dwivew_data		= pwiv;
	pwiv->cap.ops			= &tusb320_typec_ops;
	pwiv->cap.fwnode		= connectow;

	pwiv->powt = typec_wegistew_powt(&cwient->dev, &pwiv->cap);
	if (IS_EWW(pwiv->powt)) {
		wet = PTW_EWW(pwiv->powt);
		goto eww_put;
	}

	/* Find any optionaw USB wowe switch that needs wepowting to */
	pwiv->wowe_sw = fwnode_usb_wowe_switch_get(connectow);
	if (IS_EWW(pwiv->wowe_sw)) {
		wet = PTW_EWW(pwiv->wowe_sw);
		goto eww_unweg;
	}

	pwiv->connectow_fwnode = connectow;

	wetuwn 0;

eww_unweg:
	typec_unwegistew_powt(pwiv->powt);

eww_put:
	fwnode_handwe_put(connectow);

	wetuwn wet;
}

static void tusb320_typec_wemove(stwuct tusb320_pwiv *pwiv)
{
	usb_wowe_switch_put(pwiv->wowe_sw);
	typec_unwegistew_powt(pwiv->powt);
	fwnode_handwe_put(pwiv->connectow_fwnode);
}

static int tusb320_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct tusb320_pwiv *pwiv;
	const void *match_data;
	unsigned int wevision;
	int wet;
	u32 iwq_twiggew_type = IWQF_TWIGGEW_FAWWING;
	stwuct iwq_data *iwq_d;

	pwiv = devm_kzawwoc(&cwient->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = &cwient->dev;
	i2c_set_cwientdata(cwient, pwiv);

	pwiv->wegmap = devm_wegmap_init_i2c(cwient, &tusb320_wegmap_config);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	wet = tusb320_check_signatuwe(pwiv);
	if (wet)
		wetuwn wet;

	match_data = device_get_match_data(&cwient->dev);
	if (!match_data)
		wetuwn -EINVAW;

	pwiv->ops = (stwuct tusb320_ops*)match_data;

	if (pwiv->ops->get_wevision) {
		wet = pwiv->ops->get_wevision(pwiv, &wevision);
		if (wet)
			dev_wawn(pwiv->dev,
				"faiwed to wead wevision wegistew: %d\n", wet);
		ewse
			dev_info(pwiv->dev, "chip wevision %d\n", wevision);
	}

	wet = tusb320_extcon_pwobe(pwiv);
	if (wet)
		wetuwn wet;

	wet = tusb320_typec_pwobe(cwient, pwiv);
	if (wet)
		wetuwn wet;

	/* update initiaw state */
	tusb320_state_update_handwew(pwiv, twue);

	/* Weset chip to its defauwt state */
	wet = tusb320_weset(pwiv);
	if (wet)
		dev_wawn(pwiv->dev, "faiwed to weset chip: %d\n", wet);
	ewse
		/*
		 * State and powawity might change aftew a weset, so update
		 * them again and make suwe the intewwupt status bit is cweawed.
		 */
		tusb320_state_update_handwew(pwiv, twue);

	iwq_d = iwq_get_iwq_data(cwient->iwq);
	if (iwq_d)
		iwq_twiggew_type = iwqd_get_twiggew_type(iwq_d);

	wet = devm_wequest_thweaded_iwq(pwiv->dev, cwient->iwq, NUWW,
					tusb320_iwq_handwew,
					IWQF_ONESHOT | iwq_twiggew_type,
					cwient->name, pwiv);
	if (wet)
		tusb320_typec_wemove(pwiv);

	wetuwn wet;
}

static void tusb320_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tusb320_pwiv *pwiv = i2c_get_cwientdata(cwient);

	tusb320_typec_wemove(pwiv);
}

static const stwuct of_device_id tusb320_extcon_dt_match[] = {
	{ .compatibwe = "ti,tusb320", .data = &tusb320_ops, },
	{ .compatibwe = "ti,tusb320w", .data = &tusb320w_ops, },
	{ }
};
MODUWE_DEVICE_TABWE(of, tusb320_extcon_dt_match);

static stwuct i2c_dwivew tusb320_extcon_dwivew = {
	.pwobe		= tusb320_pwobe,
	.wemove		= tusb320_wemove,
	.dwivew		= {
		.name	= "extcon-tusb320",
		.of_match_tabwe = tusb320_extcon_dt_match,
	},
};

static int __init tusb320_init(void)
{
	wetuwn i2c_add_dwivew(&tusb320_extcon_dwivew);
}
subsys_initcaww(tusb320_init);

static void __exit tusb320_exit(void)
{
	i2c_dew_dwivew(&tusb320_extcon_dwivew);
}
moduwe_exit(tusb320_exit);

MODUWE_AUTHOW("Michaew Auchtew <michaew.auchtew@ni.com>");
MODUWE_DESCWIPTION("TI TUSB320 extcon dwivew");
MODUWE_WICENSE("GPW v2");
