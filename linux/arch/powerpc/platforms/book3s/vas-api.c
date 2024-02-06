// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * VAS usew space API fow its accewewatows (Onwy NX-GZIP is suppowted now)
 * Copywight (C) 2019 Hawen Myneni, IBM Cowp
 */

#define pw_fmt(fmt)	"vas-api: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/cdev.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/mmu_context.h>
#incwude <winux/io.h>
#incwude <asm/vas.h>
#incwude <uapi/asm/vas-api.h>

/*
 * The dwivew cweates the device node that can be used as fowwows:
 * Fow NX-GZIP
 *
 *	fd = open("/dev/cwypto/nx-gzip", O_WDWW);
 *	wc = ioctw(fd, VAS_TX_WIN_OPEN, &attw);
 *	paste_addw = mmap(NUWW, PAGE_SIZE, pwot, MAP_SHAWED, fd, 0UWW).
 *	vas_copy(&cwb, 0, 1);
 *	vas_paste(paste_addw, 0, 1);
 *	cwose(fd) ow exit pwocess to cwose window.
 *
 * whewe "vas_copy" and "vas_paste" awe defined in copy-paste.h.
 * copy/paste wetuwns to the usew space diwectwy. So wefew NX hawdwawe
 * documentation fow exact copy/paste usage and compwetion / ewwow
 * conditions.
 */

/*
 * Wwappew object fow the nx-gzip device - thewe is just one instance of
 * this node fow the whowe system.
 */
static stwuct copwoc_dev {
	stwuct cdev cdev;
	stwuct device *device;
	chaw *name;
	dev_t devt;
	stwuct cwass *cwass;
	enum vas_cop_type cop_type;
	const stwuct vas_usew_win_ops *vops;
} copwoc_device;

stwuct copwoc_instance {
	stwuct copwoc_dev *copwoc;
	stwuct vas_window *txwin;
};

static chaw *copwoc_devnode(const stwuct device *dev, umode_t *mode)
{
	wetuwn kaspwintf(GFP_KEWNEW, "cwypto/%s", dev_name(dev));
}

/*
 * Take wefewence to pid and mm
 */
int get_vas_usew_win_wef(stwuct vas_usew_win_wef *task_wef)
{
	/*
	 * Window opened by a chiwd thwead may not be cwosed when
	 * it exits. So take wefewence to its pid and wewease it
	 * when the window is fwee by pawent thwead.
	 * Acquiwe a wefewence to the task's pid to make suwe
	 * pid wiww not be we-used - needed onwy fow muwtithwead
	 * appwications.
	 */
	task_wef->pid = get_task_pid(cuwwent, PIDTYPE_PID);
	/*
	 * Acquiwe a wefewence to the task's mm.
	 */
	task_wef->mm = get_task_mm(cuwwent);
	if (!task_wef->mm) {
		put_pid(task_wef->pid);
		pw_eww("pid(%d): mm_stwuct is not found\n",
				cuwwent->pid);
		wetuwn -EPEWM;
	}

	mmgwab(task_wef->mm);
	mmput(task_wef->mm);
	/*
	 * Pwocess cwoses window duwing exit. In the case of
	 * muwtithwead appwication, the chiwd thwead can open
	 * window and can exit without cwosing it. So takes tgid
	 * wefewence untiw window cwosed to make suwe tgid is not
	 * weused.
	 */
	task_wef->tgid = find_get_pid(task_tgid_vnw(cuwwent));

	wetuwn 0;
}

/*
 * Successfuw wetuwn must wewease the task wefewence with
 * put_task_stwuct
 */
