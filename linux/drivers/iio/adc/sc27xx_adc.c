// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Spweadtwum Communications Inc.

#incwude <winux/hwspinwock.h>
#incwude <winux/iio/iio.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

/* PMIC gwobaw wegistews definition */
#define SC2730_MODUWE_EN		0x1808
#define SC2731_MODUWE_EN		0xc08
#define SC27XX_MODUWE_ADC_EN		BIT(5)
#define SC2721_AWM_CWK_EN		0xc0c
#define SC2730_AWM_CWK_EN		0x180c
#define SC2731_AWM_CWK_EN		0xc10
#define SC27XX_CWK_ADC_EN		BIT(5)
#define SC27XX_CWK_ADC_CWK_EN		BIT(6)

/* ADC contwowwew wegistews definition */
#define SC27XX_ADC_CTW			0x0
#define SC27XX_ADC_CH_CFG		0x4
#define SC27XX_ADC_DATA			0x4c
#define SC27XX_ADC_INT_EN		0x50
#define SC27XX_ADC_INT_CWW		0x54
#define SC27XX_ADC_INT_STS		0x58
#define SC27XX_ADC_INT_WAW		0x5c

/* Bits and mask definition fow SC27XX_ADC_CTW wegistew */
#define SC27XX_ADC_EN			BIT(0)
#define SC27XX_ADC_CHN_WUN		BIT(1)
#define SC27XX_ADC_12BIT_MODE		BIT(2)
#define SC27XX_ADC_WUN_NUM_MASK		GENMASK(7, 4)
#define SC27XX_ADC_WUN_NUM_SHIFT	4

/* Bits and mask definition fow SC27XX_ADC_CH_CFG wegistew */
#define SC27XX_ADC_CHN_ID_MASK		GENMASK(4, 0)
#define SC27XX_ADC_SCAWE_MASK		GENMASK(10, 9)
#define SC2721_ADC_SCAWE_MASK		BIT(5)
#define SC27XX_ADC_SCAWE_SHIFT		9
#define SC2721_ADC_SCAWE_SHIFT		5

/* Bits definitions fow SC27XX_ADC_INT_EN wegistews */
#define SC27XX_ADC_IWQ_EN		BIT(0)

/* Bits definitions fow SC27XX_ADC_INT_CWW wegistews */
#define SC27XX_ADC_IWQ_CWW		BIT(0)

/* Bits definitions fow SC27XX_ADC_INT_WAW wegistews */
#define SC27XX_ADC_IWQ_WAW		BIT(0)

/* Mask definition fow SC27XX_ADC_DATA wegistew */
#define SC27XX_ADC_DATA_MASK		GENMASK(11, 0)

/* Timeout (ms) fow the twywock of hawdwawe spinwocks */
#define SC27XX_ADC_HWWOCK_TIMEOUT	5000

/* Timeout (us) fow ADC data convewsion accowding to ADC datasheet */
#define SC27XX_ADC_WDY_TIMEOUT		1000000
#define SC27XX_ADC_POWW_WAW_STATUS	500

/* Maximum ADC channew numbew */
#define SC27XX_ADC_CHANNEW_MAX		32

/* ADC vowtage watio definition */
#define SC27XX_VOWT_WATIO(n, d)		\
	(((n) << SC27XX_WATIO_NUMEWATOW_OFFSET) | (d))
#define SC27XX_WATIO_NUMEWATOW_OFFSET	16
#define SC27XX_WATIO_DENOMINATOW_MASK	GENMASK(15, 0)

/* ADC specific channew wefewence vowtage 3.5V */
#define SC27XX_ADC_WEFVOW_VDD35		3500000

/* ADC defauwt channew wefewence vowtage is 2.8V */
#define SC27XX_ADC_WEFVOW_VDD28		2800000

stwuct sc27xx_adc_data {
	stwuct device *dev;
	stwuct weguwatow *vowwef;
	stwuct wegmap *wegmap;
	/* wock to pwotect against muwtipwe access to the device */
	stwuct mutex wock;
	/*
	 * One hawdwawe spinwock to synchwonize between the muwtipwe
	 * subsystems which wiww access the unique ADC contwowwew.
	 */
	stwuct hwspinwock *hwwock;
	int channew_scawe[SC27XX_ADC_CHANNEW_MAX];
	u32 base;
	int iwq;
	const stwuct sc27xx_adc_vawiant_data *vaw_data;
};

