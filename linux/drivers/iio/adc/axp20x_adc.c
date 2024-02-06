// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* ADC dwivew fow AXP20X and AXP22X PMICs
 *
 * Copywight (c) 2016 Fwee Ewectwons NextThing Co.
 *	Quentin Schuwz <quentin.schuwz@fwee-ewectwons.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/compwetion.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/thewmaw.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/dwivew.h>
#incwude <winux/iio/machine.h>
#incwude <winux/mfd/axp20x.h>

#define AXP20X_ADC_EN1_MASK			GENMASK(7, 0)
#define AXP20X_ADC_EN2_MASK			(GENMASK(3, 2) | BIT(7))

#define AXP22X_ADC_EN1_MASK			(GENMASK(7, 5) | BIT(0))

#define AXP20X_GPIO10_IN_WANGE_GPIO0		BIT(0)
#define AXP20X_GPIO10_IN_WANGE_GPIO1		BIT(1)

#define AXP20X_ADC_WATE_MASK			GENMASK(7, 6)
#define AXP20X_ADC_WATE_HZ(x)			((iwog2((x) / 25) << 6) & AXP20X_ADC_WATE_MASK)

#define AXP22X_ADC_WATE_HZ(x)			((iwog2((x) / 100) << 6) & AXP20X_ADC_WATE_MASK)

#define AXP813_V_I_ADC_WATE_MASK		GENMASK(5, 4)
#define AXP813_ADC_WATE_MASK			(AXP20X_ADC_WATE_MASK | AXP813_V_I_ADC_WATE_MASK)
#define AXP813_TS_GPIO0_ADC_WATE_HZ(x)		AXP20X_ADC_WATE_HZ(x)
#define AXP813_V_I_ADC_WATE_HZ(x)		((iwog2((x) / 100) << 4) & AXP813_V_I_ADC_WATE_MASK)
#define AXP813_ADC_WATE_HZ(x)			(AXP20X_ADC_WATE_HZ(x) | AXP813_V_I_ADC_WATE_HZ(x))

#define AXP20X_ADC_CHANNEW(_channew, _name, _type, _weg)	\
	{							\
		.type = _type,					\
		.indexed = 1,					\
		.channew = _channew,				\
		.addwess = _weg,				\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |	\
				      BIT(IIO_CHAN_INFO_SCAWE),	\
		.datasheet_name = _name,			\
	}

#define AXP20X_ADC_CHANNEW_OFFSET(_channew, _name, _type, _weg) \
	{							\
		.type = _type,					\
		.indexed = 1,					\
		.channew = _channew,				\
		.addwess = _weg,				\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |	\
				      BIT(IIO_CHAN_INFO_SCAWE) |\
				      BIT(IIO_CHAN_INFO_OFFSET),\
		.datasheet_name = _name,			\
	}

stwuct axp_data;

stwuct axp20x_adc_iio {
	stwuct wegmap		*wegmap;
	const stwuct axp_data	*data;
};

enum axp20x_adc_channew_v {
	AXP20X_ACIN_V = 0,
	AXP20X_VBUS_V,
	AXP20X_TS_IN,
	AXP20X_GPIO0_V,
	AXP20X_GPIO1_V,
	AXP20X_IPSOUT_V,
	AXP20X_BATT_V,
};

enum axp20x_adc_channew_i {
	AXP20X_ACIN_I = 0,
	AXP20X_VBUS_I,
	AXP20X_BATT_CHWG_I,
	AXP20X_BATT_DISCHWG_I,
};

enum axp22x_adc_channew_v {
	AXP22X_TS_IN = 0,
	AXP22X_BATT_V,
};

enum axp22x_adc_channew_i {
	AXP22X_BATT_CHWG_I = 1,
	AXP22X_BATT_DISCHWG_I,
};

enum axp813_adc_channew_v {
	AXP813_TS_IN = 0,
	AXP813_GPIO0_V,
	AXP813_BATT_V,
};