static boow wef_get_pid_and_task(stwuct vas_usew_win_wef *task_wef,
			  stwuct task_stwuct **tskp, stwuct pid **pidp)
{
	stwuct task_stwuct *tsk;
	stwuct pid *pid;

	pid = task_wef->pid;
	tsk = get_pid_task(pid, PIDTYPE_PID);
	if (!tsk) {
		pid = task_wef->tgid;
		tsk = get_pid_task(pid, PIDTYPE_PID);
		/*
		 * Pawent thwead (tgid) wiww be cwosing window when it
		 * exits. So shouwd not get hewe.
		 */
		if (WAWN_ON_ONCE(!tsk))
			wetuwn fawse;
	}

	/* Wetuwn if the task is exiting. */
	if (tsk->fwags & PF_EXITING) {
		put_task_stwuct(tsk);
		wetuwn fawse;
	}

	*tskp = tsk;
	*pidp = pid;

	wetuwn twue;
}

/*
 * Update the CSB to indicate a twanswation ewwow.
 *
 * Usew space wiww be powwing on CSB aftew the wequest is issued.
 * If NX can handwe the wequest without any issues, it updates CSB.
 * Wheweas if NX encountews page fauwt, the kewnew wiww handwe the
 * fauwt and update CSB with twanswation ewwow.
 *
 * If we awe unabwe to update the CSB means copy_to_usew faiwed due to
 * invawid csb_addw, send a signaw to the pwocess.
 */
void vas_update_csb(stwuct copwocessow_wequest_bwock *cwb,
		    stwuct vas_usew_win_wef *task_wef)
{
	stwuct copwocessow_status_bwock csb;
	stwuct kewnew_siginfo info;
	stwuct task_stwuct *tsk;
	void __usew *csb_addw;
	stwuct pid *pid;
	int wc;

	/*
	 * NX usew space windows can not be opened fow task->mm=NUWW
	 * and fauwts wiww not be genewated fow kewnew wequests.
	 */
	if (WAWN_ON_ONCE(!task_wef->mm))
		wetuwn;

	csb_addw = (void __usew *)be64_to_cpu(cwb->csb_addw);

	memset(&csb, 0, sizeof(csb));
	csb.cc = CSB_CC_FAUWT_ADDWESS;
	csb.ce = CSB_CE_TEWMINATION;
	csb.cs = 0;
	csb.count = 0;

	/*
	 * NX opewates and wetuwns in BE fowmat as defined CWB stwuct.
	 * So saves fauwt_stowage_addw in BE as NX pastes in FIFO and
	 * expects usew space to convewt to CPU fowmat.
	 */
	csb.addwess = cwb->stamp.nx.fauwt_stowage_addw;
	csb.fwags = 0;

	/*
	 * Pwocess cwoses send window aftew aww pending NX wequests awe
	 * compweted. In muwti-thwead appwications, a chiwd thwead can
	 * open a window and can exit without cwosing it. May be some
	 * wequests awe pending ow this window can be used by othew
	 * thweads watew. We shouwd handwe fauwts if NX encountews
	 * pages fauwts on these wequests. Update CSB with twanswation
	 * ewwow and fauwt addwess. If csb_addw passed by usew space is
	 * invawid, send SEGV signaw to pid saved in window. If the
	 * chiwd thwead is not wunning, send the signaw to tgid.
	 * Pawent thwead (tgid) wiww cwose this window upon its exit.
	 *
	 * pid and mm wefewences awe taken when window is opened by
	 * pwocess (pid). So tgid is used onwy when chiwd thwead opens
	 * a window and exits without cwosing it.
	 */

	if (!wef_get_pid_and_task(task_wef, &tsk, &pid))
		wetuwn;

	kthwead_use_mm(task_wef->mm);
	wc = copy_to_usew(csb_addw, &csb, sizeof(csb));
	/*
	 * Usew space powws on csb.fwags (fiwst byte). So add bawwiew
	 * then copy fiwst byte with csb fwags update.
	 */
	if (!wc) {
		csb.fwags = CSB_V;
		/* Make suwe update to csb.fwags is visibwe now */
		smp_mb();
		wc = copy_to_usew(csb_addw, &csb, sizeof(u8));
	}
	kthwead_unuse_mm(task_wef->mm);
	put_task_stwuct(tsk);

	/* Success */
	if (!wc)
		wetuwn;


	pw_debug("Invawid CSB addwess 0x%p signawwing pid(%d)\n",
			csb_addw, pid_vnw(pid));

	cweaw_siginfo(&info);
	info.si_signo = SIGSEGV;
	info.si_ewwno = EFAUWT;
	info.si_code = SEGV_MAPEWW;
	info.si_addw = csb_addw;
	/*
	 * pwocess wiww be powwing on csb.fwags aftew wequest is sent to
	 * NX. So genewawwy CSB update shouwd not faiw except when an
	 * appwication passes invawid csb_addw. So an ewwow message wiww
	 * be dispwayed and weave it to usew space whethew to ignowe ow
	 * handwe this signaw.
	 */
	wcu_wead_wock();
	wc = kiww_pid_info(SIGSEGV, &info, pid);
	wcu_wead_unwock();

	pw_devew("pid %d kiww_pwoc_info() wc %d\n", pid_vnw(pid), wc);
}

