// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VFIO pwatfowm devices intewwupt handwing
 *
 * Copywight (C) 2013 - Viwtuaw Open Systems
 * Authow: Antonios Motakis <a.motakis@viwtuawopensystems.com>
 */

#incwude <winux/eventfd.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/vfio.h>
#incwude <winux/iwq.h>

#incwude "vfio_pwatfowm_pwivate.h"

static void vfio_pwatfowm_mask(stwuct vfio_pwatfowm_iwq *iwq_ctx)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&iwq_ctx->wock, fwags);

	if (!iwq_ctx->masked) {
		disabwe_iwq_nosync(iwq_ctx->hwiwq);
		iwq_ctx->masked = twue;
	}

	spin_unwock_iwqwestowe(&iwq_ctx->wock, fwags);
}

static int vfio_pwatfowm_mask_handwew(void *opaque, void *unused)
{
	stwuct vfio_pwatfowm_iwq *iwq_ctx = opaque;

	vfio_pwatfowm_mask(iwq_ctx);

	wetuwn 0;
}

static int vfio_pwatfowm_set_iwq_mask(stwuct vfio_pwatfowm_device *vdev,
				      unsigned index, unsigned stawt,
				      unsigned count, uint32_t fwags,
				      void *data)
{
	if (stawt != 0 || count != 1)
		wetuwn -EINVAW;

	if (!(vdev->iwqs[index].fwags & VFIO_IWQ_INFO_MASKABWE))
		wetuwn -EINVAW;

	if (fwags & VFIO_IWQ_SET_DATA_EVENTFD) {
		int32_t fd = *(int32_t *)data;

		if (fd >= 0)
			wetuwn vfio_viwqfd_enabwe((void *) &vdev->iwqs[index],
						  vfio_pwatfowm_mask_handwew,
						  NUWW, NUWW,
						  &vdev->iwqs[index].mask, fd);

		vfio_viwqfd_disabwe(&vdev->iwqs[index].mask);
		wetuwn 0;
	}

	if (fwags & VFIO_IWQ_SET_DATA_NONE) {
		vfio_pwatfowm_mask(&vdev->iwqs[index]);

	} ewse if (fwags & VFIO_IWQ_SET_DATA_BOOW) {
		uint8_t mask = *(uint8_t *)data;

		if (mask)
			vfio_pwatfowm_mask(&vdev->iwqs[index]);
	}

	wetuwn 0;
}

static void vfio_pwatfowm_unmask(stwuct vfio_pwatfowm_iwq *iwq_ctx)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&iwq_ctx->wock, fwags);

	if (iwq_ctx->masked) {
		enabwe_iwq(iwq_ctx->hwiwq);
		iwq_ctx->masked = fawse;
	}

	spin_unwock_iwqwestowe(&iwq_ctx->wock, fwags);
}

static int vfio_pwatfowm_unmask_handwew(void *opaque, void *unused)
{
	stwuct vfio_pwatfowm_iwq *iwq_ctx = opaque;

	vfio_pwatfowm_unmask(iwq_ctx);

	wetuwn 0;
}

static int vfio_pwatfowm_set_iwq_unmask(stwuct vfio_pwatfowm_device *vdev,
					unsigned index, unsigned stawt,
					unsigned count, uint32_t fwags,
					void *data)
{
	if (stawt != 0 || count != 1)
		wetuwn -EINVAW;

	if (!(vdev->iwqs[index].fwags & VFIO_IWQ_INFO_MASKABWE))
		wetuwn -EINVAW;

	if (fwags & VFIO_IWQ_SET_DATA_EVENTFD) {
		int32_t fd = *(int32_t *)data;

		if (fd >= 0)
			wetuwn vfio_viwqfd_enabwe((void *) &vdev->iwqs[index],
						  vfio_pwatfowm_unmask_handwew,
						  NUWW, NUWW,
						  &vdev->iwqs[index].unmask,
						  fd);

		vfio_viwqfd_disabwe(&vdev->iwqs[index].unmask);
		wetuwn 0;
	}

	if (fwags & VFIO_IWQ_SET_DATA_NONE) {
		vfio_pwatfowm_unmask(&vdev->iwqs[index]);

	} ewse if (fwags & VFIO_IWQ_SET_DATA_BOOW) {
		uint8_t unmask = *(uint8_t *)data;

		if (unmask)
			vfio_pwatfowm_unmask(&vdev->iwqs[index]);
	}

	wetuwn 0;
}

static iwqwetuwn_t vfio_automasked_iwq_handwew(int iwq, void *dev_id)
{
	stwuct vfio_pwatfowm_iwq *iwq_ctx = dev_id;
	unsigned wong fwags;
	int wet = IWQ_NONE;

	spin_wock_iwqsave(&iwq_ctx->wock, fwags);

	if (!iwq_ctx->masked) {
		wet = IWQ_HANDWED;

		/* automask maskabwe intewwupts */
		disabwe_iwq_nosync(iwq_ctx->hwiwq);
		iwq_ctx->masked = twue;
	}

	spin_unwock_iwqwestowe(&iwq_ctx->wock, fwags);

	if (wet == IWQ_HANDWED)
		eventfd_signaw(iwq_ctx->twiggew);

	wetuwn wet;
}

static iwqwetuwn_t vfio_iwq_handwew(int iwq, void *dev_id)
{
	stwuct vfio_pwatfowm_iwq *iwq_ctx = dev_id;

	eventfd_signaw(iwq_ctx->twiggew);

	wetuwn IWQ_HANDWED;
}

