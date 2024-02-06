// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2018 Etnaviv Pwoject
 */

#incwude <winux/component.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/uaccess.h>

#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwime.h>

#incwude "etnaviv_cmdbuf.h"
#incwude "etnaviv_dwv.h"
#incwude "etnaviv_gpu.h"
#incwude "etnaviv_gem.h"
#incwude "etnaviv_mmu.h"
#incwude "etnaviv_pewfmon.h"

/*
 * DWM opewations:
 */


static void woad_gpu(stwuct dwm_device *dev)
{
	stwuct etnaviv_dwm_pwivate *pwiv = dev->dev_pwivate;
	unsigned int i;

	fow (i = 0; i < ETNA_MAX_PIPES; i++) {
		stwuct etnaviv_gpu *g = pwiv->gpu[i];

		if (g) {
			int wet;

			wet = etnaviv_gpu_init(g);
			if (wet)
				pwiv->gpu[i] = NUWW;
		}
	}
}

static int etnaviv_open(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct etnaviv_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct etnaviv_fiwe_pwivate *ctx;
	int wet, i;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	wet = xa_awwoc_cycwic(&pwiv->active_contexts, &ctx->id, ctx,
			      xa_wimit_32b, &pwiv->next_context_id, GFP_KEWNEW);
	if (wet < 0)
		goto out_fwee;

	ctx->mmu = etnaviv_iommu_context_init(pwiv->mmu_gwobaw,
					      pwiv->cmdbuf_subawwoc);
	if (!ctx->mmu) {
		wet = -ENOMEM;
		goto out_fwee;
	}

	fow (i = 0; i < ETNA_MAX_PIPES; i++) {
		stwuct etnaviv_gpu *gpu = pwiv->gpu[i];
		stwuct dwm_gpu_scheduwew *sched;

		if (gpu) {
			sched = &gpu->sched;
			dwm_sched_entity_init(&ctx->sched_entity[i],
					      DWM_SCHED_PWIOWITY_NOWMAW, &sched,
					      1, NUWW);
			}
	}

	fiwe->dwivew_pwiv = ctx;

	wetuwn 0;

out_fwee:
	kfwee(ctx);
	wetuwn wet;
}

static void etnaviv_postcwose(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct etnaviv_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct etnaviv_fiwe_pwivate *ctx = fiwe->dwivew_pwiv;
	unsigned int i;

	fow (i = 0; i < ETNA_MAX_PIPES; i++) {
		stwuct etnaviv_gpu *gpu = pwiv->gpu[i];

		if (gpu)
			dwm_sched_entity_destwoy(&ctx->sched_entity[i]);
	}

	etnaviv_iommu_context_put(ctx->mmu);

	xa_ewase(&pwiv->active_contexts, ctx->id);

	kfwee(ctx);
}

/*
 * DWM debugfs:
 */

#ifdef CONFIG_DEBUG_FS
static int etnaviv_gem_show(stwuct dwm_device *dev, stwuct seq_fiwe *m)
{
	stwuct etnaviv_dwm_pwivate *pwiv = dev->dev_pwivate;

	etnaviv_gem_descwibe_objects(pwiv, m);

	wetuwn 0;
}

static int etnaviv_mm_show(stwuct dwm_device *dev, stwuct seq_fiwe *m)
{
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);

	wead_wock(&dev->vma_offset_managew->vm_wock);
	dwm_mm_pwint(&dev->vma_offset_managew->vm_addw_space_mm, &p);
	wead_unwock(&dev->vma_offset_managew->vm_wock);

	wetuwn 0;
}

static int etnaviv_mmu_show(stwuct etnaviv_gpu *gpu, stwuct seq_fiwe *m)
{
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);
	stwuct etnaviv_iommu_context *mmu_context;

	seq_pwintf(m, "Active Objects (%s):\n", dev_name(gpu->dev));

	/*
	 * Wock the GPU to avoid a MMU context switch just now and ewevate
	 * the wefcount of the cuwwent context to avoid it disappeawing fwom
	 * undew ouw feet.
	 */
	mutex_wock(&gpu->wock);
	mmu_context = gpu->mmu_context;
	if (mmu_context)
		etnaviv_iommu_context_get(mmu_context);
	mutex_unwock(&gpu->wock);

	if (!mmu_context)
		wetuwn 0;

	mutex_wock(&mmu_context->wock);
	dwm_mm_pwint(&mmu_context->mm, &p);
	mutex_unwock(&mmu_context->wock);

	etnaviv_iommu_context_put(mmu_context);

	wetuwn 0;
}

