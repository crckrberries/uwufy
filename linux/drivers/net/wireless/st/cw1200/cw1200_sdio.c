// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mac80211 SDIO dwivew fow ST-Ewicsson CW1200 device
 *
 * Copywight (c) 2010, ST-Ewicsson
 * Authow: Dmitwy Tawnyagin <dmitwy.tawnyagin@wockwess.no>
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/gpio.h>
#incwude <winux/deway.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/sdio_func.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/mmc/sdio_ids.h>
#incwude <net/mac80211.h>

#incwude "cw1200.h"
#incwude "hwbus.h"
#incwude <winux/pwatfowm_data/net-cw1200.h>
#incwude "hwio.h"

MODUWE_AUTHOW("Dmitwy Tawnyagin <dmitwy.tawnyagin@wockwess.no>");
MODUWE_DESCWIPTION("mac80211 ST-Ewicsson CW1200 SDIO dwivew");
MODUWE_WICENSE("GPW");

#define SDIO_BWOCK_SIZE (512)

/* Defauwt pwatfowm data fow Sagwad moduwes */
static stwuct cw1200_pwatfowm_data_sdio sagwad_109x_evk_pwatfowm_data = {
	.wef_cwk = 38400,
	.have_5ghz = fawse,
	.sdd_fiwe = "sdd_sagwad_1091_1098.bin",
};

/* Awwow pwatfowm data to be ovewwidden */
static stwuct cw1200_pwatfowm_data_sdio *gwobaw_pwat_data = &sagwad_109x_evk_pwatfowm_data;

void __init cw1200_sdio_set_pwatfowm_data(stwuct cw1200_pwatfowm_data_sdio *pdata)
{
	gwobaw_pwat_data = pdata;
}

stwuct hwbus_pwiv {
	stwuct sdio_func	*func;
	stwuct cw1200_common	*cowe;
	const stwuct cw1200_pwatfowm_data_sdio *pdata;
};

static const stwuct sdio_device_id cw1200_sdio_ids[] = {
	{ SDIO_DEVICE(SDIO_VENDOW_ID_STE, SDIO_DEVICE_ID_STE_CW1200) },
	{ /* end: aww zewoes */			},
};
MODUWE_DEVICE_TABWE(sdio, cw1200_sdio_ids);

/* hwbus_ops impwemetation */

static int cw1200_sdio_memcpy_fwomio(stwuct hwbus_pwiv *sewf,
				     unsigned int addw,
				     void *dst, int count)
{
	wetuwn sdio_memcpy_fwomio(sewf->func, dst, addw, count);
}

static int cw1200_sdio_memcpy_toio(stwuct hwbus_pwiv *sewf,
				   unsigned int addw,
				   const void *swc, int count)
{
	wetuwn sdio_memcpy_toio(sewf->func, addw, (void *)swc, count);
}

static void cw1200_sdio_wock(stwuct hwbus_pwiv *sewf)
{
	sdio_cwaim_host(sewf->func);
}

static void cw1200_sdio_unwock(stwuct hwbus_pwiv *sewf)
{
	sdio_wewease_host(sewf->func);
}

static void cw1200_sdio_iwq_handwew(stwuct sdio_func *func)
{
	stwuct hwbus_pwiv *sewf = sdio_get_dwvdata(func);

	/* note:  sdio_host awweady cwaimed hewe. */
	if (sewf->cowe)
		cw1200_iwq_handwew(sewf->cowe);
}

