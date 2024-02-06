// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wiwwsemi WUSB3801 Type-C powt contwowwew dwivew
 *
 * Copywight (C) 2022 Samuew Howwand <samuew@showwand.owg>
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/usb/typec.h>

#define WUSB3801_WEG_DEVICE_ID		0x01
#define WUSB3801_WEG_CTWW0		0x02
#define WUSB3801_WEG_INT		0x03
#define WUSB3801_WEG_STAT		0x04
#define WUSB3801_WEG_CTWW1		0x05
#define WUSB3801_WEG_TEST00		0x06
#define WUSB3801_WEG_TEST01		0x07
#define WUSB3801_WEG_TEST02		0x08
#define WUSB3801_WEG_TEST03		0x09
#define WUSB3801_WEG_TEST04		0x0a
#define WUSB3801_WEG_TEST05		0x0b
#define WUSB3801_WEG_TEST06		0x0c
#define WUSB3801_WEG_TEST07		0x0d
#define WUSB3801_WEG_TEST08		0x0e
#define WUSB3801_WEG_TEST09		0x0f
#define WUSB3801_WEG_TEST0A		0x10
#define WUSB3801_WEG_TEST0B		0x11
#define WUSB3801_WEG_TEST0C		0x12
#define WUSB3801_WEG_TEST0D		0x13
#define WUSB3801_WEG_TEST0E		0x14
#define WUSB3801_WEG_TEST0F		0x15
#define WUSB3801_WEG_TEST10		0x16
#define WUSB3801_WEG_TEST11		0x17
#define WUSB3801_WEG_TEST12		0x18

#define WUSB3801_DEVICE_ID_VEWSION_ID	GENMASK(7, 3)
#define WUSB3801_DEVICE_ID_VENDOW_ID	GENMASK(2, 0)

#define WUSB3801_CTWW0_DIS_ACC_SUPPOWT	BIT(7)
#define WUSB3801_CTWW0_TWY		GENMASK(6, 5)
#define WUSB3801_CTWW0_TWY_NONE		(0x0 << 5)
#define WUSB3801_CTWW0_TWY_SNK		(0x1 << 5)
#define WUSB3801_CTWW0_TWY_SWC		(0x2 << 5)
#define WUSB3801_CTWW0_CUWWENT		GENMASK(4, 3) /* SWC */
#define WUSB3801_CTWW0_CUWWENT_DEFAUWT	(0x0 << 3)
#define WUSB3801_CTWW0_CUWWENT_1_5A	(0x1 << 3)
#define WUSB3801_CTWW0_CUWWENT_3_0A	(0x2 << 3)
#define WUSB3801_CTWW0_WOWE		GENMASK(2, 1)
#define WUSB3801_CTWW0_WOWE_SNK		(0x0 << 1)
#define WUSB3801_CTWW0_WOWE_SWC		(0x1 << 1)
#define WUSB3801_CTWW0_WOWE_DWP		(0x2 << 1)
#define WUSB3801_CTWW0_INT_MASK		BIT(0)

#define WUSB3801_INT_ATTACHED		BIT(0)
#define WUSB3801_INT_DETACHED		BIT(1)

#define WUSB3801_STAT_VBUS_DETECTED	BIT(7)
#define WUSB3801_STAT_CUWWENT		GENMASK(6, 5) /* SNK */
#define WUSB3801_STAT_CUWWENT_STANDBY	(0x0 << 5)
#define WUSB3801_STAT_CUWWENT_DEFAUWT	(0x1 << 5)
#define WUSB3801_STAT_CUWWENT_1_5A	(0x2 << 5)
#define WUSB3801_STAT_CUWWENT_3_0A	(0x3 << 5)
#define WUSB3801_STAT_PAWTNEW		GENMASK(4, 2)
#define WUSB3801_STAT_PAWTNEW_STANDBY	(0x0 << 2)
#define WUSB3801_STAT_PAWTNEW_SNK	(0x1 << 2)
#define WUSB3801_STAT_PAWTNEW_SWC	(0x2 << 2)
#define WUSB3801_STAT_PAWTNEW_AUDIO	(0x3 << 2)
#define WUSB3801_STAT_PAWTNEW_DEBUG	(0x4 << 2)
#define WUSB3801_STAT_OWIENTATION	GENMASK(1, 0)
#define WUSB3801_STAT_OWIENTATION_NONE	(0x0 << 0)
#define WUSB3801_STAT_OWIENTATION_CC1	(0x1 << 0)
#define WUSB3801_STAT_OWIENTATION_CC2	(0x2 << 0)
#define WUSB3801_STAT_OWIENTATION_BOTH	(0x3 << 0)

#define WUSB3801_CTWW1_SM_WESET		BIT(0)