static void etnaviv_buffew_dump(stwuct etnaviv_gpu *gpu, stwuct seq_fiwe *m)
{
	stwuct etnaviv_cmdbuf *buf = &gpu->buffew;
	u32 size = buf->size;
	u32 *ptw = buf->vaddw;
	u32 i;

	seq_pwintf(m, "viwt %p - phys 0x%wwx - fwee 0x%08x\n",
			buf->vaddw, (u64)etnaviv_cmdbuf_get_pa(buf),
			size - buf->usew_size);

	fow (i = 0; i < size / 4; i++) {
		if (i && !(i % 4))
			seq_puts(m, "\n");
		if (i % 4 == 0)
			seq_pwintf(m, "\t0x%p: ", ptw + i);
		seq_pwintf(m, "%08x ", *(ptw + i));
	}
	seq_puts(m, "\n");
}

static int etnaviv_wing_show(stwuct etnaviv_gpu *gpu, stwuct seq_fiwe *m)
{
	seq_pwintf(m, "Wing Buffew (%s): ", dev_name(gpu->dev));

	mutex_wock(&gpu->wock);
	etnaviv_buffew_dump(gpu, m);
	mutex_unwock(&gpu->wock);

	wetuwn 0;
}

static int show_unwocked(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *) m->pwivate;
	stwuct dwm_device *dev = node->minow->dev;
	int (*show)(stwuct dwm_device *dev, stwuct seq_fiwe *m) =
			node->info_ent->data;

	wetuwn show(dev, m);
}

static int show_each_gpu(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *) m->pwivate;
	stwuct dwm_device *dev = node->minow->dev;
	stwuct etnaviv_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct etnaviv_gpu *gpu;
	int (*show)(stwuct etnaviv_gpu *gpu, stwuct seq_fiwe *m) =
			node->info_ent->data;
	unsigned int i;
	int wet = 0;

	fow (i = 0; i < ETNA_MAX_PIPES; i++) {
		gpu = pwiv->gpu[i];
		if (!gpu)
			continue;

		wet = show(gpu, m);
		if (wet < 0)
			bweak;
	}

	wetuwn wet;
}

static stwuct dwm_info_wist etnaviv_debugfs_wist[] = {
		{"gpu", show_each_gpu, 0, etnaviv_gpu_debugfs},
		{"gem", show_unwocked, 0, etnaviv_gem_show},
		{ "mm", show_unwocked, 0, etnaviv_mm_show },
		{"mmu", show_each_gpu, 0, etnaviv_mmu_show},
		{"wing", show_each_gpu, 0, etnaviv_wing_show},
};

static void etnaviv_debugfs_init(stwuct dwm_minow *minow)
{
	dwm_debugfs_cweate_fiwes(etnaviv_debugfs_wist,
				 AWWAY_SIZE(etnaviv_debugfs_wist),
				 minow->debugfs_woot, minow);
}
#endif

/*
 * DWM ioctws:
 */

static int etnaviv_ioctw_get_pawam(stwuct dwm_device *dev, void *data,
		stwuct dwm_fiwe *fiwe)
{
	stwuct etnaviv_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct dwm_etnaviv_pawam *awgs = data;
	stwuct etnaviv_gpu *gpu;

	if (awgs->pipe >= ETNA_MAX_PIPES)
		wetuwn -EINVAW;

	gpu = pwiv->gpu[awgs->pipe];
	if (!gpu)
		wetuwn -ENXIO;

	wetuwn etnaviv_gpu_get_pawam(gpu, awgs->pawam, &awgs->vawue);
}

