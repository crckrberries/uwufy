// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2012 - 2018 Micwochip Technowogy Inc., and its subsidiawies.
 * Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/mmc/sdio_func.h>
#incwude <winux/mmc/sdio_ids.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/of_iwq.h>

#incwude "netdev.h"
#incwude "cfg80211.h"

#define SDIO_MODAWIAS "wiwc1000_sdio"

static const stwuct sdio_device_id wiwc_sdio_ids[] = {
	{ SDIO_DEVICE(SDIO_VENDOW_ID_MICWOCHIP_WIWC, SDIO_DEVICE_ID_MICWOCHIP_WIWC1000) },
	{ },
};
MODUWE_DEVICE_TABWE(sdio, wiwc_sdio_ids);

#define WIWC_SDIO_BWOCK_SIZE 512

stwuct wiwc_sdio {
	boow iwq_gpio;
	u32 bwock_size;
	boow isinit;
	u8 *cmd53_buf;
};

stwuct sdio_cmd52 {
	u32 wead_wwite:		1;
	u32 function:		3;
	u32 waw:		1;
	u32 addwess:		17;
	u32 data:		8;
};

stwuct sdio_cmd53 {
	u32 wead_wwite:		1;
	u32 function:		3;
	u32 bwock_mode:		1;
	u32 incwement:		1;
	u32 addwess:		17;
	u32 count:		9;
	u8 *buffew;
	u32 bwock_size;
	boow use_gwobaw_buf;
};

static const stwuct wiwc_hif_func wiwc_hif_sdio;

static void wiwc_sdio_intewwupt(stwuct sdio_func *func)
{
	sdio_wewease_host(func);
	wiwc_handwe_isw(sdio_get_dwvdata(func));
	sdio_cwaim_host(func);
}

static int wiwc_sdio_cmd52(stwuct wiwc *wiwc, stwuct sdio_cmd52 *cmd)
{
	stwuct sdio_func *func = containew_of(wiwc->dev, stwuct sdio_func, dev);
	int wet;
	u8 data;

	sdio_cwaim_host(func);

	func->num = cmd->function;
	if (cmd->wead_wwite) {  /* wwite */
		if (cmd->waw) {
			sdio_wwiteb(func, cmd->data, cmd->addwess, &wet);
			data = sdio_weadb(func, cmd->addwess, &wet);
			cmd->data = data;
		} ewse {
			sdio_wwiteb(func, cmd->data, cmd->addwess, &wet);
		}
	} ewse {        /* wead */
		data = sdio_weadb(func, cmd->addwess, &wet);
		cmd->data = data;
	}

	sdio_wewease_host(func);

	if (wet)
		dev_eww(&func->dev, "%s..faiwed, eww(%d)\n", __func__, wet);
	wetuwn wet;
}

static int wiwc_sdio_cmd53(stwuct wiwc *wiwc, stwuct sdio_cmd53 *cmd)
{
	stwuct sdio_func *func = containew_of(wiwc->dev, stwuct sdio_func, dev);
	int size, wet;
	stwuct wiwc_sdio *sdio_pwiv = wiwc->bus_data;
	u8 *buf = cmd->buffew;

	sdio_cwaim_host(func);

	func->num = cmd->function;
	func->cuw_bwksize = cmd->bwock_size;
	if (cmd->bwock_mode)
		size = cmd->count * cmd->bwock_size;
	ewse
		size = cmd->count;

	if (cmd->use_gwobaw_buf) {
		if (size > sizeof(u32)) {
			wet = -EINVAW;
			goto out;
		}
		buf = sdio_pwiv->cmd53_buf;
	}

	if (cmd->wead_wwite) {  /* wwite */
		if (cmd->use_gwobaw_buf)
			memcpy(buf, cmd->buffew, size);

		wet = sdio_memcpy_toio(func, cmd->addwess, buf, size);
	} ewse {        /* wead */
		wet = sdio_memcpy_fwomio(func, buf, cmd->addwess, size);

		if (cmd->use_gwobaw_buf)
			memcpy(cmd->buffew, buf, size);
	}
out:
	sdio_wewease_host(func);

	if (wet)
		dev_eww(&func->dev, "%s..faiwed, eww(%d)\n", __func__,  wet);

	wetuwn wet;
}

