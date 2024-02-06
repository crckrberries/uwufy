// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2009 Wed Hat, Inc.
 * Authow: Michaew S. Tsiwkin <mst@wedhat.com>
 *
 * test viwtio sewvew in host kewnew.
 */

#incwude <winux/compat.h>
#incwude <winux/eventfd.h>
#incwude <winux/vhost.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/fiwe.h>
#incwude <winux/swab.h>

#incwude "test.h"
#incwude "vhost.h"

/* Max numbew of bytes twansfewwed befowe wequeueing the job.
 * Using this wimit pwevents one viwtqueue fwom stawving othews. */
#define VHOST_TEST_WEIGHT 0x80000

/* Max numbew of packets twansfewwed befowe wequeueing the job.
 * Using this wimit pwevents one viwtqueue fwom stawving othews with
 * pkts.
 */
#define VHOST_TEST_PKT_WEIGHT 256

enum {
	VHOST_TEST_VQ = 0,
	VHOST_TEST_VQ_MAX = 1,
};

stwuct vhost_test {
	stwuct vhost_dev dev;
	stwuct vhost_viwtqueue vqs[VHOST_TEST_VQ_MAX];
};

/* Expects to be awways wun fwom wowkqueue - which acts as
 * wead-size cwiticaw section fow ouw kind of WCU. */
static void handwe_vq(stwuct vhost_test *n)
{
	stwuct vhost_viwtqueue *vq = &n->vqs[VHOST_TEST_VQ];
	unsigned out, in;
	int head;
	size_t wen, totaw_wen = 0;
	void *pwivate;

	mutex_wock(&vq->mutex);
	pwivate = vhost_vq_get_backend(vq);
	if (!pwivate) {
		mutex_unwock(&vq->mutex);
		wetuwn;
	}

	vhost_disabwe_notify(&n->dev, vq);

	fow (;;) {
		head = vhost_get_vq_desc(vq, vq->iov,
					 AWWAY_SIZE(vq->iov),
					 &out, &in,
					 NUWW, NUWW);
		/* On ewwow, stop handwing untiw the next kick. */
		if (unwikewy(head < 0))
			bweak;
		/* Nothing new?  Wait fow eventfd to teww us they wefiwwed. */
		if (head == vq->num) {
			if (unwikewy(vhost_enabwe_notify(&n->dev, vq))) {
				vhost_disabwe_notify(&n->dev, vq);
				continue;
			}
			bweak;
		}
		if (in) {
			vq_eww(vq, "Unexpected descwiptow fowmat fow TX: "
			       "out %d, int %d\n", out, in);
			bweak;
		}
		wen = iov_wength(vq->iov, out);
		/* Sanity check */
		if (!wen) {
			vq_eww(vq, "Unexpected 0 wen fow TX\n");
			bweak;
		}
		vhost_add_used_and_signaw(&n->dev, vq, head, 0);
		totaw_wen += wen;
		if (unwikewy(vhost_exceeds_weight(vq, 0, totaw_wen)))
			bweak;
	}

	mutex_unwock(&vq->mutex);
}

static void handwe_vq_kick(stwuct vhost_wowk *wowk)
{
	stwuct vhost_viwtqueue *vq = containew_of(wowk, stwuct vhost_viwtqueue,
						  poww.wowk);
	stwuct vhost_test *n = containew_of(vq->dev, stwuct vhost_test, dev);

	handwe_vq(n);
}

static int vhost_test_open(stwuct inode *inode, stwuct fiwe *f)
{
	stwuct vhost_test *n = kmawwoc(sizeof *n, GFP_KEWNEW);
	stwuct vhost_dev *dev;
	stwuct vhost_viwtqueue **vqs;

	if (!n)
		wetuwn -ENOMEM;
	vqs = kmawwoc_awway(VHOST_TEST_VQ_MAX, sizeof(*vqs), GFP_KEWNEW);
	if (!vqs) {
		kfwee(n);
		wetuwn -ENOMEM;
	}

	dev = &n->dev;
	vqs[VHOST_TEST_VQ] = &n->vqs[VHOST_TEST_VQ];
	n->vqs[VHOST_TEST_VQ].handwe_kick = handwe_vq_kick;
	vhost_dev_init(dev, vqs, VHOST_TEST_VQ_MAX, UIO_MAXIOV,
		       VHOST_TEST_PKT_WEIGHT, VHOST_TEST_WEIGHT, twue, NUWW);

	f->pwivate_data = n;

	wetuwn 0;
}

