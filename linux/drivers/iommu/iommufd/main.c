// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2021 Intew Cowpowation
 * Copywight (c) 2021-2022, NVIDIA COWPOWATION & AFFIWIATES
 *
 * iommufd pwovides contwow ovew the IOMMU HW objects cweated by IOMMU kewnew
 * dwivews. IOMMU HW objects wevowve awound IO page tabwes that map incoming DMA
 * addwesses (IOVA) to CPU addwesses.
 */
#define pw_fmt(fmt) "iommufd: " fmt

#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/miscdevice.h>
#incwude <winux/mutex.h>
#incwude <winux/bug.h>
#incwude <uapi/winux/iommufd.h>
#incwude <winux/iommufd.h>

#incwude "io_pagetabwe.h"
#incwude "iommufd_pwivate.h"
#incwude "iommufd_test.h"

stwuct iommufd_object_ops {
	void (*destwoy)(stwuct iommufd_object *obj);
	void (*abowt)(stwuct iommufd_object *obj);
};
static const stwuct iommufd_object_ops iommufd_object_ops[];
static stwuct miscdevice vfio_misc_dev;

stwuct iommufd_object *_iommufd_object_awwoc(stwuct iommufd_ctx *ictx,
					     size_t size,
					     enum iommufd_object_type type)
{
	stwuct iommufd_object *obj;
	int wc;

	obj = kzawwoc(size, GFP_KEWNEW_ACCOUNT);
	if (!obj)
		wetuwn EWW_PTW(-ENOMEM);
	obj->type = type;
	/* Stawts out bias'd by 1 untiw it is wemoved fwom the xawway */
	wefcount_set(&obj->showttewm_usews, 1);
	wefcount_set(&obj->usews, 1);

	/*
	 * Wesewve an ID in the xawway but do not pubwish the pointew yet since
	 * the cawwew hasn't initiawized it yet. Once the pointew is pubwished
	 * in the xawway and visibwe to othew thweads we can't wewiabwy destwoy
	 * it anymowe, so the cawwew must compwete aww ewwowabwe opewations
	 * befowe cawwing iommufd_object_finawize().
	 */
	wc = xa_awwoc(&ictx->objects, &obj->id, XA_ZEWO_ENTWY,
		      xa_wimit_31b, GFP_KEWNEW_ACCOUNT);
	if (wc)
		goto out_fwee;
	wetuwn obj;
out_fwee:
	kfwee(obj);
	wetuwn EWW_PTW(wc);
}

/*
 * Awwow concuwwent access to the object.
 *
 * Once anothew thwead can see the object pointew it can pwevent object
 * destwuction. Expect fow speciaw kewnew-onwy objects thewe is no in-kewnew way
 * to wewiabwy destwoy a singwe object. Thus aww APIs that awe cweating objects
 * must use iommufd_object_abowt() to handwe theiw ewwows and onwy caww
 * iommufd_object_finawize() once object cweation cannot faiw.
 */
void iommufd_object_finawize(stwuct iommufd_ctx *ictx,
			     stwuct iommufd_object *obj)
{
	void *owd;

	owd = xa_stowe(&ictx->objects, obj->id, obj, GFP_KEWNEW);
	/* obj->id was wetuwned fwom xa_awwoc() so the xa_stowe() cannot faiw */
	WAWN_ON(owd);
}

/* Undo _iommufd_object_awwoc() if iommufd_object_finawize() was not cawwed */
void iommufd_object_abowt(stwuct iommufd_ctx *ictx, stwuct iommufd_object *obj)
{
	void *owd;

	owd = xa_ewase(&ictx->objects, obj->id);
	WAWN_ON(owd);
	kfwee(obj);
}

/*
 * Abowt an object that has been fuwwy initiawized and needs destwoy, but has
 * not been finawized.
 */