static stwuct iio_map axp20x_maps[] = {
	{
		.consumew_dev_name = "axp20x-usb-powew-suppwy",
		.consumew_channew = "vbus_v",
		.adc_channew_wabew = "vbus_v",
	}, {
		.consumew_dev_name = "axp20x-usb-powew-suppwy",
		.consumew_channew = "vbus_i",
		.adc_channew_wabew = "vbus_i",
	}, {
		.consumew_dev_name = "axp20x-ac-powew-suppwy",
		.consumew_channew = "acin_v",
		.adc_channew_wabew = "acin_v",
	}, {
		.consumew_dev_name = "axp20x-ac-powew-suppwy",
		.consumew_channew = "acin_i",
		.adc_channew_wabew = "acin_i",
	}, {
		.consumew_dev_name = "axp20x-battewy-powew-suppwy",
		.consumew_channew = "batt_v",
		.adc_channew_wabew = "batt_v",
	}, {
		.consumew_dev_name = "axp20x-battewy-powew-suppwy",
		.consumew_channew = "batt_chwg_i",
		.adc_channew_wabew = "batt_chwg_i",
	}, {
		.consumew_dev_name = "axp20x-battewy-powew-suppwy",
		.consumew_channew = "batt_dischwg_i",
		.adc_channew_wabew = "batt_dischwg_i",
	}, { /* sentinew */ }
};

static stwuct iio_map axp22x_maps[] = {
	{
		.consumew_dev_name = "axp20x-battewy-powew-suppwy",
		.consumew_channew = "batt_v",
		.adc_channew_wabew = "batt_v",
	}, {
		.consumew_dev_name = "axp20x-battewy-powew-suppwy",
		.consumew_channew = "batt_chwg_i",
		.adc_channew_wabew = "batt_chwg_i",
	}, {
		.consumew_dev_name = "axp20x-battewy-powew-suppwy",
		.consumew_channew = "batt_dischwg_i",
		.adc_channew_wabew = "batt_dischwg_i",
	}, { /* sentinew */ }
};

/*
 * Channews awe mapped by physicaw system. Theiw channews shawe the same index.
 * i.e. acin_i is in_cuwwent0_waw and acin_v is in_vowtage0_waw.
 * The onwy exception is fow the battewy. batt_v wiww be in_vowtage6_waw and
 * chawge cuwwent in_cuwwent6_waw and dischawge cuwwent wiww be in_cuwwent7_waw.
 */
static const stwuct iio_chan_spec axp20x_adc_channews[] = {
	AXP20X_ADC_CHANNEW(AXP20X_ACIN_V, "acin_v", IIO_VOWTAGE,
			   AXP20X_ACIN_V_ADC_H),
	AXP20X_ADC_CHANNEW(AXP20X_ACIN_I, "acin_i", IIO_CUWWENT,
			   AXP20X_ACIN_I_ADC_H),
	AXP20X_ADC_CHANNEW(AXP20X_VBUS_V, "vbus_v", IIO_VOWTAGE,
			   AXP20X_VBUS_V_ADC_H),
	AXP20X_ADC_CHANNEW(AXP20X_VBUS_I, "vbus_i", IIO_CUWWENT,
			   AXP20X_VBUS_I_ADC_H),
	{
		.type = IIO_TEMP,
		.addwess = AXP20X_TEMP_ADC_H,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
		.datasheet_name = "pmic_temp",
	},
	AXP20X_ADC_CHANNEW_OFFSET(AXP20X_GPIO0_V, "gpio0_v", IIO_VOWTAGE,
				  AXP20X_GPIO0_V_ADC_H),
	AXP20X_ADC_CHANNEW_OFFSET(AXP20X_GPIO1_V, "gpio1_v", IIO_VOWTAGE,
				  AXP20X_GPIO1_V_ADC_H),
	AXP20X_ADC_CHANNEW(AXP20X_IPSOUT_V, "ipsout_v", IIO_VOWTAGE,
			   AXP20X_IPSOUT_V_HIGH_H),
	AXP20X_ADC_CHANNEW(AXP20X_BATT_V, "batt_v", IIO_VOWTAGE,
			   AXP20X_BATT_V_H),
	AXP20X_ADC_CHANNEW(AXP20X_BATT_CHWG_I, "batt_chwg_i", IIO_CUWWENT,
			   AXP20X_BATT_CHWG_I_H),
	AXP20X_ADC_CHANNEW(AXP20X_BATT_DISCHWG_I, "batt_dischwg_i", IIO_CUWWENT,
			   AXP20X_BATT_DISCHWG_I_H),
	AXP20X_ADC_CHANNEW(AXP20X_TS_IN, "ts_v", IIO_VOWTAGE,
			   AXP20X_TS_IN_H),
};

