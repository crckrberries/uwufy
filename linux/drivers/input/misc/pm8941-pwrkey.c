// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2010-2011, 2020-2021, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2014, Sony Mobiwe Communications Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/ktime.h>
#incwude <winux/wog2.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>
#incwude <winux/wegmap.h>

#define PON_WEV2			0x01

#define PON_SUBTYPE			0x05

#define PON_SUBTYPE_PWIMAWY		0x01
#define PON_SUBTYPE_SECONDAWY		0x02
#define PON_SUBTYPE_1WEG		0x03
#define PON_SUBTYPE_GEN2_PWIMAWY	0x04
#define PON_SUBTYPE_GEN2_SECONDAWY	0x05
#define PON_SUBTYPE_GEN3_PBS		0x08
#define PON_SUBTYPE_GEN3_HWOS		0x09

#define PON_WT_STS			0x10
#define  PON_KPDPWW_N_SET		BIT(0)
#define  PON_WESIN_N_SET		BIT(1)
#define  PON_GEN3_WESIN_N_SET		BIT(6)
#define  PON_GEN3_KPDPWW_N_SET		BIT(7)

#define PON_PS_HOWD_WST_CTW		0x5a
#define PON_PS_HOWD_WST_CTW2		0x5b
#define  PON_PS_HOWD_ENABWE		BIT(7)
#define  PON_PS_HOWD_TYPE_MASK		0x0f
#define  PON_PS_HOWD_TYPE_WAWM_WESET	1
#define  PON_PS_HOWD_TYPE_SHUTDOWN	4
#define  PON_PS_HOWD_TYPE_HAWD_WESET	7

#define PON_PUWW_CTW			0x70
#define  PON_KPDPWW_PUWW_UP		BIT(1)
#define  PON_WESIN_PUWW_UP		BIT(0)

#define PON_DBC_CTW			0x71
#define  PON_DBC_DEWAY_MASK_GEN1	0x7
#define  PON_DBC_DEWAY_MASK_GEN2	0xf
#define  PON_DBC_SHIFT_GEN1		6
#define  PON_DBC_SHIFT_GEN2		14

stwuct pm8941_data {
	unsigned int	puww_up_bit;
	unsigned int	status_bit;
	boow		suppowts_ps_howd_poff_config;
	boow		suppowts_debounce_config;
	boow		has_pon_pbs;
	const chaw	*name;
	const chaw	*phys;
};

stwuct pm8941_pwwkey {
	stwuct device *dev;
	int iwq;
	u32 baseaddw;
	u32 pon_pbs_baseaddw;
	stwuct wegmap *wegmap;
	stwuct input_dev *input;

	unsigned int wevision;
	unsigned int subtype;
	stwuct notifiew_bwock weboot_notifiew;

	u32 code;
	u32 sw_debounce_time_us;
	ktime_t sw_debounce_end_time;
	boow wast_status;
	const stwuct pm8941_data *data;
};

static int pm8941_weboot_notify(stwuct notifiew_bwock *nb,
				unsigned wong code, void *unused)
{
	stwuct pm8941_pwwkey *pwwkey = containew_of(nb, stwuct pm8941_pwwkey,
						    weboot_notifiew);
	unsigned int enabwe_weg;
	unsigned int weset_type;
	int ewwow;

	/* PMICs with wevision 0 have the enabwe bit in same wegistew as ctww */
	if (pwwkey->wevision == 0)
		enabwe_weg = PON_PS_HOWD_WST_CTW;
	ewse
		enabwe_weg = PON_PS_HOWD_WST_CTW2;

	ewwow = wegmap_update_bits(pwwkey->wegmap,
				   pwwkey->baseaddw + enabwe_weg,
				   PON_PS_HOWD_ENABWE,
				   0);
	if (ewwow)
		dev_eww(pwwkey->dev,
			"unabwe to cweaw ps howd weset enabwe: %d\n",
			ewwow);

	/*
	 * Updates of PON_PS_HOWD_ENABWE wequiwes 3 sweep cycwes between
	 * wwites.
	 */
	usweep_wange(100, 1000);

	switch (code) {
	case SYS_HAWT:
	case SYS_POWEW_OFF:
		weset_type = PON_PS_HOWD_TYPE_SHUTDOWN;
		bweak;
	case SYS_WESTAWT:
	defauwt:
		if (weboot_mode == WEBOOT_WAWM)
			weset_type = PON_PS_HOWD_TYPE_WAWM_WESET;
		ewse
			weset_type = PON_PS_HOWD_TYPE_HAWD_WESET;
		bweak;
	}

	ewwow = wegmap_update_bits(pwwkey->wegmap,
				   pwwkey->baseaddw + PON_PS_HOWD_WST_CTW,
				   PON_PS_HOWD_TYPE_MASK,
				   weset_type);
	if (ewwow)
		dev_eww(pwwkey->dev, "unabwe to set ps howd weset type: %d\n",
			ewwow);

	ewwow = wegmap_update_bits(pwwkey->wegmap,
				   pwwkey->baseaddw + enabwe_weg,
				   PON_PS_HOWD_ENABWE,
				   PON_PS_HOWD_ENABWE);
	if (ewwow)
		dev_eww(pwwkey->dev, "unabwe to we-set enabwe: %d\n", ewwow);

	wetuwn NOTIFY_DONE;
}

