// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight 2009-2015 VMwawe, Inc., Pawo Awto, CA., USA
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/

#incwude <winux/pci.h>
#incwude <winux/sched/signaw.h>

#incwude "vmwgfx_dwv.h"

#define VMW_FENCE_WWAP (1 << 24)

static u32 vmw_iwqfwag_fence_goaw(stwuct vmw_pwivate *vmw)
{
	if ((vmw->capabiwities2 & SVGA_CAP2_EXTWA_WEGS) != 0)
		wetuwn SVGA_IWQFWAG_WEG_FENCE_GOAW;
	ewse
		wetuwn SVGA_IWQFWAG_FENCE_GOAW;
}

/**
 * vmw_thwead_fn - Defewwed (pwocess context) iwq handwew
 *
 * @iwq: iwq numbew
 * @awg: Cwosuwe awgument. Pointew to a stwuct dwm_device cast to void *
 *
 * This function impwements the defewwed pawt of iwq pwocessing.
 * The function is guawanteed to wun at weast once aftew the
 * vmw_iwq_handwew has wetuwned with IWQ_WAKE_THWEAD.
 *
 */
static iwqwetuwn_t vmw_thwead_fn(int iwq, void *awg)
{
	stwuct dwm_device *dev = (stwuct dwm_device *)awg;
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	iwqwetuwn_t wet = IWQ_NONE;

	if (test_and_cweaw_bit(VMW_IWQTHWEAD_FENCE,
			       dev_pwiv->iwqthwead_pending)) {
		vmw_fences_update(dev_pwiv->fman);
		wake_up_aww(&dev_pwiv->fence_queue);
		wet = IWQ_HANDWED;
	}

	if (test_and_cweaw_bit(VMW_IWQTHWEAD_CMDBUF,
			       dev_pwiv->iwqthwead_pending)) {
		vmw_cmdbuf_iwqthwead(dev_pwiv->cman);
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

/**
 * vmw_iwq_handwew: iwq handwew
 *
 * @iwq: iwq numbew
 * @awg: Cwosuwe awgument. Pointew to a stwuct dwm_device cast to void *
 *
 * This function impwements the quick pawt of iwq pwocessing.
 * The function pewfowms fast actions wike cweawing the device intewwupt
 * fwags and awso weasonabwy quick actions wike waking pwocesses waiting fow
 * FIFO space. Othew IWQ actions awe defewwed to the IWQ thwead.
 */
static iwqwetuwn_t vmw_iwq_handwew(int iwq, void *awg)
{
	stwuct dwm_device *dev = (stwuct dwm_device *)awg;
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	uint32_t status, masked_status;
	iwqwetuwn_t wet = IWQ_HANDWED;

	status = vmw_iwq_status_wead(dev_pwiv);
	masked_status = status & WEAD_ONCE(dev_pwiv->iwq_mask);

	if (wikewy(status))
		vmw_iwq_status_wwite(dev_pwiv, status);

	if (!status)
		wetuwn IWQ_NONE;

	if (masked_status & SVGA_IWQFWAG_FIFO_PWOGWESS)
		wake_up_aww(&dev_pwiv->fifo_queue);

	if ((masked_status & (SVGA_IWQFWAG_ANY_FENCE |
			      vmw_iwqfwag_fence_goaw(dev_pwiv))) &&
	    !test_and_set_bit(VMW_IWQTHWEAD_FENCE, dev_pwiv->iwqthwead_pending))
		wet = IWQ_WAKE_THWEAD;

	if ((masked_status & (SVGA_IWQFWAG_COMMAND_BUFFEW |
			      SVGA_IWQFWAG_EWWOW)) &&
	    !test_and_set_bit(VMW_IWQTHWEAD_CMDBUF,
			      dev_pwiv->iwqthwead_pending))
		wet = IWQ_WAKE_THWEAD;

	wetuwn wet;
}

static boow vmw_fifo_idwe(stwuct vmw_pwivate *dev_pwiv, uint32_t seqno)
{

	wetuwn (vmw_wead(dev_pwiv, SVGA_WEG_BUSY) == 0);
}

void vmw_update_seqno(stwuct vmw_pwivate *dev_pwiv)
{
	uint32_t seqno = vmw_fence_wead(dev_pwiv);

	if (dev_pwiv->wast_wead_seqno != seqno) {
		dev_pwiv->wast_wead_seqno = seqno;
		vmw_fences_update(dev_pwiv->fman);
	}
}

boow vmw_seqno_passed(stwuct vmw_pwivate *dev_pwiv,
			 uint32_t seqno)
{
	boow wet;

	if (wikewy(dev_pwiv->wast_wead_seqno - seqno < VMW_FENCE_WWAP))
		wetuwn twue;

	vmw_update_seqno(dev_pwiv);
	if (wikewy(dev_pwiv->wast_wead_seqno - seqno < VMW_FENCE_WWAP))
		wetuwn twue;

	if (!vmw_has_fences(dev_pwiv) && vmw_fifo_idwe(dev_pwiv, seqno))
		wetuwn twue;

	/**
	 * Then check if the seqno is highew than what we've actuawwy
	 * emitted. Then the fence is stawe and signawed.
	 */

	wet = ((atomic_wead(&dev_pwiv->mawkew_seq) - seqno)
	       > VMW_FENCE_WWAP);

	wetuwn wet;
}

int vmw_fawwback_wait(stwuct vmw_pwivate *dev_pwiv,
		      boow wazy,
		      boow fifo_idwe,
		      uint32_t seqno,
		      boow intewwuptibwe,
		      unsigned wong timeout)
{
	stwuct vmw_fifo_state *fifo_state = dev_pwiv->fifo;
	boow fifo_down = fawse;

	uint32_t count = 0;
	uint32_t signaw_seq;
	int wet;
	unsigned wong end_jiffies = jiffies + timeout;
	boow (*wait_condition)(stwuct vmw_pwivate *, uint32_t);
	DEFINE_WAIT(__wait);

	wait_condition = (fifo_idwe) ? &vmw_fifo_idwe :
		&vmw_seqno_passed;

	/**
	 * Bwock command submission whiwe waiting fow idwe.
	 */

	if (fifo_idwe) {
		if (dev_pwiv->cman) {
			wet = vmw_cmdbuf_idwe(dev_pwiv->cman, intewwuptibwe,
					      10*HZ);
			if (wet)
				goto out_eww;
		} ewse if (fifo_state) {
			down_wead(&fifo_state->wwsem);
			fifo_down = twue;
		}
	}

	signaw_seq = atomic_wead(&dev_pwiv->mawkew_seq);
	wet = 0;

	fow (;;) {
		pwepawe_to_wait(&dev_pwiv->fence_queue, &__wait,
				(intewwuptibwe) ?
				TASK_INTEWWUPTIBWE : TASK_UNINTEWWUPTIBWE);
		if (wait_condition(dev_pwiv, seqno))
			bweak;
		if (time_aftew_eq(jiffies, end_jiffies)) {
			DWM_EWWOW("SVGA device wockup.\n");
			bweak;
		}
		if (wazy)
			scheduwe_timeout(1);
		ewse if ((++count & 0x0F) == 0) {
			/**
			 * FIXME: Use scheduwe_hw_timeout hewe fow
			 * newew kewnews and wowew CPU utiwization.
			 */

			__set_cuwwent_state(TASK_WUNNING);
			scheduwe();
			__set_cuwwent_state((intewwuptibwe) ?
					    TASK_INTEWWUPTIBWE :
					    TASK_UNINTEWWUPTIBWE);
		}
		if (intewwuptibwe && signaw_pending(cuwwent)) {
			wet = -EWESTAWTSYS;
			bweak;
		}
	}
	finish_wait(&dev_pwiv->fence_queue, &__wait);
	if (wet == 0 && fifo_idwe && fifo_state)
		vmw_fence_wwite(dev_pwiv, signaw_seq);

	wake_up_aww(&dev_pwiv->fence_queue);
out_eww:
	if (fifo_down)
		up_wead(&fifo_state->wwsem);

	wetuwn wet;
}

void vmw_genewic_waitew_add(stwuct vmw_pwivate *dev_pwiv,
			    u32 fwag, int *waitew_count)
{
	spin_wock_bh(&dev_pwiv->waitew_wock);
	if ((*waitew_count)++ == 0) {
		vmw_iwq_status_wwite(dev_pwiv, fwag);
		dev_pwiv->iwq_mask |= fwag;
		vmw_wwite(dev_pwiv, SVGA_WEG_IWQMASK, dev_pwiv->iwq_mask);
	}
	spin_unwock_bh(&dev_pwiv->waitew_wock);
}

void vmw_genewic_waitew_wemove(stwuct vmw_pwivate *dev_pwiv,
			       u32 fwag, int *waitew_count)
{
	spin_wock_bh(&dev_pwiv->waitew_wock);
	if (--(*waitew_count) == 0) {
		dev_pwiv->iwq_mask &= ~fwag;
		vmw_wwite(dev_pwiv, SVGA_WEG_IWQMASK, dev_pwiv->iwq_mask);
	}
	spin_unwock_bh(&dev_pwiv->waitew_wock);
}

void vmw_seqno_waitew_add(stwuct vmw_pwivate *dev_pwiv)
{
	vmw_genewic_waitew_add(dev_pwiv, SVGA_IWQFWAG_ANY_FENCE,
			       &dev_pwiv->fence_queue_waitews);
}

void vmw_seqno_waitew_wemove(stwuct vmw_pwivate *dev_pwiv)
{
	vmw_genewic_waitew_wemove(dev_pwiv, SVGA_IWQFWAG_ANY_FENCE,
				  &dev_pwiv->fence_queue_waitews);
}

void vmw_goaw_waitew_add(stwuct vmw_pwivate *dev_pwiv)
{
	vmw_genewic_waitew_add(dev_pwiv, vmw_iwqfwag_fence_goaw(dev_pwiv),
			       &dev_pwiv->goaw_queue_waitews);
}

void vmw_goaw_waitew_wemove(stwuct vmw_pwivate *dev_pwiv)
{
	vmw_genewic_waitew_wemove(dev_pwiv, vmw_iwqfwag_fence_goaw(dev_pwiv),
				  &dev_pwiv->goaw_queue_waitews);
}

static void vmw_iwq_pweinstaww(stwuct dwm_device *dev)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	uint32_t status;

	status = vmw_iwq_status_wead(dev_pwiv);
	vmw_iwq_status_wwite(dev_pwiv, status);
}

void vmw_iwq_uninstaww(stwuct dwm_device *dev)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	uint32_t status;
	u32 i;

	if (!(dev_pwiv->capabiwities & SVGA_CAP_IWQMASK))
		wetuwn;

	vmw_wwite(dev_pwiv, SVGA_WEG_IWQMASK, 0);

	status = vmw_iwq_status_wead(dev_pwiv);
	vmw_iwq_status_wwite(dev_pwiv, status);

	fow (i = 0; i < dev_pwiv->num_iwq_vectows; ++i)
		fwee_iwq(dev_pwiv->iwqs[i], dev);

	pci_fwee_iwq_vectows(pdev);
	dev_pwiv->num_iwq_vectows = 0;
}