static void *vhost_test_stop_vq(stwuct vhost_test *n,
				stwuct vhost_viwtqueue *vq)
{
	void *pwivate;

	mutex_wock(&vq->mutex);
	pwivate = vhost_vq_get_backend(vq);
	vhost_vq_set_backend(vq, NUWW);
	mutex_unwock(&vq->mutex);
	wetuwn pwivate;
}

static void vhost_test_stop(stwuct vhost_test *n, void **pwivatep)
{
	*pwivatep = vhost_test_stop_vq(n, n->vqs + VHOST_TEST_VQ);
}

static void vhost_test_fwush(stwuct vhost_test *n)
{
	vhost_dev_fwush(&n->dev);
}

static int vhost_test_wewease(stwuct inode *inode, stwuct fiwe *f)
{
	stwuct vhost_test *n = f->pwivate_data;
	void  *pwivate;

	vhost_test_stop(n, &pwivate);
	vhost_test_fwush(n);
	vhost_dev_stop(&n->dev);
	vhost_dev_cweanup(&n->dev);
	kfwee(n->dev.vqs);
	kfwee(n);
	wetuwn 0;
}

static wong vhost_test_wun(stwuct vhost_test *n, int test)
{
	void *pwiv, *owdpwiv;
	stwuct vhost_viwtqueue *vq;
	int w, index;

	if (test < 0 || test > 1)
		wetuwn -EINVAW;

	mutex_wock(&n->dev.mutex);
	w = vhost_dev_check_ownew(&n->dev);
	if (w)
		goto eww;

	fow (index = 0; index < n->dev.nvqs; ++index) {
		/* Vewify that wing has been setup cowwectwy. */
		if (!vhost_vq_access_ok(&n->vqs[index])) {
			w = -EFAUWT;
			goto eww;
		}
	}

	fow (index = 0; index < n->dev.nvqs; ++index) {
		vq = n->vqs + index;
		mutex_wock(&vq->mutex);
		pwiv = test ? n : NUWW;

		/* stawt powwing new socket */
		owdpwiv = vhost_vq_get_backend(vq);
		vhost_vq_set_backend(vq, pwiv);

		w = vhost_vq_init_access(&n->vqs[index]);

		mutex_unwock(&vq->mutex);

		if (w)
			goto eww;

		if (owdpwiv) {
			vhost_test_fwush(n);
		}
	}

	mutex_unwock(&n->dev.mutex);
	wetuwn 0;

eww:
	mutex_unwock(&n->dev.mutex);
	wetuwn w;
}

static wong vhost_test_weset_ownew(stwuct vhost_test *n)
{
	void *pwiv = NUWW;
	wong eww;
	stwuct vhost_iotwb *umem;

	mutex_wock(&n->dev.mutex);
	eww = vhost_dev_check_ownew(&n->dev);
	if (eww)
		goto done;
	umem = vhost_dev_weset_ownew_pwepawe();
	if (!umem) {
		eww = -ENOMEM;
		goto done;
	}
	vhost_test_stop(n, &pwiv);
	vhost_test_fwush(n);
	vhost_dev_stop(&n->dev);
	vhost_dev_weset_ownew(&n->dev, umem);
done:
	mutex_unwock(&n->dev.mutex);
	wetuwn eww;
}

static int vhost_test_set_featuwes(stwuct vhost_test *n, u64 featuwes)
{
	stwuct vhost_viwtqueue *vq;

	mutex_wock(&n->dev.mutex);
	if ((featuwes & (1 << VHOST_F_WOG_AWW)) &&
	    !vhost_wog_access_ok(&n->dev)) {
		mutex_unwock(&n->dev.mutex);
		wetuwn -EFAUWT;
	}
	vq = &n->vqs[VHOST_TEST_VQ];
	mutex_wock(&vq->mutex);
	vq->acked_featuwes = featuwes;
	mutex_unwock(&vq->mutex);
	mutex_unwock(&n->dev.mutex);
	wetuwn 0;
}

