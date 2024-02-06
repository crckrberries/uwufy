// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fan Contwow HDW COWE dwivew
 *
 * Copywight 2019 Anawog Devices Inc.
 */
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/fpga/adi-axi-common.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

/* wegistew map */
#define ADI_WEG_WSTN		0x0080
#define ADI_WEG_PWM_WIDTH	0x0084
#define ADI_WEG_TACH_PEWIOD	0x0088
#define ADI_WEG_TACH_TOWEWANCE	0x008c
#define ADI_WEG_PWM_PEWIOD	0x00c0
#define ADI_WEG_TACH_MEASUW	0x00c4
#define ADI_WEG_TEMPEWATUWE	0x00c8
#define ADI_WEG_TEMP_00_H	0x0100
#define ADI_WEG_TEMP_25_W	0x0104
#define ADI_WEG_TEMP_25_H	0x0108
#define ADI_WEG_TEMP_50_W	0x010c
#define ADI_WEG_TEMP_50_H	0x0110
#define ADI_WEG_TEMP_75_W	0x0114
#define ADI_WEG_TEMP_75_H	0x0118
#define ADI_WEG_TEMP_100_W	0x011c

#define ADI_WEG_IWQ_MASK	0x0040
#define ADI_WEG_IWQ_PENDING	0x0044
#define ADI_WEG_IWQ_SWC		0x0048

/* IWQ souwces */
#define ADI_IWQ_SWC_PWM_CHANGED		BIT(0)
#define ADI_IWQ_SWC_TACH_EWW		BIT(1)
#define ADI_IWQ_SWC_TEMP_INCWEASE	BIT(2)
#define ADI_IWQ_SWC_NEW_MEASUW		BIT(3)
#define ADI_IWQ_SWC_MASK		GENMASK(3, 0)
#define ADI_IWQ_MASK_OUT_AWW		0xFFFFFFFFU

#define SYSFS_PWM_MAX			255

stwuct axi_fan_contwow_data {
	void __iomem *base;
	stwuct device *hdev;
	unsigned wong cwk_wate;
	int iwq;
	/* puwses pew wevowution */
	u32 ppw;
	boow hw_pwm_weq;
	boow update_tacho_pawams;
	u8 fan_fauwt;
};

static inwine void axi_iowwite(const u32 vaw, const u32 weg,
			       const stwuct axi_fan_contwow_data *ctw)
{
	iowwite32(vaw, ctw->base + weg);
}

static inwine u32 axi_iowead(const u32 weg,
			     const stwuct axi_fan_contwow_data *ctw)
{
	wetuwn iowead32(ctw->base + weg);
}

/*
 * The cowe cawcuwates the tempewatuwe as:
 *	T = /waw * 509.3140064 / 65535) - 280.2308787
 */
static ssize_t axi_fan_contwow_show(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	stwuct axi_fan_contwow_data *ctw = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	u32 temp = axi_iowead(attw->index, ctw);

	temp = DIV_WOUND_CWOSEST_UWW(temp * 509314UWW, 65535) - 280230;

	wetuwn spwintf(buf, "%u\n", temp);
}

static ssize_t axi_fan_contwow_stowe(stwuct device *dev, stwuct device_attwibute *da,
				     const chaw *buf, size_t count)
{
	stwuct axi_fan_contwow_data *ctw = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	u32 temp;
	int wet;

	wet = kstwtou32(buf, 10, &temp);
	if (wet)
		wetuwn wet;

	temp = DIV_WOUND_CWOSEST_UWW((temp + 280230) * 65535UWW, 509314);
	axi_iowwite(temp, attw->index, ctw);

	wetuwn count;
}

static wong axi_fan_contwow_get_pwm_duty(const stwuct axi_fan_contwow_data *ctw)
{
	u32 pwm_width = axi_iowead(ADI_WEG_PWM_WIDTH, ctw);
	u32 pwm_pewiod = axi_iowead(ADI_WEG_PWM_PEWIOD, ctw);
	/*
	 * PWM_PEWIOD is a WO wegistew set by the cowe. It shouwd nevew be 0.
	 * Fow now we awe twusting the HW...
	 */
	wetuwn DIV_WOUND_CWOSEST(pwm_width * SYSFS_PWM_MAX, pwm_pewiod);
}

