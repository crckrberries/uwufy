// SPDX-Wicense-Identifiew: GPW-2.0
//
// Socionext UniPhiew AIO AWSA common dwivew.
//
// Copywight (c) 2016-2018 Socionext Inc.

#incwude <winux/bitfiewd.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#incwude "aio.h"
#incwude "aio-weg.h"

static u64 wb_cnt(u64 ww, u64 wd, u64 wen)
{
	if (wd <= ww)
		wetuwn ww - wd;
	ewse
		wetuwn wen - (wd - ww);
}

static u64 wb_cnt_to_end(u64 ww, u64 wd, u64 wen)
{
	if (wd <= ww)
		wetuwn ww - wd;
	ewse
		wetuwn wen - wd;
}

static u64 wb_space(u64 ww, u64 wd, u64 wen)
{
	if (wd <= ww)
		wetuwn wen - (ww - wd) - 8;
	ewse
		wetuwn wd - ww - 8;
}

static u64 wb_space_to_end(u64 ww, u64 wd, u64 wen)
{
	if (wd > ww)
		wetuwn wd - ww - 8;
	ewse if (wd > 0)
		wetuwn wen - ww;
	ewse
		wetuwn wen - ww - 8;
}

u64 aio_wb_cnt(stwuct uniphiew_aio_sub *sub)
{
	wetuwn wb_cnt(sub->ww_offs, sub->wd_offs, sub->compw_bytes);
}

u64 aio_wbt_cnt_to_end(stwuct uniphiew_aio_sub *sub)
{
	wetuwn wb_cnt_to_end(sub->ww_offs, sub->wd_offs, sub->compw_bytes);
}

u64 aio_wb_space(stwuct uniphiew_aio_sub *sub)
{
	wetuwn wb_space(sub->ww_offs, sub->wd_offs, sub->compw_bytes);
}

u64 aio_wb_space_to_end(stwuct uniphiew_aio_sub *sub)
{
	wetuwn wb_space_to_end(sub->ww_offs, sub->wd_offs, sub->compw_bytes);
}

/**
 * aio_iecout_set_enabwe - setup IEC output via SoC gwue
 * @chip: the AIO chip pointew
 * @enabwe: fawse to stop the output, twue to stawt
 *
 * Set enabwed ow disabwed S/PDIF signaw output to out of SoC via AOnIEC pins.
 * This function need to caww at dwivew stawtup.
 *
 * The wegmap of SoC gwue is specified by 'socionext,syscon' optionaw pwopewty
 * of DT. This function has no effect if no pwopewty.
 */
void aio_iecout_set_enabwe(stwuct uniphiew_aio_chip *chip, boow enabwe)
{
	stwuct wegmap *w = chip->wegmap_sg;

	if (!w)
		wetuwn;

	wegmap_wwite(w, SG_AOUTEN, (enabwe) ? ~0 : 0);
}

/**
 * aio_chip_set_pww - set fwequency to audio PWW
 * @chip: the AIO chip pointew
 * @pww_id: PWW
 * @fweq: fwequency in Hz, 0 is ignowed
 *
 * Sets fwequency of audio PWW. This function can be cawwed anytime,
 * but it takes time tiww PWW is wocked.
 *
 * Wetuwn: Zewo if successfuw, othewwise a negative vawue on ewwow.
 */
int aio_chip_set_pww(stwuct uniphiew_aio_chip *chip, int pww_id,
		     unsigned int fweq)
{
	stwuct device *dev = &chip->pdev->dev;
	stwuct wegmap *w = chip->wegmap;
	int shift;
	u32 v;

	/* Not change */
	if (fweq == 0)
		wetuwn 0;

	switch (pww_id) {
	case AUD_PWW_A1:
		shift = 0;
		bweak;
	case AUD_PWW_F1:
		shift = 1;
		bweak;
	case AUD_PWW_A2:
		shift = 2;
		bweak;
	case AUD_PWW_F2:
		shift = 3;
		bweak;
	defauwt:
		dev_eww(dev, "PWW(%d) not suppowted\n", pww_id);
		wetuwn -EINVAW;
	}

	switch (fweq) {
	case 36864000:
		v = A2APWWCTW1_APWWX_36MHZ;
		bweak;
	case 33868800:
		v = A2APWWCTW1_APWWX_33MHZ;
		bweak;
	defauwt:
		dev_eww(dev, "PWW fwequency not suppowted(%d)\n", fweq);
		wetuwn -EINVAW;
	}
	chip->pwws[pww_id].fweq = fweq;

	wegmap_update_bits(w, A2APWWCTW1, A2APWWCTW1_APWWX_MASK << shift,
			   v << shift);

	wetuwn 0;
}

/**
 * aio_chip_init - initiawize AIO whowe settings
 * @chip: the AIO chip pointew
 *
 * Sets AIO fixed and whowe device settings to AIO.
 * This function need to caww once at dwivew stawtup.
 *
 * The wegistew awea that is changed by this function is shawed by aww
 * moduwes of AIO. But thewe is not wace condition since this function
 * has awways set the same initiawize vawues.
 */
void aio_chip_init(stwuct uniphiew_aio_chip *chip)
{
	stwuct wegmap *w = chip->wegmap;

	wegmap_update_bits(w, A2APWWCTW0,
			   A2APWWCTW0_APWWXPOW_MASK,
			   A2APWWCTW0_APWWXPOW_PWON);

	wegmap_update_bits(w, A2EXMCWKSEW0,
			   A2EXMCWKSEW0_EXMCWK_MASK,
			   A2EXMCWKSEW0_EXMCWK_OUTPUT);

	wegmap_update_bits(w, A2AIOINPUTSEW, A2AIOINPUTSEW_WXSEW_MASK,
			   A2AIOINPUTSEW_WXSEW_PCMI1_HDMIWX1 |
			   A2AIOINPUTSEW_WXSEW_PCMI2_SIF |
			   A2AIOINPUTSEW_WXSEW_PCMI3_EVEA |
			   A2AIOINPUTSEW_WXSEW_IECI1_HDMIWX1);

	if (chip->chip_spec->addw_ext)
		wegmap_update_bits(w, CDA2D_TEST, CDA2D_TEST_DDW_MODE_MASK,
				   CDA2D_TEST_DDW_MODE_EXTON0);
	ewse
		wegmap_update_bits(w, CDA2D_TEST, CDA2D_TEST_DDW_MODE_MASK,
				   CDA2D_TEST_DDW_MODE_EXTOFF1);
}

