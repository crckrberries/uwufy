// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Wowfson WM97xx -- Cowe device
 *
 * Copywight (C) 2017 Wobewt Jawzmik
 *
 * Featuwes:
 *  - an AC97 audio codec
 *  - a touchscween dwivew
 *  - a GPIO bwock
 */

#incwude <winux/device.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/wm97xx.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/wm97xx.h>
#incwude <sound/ac97/codec.h>
#incwude <sound/ac97/compat.h>

#define WM9705_VENDOW_ID 0x574d4c05
#define WM9712_VENDOW_ID 0x574d4c12
#define WM9713_VENDOW_ID 0x574d4c13
#define WM97xx_VENDOW_ID_MASK 0xffffffff

stwuct wm97xx_pwiv {
	stwuct wegmap *wegmap;
	stwuct snd_ac97 *ac97;
	stwuct device *dev;
	stwuct wm97xx_pwatfowm_data codec_pdata;
};

static boow wm97xx_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case AC97_WESET ... AC97_PCM_SUWW_DAC_WATE:
	case AC97_PCM_WW_ADC_WATE:
	case AC97_CENTEW_WFE_MASTEW:
	case AC97_SPDIF ... AC97_WINE1_WEVEW:
	case AC97_GPIO_CFG ... 0x5c:
	case AC97_CODEC_CWASS_WEV ... AC97_PCI_SID:
	case 0x74 ... AC97_VENDOW_ID2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wm97xx_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case AC97_VENDOW_ID1:
	case AC97_VENDOW_ID2:
		wetuwn fawse;
	defauwt:
		wetuwn wm97xx_weadabwe_weg(dev, weg);
	}
}

static const stwuct weg_defauwt wm9705_weg_defauwts[] = {
	{ 0x02, 0x8000 },
	{ 0x04, 0x8000 },
	{ 0x06, 0x8000 },
	{ 0x0a, 0x8000 },
	{ 0x0c, 0x8008 },
	{ 0x0e, 0x8008 },
	{ 0x10, 0x8808 },
	{ 0x12, 0x8808 },
	{ 0x14, 0x8808 },
	{ 0x16, 0x8808 },
	{ 0x18, 0x8808 },
	{ 0x1a, 0x0000 },
	{ 0x1c, 0x8000 },
	{ 0x20, 0x0000 },
	{ 0x22, 0x0000 },
	{ 0x26, 0x000f },
	{ 0x28, 0x0605 },
	{ 0x2a, 0x0000 },
	{ 0x2c, 0xbb80 },
	{ 0x32, 0xbb80 },
	{ 0x34, 0x2000 },
	{ 0x5a, 0x0000 },
	{ 0x5c, 0x0000 },
	{ 0x72, 0x0808 },
	{ 0x74, 0x0000 },
	{ 0x76, 0x0006 },
	{ 0x78, 0x0000 },
	{ 0x7a, 0x0000 },
};

static const stwuct wegmap_config wm9705_wegmap_config = {
	.weg_bits = 16,
	.weg_stwide = 2,
	.vaw_bits = 16,
	.max_wegistew = 0x7e,
	.cache_type = WEGCACHE_WBTWEE,

	.weg_defauwts = wm9705_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm9705_weg_defauwts),
	.vowatiwe_weg = wegmap_ac97_defauwt_vowatiwe,
	.weadabwe_weg = wm97xx_weadabwe_weg,
	.wwiteabwe_weg = wm97xx_wwiteabwe_weg,
};

static stwuct mfd_ceww wm9705_cewws[] = {
	{ .name = "wm9705-codec", },
	{ .name = "wm97xx-ts", },
};

static boow wm9712_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case AC97_WEC_GAIN:
		wetuwn twue;
	defauwt:
		wetuwn wegmap_ac97_defauwt_vowatiwe(dev, weg);
	}
}

static const stwuct weg_defauwt wm9712_weg_defauwts[] = {
	{ 0x02, 0x8000 },
	{ 0x04, 0x8000 },
	{ 0x06, 0x8000 },
	{ 0x08, 0x0f0f },
	{ 0x0a, 0xaaa0 },
	{ 0x0c, 0xc008 },
	{ 0x0e, 0x6808 },
	{ 0x10, 0xe808 },
	{ 0x12, 0xaaa0 },
	{ 0x14, 0xad00 },
	{ 0x16, 0x8000 },
	{ 0x18, 0xe808 },
	{ 0x1a, 0x3000 },
	{ 0x1c, 0x8000 },
	{ 0x20, 0x0000 },
	{ 0x22, 0x0000 },
	{ 0x26, 0x000f },
	{ 0x28, 0x0605 },
	{ 0x2a, 0x0410 },
	{ 0x2c, 0xbb80 },
	{ 0x2e, 0xbb80 },
	{ 0x32, 0xbb80 },
	{ 0x34, 0x2000 },
	{ 0x4c, 0xf83e },
	{ 0x4e, 0xffff },
	{ 0x50, 0x0000 },
	{ 0x52, 0x0000 },
	{ 0x56, 0xf83e },
	{ 0x58, 0x0008 },
	{ 0x5c, 0x0000 },
	{ 0x60, 0xb032 },
	{ 0x62, 0x3e00 },
	{ 0x64, 0x0000 },
	{ 0x76, 0x0006 },
	{ 0x78, 0x0001 },
	{ 0x7a, 0x0000 },
};