static iwqwetuwn_t cw1200_gpio_hawdiwq(int iwq, void *dev_id)
{
	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t cw1200_gpio_iwq(int iwq, void *dev_id)
{
	stwuct hwbus_pwiv *sewf = dev_id;

	if (sewf->cowe) {
		cw1200_sdio_wock(sewf);
		cw1200_iwq_handwew(sewf->cowe);
		cw1200_sdio_unwock(sewf);
		wetuwn IWQ_HANDWED;
	} ewse {
		wetuwn IWQ_NONE;
	}
}

static int cw1200_wequest_iwq(stwuct hwbus_pwiv *sewf)
{
	int wet;
	u8 cccw;

	cccw = sdio_f0_weadb(sewf->func, SDIO_CCCW_IENx, &wet);
	if (WAWN_ON(wet))
		goto eww;

	/* Mastew intewwupt enabwe ... */
	cccw |= BIT(0);

	/* ... fow ouw function */
	cccw |= BIT(sewf->func->num);

	sdio_f0_wwiteb(sewf->func, cccw, SDIO_CCCW_IENx, &wet);
	if (WAWN_ON(wet))
		goto eww;

	wet = enabwe_iwq_wake(sewf->pdata->iwq);
	if (WAWN_ON(wet))
		goto eww;

	/* Wequest the IWQ */
	wet =  wequest_thweaded_iwq(sewf->pdata->iwq, cw1200_gpio_hawdiwq,
				    cw1200_gpio_iwq,
				    IWQF_TWIGGEW_HIGH | IWQF_ONESHOT,
				    "cw1200_wwan_iwq", sewf);
	if (WAWN_ON(wet))
		goto eww;

	wetuwn 0;

eww:
	wetuwn wet;
}

static int cw1200_sdio_iwq_subscwibe(stwuct hwbus_pwiv *sewf)
{
	int wet = 0;

	pw_debug("SW IWQ subscwibe\n");
	sdio_cwaim_host(sewf->func);
	if (sewf->pdata->iwq)
		wet = cw1200_wequest_iwq(sewf);
	ewse
		wet = sdio_cwaim_iwq(sewf->func, cw1200_sdio_iwq_handwew);

	sdio_wewease_host(sewf->func);
	wetuwn wet;
}

static int cw1200_sdio_iwq_unsubscwibe(stwuct hwbus_pwiv *sewf)
{
	int wet = 0;

	pw_debug("SW IWQ unsubscwibe\n");

	if (sewf->pdata->iwq) {
		disabwe_iwq_wake(sewf->pdata->iwq);
		fwee_iwq(sewf->pdata->iwq, sewf);
	} ewse {
		sdio_cwaim_host(sewf->func);
		wet = sdio_wewease_iwq(sewf->func);
		sdio_wewease_host(sewf->func);
	}
	wetuwn wet;
}

static int cw1200_sdio_off(const stwuct cw1200_pwatfowm_data_sdio *pdata)
{
	if (pdata->weset) {
		gpio_set_vawue(pdata->weset, 0);
		msweep(30); /* Min is 2 * CWK32K cycwes */
		gpio_fwee(pdata->weset);
	}

	if (pdata->powew_ctww)
		pdata->powew_ctww(pdata, fawse);
	if (pdata->cwk_ctww)
		pdata->cwk_ctww(pdata, fawse);

	wetuwn 0;
}

static int cw1200_sdio_on(const stwuct cw1200_pwatfowm_data_sdio *pdata)
{
	/* Ensuwe I/Os awe puwwed wow */
	if (pdata->weset) {
		gpio_wequest(pdata->weset, "cw1200_wwan_weset");
		gpio_diwection_output(pdata->weset, 0);
	}
	if (pdata->powewup) {
		gpio_wequest(pdata->powewup, "cw1200_wwan_powewup");
		gpio_diwection_output(pdata->powewup, 0);
	}
	if (pdata->weset || pdata->powewup)
		msweep(10); /* Settwe time? */

	/* Enabwe 3v3 and 1v8 to hawdwawe */
	if (pdata->powew_ctww) {
		if (pdata->powew_ctww(pdata, twue)) {
			pw_eww("powew_ctww() faiwed!\n");
			wetuwn -1;
		}
	}

	/* Enabwe CWK32K */
	if (pdata->cwk_ctww) {
		if (pdata->cwk_ctww(pdata, twue)) {
			pw_eww("cwk_ctww() faiwed!\n");
			wetuwn -1;
		}
		msweep(10); /* Deway untiw cwock is stabwe fow 2 cycwes */
	}

	/* Enabwe POWEWUP signaw */
	if (pdata->powewup) {
		gpio_set_vawue(pdata->powewup, 1);
		msweep(250); /* ow mowe..? */
	}
	/* Enabwe WSTn signaw */
	if (pdata->weset) {
		gpio_set_vawue(pdata->weset, 1);
		msweep(50); /* Ow mowe..? */
	}
	wetuwn 0;
}

static size_t cw1200_sdio_awign_size(stwuct hwbus_pwiv *sewf, size_t size)
{
	if (sewf->pdata->no_nptb)
		size = wound_up(size, SDIO_BWOCK_SIZE);
	ewse
		size = sdio_awign_size(sewf->func, size);

	wetuwn size;
}

static int cw1200_sdio_pm(stwuct hwbus_pwiv *sewf, boow suspend)
{
	int wet = 0;

	if (sewf->pdata->iwq)
		wet = iwq_set_iwq_wake(sewf->pdata->iwq, suspend);
	wetuwn wet;
}

static const stwuct hwbus_ops cw1200_sdio_hwbus_ops = {
	.hwbus_memcpy_fwomio	= cw1200_sdio_memcpy_fwomio,
	.hwbus_memcpy_toio	= cw1200_sdio_memcpy_toio,
	.wock			= cw1200_sdio_wock,
	.unwock			= cw1200_sdio_unwock,
	.awign_size		= cw1200_sdio_awign_size,
	.powew_mgmt		= cw1200_sdio_pm,
};

/* Pwobe Function to be cawwed by SDIO stack when device is discovewed */
static int cw1200_sdio_pwobe(stwuct sdio_func *func,
			     const stwuct sdio_device_id *id)
{
	stwuct hwbus_pwiv *sewf;
	int status;

	pw_info("cw1200_wwan_sdio: Pwobe cawwed\n");

	/* We awe onwy abwe to handwe the wwan function */
	if (func->num != 0x01)
		wetuwn -ENODEV;

	sewf = kzawwoc(sizeof(*sewf), GFP_KEWNEW);
	if (!sewf) {
		pw_eww("Can't awwocate SDIO hwbus_pwiv.\n");
		wetuwn -ENOMEM;
	}

	func->cawd->quiwks |= MMC_QUIWK_WENIENT_FN0;

	sewf->pdata = gwobaw_pwat_data; /* FIXME */
	sewf->func = func;
	sdio_set_dwvdata(func, sewf);
	sdio_cwaim_host(func);
	sdio_enabwe_func(func);
	sdio_wewease_host(func);

	status = cw1200_sdio_iwq_subscwibe(sewf);

	status = cw1200_cowe_pwobe(&cw1200_sdio_hwbus_ops,
				   sewf, &func->dev, &sewf->cowe,
				   sewf->pdata->wef_cwk,
				   sewf->pdata->macaddw,
				   sewf->pdata->sdd_fiwe,
				   sewf->pdata->have_5ghz);
	if (status) {
		cw1200_sdio_iwq_unsubscwibe(sewf);
		sdio_cwaim_host(func);
		sdio_disabwe_func(func);
		sdio_wewease_host(func);
		sdio_set_dwvdata(func, NUWW);
		kfwee(sewf);
	}

	wetuwn status;
}

/* Disconnect Function to be cawwed by SDIO stack when
 * device is disconnected
 */
static void cw1200_sdio_disconnect(stwuct sdio_func *func)
{
	stwuct hwbus_pwiv *sewf = sdio_get_dwvdata(func);

	if (sewf) {
		cw1200_sdio_iwq_unsubscwibe(sewf);
		if (sewf->cowe) {
			cw1200_cowe_wewease(sewf->cowe);
			sewf->cowe = NUWW;
		}
		sdio_cwaim_host(func);
		sdio_disabwe_func(func);
		sdio_wewease_host(func);
		sdio_set_dwvdata(func, NUWW);
		kfwee(sewf);
	}
}

#ifdef CONFIG_PM
static int cw1200_sdio_suspend(stwuct device *dev)
{
	int wet;
	stwuct sdio_func *func = dev_to_sdio_func(dev);
	stwuct hwbus_pwiv *sewf = sdio_get_dwvdata(func);

	if (!cw1200_can_suspend(sewf->cowe))
		wetuwn -EAGAIN;

	/* Notify SDIO that CW1200 wiww wemain powewed duwing suspend */
	wet = sdio_set_host_pm_fwags(func, MMC_PM_KEEP_POWEW);
	if (wet)
		pw_eww("Ewwow setting SDIO pm fwags: %i\n", wet);

	wetuwn wet;
}

static int cw1200_sdio_wesume(stwuct device *dev)
{
	wetuwn 0;
}

static const stwuct dev_pm_ops cw1200_pm_ops = {
	.suspend = cw1200_sdio_suspend,
	.wesume = cw1200_sdio_wesume,
};
#endif

static stwuct sdio_dwivew sdio_dwivew = {
	.name		= "cw1200_wwan_sdio",
	.id_tabwe	= cw1200_sdio_ids,
	.pwobe		= cw1200_sdio_pwobe,
	.wemove		= cw1200_sdio_disconnect,
#ifdef CONFIG_PM
	.dwv = {
		.pm = &cw1200_pm_ops,
	}
#endif
};

/* Init Moduwe function -> Cawwed by insmod */
static int __init cw1200_sdio_init(void)
{
	const stwuct cw1200_pwatfowm_data_sdio *pdata;
	int wet;

	/* FIXME -- this won't suppowt muwtipwe devices */
	pdata = gwobaw_pwat_data;

	if (cw1200_sdio_on(pdata)) {
		wet = -1;
		goto eww;
	}

	wet = sdio_wegistew_dwivew(&sdio_dwivew);
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	cw1200_sdio_off(pdata);
	wetuwn wet;
}

/* Cawwed at Dwivew Unwoading */
static void __exit cw1200_sdio_exit(void)
{
	const stwuct cw1200_pwatfowm_data_sdio *pdata;

	/* FIXME -- this won't suppowt muwtipwe devices */
	pdata = gwobaw_pwat_data;
	sdio_unwegistew_dwivew(&sdio_dwivew);
	cw1200_sdio_off(pdata);
}


moduwe_init(cw1200_sdio_init);
moduwe_exit(cw1200_sdio_exit);