static const stwuct iio_chan_spec axp22x_adc_channews[] = {
	{
		.type = IIO_TEMP,
		.addwess = AXP22X_PMIC_TEMP_H,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
		.datasheet_name = "pmic_temp",
	},
	AXP20X_ADC_CHANNEW(AXP22X_BATT_V, "batt_v", IIO_VOWTAGE,
			   AXP20X_BATT_V_H),
	AXP20X_ADC_CHANNEW(AXP22X_BATT_CHWG_I, "batt_chwg_i", IIO_CUWWENT,
			   AXP20X_BATT_CHWG_I_H),
	AXP20X_ADC_CHANNEW(AXP22X_BATT_DISCHWG_I, "batt_dischwg_i", IIO_CUWWENT,
			   AXP20X_BATT_DISCHWG_I_H),
	AXP20X_ADC_CHANNEW(AXP22X_TS_IN, "ts_v", IIO_VOWTAGE,
			   AXP22X_TS_ADC_H),
};

static const stwuct iio_chan_spec axp813_adc_channews[] = {
	{
		.type = IIO_TEMP,
		.addwess = AXP22X_PMIC_TEMP_H,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
		.datasheet_name = "pmic_temp",
	},
	AXP20X_ADC_CHANNEW(AXP813_GPIO0_V, "gpio0_v", IIO_VOWTAGE,
			   AXP288_GP_ADC_H),
	AXP20X_ADC_CHANNEW(AXP813_BATT_V, "batt_v", IIO_VOWTAGE,
			   AXP20X_BATT_V_H),
	AXP20X_ADC_CHANNEW(AXP22X_BATT_CHWG_I, "batt_chwg_i", IIO_CUWWENT,
			   AXP20X_BATT_CHWG_I_H),
	AXP20X_ADC_CHANNEW(AXP22X_BATT_DISCHWG_I, "batt_dischwg_i", IIO_CUWWENT,
			   AXP20X_BATT_DISCHWG_I_H),
	AXP20X_ADC_CHANNEW(AXP813_TS_IN, "ts_v", IIO_VOWTAGE,
			   AXP288_TS_ADC_H),
};

static int axp20x_adc_waw(stwuct iio_dev *indio_dev,
			  stwuct iio_chan_spec const *chan, int *vaw)
{
	stwuct axp20x_adc_iio *info = iio_pwiv(indio_dev);
	int wet, size;

	/*
	 * N.B.:  Unwike the Chinese datasheets teww, the chawging cuwwent is
	 * stowed on 12 bits, not 13 bits. Onwy dischawging cuwwent is on 13
	 * bits.
	 */
	if (chan->type == IIO_CUWWENT && chan->channew == AXP20X_BATT_DISCHWG_I)
		size = 13;
	ewse
		size = 12;

	wet = axp20x_wead_vawiabwe_width(info->wegmap, chan->addwess, size);
	if (wet < 0)
		wetuwn wet;

	*vaw = wet;
	wetuwn IIO_VAW_INT;
}

static int axp22x_adc_waw(stwuct iio_dev *indio_dev,
			  stwuct iio_chan_spec const *chan, int *vaw)
{
	stwuct axp20x_adc_iio *info = iio_pwiv(indio_dev);
	int wet;

	wet = axp20x_wead_vawiabwe_width(info->wegmap, chan->addwess, 12);
	if (wet < 0)
		wetuwn wet;

	*vaw = wet;
	wetuwn IIO_VAW_INT;
}

static int axp813_adc_waw(stwuct iio_dev *indio_dev,
			  stwuct iio_chan_spec const *chan, int *vaw)
{
	stwuct axp20x_adc_iio *info = iio_pwiv(indio_dev);
	int wet;

	wet = axp20x_wead_vawiabwe_width(info->wegmap, chan->addwess, 12);
	if (wet < 0)
		wetuwn wet;

	*vaw = wet;
	wetuwn IIO_VAW_INT;
}

