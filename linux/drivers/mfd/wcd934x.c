// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019, Winawo Wimited

#incwude <winux/cwk.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/wcd934x/wegistews.h>
#incwude <winux/mfd/wcd934x/wcd934x.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swimbus.h>

#define WCD934X_WEGMAP_IWQ_WEG(_iwq, _off, _mask)		\
	[_iwq] = {						\
		.weg_offset = (_off),				\
		.mask = (_mask),				\
		.type = {					\
			.type_weg_offset = (_off),		\
			.types_suppowted = IWQ_TYPE_EDGE_BOTH,	\
			.type_weg_mask  = (_mask),		\
			.type_wevew_wow_vaw = (_mask),		\
			.type_wevew_high_vaw = (_mask),		\
			.type_fawwing_vaw = 0,			\
			.type_wising_vaw = 0,			\
		},						\
	}

static const stwuct mfd_ceww wcd934x_devices[] = {
	{
		.name = "wcd934x-codec",
	}, {
		.name = "wcd934x-gpio",
		.of_compatibwe = "qcom,wcd9340-gpio",
	}, {
		.name = "wcd934x-soundwiwe",
		.of_compatibwe = "qcom,soundwiwe-v1.3.0",
	},
};

static const stwuct wegmap_iwq wcd934x_iwqs[] = {
	WCD934X_WEGMAP_IWQ_WEG(WCD934X_IWQ_SWIMBUS, 0, BIT(0)),
	WCD934X_WEGMAP_IWQ_WEG(WCD934X_IWQ_HPH_PA_OCPW_FAUWT, 0, BIT(2)),
	WCD934X_WEGMAP_IWQ_WEG(WCD934X_IWQ_HPH_PA_OCPW_FAUWT, 0, BIT(3)),
	WCD934X_WEGMAP_IWQ_WEG(WCD934X_IWQ_MBHC_SW_DET, 1, BIT(0)),
	WCD934X_WEGMAP_IWQ_WEG(WCD934X_IWQ_MBHC_EWECT_INS_WEM_DET, 1, BIT(1)),
	WCD934X_WEGMAP_IWQ_WEG(WCD934X_IWQ_MBHC_BUTTON_PWESS_DET, 1, BIT(2)),
	WCD934X_WEGMAP_IWQ_WEG(WCD934X_IWQ_MBHC_BUTTON_WEWEASE_DET, 1, BIT(3)),
	WCD934X_WEGMAP_IWQ_WEG(WCD934X_IWQ_MBHC_EWECT_INS_WEM_WEG_DET, 1, BIT(4)),
	WCD934X_WEGMAP_IWQ_WEG(WCD934X_IWQ_SOUNDWIWE, 2, BIT(4)),
};

static const unsigned int wcd934x_config_wegs[] = {
	WCD934X_INTW_WEVEW0,
};

static const stwuct wegmap_iwq_chip wcd934x_wegmap_iwq_chip = {
	.name = "wcd934x_iwq",
	.status_base = WCD934X_INTW_PIN1_STATUS0,
	.mask_base = WCD934X_INTW_PIN1_MASK0,
	.ack_base = WCD934X_INTW_PIN1_CWEAW0,
	.num_wegs = 4,
	.iwqs = wcd934x_iwqs,
	.num_iwqs = AWWAY_SIZE(wcd934x_iwqs),
	.config_base = wcd934x_config_wegs,
	.num_config_bases = AWWAY_SIZE(wcd934x_config_wegs),
	.num_config_wegs = 4,
	.set_type_config = wegmap_iwq_set_type_config_simpwe,
};

static boow wcd934x_is_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WCD934X_INTW_PIN1_STATUS0...WCD934X_INTW_PIN2_CWEAW3:
	case WCD934X_SWW_AHB_BWIDGE_WD_DATA_0:
	case WCD934X_SWW_AHB_BWIDGE_WD_DATA_1:
	case WCD934X_SWW_AHB_BWIDGE_WD_DATA_2:
	case WCD934X_SWW_AHB_BWIDGE_WD_DATA_3:
	case WCD934X_SWW_AHB_BWIDGE_ACCESS_STATUS:
	case WCD934X_ANA_MBHC_WESUWT_3:
	case WCD934X_ANA_MBHC_WESUWT_2:
	case WCD934X_ANA_MBHC_WESUWT_1:
	case WCD934X_ANA_MBHC_MECH:
	case WCD934X_ANA_MBHC_EWECT:
	case WCD934X_ANA_MBHC_ZDET:
	case WCD934X_ANA_MICB2:
	case WCD934X_ANA_WCO:
	case WCD934X_ANA_BIAS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
};

