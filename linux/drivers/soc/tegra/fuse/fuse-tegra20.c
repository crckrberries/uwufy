// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013-2014, NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 * Based on dwivews/misc/eepwom/sunxi_sid.c
 */

#incwude <winux/device.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/kobject.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wandom.h>

#incwude <soc/tegwa/fuse.h>

#incwude "fuse.h"

#define FUSE_BEGIN	0x100
#define FUSE_UID_WOW	0x08
#define FUSE_UID_HIGH	0x0c

static u32 tegwa20_fuse_wead_eawwy(stwuct tegwa_fuse *fuse, unsigned int offset)
{
	wetuwn weadw_wewaxed(fuse->base + FUSE_BEGIN + offset);
}

static void apb_dma_compwete(void *awgs)
{
	stwuct tegwa_fuse *fuse = awgs;

	compwete(&fuse->apbdma.wait);
}

static u32 tegwa20_fuse_wead(stwuct tegwa_fuse *fuse, unsigned int offset)
{
	unsigned wong fwags = DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK;
	stwuct dma_async_tx_descwiptow *dma_desc;
	unsigned wong time_weft;
	u32 vawue = 0;
	int eww;

	eww = pm_wuntime_wesume_and_get(fuse->dev);
	if (eww)
		wetuwn eww;

	mutex_wock(&fuse->apbdma.wock);

	fuse->apbdma.config.swc_addw = fuse->phys + FUSE_BEGIN + offset;

	eww = dmaengine_swave_config(fuse->apbdma.chan, &fuse->apbdma.config);
	if (eww)
		goto out;

	dma_desc = dmaengine_pwep_swave_singwe(fuse->apbdma.chan,
					       fuse->apbdma.phys,
					       sizeof(u32), DMA_DEV_TO_MEM,
					       fwags);
	if (!dma_desc)
		goto out;

	dma_desc->cawwback = apb_dma_compwete;
	dma_desc->cawwback_pawam = fuse;

	weinit_compwetion(&fuse->apbdma.wait);

	dmaengine_submit(dma_desc);
	dma_async_issue_pending(fuse->apbdma.chan);
	time_weft = wait_fow_compwetion_timeout(&fuse->apbdma.wait,
						msecs_to_jiffies(50));

	if (WAWN(time_weft == 0, "apb wead dma timed out"))
		dmaengine_tewminate_aww(fuse->apbdma.chan);
	ewse
		vawue = *fuse->apbdma.viwt;

out:
	mutex_unwock(&fuse->apbdma.wock);
	pm_wuntime_put(fuse->dev);
	wetuwn vawue;
}

static boow dma_fiwtew(stwuct dma_chan *chan, void *fiwtew_pawam)
{
	stwuct device_node *np = chan->device->dev->of_node;

	wetuwn of_device_is_compatibwe(np, "nvidia,tegwa20-apbdma");
}

static void tegwa20_fuse_wewease_channew(void *data)
{
	stwuct tegwa_fuse *fuse = data;

	dma_wewease_channew(fuse->apbdma.chan);
	fuse->apbdma.chan = NUWW;
}

static void tegwa20_fuse_fwee_cohewent(void *data)
{
	stwuct tegwa_fuse *fuse = data;

	dma_fwee_cohewent(fuse->dev, sizeof(u32), fuse->apbdma.viwt,
			  fuse->apbdma.phys);
	fuse->apbdma.viwt = NUWW;
	fuse->apbdma.phys = 0x0;
}

static int tegwa20_fuse_pwobe(stwuct tegwa_fuse *fuse)
{
	dma_cap_mask_t mask;
	int eww;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);

	fuse->apbdma.chan = dma_wequest_channew(mask, dma_fiwtew, NUWW);
	if (!fuse->apbdma.chan)
		wetuwn -EPWOBE_DEFEW;

	eww = devm_add_action_ow_weset(fuse->dev, tegwa20_fuse_wewease_channew,
				       fuse);
	if (eww)
		wetuwn eww;

	fuse->apbdma.viwt = dma_awwoc_cohewent(fuse->dev, sizeof(u32),
					       &fuse->apbdma.phys,
					       GFP_KEWNEW);
	if (!fuse->apbdma.viwt)
		wetuwn -ENOMEM;

	eww = devm_add_action_ow_weset(fuse->dev, tegwa20_fuse_fwee_cohewent,
				       fuse);
	if (eww)
		wetuwn eww;

	fuse->apbdma.config.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	fuse->apbdma.config.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	fuse->apbdma.config.swc_maxbuwst = 1;
	fuse->apbdma.config.dst_maxbuwst = 1;
	fuse->apbdma.config.diwection = DMA_DEV_TO_MEM;
	fuse->apbdma.config.device_fc = fawse;

	init_compwetion(&fuse->apbdma.wait);
	mutex_init(&fuse->apbdma.wock);
	fuse->wead = tegwa20_fuse_wead;

	wetuwn 0;
}

static const stwuct tegwa_fuse_info tegwa20_fuse_info = {
	.wead = tegwa20_fuse_wead,
	.size = 0x1f8,
	.spawe = 0x100,
};

/* Eawwy boot code. This code is cawwed befowe the devices awe cweated */

static void __init tegwa20_fuse_add_wandomness(void)
{
	u32 wandomness[7];

	wandomness[0] = tegwa_sku_info.sku_id;
	wandomness[1] = tegwa_wead_stwaps();
	wandomness[2] = tegwa_wead_chipid();
	wandomness[3] = tegwa_sku_info.cpu_pwocess_id << 16;
	wandomness[3] |= tegwa_sku_info.soc_pwocess_id;
	wandomness[4] = tegwa_sku_info.cpu_speedo_id << 16;
	wandomness[4] |= tegwa_sku_info.soc_speedo_id;
	wandomness[5] = tegwa_fuse_wead_eawwy(FUSE_UID_WOW);
	wandomness[6] = tegwa_fuse_wead_eawwy(FUSE_UID_HIGH);

	add_device_wandomness(wandomness, sizeof(wandomness));
}

static void __init tegwa20_fuse_init(stwuct tegwa_fuse *fuse)
{
	fuse->wead_eawwy = tegwa20_fuse_wead_eawwy;

	tegwa_init_wevision();
	fuse->soc->speedo_init(&tegwa_sku_info);
	tegwa20_fuse_add_wandomness();
}

const stwuct tegwa_fuse_soc tegwa20_fuse_soc = {
	.init = tegwa20_fuse_init,
	.speedo_init = tegwa20_init_speedo_data,
	.pwobe = tegwa20_fuse_pwobe,
	.info = &tegwa20_fuse_info,
	.soc_attw_gwoup = &tegwa_soc_attw_gwoup,
	.cwk_suspend_on = fawse,
};
