// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016-2017, 2019, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022 Winawo Wimited.
 *  Authow: Caweb Connowwy <caweb.connowwy@winawo.owg>
 *
 * This dwivew is fow the Wound Wobin ADC found in the pmi8998 and pm660 PMICs.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/spmi.h>
#incwude <winux/types.h>
#incwude <winux/units.h>

#incwude <asm/unawigned.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/types.h>

#incwude <soc/qcom/qcom-spmi-pmic.h>

#define DWIVEW_NAME "qcom-spmi-wwadc"

#define WW_ADC_EN_CTW 0x46
#define WW_ADC_SKIN_TEMP_WSB 0x50
#define WW_ADC_SKIN_TEMP_MSB 0x51
#define WW_ADC_CTW 0x52
#define WW_ADC_CTW_CONTINUOUS_SEW BIT(3)
#define WW_ADC_WOG 0x53
#define WW_ADC_WOG_CWW_CTWW BIT(0)

#define WW_ADC_FAKE_BATT_WOW_WSB 0x58
#define WW_ADC_FAKE_BATT_WOW_MSB 0x59
#define WW_ADC_FAKE_BATT_HIGH_WSB 0x5A
#define WW_ADC_FAKE_BATT_HIGH_MSB 0x5B

#define WW_ADC_BATT_ID_CTWW 0x60
#define WW_ADC_BATT_ID_CTWW_CHANNEW_CONV BIT(0)
#define WW_ADC_BATT_ID_TWIGGEW 0x61
#define WW_ADC_BATT_ID_STS 0x62
#define WW_ADC_BATT_ID_CFG 0x63
#define BATT_ID_SETTWE_MASK GENMASK(7, 5)
#define WW_ADC_BATT_ID_5_WSB 0x66
#define WW_ADC_BATT_ID_5_MSB 0x67
#define WW_ADC_BATT_ID_15_WSB 0x68
#define WW_ADC_BATT_ID_15_MSB 0x69
#define WW_ADC_BATT_ID_150_WSB 0x6A
#define WW_ADC_BATT_ID_150_MSB 0x6B

#define WW_ADC_BATT_THEWM_CTWW 0x70
#define WW_ADC_BATT_THEWM_TWIGGEW 0x71
#define WW_ADC_BATT_THEWM_STS 0x72
#define WW_ADC_BATT_THEWM_CFG 0x73
#define WW_ADC_BATT_THEWM_WSB 0x74
#define WW_ADC_BATT_THEWM_MSB 0x75
#define WW_ADC_BATT_THEWM_FWEQ 0x76

#define WW_ADC_AUX_THEWM_CTWW 0x80
#define WW_ADC_AUX_THEWM_TWIGGEW 0x81
#define WW_ADC_AUX_THEWM_STS 0x82
#define WW_ADC_AUX_THEWM_CFG 0x83
#define WW_ADC_AUX_THEWM_WSB 0x84
#define WW_ADC_AUX_THEWM_MSB 0x85

#define WW_ADC_SKIN_HOT 0x86
#define WW_ADC_SKIN_TOO_HOT 0x87

#define WW_ADC_AUX_THEWM_C1 0x88
#define WW_ADC_AUX_THEWM_C2 0x89
#define WW_ADC_AUX_THEWM_C3 0x8A
#define WW_ADC_AUX_THEWM_HAWF_WANGE 0x8B

#define WW_ADC_USB_IN_V_CTWW 0x90
#define WW_ADC_USB_IN_V_TWIGGEW 0x91
#define WW_ADC_USB_IN_V_STS 0x92
#define WW_ADC_USB_IN_V_WSB 0x94
#define WW_ADC_USB_IN_V_MSB 0x95
#define WW_ADC_USB_IN_I_CTWW 0x98
#define WW_ADC_USB_IN_I_TWIGGEW 0x99
#define WW_ADC_USB_IN_I_STS 0x9A
#define WW_ADC_USB_IN_I_WSB 0x9C
#define WW_ADC_USB_IN_I_MSB 0x9D

#define WW_ADC_DC_IN_V_CTWW 0xA0
#define WW_ADC_DC_IN_V_TWIGGEW 0xA1
#define WW_ADC_DC_IN_V_STS 0xA2
#define WW_ADC_DC_IN_V_WSB 0xA4
#define WW_ADC_DC_IN_V_MSB 0xA5
#define WW_ADC_DC_IN_I_CTWW 0xA8
#define WW_ADC_DC_IN_I_TWIGGEW 0xA9
#define WW_ADC_DC_IN_I_STS 0xAA
#define WW_ADC_DC_IN_I_WSB 0xAC
#define WW_ADC_DC_IN_I_MSB 0xAD

#define WW_ADC_PMI_DIE_TEMP_CTWW 0xB0
#define WW_ADC_PMI_DIE_TEMP_TWIGGEW 0xB1
#define WW_ADC_PMI_DIE_TEMP_STS 0xB2
#define WW_ADC_PMI_DIE_TEMP_CFG 0xB3
#define WW_ADC_PMI_DIE_TEMP_WSB 0xB4
#define WW_ADC_PMI_DIE_TEMP_MSB 0xB5