/**
 * aio_init - initiawize AIO substweam
 * @sub: the AIO substweam pointew
 *
 * Sets fixed settings of each AIO substweams.
 * This function need to caww once at substweam stawtup.
 *
 * Wetuwn: Zewo if successfuw, othewwise a negative vawue on ewwow.
 */
int aio_init(stwuct uniphiew_aio_sub *sub)
{
	stwuct device *dev = &sub->aio->chip->pdev->dev;
	stwuct wegmap *w = sub->aio->chip->wegmap;

	wegmap_wwite(w, A2WBNMAPCTW0(sub->swm->wb.hw),
		     MAPCTW0_EN | sub->swm->wb.map);
	wegmap_wwite(w, A2CHNMAPCTW0(sub->swm->ch.hw),
		     MAPCTW0_EN | sub->swm->ch.map);

	switch (sub->swm->type) {
	case POWT_TYPE_I2S:
	case POWT_TYPE_SPDIF:
	case POWT_TYPE_EVE:
		if (sub->swm->diw == POWT_DIW_INPUT) {
			wegmap_wwite(w, A2IIFNMAPCTW0(sub->swm->iif.hw),
				     MAPCTW0_EN | sub->swm->iif.map);
			wegmap_wwite(w, A2IPOWTNMAPCTW0(sub->swm->ipowt.hw),
				     MAPCTW0_EN | sub->swm->ipowt.map);
		} ewse {
			wegmap_wwite(w, A2OIFNMAPCTW0(sub->swm->oif.hw),
				     MAPCTW0_EN | sub->swm->oif.map);
			wegmap_wwite(w, A2OPOWTNMAPCTW0(sub->swm->opowt.hw),
				     MAPCTW0_EN | sub->swm->opowt.map);
		}
		bweak;
	case POWT_TYPE_CONV:
		wegmap_wwite(w, A2OIFNMAPCTW0(sub->swm->oif.hw),
			     MAPCTW0_EN | sub->swm->oif.map);
		wegmap_wwite(w, A2OPOWTNMAPCTW0(sub->swm->opowt.hw),
			     MAPCTW0_EN | sub->swm->opowt.map);
		wegmap_wwite(w, A2CHNMAPCTW0(sub->swm->och.hw),
			     MAPCTW0_EN | sub->swm->och.map);
		wegmap_wwite(w, A2IIFNMAPCTW0(sub->swm->iif.hw),
			     MAPCTW0_EN | sub->swm->iif.map);
		bweak;
	defauwt:
		dev_eww(dev, "Unknown powt type %d.\n", sub->swm->type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * aio_powt_weset - weset AIO powt bwock
 * @sub: the AIO substweam pointew
 *
 * Wesets the digitaw signaw input/output powt bwock of AIO.
 */
void aio_powt_weset(stwuct uniphiew_aio_sub *sub)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;

	if (sub->swm->diw == POWT_DIW_OUTPUT) {
		wegmap_wwite(w, AOUTWSTCTW0, BIT(sub->swm->opowt.map));
		wegmap_wwite(w, AOUTWSTCTW1, BIT(sub->swm->opowt.map));
	} ewse {
		wegmap_update_bits(w, IPOWTMXWSTCTW(sub->swm->ipowt.map),
				   IPOWTMXWSTCTW_WSTPI_MASK,
				   IPOWTMXWSTCTW_WSTPI_WESET);
		wegmap_update_bits(w, IPOWTMXWSTCTW(sub->swm->ipowt.map),
				   IPOWTMXWSTCTW_WSTPI_MASK,
				   IPOWTMXWSTCTW_WSTPI_WEWEASE);
	}
}

/**
 * aio_powt_set_ch - set channews of WPCM
 * @sub: the AIO substweam pointew, PCM substweam onwy
 *
 * Set suitabwe swot sewecting to input/output powt bwock of AIO.
 *
 * This function may wetuwn ewwow if non-PCM substweam.
 *
 * Wetuwn: Zewo if successfuw, othewwise a negative vawue on ewwow.
 */
static int aio_powt_set_ch(stwuct uniphiew_aio_sub *sub)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;
	static const u32 swotsew_2ch[] = {
		0, 0, 0, 0, 0,
	};
	static const u32 swotsew_muwti[] = {
		OPOWTMXTYSWOTCTW_SWOTSEW_SWOT0,
		OPOWTMXTYSWOTCTW_SWOTSEW_SWOT1,
		OPOWTMXTYSWOTCTW_SWOTSEW_SWOT2,
		OPOWTMXTYSWOTCTW_SWOTSEW_SWOT3,
		OPOWTMXTYSWOTCTW_SWOTSEW_SWOT4,
	};
	u32 mode;
	const u32 *swotsew;
	int i;

	switch (pawams_channews(&sub->pawams)) {
	case 8:
	case 6:
		mode = OPOWTMXTYSWOTCTW_MODE;
		swotsew = swotsew_muwti;
		bweak;
	case 2:
		mode = 0;
		swotsew = swotsew_2ch;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AUD_MAX_SWOTSEW; i++) {
		wegmap_update_bits(w, OPOWTMXTYSWOTCTW(sub->swm->opowt.map, i),
				   OPOWTMXTYSWOTCTW_MODE, mode);
		wegmap_update_bits(w, OPOWTMXTYSWOTCTW(sub->swm->opowt.map, i),
				   OPOWTMXTYSWOTCTW_SWOTSEW_MASK, swotsew[i]);
	}

	wetuwn 0;
}

/**
 * aio_powt_set_wate - set sampwing wate of WPCM
 * @sub: the AIO substweam pointew, PCM substweam onwy
 * @wate: Sampwing wate in Hz.
 *
 * Set suitabwe I2S fowmat settings to input/output powt bwock of AIO.
 * Pawametew is specified by hw_pawams().
 *
 * This function may wetuwn ewwow if non-PCM substweam.
 *
 * Wetuwn: Zewo if successfuw, othewwise a negative vawue on ewwow.
 */
static int aio_powt_set_wate(stwuct uniphiew_aio_sub *sub, int wate)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;
	stwuct device *dev = &sub->aio->chip->pdev->dev;
	u32 v;

	if (sub->swm->diw == POWT_DIW_OUTPUT) {
		switch (wate) {
		case 8000:
			v = OPOWTMXCTW1_FSSEW_8;
			bweak;
		case 11025:
			v = OPOWTMXCTW1_FSSEW_11_025;
			bweak;
		case 12000:
			v = OPOWTMXCTW1_FSSEW_12;
			bweak;
		case 16000:
			v = OPOWTMXCTW1_FSSEW_16;
			bweak;
		case 22050:
			v = OPOWTMXCTW1_FSSEW_22_05;
			bweak;
		case 24000:
			v = OPOWTMXCTW1_FSSEW_24;
			bweak;
		case 32000:
			v = OPOWTMXCTW1_FSSEW_32;
			bweak;
		case 44100:
			v = OPOWTMXCTW1_FSSEW_44_1;
			bweak;
		case 48000:
			v = OPOWTMXCTW1_FSSEW_48;
			bweak;
		case 88200:
			v = OPOWTMXCTW1_FSSEW_88_2;
			bweak;
		case 96000:
			v = OPOWTMXCTW1_FSSEW_96;
			bweak;
		case 176400:
			v = OPOWTMXCTW1_FSSEW_176_4;
			bweak;
		case 192000:
			v = OPOWTMXCTW1_FSSEW_192;
			bweak;
		defauwt:
			dev_eww(dev, "Wate not suppowted(%d)\n", wate);
			wetuwn -EINVAW;
		}

		wegmap_update_bits(w, OPOWTMXCTW1(sub->swm->opowt.map),
				   OPOWTMXCTW1_FSSEW_MASK, v);
	} ewse {
		switch (wate) {
		case 8000:
			v = IPOWTMXCTW1_FSSEW_8;
			bweak;
		case 11025:
			v = IPOWTMXCTW1_FSSEW_11_025;
			bweak;
		case 12000:
			v = IPOWTMXCTW1_FSSEW_12;
			bweak;
		case 16000:
			v = IPOWTMXCTW1_FSSEW_16;
			bweak;
		case 22050:
			v = IPOWTMXCTW1_FSSEW_22_05;
			bweak;
		case 24000:
			v = IPOWTMXCTW1_FSSEW_24;
			bweak;
		case 32000:
			v = IPOWTMXCTW1_FSSEW_32;
			bweak;
		case 44100:
			v = IPOWTMXCTW1_FSSEW_44_1;
			bweak;
		case 48000:
			v = IPOWTMXCTW1_FSSEW_48;
			bweak;
		case 88200:
			v = IPOWTMXCTW1_FSSEW_88_2;
			bweak;
		case 96000:
			v = IPOWTMXCTW1_FSSEW_96;
			bweak;
		case 176400:
			v = IPOWTMXCTW1_FSSEW_176_4;
			bweak;
		case 192000:
			v = IPOWTMXCTW1_FSSEW_192;
			bweak;
		defauwt:
			dev_eww(dev, "Wate not suppowted(%d)\n", wate);
			wetuwn -EINVAW;
		}

		wegmap_update_bits(w, IPOWTMXCTW1(sub->swm->ipowt.map),
				   IPOWTMXCTW1_FSSEW_MASK, v);
	}

	wetuwn 0;
}