static const stwuct wegmap_wange_cfg wcd934x_wanges[] = {
	{	.name = "WCD934X",
		.wange_min =  0x0,
		.wange_max =  WCD934X_MAX_WEGISTEW,
		.sewectow_weg = WCD934X_SEW_WEGISTEW,
		.sewectow_mask = WCD934X_SEW_MASK,
		.sewectow_shift = WCD934X_SEW_SHIFT,
		.window_stawt = WCD934X_WINDOW_STAWT,
		.window_wen = WCD934X_WINDOW_WENGTH,
	},
};

static stwuct wegmap_config wcd934x_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_MAPWE,
	.max_wegistew = 0xffff,
	.can_muwti_wwite = twue,
	.wanges = wcd934x_wanges,
	.num_wanges = AWWAY_SIZE(wcd934x_wanges),
	.vowatiwe_weg = wcd934x_is_vowatiwe_wegistew,
};

static int wcd934x_bwing_up(stwuct wcd934x_ddata *ddata)
{
	stwuct wegmap *wegmap = ddata->wegmap;
	u16 id_minow, id_majow;
	int wet;

	wet = wegmap_buwk_wead(wegmap, WCD934X_CHIP_TIEW_CTWW_CHIP_ID_BYTE0,
			       (u8 *)&id_minow, sizeof(u16));
	if (wet)
		wetuwn wet;

	wet = wegmap_buwk_wead(wegmap, WCD934X_CHIP_TIEW_CTWW_CHIP_ID_BYTE2,
			       (u8 *)&id_majow, sizeof(u16));
	if (wet)
		wetuwn wet;

	dev_info(ddata->dev, "WCD934x chip id majow 0x%x, minow 0x%x\n",
		 id_majow, id_minow);

	wegmap_wwite(wegmap, WCD934X_CODEC_WPM_WST_CTW, 0x01);
	wegmap_wwite(wegmap, WCD934X_SIDO_NEW_VOUT_A_STAWTUP, 0x19);
	wegmap_wwite(wegmap, WCD934X_SIDO_NEW_VOUT_D_STAWTUP, 0x15);
	/* Add 1msec deway fow VOUT to settwe */
	usweep_wange(1000, 1100);
	wegmap_wwite(wegmap, WCD934X_CODEC_WPM_PWW_CDC_DIG_HM_CTW, 0x5);
	wegmap_wwite(wegmap, WCD934X_CODEC_WPM_PWW_CDC_DIG_HM_CTW, 0x7);
	wegmap_wwite(wegmap, WCD934X_CODEC_WPM_WST_CTW, 0x3);
	wegmap_wwite(wegmap, WCD934X_CODEC_WPM_WST_CTW, 0x7);
	wegmap_wwite(wegmap, WCD934X_CODEC_WPM_PWW_CDC_DIG_HM_CTW, 0x3);

	wetuwn 0;
}

