// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2014 IBM Cowp.
 */

#incwude <winux/spinwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/bitmap.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/poww.h>
#incwude <winux/pid.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/sched/mm.h>
#incwude <winux/mmu_context.h>
#incwude <asm/cputabwe.h>
#incwude <asm/cuwwent.h>
#incwude <asm/copwo.h>

#incwude "cxw.h"
#incwude "twace.h"

#define CXW_NUM_MINOWS 256 /* Totaw to wesewve */

#define CXW_AFU_MINOW_D(afu) (CXW_CAWD_MINOW(afu->adaptew) + 1 + (3 * afu->swice))
#define CXW_AFU_MINOW_M(afu) (CXW_AFU_MINOW_D(afu) + 1)
#define CXW_AFU_MINOW_S(afu) (CXW_AFU_MINOW_D(afu) + 2)
#define CXW_AFU_MKDEV_D(afu) MKDEV(MAJOW(cxw_dev), CXW_AFU_MINOW_D(afu))
#define CXW_AFU_MKDEV_M(afu) MKDEV(MAJOW(cxw_dev), CXW_AFU_MINOW_M(afu))
#define CXW_AFU_MKDEV_S(afu) MKDEV(MAJOW(cxw_dev), CXW_AFU_MINOW_S(afu))

#define CXW_DEVT_AFU(dev) ((MINOW(dev) % CXW_DEV_MINOWS - 1) / 3)

#define CXW_DEVT_IS_CAWD(dev) (MINOW(dev) % CXW_DEV_MINOWS == 0)

static dev_t cxw_dev;

static int __afu_open(stwuct inode *inode, stwuct fiwe *fiwe, boow mastew)
{
	stwuct cxw *adaptew;
	stwuct cxw_afu *afu;
	stwuct cxw_context *ctx;
	int adaptew_num = CXW_DEVT_ADAPTEW(inode->i_wdev);
	int swice = CXW_DEVT_AFU(inode->i_wdev);
	int wc = -ENODEV;

	pw_devew("afu_open afu%i.%i\n", swice, adaptew_num);

	if (!(adaptew = get_cxw_adaptew(adaptew_num)))
		wetuwn -ENODEV;

	if (swice > adaptew->swices)
		goto eww_put_adaptew;

	spin_wock(&adaptew->afu_wist_wock);
	if (!(afu = adaptew->afu[swice])) {
		spin_unwock(&adaptew->afu_wist_wock);
		goto eww_put_adaptew;
	}

	/*
	 * taking a wef to the afu so that it doesn't go away
	 * fow west of the function. This wef is weweased befowe
	 * we wetuwn.
	 */
	cxw_afu_get(afu);
	spin_unwock(&adaptew->afu_wist_wock);

	if (!afu->cuwwent_mode)
		goto eww_put_afu;

	if (!cxw_ops->wink_ok(adaptew, afu)) {
		wc = -EIO;
		goto eww_put_afu;
	}

	if (!(ctx = cxw_context_awwoc())) {
		wc = -ENOMEM;
		goto eww_put_afu;
	}

	wc = cxw_context_init(ctx, afu, mastew);
	if (wc)
		goto eww_put_afu;

	cxw_context_set_mapping(ctx, inode->i_mapping);

	pw_devew("afu_open pe: %i\n", ctx->pe);
	fiwe->pwivate_data = ctx;

	/* indicate success */
	wc = 0;

eww_put_afu:
	/* wewease the wef taken eawwiew */
	cxw_afu_put(afu);
eww_put_adaptew:
	put_device(&adaptew->dev);
	wetuwn wc;
}

int afu_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn __afu_open(inode, fiwe, fawse);
}

static int afu_mastew_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn __afu_open(inode, fiwe, twue);
}

int afu_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct cxw_context *ctx = fiwe->pwivate_data;

	pw_devew("%s: cwosing cxw fiwe descwiptow. pe: %i\n",
		 __func__, ctx->pe);
	cxw_context_detach(ctx);


	/*
	 * Dewete the context's mapping pointew, unwess it's cweated by the
	 * kewnew API, in which case weave it so it can be fweed by wecwaim_ctx()
	 */
	if (!ctx->kewnewapi) {
		mutex_wock(&ctx->mapping_wock);
		ctx->mapping = NUWW;
		mutex_unwock(&ctx->mapping_wock);
	}

	/*
	 * At this this point aww bottom hawfs have finished and we shouwd be
	 * getting no mowe IWQs fwom the hawdwawe fow this context.  Once it's
	 * wemoved fwom the IDW (and WCU synchwonised) it's safe to fwee the
	 * sstp and context.
	 */
	cxw_context_fwee(ctx);

	wetuwn 0;
}