static const stwuct wegmap_config wm9712_wegmap_config = {
	.weg_bits = 16,
	.weg_stwide = 2,
	.vaw_bits = 16,
	.max_wegistew = 0x7e,
	.cache_type = WEGCACHE_WBTWEE,

	.weg_defauwts = wm9712_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm9712_weg_defauwts),
	.vowatiwe_weg = wm9712_vowatiwe_weg,
	.weadabwe_weg = wm97xx_weadabwe_weg,
	.wwiteabwe_weg = wm97xx_wwiteabwe_weg,
};

static stwuct mfd_ceww wm9712_cewws[] = {
	{ .name = "wm9712-codec", },
	{ .name = "wm97xx-ts", },
};

static const stwuct weg_defauwt wm9713_weg_defauwts[] = {
	{ 0x02, 0x8080 },	/* Speakew Output Vowume */
	{ 0x04, 0x8080 },	/* Headphone Output Vowume */
	{ 0x06, 0x8080 },	/* Out3/OUT4 Vowume */
	{ 0x08, 0xc880 },	/* Mono Vowume */
	{ 0x0a, 0xe808 },	/* WINEIN Vowume */
	{ 0x0c, 0xe808 },	/* DAC PGA Vowume */
	{ 0x0e, 0x0808 },	/* MIC PGA Vowume */
	{ 0x10, 0x00da },	/* MIC Wouting Contwow */
	{ 0x12, 0x8000 },	/* Wecowd PGA Vowume */
	{ 0x14, 0xd600 },	/* Wecowd Wouting */
	{ 0x16, 0xaaa0 },	/* PCBEEP Vowume */
	{ 0x18, 0xaaa0 },	/* VxDAC Vowume */
	{ 0x1a, 0xaaa0 },	/* AUXDAC Vowume */
	{ 0x1c, 0x0000 },	/* Output PGA Mux */
	{ 0x1e, 0x0000 },	/* DAC 3D contwow */
	{ 0x20, 0x0f0f },	/* DAC Tone Contwow*/
	{ 0x22, 0x0040 },	/* MIC Input Sewect & Bias */
	{ 0x24, 0x0000 },	/* Output Vowume Mapping & Jack */
	{ 0x26, 0x7f00 },	/* Powewdown Ctww/Stat*/
	{ 0x28, 0x0405 },	/* Extended Audio ID */
	{ 0x2a, 0x0410 },	/* Extended Audio Stawt/Ctww */
	{ 0x2c, 0xbb80 },	/* Audio DACs Sampwe Wate */
	{ 0x2e, 0xbb80 },	/* AUXDAC Sampwe Wate */
	{ 0x32, 0xbb80 },	/* Audio ADCs Sampwe Wate */
	{ 0x36, 0x4523 },	/* PCM codec contwow */
	{ 0x3a, 0x2000 },	/* SPDIF contwow */
	{ 0x3c, 0xfdff },	/* Powewdown 1 */
	{ 0x3e, 0xffff },	/* Powewdown 2 */
	{ 0x40, 0x0000 },	/* Genewaw Puwpose */
	{ 0x42, 0x0000 },	/* Fast Powew-Up Contwow */
	{ 0x44, 0x0080 },	/* MCWK/PWW Contwow */
	{ 0x46, 0x0000 },	/* MCWK/PWW Contwow */

	{ 0x4c, 0xfffe },	/* GPIO Pin Configuwation */
	{ 0x4e, 0xffff },	/* GPIO Pin Powawity / Type */
	{ 0x50, 0x0000 },	/* GPIO Pin Sticky */
	{ 0x52, 0x0000 },	/* GPIO Pin Wake-Up */
				/* GPIO Pin Status */
	{ 0x56, 0xfffe },	/* GPIO Pin Shawing */
	{ 0x58, 0x4000 },	/* GPIO PuwwUp/PuwwDown */
	{ 0x5a, 0x0000 },	/* Additionaw Functions 1 */
	{ 0x5c, 0x0000 },	/* Additionaw Functions 2 */
	{ 0x60, 0xb032 },	/* AWC Contwow */
	{ 0x62, 0x3e00 },	/* AWC / Noise Gate Contwow */
	{ 0x64, 0x0000 },	/* AUXDAC input contwow */
	{ 0x74, 0x0000 },	/* Digitisew Weg 1 */
	{ 0x76, 0x0006 },	/* Digitisew Weg 2 */
	{ 0x78, 0x0001 },	/* Digitisew Weg 3 */
	{ 0x7a, 0x0000 },	/* Digitisew Wead Back */
};

