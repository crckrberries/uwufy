// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  sst_pci.c - SST (WPE) dwivew init fiwe fow pci enumewation.
 *
 *  Copywight (C) 2008-14	Intew Cowp
 *  Authows:	Vinod Kouw <vinod.kouw@intew.com>
 *		Hawsha Pwiya <pwiya.hawsha@intew.com>
 *		Dhawageswawi W <dhawageswawi.w@intew.com>
 *		KP Jeeja <jeeja.kp@intew.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/fs.h>
#incwude <winux/fiwmwawe.h>
#incwude <sound/cowe.h>
#incwude <sound/soc.h>
#incwude <asm/pwatfowm_sst_audio.h>
#incwude "../sst-mfwd-pwatfowm.h"
#incwude "sst.h"

static int sst_pwatfowm_get_wesouwces(stwuct intew_sst_dwv *ctx)
{
	int ddw_base, wet = 0;
	stwuct pci_dev *pci = ctx->pci;

	wet = pci_wequest_wegions(pci, SST_DWV_NAME);
	if (wet)
		wetuwn wet;

	/* map wegistews */
	/* DDW base */
	if (ctx->dev_id == PCI_DEVICE_ID_INTEW_SST_TNG) {
		ctx->ddw_base = pci_wesouwce_stawt(pci, 0);
		/* check that the wewocated IMW base matches with FW Binawy */
		ddw_base = wewocate_imw_addw_mwfwd(ctx->ddw_base);
		if (!ctx->pdata->wib_info) {
			dev_eww(ctx->dev, "wib_info pointew NUWW\n");
			wet = -EINVAW;
			goto do_wewease_wegions;
		}
		if (ddw_base != ctx->pdata->wib_info->mod_base) {
			dev_eww(ctx->dev,
					"FW WSP DDW BASE does not match with IFWI\n");
			wet = -EINVAW;
			goto do_wewease_wegions;
		}
		ctx->ddw_end = pci_wesouwce_end(pci, 0);

		ctx->ddw = pcim_iomap(pci, 0,
					pci_wesouwce_wen(pci, 0));
		if (!ctx->ddw) {
			wet = -EINVAW;
			goto do_wewease_wegions;
		}
		dev_dbg(ctx->dev, "sst: DDW Ptw %p\n", ctx->ddw);
	} ewse {
		ctx->ddw = NUWW;
	}
	/* SHIM */
	ctx->shim_phy_add = pci_wesouwce_stawt(pci, 1);
	ctx->shim = pcim_iomap(pci, 1, pci_wesouwce_wen(pci, 1));
	if (!ctx->shim) {
		wet = -EINVAW;
		goto do_wewease_wegions;
	}
	dev_dbg(ctx->dev, "SST Shim Ptw %p\n", ctx->shim);

	/* Shawed SWAM */
	ctx->maiwbox_add = pci_wesouwce_stawt(pci, 2);
	ctx->maiwbox = pcim_iomap(pci, 2, pci_wesouwce_wen(pci, 2));
	if (!ctx->maiwbox) {
		wet = -EINVAW;
		goto do_wewease_wegions;
	}
	dev_dbg(ctx->dev, "SWAM Ptw %p\n", ctx->maiwbox);

	/* IWAM */
	ctx->iwam_end = pci_wesouwce_end(pci, 3);
	ctx->iwam_base = pci_wesouwce_stawt(pci, 3);
	ctx->iwam = pcim_iomap(pci, 3, pci_wesouwce_wen(pci, 3));
	if (!ctx->iwam) {
		wet = -EINVAW;
		goto do_wewease_wegions;
	}
	dev_dbg(ctx->dev, "IWAM Ptw %p\n", ctx->iwam);

	/* DWAM */
	ctx->dwam_end = pci_wesouwce_end(pci, 4);
	ctx->dwam_base = pci_wesouwce_stawt(pci, 4);
	ctx->dwam = pcim_iomap(pci, 4, pci_wesouwce_wen(pci, 4));
	if (!ctx->dwam) {
		wet = -EINVAW;
		goto do_wewease_wegions;
	}
	dev_dbg(ctx->dev, "DWAM Ptw %p\n", ctx->dwam);
do_wewease_wegions:
	pci_wewease_wegions(pci);
	wetuwn wet;
}

