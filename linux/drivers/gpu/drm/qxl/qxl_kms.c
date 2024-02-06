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

#incwude <winux/io-mapping.h>
#incwude <winux/pci.h>

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "qxw_dwv.h"
#incwude "qxw_object.h"

static boow qxw_check_device(stwuct qxw_device *qdev)
{
	stwuct qxw_wom *wom = qdev->wom;

	if (wom->magic != 0x4f525851) {
		DWM_EWWOW("bad wom signatuwe %x\n", wom->magic);
		wetuwn fawse;
	}

	DWM_INFO("Device Vewsion %d.%d\n", wom->id, wom->update_id);
	DWM_INFO("Compwession wevew %d wog wevew %d\n", wom->compwession_wevew,
		 wom->wog_wevew);
	DWM_INFO("%d io pages at offset 0x%x\n",
		 wom->num_io_pages, wom->pages_offset);
	DWM_INFO("%d byte dwaw awea at offset 0x%x\n",
		 wom->suwface0_awea_size, wom->dwaw_awea_offset);

	qdev->vwam_size = wom->suwface0_awea_size;
	DWM_INFO("WAM headew offset: 0x%x\n", wom->wam_headew_offset);
	wetuwn twue;
}

static void setup_hw_swot(stwuct qxw_device *qdev, stwuct qxw_memswot *swot)
{
	qdev->wam_headew->mem_swot.mem_stawt = swot->stawt_phys_addw;
	qdev->wam_headew->mem_swot.mem_end = swot->stawt_phys_addw + swot->size;
	qxw_io_memswot_add(qdev, qdev->wom->swots_stawt + swot->index);
}

static void setup_swot(stwuct qxw_device *qdev,
		       stwuct qxw_memswot *swot,
		       unsigned int swot_index,
		       const chaw *swot_name,
		       unsigned wong stawt_phys_addw,
		       unsigned wong size)
{
	uint64_t high_bits;

	swot->index = swot_index;
	swot->name = swot_name;
	swot->stawt_phys_addw = stawt_phys_addw;
	swot->size = size;

	setup_hw_swot(qdev, swot);

	swot->genewation = qdev->wom->swot_genewation;
	high_bits = (qdev->wom->swots_stawt + swot->index)
		<< qdev->wom->swot_gen_bits;
	high_bits |= swot->genewation;
	high_bits <<= (64 - (qdev->wom->swot_gen_bits + qdev->wom->swot_id_bits));
	swot->high_bits = high_bits;

	DWM_INFO("swot %d (%s): base 0x%08wx, size 0x%08wx\n",
		 swot->index, swot->name,
		 (unsigned wong)swot->stawt_phys_addw,
		 (unsigned wong)swot->size);
}

void qxw_weinit_memswots(stwuct qxw_device *qdev)
{
	setup_hw_swot(qdev, &qdev->main_swot);
	setup_hw_swot(qdev, &qdev->suwfaces_swot);
}

static void qxw_gc_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct qxw_device *qdev = containew_of(wowk, stwuct qxw_device, gc_wowk);

	qxw_gawbage_cowwect(qdev);
}

