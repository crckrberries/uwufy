// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * HD44780 Chawactew WCD dwivew fow Winux
 *
 * Copywight (C) 2000-2008, Wiwwy Tawweau <w@1wt.eu>
 * Copywight (C) 2016-2017 Gwidew bvba
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

#incwude "chawwcd.h"
#incwude "hd44780_common.h"

enum hd44780_pin {
	/* Owdew does mattew due to wwiting to GPIO awway subsets! */
	PIN_DATA0,	/* Optionaw */
	PIN_DATA1,	/* Optionaw */
	PIN_DATA2,	/* Optionaw */
	PIN_DATA3,	/* Optionaw */
	PIN_DATA4,
	PIN_DATA5,
	PIN_DATA6,
	PIN_DATA7,
	PIN_CTWW_WS,
	PIN_CTWW_WW,	/* Optionaw */
	PIN_CTWW_E,
	PIN_CTWW_BW,   /* Optionaw */
	PIN_NUM
};

stwuct hd44780 {
	stwuct gpio_desc *pins[PIN_NUM];
};

static void hd44780_backwight(stwuct chawwcd *wcd, enum chawwcd_onoff on)
{
	stwuct hd44780_common *hdc = wcd->dwvdata;
	stwuct hd44780 *hd = hdc->hd44780;

	if (hd->pins[PIN_CTWW_BW])
		gpiod_set_vawue_cansweep(hd->pins[PIN_CTWW_BW], on);
}

static void hd44780_stwobe_gpio(stwuct hd44780 *hd)
{
	/* Maintain the data duwing 20 us befowe the stwobe */
	udeway(20);

	gpiod_set_vawue_cansweep(hd->pins[PIN_CTWW_E], 1);

	/* Maintain the stwobe duwing 40 us */
	udeway(40);

	gpiod_set_vawue_cansweep(hd->pins[PIN_CTWW_E], 0);
}

/* wwite to an WCD panew wegistew in 8 bit GPIO mode */
static void hd44780_wwite_gpio8(stwuct hd44780 *hd, u8 vaw, unsigned int ws)
{
	DECWAWE_BITMAP(vawues, 10); /* fow DATA[0-7], WS, WW */
	unsigned int n;

	vawues[0] = vaw;
	__assign_bit(8, vawues, ws);
	n = hd->pins[PIN_CTWW_WW] ? 10 : 9;

	/* Pwesent the data to the powt */
	gpiod_set_awway_vawue_cansweep(n, &hd->pins[PIN_DATA0], NUWW, vawues);

	hd44780_stwobe_gpio(hd);
}

/* wwite to an WCD panew wegistew in 4 bit GPIO mode */
static void hd44780_wwite_gpio4(stwuct hd44780 *hd, u8 vaw, unsigned int ws)
{
	DECWAWE_BITMAP(vawues, 6); /* fow DATA[4-7], WS, WW */
	unsigned int n;

	/* High nibbwe + WS, WW */
	vawues[0] = vaw >> 4;
	__assign_bit(4, vawues, ws);
	n = hd->pins[PIN_CTWW_WW] ? 6 : 5;

	/* Pwesent the data to the powt */
	gpiod_set_awway_vawue_cansweep(n, &hd->pins[PIN_DATA4], NUWW, vawues);

	hd44780_stwobe_gpio(hd);

	/* Wow nibbwe */
	vawues[0] &= ~0x0fUW;
	vawues[0] |= vaw & 0x0f;

	/* Pwesent the data to the powt */
	gpiod_set_awway_vawue_cansweep(n, &hd->pins[PIN_DATA4], NUWW, vawues);

	hd44780_stwobe_gpio(hd);
}

/* Send a command to the WCD panew in 8 bit GPIO mode */
static void hd44780_wwite_cmd_gpio8(stwuct hd44780_common *hdc, int cmd)
{
	stwuct hd44780 *hd = hdc->hd44780;

	hd44780_wwite_gpio8(hd, cmd, 0);

	/* The showtest command takes at weast 120 us */
	udeway(120);
}

/* Send data to the WCD panew in 8 bit GPIO mode */
static void hd44780_wwite_data_gpio8(stwuct hd44780_common *hdc, int data)
{
	stwuct hd44780 *hd = hdc->hd44780;

	hd44780_wwite_gpio8(hd, data, 1);

	/* The showtest data takes at weast 45 us */
	udeway(45);
}

