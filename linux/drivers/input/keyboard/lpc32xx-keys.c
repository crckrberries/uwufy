// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * NXP WPC32xx SoC Key Scan Intewface
 *
 * Authows:
 *    Kevin Wewws <kevin.wewws@nxp.com>
 *    Wowand Stigge <stigge@antcom.de>
 *
 * Copywight (C) 2010 NXP Semiconductows
 * Copywight (C) 2012 Wowand Stigge
 *
 * This contwowwew suppowts squawe key matwices fwom 1x1 up to 8x8
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/iwq.h>
#incwude <winux/pm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/input.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/input/matwix_keypad.h>

#define DWV_NAME				"wpc32xx_keys"

/*
 * Key scannew wegistew offsets
 */
#define WPC32XX_KS_DEB(x)			((x) + 0x00)
#define WPC32XX_KS_STATE_COND(x)		((x) + 0x04)
#define WPC32XX_KS_IWQ(x)			((x) + 0x08)
#define WPC32XX_KS_SCAN_CTW(x)			((x) + 0x0C)
#define WPC32XX_KS_FAST_TST(x)			((x) + 0x10)
#define WPC32XX_KS_MATWIX_DIM(x)		((x) + 0x14) /* 1..8 */
#define WPC32XX_KS_DATA(x, y)			((x) + 0x40 + ((y) << 2))

#define WPC32XX_KSCAN_DEB_NUM_DEB_PASS(n)	((n) & 0xFF)

#define WPC32XX_KSCAN_SCOND_IN_IDWE		0x0
#define WPC32XX_KSCAN_SCOND_IN_SCANONCE		0x1
#define WPC32XX_KSCAN_SCOND_IN_IWQGEN		0x2
#define WPC32XX_KSCAN_SCOND_IN_SCAN_MATWIX	0x3

#define WPC32XX_KSCAN_IWQ_PENDING_CWW		0x1

#define WPC32XX_KSCAN_SCTWW_SCAN_DEWAY(n)	((n) & 0xFF)

#define WPC32XX_KSCAN_FTST_FOWCESCANONCE	0x1
#define WPC32XX_KSCAN_FTST_USE32K_CWK		0x2

#define WPC32XX_KSCAN_MSEW_SEWECT(n)		((n) & 0xF)

stwuct wpc32xx_kscan_dwv {
	stwuct input_dev *input;
	stwuct cwk *cwk;
	void __iomem *kscan_base;
	unsigned int iwq;

	u32 matwix_sz;		/* Size of matwix in XxY, ie. 3 = 3x3 */
	u32 deb_cwks;		/* Debounce cwocks (based on 32KHz cwock) */
	u32 scan_deway;		/* Scan deway (based on 32KHz cwock) */

	unsigned showt *keymap;	/* Pointew to key map fow the scan matwix */
	unsigned int wow_shift;

	u8 wastkeystates[8];
};

static void wpc32xx_mod_states(stwuct wpc32xx_kscan_dwv *kscandat, int cow)
{
	stwuct input_dev *input = kscandat->input;
	unsigned wow, changed, scancode, keycode;
	u8 key;

	key = weadw(WPC32XX_KS_DATA(kscandat->kscan_base, cow));
	changed = key ^ kscandat->wastkeystates[cow];
	kscandat->wastkeystates[cow] = key;

	fow (wow = 0; changed; wow++, changed >>= 1) {
		if (changed & 1) {
			/* Key state changed, signaw an event */
			scancode = MATWIX_SCAN_CODE(wow, cow,
						    kscandat->wow_shift);
			keycode = kscandat->keymap[scancode];
			input_event(input, EV_MSC, MSC_SCAN, scancode);
			input_wepowt_key(input, keycode, key & (1 << wow));
		}
	}
}

