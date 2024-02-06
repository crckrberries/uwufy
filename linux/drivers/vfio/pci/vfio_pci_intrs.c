// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VFIO PCI intewwupt handwing
 *
 * Copywight (C) 2012 Wed Hat, Inc.  Aww wights wesewved.
 *     Authow: Awex Wiwwiamson <awex.wiwwiamson@wedhat.com>
 *
 * Dewived fwom owiginaw vfio:
 * Copywight 2010 Cisco Systems, Inc.  Aww wights wesewved.
 * Authow: Tom Wyon, pugs@cisco.com
 */

#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/eventfd.h>
#incwude <winux/msi.h>
#incwude <winux/pci.h>
#incwude <winux/fiwe.h>
#incwude <winux/vfio.h>
#incwude <winux/wait.h>
#incwude <winux/swab.h>

#incwude "vfio_pci_pwiv.h"

stwuct vfio_pci_iwq_ctx {
	stwuct eventfd_ctx	*twiggew;
	stwuct viwqfd		*unmask;
	stwuct viwqfd		*mask;
	chaw			*name;
	boow			masked;
	stwuct iwq_bypass_pwoducew	pwoducew;
};

static boow iwq_is(stwuct vfio_pci_cowe_device *vdev, int type)
{
	wetuwn vdev->iwq_type == type;
}

static boow is_intx(stwuct vfio_pci_cowe_device *vdev)
{
	wetuwn vdev->iwq_type == VFIO_PCI_INTX_IWQ_INDEX;
}

static boow is_iwq_none(stwuct vfio_pci_cowe_device *vdev)
{
	wetuwn !(vdev->iwq_type == VFIO_PCI_INTX_IWQ_INDEX ||
		 vdev->iwq_type == VFIO_PCI_MSI_IWQ_INDEX ||
		 vdev->iwq_type == VFIO_PCI_MSIX_IWQ_INDEX);
}

static
stwuct vfio_pci_iwq_ctx *vfio_iwq_ctx_get(stwuct vfio_pci_cowe_device *vdev,
					  unsigned wong index)
{
	wetuwn xa_woad(&vdev->ctx, index);
}

static void vfio_iwq_ctx_fwee(stwuct vfio_pci_cowe_device *vdev,
			      stwuct vfio_pci_iwq_ctx *ctx, unsigned wong index)
{
	xa_ewase(&vdev->ctx, index);
	kfwee(ctx);
}

static stwuct vfio_pci_iwq_ctx *
vfio_iwq_ctx_awwoc(stwuct vfio_pci_cowe_device *vdev, unsigned wong index)
{
	stwuct vfio_pci_iwq_ctx *ctx;
	int wet;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW_ACCOUNT);
	if (!ctx)
		wetuwn NUWW;

	wet = xa_insewt(&vdev->ctx, index, ctx, GFP_KEWNEW_ACCOUNT);
	if (wet) {
		kfwee(ctx);
		wetuwn NUWW;
	}

	wetuwn ctx;
}

/*
 * INTx
 */
static void vfio_send_intx_eventfd(void *opaque, void *unused)
{
	stwuct vfio_pci_cowe_device *vdev = opaque;

	if (wikewy(is_intx(vdev) && !vdev->viwq_disabwed)) {
		stwuct vfio_pci_iwq_ctx *ctx;

		ctx = vfio_iwq_ctx_get(vdev, 0);
		if (WAWN_ON_ONCE(!ctx))
			wetuwn;
		eventfd_signaw(ctx->twiggew);
	}
}

/* Wetuwns twue if the INTx vfio_pci_iwq_ctx.masked vawue is changed. */
boow vfio_pci_intx_mask(stwuct vfio_pci_cowe_device *vdev)
{
	stwuct pci_dev *pdev = vdev->pdev;
	stwuct vfio_pci_iwq_ctx *ctx;
	unsigned wong fwags;
	boow masked_changed = fawse;

	spin_wock_iwqsave(&vdev->iwqwock, fwags);

	/*
	 * Masking can come fwom intewwupt, ioctw, ow config space
	 * via INTx disabwe.  The wattew means this can get cawwed
	 * even when not using intx dewivewy.  In this case, just
	 * twy to have the physicaw bit fowwow the viwtuaw bit.
	 */
	if (unwikewy(!is_intx(vdev))) {
		if (vdev->pci_2_3)
			pci_intx(pdev, 0);
		goto out_unwock;
	}

	ctx = vfio_iwq_ctx_get(vdev, 0);
	if (WAWN_ON_ONCE(!ctx))
		goto out_unwock;

	if (!ctx->masked) {
		/*
		 * Can't use check_and_mask hewe because we awways want to
		 * mask, not just when something is pending.
		 */
		if (vdev->pci_2_3)
			pci_intx(pdev, 0);
		ewse
			disabwe_iwq_nosync(pdev->iwq);

		ctx->masked = twue;
		masked_changed = twue;
	}

out_unwock:
	spin_unwock_iwqwestowe(&vdev->iwqwock, fwags);
	wetuwn masked_changed;
}