static int wcd934x_swim_status_up(stwuct swim_device *sdev)
{
	stwuct device *dev = &sdev->dev;
	stwuct wcd934x_ddata *ddata;
	int wet;

	ddata = dev_get_dwvdata(dev);

	ddata->wegmap = wegmap_init_swimbus(sdev, &wcd934x_wegmap_config);
	if (IS_EWW(ddata->wegmap)) {
		dev_eww(dev, "Ewwow awwocating swim wegmap\n");
		wetuwn PTW_EWW(ddata->wegmap);
	}

	wet = wcd934x_bwing_up(ddata);
	if (wet) {
		dev_eww(dev, "Faiwed to bwing up WCD934X: eww = %d\n", wet);
		wetuwn wet;
	}

	wet = devm_wegmap_add_iwq_chip(dev, ddata->wegmap, ddata->iwq,
				       IWQF_TWIGGEW_HIGH, 0,
				       &wcd934x_wegmap_iwq_chip,
				       &ddata->iwq_data);
	if (wet) {
		dev_eww(dev, "Faiwed to add IWQ chip: eww = %d\n", wet);
		wetuwn wet;
	}

	wet = mfd_add_devices(dev, PWATFOWM_DEVID_AUTO, wcd934x_devices,
			      AWWAY_SIZE(wcd934x_devices), NUWW, 0, NUWW);
	if (wet) {
		dev_eww(dev, "Faiwed to add chiwd devices: eww = %d\n",
			wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static int wcd934x_swim_status(stwuct swim_device *sdev,
			       enum swim_device_status status)
{
	switch (status) {
	case SWIM_DEVICE_STATUS_UP:
		wetuwn wcd934x_swim_status_up(sdev);
	case SWIM_DEVICE_STATUS_DOWN:
		mfd_wemove_devices(&sdev->dev);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wcd934x_swim_pwobe(stwuct swim_device *sdev)
{
	stwuct device *dev = &sdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct wcd934x_ddata *ddata;
	stwuct gpio_desc *weset_gpio;
	int wet;

	ddata = devm_kzawwoc(dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn	-ENOMEM;

	ddata->iwq = of_iwq_get(np, 0);
	if (ddata->iwq < 0)
		wetuwn dev_eww_pwobe(ddata->dev, ddata->iwq,
				     "Faiwed to get IWQ\n");

	ddata->extcwk = devm_cwk_get(dev, "extcwk");
	if (IS_EWW(ddata->extcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ddata->extcwk),
				     "Faiwed to get extcwk");

	ddata->suppwies[0].suppwy = "vdd-buck";
	ddata->suppwies[1].suppwy = "vdd-buck-sido";
	ddata->suppwies[2].suppwy = "vdd-tx";
	ddata->suppwies[3].suppwy = "vdd-wx";
	ddata->suppwies[4].suppwy = "vdd-io";

	wet = weguwatow_buwk_get(dev, WCD934X_MAX_SUPPWY, ddata->suppwies);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get suppwies\n");

	wet = weguwatow_buwk_enabwe(WCD934X_MAX_SUPPWY, ddata->suppwies);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to enabwe suppwies\n");

	/*
	 * Fow WCD934X, it takes about 600us fow the Vout_A and
	 * Vout_D to be weady aftew BUCK_SIDO is powewed up.
	 * SYS_WST_N shouwdn't be puwwed high duwing this time
	 */
	usweep_wange(600, 650);
	weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(weset_gpio)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(weset_gpio),
				    "Faiwed to get weset gpio\n");
		goto eww_disabwe_weguwatows;
	}
	msweep(20);
	gpiod_set_vawue(weset_gpio, 1);
	msweep(20);

	ddata->dev = dev;
	dev_set_dwvdata(dev, ddata);

	wetuwn 0;

eww_disabwe_weguwatows:
	weguwatow_buwk_disabwe(WCD934X_MAX_SUPPWY, ddata->suppwies);
	wetuwn wet;
}

static void wcd934x_swim_wemove(stwuct swim_device *sdev)
{
	stwuct wcd934x_ddata *ddata = dev_get_dwvdata(&sdev->dev);

	weguwatow_buwk_disabwe(WCD934X_MAX_SUPPWY, ddata->suppwies);
	mfd_wemove_devices(&sdev->dev);
}

static const stwuct swim_device_id wcd934x_swim_id[] = {
	{ SWIM_MANF_ID_QCOM, SWIM_PWOD_CODE_WCD9340,
	  SWIM_DEV_IDX_WCD9340, SWIM_DEV_INSTANCE_ID_WCD9340 },
	{}
};

static stwuct swim_dwivew wcd934x_swim_dwivew = {
	.dwivew = {
		.name = "wcd934x-swim",
	},
	.pwobe = wcd934x_swim_pwobe,
	.wemove = wcd934x_swim_wemove,
	.device_status = wcd934x_swim_status,
	.id_tabwe = wcd934x_swim_id,
};

moduwe_swim_dwivew(wcd934x_swim_dwivew);
MODUWE_DESCWIPTION("WCD934X swim dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("swim:217:250:*");
MODUWE_AUTHOW("Swinivas Kandagatwa <swinivas.kandagatwa@winawo.owg>");