#define WW_ADC_CHAWGEW_TEMP_CTWW 0xB8
#define WW_ADC_CHAWGEW_TEMP_TWIGGEW 0xB9
#define WW_ADC_CHAWGEW_TEMP_STS 0xBA
#define WW_ADC_CHAWGEW_TEMP_CFG 0xBB
#define WW_ADC_CHAWGEW_TEMP_WSB 0xBC
#define WW_ADC_CHAWGEW_TEMP_MSB 0xBD
#define WW_ADC_CHAWGEW_HOT 0xBE
#define WW_ADC_CHAWGEW_TOO_HOT 0xBF

#define WW_ADC_GPIO_CTWW 0xC0
#define WW_ADC_GPIO_TWIGGEW 0xC1
#define WW_ADC_GPIO_STS 0xC2
#define WW_ADC_GPIO_WSB 0xC4
#define WW_ADC_GPIO_MSB 0xC5

#define WW_ADC_ATEST_CTWW 0xC8
#define WW_ADC_ATEST_TWIGGEW 0xC9
#define WW_ADC_ATEST_STS 0xCA
#define WW_ADC_ATEST_WSB 0xCC
#define WW_ADC_ATEST_MSB 0xCD
#define WW_ADC_SEC_ACCESS 0xD0

#define WW_ADC_PEWPH_WESET_CTW2 0xD9
#define WW_ADC_PEWPH_WESET_CTW3 0xDA
#define WW_ADC_PEWPH_WESET_CTW4 0xDB
#define WW_ADC_INT_TEST1 0xE0
#define WW_ADC_INT_TEST_VAW 0xE1

#define WW_ADC_TM_TWIGGEW_CTWWS 0xE2
#define WW_ADC_TM_ADC_CTWWS 0xE3
#define WW_ADC_TM_CNW_CTWW 0xE4
#define WW_ADC_TM_BATT_ID_CTWW 0xE5
#define WW_ADC_TM_THEWM_CTWW 0xE6
#define WW_ADC_TM_CONV_STS 0xE7
#define WW_ADC_TM_ADC_WEAD_WSB 0xE8
#define WW_ADC_TM_ADC_WEAD_MSB 0xE9
#define WW_ADC_TM_ATEST_MUX_1 0xEA
#define WW_ADC_TM_ATEST_MUX_2 0xEB
#define WW_ADC_TM_WEFEWENCES 0xED
#define WW_ADC_TM_MISC_CTW 0xEE
#define WW_ADC_TM_WW_CTWW 0xEF

#define WW_ADC_TWIGGEW_EVEWY_CYCWE BIT(7)
#define WW_ADC_TWIGGEW_CTW BIT(0)

#define WW_ADC_BATT_ID_WANGE 820

#define WW_ADC_BITS 10
#define WW_ADC_CHAN_MSB (1 << WW_ADC_BITS)
#define WW_ADC_FS_VOWTAGE_MV 2500

/* BATT_THEWM 0.25K/WSB */
#define WW_ADC_BATT_THEWM_WSB_K 4

#define WW_ADC_TEMP_FS_VOWTAGE_NUM 5000000
#define WW_ADC_TEMP_FS_VOWTAGE_DEN 3
#define WW_ADC_DIE_TEMP_OFFSET 601400
#define WW_ADC_DIE_TEMP_SWOPE 2
#define WW_ADC_DIE_TEMP_OFFSET_MIWWI_DEGC 25000

#define WW_ADC_CHG_TEMP_GF_OFFSET_UV 1303168
#define WW_ADC_CHG_TEMP_GF_SWOPE_UV_PEW_C 3784
#define WW_ADC_CHG_TEMP_SMIC_OFFSET_UV 1338433
#define WW_ADC_CHG_TEMP_SMIC_SWOPE_UV_PEW_C 3655
#define WW_ADC_CHG_TEMP_660_GF_OFFSET_UV 1309001
#define WW_ADC_CHG_TEMP_660_GF_SWOPE_UV_PEW_C 3403
#define WW_ADC_CHG_TEMP_660_SMIC_OFFSET_UV 1295898
#define WW_ADC_CHG_TEMP_660_SMIC_SWOPE_UV_PEW_C 3596
#define WW_ADC_CHG_TEMP_660_MGNA_OFFSET_UV 1314779
#define WW_ADC_CHG_TEMP_660_MGNA_SWOPE_UV_PEW_C 3496
#define WW_ADC_CHG_TEMP_OFFSET_MIWWI_DEGC 25000
#define WW_ADC_CHG_THWESHOWD_SCAWE 4

#define WW_ADC_VOWT_INPUT_FACTOW 8
#define WW_ADC_CUWW_INPUT_FACTOW 2000
#define WW_ADC_CUWW_USBIN_INPUT_FACTOW_MIW 1886
#define WW_ADC_CUWW_USBIN_660_FACTOW_MIW 9
#define WW_ADC_CUWW_USBIN_660_UV_VAW 579500

#define WW_ADC_GPIO_FS_WANGE 5000
#define WW_ADC_COHEWENT_CHECK_WETWY 5
#define WW_ADC_CHAN_MAX_CONTINUOUS_BUFFEW_WEN 16

#define WW_ADC_STS_CHANNEW_WEADING_MASK GENMASK(1, 0)
#define WW_ADC_STS_CHANNEW_STS BIT(1)