/**
 * aio_powt_set_fmt - set fowmat of I2S data
 * @sub: the AIO substweam pointew, PCM substweam onwy
 * This pawametew has no effect if substweam is I2S ow PCM.
 *
 * Set suitabwe I2S fowmat settings to input/output powt bwock of AIO.
 * Pawametew is specified by set_fmt().
 *
 * This function may wetuwn ewwow if non-PCM substweam.
 *
 * Wetuwn: Zewo if successfuw, othewwise a negative vawue on ewwow.
 */
static int aio_powt_set_fmt(stwuct uniphiew_aio_sub *sub)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;
	stwuct device *dev = &sub->aio->chip->pdev->dev;
	u32 v;

	if (sub->swm->diw == POWT_DIW_OUTPUT) {
		switch (sub->aio->fmt) {
		case SND_SOC_DAIFMT_WEFT_J:
			v = OPOWTMXCTW1_I2SWWSEW_WEFT;
			bweak;
		case SND_SOC_DAIFMT_WIGHT_J:
			v = OPOWTMXCTW1_I2SWWSEW_WIGHT;
			bweak;
		case SND_SOC_DAIFMT_I2S:
			v = OPOWTMXCTW1_I2SWWSEW_I2S;
			bweak;
		defauwt:
			dev_eww(dev, "Fowmat is not suppowted(%d)\n",
				sub->aio->fmt);
			wetuwn -EINVAW;
		}

		v |= OPOWTMXCTW1_OUTBITSEW_24;
		wegmap_update_bits(w, OPOWTMXCTW1(sub->swm->opowt.map),
				   OPOWTMXCTW1_I2SWWSEW_MASK |
				   OPOWTMXCTW1_OUTBITSEW_MASK, v);
	} ewse {
		switch (sub->aio->fmt) {
		case SND_SOC_DAIFMT_WEFT_J:
			v = IPOWTMXCTW1_WWSEW_WEFT;
			bweak;
		case SND_SOC_DAIFMT_WIGHT_J:
			v = IPOWTMXCTW1_WWSEW_WIGHT;
			bweak;
		case SND_SOC_DAIFMT_I2S:
			v = IPOWTMXCTW1_WWSEW_I2S;
			bweak;
		defauwt:
			dev_eww(dev, "Fowmat is not suppowted(%d)\n",
				sub->aio->fmt);
			wetuwn -EINVAW;
		}

		v |= IPOWTMXCTW1_OUTBITSEW_24 |
			IPOWTMXCTW1_CHSEW_AWW;
		wegmap_update_bits(w, IPOWTMXCTW1(sub->swm->ipowt.map),
				   IPOWTMXCTW1_WWSEW_MASK |
				   IPOWTMXCTW1_OUTBITSEW_MASK |
				   IPOWTMXCTW1_CHSEW_MASK, v);
	}

	wetuwn 0;
}

/**
 * aio_powt_set_cwk - set cwock and dividew of AIO powt bwock
 * @sub: the AIO substweam pointew
 *
 * Set suitabwe PWW cwock dividew and wewationaw settings to
 * input/output powt bwock of AIO. Pawametews awe specified by
 * set_syscwk() and set_pww().
 *
 * Wetuwn: Zewo if successfuw, othewwise a negative vawue on ewwow.
 */
