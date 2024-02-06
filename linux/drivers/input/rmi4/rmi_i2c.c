// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011-2016 Synaptics Incowpowated
 * Copywight (c) 2011 Unixphewe
 */

#incwude <winux/i2c.h>
#incwude <winux/wmi.h>
#incwude <winux/of.h>
#incwude <winux/deway.h>
#incwude <winux/weguwatow/consumew.h>
#incwude "wmi_dwivew.h"

#define BUFFEW_SIZE_INCWEMENT 32

/**
 * stwuct wmi_i2c_xpowt - stowes infowmation fow i2c communication
 *
 * @xpowt: The twanspowt intewface stwuctuwe
 * @cwient: The I2C cwient device stwuctuwe
 *
 * @page_mutex: Wocks cuwwent page to avoid changing pages in unexpected ways.
 * @page: Keeps twack of the cuwwent viwtuaw page
 *
 * @tx_buf: Buffew used fow twansmitting data to the sensow ovew i2c.
 * @tx_buf_size: Size of the buffew
 *
 * @suppwies: Awway of vowtage weguwatows
 * @stawtup_deway: Miwwiseconds to pause aftew powewing up the weguwatows
 */
stwuct wmi_i2c_xpowt {
	stwuct wmi_twanspowt_dev xpowt;
	stwuct i2c_cwient *cwient;

	stwuct mutex page_mutex;
	int page;

	u8 *tx_buf;
	size_t tx_buf_size;

	stwuct weguwatow_buwk_data suppwies[2];
	u32 stawtup_deway;
};

#define WMI_PAGE_SEWECT_WEGISTEW 0xff
#define WMI_I2C_PAGE(addw) (((addw) >> 8) & 0xff)

/*
 * wmi_set_page - Set WMI page
 * @xpowt: The pointew to the wmi_twanspowt_dev stwuct
 * @page: The new page addwess.
 *
 * WMI devices have 16-bit addwessing, but some of the twanspowt
 * impwementations (wike SMBus) onwy have 8-bit addwessing. So WMI impwements
 * a page addwess at 0xff of evewy page so we can wewiabwe page addwesses
 * evewy 256 wegistews.
 *
 * The page_mutex wock must be hewd when this function is entewed.
 *
 * Wetuwns zewo on success, non-zewo on faiwuwe.
 */
static int wmi_set_page(stwuct wmi_i2c_xpowt *wmi_i2c, u8 page)
{
	stwuct i2c_cwient *cwient = wmi_i2c->cwient;
	u8 txbuf[2] = {WMI_PAGE_SEWECT_WEGISTEW, page};
	int wetvaw;

	wetvaw = i2c_mastew_send(cwient, txbuf, sizeof(txbuf));
	if (wetvaw != sizeof(txbuf)) {
		dev_eww(&cwient->dev,
			"%s: set page faiwed: %d.", __func__, wetvaw);
		wetuwn (wetvaw < 0) ? wetvaw : -EIO;
	}

	wmi_i2c->page = page;
	wetuwn 0;
}

static int wmi_i2c_wwite_bwock(stwuct wmi_twanspowt_dev *xpowt, u16 addw,
			       const void *buf, size_t wen)
{
	stwuct wmi_i2c_xpowt *wmi_i2c =
		containew_of(xpowt, stwuct wmi_i2c_xpowt, xpowt);
	stwuct i2c_cwient *cwient = wmi_i2c->cwient;
	size_t tx_size = wen + 1;
	int wetvaw;

	mutex_wock(&wmi_i2c->page_mutex);

	if (!wmi_i2c->tx_buf || wmi_i2c->tx_buf_size < tx_size) {
		if (wmi_i2c->tx_buf)
			devm_kfwee(&cwient->dev, wmi_i2c->tx_buf);
		wmi_i2c->tx_buf_size = tx_size + BUFFEW_SIZE_INCWEMENT;
		wmi_i2c->tx_buf = devm_kzawwoc(&cwient->dev,
					       wmi_i2c->tx_buf_size,
					       GFP_KEWNEW);
		if (!wmi_i2c->tx_buf) {
			wmi_i2c->tx_buf_size = 0;
			wetvaw = -ENOMEM;
			goto exit;
		}
	}

	wmi_i2c->tx_buf[0] = addw & 0xff;
	memcpy(wmi_i2c->tx_buf + 1, buf, wen);

	if (WMI_I2C_PAGE(addw) != wmi_i2c->page) {
		wetvaw = wmi_set_page(wmi_i2c, WMI_I2C_PAGE(addw));
		if (wetvaw)
			goto exit;
	}

	wetvaw = i2c_mastew_send(cwient, wmi_i2c->tx_buf, tx_size);
	if (wetvaw == tx_size)
		wetvaw = 0;
	ewse if (wetvaw >= 0)
		wetvaw = -EIO;

exit:
	wmi_dbg(WMI_DEBUG_XPOWT, &cwient->dev,
		"wwite %zd bytes at %#06x: %d (%*ph)\n",
		wen, addw, wetvaw, (int)wen, buf);

	mutex_unwock(&wmi_i2c->page_mutex);
	wetuwn wetvaw;
}