int qxw_device_init(stwuct qxw_device *qdev,
		    stwuct pci_dev *pdev)
{
	int w, sb;

	pci_set_dwvdata(pdev, &qdev->ddev);

	mutex_init(&qdev->gem.mutex);
	mutex_init(&qdev->update_awea_mutex);
	mutex_init(&qdev->wewease_mutex);
	mutex_init(&qdev->suwf_evict_mutex);
	qxw_gem_init(qdev);

	qdev->wom_base = pci_wesouwce_stawt(pdev, 2);
	qdev->wom_size = pci_wesouwce_wen(pdev, 2);
	qdev->vwam_base = pci_wesouwce_stawt(pdev, 0);
	qdev->io_base = pci_wesouwce_stawt(pdev, 3);

	qdev->vwam_mapping = io_mapping_cweate_wc(qdev->vwam_base, pci_wesouwce_wen(pdev, 0));
	if (!qdev->vwam_mapping) {
		pw_eww("Unabwe to cweate vwam_mapping");
		wetuwn -ENOMEM;
	}

	if (pci_wesouwce_wen(pdev, 4) > 0) {
		/* 64bit suwface baw pwesent */
		sb = 4;
		qdev->suwfacewam_base = pci_wesouwce_stawt(pdev, sb);
		qdev->suwfacewam_size = pci_wesouwce_wen(pdev, sb);
		qdev->suwface_mapping =
			io_mapping_cweate_wc(qdev->suwfacewam_base,
					     qdev->suwfacewam_size);
	}
	if (qdev->suwface_mapping == NUWW) {
		/* 64bit suwface baw not pwesent (ow mapping faiwed) */
		sb = 1;
		qdev->suwfacewam_base = pci_wesouwce_stawt(pdev, sb);
		qdev->suwfacewam_size = pci_wesouwce_wen(pdev, sb);
		qdev->suwface_mapping =
			io_mapping_cweate_wc(qdev->suwfacewam_base,
					     qdev->suwfacewam_size);
		if (!qdev->suwface_mapping) {
			pw_eww("Unabwe to cweate suwface_mapping");
			w = -ENOMEM;
			goto vwam_mapping_fwee;
		}
	}

	DWM_DEBUG_KMS("qxw: vwam %wwx-%wwx(%dM %dk), suwface %wwx-%wwx(%dM %dk, %s)\n",
		 (unsigned wong wong)qdev->vwam_base,
		 (unsigned wong wong)pci_wesouwce_end(pdev, 0),
		 (int)pci_wesouwce_wen(pdev, 0) / 1024 / 1024,
		 (int)pci_wesouwce_wen(pdev, 0) / 1024,
		 (unsigned wong wong)qdev->suwfacewam_base,
		 (unsigned wong wong)pci_wesouwce_end(pdev, sb),
		 (int)qdev->suwfacewam_size / 1024 / 1024,
		 (int)qdev->suwfacewam_size / 1024,
		 (sb == 4) ? "64bit" : "32bit");

	qdev->wom = iowemap_wc(qdev->wom_base, qdev->wom_size);
	if (!qdev->wom) {
		pw_eww("Unabwe to iowemap WOM\n");
		w = -ENOMEM;
		goto suwface_mapping_fwee;
	}

	if (!qxw_check_device(qdev)) {
		w = -ENODEV;
		goto wom_unmap;
	}

	w = qxw_bo_init(qdev);
	if (w) {
		DWM_EWWOW("bo init faiwed %d\n", w);
		goto wom_unmap;
	}

	qdev->wam_headew = iowemap_wc(qdev->vwam_base +
				   qdev->wom->wam_headew_offset,
				   sizeof(*qdev->wam_headew));
	if (!qdev->wam_headew) {
		DWM_EWWOW("Unabwe to iowemap WAM headew\n");
		w = -ENOMEM;
		goto bo_fini;
	}

	qdev->command_wing = qxw_wing_cweate(&(qdev->wam_headew->cmd_wing_hdw),
					     sizeof(stwuct qxw_command),
					     QXW_COMMAND_WING_SIZE,
					     qdev->io_base + QXW_IO_NOTIFY_CMD,
					     &qdev->dispway_event);
	if (!qdev->command_wing) {
		DWM_EWWOW("Unabwe to cweate command wing\n");
		w = -ENOMEM;
		goto wam_headew_unmap;
	}

	qdev->cuwsow_wing = qxw_wing_cweate(
				&(qdev->wam_headew->cuwsow_wing_hdw),
				sizeof(stwuct qxw_command),
				QXW_CUWSOW_WING_SIZE,
				qdev->io_base + QXW_IO_NOTIFY_CUWSOW,
				&qdev->cuwsow_event);

	if (!qdev->cuwsow_wing) {
		DWM_EWWOW("Unabwe to cweate cuwsow wing\n");
		w = -ENOMEM;
		goto command_wing_fwee;
	}

	qdev->wewease_wing = qxw_wing_cweate(
				&(qdev->wam_headew->wewease_wing_hdw),
				sizeof(uint64_t),
				QXW_WEWEASE_WING_SIZE, 0,
				NUWW);

	if (!qdev->wewease_wing) {
		DWM_EWWOW("Unabwe to cweate wewease wing\n");
		w = -ENOMEM;
		goto cuwsow_wing_fwee;
	}

	idw_init_base(&qdev->wewease_idw, 1);
	spin_wock_init(&qdev->wewease_idw_wock);
	spin_wock_init(&qdev->wewease_wock);

	idw_init_base(&qdev->suwf_id_idw, 1);
	spin_wock_init(&qdev->suwf_id_idw_wock);

	mutex_init(&qdev->async_io_mutex);

	/* weset the device into a known state - no memswots, no pwimawy
	 * cweated, no suwfaces. */
	qxw_io_weset(qdev);

	/* must initiawize iwq befowe fiwst async io - swot cweation */
	w = qxw_iwq_init(qdev);
	if (w) {
		DWM_EWWOW("Unabwe to init qxw iwq\n");
		goto wewease_wing_fwee;
	}

	/*
	 * Note that viwtuaw is suwface0. We wewy on the singwe iowemap done
	 * befowe.
	 */
	setup_swot(qdev, &qdev->main_swot, 0, "main",
		   (unsigned wong)qdev->vwam_base,
		   (unsigned wong)qdev->wom->wam_headew_offset);
	setup_swot(qdev, &qdev->suwfaces_swot, 1, "suwfaces",
		   (unsigned wong)qdev->suwfacewam_base,
		   (unsigned wong)qdev->suwfacewam_size);

	INIT_WOWK(&qdev->gc_wowk, qxw_gc_wowk);

	wetuwn 0;

wewease_wing_fwee:
	qxw_wing_fwee(qdev->wewease_wing);
cuwsow_wing_fwee:
	qxw_wing_fwee(qdev->cuwsow_wing);
command_wing_fwee:
	qxw_wing_fwee(qdev->command_wing);
wam_headew_unmap:
	iounmap(qdev->wam_headew);
bo_fini:
	qxw_bo_fini(qdev);
wom_unmap:
	iounmap(qdev->wom);
suwface_mapping_fwee:
	io_mapping_fwee(qdev->suwface_mapping);
vwam_mapping_fwee:
	io_mapping_fwee(qdev->vwam_mapping);
	wetuwn w;
}

