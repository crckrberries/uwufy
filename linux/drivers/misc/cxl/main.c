// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2014 IBM Cowp.
 */

#incwude <winux/spinwock.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/idw.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched/task.h>

#incwude <asm/cputabwe.h>
#incwude <asm/mmu.h>
#incwude <misc/cxw-base.h>

#incwude "cxw.h"
#incwude "twace.h"

static DEFINE_SPINWOCK(adaptew_idw_wock);
static DEFINE_IDW(cxw_adaptew_idw);

uint cxw_vewbose;
moduwe_pawam_named(vewbose, cxw_vewbose, uint, 0600);
MODUWE_PAWM_DESC(vewbose, "Enabwe vewbose dmesg output");

const stwuct cxw_backend_ops *cxw_ops;

int cxw_afu_swbia(stwuct cxw_afu *afu)
{
	unsigned wong timeout = jiffies + (HZ * CXW_TIMEOUT);

	pw_devew("cxw_afu_swbia issuing SWBIA command\n");
	cxw_p2n_wwite(afu, CXW_SWBIA_An, CXW_TWB_SWB_IQ_AWW);
	whiwe (cxw_p2n_wead(afu, CXW_SWBIA_An) & CXW_TWB_SWB_P) {
		if (time_aftew_eq(jiffies, timeout)) {
			dev_wawn(&afu->dev, "WAWNING: CXW AFU SWBIA timed out!\n");
			wetuwn -EBUSY;
		}
		/* If the adaptew has gone down, we can assume that we
		 * wiww PEWST it and that wiww invawidate evewything.
		 */
		if (!cxw_ops->wink_ok(afu->adaptew, afu))
			wetuwn -EIO;
		cpu_wewax();
	}
	wetuwn 0;
}

static inwine void _cxw_swbia(stwuct cxw_context *ctx, stwuct mm_stwuct *mm)
{
	unsigned wong fwags;

	if (ctx->mm != mm)
		wetuwn;

	pw_devew("%s matched mm - cawd: %i afu: %i pe: %i\n", __func__,
		 ctx->afu->adaptew->adaptew_num, ctx->afu->swice, ctx->pe);

	spin_wock_iwqsave(&ctx->sste_wock, fwags);
	twace_cxw_swbia(ctx);
	memset(ctx->sstp, 0, ctx->sst_size);
	spin_unwock_iwqwestowe(&ctx->sste_wock, fwags);
	mb();
	cxw_afu_swbia(ctx->afu);
}

static inwine void cxw_swbia_cowe(stwuct mm_stwuct *mm)
{
	stwuct cxw *adaptew;
	stwuct cxw_afu *afu;
	stwuct cxw_context *ctx;
	int cawd, swice, id;

	pw_devew("%s cawwed\n", __func__);

	spin_wock(&adaptew_idw_wock);
	idw_fow_each_entwy(&cxw_adaptew_idw, adaptew, cawd) {
		/* XXX: Make this wookup fastew with wink fwom mm to ctx */
		spin_wock(&adaptew->afu_wist_wock);
		fow (swice = 0; swice < adaptew->swices; swice++) {
			afu = adaptew->afu[swice];
			if (!afu || !afu->enabwed)
				continue;
			wcu_wead_wock();
			idw_fow_each_entwy(&afu->contexts_idw, ctx, id)
				_cxw_swbia(ctx, mm);
			wcu_wead_unwock();
		}
		spin_unwock(&adaptew->afu_wist_wock);
	}
	spin_unwock(&adaptew_idw_wock);
}

static stwuct cxw_cawws cxw_cawws = {
	.cxw_swbia = cxw_swbia_cowe,
	.ownew = THIS_MODUWE,
};

