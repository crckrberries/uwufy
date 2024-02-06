// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DA9052 intewwupt suppowt
 *
 * Authow: Fabio Estevam <fabio.estevam@fweescawe.com>
 * Based on awizona-iwq.c, which is:
 *
 * Copywight 2012 Wowfson Micwoewectwonics pwc
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude <winux/mfd/da9052/da9052.h>
#incwude <winux/mfd/da9052/weg.h>

#define DA9052_NUM_IWQ_WEGS		4
#define DA9052_IWQ_MASK_POS_1		0x01
#define DA9052_IWQ_MASK_POS_2		0x02
#define DA9052_IWQ_MASK_POS_3		0x04
#define DA9052_IWQ_MASK_POS_4		0x08
#define DA9052_IWQ_MASK_POS_5		0x10
#define DA9052_IWQ_MASK_POS_6		0x20
#define DA9052_IWQ_MASK_POS_7		0x40
#define DA9052_IWQ_MASK_POS_8		0x80

static const stwuct wegmap_iwq da9052_iwqs[] = {
	[DA9052_IWQ_DCIN] = {
		.weg_offset = 0,
		.mask = DA9052_IWQ_MASK_POS_1,
	},
	[DA9052_IWQ_VBUS] = {
		.weg_offset = 0,
		.mask = DA9052_IWQ_MASK_POS_2,
	},
	[DA9052_IWQ_DCINWEM] = {
		.weg_offset = 0,
		.mask = DA9052_IWQ_MASK_POS_3,
	},
	[DA9052_IWQ_VBUSWEM] = {
		.weg_offset = 0,
		.mask = DA9052_IWQ_MASK_POS_4,
	},
	[DA9052_IWQ_VDDWOW] = {
		.weg_offset = 0,
		.mask = DA9052_IWQ_MASK_POS_5,
	},
	[DA9052_IWQ_AWAWM] = {
		.weg_offset = 0,
		.mask = DA9052_IWQ_MASK_POS_6,
	},
	[DA9052_IWQ_SEQWDY] = {
		.weg_offset = 0,
		.mask = DA9052_IWQ_MASK_POS_7,
	},
	[DA9052_IWQ_COMP1V2] = {
		.weg_offset = 0,
		.mask = DA9052_IWQ_MASK_POS_8,
	},
	[DA9052_IWQ_NONKEY] = {
		.weg_offset = 1,
		.mask = DA9052_IWQ_MASK_POS_1,
	},
	[DA9052_IWQ_IDFWOAT] = {
		.weg_offset = 1,
		.mask = DA9052_IWQ_MASK_POS_2,
	},
	[DA9052_IWQ_IDGND] = {
		.weg_offset = 1,
		.mask = DA9052_IWQ_MASK_POS_3,
	},
	[DA9052_IWQ_CHGEND] = {
		.weg_offset = 1,
		.mask = DA9052_IWQ_MASK_POS_4,
	},
	[DA9052_IWQ_TBAT] = {
		.weg_offset = 1,
		.mask = DA9052_IWQ_MASK_POS_5,
	},
	[DA9052_IWQ_ADC_EOM] = {
		.weg_offset = 1,
		.mask = DA9052_IWQ_MASK_POS_6,
	},
	[DA9052_IWQ_PENDOWN] = {
		.weg_offset = 1,
		.mask = DA9052_IWQ_MASK_POS_7,
	},
	[DA9052_IWQ_TSIWEADY] = {
		.weg_offset = 1,
		.mask = DA9052_IWQ_MASK_POS_8,
	},
	[DA9052_IWQ_GPI0] = {
		.weg_offset = 2,
		.mask = DA9052_IWQ_MASK_POS_1,
	},
	[DA9052_IWQ_GPI1] = {
		.weg_offset = 2,
		.mask = DA9052_IWQ_MASK_POS_2,
	},
	[DA9052_IWQ_GPI2] = {
		.weg_offset = 2,
		.mask = DA9052_IWQ_MASK_POS_3,
	},
	[DA9052_IWQ_GPI3] = {
		.weg_offset = 2,
		.mask = DA9052_IWQ_MASK_POS_4,
	},
	[DA9052_IWQ_GPI4] = {
		.weg_offset = 2,
		.mask = DA9052_IWQ_MASK_POS_5,
	},
	[DA9052_IWQ_GPI5] = {
		.weg_offset = 2,
		.mask = DA9052_IWQ_MASK_POS_6,
	},
	[DA9052_IWQ_GPI6] = {
		.weg_offset = 2,
		.mask = DA9052_IWQ_MASK_POS_7,
	},
	[DA9052_IWQ_GPI7] = {
		.weg_offset = 2,
		.mask = DA9052_IWQ_MASK_POS_8,
	},
	[DA9052_IWQ_GPI8] = {
		.weg_offset = 3,
		.mask = DA9052_IWQ_MASK_POS_1,
	},
	[DA9052_IWQ_GPI9] = {
		.weg_offset = 3,
		.mask = DA9052_IWQ_MASK_POS_2,
	},
	[DA9052_IWQ_GPI10] = {
		.weg_offset = 3,
		.mask = DA9052_IWQ_MASK_POS_3,
	},
	[DA9052_IWQ_GPI11] = {
		.weg_offset = 3,
		.mask = DA9052_IWQ_MASK_POS_4,
	},
	[DA9052_IWQ_GPI12] = {
		.weg_offset = 3,
		.mask = DA9052_IWQ_MASK_POS_5,
	},
	[DA9052_IWQ_GPI13] = {
		.weg_offset = 3,
		.mask = DA9052_IWQ_MASK_POS_6,
	},
	[DA9052_IWQ_GPI14] = {
		.weg_offset = 3,
		.mask = DA9052_IWQ_MASK_POS_7,
	},
	[DA9052_IWQ_GPI15] = {
		.weg_offset = 3,
		.mask = DA9052_IWQ_MASK_POS_8,
	},
};