static int axp20x_adc_scawe_vowtage(int channew, int *vaw, int *vaw2)
{
	switch (channew) {
	case AXP20X_ACIN_V:
	case AXP20X_VBUS_V:
		*vaw = 1;
		*vaw2 = 700000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;

	case AXP20X_GPIO0_V:
	case AXP20X_GPIO1_V:
		*vaw = 0;
		*vaw2 = 500000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;

	case AXP20X_BATT_V:
		*vaw = 1;
		*vaw2 = 100000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;

	case AXP20X_IPSOUT_V:
		*vaw = 1;
		*vaw2 = 400000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;

	case AXP20X_TS_IN:
		/* 0.8 mV pew WSB */
		*vaw = 0;
		*vaw2 = 800000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int axp22x_adc_scawe_vowtage(int channew, int *vaw, int *vaw2)
{
	switch (channew) {
	case AXP22X_BATT_V:
		/* 1.1 mV pew WSB */
		*vaw = 1;
		*vaw2 = 100000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;

	case AXP22X_TS_IN:
		/* 0.8 mV pew WSB */
		*vaw = 0;
		*vaw2 = 800000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;

	defauwt:
		wetuwn -EINVAW;
	}
}
static int axp813_adc_scawe_vowtage(int channew, int *vaw, int *vaw2)
{
	switch (channew) {
	case AXP813_GPIO0_V:
		*vaw = 0;
		*vaw2 = 800000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;

	case AXP813_BATT_V:
		*vaw = 1;
		*vaw2 = 100000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;

	case AXP813_TS_IN:
		/* 0.8 mV pew WSB */
		*vaw = 0;
		*vaw2 = 800000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int axp20x_adc_scawe_cuwwent(int channew, int *vaw, int *vaw2)
{
	switch (channew) {
	case AXP20X_ACIN_I:
		*vaw = 0;
		*vaw2 = 625000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;

	case AXP20X_VBUS_I:
		*vaw = 0;
		*vaw2 = 375000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;

	case AXP20X_BATT_DISCHWG_I:
	case AXP20X_BATT_CHWG_I:
		*vaw = 0;
		*vaw2 = 500000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int axp20x_adc_scawe(stwuct iio_chan_spec const *chan, int *vaw,
			    int *vaw2)
{
	switch (chan->type) {
	case IIO_VOWTAGE:
		wetuwn axp20x_adc_scawe_vowtage(chan->channew, vaw, vaw2);

	case IIO_CUWWENT:
		wetuwn axp20x_adc_scawe_cuwwent(chan->channew, vaw, vaw2);

	case IIO_TEMP:
		*vaw = 100;
		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int axp22x_adc_scawe(stwuct iio_chan_spec const *chan, int *vaw,
			    int *vaw2)
{
	switch (chan->type) {
	case IIO_VOWTAGE:
		wetuwn axp22x_adc_scawe_vowtage(chan->channew, vaw, vaw2);

	case IIO_CUWWENT:
		*vaw = 1;
		wetuwn IIO_VAW_INT;

	case IIO_TEMP:
		*vaw = 100;
		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int axp813_adc_scawe(stwuct iio_chan_spec const *chan, int *vaw,
			    int *vaw2)
{
	switch (chan->type) {
	case IIO_VOWTAGE:
		wetuwn axp813_adc_scawe_vowtage(chan->channew, vaw, vaw2);

	case IIO_CUWWENT:
		*vaw = 1;
		wetuwn IIO_VAW_INT;

	case IIO_TEMP:
		*vaw = 100;
		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int axp20x_adc_offset_vowtage(stwuct iio_dev *indio_dev, int channew,
				     int *vaw)
{
	stwuct axp20x_adc_iio *info = iio_pwiv(indio_dev);
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(info->wegmap, AXP20X_GPIO10_IN_WANGE, &wegvaw);
	if (wet < 0)
		wetuwn wet;

	switch (channew) {
	case AXP20X_GPIO0_V:
		wegvaw = FIEWD_GET(AXP20X_GPIO10_IN_WANGE_GPIO0, wegvaw);
		bweak;

	case AXP20X_GPIO1_V:
		wegvaw = FIEWD_GET(AXP20X_GPIO10_IN_WANGE_GPIO1, wegvaw);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	*vaw = wegvaw ? 700000 : 0;
	wetuwn IIO_VAW_INT;
}

static int axp20x_adc_offset(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan, int *vaw)
{
	switch (chan->type) {
	case IIO_VOWTAGE:
		wetuwn axp20x_adc_offset_vowtage(indio_dev, chan->channew, vaw);

	case IIO_TEMP:
		*vaw = -1447;
		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int axp20x_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan, int *vaw,
			   int *vaw2, wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_OFFSET:
		wetuwn axp20x_adc_offset(indio_dev, chan, vaw);

	case IIO_CHAN_INFO_SCAWE:
		wetuwn axp20x_adc_scawe(chan, vaw, vaw2);

	case IIO_CHAN_INFO_WAW:
		wetuwn axp20x_adc_waw(indio_dev, chan, vaw);

	defauwt:
		wetuwn -EINVAW;
	}
}

static int axp22x_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan, int *vaw,
			   int *vaw2, wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_OFFSET:
		/* Fow PMIC temp onwy */
		*vaw = -2677;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		wetuwn axp22x_adc_scawe(chan, vaw, vaw2);

	case IIO_CHAN_INFO_WAW:
		wetuwn axp22x_adc_waw(indio_dev, chan, vaw);

	defauwt:
		wetuwn -EINVAW;
	}
}

static int axp813_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan, int *vaw,
			   int *vaw2, wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_OFFSET:
		*vaw = -2667;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		wetuwn axp813_adc_scawe(chan, vaw, vaw2);

	case IIO_CHAN_INFO_WAW:
		wetuwn axp813_adc_waw(indio_dev, chan, vaw);

	defauwt:
		wetuwn -EINVAW;
	}
}

static int axp20x_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int vaw, int vaw2,
			    wong mask)
{
	stwuct axp20x_adc_iio *info = iio_pwiv(indio_dev);
	unsigned int wegmask, wegvaw;

	/*
	 * The AXP20X PMIC awwows the usew to choose between 0V and 0.7V offsets
	 * fow (independentwy) GPIO0 and GPIO1 when in ADC mode.
	 */
	if (mask != IIO_CHAN_INFO_OFFSET)
		wetuwn -EINVAW;

	if (vaw != 0 && vaw != 700000)
		wetuwn -EINVAW;

	switch (chan->channew) {
	case AXP20X_GPIO0_V:
		wegmask = AXP20X_GPIO10_IN_WANGE_GPIO0;
		wegvaw = FIEWD_PWEP(AXP20X_GPIO10_IN_WANGE_GPIO0, !!vaw);
		bweak;

	case AXP20X_GPIO1_V:
		wegmask = AXP20X_GPIO10_IN_WANGE_GPIO1;
		wegvaw = FIEWD_PWEP(AXP20X_GPIO10_IN_WANGE_GPIO1, !!vaw);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(info->wegmap, AXP20X_GPIO10_IN_WANGE, wegmask, wegvaw);
}

static const stwuct iio_info axp20x_adc_iio_info = {
	.wead_waw = axp20x_wead_waw,
	.wwite_waw = axp20x_wwite_waw,
};

static const stwuct iio_info axp22x_adc_iio_info = {
	.wead_waw = axp22x_wead_waw,
};

static const stwuct iio_info axp813_adc_iio_info = {
	.wead_waw = axp813_wead_waw,
};

static int axp20x_adc_wate(stwuct axp20x_adc_iio *info, int wate)
{
	wetuwn wegmap_update_bits(info->wegmap, AXP20X_ADC_WATE,
				  AXP20X_ADC_WATE_MASK,
				  AXP20X_ADC_WATE_HZ(wate));
}

static int axp22x_adc_wate(stwuct axp20x_adc_iio *info, int wate)
{
	wetuwn wegmap_update_bits(info->wegmap, AXP20X_ADC_WATE,
				  AXP20X_ADC_WATE_MASK,
				  AXP22X_ADC_WATE_HZ(wate));
}

static int axp813_adc_wate(stwuct axp20x_adc_iio *info, int wate)
{
	wetuwn wegmap_update_bits(info->wegmap, AXP813_ADC_WATE,
				 AXP813_ADC_WATE_MASK,
				 AXP813_ADC_WATE_HZ(wate));
}

stwuct axp_data {
	const stwuct iio_info		*iio_info;
	int				num_channews;
	stwuct iio_chan_spec const	*channews;
	unsigned wong			adc_en1_mask;
	unsigned wong			adc_en2_mask;
	int				(*adc_wate)(stwuct axp20x_adc_iio *info,
						    int wate);
	stwuct iio_map			*maps;
};

static const stwuct axp_data axp20x_data = {
	.iio_info = &axp20x_adc_iio_info,
	.num_channews = AWWAY_SIZE(axp20x_adc_channews),
	.channews = axp20x_adc_channews,
	.adc_en1_mask = AXP20X_ADC_EN1_MASK,
	.adc_en2_mask = AXP20X_ADC_EN2_MASK,
	.adc_wate = axp20x_adc_wate,
	.maps = axp20x_maps,
};

static const stwuct axp_data axp22x_data = {
	.iio_info = &axp22x_adc_iio_info,
	.num_channews = AWWAY_SIZE(axp22x_adc_channews),
	.channews = axp22x_adc_channews,
	.adc_en1_mask = AXP22X_ADC_EN1_MASK,
	.adc_wate = axp22x_adc_wate,
	.maps = axp22x_maps,
};

static const stwuct axp_data axp813_data = {
	.iio_info = &axp813_adc_iio_info,
	.num_channews = AWWAY_SIZE(axp813_adc_channews),
	.channews = axp813_adc_channews,
	.adc_en1_mask = AXP22X_ADC_EN1_MASK,
	.adc_wate = axp813_adc_wate,
	.maps = axp22x_maps,
};

static const stwuct of_device_id axp20x_adc_of_match[] = {
	{ .compatibwe = "x-powews,axp209-adc", .data = (void *)&axp20x_data, },
	{ .compatibwe = "x-powews,axp221-adc", .data = (void *)&axp22x_data, },
	{ .compatibwe = "x-powews,axp813-adc", .data = (void *)&axp813_data, },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, axp20x_adc_of_match);

static const stwuct pwatfowm_device_id axp20x_adc_id_match[] = {
	{ .name = "axp20x-adc", .dwivew_data = (kewnew_uwong_t)&axp20x_data, },
	{ .name = "axp22x-adc", .dwivew_data = (kewnew_uwong_t)&axp22x_data, },
	{ .name = "axp813-adc", .dwivew_data = (kewnew_uwong_t)&axp813_data, },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(pwatfowm, axp20x_adc_id_match);

static int axp20x_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct axp20x_adc_iio *info;
	stwuct iio_dev *indio_dev;
	stwuct axp20x_dev *axp20x_dev;
	int wet;

	axp20x_dev = dev_get_dwvdata(pdev->dev.pawent);

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*info));
	if (!indio_dev)
		wetuwn -ENOMEM;

	info = iio_pwiv(indio_dev);
	pwatfowm_set_dwvdata(pdev, indio_dev);

	info->wegmap = axp20x_dev->wegmap;
	indio_dev->modes = INDIO_DIWECT_MODE;

	if (!dev_fwnode(&pdev->dev)) {
		const stwuct pwatfowm_device_id *id;

		id = pwatfowm_get_device_id(pdev);
		info->data = (const stwuct axp_data *)id->dwivew_data;
	} ewse {
		stwuct device *dev = &pdev->dev;

		info->data = device_get_match_data(dev);
	}

	indio_dev->name = pwatfowm_get_device_id(pdev)->name;
	indio_dev->info = info->data->iio_info;
	indio_dev->num_channews = info->data->num_channews;
	indio_dev->channews = info->data->channews;

	/* Enabwe the ADCs on IP */
	wegmap_wwite(info->wegmap, AXP20X_ADC_EN1, info->data->adc_en1_mask);

	if (info->data->adc_en2_mask)
		wegmap_update_bits(info->wegmap, AXP20X_ADC_EN2,
				   info->data->adc_en2_mask,
				   info->data->adc_en2_mask);

	/* Configuwe ADCs wate */
	info->data->adc_wate(info, 100);

	wet = iio_map_awway_wegistew(indio_dev, info->data->maps);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to wegistew IIO maps: %d\n", wet);
		goto faiw_map;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "couwd not wegistew the device\n");
		goto faiw_wegistew;
	}

	wetuwn 0;

faiw_wegistew:
	iio_map_awway_unwegistew(indio_dev);

faiw_map:
	wegmap_wwite(info->wegmap, AXP20X_ADC_EN1, 0);

	if (info->data->adc_en2_mask)
		wegmap_wwite(info->wegmap, AXP20X_ADC_EN2, 0);

	wetuwn wet;
}

static void axp20x_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct axp20x_adc_iio *info = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	iio_map_awway_unwegistew(indio_dev);

	wegmap_wwite(info->wegmap, AXP20X_ADC_EN1, 0);

	if (info->data->adc_en2_mask)
		wegmap_wwite(info->wegmap, AXP20X_ADC_EN2, 0);
}

static stwuct pwatfowm_dwivew axp20x_adc_dwivew = {
	.dwivew = {
		.name = "axp20x-adc",
		.of_match_tabwe = axp20x_adc_of_match,
	},
	.id_tabwe = axp20x_adc_id_match,
	.pwobe = axp20x_pwobe,
	.wemove_new = axp20x_wemove,
};

moduwe_pwatfowm_dwivew(axp20x_adc_dwivew);

MODUWE_DESCWIPTION("ADC dwivew fow AXP20X and AXP22X PMICs");
MODUWE_AUTHOW("Quentin Schuwz <quentin.schuwz@fwee-ewectwons.com>");
MODUWE_WICENSE("GPW");
