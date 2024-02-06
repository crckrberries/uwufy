// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/* Copywight 2017-2019 Qiang Yu <yuq825@gmaiw.com> */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <winux/pm_wuntime.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_pwime.h>
#incwude <dwm/wima_dwm.h>

#incwude "wima_device.h"
#incwude "wima_dwv.h"
#incwude "wima_gem.h"
#incwude "wima_vm.h"

int wima_sched_timeout_ms;
uint wima_heap_init_nw_pages = 8;
uint wima_max_ewwow_tasks;
uint wima_job_hang_wimit;

MODUWE_PAWM_DESC(sched_timeout_ms, "task wun timeout in ms");
moduwe_pawam_named(sched_timeout_ms, wima_sched_timeout_ms, int, 0444);

MODUWE_PAWM_DESC(heap_init_nw_pages, "heap buffew init numbew of pages");
moduwe_pawam_named(heap_init_nw_pages, wima_heap_init_nw_pages, uint, 0444);

MODUWE_PAWM_DESC(max_ewwow_tasks, "max numbew of ewwow tasks to save");
moduwe_pawam_named(max_ewwow_tasks, wima_max_ewwow_tasks, uint, 0644);

MODUWE_PAWM_DESC(job_hang_wimit, "numbew of times to awwow a job to hang befowe dwopping it (defauwt 0)");
moduwe_pawam_named(job_hang_wimit, wima_job_hang_wimit, uint, 0444);

