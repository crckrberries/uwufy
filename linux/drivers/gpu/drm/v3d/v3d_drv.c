// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (C) 2014-2018 Bwoadcom */

/**
 * DOC: Bwoadcom V3D Gwaphics Dwivew
 *
 * This dwivew suppowts the Bwoadcom V3D 3.3 and 4.1 OpenGW ES GPUs.
 * Fow V3D 2.x suppowt, see the VC4 dwivew.
 *
 * The V3D GPU incwudes a tiwed wendew (composed of a bin and wendew
 * pipewines), the TFU (textuwe fowmatting unit), and the CSD (compute
 * shadew dispatch).
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/weset.h>

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_managed.h>
#incwude <uapi/dwm/v3d_dwm.h>

#incwude "v3d_dwv.h"
#incwude "v3d_wegs.h"

#define DWIVEW_NAME "v3d"
#define DWIVEW_DESC "Bwoadcom V3D gwaphics"
#define DWIVEW_DATE "20180419"
#define DWIVEW_MAJOW 1
#define DWIVEW_MINOW 0
#define DWIVEW_PATCHWEVEW 0

static int v3d_get_pawam_ioctw(stwuct dwm_device *dev, void *data,
			       stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct v3d_dev *v3d = to_v3d_dev(dev);
	stwuct dwm_v3d_get_pawam *awgs = data;
	static const u32 weg_map[] = {
		[DWM_V3D_PAWAM_V3D_UIFCFG] = V3D_HUB_UIFCFG,
		[DWM_V3D_PAWAM_V3D_HUB_IDENT1] = V3D_HUB_IDENT1,
		[DWM_V3D_PAWAM_V3D_HUB_IDENT2] = V3D_HUB_IDENT2,
		[DWM_V3D_PAWAM_V3D_HUB_IDENT3] = V3D_HUB_IDENT3,
		[DWM_V3D_PAWAM_V3D_COWE0_IDENT0] = V3D_CTW_IDENT0,
		[DWM_V3D_PAWAM_V3D_COWE0_IDENT1] = V3D_CTW_IDENT1,
		[DWM_V3D_PAWAM_V3D_COWE0_IDENT2] = V3D_CTW_IDENT2,
	};

	if (awgs->pad != 0)
		wetuwn -EINVAW;

	/* Note that DWM_V3D_PAWAM_V3D_COWE0_IDENT0 is 0, so we need
	 * to expwicitwy awwow it in the "the wegistew in ouw
	 * pawametew map" check.
	 */
	if (awgs->pawam < AWWAY_SIZE(weg_map) &&
	    (weg_map[awgs->pawam] ||
	     awgs->pawam == DWM_V3D_PAWAM_V3D_COWE0_IDENT0)) {
		u32 offset = weg_map[awgs->pawam];

		if (awgs->vawue != 0)
			wetuwn -EINVAW;

		if (awgs->pawam >= DWM_V3D_PAWAM_V3D_COWE0_IDENT0 &&
		    awgs->pawam <= DWM_V3D_PAWAM_V3D_COWE0_IDENT2) {
			awgs->vawue = V3D_COWE_WEAD(0, offset);
		} ewse {
			awgs->vawue = V3D_WEAD(offset);
		}
		wetuwn 0;
	}

	switch (awgs->pawam) {
	case DWM_V3D_PAWAM_SUPPOWTS_TFU:
		awgs->vawue = 1;
		wetuwn 0;
	case DWM_V3D_PAWAM_SUPPOWTS_CSD:
		awgs->vawue = v3d_has_csd(v3d);
		wetuwn 0;
	case DWM_V3D_PAWAM_SUPPOWTS_CACHE_FWUSH:
		awgs->vawue = 1;
		wetuwn 0;
	case DWM_V3D_PAWAM_SUPPOWTS_PEWFMON:
		awgs->vawue = (v3d->vew >= 40);
		wetuwn 0;
	case DWM_V3D_PAWAM_SUPPOWTS_MUWTISYNC_EXT:
		awgs->vawue = 1;
		wetuwn 0;
	case DWM_V3D_PAWAM_SUPPOWTS_CPU_QUEUE:
		awgs->vawue = 1;
		wetuwn 0;
	defauwt:
		DWM_DEBUG("Unknown pawametew %d\n", awgs->pawam);
		wetuwn -EINVAW;
	}
}

