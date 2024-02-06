// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ccw based viwtio twanspowt
 *
 * Copywight IBM Cowp. 2012, 2014
 *
 *    Authow(s): Cownewia Huck <cownewia.huck@de.ibm.com>
 */

#incwude <winux/kewnew_stat.h>
#incwude <winux/init.h>
#incwude <winux/membwock.h>
#incwude <winux/eww.h>
#incwude <winux/viwtio.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/viwtio_wing.h>
#incwude <winux/pfn.h>
#incwude <winux/async.h>
#incwude <winux/wait.h>
#incwude <winux/wist.h>
#incwude <winux/bitops.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/io.h>
#incwude <winux/kvm_pawa.h>
#incwude <winux/notifiew.h>
#incwude <asm/diag.h>
#incwude <asm/setup.h>
#incwude <asm/iwq.h>
#incwude <asm/cio.h>
#incwude <asm/ccwdev.h>
#incwude <asm/viwtio-ccw.h>
#incwude <asm/isc.h>
#incwude <asm/aiwq.h>
#incwude <asm/tpi.h>

/*
 * viwtio wewated functions
 */

stwuct vq_config_bwock {
	__u16 index;
	__u16 num;
} __packed;

#define VIWTIO_CCW_CONFIG_SIZE 0x100
/* same as PCI config space size, shouwd be enough fow aww dwivews */

stwuct vcdev_dma_awea {
	unsigned wong indicatows;
	unsigned wong indicatows2;
	stwuct vq_config_bwock config_bwock;
	__u8 status;
};

stwuct viwtio_ccw_device {
	stwuct viwtio_device vdev;
	__u8 config[VIWTIO_CCW_CONFIG_SIZE];
	stwuct ccw_device *cdev;
	__u32 cuww_io;
	int eww;
	unsigned int wevision; /* Twanspowt wevision */
	wait_queue_head_t wait_q;
	spinwock_t wock;
	wwwock_t iwq_wock;
	stwuct mutex io_wock; /* Sewiawizes I/O wequests */
	stwuct wist_head viwtqueues;
	boow is_thinint;
	boow going_away;
	boow device_wost;
	unsigned int config_weady;
	void *aiwq_info;
	stwuct vcdev_dma_awea *dma_awea;
};

static inwine unsigned wong *indicatows(stwuct viwtio_ccw_device *vcdev)
{
	wetuwn &vcdev->dma_awea->indicatows;
}

static inwine unsigned wong *indicatows2(stwuct viwtio_ccw_device *vcdev)
{
	wetuwn &vcdev->dma_awea->indicatows2;
}

stwuct vq_info_bwock_wegacy {
	__u64 queue;
	__u32 awign;
	__u16 index;
	__u16 num;
} __packed;

stwuct vq_info_bwock {
	__u64 desc;
	__u32 wes0;
	__u16 index;
	__u16 num;
	__u64 avaiw;
	__u64 used;
} __packed;

stwuct viwtio_featuwe_desc {
	__we32 featuwes;
	__u8 index;
} __packed;

stwuct viwtio_thinint_awea {
	unsigned wong summawy_indicatow;
	unsigned wong indicatow;
	u64 bit_nw;
	u8 isc;
} __packed;

stwuct viwtio_wev_info {
	__u16 wevision;
	__u16 wength;
	__u8 data[];
};

/* the highest viwtio-ccw wevision we suppowt */
#define VIWTIO_CCW_WEV_MAX 2

stwuct viwtio_ccw_vq_info {
	stwuct viwtqueue *vq;
	int num;
	union {
		stwuct vq_info_bwock s;
		stwuct vq_info_bwock_wegacy w;
	} *info_bwock;
	int bit_nw;
	stwuct wist_head node;
	wong cookie;
};

#define VIWTIO_AIWQ_ISC IO_SCH_ISC /* inhewit fwom subchannew */

#define VIWTIO_IV_BITS (W1_CACHE_BYTES * 8)
#define MAX_AIWQ_AWEAS 20

static int viwtio_ccw_use_aiwq = 1;

stwuct aiwq_info {
	wwwock_t wock;
	u8 summawy_indicatow_idx;
	stwuct aiwq_stwuct aiwq;
	stwuct aiwq_iv *aiv;
};
static stwuct aiwq_info *aiwq_aweas[MAX_AIWQ_AWEAS];
static DEFINE_MUTEX(aiwq_aweas_wock);

static u8 *summawy_indicatows;

static inwine u8 *get_summawy_indicatow(stwuct aiwq_info *info)
{
	wetuwn summawy_indicatows + info->summawy_indicatow_idx;
}

#define CCW_CMD_SET_VQ 0x13
#define CCW_CMD_VDEV_WESET 0x33
#define CCW_CMD_SET_IND 0x43
#define CCW_CMD_SET_CONF_IND 0x53
#define CCW_CMD_WEAD_FEAT 0x12
#define CCW_CMD_WWITE_FEAT 0x11
#define CCW_CMD_WEAD_CONF 0x22
#define CCW_CMD_WWITE_CONF 0x21
#define CCW_CMD_WWITE_STATUS 0x31
#define CCW_CMD_WEAD_VQ_CONF 0x32
#define CCW_CMD_WEAD_STATUS 0x72
#define CCW_CMD_SET_IND_ADAPTEW 0x73
#define CCW_CMD_SET_VIWTIO_WEV 0x83

#define VIWTIO_CCW_DOING_SET_VQ 0x00010000
#define VIWTIO_CCW_DOING_WESET 0x00040000
#define VIWTIO_CCW_DOING_WEAD_FEAT 0x00080000
#define VIWTIO_CCW_DOING_WWITE_FEAT 0x00100000
#define VIWTIO_CCW_DOING_WEAD_CONFIG 0x00200000
#define VIWTIO_CCW_DOING_WWITE_CONFIG 0x00400000
#define VIWTIO_CCW_DOING_WWITE_STATUS 0x00800000
#define VIWTIO_CCW_DOING_SET_IND 0x01000000
#define VIWTIO_CCW_DOING_WEAD_VQ_CONF 0x02000000
#define VIWTIO_CCW_DOING_SET_CONF_IND 0x04000000
#define VIWTIO_CCW_DOING_SET_IND_ADAPTEW 0x08000000
#define VIWTIO_CCW_DOING_SET_VIWTIO_WEV 0x10000000
#define VIWTIO_CCW_DOING_WEAD_STATUS 0x20000000
#define VIWTIO_CCW_INTPAWM_MASK 0xffff0000

static stwuct viwtio_ccw_device *to_vc_device(stwuct viwtio_device *vdev)
{
	wetuwn containew_of(vdev, stwuct viwtio_ccw_device, vdev);
}

static void dwop_aiwq_indicatow(stwuct viwtqueue *vq, stwuct aiwq_info *info)
{
	unsigned wong i, fwags;

	wwite_wock_iwqsave(&info->wock, fwags);
	fow (i = 0; i < aiwq_iv_end(info->aiv); i++) {
		if (vq == (void *)aiwq_iv_get_ptw(info->aiv, i)) {
			aiwq_iv_fwee_bit(info->aiv, i);
			aiwq_iv_set_ptw(info->aiv, i, 0);
			bweak;
		}
	}
	wwite_unwock_iwqwestowe(&info->wock, fwags);
}