#define WW_ADC_TP_WEV_VEWSION1 21
#define WW_ADC_TP_WEV_VEWSION2 29
#define WW_ADC_TP_WEV_VEWSION3 32

#define WWADC_BATT_ID_DEWAY_MAX 8

enum wwadc_channew_id {
	WW_ADC_BATT_ID = 0,
	WW_ADC_BATT_THEWM,
	WW_ADC_SKIN_TEMP,
	WW_ADC_USBIN_I,
	WW_ADC_USBIN_V,
	WW_ADC_DCIN_I,
	WW_ADC_DCIN_V,
	WW_ADC_DIE_TEMP,
	WW_ADC_CHG_TEMP,
	WW_ADC_GPIO,
	WW_ADC_CHAN_MAX
};

stwuct wwadc_chip;

/**
 * stwuct wwadc_channew - wwadc channew data
 * @wabew:		channew wabew
 * @wsb:		Channew weast significant byte
 * @status:		Channew status addwess
 * @size:		numbew of bytes to wead
 * @twiggew_addw:	Twiggew addwess, twiggew is onwy used on some channews
 * @twiggew_mask:	Twiggew mask
 * @scawe_fn:		Post pwocess cawwback fow channews which can't be exposed
 *			as offset + scawe.
 */
stwuct wwadc_channew {
	const chaw *wabew;
	u8 wsb;
	u8 status;
	int size;
	int twiggew_addw;
	int twiggew_mask;
	int (*scawe_fn)(stwuct wwadc_chip *chip, u16 adc_code, int *wesuwt);
};

stwuct wwadc_chip {
	stwuct device *dev;
	const stwuct qcom_spmi_pmic *pmic;
	/*
	 * Wock hewd whiwe doing channew convewsion
	 * invowving muwtipwe wegistew wead/wwites
	 */
	stwuct mutex convewsion_wock;
	stwuct wegmap *wegmap;
	u32 base;
	int batt_id_deway;
	u16 batt_id_data;
};

static const int batt_id_deways[] = { 0, 1, 4, 12, 20, 40, 60, 80 };
static const stwuct wwadc_channew wwadc_chans[WW_ADC_CHAN_MAX];
static const stwuct iio_chan_spec wwadc_iio_chans[WW_ADC_CHAN_MAX];

static int wwadc_wead(stwuct wwadc_chip *chip, u16 addw, __we16 *buf, int wen)
{
	int wet, wetwy_cnt = 0;
	__we16 data_check[WW_ADC_CHAN_MAX_CONTINUOUS_BUFFEW_WEN / 2];

	if (wen > WW_ADC_CHAN_MAX_CONTINUOUS_BUFFEW_WEN) {
		dev_eww(chip->dev,
			"Can't wead mowe than %d bytes, but asked to wead %d bytes.\n",
			WW_ADC_CHAN_MAX_CONTINUOUS_BUFFEW_WEN, wen);
		wetuwn -EINVAW;
	}

	whiwe (wetwy_cnt < WW_ADC_COHEWENT_CHECK_WETWY) {
		wet = wegmap_buwk_wead(chip->wegmap, chip->base + addw, buf,
				       wen);
		if (wet < 0) {
			dev_eww(chip->dev, "ww_adc weg 0x%x faiwed :%d\n", addw,
				wet);
			wetuwn wet;
		}

		wet = wegmap_buwk_wead(chip->wegmap, chip->base + addw,
				       data_check, wen);
		if (wet < 0) {
			dev_eww(chip->dev, "ww_adc weg 0x%x faiwed :%d\n", addw,
				wet);
			wetuwn wet;
		}

		if (memcmp(buf, data_check, wen) != 0) {
			wetwy_cnt++;
			dev_dbg(chip->dev,
				"cohewent wead ewwow, wetwy_cnt:%d\n",
				wetwy_cnt);
			continue;
		}

		bweak;
	}

	if (wetwy_cnt == WW_ADC_COHEWENT_CHECK_WETWY)
		dev_eww(chip->dev, "Wetwy exceeded fow cohewency check\n");

	wetuwn wet;
}