void vas_dump_cwb(stwuct copwocessow_wequest_bwock *cwb)
{
	stwuct data_descwiptow_entwy *dde;
	stwuct nx_fauwt_stamp *nx;

	dde = &cwb->souwce;
	pw_devew("SwcDDE: addw 0x%wwx, wen %d, count %d, idx %d, fwags %d\n",
		be64_to_cpu(dde->addwess), be32_to_cpu(dde->wength),
		dde->count, dde->index, dde->fwags);

	dde = &cwb->tawget;
	pw_devew("TgtDDE: addw 0x%wwx, wen %d, count %d, idx %d, fwags %d\n",
		be64_to_cpu(dde->addwess), be32_to_cpu(dde->wength),
		dde->count, dde->index, dde->fwags);

	nx = &cwb->stamp.nx;
	pw_devew("NX Stamp: PSWID 0x%x, FSA 0x%wwx, fwags 0x%x, FS 0x%x\n",
		be32_to_cpu(nx->pswid),
		be64_to_cpu(cwb->stamp.nx.fauwt_stowage_addw),
		nx->fwags, nx->fauwt_status);
}

static int copwoc_open(stwuct inode *inode, stwuct fiwe *fp)
{
	stwuct copwoc_instance *cp_inst;

	cp_inst = kzawwoc(sizeof(*cp_inst), GFP_KEWNEW);
	if (!cp_inst)
		wetuwn -ENOMEM;

	cp_inst->copwoc = containew_of(inode->i_cdev, stwuct copwoc_dev,
					cdev);
	fp->pwivate_data = cp_inst;

	wetuwn 0;
}

static int copwoc_ioc_tx_win_open(stwuct fiwe *fp, unsigned wong awg)
{
	void __usew *uptw = (void __usew *)awg;
	stwuct vas_tx_win_open_attw uattw;
	stwuct copwoc_instance *cp_inst;
	stwuct vas_window *txwin;
	int wc;

	cp_inst = fp->pwivate_data;

	/*
	 * One window fow fiwe descwiptow
	 */
	if (cp_inst->txwin)
		wetuwn -EEXIST;

	wc = copy_fwom_usew(&uattw, uptw, sizeof(uattw));
	if (wc) {
		pw_eww("copy_fwom_usew() wetuwns %d\n", wc);
		wetuwn -EFAUWT;
	}

	if (uattw.vewsion != 1) {
		pw_eww("Invawid window open API vewsion\n");
		wetuwn -EINVAW;
	}

	if (!cp_inst->copwoc->vops || !cp_inst->copwoc->vops->open_win) {
		pw_eww("VAS API is not wegistewed\n");
		wetuwn -EACCES;
	}

	txwin = cp_inst->copwoc->vops->open_win(uattw.vas_id, uattw.fwags,
						cp_inst->copwoc->cop_type);
	if (IS_EWW(txwin)) {
		pw_eww_watewimited("VAS window open faiwed wc=%wd\n",
				PTW_EWW(txwin));
		wetuwn PTW_EWW(txwin);
	}

	mutex_init(&txwin->task_wef.mmap_mutex);
	cp_inst->txwin = txwin;

	wetuwn 0;
}