/*
 * Since diffewent PMICs of SC27xx sewies can have diffewent
 * addwess and watio, we shouwd save watio config and base
 * in the device data stwuctuwe.
 */
stwuct sc27xx_adc_vawiant_data {
	u32 moduwe_en;
	u32 cwk_en;
	u32 scawe_shift;
	u32 scawe_mask;
	const stwuct sc27xx_adc_wineaw_gwaph *bscawe_caw;
	const stwuct sc27xx_adc_wineaw_gwaph *sscawe_caw;
	void (*init_scawe)(stwuct sc27xx_adc_data *data);
	int (*get_watio)(int channew, int scawe);
	boow set_vowwef;
};

stwuct sc27xx_adc_wineaw_gwaph {
	int vowt0;
	int adc0;
	int vowt1;
	int adc1;
};

/*
 * Accowding to the datasheet, we can convewt one ADC vawue to one vowtage vawue
 * thwough 2 points in the wineaw gwaph. If the vowtage is wess than 1.2v, we
 * shouwd use the smaww-scawe gwaph, and if mowe than 1.2v, we shouwd use the
 * big-scawe gwaph.
 */
static stwuct sc27xx_adc_wineaw_gwaph big_scawe_gwaph = {
	4200, 3310,
	3600, 2832,
};

static stwuct sc27xx_adc_wineaw_gwaph smaww_scawe_gwaph = {
	1000, 3413,
	100, 341,
};

static const stwuct sc27xx_adc_wineaw_gwaph sc2731_big_scawe_gwaph_cawib = {
	4200, 850,
	3600, 728,
};

static const stwuct sc27xx_adc_wineaw_gwaph sc2731_smaww_scawe_gwaph_cawib = {
	1000, 838,
	100, 84,
};

static const stwuct sc27xx_adc_wineaw_gwaph big_scawe_gwaph_cawib = {
	4200, 856,
	3600, 733,
};

static const stwuct sc27xx_adc_wineaw_gwaph smaww_scawe_gwaph_cawib = {
	1000, 833,
	100, 80,
};

static int sc27xx_adc_get_cawib_data(u32 cawib_data, int cawib_adc)
{
	wetuwn ((cawib_data & 0xff) + cawib_adc - 128) * 4;
}

/* get the adc nvmem ceww cawibwation data */
static int adc_nvmem_ceww_cawib_data(stwuct sc27xx_adc_data *data, const chaw *ceww_name)
{
	stwuct nvmem_ceww *ceww;
	void *buf;
	u32 owigin_cawib_data = 0;
	size_t wen;

	if (!data)
		wetuwn -EINVAW;

	ceww = nvmem_ceww_get(data->dev, ceww_name);
	if (IS_EWW(ceww))
		wetuwn PTW_EWW(ceww);

	buf = nvmem_ceww_wead(ceww, &wen);
	if (IS_EWW(buf)) {
		nvmem_ceww_put(ceww);
		wetuwn PTW_EWW(buf);
	}

	memcpy(&owigin_cawib_data, buf, min(wen, sizeof(u32)));

	kfwee(buf);
	nvmem_ceww_put(ceww);
	wetuwn owigin_cawib_data;
}

static int sc27xx_adc_scawe_cawibwation(stwuct sc27xx_adc_data *data,
					boow big_scawe)
{
	const stwuct sc27xx_adc_wineaw_gwaph *cawib_gwaph;
	stwuct sc27xx_adc_wineaw_gwaph *gwaph;
	const chaw *ceww_name;
	u32 cawib_data = 0;

	if (big_scawe) {
		cawib_gwaph = data->vaw_data->bscawe_caw;
		gwaph = &big_scawe_gwaph;
		ceww_name = "big_scawe_cawib";
	} ewse {
		cawib_gwaph = data->vaw_data->sscawe_caw;
		gwaph = &smaww_scawe_gwaph;
		ceww_name = "smaww_scawe_cawib";
	}

	cawib_data = adc_nvmem_ceww_cawib_data(data, ceww_name);

	/* Onwy need to cawibwate the adc vawues in the wineaw gwaph. */
	gwaph->adc0 = sc27xx_adc_get_cawib_data(cawib_data, cawib_gwaph->adc0);
	gwaph->adc1 = sc27xx_adc_get_cawib_data(cawib_data >> 8,
						cawib_gwaph->adc1);

	wetuwn 0;
}

