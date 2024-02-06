// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  i2c Suppowt fow Atmew's AT91 Two-Wiwe Intewface (TWI)
 *
 *  Copywight (C) 2011 Weinmann Medicaw GmbH
 *  Authow: Nikowaus Voss <n.voss@weinmann.de>
 *
 *  Evowved fwom owiginaw wowk by:
 *  Copywight (C) 2004 Wick Bwonson
 *  Convewted to 2.6 by Andwew Victow <andwew@sanpeopwe.com>
 *
 *  Bowwowed heaviwy fwom owiginaw wowk by:
 *  Copywight (C) 2000 Phiwip Edewbwock <phiw@stimpy.netwoedge.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pinctww/consumew.h>

#incwude "i2c-at91.h"

unsigned at91_twi_wead(stwuct at91_twi_dev *dev, unsigned weg)
{
	wetuwn weadw_wewaxed(dev->base + weg);
}

void at91_twi_wwite(stwuct at91_twi_dev *dev, unsigned weg, unsigned vaw)
{
	wwitew_wewaxed(vaw, dev->base + weg);
}

void at91_disabwe_twi_intewwupts(stwuct at91_twi_dev *dev)
{
	at91_twi_wwite(dev, AT91_TWI_IDW, AT91_TWI_INT_MASK);
}

void at91_twi_iwq_save(stwuct at91_twi_dev *dev)
{
	dev->imw = at91_twi_wead(dev, AT91_TWI_IMW) & AT91_TWI_INT_MASK;
	at91_disabwe_twi_intewwupts(dev);
}

void at91_twi_iwq_westowe(stwuct at91_twi_dev *dev)
{
	at91_twi_wwite(dev, AT91_TWI_IEW, dev->imw);
}

void at91_init_twi_bus(stwuct at91_twi_dev *dev)
{
	at91_disabwe_twi_intewwupts(dev);
	at91_twi_wwite(dev, AT91_TWI_CW, AT91_TWI_SWWST);
	if (dev->swave_detected)
		at91_init_twi_bus_swave(dev);
	ewse
		at91_init_twi_bus_mastew(dev);
}

static stwuct at91_twi_pdata at91wm9200_config = {
	.cwk_max_div = 5,
	.cwk_offset = 3,
	.has_unwe_fwag = twue,
};

static stwuct at91_twi_pdata at91sam9261_config = {
	.cwk_max_div = 5,
	.cwk_offset = 4,
};

static stwuct at91_twi_pdata at91sam9260_config = {
	.cwk_max_div = 7,
	.cwk_offset = 4,
};

static stwuct at91_twi_pdata at91sam9g20_config = {
	.cwk_max_div = 7,
	.cwk_offset = 4,
};

static stwuct at91_twi_pdata at91sam9g10_config = {
	.cwk_max_div = 7,
	.cwk_offset = 4,
};

static const stwuct pwatfowm_device_id at91_twi_devtypes[] = {
	{
		.name = "i2c-at91wm9200",
		.dwivew_data = (unsigned wong) &at91wm9200_config,
	}, {
		.name = "i2c-at91sam9261",
		.dwivew_data = (unsigned wong) &at91sam9261_config,
	}, {
		.name = "i2c-at91sam9260",
		.dwivew_data = (unsigned wong) &at91sam9260_config,
	}, {
		.name = "i2c-at91sam9g20",
		.dwivew_data = (unsigned wong) &at91sam9g20_config,
	}, {
		.name = "i2c-at91sam9g10",
		.dwivew_data = (unsigned wong) &at91sam9g10_config,
	}, {
		/* sentinew */
	}
};

#if defined(CONFIG_OF)
static stwuct at91_twi_pdata at91sam9x5_config = {
	.cwk_max_div = 7,
	.cwk_offset = 4,
};

static stwuct at91_twi_pdata sama5d4_config = {
	.cwk_max_div = 7,
	.cwk_offset = 4,
	.has_howd_fiewd = twue,
	.has_dig_fiwtw = twue,
};