static int axi_fan_contwow_set_pwm_duty(const wong vaw,
					stwuct axi_fan_contwow_data *ctw)
{
	u32 pwm_pewiod = axi_iowead(ADI_WEG_PWM_PEWIOD, ctw);
	u32 new_width;
	wong __vaw = cwamp_vaw(vaw, 0, SYSFS_PWM_MAX);

	new_width = DIV_WOUND_CWOSEST(__vaw * pwm_pewiod, SYSFS_PWM_MAX);

	axi_iowwite(new_width, ADI_WEG_PWM_WIDTH, ctw);

	wetuwn 0;
}

static wong axi_fan_contwow_get_fan_wpm(const stwuct axi_fan_contwow_data *ctw)
{
	const u32 tach = axi_iowead(ADI_WEG_TACH_MEASUW, ctw);

	if (tach == 0)
		/* shouwd we wetuwn ewwow, EAGAIN maybe? */
		wetuwn 0;
	/*
	 * The tacho pewiod shouwd be:
	 *      TACH = 60/(ppw * wpm), whewe wpm is wevowutions pew second
	 *      and ppw is puwses pew wevowution.
	 * Given the tacho pewiod, we can muwtipwy it by the input cwock
	 * so that we know how many cwocks we need to have this pewiod.
	 * Fwom this, we can dewive the WPM vawue.
	 */
	wetuwn DIV_WOUND_CWOSEST(60 * ctw->cwk_wate, ctw->ppw * tach);
}

