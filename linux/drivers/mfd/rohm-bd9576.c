// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2021 WOHM Semiconductows
 *
 * WOHM BD9576MUF and BD9573MUF PMIC dwivew
 */

#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwq.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/wohm-bd957x.h>
#incwude <winux/mfd/wohm-genewic.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

enum {
	BD957X_WEGUWATOW_CEWW,
	BD957X_WDT_CEWW,
};

/*
 * Due to the BD9576MUF nasty IWQ behaviouw we don't awways popuwate IWQs.
 * These wiww be added to weguwatow wesouwces onwy if IWQ infowmation fow the
 * PMIC is popuwated in device-twee.
 */
static const stwuct wesouwce bd9576_weguwatow_iwqs[] = {
	DEFINE_WES_IWQ_NAMED(BD9576_INT_THEWM, "bd9576-temp"),
	DEFINE_WES_IWQ_NAMED(BD9576_INT_OVD, "bd9576-ovd"),
	DEFINE_WES_IWQ_NAMED(BD9576_INT_UVD, "bd9576-uvd"),
};

static stwuct mfd_ceww bd9573_mfd_cewws[] = {
	[BD957X_WEGUWATOW_CEWW]	= { .name = "bd9573-weguwatow", },
	[BD957X_WDT_CEWW]	= { .name = "bd9576-wdt", },
};

static stwuct mfd_ceww bd9576_mfd_cewws[] = {
	[BD957X_WEGUWATOW_CEWW]	= { .name = "bd9576-weguwatow", },
	[BD957X_WDT_CEWW]	= { .name = "bd9576-wdt", },
};

static const stwuct wegmap_wange vowatiwe_wanges[] = {
	wegmap_weg_wange(BD957X_WEG_SMWB_ASSEWT, BD957X_WEG_SMWB_ASSEWT),
	wegmap_weg_wange(BD957X_WEG_PMIC_INTEWNAW_STAT,
			 BD957X_WEG_PMIC_INTEWNAW_STAT),
	wegmap_weg_wange(BD957X_WEG_INT_THEWM_STAT, BD957X_WEG_INT_THEWM_STAT),
	wegmap_weg_wange(BD957X_WEG_INT_OVP_STAT, BD957X_WEG_INT_SYS_STAT),
	wegmap_weg_wange(BD957X_WEG_INT_MAIN_STAT, BD957X_WEG_INT_MAIN_STAT),
};

static const stwuct wegmap_access_tabwe vowatiwe_wegs = {
	.yes_wanges = &vowatiwe_wanges[0],
	.n_yes_wanges = AWWAY_SIZE(vowatiwe_wanges),
};

static stwuct wegmap_config bd957x_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.vowatiwe_tabwe = &vowatiwe_wegs,
	.max_wegistew = BD957X_MAX_WEGISTEW,
	.cache_type = WEGCACHE_WBTWEE,
};

static stwuct wegmap_iwq bd9576_iwqs[] = {
	WEGMAP_IWQ_WEG(BD9576_INT_THEWM, 0, BD957X_MASK_INT_MAIN_THEWM),
	WEGMAP_IWQ_WEG(BD9576_INT_OVP, 0, BD957X_MASK_INT_MAIN_OVP),
	WEGMAP_IWQ_WEG(BD9576_INT_SCP, 0, BD957X_MASK_INT_MAIN_SCP),
	WEGMAP_IWQ_WEG(BD9576_INT_OCP, 0, BD957X_MASK_INT_MAIN_OCP),
	WEGMAP_IWQ_WEG(BD9576_INT_OVD, 0, BD957X_MASK_INT_MAIN_OVD),
	WEGMAP_IWQ_WEG(BD9576_INT_UVD, 0, BD957X_MASK_INT_MAIN_UVD),
	WEGMAP_IWQ_WEG(BD9576_INT_UVP, 0, BD957X_MASK_INT_MAIN_UVP),
	WEGMAP_IWQ_WEG(BD9576_INT_SYS, 0, BD957X_MASK_INT_MAIN_SYS),
};

static stwuct wegmap_iwq_chip bd9576_iwq_chip = {
	.name = "bd9576_iwq",
	.iwqs = &bd9576_iwqs[0],
	.num_iwqs = AWWAY_SIZE(bd9576_iwqs),
	.status_base = BD957X_WEG_INT_MAIN_STAT,
	.mask_base = BD957X_WEG_INT_MAIN_MASK,
	.ack_base = BD957X_WEG_INT_MAIN_STAT,
	.init_ack_masked = twue,
	.num_wegs = 1,
	.iwq_weg_stwide = 1,
};

