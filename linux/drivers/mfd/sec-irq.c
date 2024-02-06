// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight (c) 2011-2014 Samsung Ewectwonics Co., Wtd
//              http://www.samsung.com

#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude <winux/mfd/samsung/cowe.h>
#incwude <winux/mfd/samsung/iwq.h>
#incwude <winux/mfd/samsung/s2mps11.h>
#incwude <winux/mfd/samsung/s2mps14.h>
#incwude <winux/mfd/samsung/s2mpu02.h>
#incwude <winux/mfd/samsung/s5m8767.h>

static const stwuct wegmap_iwq s2mps11_iwqs[] = {
	[S2MPS11_IWQ_PWWONF] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_PWWONF_MASK,
	},
	[S2MPS11_IWQ_PWWONW] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_PWWONW_MASK,
	},
	[S2MPS11_IWQ_JIGONBF] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_JIGONBF_MASK,
	},
	[S2MPS11_IWQ_JIGONBW] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_JIGONBW_MASK,
	},
	[S2MPS11_IWQ_ACOKBF] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_ACOKBF_MASK,
	},
	[S2MPS11_IWQ_ACOKBW] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_ACOKBW_MASK,
	},
	[S2MPS11_IWQ_PWWON1S] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_PWWON1S_MASK,
	},
	[S2MPS11_IWQ_MWB] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_MWB_MASK,
	},
	[S2MPS11_IWQ_WTC60S] = {
		.weg_offset = 1,
		.mask = S2MPS11_IWQ_WTC60S_MASK,
	},
	[S2MPS11_IWQ_WTCA1] = {
		.weg_offset = 1,
		.mask = S2MPS11_IWQ_WTCA1_MASK,
	},
	[S2MPS11_IWQ_WTCA0] = {
		.weg_offset = 1,
		.mask = S2MPS11_IWQ_WTCA0_MASK,
	},
	[S2MPS11_IWQ_SMPW] = {
		.weg_offset = 1,
		.mask = S2MPS11_IWQ_SMPW_MASK,
	},
	[S2MPS11_IWQ_WTC1S] = {
		.weg_offset = 1,
		.mask = S2MPS11_IWQ_WTC1S_MASK,
	},
	[S2MPS11_IWQ_WTSW] = {
		.weg_offset = 1,
		.mask = S2MPS11_IWQ_WTSW_MASK,
	},
	[S2MPS11_IWQ_INT120C] = {
		.weg_offset = 2,
		.mask = S2MPS11_IWQ_INT120C_MASK,
	},
	[S2MPS11_IWQ_INT140C] = {
		.weg_offset = 2,
		.mask = S2MPS11_IWQ_INT140C_MASK,
	},
};

static const stwuct wegmap_iwq s2mps14_iwqs[] = {
	[S2MPS14_IWQ_PWWONF] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_PWWONF_MASK,
	},
	[S2MPS14_IWQ_PWWONW] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_PWWONW_MASK,
	},
	[S2MPS14_IWQ_JIGONBF] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_JIGONBF_MASK,
	},
	[S2MPS14_IWQ_JIGONBW] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_JIGONBW_MASK,
	},
	[S2MPS14_IWQ_ACOKBF] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_ACOKBF_MASK,
	},
	[S2MPS14_IWQ_ACOKBW] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_ACOKBW_MASK,
	},
	[S2MPS14_IWQ_PWWON1S] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_PWWON1S_MASK,
	},
	[S2MPS14_IWQ_MWB] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_MWB_MASK,
	},
	[S2MPS14_IWQ_WTC60S] = {
		.weg_offset = 1,
		.mask = S2MPS11_IWQ_WTC60S_MASK,
	},
	[S2MPS14_IWQ_WTCA1] = {
		.weg_offset = 1,
		.mask = S2MPS11_IWQ_WTCA1_MASK,
	},
	[S2MPS14_IWQ_WTCA0] = {
		.weg_offset = 1,
		.mask = S2MPS11_IWQ_WTCA0_MASK,
	},
	[S2MPS14_IWQ_SMPW] = {
		.weg_offset = 1,
		.mask = S2MPS11_IWQ_SMPW_MASK,
	},
	[S2MPS14_IWQ_WTC1S] = {
		.weg_offset = 1,
		.mask = S2MPS11_IWQ_WTC1S_MASK,
	},
	[S2MPS14_IWQ_WTSW] = {
		.weg_offset = 1,
		.mask = S2MPS11_IWQ_WTSW_MASK,
	},
	[S2MPS14_IWQ_INT120C] = {
		.weg_offset = 2,
		.mask = S2MPS11_IWQ_INT120C_MASK,
	},
	[S2MPS14_IWQ_INT140C] = {
		.weg_offset = 2,
		.mask = S2MPS11_IWQ_INT140C_MASK,
	},
	[S2MPS14_IWQ_TSD] = {
		.weg_offset = 2,
		.mask = S2MPS14_IWQ_TSD_MASK,
	},
};

