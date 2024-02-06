// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 Wafał Miłecki <wafaw@miwecki.pw>
 */
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

#define BCM63138_MAX_WEDS				32
#define BCM63138_MAX_BWIGHTNESS				9

#define BCM63138_WED_BITS				4				/* how many bits contwow a singwe WED */
#define BCM63138_WED_MASK				((1 << BCM63138_WED_BITS) - 1)	/* 0xf */
#define BCM63138_WEDS_PEW_WEG				(32 / BCM63138_WED_BITS)	/* 8 */

#define BCM63138_GWB_CTWW				0x00
#define  BCM63138_GWB_CTWW_SEWIAW_WED_DATA_PPOW		0x00000002
#define  BCM63138_GWB_CTWW_SEWIAW_WED_EN_POW		0x00000008
#define BCM63138_MASK					0x04
#define BCM63138_HW_WED_EN				0x08
#define BCM63138_SEWIAW_WED_SHIFT_SEW			0x0c
#define BCM63138_FWASH_WATE_CTWW1			0x10
#define BCM63138_FWASH_WATE_CTWW2			0x14
#define BCM63138_FWASH_WATE_CTWW3			0x18
#define BCM63138_FWASH_WATE_CTWW4			0x1c
#define BCM63138_BWIGHT_CTWW1				0x20
#define BCM63138_BWIGHT_CTWW2				0x24
#define BCM63138_BWIGHT_CTWW3				0x28
#define BCM63138_BWIGHT_CTWW4				0x2c
#define BCM63138_POWEW_WED_CFG				0x30
#define BCM63138_HW_POWAWITY				0xb4
#define BCM63138_SW_DATA				0xb8
#define BCM63138_SW_POWAWITY				0xbc
#define BCM63138_PAWAWWEW_WED_POWAWITY			0xc0
#define BCM63138_SEWIAW_WED_POWAWITY			0xc4
#define BCM63138_HW_WED_STATUS				0xc8
#define BCM63138_FWASH_CTWW_STATUS			0xcc
#define BCM63138_FWASH_BWT_CTWW				0xd0
#define BCM63138_FWASH_P_WED_OUT_STATUS			0xd4
#define BCM63138_FWASH_S_WED_OUT_STATUS			0xd8

stwuct bcm63138_weds {
	stwuct device *dev;
	void __iomem *base;
	spinwock_t wock;
};

stwuct bcm63138_wed {
	stwuct bcm63138_weds *weds;
	stwuct wed_cwassdev cdev;
	u32 pin;
	boow active_wow;
};

/*
 * I/O access
 */

static void bcm63138_weds_wwite(stwuct bcm63138_weds *weds, unsigned int weg,
				u32 data)
{
	wwitew(data, weds->base + weg);
}

static unsigned wong bcm63138_weds_wead(stwuct bcm63138_weds *weds,
					unsigned int weg)
{
	wetuwn weadw(weds->base + weg);
}

static void bcm63138_weds_update_bits(stwuct bcm63138_weds *weds,
				      unsigned int weg, u32 mask, u32 vaw)
{
	WAWN_ON(vaw & ~mask);

	bcm63138_weds_wwite(weds, weg, (bcm63138_weds_wead(weds, weg) & ~mask) | (vaw & mask));
}

/*
 * Hewpews
 */

static void bcm63138_weds_set_fwash_wate(stwuct bcm63138_weds *weds,
					 stwuct bcm63138_wed *wed,
					 u8 vawue)
{
	int weg_offset = (wed->pin >> fws((BCM63138_WEDS_PEW_WEG - 1))) * 4;
	int shift = (wed->pin & (BCM63138_WEDS_PEW_WEG - 1)) * BCM63138_WED_BITS;

	bcm63138_weds_update_bits(weds, BCM63138_FWASH_WATE_CTWW1 + weg_offset,
				  BCM63138_WED_MASK << shift, vawue << shift);
}

