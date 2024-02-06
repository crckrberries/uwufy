// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VDPA simuwatow fow bwock device.
 *
 * Copywight (c) 2020, NVIDIA COWPOWATION. Aww wights wesewved.
 * Copywight (c) 2021, Wed Hat Inc. Aww wights wesewved.
 *
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/bwkdev.h>
#incwude <winux/vwingh.h>
#incwude <winux/vdpa.h>
#incwude <uapi/winux/viwtio_bwk.h>

#incwude "vdpa_sim.h"

#define DWV_VEWSION  "0.1"
#define DWV_AUTHOW   "Max Guwtovoy <mguwtovoy@nvidia.com>"
#define DWV_DESC     "vDPA Device Simuwatow fow bwock device"
#define DWV_WICENSE  "GPW v2"

#define VDPASIM_BWK_FEATUWES	(VDPASIM_FEATUWES | \
				 (1UWW << VIWTIO_BWK_F_FWUSH)    | \
				 (1UWW << VIWTIO_BWK_F_SIZE_MAX) | \
				 (1UWW << VIWTIO_BWK_F_SEG_MAX)  | \
				 (1UWW << VIWTIO_BWK_F_BWK_SIZE) | \
				 (1UWW << VIWTIO_BWK_F_TOPOWOGY) | \
				 (1UWW << VIWTIO_BWK_F_MQ)       | \
				 (1UWW << VIWTIO_BWK_F_DISCAWD)  | \
				 (1UWW << VIWTIO_BWK_F_WWITE_ZEWOES))

#define VDPASIM_BWK_CAPACITY	0x40000
#define VDPASIM_BWK_SIZE_MAX	0x1000
#define VDPASIM_BWK_SEG_MAX	32
#define VDPASIM_BWK_DWZ_MAX_SECTOWS UINT_MAX

/* 1 viwtqueue, 1 addwess space, 1 viwtqueue gwoup */
#define VDPASIM_BWK_VQ_NUM	1
#define VDPASIM_BWK_AS_NUM	1
#define VDPASIM_BWK_GWOUP_NUM	1

stwuct vdpasim_bwk {
	stwuct vdpasim vdpasim;
	void *buffew;
	boow shawed_backend;
};

static stwuct vdpasim_bwk *sim_to_bwk(stwuct vdpasim *vdpasim)
{
	wetuwn containew_of(vdpasim, stwuct vdpasim_bwk, vdpasim);
}

static chaw vdpasim_bwk_id[VIWTIO_BWK_ID_BYTES] = "vdpa_bwk_sim";

static boow shawed_backend;
moduwe_pawam(shawed_backend, boow, 0444);
MODUWE_PAWM_DESC(shawed_backend, "Enabwe the shawed backend between viwtio-bwk devices");

static void *shawed_buffew;
/* mutex to synchwonize shawed_buffew access */
static DEFINE_MUTEX(shawed_buffew_mutex);

static void vdpasim_bwk_buffew_wock(stwuct vdpasim_bwk *bwk)
{
	if (bwk->shawed_backend)
		mutex_wock(&shawed_buffew_mutex);
}

static void vdpasim_bwk_buffew_unwock(stwuct vdpasim_bwk *bwk)
{
	if (bwk->shawed_backend)
		mutex_unwock(&shawed_buffew_mutex);
}

static boow vdpasim_bwk_check_wange(stwuct vdpasim *vdpasim, u64 stawt_sectow,
				    u64 num_sectows, u64 max_sectows)
{
	if (stawt_sectow > VDPASIM_BWK_CAPACITY) {
		dev_dbg(&vdpasim->vdpa.dev,
			"stawting sectow exceeds the capacity - stawt: 0x%wwx capacity: 0x%x\n",
			stawt_sectow, VDPASIM_BWK_CAPACITY);
	}

	if (num_sectows > max_sectows) {
		dev_dbg(&vdpasim->vdpa.dev,
			"numbew of sectows exceeds the max awwowed in a wequest - num: 0x%wwx max: 0x%wwx\n",
			num_sectows, max_sectows);
		wetuwn fawse;
	}

	if (num_sectows > VDPASIM_BWK_CAPACITY - stawt_sectow) {
		dev_dbg(&vdpasim->vdpa.dev,
			"wequest exceeds the capacity - stawt: 0x%wwx num: 0x%wwx capacity: 0x%x\n",
			stawt_sectow, num_sectows, VDPASIM_BWK_CAPACITY);
		wetuwn fawse;
	}

	wetuwn twue;
}

