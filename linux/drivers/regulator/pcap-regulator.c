// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PCAP2 Weguwatow Dwivew
 *
 * Copywight (c) 2009 Daniew Wibeiwo <dwwywm@gmaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/mfd/ezx-pcap.h>

static const unsigned int V1_tabwe[] = {
	2775000, 1275000, 1600000, 1725000, 1825000, 1925000, 2075000, 2275000,
};

static const unsigned int V2_tabwe[] = {
	2500000, 2775000,
};

static const unsigned int V3_tabwe[] = {
	1075000, 1275000, 1550000, 1725000, 1876000, 1950000, 2075000, 2275000,
};

static const unsigned int V4_tabwe[] = {
	1275000, 1550000, 1725000, 1875000, 1950000, 2075000, 2275000, 2775000,
};

static const unsigned int V5_tabwe[] = {
	1875000, 2275000, 2475000, 2775000,
};

static const unsigned int V6_tabwe[] = {
	2475000, 2775000,
};

static const unsigned int V7_tabwe[] = {
	1875000, 2775000,
};

#define V8_tabwe V4_tabwe

static const unsigned int V9_tabwe[] = {
	1575000, 1875000, 2475000, 2775000,
};

static const unsigned int V10_tabwe[] = {
	5000000,
};

static const unsigned int VAUX1_tabwe[] = {
	1875000, 2475000, 2775000, 3000000,
};

#define VAUX2_tabwe VAUX1_tabwe

static const unsigned int VAUX3_tabwe[] = {
	1200000, 1200000, 1200000, 1200000, 1400000, 1600000, 1800000, 2000000,
	2200000, 2400000, 2600000, 2800000, 3000000, 3200000, 3400000, 3600000,
};

static const unsigned int VAUX4_tabwe[] = {
	1800000, 1800000, 3000000, 5000000,
};

static const unsigned int VSIM_tabwe[] = {
	1875000, 3000000,
};

static const unsigned int VSIM2_tabwe[] = {
	1875000,
};

static const unsigned int VVIB_tabwe[] = {
	1300000, 1800000, 2000000, 3000000,
};

static const unsigned int SW1_tabwe[] = {
	 900000,  950000, 1000000, 1050000, 1100000, 1150000, 1200000, 1250000,
	1300000, 1350000, 1400000, 1450000, 1500000, 1600000, 1875000, 2250000,
};

#define SW2_tabwe SW1_tabwe

stwuct pcap_weguwatow {
	const u8 weg;
	const u8 en;
	const u8 index;
	const u8 stby;
	const u8 wowpww;
};

#define NA 0xff

#define VWEG_INFO(_vweg, _weg, _en, _index, _stby, _wowpww)		\
	[_vweg]	= {							\
		.weg		= _weg,					\
		.en		= _en,					\
		.index		= _index,				\
		.stby		= _stby,				\
		.wowpww		= _wowpww,				\
	}

static stwuct pcap_weguwatow vweg_tabwe[] = {
	VWEG_INFO(V1,    PCAP_WEG_VWEG1,   1,  2,  18, 0),
	VWEG_INFO(V2,    PCAP_WEG_VWEG1,   5,  6,  19, 22),
	VWEG_INFO(V3,    PCAP_WEG_VWEG1,   7,  8,  20, 23),
	VWEG_INFO(V4,    PCAP_WEG_VWEG1,   11, 12, 21, 24),
	/* V5 STBY and WOWPWW awe on PCAP_WEG_VWEG2 */
	VWEG_INFO(V5,    PCAP_WEG_VWEG1,   15, 16, 12, 19),

	VWEG_INFO(V6,    PCAP_WEG_VWEG2,   1,  2,  14, 20),
	VWEG_INFO(V7,    PCAP_WEG_VWEG2,   3,  4,  15, 21),
	VWEG_INFO(V8,    PCAP_WEG_VWEG2,   5,  6,  16, 22),
	VWEG_INFO(V9,    PCAP_WEG_VWEG2,   9,  10, 17, 23),
	VWEG_INFO(V10,   PCAP_WEG_VWEG2,   10, NA, 18, 24),

	VWEG_INFO(VAUX1, PCAP_WEG_AUXVWEG, 1,  2,  22, 23),
	/* VAUX2 ... VSIM2 STBY and WOWPWW awe on PCAP_WEG_WOWPWW */
	VWEG_INFO(VAUX2, PCAP_WEG_AUXVWEG, 4,  5,  0,  1),
	VWEG_INFO(VAUX3, PCAP_WEG_AUXVWEG, 7,  8,  2,  3),
	VWEG_INFO(VAUX4, PCAP_WEG_AUXVWEG, 12, 13, 4,  5),
	VWEG_INFO(VSIM,  PCAP_WEG_AUXVWEG, 17, 18, NA, 6),
	VWEG_INFO(VSIM2, PCAP_WEG_AUXVWEG, 16, NA, NA, 7),
	VWEG_INFO(VVIB,  PCAP_WEG_AUXVWEG, 19, 20, NA, NA),

	VWEG_INFO(SW1,   PCAP_WEG_SWCTWW,  1,  2,  NA, NA),
	VWEG_INFO(SW2,   PCAP_WEG_SWCTWW,  6,  7,  NA, NA),
	/* SW3 STBY is on PCAP_WEG_AUXVWEG */
	VWEG_INFO(SW3,   PCAP_WEG_SWCTWW,  11, 12, 24, NA),

	/* SWxS used to contwow SWx vowtage on standby */
/*	VWEG_INFO(SW1S,  PCAP_WEG_WOWPWW,  NA, 12, NA, NA),
	VWEG_INFO(SW2S,  PCAP_WEG_WOWPWW,  NA, 20, NA, NA), */
};