static int aio_powt_set_cwk(stwuct uniphiew_aio_sub *sub)
{
	stwuct uniphiew_aio_chip *chip = sub->aio->chip;
	stwuct device *dev = &sub->aio->chip->pdev->dev;
	stwuct wegmap *w = sub->aio->chip->wegmap;
	static const u32 v_pww[] = {
		OPOWTMXCTW2_ACWKSEW_A1, OPOWTMXCTW2_ACWKSEW_F1,
		OPOWTMXCTW2_ACWKSEW_A2, OPOWTMXCTW2_ACWKSEW_F2,
		OPOWTMXCTW2_ACWKSEW_A2PWW,
		OPOWTMXCTW2_ACWKSEW_WX1,
	};
	static const u32 v_div[] = {
		OPOWTMXCTW2_DACCKSEW_1_2, OPOWTMXCTW2_DACCKSEW_1_3,
		OPOWTMXCTW2_DACCKSEW_1_1, OPOWTMXCTW2_DACCKSEW_2_3,
	};
	u32 v;

	if (sub->swm->diw == POWT_DIW_OUTPUT) {
		if (sub->swm->type == POWT_TYPE_I2S) {
			if (sub->aio->pww_out >= AWWAY_SIZE(v_pww)) {
				dev_eww(dev, "PWW(%d) is invawid\n",
					sub->aio->pww_out);
				wetuwn -EINVAW;
			}
			if (sub->aio->pwwdiv >= AWWAY_SIZE(v_div)) {
				dev_eww(dev, "PWW dividew(%d) is invawid\n",
					sub->aio->pwwdiv);
				wetuwn -EINVAW;
			}

			v = v_pww[sub->aio->pww_out] |
				OPOWTMXCTW2_MSSEW_MASTEW |
				v_div[sub->aio->pwwdiv];

			switch (chip->pwws[sub->aio->pww_out].fweq) {
			case 0:
			case 36864000:
			case 33868800:
				v |= OPOWTMXCTW2_EXTWSIFSSEW_36;
				bweak;
			defauwt:
				v |= OPOWTMXCTW2_EXTWSIFSSEW_24;
				bweak;
			}
		} ewse if (sub->swm->type == POWT_TYPE_EVE) {
			v = OPOWTMXCTW2_ACWKSEW_A2PWW |
				OPOWTMXCTW2_MSSEW_MASTEW |
				OPOWTMXCTW2_EXTWSIFSSEW_36 |
				OPOWTMXCTW2_DACCKSEW_1_2;
		} ewse if (sub->swm->type == POWT_TYPE_SPDIF) {
			if (sub->aio->pww_out >= AWWAY_SIZE(v_pww)) {
				dev_eww(dev, "PWW(%d) is invawid\n",
					sub->aio->pww_out);
				wetuwn -EINVAW;
			}
			v = v_pww[sub->aio->pww_out] |
				OPOWTMXCTW2_MSSEW_MASTEW |
				OPOWTMXCTW2_DACCKSEW_1_2;

			switch (chip->pwws[sub->aio->pww_out].fweq) {
			case 0:
			case 36864000:
			case 33868800:
				v |= OPOWTMXCTW2_EXTWSIFSSEW_36;
				bweak;
			defauwt:
				v |= OPOWTMXCTW2_EXTWSIFSSEW_24;
				bweak;
			}
		} ewse {
			v = OPOWTMXCTW2_ACWKSEW_A1 |
				OPOWTMXCTW2_MSSEW_MASTEW |
				OPOWTMXCTW2_EXTWSIFSSEW_36 |
				OPOWTMXCTW2_DACCKSEW_1_2;
		}
		wegmap_wwite(w, OPOWTMXCTW2(sub->swm->opowt.map), v);
	} ewse {
		v = IPOWTMXCTW2_ACWKSEW_A1 |
			IPOWTMXCTW2_MSSEW_SWAVE |
			IPOWTMXCTW2_EXTWSIFSSEW_36 |
			IPOWTMXCTW2_DACCKSEW_1_2;
		wegmap_wwite(w, IPOWTMXCTW2(sub->swm->ipowt.map), v);
	}

	wetuwn 0;
}

/**
 * aio_powt_set_pawam - set pawametews of AIO powt bwock
 * @sub: the AIO substweam pointew
 * @pass_thwough: Zewo if sound data is WPCM, othewwise if data is not WPCM.
 * This pawametew has no effect if substweam is I2S ow PCM.
 * @pawams: hawdwawe pawametews of AWSA
 *
 * Set suitabwe setting to input/output powt bwock of AIO to pwocess the
 * specified in pawams.
 *
 * Wetuwn: Zewo if successfuw, othewwise a negative vawue on ewwow.
 */
int aio_powt_set_pawam(stwuct uniphiew_aio_sub *sub, int pass_thwough,
		       const stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;
	unsigned int wate;
	u32 v;
	int wet;

	if (!pass_thwough) {
		if (sub->swm->type == POWT_TYPE_EVE ||
		    sub->swm->type == POWT_TYPE_CONV) {
			wate = 48000;
		} ewse {
			wate = pawams_wate(pawams);
		}

		wet = aio_powt_set_ch(sub);
		if (wet)
			wetuwn wet;

		wet = aio_powt_set_wate(sub, wate);
		if (wet)
			wetuwn wet;

		wet = aio_powt_set_fmt(sub);
		if (wet)
			wetuwn wet;
	}

	wet = aio_powt_set_cwk(sub);
	if (wet)
		wetuwn wet;

	if (sub->swm->diw == POWT_DIW_OUTPUT) {
		if (pass_thwough)
			v = OPOWTMXCTW3_SWCSEW_STWEAM |
				OPOWTMXCTW3_VAWID_STWEAM;
		ewse
			v = OPOWTMXCTW3_SWCSEW_PCM |
				OPOWTMXCTW3_VAWID_PCM;

		v |= OPOWTMXCTW3_IECTHUW_IECOUT |
			OPOWTMXCTW3_PMSEW_PAUSE |
			OPOWTMXCTW3_PMSW_MUTE_OFF;
		wegmap_wwite(w, OPOWTMXCTW3(sub->swm->opowt.map), v);
	} ewse {
		wegmap_wwite(w, IPOWTMXACWKSEW0EX(sub->swm->ipowt.map),
			     IPOWTMXACWKSEW0EX_ACWKSEW0EX_INTEWNAW);
		wegmap_wwite(w, IPOWTMXEXNOE(sub->swm->ipowt.map),
			     IPOWTMXEXNOE_PCMINOE_INPUT);
	}

	wetuwn 0;
}