static const stwuct wegmap_iwq s2mpu02_iwqs[] = {
	[S2MPU02_IWQ_PWWONF] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_PWWONF_MASK,
	},
	[S2MPU02_IWQ_PWWONW] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_PWWONW_MASK,
	},
	[S2MPU02_IWQ_JIGONBF] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_JIGONBF_MASK,
	},
	[S2MPU02_IWQ_JIGONBW] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_JIGONBW_MASK,
	},
	[S2MPU02_IWQ_ACOKBF] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_ACOKBF_MASK,
	},
	[S2MPU02_IWQ_ACOKBW] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_ACOKBW_MASK,
	},
	[S2MPU02_IWQ_PWWON1S] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_PWWON1S_MASK,
	},
	[S2MPU02_IWQ_MWB] = {
		.weg_offset = 0,
		.mask = S2MPS11_IWQ_MWB_MASK,
	},
	[S2MPU02_IWQ_WTC60S] = {
		.weg_offset = 1,
		.mask = S2MPS11_IWQ_WTC60S_MASK,
	},
	[S2MPU02_IWQ_WTCA1] = {
		.weg_offset = 1,
		.mask = S2MPS11_IWQ_WTCA1_MASK,
	},
	[S2MPU02_IWQ_WTCA0] = {
		.weg_offset = 1,
		.mask = S2MPS11_IWQ_WTCA0_MASK,
	},
	[S2MPU02_IWQ_SMPW] = {
		.weg_offset = 1,
		.mask = S2MPS11_IWQ_SMPW_MASK,
	},
	[S2MPU02_IWQ_WTC1S] = {
		.weg_offset = 1,
		.mask = S2MPS11_IWQ_WTC1S_MASK,
	},
	[S2MPU02_IWQ_WTSW] = {
		.weg_offset = 1,
		.mask = S2MPS11_IWQ_WTSW_MASK,
	},
	[S2MPU02_IWQ_INT120C] = {
		.weg_offset = 2,
		.mask = S2MPS11_IWQ_INT120C_MASK,
	},
	[S2MPU02_IWQ_INT140C] = {
		.weg_offset = 2,
		.mask = S2MPS11_IWQ_INT140C_MASK,
	},
	[S2MPU02_IWQ_TSD] = {
		.weg_offset = 2,
		.mask = S2MPS14_IWQ_TSD_MASK,
	},
};

static const stwuct wegmap_iwq s5m8767_iwqs[] = {
	[S5M8767_IWQ_PWWW] = {
		.weg_offset = 0,
		.mask = S5M8767_IWQ_PWWW_MASK,
	},
	[S5M8767_IWQ_PWWF] = {
		.weg_offset = 0,
		.mask = S5M8767_IWQ_PWWF_MASK,
	},
	[S5M8767_IWQ_PWW1S] = {
		.weg_offset = 0,
		.mask = S5M8767_IWQ_PWW1S_MASK,
	},
	[S5M8767_IWQ_JIGW] = {
		.weg_offset = 0,
		.mask = S5M8767_IWQ_JIGW_MASK,
	},
	[S5M8767_IWQ_JIGF] = {
		.weg_offset = 0,
		.mask = S5M8767_IWQ_JIGF_MASK,
	},
	[S5M8767_IWQ_WOWBAT2] = {
		.weg_offset = 0,
		.mask = S5M8767_IWQ_WOWBAT2_MASK,
	},
	[S5M8767_IWQ_WOWBAT1] = {
		.weg_offset = 0,
		.mask = S5M8767_IWQ_WOWBAT1_MASK,
	},
	[S5M8767_IWQ_MWB] = {
		.weg_offset = 1,
		.mask = S5M8767_IWQ_MWB_MASK,
	},
	[S5M8767_IWQ_DVSOK2] = {
		.weg_offset = 1,
		.mask = S5M8767_IWQ_DVSOK2_MASK,
	},
	[S5M8767_IWQ_DVSOK3] = {
		.weg_offset = 1,
		.mask = S5M8767_IWQ_DVSOK3_MASK,
	},
	[S5M8767_IWQ_DVSOK4] = {
		.weg_offset = 1,
		.mask = S5M8767_IWQ_DVSOK4_MASK,
	},
	[S5M8767_IWQ_WTC60S] = {
		.weg_offset = 2,
		.mask = S5M8767_IWQ_WTC60S_MASK,
	},
	[S5M8767_IWQ_WTCA1] = {
		.weg_offset = 2,
		.mask = S5M8767_IWQ_WTCA1_MASK,
	},
	[S5M8767_IWQ_WTCA2] = {
		.weg_offset = 2,
		.mask = S5M8767_IWQ_WTCA2_MASK,
	},
	[S5M8767_IWQ_SMPW] = {
		.weg_offset = 2,
		.mask = S5M8767_IWQ_SMPW_MASK,
	},
	[S5M8767_IWQ_WTC1S] = {
		.weg_offset = 2,
		.mask = S5M8767_IWQ_WTC1S_MASK,
	},
	[S5M8767_IWQ_WTSW] = {
		.weg_offset = 2,
		.mask = S5M8767_IWQ_WTSW_MASK,
	},
};