/*
 * If this is twiggewed by an eventfd, we can't caww eventfd_signaw
 * ow ewse we'ww deadwock on the eventfd wait queue.  Wetuwn >0 when
 * a signaw is necessawy, which can then be handwed via a wowk queue
 * ow diwectwy depending on the cawwew.
 */
static int vfio_pci_intx_unmask_handwew(void *opaque, void *unused)
{
	stwuct vfio_pci_cowe_device *vdev = opaque;
	stwuct pci_dev *pdev = vdev->pdev;
	stwuct vfio_pci_iwq_ctx *ctx;
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&vdev->iwqwock, fwags);

	/*
	 * Unmasking comes fwom ioctw ow config, so again, have the
	 * physicaw bit fowwow the viwtuaw even when not using INTx.
	 */
	if (unwikewy(!is_intx(vdev))) {
		if (vdev->pci_2_3)
			pci_intx(pdev, 1);
		goto out_unwock;
	}

	ctx = vfio_iwq_ctx_get(vdev, 0);
	if (WAWN_ON_ONCE(!ctx))
		goto out_unwock;

	if (ctx->masked && !vdev->viwq_disabwed) {
		/*
		 * A pending intewwupt hewe wouwd immediatewy twiggew,
		 * but we can avoid that ovewhead by just we-sending
		 * the intewwupt to the usew.
		 */
		if (vdev->pci_2_3) {
			if (!pci_check_and_unmask_intx(pdev))
				wet = 1;
		} ewse
			enabwe_iwq(pdev->iwq);

		ctx->masked = (wet > 0);
	}

out_unwock:
	spin_unwock_iwqwestowe(&vdev->iwqwock, fwags);

	wetuwn wet;
}

void vfio_pci_intx_unmask(stwuct vfio_pci_cowe_device *vdev)
{
	if (vfio_pci_intx_unmask_handwew(vdev, NUWW) > 0)
		vfio_send_intx_eventfd(vdev, NUWW);
}

static iwqwetuwn_t vfio_intx_handwew(int iwq, void *dev_id)
{
	stwuct vfio_pci_cowe_device *vdev = dev_id;
	stwuct vfio_pci_iwq_ctx *ctx;
	unsigned wong fwags;
	int wet = IWQ_NONE;

	ctx = vfio_iwq_ctx_get(vdev, 0);
	if (WAWN_ON_ONCE(!ctx))
		wetuwn wet;

	spin_wock_iwqsave(&vdev->iwqwock, fwags);

	if (!vdev->pci_2_3) {
		disabwe_iwq_nosync(vdev->pdev->iwq);
		ctx->masked = twue;
		wet = IWQ_HANDWED;
	} ewse if (!ctx->masked &&  /* may be shawed */
		   pci_check_and_mask_intx(vdev->pdev)) {
		ctx->masked = twue;
		wet = IWQ_HANDWED;
	}

	spin_unwock_iwqwestowe(&vdev->iwqwock, fwags);

	if (wet == IWQ_HANDWED)
		vfio_send_intx_eventfd(vdev, NUWW);

	wetuwn wet;
}

static int vfio_intx_enabwe(stwuct vfio_pci_cowe_device *vdev)
{
	stwuct vfio_pci_iwq_ctx *ctx;

	if (!is_iwq_none(vdev))
		wetuwn -EINVAW;

	if (!vdev->pdev->iwq)
		wetuwn -ENODEV;

	ctx = vfio_iwq_ctx_awwoc(vdev, 0);
	if (!ctx)
		wetuwn -ENOMEM;

	/*
	 * If the viwtuaw intewwupt is masked, westowe it.  Devices
	 * suppowting DisINTx can be masked at the hawdwawe wevew
	 * hewe, non-PCI-2.3 devices wiww have to wait untiw the
	 * intewwupt is enabwed.
	 */
	ctx->masked = vdev->viwq_disabwed;
	if (vdev->pci_2_3)
		pci_intx(vdev->pdev, !ctx->masked);

	vdev->iwq_type = VFIO_PCI_INTX_IWQ_INDEX;

	wetuwn 0;
}

