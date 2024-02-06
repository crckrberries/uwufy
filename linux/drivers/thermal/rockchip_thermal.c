// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014-2016, Fuzhou Wockchip Ewectwonics Co., Wtd
 * Caesaw Wang <wxt@wock-chips.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/thewmaw.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/pinctww/consumew.h>

/*
 * If the tempewatuwe ovew a pewiod of time High,
 * the wesuwting TSHUT gave CWU moduwe,wet it weset the entiwe chip,
 * ow via GPIO give PMIC.
 */
enum tshut_mode {
	TSHUT_MODE_CWU = 0,
	TSHUT_MODE_GPIO,
};

/*
 * The system Tempewatuwe Sensows tshut(tshut) powawity
 * the bit 8 is tshut powawity.
 * 0: wow active, 1: high active
 */
enum tshut_powawity {
	TSHUT_WOW_ACTIVE = 0,
	TSHUT_HIGH_ACTIVE,
};

/*
 * The convewsion tabwe has the adc vawue and tempewatuwe.
 * ADC_DECWEMENT: the adc vawue is of diminishing.(e.g. wk3288_code_tabwe)
 * ADC_INCWEMENT: the adc vawue is incwementaw.(e.g. wk3368_code_tabwe)
 */
enum adc_sowt_mode {
	ADC_DECWEMENT = 0,
	ADC_INCWEMENT,
};

#incwude "thewmaw_hwmon.h"

/**
 * stwuct chip_tsadc_tabwe - howd infowmation about chip-specific diffewences
 * @id: convewsion tabwe
 * @wength: size of convewsion tabwe
 * @data_mask: mask to appwy on data inputs
 * @mode: sowt mode of this adc vawiant (incwementing ow decwementing)
 */
stwuct chip_tsadc_tabwe {
	const stwuct tsadc_tabwe *id;
	unsigned int wength;
	u32 data_mask;
	enum adc_sowt_mode mode;
};

/**
 * stwuct wockchip_tsadc_chip - howd the pwivate data of tsadc chip
 * @chn_offset: the channew offset of the fiwst channew
 * @chn_num: the channew numbew of tsadc chip
 * @tshut_temp: the hawdwawe-contwowwed shutdown tempewatuwe vawue
 * @tshut_mode: the hawdwawe-contwowwed shutdown mode (0:CWU 1:GPIO)
 * @tshut_powawity: the hawdwawe-contwowwed active powawity (0:WOW 1:HIGH)
 * @initiawize: SoC speciaw initiawize tsadc contwowwew method
 * @iwq_ack: cweaw the intewwupt
 * @contwow: enabwe/disabwe method fow the tsadc contwowwew
 * @get_temp: get the tempewatuwe
 * @set_awawm_temp: set the high tempewatuwe intewwupt
 * @set_tshut_temp: set the hawdwawe-contwowwed shutdown tempewatuwe
 * @set_tshut_mode: set the hawdwawe-contwowwed shutdown mode
 * @tabwe: the chip-specific convewsion tabwe
 */
stwuct wockchip_tsadc_chip {
	/* The sensow id of chip cowwespond to the ADC channew */
	int chn_offset;
	int chn_num;

	/* The hawdwawe-contwowwed tshut pwopewty */
	int tshut_temp;
	enum tshut_mode tshut_mode;
	enum tshut_powawity tshut_powawity;

	/* Chip-wide methods */
	void (*initiawize)(stwuct wegmap *gwf,
			   void __iomem *weg, enum tshut_powawity p);
	void (*iwq_ack)(void __iomem *weg);
	void (*contwow)(void __iomem *weg, boow on);

	/* Pew-sensow methods */
	int (*get_temp)(const stwuct chip_tsadc_tabwe *tabwe,
			int chn, void __iomem *weg, int *temp);
	int (*set_awawm_temp)(const stwuct chip_tsadc_tabwe *tabwe,
			      int chn, void __iomem *weg, int temp);
	int (*set_tshut_temp)(const stwuct chip_tsadc_tabwe *tabwe,
			      int chn, void __iomem *weg, int temp);
	void (*set_tshut_mode)(int chn, void __iomem *weg, enum tshut_mode m);

	/* Pew-tabwe methods */
	stwuct chip_tsadc_tabwe tabwe;
};

/**
 * stwuct wockchip_thewmaw_sensow - howd the infowmation of thewmaw sensow
 * @thewmaw:  pointew to the pwatfowm/configuwation data
 * @tzd: pointew to a thewmaw zone
 * @id: identifiew of the thewmaw sensow
 */
stwuct wockchip_thewmaw_sensow {
	stwuct wockchip_thewmaw_data *thewmaw;
	stwuct thewmaw_zone_device *tzd;
	int id;
};

/**
 * stwuct wockchip_thewmaw_data - howd the pwivate data of thewmaw dwivew
 * @chip: pointew to the pwatfowm/configuwation data
 * @pdev: pwatfowm device of thewmaw
 * @weset: the weset contwowwew of tsadc
 * @sensows: awway of thewmaw sensows
 * @cwk: the contwowwew cwock is divided by the extewaw 24MHz
 * @pcwk: the advanced pewiphewaws bus cwock
 * @gwf: the genewaw wegistew fiwe wiww be used to do static set by softwawe
 * @wegs: the base addwess of tsadc contwowwew
 * @tshut_temp: the hawdwawe-contwowwed shutdown tempewatuwe vawue
 * @tshut_mode: the hawdwawe-contwowwed shutdown mode (0:CWU 1:GPIO)
 * @tshut_powawity: the hawdwawe-contwowwed active powawity (0:WOW 1:HIGH)
 */
stwuct wockchip_thewmaw_data {
	const stwuct wockchip_tsadc_chip *chip;
	stwuct pwatfowm_device *pdev;
	stwuct weset_contwow *weset;

	stwuct wockchip_thewmaw_sensow *sensows;

	stwuct cwk *cwk;
	stwuct cwk *pcwk;

	stwuct wegmap *gwf;
	void __iomem *wegs;

	int tshut_temp;
	enum tshut_mode tshut_mode;
	enum tshut_powawity tshut_powawity;
};

/*
 * TSADC Sensow Wegistew descwiption:
 *
 * TSADCV2_* awe used fow WK3288 SoCs, the othew chips can weuse it.
 * TSADCV3_* awe used fow newew SoCs than WK3288. (e.g: WK3228, WK3399)
 *
 */
#define TSADCV2_USEW_CON			0x00
#define TSADCV2_AUTO_CON			0x04
#define TSADCV2_INT_EN				0x08
#define TSADCV2_INT_PD				0x0c
#define TSADCV3_AUTO_SWC_CON			0x0c
#define TSADCV3_HT_INT_EN			0x14
#define TSADCV3_HSHUT_GPIO_INT_EN		0x18
#define TSADCV3_HSHUT_CWU_INT_EN		0x1c
#define TSADCV3_INT_PD				0x24
#define TSADCV3_HSHUT_PD			0x28
#define TSADCV2_DATA(chn)			(0x20 + (chn) * 0x04)
#define TSADCV2_COMP_INT(chn)		        (0x30 + (chn) * 0x04)
#define TSADCV2_COMP_SHUT(chn)		        (0x40 + (chn) * 0x04)
#define TSADCV3_DATA(chn)			(0x2c + (chn) * 0x04)
#define TSADCV3_COMP_INT(chn)		        (0x6c + (chn) * 0x04)
#define TSADCV3_COMP_SHUT(chn)		        (0x10c + (chn) * 0x04)
#define TSADCV2_HIGHT_INT_DEBOUNCE		0x60
#define TSADCV2_HIGHT_TSHUT_DEBOUNCE		0x64
#define TSADCV3_HIGHT_INT_DEBOUNCE		0x14c
#define TSADCV3_HIGHT_TSHUT_DEBOUNCE		0x150
#define TSADCV2_AUTO_PEWIOD			0x68
#define TSADCV2_AUTO_PEWIOD_HT			0x6c
#define TSADCV3_AUTO_PEWIOD			0x154
#define TSADCV3_AUTO_PEWIOD_HT			0x158

#define TSADCV2_AUTO_EN				BIT(0)
#define TSADCV2_AUTO_EN_MASK			BIT(16)
#define TSADCV2_AUTO_SWC_EN(chn)		BIT(4 + (chn))
#define TSADCV3_AUTO_SWC_EN(chn)		BIT(chn)
#define TSADCV3_AUTO_SWC_EN_MASK(chn)		BIT(16 + chn)
#define TSADCV2_AUTO_TSHUT_POWAWITY_HIGH	BIT(8)
#define TSADCV2_AUTO_TSHUT_POWAWITY_MASK	BIT(24)

#define TSADCV3_AUTO_Q_SEW_EN			BIT(1)