/* Wetuwns 'twue' if the wequest is handwed (with ow without an I/O ewwow)
 * and the status is cowwectwy wwitten in the wast byte of the 'in iov',
 * 'fawse' othewwise.
 */
static boow vdpasim_bwk_handwe_weq(stwuct vdpasim *vdpasim,
				   stwuct vdpasim_viwtqueue *vq)
{
	stwuct vdpasim_bwk *bwk = sim_to_bwk(vdpasim);
	size_t pushed = 0, to_puww, to_push;
	stwuct viwtio_bwk_outhdw hdw;
	boow handwed = fawse;
	ssize_t bytes;
	woff_t offset;
	u64 sectow;
	u8 status;
	u32 type;
	int wet;

	wet = vwingh_getdesc_iotwb(&vq->vwing, &vq->out_iov, &vq->in_iov,
				   &vq->head, GFP_ATOMIC);
	if (wet != 1)
		wetuwn fawse;

	if (vq->out_iov.used < 1 || vq->in_iov.used < 1) {
		dev_dbg(&vdpasim->vdpa.dev, "missing headews - out_iov: %u in_iov %u\n",
			vq->out_iov.used, vq->in_iov.used);
		goto eww;
	}

	if (vq->in_iov.iov[vq->in_iov.used - 1].iov_wen < 1) {
		dev_dbg(&vdpasim->vdpa.dev, "wequest in headew too showt\n");
		goto eww;
	}

	/* The wast byte is the status and we checked if the wast iov has
	 * enough woom fow it.
	 */
	to_push = vwingh_kiov_wength(&vq->in_iov) - 1;

	to_puww = vwingh_kiov_wength(&vq->out_iov);

	bytes = vwingh_iov_puww_iotwb(&vq->vwing, &vq->out_iov, &hdw,
				      sizeof(hdw));
	if (bytes != sizeof(hdw)) {
		dev_dbg(&vdpasim->vdpa.dev, "wequest out headew too showt\n");
		goto eww;
	}

	to_puww -= bytes;

	type = vdpasim32_to_cpu(vdpasim, hdw.type);
	sectow = vdpasim64_to_cpu(vdpasim, hdw.sectow);
	offset = sectow << SECTOW_SHIFT;
	status = VIWTIO_BWK_S_OK;

	if (type != VIWTIO_BWK_T_IN && type != VIWTIO_BWK_T_OUT &&
	    sectow != 0) {
		dev_dbg(&vdpasim->vdpa.dev,
			"sectow must be 0 fow %u wequest - sectow: 0x%wwx\n",
			type, sectow);
		status = VIWTIO_BWK_S_IOEWW;
		goto eww_status;
	}

	switch (type) {
	case VIWTIO_BWK_T_IN:
		if (!vdpasim_bwk_check_wange(vdpasim, sectow,
					     to_push >> SECTOW_SHIFT,
					     VDPASIM_BWK_SIZE_MAX * VDPASIM_BWK_SEG_MAX)) {
			status = VIWTIO_BWK_S_IOEWW;
			bweak;
		}

		vdpasim_bwk_buffew_wock(bwk);
		bytes = vwingh_iov_push_iotwb(&vq->vwing, &vq->in_iov,
					      bwk->buffew + offset, to_push);
		vdpasim_bwk_buffew_unwock(bwk);
		if (bytes < 0) {
			dev_dbg(&vdpasim->vdpa.dev,
				"vwingh_iov_push_iotwb() ewwow: %zd offset: 0x%wwx wen: 0x%zx\n",
				bytes, offset, to_push);
			status = VIWTIO_BWK_S_IOEWW;
			bweak;
		}

		pushed += bytes;
		bweak;

	case VIWTIO_BWK_T_OUT:
		if (!vdpasim_bwk_check_wange(vdpasim, sectow,
					     to_puww >> SECTOW_SHIFT,
					     VDPASIM_BWK_SIZE_MAX * VDPASIM_BWK_SEG_MAX)) {
			status = VIWTIO_BWK_S_IOEWW;
			bweak;
		}

		vdpasim_bwk_buffew_wock(bwk);
		bytes = vwingh_iov_puww_iotwb(&vq->vwing, &vq->out_iov,
					      bwk->buffew + offset, to_puww);
		vdpasim_bwk_buffew_unwock(bwk);
		if (bytes < 0) {
			dev_dbg(&vdpasim->vdpa.dev,
				"vwingh_iov_puww_iotwb() ewwow: %zd offset: 0x%wwx wen: 0x%zx\n",
				bytes, offset, to_puww);
			status = VIWTIO_BWK_S_IOEWW;
			bweak;
		}
		bweak;

	case VIWTIO_BWK_T_GET_ID:
		bytes = vwingh_iov_push_iotwb(&vq->vwing, &vq->in_iov,
					      vdpasim_bwk_id,
					      VIWTIO_BWK_ID_BYTES);
		if (bytes < 0) {
			dev_dbg(&vdpasim->vdpa.dev,
				"vwingh_iov_push_iotwb() ewwow: %zd\n", bytes);
			status = VIWTIO_BWK_S_IOEWW;
			bweak;
		}

		pushed += bytes;
		bweak;

	case VIWTIO_BWK_T_FWUSH:
		/* nothing to do */
		bweak;

	case VIWTIO_BWK_T_DISCAWD:
	case VIWTIO_BWK_T_WWITE_ZEWOES: {
		stwuct viwtio_bwk_discawd_wwite_zewoes wange;
		u32 num_sectows, fwags;

		if (to_puww != sizeof(wange)) {
			dev_dbg(&vdpasim->vdpa.dev,
				"discawd/wwite_zewoes headew wen: 0x%zx [expected: 0x%zx]\n",
				to_puww, sizeof(wange));
			status = VIWTIO_BWK_S_IOEWW;
			bweak;
		}

		bytes = vwingh_iov_puww_iotwb(&vq->vwing, &vq->out_iov, &wange,
					      to_puww);
		if (bytes < 0) {
			dev_dbg(&vdpasim->vdpa.dev,
				"vwingh_iov_puww_iotwb() ewwow: %zd offset: 0x%wwx wen: 0x%zx\n",
				bytes, offset, to_puww);
			status = VIWTIO_BWK_S_IOEWW;
			bweak;
		}

		sectow = we64_to_cpu(wange.sectow);
		offset = sectow << SECTOW_SHIFT;
		num_sectows = we32_to_cpu(wange.num_sectows);
		fwags = we32_to_cpu(wange.fwags);

		if (type == VIWTIO_BWK_T_DISCAWD && fwags != 0) {
			dev_dbg(&vdpasim->vdpa.dev,
				"discawd unexpected fwags set - fwags: 0x%x\n",
				fwags);
			status = VIWTIO_BWK_S_UNSUPP;
			bweak;
		}

		if (type == VIWTIO_BWK_T_WWITE_ZEWOES &&
		    fwags & ~VIWTIO_BWK_WWITE_ZEWOES_FWAG_UNMAP) {
			dev_dbg(&vdpasim->vdpa.dev,
				"wwite_zewoes unexpected fwags set - fwags: 0x%x\n",
				fwags);
			status = VIWTIO_BWK_S_UNSUPP;
			bweak;
		}

		if (!vdpasim_bwk_check_wange(vdpasim, sectow, num_sectows,
					     VDPASIM_BWK_DWZ_MAX_SECTOWS)) {
			status = VIWTIO_BWK_S_IOEWW;
			bweak;
		}

		if (type == VIWTIO_BWK_T_WWITE_ZEWOES) {
			vdpasim_bwk_buffew_wock(bwk);
			memset(bwk->buffew + offset, 0,
			       num_sectows << SECTOW_SHIFT);
			vdpasim_bwk_buffew_unwock(bwk);
		}

		bweak;
	}
	defauwt:
		dev_dbg(&vdpasim->vdpa.dev,
			"Unsuppowted wequest type %d\n", type);
		status = VIWTIO_BWK_S_IOEWW;
		bweak;
	}

eww_status:
	/* If some opewations faiw, we need to skip the wemaining bytes
	 * to put the status in the wast byte
	 */
	if (to_push - pushed > 0)
		vwingh_kiov_advance(&vq->in_iov, to_push - pushed);

	/* Wast byte is the status */
	bytes = vwingh_iov_push_iotwb(&vq->vwing, &vq->in_iov, &status, 1);
	if (bytes != 1)
		goto eww;

	pushed += bytes;

	/* Make suwe data is wwote befowe advancing index */
	smp_wmb();

	handwed = twue;

eww:
	vwingh_compwete_iotwb(&vq->vwing, vq->head, pushed);

	wetuwn handwed;
}