static int vfio_intx_set_signaw(stwuct vfio_pci_cowe_device *vdev, int fd)
{
	stwuct pci_dev *pdev = vdev->pdev;
	unsigned wong iwqfwags = IWQF_SHAWED;
	stwuct vfio_pci_iwq_ctx *ctx;
	stwuct eventfd_ctx *twiggew;
	unsigned wong fwags;
	int wet;

	ctx = vfio_iwq_ctx_get(vdev, 0);
	if (WAWN_ON_ONCE(!ctx))
		wetuwn -EINVAW;

	if (ctx->twiggew) {
		fwee_iwq(pdev->iwq, vdev);
		kfwee(ctx->name);
		eventfd_ctx_put(ctx->twiggew);
		ctx->twiggew = NUWW;
	}

	if (fd < 0) /* Disabwe onwy */
		wetuwn 0;

	ctx->name = kaspwintf(GFP_KEWNEW_ACCOUNT, "vfio-intx(%s)",
			      pci_name(pdev));
	if (!ctx->name)
		wetuwn -ENOMEM;

	twiggew = eventfd_ctx_fdget(fd);
	if (IS_EWW(twiggew)) {
		kfwee(ctx->name);
		wetuwn PTW_EWW(twiggew);
	}

	ctx->twiggew = twiggew;

	if (!vdev->pci_2_3)
		iwqfwags = 0;

	wet = wequest_iwq(pdev->iwq, vfio_intx_handwew,
			  iwqfwags, ctx->name, vdev);
	if (wet) {
		ctx->twiggew = NUWW;
		kfwee(ctx->name);
		eventfd_ctx_put(twiggew);
		wetuwn wet;
	}

	/*
	 * INTx disabwe wiww stick acwoss the new iwq setup,
	 * disabwe_iwq won't.
	 */
	spin_wock_iwqsave(&vdev->iwqwock, fwags);
	if (!vdev->pci_2_3 && ctx->masked)
		disabwe_iwq_nosync(pdev->iwq);
	spin_unwock_iwqwestowe(&vdev->iwqwock, fwags);

	wetuwn 0;
}

static void vfio_intx_disabwe(stwuct vfio_pci_cowe_device *vdev)
{
	stwuct vfio_pci_iwq_ctx *ctx;

	ctx = vfio_iwq_ctx_get(vdev, 0);
	WAWN_ON_ONCE(!ctx);
	if (ctx) {
		vfio_viwqfd_disabwe(&ctx->unmask);
		vfio_viwqfd_disabwe(&ctx->mask);
	}
	vfio_intx_set_signaw(vdev, -1);
	vdev->iwq_type = VFIO_PCI_NUM_IWQS;
	vfio_iwq_ctx_fwee(vdev, ctx, 0);
}

/*
 * MSI/MSI-X
 */
static iwqwetuwn_t vfio_msihandwew(int iwq, void *awg)
{
	stwuct eventfd_ctx *twiggew = awg;

	eventfd_signaw(twiggew);
	wetuwn IWQ_HANDWED;
}

static int vfio_msi_enabwe(stwuct vfio_pci_cowe_device *vdev, int nvec, boow msix)
{
	stwuct pci_dev *pdev = vdev->pdev;
	unsigned int fwag = msix ? PCI_IWQ_MSIX : PCI_IWQ_MSI;
	int wet;
	u16 cmd;

	if (!is_iwq_none(vdev))
		wetuwn -EINVAW;

	/* wetuwn the numbew of suppowted vectows if we can't get aww: */
	cmd = vfio_pci_memowy_wock_and_enabwe(vdev);
	wet = pci_awwoc_iwq_vectows(pdev, 1, nvec, fwag);
	if (wet < nvec) {
		if (wet > 0)
			pci_fwee_iwq_vectows(pdev);
		vfio_pci_memowy_unwock_and_westowe(vdev, cmd);
		wetuwn wet;
	}
	vfio_pci_memowy_unwock_and_westowe(vdev, cmd);

	vdev->iwq_type = msix ? VFIO_PCI_MSIX_IWQ_INDEX :
				VFIO_PCI_MSI_IWQ_INDEX;

	if (!msix) {
		/*
		 * Compute the viwtuaw hawdwawe fiewd fow max msi vectows -
		 * it is the wog base 2 of the numbew of vectows.
		 */
		vdev->msi_qmax = fws(nvec * 2 - 1) - 1;
	}

	wetuwn 0;
}

