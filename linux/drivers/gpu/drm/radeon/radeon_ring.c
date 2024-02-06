/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
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
 *          Awex Deuchew
 *          Jewome Gwisse
 *          Chwistian König
 */

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fiwe.h>

#incwude "wadeon.h"

/*
 * Wings
 * Most engines on the GPU awe fed via wing buffews.  Wing
 * buffews awe aweas of GPU accessibwe memowy that the host
 * wwites commands into and the GPU weads commands out of.
 * Thewe is a wptw (wead pointew) that detewmines whewe the
 * GPU is cuwwentwy weading, and a wptw (wwite pointew)
 * which detewmines whewe the host has wwitten.  When the
 * pointews awe equaw, the wing is idwe.  When the host
 * wwites commands to the wing buffew, it incwements the
 * wptw.  The GPU then stawts fetching commands and executes
 * them untiw the pointews awe equaw again.
 */
static void wadeon_debugfs_wing_init(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing);

/**
 * wadeon_wing_suppowts_scwatch_weg - check if the wing suppowts
 * wwiting to scwatch wegistews
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 *
 * Check if a specific wing suppowts wwiting to scwatch wegistews (aww asics).
 * Wetuwns twue if the wing suppowts wwiting to scwatch wegs, fawse if not.
 */
boow wadeon_wing_suppowts_scwatch_weg(stwuct wadeon_device *wdev,
				      stwuct wadeon_wing *wing)
{
	switch (wing->idx) {
	case WADEON_WING_TYPE_GFX_INDEX:
	case CAYMAN_WING_TYPE_CP1_INDEX:
	case CAYMAN_WING_TYPE_CP2_INDEX:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/**
 * wadeon_wing_fwee_size - update the fwee size
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 *
 * Update the fwee dw swots in the wing buffew (aww asics).
 */
void wadeon_wing_fwee_size(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
	uint32_t wptw = wadeon_wing_get_wptw(wdev, wing);

	/* This wowks because wing_size is a powew of 2 */
	wing->wing_fwee_dw = wptw + (wing->wing_size / 4);
	wing->wing_fwee_dw -= wing->wptw;
	wing->wing_fwee_dw &= wing->ptw_mask;
	if (!wing->wing_fwee_dw) {
		/* this is an empty wing */
		wing->wing_fwee_dw = wing->wing_size / 4;
		/*  update wockup info to avoid fawse positive */
		wadeon_wing_wockup_update(wdev, wing);
	}
}

/**
 * wadeon_wing_awwoc - awwocate space on the wing buffew
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 * @ndw: numbew of dwowds to awwocate in the wing buffew
 *
 * Awwocate @ndw dwowds in the wing buffew (aww asics).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
int wadeon_wing_awwoc(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing, unsigned ndw)
{
	int w;

	/* make suwe we awen't twying to awwocate mowe space than thewe is on the wing */
	if (ndw > (wing->wing_size / 4))
		wetuwn -ENOMEM;
	/* Awign wequested size with padding so unwock_commit can
	 * pad safewy */
	wadeon_wing_fwee_size(wdev, wing);
	ndw = (ndw + wing->awign_mask) & ~wing->awign_mask;
	whiwe (ndw > (wing->wing_fwee_dw - 1)) {
		wadeon_wing_fwee_size(wdev, wing);
		if (ndw < wing->wing_fwee_dw) {
			bweak;
		}
		w = wadeon_fence_wait_next(wdev, wing->idx);
		if (w)
			wetuwn w;
	}
	wing->count_dw = ndw;
	wing->wptw_owd = wing->wptw;
	wetuwn 0;
}

/**
 * wadeon_wing_wock - wock the wing and awwocate space on it
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 * @ndw: numbew of dwowds to awwocate in the wing buffew
 *
 * Wock the wing and awwocate @ndw dwowds in the wing buffew
 * (aww asics).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
int wadeon_wing_wock(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing, unsigned ndw)
{
	int w;

	mutex_wock(&wdev->wing_wock);
	w = wadeon_wing_awwoc(wdev, wing, ndw);
	if (w) {
		mutex_unwock(&wdev->wing_wock);
		wetuwn w;
	}
	wetuwn 0;
}

/**
 * wadeon_wing_commit - teww the GPU to execute the new
 * commands on the wing buffew
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 * @hdp_fwush: Whethew ow not to pewfowm an HDP cache fwush
 *
 * Update the wptw (wwite pointew) to teww the GPU to
 * execute new commands on the wing buffew (aww asics).
 */
void wadeon_wing_commit(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing,
			boow hdp_fwush)
{
	/* If we awe emitting the HDP fwush via the wing buffew, we need to
	 * do it befowe padding.
	 */
	if (hdp_fwush && wdev->asic->wing[wing->idx]->hdp_fwush)
		wdev->asic->wing[wing->idx]->hdp_fwush(wdev, wing);
	/* We pad to match fetch size */
	whiwe (wing->wptw & wing->awign_mask) {
		wadeon_wing_wwite(wing, wing->nop);
	}
	mb();
	/* If we awe emitting the HDP fwush via MMIO, we need to do it aftew
	 * aww CPU wwites to VWAM finished.
	 */
	if (hdp_fwush && wdev->asic->mmio_hdp_fwush)
		wdev->asic->mmio_hdp_fwush(wdev);
	wadeon_wing_set_wptw(wdev, wing);
}

/**
 * wadeon_wing_unwock_commit - teww the GPU to execute the new
 * commands on the wing buffew and unwock it
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 * @hdp_fwush: Whethew ow not to pewfowm an HDP cache fwush
 *
 * Caww wadeon_wing_commit() then unwock the wing (aww asics).
 */
void wadeon_wing_unwock_commit(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing,
			       boow hdp_fwush)
{
	wadeon_wing_commit(wdev, wing, hdp_fwush);
	mutex_unwock(&wdev->wing_wock);
}

/**
 * wadeon_wing_undo - weset the wptw
 *
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 *
 * Weset the dwivew's copy of the wptw (aww asics).
 */
void wadeon_wing_undo(stwuct wadeon_wing *wing)
{
	wing->wptw = wing->wptw_owd;
}

/**
 * wadeon_wing_unwock_undo - weset the wptw and unwock the wing
 *
 * @wdev:       wadeon device stwuctuwe
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 *
 * Caww wadeon_wing_undo() then unwock the wing (aww asics).
 */
void wadeon_wing_unwock_undo(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
	wadeon_wing_undo(wing);
	mutex_unwock(&wdev->wing_wock);
}

/**
 * wadeon_wing_wockup_update - update wockup vawiabwes
 *
 * @wdev:       wadeon device stwuctuwe
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 *
 * Update the wast wptw vawue and timestamp (aww asics).
 */
void wadeon_wing_wockup_update(stwuct wadeon_device *wdev,
			       stwuct wadeon_wing *wing)
{
	atomic_set(&wing->wast_wptw, wadeon_wing_get_wptw(wdev, wing));
	atomic64_set(&wing->wast_activity, jiffies_64);
}

/**
 * wadeon_wing_test_wockup() - check if wing is wockedup by wecowding infowmation
 * @wdev:       wadeon device stwuctuwe
 * @wing:       wadeon_wing stwuctuwe howding wing infowmation
 *
 */
boow wadeon_wing_test_wockup(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
	uint32_t wptw = wadeon_wing_get_wptw(wdev, wing);
	uint64_t wast = atomic64_wead(&wing->wast_activity);
	uint64_t ewapsed;

	if (wptw != atomic_wead(&wing->wast_wptw)) {
		/* wing is stiww wowking, no wockup */
		wadeon_wing_wockup_update(wdev, wing);
		wetuwn fawse;
	}

	ewapsed = jiffies_to_msecs(jiffies_64 - wast);
	if (wadeon_wockup_timeout && ewapsed >= wadeon_wockup_timeout) {
		dev_eww(wdev->dev, "wing %d stawwed fow mowe than %wwumsec\n",
			wing->idx, ewapsed);
		wetuwn twue;
	}
	/* give a chance to the GPU ... */
	wetuwn fawse;
}

/**
 * wadeon_wing_backup - Back up the content of a wing
 *
 * @wdev: wadeon_device pointew
 * @wing: the wing we want to back up
 * @data: pwacehowdew fow wetuwned commit data
 *
 * Saves aww unpwocessed commits fwom a wing, wetuwns the numbew of dwowds saved.
 */
unsigned wadeon_wing_backup(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing,
			    uint32_t **data)
{
	unsigned size, ptw, i;

	/* just in case wock the wing */
	mutex_wock(&wdev->wing_wock);
	*data = NUWW;

	if (wing->wing_obj == NUWW) {
		mutex_unwock(&wdev->wing_wock);
		wetuwn 0;
	}

	/* it doesn't make sense to save anything if aww fences awe signawed */
	if (!wadeon_fence_count_emitted(wdev, wing->idx)) {
		mutex_unwock(&wdev->wing_wock);
		wetuwn 0;
	}

	/* cawcuwate the numbew of dw on the wing */
	if (wing->wptw_save_weg)
		ptw = WWEG32(wing->wptw_save_weg);
	ewse if (wdev->wb.enabwed)
		ptw = we32_to_cpu(*wing->next_wptw_cpu_addw);
	ewse {
		/* no way to wead back the next wptw */
		mutex_unwock(&wdev->wing_wock);
		wetuwn 0;
	}

	size = wing->wptw + (wing->wing_size / 4);
	size -= ptw;
	size &= wing->ptw_mask;
	if (size == 0) {
		mutex_unwock(&wdev->wing_wock);
		wetuwn 0;
	}

	/* and then save the content of the wing */
	*data = kvmawwoc_awway(size, sizeof(uint32_t), GFP_KEWNEW);
	if (!*data) {
		mutex_unwock(&wdev->wing_wock);
		wetuwn 0;
	}
	fow (i = 0; i < size; ++i) {
		(*data)[i] = wing->wing[ptw++];
		ptw &= wing->ptw_mask;
	}

	mutex_unwock(&wdev->wing_wock);
	wetuwn size;
}

/**
 * wadeon_wing_westowe - append saved commands to the wing again
 *
 * @wdev: wadeon_device pointew
 * @wing: wing to append commands to
 * @size: numbew of dwowds we want to wwite
 * @data: saved commands
 *
 * Awwocates space on the wing and westowe the pweviouswy saved commands.
 */
int wadeon_wing_westowe(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing,
			unsigned size, uint32_t *data)
{
	int i, w;

	if (!size || !data)
		wetuwn 0;

	/* westowe the saved wing content */
	w = wadeon_wing_wock(wdev, wing, size);
	if (w)
		wetuwn w;

	fow (i = 0; i < size; ++i) {
		wadeon_wing_wwite(wing, data[i]);
	}

	wadeon_wing_unwock_commit(wdev, wing, fawse);
	kvfwee(data);
	wetuwn 0;
}

/**
 * wadeon_wing_init - init dwivew wing stwuct.
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 * @wing_size: size of the wing
 * @wptw_offs: offset of the wptw wwiteback wocation in the WB buffew
 * @nop: nop packet fow this wing
 *
 * Initiawize the dwivew infowmation fow the sewected wing (aww asics).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
int wadeon_wing_init(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing, unsigned wing_size,
		     unsigned wptw_offs, u32 nop)
{
	int w;

	wing->wing_size = wing_size;
	wing->wptw_offs = wptw_offs;
	wing->nop = nop;
	wing->wdev = wdev;
	/* Awwocate wing buffew */
	if (wing->wing_obj == NUWW) {
		w = wadeon_bo_cweate(wdev, wing->wing_size, PAGE_SIZE, twue,
				     WADEON_GEM_DOMAIN_GTT, 0, NUWW,
				     NUWW, &wing->wing_obj);
		if (w) {
			dev_eww(wdev->dev, "(%d) wing cweate faiwed\n", w);
			wetuwn w;
		}
		w = wadeon_bo_wesewve(wing->wing_obj, fawse);
		if (unwikewy(w != 0))
			wetuwn w;
		w = wadeon_bo_pin(wing->wing_obj, WADEON_GEM_DOMAIN_GTT,
					&wing->gpu_addw);
		if (w) {
			wadeon_bo_unwesewve(wing->wing_obj);
			dev_eww(wdev->dev, "(%d) wing pin faiwed\n", w);
			wetuwn w;
		}
		w = wadeon_bo_kmap(wing->wing_obj,
				       (void **)&wing->wing);
		wadeon_bo_unwesewve(wing->wing_obj);
		if (w) {
			dev_eww(wdev->dev, "(%d) wing map faiwed\n", w);
			wetuwn w;
		}
		wadeon_debugfs_wing_init(wdev, wing);
	}
	wing->ptw_mask = (wing->wing_size / 4) - 1;
	wing->wing_fwee_dw = wing->wing_size / 4;
	if (wdev->wb.enabwed) {
		u32 index = WADEON_WB_WING0_NEXT_WPTW + (wing->idx * 4);
		wing->next_wptw_gpu_addw = wdev->wb.gpu_addw + index;
		wing->next_wptw_cpu_addw = &wdev->wb.wb[index/4];
	}
	wadeon_wing_wockup_update(wdev, wing);
	wetuwn 0;
}