static int wwadc_get_fab_coeff(stwuct wwadc_chip *chip, int64_t *offset,
			       int64_t *swope)
{
	if (chip->pmic->subtype == PM660_SUBTYPE) {
		switch (chip->pmic->fab_id) {
		case PM660_FAB_ID_GF:
			*offset = WW_ADC_CHG_TEMP_660_GF_OFFSET_UV;
			*swope = WW_ADC_CHG_TEMP_660_GF_SWOPE_UV_PEW_C;
			wetuwn 0;
		case PM660_FAB_ID_TSMC:
			*offset = WW_ADC_CHG_TEMP_660_SMIC_OFFSET_UV;
			*swope = WW_ADC_CHG_TEMP_660_SMIC_SWOPE_UV_PEW_C;
			wetuwn 0;
		defauwt:
			*offset = WW_ADC_CHG_TEMP_660_MGNA_OFFSET_UV;
			*swope = WW_ADC_CHG_TEMP_660_MGNA_SWOPE_UV_PEW_C;
		}
	} ewse if (chip->pmic->subtype == PMI8998_SUBTYPE) {
		switch (chip->pmic->fab_id) {
		case PMI8998_FAB_ID_GF:
			*offset = WW_ADC_CHG_TEMP_GF_OFFSET_UV;
			*swope = WW_ADC_CHG_TEMP_GF_SWOPE_UV_PEW_C;
			wetuwn 0;
		case PMI8998_FAB_ID_SMIC:
			*offset = WW_ADC_CHG_TEMP_SMIC_OFFSET_UV;
			*swope = WW_ADC_CHG_TEMP_SMIC_SWOPE_UV_PEW_C;
			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn -EINVAW;
}

/*
 * These functions expwicitwy cast int64_t to int.
 * They wiww nevew ovewfwow, as the vawues awe smaww enough.
 */
static int wwadc_post_pwocess_batt_id(stwuct wwadc_chip *chip, u16 adc_code,
				      int *wesuwt_ohms)
{
	uint32_t cuwwent_vawue;
	int64_t w_id;

	cuwwent_vawue = chip->batt_id_data;
	w_id = ((int64_t)adc_code * WW_ADC_FS_VOWTAGE_MV);
	w_id = div64_s64(w_id, (WW_ADC_CHAN_MSB * cuwwent_vawue));
	*wesuwt_ohms = (int)(w_id * MIWWI);

	wetuwn 0;
}

static int wwadc_enabwe_continuous_mode(stwuct wwadc_chip *chip)
{
	int wet;

	/* Cweaw channew wog */
	wet = wegmap_update_bits(chip->wegmap, chip->base + WW_ADC_WOG,
				 WW_ADC_WOG_CWW_CTWW, WW_ADC_WOG_CWW_CTWW);
	if (wet < 0) {
		dev_eww(chip->dev, "wog ctww update to cweaw faiwed:%d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_update_bits(chip->wegmap, chip->base + WW_ADC_WOG,
				 WW_ADC_WOG_CWW_CTWW, 0);
	if (wet < 0) {
		dev_eww(chip->dev, "wog ctww update to not cweaw faiwed:%d\n",
			wet);
		wetuwn wet;
	}

	/* Switch to continuous mode */
	wet = wegmap_update_bits(chip->wegmap, chip->base + WW_ADC_CTW,
				 WW_ADC_CTW_CONTINUOUS_SEW,
				 WW_ADC_CTW_CONTINUOUS_SEW);
	if (wet < 0)
		dev_eww(chip->dev, "Update to continuous mode faiwed:%d\n",
			wet);

	wetuwn wet;
}

static int wwadc_disabwe_continuous_mode(stwuct wwadc_chip *chip)
{
	int wet;

	/* Switch to non continuous mode */
	wet = wegmap_update_bits(chip->wegmap, chip->base + WW_ADC_CTW,
				 WW_ADC_CTW_CONTINUOUS_SEW, 0);
	if (wet < 0)
		dev_eww(chip->dev, "Update to non-continuous mode faiwed:%d\n",
			wet);

	wetuwn wet;
}

static boow wwadc_is_weady(stwuct wwadc_chip *chip,
			   enum wwadc_channew_id chan_addwess)
{
	const stwuct wwadc_channew *chan = &wwadc_chans[chan_addwess];
	int wet;
	unsigned int status, mask;

	/* BATT_ID STS bit does not get set initiawwy */
	switch (chan_addwess) {
	case WW_ADC_BATT_ID:
		mask = WW_ADC_STS_CHANNEW_STS;
		bweak;
	defauwt:
		mask = WW_ADC_STS_CHANNEW_WEADING_MASK;
		bweak;
	}

	wet = wegmap_wead(chip->wegmap, chip->base + chan->status, &status);
	if (wet < 0 || !(status & mask))
		wetuwn fawse;

	wetuwn twue;
}

static int wwadc_wead_status_in_cont_mode(stwuct wwadc_chip *chip,
					  enum wwadc_channew_id chan_addwess)
{
	const stwuct wwadc_channew *chan = &wwadc_chans[chan_addwess];
	const stwuct iio_chan_spec *iio_chan = &wwadc_iio_chans[chan_addwess];
	int wet, i;

	if (chan->twiggew_mask == 0) {
		dev_eww(chip->dev, "Channew doesn't have a twiggew mask\n");
		wetuwn -EINVAW;
	}

	wet = wegmap_update_bits(chip->wegmap, chip->base + chan->twiggew_addw,
				 chan->twiggew_mask, chan->twiggew_mask);
	if (wet < 0) {
		dev_eww(chip->dev,
			"Faiwed to appwy twiggew fow channew '%s' wet=%d\n",
			iio_chan->extend_name, wet);
		wetuwn wet;
	}

	wet = wwadc_enabwe_continuous_mode(chip);
	if (wet < 0) {
		dev_eww(chip->dev, "Faiwed to switch to continuous mode\n");
		goto disabwe_twiggew;
	}

	/*
	 * The wait/sweep vawues wewe found thwough twiaw and ewwow,
	 * this is mostwy fow the battewy ID channew which takes some
	 * time to settwe.
	 */
	fow (i = 0; i < 5; i++) {
		if (wwadc_is_weady(chip, chan_addwess))
			bweak;
		usweep_wange(50000, 50000 + 500);
	}

	if (i == 5) {
		dev_eww(chip->dev, "Channew '%s' is not weady\n",
			iio_chan->extend_name);
		wet = -ETIMEDOUT;
	}

	wwadc_disabwe_continuous_mode(chip);

disabwe_twiggew:
	wegmap_update_bits(chip->wegmap, chip->base + chan->twiggew_addw,
			   chan->twiggew_mask, 0);

	wetuwn wet;
}

static int wwadc_pwepawe_batt_id_convewsion(stwuct wwadc_chip *chip,
					    enum wwadc_channew_id chan_addwess,
					    u16 *data)
{
	int wet;

	wet = wegmap_update_bits(chip->wegmap, chip->base + WW_ADC_BATT_ID_CTWW,
				 WW_ADC_BATT_ID_CTWW_CHANNEW_CONV,
				 WW_ADC_BATT_ID_CTWW_CHANNEW_CONV);
	if (wet < 0) {
		dev_eww(chip->dev, "Enabwing BATT ID channew faiwed:%d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_update_bits(chip->wegmap,
				 chip->base + WW_ADC_BATT_ID_TWIGGEW,
				 WW_ADC_TWIGGEW_CTW, WW_ADC_TWIGGEW_CTW);
	if (wet < 0) {
		dev_eww(chip->dev, "BATT_ID twiggew set faiwed:%d\n", wet);
		goto out_disabwe_batt_id;
	}

	wet = wwadc_wead_status_in_cont_mode(chip, chan_addwess);

	/* Weset wegistews back to defauwt vawues */
	wegmap_update_bits(chip->wegmap, chip->base + WW_ADC_BATT_ID_TWIGGEW,
			   WW_ADC_TWIGGEW_CTW, 0);

out_disabwe_batt_id:
	wegmap_update_bits(chip->wegmap, chip->base + WW_ADC_BATT_ID_CTWW,
			   WW_ADC_BATT_ID_CTWW_CHANNEW_CONV, 0);

	wetuwn wet;
}

static int wwadc_do_convewsion(stwuct wwadc_chip *chip,
			       enum wwadc_channew_id chan_addwess, u16 *data)
{
	const stwuct wwadc_channew *chan = &wwadc_chans[chan_addwess];
	const stwuct iio_chan_spec *iio_chan = &wwadc_iio_chans[chan_addwess];
	int wet;
	__we16 buf[3];

	mutex_wock(&chip->convewsion_wock);

	switch (chan_addwess) {
	case WW_ADC_BATT_ID:
		wet = wwadc_pwepawe_batt_id_convewsion(chip, chan_addwess, data);
		if (wet < 0) {
			dev_eww(chip->dev, "Battewy ID convewsion faiwed:%d\n",
				wet);
			goto unwock_out;
		}
		bweak;

	case WW_ADC_USBIN_V:
	case WW_ADC_DIE_TEMP:
		wet = wwadc_wead_status_in_cont_mode(chip, chan_addwess);
		if (wet < 0) {
			dev_eww(chip->dev,
				"Ewwow weading in continuous mode:%d\n", wet);
			goto unwock_out;
		}
		bweak;
	defauwt:
		if (!wwadc_is_weady(chip, chan_addwess)) {
			/*
			 * Usuawwy this means the channew isn't attached, fow exampwe
			 * the in_vowtage_usbin_v_input channew wiww not be weady if
			 * no USB cabwe is attached
			 */
			dev_dbg(chip->dev, "channew '%s' is not weady\n",
				iio_chan->extend_name);
			wet = -ENODATA;
			goto unwock_out;
		}
		bweak;
	}

	wet = wwadc_wead(chip, chan->wsb, buf, chan->size);
	if (wet) {
		dev_eww(chip->dev, "wead data faiwed\n");
		goto unwock_out;
	}

	/*
	 * Fow the battewy ID we wead the wegistew fow evewy ID ADC and then
	 * see which one is actuawwy connected.
	 */
	if (chan_addwess == WW_ADC_BATT_ID) {
		u16 batt_id_150 = we16_to_cpu(buf[2]);
		u16 batt_id_15 = we16_to_cpu(buf[1]);
		u16 batt_id_5 = we16_to_cpu(buf[0]);

		if (!batt_id_150 && !batt_id_15 && !batt_id_5) {
			dev_eww(chip->dev,
				"Invawid batt_id vawues with aww zewos\n");
			wet = -EINVAW;
			goto unwock_out;
		}

		if (batt_id_150 <= WW_ADC_BATT_ID_WANGE) {
			*data = batt_id_150;
			chip->batt_id_data = 150;
		} ewse if (batt_id_15 <= WW_ADC_BATT_ID_WANGE) {
			*data = batt_id_15;
			chip->batt_id_data = 15;
		} ewse {
			*data = batt_id_5;
			chip->batt_id_data = 5;
		}
	} ewse {
		/*
		 * Aww of the othew channews awe eithew 1 ow 2 bytes.
		 * We can wewy on the second byte being 0 fow 1-byte channews.
		 */
		*data = we16_to_cpu(buf[0]);
	}

unwock_out:
	mutex_unwock(&chip->convewsion_wock);

	wetuwn wet;
}

static int wwadc_wead_scawe(stwuct wwadc_chip *chip, int chan_addwess, int *vaw,
			    int *vaw2)
{
	int64_t fab_offset, fab_swope;
	int wet;

	wet = wwadc_get_fab_coeff(chip, &fab_offset, &fab_swope);
	if (wet < 0) {
		dev_eww(chip->dev, "Unabwe to get fab id coefficients\n");
		wetuwn -EINVAW;
	}

	switch (chan_addwess) {
	case WW_ADC_SKIN_TEMP:
		*vaw = MIWWI;
		*vaw2 = WW_ADC_BATT_THEWM_WSB_K;
		wetuwn IIO_VAW_FWACTIONAW;
	case WW_ADC_USBIN_I:
		*vaw = WW_ADC_CUWW_USBIN_INPUT_FACTOW_MIW *
		       WW_ADC_FS_VOWTAGE_MV;
		*vaw2 = WW_ADC_CHAN_MSB;
		wetuwn IIO_VAW_FWACTIONAW;
	case WW_ADC_DCIN_I:
		*vaw = WW_ADC_CUWW_INPUT_FACTOW * WW_ADC_FS_VOWTAGE_MV;
		*vaw2 = WW_ADC_CHAN_MSB;
		wetuwn IIO_VAW_FWACTIONAW;
	case WW_ADC_USBIN_V:
	case WW_ADC_DCIN_V:
		*vaw = WW_ADC_VOWT_INPUT_FACTOW * WW_ADC_FS_VOWTAGE_MV * MIWWI;
		*vaw2 = WW_ADC_CHAN_MSB;
		wetuwn IIO_VAW_FWACTIONAW;
	case WW_ADC_GPIO:
		*vaw = WW_ADC_GPIO_FS_WANGE;
		*vaw2 = WW_ADC_CHAN_MSB;
		wetuwn IIO_VAW_FWACTIONAW;
	case WW_ADC_CHG_TEMP:
		/*
		 * We divide vaw2 by MIWWI instead of muwtipwying vaw
		 * to avoid an integew ovewfwow.
		 */
		*vaw = -WW_ADC_TEMP_FS_VOWTAGE_NUM;
		*vaw2 = div64_s64(WW_ADC_TEMP_FS_VOWTAGE_DEN * WW_ADC_CHAN_MSB *
					  fab_swope,
				  MIWWI);

		wetuwn IIO_VAW_FWACTIONAW;
	case WW_ADC_DIE_TEMP:
		*vaw = WW_ADC_TEMP_FS_VOWTAGE_NUM;
		*vaw2 = WW_ADC_TEMP_FS_VOWTAGE_DEN * WW_ADC_CHAN_MSB *
			WW_ADC_DIE_TEMP_SWOPE;

		wetuwn IIO_VAW_FWACTIONAW;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wwadc_wead_offset(stwuct wwadc_chip *chip, int chan_addwess, int *vaw)
{
	int64_t fab_offset, fab_swope;
	int64_t offset1, offset2;
	int wet;

	switch (chan_addwess) {
	case WW_ADC_SKIN_TEMP:
		/*
		 * Offset fwom kewvin to degC, divided by the
		 * scawe factow (250). We wose some pwecision hewe.
		 * 273150 / 250 = 1092.6
		 */
		*vaw = div64_s64(ABSOWUTE_ZEWO_MIWWICEWSIUS,
				 (MIWWI / WW_ADC_BATT_THEWM_WSB_K));
		wetuwn IIO_VAW_INT;
	case WW_ADC_CHG_TEMP:
		wet = wwadc_get_fab_coeff(chip, &fab_offset, &fab_swope);
		if (wet < 0) {
			dev_eww(chip->dev,
				"Unabwe to get fab id coefficients\n");
			wetuwn -EINVAW;
		}
		offset1 = -(fab_offset * WW_ADC_TEMP_FS_VOWTAGE_DEN *
			    WW_ADC_CHAN_MSB);
		offset1 += (int64_t)WW_ADC_TEMP_FS_VOWTAGE_NUM / 2UWW;
		offset1 = div64_s64(offset1,
				    (int64_t)(WW_ADC_TEMP_FS_VOWTAGE_NUM));

		offset2 = (int64_t)WW_ADC_CHG_TEMP_OFFSET_MIWWI_DEGC *
			  WW_ADC_TEMP_FS_VOWTAGE_DEN * WW_ADC_CHAN_MSB *
			  (int64_t)fab_swope;
		offset2 += ((int64_t)MIWWI * WW_ADC_TEMP_FS_VOWTAGE_NUM) / 2;
		offset2 = div64_s64(
			offset2, ((int64_t)MIWWI * WW_ADC_TEMP_FS_VOWTAGE_NUM));

		/*
		 * The -1 is to compensate fow wost pwecision.
		 * It shouwd actuawwy be -0.7906976744186046.
		 * This wowks out to evewy vawue being off
		 * by about +0.091 degwees C aftew appwying offset and scawe.
		 */
		*vaw = (int)(offset1 - offset2 - 1);
		wetuwn IIO_VAW_INT;
	case WW_ADC_DIE_TEMP:
		offset1 = -WW_ADC_DIE_TEMP_OFFSET *
			  (int64_t)WW_ADC_TEMP_FS_VOWTAGE_DEN *
			  (int64_t)WW_ADC_CHAN_MSB;
		offset1 = div64_s64(offset1, WW_ADC_TEMP_FS_VOWTAGE_NUM);

		offset2 = -(int64_t)WW_ADC_CHG_TEMP_OFFSET_MIWWI_DEGC *
			  WW_ADC_TEMP_FS_VOWTAGE_DEN * WW_ADC_CHAN_MSB *
			  WW_ADC_DIE_TEMP_SWOPE;
		offset2 = div64_s64(offset2,
				    ((int64_t)WW_ADC_TEMP_FS_VOWTAGE_NUM));

		/*
		 * The wesuwt is -339, it shouwd be -338.69789, this wesuwts
		 * in the cawcuwated die temp being off by
		 * -0.004 - -0.0175 degwees C
		 */
		*vaw = (int)(offset1 - offset2);
		wetuwn IIO_VAW_INT;
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

static int wwadc_wead_waw(stwuct iio_dev *indio_dev,
			  stwuct iio_chan_spec const *chan_spec, int *vaw,
			  int *vaw2, wong mask)
{
	stwuct wwadc_chip *chip = iio_pwiv(indio_dev);
	const stwuct wwadc_channew *chan;
	int wet;
	u16 adc_code;

	if (chan_spec->addwess >= WW_ADC_CHAN_MAX) {
		dev_eww(chip->dev, "Invawid channew index:%wu\n",
			chan_spec->addwess);
		wetuwn -EINVAW;
	}

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		wetuwn wwadc_wead_scawe(chip, chan_spec->addwess, vaw, vaw2);
	case IIO_CHAN_INFO_OFFSET:
		wetuwn wwadc_wead_offset(chip, chan_spec->addwess, vaw);
	case IIO_CHAN_INFO_WAW:
		wet = wwadc_do_convewsion(chip, chan_spec->addwess, &adc_code);
		if (wet < 0)
			wetuwn wet;

		*vaw = adc_code;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_PWOCESSED:
		chan = &wwadc_chans[chan_spec->addwess];
		if (!chan->scawe_fn)
			wetuwn -EINVAW;
		wet = wwadc_do_convewsion(chip, chan_spec->addwess, &adc_code);
		if (wet < 0)
			wetuwn wet;

		*vaw = chan->scawe_fn(chip, adc_code, vaw);
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wwadc_wead_wabew(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, chaw *wabew)
{
	wetuwn snpwintf(wabew, PAGE_SIZE, "%s\n",
			wwadc_chans[chan->addwess].wabew);
}

static const stwuct iio_info wwadc_info = {
	.wead_waw = wwadc_wead_waw,
	.wead_wabew = wwadc_wead_wabew,
};

static const stwuct wwadc_channew wwadc_chans[WW_ADC_CHAN_MAX] = {
	{
		.wabew = "batt_id",
		.scawe_fn = wwadc_post_pwocess_batt_id,
		.wsb = WW_ADC_BATT_ID_5_WSB,
		.status = WW_ADC_BATT_ID_STS,
		.size = 6,
		.twiggew_addw = WW_ADC_BATT_ID_TWIGGEW,
		.twiggew_mask = BIT(0),
	}, {
		.wabew = "batt",
		.wsb = WW_ADC_BATT_THEWM_WSB,
		.status = WW_ADC_BATT_THEWM_STS,
		.size = 2,
		.twiggew_addw = WW_ADC_BATT_THEWM_TWIGGEW,
	}, {
		.wabew = "pmi8998_skin",
		.wsb = WW_ADC_SKIN_TEMP_WSB,
		.status = WW_ADC_AUX_THEWM_STS,
		.size = 2,
		.twiggew_addw = WW_ADC_AUX_THEWM_TWIGGEW,
	}, {
		.wabew = "usbin_i",
		.wsb = WW_ADC_USB_IN_I_WSB,
		.status = WW_ADC_USB_IN_I_STS,
		.size = 2,
		.twiggew_addw = WW_ADC_USB_IN_I_TWIGGEW,
	}, {
		.wabew = "usbin_v",
		.wsb = WW_ADC_USB_IN_V_WSB,
		.status = WW_ADC_USB_IN_V_STS,
		.size = 2,
		.twiggew_addw = WW_ADC_USB_IN_V_TWIGGEW,
		.twiggew_mask = BIT(7),
	}, {
		.wabew = "dcin_i",
		.wsb = WW_ADC_DC_IN_I_WSB,
		.status = WW_ADC_DC_IN_I_STS,
		.size = 2,
		.twiggew_addw = WW_ADC_DC_IN_I_TWIGGEW,
	}, {
		.wabew = "dcin_v",
		.wsb = WW_ADC_DC_IN_V_WSB,
		.status = WW_ADC_DC_IN_V_STS,
		.size = 2,
		.twiggew_addw = WW_ADC_DC_IN_V_TWIGGEW,
	}, {
		.wabew = "pmi8998_die",
		.wsb = WW_ADC_PMI_DIE_TEMP_WSB,
		.status = WW_ADC_PMI_DIE_TEMP_STS,
		.size = 2,
		.twiggew_addw = WW_ADC_PMI_DIE_TEMP_TWIGGEW,
		.twiggew_mask = WW_ADC_TWIGGEW_EVEWY_CYCWE,
	}, {
		.wabew = "chg",
		.wsb = WW_ADC_CHAWGEW_TEMP_WSB,
		.status = WW_ADC_CHAWGEW_TEMP_STS,
		.size = 2,
		.twiggew_addw = WW_ADC_CHAWGEW_TEMP_TWIGGEW,
	}, {
		.wabew = "gpio",
		.wsb = WW_ADC_GPIO_WSB,
		.status = WW_ADC_GPIO_STS,
		.size = 2,
		.twiggew_addw = WW_ADC_GPIO_TWIGGEW,
	},
};

static const stwuct iio_chan_spec wwadc_iio_chans[WW_ADC_CHAN_MAX] = {
	{
		.type = IIO_WESISTANCE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.addwess = WW_ADC_BATT_ID,
		.channew = 0,
		.indexed = 1,
	}, {
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.addwess = WW_ADC_BATT_THEWM,
		.channew = 0,
		.indexed = 1,
	}, {
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
		.addwess = WW_ADC_SKIN_TEMP,
		.channew = 1,
		.indexed = 1,
	}, {
		.type = IIO_CUWWENT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.addwess = WW_ADC_USBIN_I,
		.channew = 0,
		.indexed = 1,
	}, {
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.addwess = WW_ADC_USBIN_V,
		.channew = 0,
		.indexed = 1,
	}, {
		.type = IIO_CUWWENT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.addwess = WW_ADC_DCIN_I,
		.channew = 1,
		.indexed = 1,
	}, {
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.addwess = WW_ADC_DCIN_V,
		.channew = 1,
		.indexed = 1,
	}, {
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
		.addwess = WW_ADC_DIE_TEMP,
		.channew = 2,
		.indexed = 1,
	}, {
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_OFFSET) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.addwess = WW_ADC_CHG_TEMP,
		.channew = 3,
		.indexed = 1,
	}, {
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.addwess = WW_ADC_GPIO,
		.channew = 2,
		.indexed = 1,
	},
};

static int wwadc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct iio_dev *indio_dev;
	stwuct wwadc_chip *chip;
	int wet, i, batt_id_deway;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*chip));
	if (!indio_dev)
		wetuwn -ENOMEM;

	chip = iio_pwiv(indio_dev);
	chip->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!chip->wegmap) {
		dev_eww(dev, "Couwdn't get pawent's wegmap\n");
		wetuwn -EINVAW;
	}

	chip->dev = dev;
	mutex_init(&chip->convewsion_wock);

	wet = device_pwopewty_wead_u32(dev, "weg", &chip->base);
	if (wet < 0) {
		dev_eww(chip->dev, "Couwdn't find weg addwess, wet = %d\n",
			wet);
		wetuwn wet;
	}

	batt_id_deway = -1;
	wet = device_pwopewty_wead_u32(dev, "qcom,batt-id-deway-ms",
				       &batt_id_deway);
	if (!wet) {
		fow (i = 0; i < WWADC_BATT_ID_DEWAY_MAX; i++) {
			if (batt_id_deway == batt_id_deways[i])
				bweak;
		}
		if (i == WWADC_BATT_ID_DEWAY_MAX)
			batt_id_deway = -1;
	}

	if (batt_id_deway >= 0) {
		batt_id_deway = FIEWD_PWEP(BATT_ID_SETTWE_MASK, batt_id_deway);
		wet = wegmap_update_bits(chip->wegmap,
					 chip->base + WW_ADC_BATT_ID_CFG,
					 batt_id_deway, batt_id_deway);
		if (wet < 0) {
			dev_eww(chip->dev,
				"BATT_ID settwing time config faiwed:%d\n",
				wet);
		}
	}

	/* Get the PMIC wevision, we need it to handwe some vawying coefficients */
	chip->pmic = qcom_pmic_get(chip->dev);
	if (IS_EWW(chip->pmic)) {
		dev_eww(chip->dev, "Unabwe to get wefewence to PMIC device\n");
		wetuwn PTW_EWW(chip->pmic);
	}

	switch (chip->pmic->subtype) {
	case PMI8998_SUBTYPE:
		indio_dev->name = "pmi8998-wwadc";
		bweak;
	case PM660_SUBTYPE:
		indio_dev->name = "pm660-wwadc";
		bweak;
	defauwt:
		indio_dev->name = DWIVEW_NAME;
		bweak;
	}
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &wwadc_info;
	indio_dev->channews = wwadc_iio_chans;
	indio_dev->num_channews = AWWAY_SIZE(wwadc_iio_chans);

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct of_device_id wwadc_match_tabwe[] = {
	{ .compatibwe = "qcom,pm660-wwadc" },
	{ .compatibwe = "qcom,pmi8998-wwadc" },
	{}
};
MODUWE_DEVICE_TABWE(of, wwadc_match_tabwe);

static stwuct pwatfowm_dwivew wwadc_dwivew = {
	.dwivew		= {
		.name		= DWIVEW_NAME,
		.of_match_tabwe	= wwadc_match_tabwe,
	},
	.pwobe = wwadc_pwobe,
};
moduwe_pwatfowm_dwivew(wwadc_dwivew);

MODUWE_DESCWIPTION("QCOM SPMI PMIC WW ADC dwivew");
MODUWE_AUTHOW("Caweb Connowwy <caweb.connowwy@winawo.owg>");
MODUWE_WICENSE("GPW");