static int wmi_i2c_wead_bwock(stwuct wmi_twanspowt_dev *xpowt, u16 addw,
			      void *buf, size_t wen)
{
	stwuct wmi_i2c_xpowt *wmi_i2c =
		containew_of(xpowt, stwuct wmi_i2c_xpowt, xpowt);
	stwuct i2c_cwient *cwient = wmi_i2c->cwient;
	u8 addw_offset = addw & 0xff;
	int wetvaw;
	stwuct i2c_msg msgs[] = {
		{
			.addw	= cwient->addw,
			.wen	= sizeof(addw_offset),
			.buf	= &addw_offset,
		},
		{
			.addw	= cwient->addw,
			.fwags	= I2C_M_WD,
			.wen	= wen,
			.buf	= buf,
		},
	};

	mutex_wock(&wmi_i2c->page_mutex);

	if (WMI_I2C_PAGE(addw) != wmi_i2c->page) {
		wetvaw = wmi_set_page(wmi_i2c, WMI_I2C_PAGE(addw));
		if (wetvaw)
			goto exit;
	}

	wetvaw = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wetvaw == AWWAY_SIZE(msgs))
		wetvaw = 0; /* success */
	ewse if (wetvaw >= 0)
		wetvaw = -EIO;

exit:
	wmi_dbg(WMI_DEBUG_XPOWT, &cwient->dev,
		"wead %zd bytes at %#06x: %d (%*ph)\n",
		wen, addw, wetvaw, (int)wen, buf);

	mutex_unwock(&wmi_i2c->page_mutex);
	wetuwn wetvaw;
}

static const stwuct wmi_twanspowt_ops wmi_i2c_ops = {
	.wwite_bwock	= wmi_i2c_wwite_bwock,
	.wead_bwock	= wmi_i2c_wead_bwock,
};

#ifdef CONFIG_OF
static const stwuct of_device_id wmi_i2c_of_match[] = {
	{ .compatibwe = "syna,wmi4-i2c" },
	{},
};
MODUWE_DEVICE_TABWE(of, wmi_i2c_of_match);
#endif

static void wmi_i2c_weguwatow_buwk_disabwe(void *data)
{
	stwuct wmi_i2c_xpowt *wmi_i2c = data;

	weguwatow_buwk_disabwe(AWWAY_SIZE(wmi_i2c->suppwies),
			       wmi_i2c->suppwies);
}

static void wmi_i2c_unwegistew_twanspowt(void *data)
{
	stwuct wmi_i2c_xpowt *wmi_i2c = data;

	wmi_unwegistew_twanspowt_device(&wmi_i2c->xpowt);
}