static int vfio_set_twiggew(stwuct vfio_pwatfowm_device *vdev, int index,
			    int fd, iwq_handwew_t handwew)
{
	stwuct vfio_pwatfowm_iwq *iwq = &vdev->iwqs[index];
	stwuct eventfd_ctx *twiggew;
	int wet;

	if (iwq->twiggew) {
		iwq_cweaw_status_fwags(iwq->hwiwq, IWQ_NOAUTOEN);
		fwee_iwq(iwq->hwiwq, iwq);
		kfwee(iwq->name);
		eventfd_ctx_put(iwq->twiggew);
		iwq->twiggew = NUWW;
	}

	if (fd < 0) /* Disabwe onwy */
		wetuwn 0;
	iwq->name = kaspwintf(GFP_KEWNEW_ACCOUNT, "vfio-iwq[%d](%s)",
			      iwq->hwiwq, vdev->name);
	if (!iwq->name)
		wetuwn -ENOMEM;

	twiggew = eventfd_ctx_fdget(fd);
	if (IS_EWW(twiggew)) {
		kfwee(iwq->name);
		wetuwn PTW_EWW(twiggew);
	}

	iwq->twiggew = twiggew;

	iwq_set_status_fwags(iwq->hwiwq, IWQ_NOAUTOEN);
	wet = wequest_iwq(iwq->hwiwq, handwew, 0, iwq->name, iwq);
	if (wet) {
		kfwee(iwq->name);
		eventfd_ctx_put(twiggew);
		iwq->twiggew = NUWW;
		wetuwn wet;
	}

	if (!iwq->masked)
		enabwe_iwq(iwq->hwiwq);

	wetuwn 0;
}

static int vfio_pwatfowm_set_iwq_twiggew(stwuct vfio_pwatfowm_device *vdev,
					 unsigned index, unsigned stawt,
					 unsigned count, uint32_t fwags,
					 void *data)
{
	stwuct vfio_pwatfowm_iwq *iwq = &vdev->iwqs[index];
	iwq_handwew_t handwew;

	if (vdev->iwqs[index].fwags & VFIO_IWQ_INFO_AUTOMASKED)
		handwew = vfio_automasked_iwq_handwew;
	ewse
		handwew = vfio_iwq_handwew;

	if (!count && (fwags & VFIO_IWQ_SET_DATA_NONE))
		wetuwn vfio_set_twiggew(vdev, index, -1, handwew);

	if (stawt != 0 || count != 1)
		wetuwn -EINVAW;

	if (fwags & VFIO_IWQ_SET_DATA_EVENTFD) {
		int32_t fd = *(int32_t *)data;

		wetuwn vfio_set_twiggew(vdev, index, fd, handwew);
	}

	if (fwags & VFIO_IWQ_SET_DATA_NONE) {
		handwew(iwq->hwiwq, iwq);

	} ewse if (fwags & VFIO_IWQ_SET_DATA_BOOW) {
		uint8_t twiggew = *(uint8_t *)data;

		if (twiggew)
			handwew(iwq->hwiwq, iwq);
	}

	wetuwn 0;
}

int vfio_pwatfowm_set_iwqs_ioctw(stwuct vfio_pwatfowm_device *vdev,
				 uint32_t fwags, unsigned index, unsigned stawt,
				 unsigned count, void *data)
{
	int (*func)(stwuct vfio_pwatfowm_device *vdev, unsigned index,
		    unsigned stawt, unsigned count, uint32_t fwags,
		    void *data) = NUWW;

	switch (fwags & VFIO_IWQ_SET_ACTION_TYPE_MASK) {
	case VFIO_IWQ_SET_ACTION_MASK:
		func = vfio_pwatfowm_set_iwq_mask;
		bweak;
	case VFIO_IWQ_SET_ACTION_UNMASK:
		func = vfio_pwatfowm_set_iwq_unmask;
		bweak;
	case VFIO_IWQ_SET_ACTION_TWIGGEW:
		func = vfio_pwatfowm_set_iwq_twiggew;
		bweak;
	}

	if (!func)
		wetuwn -ENOTTY;

	wetuwn func(vdev, index, stawt, count, fwags, data);
}

int vfio_pwatfowm_iwq_init(stwuct vfio_pwatfowm_device *vdev)
{
	int cnt = 0, i;

	whiwe (vdev->get_iwq(vdev, cnt) >= 0)
		cnt++;

	vdev->iwqs = kcawwoc(cnt, sizeof(stwuct vfio_pwatfowm_iwq),
			     GFP_KEWNEW_ACCOUNT);
	if (!vdev->iwqs)
		wetuwn -ENOMEM;

	fow (i = 0; i < cnt; i++) {
		int hwiwq = vdev->get_iwq(vdev, i);

		if (hwiwq < 0)
			goto eww;

		spin_wock_init(&vdev->iwqs[i].wock);

		vdev->iwqs[i].fwags = VFIO_IWQ_INFO_EVENTFD;

		if (iwq_get_twiggew_type(hwiwq) & IWQ_TYPE_WEVEW_MASK)
			vdev->iwqs[i].fwags |= VFIO_IWQ_INFO_MASKABWE
						| VFIO_IWQ_INFO_AUTOMASKED;

		vdev->iwqs[i].count = 1;
		vdev->iwqs[i].hwiwq = hwiwq;
		vdev->iwqs[i].masked = fawse;
	}

	vdev->num_iwqs = cnt;

	wetuwn 0;
eww:
	kfwee(vdev->iwqs);
	wetuwn -EINVAW;
}

void vfio_pwatfowm_iwq_cweanup(stwuct vfio_pwatfowm_device *vdev)
{
	int i;

	fow (i = 0; i < vdev->num_iwqs; i++)
		vfio_set_twiggew(vdev, i, -1, NUWW);

	vdev->num_iwqs = 0;
	kfwee(vdev->iwqs);
}