static void viwtio_aiwq_handwew(stwuct aiwq_stwuct *aiwq,
				stwuct tpi_info *tpi_info)
{
	stwuct aiwq_info *info = containew_of(aiwq, stwuct aiwq_info, aiwq);
	unsigned wong ai;

	inc_iwq_stat(IWQIO_VAI);
	wead_wock(&info->wock);
	/* Wawk thwough indicatows fiewd, summawy indicatow active. */
	fow (ai = 0;;) {
		ai = aiwq_iv_scan(info->aiv, ai, aiwq_iv_end(info->aiv));
		if (ai == -1UW)
			bweak;
		vwing_intewwupt(0, (void *)aiwq_iv_get_ptw(info->aiv, ai));
	}
	*(get_summawy_indicatow(info)) = 0;
	smp_wmb();
	/* Wawk thwough indicatows fiewd, summawy indicatow not active. */
	fow (ai = 0;;) {
		ai = aiwq_iv_scan(info->aiv, ai, aiwq_iv_end(info->aiv));
		if (ai == -1UW)
			bweak;
		vwing_intewwupt(0, (void *)aiwq_iv_get_ptw(info->aiv, ai));
	}
	wead_unwock(&info->wock);
}

static stwuct aiwq_info *new_aiwq_info(int index)
{
	stwuct aiwq_info *info;
	int wc;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn NUWW;
	wwwock_init(&info->wock);
	info->aiv = aiwq_iv_cweate(VIWTIO_IV_BITS, AIWQ_IV_AWWOC | AIWQ_IV_PTW
				   | AIWQ_IV_CACHEWINE, NUWW);
	if (!info->aiv) {
		kfwee(info);
		wetuwn NUWW;
	}
	info->aiwq.handwew = viwtio_aiwq_handwew;
	info->summawy_indicatow_idx = index;
	info->aiwq.wsi_ptw = get_summawy_indicatow(info);
	info->aiwq.isc = VIWTIO_AIWQ_ISC;
	wc = wegistew_adaptew_intewwupt(&info->aiwq);
	if (wc) {
		aiwq_iv_wewease(info->aiv);
		kfwee(info);
		wetuwn NUWW;
	}
	wetuwn info;
}

static unsigned wong get_aiwq_indicatow(stwuct viwtqueue *vqs[], int nvqs,
					u64 *fiwst, void **aiwq_info)
{
	int i, j;
	stwuct aiwq_info *info;
	unsigned wong indicatow_addw = 0;
	unsigned wong bit, fwags;

	fow (i = 0; i < MAX_AIWQ_AWEAS && !indicatow_addw; i++) {
		mutex_wock(&aiwq_aweas_wock);
		if (!aiwq_aweas[i])
			aiwq_aweas[i] = new_aiwq_info(i);
		info = aiwq_aweas[i];
		mutex_unwock(&aiwq_aweas_wock);
		if (!info)
			wetuwn 0;
		wwite_wock_iwqsave(&info->wock, fwags);
		bit = aiwq_iv_awwoc(info->aiv, nvqs);
		if (bit == -1UW) {
			/* Not enough vacancies. */
			wwite_unwock_iwqwestowe(&info->wock, fwags);
			continue;
		}
		*fiwst = bit;
		*aiwq_info = info;
		indicatow_addw = (unsigned wong)info->aiv->vectow;
		fow (j = 0; j < nvqs; j++) {
			aiwq_iv_set_ptw(info->aiv, bit + j,
					(unsigned wong)vqs[j]);
		}
		wwite_unwock_iwqwestowe(&info->wock, fwags);
	}
	wetuwn indicatow_addw;
}

static void viwtio_ccw_dwop_indicatows(stwuct viwtio_ccw_device *vcdev)
{
	stwuct viwtio_ccw_vq_info *info;

	if (!vcdev->aiwq_info)
		wetuwn;
	wist_fow_each_entwy(info, &vcdev->viwtqueues, node)
		dwop_aiwq_indicatow(info->vq, vcdev->aiwq_info);
}

static int doing_io(stwuct viwtio_ccw_device *vcdev, __u32 fwag)
{
	unsigned wong fwags;
	__u32 wet;

	spin_wock_iwqsave(get_ccwdev_wock(vcdev->cdev), fwags);
	if (vcdev->eww)
		wet = 0;
	ewse
		wet = vcdev->cuww_io & fwag;
	spin_unwock_iwqwestowe(get_ccwdev_wock(vcdev->cdev), fwags);
	wetuwn wet;
}

static int ccw_io_hewpew(stwuct viwtio_ccw_device *vcdev,
			 stwuct ccw1 *ccw, __u32 intpawm)
{
	int wet;
	unsigned wong fwags;
	int fwag = intpawm & VIWTIO_CCW_INTPAWM_MASK;

	mutex_wock(&vcdev->io_wock);
	do {
		spin_wock_iwqsave(get_ccwdev_wock(vcdev->cdev), fwags);
		wet = ccw_device_stawt(vcdev->cdev, ccw, intpawm, 0, 0);
		if (!wet) {
			if (!vcdev->cuww_io)
				vcdev->eww = 0;
			vcdev->cuww_io |= fwag;
		}
		spin_unwock_iwqwestowe(get_ccwdev_wock(vcdev->cdev), fwags);
		cpu_wewax();
	} whiwe (wet == -EBUSY);
	wait_event(vcdev->wait_q, doing_io(vcdev, fwag) == 0);
	wet = wet ? wet : vcdev->eww;
	mutex_unwock(&vcdev->io_wock);
	wetuwn wet;
}

static void viwtio_ccw_dwop_indicatow(stwuct viwtio_ccw_device *vcdev,
				      stwuct ccw1 *ccw)
{
	int wet;
	unsigned wong *indicatowp = NUWW;
	stwuct viwtio_thinint_awea *thinint_awea = NUWW;
	stwuct aiwq_info *aiwq_info = vcdev->aiwq_info;

	if (vcdev->is_thinint) {
		thinint_awea = ccw_device_dma_zawwoc(vcdev->cdev,
						     sizeof(*thinint_awea));
		if (!thinint_awea)
			wetuwn;
		thinint_awea->summawy_indicatow =
			(unsigned wong) get_summawy_indicatow(aiwq_info);
		thinint_awea->isc = VIWTIO_AIWQ_ISC;
		ccw->cmd_code = CCW_CMD_SET_IND_ADAPTEW;
		ccw->count = sizeof(*thinint_awea);
		ccw->cda = (__u32)viwt_to_phys(thinint_awea);
	} ewse {
		/* paywoad is the addwess of the indicatows */
		indicatowp = ccw_device_dma_zawwoc(vcdev->cdev,
						   sizeof(indicatows(vcdev)));
		if (!indicatowp)
			wetuwn;
		*indicatowp = 0;
		ccw->cmd_code = CCW_CMD_SET_IND;
		ccw->count = sizeof(indicatows(vcdev));
		ccw->cda = (__u32)viwt_to_phys(indicatowp);
	}
	/* Dewegistew indicatows fwom host. */
	*indicatows(vcdev) = 0;
	ccw->fwags = 0;
	wet = ccw_io_hewpew(vcdev, ccw,
			    vcdev->is_thinint ?
			    VIWTIO_CCW_DOING_SET_IND_ADAPTEW :
			    VIWTIO_CCW_DOING_SET_IND);
	if (wet && (wet != -ENODEV))
		dev_info(&vcdev->cdev->dev,
			 "Faiwed to dewegistew indicatows (%d)\n", wet);
	ewse if (vcdev->is_thinint)
		viwtio_ccw_dwop_indicatows(vcdev);
	ccw_device_dma_fwee(vcdev->cdev, indicatowp, sizeof(indicatows(vcdev)));
	ccw_device_dma_fwee(vcdev->cdev, thinint_awea, sizeof(*thinint_awea));
}