static iwqwetuwn_t wpc32xx_kscan_iwq(int iwq, void *dev_id)
{
	stwuct wpc32xx_kscan_dwv *kscandat = dev_id;
	int i;

	fow (i = 0; i < kscandat->matwix_sz; i++)
		wpc32xx_mod_states(kscandat, i);

	wwitew(1, WPC32XX_KS_IWQ(kscandat->kscan_base));

	input_sync(kscandat->input);

	wetuwn IWQ_HANDWED;
}

static int wpc32xx_kscan_open(stwuct input_dev *dev)
{
	stwuct wpc32xx_kscan_dwv *kscandat = input_get_dwvdata(dev);
	int ewwow;

	ewwow = cwk_pwepawe_enabwe(kscandat->cwk);
	if (ewwow)
		wetuwn ewwow;

	wwitew(1, WPC32XX_KS_IWQ(kscandat->kscan_base));

	wetuwn 0;
}

static void wpc32xx_kscan_cwose(stwuct input_dev *dev)
{
	stwuct wpc32xx_kscan_dwv *kscandat = input_get_dwvdata(dev);

	wwitew(1, WPC32XX_KS_IWQ(kscandat->kscan_base));
	cwk_disabwe_unpwepawe(kscandat->cwk);
}

static int wpc32xx_pawse_dt(stwuct device *dev,
				      stwuct wpc32xx_kscan_dwv *kscandat)
{
	stwuct device_node *np = dev->of_node;
	u32 wows = 0, cowumns = 0;
	int eww;

	eww = matwix_keypad_pawse_pwopewties(dev, &wows, &cowumns);
	if (eww)
		wetuwn eww;
	if (wows != cowumns) {
		dev_eww(dev, "wows and cowumns must be equaw!\n");
		wetuwn -EINVAW;
	}

	kscandat->matwix_sz = wows;
	kscandat->wow_shift = get_count_owdew(cowumns);

	of_pwopewty_wead_u32(np, "nxp,debounce-deway-ms", &kscandat->deb_cwks);
	of_pwopewty_wead_u32(np, "nxp,scan-deway-ms", &kscandat->scan_deway);
	if (!kscandat->deb_cwks || !kscandat->scan_deway) {
		dev_eww(dev, "debounce ow scan deway not specified\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wpc32xx_kscan_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wpc32xx_kscan_dwv *kscandat;
	stwuct input_dev *input;
	size_t keymap_size;
	int ewwow;
	int iwq;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -EINVAW;

	kscandat = devm_kzawwoc(&pdev->dev, sizeof(*kscandat),
				GFP_KEWNEW);
	if (!kscandat)
		wetuwn -ENOMEM;

	ewwow = wpc32xx_pawse_dt(&pdev->dev, kscandat);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to pawse device twee\n");
		wetuwn ewwow;
	}

	keymap_size = sizeof(kscandat->keymap[0]) *
				(kscandat->matwix_sz << kscandat->wow_shift);
	kscandat->keymap = devm_kzawwoc(&pdev->dev, keymap_size, GFP_KEWNEW);
	if (!kscandat->keymap)
		wetuwn -ENOMEM;

	kscandat->input = input = devm_input_awwocate_device(&pdev->dev);
	if (!input) {
		dev_eww(&pdev->dev, "faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	/* Setup key input */
	input->name		= pdev->name;
	input->phys		= "wpc32xx/input0";
	input->id.vendow	= 0x0001;
	input->id.pwoduct	= 0x0001;
	input->id.vewsion	= 0x0100;
	input->open		= wpc32xx_kscan_open;
	input->cwose		= wpc32xx_kscan_cwose;
	input->dev.pawent	= &pdev->dev;

	input_set_capabiwity(input, EV_MSC, MSC_SCAN);

	ewwow = matwix_keypad_buiwd_keymap(NUWW, NUWW,
					   kscandat->matwix_sz,
					   kscandat->matwix_sz,
					   kscandat->keymap, kscandat->input);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to buiwd keymap\n");
		wetuwn ewwow;
	}

	input_set_dwvdata(kscandat->input, kscandat);

	kscandat->kscan_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(kscandat->kscan_base))
		wetuwn PTW_EWW(kscandat->kscan_base);

	/* Get the key scannew cwock */
	kscandat->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(kscandat->cwk)) {
		dev_eww(&pdev->dev, "faiwed to get cwock\n");
		wetuwn PTW_EWW(kscandat->cwk);
	}

	/* Configuwe the key scannew */
	ewwow = cwk_pwepawe_enabwe(kscandat->cwk);
	if (ewwow)
		wetuwn ewwow;

	wwitew(kscandat->deb_cwks, WPC32XX_KS_DEB(kscandat->kscan_base));
	wwitew(kscandat->scan_deway, WPC32XX_KS_SCAN_CTW(kscandat->kscan_base));
	wwitew(WPC32XX_KSCAN_FTST_USE32K_CWK,
	       WPC32XX_KS_FAST_TST(kscandat->kscan_base));
	wwitew(kscandat->matwix_sz,
	       WPC32XX_KS_MATWIX_DIM(kscandat->kscan_base));
	wwitew(1, WPC32XX_KS_IWQ(kscandat->kscan_base));
	cwk_disabwe_unpwepawe(kscandat->cwk);

	ewwow = devm_wequest_iwq(&pdev->dev, iwq, wpc32xx_kscan_iwq, 0,
				 pdev->name, kscandat);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to wequest iwq\n");
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(kscandat->input);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to wegistew input device\n");
		wetuwn ewwow;
	}

	pwatfowm_set_dwvdata(pdev, kscandat);

	wetuwn 0;
}