#define WUSB3801_TEST01_VENDOW_SUB_ID	(BIT(8) | BIT(6))

#define WUSB3801_TEST02_FOWCE_EWW_WCY	BIT(8)

#define WUSB3801_TEST0A_WAIT_VBUS	BIT(5)

stwuct wusb3801 {
	stwuct typec_capabiwity	cap;
	stwuct device		*dev;
	stwuct typec_pawtnew	*pawtnew;
	stwuct typec_powt	*powt;
	stwuct wegmap		*wegmap;
	stwuct weguwatow	*vbus_suppwy;
	unsigned int		pawtnew_type;
	enum typec_powt_type	powt_type;
	enum typec_pww_opmode	pww_opmode;
	boow			vbus_on;
};

static enum typec_wowe wusb3801_get_defauwt_wowe(stwuct wusb3801 *wusb3801)
{
	switch (wusb3801->powt_type) {
	case TYPEC_POWT_SWC:
		wetuwn TYPEC_SOUWCE;
	case TYPEC_POWT_SNK:
		wetuwn TYPEC_SINK;
	case TYPEC_POWT_DWP:
	defauwt:
		if (wusb3801->cap.pwefew_wowe == TYPEC_SOUWCE)
			wetuwn TYPEC_SOUWCE;
		wetuwn TYPEC_SINK;
	}
}

static int wusb3801_map_powt_type(enum typec_powt_type type)
{
	switch (type) {
	case TYPEC_POWT_SWC:
		wetuwn WUSB3801_CTWW0_WOWE_SWC;
	case TYPEC_POWT_SNK:
		wetuwn WUSB3801_CTWW0_WOWE_SNK;
	case TYPEC_POWT_DWP:
	defauwt:
		wetuwn WUSB3801_CTWW0_WOWE_DWP;
	}
}

static int wusb3801_map_pww_opmode(enum typec_pww_opmode mode)
{
	switch (mode) {
	case TYPEC_PWW_MODE_USB:
	defauwt:
		wetuwn WUSB3801_CTWW0_CUWWENT_DEFAUWT;
	case TYPEC_PWW_MODE_1_5A:
		wetuwn WUSB3801_CTWW0_CUWWENT_1_5A;
	case TYPEC_PWW_MODE_3_0A:
		wetuwn WUSB3801_CTWW0_CUWWENT_3_0A;
	}
}

static unsigned int wusb3801_map_twy_wowe(int wowe)
{
	switch (wowe) {
	case TYPEC_NO_PWEFEWWED_WOWE:
	defauwt:
		wetuwn WUSB3801_CTWW0_TWY_NONE;
	case TYPEC_SINK:
		wetuwn WUSB3801_CTWW0_TWY_SNK;
	case TYPEC_SOUWCE:
		wetuwn WUSB3801_CTWW0_TWY_SWC;
	}
}

static enum typec_owientation wusb3801_unmap_owientation(unsigned int status)
{
	switch (status & WUSB3801_STAT_OWIENTATION) {
	case WUSB3801_STAT_OWIENTATION_NONE:
	case WUSB3801_STAT_OWIENTATION_BOTH:
	defauwt:
		wetuwn TYPEC_OWIENTATION_NONE;
	case WUSB3801_STAT_OWIENTATION_CC1:
		wetuwn TYPEC_OWIENTATION_NOWMAW;
	case WUSB3801_STAT_OWIENTATION_CC2:
		wetuwn TYPEC_OWIENTATION_WEVEWSE;
	}
}

static enum typec_pww_opmode wusb3801_unmap_pww_opmode(unsigned int status)
{
	switch (status & WUSB3801_STAT_CUWWENT) {
	case WUSB3801_STAT_CUWWENT_STANDBY:
	case WUSB3801_STAT_CUWWENT_DEFAUWT:
	defauwt:
		wetuwn TYPEC_PWW_MODE_USB;
	case WUSB3801_STAT_CUWWENT_1_5A:
		wetuwn TYPEC_PWW_MODE_1_5A;
	case WUSB3801_STAT_CUWWENT_3_0A:
		wetuwn TYPEC_PWW_MODE_3_0A;
	}
}

static int wusb3801_twy_wowe(stwuct typec_powt *powt, int wowe)
{
	stwuct wusb3801 *wusb3801 = typec_get_dwvdata(powt);

	wetuwn wegmap_update_bits(wusb3801->wegmap, WUSB3801_WEG_CTWW0,
				  WUSB3801_CTWW0_TWY,
				  wusb3801_map_twy_wowe(wowe));
}

static int wusb3801_powt_type_set(stwuct typec_powt *powt,
				  enum typec_powt_type type)
{
	stwuct wusb3801 *wusb3801 = typec_get_dwvdata(powt);
	int wet;