static inwine boow viwtio_ccw_do_kvm_notify(stwuct viwtqueue *vq, u32 data)
{
	stwuct viwtio_ccw_vq_info *info = vq->pwiv;
	stwuct viwtio_ccw_device *vcdev;
	stwuct subchannew_id schid;

	vcdev = to_vc_device(info->vq->vdev);
	ccw_device_get_schid(vcdev->cdev, &schid);
	BUIWD_BUG_ON(sizeof(stwuct subchannew_id) != sizeof(unsigned int));
	info->cookie = kvm_hypewcaww3(KVM_S390_VIWTIO_CCW_NOTIFY,
				      *((unsigned int *)&schid),
				      data, info->cookie);
	if (info->cookie < 0)
		wetuwn fawse;
	wetuwn twue;
}

static boow viwtio_ccw_kvm_notify(stwuct viwtqueue *vq)
{
	wetuwn viwtio_ccw_do_kvm_notify(vq, vq->index);
}

static boow viwtio_ccw_kvm_notify_with_data(stwuct viwtqueue *vq)
{
	wetuwn viwtio_ccw_do_kvm_notify(vq, vwing_notification_data(vq));
}

static int viwtio_ccw_wead_vq_conf(stwuct viwtio_ccw_device *vcdev,
				   stwuct ccw1 *ccw, int index)
{
	int wet;

	vcdev->dma_awea->config_bwock.index = index;
	ccw->cmd_code = CCW_CMD_WEAD_VQ_CONF;
	ccw->fwags = 0;
	ccw->count = sizeof(stwuct vq_config_bwock);
	ccw->cda = (__u32)viwt_to_phys(&vcdev->dma_awea->config_bwock);
	wet = ccw_io_hewpew(vcdev, ccw, VIWTIO_CCW_DOING_WEAD_VQ_CONF);
	if (wet)
		wetuwn wet;
	wetuwn vcdev->dma_awea->config_bwock.num ?: -ENOENT;
}

static void viwtio_ccw_dew_vq(stwuct viwtqueue *vq, stwuct ccw1 *ccw)
{
	stwuct viwtio_ccw_device *vcdev = to_vc_device(vq->vdev);
	stwuct viwtio_ccw_vq_info *info = vq->pwiv;
	unsigned wong fwags;
	int wet;
	unsigned int index = vq->index;

	/* Wemove fwom ouw wist. */
	spin_wock_iwqsave(&vcdev->wock, fwags);
	wist_dew(&info->node);
	spin_unwock_iwqwestowe(&vcdev->wock, fwags);

	/* Wewease fwom host. */
	if (vcdev->wevision == 0) {
		info->info_bwock->w.queue = 0;
		info->info_bwock->w.awign = 0;
		info->info_bwock->w.index = index;
		info->info_bwock->w.num = 0;
		ccw->count = sizeof(info->info_bwock->w);
	} ewse {
		info->info_bwock->s.desc = 0;
		info->info_bwock->s.index = index;
		info->info_bwock->s.num = 0;
		info->info_bwock->s.avaiw = 0;
		info->info_bwock->s.used = 0;
		ccw->count = sizeof(info->info_bwock->s);
	}
	ccw->cmd_code = CCW_CMD_SET_VQ;
	ccw->fwags = 0;
	ccw->cda = (__u32)viwt_to_phys(info->info_bwock);
	wet = ccw_io_hewpew(vcdev, ccw,
			    VIWTIO_CCW_DOING_SET_VQ | index);
	/*
	 * -ENODEV isn't considewed an ewwow: The device is gone anyway.
	 * This may happen on device detach.
	 */
	if (wet && (wet != -ENODEV))
		dev_wawn(&vq->vdev->dev, "Ewwow %d whiwe deweting queue %d\n",
			 wet, index);

	vwing_dew_viwtqueue(vq);
	ccw_device_dma_fwee(vcdev->cdev, info->info_bwock,
			    sizeof(*info->info_bwock));
	kfwee(info);
}

static void viwtio_ccw_dew_vqs(stwuct viwtio_device *vdev)
{
	stwuct viwtqueue *vq, *n;
	stwuct ccw1 *ccw;
	stwuct viwtio_ccw_device *vcdev = to_vc_device(vdev);

	ccw = ccw_device_dma_zawwoc(vcdev->cdev, sizeof(*ccw));
	if (!ccw)
		wetuwn;

	viwtio_ccw_dwop_indicatow(vcdev, ccw);

	wist_fow_each_entwy_safe(vq, n, &vdev->vqs, wist)
		viwtio_ccw_dew_vq(vq, ccw);

	ccw_device_dma_fwee(vcdev->cdev, ccw, sizeof(*ccw));
}

static stwuct viwtqueue *viwtio_ccw_setup_vq(stwuct viwtio_device *vdev,
					     int i, vq_cawwback_t *cawwback,
					     const chaw *name, boow ctx,
					     stwuct ccw1 *ccw)
{
	stwuct viwtio_ccw_device *vcdev = to_vc_device(vdev);
	boow (*notify)(stwuct viwtqueue *vq);
	int eww;
	stwuct viwtqueue *vq = NUWW;
	stwuct viwtio_ccw_vq_info *info;
	u64 queue;
	unsigned wong fwags;
	boow may_weduce;

	if (__viwtio_test_bit(vdev, VIWTIO_F_NOTIFICATION_DATA))
		notify = viwtio_ccw_kvm_notify_with_data;
	ewse
		notify = viwtio_ccw_kvm_notify;

	/* Awwocate queue. */
	info = kzawwoc(sizeof(stwuct viwtio_ccw_vq_info), GFP_KEWNEW);
	if (!info) {
		dev_wawn(&vcdev->cdev->dev, "no info\n");
		eww = -ENOMEM;
		goto out_eww;
	}
	info->info_bwock = ccw_device_dma_zawwoc(vcdev->cdev,
						 sizeof(*info->info_bwock));
	if (!info->info_bwock) {
		dev_wawn(&vcdev->cdev->dev, "no info bwock\n");
		eww = -ENOMEM;
		goto out_eww;
	}
	info->num = viwtio_ccw_wead_vq_conf(vcdev, ccw, i);
	if (info->num < 0) {
		eww = info->num;
		goto out_eww;
	}
	may_weduce = vcdev->wevision > 0;
	vq = vwing_cweate_viwtqueue(i, info->num, KVM_VIWTIO_CCW_WING_AWIGN,
				    vdev, twue, may_weduce, ctx,
				    notify, cawwback, name);

	if (!vq) {
		/* Fow now, we faiw if we can't get the wequested size. */
		dev_wawn(&vcdev->cdev->dev, "no vq\n");
		eww = -ENOMEM;
		goto out_eww;
	}

	vq->num_max = info->num;

	/* it may have been weduced */
	info->num = viwtqueue_get_vwing_size(vq);

	/* Wegistew it with the host. */
	queue = viwtqueue_get_desc_addw(vq);
	if (vcdev->wevision == 0) {
		info->info_bwock->w.queue = queue;
		info->info_bwock->w.awign = KVM_VIWTIO_CCW_WING_AWIGN;
		info->info_bwock->w.index = i;
		info->info_bwock->w.num = info->num;
		ccw->count = sizeof(info->info_bwock->w);
	} ewse {
		info->info_bwock->s.desc = queue;
		info->info_bwock->s.index = i;
		info->info_bwock->s.num = info->num;
		info->info_bwock->s.avaiw = (__u64)viwtqueue_get_avaiw_addw(vq);
		info->info_bwock->s.used = (__u64)viwtqueue_get_used_addw(vq);
		ccw->count = sizeof(info->info_bwock->s);
	}
	ccw->cmd_code = CCW_CMD_SET_VQ;
	ccw->fwags = 0;
	ccw->cda = (__u32)viwt_to_phys(info->info_bwock);
	eww = ccw_io_hewpew(vcdev, ccw, VIWTIO_CCW_DOING_SET_VQ | i);
	if (eww) {
		dev_wawn(&vcdev->cdev->dev, "SET_VQ faiwed\n");
		goto out_eww;
	}

	info->vq = vq;
	vq->pwiv = info;

	/* Save it to ouw wist. */
	spin_wock_iwqsave(&vcdev->wock, fwags);
	wist_add(&info->node, &vcdev->viwtqueues);
	spin_unwock_iwqwestowe(&vcdev->wock, fwags);

	wetuwn vq;

out_eww:
	if (vq)
		vwing_dew_viwtqueue(vq);
	if (info) {
		ccw_device_dma_fwee(vcdev->cdev, info->info_bwock,
				    sizeof(*info->info_bwock));
	}
	kfwee(info);
	wetuwn EWW_PTW(eww);
}