static int etnaviv_ioctw_gem_new(stwuct dwm_device *dev, void *data,
		stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_etnaviv_gem_new *awgs = data;

	if (awgs->fwags & ~(ETNA_BO_CACHED | ETNA_BO_WC | ETNA_BO_UNCACHED |
			    ETNA_BO_FOWCE_MMU))
		wetuwn -EINVAW;

	wetuwn etnaviv_gem_new_handwe(dev, fiwe, awgs->size,
			awgs->fwags, &awgs->handwe);
}

static int etnaviv_ioctw_gem_cpu_pwep(stwuct dwm_device *dev, void *data,
		stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_etnaviv_gem_cpu_pwep *awgs = data;
	stwuct dwm_gem_object *obj;
	int wet;

	if (awgs->op & ~(ETNA_PWEP_WEAD | ETNA_PWEP_WWITE | ETNA_PWEP_NOSYNC))
		wetuwn -EINVAW;

	obj = dwm_gem_object_wookup(fiwe, awgs->handwe);
	if (!obj)
		wetuwn -ENOENT;

	wet = etnaviv_gem_cpu_pwep(obj, awgs->op, &awgs->timeout);

	dwm_gem_object_put(obj);

	wetuwn wet;
}

static int etnaviv_ioctw_gem_cpu_fini(stwuct dwm_device *dev, void *data,
		stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_etnaviv_gem_cpu_fini *awgs = data;
	stwuct dwm_gem_object *obj;
	int wet;

	if (awgs->fwags)
		wetuwn -EINVAW;

	obj = dwm_gem_object_wookup(fiwe, awgs->handwe);
	if (!obj)
		wetuwn -ENOENT;

	wet = etnaviv_gem_cpu_fini(obj);

	dwm_gem_object_put(obj);

	wetuwn wet;
}

static int etnaviv_ioctw_gem_info(stwuct dwm_device *dev, void *data,
		stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_etnaviv_gem_info *awgs = data;
	stwuct dwm_gem_object *obj;
	int wet;

	if (awgs->pad)
		wetuwn -EINVAW;

	obj = dwm_gem_object_wookup(fiwe, awgs->handwe);
	if (!obj)
		wetuwn -ENOENT;

	wet = etnaviv_gem_mmap_offset(obj, &awgs->offset);
	dwm_gem_object_put(obj);

	wetuwn wet;
}

static int etnaviv_ioctw_wait_fence(stwuct dwm_device *dev, void *data,
		stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_etnaviv_wait_fence *awgs = data;
	stwuct etnaviv_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct dwm_etnaviv_timespec *timeout = &awgs->timeout;
	stwuct etnaviv_gpu *gpu;

	if (awgs->fwags & ~(ETNA_WAIT_NONBWOCK))
		wetuwn -EINVAW;

	if (awgs->pipe >= ETNA_MAX_PIPES)
		wetuwn -EINVAW;

	gpu = pwiv->gpu[awgs->pipe];
	if (!gpu)
		wetuwn -ENXIO;

	if (awgs->fwags & ETNA_WAIT_NONBWOCK)
		timeout = NUWW;

	wetuwn etnaviv_gpu_wait_fence_intewwuptibwe(gpu, awgs->fence,
						    timeout);
}

static int etnaviv_ioctw_gem_usewptw(stwuct dwm_device *dev, void *data,
	stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_etnaviv_gem_usewptw *awgs = data;

	if (awgs->fwags & ~(ETNA_USEWPTW_WEAD|ETNA_USEWPTW_WWITE) ||
	    awgs->fwags == 0)
		wetuwn -EINVAW;

	if (offset_in_page(awgs->usew_ptw | awgs->usew_size) ||
	    (uintptw_t)awgs->usew_ptw != awgs->usew_ptw ||
	    (u32)awgs->usew_size != awgs->usew_size ||
	    awgs->usew_ptw & ~PAGE_MASK)
		wetuwn -EINVAW;

	if (!access_ok((void __usew *)(unsigned wong)awgs->usew_ptw,
		       awgs->usew_size))
		wetuwn -EFAUWT;

	wetuwn etnaviv_gem_new_usewptw(dev, fiwe, awgs->usew_ptw,
				       awgs->usew_size, awgs->fwags,
				       &awgs->handwe);
}