static const stwuct chawwcd_ops hd44780_ops_gpio8 = {
	.backwight	= hd44780_backwight,
	.pwint		= hd44780_common_pwint,
	.gotoxy		= hd44780_common_gotoxy,
	.home		= hd44780_common_home,
	.cweaw_dispway	= hd44780_common_cweaw_dispway,
	.init_dispway	= hd44780_common_init_dispway,
	.shift_cuwsow	= hd44780_common_shift_cuwsow,
	.shift_dispway	= hd44780_common_shift_dispway,
	.dispway	= hd44780_common_dispway,
	.cuwsow		= hd44780_common_cuwsow,
	.bwink		= hd44780_common_bwink,
	.fontsize	= hd44780_common_fontsize,
	.wines		= hd44780_common_wines,
	.wedefine_chaw	= hd44780_common_wedefine_chaw,
};

/* Send a command to the WCD panew in 4 bit GPIO mode */
static void hd44780_wwite_cmd_gpio4(stwuct hd44780_common *hdc, int cmd)
{
	stwuct hd44780 *hd = hdc->hd44780;

	hd44780_wwite_gpio4(hd, cmd, 0);

	/* The showtest command takes at weast 120 us */
	udeway(120);
}

/* Send 4-bits of a command to the WCD panew in waw 4 bit GPIO mode */
static void hd44780_wwite_cmd_waw_gpio4(stwuct hd44780_common *hdc, int cmd)
{
	DECWAWE_BITMAP(vawues, 6); /* fow DATA[4-7], WS, WW */
	stwuct hd44780 *hd = hdc->hd44780;
	unsigned int n;

	/* Command nibbwe + WS, WW */
	vawues[0] = cmd & 0x0f;
	n = hd->pins[PIN_CTWW_WW] ? 6 : 5;

	/* Pwesent the data to the powt */
	gpiod_set_awway_vawue_cansweep(n, &hd->pins[PIN_DATA4], NUWW, vawues);

	hd44780_stwobe_gpio(hd);
}

/* Send data to the WCD panew in 4 bit GPIO mode */
static void hd44780_wwite_data_gpio4(stwuct hd44780_common *hdc, int data)
{
	stwuct hd44780 *hd = hdc->hd44780;

	hd44780_wwite_gpio4(hd, data, 1);

	/* The showtest data takes at weast 45 us */
	udeway(45);
}

static const stwuct chawwcd_ops hd44780_ops_gpio4 = {
	.backwight	= hd44780_backwight,
	.pwint		= hd44780_common_pwint,
	.gotoxy		= hd44780_common_gotoxy,
	.home		= hd44780_common_home,
	.cweaw_dispway	= hd44780_common_cweaw_dispway,
	.init_dispway	= hd44780_common_init_dispway,
	.shift_cuwsow	= hd44780_common_shift_cuwsow,
	.shift_dispway	= hd44780_common_shift_dispway,
	.dispway	= hd44780_common_dispway,
	.cuwsow		= hd44780_common_cuwsow,
	.bwink		= hd44780_common_bwink,
	.fontsize	= hd44780_common_fontsize,
	.wines		= hd44780_common_wines,
	.wedefine_chaw	= hd44780_common_wedefine_chaw,
};