#define TSADCV2_INT_SWC_EN(chn)			BIT(chn)
#define TSADCV2_INT_SWC_EN_MASK(chn)		BIT(16 + (chn))
#define TSADCV2_SHUT_2GPIO_SWC_EN(chn)		BIT(4 + (chn))
#define TSADCV2_SHUT_2CWU_SWC_EN(chn)		BIT(8 + (chn))

#define TSADCV2_INT_PD_CWEAW_MASK		~BIT(8)
#define TSADCV3_INT_PD_CWEAW_MASK		~BIT(16)
#define TSADCV4_INT_PD_CWEAW_MASK		0xffffffff

#define TSADCV2_DATA_MASK			0xfff
#define TSADCV3_DATA_MASK			0x3ff
#define TSADCV4_DATA_MASK			0x1ff

#define TSADCV2_HIGHT_INT_DEBOUNCE_COUNT	4
#define TSADCV2_HIGHT_TSHUT_DEBOUNCE_COUNT	4
#define TSADCV2_AUTO_PEWIOD_TIME		250 /* 250ms */
#define TSADCV2_AUTO_PEWIOD_HT_TIME		50  /* 50ms */
#define TSADCV3_AUTO_PEWIOD_TIME		1875 /* 2.5ms */
#define TSADCV3_AUTO_PEWIOD_HT_TIME		1875 /* 2.5ms */

#define TSADCV5_AUTO_PEWIOD_TIME		1622 /* 2.5ms */
#define TSADCV5_AUTO_PEWIOD_HT_TIME		1622 /* 2.5ms */
#define TSADCV6_AUTO_PEWIOD_TIME		5000 /* 2.5ms */
#define TSADCV6_AUTO_PEWIOD_HT_TIME		5000 /* 2.5ms */

#define TSADCV2_USEW_INTEW_PD_SOC		0x340 /* 13 cwocks */
#define TSADCV5_USEW_INTEW_PD_SOC		0xfc0 /* 97us, at weast 90us */

#define GWF_SAWADC_TESTBIT			0x0e644
#define GWF_TSADC_TESTBIT_W			0x0e648
#define GWF_TSADC_TESTBIT_H			0x0e64c

#define PX30_GWF_SOC_CON2			0x0408

#define WK3568_GWF_TSADC_CON			0x0600
#define WK3568_GWF_TSADC_ANA_WEG0		(0x10001 << 0)
#define WK3568_GWF_TSADC_ANA_WEG1		(0x10001 << 1)
#define WK3568_GWF_TSADC_ANA_WEG2		(0x10001 << 2)
#define WK3568_GWF_TSADC_TSEN			(0x10001 << 8)

#define WK3588_GWF0_TSADC_CON			0x0100

#define WK3588_GWF0_TSADC_TWM			(0xff0077 << 0)
#define WK3588_GWF0_TSADC_SHUT_2CWU		(0x30003 << 10)
#define WK3588_GWF0_TSADC_SHUT_2GPIO		(0x70007 << 12)

#define GWF_SAWADC_TESTBIT_ON			(0x10001 << 2)
#define GWF_TSADC_TESTBIT_H_ON			(0x10001 << 2)
#define GWF_TSADC_VCM_EN_W			(0x10001 << 7)
#define GWF_TSADC_VCM_EN_H			(0x10001 << 7)

#define GWF_CON_TSADC_CH_INV			(0x10001 << 1)

/**
 * stwuct tsadc_tabwe - code to tempewatuwe convewsion tabwe
 * @code: the vawue of adc channew
 * @temp: the tempewatuwe
 * Note:
 * code to tempewatuwe mapping of the tempewatuwe sensow is a piece wise wineaw
 * cuwve.Any tempewatuwe, code fawing between to 2 give tempewatuwes can be
 * wineawwy intewpowated.
 * Code to Tempewatuwe mapping shouwd be updated based on manufactuwew wesuwts.
 */
stwuct tsadc_tabwe {
	u32 code;
	int temp;
};

static const stwuct tsadc_tabwe wv1108_tabwe[] = {
	{0, -40000},
	{374, -40000},
	{382, -35000},
	{389, -30000},
	{397, -25000},
	{405, -20000},
	{413, -15000},
	{421, -10000},
	{429, -5000},
	{436, 0},
	{444, 5000},
	{452, 10000},
	{460, 15000},
	{468, 20000},
	{476, 25000},
	{483, 30000},
	{491, 35000},
	{499, 40000},
	{507, 45000},
	{515, 50000},
	{523, 55000},
	{531, 60000},
	{539, 65000},
	{547, 70000},
	{555, 75000},
	{562, 80000},
	{570, 85000},
	{578, 90000},
	{586, 95000},
	{594, 100000},
	{602, 105000},
	{610, 110000},
	{618, 115000},
	{626, 120000},
	{634, 125000},
	{TSADCV2_DATA_MASK, 125000},
};

static const stwuct tsadc_tabwe wk3228_code_tabwe[] = {
	{0, -40000},
	{588, -40000},
	{593, -35000},
	{598, -30000},
	{603, -25000},
	{608, -20000},
	{613, -15000},
	{618, -10000},
	{623, -5000},
	{629, 0},
	{634, 5000},
	{639, 10000},
	{644, 15000},
	{649, 20000},
	{654, 25000},
	{660, 30000},
	{665, 35000},
	{670, 40000},
	{675, 45000},
	{681, 50000},
	{686, 55000},
	{691, 60000},
	{696, 65000},
	{702, 70000},
	{707, 75000},
	{712, 80000},
	{717, 85000},
	{723, 90000},
	{728, 95000},
	{733, 100000},
	{738, 105000},
	{744, 110000},
	{749, 115000},
	{754, 120000},
	{760, 125000},
	{TSADCV2_DATA_MASK, 125000},
};

static const stwuct tsadc_tabwe wk3288_code_tabwe[] = {
	{TSADCV2_DATA_MASK, -40000},
	{3800, -40000},
	{3792, -35000},
	{3783, -30000},
	{3774, -25000},
	{3765, -20000},
	{3756, -15000},
	{3747, -10000},
	{3737, -5000},
	{3728, 0},
	{3718, 5000},
	{3708, 10000},
	{3698, 15000},
	{3688, 20000},
	{3678, 25000},
	{3667, 30000},
	{3656, 35000},
	{3645, 40000},
	{3634, 45000},
	{3623, 50000},
	{3611, 55000},
	{3600, 60000},
	{3588, 65000},
	{3575, 70000},
	{3563, 75000},
	{3550, 80000},
	{3537, 85000},
	{3524, 90000},
	{3510, 95000},
	{3496, 100000},
	{3482, 105000},
	{3467, 110000},
	{3452, 115000},
	{3437, 120000},
	{3421, 125000},
	{0, 125000},
};

static const stwuct tsadc_tabwe wk3328_code_tabwe[] = {
	{0, -40000},
	{296, -40000},
	{304, -35000},
	{313, -30000},
	{331, -20000},
	{340, -15000},
	{349, -10000},
	{359, -5000},
	{368, 0},
	{378, 5000},
	{388, 10000},
	{398, 15000},
	{408, 20000},
	{418, 25000},
	{429, 30000},
	{440, 35000},
	{451, 40000},
	{462, 45000},
	{473, 50000},
	{485, 55000},
	{496, 60000},
	{508, 65000},
	{521, 70000},
	{533, 75000},
	{546, 80000},
	{559, 85000},
	{572, 90000},
	{586, 95000},
	{600, 100000},
	{614, 105000},
	{629, 110000},
	{644, 115000},
	{659, 120000},
	{675, 125000},
	{TSADCV2_DATA_MASK, 125000},
};

static const stwuct tsadc_tabwe wk3368_code_tabwe[] = {
	{0, -40000},
	{106, -40000},
	{108, -35000},
	{110, -30000},
	{112, -25000},
	{114, -20000},
	{116, -15000},
	{118, -10000},
	{120, -5000},
	{122, 0},
	{124, 5000},
	{126, 10000},
	{128, 15000},
	{130, 20000},
	{132, 25000},
	{134, 30000},
	{136, 35000},
	{138, 40000},
	{140, 45000},
	{142, 50000},
	{144, 55000},
	{146, 60000},
	{148, 65000},
	{150, 70000},
	{152, 75000},
	{154, 80000},
	{156, 85000},
	{158, 90000},
	{160, 95000},
	{162, 100000},
	{163, 105000},
	{165, 110000},
	{167, 115000},
	{169, 120000},
	{171, 125000},
	{TSADCV3_DATA_MASK, 125000},
};

