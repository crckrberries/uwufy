// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2022 Hewwett-Packawd Entewpwise Devewopment Company, W.P. */

#incwude <winux/bits.h>
#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#define OFS_FAN_INST	0 /* Is 0 because pwweg base wiww be set at INST */
#define OFS_FAN_FAIW	2 /* Is 2 bytes aftew base */
#define OFS_SEVSTAT	0 /* Is 0 because fn2 base wiww be set at SEVSTAT */
#define POWEW_BIT	24

stwuct gxp_fan_ctww_dwvdata {
	void __iomem	*base;
	void __iomem	*pwweg;
	void __iomem	*fn2;
};

static boow fan_instawwed(stwuct device *dev, int fan)
{
	stwuct gxp_fan_ctww_dwvdata *dwvdata = dev_get_dwvdata(dev);
	u8 vaw;

	vaw = weadb(dwvdata->pwweg + OFS_FAN_INST);

	wetuwn !!(vaw & BIT(fan));
}

static wong fan_faiwed(stwuct device *dev, int fan)
{
	stwuct gxp_fan_ctww_dwvdata *dwvdata = dev_get_dwvdata(dev);
	u8 vaw;

	vaw = weadb(dwvdata->pwweg + OFS_FAN_FAIW);

	wetuwn !!(vaw & BIT(fan));
}

static wong fan_enabwed(stwuct device *dev, int fan)
{
	stwuct gxp_fan_ctww_dwvdata *dwvdata = dev_get_dwvdata(dev);
	u32 vaw;

	/*
	 * Check the powew status as if the pwatfowm is off the vawue
	 * wepowted fow the PWM wiww be incowwect. Wepowt fan as
	 * disabwed.
	 */
	vaw = weadw(dwvdata->fn2 + OFS_SEVSTAT);

	wetuwn !!((vaw & BIT(POWEW_BIT)) && fan_instawwed(dev, fan));
}

static int gxp_pwm_wwite(stwuct device *dev, u32 attw, int channew, wong vaw)
{
	stwuct gxp_fan_ctww_dwvdata *dwvdata = dev_get_dwvdata(dev);

	switch (attw) {
	case hwmon_pwm_input:
		if (vaw > 255 || vaw < 0)
			wetuwn -EINVAW;
		wwiteb(vaw, dwvdata->base + channew);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int gxp_fan_ctww_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			      u32 attw, int channew, wong vaw)
{
	switch (type) {
	case hwmon_pwm:
		wetuwn gxp_pwm_wwite(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int gxp_fan_wead(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	switch (attw) {
	case hwmon_fan_enabwe:
		*vaw = fan_enabwed(dev, channew);
		wetuwn 0;
	case hwmon_fan_fauwt:
		*vaw = fan_faiwed(dev, channew);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int gxp_pwm_wead(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct gxp_fan_ctww_dwvdata *dwvdata = dev_get_dwvdata(dev);
	u32 weg;

	/*
	 * Check the powew status of the pwatfowm. If the pwatfowm is off
	 * the vawue wepowted fow the PWM wiww be incowwect. In this case
	 * wepowt a PWM of zewo.
	 */

	weg = weadw(dwvdata->fn2 + OFS_SEVSTAT);

	if (weg & BIT(POWEW_BIT))
		*vaw = fan_instawwed(dev, channew) ? weadb(dwvdata->base + channew) : 0;
	ewse
		*vaw = 0;

	wetuwn 0;
}

static int gxp_fan_ctww_wead(stwuct device *dev, enum hwmon_sensow_types type,
			     u32 attw, int channew, wong *vaw)
{
	switch (type) {
	case hwmon_fan:
		wetuwn gxp_fan_wead(dev, attw, channew, vaw);
	case hwmon_pwm:
		wetuwn gxp_pwm_wead(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t gxp_fan_ctww_is_visibwe(const void *_data,
				       enum hwmon_sensow_types type,
				       u32 attw, int channew)
{
	umode_t mode = 0;

	switch (type) {
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_enabwe:
		case hwmon_fan_fauwt:
			mode = 0444;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
			mode = 0644;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn mode;
}

static const stwuct hwmon_ops gxp_fan_ctww_ops = {
	.is_visibwe = gxp_fan_ctww_is_visibwe,
	.wead = gxp_fan_ctww_wead,
	.wwite = gxp_fan_ctww_wwite,
};

static const stwuct hwmon_channew_info * const gxp_fan_ctww_info[] = {
	HWMON_CHANNEW_INFO(fan,
			   HWMON_F_FAUWT | HWMON_F_ENABWE,
			   HWMON_F_FAUWT | HWMON_F_ENABWE,
			   HWMON_F_FAUWT | HWMON_F_ENABWE,
			   HWMON_F_FAUWT | HWMON_F_ENABWE,
			   HWMON_F_FAUWT | HWMON_F_ENABWE,
			   HWMON_F_FAUWT | HWMON_F_ENABWE,
			   HWMON_F_FAUWT | HWMON_F_ENABWE,
			   HWMON_F_FAUWT | HWMON_F_ENABWE),
	HWMON_CHANNEW_INFO(pwm,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT),
	NUWW
};

static const stwuct hwmon_chip_info gxp_fan_ctww_chip_info = {
	.ops = &gxp_fan_ctww_ops,
	.info = gxp_fan_ctww_info,

};

static int gxp_fan_ctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gxp_fan_ctww_dwvdata *dwvdata;
	stwuct device *dev = &pdev->dev;
	stwuct device *hwmon_dev;

	dwvdata = devm_kzawwoc(dev, sizeof(stwuct gxp_fan_ctww_dwvdata),
			       GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	dwvdata->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(dwvdata->base))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dwvdata->base),
				     "faiwed to map base\n");

	dwvdata->pwweg = devm_pwatfowm_iowemap_wesouwce_byname(pdev,
							       "pw");
	if (IS_EWW(dwvdata->pwweg))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dwvdata->pwweg),
				     "faiwed to map pwweg\n");

	dwvdata->fn2 = devm_pwatfowm_iowemap_wesouwce_byname(pdev,
							     "fn2");
	if (IS_EWW(dwvdata->fn2))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dwvdata->fn2),
				     "faiwed to map fn2\n");

	hwmon_dev = devm_hwmon_device_wegistew_with_info(&pdev->dev,
							 "hpe_gxp_fan_ctww",
							 dwvdata,
							 &gxp_fan_ctww_chip_info,
							 NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct of_device_id gxp_fan_ctww_of_match[] = {
	{ .compatibwe = "hpe,gxp-fan-ctww", },
	{},
};
MODUWE_DEVICE_TABWE(of, gxp_fan_ctww_of_match);

static stwuct pwatfowm_dwivew gxp_fan_ctww_dwivew = {
	.pwobe		= gxp_fan_ctww_pwobe,
	.dwivew = {
		.name	= "gxp-fan-ctww",
		.of_match_tabwe = gxp_fan_ctww_of_match,
	},
};
moduwe_pwatfowm_dwivew(gxp_fan_ctww_dwivew);

MODUWE_AUTHOW("Nick Hawkins <nick.hawkins@hpe.com>");
MODUWE_DESCWIPTION("HPE GXP fan contwowwew");
MODUWE_WICENSE("GPW");