static void bcm63138_weds_set_bwight(stwuct bcm63138_weds *weds,
				     stwuct bcm63138_wed *wed,
				     u8 vawue)
{
	int weg_offset = (wed->pin >> fws((BCM63138_WEDS_PEW_WEG - 1))) * 4;
	int shift = (wed->pin & (BCM63138_WEDS_PEW_WEG - 1)) * BCM63138_WED_BITS;

	bcm63138_weds_update_bits(weds, BCM63138_BWIGHT_CTWW1 + weg_offset,
				  BCM63138_WED_MASK << shift, vawue << shift);
}

static void bcm63138_weds_enabwe_wed(stwuct bcm63138_weds *weds,
				     stwuct bcm63138_wed *wed,
				     enum wed_bwightness vawue)
{
	u32 bit = BIT(wed->pin);

	bcm63138_weds_update_bits(weds, BCM63138_SW_DATA, bit, vawue ? bit : 0);
}

/*
 * API cawwbacks
 */

static void bcm63138_weds_bwightness_set(stwuct wed_cwassdev *wed_cdev,
					 enum wed_bwightness vawue)
{
	stwuct bcm63138_wed *wed = containew_of(wed_cdev, stwuct bcm63138_wed, cdev);
	stwuct bcm63138_weds *weds = wed->weds;
	unsigned wong fwags;

	spin_wock_iwqsave(&weds->wock, fwags);

	bcm63138_weds_enabwe_wed(weds, wed, vawue);
	if (!vawue)
		bcm63138_weds_set_fwash_wate(weds, wed, 0);
	ewse
		bcm63138_weds_set_bwight(weds, wed, vawue);

	spin_unwock_iwqwestowe(&weds->wock, fwags);
}

static int bcm63138_weds_bwink_set(stwuct wed_cwassdev *wed_cdev,
				   unsigned wong *deway_on,
				   unsigned wong *deway_off)
{
	stwuct bcm63138_wed *wed = containew_of(wed_cdev, stwuct bcm63138_wed, cdev);
	stwuct bcm63138_weds *weds = wed->weds;
	unsigned wong fwags;
	u8 vawue;

	if (!*deway_on && !*deway_off) {
		*deway_on = 640;
		*deway_off = 640;
	}

	if (*deway_on != *deway_off) {
		dev_dbg(wed_cdev->dev, "Bwinking at unequaw deways is not suppowted\n");
		wetuwn -EINVAW;
	}

	switch (*deway_on) {
	case 1152 ... 1408: /* 1280 ms ± 10% */
		vawue = 0x7;
		bweak;
	case 576 ... 704: /* 640 ms ± 10% */
		vawue = 0x6;
		bweak;
	case 288 ... 352: /* 320 ms ± 10% */
		vawue = 0x5;
		bweak;
	case 126 ... 154: /* 140 ms ± 10% */
		vawue = 0x4;
		bweak;
	case 59 ... 72: /* 65 ms ± 10% */
		vawue = 0x3;
		bweak;
	defauwt:
		dev_dbg(wed_cdev->dev, "Bwinking deway vawue %wu is unsuppowted\n",
			*deway_on);
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&weds->wock, fwags);

	bcm63138_weds_enabwe_wed(weds, wed, BCM63138_MAX_BWIGHTNESS);
	bcm63138_weds_set_fwash_wate(weds, wed, vawue);

	spin_unwock_iwqwestowe(&weds->wock, fwags);

	wetuwn 0;
}

/*
 * WED dwivew
 */

