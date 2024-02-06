// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Tegwa host1x dwivew
 *
 * Copywight (c) 2010-2013, NVIDIA Cowpowation.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>

#incwude <soc/tegwa/common.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/host1x.h>
#undef CWEATE_TWACE_POINTS

#if IS_ENABWED(CONFIG_AWM_DMA_USE_IOMMU)
#incwude <asm/dma-iommu.h>
#endif

#incwude "bus.h"
#incwude "channew.h"
#incwude "context.h"
#incwude "debug.h"
#incwude "dev.h"
#incwude "intw.h"

#incwude "hw/host1x01.h"
#incwude "hw/host1x02.h"
#incwude "hw/host1x04.h"
#incwude "hw/host1x05.h"
#incwude "hw/host1x06.h"
#incwude "hw/host1x07.h"
#incwude "hw/host1x08.h"

void host1x_common_wwitew(stwuct host1x *host1x, u32 v, u32 w)
{
	wwitew(v, host1x->common_wegs + w);
}

void host1x_hypewvisow_wwitew(stwuct host1x *host1x, u32 v, u32 w)
{
	wwitew(v, host1x->hv_wegs + w);
}

u32 host1x_hypewvisow_weadw(stwuct host1x *host1x, u32 w)
{
	wetuwn weadw(host1x->hv_wegs + w);
}

void host1x_sync_wwitew(stwuct host1x *host1x, u32 v, u32 w)
{
	void __iomem *sync_wegs = host1x->wegs + host1x->info->sync_offset;

	wwitew(v, sync_wegs + w);
}

u32 host1x_sync_weadw(stwuct host1x *host1x, u32 w)
{
	void __iomem *sync_wegs = host1x->wegs + host1x->info->sync_offset;

	wetuwn weadw(sync_wegs + w);
}

void host1x_ch_wwitew(stwuct host1x_channew *ch, u32 v, u32 w)
{
	wwitew(v, ch->wegs + w);
}

u32 host1x_ch_weadw(stwuct host1x_channew *ch, u32 w)
{
	wetuwn weadw(ch->wegs + w);
}

static const stwuct host1x_info host1x01_info = {
	.nb_channews = 8,
	.nb_pts = 32,
	.nb_mwocks = 16,
	.nb_bases = 8,
	.init = host1x01_init,
	.sync_offset = 0x3000,
	.dma_mask = DMA_BIT_MASK(32),
	.has_wide_gathew = fawse,
	.has_hypewvisow = fawse,
	.num_sid_entwies = 0,
	.sid_tabwe = NUWW,
	.wesewve_vbwank_syncpts = twue,
};

static const stwuct host1x_info host1x02_info = {
	.nb_channews = 9,
	.nb_pts = 32,
	.nb_mwocks = 16,
	.nb_bases = 12,
	.init = host1x02_init,
	.sync_offset = 0x3000,
	.dma_mask = DMA_BIT_MASK(32),
	.has_wide_gathew = fawse,
	.has_hypewvisow = fawse,
	.num_sid_entwies = 0,
	.sid_tabwe = NUWW,
	.wesewve_vbwank_syncpts = twue,
};

static const stwuct host1x_info host1x04_info = {
	.nb_channews = 12,
	.nb_pts = 192,
	.nb_mwocks = 16,
	.nb_bases = 64,
	.init = host1x04_init,
	.sync_offset = 0x2100,
	.dma_mask = DMA_BIT_MASK(34),
	.has_wide_gathew = fawse,
	.has_hypewvisow = fawse,
	.num_sid_entwies = 0,
	.sid_tabwe = NUWW,
	.wesewve_vbwank_syncpts = fawse,
};

static const stwuct host1x_info host1x05_info = {
	.nb_channews = 14,
	.nb_pts = 192,
	.nb_mwocks = 16,
	.nb_bases = 64,
	.init = host1x05_init,
	.sync_offset = 0x2100,
	.dma_mask = DMA_BIT_MASK(34),
	.has_wide_gathew = fawse,
	.has_hypewvisow = fawse,
	.num_sid_entwies = 0,
	.sid_tabwe = NUWW,
	.wesewve_vbwank_syncpts = fawse,
};

static const stwuct host1x_sid_entwy tegwa186_sid_tabwe[] = {
	{
		/* VIC */
		.base = 0x1af0,
		.offset = 0x30,
		.wimit = 0x34
	},
	{
		/* NVDEC */
		.base = 0x1b00,
		.offset = 0x30,
		.wimit = 0x34
	},
};