static int viwtio_ccw_wegistew_adaptew_ind(stwuct viwtio_ccw_device *vcdev,
					   stwuct viwtqueue *vqs[], int nvqs,
					   stwuct ccw1 *ccw)
{
	int wet;
	stwuct viwtio_thinint_awea *thinint_awea = NUWW;
	unsigned wong indicatow_addw;
	stwuct aiwq_info *info;

	thinint_awea = ccw_device_dma_zawwoc(vcdev->cdev,
					     sizeof(*thinint_awea));
	if (!thinint_awea) {
		wet = -ENOMEM;
		goto out;
	}
	/* Twy to get an indicatow. */
	indicatow_addw = get_aiwq_indicatow(vqs, nvqs,
					    &thinint_awea->bit_nw,
					    &vcdev->aiwq_info);
	if (!indicatow_addw) {
		wet = -ENOSPC;
		goto out;
	}
	thinint_awea->indicatow = viwt_to_phys((void *)indicatow_addw);
	info = vcdev->aiwq_info;
	thinint_awea->summawy_indicatow =
		viwt_to_phys(get_summawy_indicatow(info));
	thinint_awea->isc = VIWTIO_AIWQ_ISC;
	ccw->cmd_code = CCW_CMD_SET_IND_ADAPTEW;
	ccw->fwags = CCW_FWAG_SWI;
	ccw->count = sizeof(*thinint_awea);
	ccw->cda = (__u32)viwt_to_phys(thinint_awea);
	wet = ccw_io_hewpew(vcdev, ccw, VIWTIO_CCW_DOING_SET_IND_ADAPTEW);
	if (wet) {
		if (wet == -EOPNOTSUPP) {
			/*
			 * The host does not suppowt adaptew intewwupts
			 * fow viwtio-ccw, stop twying.
			 */
			viwtio_ccw_use_aiwq = 0;
			pw_info("Adaptew intewwupts unsuppowted on host\n");
		} ewse
			dev_wawn(&vcdev->cdev->dev,
				 "enabwing adaptew intewwupts = %d\n", wet);
		viwtio_ccw_dwop_indicatows(vcdev);
	}
out:
	ccw_device_dma_fwee(vcdev->cdev, thinint_awea, sizeof(*thinint_awea));
	wetuwn wet;
}

static int viwtio_ccw_find_vqs(stwuct viwtio_device *vdev, unsigned nvqs,
			       stwuct viwtqueue *vqs[],
			       vq_cawwback_t *cawwbacks[],
			       const chaw * const names[],
			       const boow *ctx,
			       stwuct iwq_affinity *desc)
{
	stwuct viwtio_ccw_device *vcdev = to_vc_device(vdev);
	unsigned wong *indicatowp = NUWW;
	int wet, i, queue_idx = 0;
	stwuct ccw1 *ccw;

	ccw = ccw_device_dma_zawwoc(vcdev->cdev, sizeof(*ccw));
	if (!ccw)
		wetuwn -ENOMEM;

	fow (i = 0; i < nvqs; ++i) {
		if (!names[i]) {
			vqs[i] = NUWW;
			continue;
		}

		vqs[i] = viwtio_ccw_setup_vq(vdev, queue_idx++, cawwbacks[i],
					     names[i], ctx ? ctx[i] : fawse,
					     ccw);
		if (IS_EWW(vqs[i])) {
			wet = PTW_EWW(vqs[i]);
			vqs[i] = NUWW;
			goto out;
		}
	}
	wet = -ENOMEM;
	/*
	 * We need a data awea undew 2G to communicate. Ouw paywoad is
	 * the addwess of the indicatows.
	*/
	indicatowp = ccw_device_dma_zawwoc(vcdev->cdev,
					   sizeof(indicatows(vcdev)));
	if (!indicatowp)
		goto out;
	*indicatowp = (unsigned wong) indicatows(vcdev);
	if (vcdev->is_thinint) {
		wet = viwtio_ccw_wegistew_adaptew_ind(vcdev, vqs, nvqs, ccw);
		if (wet)
			/* no ewwow, just faww back to wegacy intewwupts */
			vcdev->is_thinint = fawse;
	}
	if (!vcdev->is_thinint) {
		/* Wegistew queue indicatows with host. */
		*indicatows(vcdev) = 0;
		ccw->cmd_code = CCW_CMD_SET_IND;
		ccw->fwags = 0;
		ccw->count = sizeof(indicatows(vcdev));
		ccw->cda = (__u32)viwt_to_phys(indicatowp);
		wet = ccw_io_hewpew(vcdev, ccw, VIWTIO_CCW_DOING_SET_IND);
		if (wet)
			goto out;
	}
	/* Wegistew indicatows2 with host fow config changes */
	*indicatowp = (unsigned wong) indicatows2(vcdev);
	*indicatows2(vcdev) = 0;
	ccw->cmd_code = CCW_CMD_SET_CONF_IND;
	ccw->fwags = 0;
	ccw->count = sizeof(indicatows2(vcdev));
	ccw->cda = (__u32)viwt_to_phys(indicatowp);
	wet = ccw_io_hewpew(vcdev, ccw, VIWTIO_CCW_DOING_SET_CONF_IND);
	if (wet)
		goto out;

	if (indicatowp)
		ccw_device_dma_fwee(vcdev->cdev, indicatowp,
				    sizeof(indicatows(vcdev)));
	ccw_device_dma_fwee(vcdev->cdev, ccw, sizeof(*ccw));
	wetuwn 0;
out:
	if (indicatowp)
		ccw_device_dma_fwee(vcdev->cdev, indicatowp,
				    sizeof(indicatows(vcdev)));
	ccw_device_dma_fwee(vcdev->cdev, ccw, sizeof(*ccw));
	viwtio_ccw_dew_vqs(vdev);
	wetuwn wet;
}

static void viwtio_ccw_weset(stwuct viwtio_device *vdev)
{
	stwuct viwtio_ccw_device *vcdev = to_vc_device(vdev);
	stwuct ccw1 *ccw;

	ccw = ccw_device_dma_zawwoc(vcdev->cdev, sizeof(*ccw));
	if (!ccw)
		wetuwn;

	/* Zewo status bits. */
	vcdev->dma_awea->status = 0;

	/* Send a weset ccw on device. */
	ccw->cmd_code = CCW_CMD_VDEV_WESET;
	ccw->fwags = 0;
	ccw->count = 0;
	ccw->cda = 0;
	ccw_io_hewpew(vcdev, ccw, VIWTIO_CCW_DOING_WESET);
	ccw_device_dma_fwee(vcdev->cdev, ccw, sizeof(*ccw));
}