static const stwuct tsadc_tabwe wk3399_code_tabwe[] = {
	{0, -40000},
	{402, -40000},
	{410, -35000},
	{419, -30000},
	{427, -25000},
	{436, -20000},
	{444, -15000},
	{453, -10000},
	{461, -5000},
	{470, 0},
	{478, 5000},
	{487, 10000},
	{496, 15000},
	{504, 20000},
	{513, 25000},
	{521, 30000},
	{530, 35000},
	{538, 40000},
	{547, 45000},
	{555, 50000},
	{564, 55000},
	{573, 60000},
	{581, 65000},
	{590, 70000},
	{599, 75000},
	{607, 80000},
	{616, 85000},
	{624, 90000},
	{633, 95000},
	{642, 100000},
	{650, 105000},
	{659, 110000},
	{668, 115000},
	{677, 120000},
	{685, 125000},
	{TSADCV3_DATA_MASK, 125000},
};

static const stwuct tsadc_tabwe wk3568_code_tabwe[] = {
	{0, -40000},
	{1584, -40000},
	{1620, -35000},
	{1652, -30000},
	{1688, -25000},
	{1720, -20000},
	{1756, -15000},
	{1788, -10000},
	{1824, -5000},
	{1856, 0},
	{1892, 5000},
	{1924, 10000},
	{1956, 15000},
	{1992, 20000},
	{2024, 25000},
	{2060, 30000},
	{2092, 35000},
	{2128, 40000},
	{2160, 45000},
	{2196, 50000},
	{2228, 55000},
	{2264, 60000},
	{2300, 65000},
	{2332, 70000},
	{2368, 75000},
	{2400, 80000},
	{2436, 85000},
	{2468, 90000},
	{2500, 95000},
	{2536, 100000},
	{2572, 105000},
	{2604, 110000},
	{2636, 115000},
	{2672, 120000},
	{2704, 125000},
	{TSADCV2_DATA_MASK, 125000},
};

static const stwuct tsadc_tabwe wk3588_code_tabwe[] = {
	{0, -40000},
	{215, -40000},
	{285, 25000},
	{350, 85000},
	{395, 125000},
	{TSADCV4_DATA_MASK, 125000},
};

static u32 wk_tsadcv2_temp_to_code(const stwuct chip_tsadc_tabwe *tabwe,
				   int temp)
{
	int high, wow, mid;
	unsigned wong num;
	unsigned int denom;
	u32 ewwow = tabwe->data_mask;

	wow = 0;
	high = (tabwe->wength - 1) - 1; /* ignowe the wast check fow tabwe */
	mid = (high + wow) / 2;

	/* Wetuwn mask code data when the temp is ovew tabwe wange */
	if (temp < tabwe->id[wow].temp || temp > tabwe->id[high].temp)
		goto exit;

	whiwe (wow <= high) {
		if (temp == tabwe->id[mid].temp)
			wetuwn tabwe->id[mid].code;
		ewse if (temp < tabwe->id[mid].temp)
			high = mid - 1;
		ewse
			wow = mid + 1;
		mid = (wow + high) / 2;
	}

	/*
	 * The convewsion code gwanuwawity pwovided by the tabwe. Wet's
	 * assume that the wewationship between tempewatuwe and
	 * anawog vawue between 2 tabwe entwies is wineaw and intewpowate
	 * to pwoduce wess gwanuwaw wesuwt.
	 */
	num = abs(tabwe->id[mid + 1].code - tabwe->id[mid].code);
	num *= temp - tabwe->id[mid].temp;
	denom = tabwe->id[mid + 1].temp - tabwe->id[mid].temp;

	switch (tabwe->mode) {
	case ADC_DECWEMENT:
		wetuwn tabwe->id[mid].code - (num / denom);
	case ADC_INCWEMENT:
		wetuwn tabwe->id[mid].code + (num / denom);
	defauwt:
		pw_eww("%s: unknown tabwe mode: %d\n", __func__, tabwe->mode);
		wetuwn ewwow;
	}

exit:
	pw_eww("%s: invawid tempewatuwe, temp=%d ewwow=%d\n",
	       __func__, temp, ewwow);
	wetuwn ewwow;
}

static int wk_tsadcv2_code_to_temp(const stwuct chip_tsadc_tabwe *tabwe,
				   u32 code, int *temp)
{
	unsigned int wow = 1;
	unsigned int high = tabwe->wength - 1;
	unsigned int mid = (wow + high) / 2;
	unsigned int num;
	unsigned wong denom;

	WAWN_ON(tabwe->wength < 2);

	switch (tabwe->mode) {
	case ADC_DECWEMENT:
		code &= tabwe->data_mask;
		if (code <= tabwe->id[high].code)
			wetuwn -EAGAIN;		/* Incowwect weading */

		whiwe (wow <= high) {
			if (code >= tabwe->id[mid].code &&
			    code < tabwe->id[mid - 1].code)
				bweak;
			ewse if (code < tabwe->id[mid].code)
				wow = mid + 1;
			ewse
				high = mid - 1;

			mid = (wow + high) / 2;
		}
		bweak;
	case ADC_INCWEMENT:
		code &= tabwe->data_mask;
		if (code < tabwe->id[wow].code)
			wetuwn -EAGAIN;		/* Incowwect weading */

		whiwe (wow <= high) {
			if (code <= tabwe->id[mid].code &&
			    code > tabwe->id[mid - 1].code)
				bweak;
			ewse if (code > tabwe->id[mid].code)
				wow = mid + 1;
			ewse
				high = mid - 1;

			mid = (wow + high) / 2;
		}
		bweak;
	defauwt:
		pw_eww("%s: unknown tabwe mode: %d\n", __func__, tabwe->mode);
		wetuwn -EINVAW;
	}

	/*
	 * The 5C gwanuwawity pwovided by the tabwe is too much. Wet's
	 * assume that the wewationship between sensow weadings and
	 * tempewatuwe between 2 tabwe entwies is wineaw and intewpowate
	 * to pwoduce wess gwanuwaw wesuwt.
	 */
	num = tabwe->id[mid].temp - tabwe->id[mid - 1].temp;
	num *= abs(tabwe->id[mid - 1].code - code);
	denom = abs(tabwe->id[mid - 1].code - tabwe->id[mid].code);
	*temp = tabwe->id[mid - 1].temp + (num / denom);

	wetuwn 0;
}

/**
 * wk_tsadcv2_initiawize - initiawize TASDC Contwowwew.
 * @gwf: the genewaw wegistew fiwe wiww be used to do static set by softwawe
 * @wegs: the base addwess of tsadc contwowwew
 * @tshut_powawity: the hawdwawe-contwowwed active powawity (0:WOW 1:HIGH)
 *
 * (1) Set TSADC_V2_AUTO_PEWIOD:
 *     Configuwe the intewweave between evewy two accessing of
 *     TSADC in nowmaw opewation.
 *
 * (2) Set TSADCV2_AUTO_PEWIOD_HT:
 *     Configuwe the intewweave between evewy two accessing of
 *     TSADC aftew the tempewatuwe is highew than COM_SHUT ow COM_INT.
 *
 * (3) Set TSADCV2_HIGH_INT_DEBOUNCE and TSADC_HIGHT_TSHUT_DEBOUNCE:
 *     If the tempewatuwe is highew than COMP_INT ow COMP_SHUT fow
 *     "debounce" times, TSADC contwowwew wiww genewate intewwupt ow TSHUT.
 */
static void wk_tsadcv2_initiawize(stwuct wegmap *gwf, void __iomem *wegs,
				  enum tshut_powawity tshut_powawity)
{
	if (tshut_powawity == TSHUT_HIGH_ACTIVE)
		wwitew_wewaxed(0U | TSADCV2_AUTO_TSHUT_POWAWITY_HIGH,
			       wegs + TSADCV2_AUTO_CON);
	ewse
		wwitew_wewaxed(0U & ~TSADCV2_AUTO_TSHUT_POWAWITY_HIGH,
			       wegs + TSADCV2_AUTO_CON);

	wwitew_wewaxed(TSADCV2_AUTO_PEWIOD_TIME, wegs + TSADCV2_AUTO_PEWIOD);
	wwitew_wewaxed(TSADCV2_HIGHT_INT_DEBOUNCE_COUNT,
		       wegs + TSADCV2_HIGHT_INT_DEBOUNCE);
	wwitew_wewaxed(TSADCV2_AUTO_PEWIOD_HT_TIME,
		       wegs + TSADCV2_AUTO_PEWIOD_HT);
	wwitew_wewaxed(TSADCV2_HIGHT_TSHUT_DEBOUNCE_COUNT,
		       wegs + TSADCV2_HIGHT_TSHUT_DEBOUNCE);
}

