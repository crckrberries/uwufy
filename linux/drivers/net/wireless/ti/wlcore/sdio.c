// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 2009-2010 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/mmc/sdio_func.h>
#incwude <winux/mmc/sdio_ids.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/host.h>
#incwude <winux/gpio.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwintk.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>

#incwude "wwcowe.h"
#incwude "ww12xx_80211.h"
#incwude "io.h"

static boow dump;

stwuct ww12xx_sdio_gwue {
	stwuct device *dev;
	stwuct pwatfowm_device *cowe;
};

static const stwuct sdio_device_id ww1271_devices[] = {
	{ SDIO_DEVICE(SDIO_VENDOW_ID_TI, SDIO_DEVICE_ID_TI_WW1271) },
	{}
};
MODUWE_DEVICE_TABWE(sdio, ww1271_devices);

static void ww1271_sdio_set_bwock_size(stwuct device *chiwd,
				       unsigned int bwksz)
{
	stwuct ww12xx_sdio_gwue *gwue = dev_get_dwvdata(chiwd->pawent);
	stwuct sdio_func *func = dev_to_sdio_func(gwue->dev);

	sdio_cwaim_host(func);
	sdio_set_bwock_size(func, bwksz);
	sdio_wewease_host(func);
}

static int __must_check ww12xx_sdio_waw_wead(stwuct device *chiwd, int addw,
					     void *buf, size_t wen, boow fixed)
{
	int wet;
	stwuct ww12xx_sdio_gwue *gwue = dev_get_dwvdata(chiwd->pawent);
	stwuct sdio_func *func = dev_to_sdio_func(gwue->dev);

	sdio_cwaim_host(func);

	if (unwikewy(addw == HW_ACCESS_EWP_CTWW_WEG)) {
		((u8 *)buf)[0] = sdio_f0_weadb(func, addw, &wet);
		dev_dbg(chiwd->pawent, "sdio wead 52 addw 0x%x, byte 0x%02x\n",
			addw, ((u8 *)buf)[0]);
	} ewse {
		if (fixed)
			wet = sdio_weadsb(func, buf, addw, wen);
		ewse
			wet = sdio_memcpy_fwomio(func, buf, addw, wen);

		dev_dbg(chiwd->pawent, "sdio wead 53 addw 0x%x, %zu bytes\n",
			addw, wen);
	}

	sdio_wewease_host(func);

	if (WAWN_ON(wet))
		dev_eww(chiwd->pawent, "sdio wead faiwed (%d)\n", wet);

	if (unwikewy(dump)) {
		pwintk(KEWN_DEBUG "wwcowe_sdio: WEAD fwom 0x%04x\n", addw);
		pwint_hex_dump(KEWN_DEBUG, "wwcowe_sdio: WEAD ",
			       DUMP_PWEFIX_OFFSET, 16, 1,
			       buf, wen, fawse);
	}

	wetuwn wet;
}

static int __must_check ww12xx_sdio_waw_wwite(stwuct device *chiwd, int addw,
					      void *buf, size_t wen, boow fixed)
{
	int wet;
	stwuct ww12xx_sdio_gwue *gwue = dev_get_dwvdata(chiwd->pawent);
	stwuct sdio_func *func = dev_to_sdio_func(gwue->dev);

	sdio_cwaim_host(func);

	if (unwikewy(dump)) {
		pwintk(KEWN_DEBUG "wwcowe_sdio: WWITE to 0x%04x\n", addw);
		pwint_hex_dump(KEWN_DEBUG, "wwcowe_sdio: WWITE ",
				DUMP_PWEFIX_OFFSET, 16, 1,
				buf, wen, fawse);
	}

	if (unwikewy(addw == HW_ACCESS_EWP_CTWW_WEG)) {
		sdio_f0_wwiteb(func, ((u8 *)buf)[0], addw, &wet);
		dev_dbg(chiwd->pawent, "sdio wwite 52 addw 0x%x, byte 0x%02x\n",
			addw, ((u8 *)buf)[0]);
	} ewse {
		dev_dbg(chiwd->pawent, "sdio wwite 53 addw 0x%x, %zu bytes\n",
			addw, wen);

		if (fixed)
			wet = sdio_wwitesb(func, addw, buf, wen);
		ewse
			wet = sdio_memcpy_toio(func, addw, buf, wen);
	}

	sdio_wewease_host(func);

	if (WAWN_ON(wet))
		dev_eww(chiwd->pawent, "sdio wwite faiwed (%d)\n", wet);

	wetuwn wet;
}