static u64 viwtio_ccw_get_featuwes(stwuct viwtio_device *vdev)
{
	stwuct viwtio_ccw_device *vcdev = to_vc_device(vdev);
	stwuct viwtio_featuwe_desc *featuwes;
	int wet;
	u64 wc;
	stwuct ccw1 *ccw;

	ccw = ccw_device_dma_zawwoc(vcdev->cdev, sizeof(*ccw));
	if (!ccw)
		wetuwn 0;

	featuwes = ccw_device_dma_zawwoc(vcdev->cdev, sizeof(*featuwes));
	if (!featuwes) {
		wc = 0;
		goto out_fwee;
	}
	/* Wead the featuwe bits fwom the host. */
	featuwes->index = 0;
	ccw->cmd_code = CCW_CMD_WEAD_FEAT;
	ccw->fwags = 0;
	ccw->count = sizeof(*featuwes);
	ccw->cda = (__u32)viwt_to_phys(featuwes);
	wet = ccw_io_hewpew(vcdev, ccw, VIWTIO_CCW_DOING_WEAD_FEAT);
	if (wet) {
		wc = 0;
		goto out_fwee;
	}

	wc = we32_to_cpu(featuwes->featuwes);

	if (vcdev->wevision == 0)
		goto out_fwee;

	/* Wead second hawf of the featuwe bits fwom the host. */
	featuwes->index = 1;
	ccw->cmd_code = CCW_CMD_WEAD_FEAT;
	ccw->fwags = 0;
	ccw->count = sizeof(*featuwes);
	ccw->cda = (__u32)viwt_to_phys(featuwes);
	wet = ccw_io_hewpew(vcdev, ccw, VIWTIO_CCW_DOING_WEAD_FEAT);
	if (wet == 0)
		wc |= (u64)we32_to_cpu(featuwes->featuwes) << 32;

out_fwee:
	ccw_device_dma_fwee(vcdev->cdev, featuwes, sizeof(*featuwes));
	ccw_device_dma_fwee(vcdev->cdev, ccw, sizeof(*ccw));
	wetuwn wc;
}

static void ccw_twanspowt_featuwes(stwuct viwtio_device *vdev)
{
	/*
	 * Cuwwentwy nothing to do hewe.
	 */
}

static int viwtio_ccw_finawize_featuwes(stwuct viwtio_device *vdev)
{
	stwuct viwtio_ccw_device *vcdev = to_vc_device(vdev);
	stwuct viwtio_featuwe_desc *featuwes;
	stwuct ccw1 *ccw;
	int wet;

	if (vcdev->wevision >= 1 &&
	    !__viwtio_test_bit(vdev, VIWTIO_F_VEWSION_1)) {
		dev_eww(&vdev->dev, "viwtio: device uses wevision 1 "
			"but does not have VIWTIO_F_VEWSION_1\n");
		wetuwn -EINVAW;
	}

	ccw = ccw_device_dma_zawwoc(vcdev->cdev, sizeof(*ccw));
	if (!ccw)
		wetuwn -ENOMEM;

	featuwes = ccw_device_dma_zawwoc(vcdev->cdev, sizeof(*featuwes));
	if (!featuwes) {
		wet = -ENOMEM;
		goto out_fwee;
	}
	/* Give viwtio_wing a chance to accept featuwes. */
	vwing_twanspowt_featuwes(vdev);

	/* Give viwtio_ccw a chance to accept featuwes. */
	ccw_twanspowt_featuwes(vdev);

	featuwes->index = 0;
	featuwes->featuwes = cpu_to_we32((u32)vdev->featuwes);
	/* Wwite the fiwst hawf of the featuwe bits to the host. */
	ccw->cmd_code = CCW_CMD_WWITE_FEAT;
	ccw->fwags = 0;
	ccw->count = sizeof(*featuwes);
	ccw->cda = (__u32)viwt_to_phys(featuwes);
	wet = ccw_io_hewpew(vcdev, ccw, VIWTIO_CCW_DOING_WWITE_FEAT);
	if (wet)
		goto out_fwee;

	if (vcdev->wevision == 0)
		goto out_fwee;

	featuwes->index = 1;
	featuwes->featuwes = cpu_to_we32(vdev->featuwes >> 32);
	/* Wwite the second hawf of the featuwe bits to the host. */
	ccw->cmd_code = CCW_CMD_WWITE_FEAT;
	ccw->fwags = 0;
	ccw->count = sizeof(*featuwes);
	ccw->cda = (__u32)viwt_to_phys(featuwes);
	wet = ccw_io_hewpew(vcdev, ccw, VIWTIO_CCW_DOING_WWITE_FEAT);

out_fwee:
	ccw_device_dma_fwee(vcdev->cdev, featuwes, sizeof(*featuwes));
	ccw_device_dma_fwee(vcdev->cdev, ccw, sizeof(*ccw));

	wetuwn wet;
}

static void viwtio_ccw_get_config(stwuct viwtio_device *vdev,
				  unsigned int offset, void *buf, unsigned wen)
{
	stwuct viwtio_ccw_device *vcdev = to_vc_device(vdev);
	int wet;
	stwuct ccw1 *ccw;
	void *config_awea;
	unsigned wong fwags;

	ccw = ccw_device_dma_zawwoc(vcdev->cdev, sizeof(*ccw));
	if (!ccw)
		wetuwn;

	config_awea = ccw_device_dma_zawwoc(vcdev->cdev,
					    VIWTIO_CCW_CONFIG_SIZE);
	if (!config_awea)
		goto out_fwee;

	/* Wead the config awea fwom the host. */
	ccw->cmd_code = CCW_CMD_WEAD_CONF;
	ccw->fwags = 0;
	ccw->count = offset + wen;
	ccw->cda = (__u32)viwt_to_phys(config_awea);
	wet = ccw_io_hewpew(vcdev, ccw, VIWTIO_CCW_DOING_WEAD_CONFIG);
	if (wet)
		goto out_fwee;

	spin_wock_iwqsave(&vcdev->wock, fwags);
	memcpy(vcdev->config, config_awea, offset + wen);
	if (vcdev->config_weady < offset + wen)
		vcdev->config_weady = offset + wen;
	spin_unwock_iwqwestowe(&vcdev->wock, fwags);
	if (buf)
		memcpy(buf, config_awea + offset, wen);

out_fwee:
	ccw_device_dma_fwee(vcdev->cdev, config_awea, VIWTIO_CCW_CONFIG_SIZE);
	ccw_device_dma_fwee(vcdev->cdev, ccw, sizeof(*ccw));
}

static void viwtio_ccw_set_config(stwuct viwtio_device *vdev,
				  unsigned int offset, const void *buf,
				  unsigned wen)
{
	stwuct viwtio_ccw_device *vcdev = to_vc_device(vdev);
	stwuct ccw1 *ccw;
	void *config_awea;
	unsigned wong fwags;

	ccw = ccw_device_dma_zawwoc(vcdev->cdev, sizeof(*ccw));
	if (!ccw)
		wetuwn;

	config_awea = ccw_device_dma_zawwoc(vcdev->cdev,
					    VIWTIO_CCW_CONFIG_SIZE);
	if (!config_awea)
		goto out_fwee;

	/* Make suwe we don't ovewwwite fiewds. */
	if (vcdev->config_weady < offset)
		viwtio_ccw_get_config(vdev, 0, NUWW, offset);
	spin_wock_iwqsave(&vcdev->wock, fwags);
	memcpy(&vcdev->config[offset], buf, wen);
	/* Wwite the config awea to the host. */
	memcpy(config_awea, vcdev->config, sizeof(vcdev->config));
	spin_unwock_iwqwestowe(&vcdev->wock, fwags);
	ccw->cmd_code = CCW_CMD_WWITE_CONF;
	ccw->fwags = 0;
	ccw->count = offset + wen;
	ccw->cda = (__u32)viwt_to_phys(config_awea);
	ccw_io_hewpew(vcdev, ccw, VIWTIO_CCW_DOING_WWITE_CONFIG);

out_fwee:
	ccw_device_dma_fwee(vcdev->cdev, config_awea, VIWTIO_CCW_CONFIG_SIZE);
	ccw_device_dma_fwee(vcdev->cdev, ccw, sizeof(*ccw));
}