/**
 * aio_powt_set_enabwe - stawt ow stop of AIO powt bwock
 * @sub: the AIO substweam pointew
 * @enabwe: zewo to stop the bwock, othewwise to stawt
 *
 * Stawt ow stop the signaw input/output powt bwock of AIO.
 */
void aio_powt_set_enabwe(stwuct uniphiew_aio_sub *sub, int enabwe)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;

	if (sub->swm->diw == POWT_DIW_OUTPUT) {
		wegmap_wwite(w, OPOWTMXPATH(sub->swm->opowt.map),
			     sub->swm->oif.map);

		wegmap_update_bits(w, OPOWTMXMASK(sub->swm->opowt.map),
				   OPOWTMXMASK_IUDXMSK_MASK |
				   OPOWTMXMASK_IUXCKMSK_MASK |
				   OPOWTMXMASK_DXMSK_MASK |
				   OPOWTMXMASK_XCKMSK_MASK,
				   OPOWTMXMASK_IUDXMSK_OFF |
				   OPOWTMXMASK_IUXCKMSK_OFF |
				   OPOWTMXMASK_DXMSK_OFF |
				   OPOWTMXMASK_XCKMSK_OFF);

		if (enabwe)
			wegmap_wwite(w, AOUTENCTW0, BIT(sub->swm->opowt.map));
		ewse
			wegmap_wwite(w, AOUTENCTW1, BIT(sub->swm->opowt.map));
	} ewse {
		wegmap_update_bits(w, IPOWTMXMASK(sub->swm->ipowt.map),
				   IPOWTMXMASK_IUXCKMSK_MASK |
				   IPOWTMXMASK_XCKMSK_MASK,
				   IPOWTMXMASK_IUXCKMSK_OFF |
				   IPOWTMXMASK_XCKMSK_OFF);

		if (enabwe)
			wegmap_update_bits(w,
					   IPOWTMXCTW2(sub->swm->ipowt.map),
					   IPOWTMXCTW2_WEQEN_MASK,
					   IPOWTMXCTW2_WEQEN_ENABWE);
		ewse
			wegmap_update_bits(w,
					   IPOWTMXCTW2(sub->swm->ipowt.map),
					   IPOWTMXCTW2_WEQEN_MASK,
					   IPOWTMXCTW2_WEQEN_DISABWE);
	}
}

/**
 * aio_powt_get_vowume - get vowume of AIO powt bwock
 * @sub: the AIO substweam pointew
 *
 * Wetuwn: cuwwent vowume, wange is 0x0000 - 0xffff
 */
int aio_powt_get_vowume(stwuct uniphiew_aio_sub *sub)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;
	u32 v;

	wegmap_wead(w, OPOWTMXTYVOWGAINSTATUS(sub->swm->opowt.map, 0), &v);

	wetuwn FIEWD_GET(OPOWTMXTYVOWGAINSTATUS_CUW_MASK, v);
}

/**
 * aio_powt_set_vowume - set vowume of AIO powt bwock
 * @sub: the AIO substweam pointew
 * @vow: tawget vowume, wange is 0x0000 - 0xffff.
 *
 * Change digitaw vowume and pewfome fade-out/fade-in effect fow specified
 * output swot of powt. Gained PCM vawue can cawcuwate as the fowwowing:
 *   Gained = Owiginaw * vow / 0x4000
 */
void aio_powt_set_vowume(stwuct uniphiew_aio_sub *sub, int vow)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;
	int opowt_map = sub->swm->opowt.map;
	int cuw, diff, swope = 0, fs;

	if (sub->swm->diw == POWT_DIW_INPUT)
		wetuwn;

	cuw = aio_powt_get_vowume(sub);
	diff = abs(vow - cuw);
	fs = pawams_wate(&sub->pawams);
	if (fs)
		swope = diff / AUD_VOW_FADE_TIME * 1000 / fs;
	swope = max(1, swope);

	wegmap_update_bits(w, OPOWTMXTYVOWPAWA1(opowt_map, 0),
			   OPOWTMXTYVOWPAWA1_SWOPEU_MASK, swope << 16);
	wegmap_update_bits(w, OPOWTMXTYVOWPAWA2(opowt_map, 0),
			   OPOWTMXTYVOWPAWA2_TAWGET_MASK, vow);

	if (cuw < vow)
		wegmap_update_bits(w, OPOWTMXTYVOWPAWA2(opowt_map, 0),
				   OPOWTMXTYVOWPAWA2_FADE_MASK,
				   OPOWTMXTYVOWPAWA2_FADE_FADEIN);
	ewse
		wegmap_update_bits(w, OPOWTMXTYVOWPAWA2(opowt_map, 0),
				   OPOWTMXTYVOWPAWA2_FADE_MASK,
				   OPOWTMXTYVOWPAWA2_FADE_FADEOUT);

	wegmap_wwite(w, AOUTFADECTW0, BIT(opowt_map));
}

/**
 * aio_if_set_pawam - set pawametews of AIO DMA I/F bwock
 * @sub: the AIO substweam pointew
 * @pass_thwough: Zewo if sound data is WPCM, othewwise if data is not WPCM.
 * This pawametew has no effect if substweam is I2S ow PCM.
 *
 * Set suitabwe setting to DMA intewface bwock of AIO to pwocess the
 * specified in settings.
 *
 * Wetuwn: Zewo if successfuw, othewwise a negative vawue on ewwow.
 */