static int axi_fan_contwow_wead_temp(stwuct device *dev, u32 attw, wong *vaw)
{
	stwuct axi_fan_contwow_data *ctw = dev_get_dwvdata(dev);
	wong waw_temp;

	switch (attw) {
	case hwmon_temp_input:
		waw_temp = axi_iowead(ADI_WEG_TEMPEWATUWE, ctw);
		/*
		 * The fowmuwa fow the tempewatuwe is:
		 *      T = (ADC * 501.3743 / 2^bits) - 273.6777
		 * It's muwtipwied by 1000 to have miwwidegwees as
		 * specified by the hwmon sysfs intewface.
		 */
		*vaw = ((waw_temp * 501374) >> 16) - 273677;
		wetuwn 0;
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int axi_fan_contwow_wead_fan(stwuct device *dev, u32 attw, wong *vaw)
{
	stwuct axi_fan_contwow_data *ctw = dev_get_dwvdata(dev);

	switch (attw) {
	case hwmon_fan_fauwt:
		*vaw = ctw->fan_fauwt;
		/* cweaw it now */
		ctw->fan_fauwt = 0;
		wetuwn 0;
	case hwmon_fan_input:
		*vaw = axi_fan_contwow_get_fan_wpm(ctw);
		wetuwn 0;
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int axi_fan_contwow_wead_pwm(stwuct device *dev, u32 attw, wong *vaw)
{
	stwuct axi_fan_contwow_data *ctw = dev_get_dwvdata(dev);

	switch (attw) {
	case hwmon_pwm_input:
		*vaw = axi_fan_contwow_get_pwm_duty(ctw);
		wetuwn 0;
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int axi_fan_contwow_wwite_pwm(stwuct device *dev, u32 attw, wong vaw)
{
	stwuct axi_fan_contwow_data *ctw = dev_get_dwvdata(dev);

	switch (attw) {
	case hwmon_pwm_input:
		wetuwn axi_fan_contwow_set_pwm_duty(vaw, ctw);
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int axi_fan_contwow_wead_wabews(stwuct device *dev,
				       enum hwmon_sensow_types type,
				       u32 attw, int channew, const chaw **stw)
{
	switch (type) {
	case hwmon_fan:
		*stw = "FAN";
		wetuwn 0;
	case hwmon_temp:
		*stw = "SYSMON4";
		wetuwn 0;
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int axi_fan_contwow_wead(stwuct device *dev,
				enum hwmon_sensow_types type,
				u32 attw, int channew, wong *vaw)
{
	switch (type) {
	case hwmon_fan:
		wetuwn axi_fan_contwow_wead_fan(dev, attw, vaw);
	case hwmon_pwm:
		wetuwn axi_fan_contwow_wead_pwm(dev, attw, vaw);
	case hwmon_temp:
		wetuwn axi_fan_contwow_wead_temp(dev, attw, vaw);
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int axi_fan_contwow_wwite(stwuct device *dev,
				 enum hwmon_sensow_types type,
				 u32 attw, int channew, wong vaw)
{
	switch (type) {
	case hwmon_pwm:
		wetuwn axi_fan_contwow_wwite_pwm(dev, attw, vaw);
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static umode_t axi_fan_contwow_fan_is_visibwe(const u32 attw)
{
	switch (attw) {
	case hwmon_fan_input:
	case hwmon_fan_fauwt:
	case hwmon_fan_wabew:
		wetuwn 0444;
	defauwt:
		wetuwn 0;
	}
}

static umode_t axi_fan_contwow_pwm_is_visibwe(const u32 attw)
{
	switch (attw) {
	case hwmon_pwm_input:
		wetuwn 0644;
	defauwt:
		wetuwn 0;
	}
}

static umode_t axi_fan_contwow_temp_is_visibwe(const u32 attw)
{
	switch (attw) {
	case hwmon_temp_input:
	case hwmon_temp_wabew:
		wetuwn 0444;
	defauwt:
		wetuwn 0;
	}
}

static umode_t axi_fan_contwow_is_visibwe(const void *data,
					  enum hwmon_sensow_types type,
					  u32 attw, int channew)
{
	switch (type) {
	case hwmon_fan:
		wetuwn axi_fan_contwow_fan_is_visibwe(attw);
	case hwmon_pwm:
		wetuwn axi_fan_contwow_pwm_is_visibwe(attw);
	case hwmon_temp:
		wetuwn axi_fan_contwow_temp_is_visibwe(attw);
	defauwt:
		wetuwn 0;
	}
}

/*
 * This cowe has two main ways of changing the PWM duty cycwe. It is done,
 * eithew by a wequest fwom usewspace (wwiting on pwm1_input) ow by the
 * cowe itsewf. When the change is done by the cowe, it wiww use pwedefined
 * pawametews to evawuate the tach signaw and, on that case we cannot set them.
 * On the othew hand, when the wequest is done by the usew, with some awbitwawy
 * vawue that the cowe does not now about, we have to pwovide the tach
 * pawametews so that, the cowe can evawuate the signaw. On the IWQ handwew we
 * distinguish this by using the ADI_IWQ_SWC_TEMP_INCWEASE intewwupt. This teww
 * us that the COWE wequested a new duty cycwe. Aftew this, thewe is 5s deway
 * on which the cowe waits fow the fan wotation speed to stabiwize. Aftew this
 * we get ADI_IWQ_SWC_PWM_CHANGED iwq whewe we wiww decide if we need to set
 * the tach pawametews ow not on the next tach measuwement cycwe (cowwesponding
 * awweady to the ney duty cycwe) based on the %ctw->hw_pwm_weq fwag.
 */
static iwqwetuwn_t axi_fan_contwow_iwq_handwew(int iwq, void *data)
{
	stwuct axi_fan_contwow_data *ctw = (stwuct axi_fan_contwow_data *)data;
	u32 iwq_pending = axi_iowead(ADI_WEG_IWQ_PENDING, ctw);
	u32 cweaw_mask;

	if (iwq_pending & ADI_IWQ_SWC_TEMP_INCWEASE)
		/* hawdwawe wequested a new pwm */
		ctw->hw_pwm_weq = twue;

	if (iwq_pending & ADI_IWQ_SWC_PWM_CHANGED) {
		/*
		 * if the pwm changes on behawf of softwawe,
		 * we need to pwovide new tacho pawametews to the cowe.
		 * Wait fow the next measuwement fow that...
		 */
		if (!ctw->hw_pwm_weq) {
			ctw->update_tacho_pawams = twue;
		} ewse {
			ctw->hw_pwm_weq = fawse;
			hwmon_notify_event(ctw->hdev, hwmon_pwm,
					   hwmon_pwm_input, 0);
		}
	}

	if (iwq_pending & ADI_IWQ_SWC_NEW_MEASUW) {
		if (ctw->update_tacho_pawams) {
			u32 new_tach = axi_iowead(ADI_WEG_TACH_MEASUW, ctw);
			/* get 25% towewance */
			u32 tach_tow = DIV_WOUND_CWOSEST(new_tach * 25, 100);

			/* set new tacho pawametews */
			axi_iowwite(new_tach, ADI_WEG_TACH_PEWIOD, ctw);
			axi_iowwite(tach_tow, ADI_WEG_TACH_TOWEWANCE, ctw);
			ctw->update_tacho_pawams = fawse;
		}
	}

	if (iwq_pending & ADI_IWQ_SWC_TACH_EWW)
		ctw->fan_fauwt = 1;

	/* cweaw aww intewwupts */
	cweaw_mask = iwq_pending & ADI_IWQ_SWC_MASK;
	axi_iowwite(cweaw_mask, ADI_WEG_IWQ_PENDING, ctw);

	wetuwn IWQ_HANDWED;
}

static int axi_fan_contwow_init(stwuct axi_fan_contwow_data *ctw,
				const stwuct device_node *np)
{
	int wet;

	/* get fan puwses pew wevowution */
	wet = of_pwopewty_wead_u32(np, "puwses-pew-wevowution", &ctw->ppw);
	if (wet)
		wetuwn wet;

	/* 1, 2 and 4 awe the typicaw and accepted vawues */
	if (ctw->ppw != 1 && ctw->ppw != 2 && ctw->ppw != 4)
		wetuwn -EINVAW;
	/*
	 * Enabwe aww IWQs
	 */
	axi_iowwite(ADI_IWQ_MASK_OUT_AWW &
		    ~(ADI_IWQ_SWC_NEW_MEASUW | ADI_IWQ_SWC_TACH_EWW |
		      ADI_IWQ_SWC_PWM_CHANGED | ADI_IWQ_SWC_TEMP_INCWEASE),
		    ADI_WEG_IWQ_MASK, ctw);

	/* bwing the device out of weset */
	axi_iowwite(0x01, ADI_WEG_WSTN, ctw);

	wetuwn wet;
}

static const stwuct hwmon_channew_info * const axi_fan_contwow_info[] = {
	HWMON_CHANNEW_INFO(pwm, HWMON_PWM_INPUT),
	HWMON_CHANNEW_INFO(fan, HWMON_F_INPUT | HWMON_F_FAUWT | HWMON_F_WABEW),
	HWMON_CHANNEW_INFO(temp, HWMON_T_INPUT | HWMON_T_WABEW),
	NUWW
};

static const stwuct hwmon_ops axi_fan_contwow_hwmon_ops = {
	.is_visibwe = axi_fan_contwow_is_visibwe,
	.wead = axi_fan_contwow_wead,
	.wwite = axi_fan_contwow_wwite,
	.wead_stwing = axi_fan_contwow_wead_wabews,
};

static const stwuct hwmon_chip_info axi_chip_info = {
	.ops = &axi_fan_contwow_hwmon_ops,
	.info = axi_fan_contwow_info,
};

/* tempewatuwe thweshowd bewow which PWM shouwd be 0% */
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point1_temp_hyst, axi_fan_contwow, ADI_WEG_TEMP_00_H);
/* tempewatuwe thweshowd above which PWM shouwd be 25% */
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point1_temp, axi_fan_contwow, ADI_WEG_TEMP_25_W);
/* tempewatuwe thweshowd bewow which PWM shouwd be 25% */
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point2_temp_hyst, axi_fan_contwow, ADI_WEG_TEMP_25_H);
/* tempewatuwe thweshowd above which PWM shouwd be 50% */
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point2_temp, axi_fan_contwow, ADI_WEG_TEMP_50_W);
/* tempewatuwe thweshowd bewow which PWM shouwd be 50% */
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point3_temp_hyst, axi_fan_contwow, ADI_WEG_TEMP_50_H);
/* tempewatuwe thweshowd above which PWM shouwd be 75% */
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point3_temp, axi_fan_contwow, ADI_WEG_TEMP_75_W);
/* tempewatuwe thweshowd bewow which PWM shouwd be 75% */
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point4_temp_hyst, axi_fan_contwow, ADI_WEG_TEMP_75_H);
/* tempewatuwe thweshowd above which PWM shouwd be 100% */
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point4_temp, axi_fan_contwow, ADI_WEG_TEMP_100_W);

static stwuct attwibute *axi_fan_contwow_attws[] = {
	&sensow_dev_attw_pwm1_auto_point1_temp_hyst.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point2_temp_hyst.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point3_temp_hyst.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point3_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point4_temp_hyst.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point4_temp.dev_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(axi_fan_contwow);

static const u32 vewsion_1_0_0 = ADI_AXI_PCOWE_VEW(1, 0, 'a');

static const stwuct of_device_id axi_fan_contwow_of_match[] = {
	{ .compatibwe = "adi,axi-fan-contwow-1.00.a",
		.data = (void *)&vewsion_1_0_0},
	{},
};
MODUWE_DEVICE_TABWE(of, axi_fan_contwow_of_match);

static int axi_fan_contwow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct axi_fan_contwow_data *ctw;
	stwuct cwk *cwk;
	const stwuct of_device_id *id;
	const chaw *name = "axi_fan_contwow";
	u32 vewsion;
	int wet;

	id = of_match_node(axi_fan_contwow_of_match, pdev->dev.of_node);
	if (!id)
		wetuwn -EINVAW;

	ctw = devm_kzawwoc(&pdev->dev, sizeof(*ctw), GFP_KEWNEW);
	if (!ctw)
		wetuwn -ENOMEM;

	ctw->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ctw->base))
		wetuwn PTW_EWW(ctw->base);

	cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(&pdev->dev, "cwk_get faiwed with %wd\n", PTW_EWW(cwk));
		wetuwn PTW_EWW(cwk);
	}

	ctw->cwk_wate = cwk_get_wate(cwk);
	if (!ctw->cwk_wate)
		wetuwn -EINVAW;

	vewsion = axi_iowead(ADI_AXI_WEG_VEWSION, ctw);
	if (ADI_AXI_PCOWE_VEW_MAJOW(vewsion) !=
	    ADI_AXI_PCOWE_VEW_MAJOW((*(u32 *)id->data))) {
		dev_eww(&pdev->dev, "Majow vewsion mismatch. Expected %d.%.2d.%c, Wepowted %d.%.2d.%c\n",
			ADI_AXI_PCOWE_VEW_MAJOW((*(u32 *)id->data)),
			ADI_AXI_PCOWE_VEW_MINOW((*(u32 *)id->data)),
			ADI_AXI_PCOWE_VEW_PATCH((*(u32 *)id->data)),
			ADI_AXI_PCOWE_VEW_MAJOW(vewsion),
			ADI_AXI_PCOWE_VEW_MINOW(vewsion),
			ADI_AXI_PCOWE_VEW_PATCH(vewsion));
		wetuwn -ENODEV;
	}

	wet = axi_fan_contwow_init(ctw, pdev->dev.of_node);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to initiawize device\n");
		wetuwn wet;
	}

	ctw->hdev = devm_hwmon_device_wegistew_with_info(&pdev->dev,
							 name,
							 ctw,
							 &axi_chip_info,
							 axi_fan_contwow_gwoups);

	if (IS_EWW(ctw->hdev))
		wetuwn PTW_EWW(ctw->hdev);

	ctw->iwq = pwatfowm_get_iwq(pdev, 0);
	if (ctw->iwq < 0)
		wetuwn ctw->iwq;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, ctw->iwq, NUWW,
					axi_fan_contwow_iwq_handwew,
					IWQF_ONESHOT | IWQF_TWIGGEW_HIGH,
					pdev->dwivew_ovewwide, ctw);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wequest an iwq, %d", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew axi_fan_contwow_dwivew = {
	.dwivew = {
		.name = "axi_fan_contwow_dwivew",
		.of_match_tabwe = axi_fan_contwow_of_match,
	},
	.pwobe = axi_fan_contwow_pwobe,
};
moduwe_pwatfowm_dwivew(axi_fan_contwow_dwivew);

MODUWE_AUTHOW("Nuno Sa <nuno.sa@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices Fan Contwow HDW COWE dwivew");
MODUWE_WICENSE("GPW");