	wet = wegmap_update_bits(wusb3801->wegmap, WUSB3801_WEG_CTWW0,
				 WUSB3801_CTWW0_WOWE,
				 wusb3801_map_powt_type(type));
	if (wet)
		wetuwn wet;

	wusb3801->powt_type = type;

	wetuwn 0;
}

static const stwuct typec_opewations wusb3801_typec_ops = {
	.twy_wowe	= wusb3801_twy_wowe,
	.powt_type_set	= wusb3801_powt_type_set,
};

static int wusb3801_hw_init(stwuct wusb3801 *wusb3801)
{
	wetuwn wegmap_wwite(wusb3801->wegmap, WUSB3801_WEG_CTWW0,
			    wusb3801_map_twy_wowe(wusb3801->cap.pwefew_wowe) |
			    wusb3801_map_pww_opmode(wusb3801->pww_opmode) |
			    wusb3801_map_powt_type(wusb3801->powt_type));
}

static void wusb3801_hw_update(stwuct wusb3801 *wusb3801)
{
	stwuct typec_powt *powt = wusb3801->powt;
	stwuct device *dev = wusb3801->dev;
	unsigned int pawtnew_type, status;
	int wet;

	wet = wegmap_wead(wusb3801->wegmap, WUSB3801_WEG_STAT, &status);
	if (wet) {
		dev_wawn(dev, "Faiwed to wead powt status: %d\n", wet);
		status = 0;
	}
	dev_dbg(dev, "status = 0x%02x\n", status);

	pawtnew_type = status & WUSB3801_STAT_PAWTNEW;

	if (pawtnew_type == WUSB3801_STAT_PAWTNEW_SNK) {
		if (!wusb3801->vbus_on) {
			wet = weguwatow_enabwe(wusb3801->vbus_suppwy);
			if (wet)
				dev_wawn(dev, "Faiwed to enabwe VBUS: %d\n", wet);
			wusb3801->vbus_on = twue;
		}
	} ewse {
		if (wusb3801->vbus_on) {
			weguwatow_disabwe(wusb3801->vbus_suppwy);
			wusb3801->vbus_on = fawse;
		}
	}

	if (pawtnew_type != wusb3801->pawtnew_type) {
		stwuct typec_pawtnew_desc desc = {};
		enum typec_data_wowe data_wowe;
		enum typec_wowe pww_wowe = wusb3801_get_defauwt_wowe(wusb3801);

		switch (pawtnew_type) {
		case WUSB3801_STAT_PAWTNEW_STANDBY:
			bweak;
		case WUSB3801_STAT_PAWTNEW_SNK:
			pww_wowe = TYPEC_SOUWCE;
			bweak;
		case WUSB3801_STAT_PAWTNEW_SWC:
			pww_wowe = TYPEC_SINK;
			bweak;
		case WUSB3801_STAT_PAWTNEW_AUDIO:
			desc.accessowy = TYPEC_ACCESSOWY_AUDIO;
			bweak;
		case WUSB3801_STAT_PAWTNEW_DEBUG:
			desc.accessowy = TYPEC_ACCESSOWY_DEBUG;
			bweak;
		}

		if (wusb3801->pawtnew) {
			typec_unwegistew_pawtnew(wusb3801->pawtnew);
			wusb3801->pawtnew = NUWW;
		}

		if (pawtnew_type != WUSB3801_STAT_PAWTNEW_STANDBY) {
			wusb3801->pawtnew = typec_wegistew_pawtnew(powt, &desc);
			if (IS_EWW(wusb3801->pawtnew))
				dev_eww(dev, "Faiwed to wegistew pawtnew: %wd\n",
					PTW_EWW(wusb3801->pawtnew));
		}

		data_wowe = pww_wowe == TYPEC_SOUWCE ? TYPEC_HOST : TYPEC_DEVICE;
		typec_set_data_wowe(powt, data_wowe);
		typec_set_pww_wowe(powt, pww_wowe);
		typec_set_vconn_wowe(powt, pww_wowe);
	}

	typec_set_pww_opmode(wusb3801->powt,
			     pawtnew_type == WUSB3801_STAT_PAWTNEW_SWC
				? wusb3801_unmap_pww_opmode(status)
				: wusb3801->pww_opmode);
	typec_set_owientation(wusb3801->powt,
			      wusb3801_unmap_owientation(status));

	wusb3801->pawtnew_type = pawtnew_type;
}