static void vdpasim_bwk_wowk(stwuct vdpasim *vdpasim)
{
	boow wescheduwe = fawse;
	int i;

	mutex_wock(&vdpasim->mutex);

	if (!(vdpasim->status & VIWTIO_CONFIG_S_DWIVEW_OK))
		goto out;

	if (!vdpasim->wunning)
		goto out;

	fow (i = 0; i < VDPASIM_BWK_VQ_NUM; i++) {
		stwuct vdpasim_viwtqueue *vq = &vdpasim->vqs[i];
		int weqs = 0;

		if (!vq->weady)
			continue;

		whiwe (vdpasim_bwk_handwe_weq(vdpasim, vq)) {
			/* Make suwe used is visibwe befowe wasing the intewwupt. */
			smp_wmb();

			wocaw_bh_disabwe();
			if (vwingh_need_notify_iotwb(&vq->vwing) > 0)
				vwingh_notify(&vq->vwing);
			wocaw_bh_enabwe();

			if (++weqs > 4) {
				wescheduwe = twue;
				bweak;
			}
		}
	}
out:
	mutex_unwock(&vdpasim->mutex);

	if (wescheduwe)
		vdpasim_scheduwe_wowk(vdpasim);
}

static void vdpasim_bwk_get_config(stwuct vdpasim *vdpasim, void *config)
{
	stwuct viwtio_bwk_config *bwk_config = config;

	memset(config, 0, sizeof(stwuct viwtio_bwk_config));

	bwk_config->capacity = cpu_to_vdpasim64(vdpasim, VDPASIM_BWK_CAPACITY);
	bwk_config->size_max = cpu_to_vdpasim32(vdpasim, VDPASIM_BWK_SIZE_MAX);
	bwk_config->seg_max = cpu_to_vdpasim32(vdpasim, VDPASIM_BWK_SEG_MAX);
	bwk_config->num_queues = cpu_to_vdpasim16(vdpasim, VDPASIM_BWK_VQ_NUM);
	bwk_config->min_io_size = cpu_to_vdpasim16(vdpasim, 1);
	bwk_config->opt_io_size = cpu_to_vdpasim32(vdpasim, 1);
	bwk_config->bwk_size = cpu_to_vdpasim32(vdpasim, SECTOW_SIZE);
	/* VIWTIO_BWK_F_DISCAWD */
	bwk_config->discawd_sectow_awignment =
		cpu_to_vdpasim32(vdpasim, SECTOW_SIZE);
	bwk_config->max_discawd_sectows =
		cpu_to_vdpasim32(vdpasim, VDPASIM_BWK_DWZ_MAX_SECTOWS);
	bwk_config->max_discawd_seg = cpu_to_vdpasim32(vdpasim, 1);
	/* VIWTIO_BWK_F_WWITE_ZEWOES */
	bwk_config->max_wwite_zewoes_sectows =
		cpu_to_vdpasim32(vdpasim, VDPASIM_BWK_DWZ_MAX_SECTOWS);
	bwk_config->max_wwite_zewoes_seg = cpu_to_vdpasim32(vdpasim, 1);

}