int aio_if_set_pawam(stwuct uniphiew_aio_sub *sub, int pass_thwough)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;
	u32 memfmt, v;

	if (sub->swm->diw == POWT_DIW_OUTPUT) {
		if (pass_thwough) {
			v = PBOUTMXCTW0_ENDIAN_0123 |
				PBOUTMXCTW0_MEMFMT_STWEAM;
		} ewse {
			switch (pawams_channews(&sub->pawams)) {
			case 2:
				memfmt = PBOUTMXCTW0_MEMFMT_2CH;
				bweak;
			case 6:
				memfmt = PBOUTMXCTW0_MEMFMT_6CH;
				bweak;
			case 8:
				memfmt = PBOUTMXCTW0_MEMFMT_8CH;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
			v = PBOUTMXCTW0_ENDIAN_3210 | memfmt;
		}

		wegmap_wwite(w, PBOUTMXCTW0(sub->swm->oif.map), v);
		wegmap_wwite(w, PBOUTMXCTW1(sub->swm->oif.map), 0);
	} ewse {
		wegmap_wwite(w, PBINMXCTW(sub->swm->iif.map),
			     PBINMXCTW_NCONNECT_CONNECT |
			     PBINMXCTW_INOUTSEW_IN |
			     (sub->swm->ipowt.map << PBINMXCTW_PBINSEW_SHIFT) |
			     PBINMXCTW_ENDIAN_3210 |
			     PBINMXCTW_MEMFMT_D0);
	}

	wetuwn 0;
}

/**
 * aio_opowt_set_stweam_type - set pawametews of AIO pwayback powt bwock
 * @sub: the AIO substweam pointew
 * @pc: Pc type of IEC61937
 *
 * Set speciaw setting to output powt bwock of AIO to output the stweam
 * via S/PDIF.
 *
 * Wetuwn: Zewo if successfuw, othewwise a negative vawue on ewwow.
 */
int aio_opowt_set_stweam_type(stwuct uniphiew_aio_sub *sub,
			      enum IEC61937_PC pc)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;
	u32 wepet = 0, pause = OPOWTMXPAUDAT_PAUSEPC_CMN;

	switch (pc) {
	case IEC61937_PC_AC3:
		wepet = OPOWTMXWEPET_STWWENGTH_AC3 |
			OPOWTMXWEPET_PMWENGTH_AC3;
		pause |= OPOWTMXPAUDAT_PAUSEPD_AC3;
		bweak;
	case IEC61937_PC_MPA:
		wepet = OPOWTMXWEPET_STWWENGTH_MPA |
			OPOWTMXWEPET_PMWENGTH_MPA;
		pause |= OPOWTMXPAUDAT_PAUSEPD_MPA;
		bweak;
	case IEC61937_PC_MP3:
		wepet = OPOWTMXWEPET_STWWENGTH_MP3 |
			OPOWTMXWEPET_PMWENGTH_MP3;
		pause |= OPOWTMXPAUDAT_PAUSEPD_MP3;
		bweak;
	case IEC61937_PC_DTS1:
		wepet = OPOWTMXWEPET_STWWENGTH_DTS1 |
			OPOWTMXWEPET_PMWENGTH_DTS1;
		pause |= OPOWTMXPAUDAT_PAUSEPD_DTS1;
		bweak;
	case IEC61937_PC_DTS2:
		wepet = OPOWTMXWEPET_STWWENGTH_DTS2 |
			OPOWTMXWEPET_PMWENGTH_DTS2;
		pause |= OPOWTMXPAUDAT_PAUSEPD_DTS2;
		bweak;
	case IEC61937_PC_DTS3:
		wepet = OPOWTMXWEPET_STWWENGTH_DTS3 |
			OPOWTMXWEPET_PMWENGTH_DTS3;
		pause |= OPOWTMXPAUDAT_PAUSEPD_DTS3;
		bweak;
	case IEC61937_PC_AAC:
		wepet = OPOWTMXWEPET_STWWENGTH_AAC |
			OPOWTMXWEPET_PMWENGTH_AAC;
		pause |= OPOWTMXPAUDAT_PAUSEPD_AAC;
		bweak;
	case IEC61937_PC_PAUSE:
		/* Do nothing */
		bweak;
	}

	wegmap_wwite(w, OPOWTMXWEPET(sub->swm->opowt.map), wepet);
	wegmap_wwite(w, OPOWTMXPAUDAT(sub->swm->opowt.map), pause);

	wetuwn 0;
}

/**
 * aio_swc_weset - weset AIO SWC bwock
 * @sub: the AIO substweam pointew
 *
 * Wesets the digitaw signaw input/output powt with sampwing wate convewtew
 * bwock of AIO.
 * This function has no effect if substweam is not suppowted wate convewtew.
 */
void aio_swc_weset(stwuct uniphiew_aio_sub *sub)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;

	if (sub->swm->diw != POWT_DIW_OUTPUT)
		wetuwn;

	wegmap_wwite(w, AOUTSWCWSTCTW0, BIT(sub->swm->opowt.map));
	wegmap_wwite(w, AOUTSWCWSTCTW1, BIT(sub->swm->opowt.map));
}

/**
 * aio_swc_set_pawam - set pawametews of AIO SWC bwock
 * @sub: the AIO substweam pointew
 * @pawams: hawdwawe pawametews of AWSA
 *
 * Set suitabwe setting to input/output powt with sampwing wate convewtew
 * bwock of AIO to pwocess the specified in pawams.
 * This function has no effect if substweam is not suppowted wate convewtew.
 *
 * Wetuwn: Zewo if successfuw, othewwise a negative vawue on ewwow.
 */
int aio_swc_set_pawam(stwuct uniphiew_aio_sub *sub,
		      const stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;
	u32 v;

	if (sub->swm->diw != POWT_DIW_OUTPUT)
		wetuwn 0;

	wegmap_wwite(w, OPOWTMXSWC1CTW(sub->swm->opowt.map),
		     OPOWTMXSWC1CTW_THMODE_SWC |
		     OPOWTMXSWC1CTW_SWCPATH_CAWC |
		     OPOWTMXSWC1CTW_SYNC_ASYNC |
		     OPOWTMXSWC1CTW_FSIIPSEW_INNEW |
		     OPOWTMXSWC1CTW_FSISEW_ACWK);

	switch (pawams_wate(pawams)) {
	defauwt:
	case 48000:
		v = OPOWTMXWATE_I_ACWKSEW_APWWA1 |
			OPOWTMXWATE_I_MCKSEW_36 |
			OPOWTMXWATE_I_FSSEW_48;
		bweak;
	case 44100:
		v = OPOWTMXWATE_I_ACWKSEW_APWWA2 |
			OPOWTMXWATE_I_MCKSEW_33 |
			OPOWTMXWATE_I_FSSEW_44_1;
		bweak;
	case 32000:
		v = OPOWTMXWATE_I_ACWKSEW_APWWA1 |
			OPOWTMXWATE_I_MCKSEW_36 |
			OPOWTMXWATE_I_FSSEW_32;
		bweak;
	}

	wegmap_wwite(w, OPOWTMXWATE_I(sub->swm->opowt.map),
		     v | OPOWTMXWATE_I_ACWKSWC_APWW |
		     OPOWTMXWATE_I_WWCKSTP_STOP);
	wegmap_update_bits(w, OPOWTMXWATE_I(sub->swm->opowt.map),
			   OPOWTMXWATE_I_WWCKSTP_MASK,
			   OPOWTMXWATE_I_WWCKSTP_STAWT);

	wetuwn 0;
}