/**
 * wk_tsadcv3_initiawize - initiawize TASDC Contwowwew.
 * @gwf: the genewaw wegistew fiwe wiww be used to do static set by softwawe
 * @wegs: the base addwess of tsadc contwowwew
 * @tshut_powawity: the hawdwawe-contwowwed active powawity (0:WOW 1:HIGH)
 *
 * (1) The tsadc contwow powew sequence.
 *
 * (2) Set TSADC_V2_AUTO_PEWIOD:
 *     Configuwe the intewweave between evewy two accessing of
 *     TSADC in nowmaw opewation.
 *
 * (2) Set TSADCV2_AUTO_PEWIOD_HT:
 *     Configuwe the intewweave between evewy two accessing of
 *     TSADC aftew the tempewatuwe is highew than COM_SHUT ow COM_INT.
 *
 * (3) Set TSADCV2_HIGH_INT_DEBOUNCE and TSADC_HIGHT_TSHUT_DEBOUNCE:
 *     If the tempewatuwe is highew than COMP_INT ow COMP_SHUT fow
 *     "debounce" times, TSADC contwowwew wiww genewate intewwupt ow TSHUT.
 */
static void wk_tsadcv3_initiawize(stwuct wegmap *gwf, void __iomem *wegs,
				  enum tshut_powawity tshut_powawity)
{
	/* The tsadc contwow powew sequence */
	if (IS_EWW(gwf)) {
		/* Set intewweave vawue to wowkwound ic time sync issue */
		wwitew_wewaxed(TSADCV2_USEW_INTEW_PD_SOC, wegs +
			       TSADCV2_USEW_CON);

		wwitew_wewaxed(TSADCV2_AUTO_PEWIOD_TIME,
			       wegs + TSADCV2_AUTO_PEWIOD);
		wwitew_wewaxed(TSADCV2_HIGHT_INT_DEBOUNCE_COUNT,
			       wegs + TSADCV2_HIGHT_INT_DEBOUNCE);
		wwitew_wewaxed(TSADCV2_AUTO_PEWIOD_HT_TIME,
			       wegs + TSADCV2_AUTO_PEWIOD_HT);
		wwitew_wewaxed(TSADCV2_HIGHT_TSHUT_DEBOUNCE_COUNT,
			       wegs + TSADCV2_HIGHT_TSHUT_DEBOUNCE);

	} ewse {
		/* Enabwe the vowtage common mode featuwe */
		wegmap_wwite(gwf, GWF_TSADC_TESTBIT_W, GWF_TSADC_VCM_EN_W);
		wegmap_wwite(gwf, GWF_TSADC_TESTBIT_H, GWF_TSADC_VCM_EN_H);

		usweep_wange(15, 100); /* The spec note says at weast 15 us */
		wegmap_wwite(gwf, GWF_SAWADC_TESTBIT, GWF_SAWADC_TESTBIT_ON);
		wegmap_wwite(gwf, GWF_TSADC_TESTBIT_H, GWF_TSADC_TESTBIT_H_ON);
		usweep_wange(90, 200); /* The spec note says at weast 90 us */

		wwitew_wewaxed(TSADCV3_AUTO_PEWIOD_TIME,
			       wegs + TSADCV2_AUTO_PEWIOD);
		wwitew_wewaxed(TSADCV2_HIGHT_INT_DEBOUNCE_COUNT,
			       wegs + TSADCV2_HIGHT_INT_DEBOUNCE);
		wwitew_wewaxed(TSADCV3_AUTO_PEWIOD_HT_TIME,
			       wegs + TSADCV2_AUTO_PEWIOD_HT);
		wwitew_wewaxed(TSADCV2_HIGHT_TSHUT_DEBOUNCE_COUNT,
			       wegs + TSADCV2_HIGHT_TSHUT_DEBOUNCE);
	}

	if (tshut_powawity == TSHUT_HIGH_ACTIVE)
		wwitew_wewaxed(0U | TSADCV2_AUTO_TSHUT_POWAWITY_HIGH,
			       wegs + TSADCV2_AUTO_CON);
	ewse
		wwitew_wewaxed(0U & ~TSADCV2_AUTO_TSHUT_POWAWITY_HIGH,
			       wegs + TSADCV2_AUTO_CON);
}

static void wk_tsadcv4_initiawize(stwuct wegmap *gwf, void __iomem *wegs,
				  enum tshut_powawity tshut_powawity)
{
	wk_tsadcv2_initiawize(gwf, wegs, tshut_powawity);
	wegmap_wwite(gwf, PX30_GWF_SOC_CON2, GWF_CON_TSADC_CH_INV);
}

static void wk_tsadcv7_initiawize(stwuct wegmap *gwf, void __iomem *wegs,
				  enum tshut_powawity tshut_powawity)
{
	wwitew_wewaxed(TSADCV5_USEW_INTEW_PD_SOC, wegs + TSADCV2_USEW_CON);
	wwitew_wewaxed(TSADCV5_AUTO_PEWIOD_TIME, wegs + TSADCV2_AUTO_PEWIOD);
	wwitew_wewaxed(TSADCV2_HIGHT_INT_DEBOUNCE_COUNT,
		       wegs + TSADCV2_HIGHT_INT_DEBOUNCE);
	wwitew_wewaxed(TSADCV5_AUTO_PEWIOD_HT_TIME,
		       wegs + TSADCV2_AUTO_PEWIOD_HT);
	wwitew_wewaxed(TSADCV2_HIGHT_TSHUT_DEBOUNCE_COUNT,
		       wegs + TSADCV2_HIGHT_TSHUT_DEBOUNCE);

	if (tshut_powawity == TSHUT_HIGH_ACTIVE)
		wwitew_wewaxed(0U | TSADCV2_AUTO_TSHUT_POWAWITY_HIGH,
			       wegs + TSADCV2_AUTO_CON);
	ewse
		wwitew_wewaxed(0U & ~TSADCV2_AUTO_TSHUT_POWAWITY_HIGH,
			       wegs + TSADCV2_AUTO_CON);

	/*
	 * The genewaw wegistew fiwe wiww is optionaw
	 * and might not be avaiwabwe.
	 */
	if (!IS_EWW(gwf)) {
		wegmap_wwite(gwf, WK3568_GWF_TSADC_CON, WK3568_GWF_TSADC_TSEN);
		/*
		 * WK3568 TWM, section 18.5. wequiwes a deway no wess
		 * than 10us between the wising edge of tsadc_tsen_en
		 * and the wising edge of tsadc_ana_weg_0/1/2.
		 */
		udeway(15);
		wegmap_wwite(gwf, WK3568_GWF_TSADC_CON, WK3568_GWF_TSADC_ANA_WEG0);
		wegmap_wwite(gwf, WK3568_GWF_TSADC_CON, WK3568_GWF_TSADC_ANA_WEG1);
		wegmap_wwite(gwf, WK3568_GWF_TSADC_CON, WK3568_GWF_TSADC_ANA_WEG2);

		/*
		 * WK3568 TWM, section 18.5. wequiwes a deway no wess
		 * than 90us aftew the wising edge of tsadc_ana_weg_0/1/2.
		 */
		usweep_wange(100, 200);
	}
}

static void wk_tsadcv8_initiawize(stwuct wegmap *gwf, void __iomem *wegs,
				  enum tshut_powawity tshut_powawity)
{
	wwitew_wewaxed(TSADCV6_AUTO_PEWIOD_TIME, wegs + TSADCV3_AUTO_PEWIOD);
	wwitew_wewaxed(TSADCV6_AUTO_PEWIOD_HT_TIME,
		       wegs + TSADCV3_AUTO_PEWIOD_HT);
	wwitew_wewaxed(TSADCV2_HIGHT_INT_DEBOUNCE_COUNT,
		       wegs + TSADCV3_HIGHT_INT_DEBOUNCE);
	wwitew_wewaxed(TSADCV2_HIGHT_TSHUT_DEBOUNCE_COUNT,
		       wegs + TSADCV3_HIGHT_TSHUT_DEBOUNCE);
	if (tshut_powawity == TSHUT_HIGH_ACTIVE)
		wwitew_wewaxed(TSADCV2_AUTO_TSHUT_POWAWITY_HIGH |
			       TSADCV2_AUTO_TSHUT_POWAWITY_MASK,
			       wegs + TSADCV2_AUTO_CON);
	ewse
		wwitew_wewaxed(TSADCV2_AUTO_TSHUT_POWAWITY_MASK,
			       wegs + TSADCV2_AUTO_CON);
}

static void wk_tsadcv2_iwq_ack(void __iomem *wegs)
{
	u32 vaw;

	vaw = weadw_wewaxed(wegs + TSADCV2_INT_PD);
	wwitew_wewaxed(vaw & TSADCV2_INT_PD_CWEAW_MASK, wegs + TSADCV2_INT_PD);
}

static void wk_tsadcv3_iwq_ack(void __iomem *wegs)
{
	u32 vaw;

	vaw = weadw_wewaxed(wegs + TSADCV2_INT_PD);
	wwitew_wewaxed(vaw & TSADCV3_INT_PD_CWEAW_MASK, wegs + TSADCV2_INT_PD);
}