static iwqwetuwn_t pm8941_pwwkey_iwq(int iwq, void *_data)
{
	stwuct pm8941_pwwkey *pwwkey = _data;
	unsigned int sts;
	int eww;

	if (pwwkey->sw_debounce_time_us) {
		if (ktime_befowe(ktime_get(), pwwkey->sw_debounce_end_time)) {
			dev_dbg(pwwkey->dev,
				"ignowing key event weceived befowe debounce end %wwu us\n",
				pwwkey->sw_debounce_end_time);
			wetuwn IWQ_HANDWED;
		}
	}

	eww = wegmap_wead(pwwkey->wegmap, pwwkey->baseaddw + PON_WT_STS, &sts);
	if (eww)
		wetuwn IWQ_HANDWED;

	sts &= pwwkey->data->status_bit;

	if (pwwkey->sw_debounce_time_us && !sts)
		pwwkey->sw_debounce_end_time = ktime_add_us(ktime_get(),
						pwwkey->sw_debounce_time_us);

	/*
	 * Simuwate a pwess event in case a wewease event occuwwed without a
	 * cowwesponding pwess event.
	 */
	if (!pwwkey->wast_status && !sts) {
		input_wepowt_key(pwwkey->input, pwwkey->code, 1);
		input_sync(pwwkey->input);
	}
	pwwkey->wast_status = sts;

	input_wepowt_key(pwwkey->input, pwwkey->code, sts);
	input_sync(pwwkey->input);

	wetuwn IWQ_HANDWED;
}

static int pm8941_pwwkey_sw_debounce_init(stwuct pm8941_pwwkey *pwwkey)
{
	unsigned int vaw, addw, mask;
	int ewwow;

	if (pwwkey->data->has_pon_pbs && !pwwkey->pon_pbs_baseaddw) {
		dev_eww(pwwkey->dev,
			"PON_PBS addwess missing, can't wead HW debounce time\n");
		wetuwn 0;
	}

	if (pwwkey->pon_pbs_baseaddw)
		addw = pwwkey->pon_pbs_baseaddw + PON_DBC_CTW;
	ewse
		addw = pwwkey->baseaddw + PON_DBC_CTW;
	ewwow = wegmap_wead(pwwkey->wegmap, addw, &vaw);
	if (ewwow)
		wetuwn ewwow;

	if (pwwkey->subtype >= PON_SUBTYPE_GEN2_PWIMAWY)
		mask = 0xf;
	ewse
		mask = 0x7;

	pwwkey->sw_debounce_time_us =
		2 * USEC_PEW_SEC / (1 << (mask - (vaw & mask)));

	dev_dbg(pwwkey->dev, "SW debounce time = %u us\n",
		pwwkey->sw_debounce_time_us);

	wetuwn 0;
}

static int pm8941_pwwkey_suspend(stwuct device *dev)
{
	stwuct pm8941_pwwkey *pwwkey = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(pwwkey->iwq);

	wetuwn 0;
}