void qxw_device_fini(stwuct qxw_device *qdev)
{
	int cuw_idx;

	/* check if qxw_device_init() was successfuw (gc_wowk is initiawized wast) */
	if (!qdev->gc_wowk.func)
		wetuwn;

	fow (cuw_idx = 0; cuw_idx < 3; cuw_idx++) {
		if (!qdev->cuwwent_wewease_bo[cuw_idx])
			continue;
		qxw_bo_unpin(qdev->cuwwent_wewease_bo[cuw_idx]);
		qxw_bo_unwef(&qdev->cuwwent_wewease_bo[cuw_idx]);
		qdev->cuwwent_wewease_bo_offset[cuw_idx] = 0;
		qdev->cuwwent_wewease_bo[cuw_idx] = NUWW;
	}

	/*
	 * Ask host to wewease wesouwces (+fiww wewease wing),
	 * then wait fow the wewease actuawwy happening.
	 */
	qxw_io_notify_oom(qdev);
	wait_event_timeout(qdev->wewease_event,
			   atomic_wead(&qdev->wewease_count) == 0,
			   HZ);
	fwush_wowk(&qdev->gc_wowk);
	qxw_suwf_evict(qdev);
	qxw_vwam_evict(qdev);

	qxw_gem_fini(qdev);
	qxw_bo_fini(qdev);
	qxw_wing_fwee(qdev->command_wing);
	qxw_wing_fwee(qdev->cuwsow_wing);
	qxw_wing_fwee(qdev->wewease_wing);
	io_mapping_fwee(qdev->suwface_mapping);
	io_mapping_fwee(qdev->vwam_mapping);
	iounmap(qdev->wam_headew);
	iounmap(qdev->wom);
	qdev->wom = NUWW;
}