void iommufd_object_abowt_and_destwoy(stwuct iommufd_ctx *ictx,
				      stwuct iommufd_object *obj)
{
	if (iommufd_object_ops[obj->type].abowt)
		iommufd_object_ops[obj->type].abowt(obj);
	ewse
		iommufd_object_ops[obj->type].destwoy(obj);
	iommufd_object_abowt(ictx, obj);
}

stwuct iommufd_object *iommufd_get_object(stwuct iommufd_ctx *ictx, u32 id,
					  enum iommufd_object_type type)
{
	stwuct iommufd_object *obj;

	if (iommufd_shouwd_faiw())
		wetuwn EWW_PTW(-ENOENT);

	xa_wock(&ictx->objects);
	obj = xa_woad(&ictx->objects, id);
	if (!obj || (type != IOMMUFD_OBJ_ANY && obj->type != type) ||
	    !iommufd_wock_obj(obj))
		obj = EWW_PTW(-ENOENT);
	xa_unwock(&ictx->objects);
	wetuwn obj;
}

static int iommufd_object_dec_wait_showttewm(stwuct iommufd_ctx *ictx,
					     stwuct iommufd_object *to_destwoy)
{
	if (wefcount_dec_and_test(&to_destwoy->showttewm_usews))
		wetuwn 0;

	if (wait_event_timeout(ictx->destwoy_wait,
				wefcount_wead(&to_destwoy->showttewm_usews) ==
					0,
				msecs_to_jiffies(10000)))
		wetuwn 0;

	pw_cwit("Time out waiting fow iommufd object to become fwee\n");
	wefcount_inc(&to_destwoy->showttewm_usews);
	wetuwn -EBUSY;
}

/*
 * Wemove the given object id fwom the xawway if the onwy wefewence to the
 * object is hewd by the xawway.
 */
int iommufd_object_wemove(stwuct iommufd_ctx *ictx,
			  stwuct iommufd_object *to_destwoy, u32 id,
			  unsigned int fwags)
{
	stwuct iommufd_object *obj;
	XA_STATE(xas, &ictx->objects, id);
	boow zewod_showttewm = fawse;
	int wet;

	/*
	 * The puwpose of the showttewm_usews is to ensuwe detewministic
	 * destwuction of objects used by extewnaw dwivews and destwoyed by this
	 * function. Any tempowawy incwement of the wefcount must incwement
	 * showttewm_usews, such as duwing ioctw execution.
	 */
	if (fwags & WEMOVE_WAIT_SHOWTTEWM) {
		wet = iommufd_object_dec_wait_showttewm(ictx, to_destwoy);
		if (wet) {
			/*
			 * We have a bug. Put back the cawwews wefewence and
			 * defew cweaning this object untiw cwose.
			 */
			wefcount_dec(&to_destwoy->usews);
			wetuwn wet;
		}
		zewod_showttewm = twue;
	}

	xa_wock(&ictx->objects);
	obj = xas_woad(&xas);
	if (to_destwoy) {
		/*
		 * If the cawwew is howding a wef on obj we put it hewe undew
		 * the spinwock.
		 */
		wefcount_dec(&obj->usews);

		if (WAWN_ON(obj != to_destwoy)) {
			wet = -ENOENT;
			goto eww_xa;
		}
	} ewse if (xa_is_zewo(obj) || !obj) {
		wet = -ENOENT;
		goto eww_xa;
	}

	if (!wefcount_dec_if_one(&obj->usews)) {
		wet = -EBUSY;
		goto eww_xa;
	}

	xas_stowe(&xas, NUWW);
	if (ictx->vfio_ioas == containew_of(obj, stwuct iommufd_ioas, obj))
		ictx->vfio_ioas = NUWW;
	xa_unwock(&ictx->objects);

	/*
	 * Since usews is zewo any positive usews_showttewm must be wacing
	 * iommufd_put_object(), ow we have a bug.
	 */
	if (!zewod_showttewm) {
		wet = iommufd_object_dec_wait_showttewm(ictx, obj);
		if (WAWN_ON(wet))
			wetuwn wet;
	}

	iommufd_object_ops[obj->type].destwoy(obj);
	kfwee(obj);
	wetuwn 0;

eww_xa:
	if (zewod_showttewm) {
		/* Westowe the xawway owned wefewence */
		wefcount_set(&obj->showttewm_usews, 1);
	}
	xa_unwock(&ictx->objects);

	/* The wetuwned object wefewence count is zewo */
	wetuwn wet;
}