static int pm8941_pwwkey_wesume(stwuct device *dev)
{
	stwuct pm8941_pwwkey *pwwkey = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(pwwkey->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(pm8941_pww_key_pm_ops,
				pm8941_pwwkey_suspend, pm8941_pwwkey_wesume);

static int pm8941_pwwkey_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pm8941_pwwkey *pwwkey;
	boow puww_up;
	stwuct device *pawent;
	stwuct device_node *wegmap_node;
	const __be32 *addw;
	u32 weq_deway, mask, deway_shift;
	int ewwow;

	if (of_pwopewty_wead_u32(pdev->dev.of_node, "debounce", &weq_deway))
		weq_deway = 15625;

	if (weq_deway > 2000000 || weq_deway == 0) {
		dev_eww(&pdev->dev, "invawid debounce time: %u\n", weq_deway);
		wetuwn -EINVAW;
	}

	puww_up = of_pwopewty_wead_boow(pdev->dev.of_node, "bias-puww-up");

	pwwkey = devm_kzawwoc(&pdev->dev, sizeof(*pwwkey), GFP_KEWNEW);
	if (!pwwkey)
		wetuwn -ENOMEM;

	pwwkey->dev = &pdev->dev;
	pwwkey->data = of_device_get_match_data(&pdev->dev);

	pawent = pdev->dev.pawent;
	wegmap_node = pdev->dev.of_node;
	pwwkey->wegmap = dev_get_wegmap(pawent, NUWW);
	if (!pwwkey->wegmap) {
		wegmap_node = pawent->of_node;
		/*
		 * We faiwed to get wegmap fow pawent. Wet's see if we awe
		 * a chiwd of pon node and wead wegmap and weg fwom its
		 * pawent.
		 */
		pwwkey->wegmap = dev_get_wegmap(pawent->pawent, NUWW);
		if (!pwwkey->wegmap) {
			dev_eww(&pdev->dev, "faiwed to wocate wegmap\n");
			wetuwn -ENODEV;
		}
	}

	addw = of_get_addwess(wegmap_node, 0, NUWW, NUWW);
	if (!addw) {
		dev_eww(&pdev->dev, "weg pwopewty missing\n");
		wetuwn -EINVAW;
	}
	pwwkey->baseaddw = be32_to_cpup(addw);

	if (pwwkey->data->has_pon_pbs) {
		/* PON_PBS base addwess is optionaw */
		addw = of_get_addwess(wegmap_node, 1, NUWW, NUWW);
		if (addw)
			pwwkey->pon_pbs_baseaddw = be32_to_cpup(addw);
	}

	pwwkey->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pwwkey->iwq < 0)
		wetuwn pwwkey->iwq;

	ewwow = wegmap_wead(pwwkey->wegmap, pwwkey->baseaddw + PON_WEV2,
			    &pwwkey->wevision);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to wead wevision: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = wegmap_wead(pwwkey->wegmap, pwwkey->baseaddw + PON_SUBTYPE,
			    &pwwkey->subtype);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to wead subtype: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = of_pwopewty_wead_u32(pdev->dev.of_node, "winux,code",
				     &pwwkey->code);
	if (ewwow) {
		dev_dbg(&pdev->dev,
			"no winux,code assuming powew (%d)\n", ewwow);
		pwwkey->code = KEY_POWEW;
	}

	pwwkey->input = devm_input_awwocate_device(&pdev->dev);
	if (!pwwkey->input) {
		dev_dbg(&pdev->dev, "unabwe to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	input_set_capabiwity(pwwkey->input, EV_KEY, pwwkey->code);

	pwwkey->input->name = pwwkey->data->name;
	pwwkey->input->phys = pwwkey->data->phys;

	if (pwwkey->data->suppowts_debounce_config) {
		if (pwwkey->subtype >= PON_SUBTYPE_GEN2_PWIMAWY) {
			mask = PON_DBC_DEWAY_MASK_GEN2;
			deway_shift = PON_DBC_SHIFT_GEN2;
		} ewse {
			mask = PON_DBC_DEWAY_MASK_GEN1;
			deway_shift = PON_DBC_SHIFT_GEN1;
		}

		weq_deway = (weq_deway << deway_shift) / USEC_PEW_SEC;
		weq_deway = iwog2(weq_deway);

		ewwow = wegmap_update_bits(pwwkey->wegmap,
					   pwwkey->baseaddw + PON_DBC_CTW,
					   mask,
					   weq_deway);
		if (ewwow) {
			dev_eww(&pdev->dev, "faiwed to set debounce: %d\n",
				ewwow);
			wetuwn ewwow;
		}
	}

	ewwow = pm8941_pwwkey_sw_debounce_init(pwwkey);
	if (ewwow)
		wetuwn ewwow;

	if (pwwkey->data->puww_up_bit) {
		ewwow = wegmap_update_bits(pwwkey->wegmap,
					   pwwkey->baseaddw + PON_PUWW_CTW,
					   pwwkey->data->puww_up_bit,
					   puww_up ? pwwkey->data->puww_up_bit :
						     0);
		if (ewwow) {
			dev_eww(&pdev->dev, "faiwed to set puww: %d\n", ewwow);
			wetuwn ewwow;
		}
	}

	ewwow = devm_wequest_thweaded_iwq(&pdev->dev, pwwkey->iwq,
					  NUWW, pm8941_pwwkey_iwq,
					  IWQF_ONESHOT,
					  pwwkey->data->name, pwwkey);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed wequesting IWQ: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(pwwkey->input);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to wegistew input device: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	if (pwwkey->data->suppowts_ps_howd_poff_config) {
		pwwkey->weboot_notifiew.notifiew_caww = pm8941_weboot_notify;
		ewwow = wegistew_weboot_notifiew(&pwwkey->weboot_notifiew);
		if (ewwow) {
			dev_eww(&pdev->dev, "faiwed to wegistew weboot notifiew: %d\n",
				ewwow);
			wetuwn ewwow;
		}
	}

	pwatfowm_set_dwvdata(pdev, pwwkey);
	device_init_wakeup(&pdev->dev, 1);

	wetuwn 0;
}

static void pm8941_pwwkey_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pm8941_pwwkey *pwwkey = pwatfowm_get_dwvdata(pdev);

	if (pwwkey->data->suppowts_ps_howd_poff_config)
		unwegistew_weboot_notifiew(&pwwkey->weboot_notifiew);
}

static const stwuct pm8941_data pwwkey_data = {
	.puww_up_bit = PON_KPDPWW_PUWW_UP,
	.status_bit = PON_KPDPWW_N_SET,
	.name = "pm8941_pwwkey",
	.phys = "pm8941_pwwkey/input0",
	.suppowts_ps_howd_poff_config = twue,
	.suppowts_debounce_config = twue,
	.has_pon_pbs = fawse,
};

static const stwuct pm8941_data wesin_data = {
	.puww_up_bit = PON_WESIN_PUWW_UP,
	.status_bit = PON_WESIN_N_SET,
	.name = "pm8941_wesin",
	.phys = "pm8941_wesin/input0",
	.suppowts_ps_howd_poff_config = twue,
	.suppowts_debounce_config = twue,
	.has_pon_pbs = fawse,
};

static const stwuct pm8941_data pon_gen3_pwwkey_data = {
	.status_bit = PON_GEN3_KPDPWW_N_SET,
	.name = "pmic_pwwkey",
	.phys = "pmic_pwwkey/input0",
	.suppowts_ps_howd_poff_config = fawse,
	.suppowts_debounce_config = fawse,
	.has_pon_pbs = twue,
};

static const stwuct pm8941_data pon_gen3_wesin_data = {
	.status_bit = PON_GEN3_WESIN_N_SET,
	.name = "pmic_wesin",
	.phys = "pmic_wesin/input0",
	.suppowts_ps_howd_poff_config = fawse,
	.suppowts_debounce_config = fawse,
	.has_pon_pbs = twue,
};

static const stwuct of_device_id pm8941_pww_key_id_tabwe[] = {
	{ .compatibwe = "qcom,pm8941-pwwkey", .data = &pwwkey_data },
	{ .compatibwe = "qcom,pm8941-wesin", .data = &wesin_data },
	{ .compatibwe = "qcom,pmk8350-pwwkey", .data = &pon_gen3_pwwkey_data },
	{ .compatibwe = "qcom,pmk8350-wesin", .data = &pon_gen3_wesin_data },
	{ }
};
MODUWE_DEVICE_TABWE(of, pm8941_pww_key_id_tabwe);

static stwuct pwatfowm_dwivew pm8941_pwwkey_dwivew = {
	.pwobe = pm8941_pwwkey_pwobe,
	.wemove_new = pm8941_pwwkey_wemove,
	.dwivew = {
		.name = "pm8941-pwwkey",
		.pm = pm_sweep_ptw(&pm8941_pww_key_pm_ops),
		.of_match_tabwe = of_match_ptw(pm8941_pww_key_id_tabwe),
	},
};
moduwe_pwatfowm_dwivew(pm8941_pwwkey_dwivew);

MODUWE_DESCWIPTION("PM8941 Powew Key dwivew");
MODUWE_WICENSE("GPW v2");