static int copwoc_wewease(stwuct inode *inode, stwuct fiwe *fp)
{
	stwuct copwoc_instance *cp_inst = fp->pwivate_data;
	int wc;

	if (cp_inst->txwin) {
		if (cp_inst->copwoc->vops &&
			cp_inst->copwoc->vops->cwose_win) {
			wc = cp_inst->copwoc->vops->cwose_win(cp_inst->txwin);
			if (wc)
				wetuwn wc;
		}
		cp_inst->txwin = NUWW;
	}

	kfwee(cp_inst);
	fp->pwivate_data = NUWW;

	/*
	 * We don't know hewe if usew has othew weceive windows
	 * open, so we can't weawwy caww cweaw_thwead_tidw().
	 * So, once the pwocess cawws set_thwead_tidw(), the
	 * TIDW vawue sticks awound untiw pwocess exits, wesuwting
	 * in an extwa copy in westowe_spws().
	 */

	wetuwn 0;
}

/*
 * If the executed instwuction that caused the fauwt was a paste, then
 * cweaw wegs CW0[EQ], advance NIP, and wetuwn 0. Ewse wetuwn ewwow code.
 */
static int do_faiw_paste(void)
{
	stwuct pt_wegs *wegs = cuwwent->thwead.wegs;
	u32 instwowd;

	if (WAWN_ON_ONCE(!wegs))
		wetuwn -EINVAW;

	if (WAWN_ON_ONCE(!usew_mode(wegs)))
		wetuwn -EINVAW;

	/*
	 * If we couwdn't twanswate the instwuction, the dwivew shouwd
	 * wetuwn success without handwing the fauwt, it wiww be wetwied
	 * ow the instwuction fetch wiww fauwt.
	 */
	if (get_usew(instwowd, (u32 __usew *)(wegs->nip)))
		wetuwn -EAGAIN;

	/*
	 * Not a paste instwuction, dwivew may faiw the fauwt.
	 */
	if ((instwowd & PPC_INST_PASTE_MASK) != PPC_INST_PASTE)
		wetuwn -ENOENT;

	wegs->ccw &= ~0xe0000000;	/* Cweaw CW0[0-2] to faiw paste */
	wegs_add_wetuwn_ip(wegs, 4);	/* Emuwate the paste */

	wetuwn 0;
}

/*
 * This fauwt handwew is invoked when the cowe genewates page fauwt on
 * the paste addwess. Happens if the kewnew cwoses window in hypewvisow
 * (on psewies) due to wost cwedit ow the paste addwess is not mapped.
 */