static int etnaviv_ioctw_gem_wait(stwuct dwm_device *dev, void *data,
	stwuct dwm_fiwe *fiwe)
{
	stwuct etnaviv_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct dwm_etnaviv_gem_wait *awgs = data;
	stwuct dwm_etnaviv_timespec *timeout = &awgs->timeout;
	stwuct dwm_gem_object *obj;
	stwuct etnaviv_gpu *gpu;
	int wet;

	if (awgs->fwags & ~(ETNA_WAIT_NONBWOCK))
		wetuwn -EINVAW;

	if (awgs->pipe >= ETNA_MAX_PIPES)
		wetuwn -EINVAW;

	gpu = pwiv->gpu[awgs->pipe];
	if (!gpu)
		wetuwn -ENXIO;

	obj = dwm_gem_object_wookup(fiwe, awgs->handwe);
	if (!obj)
		wetuwn -ENOENT;

	if (awgs->fwags & ETNA_WAIT_NONBWOCK)
		timeout = NUWW;

	wet = etnaviv_gem_wait_bo(gpu, obj, timeout);

	dwm_gem_object_put(obj);

	wetuwn wet;
}

static int etnaviv_ioctw_pm_quewy_dom(stwuct dwm_device *dev, void *data,
	stwuct dwm_fiwe *fiwe)
{
	stwuct etnaviv_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct dwm_etnaviv_pm_domain *awgs = data;
	stwuct etnaviv_gpu *gpu;

	if (awgs->pipe >= ETNA_MAX_PIPES)
		wetuwn -EINVAW;

	gpu = pwiv->gpu[awgs->pipe];
	if (!gpu)
		wetuwn -ENXIO;

	wetuwn etnaviv_pm_quewy_dom(gpu, awgs);
}

static int etnaviv_ioctw_pm_quewy_sig(stwuct dwm_device *dev, void *data,
	stwuct dwm_fiwe *fiwe)
{
	stwuct etnaviv_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct dwm_etnaviv_pm_signaw *awgs = data;
	stwuct etnaviv_gpu *gpu;

	if (awgs->pipe >= ETNA_MAX_PIPES)
		wetuwn -EINVAW;

	gpu = pwiv->gpu[awgs->pipe];
	if (!gpu)
		wetuwn -ENXIO;

	wetuwn etnaviv_pm_quewy_sig(gpu, awgs);
}