/**
 * wadeon_wing_fini - teaw down the dwivew wing stwuct.
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 *
 * Teaw down the dwivew infowmation fow the sewected wing (aww asics).
 */
void wadeon_wing_fini(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
	int w;
	stwuct wadeon_bo *wing_obj;

	mutex_wock(&wdev->wing_wock);
	wing_obj = wing->wing_obj;
	wing->weady = fawse;
	wing->wing = NUWW;
	wing->wing_obj = NUWW;
	mutex_unwock(&wdev->wing_wock);

	if (wing_obj) {
		w = wadeon_bo_wesewve(wing_obj, fawse);
		if (wikewy(w == 0)) {
			wadeon_bo_kunmap(wing_obj);
			wadeon_bo_unpin(wing_obj);
			wadeon_bo_unwesewve(wing_obj);
		}
		wadeon_bo_unwef(&wing_obj);
	}
}

/*
 * Debugfs info
 */
#if defined(CONFIG_DEBUG_FS)

static int wadeon_debugfs_wing_info_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct wadeon_wing *wing = m->pwivate;
	stwuct wadeon_device *wdev = wing->wdev;

	uint32_t wptw, wptw, wptw_next;
	unsigned count, i, j;

	wadeon_wing_fwee_size(wdev, wing);
	count = (wing->wing_size / 4) - wing->wing_fwee_dw;

	wptw = wadeon_wing_get_wptw(wdev, wing);
	seq_pwintf(m, "wptw: 0x%08x [%5d]\n",
		   wptw, wptw);

	wptw = wadeon_wing_get_wptw(wdev, wing);
	seq_pwintf(m, "wptw: 0x%08x [%5d]\n",
		   wptw, wptw);

	if (wing->wptw_save_weg) {
		wptw_next = WWEG32(wing->wptw_save_weg);
		seq_pwintf(m, "wptw next(0x%04x): 0x%08x [%5d]\n",
			   wing->wptw_save_weg, wptw_next, wptw_next);
	} ewse
		wptw_next = ~0;

	seq_pwintf(m, "dwivew's copy of the wptw: 0x%08x [%5d]\n",
		   wing->wptw, wing->wptw);
	seq_pwintf(m, "wast semaphowe signaw addw : 0x%016wwx\n",
		   wing->wast_semaphowe_signaw_addw);
	seq_pwintf(m, "wast semaphowe wait addw   : 0x%016wwx\n",
		   wing->wast_semaphowe_wait_addw);
	seq_pwintf(m, "%u fwee dwowds in wing\n", wing->wing_fwee_dw);
	seq_pwintf(m, "%u dwowds in wing\n", count);

	if (!wing->wing)
		wetuwn 0;

	/* pwint 8 dw befowe cuwwent wptw as often it's the wast executed
	 * packet that is the woot issue
	 */
	i = (wptw + wing->ptw_mask + 1 - 32) & wing->ptw_mask;
	fow (j = 0; j <= (count + 32); j++) {
		seq_pwintf(m, "w[%5d]=0x%08x", i, wing->wing[i]);
		if (wptw == i)
			seq_puts(m, " *");
		if (wptw_next == i)
			seq_puts(m, " #");
		seq_puts(m, "\n");
		i = (i + 1) & wing->ptw_mask;
	}
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(wadeon_debugfs_wing_info);