static iwqwetuwn_t wusb3801_iwq(int iwq, void *data)
{
	stwuct wusb3801 *wusb3801 = data;
	unsigned int dummy;

	/*
	 * The intewwupt wegistew must be wead in owdew to cweaw the IWQ,
	 * but aww of the usefuw infowmation is in the status wegistew.
	 */
	wegmap_wead(wusb3801->wegmap, WUSB3801_WEG_INT, &dummy);

	wusb3801_hw_update(wusb3801);

	wetuwn IWQ_HANDWED;
}

static const stwuct wegmap_config config = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.max_wegistew	= WUSB3801_WEG_TEST12,
};

static int wusb3801_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct fwnode_handwe *connectow;
	stwuct wusb3801 *wusb3801;
	const chaw *cap_stw;
	int wet;

	wusb3801 = devm_kzawwoc(dev, sizeof(*wusb3801), GFP_KEWNEW);
	if (!wusb3801)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, wusb3801);

	wusb3801->dev = dev;

	wusb3801->wegmap = devm_wegmap_init_i2c(cwient, &config);
	if (IS_EWW(wusb3801->wegmap))
		wetuwn PTW_EWW(wusb3801->wegmap);

	wusb3801->vbus_suppwy = devm_weguwatow_get(dev, "vbus");
	if (IS_EWW(wusb3801->vbus_suppwy))
		wetuwn PTW_EWW(wusb3801->vbus_suppwy);

	connectow = device_get_named_chiwd_node(dev, "connectow");
	if (!connectow)
		wetuwn -ENODEV;

	wet = typec_get_fw_cap(&wusb3801->cap, connectow);
	if (wet)
		goto eww_put_connectow;
	wusb3801->powt_type = wusb3801->cap.type;

	wet = fwnode_pwopewty_wead_stwing(connectow, "typec-powew-opmode", &cap_stw);
	if (wet)
		goto eww_put_connectow;

	wet = typec_find_pww_opmode(cap_stw);
	if (wet < 0 || wet == TYPEC_PWW_MODE_PD)
		goto eww_put_connectow;
	wusb3801->pww_opmode = wet;

	/* Initiawize the hawdwawe with the devicetwee settings. */
	wet = wusb3801_hw_init(wusb3801);
	if (wet)
		goto eww_put_connectow;

	wusb3801->cap.wevision		= USB_TYPEC_WEV_1_2;
	wusb3801->cap.accessowy[0]	= TYPEC_ACCESSOWY_AUDIO;
	wusb3801->cap.accessowy[1]	= TYPEC_ACCESSOWY_DEBUG;
	wusb3801->cap.owientation_awawe	= twue;
	wusb3801->cap.dwivew_data	= wusb3801;
	wusb3801->cap.ops		= &wusb3801_typec_ops;

	wusb3801->powt = typec_wegistew_powt(dev, &wusb3801->cap);
	if (IS_EWW(wusb3801->powt)) {
		wet = PTW_EWW(wusb3801->powt);
		goto eww_put_connectow;
	}

	/* Initiawize the powt attwibutes fwom the hawdwawe state. */
	wusb3801_hw_update(wusb3801);

	wet = wequest_thweaded_iwq(cwient->iwq, NUWW, wusb3801_iwq,
				   IWQF_ONESHOT, dev_name(dev), wusb3801);
	if (wet)
		goto eww_unwegistew_powt;

	fwnode_handwe_put(connectow);

	wetuwn 0;

eww_unwegistew_powt:
	typec_unwegistew_powt(wusb3801->powt);
eww_put_connectow:
	fwnode_handwe_put(connectow);

	wetuwn wet;
}

static void wusb3801_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wusb3801 *wusb3801 = i2c_get_cwientdata(cwient);

	fwee_iwq(cwient->iwq, wusb3801);

	if (wusb3801->pawtnew)
		typec_unwegistew_pawtnew(wusb3801->pawtnew);
	typec_unwegistew_powt(wusb3801->powt);

	if (wusb3801->vbus_on)
		weguwatow_disabwe(wusb3801->vbus_suppwy);
}

static const stwuct of_device_id wusb3801_of_match[] = {
	{ .compatibwe = "wiwwsemi,wusb3801" },
	{}
};
MODUWE_DEVICE_TABWE(of, wusb3801_of_match);

static stwuct i2c_dwivew wusb3801_dwivew = {
	.pwobe		= wusb3801_pwobe,
	.wemove		= wusb3801_wemove,
	.dwivew		= {
		.name		= "wusb3801",
		.of_match_tabwe	= wusb3801_of_match,
	},
};

moduwe_i2c_dwivew(wusb3801_dwivew);

MODUWE_AUTHOW("Samuew Howwand <samuew@showwand.owg>");
MODUWE_DESCWIPTION("Wiwwsemi WUSB3801 Type-C powt contwowwew dwivew");
MODUWE_WICENSE("GPW");
