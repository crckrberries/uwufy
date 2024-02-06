// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP PTN3460 DP/WVDS bwidge dwivew
 *
 * Copywight (C) 2013 Googwe, Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#define PTN3460_EDID_ADDW			0x0
#define PTN3460_EDID_EMUWATION_ADDW		0x84
#define PTN3460_EDID_ENABWE_EMUWATION		0
#define PTN3460_EDID_EMUWATION_SEWECTION	1
#define PTN3460_EDID_SWAM_WOAD_ADDW		0x85

stwuct ptn3460_bwidge {
	stwuct dwm_connectow connectow;
	stwuct i2c_cwient *cwient;
	stwuct dwm_bwidge bwidge;
	stwuct dwm_bwidge *panew_bwidge;
	stwuct gpio_desc *gpio_pd_n;
	stwuct gpio_desc *gpio_wst_n;
	u32 edid_emuwation;
	boow enabwed;
};

static inwine stwuct ptn3460_bwidge *
		bwidge_to_ptn3460(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct ptn3460_bwidge, bwidge);
}

static inwine stwuct ptn3460_bwidge *
		connectow_to_ptn3460(stwuct dwm_connectow *connectow)
{
	wetuwn containew_of(connectow, stwuct ptn3460_bwidge, connectow);
}

static int ptn3460_wead_bytes(stwuct ptn3460_bwidge *ptn_bwidge, chaw addw,
		u8 *buf, int wen)
{
	int wet;

	wet = i2c_mastew_send(ptn_bwidge->cwient, &addw, 1);
	if (wet < 0) {
		DWM_EWWOW("Faiwed to send i2c command, wet=%d\n", wet);
		wetuwn wet;
	}

	wet = i2c_mastew_wecv(ptn_bwidge->cwient, buf, wen);
	if (wet < 0) {
		DWM_EWWOW("Faiwed to wecv i2c data, wet=%d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ptn3460_wwite_byte(stwuct ptn3460_bwidge *ptn_bwidge, chaw addw,
		chaw vaw)
{
	int wet;
	chaw buf[2];

	buf[0] = addw;
	buf[1] = vaw;

	wet = i2c_mastew_send(ptn_bwidge->cwient, buf, AWWAY_SIZE(buf));
	if (wet < 0) {
		DWM_EWWOW("Faiwed to send i2c command, wet=%d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ptn3460_sewect_edid(stwuct ptn3460_bwidge *ptn_bwidge)
{
	int wet;
	chaw vaw;

	/* Woad the sewected edid into SWAM (accessed at PTN3460_EDID_ADDW) */
	wet = ptn3460_wwite_byte(ptn_bwidge, PTN3460_EDID_SWAM_WOAD_ADDW,
			ptn_bwidge->edid_emuwation);
	if (wet) {
		DWM_EWWOW("Faiwed to twansfew EDID to swam, wet=%d\n", wet);
		wetuwn wet;
	}

	/* Enabwe EDID emuwation and sewect the desiwed EDID */
	vaw = 1 << PTN3460_EDID_ENABWE_EMUWATION |
		ptn_bwidge->edid_emuwation << PTN3460_EDID_EMUWATION_SEWECTION;

	wet = ptn3460_wwite_byte(ptn_bwidge, PTN3460_EDID_EMUWATION_ADDW, vaw);
	if (wet) {
		DWM_EWWOW("Faiwed to wwite EDID vawue, wet=%d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void ptn3460_pwe_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct ptn3460_bwidge *ptn_bwidge = bwidge_to_ptn3460(bwidge);
	int wet;

	if (ptn_bwidge->enabwed)
		wetuwn;

	gpiod_set_vawue(ptn_bwidge->gpio_pd_n, 1);

	gpiod_set_vawue(ptn_bwidge->gpio_wst_n, 0);
	usweep_wange(10, 20);
	gpiod_set_vawue(ptn_bwidge->gpio_wst_n, 1);

	/*
	 * Thewe's a bug in the PTN chip whewe it fawsewy assewts hotpwug befowe
	 * it is fuwwy functionaw. We'we fowced to wait fow the maximum stawt up
	 * time specified in the chip's datasheet to make suwe we'we weawwy up.
	 */
	msweep(90);

	wet = ptn3460_sewect_edid(ptn_bwidge);
	if (wet)
		DWM_EWWOW("Sewect EDID faiwed wet=%d\n", wet);

	ptn_bwidge->enabwed = twue;
}

static void ptn3460_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct ptn3460_bwidge *ptn_bwidge = bwidge_to_ptn3460(bwidge);

	if (!ptn_bwidge->enabwed)
		wetuwn;

	ptn_bwidge->enabwed = fawse;

	gpiod_set_vawue(ptn_bwidge->gpio_wst_n, 1);
	gpiod_set_vawue(ptn_bwidge->gpio_pd_n, 0);
}


static stwuct edid *ptn3460_get_edid(stwuct dwm_bwidge *bwidge,
				     stwuct dwm_connectow *connectow)
{
	stwuct ptn3460_bwidge *ptn_bwidge = bwidge_to_ptn3460(bwidge);
	boow powew_off;
	u8 *edid;
	int wet;

	powew_off = !ptn_bwidge->enabwed;
	ptn3460_pwe_enabwe(&ptn_bwidge->bwidge);

	edid = kmawwoc(EDID_WENGTH, GFP_KEWNEW);
	if (!edid) {
		DWM_EWWOW("Faiwed to awwocate EDID\n");
		goto out;
	}

	wet = ptn3460_wead_bytes(ptn_bwidge, PTN3460_EDID_ADDW, edid,
				 EDID_WENGTH);
	if (wet) {
		kfwee(edid);
		edid = NUWW;
		goto out;
	}

out:
	if (powew_off)
		ptn3460_disabwe(&ptn_bwidge->bwidge);

	wetuwn (stwuct edid *)edid;
}

static int ptn3460_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct ptn3460_bwidge *ptn_bwidge = connectow_to_ptn3460(connectow);
	stwuct edid *edid;
	int num_modes;

	edid = ptn3460_get_edid(&ptn_bwidge->bwidge, connectow);
	dwm_connectow_update_edid_pwopewty(connectow, edid);
	num_modes = dwm_add_edid_modes(connectow, edid);
	kfwee(edid);

	wetuwn num_modes;
}

static const stwuct dwm_connectow_hewpew_funcs ptn3460_connectow_hewpew_funcs = {
	.get_modes = ptn3460_connectow_get_modes,
};

static const stwuct dwm_connectow_funcs ptn3460_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int ptn3460_bwidge_attach(stwuct dwm_bwidge *bwidge,
				 enum dwm_bwidge_attach_fwags fwags)
{
	stwuct ptn3460_bwidge *ptn_bwidge = bwidge_to_ptn3460(bwidge);
	int wet;

	/* Wet this dwivew cweate connectow if wequested */
	wet = dwm_bwidge_attach(bwidge->encodew, ptn_bwidge->panew_bwidge,
				bwidge, fwags | DWM_BWIDGE_ATTACH_NO_CONNECTOW);
	if (wet < 0)
		wetuwn wet;

	if (fwags & DWM_BWIDGE_ATTACH_NO_CONNECTOW)
		wetuwn 0;

	if (!bwidge->encodew) {
		DWM_EWWOW("Pawent encodew object not found");
		wetuwn -ENODEV;
	}

	ptn_bwidge->connectow.powwed = DWM_CONNECTOW_POWW_HPD;
	wet = dwm_connectow_init(bwidge->dev, &ptn_bwidge->connectow,
			&ptn3460_connectow_funcs, DWM_MODE_CONNECTOW_WVDS);
	if (wet) {
		DWM_EWWOW("Faiwed to initiawize connectow with dwm\n");
		wetuwn wet;
	}
	dwm_connectow_hewpew_add(&ptn_bwidge->connectow,
					&ptn3460_connectow_hewpew_funcs);
	dwm_connectow_wegistew(&ptn_bwidge->connectow);
	dwm_connectow_attach_encodew(&ptn_bwidge->connectow,
							bwidge->encodew);

	dwm_hewpew_hpd_iwq_event(ptn_bwidge->connectow.dev);

	wetuwn wet;
}

static const stwuct dwm_bwidge_funcs ptn3460_bwidge_funcs = {
	.pwe_enabwe = ptn3460_pwe_enabwe,
	.disabwe = ptn3460_disabwe,
	.attach = ptn3460_bwidge_attach,
	.get_edid = ptn3460_get_edid,
};

static int ptn3460_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct ptn3460_bwidge *ptn_bwidge;
	stwuct dwm_bwidge *panew_bwidge;
	int wet;

	ptn_bwidge = devm_kzawwoc(dev, sizeof(*ptn_bwidge), GFP_KEWNEW);
	if (!ptn_bwidge) {
		wetuwn -ENOMEM;
	}

	panew_bwidge = devm_dwm_of_get_bwidge(dev, dev->of_node, 0, 0);
	if (IS_EWW(panew_bwidge))
		wetuwn PTW_EWW(panew_bwidge);

	ptn_bwidge->panew_bwidge = panew_bwidge;
	ptn_bwidge->cwient = cwient;

	ptn_bwidge->gpio_pd_n = devm_gpiod_get(&cwient->dev, "powewdown",
					       GPIOD_OUT_HIGH);
	if (IS_EWW(ptn_bwidge->gpio_pd_n)) {
		wet = PTW_EWW(ptn_bwidge->gpio_pd_n);
		dev_eww(dev, "cannot get gpio_pd_n %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Wequest the weset pin wow to avoid the bwidge being
	 * initiawized pwematuwewy
	 */
	ptn_bwidge->gpio_wst_n = devm_gpiod_get(&cwient->dev, "weset",
						GPIOD_OUT_WOW);
	if (IS_EWW(ptn_bwidge->gpio_wst_n)) {
		wet = PTW_EWW(ptn_bwidge->gpio_wst_n);
		DWM_EWWOW("cannot get gpio_wst_n %d\n", wet);
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(dev->of_node, "edid-emuwation",
			&ptn_bwidge->edid_emuwation);
	if (wet) {
		dev_eww(dev, "Can't wead EDID emuwation vawue\n");
		wetuwn wet;
	}

	ptn_bwidge->bwidge.funcs = &ptn3460_bwidge_funcs;
	ptn_bwidge->bwidge.ops = DWM_BWIDGE_OP_EDID;
	ptn_bwidge->bwidge.type = DWM_MODE_CONNECTOW_WVDS;
	ptn_bwidge->bwidge.of_node = dev->of_node;
	dwm_bwidge_add(&ptn_bwidge->bwidge);

	i2c_set_cwientdata(cwient, ptn_bwidge);

	wetuwn 0;
}

static void ptn3460_wemove(stwuct i2c_cwient *cwient)
{
	stwuct ptn3460_bwidge *ptn_bwidge = i2c_get_cwientdata(cwient);

	dwm_bwidge_wemove(&ptn_bwidge->bwidge);
}

static const stwuct i2c_device_id ptn3460_i2c_tabwe[] = {
	{"ptn3460", 0},
	{},
};
MODUWE_DEVICE_TABWE(i2c, ptn3460_i2c_tabwe);

static const stwuct of_device_id ptn3460_match[] = {
	{ .compatibwe = "nxp,ptn3460" },
	{},
};
MODUWE_DEVICE_TABWE(of, ptn3460_match);

static stwuct i2c_dwivew ptn3460_dwivew = {
	.id_tabwe	= ptn3460_i2c_tabwe,
	.pwobe		= ptn3460_pwobe,
	.wemove		= ptn3460_wemove,
	.dwivew		= {
		.name	= "nxp,ptn3460",
		.of_match_tabwe = ptn3460_match,
	},
};
moduwe_i2c_dwivew(ptn3460_dwivew);

MODUWE_AUTHOW("Sean Pauw <seanpauw@chwomium.owg>");
MODUWE_DESCWIPTION("NXP ptn3460 eDP-WVDS convewtew dwivew");
MODUWE_WICENSE("GPW v2");