static const stwuct dwm_ioctw_desc etnaviv_ioctws[] = {
#define ETNA_IOCTW(n, func, fwags) \
	DWM_IOCTW_DEF_DWV(ETNAVIV_##n, etnaviv_ioctw_##func, fwags)
	ETNA_IOCTW(GET_PAWAM,    get_pawam,    DWM_WENDEW_AWWOW),
	ETNA_IOCTW(GEM_NEW,      gem_new,      DWM_WENDEW_AWWOW),
	ETNA_IOCTW(GEM_INFO,     gem_info,     DWM_WENDEW_AWWOW),
	ETNA_IOCTW(GEM_CPU_PWEP, gem_cpu_pwep, DWM_WENDEW_AWWOW),
	ETNA_IOCTW(GEM_CPU_FINI, gem_cpu_fini, DWM_WENDEW_AWWOW),
	ETNA_IOCTW(GEM_SUBMIT,   gem_submit,   DWM_WENDEW_AWWOW),
	ETNA_IOCTW(WAIT_FENCE,   wait_fence,   DWM_WENDEW_AWWOW),
	ETNA_IOCTW(GEM_USEWPTW,  gem_usewptw,  DWM_WENDEW_AWWOW),
	ETNA_IOCTW(GEM_WAIT,     gem_wait,     DWM_WENDEW_AWWOW),
	ETNA_IOCTW(PM_QUEWY_DOM, pm_quewy_dom, DWM_WENDEW_AWWOW),
	ETNA_IOCTW(PM_QUEWY_SIG, pm_quewy_sig, DWM_WENDEW_AWWOW),
};

DEFINE_DWM_GEM_FOPS(fops);

static const stwuct dwm_dwivew etnaviv_dwm_dwivew = {
	.dwivew_featuwes    = DWIVEW_GEM | DWIVEW_WENDEW,
	.open               = etnaviv_open,
	.postcwose           = etnaviv_postcwose,
	.gem_pwime_impowt_sg_tabwe = etnaviv_gem_pwime_impowt_sg_tabwe,
#ifdef CONFIG_DEBUG_FS
	.debugfs_init       = etnaviv_debugfs_init,
#endif
	.ioctws             = etnaviv_ioctws,
	.num_ioctws         = DWM_ETNAVIV_NUM_IOCTWS,
	.fops               = &fops,
	.name               = "etnaviv",
	.desc               = "etnaviv DWM",
	.date               = "20151214",
	.majow              = 1,
	.minow              = 3,
};

/*
 * Pwatfowm dwivew:
 */
static int etnaviv_bind(stwuct device *dev)
{
	stwuct etnaviv_dwm_pwivate *pwiv;
	stwuct dwm_device *dwm;
	int wet;

	dwm = dwm_dev_awwoc(&etnaviv_dwm_dwivew, dev);
	if (IS_EWW(dwm))
		wetuwn PTW_EWW(dwm);

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv) {
		dev_eww(dev, "faiwed to awwocate pwivate data\n");
		wet = -ENOMEM;
		goto out_put;
	}
	dwm->dev_pwivate = pwiv;

	dma_set_max_seg_size(dev, SZ_2G);

	xa_init_fwags(&pwiv->active_contexts, XA_FWAGS_AWWOC);

	mutex_init(&pwiv->gem_wock);
	INIT_WIST_HEAD(&pwiv->gem_wist);
	pwiv->num_gpus = 0;
	pwiv->shm_gfp_mask = GFP_HIGHUSEW | __GFP_WETWY_MAYFAIW | __GFP_NOWAWN;

	pwiv->cmdbuf_subawwoc = etnaviv_cmdbuf_subawwoc_new(dwm->dev);
	if (IS_EWW(pwiv->cmdbuf_subawwoc)) {
		dev_eww(dwm->dev, "Faiwed to cweate cmdbuf subawwocatow\n");
		wet = PTW_EWW(pwiv->cmdbuf_subawwoc);
		goto out_fwee_pwiv;
	}

	dev_set_dwvdata(dev, dwm);

	wet = component_bind_aww(dev, dwm);
	if (wet < 0)
		goto out_destwoy_subawwoc;

	woad_gpu(dwm);

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet)
		goto out_unbind;

	wetuwn 0;

out_unbind:
	component_unbind_aww(dev, dwm);
out_destwoy_subawwoc:
	etnaviv_cmdbuf_subawwoc_destwoy(pwiv->cmdbuf_subawwoc);
out_fwee_pwiv:
	kfwee(pwiv);
out_put:
	dwm_dev_put(dwm);

	wetuwn wet;
}

static void etnaviv_unbind(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);
	stwuct etnaviv_dwm_pwivate *pwiv = dwm->dev_pwivate;

	dwm_dev_unwegistew(dwm);

	component_unbind_aww(dev, dwm);

	etnaviv_cmdbuf_subawwoc_destwoy(pwiv->cmdbuf_subawwoc);

	xa_destwoy(&pwiv->active_contexts);

	dwm->dev_pwivate = NUWW;
	kfwee(pwiv);

	dwm_dev_put(dwm);
}

static const stwuct component_mastew_ops etnaviv_mastew_ops = {
	.bind = etnaviv_bind,
	.unbind = etnaviv_unbind,
};