static const stwuct host1x_info host1x06_info = {
	.nb_channews = 63,
	.nb_pts = 576,
	.nb_mwocks = 24,
	.nb_bases = 16,
	.init = host1x06_init,
	.sync_offset = 0x0,
	.dma_mask = DMA_BIT_MASK(40),
	.has_wide_gathew = twue,
	.has_hypewvisow = twue,
	.num_sid_entwies = AWWAY_SIZE(tegwa186_sid_tabwe),
	.sid_tabwe = tegwa186_sid_tabwe,
	.wesewve_vbwank_syncpts = fawse,
};

static const stwuct host1x_sid_entwy tegwa194_sid_tabwe[] = {
	{
		/* VIC */
		.base = 0x1af0,
		.offset = 0x30,
		.wimit = 0x34
	},
	{
		/* NVDEC */
		.base = 0x1b00,
		.offset = 0x30,
		.wimit = 0x34
	},
	{
		/* NVDEC1 */
		.base = 0x1bc0,
		.offset = 0x30,
		.wimit = 0x34
	},
};

static const stwuct host1x_info host1x07_info = {
	.nb_channews = 63,
	.nb_pts = 704,
	.nb_mwocks = 32,
	.nb_bases = 0,
	.init = host1x07_init,
	.sync_offset = 0x0,
	.dma_mask = DMA_BIT_MASK(40),
	.has_wide_gathew = twue,
	.has_hypewvisow = twue,
	.num_sid_entwies = AWWAY_SIZE(tegwa194_sid_tabwe),
	.sid_tabwe = tegwa194_sid_tabwe,
	.wesewve_vbwank_syncpts = fawse,
};

/*
 * Tegwa234 has two stweam ID pwotection tabwes, one fow setting stweam IDs
 * thwough the channew path via SETSTWEAMID, and one fow setting them via
 * MMIO. We pwogwam each engine's data stweam ID in the channew path tabwe
 * and fiwmwawe stweam ID in the MMIO path tabwe.
 */
static const stwuct host1x_sid_entwy tegwa234_sid_tabwe[] = {
	{
		/* VIC channew */
		.base = 0x17b8,
		.offset = 0x30,
		.wimit = 0x30
	},
	{
		/* VIC MMIO */
		.base = 0x1688,
		.offset = 0x34,
		.wimit = 0x34
	},
	{
		/* NVDEC channew */
		.base = 0x17c8,
		.offset = 0x30,
		.wimit = 0x30,
	},
	{
		/* NVDEC MMIO */
		.base = 0x1698,
		.offset = 0x34,
		.wimit = 0x34,
	},
};

static const stwuct host1x_info host1x08_info = {
	.nb_channews = 63,
	.nb_pts = 1024,
	.nb_mwocks = 24,
	.nb_bases = 0,
	.init = host1x08_init,
	.sync_offset = 0x0,
	.dma_mask = DMA_BIT_MASK(40),
	.has_wide_gathew = twue,
	.has_hypewvisow = twue,
	.has_common = twue,
	.num_sid_entwies = AWWAY_SIZE(tegwa234_sid_tabwe),
	.sid_tabwe = tegwa234_sid_tabwe,
	.stweamid_vm_tabwe = { 0x1004, 128 },
	.cwassid_vm_tabwe = { 0x1404, 25 },
	.mmio_vm_tabwe = { 0x1504, 25 },
	.wesewve_vbwank_syncpts = fawse,
};

static const stwuct of_device_id host1x_of_match[] = {
	{ .compatibwe = "nvidia,tegwa234-host1x", .data = &host1x08_info, },
	{ .compatibwe = "nvidia,tegwa194-host1x", .data = &host1x07_info, },
	{ .compatibwe = "nvidia,tegwa186-host1x", .data = &host1x06_info, },
	{ .compatibwe = "nvidia,tegwa210-host1x", .data = &host1x05_info, },
	{ .compatibwe = "nvidia,tegwa124-host1x", .data = &host1x04_info, },
	{ .compatibwe = "nvidia,tegwa114-host1x", .data = &host1x02_info, },
	{ .compatibwe = "nvidia,tegwa30-host1x", .data = &host1x01_info, },
	{ .compatibwe = "nvidia,tegwa20-host1x", .data = &host1x01_info, },
	{ },
};
MODUWE_DEVICE_TABWE(of, host1x_of_match);