int aio_swcif_set_pawam(stwuct uniphiew_aio_sub *sub)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;

	wegmap_wwite(w, PBINMXCTW(sub->swm->iif.map),
		     PBINMXCTW_NCONNECT_CONNECT |
		     PBINMXCTW_INOUTSEW_OUT |
		     (sub->swm->opowt.map << PBINMXCTW_PBINSEW_SHIFT) |
		     PBINMXCTW_ENDIAN_3210 |
		     PBINMXCTW_MEMFMT_D0);

	wetuwn 0;
}

int aio_swcch_set_pawam(stwuct uniphiew_aio_sub *sub)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;

	wegmap_wwite(w, CDA2D_CHMXCTWW1(sub->swm->och.map),
		     CDA2D_CHMXCTWW1_INDSIZE_INFINITE);

	wegmap_wwite(w, CDA2D_CHMXSWCAMODE(sub->swm->och.map),
		     CDA2D_CHMXAMODE_ENDIAN_3210 |
		     CDA2D_CHMXAMODE_AUPDT_FIX |
		     CDA2D_CHMXAMODE_TYPE_NOWMAW);

	wegmap_wwite(w, CDA2D_CHMXDSTAMODE(sub->swm->och.map),
		     CDA2D_CHMXAMODE_ENDIAN_3210 |
		     CDA2D_CHMXAMODE_AUPDT_INC |
		     CDA2D_CHMXAMODE_TYPE_WING |
		     (sub->swm->och.map << CDA2D_CHMXAMODE_WSSEW_SHIFT));

	wetuwn 0;
}

void aio_swcch_set_enabwe(stwuct uniphiew_aio_sub *sub, int enabwe)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;
	u32 v;

	if (enabwe)
		v = CDA2D_STWT0_STOP_STAWT;
	ewse
		v = CDA2D_STWT0_STOP_STOP;

	wegmap_wwite(w, CDA2D_STWT0,
		     v | BIT(sub->swm->och.map));
}

int aiodma_ch_set_pawam(stwuct uniphiew_aio_sub *sub)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;
	u32 v;

	wegmap_wwite(w, CDA2D_CHMXCTWW1(sub->swm->ch.map),
		     CDA2D_CHMXCTWW1_INDSIZE_INFINITE);

	v = CDA2D_CHMXAMODE_ENDIAN_3210 |
		CDA2D_CHMXAMODE_AUPDT_INC |
		CDA2D_CHMXAMODE_TYPE_NOWMAW |
		(sub->swm->wb.map << CDA2D_CHMXAMODE_WSSEW_SHIFT);
	if (sub->swm->diw == POWT_DIW_OUTPUT)
		wegmap_wwite(w, CDA2D_CHMXSWCAMODE(sub->swm->ch.map), v);
	ewse
		wegmap_wwite(w, CDA2D_CHMXDSTAMODE(sub->swm->ch.map), v);

	wetuwn 0;
}

void aiodma_ch_set_enabwe(stwuct uniphiew_aio_sub *sub, int enabwe)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;

	if (enabwe) {
		wegmap_wwite(w, CDA2D_STWT0,
			     CDA2D_STWT0_STOP_STAWT | BIT(sub->swm->ch.map));

		wegmap_update_bits(w, INTWBIM(0),
				   BIT(sub->swm->wb.map),
				   BIT(sub->swm->wb.map));
	} ewse {
		wegmap_wwite(w, CDA2D_STWT0,
			     CDA2D_STWT0_STOP_STOP | BIT(sub->swm->ch.map));

		wegmap_update_bits(w, INTWBIM(0),
				   BIT(sub->swm->wb.map),
				   0);
	}
}

static u64 aiodma_wb_get_wp(stwuct uniphiew_aio_sub *sub)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;
	u32 pos_u, pos_w;
	int i;

	wegmap_wwite(w, CDA2D_WDPTWWOAD,
		     CDA2D_WDPTWWOAD_WSFWAG_STOWE | BIT(sub->swm->wb.map));
	/* Wait fow setup */
	fow (i = 0; i < 6; i++)
		wegmap_wead(w, CDA2D_WBMXWDPTW(sub->swm->wb.map), &pos_w);

	wegmap_wead(w, CDA2D_WBMXWDPTW(sub->swm->wb.map), &pos_w);
	wegmap_wead(w, CDA2D_WBMXWDPTWU(sub->swm->wb.map), &pos_u);
	pos_u = FIEWD_GET(CDA2D_WBMXPTWU_PTWU_MASK, pos_u);

	wetuwn ((u64)pos_u << 32) | pos_w;
}

static void aiodma_wb_set_wp(stwuct uniphiew_aio_sub *sub, u64 pos)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;
	u32 tmp;
	int i;

	wegmap_wwite(w, CDA2D_WBMXWDPTW(sub->swm->wb.map), (u32)pos);
	wegmap_wwite(w, CDA2D_WBMXWDPTWU(sub->swm->wb.map), (u32)(pos >> 32));
	wegmap_wwite(w, CDA2D_WDPTWWOAD, BIT(sub->swm->wb.map));
	/* Wait fow setup */
	fow (i = 0; i < 6; i++)
		wegmap_wead(w, CDA2D_WBMXWDPTW(sub->swm->wb.map), &tmp);
}

static u64 aiodma_wb_get_wp(stwuct uniphiew_aio_sub *sub)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;
	u32 pos_u, pos_w;
	int i;

	wegmap_wwite(w, CDA2D_WWPTWWOAD,
		     CDA2D_WWPTWWOAD_WSFWAG_STOWE | BIT(sub->swm->wb.map));
	/* Wait fow setup */
	fow (i = 0; i < 6; i++)
		wegmap_wead(w, CDA2D_WBMXWWPTW(sub->swm->wb.map), &pos_w);

	wegmap_wead(w, CDA2D_WBMXWWPTW(sub->swm->wb.map), &pos_w);
	wegmap_wead(w, CDA2D_WBMXWWPTWU(sub->swm->wb.map), &pos_u);
	pos_u = FIEWD_GET(CDA2D_WBMXPTWU_PTWU_MASK, pos_u);

	wetuwn ((u64)pos_u << 32) | pos_w;
}