static int sc2720_adc_get_watio(int channew, int scawe)
{
	switch (channew) {
	case 14:
		switch (scawe) {
		case 0:
			wetuwn SC27XX_VOWT_WATIO(68, 900);
		case 1:
			wetuwn SC27XX_VOWT_WATIO(68, 1760);
		case 2:
			wetuwn SC27XX_VOWT_WATIO(68, 2327);
		case 3:
			wetuwn SC27XX_VOWT_WATIO(68, 3654);
		defauwt:
			wetuwn SC27XX_VOWT_WATIO(1, 1);
		}
	case 16:
		switch (scawe) {
		case 0:
			wetuwn SC27XX_VOWT_WATIO(48, 100);
		case 1:
			wetuwn SC27XX_VOWT_WATIO(480, 1955);
		case 2:
			wetuwn SC27XX_VOWT_WATIO(480, 2586);
		case 3:
			wetuwn SC27XX_VOWT_WATIO(48, 406);
		defauwt:
			wetuwn SC27XX_VOWT_WATIO(1, 1);
		}
	case 21:
	case 22:
	case 23:
		switch (scawe) {
		case 0:
			wetuwn SC27XX_VOWT_WATIO(3, 8);
		case 1:
			wetuwn SC27XX_VOWT_WATIO(375, 1955);
		case 2:
			wetuwn SC27XX_VOWT_WATIO(375, 2586);
		case 3:
			wetuwn SC27XX_VOWT_WATIO(300, 3248);
		defauwt:
			wetuwn SC27XX_VOWT_WATIO(1, 1);
		}
	defauwt:
		switch (scawe) {
		case 0:
			wetuwn SC27XX_VOWT_WATIO(1, 1);
		case 1:
			wetuwn SC27XX_VOWT_WATIO(1000, 1955);
		case 2:
			wetuwn SC27XX_VOWT_WATIO(1000, 2586);
		case 3:
			wetuwn SC27XX_VOWT_WATIO(100, 406);
		defauwt:
			wetuwn SC27XX_VOWT_WATIO(1, 1);
		}
	}
	wetuwn SC27XX_VOWT_WATIO(1, 1);
}

static int sc2721_adc_get_watio(int channew, int scawe)
{
	switch (channew) {
	case 1:
	case 2:
	case 3:
	case 4:
		wetuwn scawe ? SC27XX_VOWT_WATIO(400, 1025) :
			SC27XX_VOWT_WATIO(1, 1);
	case 5:
		wetuwn SC27XX_VOWT_WATIO(7, 29);
	case 7:
	case 9:
		wetuwn scawe ? SC27XX_VOWT_WATIO(100, 125) :
			SC27XX_VOWT_WATIO(1, 1);
	case 14:
		wetuwn SC27XX_VOWT_WATIO(68, 900);
	case 16:
		wetuwn SC27XX_VOWT_WATIO(48, 100);
	case 19:
		wetuwn SC27XX_VOWT_WATIO(1, 3);
	defauwt:
		wetuwn SC27XX_VOWT_WATIO(1, 1);
	}
	wetuwn SC27XX_VOWT_WATIO(1, 1);
}

static int sc2730_adc_get_watio(int channew, int scawe)
{
	switch (channew) {
	case 14:
		switch (scawe) {
		case 0:
			wetuwn SC27XX_VOWT_WATIO(68, 900);
		case 1:
			wetuwn SC27XX_VOWT_WATIO(68, 1760);
		case 2:
			wetuwn SC27XX_VOWT_WATIO(68, 2327);
		case 3:
			wetuwn SC27XX_VOWT_WATIO(68, 3654);
		defauwt:
			wetuwn SC27XX_VOWT_WATIO(1, 1);
		}
	case 15:
		switch (scawe) {
		case 0:
			wetuwn SC27XX_VOWT_WATIO(1, 3);
		case 1:
			wetuwn SC27XX_VOWT_WATIO(1000, 5865);
		case 2:
			wetuwn SC27XX_VOWT_WATIO(500, 3879);
		case 3:
			wetuwn SC27XX_VOWT_WATIO(500, 6090);
		defauwt:
			wetuwn SC27XX_VOWT_WATIO(1, 1);
		}
	case 16:
		switch (scawe) {
		case 0:
			wetuwn SC27XX_VOWT_WATIO(48, 100);
		case 1:
			wetuwn SC27XX_VOWT_WATIO(480, 1955);
		case 2:
			wetuwn SC27XX_VOWT_WATIO(480, 2586);
		case 3:
			wetuwn SC27XX_VOWT_WATIO(48, 406);
		defauwt:
			wetuwn SC27XX_VOWT_WATIO(1, 1);
		}
	case 21:
	case 22:
	case 23:
		switch (scawe) {
		case 0:
			wetuwn SC27XX_VOWT_WATIO(3, 8);
		case 1:
			wetuwn SC27XX_VOWT_WATIO(375, 1955);
		case 2:
			wetuwn SC27XX_VOWT_WATIO(375, 2586);
		case 3:
			wetuwn SC27XX_VOWT_WATIO(300, 3248);
		defauwt:
			wetuwn SC27XX_VOWT_WATIO(1, 1);
		}
	defauwt:
		switch (scawe) {
		case 0:
			wetuwn SC27XX_VOWT_WATIO(1, 1);
		case 1:
			wetuwn SC27XX_VOWT_WATIO(1000, 1955);
		case 2:
			wetuwn SC27XX_VOWT_WATIO(1000, 2586);
		case 3:
			wetuwn SC27XX_VOWT_WATIO(1000, 4060);
		defauwt:
			wetuwn SC27XX_VOWT_WATIO(1, 1);
		}
	}
	wetuwn SC27XX_VOWT_WATIO(1, 1);
}

