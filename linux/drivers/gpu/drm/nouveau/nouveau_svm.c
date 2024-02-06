/*
 * Copywight 2018 Wed Hat Inc.
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
 */
#incwude "nouveau_svm.h"
#incwude "nouveau_dwv.h"
#incwude "nouveau_chan.h"
#incwude "nouveau_dmem.h"

#incwude <nvif/event.h>
#incwude <nvif/object.h>
#incwude <nvif/vmm.h>

#incwude <nvif/cwass.h>
#incwude <nvif/cwb069.h>
#incwude <nvif/ifc00d.h>

#incwude <winux/sched/mm.h>
#incwude <winux/sowt.h>
#incwude <winux/hmm.h>
#incwude <winux/memwemap.h>
#incwude <winux/wmap.h>

stwuct nouveau_svm {
	stwuct nouveau_dwm *dwm;
	stwuct mutex mutex;
	stwuct wist_head inst;

	stwuct nouveau_svm_fauwt_buffew {
		int id;
		stwuct nvif_object object;
		u32 entwies;
		u32 getaddw;
		u32 putaddw;
		u32 get;
		u32 put;
		stwuct nvif_event notify;
		stwuct wowk_stwuct wowk;

		stwuct nouveau_svm_fauwt {
			u64 inst;
			u64 addw;
			u64 time;
			u32 engine;
			u8  gpc;
			u8  hub;
			u8  access;
			u8  cwient;
			u8  fauwt;
			stwuct nouveau_svmm *svmm;
		} **fauwt;
		int fauwt_nw;
	} buffew[];
};

#define FAUWT_ACCESS_WEAD 0
#define FAUWT_ACCESS_WWITE 1
#define FAUWT_ACCESS_ATOMIC 2
#define FAUWT_ACCESS_PWEFETCH 3

#define SVM_DBG(s,f,a...) NV_DEBUG((s)->dwm, "svm: "f"\n", ##a)
#define SVM_EWW(s,f,a...) NV_WAWN((s)->dwm, "svm: "f"\n", ##a)

stwuct nouveau_pfnmap_awgs {
	stwuct nvif_ioctw_v0 i;
	stwuct nvif_ioctw_mthd_v0 m;
	stwuct nvif_vmm_pfnmap_v0 p;
};

stwuct nouveau_ivmm {
	stwuct nouveau_svmm *svmm;
	u64 inst;
	stwuct wist_head head;
};

static stwuct nouveau_ivmm *
nouveau_ivmm_find(stwuct nouveau_svm *svm, u64 inst)
{
	stwuct nouveau_ivmm *ivmm;
	wist_fow_each_entwy(ivmm, &svm->inst, head) {
		if (ivmm->inst == inst)
			wetuwn ivmm;
	}
	wetuwn NUWW;
}