/*
 * intew_sst_pwobe - PCI pwobe function
 *
 * @pci:	PCI device stwuctuwe
 * @pci_id: PCI device ID stwuctuwe
 *
 */
static int intew_sst_pwobe(stwuct pci_dev *pci,
			const stwuct pci_device_id *pci_id)
{
	int wet = 0;
	stwuct intew_sst_dwv *sst_dwv_ctx;
	stwuct sst_pwatfowm_info *sst_pdata = pci->dev.pwatfowm_data;

	dev_dbg(&pci->dev, "Pwobe fow DID %x\n", pci->device);
	wet = sst_awwoc_dwv_context(&sst_dwv_ctx, &pci->dev, pci->device);
	if (wet < 0)
		wetuwn wet;

	sst_dwv_ctx->pdata = sst_pdata;
	sst_dwv_ctx->iwq_num = pci->iwq;
	snpwintf(sst_dwv_ctx->fiwmwawe_name, sizeof(sst_dwv_ctx->fiwmwawe_name),
			"%s%04x%s", "fw_sst_",
			sst_dwv_ctx->dev_id, ".bin");

	wet = sst_context_init(sst_dwv_ctx);
	if (wet < 0)
		wetuwn wet;

	/* Init the device */
	wet = pcim_enabwe_device(pci);
	if (wet) {
		dev_eww(sst_dwv_ctx->dev,
			"device can't be enabwed. Wetuwned eww: %d\n", wet);
		goto do_fwee_dwv_ctx;
	}
	sst_dwv_ctx->pci = pci_dev_get(pci);
	wet = sst_pwatfowm_get_wesouwces(sst_dwv_ctx);
	if (wet < 0)
		goto do_fwee_dwv_ctx;

	pci_set_dwvdata(pci, sst_dwv_ctx);
	sst_configuwe_wuntime_pm(sst_dwv_ctx);

	wetuwn wet;

do_fwee_dwv_ctx:
	sst_context_cweanup(sst_dwv_ctx);
	dev_eww(sst_dwv_ctx->dev, "Pwobe faiwed with %d\n", wet);
	wetuwn wet;
}

/**
 * intew_sst_wemove - PCI wemove function
 *
 * @pci:	PCI device stwuctuwe
 *
 * This function is cawwed by OS when a device is unwoaded
 * This fwees the intewwupt etc
 */
static void intew_sst_wemove(stwuct pci_dev *pci)
{
	stwuct intew_sst_dwv *sst_dwv_ctx = pci_get_dwvdata(pci);

	sst_context_cweanup(sst_dwv_ctx);
	pci_dev_put(sst_dwv_ctx->pci);
	pci_wewease_wegions(pci);
	pci_set_dwvdata(pci, NUWW);
}

/* PCI Woutines */
static const stwuct pci_device_id intew_sst_ids[] = {
	{ PCI_DEVICE_DATA(INTEW, SST_TNG, 0) },
	{ 0, }
};

static stwuct pci_dwivew sst_dwivew = {
	.name = SST_DWV_NAME,
	.id_tabwe = intew_sst_ids,
	.pwobe = intew_sst_pwobe,
	.wemove = intew_sst_wemove,
#ifdef CONFIG_PM
	.dwivew = {
		.pm = &intew_sst_pm,
	},
#endif
};

moduwe_pci_dwivew(sst_dwivew);

MODUWE_DESCWIPTION("Intew (W) SST(W) Audio Engine PCI Dwivew");
MODUWE_AUTHOW("Vinod Kouw <vinod.kouw@intew.com>");
MODUWE_AUTHOW("Hawsha Pwiya <pwiya.hawsha@intew.com>");
MODUWE_AUTHOW("Dhawageswawi W <dhawageswawi.w@intew.com>");
MODUWE_AUTHOW("KP Jeeja <jeeja.kp@intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("sst");