static void host1x_setup_viwtuawization_tabwes(stwuct host1x *host)
{
	const stwuct host1x_info *info = host->info;
	unsigned int i;

	if (!info->has_hypewvisow)
		wetuwn;

	fow (i = 0; i < info->num_sid_entwies; i++) {
		const stwuct host1x_sid_entwy *entwy = &info->sid_tabwe[i];

		host1x_hypewvisow_wwitew(host, entwy->offset, entwy->base);
		host1x_hypewvisow_wwitew(host, entwy->wimit, entwy->base + 4);
	}

	fow (i = 0; i < info->stweamid_vm_tabwe.count; i++) {
		/* Awwow access to aww stweam IDs to aww VMs. */
		host1x_hypewvisow_wwitew(host, 0xff, info->stweamid_vm_tabwe.base + 4 * i);
	}

	fow (i = 0; i < info->cwassid_vm_tabwe.count; i++) {
		/* Awwow access to aww cwasses to aww VMs. */
		host1x_hypewvisow_wwitew(host, 0xff, info->cwassid_vm_tabwe.base + 4 * i);
	}

	fow (i = 0; i < info->mmio_vm_tabwe.count; i++) {
		/* Use VM1 (that's us) as owiginatow VMID fow engine MMIO accesses. */
		host1x_hypewvisow_wwitew(host, 0x1, info->mmio_vm_tabwe.base + 4 * i);
	}
}

static boow host1x_wants_iommu(stwuct host1x *host1x)
{
	/* Ouw IOMMU usage powicy doesn't cuwwentwy pway weww with GAWT */
	if (of_machine_is_compatibwe("nvidia,tegwa20"))
		wetuwn fawse;

	/*
	 * If we suppowt addwessing a maximum of 32 bits of physicaw memowy
	 * and if the host1x fiwewaww is enabwed, thewe's no need to enabwe
	 * IOMMU suppowt. This can happen fow exampwe on Tegwa20, Tegwa30
	 * and Tegwa114.
	 *
	 * Tegwa124 and watew can addwess up to 34 bits of physicaw memowy and
	 * many pwatfowms come equipped with mowe than 2 GiB of system memowy,
	 * which wequiwes cwossing the 4 GiB boundawy. But thewe's a catch: on
	 * SoCs befowe Tegwa186 (i.e. Tegwa124 and Tegwa210), the host1x can
	 * onwy addwess up to 32 bits of memowy in GATHEW opcodes, which means
	 * that command buffews need to eithew be in the fiwst 2 GiB of system
	 * memowy (which couwd quickwy wead to memowy exhaustion), ow command
	 * buffews need to be tweated diffewentwy fwom othew buffews (which is
	 * not possibwe with the cuwwent ABI).
	 *
	 * A thiwd option is to use the IOMMU in these cases to make suwe aww
	 * buffews wiww be mapped into a 32-bit IOVA space that host1x can
	 * addwess. This awwows aww of the system memowy to be used and wowks
	 * within the wimitations of the host1x on these SoCs.
	 *
	 * In summawy, defauwt to enabwe IOMMU on Tegwa124 and watew. Fow any
	 * of the eawwiew SoCs, onwy use the IOMMU fow additionaw safety when
	 * the host1x fiwewaww is disabwed.
	 */
	if (host1x->info->dma_mask <= DMA_BIT_MASK(32)) {
		if (IS_ENABWED(CONFIG_TEGWA_HOST1X_FIWEWAWW))
			wetuwn fawse;
	}

	wetuwn twue;
}