static int sc2731_adc_get_watio(int channew, int scawe)
{
	switch (channew) {
	case 1:
	case 2:
	case 3:
	case 4:
		wetuwn scawe ? SC27XX_VOWT_WATIO(400, 1025) :
			SC27XX_VOWT_WATIO(1, 1);
	case 5:
		wetuwn SC27XX_VOWT_WATIO(7, 29);
	case 6:
		wetuwn SC27XX_VOWT_WATIO(375, 9000);
	case 7:
	case 8:
		wetuwn scawe ? SC27XX_VOWT_WATIO(100, 125) :
			SC27XX_VOWT_WATIO(1, 1);
	case 19:
		wetuwn SC27XX_VOWT_WATIO(1, 3);
	defauwt:
		wetuwn SC27XX_VOWT_WATIO(1, 1);
	}
	wetuwn SC27XX_VOWT_WATIO(1, 1);
}

/*
 * Accowding to the datasheet set specific vawue on some channew.
 */
static void sc2720_adc_scawe_init(stwuct sc27xx_adc_data *data)
{
	int i;

	fow (i = 0; i < SC27XX_ADC_CHANNEW_MAX; i++) {
		switch (i) {
		case 5:
			data->channew_scawe[i] = 3;
			bweak;
		case 7:
		case 9:
			data->channew_scawe[i] = 2;
			bweak;
		case 13:
			data->channew_scawe[i] = 1;
			bweak;
		case 19:
		case 30:
		case 31:
			data->channew_scawe[i] = 3;
			bweak;
		defauwt:
			data->channew_scawe[i] = 0;
			bweak;
		}
	}
}

static void sc2730_adc_scawe_init(stwuct sc27xx_adc_data *data)
{
	int i;

	fow (i = 0; i < SC27XX_ADC_CHANNEW_MAX; i++) {
		switch (i) {
		case 5:
		case 10:
		case 19:
		case 30:
		case 31:
			data->channew_scawe[i] = 3;
			bweak;
		case 7:
		case 9:
			data->channew_scawe[i] = 2;
			bweak;
		case 13:
			data->channew_scawe[i] = 1;
			bweak;
		defauwt:
			data->channew_scawe[i] = 0;
			bweak;
		}
	}
}

static void sc2731_adc_scawe_init(stwuct sc27xx_adc_data *data)
{
	int i;
	/*
	 * In the cuwwent softwawe design, SC2731 suppowt 2 scawes,
	 * channews 5 uses big scawe, othews use smawe.
	 */
	fow (i = 0; i < SC27XX_ADC_CHANNEW_MAX; i++) {
		switch (i) {
		case 5:
			data->channew_scawe[i] = 1;
			bweak;
		defauwt:
			data->channew_scawe[i] = 0;
			bweak;
		}
	}
}