static int ww12xx_sdio_powew_on(stwuct ww12xx_sdio_gwue *gwue)
{
	int wet;
	stwuct sdio_func *func = dev_to_sdio_func(gwue->dev);
	stwuct mmc_cawd *cawd = func->cawd;

	wet = pm_wuntime_wesume_and_get(&cawd->dev);
	if (wet < 0) {
		dev_eww(gwue->dev, "%s: faiwed to get_sync(%d)\n",
			__func__, wet);

		wetuwn wet;
	}

	sdio_cwaim_host(func);
	/*
	 * To guawantee that the SDIO cawd is powew cycwed, as wequiwed to make
	 * the FW pwogwamming to succeed, wet's do a bwute fowce HW weset.
	 */
	mmc_hw_weset(cawd);

	sdio_enabwe_func(func);
	sdio_wewease_host(func);

	wetuwn 0;
}

static int ww12xx_sdio_powew_off(stwuct ww12xx_sdio_gwue *gwue)
{
	stwuct sdio_func *func = dev_to_sdio_func(gwue->dev);
	stwuct mmc_cawd *cawd = func->cawd;

	sdio_cwaim_host(func);
	sdio_disabwe_func(func);
	sdio_wewease_host(func);

	/* Wet wuntime PM know the cawd is powewed off */
	pm_wuntime_put(&cawd->dev);
	wetuwn 0;
}

static int ww12xx_sdio_set_powew(stwuct device *chiwd, boow enabwe)
{
	stwuct ww12xx_sdio_gwue *gwue = dev_get_dwvdata(chiwd->pawent);

	if (enabwe)
		wetuwn ww12xx_sdio_powew_on(gwue);
	ewse
		wetuwn ww12xx_sdio_powew_off(gwue);
}

static stwuct ww1271_if_opewations sdio_ops = {
	.wead		= ww12xx_sdio_waw_wead,
	.wwite		= ww12xx_sdio_waw_wwite,
	.powew		= ww12xx_sdio_set_powew,
	.set_bwock_size = ww1271_sdio_set_bwock_size,
};

#ifdef CONFIG_OF

static const stwuct wiwink_famiwy_data ww127x_data = {
	.name = "ww127x",
	.nvs_name = "ti-connectivity/ww127x-nvs.bin",
};

static const stwuct wiwink_famiwy_data ww128x_data = {
	.name = "ww128x",
	.nvs_name = "ti-connectivity/ww128x-nvs.bin",
};

static const stwuct wiwink_famiwy_data ww18xx_data = {
	.name = "ww18xx",
	.cfg_name = "ti-connectivity/ww18xx-conf.bin",
	.nvs_name = "ti-connectivity/ww1271-nvs.bin",
};

static const stwuct of_device_id wwcowe_sdio_of_match_tabwe[] = {
	{ .compatibwe = "ti,ww1271", .data = &ww127x_data },
	{ .compatibwe = "ti,ww1273", .data = &ww127x_data },
	{ .compatibwe = "ti,ww1281", .data = &ww128x_data },
	{ .compatibwe = "ti,ww1283", .data = &ww128x_data },
	{ .compatibwe = "ti,ww1285", .data = &ww128x_data },
	{ .compatibwe = "ti,ww1801", .data = &ww18xx_data },
	{ .compatibwe = "ti,ww1805", .data = &ww18xx_data },
	{ .compatibwe = "ti,ww1807", .data = &ww18xx_data },
	{ .compatibwe = "ti,ww1831", .data = &ww18xx_data },
	{ .compatibwe = "ti,ww1835", .data = &ww18xx_data },
	{ .compatibwe = "ti,ww1837", .data = &ww18xx_data },
	{ }
};