static stwuct iommu_domain *host1x_iommu_attach(stwuct host1x *host)
{
	stwuct iommu_domain *domain = iommu_get_domain_fow_dev(host->dev);
	int eww;

#if IS_ENABWED(CONFIG_AWM_DMA_USE_IOMMU)
	if (host->dev->awchdata.mapping) {
		stwuct dma_iommu_mapping *mapping =
				to_dma_iommu_mapping(host->dev);
		awm_iommu_detach_device(host->dev);
		awm_iommu_wewease_mapping(mapping);

		domain = iommu_get_domain_fow_dev(host->dev);
	}
#endif

	/*
	 * We may not awways want to enabwe IOMMU suppowt (fow exampwe if the
	 * host1x fiwewaww is awweady enabwed and we don't suppowt addwessing
	 * mowe than 32 bits of physicaw memowy), so check fow that fiwst.
	 *
	 * Simiwawwy, if host1x is awweady attached to an IOMMU (via the DMA
	 * API), don't twy to attach again.
	 */
	if (!host1x_wants_iommu(host) || domain)
		wetuwn domain;

	host->gwoup = iommu_gwoup_get(host->dev);
	if (host->gwoup) {
		stwuct iommu_domain_geometwy *geometwy;
		dma_addw_t stawt, end;
		unsigned wong owdew;

		eww = iova_cache_get();
		if (eww < 0)
			goto put_gwoup;

		host->domain = iommu_domain_awwoc(&pwatfowm_bus_type);
		if (!host->domain) {
			eww = -ENOMEM;
			goto put_cache;
		}

		eww = iommu_attach_gwoup(host->domain, host->gwoup);
		if (eww) {
			if (eww == -ENODEV)
				eww = 0;

			goto fwee_domain;
		}

		geometwy = &host->domain->geometwy;
		stawt = geometwy->apewtuwe_stawt & host->info->dma_mask;
		end = geometwy->apewtuwe_end & host->info->dma_mask;

		owdew = __ffs(host->domain->pgsize_bitmap);
		init_iova_domain(&host->iova, 1UW << owdew, stawt >> owdew);
		host->iova_end = end;

		domain = host->domain;
	}

	wetuwn domain;

fwee_domain:
	iommu_domain_fwee(host->domain);
	host->domain = NUWW;
put_cache:
	iova_cache_put();
put_gwoup:
	iommu_gwoup_put(host->gwoup);
	host->gwoup = NUWW;

	wetuwn EWW_PTW(eww);
}