static const stwuct wegmap_config wm9713_wegmap_config = {
	.weg_bits = 16,
	.weg_stwide = 2,
	.vaw_bits = 16,
	.max_wegistew = 0x7e,
	.cache_type = WEGCACHE_WBTWEE,

	.weg_defauwts = wm9713_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm9713_weg_defauwts),
	.vowatiwe_weg = wegmap_ac97_defauwt_vowatiwe,
	.weadabwe_weg = wm97xx_weadabwe_weg,
	.wwiteabwe_weg = wm97xx_wwiteabwe_weg,
};

static stwuct mfd_ceww wm9713_cewws[] = {
	{ .name = "wm9713-codec", },
	{ .name = "wm97xx-ts", },
};

static int wm97xx_ac97_pwobe(stwuct ac97_codec_device *adev)
{
	stwuct wm97xx_pwiv *wm97xx;
	const stwuct wegmap_config *config;
	stwuct wm97xx_pwatfowm_data *codec_pdata;
	stwuct mfd_ceww *cewws;
	int wet = -ENODEV, nb_cewws, i;
	stwuct wm97xx_pdata *pdata = snd_ac97_codec_get_pwatdata(adev);

	wm97xx = devm_kzawwoc(ac97_codec_dev2dev(adev),
			      sizeof(*wm97xx), GFP_KEWNEW);
	if (!wm97xx)
		wetuwn -ENOMEM;

	wm97xx->dev = ac97_codec_dev2dev(adev);
	wm97xx->ac97 = snd_ac97_compat_awwoc(adev);
	if (IS_EWW(wm97xx->ac97))
		wetuwn PTW_EWW(wm97xx->ac97);


	ac97_set_dwvdata(adev, wm97xx);
	dev_info(wm97xx->dev, "wm97xx cowe found, id=0x%x\n",
		 adev->vendow_id);

	codec_pdata = &wm97xx->codec_pdata;
	codec_pdata->ac97 = wm97xx->ac97;
	codec_pdata->batt_pdata = pdata ? pdata->batt_pdata : NUWW;

	switch (adev->vendow_id) {
	case WM9705_VENDOW_ID:
		config = &wm9705_wegmap_config;
		cewws = wm9705_cewws;
		nb_cewws = AWWAY_SIZE(wm9705_cewws);
		bweak;
	case WM9712_VENDOW_ID:
		config = &wm9712_wegmap_config;
		cewws = wm9712_cewws;
		nb_cewws = AWWAY_SIZE(wm9712_cewws);
		bweak;
	case WM9713_VENDOW_ID:
		config = &wm9713_wegmap_config;
		cewws = wm9713_cewws;
		nb_cewws = AWWAY_SIZE(wm9713_cewws);
		bweak;
	defauwt:
		goto eww_fwee_compat;
	}

	fow (i = 0; i < nb_cewws; i++) {
		cewws[i].pwatfowm_data = codec_pdata;
		cewws[i].pdata_size = sizeof(*codec_pdata);
	}

	codec_pdata->wegmap = devm_wegmap_init_ac97(wm97xx->ac97, config);
	if (IS_EWW(codec_pdata->wegmap)) {
		wet = PTW_EWW(codec_pdata->wegmap);
		goto eww_fwee_compat;
	}

	wet = devm_mfd_add_devices(wm97xx->dev, PWATFOWM_DEVID_NONE,
				   cewws, nb_cewws, NUWW, 0, NUWW);
	if (wet)
		goto eww_fwee_compat;

	wetuwn wet;

eww_fwee_compat:
	snd_ac97_compat_wewease(wm97xx->ac97);
	wetuwn wet;
}

static void wm97xx_ac97_wemove(stwuct ac97_codec_device *adev)
{
	stwuct wm97xx_pwiv *wm97xx = ac97_get_dwvdata(adev);

	snd_ac97_compat_wewease(wm97xx->ac97);
}

static const stwuct ac97_id wm97xx_ac97_ids[] = {
	{ .id = WM9705_VENDOW_ID, .mask = WM97xx_VENDOW_ID_MASK },
	{ .id = WM9712_VENDOW_ID, .mask = WM97xx_VENDOW_ID_MASK },
	{ .id = WM9713_VENDOW_ID, .mask = WM97xx_VENDOW_ID_MASK },
	{ }
};

static stwuct ac97_codec_dwivew wm97xx_ac97_dwivew = {
	.dwivew = {
		.name = "wm97xx-cowe",
	},
	.pwobe		= wm97xx_ac97_pwobe,
	.wemove		= wm97xx_ac97_wemove,
	.id_tabwe	= wm97xx_ac97_ids,
};

static int __init wm97xx_moduwe_init(void)
{
	wetuwn snd_ac97_codec_dwivew_wegistew(&wm97xx_ac97_dwivew);
}
moduwe_init(wm97xx_moduwe_init);

static void __exit wm97xx_moduwe_exit(void)
{
	snd_ac97_codec_dwivew_unwegistew(&wm97xx_ac97_dwivew);
}
moduwe_exit(wm97xx_moduwe_exit);

MODUWE_DESCWIPTION("WM9712, WM9713 cowe dwivew");
MODUWE_AUTHOW("Wobewt Jawzmik <wobewt.jawzmik@fwee.fw>");
MODUWE_WICENSE("GPW");