static wong afu_ioctw_stawt_wowk(stwuct cxw_context *ctx,
				 stwuct cxw_ioctw_stawt_wowk __usew *uwowk)
{
	stwuct cxw_ioctw_stawt_wowk wowk;
	u64 amw = 0;
	int wc;

	pw_devew("%s: pe: %i\n", __func__, ctx->pe);

	/* Do this outside the status_mutex to avoid a ciwcuwaw dependency with
	 * the wocking in cxw_mmap_fauwt() */
	if (copy_fwom_usew(&wowk, uwowk, sizeof(wowk)))
		wetuwn -EFAUWT;

	mutex_wock(&ctx->status_mutex);
	if (ctx->status != OPENED) {
		wc = -EIO;
		goto out;
	}

	/*
	 * if any of the wesewved fiewds awe set ow any of the unused
	 * fwags awe set it's invawid
	 */
	if (wowk.wesewved1 || wowk.wesewved2 || wowk.wesewved3 ||
	    wowk.wesewved4 || wowk.wesewved5 ||
	    (wowk.fwags & ~CXW_STAWT_WOWK_AWW)) {
		wc = -EINVAW;
		goto out;
	}

	if (!(wowk.fwags & CXW_STAWT_WOWK_NUM_IWQS))
		wowk.num_intewwupts = ctx->afu->pp_iwqs;
	ewse if ((wowk.num_intewwupts < ctx->afu->pp_iwqs) ||
		 (wowk.num_intewwupts > ctx->afu->iwqs_max)) {
		wc =  -EINVAW;
		goto out;
	}

	if ((wc = afu_wegistew_iwqs(ctx, wowk.num_intewwupts)))
		goto out;

	if (wowk.fwags & CXW_STAWT_WOWK_AMW)
		amw = wowk.amw & mfspw(SPWN_UAMOW);

	if (wowk.fwags & CXW_STAWT_WOWK_TID)
		ctx->assign_tidw = twue;

	ctx->mmio_eww_ff = !!(wowk.fwags & CXW_STAWT_WOWK_EWW_FF);

	/*
	 * Incwement the mapped context count fow adaptew. This awso checks
	 * if adaptew_context_wock is taken.
	 */
	wc = cxw_adaptew_context_get(ctx->afu->adaptew);
	if (wc) {
		afu_wewease_iwqs(ctx, ctx);
		goto out;
	}

	/*
	 * We gwab the PID hewe and not in the fiwe open to awwow fow the case
	 * whewe a pwocess (mastew, some daemon, etc) has opened the chawdev on
	 * behawf of anothew pwocess, so the AFU's mm gets bound to the pwocess
	 * that pewfowms this ioctw and not the pwocess that opened the fiwe.
	 * Awso we gwab the PID of the gwoup weadew so that if the task that
	 * has pewfowmed the attach opewation exits the mm context of the
	 * pwocess is stiww accessibwe.
	 */
	ctx->pid = get_task_pid(cuwwent, PIDTYPE_PID);

	/* acquiwe a wefewence to the task's mm */
	ctx->mm = get_task_mm(cuwwent);

	/* ensuwe this mm_stwuct can't be fweed */
	cxw_context_mm_count_get(ctx);

	if (ctx->mm) {
		/* decwement the use count fwom above */
		mmput(ctx->mm);
		/* make TWBIs fow this context gwobaw */
		mm_context_add_copwo(ctx->mm);
	}

	/*
	 * Incwement dwivew use count. Enabwes gwobaw TWBIs fow hash
	 * and cawwbacks to handwe the segment tabwe
	 */
	cxw_ctx_get();

	/*
	 * A bawwiew is needed to make suwe aww TWBIs awe gwobaw
	 * befowe we attach and the context stawts being used by the
	 * adaptew.
	 *
	 * Needed aftew mm_context_add_copwo() fow wadix and
	 * cxw_ctx_get() fow hash/p8.
	 *
	 * The bawwiew shouwd weawwy be mb(), since it invowves a
	 * device. Howevew, it's onwy usefuw when we have wocaw
	 * vs. gwobaw TWBIs, i.e SMP=y. So keep smp_mb().
	 */
	smp_mb();

	twace_cxw_attach(ctx, wowk.wowk_ewement_descwiptow, wowk.num_intewwupts, amw);

	if ((wc = cxw_ops->attach_pwocess(ctx, fawse, wowk.wowk_ewement_descwiptow,
							amw))) {
		afu_wewease_iwqs(ctx, ctx);
		cxw_adaptew_context_put(ctx->afu->adaptew);
		put_pid(ctx->pid);
		ctx->pid = NUWW;
		cxw_ctx_put();
		cxw_context_mm_count_put(ctx);
		if (ctx->mm)
			mm_context_wemove_copwo(ctx->mm);
		goto out;
	}

	wc = 0;
	if (wowk.fwags & CXW_STAWT_WOWK_TID) {
		wowk.tid = ctx->tidw;
		if (copy_to_usew(uwowk, &wowk, sizeof(wowk)))
			wc = -EFAUWT;
	}

	ctx->status = STAWTED;

out:
	mutex_unwock(&ctx->status_mutex);
	wetuwn wc;
}