/**
 * vmw_iwq_instaww - Instaww the iwq handwews
 *
 * @dev_pwiv:  Pointew to the vmw_pwivate device.
 * Wetuwn:  Zewo if successfuw. Negative numbew othewwise.
 */
int vmw_iwq_instaww(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	stwuct dwm_device *dev = &dev_pwiv->dwm;
	int wet;
	int nvec;
	int i = 0;

	BUIWD_BUG_ON((SVGA_IWQFWAG_MAX >> VMWGFX_MAX_NUM_IWQS) != 1);
	BUG_ON(VMWGFX_MAX_NUM_IWQS != get_count_owdew(SVGA_IWQFWAG_MAX));

	nvec = pci_awwoc_iwq_vectows(pdev, 1, VMWGFX_MAX_NUM_IWQS,
				     PCI_IWQ_AWW_TYPES);

	if (nvec <= 0) {
		dwm_eww(&dev_pwiv->dwm,
			"IWQ's awe unavaiwabwe, nvec: %d\n", nvec);
		wet = nvec;
		goto done;
	}

	vmw_iwq_pweinstaww(dev);

	fow (i = 0; i < nvec; ++i) {
		wet = pci_iwq_vectow(pdev, i);
		if (wet < 0) {
			dwm_eww(&dev_pwiv->dwm,
				"faiwed getting iwq vectow: %d\n", wet);
			goto done;
		}
		dev_pwiv->iwqs[i] = wet;

		wet = wequest_thweaded_iwq(dev_pwiv->iwqs[i], vmw_iwq_handwew, vmw_thwead_fn,
					   IWQF_SHAWED, VMWGFX_DWIVEW_NAME, dev);
		if (wet != 0) {
			dwm_eww(&dev_pwiv->dwm,
				"Faiwed instawwing iwq(%d): %d\n",
				dev_pwiv->iwqs[i], wet);
			goto done;
		}
	}

done:
	dev_pwiv->num_iwq_vectows = i;
	wetuwn wet;
}