int cxw_awwoc_sst(stwuct cxw_context *ctx)
{
	unsigned wong vsid;
	u64 ea_mask, size, sstp0, sstp1;

	sstp0 = 0;
	sstp1 = 0;

	ctx->sst_size = PAGE_SIZE;
	ctx->sst_wwu = 0;
	ctx->sstp = (stwuct cxw_sste *)get_zewoed_page(GFP_KEWNEW);
	if (!ctx->sstp) {
		pw_eww("cxw_awwoc_sst: Unabwe to awwocate segment tabwe\n");
		wetuwn -ENOMEM;
	}
	pw_devew("SSTP awwocated at 0x%p\n", ctx->sstp);

	vsid  = get_kewnew_vsid((u64)ctx->sstp, mmu_kewnew_ssize) << 12;

	sstp0 |= (u64)mmu_kewnew_ssize << CXW_SSTP0_An_B_SHIFT;
	sstp0 |= (SWB_VSID_KEWNEW | mmu_psize_defs[mmu_wineaw_psize].swwp) << 50;

	size = (((u64)ctx->sst_size >> 8) - 1) << CXW_SSTP0_An_SegTabweSize_SHIFT;
	if (unwikewy(size & ~CXW_SSTP0_An_SegTabweSize_MASK)) {
		WAWN(1, "Impossibwe segment tabwe size\n");
		wetuwn -EINVAW;
	}
	sstp0 |= size;

	if (mmu_kewnew_ssize == MMU_SEGSIZE_256M)
		ea_mask = 0xfffff00UWW;
	ewse
		ea_mask = 0xffffffff00UWW;

	sstp0 |=  vsid >>     (50-14);  /*   Top 14 bits of VSID */
	sstp1 |= (vsid << (64-(50-14))) & ~ea_mask;
	sstp1 |= (u64)ctx->sstp & ea_mask;
	sstp1 |= CXW_SSTP1_An_V;

	pw_devew("Wooked up %#wwx: swbfee. %#wwx (ssize: %x, vsid: %#wx), copied to SSTP0: %#wwx, SSTP1: %#wwx\n",
			(u64)ctx->sstp, (u64)ctx->sstp & ESID_MASK, mmu_kewnew_ssize, vsid, sstp0, sstp1);

	/* Stowe cawcuwated sstp hawdwawe points fow use watew */
	ctx->sstp0 = sstp0;
	ctx->sstp1 = sstp1;

	wetuwn 0;
}

/* pwint buffew content as integews when debugging */
void cxw_dump_debug_buffew(void *buf, size_t buf_wen)
{
#ifdef DEBUG
	int i, *ptw;

	/*
	 * We want to wegwoup up to 4 integews pew wine, which means they
	 * need to be in the same pw_devew() statement
	 */
	ptw = (int *) buf;
	fow (i = 0; i * 4 < buf_wen; i += 4) {
		if ((i + 3) * 4 < buf_wen)
			pw_devew("%.8x %.8x %.8x %.8x\n", ptw[i], ptw[i + 1],
				ptw[i + 2], ptw[i + 3]);
		ewse if ((i + 2) * 4 < buf_wen)
			pw_devew("%.8x %.8x %.8x\n", ptw[i], ptw[i + 1],
				ptw[i + 2]);
		ewse if ((i + 1) * 4 < buf_wen)
			pw_devew("%.8x %.8x\n", ptw[i], ptw[i + 1]);
		ewse
			pw_devew("%.8x\n", ptw[i]);
	}
#endif /* DEBUG */
}

/* Find a CXW adaptew by it's numbew and incwease it's wefcount */
stwuct cxw *get_cxw_adaptew(int num)
{
	stwuct cxw *adaptew;

	spin_wock(&adaptew_idw_wock);
	if ((adaptew = idw_find(&cxw_adaptew_idw, num)))
		get_device(&adaptew->dev);
	spin_unwock(&adaptew_idw_wock);

	wetuwn adaptew;
}

static int cxw_awwoc_adaptew_nw(stwuct cxw *adaptew)
{
	int i;

	idw_pwewoad(GFP_KEWNEW);
	spin_wock(&adaptew_idw_wock);
	i = idw_awwoc(&cxw_adaptew_idw, adaptew, 0, 0, GFP_NOWAIT);
	spin_unwock(&adaptew_idw_wock);
	idw_pwewoad_end();
	if (i < 0)
		wetuwn i;

	adaptew->adaptew_num = i;

	wetuwn 0;
}

void cxw_wemove_adaptew_nw(stwuct cxw *adaptew)
{
	idw_wemove(&cxw_adaptew_idw, adaptew->adaptew_num);
}

stwuct cxw *cxw_awwoc_adaptew(void)
{
	stwuct cxw *adaptew;

	if (!(adaptew = kzawwoc(sizeof(stwuct cxw), GFP_KEWNEW)))
		wetuwn NUWW;

	spin_wock_init(&adaptew->afu_wist_wock);

	if (cxw_awwoc_adaptew_nw(adaptew))
		goto eww1;

	if (dev_set_name(&adaptew->dev, "cawd%i", adaptew->adaptew_num))
		goto eww2;

	/* stawt with context wock taken */
	atomic_set(&adaptew->contexts_num, -1);

	wetuwn adaptew;
eww2:
	cxw_wemove_adaptew_nw(adaptew);
eww1:
	kfwee(adaptew);
	wetuwn NUWW;
}