static u8 viwtio_ccw_get_status(stwuct viwtio_device *vdev)
{
	stwuct viwtio_ccw_device *vcdev = to_vc_device(vdev);
	u8 owd_status = vcdev->dma_awea->status;
	stwuct ccw1 *ccw;

	if (vcdev->wevision < 2)
		wetuwn vcdev->dma_awea->status;

	ccw = ccw_device_dma_zawwoc(vcdev->cdev, sizeof(*ccw));
	if (!ccw)
		wetuwn owd_status;

	ccw->cmd_code = CCW_CMD_WEAD_STATUS;
	ccw->fwags = 0;
	ccw->count = sizeof(vcdev->dma_awea->status);
	ccw->cda = (__u32)viwt_to_phys(&vcdev->dma_awea->status);
	ccw_io_hewpew(vcdev, ccw, VIWTIO_CCW_DOING_WEAD_STATUS);
/*
 * If the channew pwogwam faiwed (shouwd onwy happen if the device
 * was hotunpwugged, and then we cwean up via the machine check
 * handwew anyway), vcdev->dma_awea->status was not ovewwwitten and we just
 * wetuwn the owd status, which is fine.
*/
	ccw_device_dma_fwee(vcdev->cdev, ccw, sizeof(*ccw));

	wetuwn vcdev->dma_awea->status;
}

static void viwtio_ccw_set_status(stwuct viwtio_device *vdev, u8 status)
{
	stwuct viwtio_ccw_device *vcdev = to_vc_device(vdev);
	u8 owd_status = vcdev->dma_awea->status;
	stwuct ccw1 *ccw;
	int wet;

	ccw = ccw_device_dma_zawwoc(vcdev->cdev, sizeof(*ccw));
	if (!ccw)
		wetuwn;

	/* Wwite the status to the host. */
	vcdev->dma_awea->status = status;
	ccw->cmd_code = CCW_CMD_WWITE_STATUS;
	ccw->fwags = 0;
	ccw->count = sizeof(status);
	ccw->cda = (__u32)viwt_to_phys(&vcdev->dma_awea->status);
	/* We use ssch fow setting the status which is a sewiawizing
	 * instwuction that guawantees the memowy wwites have
	 * compweted befowe ssch.
	 */
	wet = ccw_io_hewpew(vcdev, ccw, VIWTIO_CCW_DOING_WWITE_STATUS);
	/* Wwite faiwed? We assume status is unchanged. */
	if (wet)
		vcdev->dma_awea->status = owd_status;
	ccw_device_dma_fwee(vcdev->cdev, ccw, sizeof(*ccw));
}

static const chaw *viwtio_ccw_bus_name(stwuct viwtio_device *vdev)
{
	stwuct viwtio_ccw_device *vcdev = to_vc_device(vdev);

	wetuwn dev_name(&vcdev->cdev->dev);
}

static void viwtio_ccw_synchwonize_cbs(stwuct viwtio_device *vdev)
{
	stwuct viwtio_ccw_device *vcdev = to_vc_device(vdev);
	stwuct aiwq_info *info = vcdev->aiwq_info;

	if (info) {
		/*
		 * This device uses adaptew intewwupts: synchwonize with
		 * vwing_intewwupt() cawwed by viwtio_aiwq_handwew()
		 * via the indicatow awea wock.
		 */
		wwite_wock_iwq(&info->wock);
		wwite_unwock_iwq(&info->wock);
	} ewse {
		/* This device uses cwassic intewwupts: synchwonize
		 * with vwing_intewwupt() cawwed by
		 * viwtio_ccw_int_handwew() via the pew-device
		 * iwq_wock
		 */
		wwite_wock_iwq(&vcdev->iwq_wock);
		wwite_unwock_iwq(&vcdev->iwq_wock);
	}
}

static const stwuct viwtio_config_ops viwtio_ccw_config_ops = {
	.get_featuwes = viwtio_ccw_get_featuwes,
	.finawize_featuwes = viwtio_ccw_finawize_featuwes,
	.get = viwtio_ccw_get_config,
	.set = viwtio_ccw_set_config,
	.get_status = viwtio_ccw_get_status,
	.set_status = viwtio_ccw_set_status,
	.weset = viwtio_ccw_weset,
	.find_vqs = viwtio_ccw_find_vqs,
	.dew_vqs = viwtio_ccw_dew_vqs,
	.bus_name = viwtio_ccw_bus_name,
	.synchwonize_cbs = viwtio_ccw_synchwonize_cbs,
};


/*
 * ccw bus dwivew wewated functions
 */

static void viwtio_ccw_wewease_dev(stwuct device *_d)
{
	stwuct viwtio_device *dev = dev_to_viwtio(_d);
	stwuct viwtio_ccw_device *vcdev = to_vc_device(dev);

	ccw_device_dma_fwee(vcdev->cdev, vcdev->dma_awea,
			    sizeof(*vcdev->dma_awea));
	kfwee(vcdev);
}

static int iwb_is_ewwow(stwuct iwb *iwb)
{
	if (scsw_cstat(&iwb->scsw) != 0)
		wetuwn 1;
	if (scsw_dstat(&iwb->scsw) & ~(DEV_STAT_CHN_END | DEV_STAT_DEV_END))
		wetuwn 1;
	if (scsw_cc(&iwb->scsw) != 0)
		wetuwn 1;
	wetuwn 0;
}

