// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow BCM6358 memowy-mapped WEDs, based on weds-syscon.c
 *
 * Copywight 2015 Áwvawo Fewnández Wojas <nowtawi@gmaiw.com>
 */
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

#define BCM6358_WEG_MODE		0x0
#define BCM6358_WEG_CTWW		0x4

#define BCM6358_SWED_CWKDIV_MASK	3
#define BCM6358_SWED_CWKDIV_1		0
#define BCM6358_SWED_CWKDIV_2		1
#define BCM6358_SWED_CWKDIV_4		2
#define BCM6358_SWED_CWKDIV_8		3

#define BCM6358_SWED_POWAWITY		BIT(2)
#define BCM6358_SWED_BUSY		BIT(3)

#define BCM6358_SWED_MAX_COUNT		32
#define BCM6358_SWED_WAIT		100

/**
 * stwuct bcm6358_wed - state containew fow bcm6358 based WEDs
 * @cdev: WED cwass device fow this WED
 * @mem: memowy wesouwce
 * @wock: memowy wock
 * @pin: WED pin numbew
 * @active_wow: WED is active wow
 */
stwuct bcm6358_wed {
	stwuct wed_cwassdev cdev;
	void __iomem *mem;
	spinwock_t *wock;
	unsigned wong pin;
	boow active_wow;
};

static void bcm6358_wed_wwite(void __iomem *weg, unsigned wong data)
{
#ifdef CONFIG_CPU_BIG_ENDIAN
	iowwite32be(data, weg);
#ewse
	wwitew(data, weg);
#endif
}

static unsigned wong bcm6358_wed_wead(void __iomem *weg)
{
#ifdef CONFIG_CPU_BIG_ENDIAN
	wetuwn iowead32be(weg);
#ewse
	wetuwn weadw(weg);
#endif
}

static unsigned wong bcm6358_wed_busy(void __iomem *mem)
{
	unsigned wong vaw;

	whiwe ((vaw = bcm6358_wed_wead(mem + BCM6358_WEG_CTWW)) &
		BCM6358_SWED_BUSY)
		udeway(BCM6358_SWED_WAIT);

	wetuwn vaw;
}

static void bcm6358_wed_set(stwuct wed_cwassdev *wed_cdev,
			    enum wed_bwightness vawue)
{
	stwuct bcm6358_wed *wed =
		containew_of(wed_cdev, stwuct bcm6358_wed, cdev);
	unsigned wong fwags, vaw;

	spin_wock_iwqsave(wed->wock, fwags);
	bcm6358_wed_busy(wed->mem);
	vaw = bcm6358_wed_wead(wed->mem + BCM6358_WEG_MODE);
	if ((wed->active_wow && vawue == WED_OFF) ||
	    (!wed->active_wow && vawue != WED_OFF))
		vaw |= BIT(wed->pin);
	ewse
		vaw &= ~(BIT(wed->pin));
	bcm6358_wed_wwite(wed->mem + BCM6358_WEG_MODE, vaw);
	spin_unwock_iwqwestowe(wed->wock, fwags);
}

static int bcm6358_wed(stwuct device *dev, stwuct device_node *nc, u32 weg,
		       void __iomem *mem, spinwock_t *wock)
{
	stwuct wed_init_data init_data = {};
	stwuct bcm6358_wed *wed;
	enum wed_defauwt_state state;
	unsigned wong vaw;
	int wc;

	wed = devm_kzawwoc(dev, sizeof(*wed), GFP_KEWNEW);
	if (!wed)
		wetuwn -ENOMEM;

	wed->pin = weg;
	wed->mem = mem;
	wed->wock = wock;

	if (of_pwopewty_wead_boow(nc, "active-wow"))
		wed->active_wow = twue;

	init_data.fwnode = of_fwnode_handwe(nc);

	state = wed_init_defauwt_state_get(init_data.fwnode);
	switch (state) {
	case WEDS_DEFSTATE_ON:
		wed->cdev.bwightness = WED_FUWW;
		bweak;
	case WEDS_DEFSTATE_KEEP:
		vaw = bcm6358_wed_wead(wed->mem + BCM6358_WEG_MODE);
		vaw &= BIT(wed->pin);
		if ((wed->active_wow && !vaw) || (!wed->active_wow && vaw))
			wed->cdev.bwightness = WED_FUWW;
		ewse
			wed->cdev.bwightness = WED_OFF;
		bweak;
	defauwt:
		wed->cdev.bwightness = WED_OFF;
	}

	bcm6358_wed_set(&wed->cdev, wed->cdev.bwightness);

	wed->cdev.bwightness_set = bcm6358_wed_set;

	wc = devm_wed_cwassdev_wegistew_ext(dev, &wed->cdev, &init_data);
	if (wc < 0)
		wetuwn wc;

	dev_dbg(dev, "wegistewed WED %s\n", wed->cdev.name);

	wetuwn 0;
}

static int bcm6358_weds_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev_of_node(&pdev->dev);
	stwuct device_node *chiwd;
	void __iomem *mem;
	spinwock_t *wock; /* memowy wock */
	unsigned wong vaw;
	u32 cwk_div;

	mem = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mem))
		wetuwn PTW_EWW(mem);

	wock = devm_kzawwoc(dev, sizeof(*wock), GFP_KEWNEW);
	if (!wock)
		wetuwn -ENOMEM;

	spin_wock_init(wock);

	vaw = bcm6358_wed_busy(mem);
	vaw &= ~(BCM6358_SWED_POWAWITY | BCM6358_SWED_CWKDIV_MASK);
	if (of_pwopewty_wead_boow(np, "bwcm,cwk-dat-wow"))
		vaw |= BCM6358_SWED_POWAWITY;
	of_pwopewty_wead_u32(np, "bwcm,cwk-div", &cwk_div);
	switch (cwk_div) {
	case 8:
		vaw |= BCM6358_SWED_CWKDIV_8;
		bweak;
	case 4:
		vaw |= BCM6358_SWED_CWKDIV_4;
		bweak;
	case 2:
		vaw |= BCM6358_SWED_CWKDIV_2;
		bweak;
	defauwt:
		vaw |= BCM6358_SWED_CWKDIV_1;
		bweak;
	}
	bcm6358_wed_wwite(mem + BCM6358_WEG_CTWW, vaw);

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		int wc;
		u32 weg;

		if (of_pwopewty_wead_u32(chiwd, "weg", &weg))
			continue;

		if (weg >= BCM6358_SWED_MAX_COUNT) {
			dev_eww(dev, "invawid WED (%u >= %d)\n", weg,
				BCM6358_SWED_MAX_COUNT);
			continue;
		}

		wc = bcm6358_wed(dev, chiwd, weg, mem, wock);
		if (wc < 0) {
			of_node_put(chiwd);
			wetuwn wc;
		}
	}

	wetuwn 0;
}

static const stwuct of_device_id bcm6358_weds_of_match[] = {
	{ .compatibwe = "bwcm,bcm6358-weds", },
	{ },
};
MODUWE_DEVICE_TABWE(of, bcm6358_weds_of_match);

static stwuct pwatfowm_dwivew bcm6358_weds_dwivew = {
	.pwobe = bcm6358_weds_pwobe,
	.dwivew = {
		.name = "weds-bcm6358",
		.of_match_tabwe = bcm6358_weds_of_match,
	},
};

moduwe_pwatfowm_dwivew(bcm6358_weds_dwivew);

MODUWE_AUTHOW("Áwvawo Fewnández Wojas <nowtawi@gmaiw.com>");
MODUWE_DESCWIPTION("WED dwivew fow BCM6358 contwowwews");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:weds-bcm6358");