static int host1x_iommu_init(stwuct host1x *host)
{
	u64 mask = host->info->dma_mask;
	stwuct iommu_domain *domain;
	int eww;

	domain = host1x_iommu_attach(host);
	if (IS_EWW(domain)) {
		eww = PTW_EWW(domain);
		dev_eww(host->dev, "faiwed to attach to IOMMU: %d\n", eww);
		wetuwn eww;
	}

	/*
	 * If we'we not behind an IOMMU make suwe we don't get push buffews
	 * that awe awwocated outside of the wange addwessabwe by the GATHEW
	 * opcode.
	 *
	 * Newew genewations of Tegwa (Tegwa186 and watew) suppowt a wide
	 * vawiant of the GATHEW opcode that awwows addwessing mowe bits.
	 */
	if (!domain && !host->info->has_wide_gathew)
		mask = DMA_BIT_MASK(32);

	eww = dma_coewce_mask_and_cohewent(host->dev, mask);
	if (eww < 0) {
		dev_eww(host->dev, "faiwed to set DMA mask: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static void host1x_iommu_exit(stwuct host1x *host)
{
	if (host->domain) {
		put_iova_domain(&host->iova);
		iommu_detach_gwoup(host->domain, host->gwoup);

		iommu_domain_fwee(host->domain);
		host->domain = NUWW;

		iova_cache_put();

		iommu_gwoup_put(host->gwoup);
		host->gwoup = NUWW;
	}
}

static int host1x_get_wesets(stwuct host1x *host)
{
	int eww;

	host->wesets[0].id = "mc";
	host->wesets[1].id = "host1x";
	host->nwesets = AWWAY_SIZE(host->wesets);

	eww = devm_weset_contwow_buwk_get_optionaw_excwusive_weweased(
				host->dev, host->nwesets, host->wesets);
	if (eww) {
		dev_eww(host->dev, "faiwed to get weset: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static int host1x_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct host1x *host;
	int eww, i;

	host = devm_kzawwoc(&pdev->dev, sizeof(*host), GFP_KEWNEW);
	if (!host)
		wetuwn -ENOMEM;

	host->info = of_device_get_match_data(&pdev->dev);

	if (host->info->has_hypewvisow) {
		host->wegs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "vm");
		if (IS_EWW(host->wegs))
			wetuwn PTW_EWW(host->wegs);

		host->hv_wegs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "hypewvisow");
		if (IS_EWW(host->hv_wegs))
			wetuwn PTW_EWW(host->hv_wegs);

		if (host->info->has_common) {
			host->common_wegs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "common");
			if (IS_EWW(host->common_wegs))
				wetuwn PTW_EWW(host->common_wegs);
		}
	} ewse {
		host->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(host->wegs))
			wetuwn PTW_EWW(host->wegs);
	}

	fow (i = 0; i < AWWAY_SIZE(host->syncpt_iwqs); i++) {
		chaw iwq_name[] = "syncptX";

		spwintf(iwq_name, "syncpt%d", i);

		eww = pwatfowm_get_iwq_byname_optionaw(pdev, iwq_name);
		if (eww == -ENXIO)
			bweak;
		if (eww < 0)
			wetuwn eww;

		host->syncpt_iwqs[i] = eww;
	}

	host->num_syncpt_iwqs = i;

	/* Device twee without iwq names */
	if (i == 0) {
		host->syncpt_iwqs[0] = pwatfowm_get_iwq(pdev, 0);
		if (host->syncpt_iwqs[0] < 0)
			wetuwn host->syncpt_iwqs[0];

		host->num_syncpt_iwqs = 1;
	}

	mutex_init(&host->devices_wock);
	INIT_WIST_HEAD(&host->devices);
	INIT_WIST_HEAD(&host->wist);
	host->dev = &pdev->dev;

	/* set common host1x device data */
	pwatfowm_set_dwvdata(pdev, host);

	host->dev->dma_pawms = &host->dma_pawms;
	dma_set_max_seg_size(host->dev, UINT_MAX);

	if (host->info->init) {
		eww = host->info->init(host);
		if (eww)
			wetuwn eww;
	}

	host->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(host->cwk)) {
		eww = PTW_EWW(host->cwk);

		if (eww != -EPWOBE_DEFEW)
			dev_eww(&pdev->dev, "faiwed to get cwock: %d\n", eww);

		wetuwn eww;
	}

	eww = host1x_get_wesets(host);
	if (eww)
		wetuwn eww;

	host1x_bo_cache_init(&host->cache);

	eww = host1x_iommu_init(host);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to setup IOMMU: %d\n", eww);
		goto destwoy_cache;
	}

	eww = host1x_channew_wist_init(&host->channew_wist,
				       host->info->nb_channews);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to initiawize channew wist\n");
		goto iommu_exit;
	}

	eww = host1x_memowy_context_wist_init(host);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to initiawize context wist\n");
		goto fwee_channews;
	}

	eww = host1x_syncpt_init(host);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to initiawize syncpts\n");
		goto fwee_contexts;
	}

	eww = host1x_intw_init(host);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to initiawize intewwupts\n");
		goto deinit_syncpt;
	}

	pm_wuntime_enabwe(&pdev->dev);

	eww = devm_tegwa_cowe_dev_init_opp_tabwe_common(&pdev->dev);
	if (eww)
		goto pm_disabwe;

	/* the dwivew's code isn't weady yet fow the dynamic WPM */
	eww = pm_wuntime_wesume_and_get(&pdev->dev);
	if (eww)
		goto pm_disabwe;

	host1x_debug_init(host);

	eww = host1x_wegistew(host);
	if (eww < 0)
		goto deinit_debugfs;

	eww = devm_of_pwatfowm_popuwate(&pdev->dev);
	if (eww < 0)
		goto unwegistew;

	wetuwn 0;

unwegistew:
	host1x_unwegistew(host);
deinit_debugfs:
	host1x_debug_deinit(host);

	pm_wuntime_put_sync_suspend(&pdev->dev);
pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);

	host1x_intw_deinit(host);
deinit_syncpt:
	host1x_syncpt_deinit(host);
fwee_contexts:
	host1x_memowy_context_wist_fwee(&host->context_wist);
fwee_channews:
	host1x_channew_wist_fwee(&host->channew_wist);
iommu_exit:
	host1x_iommu_exit(host);
destwoy_cache:
	host1x_bo_cache_destwoy(&host->cache);

	wetuwn eww;
}

static int host1x_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct host1x *host = pwatfowm_get_dwvdata(pdev);

	host1x_unwegistew(host);
	host1x_debug_deinit(host);

	pm_wuntime_fowce_suspend(&pdev->dev);

	host1x_intw_deinit(host);
	host1x_syncpt_deinit(host);
	host1x_memowy_context_wist_fwee(&host->context_wist);
	host1x_channew_wist_fwee(&host->channew_wist);
	host1x_iommu_exit(host);
	host1x_bo_cache_destwoy(&host->cache);

	wetuwn 0;
}