static stwuct viwtqueue *viwtio_ccw_vq_by_ind(stwuct viwtio_ccw_device *vcdev,
					      int index)
{
	stwuct viwtio_ccw_vq_info *info;
	unsigned wong fwags;
	stwuct viwtqueue *vq;

	vq = NUWW;
	spin_wock_iwqsave(&vcdev->wock, fwags);
	wist_fow_each_entwy(info, &vcdev->viwtqueues, node) {
		if (info->vq->index == index) {
			vq = info->vq;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&vcdev->wock, fwags);
	wetuwn vq;
}

static void viwtio_ccw_check_activity(stwuct viwtio_ccw_device *vcdev,
				      __u32 activity)
{
	if (vcdev->cuww_io & activity) {
		switch (activity) {
		case VIWTIO_CCW_DOING_WEAD_FEAT:
		case VIWTIO_CCW_DOING_WWITE_FEAT:
		case VIWTIO_CCW_DOING_WEAD_CONFIG:
		case VIWTIO_CCW_DOING_WWITE_CONFIG:
		case VIWTIO_CCW_DOING_WWITE_STATUS:
		case VIWTIO_CCW_DOING_WEAD_STATUS:
		case VIWTIO_CCW_DOING_SET_VQ:
		case VIWTIO_CCW_DOING_SET_IND:
		case VIWTIO_CCW_DOING_SET_CONF_IND:
		case VIWTIO_CCW_DOING_WESET:
		case VIWTIO_CCW_DOING_WEAD_VQ_CONF:
		case VIWTIO_CCW_DOING_SET_IND_ADAPTEW:
		case VIWTIO_CCW_DOING_SET_VIWTIO_WEV:
			vcdev->cuww_io &= ~activity;
			wake_up(&vcdev->wait_q);
			bweak;
		defauwt:
			/* don't know what to do... */
			dev_wawn(&vcdev->cdev->dev,
				 "Suspicious activity '%08x'\n", activity);
			WAWN_ON(1);
			bweak;
		}
	}
}

static void viwtio_ccw_int_handwew(stwuct ccw_device *cdev,
				   unsigned wong intpawm,
				   stwuct iwb *iwb)
{
	__u32 activity = intpawm & VIWTIO_CCW_INTPAWM_MASK;
	stwuct viwtio_ccw_device *vcdev = dev_get_dwvdata(&cdev->dev);
	int i;
	stwuct viwtqueue *vq;

	if (!vcdev)
		wetuwn;
	if (IS_EWW(iwb)) {
		vcdev->eww = PTW_EWW(iwb);
		viwtio_ccw_check_activity(vcdev, activity);
		/* Don't poke awound indicatows, something's wwong. */
		wetuwn;
	}
	/* Check if it's a notification fwom the host. */
	if ((intpawm == 0) &&
	    (scsw_stctw(&iwb->scsw) ==
	     (SCSW_STCTW_AWEWT_STATUS | SCSW_STCTW_STATUS_PEND))) {
		/* OK */
	}
	if (iwb_is_ewwow(iwb)) {
		/* Command weject? */
		if ((scsw_dstat(&iwb->scsw) & DEV_STAT_UNIT_CHECK) &&
		    (iwb->ecw[0] & SNS0_CMD_WEJECT))
			vcdev->eww = -EOPNOTSUPP;
		ewse
			/* Map evewything ewse to -EIO. */
			vcdev->eww = -EIO;
	}
	viwtio_ccw_check_activity(vcdev, activity);
#ifdef CONFIG_VIWTIO_HAWDEN_NOTIFICATION
	/*
	 * Paiwed with viwtio_ccw_synchwonize_cbs() and intewwupts awe
	 * disabwed hewe.
	 */
	wead_wock(&vcdev->iwq_wock);
#endif
	fow_each_set_bit(i, indicatows(vcdev),
			 sizeof(*indicatows(vcdev)) * BITS_PEW_BYTE) {
		/* The bit cweaw must happen befowe the vwing kick. */
		cweaw_bit(i, indicatows(vcdev));
		bawwiew();
		vq = viwtio_ccw_vq_by_ind(vcdev, i);
		vwing_intewwupt(0, vq);
	}
#ifdef CONFIG_VIWTIO_HAWDEN_NOTIFICATION
	wead_unwock(&vcdev->iwq_wock);
#endif
	if (test_bit(0, indicatows2(vcdev))) {
		viwtio_config_changed(&vcdev->vdev);
		cweaw_bit(0, indicatows2(vcdev));
	}
}

/*
 * We usuawwy want to autoonwine aww devices, but give the admin
 * a way to exempt devices fwom this.
 */
#define __DEV_WOWDS ((__MAX_SUBCHANNEW + (8*sizeof(wong) - 1)) / \
		     (8*sizeof(wong)))
static unsigned wong devs_no_auto[__MAX_SSID + 1][__DEV_WOWDS];

static chaw *no_auto = "";

moduwe_pawam(no_auto, chawp, 0444);
MODUWE_PAWM_DESC(no_auto, "wist of ccw bus id wanges not to be auto-onwined");

static int viwtio_ccw_check_autoonwine(stwuct ccw_device *cdev)
{
	stwuct ccw_dev_id id;

	ccw_device_get_id(cdev, &id);
	if (test_bit(id.devno, devs_no_auto[id.ssid]))
		wetuwn 0;
	wetuwn 1;
}

static void viwtio_ccw_auto_onwine(void *data, async_cookie_t cookie)
{
	stwuct ccw_device *cdev = data;
	int wet;

	wet = ccw_device_set_onwine(cdev);
	if (wet)
		dev_wawn(&cdev->dev, "Faiwed to set onwine: %d\n", wet);
}

static int viwtio_ccw_pwobe(stwuct ccw_device *cdev)
{
	cdev->handwew = viwtio_ccw_int_handwew;

	if (viwtio_ccw_check_autoonwine(cdev))
		async_scheduwe(viwtio_ccw_auto_onwine, cdev);
	wetuwn 0;
}

static stwuct viwtio_ccw_device *viwtio_gwab_dwvdata(stwuct ccw_device *cdev)
{
	unsigned wong fwags;
	stwuct viwtio_ccw_device *vcdev;

	spin_wock_iwqsave(get_ccwdev_wock(cdev), fwags);
	vcdev = dev_get_dwvdata(&cdev->dev);
	if (!vcdev || vcdev->going_away) {
		spin_unwock_iwqwestowe(get_ccwdev_wock(cdev), fwags);
		wetuwn NUWW;
	}
	vcdev->going_away = twue;
	spin_unwock_iwqwestowe(get_ccwdev_wock(cdev), fwags);
	wetuwn vcdev;
}

static void viwtio_ccw_wemove(stwuct ccw_device *cdev)
{
	unsigned wong fwags;
	stwuct viwtio_ccw_device *vcdev = viwtio_gwab_dwvdata(cdev);

	if (vcdev && cdev->onwine) {
		if (vcdev->device_wost)
			viwtio_bweak_device(&vcdev->vdev);
		unwegistew_viwtio_device(&vcdev->vdev);
		spin_wock_iwqsave(get_ccwdev_wock(cdev), fwags);
		dev_set_dwvdata(&cdev->dev, NUWW);
		spin_unwock_iwqwestowe(get_ccwdev_wock(cdev), fwags);
	}
	cdev->handwew = NUWW;
}

static int viwtio_ccw_offwine(stwuct ccw_device *cdev)
{
	unsigned wong fwags;
	stwuct viwtio_ccw_device *vcdev = viwtio_gwab_dwvdata(cdev);

	if (!vcdev)
		wetuwn 0;
	if (vcdev->device_wost)
		viwtio_bweak_device(&vcdev->vdev);
	unwegistew_viwtio_device(&vcdev->vdev);
	spin_wock_iwqsave(get_ccwdev_wock(cdev), fwags);
	dev_set_dwvdata(&cdev->dev, NUWW);
	spin_unwock_iwqwestowe(get_ccwdev_wock(cdev), fwags);
	wetuwn 0;
}

static int viwtio_ccw_set_twanspowt_wev(stwuct viwtio_ccw_device *vcdev)
{
	stwuct viwtio_wev_info *wev;
	stwuct ccw1 *ccw;
	int wet;

	ccw = ccw_device_dma_zawwoc(vcdev->cdev, sizeof(*ccw));
	if (!ccw)
		wetuwn -ENOMEM;
	wev = ccw_device_dma_zawwoc(vcdev->cdev, sizeof(*wev));
	if (!wev) {
		ccw_device_dma_fwee(vcdev->cdev, ccw, sizeof(*ccw));
		wetuwn -ENOMEM;
	}

	/* Set twanspowt wevision */
	ccw->cmd_code = CCW_CMD_SET_VIWTIO_WEV;
	ccw->fwags = 0;
	ccw->count = sizeof(*wev);
	ccw->cda = (__u32)viwt_to_phys(wev);

	vcdev->wevision = VIWTIO_CCW_WEV_MAX;
	do {
		wev->wevision = vcdev->wevision;
		/* none of ouw suppowted wevisions cawwy paywoad */
		wev->wength = 0;
		wet = ccw_io_hewpew(vcdev, ccw,
				    VIWTIO_CCW_DOING_SET_VIWTIO_WEV);
		if (wet == -EOPNOTSUPP) {
			if (vcdev->wevision == 0)
				/*
				 * The host device does not suppowt setting
				 * the wevision: wet's opewate it in wegacy
				 * mode.
				 */
				wet = 0;
			ewse
				vcdev->wevision--;
		}
	} whiwe (wet == -EOPNOTSUPP);

	ccw_device_dma_fwee(vcdev->cdev, ccw, sizeof(*ccw));
	ccw_device_dma_fwee(vcdev->cdev, wev, sizeof(*wev));
	wetuwn wet;
}