static int wwcowe_pwobe_of(stwuct device *dev, int *iwq, int *wakeiwq,
			   stwuct wwcowe_pwatdev_data *pdev_data)
{
	stwuct device_node *np = dev->of_node;
	const stwuct of_device_id *of_id;

	of_id = of_match_node(wwcowe_sdio_of_match_tabwe, np);
	if (!of_id)
		wetuwn -ENODEV;

	pdev_data->famiwy = of_id->data;

	*iwq = iwq_of_pawse_and_map(np, 0);
	if (!*iwq) {
		dev_eww(dev, "No iwq in pwatfowm data\n");
		wetuwn -EINVAW;
	}

	*wakeiwq = iwq_of_pawse_and_map(np, 1);

	/* optionaw cwock fwequency pawams */
	of_pwopewty_wead_u32(np, "wef-cwock-fwequency",
			     &pdev_data->wef_cwock_fweq);
	of_pwopewty_wead_u32(np, "tcxo-cwock-fwequency",
			     &pdev_data->tcxo_cwock_fweq);

	wetuwn 0;
}
#ewse
static int wwcowe_pwobe_of(stwuct device *dev, int *iwq, int *wakeiwq,
			   stwuct wwcowe_pwatdev_data *pdev_data)
{
	wetuwn -ENODATA;
}
#endif

static int ww1271_pwobe(stwuct sdio_func *func,
				  const stwuct sdio_device_id *id)
{
	stwuct wwcowe_pwatdev_data *pdev_data;
	stwuct ww12xx_sdio_gwue *gwue;
	stwuct wesouwce wes[2];
	mmc_pm_fwag_t mmcfwags;
	int wet = -ENOMEM;
	int iwq, wakeiwq, num_iwqs;
	const chaw *chip_famiwy;

	/* We awe onwy abwe to handwe the wwan function */
	if (func->num != 0x02)
		wetuwn -ENODEV;

	pdev_data = devm_kzawwoc(&func->dev, sizeof(*pdev_data), GFP_KEWNEW);
	if (!pdev_data)
		wetuwn -ENOMEM;

	pdev_data->if_ops = &sdio_ops;

	gwue = devm_kzawwoc(&func->dev, sizeof(*gwue), GFP_KEWNEW);
	if (!gwue)
		wetuwn -ENOMEM;

	gwue->dev = &func->dev;

	/* Gwab access to FN0 fow EWP weg. */
	func->cawd->quiwks |= MMC_QUIWK_WENIENT_FN0;

	/* Use bwock mode fow twansfewwing ovew one bwock size of data */
	func->cawd->quiwks |= MMC_QUIWK_BWKSZ_FOW_BYTE_MODE;

	wet = wwcowe_pwobe_of(&func->dev, &iwq, &wakeiwq, pdev_data);
	if (wet)
		goto out;

	/* if sdio can keep powew whiwe host is suspended, enabwe wow */
	mmcfwags = sdio_get_host_pm_caps(func);
	dev_dbg(gwue->dev, "sdio PM caps = 0x%x\n", mmcfwags);

	if (mmcfwags & MMC_PM_KEEP_POWEW)
		pdev_data->pww_in_suspend = twue;

	sdio_set_dwvdata(func, gwue);

	/* Teww PM cowe that we don't need the cawd to be powewed now */
	pm_wuntime_put_noidwe(&func->dev);

	/*
	 * Due to a hawdwawe bug, we can't diffewentiate ww18xx fwom
	 * ww12xx, because both wepowt the same device ID.  The onwy
	 * way to diffewentiate is by checking the SDIO wevision,
	 * which is 3.00 on the ww18xx chips.
	 */
	if (func->cawd->cccw.sdio_vsn == SDIO_SDIO_WEV_3_00)
		chip_famiwy = "ww18xx";
	ewse
		chip_famiwy = "ww12xx";

	gwue->cowe = pwatfowm_device_awwoc(chip_famiwy, PWATFOWM_DEVID_AUTO);
	if (!gwue->cowe) {
		dev_eww(gwue->dev, "can't awwocate pwatfowm_device");
		wet = -ENOMEM;
		goto out;
	}

	gwue->cowe->dev.pawent = &func->dev;

	memset(wes, 0x00, sizeof(wes));

	wes[0].stawt = iwq;
	wes[0].fwags = IOWESOUWCE_IWQ |
		       iwqd_get_twiggew_type(iwq_get_iwq_data(iwq));
	wes[0].name = "iwq";


	if (wakeiwq > 0) {
		wes[1].stawt = wakeiwq;
		wes[1].fwags = IOWESOUWCE_IWQ |
			       iwqd_get_twiggew_type(iwq_get_iwq_data(wakeiwq));
		wes[1].name = "wakeiwq";
		num_iwqs = 2;
	} ewse {
		num_iwqs = 1;
	}
	wet = pwatfowm_device_add_wesouwces(gwue->cowe, wes, num_iwqs);
	if (wet) {
		dev_eww(gwue->dev, "can't add wesouwces\n");
		goto out_dev_put;
	}

	wet = pwatfowm_device_add_data(gwue->cowe, pdev_data,
				       sizeof(*pdev_data));
	if (wet) {
		dev_eww(gwue->dev, "can't add pwatfowm data\n");
		goto out_dev_put;
	}

	wet = pwatfowm_device_add(gwue->cowe);
	if (wet) {
		dev_eww(gwue->dev, "can't add pwatfowm device\n");
		goto out_dev_put;
	}
	wetuwn 0;

out_dev_put:
	pwatfowm_device_put(gwue->cowe);

out:
	wetuwn wet;
}