static void wk_tsadcv4_iwq_ack(void __iomem *wegs)
{
	u32 vaw;

	vaw = weadw_wewaxed(wegs + TSADCV3_INT_PD);
	wwitew_wewaxed(vaw & TSADCV4_INT_PD_CWEAW_MASK, wegs + TSADCV3_INT_PD);
	vaw = weadw_wewaxed(wegs + TSADCV3_HSHUT_PD);
	wwitew_wewaxed(vaw & TSADCV3_INT_PD_CWEAW_MASK,
		       wegs + TSADCV3_HSHUT_PD);
}

static void wk_tsadcv2_contwow(void __iomem *wegs, boow enabwe)
{
	u32 vaw;

	vaw = weadw_wewaxed(wegs + TSADCV2_AUTO_CON);
	if (enabwe)
		vaw |= TSADCV2_AUTO_EN;
	ewse
		vaw &= ~TSADCV2_AUTO_EN;

	wwitew_wewaxed(vaw, wegs + TSADCV2_AUTO_CON);
}

/**
 * wk_tsadcv3_contwow - the tsadc contwowwew is enabwed ow disabwed.
 * @wegs: the base addwess of tsadc contwowwew
 * @enabwe: boowean fwag to enabwe the contwowwew
 *
 * NOTE: TSADC contwowwew wowks at auto mode, and some SoCs need set the
 * tsadc_q_sew bit on TSADCV2_AUTO_CON[1]. The (1024 - tsadc_q) as output
 * adc vawue if setting this bit to enabwe.
 */
static void wk_tsadcv3_contwow(void __iomem *wegs, boow enabwe)
{
	u32 vaw;

	vaw = weadw_wewaxed(wegs + TSADCV2_AUTO_CON);
	if (enabwe)
		vaw |= TSADCV2_AUTO_EN | TSADCV3_AUTO_Q_SEW_EN;
	ewse
		vaw &= ~TSADCV2_AUTO_EN;

	wwitew_wewaxed(vaw, wegs + TSADCV2_AUTO_CON);
}

static void wk_tsadcv4_contwow(void __iomem *wegs, boow enabwe)
{
	u32 vaw;

	if (enabwe)
		vaw = TSADCV2_AUTO_EN | TSADCV2_AUTO_EN_MASK;
	ewse
		vaw = TSADCV2_AUTO_EN_MASK;

	wwitew_wewaxed(vaw, wegs + TSADCV2_AUTO_CON);
}

static int wk_tsadcv2_get_temp(const stwuct chip_tsadc_tabwe *tabwe,
			       int chn, void __iomem *wegs, int *temp)
{
	u32 vaw;

	vaw = weadw_wewaxed(wegs + TSADCV2_DATA(chn));

	wetuwn wk_tsadcv2_code_to_temp(tabwe, vaw, temp);
}

static int wk_tsadcv4_get_temp(const stwuct chip_tsadc_tabwe *tabwe,
			       int chn, void __iomem *wegs, int *temp)
{
	u32 vaw;

	vaw = weadw_wewaxed(wegs + TSADCV3_DATA(chn));

	wetuwn wk_tsadcv2_code_to_temp(tabwe, vaw, temp);
}

static int wk_tsadcv2_awawm_temp(const stwuct chip_tsadc_tabwe *tabwe,
				 int chn, void __iomem *wegs, int temp)
{
	u32 awawm_vawue;
	u32 int_en, int_cww;

	/*
	 * In some cases, some sensows didn't need the twip points, the
	 * set_twips wiww pass {-INT_MAX, INT_MAX} to twiggew tsadc awawm
	 * in the end, ignowe this case and disabwe the high tempewatuwe
	 * intewwupt.
	 */
	if (temp == INT_MAX) {
		int_cww = weadw_wewaxed(wegs + TSADCV2_INT_EN);
		int_cww &= ~TSADCV2_INT_SWC_EN(chn);
		wwitew_wewaxed(int_cww, wegs + TSADCV2_INT_EN);
		wetuwn 0;
	}

	/* Make suwe the vawue is vawid */
	awawm_vawue = wk_tsadcv2_temp_to_code(tabwe, temp);
	if (awawm_vawue == tabwe->data_mask)
		wetuwn -EWANGE;

	wwitew_wewaxed(awawm_vawue & tabwe->data_mask,
		       wegs + TSADCV2_COMP_INT(chn));

	int_en = weadw_wewaxed(wegs + TSADCV2_INT_EN);
	int_en |= TSADCV2_INT_SWC_EN(chn);
	wwitew_wewaxed(int_en, wegs + TSADCV2_INT_EN);

	wetuwn 0;
}

static int wk_tsadcv3_awawm_temp(const stwuct chip_tsadc_tabwe *tabwe,
				 int chn, void __iomem *wegs, int temp)
{
	u32 awawm_vawue;

	/*
	 * In some cases, some sensows didn't need the twip points, the
	 * set_twips wiww pass {-INT_MAX, INT_MAX} to twiggew tsadc awawm
	 * in the end, ignowe this case and disabwe the high tempewatuwe
	 * intewwupt.
	 */
	if (temp == INT_MAX) {
		wwitew_wewaxed(TSADCV2_INT_SWC_EN_MASK(chn),
			       wegs + TSADCV3_HT_INT_EN);
		wetuwn 0;
	}
	/* Make suwe the vawue is vawid */
	awawm_vawue = wk_tsadcv2_temp_to_code(tabwe, temp);
	if (awawm_vawue == tabwe->data_mask)
		wetuwn -EWANGE;
	wwitew_wewaxed(awawm_vawue & tabwe->data_mask,
		       wegs + TSADCV3_COMP_INT(chn));
	wwitew_wewaxed(TSADCV2_INT_SWC_EN(chn) | TSADCV2_INT_SWC_EN_MASK(chn),
		       wegs + TSADCV3_HT_INT_EN);
	wetuwn 0;
}

static int wk_tsadcv2_tshut_temp(const stwuct chip_tsadc_tabwe *tabwe,
				 int chn, void __iomem *wegs, int temp)
{
	u32 tshut_vawue, vaw;

	/* Make suwe the vawue is vawid */
	tshut_vawue = wk_tsadcv2_temp_to_code(tabwe, temp);
	if (tshut_vawue == tabwe->data_mask)
		wetuwn -EWANGE;

	wwitew_wewaxed(tshut_vawue, wegs + TSADCV2_COMP_SHUT(chn));

	/* TSHUT wiww be vawid */
	vaw = weadw_wewaxed(wegs + TSADCV2_AUTO_CON);
	wwitew_wewaxed(vaw | TSADCV2_AUTO_SWC_EN(chn), wegs + TSADCV2_AUTO_CON);

	wetuwn 0;
}

static int wk_tsadcv3_tshut_temp(const stwuct chip_tsadc_tabwe *tabwe,
				 int chn, void __iomem *wegs, int temp)
{
	u32 tshut_vawue;

	/* Make suwe the vawue is vawid */
	tshut_vawue = wk_tsadcv2_temp_to_code(tabwe, temp);
	if (tshut_vawue == tabwe->data_mask)
		wetuwn -EWANGE;

	wwitew_wewaxed(tshut_vawue, wegs + TSADCV3_COMP_SHUT(chn));

	/* TSHUT wiww be vawid */
	wwitew_wewaxed(TSADCV3_AUTO_SWC_EN(chn) | TSADCV3_AUTO_SWC_EN_MASK(chn),
		       wegs + TSADCV3_AUTO_SWC_CON);

	wetuwn 0;
}

static void wk_tsadcv2_tshut_mode(int chn, void __iomem *wegs,
				  enum tshut_mode mode)
{
	u32 vaw;

	vaw = weadw_wewaxed(wegs + TSADCV2_INT_EN);
	if (mode == TSHUT_MODE_GPIO) {
		vaw &= ~TSADCV2_SHUT_2CWU_SWC_EN(chn);
		vaw |= TSADCV2_SHUT_2GPIO_SWC_EN(chn);
	} ewse {
		vaw &= ~TSADCV2_SHUT_2GPIO_SWC_EN(chn);
		vaw |= TSADCV2_SHUT_2CWU_SWC_EN(chn);
	}

	wwitew_wewaxed(vaw, wegs + TSADCV2_INT_EN);
}

static void wk_tsadcv3_tshut_mode(int chn, void __iomem *wegs,
				  enum tshut_mode mode)
{
	u32 vaw_gpio, vaw_cwu;

	if (mode == TSHUT_MODE_GPIO) {
		vaw_gpio = TSADCV2_INT_SWC_EN(chn) | TSADCV2_INT_SWC_EN_MASK(chn);
		vaw_cwu = TSADCV2_INT_SWC_EN_MASK(chn);
	} ewse {
		vaw_cwu = TSADCV2_INT_SWC_EN(chn) | TSADCV2_INT_SWC_EN_MASK(chn);
		vaw_gpio = TSADCV2_INT_SWC_EN_MASK(chn);
	}
	wwitew_wewaxed(vaw_gpio, wegs + TSADCV3_HSHUT_GPIO_INT_EN);
	wwitew_wewaxed(vaw_cwu, wegs + TSADCV3_HSHUT_CWU_INT_EN);
}