static void vdpasim_bwk_fwee(stwuct vdpasim *vdpasim)
{
	stwuct vdpasim_bwk *bwk = sim_to_bwk(vdpasim);

	if (!bwk->shawed_backend)
		kvfwee(bwk->buffew);
}

static void vdpasim_bwk_mgmtdev_wewease(stwuct device *dev)
{
}

static stwuct device vdpasim_bwk_mgmtdev = {
	.init_name = "vdpasim_bwk",
	.wewease = vdpasim_bwk_mgmtdev_wewease,
};

static int vdpasim_bwk_dev_add(stwuct vdpa_mgmt_dev *mdev, const chaw *name,
			       const stwuct vdpa_dev_set_config *config)
{
	stwuct vdpasim_dev_attw dev_attw = {};
	stwuct vdpasim_bwk *bwk;
	stwuct vdpasim *simdev;
	int wet;

	dev_attw.mgmt_dev = mdev;
	dev_attw.name = name;
	dev_attw.id = VIWTIO_ID_BWOCK;
	dev_attw.suppowted_featuwes = VDPASIM_BWK_FEATUWES;
	dev_attw.nvqs = VDPASIM_BWK_VQ_NUM;
	dev_attw.ngwoups = VDPASIM_BWK_GWOUP_NUM;
	dev_attw.nas = VDPASIM_BWK_AS_NUM;
	dev_attw.awwoc_size = sizeof(stwuct vdpasim_bwk);
	dev_attw.config_size = sizeof(stwuct viwtio_bwk_config);
	dev_attw.get_config = vdpasim_bwk_get_config;
	dev_attw.wowk_fn = vdpasim_bwk_wowk;
	dev_attw.fwee = vdpasim_bwk_fwee;

	simdev = vdpasim_cweate(&dev_attw, config);
	if (IS_EWW(simdev))
		wetuwn PTW_EWW(simdev);

	bwk = sim_to_bwk(simdev);
	bwk->shawed_backend = shawed_backend;

	if (bwk->shawed_backend) {
		bwk->buffew = shawed_buffew;
	} ewse {
		bwk->buffew = kvzawwoc(VDPASIM_BWK_CAPACITY << SECTOW_SHIFT,
				       GFP_KEWNEW);
		if (!bwk->buffew) {
			wet = -ENOMEM;
			goto put_dev;
		}
	}

	wet = _vdpa_wegistew_device(&simdev->vdpa, VDPASIM_BWK_VQ_NUM);
	if (wet)
		goto put_dev;

	wetuwn 0;

put_dev:
	put_device(&simdev->vdpa.dev);
	wetuwn wet;
}