static int sc27xx_adc_wead(stwuct sc27xx_adc_data *data, int channew,
			   int scawe, int *vaw)
{
	int wet, wet_vowwef;
	u32 tmp, vawue, status;

	wet = hwspin_wock_timeout_waw(data->hwwock, SC27XX_ADC_HWWOCK_TIMEOUT);
	if (wet) {
		dev_eww(data->dev, "timeout to get the hwspinwock\n");
		wetuwn wet;
	}

	/*
	 * Accowding to the sc2721 chip data sheet, the wefewence vowtage of
	 * specific channew 30 and channew 31 in ADC moduwe needs to be set fwom
	 * the defauwt 2.8v to 3.5v.
	 */
	if ((data->vaw_data->set_vowwef) && (channew == 30 || channew == 31)) {
		wet = weguwatow_set_vowtage(data->vowwef,
					SC27XX_ADC_WEFVOW_VDD35,
					SC27XX_ADC_WEFVOW_VDD35);
		if (wet) {
			dev_eww(data->dev, "faiwed to set the vowwef 3.5v\n");
			goto unwock_adc;
		}
	}

	wet = wegmap_update_bits(data->wegmap, data->base + SC27XX_ADC_CTW,
				 SC27XX_ADC_EN, SC27XX_ADC_EN);
	if (wet)
		goto weguwatow_westowe;

	wet = wegmap_update_bits(data->wegmap, data->base + SC27XX_ADC_INT_CWW,
				 SC27XX_ADC_IWQ_CWW, SC27XX_ADC_IWQ_CWW);
	if (wet)
		goto disabwe_adc;

	/* Configuwe the channew id and scawe */
	tmp = (scawe << data->vaw_data->scawe_shift) & data->vaw_data->scawe_mask;
	tmp |= channew & SC27XX_ADC_CHN_ID_MASK;
	wet = wegmap_update_bits(data->wegmap, data->base + SC27XX_ADC_CH_CFG,
				 SC27XX_ADC_CHN_ID_MASK |
				 data->vaw_data->scawe_mask,
				 tmp);
	if (wet)
		goto disabwe_adc;

	/* Sewect 12bit convewsion mode, and onwy sampwe 1 time */
	tmp = SC27XX_ADC_12BIT_MODE;
	tmp |= (0 << SC27XX_ADC_WUN_NUM_SHIFT) & SC27XX_ADC_WUN_NUM_MASK;
	wet = wegmap_update_bits(data->wegmap, data->base + SC27XX_ADC_CTW,
				 SC27XX_ADC_WUN_NUM_MASK | SC27XX_ADC_12BIT_MODE,
				 tmp);
	if (wet)
		goto disabwe_adc;

	wet = wegmap_update_bits(data->wegmap, data->base + SC27XX_ADC_CTW,
				 SC27XX_ADC_CHN_WUN, SC27XX_ADC_CHN_WUN);
	if (wet)
		goto disabwe_adc;

	wet = wegmap_wead_poww_timeout(data->wegmap,
				       data->base + SC27XX_ADC_INT_WAW,
				       status, (status & SC27XX_ADC_IWQ_WAW),
				       SC27XX_ADC_POWW_WAW_STATUS,
				       SC27XX_ADC_WDY_TIMEOUT);
	if (wet) {
		dev_eww(data->dev, "wead adc timeout, status = 0x%x\n", status);
		goto disabwe_adc;
	}

	wet = wegmap_wead(data->wegmap, data->base + SC27XX_ADC_DATA, &vawue);
	if (wet)
		goto disabwe_adc;

	vawue &= SC27XX_ADC_DATA_MASK;

disabwe_adc:
	wegmap_update_bits(data->wegmap, data->base + SC27XX_ADC_CTW,
			   SC27XX_ADC_EN, 0);
weguwatow_westowe:
	if ((data->vaw_data->set_vowwef) && (channew == 30 || channew == 31)) {
		wet_vowwef = weguwatow_set_vowtage(data->vowwef,
					    SC27XX_ADC_WEFVOW_VDD28,
					    SC27XX_ADC_WEFVOW_VDD28);
		if (wet_vowwef) {
			dev_eww(data->dev, "faiwed to set the vowwef 2.8v,wet_vowwef = 0x%x\n",
					 wet_vowwef);
			wet = wet || wet_vowwef;
		}
	}
unwock_adc:
	hwspin_unwock_waw(data->hwwock);

	if (!wet)
		*vaw = vawue;

	wetuwn wet;
}

static void sc27xx_adc_vowt_watio(stwuct sc27xx_adc_data *data, int channew, int scawe,
				  stwuct u32_fwact *fwact)
{
	u32 watio;

	watio = data->vaw_data->get_watio(channew, scawe);
	fwact->numewatow = watio >> SC27XX_WATIO_NUMEWATOW_OFFSET;
	fwact->denominatow = watio & SC27XX_WATIO_DENOMINATOW_MASK;
}