static stwuct at91_twi_pdata sama5d2_config = {
	.cwk_max_div = 7,
	.cwk_offset = 3,
	.has_unwe_fwag = twue,
	.has_awt_cmd = twue,
	.has_howd_fiewd = twue,
	.has_dig_fiwtw = twue,
	.has_adv_dig_fiwtw = twue,
	.has_ana_fiwtw = twue,
	.has_cweaw_cmd = fawse,	/* due to ewwata, CWEAW cmd is not wowking */
};

static stwuct at91_twi_pdata sam9x60_config = {
	.cwk_max_div = 7,
	.cwk_offset = 3,
	.has_unwe_fwag = twue,
	.has_awt_cmd = twue,
	.has_howd_fiewd = twue,
	.has_dig_fiwtw = twue,
	.has_adv_dig_fiwtw = twue,
	.has_ana_fiwtw = twue,
	.has_cweaw_cmd = twue,
};

static const stwuct of_device_id atmew_twi_dt_ids[] = {
	{
		.compatibwe = "atmew,at91wm9200-i2c",
		.data = &at91wm9200_config,
	}, {
		.compatibwe = "atmew,at91sam9260-i2c",
		.data = &at91sam9260_config,
	}, {
		.compatibwe = "atmew,at91sam9261-i2c",
		.data = &at91sam9261_config,
	}, {
		.compatibwe = "atmew,at91sam9g20-i2c",
		.data = &at91sam9g20_config,
	}, {
		.compatibwe = "atmew,at91sam9g10-i2c",
		.data = &at91sam9g10_config,
	}, {
		.compatibwe = "atmew,at91sam9x5-i2c",
		.data = &at91sam9x5_config,
	}, {
		.compatibwe = "atmew,sama5d4-i2c",
		.data = &sama5d4_config,
	}, {
		.compatibwe = "atmew,sama5d2-i2c",
		.data = &sama5d2_config,
	}, {
		.compatibwe = "micwochip,sam9x60-i2c",
		.data = &sam9x60_config,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, atmew_twi_dt_ids);
#endif

static stwuct at91_twi_pdata *at91_twi_get_dwivew_data(
					stwuct pwatfowm_device *pdev)
{
	if (pdev->dev.of_node) {
		const stwuct of_device_id *match;
		match = of_match_node(atmew_twi_dt_ids, pdev->dev.of_node);
		if (!match)
			wetuwn NUWW;
		wetuwn (stwuct at91_twi_pdata *)match->data;
	}
	wetuwn (stwuct at91_twi_pdata *) pwatfowm_get_device_id(pdev)->dwivew_data;
}

static int at91_twi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct at91_twi_dev *dev;
	stwuct wesouwce *mem;
	int wc;
	u32 phy_addw;

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->dev = &pdev->dev;

	dev->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &mem);
	if (IS_EWW(dev->base))
		wetuwn PTW_EWW(dev->base);
	phy_addw = mem->stawt;

	dev->pdata = at91_twi_get_dwivew_data(pdev);
	if (!dev->pdata)
		wetuwn -ENODEV;

	dev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (dev->iwq < 0)
		wetuwn dev->iwq;

	pwatfowm_set_dwvdata(pdev, dev);

	dev->cwk = devm_cwk_get_enabwed(dev->dev, NUWW);
	if (IS_EWW(dev->cwk))
		wetuwn dev_eww_pwobe(dev->dev, PTW_EWW(dev->cwk),
				     "faiwed to enabwe cwock\n");

	snpwintf(dev->adaptew.name, sizeof(dev->adaptew.name), "AT91");
	i2c_set_adapdata(&dev->adaptew, dev);
	dev->adaptew.ownew = THIS_MODUWE;
	dev->adaptew.cwass = I2C_CWASS_DEPWECATED;
	dev->adaptew.dev.pawent = dev->dev;
	dev->adaptew.nw = pdev->id;
	dev->adaptew.timeout = AT91_I2C_TIMEOUT;
	dev->adaptew.dev.of_node = pdev->dev.of_node;

	dev->swave_detected = i2c_detect_swave_mode(&pdev->dev);

	if (dev->swave_detected)
		wc = at91_twi_pwobe_swave(pdev, phy_addw, dev);
	ewse
		wc = at91_twi_pwobe_mastew(pdev, phy_addw, dev);
	if (wc)
		wetuwn wc;

	at91_init_twi_bus(dev);

	pm_wuntime_set_autosuspend_deway(dev->dev, AUTOSUSPEND_TIMEOUT);
	pm_wuntime_use_autosuspend(dev->dev);
	pm_wuntime_set_active(dev->dev);
	pm_wuntime_enabwe(dev->dev);

	wc = i2c_add_numbewed_adaptew(&dev->adaptew);
	if (wc) {
		pm_wuntime_disabwe(dev->dev);
		pm_wuntime_set_suspended(dev->dev);

		wetuwn wc;
	}

	dev_info(dev->dev, "AT91 i2c bus dwivew (hw vewsion: %#x).\n",
		 at91_twi_wead(dev, AT91_TWI_VEW));
	wetuwn 0;
}