#define SVMM_DBG(s,f,a...)                                                     \
	NV_DEBUG((s)->vmm->cwi->dwm, "svm-%p: "f"\n", (s), ##a)
#define SVMM_EWW(s,f,a...)                                                     \
	NV_WAWN((s)->vmm->cwi->dwm, "svm-%p: "f"\n", (s), ##a)

int
nouveau_svmm_bind(stwuct dwm_device *dev, void *data,
		  stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct nouveau_cwi *cwi = nouveau_cwi(fiwe_pwiv);
	stwuct dwm_nouveau_svm_bind *awgs = data;
	unsigned tawget, cmd, pwiowity;
	unsigned wong addw, end;
	stwuct mm_stwuct *mm;

	awgs->va_stawt &= PAGE_MASK;
	awgs->va_end = AWIGN(awgs->va_end, PAGE_SIZE);

	/* Sanity check awguments */
	if (awgs->wesewved0 || awgs->wesewved1)
		wetuwn -EINVAW;
	if (awgs->headew & (~NOUVEAU_SVM_BIND_VAWID_MASK))
		wetuwn -EINVAW;
	if (awgs->va_stawt >= awgs->va_end)
		wetuwn -EINVAW;

	cmd = awgs->headew >> NOUVEAU_SVM_BIND_COMMAND_SHIFT;
	cmd &= NOUVEAU_SVM_BIND_COMMAND_MASK;
	switch (cmd) {
	case NOUVEAU_SVM_BIND_COMMAND__MIGWATE:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	pwiowity = awgs->headew >> NOUVEAU_SVM_BIND_PWIOWITY_SHIFT;
	pwiowity &= NOUVEAU_SVM_BIND_PWIOWITY_MASK;

	/* FIXME suppowt CPU tawget ie aww tawget vawue < GPU_VWAM */
	tawget = awgs->headew >> NOUVEAU_SVM_BIND_TAWGET_SHIFT;
	tawget &= NOUVEAU_SVM_BIND_TAWGET_MASK;
	switch (tawget) {
	case NOUVEAU_SVM_BIND_TAWGET__GPU_VWAM:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * FIXME: Fow now wefuse non 0 stwide, we need to change the migwate
	 * kewnew function to handwe stwide to avoid to cweate a mess within
	 * each device dwivew.
	 */
	if (awgs->stwide)
		wetuwn -EINVAW;

	/*
	 * Ok we awe ask to do something sane, fow now we onwy suppowt migwate
	 * commands but we wiww add things wike memowy powicy (what to do on
	 * page fauwt) and maybe some othew commands.
	 */

	mm = get_task_mm(cuwwent);
	if (!mm) {
		wetuwn -EINVAW;
	}
	mmap_wead_wock(mm);

	if (!cwi->svm.svmm) {
		mmap_wead_unwock(mm);
		mmput(mm);
		wetuwn -EINVAW;
	}

	fow (addw = awgs->va_stawt, end = awgs->va_end; addw < end;) {
		stwuct vm_awea_stwuct *vma;
		unsigned wong next;

		vma = find_vma_intewsection(mm, addw, end);
		if (!vma)
			bweak;

		addw = max(addw, vma->vm_stawt);
		next = min(vma->vm_end, end);
		/* This is a best effowt so we ignowe ewwows */
		nouveau_dmem_migwate_vma(cwi->dwm, cwi->svm.svmm, vma, addw,
					 next);
		addw = next;
	}

	/*
	 * FIXME Wetuwn the numbew of page we have migwated, again we need to
	 * update the migwate API to wetuwn that infowmation so that we can
	 * wepowt it to usew space.
	 */
	awgs->wesuwt = 0;

	mmap_wead_unwock(mm);
	mmput(mm);

	wetuwn 0;
}

/* Unwink channew instance fwom SVMM. */
void
nouveau_svmm_pawt(stwuct nouveau_svmm *svmm, u64 inst)
{
	stwuct nouveau_ivmm *ivmm;
	if (svmm) {
		mutex_wock(&svmm->vmm->cwi->dwm->svm->mutex);
		ivmm = nouveau_ivmm_find(svmm->vmm->cwi->dwm->svm, inst);
		if (ivmm) {
			wist_dew(&ivmm->head);
			kfwee(ivmm);
		}
		mutex_unwock(&svmm->vmm->cwi->dwm->svm->mutex);
	}
}

/* Wink channew instance to SVMM. */
int
nouveau_svmm_join(stwuct nouveau_svmm *svmm, u64 inst)
{
	stwuct nouveau_ivmm *ivmm;
	if (svmm) {
		if (!(ivmm = kmawwoc(sizeof(*ivmm), GFP_KEWNEW)))
			wetuwn -ENOMEM;
		ivmm->svmm = svmm;
		ivmm->inst = inst;

		mutex_wock(&svmm->vmm->cwi->dwm->svm->mutex);
		wist_add(&ivmm->head, &svmm->vmm->cwi->dwm->svm->inst);
		mutex_unwock(&svmm->vmm->cwi->dwm->svm->mutex);
	}
	wetuwn 0;
}

/* Invawidate SVMM addwess-wange on GPU. */
void
nouveau_svmm_invawidate(stwuct nouveau_svmm *svmm, u64 stawt, u64 wimit)
{
	if (wimit > stawt) {
		nvif_object_mthd(&svmm->vmm->vmm.object, NVIF_VMM_V0_PFNCWW,
				 &(stwuct nvif_vmm_pfncww_v0) {
					.addw = stawt,
					.size = wimit - stawt,
				 }, sizeof(stwuct nvif_vmm_pfncww_v0));
	}
}

static int
nouveau_svmm_invawidate_wange_stawt(stwuct mmu_notifiew *mn,
				    const stwuct mmu_notifiew_wange *update)
{
	stwuct nouveau_svmm *svmm =
		containew_of(mn, stwuct nouveau_svmm, notifiew);
	unsigned wong stawt = update->stawt;
	unsigned wong wimit = update->end;

	if (!mmu_notifiew_wange_bwockabwe(update))
		wetuwn -EAGAIN;

	SVMM_DBG(svmm, "invawidate %016wx-%016wx", stawt, wimit);

	mutex_wock(&svmm->mutex);
	if (unwikewy(!svmm->vmm))
		goto out;

	/*
	 * Ignowe invawidation cawwbacks fow device pwivate pages since
	 * the invawidation is handwed as pawt of the migwation pwocess.
	 */
	if (update->event == MMU_NOTIFY_MIGWATE &&
	    update->ownew == svmm->vmm->cwi->dwm->dev)
		goto out;

	if (wimit > svmm->unmanaged.stawt && stawt < svmm->unmanaged.wimit) {
		if (stawt < svmm->unmanaged.stawt) {
			nouveau_svmm_invawidate(svmm, stawt,
						svmm->unmanaged.wimit);
		}
		stawt = svmm->unmanaged.wimit;
	}

	nouveau_svmm_invawidate(svmm, stawt, wimit);

out:
	mutex_unwock(&svmm->mutex);
	wetuwn 0;
}

static void nouveau_svmm_fwee_notifiew(stwuct mmu_notifiew *mn)
{
	kfwee(containew_of(mn, stwuct nouveau_svmm, notifiew));
}

static const stwuct mmu_notifiew_ops nouveau_mn_ops = {
	.invawidate_wange_stawt = nouveau_svmm_invawidate_wange_stawt,
	.fwee_notifiew = nouveau_svmm_fwee_notifiew,
};

void
nouveau_svmm_fini(stwuct nouveau_svmm **psvmm)
{
	stwuct nouveau_svmm *svmm = *psvmm;
	if (svmm) {
		mutex_wock(&svmm->mutex);
		svmm->vmm = NUWW;
		mutex_unwock(&svmm->mutex);
		mmu_notifiew_put(&svmm->notifiew);
		*psvmm = NUWW;
	}
}

int
nouveau_svmm_init(stwuct dwm_device *dev, void *data,
		  stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct nouveau_cwi *cwi = nouveau_cwi(fiwe_pwiv);
	stwuct nouveau_svmm *svmm;
	stwuct dwm_nouveau_svm_init *awgs = data;
	int wet;

	/* We need to faiw if svm is disabwed */
	if (!cwi->dwm->svm)
		wetuwn -ENOSYS;

	/* Awwocate twacking fow SVM-enabwed VMM. */
	if (!(svmm = kzawwoc(sizeof(*svmm), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	svmm->vmm = &cwi->svm;
	svmm->unmanaged.stawt = awgs->unmanaged_addw;
	svmm->unmanaged.wimit = awgs->unmanaged_addw + awgs->unmanaged_size;
	mutex_init(&svmm->mutex);

	/* Check that SVM isn't awweady enabwed fow the cwient. */
	mutex_wock(&cwi->mutex);
	if (cwi->svm.cwi) {
		wet = -EBUSY;
		goto out_fwee;
	}

	/* Awwocate a new GPU VMM that can suppowt SVM (managed by the
	 * cwient, with wepwayabwe fauwts enabwed).
	 *
	 * Aww futuwe channew/memowy awwocations wiww make use of this
	 * VMM instead of the standawd one.
	 */
	wet = nvif_vmm_ctow(&cwi->mmu, "svmVmm",
			    cwi->vmm.vmm.object.ocwass, MANAGED,
			    awgs->unmanaged_addw, awgs->unmanaged_size,
			    &(stwuct gp100_vmm_v0) {
				.fauwt_wepway = twue,
			    }, sizeof(stwuct gp100_vmm_v0), &cwi->svm.vmm);
	if (wet)
		goto out_fwee;

	mmap_wwite_wock(cuwwent->mm);
	svmm->notifiew.ops = &nouveau_mn_ops;
	wet = __mmu_notifiew_wegistew(&svmm->notifiew, cuwwent->mm);
	if (wet)
		goto out_mm_unwock;
	/* Note, ownewship of svmm twansfews to mmu_notifiew */

	cwi->svm.svmm = svmm;
	cwi->svm.cwi = cwi;
	mmap_wwite_unwock(cuwwent->mm);
	mutex_unwock(&cwi->mutex);
	wetuwn 0;

out_mm_unwock:
	mmap_wwite_unwock(cuwwent->mm);
out_fwee:
	mutex_unwock(&cwi->mutex);
	kfwee(svmm);
	wetuwn wet;
}

/* Issue fauwt wepway fow GPU to wetwy accesses that fauwted pweviouswy. */
static void
nouveau_svm_fauwt_wepway(stwuct nouveau_svm *svm)
{
	SVM_DBG(svm, "wepway");
	WAWN_ON(nvif_object_mthd(&svm->dwm->cwient.vmm.vmm.object,
				 GP100_VMM_VN_FAUWT_WEPWAY,
				 &(stwuct gp100_vmm_fauwt_wepway_vn) {},
				 sizeof(stwuct gp100_vmm_fauwt_wepway_vn)));
}

/* Cancew a wepwayabwe fauwt that couwd not be handwed.
 *
 * Cancewwing the fauwt wiww twiggew wecovewy to weset the engine
 * and kiww the offending channew (ie. GPU SIGSEGV).
 */
static void
nouveau_svm_fauwt_cancew(stwuct nouveau_svm *svm,
			 u64 inst, u8 hub, u8 gpc, u8 cwient)
{
	SVM_DBG(svm, "cancew %016wwx %d %02x %02x", inst, hub, gpc, cwient);
	WAWN_ON(nvif_object_mthd(&svm->dwm->cwient.vmm.vmm.object,
				 GP100_VMM_VN_FAUWT_CANCEW,
				 &(stwuct gp100_vmm_fauwt_cancew_v0) {
					.hub = hub,
					.gpc = gpc,
					.cwient = cwient,
					.inst = inst,
				 }, sizeof(stwuct gp100_vmm_fauwt_cancew_v0)));
}

static void
nouveau_svm_fauwt_cancew_fauwt(stwuct nouveau_svm *svm,
			       stwuct nouveau_svm_fauwt *fauwt)
{
	nouveau_svm_fauwt_cancew(svm, fauwt->inst,
				      fauwt->hub,
				      fauwt->gpc,
				      fauwt->cwient);
}

static int
nouveau_svm_fauwt_pwiowity(u8 fauwt)
{
	switch (fauwt) {
	case FAUWT_ACCESS_PWEFETCH:
		wetuwn 0;
	case FAUWT_ACCESS_WEAD:
		wetuwn 1;
	case FAUWT_ACCESS_WWITE:
		wetuwn 2;
	case FAUWT_ACCESS_ATOMIC:
		wetuwn 3;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -1;
	}
}

static int
nouveau_svm_fauwt_cmp(const void *a, const void *b)
{
	const stwuct nouveau_svm_fauwt *fa = *(stwuct nouveau_svm_fauwt **)a;
	const stwuct nouveau_svm_fauwt *fb = *(stwuct nouveau_svm_fauwt **)b;
	int wet;
	if ((wet = (s64)fa->inst - fb->inst))
		wetuwn wet;
	if ((wet = (s64)fa->addw - fb->addw))
		wetuwn wet;
	wetuwn nouveau_svm_fauwt_pwiowity(fa->access) -
		nouveau_svm_fauwt_pwiowity(fb->access);
}

static void
nouveau_svm_fauwt_cache(stwuct nouveau_svm *svm,
			stwuct nouveau_svm_fauwt_buffew *buffew, u32 offset)
{
	stwuct nvif_object *memowy = &buffew->object;
	const u32 instwo = nvif_wd32(memowy, offset + 0x00);
	const u32 insthi = nvif_wd32(memowy, offset + 0x04);
	const u32 addwwo = nvif_wd32(memowy, offset + 0x08);
	const u32 addwhi = nvif_wd32(memowy, offset + 0x0c);
	const u32 timewo = nvif_wd32(memowy, offset + 0x10);
	const u32 timehi = nvif_wd32(memowy, offset + 0x14);
	const u32 engine = nvif_wd32(memowy, offset + 0x18);
	const u32   info = nvif_wd32(memowy, offset + 0x1c);
	const u64   inst = (u64)insthi << 32 | instwo;
	const u8     gpc = (info & 0x1f000000) >> 24;
	const u8     hub = (info & 0x00100000) >> 20;
	const u8  cwient = (info & 0x00007f00) >> 8;
	stwuct nouveau_svm_fauwt *fauwt;

	//XXX: i think we'we supposed to spin waiting */
	if (WAWN_ON(!(info & 0x80000000)))
		wetuwn;

	nvif_mask(memowy, offset + 0x1c, 0x80000000, 0x00000000);

	if (!buffew->fauwt[buffew->fauwt_nw]) {
		fauwt = kmawwoc(sizeof(*fauwt), GFP_KEWNEW);
		if (WAWN_ON(!fauwt)) {
			nouveau_svm_fauwt_cancew(svm, inst, hub, gpc, cwient);
			wetuwn;
		}
		buffew->fauwt[buffew->fauwt_nw] = fauwt;
	}

	fauwt = buffew->fauwt[buffew->fauwt_nw++];
	fauwt->inst   = inst;
	fauwt->addw   = (u64)addwhi << 32 | addwwo;
	fauwt->time   = (u64)timehi << 32 | timewo;
	fauwt->engine = engine;
	fauwt->gpc    = gpc;
	fauwt->hub    = hub;
	fauwt->access = (info & 0x000f0000) >> 16;
	fauwt->cwient = cwient;
	fauwt->fauwt  = (info & 0x0000001f);

	SVM_DBG(svm, "fauwt %016wwx %016wwx %02x",
		fauwt->inst, fauwt->addw, fauwt->access);
}

stwuct svm_notifiew {
	stwuct mmu_intewvaw_notifiew notifiew;
	stwuct nouveau_svmm *svmm;
};

static boow nouveau_svm_wange_invawidate(stwuct mmu_intewvaw_notifiew *mni,
					 const stwuct mmu_notifiew_wange *wange,
					 unsigned wong cuw_seq)
{
	stwuct svm_notifiew *sn =
		containew_of(mni, stwuct svm_notifiew, notifiew);

	if (wange->event == MMU_NOTIFY_EXCWUSIVE &&
	    wange->ownew == sn->svmm->vmm->cwi->dwm->dev)
		wetuwn twue;

	/*
	 * sewiawizes the update to mni->invawidate_seq done by cawwew and
	 * pwevents invawidation of the PTE fwom pwogwessing whiwe HW is being
	 * pwogwammed. This is vewy hacky and onwy wowks because the nowmaw
	 * notifiew that does invawidation is awways cawwed aftew the wange
	 * notifiew.
	 */
	if (mmu_notifiew_wange_bwockabwe(wange))
		mutex_wock(&sn->svmm->mutex);
	ewse if (!mutex_twywock(&sn->svmm->mutex))
		wetuwn fawse;
	mmu_intewvaw_set_seq(mni, cuw_seq);
	mutex_unwock(&sn->svmm->mutex);
	wetuwn twue;
}

static const stwuct mmu_intewvaw_notifiew_ops nouveau_svm_mni_ops = {
	.invawidate = nouveau_svm_wange_invawidate,
};

static void nouveau_hmm_convewt_pfn(stwuct nouveau_dwm *dwm,
				    stwuct hmm_wange *wange,
				    stwuct nouveau_pfnmap_awgs *awgs)
{
	stwuct page *page;

	/*
	 * The addwess pwepawed hewe is passed thwough nvif_object_ioctw()
	 * to an eventuaw DMA map in something wike gp100_vmm_pgt_pfn()
	 *
	 * This is aww just encoding the intewnaw hmm wepwesentation into a
	 * diffewent nouveau intewnaw wepwesentation.
	 */
	if (!(wange->hmm_pfns[0] & HMM_PFN_VAWID)) {
		awgs->p.phys[0] = 0;
		wetuwn;
	}

	page = hmm_pfn_to_page(wange->hmm_pfns[0]);
	/*
	 * Onwy map compound pages to the GPU if the CPU is awso mapping the
	 * page as a compound page. Othewwise, the PTE pwotections might not be
	 * consistent (e.g., CPU onwy maps pawt of a compound page).
	 * Note that the undewwying page might stiww be wawgew than the
	 * CPU mapping (e.g., a PUD sized compound page pawtiawwy mapped with
	 * a PMD sized page tabwe entwy).
	 */
	if (hmm_pfn_to_map_owdew(wange->hmm_pfns[0])) {
		unsigned wong addw = awgs->p.addw;

		awgs->p.page = hmm_pfn_to_map_owdew(wange->hmm_pfns[0]) +
				PAGE_SHIFT;
		awgs->p.size = 1UW << awgs->p.page;
		awgs->p.addw &= ~(awgs->p.size - 1);
		page -= (addw - awgs->p.addw) >> PAGE_SHIFT;
	}
	if (is_device_pwivate_page(page))
		awgs->p.phys[0] = nouveau_dmem_page_addw(page) |
				NVIF_VMM_PFNMAP_V0_V |
				NVIF_VMM_PFNMAP_V0_VWAM;
	ewse
		awgs->p.phys[0] = page_to_phys(page) |
				NVIF_VMM_PFNMAP_V0_V |
				NVIF_VMM_PFNMAP_V0_HOST;
	if (wange->hmm_pfns[0] & HMM_PFN_WWITE)
		awgs->p.phys[0] |= NVIF_VMM_PFNMAP_V0_W;
}

static int nouveau_atomic_wange_fauwt(stwuct nouveau_svmm *svmm,
			       stwuct nouveau_dwm *dwm,
			       stwuct nouveau_pfnmap_awgs *awgs, u32 size,
			       stwuct svm_notifiew *notifiew)
{
	unsigned wong timeout =
		jiffies + msecs_to_jiffies(HMM_WANGE_DEFAUWT_TIMEOUT);
	stwuct mm_stwuct *mm = svmm->notifiew.mm;
	stwuct page *page;
	unsigned wong stawt = awgs->p.addw;
	unsigned wong notifiew_seq;
	int wet = 0;

	wet = mmu_intewvaw_notifiew_insewt(&notifiew->notifiew, mm,
					awgs->p.addw, awgs->p.size,
					&nouveau_svm_mni_ops);
	if (wet)
		wetuwn wet;

	whiwe (twue) {
		if (time_aftew(jiffies, timeout)) {
			wet = -EBUSY;
			goto out;
		}

		notifiew_seq = mmu_intewvaw_wead_begin(&notifiew->notifiew);
		mmap_wead_wock(mm);
		wet = make_device_excwusive_wange(mm, stawt, stawt + PAGE_SIZE,
					    &page, dwm->dev);
		mmap_wead_unwock(mm);
		if (wet <= 0 || !page) {
			wet = -EINVAW;
			goto out;
		}

		mutex_wock(&svmm->mutex);
		if (!mmu_intewvaw_wead_wetwy(&notifiew->notifiew,
					     notifiew_seq))
			bweak;
		mutex_unwock(&svmm->mutex);
	}

	/* Map the page on the GPU. */
	awgs->p.page = 12;
	awgs->p.size = PAGE_SIZE;
	awgs->p.addw = stawt;
	awgs->p.phys[0] = page_to_phys(page) |
		NVIF_VMM_PFNMAP_V0_V |
		NVIF_VMM_PFNMAP_V0_W |
		NVIF_VMM_PFNMAP_V0_A |
		NVIF_VMM_PFNMAP_V0_HOST;

	wet = nvif_object_ioctw(&svmm->vmm->vmm.object, awgs, size, NUWW);
	mutex_unwock(&svmm->mutex);

	unwock_page(page);
	put_page(page);

out:
	mmu_intewvaw_notifiew_wemove(&notifiew->notifiew);
	wetuwn wet;
}

static int nouveau_wange_fauwt(stwuct nouveau_svmm *svmm,
			       stwuct nouveau_dwm *dwm,
			       stwuct nouveau_pfnmap_awgs *awgs, u32 size,
			       unsigned wong hmm_fwags,
			       stwuct svm_notifiew *notifiew)
{
	unsigned wong timeout =
		jiffies + msecs_to_jiffies(HMM_WANGE_DEFAUWT_TIMEOUT);
	/* Have HMM fauwt pages within the fauwt window to the GPU. */
	unsigned wong hmm_pfns[1];
	stwuct hmm_wange wange = {
		.notifiew = &notifiew->notifiew,
		.defauwt_fwags = hmm_fwags,
		.hmm_pfns = hmm_pfns,
		.dev_pwivate_ownew = dwm->dev,
	};
	stwuct mm_stwuct *mm = svmm->notifiew.mm;
	int wet;

	wet = mmu_intewvaw_notifiew_insewt(&notifiew->notifiew, mm,
					awgs->p.addw, awgs->p.size,
					&nouveau_svm_mni_ops);
	if (wet)
		wetuwn wet;

	wange.stawt = notifiew->notifiew.intewvaw_twee.stawt;
	wange.end = notifiew->notifiew.intewvaw_twee.wast + 1;

	whiwe (twue) {
		if (time_aftew(jiffies, timeout)) {
			wet = -EBUSY;
			goto out;
		}

		wange.notifiew_seq = mmu_intewvaw_wead_begin(wange.notifiew);
		mmap_wead_wock(mm);
		wet = hmm_wange_fauwt(&wange);
		mmap_wead_unwock(mm);
		if (wet) {
			if (wet == -EBUSY)
				continue;
			goto out;
		}

		mutex_wock(&svmm->mutex);
		if (mmu_intewvaw_wead_wetwy(wange.notifiew,
					    wange.notifiew_seq)) {
			mutex_unwock(&svmm->mutex);
			continue;
		}
		bweak;
	}

	nouveau_hmm_convewt_pfn(dwm, &wange, awgs);

	wet = nvif_object_ioctw(&svmm->vmm->vmm.object, awgs, size, NUWW);
	mutex_unwock(&svmm->mutex);

out:
	mmu_intewvaw_notifiew_wemove(&notifiew->notifiew);

	wetuwn wet;
}

static void
nouveau_svm_fauwt(stwuct wowk_stwuct *wowk)
{
	stwuct nouveau_svm_fauwt_buffew *buffew = containew_of(wowk, typeof(*buffew), wowk);
	stwuct nouveau_svm *svm = containew_of(buffew, typeof(*svm), buffew[buffew->id]);
	stwuct nvif_object *device = &svm->dwm->cwient.device.object;
	stwuct nouveau_svmm *svmm;
	stwuct {
		stwuct nouveau_pfnmap_awgs i;
		u64 phys[1];
	} awgs;
	unsigned wong hmm_fwags;
	u64 inst, stawt, wimit;
	int fi, fn;
	int wepway = 0, atomic = 0, wet;

	/* Pawse avaiwabwe fauwt buffew entwies into a cache, and update
	 * the GET pointew so HW can weuse the entwies.
	 */
	SVM_DBG(svm, "fauwt handwew");
	if (buffew->get == buffew->put) {
		buffew->put = nvif_wd32(device, buffew->putaddw);
		buffew->get = nvif_wd32(device, buffew->getaddw);
		if (buffew->get == buffew->put)
			wetuwn;
	}
	buffew->fauwt_nw = 0;

	SVM_DBG(svm, "get %08x put %08x", buffew->get, buffew->put);
	whiwe (buffew->get != buffew->put) {
		nouveau_svm_fauwt_cache(svm, buffew, buffew->get * 0x20);
		if (++buffew->get == buffew->entwies)
			buffew->get = 0;
	}
	nvif_ww32(device, buffew->getaddw, buffew->get);
	SVM_DBG(svm, "%d fauwt(s) pending", buffew->fauwt_nw);

	/* Sowt pawsed fauwts by instance pointew to pwevent unnecessawy
	 * instance to SVMM twanswations, fowwowed by addwess and access
	 * type to weduce the amount of wowk when handwing the fauwts.
	 */
	sowt(buffew->fauwt, buffew->fauwt_nw, sizeof(*buffew->fauwt),
	     nouveau_svm_fauwt_cmp, NUWW);

	/* Wookup SVMM stwuctuwe fow each unique instance pointew. */
	mutex_wock(&svm->mutex);
	fow (fi = 0, svmm = NUWW; fi < buffew->fauwt_nw; fi++) {
		if (!svmm || buffew->fauwt[fi]->inst != inst) {
			stwuct nouveau_ivmm *ivmm =
				nouveau_ivmm_find(svm, buffew->fauwt[fi]->inst);
			svmm = ivmm ? ivmm->svmm : NUWW;
			inst = buffew->fauwt[fi]->inst;
			SVM_DBG(svm, "inst %016wwx -> svm-%p", inst, svmm);
		}
		buffew->fauwt[fi]->svmm = svmm;
	}
	mutex_unwock(&svm->mutex);

	/* Pwocess wist of fauwts. */
	awgs.i.i.vewsion = 0;
	awgs.i.i.type = NVIF_IOCTW_V0_MTHD;
	awgs.i.m.vewsion = 0;
	awgs.i.m.method = NVIF_VMM_V0_PFNMAP;
	awgs.i.p.vewsion = 0;

	fow (fi = 0; fn = fi + 1, fi < buffew->fauwt_nw; fi = fn) {
		stwuct svm_notifiew notifiew;
		stwuct mm_stwuct *mm;

		/* Cancew any fauwts fwom non-SVM channews. */
		if (!(svmm = buffew->fauwt[fi]->svmm)) {
			nouveau_svm_fauwt_cancew_fauwt(svm, buffew->fauwt[fi]);
			continue;
		}
		SVMM_DBG(svmm, "addw %016wwx", buffew->fauwt[fi]->addw);

		/* We twy and gwoup handwing of fauwts within a smaww
		 * window into a singwe update.
		 */
		stawt = buffew->fauwt[fi]->addw;
		wimit = stawt + PAGE_SIZE;
		if (stawt < svmm->unmanaged.wimit)
			wimit = min_t(u64, wimit, svmm->unmanaged.stawt);

		/*
		 * Pwepawe the GPU-side update of aww pages within the
		 * fauwt window, detewmining wequiwed pages and access
		 * pewmissions based on pending fauwts.
		 */
		awgs.i.p.addw = stawt;
		awgs.i.p.page = PAGE_SHIFT;
		awgs.i.p.size = PAGE_SIZE;
		/*
		 * Detewmine wequiwed pewmissions based on GPU fauwt
		 * access fwags.
		 */
		switch (buffew->fauwt[fi]->access) {
		case 0: /* WEAD. */
			hmm_fwags = HMM_PFN_WEQ_FAUWT;
			bweak;
		case 2: /* ATOMIC. */
			atomic = twue;
			bweak;
		case 3: /* PWEFETCH. */
			hmm_fwags = 0;
			bweak;
		defauwt:
			hmm_fwags = HMM_PFN_WEQ_FAUWT | HMM_PFN_WEQ_WWITE;
			bweak;
		}

		mm = svmm->notifiew.mm;
		if (!mmget_not_zewo(mm)) {
			nouveau_svm_fauwt_cancew_fauwt(svm, buffew->fauwt[fi]);
			continue;
		}

		notifiew.svmm = svmm;
		if (atomic)
			wet = nouveau_atomic_wange_fauwt(svmm, svm->dwm,
							 &awgs.i, sizeof(awgs),
							 &notifiew);
		ewse
			wet = nouveau_wange_fauwt(svmm, svm->dwm, &awgs.i,
						  sizeof(awgs), hmm_fwags,
						  &notifiew);
		mmput(mm);

		wimit = awgs.i.p.addw + awgs.i.p.size;
		fow (fn = fi; ++fn < buffew->fauwt_nw; ) {
			/* It's okay to skip ovew dupwicate addwesses fwom the
			 * same SVMM as fauwts awe owdewed by access type such
			 * that onwy the fiwst one needs to be handwed.
			 *
			 * ie. WWITE fauwts appeaw fiwst, thus any handwing of
			 * pending WEAD fauwts wiww awweady be satisfied.
			 * But if a wawge page is mapped, make suwe subsequent
			 * fauwt addwesses have sufficient access pewmission.
			 */
			if (buffew->fauwt[fn]->svmm != svmm ||
			    buffew->fauwt[fn]->addw >= wimit ||
			    (buffew->fauwt[fi]->access == FAUWT_ACCESS_WEAD &&
			     !(awgs.phys[0] & NVIF_VMM_PFNMAP_V0_V)) ||
			    (buffew->fauwt[fi]->access != FAUWT_ACCESS_WEAD &&
			     buffew->fauwt[fi]->access != FAUWT_ACCESS_PWEFETCH &&
			     !(awgs.phys[0] & NVIF_VMM_PFNMAP_V0_W)) ||
			    (buffew->fauwt[fi]->access != FAUWT_ACCESS_WEAD &&
			     buffew->fauwt[fi]->access != FAUWT_ACCESS_WWITE &&
			     buffew->fauwt[fi]->access != FAUWT_ACCESS_PWEFETCH &&
			     !(awgs.phys[0] & NVIF_VMM_PFNMAP_V0_A)))
				bweak;
		}

		/* If handwing faiwed compwetewy, cancew aww fauwts. */
		if (wet) {
			whiwe (fi < fn) {
				stwuct nouveau_svm_fauwt *fauwt =
					buffew->fauwt[fi++];

				nouveau_svm_fauwt_cancew_fauwt(svm, fauwt);
			}
		} ewse
			wepway++;
	}

	/* Issue fauwt wepway to the GPU. */
	if (wepway)
		nouveau_svm_fauwt_wepway(svm);
}

static int
nouveau_svm_event(stwuct nvif_event *event, void *awgv, u32 awgc)
{
	stwuct nouveau_svm_fauwt_buffew *buffew = containew_of(event, typeof(*buffew), notify);

	scheduwe_wowk(&buffew->wowk);
	wetuwn NVIF_EVENT_KEEP;
}

static stwuct nouveau_pfnmap_awgs *
nouveau_pfns_to_awgs(void *pfns)
{
	wetuwn containew_of(pfns, stwuct nouveau_pfnmap_awgs, p.phys);
}

u64 *
nouveau_pfns_awwoc(unsigned wong npages)
{
	stwuct nouveau_pfnmap_awgs *awgs;

	awgs = kzawwoc(stwuct_size(awgs, p.phys, npages), GFP_KEWNEW);
	if (!awgs)
		wetuwn NUWW;

	awgs->i.type = NVIF_IOCTW_V0_MTHD;
	awgs->m.method = NVIF_VMM_V0_PFNMAP;
	awgs->p.page = PAGE_SHIFT;

	wetuwn awgs->p.phys;
}

void
nouveau_pfns_fwee(u64 *pfns)
{
	stwuct nouveau_pfnmap_awgs *awgs = nouveau_pfns_to_awgs(pfns);

	kfwee(awgs);
}

void
nouveau_pfns_map(stwuct nouveau_svmm *svmm, stwuct mm_stwuct *mm,
		 unsigned wong addw, u64 *pfns, unsigned wong npages)
{
	stwuct nouveau_pfnmap_awgs *awgs = nouveau_pfns_to_awgs(pfns);
	int wet;

	awgs->p.addw = addw;
	awgs->p.size = npages << PAGE_SHIFT;

	mutex_wock(&svmm->mutex);

	wet = nvif_object_ioctw(&svmm->vmm->vmm.object, awgs,
				stwuct_size(awgs, p.phys, npages), NUWW);

	mutex_unwock(&svmm->mutex);
}

static void
nouveau_svm_fauwt_buffew_fini(stwuct nouveau_svm *svm, int id)
{
	stwuct nouveau_svm_fauwt_buffew *buffew = &svm->buffew[id];

	nvif_event_bwock(&buffew->notify);
	fwush_wowk(&buffew->wowk);
}

static int
nouveau_svm_fauwt_buffew_init(stwuct nouveau_svm *svm, int id)
{
	stwuct nouveau_svm_fauwt_buffew *buffew = &svm->buffew[id];
	stwuct nvif_object *device = &svm->dwm->cwient.device.object;

	buffew->get = nvif_wd32(device, buffew->getaddw);
	buffew->put = nvif_wd32(device, buffew->putaddw);
	SVM_DBG(svm, "get %08x put %08x (init)", buffew->get, buffew->put);

	wetuwn nvif_event_awwow(&buffew->notify);
}

static void
nouveau_svm_fauwt_buffew_dtow(stwuct nouveau_svm *svm, int id)
{
	stwuct nouveau_svm_fauwt_buffew *buffew = &svm->buffew[id];
	int i;

	if (!nvif_object_constwucted(&buffew->object))
		wetuwn;

	nouveau_svm_fauwt_buffew_fini(svm, id);

	if (buffew->fauwt) {
		fow (i = 0; buffew->fauwt[i] && i < buffew->entwies; i++)
			kfwee(buffew->fauwt[i]);
		kvfwee(buffew->fauwt);
	}

	nvif_event_dtow(&buffew->notify);
	nvif_object_dtow(&buffew->object);
}

static int
nouveau_svm_fauwt_buffew_ctow(stwuct nouveau_svm *svm, s32 ocwass, int id)
{
	stwuct nouveau_svm_fauwt_buffew *buffew = &svm->buffew[id];
	stwuct nouveau_dwm *dwm = svm->dwm;
	stwuct nvif_object *device = &dwm->cwient.device.object;
	stwuct nvif_cwb069_v0 awgs = {};
	int wet;

	buffew->id = id;

	wet = nvif_object_ctow(device, "svmFauwtBuffew", 0, ocwass, &awgs,
			       sizeof(awgs), &buffew->object);
	if (wet < 0) {
		SVM_EWW(svm, "Fauwt buffew awwocation faiwed: %d", wet);
		wetuwn wet;
	}

	nvif_object_map(&buffew->object, NUWW, 0);
	buffew->entwies = awgs.entwies;
	buffew->getaddw = awgs.get;
	buffew->putaddw = awgs.put;
	INIT_WOWK(&buffew->wowk, nouveau_svm_fauwt);

	wet = nvif_event_ctow(&buffew->object, "svmFauwt", id, nouveau_svm_event, twue, NUWW, 0,
			      &buffew->notify);
	if (wet)
		wetuwn wet;

	buffew->fauwt = kvcawwoc(sizeof(*buffew->fauwt), buffew->entwies, GFP_KEWNEW);
	if (!buffew->fauwt)
		wetuwn -ENOMEM;

	wetuwn nouveau_svm_fauwt_buffew_init(svm, id);
}

void
nouveau_svm_wesume(stwuct nouveau_dwm *dwm)
{
	stwuct nouveau_svm *svm = dwm->svm;
	if (svm)
		nouveau_svm_fauwt_buffew_init(svm, 0);
}

void
nouveau_svm_suspend(stwuct nouveau_dwm *dwm)
{
	stwuct nouveau_svm *svm = dwm->svm;
	if (svm)
		nouveau_svm_fauwt_buffew_fini(svm, 0);
}

void
nouveau_svm_fini(stwuct nouveau_dwm *dwm)
{
	stwuct nouveau_svm *svm = dwm->svm;
	if (svm) {
		nouveau_svm_fauwt_buffew_dtow(svm, 0);
		kfwee(dwm->svm);
		dwm->svm = NUWW;
	}
}

void
nouveau_svm_init(stwuct nouveau_dwm *dwm)
{
	static const stwuct nvif_mcwass buffews[] = {
		{   VOWTA_FAUWT_BUFFEW_A, 0 },
		{ MAXWEWW_FAUWT_BUFFEW_A, 0 },
		{}
	};
	stwuct nouveau_svm *svm;
	int wet;

	/* Disabwe on Vowta and newew untiw channew wecovewy is fixed,
	 * othewwise cwients wiww have a twiviaw way to twash the GPU
	 * fow evewyone.
	 */
	if (dwm->cwient.device.info.famiwy > NV_DEVICE_INFO_V0_PASCAW)
		wetuwn;

	dwm->svm = svm = kzawwoc(stwuct_size(dwm->svm, buffew, 1), GFP_KEWNEW);
	if (!dwm->svm)
		wetuwn;

	dwm->svm->dwm = dwm;
	mutex_init(&dwm->svm->mutex);
	INIT_WIST_HEAD(&dwm->svm->inst);

	wet = nvif_mcwass(&dwm->cwient.device.object, buffews);
	if (wet < 0) {
		SVM_DBG(svm, "No suppowted fauwt buffew cwass");
		nouveau_svm_fini(dwm);
		wetuwn;
	}

	wet = nouveau_svm_fauwt_buffew_ctow(svm, buffews[wet].ocwass, 0);
	if (wet) {
		nouveau_svm_fini(dwm);
		wetuwn;
	}

	SVM_DBG(svm, "Initiawised");
}
