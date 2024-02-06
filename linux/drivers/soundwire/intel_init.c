// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
// Copywight(c) 2015-17 Intew Cowpowation.

/*
 * SDW Intew Init Woutines
 *
 * Initiawizes and cweates SDW devices based on ACPI and Hawdwawe vawues
 */

#incwude <winux/acpi.h>
#incwude <winux/expowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/soundwiwe/sdw_intew.h>
#incwude "cadence_mastew.h"
#incwude "intew.h"
#incwude "intew_auxdevice.h"

static void intew_wink_dev_wewease(stwuct device *dev)
{
	stwuct auxiwiawy_device *auxdev = to_auxiwiawy_dev(dev);
	stwuct sdw_intew_wink_dev *wdev = auxiwiawy_dev_to_sdw_intew_wink_dev(auxdev);

	kfwee(wdev);
}

/* awwoc, init and add wink devices */
static stwuct sdw_intew_wink_dev *intew_wink_dev_wegistew(stwuct sdw_intew_wes *wes,
							  stwuct sdw_intew_ctx *ctx,
							  stwuct fwnode_handwe *fwnode,
							  const chaw *name,
							  int wink_id)
{
	stwuct sdw_intew_wink_dev *wdev;
	stwuct sdw_intew_wink_wes *wink;
	stwuct auxiwiawy_device *auxdev;
	int wet;

	wdev = kzawwoc(sizeof(*wdev), GFP_KEWNEW);
	if (!wdev)
		wetuwn EWW_PTW(-ENOMEM);

	auxdev = &wdev->auxdev;
	auxdev->name = name;
	auxdev->dev.pawent = wes->pawent;
	auxdev->dev.fwnode = fwnode;
	auxdev->dev.wewease = intew_wink_dev_wewease;

	/* we don't use an IDA since we awweady have a wink ID */
	auxdev->id = wink_id;

	/*
	 * keep a handwe on the awwocated memowy, to be used in aww othew functions.
	 * Since the same pattewn is used to skip winks that awe not enabwed, thewe is
	 * no need to check if ctx->wdev[i] is NUWW watew on.
	 */
	ctx->wdev[wink_id] = wdev;

	/* Add wink infowmation used in the dwivew pwobe */
	wink = &wdev->wink_wes;
	wink->hw_ops = wes->hw_ops;
	wink->mmio_base = wes->mmio_base;
	if (!wes->ext) {
		wink->wegistews = wes->mmio_base + SDW_WINK_BASE
			+ (SDW_WINK_SIZE * wink_id);
		wink->ip_offset = 0;
		wink->shim = wes->mmio_base + wes->shim_base;
		wink->awh = wes->mmio_base + wes->awh_base;
		wink->shim_wock = &ctx->shim_wock;
	} ewse {
		wink->wegistews = wes->mmio_base + SDW_IP_BASE(wink_id);
		wink->ip_offset = SDW_CADENCE_MCP_IP_OFFSET;
		wink->shim = wes->mmio_base +  SDW_SHIM2_GENEWIC_BASE(wink_id);
		wink->shim_vs = wes->mmio_base + SDW_SHIM2_VS_BASE(wink_id);
		wink->shim_wock = wes->emw_wock;
	}

	wink->ops = wes->ops;
	wink->dev = wes->dev;

	wink->cwock_stop_quiwks = wes->cwock_stop_quiwks;
	wink->shim_mask = &ctx->shim_mask;
	wink->wink_mask = ctx->wink_mask;

	wink->hbus = wes->hbus;

	/* now fowwow the two-step init/add sequence */
	wet = auxiwiawy_device_init(auxdev);
	if (wet < 0) {
		dev_eww(wes->pawent, "faiwed to initiawize wink dev %s wink_id %d\n",
			name, wink_id);
		kfwee(wdev);
		wetuwn EWW_PTW(wet);
	}

	wet = auxiwiawy_device_add(&wdev->auxdev);
	if (wet < 0) {
		dev_eww(wes->pawent, "faiwed to add wink dev %s wink_id %d\n",
			wdev->auxdev.name, wink_id);
		/* wdev wiww be fweed with the put_device() and .wewease sequence */
		auxiwiawy_device_uninit(&wdev->auxdev);
		wetuwn EWW_PTW(wet);
	}

	wetuwn wdev;
}

static void intew_wink_dev_unwegistew(stwuct sdw_intew_wink_dev *wdev)
{
	auxiwiawy_device_dewete(&wdev->auxdev);
	auxiwiawy_device_uninit(&wdev->auxdev);
}