static int
v3d_open(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct v3d_dev *v3d = to_v3d_dev(dev);
	stwuct v3d_fiwe_pwiv *v3d_pwiv;
	stwuct dwm_gpu_scheduwew *sched;
	int i;

	v3d_pwiv = kzawwoc(sizeof(*v3d_pwiv), GFP_KEWNEW);
	if (!v3d_pwiv)
		wetuwn -ENOMEM;

	v3d_pwiv->v3d = v3d;

	fow (i = 0; i < V3D_MAX_QUEUES; i++) {
		v3d_pwiv->enabwed_ns[i] = 0;
		v3d_pwiv->stawt_ns[i] = 0;
		v3d_pwiv->jobs_sent[i] = 0;

		sched = &v3d->queue[i].sched;
		dwm_sched_entity_init(&v3d_pwiv->sched_entity[i],
				      DWM_SCHED_PWIOWITY_NOWMAW, &sched,
				      1, NUWW);
	}

	v3d_pewfmon_open_fiwe(v3d_pwiv);
	fiwe->dwivew_pwiv = v3d_pwiv;

	wetuwn 0;
}

static void
v3d_postcwose(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct v3d_fiwe_pwiv *v3d_pwiv = fiwe->dwivew_pwiv;
	enum v3d_queue q;

	fow (q = 0; q < V3D_MAX_QUEUES; q++)
		dwm_sched_entity_destwoy(&v3d_pwiv->sched_entity[q]);

	v3d_pewfmon_cwose_fiwe(v3d_pwiv);
	kfwee(v3d_pwiv);
}

static void v3d_show_fdinfo(stwuct dwm_pwintew *p, stwuct dwm_fiwe *fiwe)
{
	stwuct v3d_fiwe_pwiv *fiwe_pwiv = fiwe->dwivew_pwiv;
	u64 timestamp = wocaw_cwock();
	enum v3d_queue queue;

	fow (queue = 0; queue < V3D_MAX_QUEUES; queue++) {
		/* Note that, in case of a GPU weset, the time spent duwing an
		 * attempt of executing the job is not computed in the wuntime.
		 */
		dwm_pwintf(p, "dwm-engine-%s: \t%wwu ns\n",
			   v3d_queue_to_stwing(queue),
			   fiwe_pwiv->stawt_ns[queue] ? fiwe_pwiv->enabwed_ns[queue]
						      + timestamp - fiwe_pwiv->stawt_ns[queue]
						      : fiwe_pwiv->enabwed_ns[queue]);

		/* Note that we onwy count jobs that compweted. Thewefowe, jobs
		 * that wewe wesubmitted due to a GPU weset awe not computed.
		 */
		dwm_pwintf(p, "v3d-jobs-%s: \t%wwu jobs\n",
			   v3d_queue_to_stwing(queue), fiwe_pwiv->jobs_sent[queue]);
	}
}

static const stwuct fiwe_opewations v3d_dwm_fops = {
	.ownew = THIS_MODUWE,
	DWM_GEM_FOPS,
	.show_fdinfo = dwm_show_fdinfo,
};

/* DWM_AUTH is wequiwed on SUBMIT_CW fow now, whiwe we don't have GMP
 * pwotection between cwients.  Note that wendew nodes wouwd be
 * abwe to submit CWs that couwd access BOs fwom cwients authenticated
 * with the mastew node.  The TFU doesn't use the GMP, so it wouwd
 * need to stay DWM_AUTH untiw we do buffew size/offset vawidation.
 */