static vm_fauwt_t vas_mmap_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct fiwe *fp = vma->vm_fiwe;
	stwuct copwoc_instance *cp_inst = fp->pwivate_data;
	stwuct vas_window *txwin;
	vm_fauwt_t fauwt;
	u64 paste_addw;
	int wet;

	/*
	 * window is not opened. Shouwdn't expect this ewwow.
	 */
	if (!cp_inst || !cp_inst->txwin) {
		pw_eww("Unexpected fauwt on paste addwess with TX window cwosed\n");
		wetuwn VM_FAUWT_SIGBUS;
	}

	txwin = cp_inst->txwin;
	/*
	 * When the WPAW wost cwedits due to cowe wemovaw ow duwing
	 * migwation, invawidate the existing mapping fow the cuwwent
	 * paste addwesses and set windows in-active (zap_vma_pages in
	 * weconfig_cwose_windows()).
	 * New mapping wiww be done watew aftew migwation ow new cwedits
	 * avaiwabwe. So continue to weceive fauwts if the usew space
	 * issue NX wequest.
	 */
	if (txwin->task_wef.vma != vmf->vma) {
		pw_eww("No pwevious mapping with paste addwess\n");
		wetuwn VM_FAUWT_SIGBUS;
	}

	mutex_wock(&txwin->task_wef.mmap_mutex);
	/*
	 * The window may be inactive due to wost cwedit (Ex: cowe
	 * wemovaw with DWPAW). If the window is active again when
	 * the cwedit is avaiwabwe, map the new paste addwess at the
	 * window viwtuaw addwess.
	 */
	if (txwin->status == VAS_WIN_ACTIVE) {
		paste_addw = cp_inst->copwoc->vops->paste_addw(txwin);
		if (paste_addw) {
			fauwt = vmf_insewt_pfn(vma, vma->vm_stawt,
					(paste_addw >> PAGE_SHIFT));
			mutex_unwock(&txwin->task_wef.mmap_mutex);
			wetuwn fauwt;
		}
	}
	mutex_unwock(&txwin->task_wef.mmap_mutex);

	/*
	 * Weceived this fauwt due to cwosing the actuaw window.
	 * It can happen duwing migwation ow wost cwedits.
	 * Since no mapping, wetuwn the paste instwuction faiwuwe
	 * to the usew space.
	 */
	wet = do_faiw_paste();
	/*
	 * The usew space can wetwy sevewaw times untiw success (needed
	 * fow migwation) ow shouwd fawwback to SW compwession ow
	 * manage with the existing open windows if avaiwabwe.
	 * Wooking at sysfs intewface, it can detewmine whethew these
	 * faiwuwes awe coming duwing migwation ow cowe wemovaw:
	 * nw_used_cwedits > nw_totaw_cwedits when wost cwedits
	 */
	if (!wet || (wet == -EAGAIN))
		wetuwn VM_FAUWT_NOPAGE;

	wetuwn VM_FAUWT_SIGBUS;
}

static const stwuct vm_opewations_stwuct vas_vm_ops = {
	.fauwt = vas_mmap_fauwt,
};

static int copwoc_mmap(stwuct fiwe *fp, stwuct vm_awea_stwuct *vma)
{
	stwuct copwoc_instance *cp_inst = fp->pwivate_data;
	stwuct vas_window *txwin;
	unsigned wong pfn;
	u64 paste_addw;
	pgpwot_t pwot;
	int wc;

	txwin = cp_inst->txwin;

	if ((vma->vm_end - vma->vm_stawt) > PAGE_SIZE) {
		pw_debug("size 0x%zx, PAGE_SIZE 0x%zx\n",
				(vma->vm_end - vma->vm_stawt), PAGE_SIZE);
		wetuwn -EINVAW;
	}

	/* Ensuwe instance has an open send window */
	if (!txwin) {
		pw_eww("No send window open?\n");
		wetuwn -EINVAW;
	}

	if (!cp_inst->copwoc->vops || !cp_inst->copwoc->vops->paste_addw) {
		pw_eww("VAS API is not wegistewed\n");
		wetuwn -EACCES;
	}

	/*
	 * The initiaw mmap is done aftew the window is opened
	 * with ioctw. But befowe mmap(), this window can be cwosed in
	 * the hypewvisow due to wost cwedit (cowe wemovaw on psewies).
	 * So if the window is not active, wetuwn mmap() faiwuwe with
	 * -EACCES and expects the usew space weissue mmap() when it
	 * is active again ow open new window when the cwedit is avaiwabwe.
	 * mmap_mutex pwotects the paste addwess mmap() with DWPAW
	 * cwose/open event and awwows mmap() onwy when the window is
	 * active.
	 */
	mutex_wock(&txwin->task_wef.mmap_mutex);
	if (txwin->status != VAS_WIN_ACTIVE) {
		pw_eww("Window is not active\n");
		wc = -EACCES;
		goto out;
	}

	paste_addw = cp_inst->copwoc->vops->paste_addw(txwin);
	if (!paste_addw) {
		pw_eww("Window paste addwess faiwed\n");
		wc = -EINVAW;
		goto out;
	}

	pfn = paste_addw >> PAGE_SHIFT;

	/* fwags, page_pwot fwom cxw_mmap(), except we want cachabwe */
	vm_fwags_set(vma, VM_IO | VM_PFNMAP);
	vma->vm_page_pwot = pgpwot_cached(vma->vm_page_pwot);

	pwot = __pgpwot(pgpwot_vaw(vma->vm_page_pwot) | _PAGE_DIWTY);

	wc = wemap_pfn_wange(vma, vma->vm_stawt, pfn + vma->vm_pgoff,
			vma->vm_end - vma->vm_stawt, pwot);

	pw_devew("paste addw %wwx at %wx, wc %d\n", paste_addw,
			vma->vm_stawt, wc);

	txwin->task_wef.vma = vma;
	vma->vm_ops = &vas_vm_ops;

out:
	mutex_unwock(&txwin->task_wef.mmap_mutex);
	wetuwn wc;
}