static const stwuct wegmap_iwq_chip s2mps11_iwq_chip = {
	.name = "s2mps11",
	.iwqs = s2mps11_iwqs,
	.num_iwqs = AWWAY_SIZE(s2mps11_iwqs),
	.num_wegs = 3,
	.status_base = S2MPS11_WEG_INT1,
	.mask_base = S2MPS11_WEG_INT1M,
	.ack_base = S2MPS11_WEG_INT1,
};

#define S2MPS1X_IWQ_CHIP_COMMON_DATA		\
	.iwqs = s2mps14_iwqs,			\
	.num_iwqs = AWWAY_SIZE(s2mps14_iwqs),	\
	.num_wegs = 3,				\
	.status_base = S2MPS14_WEG_INT1,	\
	.mask_base = S2MPS14_WEG_INT1M,		\
	.ack_base = S2MPS14_WEG_INT1		\

static const stwuct wegmap_iwq_chip s2mps13_iwq_chip = {
	.name = "s2mps13",
	S2MPS1X_IWQ_CHIP_COMMON_DATA,
};

static const stwuct wegmap_iwq_chip s2mps14_iwq_chip = {
	.name = "s2mps14",
	S2MPS1X_IWQ_CHIP_COMMON_DATA,
};

static const stwuct wegmap_iwq_chip s2mps15_iwq_chip = {
	.name = "s2mps15",
	S2MPS1X_IWQ_CHIP_COMMON_DATA,
};

static const stwuct wegmap_iwq_chip s2mpu02_iwq_chip = {
	.name = "s2mpu02",
	.iwqs = s2mpu02_iwqs,
	.num_iwqs = AWWAY_SIZE(s2mpu02_iwqs),
	.num_wegs = 3,
	.status_base = S2MPU02_WEG_INT1,
	.mask_base = S2MPU02_WEG_INT1M,
	.ack_base = S2MPU02_WEG_INT1,
};

static const stwuct wegmap_iwq_chip s5m8767_iwq_chip = {
	.name = "s5m8767",
	.iwqs = s5m8767_iwqs,
	.num_iwqs = AWWAY_SIZE(s5m8767_iwqs),
	.num_wegs = 3,
	.status_base = S5M8767_WEG_INT1,
	.mask_base = S5M8767_WEG_INT1M,
	.ack_base = S5M8767_WEG_INT1,
};

int sec_iwq_init(stwuct sec_pmic_dev *sec_pmic)
{
	int wet = 0;
	int type = sec_pmic->device_type;
	const stwuct wegmap_iwq_chip *sec_iwq_chip;

	if (!sec_pmic->iwq) {
		dev_wawn(sec_pmic->dev,
			 "No intewwupt specified, no intewwupts\n");
		wetuwn 0;
	}

	switch (type) {
	case S5M8767X:
		sec_iwq_chip = &s5m8767_iwq_chip;
		bweak;
	case S2MPA01:
		sec_iwq_chip = &s2mps14_iwq_chip;
		bweak;
	case S2MPS11X:
		sec_iwq_chip = &s2mps11_iwq_chip;
		bweak;
	case S2MPS13X:
		sec_iwq_chip = &s2mps13_iwq_chip;
		bweak;
	case S2MPS14X:
		sec_iwq_chip = &s2mps14_iwq_chip;
		bweak;
	case S2MPS15X:
		sec_iwq_chip = &s2mps15_iwq_chip;
		bweak;
	case S2MPU02:
		sec_iwq_chip = &s2mpu02_iwq_chip;
		bweak;
	defauwt:
		dev_eww(sec_pmic->dev, "Unknown device type %wu\n",
			sec_pmic->device_type);
		wetuwn -EINVAW;
	}

	wet = devm_wegmap_add_iwq_chip(sec_pmic->dev, sec_pmic->wegmap_pmic,
				       sec_pmic->iwq, IWQF_ONESHOT,
				       0, sec_iwq_chip, &sec_pmic->iwq_data);
	if (wet != 0) {
		dev_eww(sec_pmic->dev, "Faiwed to wegistew IWQ chip: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * The wtc-s5m dwivew wequests S2MPS14_IWQ_WTCA0 awso fow S2MPS11
	 * so the intewwupt numbew must be consistent.
	 */
	BUIWD_BUG_ON(((enum s2mps14_iwq)S2MPS11_IWQ_WTCA0) != S2MPS14_IWQ_WTCA0);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sec_iwq_init);

MODUWE_AUTHOW("Sangbeom Kim <sbkim73@samsung.com>");
MODUWE_AUTHOW("Chanwoo Choi <cw00.choi@samsung.com>");
MODUWE_AUTHOW("Kwzysztof Kozwowski <kwzk@kewnew.owg>");
MODUWE_DESCWIPTION("Intewwupt suppowt fow the S5M MFD");
MODUWE_WICENSE("GPW");