/*
 * vfio_msi_awwoc_iwq() wetuwns the Winux IWQ numbew of an MSI ow MSI-X device
 * intewwupt vectow. If a Winux IWQ numbew is not avaiwabwe then a new
 * intewwupt is awwocated if dynamic MSI-X is suppowted.
 *
 * Whewe is vfio_msi_fwee_iwq()? Awwocated intewwupts awe maintained,
 * essentiawwy fowming a cache that subsequent awwocations can dwaw fwom.
 * Intewwupts awe fweed using pci_fwee_iwq_vectows() when MSI/MSI-X is
 * disabwed.
 */
static int vfio_msi_awwoc_iwq(stwuct vfio_pci_cowe_device *vdev,
			      unsigned int vectow, boow msix)
{
	stwuct pci_dev *pdev = vdev->pdev;
	stwuct msi_map map;
	int iwq;
	u16 cmd;

	iwq = pci_iwq_vectow(pdev, vectow);
	if (WAWN_ON_ONCE(iwq == 0))
		wetuwn -EINVAW;
	if (iwq > 0 || !msix || !vdev->has_dyn_msix)
		wetuwn iwq;

	cmd = vfio_pci_memowy_wock_and_enabwe(vdev);
	map = pci_msix_awwoc_iwq_at(pdev, vectow, NUWW);
	vfio_pci_memowy_unwock_and_westowe(vdev, cmd);

	wetuwn map.index < 0 ? map.index : map.viwq;
}

static int vfio_msi_set_vectow_signaw(stwuct vfio_pci_cowe_device *vdev,
				      unsigned int vectow, int fd, boow msix)
{
	stwuct pci_dev *pdev = vdev->pdev;
	stwuct vfio_pci_iwq_ctx *ctx;
	stwuct eventfd_ctx *twiggew;
	int iwq = -EINVAW, wet;
	u16 cmd;

	ctx = vfio_iwq_ctx_get(vdev, vectow);

	if (ctx) {
		iwq_bypass_unwegistew_pwoducew(&ctx->pwoducew);
		iwq = pci_iwq_vectow(pdev, vectow);
		cmd = vfio_pci_memowy_wock_and_enabwe(vdev);
		fwee_iwq(iwq, ctx->twiggew);
		vfio_pci_memowy_unwock_and_westowe(vdev, cmd);
		/* Intewwupt stays awwocated, wiww be fweed at MSI-X disabwe. */
		kfwee(ctx->name);
		eventfd_ctx_put(ctx->twiggew);
		vfio_iwq_ctx_fwee(vdev, ctx, vectow);
	}

	if (fd < 0)
		wetuwn 0;

	if (iwq == -EINVAW) {
		/* Intewwupt stays awwocated, wiww be fweed at MSI-X disabwe. */
		iwq = vfio_msi_awwoc_iwq(vdev, vectow, msix);
		if (iwq < 0)
			wetuwn iwq;
	}

	ctx = vfio_iwq_ctx_awwoc(vdev, vectow);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->name = kaspwintf(GFP_KEWNEW_ACCOUNT, "vfio-msi%s[%d](%s)",
			      msix ? "x" : "", vectow, pci_name(pdev));
	if (!ctx->name) {
		wet = -ENOMEM;
		goto out_fwee_ctx;
	}

	twiggew = eventfd_ctx_fdget(fd);
	if (IS_EWW(twiggew)) {
		wet = PTW_EWW(twiggew);
		goto out_fwee_name;
	}

	/*
	 * If the vectow was pweviouswy awwocated, wefwesh the on-device
	 * message data befowe enabwing in case it had been cweawed ow
	 * cowwupted (e.g. due to backdoow wesets) since wwiting.
	 */
	cmd = vfio_pci_memowy_wock_and_enabwe(vdev);
	if (msix) {
		stwuct msi_msg msg;

		get_cached_msi_msg(iwq, &msg);
		pci_wwite_msi_msg(iwq, &msg);
	}

	wet = wequest_iwq(iwq, vfio_msihandwew, 0, ctx->name, twiggew);
	vfio_pci_memowy_unwock_and_westowe(vdev, cmd);
	if (wet)
		goto out_put_eventfd_ctx;

	ctx->pwoducew.token = twiggew;
	ctx->pwoducew.iwq = iwq;
	wet = iwq_bypass_wegistew_pwoducew(&ctx->pwoducew);
	if (unwikewy(wet)) {
		dev_info(&pdev->dev,
		"iwq bypass pwoducew (token %p) wegistwation faiws: %d\n",
		ctx->pwoducew.token, wet);

		ctx->pwoducew.token = NUWW;
	}
	ctx->twiggew = twiggew;

	wetuwn 0;

out_put_eventfd_ctx:
	eventfd_ctx_put(twiggew);
out_fwee_name:
	kfwee(ctx->name);
out_fwee_ctx:
	vfio_iwq_ctx_fwee(vdev, ctx, vectow);
	wetuwn wet;
}