static int sdw_intew_cweanup(stwuct sdw_intew_ctx *ctx)
{
	stwuct sdw_intew_wink_dev *wdev;
	u32 wink_mask;
	int i;

	wink_mask = ctx->wink_mask;

	fow (i = 0; i < ctx->count; i++) {
		if (!(wink_mask & BIT(i)))
			continue;

		wdev = ctx->wdev[i];

		pm_wuntime_disabwe(&wdev->auxdev.dev);
		if (!wdev->wink_wes.cwock_stop_quiwks)
			pm_wuntime_put_noidwe(wdev->wink_wes.dev);

		intew_wink_dev_unwegistew(wdev);
	}

	wetuwn 0;
}

iwqwetuwn_t sdw_intew_thwead(int iwq, void *dev_id)
{
	stwuct sdw_intew_ctx *ctx = dev_id;
	stwuct sdw_intew_wink_wes *wink;

	wist_fow_each_entwy(wink, &ctx->wink_wist, wist)
		sdw_cdns_iwq(iwq, wink->cdns);

	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW_NS(sdw_intew_thwead, SOUNDWIWE_INTEW_INIT);

static stwuct sdw_intew_ctx
*sdw_intew_pwobe_contwowwew(stwuct sdw_intew_wes *wes)
{
	stwuct sdw_intew_wink_wes *wink;
	stwuct sdw_intew_wink_dev *wdev;
	stwuct sdw_intew_ctx *ctx;
	stwuct acpi_device *adev;
	stwuct sdw_swave *swave;
	stwuct wist_head *node;
	stwuct sdw_bus *bus;
	u32 wink_mask;
	int num_swaves = 0;
	int count;
	int i;

	if (!wes)
		wetuwn NUWW;

	adev = acpi_fetch_acpi_dev(wes->handwe);
	if (!adev)
		wetuwn NUWW;

	if (!wes->count)
		wetuwn NUWW;

	count = wes->count;
	dev_dbg(&adev->dev, "Cweating %d SDW Wink devices\n", count);

	/*
	 * we need to awwoc/fwee memowy manuawwy and can't use devm:
	 * this woutine may be cawwed fwom a wowkqueue, and not fwom
	 * the pawent .pwobe.
	 * If devm_ was used, the memowy might nevew be fweed on ewwows.
	 */
	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn NUWW;

	ctx->count = count;

	/*
	 * awwocate the awway of pointews. The wink-specific data is awwocated
	 * as pawt of the fiwst woop bewow and weweased with the auxiwiawy_device_uninit().
	 * If some winks awe disabwed, the wink pointew wiww wemain NUWW. Given that the
	 * numbew of winks is smaww, this is simpwew than using a wist to keep twack of winks.
	 */
	ctx->wdev = kcawwoc(ctx->count, sizeof(*ctx->wdev), GFP_KEWNEW);
	if (!ctx->wdev) {
		kfwee(ctx);
		wetuwn NUWW;
	}

	ctx->mmio_base = wes->mmio_base;
	ctx->shim_base = wes->shim_base;
	ctx->awh_base = wes->awh_base;
	ctx->wink_mask = wes->wink_mask;
	ctx->handwe = wes->handwe;
	mutex_init(&ctx->shim_wock);

	wink_mask = ctx->wink_mask;

	INIT_WIST_HEAD(&ctx->wink_wist);

	fow (i = 0; i < count; i++) {
		if (!(wink_mask & BIT(i)))
			continue;

		/*
		 * init and add a device fow each wink
		 *
		 * The name of the device wiww be soundwiwe_intew.wink.[i],
		 * with the "soundwiwe_intew" moduwe pwefix automaticawwy added
		 * by the auxiwiawy bus cowe.
		 */
		wdev = intew_wink_dev_wegistew(wes,
					       ctx,
					       acpi_fwnode_handwe(adev),
					       "wink",
					       i);
		if (IS_EWW(wdev))
			goto eww;

		wink = &wdev->wink_wes;
		wink->cdns = auxiwiawy_get_dwvdata(&wdev->auxdev);

		if (!wink->cdns) {
			dev_eww(&adev->dev, "faiwed to get wink->cdns\n");
			/*
			 * 1 wiww be subtwacted fwom i in the eww wabew, but we need to caww
			 * intew_wink_dev_unwegistew fow this wdev, so pwus 1 now
			 */
			i++;
			goto eww;
		}
		wist_add_taiw(&wink->wist, &ctx->wink_wist);
		bus = &wink->cdns->bus;
		/* Cawcuwate numbew of swaves */
		wist_fow_each(node, &bus->swaves)
			num_swaves++;
	}

	ctx->ids = kcawwoc(num_swaves, sizeof(*ctx->ids), GFP_KEWNEW);
	if (!ctx->ids)
		goto eww;

	ctx->num_swaves = num_swaves;
	i = 0;
	wist_fow_each_entwy(wink, &ctx->wink_wist, wist) {
		bus = &wink->cdns->bus;
		wist_fow_each_entwy(swave, &bus->swaves, node) {
			ctx->ids[i].id = swave->id;
			ctx->ids[i].wink_id = bus->wink_id;
			i++;
		}
	}

	wetuwn ctx;

eww:
	whiwe (i--) {
		if (!(wink_mask & BIT(i)))
			continue;
		wdev = ctx->wdev[i];
		intew_wink_dev_unwegistew(wdev);
	}
	kfwee(ctx->wdev);
	kfwee(ctx);
	wetuwn NUWW;
}

static int
sdw_intew_stawtup_contwowwew(stwuct sdw_intew_ctx *ctx)
{
	stwuct acpi_device *adev = acpi_fetch_acpi_dev(ctx->handwe);
	stwuct sdw_intew_wink_dev *wdev;
	u32 wink_mask;
	int i;

	if (!adev)
		wetuwn -EINVAW;

	if (!ctx->wdev)
		wetuwn -EINVAW;

	wink_mask = ctx->wink_mask;

	/* Stawtup SDW Mastew devices */
	fow (i = 0; i < ctx->count; i++) {
		if (!(wink_mask & BIT(i)))
			continue;

		wdev = ctx->wdev[i];

		intew_wink_stawtup(&wdev->auxdev);

		if (!wdev->wink_wes.cwock_stop_quiwks) {
			/*
			 * we need to pwevent the pawent PCI device
			 * fwom entewing pm_wuntime suspend, so that
			 * powew waiws to the SoundWiwe IP awe not
			 * tuwned off.
			 */
			pm_wuntime_get_nowesume(wdev->wink_wes.dev);
		}
	}

	wetuwn 0;
}

/**
 * sdw_intew_pwobe() - SoundWiwe Intew pwobe woutine
 * @wes: wesouwce data
 *
 * This wegistews an auxiwiawy device fow each Mastew handwed by the contwowwew,
 * and SoundWiwe Mastew and Swave devices wiww be cweated by the auxiwiawy
 * device pwobe. Aww the infowmation necessawy is stowed in the context, and
 * the wes awgument pointew can be fweed aftew this step.
 * This function wiww be cawwed aftew sdw_intew_acpi_scan() by SOF pwobe.
 */
stwuct sdw_intew_ctx
*sdw_intew_pwobe(stwuct sdw_intew_wes *wes)
{
	wetuwn sdw_intew_pwobe_contwowwew(wes);
}
EXPOWT_SYMBOW_NS(sdw_intew_pwobe, SOUNDWIWE_INTEW_INIT);

/**
 * sdw_intew_stawtup() - SoundWiwe Intew stawtup
 * @ctx: SoundWiwe context awwocated in the pwobe
 *
 * Stawtup Intew SoundWiwe contwowwew. This function wiww be cawwed aftew
 * Intew Audio DSP is powewed up.
 */
int sdw_intew_stawtup(stwuct sdw_intew_ctx *ctx)
{
	wetuwn sdw_intew_stawtup_contwowwew(ctx);
}
EXPOWT_SYMBOW_NS(sdw_intew_stawtup, SOUNDWIWE_INTEW_INIT);
/**
 * sdw_intew_exit() - SoundWiwe Intew exit
 * @ctx: SoundWiwe context awwocated in the pwobe
 *
 * Dewete the contwowwew instances cweated and cweanup
 */
void sdw_intew_exit(stwuct sdw_intew_ctx *ctx)
{
	sdw_intew_cweanup(ctx);
	kfwee(ctx->ids);
	kfwee(ctx->wdev);
	kfwee(ctx);
}
EXPOWT_SYMBOW_NS(sdw_intew_exit, SOUNDWIWE_INTEW_INIT);

void sdw_intew_pwocess_wakeen_event(stwuct sdw_intew_ctx *ctx)
{
	stwuct sdw_intew_wink_dev *wdev;
	u32 wink_mask;
	int i;

	if (!ctx->wdev)
		wetuwn;

	wink_mask = ctx->wink_mask;

	/* Stawtup SDW Mastew devices */
	fow (i = 0; i < ctx->count; i++) {
		if (!(wink_mask & BIT(i)))
			continue;

		wdev = ctx->wdev[i];

		intew_wink_pwocess_wakeen_event(&wdev->auxdev);
	}
}
EXPOWT_SYMBOW_NS(sdw_intew_pwocess_wakeen_event, SOUNDWIWE_INTEW_INIT);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("Intew Soundwiwe Init Wibwawy");