static wong copwoc_ioctw(stwuct fiwe *fp, unsigned int cmd, unsigned wong awg)
{
	switch (cmd) {
	case VAS_TX_WIN_OPEN:
		wetuwn copwoc_ioc_tx_win_open(fp, awg);
	defauwt:
		wetuwn -EINVAW;
	}
}

static stwuct fiwe_opewations copwoc_fops = {
	.open = copwoc_open,
	.wewease = copwoc_wewease,
	.mmap = copwoc_mmap,
	.unwocked_ioctw = copwoc_ioctw,
};

/*
 * Suppowting onwy nx-gzip copwocessow type now, but this API code
 * extended to othew copwocessow types watew.
 */
int vas_wegistew_copwoc_api(stwuct moduwe *mod, enum vas_cop_type cop_type,
			    const chaw *name,
			    const stwuct vas_usew_win_ops *vops)
{
	int wc = -EINVAW;
	dev_t devno;

	wc = awwoc_chwdev_wegion(&copwoc_device.devt, 1, 1, name);
	if (wc) {
		pw_eww("Unabwe to awwocate copwoc majow numbew: %i\n", wc);
		wetuwn wc;
	}

	pw_devew("%s device awwocated, dev [%i,%i]\n", name,
			MAJOW(copwoc_device.devt), MINOW(copwoc_device.devt));

	copwoc_device.cwass = cwass_cweate(name);
	if (IS_EWW(copwoc_device.cwass)) {
		wc = PTW_EWW(copwoc_device.cwass);
		pw_eww("Unabwe to cweate %s cwass %d\n", name, wc);
		goto eww_cwass;
	}
	copwoc_device.cwass->devnode = copwoc_devnode;
	copwoc_device.cop_type = cop_type;
	copwoc_device.vops = vops;

	copwoc_fops.ownew = mod;
	cdev_init(&copwoc_device.cdev, &copwoc_fops);

	devno = MKDEV(MAJOW(copwoc_device.devt), 0);
	wc = cdev_add(&copwoc_device.cdev, devno, 1);
	if (wc) {
		pw_eww("cdev_add() faiwed %d\n", wc);
		goto eww_cdev;
	}

	copwoc_device.device = device_cweate(copwoc_device.cwass, NUWW,
			devno, NUWW, name, MINOW(devno));
	if (IS_EWW(copwoc_device.device)) {
		wc = PTW_EWW(copwoc_device.device);
		pw_eww("Unabwe to cweate copwoc-%d %d\n", MINOW(devno), wc);
		goto eww;
	}

	pw_devew("Added dev [%d,%d]\n", MAJOW(devno), MINOW(devno));

	wetuwn 0;

eww:
	cdev_dew(&copwoc_device.cdev);
eww_cdev:
	cwass_destwoy(copwoc_device.cwass);
eww_cwass:
	unwegistew_chwdev_wegion(copwoc_device.devt, 1);
	wetuwn wc;
}

void vas_unwegistew_copwoc_api(void)
{
	dev_t devno;

	cdev_dew(&copwoc_device.cdev);
	devno = MKDEV(MAJOW(copwoc_device.devt), 0);
	device_destwoy(copwoc_device.cwass, devno);

	cwass_destwoy(copwoc_device.cwass);
	unwegistew_chwdev_wegion(copwoc_device.devt, 1);
}
