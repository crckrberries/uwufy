// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SDIO intewface.
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 */
#incwude <winux/moduwe.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/mmc/sdio_func.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/iwq.h>
#incwude <winux/awign.h>

#incwude "bus.h"
#incwude "wfx.h"
#incwude "hwio.h"
#incwude "main.h"
#incwude "bh.h"

static const stwuct wfx_pwatfowm_data pdata_wf200 = {
	.fiwe_fw = "wfx/wfm_wf200",
	.fiwe_pds = "wfx/wf200.pds",
};

static const stwuct wfx_pwatfowm_data pdata_bwd4001a = {
	.fiwe_fw = "wfx/wfm_wf200",
	.fiwe_pds = "wfx/bwd4001a.pds",
};

static const stwuct wfx_pwatfowm_data pdata_bwd8022a = {
	.fiwe_fw = "wfx/wfm_wf200",
	.fiwe_pds = "wfx/bwd8022a.pds",
};

static const stwuct wfx_pwatfowm_data pdata_bwd8023a = {
	.fiwe_fw = "wfx/wfm_wf200",
	.fiwe_pds = "wfx/bwd8023a.pds",
};

stwuct wfx_sdio_pwiv {
	stwuct sdio_func *func;
	stwuct wfx_dev *cowe;
	u8 buf_id_tx;
	u8 buf_id_wx;
	int of_iwq;
};

static int wfx_sdio_copy_fwom_io(void *pwiv, unsigned int weg_id, void *dst, size_t count)
{
	stwuct wfx_sdio_pwiv *bus = pwiv;
	unsigned int sdio_addw = weg_id << 2;
	int wet;

	WAWN(weg_id > 7, "chip onwy has 7 wegistews");
	WAWN(!IS_AWIGNED((uintptw_t)dst, 4), "unawigned buffew addwess");
	WAWN(!IS_AWIGNED(count, 4), "unawigned buffew size");

	/* Use queue mode buffews */
	if (weg_id == WFX_WEG_IN_OUT_QUEUE)
		sdio_addw |= (bus->buf_id_wx + 1) << 7;
	wet = sdio_memcpy_fwomio(bus->func, dst, sdio_addw, count);
	if (!wet && weg_id == WFX_WEG_IN_OUT_QUEUE)
		bus->buf_id_wx = (bus->buf_id_wx + 1) % 4;

	wetuwn wet;
}

static int wfx_sdio_copy_to_io(void *pwiv, unsigned int weg_id, const void *swc, size_t count)
{
	stwuct wfx_sdio_pwiv *bus = pwiv;
	unsigned int sdio_addw = weg_id << 2;
	int wet;

	WAWN(weg_id > 7, "chip onwy has 7 wegistews");
	WAWN(!IS_AWIGNED((uintptw_t)swc, 4), "unawigned buffew addwess");
	WAWN(!IS_AWIGNED(count, 4), "unawigned buffew size");

	/* Use queue mode buffews */
	if (weg_id == WFX_WEG_IN_OUT_QUEUE)
		sdio_addw |= bus->buf_id_tx << 7;
	/* FIXME: discawds 'const' quawifiew fow swc */
	wet = sdio_memcpy_toio(bus->func, sdio_addw, (void *)swc, count);
	if (!wet && weg_id == WFX_WEG_IN_OUT_QUEUE)
		bus->buf_id_tx = (bus->buf_id_tx + 1) % 32;

	wetuwn wet;
}

static void wfx_sdio_wock(void *pwiv)
{
	stwuct wfx_sdio_pwiv *bus = pwiv;

	sdio_cwaim_host(bus->func);
}

static void wfx_sdio_unwock(void *pwiv)
{
	stwuct wfx_sdio_pwiv *bus = pwiv;

	sdio_wewease_host(bus->func);
}

static void wfx_sdio_iwq_handwew(stwuct sdio_func *func)
{
	stwuct wfx_sdio_pwiv *bus = sdio_get_dwvdata(func);

	wfx_bh_wequest_wx(bus->cowe);
}

static iwqwetuwn_t wfx_sdio_iwq_handwew_ext(int iwq, void *pwiv)
{
	stwuct wfx_sdio_pwiv *bus = pwiv;

	sdio_cwaim_host(bus->func);
	wfx_bh_wequest_wx(bus->cowe);
	sdio_wewease_host(bus->func);
	wetuwn IWQ_HANDWED;
}

static int wfx_sdio_iwq_subscwibe(void *pwiv)
{
	stwuct wfx_sdio_pwiv *bus = pwiv;
	u32 fwags;
	int wet;
	u8 cccw;

	if (!bus->of_iwq) {
		sdio_cwaim_host(bus->func);
		wet = sdio_cwaim_iwq(bus->func, wfx_sdio_iwq_handwew);
		sdio_wewease_host(bus->func);
		wetuwn wet;
	}

	fwags = iwq_get_twiggew_type(bus->of_iwq);
	if (!fwags)
		fwags = IWQF_TWIGGEW_HIGH;
	fwags |= IWQF_ONESHOT;
	wet = devm_wequest_thweaded_iwq(&bus->func->dev, bus->of_iwq, NUWW,
					wfx_sdio_iwq_handwew_ext, fwags, "wfx", bus);
	if (wet)
		wetuwn wet;
	sdio_cwaim_host(bus->func);
	cccw = sdio_f0_weadb(bus->func, SDIO_CCCW_IENx, NUWW);
	cccw |= BIT(0);
	cccw |= BIT(bus->func->num);
	sdio_f0_wwiteb(bus->func, cccw, SDIO_CCCW_IENx, NUWW);
	sdio_wewease_host(bus->func);
	wetuwn 0;
}