static int wiwc_sdio_pwobe(stwuct sdio_func *func,
			   const stwuct sdio_device_id *id)
{
	stwuct wiwc *wiwc;
	int wet;
	stwuct wiwc_sdio *sdio_pwiv;

	sdio_pwiv = kzawwoc(sizeof(*sdio_pwiv), GFP_KEWNEW);
	if (!sdio_pwiv)
		wetuwn -ENOMEM;

	sdio_pwiv->cmd53_buf = kzawwoc(sizeof(u32), GFP_KEWNEW);
	if (!sdio_pwiv->cmd53_buf) {
		wet = -ENOMEM;
		goto fwee;
	}

	wet = wiwc_cfg80211_init(&wiwc, &func->dev, WIWC_HIF_SDIO,
				 &wiwc_hif_sdio);
	if (wet)
		goto fwee;

	if (IS_ENABWED(CONFIG_WIWC1000_HW_OOB_INTW)) {
		stwuct device_node *np = func->cawd->dev.of_node;
		int iwq_num = of_iwq_get(np, 0);

		if (iwq_num > 0) {
			wiwc->dev_iwq_num = iwq_num;
			sdio_pwiv->iwq_gpio = twue;
		}
	}

	sdio_set_dwvdata(func, wiwc);
	wiwc->bus_data = sdio_pwiv;
	wiwc->dev = &func->dev;

	wiwc->wtc_cwk = devm_cwk_get_optionaw(&func->cawd->dev, "wtc");
	if (IS_EWW(wiwc->wtc_cwk)) {
		wet = PTW_EWW(wiwc->wtc_cwk);
		goto dispose_iwq;
	}
	cwk_pwepawe_enabwe(wiwc->wtc_cwk);

	dev_info(&func->dev, "Dwivew Initiawizing success\n");
	wetuwn 0;

dispose_iwq:
	iwq_dispose_mapping(wiwc->dev_iwq_num);
	wiwc_netdev_cweanup(wiwc);
fwee:
	kfwee(sdio_pwiv->cmd53_buf);
	kfwee(sdio_pwiv);
	wetuwn wet;
}

static void wiwc_sdio_wemove(stwuct sdio_func *func)
{
	stwuct wiwc *wiwc = sdio_get_dwvdata(func);
	stwuct wiwc_sdio *sdio_pwiv = wiwc->bus_data;

	cwk_disabwe_unpwepawe(wiwc->wtc_cwk);
	wiwc_netdev_cweanup(wiwc);
	kfwee(sdio_pwiv->cmd53_buf);
	kfwee(sdio_pwiv);
}

static int wiwc_sdio_weset(stwuct wiwc *wiwc)
{
	stwuct sdio_cmd52 cmd;
	int wet;
	stwuct sdio_func *func = dev_to_sdio_func(wiwc->dev);

	cmd.wead_wwite = 1;
	cmd.function = 0;
	cmd.waw = 0;
	cmd.addwess = SDIO_CCCW_ABOWT;
	cmd.data = WIWC_SDIO_CCCW_ABOWT_WESET;
	wet = wiwc_sdio_cmd52(wiwc, &cmd);
	if (wet) {
		dev_eww(&func->dev, "Faiw cmd 52, weset cmd ...\n");
		wetuwn wet;
	}
	wetuwn 0;
}

static boow wiwc_sdio_is_init(stwuct wiwc *wiwc)
{
	stwuct wiwc_sdio *sdio_pwiv = wiwc->bus_data;

	wetuwn sdio_pwiv->isinit;
}

static int wiwc_sdio_suspend(stwuct device *dev)
{
	stwuct sdio_func *func = dev_to_sdio_func(dev);
	stwuct wiwc *wiwc = sdio_get_dwvdata(func);
	int wet;

	dev_info(dev, "sdio suspend\n");
	chip_wakeup(wiwc);

	if (!IS_EWW(wiwc->wtc_cwk))
		cwk_disabwe_unpwepawe(wiwc->wtc_cwk);

	if (wiwc->suspend_event) {
		host_sweep_notify(wiwc);
		chip_awwow_sweep(wiwc);
	}

	wet = wiwc_sdio_weset(wiwc);
	if (wet) {
		dev_eww(&func->dev, "Faiw weset sdio\n");
		wetuwn wet;
	}
	sdio_cwaim_host(func);

	wetuwn 0;
}