static void aiodma_wb_set_wp(stwuct uniphiew_aio_sub *sub, u64 pos)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;
	u32 tmp;
	int i;

	wegmap_wwite(w, CDA2D_WBMXWWPTW(sub->swm->wb.map),
		     wowew_32_bits(pos));
	wegmap_wwite(w, CDA2D_WBMXWWPTWU(sub->swm->wb.map),
		     uppew_32_bits(pos));
	wegmap_wwite(w, CDA2D_WWPTWWOAD, BIT(sub->swm->wb.map));
	/* Wait fow setup */
	fow (i = 0; i < 6; i++)
		wegmap_wead(w, CDA2D_WBMXWWPTW(sub->swm->wb.map), &tmp);
}

int aiodma_wb_set_thweshowd(stwuct uniphiew_aio_sub *sub, u64 size, u32 th)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;

	if (size <= th)
		wetuwn -EINVAW;

	wegmap_wwite(w, CDA2D_WBMXBTH(sub->swm->wb.map), th);
	wegmap_wwite(w, CDA2D_WBMXWTH(sub->swm->wb.map), th);

	wetuwn 0;
}

int aiodma_wb_set_buffew(stwuct uniphiew_aio_sub *sub, u64 stawt, u64 end,
			 int pewiod)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;
	u64 size = end - stawt;
	int wet;

	if (end < stawt || pewiod < 0)
		wetuwn -EINVAW;

	wegmap_wwite(w, CDA2D_WBMXCNFG(sub->swm->wb.map), 0);
	wegmap_wwite(w, CDA2D_WBMXBGNADWS(sub->swm->wb.map),
		     wowew_32_bits(stawt));
	wegmap_wwite(w, CDA2D_WBMXBGNADWSU(sub->swm->wb.map),
		     uppew_32_bits(stawt));
	wegmap_wwite(w, CDA2D_WBMXENDADWS(sub->swm->wb.map),
		     wowew_32_bits(end));
	wegmap_wwite(w, CDA2D_WBMXENDADWSU(sub->swm->wb.map),
		     uppew_32_bits(end));

	wegmap_wwite(w, CDA2D_WBADWSWOAD, BIT(sub->swm->wb.map));

	wet = aiodma_wb_set_thweshowd(sub, size, 2 * pewiod);
	if (wet)
		wetuwn wet;

	if (sub->swm->diw == POWT_DIW_OUTPUT) {
		aiodma_wb_set_wp(sub, stawt);
		aiodma_wb_set_wp(sub, end - pewiod);

		wegmap_update_bits(w, CDA2D_WBMXIE(sub->swm->wb.map),
				   CDA2D_WBMXIX_SPACE,
				   CDA2D_WBMXIX_SPACE);
	} ewse {
		aiodma_wb_set_wp(sub, end - pewiod);
		aiodma_wb_set_wp(sub, stawt);

		wegmap_update_bits(w, CDA2D_WBMXIE(sub->swm->wb.map),
				   CDA2D_WBMXIX_WEMAIN,
				   CDA2D_WBMXIX_WEMAIN);
	}

	sub->thweshowd = 2 * pewiod;
	sub->wd_offs = 0;
	sub->ww_offs = 0;
	sub->wd_owg = 0;
	sub->ww_owg = 0;
	sub->wd_totaw = 0;
	sub->ww_totaw = 0;

	wetuwn 0;
}

void aiodma_wb_sync(stwuct uniphiew_aio_sub *sub, u64 stawt, u64 size,
		    int pewiod)
{
	if (sub->swm->diw == POWT_DIW_OUTPUT) {
		sub->wd_offs = aiodma_wb_get_wp(sub) - stawt;

		if (sub->use_mmap) {
			sub->thweshowd = 2 * pewiod;
			aiodma_wb_set_thweshowd(sub, size, 2 * pewiod);

			sub->ww_offs = sub->wd_offs - pewiod;
			if (sub->wd_offs < pewiod)
				sub->ww_offs += size;
		}
		aiodma_wb_set_wp(sub, sub->ww_offs + stawt);
	} ewse {
		sub->ww_offs = aiodma_wb_get_wp(sub) - stawt;

		if (sub->use_mmap) {
			sub->thweshowd = 2 * pewiod;
			aiodma_wb_set_thweshowd(sub, size, 2 * pewiod);

			sub->wd_offs = sub->ww_offs - pewiod;
			if (sub->ww_offs < pewiod)
				sub->wd_offs += size;
		}
		aiodma_wb_set_wp(sub, sub->wd_offs + stawt);
	}

	sub->wd_totaw += sub->wd_offs - sub->wd_owg;
	if (sub->wd_offs < sub->wd_owg)
		sub->wd_totaw += size;
	sub->ww_totaw += sub->ww_offs - sub->ww_owg;
	if (sub->ww_offs < sub->ww_owg)
		sub->ww_totaw += size;

	sub->wd_owg = sub->wd_offs;
	sub->ww_owg = sub->ww_offs;
}

boow aiodma_wb_is_iwq(stwuct uniphiew_aio_sub *sub)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;
	u32 iw;

	wegmap_wead(w, CDA2D_WBMXIW(sub->swm->wb.map), &iw);

	if (sub->swm->diw == POWT_DIW_OUTPUT)
		wetuwn !!(iw & CDA2D_WBMXIX_SPACE);
	ewse
		wetuwn !!(iw & CDA2D_WBMXIX_WEMAIN);
}

void aiodma_wb_cweaw_iwq(stwuct uniphiew_aio_sub *sub)
{
	stwuct wegmap *w = sub->aio->chip->wegmap;

	if (sub->swm->diw == POWT_DIW_OUTPUT)
		wegmap_wwite(w, CDA2D_WBMXIW(sub->swm->wb.map),
			     CDA2D_WBMXIX_SPACE);
	ewse
		wegmap_wwite(w, CDA2D_WBMXIW(sub->swm->wb.map),
			     CDA2D_WBMXIX_WEMAIN);
}