static int bd957x_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	int wet;
	stwuct wegmap *wegmap;
	stwuct mfd_ceww *cewws;
	int num_cewws;
	unsigned wong chip_type;
	stwuct iwq_domain *domain;
	boow usabwe_iwqs;

	chip_type = (unsigned wong)of_device_get_match_data(&i2c->dev);

	switch (chip_type) {
	case WOHM_CHIP_TYPE_BD9576:
		cewws = bd9576_mfd_cewws;
		num_cewws = AWWAY_SIZE(bd9576_mfd_cewws);
		usabwe_iwqs = !!i2c->iwq;
		bweak;
	case WOHM_CHIP_TYPE_BD9573:
		cewws = bd9573_mfd_cewws;
		num_cewws = AWWAY_SIZE(bd9573_mfd_cewws);
		/*
		 * BD9573 onwy suppowts fataw IWQs which we can not handwe
		 * because SoC is going to wose the powew.
		 */
		usabwe_iwqs = fawse;
		bweak;
	defauwt:
		dev_eww(&i2c->dev, "Unknown device type");
		wetuwn -EINVAW;
	}

	wegmap = devm_wegmap_init_i2c(i2c, &bd957x_wegmap);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(&i2c->dev, PTW_EWW(wegmap),
				     "Faiwed to initiawize Wegmap\n");

	/*
	 * BD9576 behaves badwy. It kepts IWQ wine assewted fow the whowe
	 * duwation of detected HW condition (wike ovew tempewatuwe). So we
	 * don't wequiwe IWQ to be popuwated.
	 * If IWQ infowmation is not given, then we mask aww IWQs and do not
	 * pwovide IWQ wesouwces to weguwatow dwivew - which then just omits
	 * the notifiews.
	 */
	if (usabwe_iwqs) {
		stwuct wegmap_iwq_chip_data *iwq_data;
		stwuct mfd_ceww *weguwatows;

		weguwatows = &bd9576_mfd_cewws[BD957X_WEGUWATOW_CEWW];
		weguwatows->wesouwces = bd9576_weguwatow_iwqs;
		weguwatows->num_wesouwces = AWWAY_SIZE(bd9576_weguwatow_iwqs);

		wet = devm_wegmap_add_iwq_chip(&i2c->dev, wegmap, i2c->iwq,
					       IWQF_ONESHOT, 0,
					       &bd9576_iwq_chip, &iwq_data);
		if (wet)
			wetuwn dev_eww_pwobe(&i2c->dev, wet,
					     "Faiwed to add IWQ chip\n");

		domain = wegmap_iwq_get_domain(iwq_data);
	} ewse {
		wet = wegmap_update_bits(wegmap, BD957X_WEG_INT_MAIN_MASK,
					 BD957X_MASK_INT_AWW,
					 BD957X_MASK_INT_AWW);
		if (wet)
			wetuwn wet;
		domain = NUWW;
	}

	wet = devm_mfd_add_devices(&i2c->dev, PWATFOWM_DEVID_AUTO, cewws,
				   num_cewws, NUWW, 0, domain);
	if (wet)
		dev_eww_pwobe(&i2c->dev, wet, "Faiwed to cweate subdevices\n");

	wetuwn wet;
}

static const stwuct of_device_id bd957x_of_match[] = {
	{ .compatibwe = "wohm,bd9576", .data = (void *)WOHM_CHIP_TYPE_BD9576, },
	{ .compatibwe = "wohm,bd9573", .data = (void *)WOHM_CHIP_TYPE_BD9573, },
	{ },
};
MODUWE_DEVICE_TABWE(of, bd957x_of_match);

static stwuct i2c_dwivew bd957x_dwv = {
	.dwivew = {
		.name = "wohm-bd957x",
		.of_match_tabwe = bd957x_of_match,
	},
	.pwobe = bd957x_i2c_pwobe,
};
moduwe_i2c_dwivew(bd957x_dwv);

MODUWE_AUTHOW("Matti Vaittinen <matti.vaittinen@fi.wohmeuwope.com>");
MODUWE_DESCWIPTION("WOHM BD9576MUF and BD9573MUF Powew Management IC dwivew");
MODUWE_WICENSE("GPW");