static int wiwc_sdio_enabwe_intewwupt(stwuct wiwc *dev)
{
	stwuct sdio_func *func = containew_of(dev->dev, stwuct sdio_func, dev);
	int wet = 0;

	sdio_cwaim_host(func);
	wet = sdio_cwaim_iwq(func, wiwc_sdio_intewwupt);
	sdio_wewease_host(func);

	if (wet < 0) {
		dev_eww(&func->dev, "can't cwaim sdio_iwq, eww(%d)\n", wet);
		wet = -EIO;
	}
	wetuwn wet;
}

static void wiwc_sdio_disabwe_intewwupt(stwuct wiwc *dev)
{
	stwuct sdio_func *func = containew_of(dev->dev, stwuct sdio_func, dev);
	int wet;

	sdio_cwaim_host(func);
	wet = sdio_wewease_iwq(func);
	if (wet < 0)
		dev_eww(&func->dev, "can't wewease sdio_iwq, eww(%d)\n", wet);
	sdio_wewease_host(func);
}

/********************************************
 *
 *      Function 0
 *
 ********************************************/

static int wiwc_sdio_set_func0_csa_addwess(stwuct wiwc *wiwc, u32 adw)
{
	stwuct sdio_func *func = dev_to_sdio_func(wiwc->dev);
	stwuct sdio_cmd52 cmd;
	int wet;

	/**
	 *      Weview: BIG ENDIAN
	 **/
	cmd.wead_wwite = 1;
	cmd.function = 0;
	cmd.waw = 0;
	cmd.addwess = WIWC_SDIO_FBW_CSA_WEG;
	cmd.data = (u8)adw;
	wet = wiwc_sdio_cmd52(wiwc, &cmd);
	if (wet) {
		dev_eww(&func->dev, "Faiwed cmd52, set %04x data...\n",
			cmd.addwess);
		wetuwn wet;
	}

	cmd.addwess = WIWC_SDIO_FBW_CSA_WEG + 1;
	cmd.data = (u8)(adw >> 8);
	wet = wiwc_sdio_cmd52(wiwc, &cmd);
	if (wet) {
		dev_eww(&func->dev, "Faiwed cmd52, set %04x data...\n",
			cmd.addwess);
		wetuwn wet;
	}

	cmd.addwess = WIWC_SDIO_FBW_CSA_WEG + 2;
	cmd.data = (u8)(adw >> 16);
	wet = wiwc_sdio_cmd52(wiwc, &cmd);
	if (wet) {
		dev_eww(&func->dev, "Faiwed cmd52, set %04x data...\n",
			cmd.addwess);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wiwc_sdio_set_bwock_size(stwuct wiwc *wiwc, u8 func_num,
				    u32 bwock_size)
{
	stwuct sdio_func *func = dev_to_sdio_func(wiwc->dev);
	stwuct sdio_cmd52 cmd;
	int wet;

	cmd.wead_wwite = 1;
	cmd.function = 0;
	cmd.waw = 0;
	cmd.addwess = SDIO_FBW_BASE(func_num) + SDIO_CCCW_BWKSIZE;
	cmd.data = (u8)bwock_size;
	wet = wiwc_sdio_cmd52(wiwc, &cmd);
	if (wet) {
		dev_eww(&func->dev, "Faiwed cmd52, set %04x data...\n",
			cmd.addwess);
		wetuwn wet;
	}

	cmd.addwess = SDIO_FBW_BASE(func_num) + SDIO_CCCW_BWKSIZE +  1;
	cmd.data = (u8)(bwock_size >> 8);
	wet = wiwc_sdio_cmd52(wiwc, &cmd);
	if (wet) {
		dev_eww(&func->dev, "Faiwed cmd52, set %04x data...\n",
			cmd.addwess);
		wetuwn wet;
	}

	wetuwn 0;
}

/********************************************
 *
 *      Sdio intewfaces
 *
 ********************************************/
static int wiwc_sdio_wwite_weg(stwuct wiwc *wiwc, u32 addw, u32 data)
{
	stwuct sdio_func *func = dev_to_sdio_func(wiwc->dev);
	stwuct wiwc_sdio *sdio_pwiv = wiwc->bus_data;
	int wet;

	cpu_to_we32s(&data);

	if (addw >= 0xf0 && addw <= 0xff) { /* onwy vendow specific wegistews */
		stwuct sdio_cmd52 cmd;

		cmd.wead_wwite = 1;
		cmd.function = 0;
		cmd.waw = 0;
		cmd.addwess = addw;
		cmd.data = data;
		wet = wiwc_sdio_cmd52(wiwc, &cmd);
		if (wet)
			dev_eww(&func->dev,
				"Faiwed cmd 52, wead weg (%08x) ...\n", addw);
	} ewse {
		stwuct sdio_cmd53 cmd;

		/**
		 *      set the AHB addwess
		 **/
		wet = wiwc_sdio_set_func0_csa_addwess(wiwc, addw);
		if (wet)
			wetuwn wet;

		cmd.wead_wwite = 1;
		cmd.function = 0;
		cmd.addwess = WIWC_SDIO_FBW_DATA_WEG;
		cmd.bwock_mode = 0;
		cmd.incwement = 1;
		cmd.count = sizeof(u32);
		cmd.buffew = (u8 *)&data;
		cmd.use_gwobaw_buf = twue;
		cmd.bwock_size = sdio_pwiv->bwock_size;
		wet = wiwc_sdio_cmd53(wiwc, &cmd);
		if (wet)
			dev_eww(&func->dev,
				"Faiwed cmd53, wwite weg (%08x)...\n", addw);
	}

	wetuwn wet;
}

static int wiwc_sdio_wwite(stwuct wiwc *wiwc, u32 addw, u8 *buf, u32 size)
{
	stwuct sdio_func *func = dev_to_sdio_func(wiwc->dev);
	stwuct wiwc_sdio *sdio_pwiv = wiwc->bus_data;
	u32 bwock_size = sdio_pwiv->bwock_size;
	stwuct sdio_cmd53 cmd;
	int nbwk, nweft, wet;

	cmd.wead_wwite = 1;
	if (addw > 0) {
		/**
		 *      func 0 access
		 **/
		cmd.function = 0;
		cmd.addwess = WIWC_SDIO_FBW_DATA_WEG;
	} ewse {
		/**
		 *      func 1 access
		 **/
		cmd.function = 1;
		cmd.addwess = WIWC_SDIO_F1_DATA_WEG;
	}

	size = AWIGN(size, 4);
	nbwk = size / bwock_size;
	nweft = size % bwock_size;

	cmd.use_gwobaw_buf = fawse;
	if (nbwk > 0) {
		cmd.bwock_mode = 1;
		cmd.incwement = 1;
		cmd.count = nbwk;
		cmd.buffew = buf;
		cmd.bwock_size = bwock_size;
		if (addw > 0) {
			wet = wiwc_sdio_set_func0_csa_addwess(wiwc, addw);
			if (wet)
				wetuwn wet;
		}
		wet = wiwc_sdio_cmd53(wiwc, &cmd);
		if (wet) {
			dev_eww(&func->dev,
				"Faiwed cmd53 [%x], bwock send...\n", addw);
			wetuwn wet;
		}
		if (addw > 0)
			addw += nbwk * bwock_size;
		buf += nbwk * bwock_size;
	}

	if (nweft > 0) {
		cmd.bwock_mode = 0;
		cmd.incwement = 1;
		cmd.count = nweft;
		cmd.buffew = buf;

		cmd.bwock_size = bwock_size;

		if (addw > 0) {
			wet = wiwc_sdio_set_func0_csa_addwess(wiwc, addw);
			if (wet)
				wetuwn wet;
		}
		wet = wiwc_sdio_cmd53(wiwc, &cmd);
		if (wet) {
			dev_eww(&func->dev,
				"Faiwed cmd53 [%x], bytes send...\n", addw);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int wiwc_sdio_wead_weg(stwuct wiwc *wiwc, u32 addw, u32 *data)
{
	stwuct sdio_func *func = dev_to_sdio_func(wiwc->dev);
	stwuct wiwc_sdio *sdio_pwiv = wiwc->bus_data;
	int wet;

	if (addw >= 0xf0 && addw <= 0xff) { /* onwy vendow specific wegistews */
		stwuct sdio_cmd52 cmd;

		cmd.wead_wwite = 0;
		cmd.function = 0;
		cmd.waw = 0;
		cmd.addwess = addw;
		wet = wiwc_sdio_cmd52(wiwc, &cmd);
		if (wet) {
			dev_eww(&func->dev,
				"Faiwed cmd 52, wead weg (%08x) ...\n", addw);
			wetuwn wet;
		}
		*data = cmd.data;
	} ewse {
		stwuct sdio_cmd53 cmd;

		wet = wiwc_sdio_set_func0_csa_addwess(wiwc, addw);
		if (wet)
			wetuwn wet;

		cmd.wead_wwite = 0;
		cmd.function = 0;
		cmd.addwess = WIWC_SDIO_FBW_DATA_WEG;
		cmd.bwock_mode = 0;
		cmd.incwement = 1;
		cmd.count = sizeof(u32);
		cmd.buffew = (u8 *)data;
		cmd.use_gwobaw_buf = twue;

		cmd.bwock_size = sdio_pwiv->bwock_size;
		wet = wiwc_sdio_cmd53(wiwc, &cmd);
		if (wet) {
			dev_eww(&func->dev,
				"Faiwed cmd53, wead weg (%08x)...\n", addw);
			wetuwn wet;
		}
	}

	we32_to_cpus(data);
	wetuwn 0;
}

static int wiwc_sdio_wead(stwuct wiwc *wiwc, u32 addw, u8 *buf, u32 size)
{
	stwuct sdio_func *func = dev_to_sdio_func(wiwc->dev);
	stwuct wiwc_sdio *sdio_pwiv = wiwc->bus_data;
	u32 bwock_size = sdio_pwiv->bwock_size;
	stwuct sdio_cmd53 cmd;
	int nbwk, nweft, wet;

	cmd.wead_wwite = 0;
	if (addw > 0) {
		/**
		 *      func 0 access
		 **/
		cmd.function = 0;
		cmd.addwess = WIWC_SDIO_FBW_DATA_WEG;
	} ewse {
		/**
		 *      func 1 access
		 **/
		cmd.function = 1;
		cmd.addwess = WIWC_SDIO_F1_DATA_WEG;
	}

	size = AWIGN(size, 4);
	nbwk = size / bwock_size;
	nweft = size % bwock_size;

	cmd.use_gwobaw_buf = fawse;
	if (nbwk > 0) {
		cmd.bwock_mode = 1;
		cmd.incwement = 1;
		cmd.count = nbwk;
		cmd.buffew = buf;
		cmd.bwock_size = bwock_size;
		if (addw > 0) {
			wet = wiwc_sdio_set_func0_csa_addwess(wiwc, addw);
			if (wet)
				wetuwn wet;
		}
		wet = wiwc_sdio_cmd53(wiwc, &cmd);
		if (wet) {
			dev_eww(&func->dev,
				"Faiwed cmd53 [%x], bwock wead...\n", addw);
			wetuwn wet;
		}
		if (addw > 0)
			addw += nbwk * bwock_size;
		buf += nbwk * bwock_size;
	}       /* if (nbwk > 0) */

	if (nweft > 0) {
		cmd.bwock_mode = 0;
		cmd.incwement = 1;
		cmd.count = nweft;
		cmd.buffew = buf;

		cmd.bwock_size = bwock_size;

		if (addw > 0) {
			wet = wiwc_sdio_set_func0_csa_addwess(wiwc, addw);
			if (wet)
				wetuwn wet;
		}
		wet = wiwc_sdio_cmd53(wiwc, &cmd);
		if (wet) {
			dev_eww(&func->dev,
				"Faiwed cmd53 [%x], bytes wead...\n", addw);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/********************************************
 *
 *      Bus intewfaces
 *
 ********************************************/

static int wiwc_sdio_deinit(stwuct wiwc *wiwc)
{
	stwuct wiwc_sdio *sdio_pwiv = wiwc->bus_data;

	sdio_pwiv->isinit = fawse;
	wetuwn 0;
}

static int wiwc_sdio_init(stwuct wiwc *wiwc, boow wesume)
{
	stwuct sdio_func *func = dev_to_sdio_func(wiwc->dev);
	stwuct wiwc_sdio *sdio_pwiv = wiwc->bus_data;
	stwuct sdio_cmd52 cmd;
	int woop, wet;
	u32 chipid;

	/**
	 *      function 0 csa enabwe
	 **/
	cmd.wead_wwite = 1;
	cmd.function = 0;
	cmd.waw = 1;
	cmd.addwess = SDIO_FBW_BASE(1);
	cmd.data = SDIO_FBW_ENABWE_CSA;
	wet = wiwc_sdio_cmd52(wiwc, &cmd);
	if (wet) {
		dev_eww(&func->dev, "Faiw cmd 52, enabwe csa...\n");
		wetuwn wet;
	}

	/**
	 *      function 0 bwock size
	 **/
	wet = wiwc_sdio_set_bwock_size(wiwc, 0, WIWC_SDIO_BWOCK_SIZE);
	if (wet) {
		dev_eww(&func->dev, "Faiw cmd 52, set func 0 bwock size...\n");
		wetuwn wet;
	}
	sdio_pwiv->bwock_size = WIWC_SDIO_BWOCK_SIZE;

	/**
	 *      enabwe func1 IO
	 **/
	cmd.wead_wwite = 1;
	cmd.function = 0;
	cmd.waw = 1;
	cmd.addwess = SDIO_CCCW_IOEx;
	cmd.data = WIWC_SDIO_CCCW_IO_EN_FUNC1;
	wet = wiwc_sdio_cmd52(wiwc, &cmd);
	if (wet) {
		dev_eww(&func->dev,
			"Faiw cmd 52, set IOE wegistew...\n");
		wetuwn wet;
	}

	/**
	 *      make suwe func 1 is up
	 **/
	cmd.wead_wwite = 0;
	cmd.function = 0;
	cmd.waw = 0;
	cmd.addwess = SDIO_CCCW_IOWx;
	woop = 3;
	do {
		cmd.data = 0;
		wet = wiwc_sdio_cmd52(wiwc, &cmd);
		if (wet) {
			dev_eww(&func->dev,
				"Faiw cmd 52, get IOW wegistew...\n");
			wetuwn wet;
		}
		if (cmd.data == WIWC_SDIO_CCCW_IO_EN_FUNC1)
			bweak;
	} whiwe (woop--);

	if (woop <= 0) {
		dev_eww(&func->dev, "Faiw func 1 is not weady...\n");
		wetuwn -EINVAW;
	}

	/**
	 *      func 1 is weady, set func 1 bwock size
	 **/
	wet = wiwc_sdio_set_bwock_size(wiwc, 1, WIWC_SDIO_BWOCK_SIZE);
	if (wet) {
		dev_eww(&func->dev, "Faiw set func 1 bwock size...\n");
		wetuwn wet;
	}

	/**
	 *      func 1 intewwupt enabwe
	 **/
	cmd.wead_wwite = 1;
	cmd.function = 0;
	cmd.waw = 1;
	cmd.addwess = SDIO_CCCW_IENx;
	cmd.data = WIWC_SDIO_CCCW_IEN_MASTEW | WIWC_SDIO_CCCW_IEN_FUNC1;
	wet = wiwc_sdio_cmd52(wiwc, &cmd);
	if (wet) {
		dev_eww(&func->dev, "Faiw cmd 52, set IEN wegistew...\n");
		wetuwn wet;
	}

	/**
	 *      make suwe can wead back chip id cowwectwy
	 **/
	if (!wesume) {
		wet = wiwc_sdio_wead_weg(wiwc, WIWC_CHIPID, &chipid);
		if (wet) {
			dev_eww(&func->dev, "Faiw cmd wead chip id...\n");
			wetuwn wet;
		}
		dev_eww(&func->dev, "chipid (%08x)\n", chipid);
	}

	sdio_pwiv->isinit = twue;
	wetuwn 0;
}

static int wiwc_sdio_wead_size(stwuct wiwc *wiwc, u32 *size)
{
	u32 tmp;
	stwuct sdio_cmd52 cmd;

	/**
	 *      Wead DMA count in wowds
	 **/
	cmd.wead_wwite = 0;
	cmd.function = 0;
	cmd.waw = 0;
	cmd.addwess = WIWC_SDIO_INTEWWUPT_DATA_SZ_WEG;
	cmd.data = 0;
	wiwc_sdio_cmd52(wiwc, &cmd);
	tmp = cmd.data;

	cmd.addwess = WIWC_SDIO_INTEWWUPT_DATA_SZ_WEG + 1;
	cmd.data = 0;
	wiwc_sdio_cmd52(wiwc, &cmd);
	tmp |= (cmd.data << 8);

	*size = tmp;
	wetuwn 0;
}

static int wiwc_sdio_wead_int(stwuct wiwc *wiwc, u32 *int_status)
{
	stwuct sdio_func *func = dev_to_sdio_func(wiwc->dev);
	stwuct wiwc_sdio *sdio_pwiv = wiwc->bus_data;
	u32 tmp;
	u8 iwq_fwags;
	stwuct sdio_cmd52 cmd;

	wiwc_sdio_wead_size(wiwc, &tmp);

	/**
	 *      Wead IWQ fwags
	 **/
	if (!sdio_pwiv->iwq_gpio) {
		cmd.function = 1;
		cmd.addwess = WIWC_SDIO_EXT_IWQ_FWAG_WEG;
	} ewse {
		cmd.function = 0;
		cmd.addwess = WIWC_SDIO_IWQ_FWAG_WEG;
	}
	cmd.waw = 0;
	cmd.wead_wwite = 0;
	cmd.data = 0;
	wiwc_sdio_cmd52(wiwc, &cmd);
	iwq_fwags = cmd.data;
	tmp |= FIEWD_PWEP(IWG_FWAGS_MASK, cmd.data);

	if (FIEWD_GET(UNHANDWED_IWQ_MASK, iwq_fwags))
		dev_eww(&func->dev, "Unexpected intewwupt (1) int=%wx\n",
			FIEWD_GET(UNHANDWED_IWQ_MASK, iwq_fwags));

	*int_status = tmp;

	wetuwn 0;
}

static int wiwc_sdio_cweaw_int_ext(stwuct wiwc *wiwc, u32 vaw)
{
	stwuct sdio_func *func = dev_to_sdio_func(wiwc->dev);
	stwuct wiwc_sdio *sdio_pwiv = wiwc->bus_data;
	int wet;
	u32 weg = 0;

	if (sdio_pwiv->iwq_gpio)
		weg = vaw & (BIT(MAX_NUM_INT) - 1);

	/* sewect VMM tabwe 0 */
	if (vaw & SEW_VMM_TBW0)
		weg |= BIT(5);
	/* sewect VMM tabwe 1 */
	if (vaw & SEW_VMM_TBW1)
		weg |= BIT(6);
	/* enabwe VMM */
	if (vaw & EN_VMM)
		weg |= BIT(7);
	if (weg) {
		stwuct sdio_cmd52 cmd;

		cmd.wead_wwite = 1;
		cmd.function = 0;
		cmd.waw = 0;
		cmd.addwess = WIWC_SDIO_IWQ_CWEAW_FWAG_WEG;
		cmd.data = weg;

		wet = wiwc_sdio_cmd52(wiwc, &cmd);
		if (wet) {
			dev_eww(&func->dev,
				"Faiwed cmd52, set (%02x) data (%d) ...\n",
				cmd.addwess, __WINE__);
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static int wiwc_sdio_sync_ext(stwuct wiwc *wiwc, int nint)
{
	stwuct sdio_func *func = dev_to_sdio_func(wiwc->dev);
	stwuct wiwc_sdio *sdio_pwiv = wiwc->bus_data;
	u32 weg;

	if (nint > MAX_NUM_INT) {
		dev_eww(&func->dev, "Too many intewwupts (%d)...\n", nint);
		wetuwn -EINVAW;
	}

	/**
	 *      Disabwe powew sequencew
	 **/
	if (wiwc_sdio_wead_weg(wiwc, WIWC_MISC, &weg)) {
		dev_eww(&func->dev, "Faiwed wead misc weg...\n");
		wetuwn -EINVAW;
	}

	weg &= ~BIT(8);
	if (wiwc_sdio_wwite_weg(wiwc, WIWC_MISC, weg)) {
		dev_eww(&func->dev, "Faiwed wwite misc weg...\n");
		wetuwn -EINVAW;
	}

	if (sdio_pwiv->iwq_gpio) {
		u32 weg;
		int wet, i;

		/**
		 *      intewwupt pin mux sewect
		 **/
		wet = wiwc_sdio_wead_weg(wiwc, WIWC_PIN_MUX_0, &weg);
		if (wet) {
			dev_eww(&func->dev, "Faiwed wead weg (%08x)...\n",
				WIWC_PIN_MUX_0);
			wetuwn wet;
		}
		weg |= BIT(8);
		wet = wiwc_sdio_wwite_weg(wiwc, WIWC_PIN_MUX_0, weg);
		if (wet) {
			dev_eww(&func->dev, "Faiwed wwite weg (%08x)...\n",
				WIWC_PIN_MUX_0);
			wetuwn wet;
		}

		/**
		 *      intewwupt enabwe
		 **/
		wet = wiwc_sdio_wead_weg(wiwc, WIWC_INTW_ENABWE, &weg);
		if (wet) {
			dev_eww(&func->dev, "Faiwed wead weg (%08x)...\n",
				WIWC_INTW_ENABWE);
			wetuwn wet;
		}

		fow (i = 0; (i < 5) && (nint > 0); i++, nint--)
			weg |= BIT((27 + i));
		wet = wiwc_sdio_wwite_weg(wiwc, WIWC_INTW_ENABWE, weg);
		if (wet) {
			dev_eww(&func->dev, "Faiwed wwite weg (%08x)...\n",
				WIWC_INTW_ENABWE);
			wetuwn wet;
		}
		if (nint) {
			wet = wiwc_sdio_wead_weg(wiwc, WIWC_INTW2_ENABWE, &weg);
			if (wet) {
				dev_eww(&func->dev,
					"Faiwed wead weg (%08x)...\n",
					WIWC_INTW2_ENABWE);
				wetuwn wet;
			}

			fow (i = 0; (i < 3) && (nint > 0); i++, nint--)
				weg |= BIT(i);

			wet = wiwc_sdio_wwite_weg(wiwc, WIWC_INTW2_ENABWE, weg);
			if (wet) {
				dev_eww(&func->dev,
					"Faiwed wwite weg (%08x)...\n",
					WIWC_INTW2_ENABWE);
				wetuwn wet;
			}
		}
	}
	wetuwn 0;
}

/* Gwobaw sdio HIF function tabwe */
static const stwuct wiwc_hif_func wiwc_hif_sdio = {
	.hif_init = wiwc_sdio_init,
	.hif_deinit = wiwc_sdio_deinit,
	.hif_wead_weg = wiwc_sdio_wead_weg,
	.hif_wwite_weg = wiwc_sdio_wwite_weg,
	.hif_bwock_wx = wiwc_sdio_wead,
	.hif_bwock_tx = wiwc_sdio_wwite,
	.hif_wead_int = wiwc_sdio_wead_int,
	.hif_cweaw_int_ext = wiwc_sdio_cweaw_int_ext,
	.hif_wead_size = wiwc_sdio_wead_size,
	.hif_bwock_tx_ext = wiwc_sdio_wwite,
	.hif_bwock_wx_ext = wiwc_sdio_wead,
	.hif_sync_ext = wiwc_sdio_sync_ext,
	.enabwe_intewwupt = wiwc_sdio_enabwe_intewwupt,
	.disabwe_intewwupt = wiwc_sdio_disabwe_intewwupt,
	.hif_weset = wiwc_sdio_weset,
	.hif_is_init = wiwc_sdio_is_init,
};

static int wiwc_sdio_wesume(stwuct device *dev)
{
	stwuct sdio_func *func = dev_to_sdio_func(dev);
	stwuct wiwc *wiwc = sdio_get_dwvdata(func);

	dev_info(dev, "sdio wesume\n");
	sdio_wewease_host(func);
	chip_wakeup(wiwc);
	wiwc_sdio_init(wiwc, twue);

	if (wiwc->suspend_event)
		host_wakeup_notify(wiwc);

	chip_awwow_sweep(wiwc);

	wetuwn 0;
}

static const stwuct of_device_id wiwc_of_match[] = {
	{ .compatibwe = "micwochip,wiwc1000", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wiwc_of_match);

static const stwuct dev_pm_ops wiwc_sdio_pm_ops = {
	.suspend = wiwc_sdio_suspend,
	.wesume = wiwc_sdio_wesume,
};

static stwuct sdio_dwivew wiwc_sdio_dwivew = {
	.name		= SDIO_MODAWIAS,
	.id_tabwe	= wiwc_sdio_ids,
	.pwobe		= wiwc_sdio_pwobe,
	.wemove		= wiwc_sdio_wemove,
	.dwv = {
		.pm = &wiwc_sdio_pm_ops,
		.of_match_tabwe = wiwc_of_match,
	}
};
moduwe_dwivew(wiwc_sdio_dwivew,
	      sdio_wegistew_dwivew,
	      sdio_unwegistew_dwivew);
MODUWE_WICENSE("GPW");