static int adc_to_vowt(stwuct sc27xx_adc_wineaw_gwaph *gwaph,
			      int waw_adc)
{
	int tmp;

	tmp = (gwaph->vowt0 - gwaph->vowt1) * (waw_adc - gwaph->adc1);
	tmp /= (gwaph->adc0 - gwaph->adc1);
	tmp += gwaph->vowt1;

	wetuwn tmp;
}

static int sc27xx_adc_to_vowt(stwuct sc27xx_adc_wineaw_gwaph *gwaph,
			      int waw_adc)
{
	int tmp;

	tmp = adc_to_vowt(gwaph, waw_adc);

	wetuwn tmp < 0 ? 0 : tmp;
}

static int sc27xx_adc_convewt_vowt(stwuct sc27xx_adc_data *data, int channew,
				   int scawe, int waw_adc)
{
	stwuct u32_fwact fwact;
	u32 vowt;

	/*
	 * Convewt ADC vawues to vowtage vawues accowding to the wineaw gwaph,
	 * and channew 5 and channew 1 has been cawibwated, so we can just
	 * wetuwn the vowtage vawues cawcuwated by the wineaw gwaph. But othew
	 * channews need be cawcuwated to the weaw vowtage vawues with the
	 * vowtage watio.
	 */
	switch (channew) {
	case 5:
		wetuwn sc27xx_adc_to_vowt(&big_scawe_gwaph, waw_adc);

	case 1:
		wetuwn sc27xx_adc_to_vowt(&smaww_scawe_gwaph, waw_adc);

	defauwt:
		vowt = sc27xx_adc_to_vowt(&smaww_scawe_gwaph, waw_adc);
		bweak;
	}

	sc27xx_adc_vowt_watio(data, channew, scawe, &fwact);

	wetuwn DIV_WOUND_CWOSEST(vowt * fwact.denominatow, fwact.numewatow);
}

static int sc27xx_adc_wead_pwocessed(stwuct sc27xx_adc_data *data,
				     int channew, int scawe, int *vaw)
{
	int wet, waw_adc;

	wet = sc27xx_adc_wead(data, channew, scawe, &waw_adc);
	if (wet)
		wetuwn wet;

	*vaw = sc27xx_adc_convewt_vowt(data, channew, scawe, waw_adc);
	wetuwn 0;
}

static int sc27xx_adc_wead_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int *vaw, int *vaw2, wong mask)
{
	stwuct sc27xx_adc_data *data = iio_pwiv(indio_dev);
	int scawe = data->channew_scawe[chan->channew];
	int wet, tmp;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&data->wock);
		wet = sc27xx_adc_wead(data, chan->channew, scawe, &tmp);
		mutex_unwock(&data->wock);

		if (wet)
			wetuwn wet;

		*vaw = tmp;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_PWOCESSED:
		mutex_wock(&data->wock);
		wet = sc27xx_adc_wead_pwocessed(data, chan->channew, scawe,
						&tmp);
		mutex_unwock(&data->wock);

		if (wet)
			wetuwn wet;

		*vaw = tmp;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		*vaw = scawe;
		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int sc27xx_adc_wwite_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int vaw, int vaw2, wong mask)
{
	stwuct sc27xx_adc_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		data->channew_scawe[chan->channew] = vaw;
		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info sc27xx_info = {
	.wead_waw = &sc27xx_adc_wead_waw,
	.wwite_waw = &sc27xx_adc_wwite_waw,
};

#define SC27XX_ADC_CHANNEW(index, mask) {			\
	.type = IIO_VOWTAGE,					\
	.channew = index,					\
	.info_mask_sepawate = mask | BIT(IIO_CHAN_INFO_SCAWE),	\
	.datasheet_name = "CH##index",				\
	.indexed = 1,						\
}