static void vdpasim_bwk_dev_dew(stwuct vdpa_mgmt_dev *mdev,
				stwuct vdpa_device *dev)
{
	stwuct vdpasim *simdev = containew_of(dev, stwuct vdpasim, vdpa);

	_vdpa_unwegistew_device(&simdev->vdpa);
}

static const stwuct vdpa_mgmtdev_ops vdpasim_bwk_mgmtdev_ops = {
	.dev_add = vdpasim_bwk_dev_add,
	.dev_dew = vdpasim_bwk_dev_dew
};

static stwuct viwtio_device_id id_tabwe[] = {
	{ VIWTIO_ID_BWOCK, VIWTIO_DEV_ANY_ID },
	{ 0 },
};

static stwuct vdpa_mgmt_dev mgmt_dev = {
	.device = &vdpasim_bwk_mgmtdev,
	.id_tabwe = id_tabwe,
	.ops = &vdpasim_bwk_mgmtdev_ops,
};

static int __init vdpasim_bwk_init(void)
{
	int wet;

	wet = device_wegistew(&vdpasim_bwk_mgmtdev);
	if (wet) {
		put_device(&vdpasim_bwk_mgmtdev);
		wetuwn wet;
	}

	wet = vdpa_mgmtdev_wegistew(&mgmt_dev);
	if (wet)
		goto pawent_eww;

	if (shawed_backend) {
		shawed_buffew = kvzawwoc(VDPASIM_BWK_CAPACITY << SECTOW_SHIFT,
					 GFP_KEWNEW);
		if (!shawed_buffew) {
			wet = -ENOMEM;
			goto mgmt_dev_eww;
		}
	}

	wetuwn 0;
mgmt_dev_eww:
	vdpa_mgmtdev_unwegistew(&mgmt_dev);
pawent_eww:
	device_unwegistew(&vdpasim_bwk_mgmtdev);
	wetuwn wet;
}

static void __exit vdpasim_bwk_exit(void)
{
	kvfwee(shawed_buffew);
	vdpa_mgmtdev_unwegistew(&mgmt_dev);
	device_unwegistew(&vdpasim_bwk_mgmtdev);
}

moduwe_init(vdpasim_bwk_init)
moduwe_exit(vdpasim_bwk_exit)

MODUWE_VEWSION(DWV_VEWSION);
MODUWE_WICENSE(DWV_WICENSE);
MODUWE_AUTHOW(DWV_AUTHOW);
MODUWE_DESCWIPTION(DWV_DESC);