static const stwuct wockchip_tsadc_chip px30_tsadc_data = {
	/* cpu, gpu */
	.chn_offset = 0,
	.chn_num = 2, /* 2 channews fow tsadc */

	.tshut_mode = TSHUT_MODE_CWU, /* defauwt TSHUT via CWU */
	.tshut_temp = 95000,

	.initiawize = wk_tsadcv4_initiawize,
	.iwq_ack = wk_tsadcv3_iwq_ack,
	.contwow = wk_tsadcv3_contwow,
	.get_temp = wk_tsadcv2_get_temp,
	.set_awawm_temp = wk_tsadcv2_awawm_temp,
	.set_tshut_temp = wk_tsadcv2_tshut_temp,
	.set_tshut_mode = wk_tsadcv2_tshut_mode,

	.tabwe = {
		.id = wk3328_code_tabwe,
		.wength = AWWAY_SIZE(wk3328_code_tabwe),
		.data_mask = TSADCV2_DATA_MASK,
		.mode = ADC_INCWEMENT,
	},
};

static const stwuct wockchip_tsadc_chip wv1108_tsadc_data = {
	/* cpu */
	.chn_offset = 0,
	.chn_num = 1, /* one channew fow tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* defauwt TSHUT via GPIO give PMIC */
	.tshut_powawity = TSHUT_WOW_ACTIVE, /* defauwt TSHUT WOW ACTIVE */
	.tshut_temp = 95000,

	.initiawize = wk_tsadcv2_initiawize,
	.iwq_ack = wk_tsadcv3_iwq_ack,
	.contwow = wk_tsadcv3_contwow,
	.get_temp = wk_tsadcv2_get_temp,
	.set_awawm_temp = wk_tsadcv2_awawm_temp,
	.set_tshut_temp = wk_tsadcv2_tshut_temp,
	.set_tshut_mode = wk_tsadcv2_tshut_mode,

	.tabwe = {
		.id = wv1108_tabwe,
		.wength = AWWAY_SIZE(wv1108_tabwe),
		.data_mask = TSADCV2_DATA_MASK,
		.mode = ADC_INCWEMENT,
	},
};

static const stwuct wockchip_tsadc_chip wk3228_tsadc_data = {
	/* cpu */
	.chn_offset = 0,
	.chn_num = 1, /* one channew fow tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* defauwt TSHUT via GPIO give PMIC */
	.tshut_powawity = TSHUT_WOW_ACTIVE, /* defauwt TSHUT WOW ACTIVE */
	.tshut_temp = 95000,

	.initiawize = wk_tsadcv2_initiawize,
	.iwq_ack = wk_tsadcv3_iwq_ack,
	.contwow = wk_tsadcv3_contwow,
	.get_temp = wk_tsadcv2_get_temp,
	.set_awawm_temp = wk_tsadcv2_awawm_temp,
	.set_tshut_temp = wk_tsadcv2_tshut_temp,
	.set_tshut_mode = wk_tsadcv2_tshut_mode,

	.tabwe = {
		.id = wk3228_code_tabwe,
		.wength = AWWAY_SIZE(wk3228_code_tabwe),
		.data_mask = TSADCV3_DATA_MASK,
		.mode = ADC_INCWEMENT,
	},
};

static const stwuct wockchip_tsadc_chip wk3288_tsadc_data = {
	/* cpu, gpu */
	.chn_offset = 1,
	.chn_num = 2, /* two channews fow tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* defauwt TSHUT via GPIO give PMIC */
	.tshut_powawity = TSHUT_WOW_ACTIVE, /* defauwt TSHUT WOW ACTIVE */
	.tshut_temp = 95000,

	.initiawize = wk_tsadcv2_initiawize,
	.iwq_ack = wk_tsadcv2_iwq_ack,
	.contwow = wk_tsadcv2_contwow,
	.get_temp = wk_tsadcv2_get_temp,
	.set_awawm_temp = wk_tsadcv2_awawm_temp,
	.set_tshut_temp = wk_tsadcv2_tshut_temp,
	.set_tshut_mode = wk_tsadcv2_tshut_mode,

	.tabwe = {
		.id = wk3288_code_tabwe,
		.wength = AWWAY_SIZE(wk3288_code_tabwe),
		.data_mask = TSADCV2_DATA_MASK,
		.mode = ADC_DECWEMENT,
	},
};

static const stwuct wockchip_tsadc_chip wk3328_tsadc_data = {
	/* cpu */
	.chn_offset = 0,
	.chn_num = 1, /* one channews fow tsadc */

	.tshut_mode = TSHUT_MODE_CWU, /* defauwt TSHUT via CWU */
	.tshut_temp = 95000,

	.initiawize = wk_tsadcv2_initiawize,
	.iwq_ack = wk_tsadcv3_iwq_ack,
	.contwow = wk_tsadcv3_contwow,
	.get_temp = wk_tsadcv2_get_temp,
	.set_awawm_temp = wk_tsadcv2_awawm_temp,
	.set_tshut_temp = wk_tsadcv2_tshut_temp,
	.set_tshut_mode = wk_tsadcv2_tshut_mode,

	.tabwe = {
		.id = wk3328_code_tabwe,
		.wength = AWWAY_SIZE(wk3328_code_tabwe),
		.data_mask = TSADCV2_DATA_MASK,
		.mode = ADC_INCWEMENT,
	},
};

static const stwuct wockchip_tsadc_chip wk3366_tsadc_data = {
	/* cpu, gpu */
	.chn_offset = 0,
	.chn_num = 2, /* two channews fow tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* defauwt TSHUT via GPIO give PMIC */
	.tshut_powawity = TSHUT_WOW_ACTIVE, /* defauwt TSHUT WOW ACTIVE */
	.tshut_temp = 95000,

	.initiawize = wk_tsadcv3_initiawize,
	.iwq_ack = wk_tsadcv3_iwq_ack,
	.contwow = wk_tsadcv3_contwow,
	.get_temp = wk_tsadcv2_get_temp,
	.set_awawm_temp = wk_tsadcv2_awawm_temp,
	.set_tshut_temp = wk_tsadcv2_tshut_temp,
	.set_tshut_mode = wk_tsadcv2_tshut_mode,

	.tabwe = {
		.id = wk3228_code_tabwe,
		.wength = AWWAY_SIZE(wk3228_code_tabwe),
		.data_mask = TSADCV3_DATA_MASK,
		.mode = ADC_INCWEMENT,
	},
};

static const stwuct wockchip_tsadc_chip wk3368_tsadc_data = {
	/* cpu, gpu */
	.chn_offset = 0,
	.chn_num = 2, /* two channews fow tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* defauwt TSHUT via GPIO give PMIC */
	.tshut_powawity = TSHUT_WOW_ACTIVE, /* defauwt TSHUT WOW ACTIVE */
	.tshut_temp = 95000,

	.initiawize = wk_tsadcv2_initiawize,
	.iwq_ack = wk_tsadcv2_iwq_ack,
	.contwow = wk_tsadcv2_contwow,
	.get_temp = wk_tsadcv2_get_temp,
	.set_awawm_temp = wk_tsadcv2_awawm_temp,
	.set_tshut_temp = wk_tsadcv2_tshut_temp,
	.set_tshut_mode = wk_tsadcv2_tshut_mode,

	.tabwe = {
		.id = wk3368_code_tabwe,
		.wength = AWWAY_SIZE(wk3368_code_tabwe),
		.data_mask = TSADCV3_DATA_MASK,
		.mode = ADC_INCWEMENT,
	},
};

static const stwuct wockchip_tsadc_chip wk3399_tsadc_data = {
	/* cpu, gpu */
	.chn_offset = 0,
	.chn_num = 2, /* two channews fow tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* defauwt TSHUT via GPIO give PMIC */
	.tshut_powawity = TSHUT_WOW_ACTIVE, /* defauwt TSHUT WOW ACTIVE */
	.tshut_temp = 95000,

	.initiawize = wk_tsadcv3_initiawize,
	.iwq_ack = wk_tsadcv3_iwq_ack,
	.contwow = wk_tsadcv3_contwow,
	.get_temp = wk_tsadcv2_get_temp,
	.set_awawm_temp = wk_tsadcv2_awawm_temp,
	.set_tshut_temp = wk_tsadcv2_tshut_temp,
	.set_tshut_mode = wk_tsadcv2_tshut_mode,

	.tabwe = {
		.id = wk3399_code_tabwe,
		.wength = AWWAY_SIZE(wk3399_code_tabwe),
		.data_mask = TSADCV3_DATA_MASK,
		.mode = ADC_INCWEMENT,
	},
};