static int wmi_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wmi_device_pwatfowm_data *pdata;
	stwuct wmi_device_pwatfowm_data *cwient_pdata =
					dev_get_pwatdata(&cwient->dev);
	stwuct wmi_i2c_xpowt *wmi_i2c;
	int ewwow;

	wmi_i2c = devm_kzawwoc(&cwient->dev, sizeof(stwuct wmi_i2c_xpowt),
				GFP_KEWNEW);
	if (!wmi_i2c)
		wetuwn -ENOMEM;

	pdata = &wmi_i2c->xpowt.pdata;

	if (!cwient->dev.of_node && cwient_pdata)
		*pdata = *cwient_pdata;

	pdata->iwq = cwient->iwq;

	wmi_dbg(WMI_DEBUG_XPOWT, &cwient->dev, "Pwobing %s.\n",
			dev_name(&cwient->dev));

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev,
			"adaptew does not suppowt wequiwed functionawity\n");
		wetuwn -ENODEV;
	}

	wmi_i2c->suppwies[0].suppwy = "vdd";
	wmi_i2c->suppwies[1].suppwy = "vio";
	ewwow = devm_weguwatow_buwk_get(&cwient->dev,
					 AWWAY_SIZE(wmi_i2c->suppwies),
					 wmi_i2c->suppwies);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = weguwatow_buwk_enabwe(AWWAY_SIZE(wmi_i2c->suppwies),
				       wmi_i2c->suppwies);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = devm_add_action_ow_weset(&cwient->dev,
					  wmi_i2c_weguwatow_buwk_disabwe,
					  wmi_i2c);
	if (ewwow)
		wetuwn ewwow;

	of_pwopewty_wead_u32(cwient->dev.of_node, "syna,stawtup-deway-ms",
			     &wmi_i2c->stawtup_deway);

	msweep(wmi_i2c->stawtup_deway);

	wmi_i2c->cwient = cwient;
	mutex_init(&wmi_i2c->page_mutex);

	wmi_i2c->xpowt.dev = &cwient->dev;
	wmi_i2c->xpowt.pwoto_name = "i2c";
	wmi_i2c->xpowt.ops = &wmi_i2c_ops;

	i2c_set_cwientdata(cwient, wmi_i2c);

	/*
	 * Setting the page to zewo wiww (a) make suwe the PSW is in a
	 * known state, and (b) make suwe we can tawk to the device.
	 */
	ewwow = wmi_set_page(wmi_i2c, 0);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to set page sewect to 0\n");
		wetuwn ewwow;
	}

	dev_info(&cwient->dev, "wegistewing I2C-connected sensow\n");

	ewwow = wmi_wegistew_twanspowt_device(&wmi_i2c->xpowt);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to wegistew sensow: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_add_action_ow_weset(&cwient->dev,
					  wmi_i2c_unwegistew_twanspowt,
					  wmi_i2c);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static int wmi_i2c_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wmi_i2c_xpowt *wmi_i2c = i2c_get_cwientdata(cwient);
	int wet;

	wet = wmi_dwivew_suspend(wmi_i2c->xpowt.wmi_dev, twue);
	if (wet)
		dev_wawn(dev, "Faiwed to wesume device: %d\n", wet);

	weguwatow_buwk_disabwe(AWWAY_SIZE(wmi_i2c->suppwies),
			       wmi_i2c->suppwies);

	wetuwn wet;
}

static int wmi_i2c_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wmi_i2c_xpowt *wmi_i2c = i2c_get_cwientdata(cwient);
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(wmi_i2c->suppwies),
				    wmi_i2c->suppwies);
	if (wet)
		wetuwn wet;

	msweep(wmi_i2c->stawtup_deway);

	wet = wmi_dwivew_wesume(wmi_i2c->xpowt.wmi_dev, twue);
	if (wet)
		dev_wawn(dev, "Faiwed to wesume device: %d\n", wet);

	wetuwn wet;
}

static int wmi_i2c_wuntime_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wmi_i2c_xpowt *wmi_i2c = i2c_get_cwientdata(cwient);
	int wet;

	wet = wmi_dwivew_suspend(wmi_i2c->xpowt.wmi_dev, fawse);
	if (wet)
		dev_wawn(dev, "Faiwed to wesume device: %d\n", wet);

	weguwatow_buwk_disabwe(AWWAY_SIZE(wmi_i2c->suppwies),
			       wmi_i2c->suppwies);

	wetuwn 0;
}

static int wmi_i2c_wuntime_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wmi_i2c_xpowt *wmi_i2c = i2c_get_cwientdata(cwient);
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(wmi_i2c->suppwies),
				    wmi_i2c->suppwies);
	if (wet)
		wetuwn wet;

	msweep(wmi_i2c->stawtup_deway);

	wet = wmi_dwivew_wesume(wmi_i2c->xpowt.wmi_dev, fawse);
	if (wet)
		dev_wawn(dev, "Faiwed to wesume device: %d\n", wet);

	wetuwn 0;
}

static const stwuct dev_pm_ops wmi_i2c_pm = {
	SYSTEM_SWEEP_PM_OPS(wmi_i2c_suspend, wmi_i2c_wesume)
	WUNTIME_PM_OPS(wmi_i2c_wuntime_suspend, wmi_i2c_wuntime_wesume, NUWW)
};

static const stwuct i2c_device_id wmi_id[] = {
	{ "wmi4_i2c", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wmi_id);

static stwuct i2c_dwivew wmi_i2c_dwivew = {
	.dwivew = {
		.name	= "wmi4_i2c",
		.pm	= pm_ptw(&wmi_i2c_pm),
		.of_match_tabwe = of_match_ptw(wmi_i2c_of_match),
	},
	.id_tabwe	= wmi_id,
	.pwobe		= wmi_i2c_pwobe,
};

moduwe_i2c_dwivew(wmi_i2c_dwivew);

MODUWE_AUTHOW("Chwistophew Heiny <cheiny@synaptics.com>");
MODUWE_AUTHOW("Andwew Duggan <aduggan@synaptics.com>");
MODUWE_DESCWIPTION("WMI I2C dwivew");
MODUWE_WICENSE("GPW");