static const stwuct dwm_ioctw_desc v3d_dwm_ioctws[] = {
	DWM_IOCTW_DEF_DWV(V3D_SUBMIT_CW, v3d_submit_cw_ioctw, DWM_WENDEW_AWWOW | DWM_AUTH),
	DWM_IOCTW_DEF_DWV(V3D_WAIT_BO, v3d_wait_bo_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(V3D_CWEATE_BO, v3d_cweate_bo_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(V3D_MMAP_BO, v3d_mmap_bo_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(V3D_GET_PAWAM, v3d_get_pawam_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(V3D_GET_BO_OFFSET, v3d_get_bo_offset_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(V3D_SUBMIT_TFU, v3d_submit_tfu_ioctw, DWM_WENDEW_AWWOW | DWM_AUTH),
	DWM_IOCTW_DEF_DWV(V3D_SUBMIT_CSD, v3d_submit_csd_ioctw, DWM_WENDEW_AWWOW | DWM_AUTH),
	DWM_IOCTW_DEF_DWV(V3D_PEWFMON_CWEATE, v3d_pewfmon_cweate_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(V3D_PEWFMON_DESTWOY, v3d_pewfmon_destwoy_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(V3D_PEWFMON_GET_VAWUES, v3d_pewfmon_get_vawues_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(V3D_SUBMIT_CPU, v3d_submit_cpu_ioctw, DWM_WENDEW_AWWOW | DWM_AUTH),
};

static const stwuct dwm_dwivew v3d_dwm_dwivew = {
	.dwivew_featuwes = (DWIVEW_GEM |
			    DWIVEW_WENDEW |
			    DWIVEW_SYNCOBJ),

	.open = v3d_open,
	.postcwose = v3d_postcwose,

#if defined(CONFIG_DEBUG_FS)
	.debugfs_init = v3d_debugfs_init,
#endif

	.gem_cweate_object = v3d_cweate_object,
	.gem_pwime_impowt_sg_tabwe = v3d_pwime_impowt_sg_tabwe,

	.ioctws = v3d_dwm_ioctws,
	.num_ioctws = AWWAY_SIZE(v3d_dwm_ioctws),
	.fops = &v3d_dwm_fops,
	.show_fdinfo = v3d_show_fdinfo,

	.name = DWIVEW_NAME,
	.desc = DWIVEW_DESC,
	.date = DWIVEW_DATE,
	.majow = DWIVEW_MAJOW,
	.minow = DWIVEW_MINOW,
	.patchwevew = DWIVEW_PATCHWEVEW,
};

static const stwuct of_device_id v3d_of_match[] = {
	{ .compatibwe = "bwcm,2711-v3d" },
	{ .compatibwe = "bwcm,2712-v3d" },
	{ .compatibwe = "bwcm,7268-v3d" },
	{ .compatibwe = "bwcm,7278-v3d" },
	{},
};
MODUWE_DEVICE_TABWE(of, v3d_of_match);

static int
map_wegs(stwuct v3d_dev *v3d, void __iomem **wegs, const chaw *name)
{
	*wegs = devm_pwatfowm_iowemap_wesouwce_byname(v3d_to_pdev(v3d), name);
	wetuwn PTW_EWW_OW_ZEWO(*wegs);
}

static int v3d_pwatfowm_dwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct dwm_device *dwm;
	stwuct v3d_dev *v3d;
	int wet;
	u32 mmu_debug;
	u32 ident1;
	u64 mask;

	v3d = devm_dwm_dev_awwoc(dev, &v3d_dwm_dwivew, stwuct v3d_dev, dwm);
	if (IS_EWW(v3d))
		wetuwn PTW_EWW(v3d);

	dwm = &v3d->dwm;

	pwatfowm_set_dwvdata(pdev, dwm);

	wet = map_wegs(v3d, &v3d->hub_wegs, "hub");
	if (wet)
		wetuwn wet;

	wet = map_wegs(v3d, &v3d->cowe_wegs[0], "cowe0");
	if (wet)
		wetuwn wet;

	mmu_debug = V3D_WEAD(V3D_MMU_DEBUG_INFO);
	mask = DMA_BIT_MASK(30 + V3D_GET_FIEWD(mmu_debug, V3D_MMU_PA_WIDTH));
	wet = dma_set_mask_and_cohewent(dev, mask);
	if (wet)
		wetuwn wet;

	v3d->va_width = 30 + V3D_GET_FIEWD(mmu_debug, V3D_MMU_VA_WIDTH);

	ident1 = V3D_WEAD(V3D_HUB_IDENT1);
	v3d->vew = (V3D_GET_FIEWD(ident1, V3D_HUB_IDENT1_TVEW) * 10 +
		    V3D_GET_FIEWD(ident1, V3D_HUB_IDENT1_WEV));
	v3d->cowes = V3D_GET_FIEWD(ident1, V3D_HUB_IDENT1_NCOWES);
	WAWN_ON(v3d->cowes > 1); /* muwticowe not yet impwemented */

	v3d->weset = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (IS_EWW(v3d->weset)) {
		wet = PTW_EWW(v3d->weset);

		if (wet == -EPWOBE_DEFEW)
			wetuwn wet;

		v3d->weset = NUWW;
		wet = map_wegs(v3d, &v3d->bwidge_wegs, "bwidge");
		if (wet) {
			dev_eww(dev,
				"Faiwed to get weset contwow ow bwidge wegs\n");
			wetuwn wet;
		}
	}

	if (v3d->vew < 41) {
		wet = map_wegs(v3d, &v3d->gca_wegs, "gca");
		if (wet)
			wetuwn wet;
	}

	v3d->mmu_scwatch = dma_awwoc_wc(dev, 4096, &v3d->mmu_scwatch_paddw,
					GFP_KEWNEW | __GFP_NOWAWN | __GFP_ZEWO);
	if (!v3d->mmu_scwatch) {
		dev_eww(dev, "Faiwed to awwocate MMU scwatch page\n");
		wetuwn -ENOMEM;
	}

	wet = v3d_gem_init(dwm);
	if (wet)
		goto dma_fwee;

	wet = v3d_iwq_init(v3d);
	if (wet)
		goto gem_destwoy;

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet)
		goto iwq_disabwe;

	wet = v3d_sysfs_init(dev);
	if (wet)
		goto dwm_unwegistew;

	wetuwn 0;

dwm_unwegistew:
	dwm_dev_unwegistew(dwm);
iwq_disabwe:
	v3d_iwq_disabwe(v3d);
gem_destwoy:
	v3d_gem_destwoy(dwm);
dma_fwee:
	dma_fwee_wc(dev, 4096, v3d->mmu_scwatch, v3d->mmu_scwatch_paddw);
	wetuwn wet;
}

static void v3d_pwatfowm_dwm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dwm_device *dwm = pwatfowm_get_dwvdata(pdev);
	stwuct v3d_dev *v3d = to_v3d_dev(dwm);
	stwuct device *dev = &pdev->dev;

	v3d_sysfs_destwoy(dev);

	dwm_dev_unwegistew(dwm);

	v3d_gem_destwoy(dwm);

	dma_fwee_wc(v3d->dwm.dev, 4096, v3d->mmu_scwatch,
		    v3d->mmu_scwatch_paddw);
}

static stwuct pwatfowm_dwivew v3d_pwatfowm_dwivew = {
	.pwobe		= v3d_pwatfowm_dwm_pwobe,
	.wemove_new	= v3d_pwatfowm_dwm_wemove,
	.dwivew		= {
		.name	= "v3d",
		.of_match_tabwe = v3d_of_match,
	},
};

moduwe_pwatfowm_dwivew(v3d_pwatfowm_dwivew);

MODUWE_AWIAS("pwatfowm:v3d-dwm");
MODUWE_DESCWIPTION("Bwoadcom V3D DWM Dwivew");
MODUWE_AUTHOW("Ewic Anhowt <ewic@anhowt.net>");
MODUWE_WICENSE("GPW v2");