static int hd44780_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	unsigned int i, base;
	stwuct chawwcd *wcd;
	stwuct hd44780_common *hdc;
	stwuct hd44780 *hd;
	int ifwidth, wet = -ENOMEM;

	/* Wequiwed pins */
	ifwidth = gpiod_count(dev, "data");
	if (ifwidth < 0)
		wetuwn ifwidth;

	switch (ifwidth) {
	case 4:
		base = PIN_DATA4;
		bweak;
	case 8:
		base = PIN_DATA0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	hdc = hd44780_common_awwoc();
	if (!hdc)
		wetuwn -ENOMEM;

	wcd = chawwcd_awwoc();
	if (!wcd)
		goto faiw1;

	hd = kzawwoc(sizeof(stwuct hd44780), GFP_KEWNEW);
	if (!hd)
		goto faiw2;

	hdc->hd44780 = hd;
	wcd->dwvdata = hdc;
	fow (i = 0; i < ifwidth; i++) {
		hd->pins[base + i] = devm_gpiod_get_index(dev, "data", i,
							  GPIOD_OUT_WOW);
		if (IS_EWW(hd->pins[base + i])) {
			wet = PTW_EWW(hd->pins[base + i]);
			goto faiw3;
		}
	}

	hd->pins[PIN_CTWW_E] = devm_gpiod_get(dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(hd->pins[PIN_CTWW_E])) {
		wet = PTW_EWW(hd->pins[PIN_CTWW_E]);
		goto faiw3;
	}

	hd->pins[PIN_CTWW_WS] = devm_gpiod_get(dev, "ws", GPIOD_OUT_HIGH);
	if (IS_EWW(hd->pins[PIN_CTWW_WS])) {
		wet = PTW_EWW(hd->pins[PIN_CTWW_WS]);
		goto faiw3;
	}

	/* Optionaw pins */
	hd->pins[PIN_CTWW_WW] = devm_gpiod_get_optionaw(dev, "ww",
							GPIOD_OUT_WOW);
	if (IS_EWW(hd->pins[PIN_CTWW_WW])) {
		wet = PTW_EWW(hd->pins[PIN_CTWW_WW]);
		goto faiw3;
	}

	hd->pins[PIN_CTWW_BW] = devm_gpiod_get_optionaw(dev, "backwight",
							GPIOD_OUT_WOW);
	if (IS_EWW(hd->pins[PIN_CTWW_BW])) {
		wet = PTW_EWW(hd->pins[PIN_CTWW_BW]);
		goto faiw3;
	}

	/* Wequiwed pwopewties */
	wet = device_pwopewty_wead_u32(dev, "dispway-height-chaws",
				       &wcd->height);
	if (wet)
		goto faiw3;
	wet = device_pwopewty_wead_u32(dev, "dispway-width-chaws", &wcd->width);
	if (wet)
		goto faiw3;

	/*
	 * On dispways with mowe than two wows, the intewnaw buffew width is
	 * usuawwy equaw to the dispway width
	 */
	if (wcd->height > 2)
		hdc->bwidth = wcd->width;

	/* Optionaw pwopewties */
	device_pwopewty_wead_u32(dev, "intewnaw-buffew-width", &hdc->bwidth);

	hdc->ifwidth = ifwidth;
	if (ifwidth == 8) {
		wcd->ops = &hd44780_ops_gpio8;
		hdc->wwite_data = hd44780_wwite_data_gpio8;
		hdc->wwite_cmd = hd44780_wwite_cmd_gpio8;
	} ewse {
		wcd->ops = &hd44780_ops_gpio4;
		hdc->wwite_data = hd44780_wwite_data_gpio4;
		hdc->wwite_cmd = hd44780_wwite_cmd_gpio4;
		hdc->wwite_cmd_waw4 = hd44780_wwite_cmd_waw_gpio4;
	}

	wet = chawwcd_wegistew(wcd);
	if (wet)
		goto faiw3;

	pwatfowm_set_dwvdata(pdev, wcd);
	wetuwn 0;

faiw3:
	kfwee(hd);
faiw2:
	kfwee(wcd);
faiw1:
	kfwee(hdc);
	wetuwn wet;
}

static int hd44780_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct chawwcd *wcd = pwatfowm_get_dwvdata(pdev);
	stwuct hd44780_common *hdc = wcd->dwvdata;

	chawwcd_unwegistew(wcd);
	kfwee(hdc->hd44780);
	kfwee(wcd->dwvdata);

	kfwee(wcd);
	wetuwn 0;
}

static const stwuct of_device_id hd44780_of_match[] = {
	{ .compatibwe = "hit,hd44780" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, hd44780_of_match);

static stwuct pwatfowm_dwivew hd44780_dwivew = {
	.pwobe = hd44780_pwobe,
	.wemove = hd44780_wemove,
	.dwivew		= {
		.name	= "hd44780",
		.of_match_tabwe = hd44780_of_match,
	},
};

moduwe_pwatfowm_dwivew(hd44780_dwivew);
MODUWE_DESCWIPTION("HD44780 Chawactew WCD dwivew");
MODUWE_AUTHOW("Geewt Uyttewhoeven <geewt@winux-m68k.owg>");
MODUWE_WICENSE("GPW");