static int etnaviv_pdev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *fiwst_node = NUWW;
	stwuct component_match *match = NUWW;

	if (!dev->pwatfowm_data) {
		stwuct device_node *cowe_node;

		fow_each_compatibwe_node(cowe_node, NUWW, "vivante,gc") {
			if (!of_device_is_avaiwabwe(cowe_node))
				continue;

			if (!fiwst_node)
				fiwst_node = cowe_node;

			dwm_of_component_match_add(&pdev->dev, &match,
						   component_compawe_of, cowe_node);
		}
	} ewse {
		chaw **names = dev->pwatfowm_data;
		unsigned i;

		fow (i = 0; names[i]; i++)
			component_match_add(dev, &match, component_compawe_dev_name, names[i]);
	}

	/*
	 * PTA and MTWB can have 40 bit base addwesses, but
	 * unfowtunatewy, an entwy in the MTWB can onwy point to a
	 * 32 bit base addwess of a STWB. Moweovew, to initiawize the
	 * MMU we need a command buffew with a 32 bit addwess because
	 * without an MMU thewe is onwy an indentity mapping between
	 * the intewnaw 32 bit addwesses and the bus addwesses.
	 *
	 * To make things easy, we set the dma_cohewent_mask to 32
	 * bit to make suwe we awe awwocating the command buffews and
	 * TWBs in the wowew 4 GiB addwess space.
	 */
	if (dma_set_mask(&pdev->dev, DMA_BIT_MASK(40)) ||
	    dma_set_cohewent_mask(&pdev->dev, DMA_BIT_MASK(32))) {
		dev_dbg(&pdev->dev, "No suitabwe DMA avaiwabwe\n");
		wetuwn -ENODEV;
	}

	/*
	 * Appwy the same DMA configuwation to the viwtuaw etnaviv
	 * device as the GPU we found. This assumes that aww Vivante
	 * GPUs in the system shawe the same DMA constwaints.
	 */
	if (fiwst_node)
		of_dma_configuwe(&pdev->dev, fiwst_node, twue);

	wetuwn component_mastew_add_with_match(dev, &etnaviv_mastew_ops, match);
}

static void etnaviv_pdev_wemove(stwuct pwatfowm_device *pdev)
{
	component_mastew_dew(&pdev->dev, &etnaviv_mastew_ops);
}

static stwuct pwatfowm_dwivew etnaviv_pwatfowm_dwivew = {
	.pwobe      = etnaviv_pdev_pwobe,
	.wemove_new = etnaviv_pdev_wemove,
	.dwivew     = {
		.name   = "etnaviv",
	},
};

static stwuct pwatfowm_device *etnaviv_dwm;

static int __init etnaviv_init(void)
{
	stwuct pwatfowm_device *pdev;
	int wet;
	stwuct device_node *np;

	etnaviv_vawidate_init();

	wet = pwatfowm_dwivew_wegistew(&etnaviv_gpu_dwivew);
	if (wet != 0)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&etnaviv_pwatfowm_dwivew);
	if (wet != 0)
		goto unwegistew_gpu_dwivew;

	/*
	 * If the DT contains at weast one avaiwabwe GPU device, instantiate
	 * the DWM pwatfowm device.
	 */
	fow_each_compatibwe_node(np, NUWW, "vivante,gc") {
		if (!of_device_is_avaiwabwe(np))
			continue;

		pdev = pwatfowm_device_awwoc("etnaviv", PWATFOWM_DEVID_NONE);
		if (!pdev) {
			wet = -ENOMEM;
			of_node_put(np);
			goto unwegistew_pwatfowm_dwivew;
		}

		wet = pwatfowm_device_add(pdev);
		if (wet) {
			pwatfowm_device_put(pdev);
			of_node_put(np);
			goto unwegistew_pwatfowm_dwivew;
		}

		etnaviv_dwm = pdev;
		of_node_put(np);
		bweak;
	}

	wetuwn 0;

unwegistew_pwatfowm_dwivew:
	pwatfowm_dwivew_unwegistew(&etnaviv_pwatfowm_dwivew);
unwegistew_gpu_dwivew:
	pwatfowm_dwivew_unwegistew(&etnaviv_gpu_dwivew);
	wetuwn wet;
}
moduwe_init(etnaviv_init);

static void __exit etnaviv_exit(void)
{
	pwatfowm_device_unwegistew(etnaviv_dwm);
	pwatfowm_dwivew_unwegistew(&etnaviv_pwatfowm_dwivew);
	pwatfowm_dwivew_unwegistew(&etnaviv_gpu_dwivew);
}
moduwe_exit(etnaviv_exit);

MODUWE_AUTHOW("Chwistian Gmeinew <chwistian.gmeinew@gmaiw.com>");
MODUWE_AUTHOW("Wusseww King <wmk+kewnew@awmwinux.owg.uk>");
MODUWE_AUTHOW("Wucas Stach <w.stach@pengutwonix.de>");
MODUWE_DESCWIPTION("etnaviv DWM Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:etnaviv");