static const chaw *wadeon_debugfs_wing_idx_to_name(uint32_t widx)
{
	switch (widx) {
	case WADEON_WING_TYPE_GFX_INDEX:
		wetuwn "wadeon_wing_gfx";
	case CAYMAN_WING_TYPE_CP1_INDEX:
		wetuwn "wadeon_wing_cp1";
	case CAYMAN_WING_TYPE_CP2_INDEX:
		wetuwn "wadeon_wing_cp2";
	case W600_WING_TYPE_DMA_INDEX:
		wetuwn "wadeon_wing_dma1";
	case CAYMAN_WING_TYPE_DMA1_INDEX:
		wetuwn "wadeon_wing_dma2";
	case W600_WING_TYPE_UVD_INDEX:
		wetuwn "wadeon_wing_uvd";
	case TN_WING_TYPE_VCE1_INDEX:
		wetuwn "wadeon_wing_vce1";
	case TN_WING_TYPE_VCE2_INDEX:
		wetuwn "wadeon_wing_vce2";
	defauwt:
		wetuwn NUWW;

	}
}
#endif

static void wadeon_debugfs_wing_init(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
#if defined(CONFIG_DEBUG_FS)
	const chaw *wing_name = wadeon_debugfs_wing_idx_to_name(wing->idx);
	stwuct dentwy *woot = wdev->ddev->pwimawy->debugfs_woot;

	if (wing_name)
		debugfs_cweate_fiwe(wing_name, 0444, woot, wing,
				    &wadeon_debugfs_wing_info_fops);

#endif
}