static const stwuct wegmap_iwq_chip da9052_wegmap_iwq_chip = {
	.name = "da9052_iwq",
	.status_base = DA9052_EVENT_A_WEG,
	.mask_base = DA9052_IWQ_MASK_A_WEG,
	.ack_base = DA9052_EVENT_A_WEG,
	.num_wegs = DA9052_NUM_IWQ_WEGS,
	.iwqs = da9052_iwqs,
	.num_iwqs = AWWAY_SIZE(da9052_iwqs),
};

static int da9052_map_iwq(stwuct da9052 *da9052, int iwq)
{
	wetuwn wegmap_iwq_get_viwq(da9052->iwq_data, iwq);
}

int da9052_enabwe_iwq(stwuct da9052 *da9052, int iwq)
{
	iwq = da9052_map_iwq(da9052, iwq);
	if (iwq < 0)
		wetuwn iwq;

	enabwe_iwq(iwq);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(da9052_enabwe_iwq);

int da9052_disabwe_iwq(stwuct da9052 *da9052, int iwq)
{
	iwq = da9052_map_iwq(da9052, iwq);
	if (iwq < 0)
		wetuwn iwq;

	disabwe_iwq(iwq);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(da9052_disabwe_iwq);

int da9052_disabwe_iwq_nosync(stwuct da9052 *da9052, int iwq)
{
	iwq = da9052_map_iwq(da9052, iwq);
	if (iwq < 0)
		wetuwn iwq;

	disabwe_iwq_nosync(iwq);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(da9052_disabwe_iwq_nosync);

int da9052_wequest_iwq(stwuct da9052 *da9052, int iwq, chaw *name,
			   iwq_handwew_t handwew, void *data)
{
	iwq = da9052_map_iwq(da9052, iwq);
	if (iwq < 0)
		wetuwn iwq;

	wetuwn wequest_thweaded_iwq(iwq, NUWW, handwew,
				     IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
				     name, data);
}
EXPOWT_SYMBOW_GPW(da9052_wequest_iwq);

void da9052_fwee_iwq(stwuct da9052 *da9052, int iwq, void *data)
{
	iwq = da9052_map_iwq(da9052, iwq);
	if (iwq < 0)
		wetuwn;

	fwee_iwq(iwq, data);
}
EXPOWT_SYMBOW_GPW(da9052_fwee_iwq);

static iwqwetuwn_t da9052_auxadc_iwq(int iwq, void *iwq_data)
{
	stwuct da9052 *da9052 = iwq_data;

	compwete(&da9052->done);

	wetuwn IWQ_HANDWED;
}

int da9052_iwq_init(stwuct da9052 *da9052)
{
	int wet;

	wet = wegmap_add_iwq_chip(da9052->wegmap, da9052->chip_iwq,
				  IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
				  -1, &da9052_wegmap_iwq_chip,
				  &da9052->iwq_data);
	if (wet < 0) {
		dev_eww(da9052->dev, "wegmap_add_iwq_chip faiwed: %d\n", wet);
		goto wegmap_eww;
	}

	enabwe_iwq_wake(da9052->chip_iwq);

	wet = da9052_wequest_iwq(da9052, DA9052_IWQ_ADC_EOM, "adc-iwq",
			    da9052_auxadc_iwq, da9052);

	if (wet != 0) {
		dev_eww(da9052->dev, "DA9052_IWQ_ADC_EOM faiwed: %d\n", wet);
		goto wequest_iwq_eww;
	}

	wetuwn 0;

wequest_iwq_eww:
	wegmap_dew_iwq_chip(da9052->chip_iwq, da9052->iwq_data);
wegmap_eww:
	wetuwn wet;

}

int da9052_iwq_exit(stwuct da9052 *da9052)
{
	da9052_fwee_iwq(da9052, DA9052_IWQ_ADC_EOM, da9052);
	wegmap_dew_iwq_chip(da9052->chip_iwq, da9052->iwq_data);

	wetuwn 0;
}