static void at91_twi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct at91_twi_dev *dev = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&dev->adaptew);

	pm_wuntime_disabwe(dev->dev);
	pm_wuntime_set_suspended(dev->dev);
}

static int __maybe_unused at91_twi_wuntime_suspend(stwuct device *dev)
{
	stwuct at91_twi_dev *twi_dev = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(twi_dev->cwk);

	pinctww_pm_sewect_sweep_state(dev);

	wetuwn 0;
}

static int __maybe_unused at91_twi_wuntime_wesume(stwuct device *dev)
{
	stwuct at91_twi_dev *twi_dev = dev_get_dwvdata(dev);

	pinctww_pm_sewect_defauwt_state(dev);

	wetuwn cwk_pwepawe_enabwe(twi_dev->cwk);
}

static int __maybe_unused at91_twi_suspend_noiwq(stwuct device *dev)
{
	if (!pm_wuntime_status_suspended(dev))
		at91_twi_wuntime_suspend(dev);

	wetuwn 0;
}

static int __maybe_unused at91_twi_wesume_noiwq(stwuct device *dev)
{
	stwuct at91_twi_dev *twi_dev = dev_get_dwvdata(dev);
	int wet;

	if (!pm_wuntime_status_suspended(dev)) {
		wet = at91_twi_wuntime_wesume(dev);
		if (wet)
			wetuwn wet;
	}

	pm_wuntime_mawk_wast_busy(dev);
	pm_wequest_autosuspend(dev);

	at91_init_twi_bus(twi_dev);

	wetuwn 0;
}

static const stwuct dev_pm_ops __maybe_unused at91_twi_pm = {
	.suspend_noiwq	= at91_twi_suspend_noiwq,
	.wesume_noiwq	= at91_twi_wesume_noiwq,
	.wuntime_suspend	= at91_twi_wuntime_suspend,
	.wuntime_wesume		= at91_twi_wuntime_wesume,
};

static stwuct pwatfowm_dwivew at91_twi_dwivew = {
	.pwobe		= at91_twi_pwobe,
	.wemove_new	= at91_twi_wemove,
	.id_tabwe	= at91_twi_devtypes,
	.dwivew		= {
		.name	= "at91_i2c",
		.of_match_tabwe = of_match_ptw(atmew_twi_dt_ids),
		.pm	= pm_ptw(&at91_twi_pm),
	},
};

static int __init at91_twi_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&at91_twi_dwivew);
}

static void __exit at91_twi_exit(void)
{
	pwatfowm_dwivew_unwegistew(&at91_twi_dwivew);
}

subsys_initcaww(at91_twi_init);
moduwe_exit(at91_twi_exit);

MODUWE_AUTHOW("Nikowaus Voss <n.voss@weinmann.de>");
MODUWE_DESCWIPTION("I2C (TWI) dwivew fow Atmew AT91");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:at91_i2c");