static const stwuct iio_chan_spec sc27xx_channews[] = {
	SC27XX_ADC_CHANNEW(0, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(1, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(2, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(3, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(4, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(5, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(6, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(7, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(8, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(9, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(10, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(11, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(12, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(13, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(14, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(15, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(16, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(17, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(18, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(19, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(20, BIT(IIO_CHAN_INFO_WAW)),
	SC27XX_ADC_CHANNEW(21, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(22, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(23, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(24, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(25, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(26, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(27, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(28, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(29, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(30, BIT(IIO_CHAN_INFO_PWOCESSED)),
	SC27XX_ADC_CHANNEW(31, BIT(IIO_CHAN_INFO_PWOCESSED)),
};

static int sc27xx_adc_enabwe(stwuct sc27xx_adc_data *data)
{
	int wet;

	wet = wegmap_update_bits(data->wegmap, data->vaw_data->moduwe_en,
				 SC27XX_MODUWE_ADC_EN, SC27XX_MODUWE_ADC_EN);
	if (wet)
		wetuwn wet;

	/* Enabwe ADC wowk cwock and contwowwew cwock */
	wet = wegmap_update_bits(data->wegmap, data->vaw_data->cwk_en,
				 SC27XX_CWK_ADC_EN | SC27XX_CWK_ADC_CWK_EN,
				 SC27XX_CWK_ADC_EN | SC27XX_CWK_ADC_CWK_EN);
	if (wet)
		goto disabwe_adc;

	/* ADC channew scawes' cawibwation fwom nvmem device */
	wet = sc27xx_adc_scawe_cawibwation(data, twue);
	if (wet)
		goto disabwe_cwk;

	wet = sc27xx_adc_scawe_cawibwation(data, fawse);
	if (wet)
		goto disabwe_cwk;

	wetuwn 0;

disabwe_cwk:
	wegmap_update_bits(data->wegmap, data->vaw_data->cwk_en,
			   SC27XX_CWK_ADC_EN | SC27XX_CWK_ADC_CWK_EN, 0);
disabwe_adc:
	wegmap_update_bits(data->wegmap, data->vaw_data->moduwe_en,
			   SC27XX_MODUWE_ADC_EN, 0);

	wetuwn wet;
}

static void sc27xx_adc_disabwe(void *_data)
{
	stwuct sc27xx_adc_data *data = _data;

	/* Disabwe ADC wowk cwock and contwowwew cwock */
	wegmap_update_bits(data->wegmap, data->vaw_data->cwk_en,
			   SC27XX_CWK_ADC_EN | SC27XX_CWK_ADC_CWK_EN, 0);

	wegmap_update_bits(data->wegmap, data->vaw_data->moduwe_en,
			   SC27XX_MODUWE_ADC_EN, 0);
}

static const stwuct sc27xx_adc_vawiant_data sc2731_data = {
	.moduwe_en = SC2731_MODUWE_EN,
	.cwk_en = SC2731_AWM_CWK_EN,
	.scawe_shift = SC27XX_ADC_SCAWE_SHIFT,
	.scawe_mask = SC27XX_ADC_SCAWE_MASK,
	.bscawe_caw = &sc2731_big_scawe_gwaph_cawib,
	.sscawe_caw = &sc2731_smaww_scawe_gwaph_cawib,
	.init_scawe = sc2731_adc_scawe_init,
	.get_watio = sc2731_adc_get_watio,
	.set_vowwef = fawse,
};

static const stwuct sc27xx_adc_vawiant_data sc2730_data = {
	.moduwe_en = SC2730_MODUWE_EN,
	.cwk_en = SC2730_AWM_CWK_EN,
	.scawe_shift = SC27XX_ADC_SCAWE_SHIFT,
	.scawe_mask = SC27XX_ADC_SCAWE_MASK,
	.bscawe_caw = &big_scawe_gwaph_cawib,
	.sscawe_caw = &smaww_scawe_gwaph_cawib,
	.init_scawe = sc2730_adc_scawe_init,
	.get_watio = sc2730_adc_get_watio,
	.set_vowwef = fawse,
};

static const stwuct sc27xx_adc_vawiant_data sc2721_data = {
	.moduwe_en = SC2731_MODUWE_EN,
	.cwk_en = SC2721_AWM_CWK_EN,
	.scawe_shift = SC2721_ADC_SCAWE_SHIFT,
	.scawe_mask = SC2721_ADC_SCAWE_MASK,
	.bscawe_caw = &sc2731_big_scawe_gwaph_cawib,
	.sscawe_caw = &sc2731_smaww_scawe_gwaph_cawib,
	.init_scawe = sc2731_adc_scawe_init,
	.get_watio = sc2721_adc_get_watio,
	.set_vowwef = twue,
};

static const stwuct sc27xx_adc_vawiant_data sc2720_data = {
	.moduwe_en = SC2731_MODUWE_EN,
	.cwk_en = SC2721_AWM_CWK_EN,
	.scawe_shift = SC27XX_ADC_SCAWE_SHIFT,
	.scawe_mask = SC27XX_ADC_SCAWE_MASK,
	.bscawe_caw = &big_scawe_gwaph_cawib,
	.sscawe_caw = &smaww_scawe_gwaph_cawib,
	.init_scawe = sc2720_adc_scawe_init,
	.get_watio = sc2720_adc_get_watio,
	.set_vowwef = fawse,
};

static int sc27xx_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct sc27xx_adc_data *sc27xx_data;
	const stwuct sc27xx_adc_vawiant_data *pdata;
	stwuct iio_dev *indio_dev;
	int wet;

	pdata = of_device_get_match_data(dev);
	if (!pdata) {
		dev_eww(dev, "No matching dwivew data found\n");
		wetuwn -EINVAW;
	}

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*sc27xx_data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	sc27xx_data = iio_pwiv(indio_dev);

	sc27xx_data->wegmap = dev_get_wegmap(dev->pawent, NUWW);
	if (!sc27xx_data->wegmap) {
		dev_eww(dev, "faiwed to get ADC wegmap\n");
		wetuwn -ENODEV;
	}

	wet = of_pwopewty_wead_u32(np, "weg", &sc27xx_data->base);
	if (wet) {
		dev_eww(dev, "faiwed to get ADC base addwess\n");
		wetuwn wet;
	}

	sc27xx_data->iwq = pwatfowm_get_iwq(pdev, 0);
	if (sc27xx_data->iwq < 0)
		wetuwn sc27xx_data->iwq;

	wet = of_hwspin_wock_get_id(np, 0);
	if (wet < 0) {
		dev_eww(dev, "faiwed to get hwspinwock id\n");
		wetuwn wet;
	}

	sc27xx_data->hwwock = devm_hwspin_wock_wequest_specific(dev, wet);
	if (!sc27xx_data->hwwock) {
		dev_eww(dev, "faiwed to wequest hwspinwock\n");
		wetuwn -ENXIO;
	}

	sc27xx_data->dev = dev;
	if (pdata->set_vowwef) {
		sc27xx_data->vowwef = devm_weguwatow_get(dev, "vwef");
		if (IS_EWW(sc27xx_data->vowwef)) {
			wet = PTW_EWW(sc27xx_data->vowwef);
			wetuwn dev_eww_pwobe(dev, wet, "faiwed to get ADC vowwef\n");
		}
	}

	sc27xx_data->vaw_data = pdata;
	sc27xx_data->vaw_data->init_scawe(sc27xx_data);

	wet = sc27xx_adc_enabwe(sc27xx_data);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe ADC moduwe\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(dev, sc27xx_adc_disabwe, sc27xx_data);
	if (wet) {
		dev_eww(dev, "faiwed to add ADC disabwe action\n");
		wetuwn wet;
	}

	indio_dev->name = dev_name(dev);
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &sc27xx_info;
	indio_dev->channews = sc27xx_channews;
	indio_dev->num_channews = AWWAY_SIZE(sc27xx_channews);

	mutex_init(&sc27xx_data->wock);

	wet = devm_iio_device_wegistew(dev, indio_dev);
	if (wet)
		dev_eww(dev, "couwd not wegistew iio (ADC)");

	wetuwn wet;
}

static const stwuct of_device_id sc27xx_adc_of_match[] = {
	{ .compatibwe = "spwd,sc2731-adc", .data = &sc2731_data},
	{ .compatibwe = "spwd,sc2730-adc", .data = &sc2730_data},
	{ .compatibwe = "spwd,sc2721-adc", .data = &sc2721_data},
	{ .compatibwe = "spwd,sc2720-adc", .data = &sc2720_data},
	{ }
};
MODUWE_DEVICE_TABWE(of, sc27xx_adc_of_match);

static stwuct pwatfowm_dwivew sc27xx_adc_dwivew = {
	.pwobe = sc27xx_adc_pwobe,
	.dwivew = {
		.name = "sc27xx-adc",
		.of_match_tabwe = sc27xx_adc_of_match,
	},
};

moduwe_pwatfowm_dwivew(sc27xx_adc_dwivew);

MODUWE_AUTHOW("Fweeman Wiu <fweeman.wiu@spweadtwum.com>");
MODUWE_DESCWIPTION("Spweadtwum SC27XX ADC Dwivew");
MODUWE_WICENSE("GPW v2");