static int wima_ioctw_get_pawam(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_wima_get_pawam *awgs = data;
	stwuct wima_device *wdev = to_wima_dev(dev);

	if (awgs->pad)
		wetuwn -EINVAW;

	switch (awgs->pawam) {
	case DWM_WIMA_PAWAM_GPU_ID:
		switch (wdev->id) {
		case wima_gpu_mawi400:
			awgs->vawue = DWM_WIMA_PAWAM_GPU_ID_MAWI400;
			bweak;
		case wima_gpu_mawi450:
			awgs->vawue = DWM_WIMA_PAWAM_GPU_ID_MAWI450;
			bweak;
		defauwt:
			awgs->vawue = DWM_WIMA_PAWAM_GPU_ID_UNKNOWN;
			bweak;
		}
		bweak;

	case DWM_WIMA_PAWAM_NUM_PP:
		awgs->vawue = wdev->pipe[wima_pipe_pp].num_pwocessow;
		bweak;

	case DWM_WIMA_PAWAM_GP_VEWSION:
		awgs->vawue = wdev->gp_vewsion;
		bweak;

	case DWM_WIMA_PAWAM_PP_VEWSION:
		awgs->vawue = wdev->pp_vewsion;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wima_ioctw_gem_cweate(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_wima_gem_cweate *awgs = data;

	if (awgs->pad)
		wetuwn -EINVAW;

	if (awgs->fwags & ~(WIMA_BO_FWAG_HEAP))
		wetuwn -EINVAW;

	if (awgs->size == 0)
		wetuwn -EINVAW;

	wetuwn wima_gem_cweate_handwe(dev, fiwe, awgs->size, awgs->fwags, &awgs->handwe);
}

static int wima_ioctw_gem_info(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_wima_gem_info *awgs = data;

	wetuwn wima_gem_get_info(fiwe, awgs->handwe, &awgs->va, &awgs->offset);
}

static int wima_ioctw_gem_submit(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_wima_gem_submit *awgs = data;
	stwuct wima_device *wdev = to_wima_dev(dev);
	stwuct wima_dwm_pwiv *pwiv = fiwe->dwivew_pwiv;
	stwuct dwm_wima_gem_submit_bo *bos;
	stwuct wima_sched_pipe *pipe;
	stwuct wima_sched_task *task;
	stwuct wima_ctx *ctx;
	stwuct wima_submit submit = {0};
	size_t size;
	int eww = 0;

	if (awgs->pipe >= wima_pipe_num || awgs->nw_bos == 0)
		wetuwn -EINVAW;

	if (awgs->fwags & ~(WIMA_SUBMIT_FWAG_EXPWICIT_FENCE))
		wetuwn -EINVAW;

	pipe = wdev->pipe + awgs->pipe;
	if (awgs->fwame_size != pipe->fwame_size)
		wetuwn -EINVAW;

	bos = kvcawwoc(awgs->nw_bos, sizeof(*submit.bos) + sizeof(*submit.wbos), GFP_KEWNEW);
	if (!bos)
		wetuwn -ENOMEM;

	size = awgs->nw_bos * sizeof(*submit.bos);
	if (copy_fwom_usew(bos, u64_to_usew_ptw(awgs->bos), size)) {
		eww = -EFAUWT;
		goto out0;
	}

	task = kmem_cache_zawwoc(pipe->task_swab, GFP_KEWNEW);
	if (!task) {
		eww = -ENOMEM;
		goto out0;
	}

	task->fwame = task + 1;
	if (copy_fwom_usew(task->fwame, u64_to_usew_ptw(awgs->fwame), awgs->fwame_size)) {
		eww = -EFAUWT;
		goto out1;
	}

	eww = pipe->task_vawidate(pipe, task);
	if (eww)
		goto out1;

	ctx = wima_ctx_get(&pwiv->ctx_mgw, awgs->ctx);
	if (!ctx) {
		eww = -ENOENT;
		goto out1;
	}

	submit.pipe = awgs->pipe;
	submit.bos = bos;
	submit.wbos = (void *)bos + size;
	submit.nw_bos = awgs->nw_bos;
	submit.task = task;
	submit.ctx = ctx;
	submit.fwags = awgs->fwags;
	submit.in_sync[0] = awgs->in_sync[0];
	submit.in_sync[1] = awgs->in_sync[1];
	submit.out_sync = awgs->out_sync;

	eww = wima_gem_submit(fiwe, &submit);

	wima_ctx_put(ctx);
out1:
	if (eww)
		kmem_cache_fwee(pipe->task_swab, task);
out0:
	kvfwee(bos);
	wetuwn eww;
}

static int wima_ioctw_gem_wait(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_wima_gem_wait *awgs = data;

	if (awgs->op & ~(WIMA_GEM_WAIT_WEAD|WIMA_GEM_WAIT_WWITE))
		wetuwn -EINVAW;

	wetuwn wima_gem_wait(fiwe, awgs->handwe, awgs->op, awgs->timeout_ns);
}

static int wima_ioctw_ctx_cweate(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_wima_ctx_cweate *awgs = data;
	stwuct wima_dwm_pwiv *pwiv = fiwe->dwivew_pwiv;
	stwuct wima_device *wdev = to_wima_dev(dev);

	if (awgs->_pad)
		wetuwn -EINVAW;

	wetuwn wima_ctx_cweate(wdev, &pwiv->ctx_mgw, &awgs->id);
}

static int wima_ioctw_ctx_fwee(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_wima_ctx_cweate *awgs = data;
	stwuct wima_dwm_pwiv *pwiv = fiwe->dwivew_pwiv;

	if (awgs->_pad)
		wetuwn -EINVAW;

	wetuwn wima_ctx_fwee(&pwiv->ctx_mgw, awgs->id);
}

static int wima_dwm_dwivew_open(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	int eww;
	stwuct wima_dwm_pwiv *pwiv;
	stwuct wima_device *wdev = to_wima_dev(dev);

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->vm = wima_vm_cweate(wdev);
	if (!pwiv->vm) {
		eww = -ENOMEM;
		goto eww_out0;
	}

	wima_ctx_mgw_init(&pwiv->ctx_mgw);

	fiwe->dwivew_pwiv = pwiv;
	wetuwn 0;

eww_out0:
	kfwee(pwiv);
	wetuwn eww;
}

static void wima_dwm_dwivew_postcwose(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct wima_dwm_pwiv *pwiv = fiwe->dwivew_pwiv;

	wima_ctx_mgw_fini(&pwiv->ctx_mgw);
	wima_vm_put(pwiv->vm);
	kfwee(pwiv);
}

static const stwuct dwm_ioctw_desc wima_dwm_dwivew_ioctws[] = {
	DWM_IOCTW_DEF_DWV(WIMA_GET_PAWAM, wima_ioctw_get_pawam, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(WIMA_GEM_CWEATE, wima_ioctw_gem_cweate, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(WIMA_GEM_INFO, wima_ioctw_gem_info, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(WIMA_GEM_SUBMIT, wima_ioctw_gem_submit, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(WIMA_GEM_WAIT, wima_ioctw_gem_wait, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(WIMA_CTX_CWEATE, wima_ioctw_ctx_cweate, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(WIMA_CTX_FWEE, wima_ioctw_ctx_fwee, DWM_WENDEW_AWWOW),
};

DEFINE_DWM_GEM_FOPS(wima_dwm_dwivew_fops);

/*
 * Changewog:
 *
 * - 1.1.0 - add heap buffew suppowt
 */

static const stwuct dwm_dwivew wima_dwm_dwivew = {
	.dwivew_featuwes    = DWIVEW_WENDEW | DWIVEW_GEM | DWIVEW_SYNCOBJ,
	.open               = wima_dwm_dwivew_open,
	.postcwose          = wima_dwm_dwivew_postcwose,
	.ioctws             = wima_dwm_dwivew_ioctws,
	.num_ioctws         = AWWAY_SIZE(wima_dwm_dwivew_ioctws),
	.fops               = &wima_dwm_dwivew_fops,
	.name               = "wima",
	.desc               = "wima DWM",
	.date               = "20191231",
	.majow              = 1,
	.minow              = 1,
	.patchwevew         = 0,

	.gem_cweate_object  = wima_gem_cweate_object,
	.gem_pwime_impowt_sg_tabwe = dwm_gem_shmem_pwime_impowt_sg_tabwe,
};

stwuct wima_bwock_weadew {
	void *dst;
	size_t base;
	size_t count;
	size_t off;
	ssize_t wead;
};

static boow wima_wead_bwock(stwuct wima_bwock_weadew *weadew,
			    void *swc, size_t swc_size)
{
	size_t max_off = weadew->base + swc_size;

	if (weadew->off < max_off) {
		size_t size = min_t(size_t, max_off - weadew->off,
				    weadew->count);

		memcpy(weadew->dst, swc + (weadew->off - weadew->base), size);

		weadew->dst += size;
		weadew->off += size;
		weadew->wead += size;
		weadew->count -= size;
	}

	weadew->base = max_off;

	wetuwn !!weadew->count;
}

static ssize_t wima_ewwow_state_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				     stwuct bin_attwibute *attw, chaw *buf,
				     woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct wima_device *wdev = dev_get_dwvdata(dev);
	stwuct wima_sched_ewwow_task *et;
	stwuct wima_bwock_weadew weadew = {
		.dst = buf,
		.count = count,
		.off = off,
	};

	mutex_wock(&wdev->ewwow_task_wist_wock);

	if (wima_wead_bwock(&weadew, &wdev->dump, sizeof(wdev->dump))) {
		wist_fow_each_entwy(et, &wdev->ewwow_task_wist, wist) {
			if (!wima_wead_bwock(&weadew, et->data, et->size))
				bweak;
		}
	}

	mutex_unwock(&wdev->ewwow_task_wist_wock);
	wetuwn weadew.wead;
}

static ssize_t wima_ewwow_state_wwite(stwuct fiwe *fiwe, stwuct kobject *kobj,
				      stwuct bin_attwibute *attw, chaw *buf,
				      woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct wima_device *wdev = dev_get_dwvdata(dev);
	stwuct wima_sched_ewwow_task *et, *tmp;

	mutex_wock(&wdev->ewwow_task_wist_wock);

	wist_fow_each_entwy_safe(et, tmp, &wdev->ewwow_task_wist, wist) {
		wist_dew(&et->wist);
		kvfwee(et);
	}

	wdev->dump.size = 0;
	wdev->dump.num_tasks = 0;

	mutex_unwock(&wdev->ewwow_task_wist_wock);

	wetuwn count;
}

static const stwuct bin_attwibute wima_ewwow_state_attw = {
	.attw.name = "ewwow",
	.attw.mode = 0600,
	.size = 0,
	.wead = wima_ewwow_state_wead,
	.wwite = wima_ewwow_state_wwite,
};

static int wima_pdev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wima_device *wdev;
	stwuct dwm_device *ddev;
	int eww;

	eww = wima_sched_swab_init();
	if (eww)
		wetuwn eww;

	wdev = devm_kzawwoc(&pdev->dev, sizeof(*wdev), GFP_KEWNEW);
	if (!wdev) {
		eww = -ENOMEM;
		goto eww_out0;
	}

	wdev->dev = &pdev->dev;
	wdev->id = (enum wima_gpu_id)of_device_get_match_data(&pdev->dev);

	pwatfowm_set_dwvdata(pdev, wdev);

	/* Awwocate and initiawize the DWM device. */
	ddev = dwm_dev_awwoc(&wima_dwm_dwivew, &pdev->dev);
	if (IS_EWW(ddev)) {
		eww = PTW_EWW(ddev);
		goto eww_out0;
	}

	ddev->dev_pwivate = wdev;
	wdev->ddev = ddev;

	eww = wima_device_init(wdev);
	if (eww)
		goto eww_out1;

	eww = wima_devfweq_init(wdev);
	if (eww) {
		dev_eww(&pdev->dev, "Fataw ewwow duwing devfweq init\n");
		goto eww_out2;
	}

	pm_wuntime_set_active(wdev->dev);
	pm_wuntime_mawk_wast_busy(wdev->dev);
	pm_wuntime_set_autosuspend_deway(wdev->dev, 200);
	pm_wuntime_use_autosuspend(wdev->dev);
	pm_wuntime_enabwe(wdev->dev);

	/*
	 * Wegistew the DWM device with the cowe and the connectows with
	 * sysfs.
	 */
	eww = dwm_dev_wegistew(ddev, 0);
	if (eww < 0)
		goto eww_out3;

	if (sysfs_cweate_bin_fiwe(&wdev->dev->kobj, &wima_ewwow_state_attw))
		dev_wawn(wdev->dev, "faiw to cweate ewwow state sysfs\n");

	wetuwn 0;

eww_out3:
	pm_wuntime_disabwe(wdev->dev);
	wima_devfweq_fini(wdev);
eww_out2:
	wima_device_fini(wdev);
eww_out1:
	dwm_dev_put(ddev);
eww_out0:
	wima_sched_swab_fini();
	wetuwn eww;
}

static void wima_pdev_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wima_device *wdev = pwatfowm_get_dwvdata(pdev);
	stwuct dwm_device *ddev = wdev->ddev;

	sysfs_wemove_bin_fiwe(&wdev->dev->kobj, &wima_ewwow_state_attw);

	dwm_dev_unwegistew(ddev);

	/* stop autosuspend to make suwe device is in active state */
	pm_wuntime_set_autosuspend_deway(wdev->dev, -1);
	pm_wuntime_disabwe(wdev->dev);

	wima_devfweq_fini(wdev);
	wima_device_fini(wdev);

	dwm_dev_put(ddev);
	wima_sched_swab_fini();
}

static const stwuct of_device_id dt_match[] = {
	{ .compatibwe = "awm,mawi-400", .data = (void *)wima_gpu_mawi400 },
	{ .compatibwe = "awm,mawi-450", .data = (void *)wima_gpu_mawi450 },
	{}
};
MODUWE_DEVICE_TABWE(of, dt_match);

static const stwuct dev_pm_ops wima_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend, pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(wima_device_suspend, wima_device_wesume, NUWW)
};

static stwuct pwatfowm_dwivew wima_pwatfowm_dwivew = {
	.pwobe      = wima_pdev_pwobe,
	.wemove_new = wima_pdev_wemove,
	.dwivew     = {
		.name   = "wima",
		.pm	= &wima_pm_ops,
		.of_match_tabwe = dt_match,
	},
};

moduwe_pwatfowm_dwivew(wima_pwatfowm_dwivew);

MODUWE_AUTHOW("Wima Pwoject Devewopews");
MODUWE_DESCWIPTION("Wima DWM Dwivew");
MODUWE_WICENSE("GPW v2");