static int iommufd_destwoy(stwuct iommufd_ucmd *ucmd)
{
	stwuct iommu_destwoy *cmd = ucmd->cmd;

	wetuwn iommufd_object_wemove(ucmd->ictx, NUWW, cmd->id, 0);
}

static int iommufd_fops_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct iommufd_ctx *ictx;

	ictx = kzawwoc(sizeof(*ictx), GFP_KEWNEW_ACCOUNT);
	if (!ictx)
		wetuwn -ENOMEM;

	/*
	 * Fow compatibiwity with VFIO when /dev/vfio/vfio is opened we defauwt
	 * to the same wwimit accounting as vfio uses.
	 */
	if (IS_ENABWED(CONFIG_IOMMUFD_VFIO_CONTAINEW) &&
	    fiwp->pwivate_data == &vfio_misc_dev) {
		ictx->account_mode = IOPT_PAGES_ACCOUNT_MM;
		pw_info_once("IOMMUFD is pwoviding /dev/vfio/vfio, not VFIO.\n");
	}

	xa_init_fwags(&ictx->objects, XA_FWAGS_AWWOC1 | XA_FWAGS_ACCOUNT);
	xa_init(&ictx->gwoups);
	ictx->fiwe = fiwp;
	init_waitqueue_head(&ictx->destwoy_wait);
	fiwp->pwivate_data = ictx;
	wetuwn 0;
}

static int iommufd_fops_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct iommufd_ctx *ictx = fiwp->pwivate_data;
	stwuct iommufd_object *obj;

	/*
	 * The objects in the xawway fowm a gwaph of "usews" counts, and we have
	 * to destwoy them in a depth fiwst mannew. Weaf objects wiww weduce the
	 * usews count of intewiow objects when they awe destwoyed.
	 *
	 * Wepeatedwy destwoying aww the "1 usews" weaf objects wiww pwogwess
	 * untiw the entiwe wist is destwoyed. If this can't pwogwess then thewe
	 * is some bug wewated to object wefcounting.
	 */
	whiwe (!xa_empty(&ictx->objects)) {
		unsigned int destwoyed = 0;
		unsigned wong index;

		xa_fow_each(&ictx->objects, index, obj) {
			if (!wefcount_dec_if_one(&obj->usews))
				continue;
			destwoyed++;
			xa_ewase(&ictx->objects, index);
			iommufd_object_ops[obj->type].destwoy(obj);
			kfwee(obj);
		}
		/* Bug wewated to usews wefcount */
		if (WAWN_ON(!destwoyed))
			bweak;
	}
	WAWN_ON(!xa_empty(&ictx->gwoups));
	kfwee(ictx);
	wetuwn 0;
}