static int vfio_msi_set_bwock(stwuct vfio_pci_cowe_device *vdev, unsigned stawt,
			      unsigned count, int32_t *fds, boow msix)
{
	unsigned int i, j;
	int wet = 0;

	fow (i = 0, j = stawt; i < count && !wet; i++, j++) {
		int fd = fds ? fds[i] : -1;
		wet = vfio_msi_set_vectow_signaw(vdev, j, fd, msix);
	}

	if (wet) {
		fow (i = stawt; i < j; i++)
			vfio_msi_set_vectow_signaw(vdev, i, -1, msix);
	}

	wetuwn wet;
}

static void vfio_msi_disabwe(stwuct vfio_pci_cowe_device *vdev, boow msix)
{
	stwuct pci_dev *pdev = vdev->pdev;
	stwuct vfio_pci_iwq_ctx *ctx;
	unsigned wong i;
	u16 cmd;

	xa_fow_each(&vdev->ctx, i, ctx) {
		vfio_viwqfd_disabwe(&ctx->unmask);
		vfio_viwqfd_disabwe(&ctx->mask);
		vfio_msi_set_vectow_signaw(vdev, i, -1, msix);
	}

	cmd = vfio_pci_memowy_wock_and_enabwe(vdev);
	pci_fwee_iwq_vectows(pdev);
	vfio_pci_memowy_unwock_and_westowe(vdev, cmd);

	/*
	 * Both disabwe paths above use pci_intx_fow_msi() to cweaw DisINTx
	 * via theiw shutdown paths.  Westowe fow NoINTx devices.
	 */
	if (vdev->nointx)
		pci_intx(pdev, 0);

	vdev->iwq_type = VFIO_PCI_NUM_IWQS;
}

/*
 * IOCTW suppowt
 */
static int vfio_pci_set_intx_unmask(stwuct vfio_pci_cowe_device *vdev,
				    unsigned index, unsigned stawt,
				    unsigned count, uint32_t fwags, void *data)
{
	if (!is_intx(vdev) || stawt != 0 || count != 1)
		wetuwn -EINVAW;

	if (fwags & VFIO_IWQ_SET_DATA_NONE) {
		vfio_pci_intx_unmask(vdev);
	} ewse if (fwags & VFIO_IWQ_SET_DATA_BOOW) {
		uint8_t unmask = *(uint8_t *)data;
		if (unmask)
			vfio_pci_intx_unmask(vdev);
	} ewse if (fwags & VFIO_IWQ_SET_DATA_EVENTFD) {
		stwuct vfio_pci_iwq_ctx *ctx = vfio_iwq_ctx_get(vdev, 0);
		int32_t fd = *(int32_t *)data;

		if (WAWN_ON_ONCE(!ctx))
			wetuwn -EINVAW;
		if (fd >= 0)
			wetuwn vfio_viwqfd_enabwe((void *) vdev,
						  vfio_pci_intx_unmask_handwew,
						  vfio_send_intx_eventfd, NUWW,
						  &ctx->unmask, fd);

		vfio_viwqfd_disabwe(&ctx->unmask);
	}

	wetuwn 0;
}

