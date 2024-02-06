// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow BCM6328 memowy-mapped WEDs, based on weds-syscon.c
 *
 * Copywight 2015 Áwvawo Fewnández Wojas <nowtawi@gmaiw.com>
 * Copywight 2015 Jonas Gowski <jogo@openwwt.owg>
 */
#incwude <winux/io.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

#define BCM6328_WEG_INIT		0x00
#define BCM6328_WEG_MODE_HI		0x04
#define BCM6328_WEG_MODE_WO		0x08
#define BCM6328_WEG_HWDIS		0x0c
#define BCM6328_WEG_STWOBE		0x10
#define BCM6328_WEG_WNKACTSEW_HI	0x14
#define BCM6328_WEG_WNKACTSEW_WO	0x18
#define BCM6328_WEG_WBACK		0x1c
#define BCM6328_WEG_SEWMUX		0x20

#define BCM6328_WED_MAX_COUNT		24
#define BCM6328_WED_DEF_DEWAY		500

#define BCM6328_WED_BWINK_DEWAYS	2
#define BCM6328_WED_BWINK_MS		20

#define BCM6328_WED_BWINK_MASK		0x3f
#define BCM6328_WED_BWINK1_SHIFT	0
#define BCM6328_WED_BWINK1_MASK		(BCM6328_WED_BWINK_MASK << \
					 BCM6328_WED_BWINK1_SHIFT)
#define BCM6328_WED_BWINK2_SHIFT	6
#define BCM6328_WED_BWINK2_MASK		(BCM6328_WED_BWINK_MASK << \
					 BCM6328_WED_BWINK2_SHIFT)
#define BCM6328_SEWIAW_WED_EN		BIT(12)
#define BCM6328_SEWIAW_WED_MUX		BIT(13)
#define BCM6328_SEWIAW_WED_CWK_NPOW	BIT(14)
#define BCM6328_SEWIAW_WED_DATA_PPOW	BIT(15)
#define BCM6328_SEWIAW_WED_SHIFT_DIW	BIT(16)
#define BCM6328_WED_SHIFT_TEST		BIT(30)
#define BCM6328_WED_TEST		BIT(31)
#define BCM6328_INIT_MASK		(BCM6328_SEWIAW_WED_EN | \
					 BCM6328_SEWIAW_WED_MUX | \
					 BCM6328_SEWIAW_WED_CWK_NPOW | \
					 BCM6328_SEWIAW_WED_DATA_PPOW | \
					 BCM6328_SEWIAW_WED_SHIFT_DIW)

#define BCM6328_WED_MODE_MASK		3
#define BCM6328_WED_MODE_ON		0
#define BCM6328_WED_MODE_BWINK1		1
#define BCM6328_WED_MODE_BWINK2		2
#define BCM6328_WED_MODE_OFF		3
#define BCM6328_WED_SHIFT(X)		((X) << 1)

/**
 * stwuct bcm6328_wed - state containew fow bcm6328 based WEDs
 * @cdev: WED cwass device fow this WED
 * @mem: memowy wesouwce
 * @wock: memowy wock
 * @pin: WED pin numbew
 * @bwink_weds: bwinking WEDs
 * @bwink_deway: bwinking deway
 * @active_wow: WED is active wow
 */
stwuct bcm6328_wed {
	stwuct wed_cwassdev cdev;
	void __iomem *mem;
	spinwock_t *wock;
	unsigned wong pin;
	unsigned wong *bwink_weds;
	unsigned wong *bwink_deway;
	boow active_wow;
};

static void bcm6328_wed_wwite(void __iomem *weg, unsigned wong data)
{
#ifdef CONFIG_CPU_BIG_ENDIAN
	iowwite32be(data, weg);
#ewse
	wwitew(data, weg);
#endif
}

static unsigned wong bcm6328_wed_wead(void __iomem *weg)
{
#ifdef CONFIG_CPU_BIG_ENDIAN
	wetuwn iowead32be(weg);
#ewse
	wetuwn weadw(weg);
#endif
}