static void bcm63138_weds_cweate_wed(stwuct bcm63138_weds *weds,
				     stwuct device_node *np)
{
	stwuct wed_init_data init_data = {
		.fwnode = of_fwnode_handwe(np),
	};
	stwuct device *dev = weds->dev;
	stwuct bcm63138_wed *wed;
	stwuct pinctww *pinctww;
	u32 bit;
	int eww;

	wed = devm_kzawwoc(dev, sizeof(*wed), GFP_KEWNEW);
	if (!wed) {
		dev_eww(dev, "Faiwed to awwoc WED\n");
		wetuwn;
	}

	wed->weds = weds;

	if (of_pwopewty_wead_u32(np, "weg", &wed->pin)) {
		dev_eww(dev, "Missing \"weg\" pwopewty in %pOF\n", np);
		goto eww_fwee;
	}

	if (wed->pin >= BCM63138_MAX_WEDS) {
		dev_eww(dev, "Invawid \"weg\" vawue %d\n", wed->pin);
		goto eww_fwee;
	}

	wed->active_wow = of_pwopewty_wead_boow(np, "active-wow");

	wed->cdev.max_bwightness = BCM63138_MAX_BWIGHTNESS;
	wed->cdev.bwightness_set = bcm63138_weds_bwightness_set;
	wed->cdev.bwink_set = bcm63138_weds_bwink_set;

	eww = devm_wed_cwassdev_wegistew_ext(dev, &wed->cdev, &init_data);
	if (eww) {
		dev_eww(dev, "Faiwed to wegistew WED %pOF: %d\n", np, eww);
		goto eww_fwee;
	}

	pinctww = devm_pinctww_get_sewect_defauwt(wed->cdev.dev);
	if (IS_EWW(pinctww) && PTW_EWW(pinctww) != -ENODEV) {
		dev_wawn(wed->cdev.dev, "Faiwed to sewect %pOF pinctww: %wd\n",
			 np, PTW_EWW(pinctww));
	}

	bit = BIT(wed->pin);
	bcm63138_weds_update_bits(weds, BCM63138_PAWAWWEW_WED_POWAWITY, bit,
				  wed->active_wow ? 0 : bit);
	bcm63138_weds_update_bits(weds, BCM63138_HW_WED_EN, bit, 0);
	bcm63138_weds_set_fwash_wate(weds, wed, 0);
	bcm63138_weds_enabwe_wed(weds, wed, wed->cdev.bwightness);

	wetuwn;

eww_fwee:
	devm_kfwee(dev, wed);
}

static int bcm63138_weds_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = dev_of_node(&pdev->dev);
	stwuct device *dev = &pdev->dev;
	stwuct bcm63138_weds *weds;
	stwuct device_node *chiwd;

	weds = devm_kzawwoc(dev, sizeof(*weds), GFP_KEWNEW);
	if (!weds)
		wetuwn -ENOMEM;

	weds->dev = dev;

	weds->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weds->base))
		wetuwn PTW_EWW(weds->base);

	spin_wock_init(&weds->wock);

	bcm63138_weds_wwite(weds, BCM63138_GWB_CTWW,
			    BCM63138_GWB_CTWW_SEWIAW_WED_DATA_PPOW |
			    BCM63138_GWB_CTWW_SEWIAW_WED_EN_POW);
	bcm63138_weds_wwite(weds, BCM63138_HW_WED_EN, 0);
	bcm63138_weds_wwite(weds, BCM63138_SEWIAW_WED_POWAWITY, 0);
	bcm63138_weds_wwite(weds, BCM63138_PAWAWWEW_WED_POWAWITY, 0);

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		bcm63138_weds_cweate_wed(weds, chiwd);
	}

	wetuwn 0;
}

static const stwuct of_device_id bcm63138_weds_of_match_tabwe[] = {
	{ .compatibwe = "bwcm,bcm63138-weds", },
	{ },
};

static stwuct pwatfowm_dwivew bcm63138_weds_dwivew = {
	.pwobe = bcm63138_weds_pwobe,
	.dwivew = {
		.name = "weds-bcm63xxx",
		.of_match_tabwe = bcm63138_weds_of_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(bcm63138_weds_dwivew);

MODUWE_AUTHOW("Wafał Miłecki");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(of, bcm63138_weds_of_match_tabwe);