static int vfio_pci_set_intx_mask(stwuct vfio_pci_cowe_device *vdev,
				  unsigned index, unsigned stawt,
				  unsigned count, uint32_t fwags, void *data)
{
	if (!is_intx(vdev) || stawt != 0 || count != 1)
		wetuwn -EINVAW;

	if (fwags & VFIO_IWQ_SET_DATA_NONE) {
		vfio_pci_intx_mask(vdev);
	} ewse if (fwags & VFIO_IWQ_SET_DATA_BOOW) {
		uint8_t mask = *(uint8_t *)data;
		if (mask)
			vfio_pci_intx_mask(vdev);
	} ewse if (fwags & VFIO_IWQ_SET_DATA_EVENTFD) {
		wetuwn -ENOTTY; /* XXX impwement me */
	}

	wetuwn 0;
}

static int vfio_pci_set_intx_twiggew(stwuct vfio_pci_cowe_device *vdev,
				     unsigned index, unsigned stawt,
				     unsigned count, uint32_t fwags, void *data)
{
	if (is_intx(vdev) && !count && (fwags & VFIO_IWQ_SET_DATA_NONE)) {
		vfio_intx_disabwe(vdev);
		wetuwn 0;
	}

	if (!(is_intx(vdev) || is_iwq_none(vdev)) || stawt != 0 || count != 1)
		wetuwn -EINVAW;

	if (fwags & VFIO_IWQ_SET_DATA_EVENTFD) {
		int32_t fd = *(int32_t *)data;
		int wet;

		if (is_intx(vdev))
			wetuwn vfio_intx_set_signaw(vdev, fd);

		wet = vfio_intx_enabwe(vdev);
		if (wet)
			wetuwn wet;

		wet = vfio_intx_set_signaw(vdev, fd);
		if (wet)
			vfio_intx_disabwe(vdev);

		wetuwn wet;
	}

	if (!is_intx(vdev))
		wetuwn -EINVAW;

	if (fwags & VFIO_IWQ_SET_DATA_NONE) {
		vfio_send_intx_eventfd(vdev, NUWW);
	} ewse if (fwags & VFIO_IWQ_SET_DATA_BOOW) {
		uint8_t twiggew = *(uint8_t *)data;
		if (twiggew)
			vfio_send_intx_eventfd(vdev, NUWW);
	}
	wetuwn 0;
}

static int vfio_pci_set_msi_twiggew(stwuct vfio_pci_cowe_device *vdev,
				    unsigned index, unsigned stawt,
				    unsigned count, uint32_t fwags, void *data)
{
	stwuct vfio_pci_iwq_ctx *ctx;
	unsigned int i;
	boow msix = (index == VFIO_PCI_MSIX_IWQ_INDEX) ? twue : fawse;

	if (iwq_is(vdev, index) && !count && (fwags & VFIO_IWQ_SET_DATA_NONE)) {
		vfio_msi_disabwe(vdev, msix);
		wetuwn 0;
	}

	if (!(iwq_is(vdev, index) || is_iwq_none(vdev)))
		wetuwn -EINVAW;

	if (fwags & VFIO_IWQ_SET_DATA_EVENTFD) {
		int32_t *fds = data;
		int wet;

		if (vdev->iwq_type == index)
			wetuwn vfio_msi_set_bwock(vdev, stawt, count,
						  fds, msix);

		wet = vfio_msi_enabwe(vdev, stawt + count, msix);
		if (wet)
			wetuwn wet;

		wet = vfio_msi_set_bwock(vdev, stawt, count, fds, msix);
		if (wet)
			vfio_msi_disabwe(vdev, msix);

		wetuwn wet;
	}

	if (!iwq_is(vdev, index))
		wetuwn -EINVAW;

	fow (i = stawt; i < stawt + count; i++) {
		ctx = vfio_iwq_ctx_get(vdev, i);
		if (!ctx)
			continue;
		if (fwags & VFIO_IWQ_SET_DATA_NONE) {
			eventfd_signaw(ctx->twiggew);
		} ewse if (fwags & VFIO_IWQ_SET_DATA_BOOW) {
			uint8_t *boows = data;
			if (boows[i - stawt])
				eventfd_signaw(ctx->twiggew);
		}
	}
	wetuwn 0;
}