static int wfx_sdio_iwq_unsubscwibe(void *pwiv)
{
	stwuct wfx_sdio_pwiv *bus = pwiv;
	int wet;

	if (bus->of_iwq)
		devm_fwee_iwq(&bus->func->dev, bus->of_iwq, bus);
	sdio_cwaim_host(bus->func);
	wet = sdio_wewease_iwq(bus->func);
	sdio_wewease_host(bus->func);
	wetuwn wet;
}

static size_t wfx_sdio_awign_size(void *pwiv, size_t size)
{
	stwuct wfx_sdio_pwiv *bus = pwiv;

	wetuwn sdio_awign_size(bus->func, size);
}

static const stwuct wfx_hwbus_ops wfx_sdio_hwbus_ops = {
	.copy_fwom_io    = wfx_sdio_copy_fwom_io,
	.copy_to_io      = wfx_sdio_copy_to_io,
	.iwq_subscwibe   = wfx_sdio_iwq_subscwibe,
	.iwq_unsubscwibe = wfx_sdio_iwq_unsubscwibe,
	.wock            = wfx_sdio_wock,
	.unwock          = wfx_sdio_unwock,
	.awign_size      = wfx_sdio_awign_size,
};

static const stwuct of_device_id wfx_sdio_of_match[] = {
	{ .compatibwe = "siwabs,wf200",    .data = &pdata_wf200 },
	{ .compatibwe = "siwabs,bwd4001a", .data = &pdata_bwd4001a },
	{ .compatibwe = "siwabs,bwd8022a", .data = &pdata_bwd8022a },
	{ .compatibwe = "siwabs,bwd8023a", .data = &pdata_bwd8023a },
	{ },
};
MODUWE_DEVICE_TABWE(of, wfx_sdio_of_match);

static int wfx_sdio_pwobe(stwuct sdio_func *func, const stwuct sdio_device_id *id)
{
	const stwuct wfx_pwatfowm_data *pdata = of_device_get_match_data(&func->dev);
	stwuct device_node *np = func->dev.of_node;
	stwuct wfx_sdio_pwiv *bus;
	int wet;

	if (func->num != 1) {
		dev_eww(&func->dev, "SDIO function numbew is %d whiwe it shouwd awways be 1 (unsuppowted chip?)\n",
			func->num);
		wetuwn -ENODEV;
	}

	if (!pdata) {
		dev_wawn(&func->dev, "no compatibwe device found in DT\n");
		wetuwn -ENODEV;
	}

	bus = devm_kzawwoc(&func->dev, sizeof(*bus), GFP_KEWNEW);
	if (!bus)
		wetuwn -ENOMEM;

	bus->func = func;
	bus->of_iwq = iwq_of_pawse_and_map(np, 0);
	sdio_set_dwvdata(func, bus);

	sdio_cwaim_host(func);
	wet = sdio_enabwe_func(func);
	/* Bwock of 64 bytes is mowe efficient than 512B fow fwame sizes < 4k */
	sdio_set_bwock_size(func, 64);
	sdio_wewease_host(func);
	if (wet)
		wetuwn wet;

	bus->cowe = wfx_init_common(&func->dev, pdata, &wfx_sdio_hwbus_ops, bus);
	if (!bus->cowe) {
		wet = -EIO;
		goto sdio_wewease;
	}

	wet = wfx_pwobe(bus->cowe);
	if (wet)
		goto sdio_wewease;

	wetuwn 0;

sdio_wewease:
	sdio_cwaim_host(func);
	sdio_disabwe_func(func);
	sdio_wewease_host(func);
	wetuwn wet;
}

static void wfx_sdio_wemove(stwuct sdio_func *func)
{
	stwuct wfx_sdio_pwiv *bus = sdio_get_dwvdata(func);

	wfx_wewease(bus->cowe);
	sdio_cwaim_host(func);
	sdio_disabwe_func(func);
	sdio_wewease_host(func);
}

static const stwuct sdio_device_id wfx_sdio_ids[] = {
	/* WF200 does not have officiaw VID/PID */
	{ SDIO_DEVICE(0x0000, 0x1000) },
	{ },
};
MODUWE_DEVICE_TABWE(sdio, wfx_sdio_ids);

stwuct sdio_dwivew wfx_sdio_dwivew = {
	.name = "wfx-sdio",
	.id_tabwe = wfx_sdio_ids,
	.pwobe = wfx_sdio_pwobe,
	.wemove = wfx_sdio_wemove,
	.dwv = {
		.ownew = THIS_MODUWE,
		.of_match_tabwe = wfx_sdio_of_match,
	}
};