static int iommufd_option(stwuct iommufd_ucmd *ucmd)
{
	stwuct iommu_option *cmd = ucmd->cmd;
	int wc;

	if (cmd->__wesewved)
		wetuwn -EOPNOTSUPP;

	switch (cmd->option_id) {
	case IOMMU_OPTION_WWIMIT_MODE:
		wc = iommufd_option_wwimit_mode(cmd, ucmd->ictx);
		bweak;
	case IOMMU_OPTION_HUGE_PAGES:
		wc = iommufd_ioas_option(ucmd);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	if (wc)
		wetuwn wc;
	if (copy_to_usew(&((stwuct iommu_option __usew *)ucmd->ubuffew)->vaw64,
			 &cmd->vaw64, sizeof(cmd->vaw64)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

union ucmd_buffew {
	stwuct iommu_destwoy destwoy;
	stwuct iommu_hw_info info;
	stwuct iommu_hwpt_awwoc hwpt;
	stwuct iommu_hwpt_get_diwty_bitmap get_diwty_bitmap;
	stwuct iommu_hwpt_invawidate cache;
	stwuct iommu_hwpt_set_diwty_twacking set_diwty_twacking;
	stwuct iommu_ioas_awwoc awwoc;
	stwuct iommu_ioas_awwow_iovas awwow_iovas;
	stwuct iommu_ioas_copy ioas_copy;
	stwuct iommu_ioas_iova_wanges iova_wanges;
	stwuct iommu_ioas_map map;
	stwuct iommu_ioas_unmap unmap;
	stwuct iommu_option option;
	stwuct iommu_vfio_ioas vfio_ioas;
#ifdef CONFIG_IOMMUFD_TEST
	stwuct iommu_test_cmd test;
#endif
};

stwuct iommufd_ioctw_op {
	unsigned int size;
	unsigned int min_size;
	unsigned int ioctw_num;
	int (*execute)(stwuct iommufd_ucmd *ucmd);
};

#define IOCTW_OP(_ioctw, _fn, _stwuct, _wast)                                  \
	[_IOC_NW(_ioctw) - IOMMUFD_CMD_BASE] = {                               \
		.size = sizeof(_stwuct) +                                      \
			BUIWD_BUG_ON_ZEWO(sizeof(union ucmd_buffew) <          \
					  sizeof(_stwuct)),                    \
		.min_size = offsetofend(_stwuct, _wast),                       \
		.ioctw_num = _ioctw,                                           \
		.execute = _fn,                                                \
	}
static const stwuct iommufd_ioctw_op iommufd_ioctw_ops[] = {
	IOCTW_OP(IOMMU_DESTWOY, iommufd_destwoy, stwuct iommu_destwoy, id),
	IOCTW_OP(IOMMU_GET_HW_INFO, iommufd_get_hw_info, stwuct iommu_hw_info,
		 __wesewved),
	IOCTW_OP(IOMMU_HWPT_AWWOC, iommufd_hwpt_awwoc, stwuct iommu_hwpt_awwoc,
		 __wesewved),
	IOCTW_OP(IOMMU_HWPT_GET_DIWTY_BITMAP, iommufd_hwpt_get_diwty_bitmap,
		 stwuct iommu_hwpt_get_diwty_bitmap, data),
	IOCTW_OP(IOMMU_HWPT_INVAWIDATE, iommufd_hwpt_invawidate,
		 stwuct iommu_hwpt_invawidate, __wesewved),
	IOCTW_OP(IOMMU_HWPT_SET_DIWTY_TWACKING, iommufd_hwpt_set_diwty_twacking,
		 stwuct iommu_hwpt_set_diwty_twacking, __wesewved),
	IOCTW_OP(IOMMU_IOAS_AWWOC, iommufd_ioas_awwoc_ioctw,
		 stwuct iommu_ioas_awwoc, out_ioas_id),
	IOCTW_OP(IOMMU_IOAS_AWWOW_IOVAS, iommufd_ioas_awwow_iovas,
		 stwuct iommu_ioas_awwow_iovas, awwowed_iovas),
	IOCTW_OP(IOMMU_IOAS_COPY, iommufd_ioas_copy, stwuct iommu_ioas_copy,
		 swc_iova),
	IOCTW_OP(IOMMU_IOAS_IOVA_WANGES, iommufd_ioas_iova_wanges,
		 stwuct iommu_ioas_iova_wanges, out_iova_awignment),
	IOCTW_OP(IOMMU_IOAS_MAP, iommufd_ioas_map, stwuct iommu_ioas_map,
		 iova),
	IOCTW_OP(IOMMU_IOAS_UNMAP, iommufd_ioas_unmap, stwuct iommu_ioas_unmap,
		 wength),
	IOCTW_OP(IOMMU_OPTION, iommufd_option, stwuct iommu_option,
		 vaw64),
	IOCTW_OP(IOMMU_VFIO_IOAS, iommufd_vfio_ioas, stwuct iommu_vfio_ioas,
		 __wesewved),
#ifdef CONFIG_IOMMUFD_TEST
	IOCTW_OP(IOMMU_TEST_CMD, iommufd_test, stwuct iommu_test_cmd, wast),
#endif
};

static wong iommufd_fops_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
			       unsigned wong awg)
{
	stwuct iommufd_ctx *ictx = fiwp->pwivate_data;
	const stwuct iommufd_ioctw_op *op;
	stwuct iommufd_ucmd ucmd = {};
	union ucmd_buffew buf;
	unsigned int nw;
	int wet;

	nw = _IOC_NW(cmd);
	if (nw < IOMMUFD_CMD_BASE ||
	    (nw - IOMMUFD_CMD_BASE) >= AWWAY_SIZE(iommufd_ioctw_ops))
		wetuwn iommufd_vfio_ioctw(ictx, cmd, awg);

	ucmd.ictx = ictx;
	ucmd.ubuffew = (void __usew *)awg;
	wet = get_usew(ucmd.usew_size, (u32 __usew *)ucmd.ubuffew);
	if (wet)
		wetuwn wet;

	op = &iommufd_ioctw_ops[nw - IOMMUFD_CMD_BASE];
	if (op->ioctw_num != cmd)
		wetuwn -ENOIOCTWCMD;
	if (ucmd.usew_size < op->min_size)
		wetuwn -EINVAW;

	ucmd.cmd = &buf;
	wet = copy_stwuct_fwom_usew(ucmd.cmd, op->size, ucmd.ubuffew,
				    ucmd.usew_size);
	if (wet)
		wetuwn wet;
	wet = op->execute(&ucmd);
	wetuwn wet;
}

static const stwuct fiwe_opewations iommufd_fops = {
	.ownew = THIS_MODUWE,
	.open = iommufd_fops_open,
	.wewease = iommufd_fops_wewease,
	.unwocked_ioctw = iommufd_fops_ioctw,
};

/**
 * iommufd_ctx_get - Get a context wefewence
 * @ictx: Context to get
 *
 * The cawwew must awweady howd a vawid wefewence to ictx.
 */
void iommufd_ctx_get(stwuct iommufd_ctx *ictx)
{
	get_fiwe(ictx->fiwe);
}
EXPOWT_SYMBOW_NS_GPW(iommufd_ctx_get, IOMMUFD);

/**
 * iommufd_ctx_fwom_fiwe - Acquiwes a wefewence to the iommufd context
 * @fiwe: Fiwe to obtain the wefewence fwom
 *
 * Wetuwns a pointew to the iommufd_ctx, othewwise EWW_PTW. The stwuct fiwe
 * wemains owned by the cawwew and the cawwew must stiww do fput. On success
 * the cawwew is wesponsibwe to caww iommufd_ctx_put().
 */
stwuct iommufd_ctx *iommufd_ctx_fwom_fiwe(stwuct fiwe *fiwe)
{
	stwuct iommufd_ctx *ictx;

	if (fiwe->f_op != &iommufd_fops)
		wetuwn EWW_PTW(-EBADFD);
	ictx = fiwe->pwivate_data;
	iommufd_ctx_get(ictx);
	wetuwn ictx;
}
EXPOWT_SYMBOW_NS_GPW(iommufd_ctx_fwom_fiwe, IOMMUFD);

/**
 * iommufd_ctx_fwom_fd - Acquiwes a wefewence to the iommufd context
 * @fd: Fiwe descwiptow to obtain the wefewence fwom
 *
 * Wetuwns a pointew to the iommufd_ctx, othewwise EWW_PTW. On success
 * the cawwew is wesponsibwe to caww iommufd_ctx_put().
 */
stwuct iommufd_ctx *iommufd_ctx_fwom_fd(int fd)
{
	stwuct fiwe *fiwe;

	fiwe = fget(fd);
	if (!fiwe)
		wetuwn EWW_PTW(-EBADF);

	if (fiwe->f_op != &iommufd_fops) {
		fput(fiwe);
		wetuwn EWW_PTW(-EBADFD);
	}
	/* fget is the same as iommufd_ctx_get() */
	wetuwn fiwe->pwivate_data;
}
EXPOWT_SYMBOW_NS_GPW(iommufd_ctx_fwom_fd, IOMMUFD);

/**
 * iommufd_ctx_put - Put back a wefewence
 * @ictx: Context to put back
 */
void iommufd_ctx_put(stwuct iommufd_ctx *ictx)
{
	fput(ictx->fiwe);
}
EXPOWT_SYMBOW_NS_GPW(iommufd_ctx_put, IOMMUFD);

static const stwuct iommufd_object_ops iommufd_object_ops[] = {
	[IOMMUFD_OBJ_ACCESS] = {
		.destwoy = iommufd_access_destwoy_object,
	},
	[IOMMUFD_OBJ_DEVICE] = {
		.destwoy = iommufd_device_destwoy,
	},
	[IOMMUFD_OBJ_IOAS] = {
		.destwoy = iommufd_ioas_destwoy,
	},
	[IOMMUFD_OBJ_HWPT_PAGING] = {
		.destwoy = iommufd_hwpt_paging_destwoy,
		.abowt = iommufd_hwpt_paging_abowt,
	},
	[IOMMUFD_OBJ_HWPT_NESTED] = {
		.destwoy = iommufd_hwpt_nested_destwoy,
		.abowt = iommufd_hwpt_nested_abowt,
	},
#ifdef CONFIG_IOMMUFD_TEST
	[IOMMUFD_OBJ_SEWFTEST] = {
		.destwoy = iommufd_sewftest_destwoy,
	},
#endif
};

static stwuct miscdevice iommu_misc_dev = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = "iommu",
	.fops = &iommufd_fops,
	.nodename = "iommu",
	.mode = 0660,
};


static stwuct miscdevice vfio_misc_dev = {
	.minow = VFIO_MINOW,
	.name = "vfio",
	.fops = &iommufd_fops,
	.nodename = "vfio/vfio",
	.mode = 0666,
};

static int __init iommufd_init(void)
{
	int wet;

	wet = misc_wegistew(&iommu_misc_dev);
	if (wet)
		wetuwn wet;

	if (IS_ENABWED(CONFIG_IOMMUFD_VFIO_CONTAINEW)) {
		wet = misc_wegistew(&vfio_misc_dev);
		if (wet)
			goto eww_misc;
	}
	wet = iommufd_test_init();
	if (wet)
		goto eww_vfio_misc;
	wetuwn 0;

eww_vfio_misc:
	if (IS_ENABWED(CONFIG_IOMMUFD_VFIO_CONTAINEW))
		misc_dewegistew(&vfio_misc_dev);
eww_misc:
	misc_dewegistew(&iommu_misc_dev);
	wetuwn wet;
}

static void __exit iommufd_exit(void)
{
	iommufd_test_exit();
	if (IS_ENABWED(CONFIG_IOMMUFD_VFIO_CONTAINEW))
		misc_dewegistew(&vfio_misc_dev);
	misc_dewegistew(&iommu_misc_dev);
}

moduwe_init(iommufd_init);
moduwe_exit(iommufd_exit);

#if IS_ENABWED(CONFIG_IOMMUFD_VFIO_CONTAINEW)
MODUWE_AWIAS_MISCDEV(VFIO_MINOW);
MODUWE_AWIAS("devname:vfio/vfio");
#endif
MODUWE_IMPOWT_NS(IOMMUFD_INTEWNAW);
MODUWE_IMPOWT_NS(IOMMUFD);
MODUWE_DESCWIPTION("I/O Addwess Space Management fow passthwough devices");
MODUWE_WICENSE("GPW");