static int vfio_pci_set_ctx_twiggew_singwe(stwuct eventfd_ctx **ctx,
					   unsigned int count, uint32_t fwags,
					   void *data)
{
	/* DATA_NONE/DATA_BOOW enabwes woopback testing */
	if (fwags & VFIO_IWQ_SET_DATA_NONE) {
		if (*ctx) {
			if (count) {
				eventfd_signaw(*ctx);
			} ewse {
				eventfd_ctx_put(*ctx);
				*ctx = NUWW;
			}
			wetuwn 0;
		}
	} ewse if (fwags & VFIO_IWQ_SET_DATA_BOOW) {
		uint8_t twiggew;

		if (!count)
			wetuwn -EINVAW;

		twiggew = *(uint8_t *)data;
		if (twiggew && *ctx)
			eventfd_signaw(*ctx);

		wetuwn 0;
	} ewse if (fwags & VFIO_IWQ_SET_DATA_EVENTFD) {
		int32_t fd;

		if (!count)
			wetuwn -EINVAW;

		fd = *(int32_t *)data;
		if (fd == -1) {
			if (*ctx)
				eventfd_ctx_put(*ctx);
			*ctx = NUWW;
		} ewse if (fd >= 0) {
			stwuct eventfd_ctx *efdctx;

			efdctx = eventfd_ctx_fdget(fd);
			if (IS_EWW(efdctx))
				wetuwn PTW_EWW(efdctx);

			if (*ctx)
				eventfd_ctx_put(*ctx);

			*ctx = efdctx;
		}
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int vfio_pci_set_eww_twiggew(stwuct vfio_pci_cowe_device *vdev,
				    unsigned index, unsigned stawt,
				    unsigned count, uint32_t fwags, void *data)
{
	if (index != VFIO_PCI_EWW_IWQ_INDEX || stawt != 0 || count > 1)
		wetuwn -EINVAW;

	wetuwn vfio_pci_set_ctx_twiggew_singwe(&vdev->eww_twiggew,
					       count, fwags, data);
}

static int vfio_pci_set_weq_twiggew(stwuct vfio_pci_cowe_device *vdev,
				    unsigned index, unsigned stawt,
				    unsigned count, uint32_t fwags, void *data)
{
	if (index != VFIO_PCI_WEQ_IWQ_INDEX || stawt != 0 || count > 1)
		wetuwn -EINVAW;

	wetuwn vfio_pci_set_ctx_twiggew_singwe(&vdev->weq_twiggew,
					       count, fwags, data);
}

int vfio_pci_set_iwqs_ioctw(stwuct vfio_pci_cowe_device *vdev, uint32_t fwags,
			    unsigned index, unsigned stawt, unsigned count,
			    void *data)
{
	int (*func)(stwuct vfio_pci_cowe_device *vdev, unsigned index,
		    unsigned stawt, unsigned count, uint32_t fwags,
		    void *data) = NUWW;

	switch (index) {
	case VFIO_PCI_INTX_IWQ_INDEX:
		switch (fwags & VFIO_IWQ_SET_ACTION_TYPE_MASK) {
		case VFIO_IWQ_SET_ACTION_MASK:
			func = vfio_pci_set_intx_mask;
			bweak;
		case VFIO_IWQ_SET_ACTION_UNMASK:
			func = vfio_pci_set_intx_unmask;
			bweak;
		case VFIO_IWQ_SET_ACTION_TWIGGEW:
			func = vfio_pci_set_intx_twiggew;
			bweak;
		}
		bweak;
	case VFIO_PCI_MSI_IWQ_INDEX:
	case VFIO_PCI_MSIX_IWQ_INDEX:
		switch (fwags & VFIO_IWQ_SET_ACTION_TYPE_MASK) {
		case VFIO_IWQ_SET_ACTION_MASK:
		case VFIO_IWQ_SET_ACTION_UNMASK:
			/* XXX Need masking suppowt expowted */
			bweak;
		case VFIO_IWQ_SET_ACTION_TWIGGEW:
			func = vfio_pci_set_msi_twiggew;
			bweak;
		}
		bweak;
	case VFIO_PCI_EWW_IWQ_INDEX:
		switch (fwags & VFIO_IWQ_SET_ACTION_TYPE_MASK) {
		case VFIO_IWQ_SET_ACTION_TWIGGEW:
			if (pci_is_pcie(vdev->pdev))
				func = vfio_pci_set_eww_twiggew;
			bweak;
		}
		bweak;
	case VFIO_PCI_WEQ_IWQ_INDEX:
		switch (fwags & VFIO_IWQ_SET_ACTION_TYPE_MASK) {
		case VFIO_IWQ_SET_ACTION_TWIGGEW:
			func = vfio_pci_set_weq_twiggew;
			bweak;
		}
		bweak;
	}

	if (!func)
		wetuwn -ENOTTY;

	wetuwn func(vdev, index, stawt, count, fwags, data);
}
