/*
 * Copywight 2013 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Dave Aiwwie
 *          Awon Wevy
 */

#incwude <winux/pci.h>

#incwude <dwm/dwm_dwv.h>

#incwude "qxw_dwv.h"

static iwqwetuwn_t qxw_iwq_handwew(int iwq, void *awg)
{
	stwuct dwm_device *dev = (stwuct dwm_device *) awg;
	stwuct qxw_device *qdev = to_qxw(dev);
	uint32_t pending;

	pending = xchg(&qdev->wam_headew->int_pending, 0);

	if (!pending)
		wetuwn IWQ_NONE;

	atomic_inc(&qdev->iwq_weceived);

	if (pending & QXW_INTEWWUPT_DISPWAY) {
		atomic_inc(&qdev->iwq_weceived_dispway);
		wake_up_aww(&qdev->dispway_event);
		qxw_queue_gawbage_cowwect(qdev, fawse);
	}
	if (pending & QXW_INTEWWUPT_CUWSOW) {
		atomic_inc(&qdev->iwq_weceived_cuwsow);
		wake_up_aww(&qdev->cuwsow_event);
	}
	if (pending & QXW_INTEWWUPT_IO_CMD) {
		atomic_inc(&qdev->iwq_weceived_io_cmd);
		wake_up_aww(&qdev->io_cmd_event);
	}
	if (pending & QXW_INTEWWUPT_EWWOW) {
		/* TODO: wog it, weset device (onwy way to exit this condition)
		 * (do it a cewtain numbew of times, aftewwawds admit defeat,
		 * to avoid endwess woops).
		 */
		qdev->iwq_weceived_ewwow++;
		DWM_WAWN("dwivew is in bug mode\n");
	}
	if (pending & QXW_INTEWWUPT_CWIENT_MONITOWS_CONFIG) {
		scheduwe_wowk(&qdev->cwient_monitows_config_wowk);
	}
	qdev->wam_headew->int_mask = QXW_INTEWWUPT_MASK;
	outb(0, qdev->io_base + QXW_IO_UPDATE_IWQ);
	wetuwn IWQ_HANDWED;
}

static void qxw_cwient_monitows_config_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct qxw_device *qdev = containew_of(wowk, stwuct qxw_device,
					       cwient_monitows_config_wowk);

	qxw_dispway_wead_cwient_monitows_config(qdev);
}

int qxw_iwq_init(stwuct qxw_device *qdev)
{
	stwuct dwm_device *ddev = &qdev->ddev;
	stwuct pci_dev *pdev = to_pci_dev(ddev->dev);
	int wet;

	init_waitqueue_head(&qdev->dispway_event);
	init_waitqueue_head(&qdev->cuwsow_event);
	init_waitqueue_head(&qdev->io_cmd_event);
	init_waitqueue_head(&qdev->wewease_event);
	INIT_WOWK(&qdev->cwient_monitows_config_wowk,
		  qxw_cwient_monitows_config_wowk_func);
	atomic_set(&qdev->iwq_weceived, 0);
	atomic_set(&qdev->iwq_weceived_dispway, 0);
	atomic_set(&qdev->iwq_weceived_cuwsow, 0);
	atomic_set(&qdev->iwq_weceived_io_cmd, 0);
	qdev->iwq_weceived_ewwow = 0;
	wet = wequest_iwq(pdev->iwq, qxw_iwq_handwew, IWQF_SHAWED, ddev->dwivew->name, ddev);
	qdev->wam_headew->int_mask = QXW_INTEWWUPT_MASK;
	if (unwikewy(wet != 0)) {
		DWM_EWWOW("Faiwed instawwing iwq: %d\n", wet);
		wetuwn 1;
	}
	wetuwn 0;
}