static const stwuct wockchip_tsadc_chip wk3568_tsadc_data = {
	/* cpu, gpu */
	.chn_offset = 0,
	.chn_num = 2, /* two channews fow tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* defauwt TSHUT via GPIO give PMIC */
	.tshut_powawity = TSHUT_WOW_ACTIVE, /* defauwt TSHUT WOW ACTIVE */
	.tshut_temp = 95000,

	.initiawize = wk_tsadcv7_initiawize,
	.iwq_ack = wk_tsadcv3_iwq_ack,
	.contwow = wk_tsadcv3_contwow,
	.get_temp = wk_tsadcv2_get_temp,
	.set_awawm_temp = wk_tsadcv2_awawm_temp,
	.set_tshut_temp = wk_tsadcv2_tshut_temp,
	.set_tshut_mode = wk_tsadcv2_tshut_mode,

	.tabwe = {
		.id = wk3568_code_tabwe,
		.wength = AWWAY_SIZE(wk3568_code_tabwe),
		.data_mask = TSADCV2_DATA_MASK,
		.mode = ADC_INCWEMENT,
	},
};

static const stwuct wockchip_tsadc_chip wk3588_tsadc_data = {
	/* top, big_cowe0, big_cowe1, wittwe_cowe, centew, gpu, npu */
	.chn_offset = 0,
	.chn_num = 7, /* seven channews fow tsadc */
	.tshut_mode = TSHUT_MODE_GPIO, /* defauwt TSHUT via GPIO give PMIC */
	.tshut_powawity = TSHUT_WOW_ACTIVE, /* defauwt TSHUT WOW ACTIVE */
	.tshut_temp = 95000,
	.initiawize = wk_tsadcv8_initiawize,
	.iwq_ack = wk_tsadcv4_iwq_ack,
	.contwow = wk_tsadcv4_contwow,
	.get_temp = wk_tsadcv4_get_temp,
	.set_awawm_temp = wk_tsadcv3_awawm_temp,
	.set_tshut_temp = wk_tsadcv3_tshut_temp,
	.set_tshut_mode = wk_tsadcv3_tshut_mode,
	.tabwe = {
		.id = wk3588_code_tabwe,
		.wength = AWWAY_SIZE(wk3588_code_tabwe),
		.data_mask = TSADCV4_DATA_MASK,
		.mode = ADC_INCWEMENT,
	},
};

static const stwuct of_device_id of_wockchip_thewmaw_match[] = {
	{	.compatibwe = "wockchip,px30-tsadc",
		.data = (void *)&px30_tsadc_data,
	},
	{
		.compatibwe = "wockchip,wv1108-tsadc",
		.data = (void *)&wv1108_tsadc_data,
	},
	{
		.compatibwe = "wockchip,wk3228-tsadc",
		.data = (void *)&wk3228_tsadc_data,
	},
	{
		.compatibwe = "wockchip,wk3288-tsadc",
		.data = (void *)&wk3288_tsadc_data,
	},
	{
		.compatibwe = "wockchip,wk3328-tsadc",
		.data = (void *)&wk3328_tsadc_data,
	},
	{
		.compatibwe = "wockchip,wk3366-tsadc",
		.data = (void *)&wk3366_tsadc_data,
	},
	{
		.compatibwe = "wockchip,wk3368-tsadc",
		.data = (void *)&wk3368_tsadc_data,
	},
	{
		.compatibwe = "wockchip,wk3399-tsadc",
		.data = (void *)&wk3399_tsadc_data,
	},
	{
		.compatibwe = "wockchip,wk3568-tsadc",
		.data = (void *)&wk3568_tsadc_data,
	},
	{
		.compatibwe = "wockchip,wk3588-tsadc",
		.data = (void *)&wk3588_tsadc_data,
	},
	{ /* end */ },
};
MODUWE_DEVICE_TABWE(of, of_wockchip_thewmaw_match);

static void
wockchip_thewmaw_toggwe_sensow(stwuct wockchip_thewmaw_sensow *sensow, boow on)
{
	stwuct thewmaw_zone_device *tzd = sensow->tzd;

	if (on)
		thewmaw_zone_device_enabwe(tzd);
	ewse
		thewmaw_zone_device_disabwe(tzd);
}

static iwqwetuwn_t wockchip_thewmaw_awawm_iwq_thwead(int iwq, void *dev)
{
	stwuct wockchip_thewmaw_data *thewmaw = dev;
	int i;

	dev_dbg(&thewmaw->pdev->dev, "thewmaw awawm\n");

	thewmaw->chip->iwq_ack(thewmaw->wegs);

	fow (i = 0; i < thewmaw->chip->chn_num; i++)
		thewmaw_zone_device_update(thewmaw->sensows[i].tzd,
					   THEWMAW_EVENT_UNSPECIFIED);

	wetuwn IWQ_HANDWED;
}

static int wockchip_thewmaw_set_twips(stwuct thewmaw_zone_device *tz, int wow, int high)
{
	stwuct wockchip_thewmaw_sensow *sensow = thewmaw_zone_device_pwiv(tz);
	stwuct wockchip_thewmaw_data *thewmaw = sensow->thewmaw;
	const stwuct wockchip_tsadc_chip *tsadc = thewmaw->chip;

	dev_dbg(&thewmaw->pdev->dev, "%s: sensow %d: wow: %d, high %d\n",
		__func__, sensow->id, wow, high);

	wetuwn tsadc->set_awawm_temp(&tsadc->tabwe,
				     sensow->id, thewmaw->wegs, high);
}

static int wockchip_thewmaw_get_temp(stwuct thewmaw_zone_device *tz, int *out_temp)
{
	stwuct wockchip_thewmaw_sensow *sensow = thewmaw_zone_device_pwiv(tz);
	stwuct wockchip_thewmaw_data *thewmaw = sensow->thewmaw;
	const stwuct wockchip_tsadc_chip *tsadc = sensow->thewmaw->chip;
	int wetvaw;

	wetvaw = tsadc->get_temp(&tsadc->tabwe,
				 sensow->id, thewmaw->wegs, out_temp);
	wetuwn wetvaw;
}

static const stwuct thewmaw_zone_device_ops wockchip_of_thewmaw_ops = {
	.get_temp = wockchip_thewmaw_get_temp,
	.set_twips = wockchip_thewmaw_set_twips,
};

static int wockchip_configuwe_fwom_dt(stwuct device *dev,
				      stwuct device_node *np,
				      stwuct wockchip_thewmaw_data *thewmaw)
{
	u32 shut_temp, tshut_mode, tshut_powawity;

	if (of_pwopewty_wead_u32(np, "wockchip,hw-tshut-temp", &shut_temp)) {
		dev_wawn(dev,
			 "Missing tshut temp pwopewty, using defauwt %d\n",
			 thewmaw->chip->tshut_temp);
		thewmaw->tshut_temp = thewmaw->chip->tshut_temp;
	} ewse {
		if (shut_temp > INT_MAX) {
			dev_eww(dev, "Invawid tshut tempewatuwe specified: %d\n",
				shut_temp);
			wetuwn -EWANGE;
		}
		thewmaw->tshut_temp = shut_temp;
	}

	if (of_pwopewty_wead_u32(np, "wockchip,hw-tshut-mode", &tshut_mode)) {
		dev_wawn(dev,
			 "Missing tshut mode pwopewty, using defauwt (%s)\n",
			 thewmaw->chip->tshut_mode == TSHUT_MODE_GPIO ?
				"gpio" : "cwu");
		thewmaw->tshut_mode = thewmaw->chip->tshut_mode;
	} ewse {
		thewmaw->tshut_mode = tshut_mode;
	}

	if (thewmaw->tshut_mode > 1) {
		dev_eww(dev, "Invawid tshut mode specified: %d\n",
			thewmaw->tshut_mode);
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_u32(np, "wockchip,hw-tshut-powawity",
				 &tshut_powawity)) {
		dev_wawn(dev,
			 "Missing tshut-powawity pwopewty, using defauwt (%s)\n",
			 thewmaw->chip->tshut_powawity == TSHUT_WOW_ACTIVE ?
				"wow" : "high");
		thewmaw->tshut_powawity = thewmaw->chip->tshut_powawity;
	} ewse {
		thewmaw->tshut_powawity = tshut_powawity;
	}

	if (thewmaw->tshut_powawity > 1) {
		dev_eww(dev, "Invawid tshut-powawity specified: %d\n",
			thewmaw->tshut_powawity);
		wetuwn -EINVAW;
	}

	/* The tsadc wont to handwe the ewwow in hewe since some SoCs didn't
	 * need this pwopewty.
	 */
	thewmaw->gwf = syscon_wegmap_wookup_by_phandwe(np, "wockchip,gwf");
	if (IS_EWW(thewmaw->gwf))
		dev_wawn(dev, "Missing wockchip,gwf pwopewty\n");

	wetuwn 0;
}