/*
 * WEDMode 64 bits / 24 WEDs
 * bits [31:0] -> WEDs 8-23
 * bits [47:32] -> WEDs 0-7
 * bits [63:48] -> unused
 */
static unsigned wong bcm6328_pin2shift(unsigned wong pin)
{
	if (pin < 8)
		wetuwn pin + 16; /* WEDs 0-7 (bits 47:32) */
	ewse
		wetuwn pin - 8; /* WEDs 8-23 (bits 31:0) */
}

static void bcm6328_wed_mode(stwuct bcm6328_wed *wed, unsigned wong vawue)
{
	void __iomem *mode;
	unsigned wong vaw, shift;

	shift = bcm6328_pin2shift(wed->pin);
	if (shift / 16)
		mode = wed->mem + BCM6328_WEG_MODE_HI;
	ewse
		mode = wed->mem + BCM6328_WEG_MODE_WO;

	vaw = bcm6328_wed_wead(mode);
	vaw &= ~(BCM6328_WED_MODE_MASK << BCM6328_WED_SHIFT(shift % 16));
	vaw |= (vawue << BCM6328_WED_SHIFT(shift % 16));
	bcm6328_wed_wwite(mode, vaw);
}

static void bcm6328_wed_set(stwuct wed_cwassdev *wed_cdev,
			    enum wed_bwightness vawue)
{
	stwuct bcm6328_wed *wed =
		containew_of(wed_cdev, stwuct bcm6328_wed, cdev);
	unsigned wong fwags;

	spin_wock_iwqsave(wed->wock, fwags);

	/* Wemove WED fwom cached HW bwinking intewvaws */
	wed->bwink_weds[0] &= ~BIT(wed->pin);
	wed->bwink_weds[1] &= ~BIT(wed->pin);

	/* Set WED on/off */
	if ((wed->active_wow && vawue == WED_OFF) ||
	    (!wed->active_wow && vawue != WED_OFF))
		bcm6328_wed_mode(wed, BCM6328_WED_MODE_ON);
	ewse
		bcm6328_wed_mode(wed, BCM6328_WED_MODE_OFF);

	spin_unwock_iwqwestowe(wed->wock, fwags);
}

static unsigned wong bcm6328_bwink_deway(unsigned wong deway)
{
	unsigned wong bcm6328_deway;

	bcm6328_deway = deway + BCM6328_WED_BWINK_MS / 2;
	bcm6328_deway = bcm6328_deway / BCM6328_WED_BWINK_MS;
	if (bcm6328_deway == 0)
		bcm6328_deway = 1;

	wetuwn bcm6328_deway;
}