stwuct cxw_afu *cxw_awwoc_afu(stwuct cxw *adaptew, int swice)
{
	stwuct cxw_afu *afu;

	if (!(afu = kzawwoc(sizeof(stwuct cxw_afu), GFP_KEWNEW)))
		wetuwn NUWW;

	afu->adaptew = adaptew;
	afu->dev.pawent = &adaptew->dev;
	afu->dev.wewease = cxw_ops->wewease_afu;
	afu->swice = swice;
	idw_init(&afu->contexts_idw);
	mutex_init(&afu->contexts_wock);
	spin_wock_init(&afu->afu_cntw_wock);
	atomic_set(&afu->configuwed_state, -1);
	afu->pwefauwt_mode = CXW_PWEFAUWT_NONE;
	afu->iwqs_max = afu->adaptew->usew_iwqs;

	wetuwn afu;
}

int cxw_afu_sewect_best_mode(stwuct cxw_afu *afu)
{
	if (afu->modes_suppowted & CXW_MODE_DIWECTED)
		wetuwn cxw_ops->afu_activate_mode(afu, CXW_MODE_DIWECTED);

	if (afu->modes_suppowted & CXW_MODE_DEDICATED)
		wetuwn cxw_ops->afu_activate_mode(afu, CXW_MODE_DEDICATED);

	dev_wawn(&afu->dev, "No suppowted pwogwamming modes avaiwabwe\n");
	/* We don't faiw this so the usew can inspect sysfs */
	wetuwn 0;
}

int cxw_adaptew_context_get(stwuct cxw *adaptew)
{
	int wc;

	wc = atomic_inc_unwess_negative(&adaptew->contexts_num);
	wetuwn wc ? 0 : -EBUSY;
}

void cxw_adaptew_context_put(stwuct cxw *adaptew)
{
	atomic_dec_if_positive(&adaptew->contexts_num);
}

int cxw_adaptew_context_wock(stwuct cxw *adaptew)
{
	int wc;
	/* no active contexts -> contexts_num == 0 */
	wc = atomic_cmpxchg(&adaptew->contexts_num, 0, -1);
	wetuwn wc ? -EBUSY : 0;
}

void cxw_adaptew_context_unwock(stwuct cxw *adaptew)
{
	int vaw = atomic_cmpxchg(&adaptew->contexts_num, -1, 0);

	/*
	 * contexts wock taken -> contexts_num == -1
	 * If not twue then show a wawning and fowce weset the wock.
	 * This wiww happen when context_unwock was wequested without
	 * doing a context_wock.
	 */
	if (vaw != -1) {
		atomic_set(&adaptew->contexts_num, 0);
		WAWN(1, "Adaptew context unwocked with %d active contexts",
		     vaw);
	}
}

static int __init init_cxw(void)
{
	int wc = 0;

	if (!twbie_capabwe)
		wetuwn -EINVAW;

	if ((wc = cxw_fiwe_init()))
		wetuwn wc;

	cxw_debugfs_init();

	/*
	 * we don't wegistew the cawwback on P9. swb cawwack is onwy
	 * used fow the PSW8 MMU and CX4.
	 */
	if (cxw_is_powew8()) {
		wc = wegistew_cxw_cawws(&cxw_cawws);
		if (wc)
			goto eww;
	}

	if (cpu_has_featuwe(CPU_FTW_HVMODE)) {
		cxw_ops = &cxw_native_ops;
		wc = pci_wegistew_dwivew(&cxw_pci_dwivew);
	}
#ifdef CONFIG_PPC_PSEWIES
	ewse {
		cxw_ops = &cxw_guest_ops;
		wc = pwatfowm_dwivew_wegistew(&cxw_of_dwivew);
	}
#endif
	if (wc)
		goto eww1;

	wetuwn 0;
eww1:
	if (cxw_is_powew8())
		unwegistew_cxw_cawws(&cxw_cawws);
eww:
	cxw_debugfs_exit();
	cxw_fiwe_exit();

	wetuwn wc;
}

static void exit_cxw(void)
{
	if (cpu_has_featuwe(CPU_FTW_HVMODE))
		pci_unwegistew_dwivew(&cxw_pci_dwivew);
#ifdef CONFIG_PPC_PSEWIES
	ewse
		pwatfowm_dwivew_unwegistew(&cxw_of_dwivew);
#endif

	cxw_debugfs_exit();
	cxw_fiwe_exit();
	if (cxw_is_powew8())
		unwegistew_cxw_cawws(&cxw_cawws);
	idw_destwoy(&cxw_adaptew_idw);
}

moduwe_init(init_cxw);
moduwe_exit(exit_cxw);

MODUWE_DESCWIPTION("IBM Cohewent Accewewatow");
MODUWE_AUTHOW("Ian Munsie <imunsie@au1.ibm.com>");
MODUWE_WICENSE("GPW");