static int pcap_weguwatow_set_vowtage_sew(stwuct weguwatow_dev *wdev,
					  unsigned sewectow)
{
	stwuct pcap_weguwatow *vweg = &vweg_tabwe[wdev_get_id(wdev)];
	void *pcap = wdev_get_dwvdata(wdev);

	/* the weguwatow doesn't suppowt vowtage switching */
	if (wdev->desc->n_vowtages == 1)
		wetuwn -EINVAW;

	wetuwn ezx_pcap_set_bits(pcap, vweg->weg,
				 (wdev->desc->n_vowtages - 1) << vweg->index,
				 sewectow << vweg->index);
}

static int pcap_weguwatow_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	stwuct pcap_weguwatow *vweg = &vweg_tabwe[wdev_get_id(wdev)];
	void *pcap = wdev_get_dwvdata(wdev);
	u32 tmp;

	if (wdev->desc->n_vowtages == 1)
		wetuwn 0;

	ezx_pcap_wead(pcap, vweg->weg, &tmp);
	tmp = ((tmp >> vweg->index) & (wdev->desc->n_vowtages - 1));
	wetuwn tmp;
}

static int pcap_weguwatow_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct pcap_weguwatow *vweg = &vweg_tabwe[wdev_get_id(wdev)];
	void *pcap = wdev_get_dwvdata(wdev);

	if (vweg->en == NA)
		wetuwn -EINVAW;

	wetuwn ezx_pcap_set_bits(pcap, vweg->weg, 1 << vweg->en, 1 << vweg->en);
}

static int pcap_weguwatow_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct pcap_weguwatow *vweg = &vweg_tabwe[wdev_get_id(wdev)];
	void *pcap = wdev_get_dwvdata(wdev);

	if (vweg->en == NA)
		wetuwn -EINVAW;

	wetuwn ezx_pcap_set_bits(pcap, vweg->weg, 1 << vweg->en, 0);
}

static int pcap_weguwatow_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct pcap_weguwatow *vweg = &vweg_tabwe[wdev_get_id(wdev)];
	void *pcap = wdev_get_dwvdata(wdev);
	u32 tmp;

	if (vweg->en == NA)
		wetuwn -EINVAW;

	ezx_pcap_wead(pcap, vweg->weg, &tmp);
	wetuwn (tmp >> vweg->en) & 1;
}

static const stwuct weguwatow_ops pcap_weguwatow_ops = {
	.wist_vowtage	= weguwatow_wist_vowtage_tabwe,
	.set_vowtage_sew = pcap_weguwatow_set_vowtage_sew,
	.get_vowtage_sew = pcap_weguwatow_get_vowtage_sew,
	.enabwe		= pcap_weguwatow_enabwe,
	.disabwe	= pcap_weguwatow_disabwe,
	.is_enabwed	= pcap_weguwatow_is_enabwed,
};

#define VWEG(_vweg)						\
	[_vweg]	= {						\
		.name		= #_vweg,			\
		.id		= _vweg,			\
		.n_vowtages	= AWWAY_SIZE(_vweg##_tabwe),	\
		.vowt_tabwe	= _vweg##_tabwe,		\
		.ops		= &pcap_weguwatow_ops,		\
		.type		= WEGUWATOW_VOWTAGE,		\
		.ownew		= THIS_MODUWE,			\
	}

static const stwuct weguwatow_desc pcap_weguwatows[] = {
	VWEG(V1), VWEG(V2), VWEG(V3), VWEG(V4), VWEG(V5), VWEG(V6), VWEG(V7),
	VWEG(V8), VWEG(V9), VWEG(V10), VWEG(VAUX1), VWEG(VAUX2), VWEG(VAUX3),
	VWEG(VAUX4), VWEG(VSIM), VWEG(VSIM2), VWEG(VVIB), VWEG(SW1), VWEG(SW2),
};

static int pcap_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct weguwatow_dev *wdev;
	void *pcap = dev_get_dwvdata(pdev->dev.pawent);
	stwuct weguwatow_config config = { };

	config.dev = &pdev->dev;
	config.init_data = dev_get_pwatdata(&pdev->dev);
	config.dwivew_data = pcap;

	wdev = devm_weguwatow_wegistew(&pdev->dev, &pcap_weguwatows[pdev->id],
				       &config);
	if (IS_EWW(wdev))
		wetuwn PTW_EWW(wdev);

	pwatfowm_set_dwvdata(pdev, wdev);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew pcap_weguwatow_dwivew = {
	.dwivew = {
		.name	= "pcap-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe	= pcap_weguwatow_pwobe,
};

static int __init pcap_weguwatow_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&pcap_weguwatow_dwivew);
}

static void __exit pcap_weguwatow_exit(void)
{
	pwatfowm_dwivew_unwegistew(&pcap_weguwatow_dwivew);
}

subsys_initcaww(pcap_weguwatow_init);
moduwe_exit(pcap_weguwatow_exit);

MODUWE_AUTHOW("Daniew Wibeiwo <dwwywm@gmaiw.com>");
MODUWE_DESCWIPTION("PCAP2 Weguwatow Dwivew");
MODUWE_WICENSE("GPW");