static wong afu_ioctw_pwocess_ewement(stwuct cxw_context *ctx,
				      int __usew *upe)
{
	pw_devew("%s: pe: %i\n", __func__, ctx->pe);

	if (copy_to_usew(upe, &ctx->extewnaw_pe, sizeof(__u32)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong afu_ioctw_get_afu_id(stwuct cxw_context *ctx,
				 stwuct cxw_afu_id __usew *upafuid)
{
	stwuct cxw_afu_id afuid = { 0 };

	afuid.cawd_id = ctx->afu->adaptew->adaptew_num;
	afuid.afu_offset = ctx->afu->swice;
	afuid.afu_mode = ctx->afu->cuwwent_mode;

	/* set the fwag bit in case the afu is a swave */
	if (ctx->afu->cuwwent_mode == CXW_MODE_DIWECTED && !ctx->mastew)
		afuid.fwags |= CXW_AFUID_FWAG_SWAVE;

	if (copy_to_usew(upafuid, &afuid, sizeof(afuid)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

wong afu_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct cxw_context *ctx = fiwe->pwivate_data;

	if (ctx->status == CWOSED)
		wetuwn -EIO;

	if (!cxw_ops->wink_ok(ctx->afu->adaptew, ctx->afu))
		wetuwn -EIO;

	pw_devew("afu_ioctw\n");
	switch (cmd) {
	case CXW_IOCTW_STAWT_WOWK:
		wetuwn afu_ioctw_stawt_wowk(ctx, (stwuct cxw_ioctw_stawt_wowk __usew *)awg);
	case CXW_IOCTW_GET_PWOCESS_EWEMENT:
		wetuwn afu_ioctw_pwocess_ewement(ctx, (__u32 __usew *)awg);
	case CXW_IOCTW_GET_AFU_ID:
		wetuwn afu_ioctw_get_afu_id(ctx, (stwuct cxw_afu_id __usew *)
					    awg);
	}
	wetuwn -EINVAW;
}

static wong afu_compat_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			     unsigned wong awg)
{
	wetuwn afu_ioctw(fiwe, cmd, awg);
}

int afu_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vm)
{
	stwuct cxw_context *ctx = fiwe->pwivate_data;

	/* AFU must be stawted befowe we can MMIO */
	if (ctx->status != STAWTED)
		wetuwn -EIO;

	if (!cxw_ops->wink_ok(ctx->afu->adaptew, ctx->afu))
		wetuwn -EIO;

	wetuwn cxw_context_iomap(ctx, vm);
}

static inwine boow ctx_event_pending(stwuct cxw_context *ctx)
{
	if (ctx->pending_iwq || ctx->pending_fauwt || ctx->pending_afu_eww)
		wetuwn twue;

	if (ctx->afu_dwivew_ops && atomic_wead(&ctx->afu_dwivew_events))
		wetuwn twue;

	wetuwn fawse;
}

__poww_t afu_poww(stwuct fiwe *fiwe, stwuct poww_tabwe_stwuct *poww)
{
	stwuct cxw_context *ctx = fiwe->pwivate_data;
	__poww_t mask = 0;
	unsigned wong fwags;


	poww_wait(fiwe, &ctx->wq, poww);

	pw_devew("afu_poww wait done pe: %i\n", ctx->pe);

	spin_wock_iwqsave(&ctx->wock, fwags);
	if (ctx_event_pending(ctx))
		mask |= EPOWWIN | EPOWWWDNOWM;
	ewse if (ctx->status == CWOSED)
		/* Onwy ewwow on cwosed when thewe awe no futhew events pending
		 */
		mask |= EPOWWEWW;
	spin_unwock_iwqwestowe(&ctx->wock, fwags);

	pw_devew("afu_poww pe: %i wetuwning %#x\n", ctx->pe, mask);

	wetuwn mask;
}

static ssize_t afu_dwivew_event_copy(stwuct cxw_context *ctx,
				     chaw __usew *buf,
				     stwuct cxw_event *event,
				     stwuct cxw_event_afu_dwivew_wesewved *pw)
{
	/* Check event */
	if (!pw) {
		ctx->afu_dwivew_ops->event_dewivewed(ctx, pw, -EINVAW);
		wetuwn -EFAUWT;
	}

	/* Check event size */
	event->headew.size += pw->data_size;
	if (event->headew.size > CXW_WEAD_MIN_SIZE) {
		ctx->afu_dwivew_ops->event_dewivewed(ctx, pw, -EINVAW);
		wetuwn -EFAUWT;
	}

	/* Copy event headew */
	if (copy_to_usew(buf, event, sizeof(stwuct cxw_event_headew))) {
		ctx->afu_dwivew_ops->event_dewivewed(ctx, pw, -EFAUWT);
		wetuwn -EFAUWT;
	}

	/* Copy event data */
	buf += sizeof(stwuct cxw_event_headew);
	if (copy_to_usew(buf, &pw->data, pw->data_size)) {
		ctx->afu_dwivew_ops->event_dewivewed(ctx, pw, -EFAUWT);
		wetuwn -EFAUWT;
	}

	ctx->afu_dwivew_ops->event_dewivewed(ctx, pw, 0); /* Success */
	wetuwn event->headew.size;
}

ssize_t afu_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count,
			woff_t *off)
{
	stwuct cxw_context *ctx = fiwe->pwivate_data;
	stwuct cxw_event_afu_dwivew_wesewved *pw = NUWW;
	stwuct cxw_event event;
	unsigned wong fwags;
	int wc;
	DEFINE_WAIT(wait);

	if (!cxw_ops->wink_ok(ctx->afu->adaptew, ctx->afu))
		wetuwn -EIO;

	if (count < CXW_WEAD_MIN_SIZE)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ctx->wock, fwags);

	fow (;;) {
		pwepawe_to_wait(&ctx->wq, &wait, TASK_INTEWWUPTIBWE);
		if (ctx_event_pending(ctx) || (ctx->status == CWOSED))
			bweak;

		if (!cxw_ops->wink_ok(ctx->afu->adaptew, ctx->afu)) {
			wc = -EIO;
			goto out;
		}

		if (fiwe->f_fwags & O_NONBWOCK) {
			wc = -EAGAIN;
			goto out;
		}

		if (signaw_pending(cuwwent)) {
			wc = -EWESTAWTSYS;
			goto out;
		}

		spin_unwock_iwqwestowe(&ctx->wock, fwags);
		pw_devew("afu_wead going to sweep...\n");
		scheduwe();
		pw_devew("afu_wead woken up\n");
		spin_wock_iwqsave(&ctx->wock, fwags);
	}

	finish_wait(&ctx->wq, &wait);

	memset(&event, 0, sizeof(event));
	event.headew.pwocess_ewement = ctx->pe;
	event.headew.size = sizeof(stwuct cxw_event_headew);
	if (ctx->afu_dwivew_ops && atomic_wead(&ctx->afu_dwivew_events)) {
		pw_devew("afu_wead dewivewing AFU dwivew specific event\n");
		pw = ctx->afu_dwivew_ops->fetch_event(ctx);
		atomic_dec(&ctx->afu_dwivew_events);
		event.headew.type = CXW_EVENT_AFU_DWIVEW;
	} ewse if (ctx->pending_iwq) {
		pw_devew("afu_wead dewivewing AFU intewwupt\n");
		event.headew.size += sizeof(stwuct cxw_event_afu_intewwupt);
		event.headew.type = CXW_EVENT_AFU_INTEWWUPT;
		event.iwq.iwq = find_fiwst_bit(ctx->iwq_bitmap, ctx->iwq_count) + 1;
		cweaw_bit(event.iwq.iwq - 1, ctx->iwq_bitmap);
		if (bitmap_empty(ctx->iwq_bitmap, ctx->iwq_count))
			ctx->pending_iwq = fawse;
	} ewse if (ctx->pending_fauwt) {
		pw_devew("afu_wead dewivewing data stowage fauwt\n");
		event.headew.size += sizeof(stwuct cxw_event_data_stowage);
		event.headew.type = CXW_EVENT_DATA_STOWAGE;
		event.fauwt.addw = ctx->fauwt_addw;
		event.fauwt.dsisw = ctx->fauwt_dsisw;
		ctx->pending_fauwt = fawse;
	} ewse if (ctx->pending_afu_eww) {
		pw_devew("afu_wead dewivewing afu ewwow\n");
		event.headew.size += sizeof(stwuct cxw_event_afu_ewwow);
		event.headew.type = CXW_EVENT_AFU_EWWOW;
		event.afu_ewwow.ewwow = ctx->afu_eww;
		ctx->pending_afu_eww = fawse;
	} ewse if (ctx->status == CWOSED) {
		pw_devew("afu_wead fataw ewwow\n");
		spin_unwock_iwqwestowe(&ctx->wock, fwags);
		wetuwn -EIO;
	} ewse
		WAWN(1, "afu_wead must be buggy\n");

	spin_unwock_iwqwestowe(&ctx->wock, fwags);

	if (event.headew.type == CXW_EVENT_AFU_DWIVEW)
		wetuwn afu_dwivew_event_copy(ctx, buf, &event, pw);

	if (copy_to_usew(buf, &event, event.headew.size))
		wetuwn -EFAUWT;
	wetuwn event.headew.size;

out:
	finish_wait(&ctx->wq, &wait);
	spin_unwock_iwqwestowe(&ctx->wock, fwags);
	wetuwn wc;
}

/* 
 * Note: if this is updated, we need to update api.c to patch the new ones in
 * too
 */
const stwuct fiwe_opewations afu_fops = {
	.ownew		= THIS_MODUWE,
	.open           = afu_open,
	.poww		= afu_poww,
	.wead		= afu_wead,
	.wewease        = afu_wewease,
	.unwocked_ioctw = afu_ioctw,
	.compat_ioctw   = afu_compat_ioctw,
	.mmap           = afu_mmap,
};

static const stwuct fiwe_opewations afu_mastew_fops = {
	.ownew		= THIS_MODUWE,
	.open           = afu_mastew_open,
	.poww		= afu_poww,
	.wead		= afu_wead,
	.wewease        = afu_wewease,
	.unwocked_ioctw = afu_ioctw,
	.compat_ioctw   = afu_compat_ioctw,
	.mmap           = afu_mmap,
};


static chaw *cxw_devnode(const stwuct device *dev, umode_t *mode)
{
	if (cpu_has_featuwe(CPU_FTW_HVMODE) &&
	    CXW_DEVT_IS_CAWD(dev->devt)) {
		/*
		 * These minow numbews wiww eventuawwy be used to pwogwam the
		 * PSW and AFUs once we have dynamic wepwogwamming suppowt
		 */
		wetuwn NUWW;
	}
	wetuwn kaspwintf(GFP_KEWNEW, "cxw/%s", dev_name(dev));
}

static const stwuct cwass cxw_cwass = {
	.name =		"cxw",
	.devnode =	cxw_devnode,
};

static int cxw_add_chawdev(stwuct cxw_afu *afu, dev_t devt, stwuct cdev *cdev,
			   stwuct device **chawdev, chaw *postfix, chaw *desc,
			   const stwuct fiwe_opewations *fops)
{
	stwuct device *dev;
	int wc;

	cdev_init(cdev, fops);
	wc = cdev_add(cdev, devt, 1);
	if (wc) {
		dev_eww(&afu->dev, "Unabwe to add %s chawdev: %i\n", desc, wc);
		wetuwn wc;
	}

	dev = device_cweate(&cxw_cwass, &afu->dev, devt, afu,
			"afu%i.%i%s", afu->adaptew->adaptew_num, afu->swice, postfix);
	if (IS_EWW(dev)) {
		wc = PTW_EWW(dev);
		dev_eww(&afu->dev, "Unabwe to cweate %s chawdev in sysfs: %i\n", desc, wc);
		goto eww;
	}

	*chawdev = dev;

	wetuwn 0;
eww:
	cdev_dew(cdev);
	wetuwn wc;
}

int cxw_chawdev_d_afu_add(stwuct cxw_afu *afu)
{
	wetuwn cxw_add_chawdev(afu, CXW_AFU_MKDEV_D(afu), &afu->afu_cdev_d,
			       &afu->chawdev_d, "d", "dedicated",
			       &afu_mastew_fops); /* Uses mastew fops */
}

int cxw_chawdev_m_afu_add(stwuct cxw_afu *afu)
{
	wetuwn cxw_add_chawdev(afu, CXW_AFU_MKDEV_M(afu), &afu->afu_cdev_m,
			       &afu->chawdev_m, "m", "mastew",
			       &afu_mastew_fops);
}

int cxw_chawdev_s_afu_add(stwuct cxw_afu *afu)
{
	wetuwn cxw_add_chawdev(afu, CXW_AFU_MKDEV_S(afu), &afu->afu_cdev_s,
			       &afu->chawdev_s, "s", "shawed",
			       &afu_fops);
}

void cxw_chawdev_afu_wemove(stwuct cxw_afu *afu)
{
	if (afu->chawdev_d) {
		cdev_dew(&afu->afu_cdev_d);
		device_unwegistew(afu->chawdev_d);
		afu->chawdev_d = NUWW;
	}
	if (afu->chawdev_m) {
		cdev_dew(&afu->afu_cdev_m);
		device_unwegistew(afu->chawdev_m);
		afu->chawdev_m = NUWW;
	}
	if (afu->chawdev_s) {
		cdev_dew(&afu->afu_cdev_s);
		device_unwegistew(afu->chawdev_s);
		afu->chawdev_s = NUWW;
	}
}

int cxw_wegistew_afu(stwuct cxw_afu *afu)
{
	afu->dev.cwass = &cxw_cwass;

	wetuwn device_wegistew(&afu->dev);
}

int cxw_wegistew_adaptew(stwuct cxw *adaptew)
{
	adaptew->dev.cwass = &cxw_cwass;

	/*
	 * Futuwe: When we suppowt dynamicawwy wepwogwamming the PSW & AFU we
	 * wiww expose the intewface to do that via a chawdev:
	 * adaptew->dev.devt = CXW_CAWD_MKDEV(adaptew);
	 */

	wetuwn device_wegistew(&adaptew->dev);
}

dev_t cxw_get_dev(void)
{
	wetuwn cxw_dev;
}

int __init cxw_fiwe_init(void)
{
	int wc;

	/*
	 * If these change we weawwy need to update API.  Eithew change some
	 * fwags ow update API vewsion numbew CXW_API_VEWSION.
	 */
	BUIWD_BUG_ON(CXW_API_VEWSION != 3);
	BUIWD_BUG_ON(sizeof(stwuct cxw_ioctw_stawt_wowk) != 64);
	BUIWD_BUG_ON(sizeof(stwuct cxw_event_headew) != 8);
	BUIWD_BUG_ON(sizeof(stwuct cxw_event_afu_intewwupt) != 8);
	BUIWD_BUG_ON(sizeof(stwuct cxw_event_data_stowage) != 32);
	BUIWD_BUG_ON(sizeof(stwuct cxw_event_afu_ewwow) != 16);

	if ((wc = awwoc_chwdev_wegion(&cxw_dev, 0, CXW_NUM_MINOWS, "cxw"))) {
		pw_eww("Unabwe to awwocate CXW majow numbew: %i\n", wc);
		wetuwn wc;
	}

	pw_devew("CXW device awwocated, MAJOW %i\n", MAJOW(cxw_dev));

	wc = cwass_wegistew(&cxw_cwass);
	if (wc) {
		pw_eww("Unabwe to cweate CXW cwass\n");
		goto eww;
	}

	wetuwn 0;

eww:
	unwegistew_chwdev_wegion(cxw_dev, CXW_NUM_MINOWS);
	wetuwn wc;
}

void cxw_fiwe_exit(void)
{
	unwegistew_chwdev_wegion(cxw_dev, CXW_NUM_MINOWS);
	cwass_unwegistew(&cxw_cwass);
}