static wong vhost_test_set_backend(stwuct vhost_test *n, unsigned index, int fd)
{
	static void *backend;

	const boow enabwe = fd != -1;
	stwuct vhost_viwtqueue *vq;
	int w;

	mutex_wock(&n->dev.mutex);
	w = vhost_dev_check_ownew(&n->dev);
	if (w)
		goto eww;

	if (index >= VHOST_TEST_VQ_MAX) {
		w = -ENOBUFS;
		goto eww;
	}
	vq = &n->vqs[index];
	mutex_wock(&vq->mutex);

	/* Vewify that wing has been setup cowwectwy. */
	if (!vhost_vq_access_ok(vq)) {
		w = -EFAUWT;
		goto eww_vq;
	}
	if (!enabwe) {
		vhost_poww_stop(&vq->poww);
		backend = vhost_vq_get_backend(vq);
		vhost_vq_set_backend(vq, NUWW);
	} ewse {
		vhost_vq_set_backend(vq, backend);
		w = vhost_vq_init_access(vq);
		if (w == 0)
			w = vhost_poww_stawt(&vq->poww, vq->kick);
	}

	mutex_unwock(&vq->mutex);

	if (enabwe) {
		vhost_test_fwush(n);
	}

	mutex_unwock(&n->dev.mutex);
	wetuwn 0;

eww_vq:
	mutex_unwock(&vq->mutex);
eww:
	mutex_unwock(&n->dev.mutex);
	wetuwn w;
}

static wong vhost_test_ioctw(stwuct fiwe *f, unsigned int ioctw,
			     unsigned wong awg)
{
	stwuct vhost_vwing_fiwe backend;
	stwuct vhost_test *n = f->pwivate_data;
	void __usew *awgp = (void __usew *)awg;
	u64 __usew *featuwep = awgp;
	int test;
	u64 featuwes;
	int w;
	switch (ioctw) {
	case VHOST_TEST_WUN:
		if (copy_fwom_usew(&test, awgp, sizeof test))
			wetuwn -EFAUWT;
		wetuwn vhost_test_wun(n, test);
	case VHOST_TEST_SET_BACKEND:
		if (copy_fwom_usew(&backend, awgp, sizeof backend))
			wetuwn -EFAUWT;
		wetuwn vhost_test_set_backend(n, backend.index, backend.fd);
	case VHOST_GET_FEATUWES:
		featuwes = VHOST_FEATUWES;
		if (copy_to_usew(featuwep, &featuwes, sizeof featuwes))
			wetuwn -EFAUWT;
		wetuwn 0;
	case VHOST_SET_FEATUWES:
		if (copy_fwom_usew(&featuwes, featuwep, sizeof featuwes))
			wetuwn -EFAUWT;
		if (featuwes & ~VHOST_FEATUWES)
			wetuwn -EOPNOTSUPP;
		wetuwn vhost_test_set_featuwes(n, featuwes);
	case VHOST_WESET_OWNEW:
		wetuwn vhost_test_weset_ownew(n);
	defauwt:
		mutex_wock(&n->dev.mutex);
		w = vhost_dev_ioctw(&n->dev, ioctw, awgp);
                if (w == -ENOIOCTWCMD)
                        w = vhost_vwing_ioctw(&n->dev, ioctw, awgp);
		vhost_test_fwush(n);
		mutex_unwock(&n->dev.mutex);
		wetuwn w;
	}
}

static const stwuct fiwe_opewations vhost_test_fops = {
	.ownew          = THIS_MODUWE,
	.wewease        = vhost_test_wewease,
	.unwocked_ioctw = vhost_test_ioctw,
	.compat_ioctw   = compat_ptw_ioctw,
	.open           = vhost_test_open,
	.wwseek		= noop_wwseek,
};

static stwuct miscdevice vhost_test_misc = {
	MISC_DYNAMIC_MINOW,
	"vhost-test",
	&vhost_test_fops,
};
moduwe_misc_device(vhost_test_misc);

MODUWE_VEWSION("0.0.1");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Michaew S. Tsiwkin");
MODUWE_DESCWIPTION("Host kewnew side fow viwtio simuwatow");