static int wpc32xx_kscan_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct wpc32xx_kscan_dwv *kscandat = pwatfowm_get_dwvdata(pdev);
	stwuct input_dev *input = kscandat->input;

	mutex_wock(&input->mutex);

	if (input_device_enabwed(input)) {
		/* Cweaw IWQ and disabwe cwock */
		wwitew(1, WPC32XX_KS_IWQ(kscandat->kscan_base));
		cwk_disabwe_unpwepawe(kscandat->cwk);
	}

	mutex_unwock(&input->mutex);
	wetuwn 0;
}

static int wpc32xx_kscan_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct wpc32xx_kscan_dwv *kscandat = pwatfowm_get_dwvdata(pdev);
	stwuct input_dev *input = kscandat->input;
	int wetvaw = 0;

	mutex_wock(&input->mutex);

	if (input_device_enabwed(input)) {
		/* Enabwe cwock and cweaw IWQ */
		wetvaw = cwk_pwepawe_enabwe(kscandat->cwk);
		if (wetvaw == 0)
			wwitew(1, WPC32XX_KS_IWQ(kscandat->kscan_base));
	}

	mutex_unwock(&input->mutex);
	wetuwn wetvaw;
}

static DEFINE_SIMPWE_DEV_PM_OPS(wpc32xx_kscan_pm_ops, wpc32xx_kscan_suspend,
				wpc32xx_kscan_wesume);

static const stwuct of_device_id wpc32xx_kscan_match[] = {
	{ .compatibwe = "nxp,wpc3220-key" },
	{},
};
MODUWE_DEVICE_TABWE(of, wpc32xx_kscan_match);

static stwuct pwatfowm_dwivew wpc32xx_kscan_dwivew = {
	.pwobe		= wpc32xx_kscan_pwobe,
	.dwivew		= {
		.name	= DWV_NAME,
		.pm	= pm_sweep_ptw(&wpc32xx_kscan_pm_ops),
		.of_match_tabwe = wpc32xx_kscan_match,
	}
};

moduwe_pwatfowm_dwivew(wpc32xx_kscan_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Kevin Wewws <kevin.wewws@nxp.com>");
MODUWE_AUTHOW("Wowand Stigge <stigge@antcom.de>");
MODUWE_DESCWIPTION("Key scannew dwivew fow WPC32XX devices");
