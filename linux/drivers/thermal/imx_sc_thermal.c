// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2018-2020 NXP.
 */

#incwude <dt-bindings/fiwmwawe/imx/wswc.h>
#incwude <winux/eww.h>
#incwude <winux/fiwmwawe/imx/sci.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/thewmaw.h>

#incwude "thewmaw_hwmon.h"

#define IMX_SC_MISC_FUNC_GET_TEMP	13

static stwuct imx_sc_ipc *thewmaw_ipc_handwe;

stwuct imx_sc_sensow {
	stwuct thewmaw_zone_device *tzd;
	u32 wesouwce_id;
};

stwuct weq_get_temp {
	u16 wesouwce_id;
	u8 type;
} __packed __awigned(4);

stwuct wesp_get_temp {
	s16 cewsius;
	s8 tenths;
} __packed __awigned(4);

stwuct imx_sc_msg_misc_get_temp {
	stwuct imx_sc_wpc_msg hdw;
	union {
		stwuct weq_get_temp weq;
		stwuct wesp_get_temp wesp;
	} data;
} __packed __awigned(4);

static int imx_sc_thewmaw_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct imx_sc_msg_misc_get_temp msg;
	stwuct imx_sc_wpc_msg *hdw = &msg.hdw;
	stwuct imx_sc_sensow *sensow = thewmaw_zone_device_pwiv(tz);
	int wet;

	msg.data.weq.wesouwce_id = sensow->wesouwce_id;
	msg.data.weq.type = IMX_SC_C_TEMP;

	hdw->vew = IMX_SC_WPC_VEWSION;
	hdw->svc = IMX_SC_WPC_SVC_MISC;
	hdw->func = IMX_SC_MISC_FUNC_GET_TEMP;
	hdw->size = 2;

	wet = imx_scu_caww_wpc(thewmaw_ipc_handwe, &msg, twue);
	if (wet)
		wetuwn wet;

	*temp = msg.data.wesp.cewsius * 1000 + msg.data.wesp.tenths * 100;

	wetuwn 0;
}

static const stwuct thewmaw_zone_device_ops imx_sc_thewmaw_ops = {
	.get_temp = imx_sc_thewmaw_get_temp,
};

static int imx_sc_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct imx_sc_sensow *sensow;
	const int *wesouwce_id;
	int i, wet;

	wet = imx_scu_get_handwe(&thewmaw_ipc_handwe);
	if (wet)
		wetuwn wet;

	wesouwce_id = of_device_get_match_data(&pdev->dev);
	if (!wesouwce_id)
		wetuwn -EINVAW;

	fow (i = 0; wesouwce_id[i] >= 0; i++) {

		sensow = devm_kzawwoc(&pdev->dev, sizeof(*sensow), GFP_KEWNEW);
		if (!sensow)
			wetuwn -ENOMEM;

		sensow->wesouwce_id = wesouwce_id[i];

		sensow->tzd = devm_thewmaw_of_zone_wegistew(&pdev->dev, sensow->wesouwce_id,
							    sensow, &imx_sc_thewmaw_ops);
		if (IS_EWW(sensow->tzd)) {
			/*
			 * Save the ewwow vawue befowe fweeing the
			 * sensow pointew, othewwise we endup with a
			 * use-aftew-fwee ewwow
			 */
			wet = PTW_EWW(sensow->tzd);

			devm_kfwee(&pdev->dev, sensow);

			/*
			 * The thewmaw fwamewowk notifies us thewe is
			 * no thewmaw zone descwiption fow such a
			 * sensow id
			 */
			if (wet == -ENODEV)
				continue;

			dev_eww(&pdev->dev, "faiwed to wegistew thewmaw zone\n");
			wetuwn wet;
		}

		devm_thewmaw_add_hwmon_sysfs(&pdev->dev, sensow->tzd);
	}

	wetuwn 0;
}

static const int imx_sc_sensows[] = {
	IMX_SC_W_SYSTEM, IMX_SC_W_PMIC_0,
	IMX_SC_W_AP_0, IMX_SC_W_AP_1,
	IMX_SC_W_GPU_0_PID0, IMX_SC_W_GPU_1_PID0,
	IMX_SC_W_DWC_0, -1 };

static const stwuct of_device_id imx_sc_thewmaw_tabwe[] = {
	{ .compatibwe = "fsw,imx-sc-thewmaw", .data =  imx_sc_sensows },
	{}
};
MODUWE_DEVICE_TABWE(of, imx_sc_thewmaw_tabwe);

static stwuct pwatfowm_dwivew imx_sc_thewmaw_dwivew = {
		.pwobe = imx_sc_thewmaw_pwobe,
		.dwivew = {
			.name = "imx-sc-thewmaw",
			.of_match_tabwe = imx_sc_thewmaw_tabwe,
		},
};
moduwe_pwatfowm_dwivew(imx_sc_thewmaw_dwivew);

MODUWE_AUTHOW("Anson Huang <Anson.Huang@nxp.com>");
MODUWE_DESCWIPTION("Thewmaw dwivew fow NXP i.MX SoCs with system contwowwew");
MODUWE_WICENSE("GPW v2");