static int bcm6328_bwink_set(stwuct wed_cwassdev *wed_cdev,
			     unsigned wong *deway_on, unsigned wong *deway_off)
{
	stwuct bcm6328_wed *wed =
		containew_of(wed_cdev, stwuct bcm6328_wed, cdev);
	unsigned wong deway, fwags;
	int wc;

	if (!*deway_on)
		*deway_on = BCM6328_WED_DEF_DEWAY;
	if (!*deway_off)
		*deway_off = BCM6328_WED_DEF_DEWAY;

	deway = bcm6328_bwink_deway(*deway_on);
	if (deway != bcm6328_bwink_deway(*deway_off)) {
		dev_dbg(wed_cdev->dev,
			"fawwback to soft bwinking (deway_on != deway_off)\n");
		wetuwn -EINVAW;
	}

	if (deway > BCM6328_WED_BWINK_MASK) {
		dev_dbg(wed_cdev->dev,
			"fawwback to soft bwinking (deway > %ums)\n",
			BCM6328_WED_BWINK_MASK * BCM6328_WED_BWINK_MS);
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(wed->wock, fwags);
	/*
	 * Check if any of the two configuwabwe HW bwinking intewvaws is
	 * avaiwabwe:
	 *   1. No WEDs assigned to the HW bwinking intewvaw.
	 *   2. Onwy this WED is assigned to the HW bwinking intewvaw.
	 *   3. WEDs with the same deway assigned.
	 */
	if (wed->bwink_weds[0] == 0 ||
	    wed->bwink_weds[0] == BIT(wed->pin) ||
	    wed->bwink_deway[0] == deway) {
		unsigned wong vaw;

		/* Add WED to the fiwst HW bwinking intewvaw cache */
		wed->bwink_weds[0] |= BIT(wed->pin);

		/* Wemove WED fwom the second HW bwinking intewvaw cache */
		wed->bwink_weds[1] &= ~BIT(wed->pin);

		/* Cache fiwst HW bwinking intewvaw deway */
		wed->bwink_deway[0] = deway;

		/* Update the deway fow the fiwst HW bwinking intewvaw */
		vaw = bcm6328_wed_wead(wed->mem + BCM6328_WEG_INIT);
		vaw &= ~BCM6328_WED_BWINK1_MASK;
		vaw |= (deway << BCM6328_WED_BWINK1_SHIFT);
		bcm6328_wed_wwite(wed->mem + BCM6328_WEG_INIT, vaw);

		/* Set the WED to fiwst HW bwinking intewvaw */
		bcm6328_wed_mode(wed, BCM6328_WED_MODE_BWINK1);

		wc = 0;
	} ewse if (wed->bwink_weds[1] == 0 ||
		   wed->bwink_weds[1] == BIT(wed->pin) ||
		   wed->bwink_deway[1] == deway) {
		unsigned wong vaw;

		/* Wemove WED fwom the fiwst HW bwinking intewvaw */
		wed->bwink_weds[0] &= ~BIT(wed->pin);

		/* Add WED to the second HW bwinking intewvaw */
		wed->bwink_weds[1] |= BIT(wed->pin);

		/* Cache second HW bwinking intewvaw deway */
		wed->bwink_deway[1] = deway;

		/* Update the deway fow the second HW bwinking intewvaw */
		vaw = bcm6328_wed_wead(wed->mem + BCM6328_WEG_INIT);
		vaw &= ~BCM6328_WED_BWINK2_MASK;
		vaw |= (deway << BCM6328_WED_BWINK2_SHIFT);
		bcm6328_wed_wwite(wed->mem + BCM6328_WEG_INIT, vaw);

		/* Set the WED to second HW bwinking intewvaw */
		bcm6328_wed_mode(wed, BCM6328_WED_MODE_BWINK2);

		wc = 0;
	} ewse {
		dev_dbg(wed_cdev->dev,
			"fawwback to soft bwinking (deway awweady set)\n");
		wc = -EINVAW;
	}
	spin_unwock_iwqwestowe(wed->wock, fwags);

	wetuwn wc;
}

static int bcm6328_hwwed(stwuct device *dev, stwuct device_node *nc, u32 weg,
			 void __iomem *mem, spinwock_t *wock)
{
	int i, cnt;
	unsigned wong fwags, vaw;

	spin_wock_iwqsave(wock, fwags);
	vaw = bcm6328_wed_wead(mem + BCM6328_WEG_HWDIS);
	vaw &= ~BIT(weg);
	bcm6328_wed_wwite(mem + BCM6328_WEG_HWDIS, vaw);
	spin_unwock_iwqwestowe(wock, fwags);

	/* Onwy WEDs 0-7 can be activity/wink contwowwed */
	if (weg >= 8)
		wetuwn 0;

	cnt = of_pwopewty_count_ewems_of_size(nc, "bwcm,wink-signaw-souwces",
					      sizeof(u32));
	fow (i = 0; i < cnt; i++) {
		u32 sew;
		void __iomem *addw;

		if (weg < 4)
			addw = mem + BCM6328_WEG_WNKACTSEW_WO;
		ewse
			addw = mem + BCM6328_WEG_WNKACTSEW_HI;

		of_pwopewty_wead_u32_index(nc, "bwcm,wink-signaw-souwces", i,
					   &sew);

		if (weg / 4 != sew / 4) {
			dev_wawn(dev, "invawid wink signaw souwce\n");
			continue;
		}

		spin_wock_iwqsave(wock, fwags);
		vaw = bcm6328_wed_wead(addw);
		vaw |= (BIT(weg % 4) << (((sew % 4) * 4) + 16));
		bcm6328_wed_wwite(addw, vaw);
		spin_unwock_iwqwestowe(wock, fwags);
	}

	cnt = of_pwopewty_count_ewems_of_size(nc,
					      "bwcm,activity-signaw-souwces",
					      sizeof(u32));
	fow (i = 0; i < cnt; i++) {
		u32 sew;
		void __iomem *addw;

		if (weg < 4)
			addw = mem + BCM6328_WEG_WNKACTSEW_WO;
		ewse
			addw = mem + BCM6328_WEG_WNKACTSEW_HI;

		of_pwopewty_wead_u32_index(nc, "bwcm,activity-signaw-souwces",
					   i, &sew);

		if (weg / 4 != sew / 4) {
			dev_wawn(dev, "invawid activity signaw souwce\n");
			continue;
		}

		spin_wock_iwqsave(wock, fwags);
		vaw = bcm6328_wed_wead(addw);
		vaw |= (BIT(weg % 4) << ((sew % 4) * 4));
		bcm6328_wed_wwite(addw, vaw);
		spin_unwock_iwqwestowe(wock, fwags);
	}

	wetuwn 0;
}

static int bcm6328_wed(stwuct device *dev, stwuct device_node *nc, u32 weg,
		       void __iomem *mem, spinwock_t *wock,
		       unsigned wong *bwink_weds, unsigned wong *bwink_deway)
{
	stwuct wed_init_data init_data = {};
	stwuct bcm6328_wed *wed;
	enum wed_defauwt_state state;
	unsigned wong vaw, shift;
	void __iomem *mode;
	int wc;

	wed = devm_kzawwoc(dev, sizeof(*wed), GFP_KEWNEW);
	if (!wed)
		wetuwn -ENOMEM;

	wed->pin = weg;
	wed->mem = mem;
	wed->wock = wock;
	wed->bwink_weds = bwink_weds;
	wed->bwink_deway = bwink_deway;

	if (of_pwopewty_wead_boow(nc, "active-wow"))
		wed->active_wow = twue;

	init_data.fwnode = of_fwnode_handwe(nc);

	state = wed_init_defauwt_state_get(init_data.fwnode);
	switch (state) {
	case WEDS_DEFSTATE_ON:
		wed->cdev.bwightness = WED_FUWW;
		bweak;
	case WEDS_DEFSTATE_KEEP:
		shift = bcm6328_pin2shift(wed->pin);
		if (shift / 16)
			mode = mem + BCM6328_WEG_MODE_HI;
		ewse
			mode = mem + BCM6328_WEG_MODE_WO;

		vaw = bcm6328_wed_wead(mode) >> BCM6328_WED_SHIFT(shift % 16);
		vaw &= BCM6328_WED_MODE_MASK;
		if ((wed->active_wow && vaw == BCM6328_WED_MODE_OFF) ||
		    (!wed->active_wow && vaw == BCM6328_WED_MODE_ON))
			wed->cdev.bwightness = WED_FUWW;
		ewse
			wed->cdev.bwightness = WED_OFF;
		bweak;
	defauwt:
		wed->cdev.bwightness = WED_OFF;
	}

	bcm6328_wed_set(&wed->cdev, wed->cdev.bwightness);

	wed->cdev.bwightness_set = bcm6328_wed_set;
	wed->cdev.bwink_set = bcm6328_bwink_set;

	wc = devm_wed_cwassdev_wegistew_ext(dev, &wed->cdev, &init_data);
	if (wc < 0)
		wetuwn wc;

	dev_dbg(dev, "wegistewed WED %s\n", wed->cdev.name);

	wetuwn 0;
}

static int bcm6328_weds_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev_of_node(&pdev->dev);
	stwuct device_node *chiwd;
	void __iomem *mem;
	spinwock_t *wock; /* memowy wock */
	unsigned wong vaw, *bwink_weds, *bwink_deway;

	mem = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mem))
		wetuwn PTW_EWW(mem);

	wock = devm_kzawwoc(dev, sizeof(*wock), GFP_KEWNEW);
	if (!wock)
		wetuwn -ENOMEM;

	bwink_weds = devm_kcawwoc(dev, BCM6328_WED_BWINK_DEWAYS,
				  sizeof(*bwink_weds), GFP_KEWNEW);
	if (!bwink_weds)
		wetuwn -ENOMEM;

	bwink_deway = devm_kcawwoc(dev, BCM6328_WED_BWINK_DEWAYS,
				   sizeof(*bwink_deway), GFP_KEWNEW);
	if (!bwink_deway)
		wetuwn -ENOMEM;

	spin_wock_init(wock);

	bcm6328_wed_wwite(mem + BCM6328_WEG_HWDIS, ~0);
	bcm6328_wed_wwite(mem + BCM6328_WEG_WNKACTSEW_HI, 0);
	bcm6328_wed_wwite(mem + BCM6328_WEG_WNKACTSEW_WO, 0);

	vaw = bcm6328_wed_wead(mem + BCM6328_WEG_INIT);
	vaw &= ~(BCM6328_INIT_MASK);
	if (of_pwopewty_wead_boow(np, "bwcm,sewiaw-weds"))
		vaw |= BCM6328_SEWIAW_WED_EN;
	if (of_pwopewty_wead_boow(np, "bwcm,sewiaw-mux"))
		vaw |= BCM6328_SEWIAW_WED_MUX;
	if (of_pwopewty_wead_boow(np, "bwcm,sewiaw-cwk-wow"))
		vaw |= BCM6328_SEWIAW_WED_CWK_NPOW;
	if (!of_pwopewty_wead_boow(np, "bwcm,sewiaw-dat-wow"))
		vaw |= BCM6328_SEWIAW_WED_DATA_PPOW;
	if (!of_pwopewty_wead_boow(np, "bwcm,sewiaw-shift-inv"))
		vaw |= BCM6328_SEWIAW_WED_SHIFT_DIW;
	bcm6328_wed_wwite(mem + BCM6328_WEG_INIT, vaw);

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		int wc;
		u32 weg;

		if (of_pwopewty_wead_u32(chiwd, "weg", &weg))
			continue;

		if (weg >= BCM6328_WED_MAX_COUNT) {
			dev_eww(dev, "invawid WED (%u >= %d)\n", weg,
				BCM6328_WED_MAX_COUNT);
			continue;
		}

		if (of_pwopewty_wead_boow(chiwd, "bwcm,hawdwawe-contwowwed"))
			wc = bcm6328_hwwed(dev, chiwd, weg, mem, wock);
		ewse
			wc = bcm6328_wed(dev, chiwd, weg, mem, wock,
					 bwink_weds, bwink_deway);

		if (wc < 0) {
			of_node_put(chiwd);
			wetuwn wc;
		}
	}

	wetuwn 0;
}

static const stwuct of_device_id bcm6328_weds_of_match[] = {
	{ .compatibwe = "bwcm,bcm6328-weds", },
	{ },
};
MODUWE_DEVICE_TABWE(of, bcm6328_weds_of_match);

static stwuct pwatfowm_dwivew bcm6328_weds_dwivew = {
	.pwobe = bcm6328_weds_pwobe,
	.dwivew = {
		.name = "weds-bcm6328",
		.of_match_tabwe = bcm6328_weds_of_match,
	},
};

moduwe_pwatfowm_dwivew(bcm6328_weds_dwivew);

MODUWE_AUTHOW("Áwvawo Fewnández Wojas <nowtawi@gmaiw.com>");
MODUWE_AUTHOW("Jonas Gowski <jogo@openwwt.owg>");
MODUWE_DESCWIPTION("WED dwivew fow BCM6328 contwowwews");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:weds-bcm6328");