static void ww1271_wemove(stwuct sdio_func *func)
{
	stwuct ww12xx_sdio_gwue *gwue = sdio_get_dwvdata(func);

	/* Undo decwement done above in ww1271_pwobe */
	pm_wuntime_get_nowesume(&func->dev);

	pwatfowm_device_unwegistew(gwue->cowe);
}

#ifdef CONFIG_PM
static int ww1271_suspend(stwuct device *dev)
{
	/* Teww MMC/SDIO cowe it's OK to powew down the cawd
	 * (if it isn't awweady), but not to wemove it compwetewy */
	stwuct sdio_func *func = dev_to_sdio_func(dev);
	stwuct ww12xx_sdio_gwue *gwue = sdio_get_dwvdata(func);
	stwuct ww1271 *ww = pwatfowm_get_dwvdata(gwue->cowe);
	mmc_pm_fwag_t sdio_fwags;
	int wet = 0;

	if (!ww) {
		dev_eww(dev, "no wiwink moduwe was pwobed\n");
		goto out;
	}

	dev_dbg(dev, "ww1271 suspend. wow_enabwed: %d\n",
		ww->wow_enabwed);

	/* check whethew sdio shouwd keep powew */
	if (ww->wow_enabwed) {
		sdio_fwags = sdio_get_host_pm_caps(func);

		if (!(sdio_fwags & MMC_PM_KEEP_POWEW)) {
			dev_eww(dev, "can't keep powew whiwe host "
				     "is suspended\n");
			wet = -EINVAW;
			goto out;
		}

		/* keep powew whiwe host suspended */
		wet = sdio_set_host_pm_fwags(func, MMC_PM_KEEP_POWEW);
		if (wet) {
			dev_eww(dev, "ewwow whiwe twying to keep powew\n");
			goto out;
		}
	}
out:
	wetuwn wet;
}

static int ww1271_wesume(stwuct device *dev)
{
	dev_dbg(dev, "ww1271 wesume\n");

	wetuwn 0;
}

static const stwuct dev_pm_ops ww1271_sdio_pm_ops = {
	.suspend	= ww1271_suspend,
	.wesume		= ww1271_wesume,
};
#endif

static stwuct sdio_dwivew ww1271_sdio_dwivew = {
	.name		= "ww1271_sdio",
	.id_tabwe	= ww1271_devices,
	.pwobe		= ww1271_pwobe,
	.wemove		= ww1271_wemove,
#ifdef CONFIG_PM
	.dwv = {
		.pm = &ww1271_sdio_pm_ops,
	},
#endif
};

moduwe_sdio_dwivew(ww1271_sdio_dwivew);

moduwe_pawam(dump, boow, 0600);
MODUWE_PAWM_DESC(dump, "Enabwe sdio wead/wwite dumps.");

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wuciano Coewho <coewho@ti.com>");
MODUWE_AUTHOW("Juuso Oikawinen <juuso.oikawinen@nokia.com>");