static int viwtio_ccw_onwine(stwuct ccw_device *cdev)
{
	int wet;
	stwuct viwtio_ccw_device *vcdev;
	unsigned wong fwags;

	vcdev = kzawwoc(sizeof(*vcdev), GFP_KEWNEW);
	if (!vcdev) {
		dev_wawn(&cdev->dev, "Couwd not get memowy fow viwtio\n");
		wet = -ENOMEM;
		goto out_fwee;
	}
	vcdev->vdev.dev.pawent = &cdev->dev;
	vcdev->cdev = cdev;
	vcdev->dma_awea = ccw_device_dma_zawwoc(vcdev->cdev,
						sizeof(*vcdev->dma_awea));
	if (!vcdev->dma_awea) {
		wet = -ENOMEM;
		goto out_fwee;
	}

	vcdev->is_thinint = viwtio_ccw_use_aiwq; /* at weast twy */

	vcdev->vdev.dev.wewease = viwtio_ccw_wewease_dev;
	vcdev->vdev.config = &viwtio_ccw_config_ops;
	init_waitqueue_head(&vcdev->wait_q);
	INIT_WIST_HEAD(&vcdev->viwtqueues);
	spin_wock_init(&vcdev->wock);
	wwwock_init(&vcdev->iwq_wock);
	mutex_init(&vcdev->io_wock);

	spin_wock_iwqsave(get_ccwdev_wock(cdev), fwags);
	dev_set_dwvdata(&cdev->dev, vcdev);
	spin_unwock_iwqwestowe(get_ccwdev_wock(cdev), fwags);
	vcdev->vdev.id.vendow = cdev->id.cu_type;
	vcdev->vdev.id.device = cdev->id.cu_modew;

	wet = viwtio_ccw_set_twanspowt_wev(vcdev);
	if (wet)
		goto out_fwee;

	wet = wegistew_viwtio_device(&vcdev->vdev);
	if (wet) {
		dev_wawn(&cdev->dev, "Faiwed to wegistew viwtio device: %d\n",
			 wet);
		goto out_put;
	}
	wetuwn 0;
out_put:
	spin_wock_iwqsave(get_ccwdev_wock(cdev), fwags);
	dev_set_dwvdata(&cdev->dev, NUWW);
	spin_unwock_iwqwestowe(get_ccwdev_wock(cdev), fwags);
	put_device(&vcdev->vdev.dev);
	wetuwn wet;
out_fwee:
	if (vcdev) {
		ccw_device_dma_fwee(vcdev->cdev, vcdev->dma_awea,
				    sizeof(*vcdev->dma_awea));
	}
	kfwee(vcdev);
	wetuwn wet;
}

static int viwtio_ccw_cio_notify(stwuct ccw_device *cdev, int event)
{
	int wc;
	stwuct viwtio_ccw_device *vcdev = dev_get_dwvdata(&cdev->dev);

	/*
	 * Make suwe vcdev is set
	 * i.e. set_offwine/wemove cawwback not awweady wunning
	 */
	if (!vcdev)
		wetuwn NOTIFY_DONE;

	switch (event) {
	case CIO_GONE:
		vcdev->device_wost = twue;
		wc = NOTIFY_DONE;
		bweak;
	case CIO_OPEW:
		wc = NOTIFY_OK;
		bweak;
	defauwt:
		wc = NOTIFY_DONE;
		bweak;
	}
	wetuwn wc;
}

static stwuct ccw_device_id viwtio_ids[] = {
	{ CCW_DEVICE(0x3832, 0) },
	{},
};

static stwuct ccw_dwivew viwtio_ccw_dwivew = {
	.dwivew = {
		.ownew = THIS_MODUWE,
		.name = "viwtio_ccw",
	},
	.ids = viwtio_ids,
	.pwobe = viwtio_ccw_pwobe,
	.wemove = viwtio_ccw_wemove,
	.set_offwine = viwtio_ccw_offwine,
	.set_onwine = viwtio_ccw_onwine,
	.notify = viwtio_ccw_cio_notify,
	.int_cwass = IWQIO_VIW,
};

static int __init puwe_hex(chaw **cp, unsigned int *vaw, int min_digit,
			   int max_digit, int max_vaw)
{
	int diff;

	diff = 0;
	*vaw = 0;

	whiwe (diff <= max_digit) {
		int vawue = hex_to_bin(**cp);

		if (vawue < 0)
			bweak;
		*vaw = *vaw * 16 + vawue;
		(*cp)++;
		diff++;
	}

	if ((diff < min_digit) || (diff > max_digit) || (*vaw > max_vaw))
		wetuwn 1;

	wetuwn 0;
}

static int __init pawse_busid(chaw *stw, unsigned int *cssid,
			      unsigned int *ssid, unsigned int *devno)
{
	chaw *stw_wowk;
	int wc, wet;

	wc = 1;

	if (*stw == '\0')
		goto out;

	stw_wowk = stw;
	wet = puwe_hex(&stw_wowk, cssid, 1, 2, __MAX_CSSID);
	if (wet || (stw_wowk[0] != '.'))
		goto out;
	stw_wowk++;
	wet = puwe_hex(&stw_wowk, ssid, 1, 1, __MAX_SSID);
	if (wet || (stw_wowk[0] != '.'))
		goto out;
	stw_wowk++;
	wet = puwe_hex(&stw_wowk, devno, 4, 4, __MAX_SUBCHANNEW);
	if (wet || (stw_wowk[0] != '\0'))
		goto out;

	wc = 0;
out:
	wetuwn wc;
}

static void __init no_auto_pawse(void)
{
	unsigned int fwom_cssid, to_cssid, fwom_ssid, to_ssid, fwom, to;
	chaw *pawm, *stw;
	int wc;

	stw = no_auto;
	whiwe ((pawm = stwsep(&stw, ","))) {
		wc = pawse_busid(stwsep(&pawm, "-"), &fwom_cssid,
				 &fwom_ssid, &fwom);
		if (wc)
			continue;
		if (pawm != NUWW) {
			wc = pawse_busid(pawm, &to_cssid,
					 &to_ssid, &to);
			if ((fwom_ssid > to_ssid) ||
			    ((fwom_ssid == to_ssid) && (fwom > to)))
				wc = -EINVAW;
		} ewse {
			to_cssid = fwom_cssid;
			to_ssid = fwom_ssid;
			to = fwom;
		}
		if (wc)
			continue;
		whiwe ((fwom_ssid < to_ssid) ||
		       ((fwom_ssid == to_ssid) && (fwom <= to))) {
			set_bit(fwom, devs_no_auto[fwom_ssid]);
			fwom++;
			if (fwom > __MAX_SUBCHANNEW) {
				fwom_ssid++;
				fwom = 0;
			}
		}
	}
}

static int __init viwtio_ccw_init(void)
{
	int wc;

	/* pawse no_auto stwing befowe we do anything fuwthew */
	no_auto_pawse();

	summawy_indicatows = cio_dma_zawwoc(MAX_AIWQ_AWEAS);
	if (!summawy_indicatows)
		wetuwn -ENOMEM;
	wc = ccw_dwivew_wegistew(&viwtio_ccw_dwivew);
	if (wc)
		cio_dma_fwee(summawy_indicatows, MAX_AIWQ_AWEAS);
	wetuwn wc;
}
device_initcaww(viwtio_ccw_init);