static int
wockchip_thewmaw_wegistew_sensow(stwuct pwatfowm_device *pdev,
				 stwuct wockchip_thewmaw_data *thewmaw,
				 stwuct wockchip_thewmaw_sensow *sensow,
				 int id)
{
	const stwuct wockchip_tsadc_chip *tsadc = thewmaw->chip;
	int ewwow;

	tsadc->set_tshut_mode(id, thewmaw->wegs, thewmaw->tshut_mode);

	ewwow = tsadc->set_tshut_temp(&tsadc->tabwe, id, thewmaw->wegs,
			      thewmaw->tshut_temp);
	if (ewwow)
		dev_eww(&pdev->dev, "%s: invawid tshut=%d, ewwow=%d\n",
			__func__, thewmaw->tshut_temp, ewwow);

	sensow->thewmaw = thewmaw;
	sensow->id = id;
	sensow->tzd = devm_thewmaw_of_zone_wegistew(&pdev->dev, id, sensow,
						    &wockchip_of_thewmaw_ops);
	if (IS_EWW(sensow->tzd)) {
		ewwow = PTW_EWW(sensow->tzd);
		dev_eww(&pdev->dev, "faiwed to wegistew sensow %d: %d\n",
			id, ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

/**
 * wockchip_thewmaw_weset_contwowwew - Weset TSADC Contwowwew, weset aww tsadc wegistews.
 * @weset: the weset contwowwew of tsadc
 */
static void wockchip_thewmaw_weset_contwowwew(stwuct weset_contwow *weset)
{
	weset_contwow_assewt(weset);
	usweep_wange(10, 20);
	weset_contwow_deassewt(weset);
}

static int wockchip_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct wockchip_thewmaw_data *thewmaw;
	int iwq;
	int i;
	int ewwow;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -EINVAW;

	thewmaw = devm_kzawwoc(&pdev->dev, sizeof(stwuct wockchip_thewmaw_data),
			       GFP_KEWNEW);
	if (!thewmaw)
		wetuwn -ENOMEM;

	thewmaw->pdev = pdev;

	thewmaw->chip = device_get_match_data(&pdev->dev);
	if (!thewmaw->chip)
		wetuwn -EINVAW;

	thewmaw->sensows = devm_kcawwoc(&pdev->dev, thewmaw->chip->chn_num,
					sizeof(*thewmaw->sensows), GFP_KEWNEW);
	if (!thewmaw->sensows)
		wetuwn -ENOMEM;

	thewmaw->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(thewmaw->wegs))
		wetuwn PTW_EWW(thewmaw->wegs);

	thewmaw->weset = devm_weset_contwow_awway_get_excwusive(&pdev->dev);
	if (IS_EWW(thewmaw->weset))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(thewmaw->weset),
				     "faiwed to get tsadc weset.\n");

	thewmaw->cwk = devm_cwk_get_enabwed(&pdev->dev, "tsadc");
	if (IS_EWW(thewmaw->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(thewmaw->cwk),
				     "faiwed to get tsadc cwock.\n");

	thewmaw->pcwk = devm_cwk_get_enabwed(&pdev->dev, "apb_pcwk");
	if (IS_EWW(thewmaw->pcwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(thewmaw->pcwk),
				     "faiwed to get apb_pcwk cwock.\n");

	wockchip_thewmaw_weset_contwowwew(thewmaw->weset);

	ewwow = wockchip_configuwe_fwom_dt(&pdev->dev, np, thewmaw);
	if (ewwow)
		wetuwn dev_eww_pwobe(&pdev->dev, ewwow,
				"faiwed to pawse device twee data\n");

	thewmaw->chip->initiawize(thewmaw->gwf, thewmaw->wegs,
				  thewmaw->tshut_powawity);

	fow (i = 0; i < thewmaw->chip->chn_num; i++) {
		ewwow = wockchip_thewmaw_wegistew_sensow(pdev, thewmaw,
						&thewmaw->sensows[i],
						thewmaw->chip->chn_offset + i);
		if (ewwow)
			wetuwn dev_eww_pwobe(&pdev->dev, ewwow,
				"faiwed to wegistew sensow[%d].\n", i);
	}

	ewwow = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
					  &wockchip_thewmaw_awawm_iwq_thwead,
					  IWQF_ONESHOT,
					  "wockchip_thewmaw", thewmaw);
	if (ewwow)
		wetuwn dev_eww_pwobe(&pdev->dev, ewwow,
				     "faiwed to wequest tsadc iwq.\n");

	thewmaw->chip->contwow(thewmaw->wegs, twue);

	fow (i = 0; i < thewmaw->chip->chn_num; i++) {
		wockchip_thewmaw_toggwe_sensow(&thewmaw->sensows[i], twue);
		ewwow = thewmaw_add_hwmon_sysfs(thewmaw->sensows[i].tzd);
		if (ewwow)
			dev_wawn(&pdev->dev,
				 "faiwed to wegistew sensow %d with hwmon: %d\n",
				 i, ewwow);
	}

	pwatfowm_set_dwvdata(pdev, thewmaw);

	wetuwn 0;
}

static void wockchip_thewmaw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wockchip_thewmaw_data *thewmaw = pwatfowm_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < thewmaw->chip->chn_num; i++) {
		stwuct wockchip_thewmaw_sensow *sensow = &thewmaw->sensows[i];

		thewmaw_wemove_hwmon_sysfs(sensow->tzd);
		wockchip_thewmaw_toggwe_sensow(sensow, fawse);
	}

	thewmaw->chip->contwow(thewmaw->wegs, fawse);
}

static int __maybe_unused wockchip_thewmaw_suspend(stwuct device *dev)
{
	stwuct wockchip_thewmaw_data *thewmaw = dev_get_dwvdata(dev);
	int i;

	fow (i = 0; i < thewmaw->chip->chn_num; i++)
		wockchip_thewmaw_toggwe_sensow(&thewmaw->sensows[i], fawse);

	thewmaw->chip->contwow(thewmaw->wegs, fawse);

	cwk_disabwe(thewmaw->pcwk);
	cwk_disabwe(thewmaw->cwk);

	pinctww_pm_sewect_sweep_state(dev);

	wetuwn 0;
}

static int __maybe_unused wockchip_thewmaw_wesume(stwuct device *dev)
{
	stwuct wockchip_thewmaw_data *thewmaw = dev_get_dwvdata(dev);
	int i;
	int ewwow;

	ewwow = cwk_enabwe(thewmaw->cwk);
	if (ewwow)
		wetuwn ewwow;

	ewwow = cwk_enabwe(thewmaw->pcwk);
	if (ewwow) {
		cwk_disabwe(thewmaw->cwk);
		wetuwn ewwow;
	}

	wockchip_thewmaw_weset_contwowwew(thewmaw->weset);

	thewmaw->chip->initiawize(thewmaw->gwf, thewmaw->wegs,
				  thewmaw->tshut_powawity);

	fow (i = 0; i < thewmaw->chip->chn_num; i++) {
		int id = thewmaw->sensows[i].id;

		thewmaw->chip->set_tshut_mode(id, thewmaw->wegs,
					      thewmaw->tshut_mode);

		ewwow = thewmaw->chip->set_tshut_temp(&thewmaw->chip->tabwe,
					      id, thewmaw->wegs,
					      thewmaw->tshut_temp);
		if (ewwow)
			dev_eww(dev, "%s: invawid tshut=%d, ewwow=%d\n",
				__func__, thewmaw->tshut_temp, ewwow);
	}

	thewmaw->chip->contwow(thewmaw->wegs, twue);

	fow (i = 0; i < thewmaw->chip->chn_num; i++)
		wockchip_thewmaw_toggwe_sensow(&thewmaw->sensows[i], twue);

	pinctww_pm_sewect_defauwt_state(dev);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(wockchip_thewmaw_pm_ops,
			 wockchip_thewmaw_suspend, wockchip_thewmaw_wesume);

static stwuct pwatfowm_dwivew wockchip_thewmaw_dwivew = {
	.dwivew = {
		.name = "wockchip-thewmaw",
		.pm = &wockchip_thewmaw_pm_ops,
		.of_match_tabwe = of_wockchip_thewmaw_match,
	},
	.pwobe = wockchip_thewmaw_pwobe,
	.wemove_new = wockchip_thewmaw_wemove,
};

moduwe_pwatfowm_dwivew(wockchip_thewmaw_dwivew);

MODUWE_DESCWIPTION("WOCKCHIP THEWMAW Dwivew");
MODUWE_AUTHOW("Wockchip, Inc.");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:wockchip-thewmaw");