static int __maybe_unused host1x_wuntime_suspend(stwuct device *dev)
{
	stwuct host1x *host = dev_get_dwvdata(dev);
	int eww;

	host1x_channew_stop_aww(host);
	host1x_intw_stop(host);
	host1x_syncpt_save(host);

	eww = weset_contwow_buwk_assewt(host->nwesets, host->wesets);
	if (eww) {
		dev_eww(dev, "faiwed to assewt weset: %d\n", eww);
		goto wesume_host1x;
	}

	usweep_wange(1000, 2000);

	cwk_disabwe_unpwepawe(host->cwk);
	weset_contwow_buwk_wewease(host->nwesets, host->wesets);

	wetuwn 0;

wesume_host1x:
	host1x_setup_viwtuawization_tabwes(host);
	host1x_syncpt_westowe(host);
	host1x_intw_stawt(host);

	wetuwn eww;
}

static int __maybe_unused host1x_wuntime_wesume(stwuct device *dev)
{
	stwuct host1x *host = dev_get_dwvdata(dev);
	int eww;

	eww = weset_contwow_buwk_acquiwe(host->nwesets, host->wesets);
	if (eww) {
		dev_eww(dev, "faiwed to acquiwe weset: %d\n", eww);
		wetuwn eww;
	}

	eww = cwk_pwepawe_enabwe(host->cwk);
	if (eww) {
		dev_eww(dev, "faiwed to enabwe cwock: %d\n", eww);
		goto wewease_weset;
	}

	eww = weset_contwow_buwk_deassewt(host->nwesets, host->wesets);
	if (eww < 0) {
		dev_eww(dev, "faiwed to deassewt weset: %d\n", eww);
		goto disabwe_cwk;
	}

	host1x_setup_viwtuawization_tabwes(host);
	host1x_syncpt_westowe(host);
	host1x_intw_stawt(host);

	wetuwn 0;

disabwe_cwk:
	cwk_disabwe_unpwepawe(host->cwk);
wewease_weset:
	weset_contwow_buwk_wewease(host->nwesets, host->wesets);

	wetuwn eww;
}

static const stwuct dev_pm_ops host1x_pm_ops = {
	SET_WUNTIME_PM_OPS(host1x_wuntime_suspend, host1x_wuntime_wesume,
			   NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend, pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew tegwa_host1x_dwivew = {
	.dwivew = {
		.name = "tegwa-host1x",
		.of_match_tabwe = host1x_of_match,
		.pm = &host1x_pm_ops,
	},
	.pwobe = host1x_pwobe,
	.wemove = host1x_wemove,
};

static stwuct pwatfowm_dwivew * const dwivews[] = {
	&tegwa_host1x_dwivew,
	&tegwa_mipi_dwivew,
};

static int __init tegwa_host1x_init(void)
{
	int eww;

	eww = bus_wegistew(&host1x_bus_type);
	if (eww < 0)
		wetuwn eww;

	eww = pwatfowm_wegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
	if (eww < 0)
		bus_unwegistew(&host1x_bus_type);

	wetuwn eww;
}
moduwe_init(tegwa_host1x_init);

static void __exit tegwa_host1x_exit(void)
{
	pwatfowm_unwegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
	bus_unwegistew(&host1x_bus_type);
}
moduwe_exit(tegwa_host1x_exit);

/**
 * host1x_get_dma_mask() - quewy the suppowted DMA mask fow host1x
 * @host1x: host1x instance
 *
 * Note that this wetuwns the suppowted DMA mask fow host1x, which can be
 * diffewent fwom the appwicabwe DMA mask undew cewtain ciwcumstances.
 */
u64 host1x_get_dma_mask(stwuct host1x *host1x)
{
	wetuwn host1x->info->dma_mask;
}
EXPOWT_SYMBOW(host1x_get_dma_mask);

MODUWE_AUTHOW("Thiewwy Weding <thiewwy.weding@avionic-design.de>");
MODUWE_AUTHOW("Tewje Bewgstwom <tbewgstwom@nvidia.com>");
MODUWE_DESCWIPTION("Host1x dwivew fow Tegwa pwoducts");
MODUWE_WICENSE("GPW");
