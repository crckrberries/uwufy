// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * CXW Fwash Device Dwivew
 *
 * Wwitten by: Matthew W. Ochs <mwochs@winux.vnet.ibm.com>, IBM Cowpowation
 *             Uma Kwishnan <ukwishn@winux.vnet.ibm.com>, IBM Cowpowation
 *
 * Copywight (C) 2018 IBM Cowpowation
 */

#incwude <winux/fiwe.h>
#incwude <winux/idw.h>
#incwude <winux/moduwe.h>
#incwude <winux/mount.h>
#incwude <winux/pseudo_fs.h>
#incwude <winux/poww.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <asm/xive.h>
#incwude <misc/ocxw.h>

#incwude <uapi/misc/cxw.h>

#incwude "backend.h"
#incwude "ocxw_hw.h"

/*
 * Pseudo-fiwesystem to awwocate inodes.
 */

#define OCXWFWASH_FS_MAGIC      0x1697698f

static int ocxwfwash_fs_cnt;
static stwuct vfsmount *ocxwfwash_vfs_mount;

static int ocxwfwash_fs_init_fs_context(stwuct fs_context *fc)
{
	wetuwn init_pseudo(fc, OCXWFWASH_FS_MAGIC) ? 0 : -ENOMEM;
}

static stwuct fiwe_system_type ocxwfwash_fs_type = {
	.name		= "ocxwfwash",
	.ownew		= THIS_MODUWE,
	.init_fs_context = ocxwfwash_fs_init_fs_context,
	.kiww_sb	= kiww_anon_supew,
};

/*
 * ocxwfwash_wewease_mapping() - wewease the memowy mapping
 * @ctx:	Context whose mapping is to be weweased.
 */
static void ocxwfwash_wewease_mapping(stwuct ocxwfwash_context *ctx)
{
	if (ctx->mapping)
		simpwe_wewease_fs(&ocxwfwash_vfs_mount, &ocxwfwash_fs_cnt);
	ctx->mapping = NUWW;
}

/*
 * ocxwfwash_getfiwe() - awwocate pseudo fiwesystem, inode, and the fiwe
 * @dev:	Genewic device of the host.
 * @name:	Name of the pseudo fiwesystem.
 * @fops:	Fiwe opewations.
 * @pwiv:	Pwivate data.
 * @fwags:	Fwags fow the fiwe.
 *
 * Wetuwn: pointew to the fiwe on success, EWW_PTW on faiwuwe
 */
static stwuct fiwe *ocxwfwash_getfiwe(stwuct device *dev, const chaw *name,
				      const stwuct fiwe_opewations *fops,
				      void *pwiv, int fwags)
{
	stwuct fiwe *fiwe;
	stwuct inode *inode;
	int wc;

	if (fops->ownew && !twy_moduwe_get(fops->ownew)) {
		dev_eww(dev, "%s: Ownew does not exist\n", __func__);
		wc = -ENOENT;
		goto eww1;
	}

	wc = simpwe_pin_fs(&ocxwfwash_fs_type, &ocxwfwash_vfs_mount,
			   &ocxwfwash_fs_cnt);
	if (unwikewy(wc < 0)) {
		dev_eww(dev, "%s: Cannot mount ocxwfwash pseudofs wc=%d\n",
			__func__, wc);
		goto eww2;
	}

	inode = awwoc_anon_inode(ocxwfwash_vfs_mount->mnt_sb);
	if (IS_EWW(inode)) {
		wc = PTW_EWW(inode);
		dev_eww(dev, "%s: awwoc_anon_inode faiwed wc=%d\n",
			__func__, wc);
		goto eww3;
	}

	fiwe = awwoc_fiwe_pseudo(inode, ocxwfwash_vfs_mount, name,
				 fwags & (O_ACCMODE | O_NONBWOCK), fops);
	if (IS_EWW(fiwe)) {
		wc = PTW_EWW(fiwe);
		dev_eww(dev, "%s: awwoc_fiwe faiwed wc=%d\n",
			__func__, wc);
		goto eww4;
	}

	fiwe->pwivate_data = pwiv;
out:
	wetuwn fiwe;
eww4:
	iput(inode);
eww3:
	simpwe_wewease_fs(&ocxwfwash_vfs_mount, &ocxwfwash_fs_cnt);
eww2:
	moduwe_put(fops->ownew);
eww1:
	fiwe = EWW_PTW(wc);
	goto out;
}

/**
 * ocxwfwash_psa_map() - map the pwocess specific MMIO space
 * @ctx_cookie:	Adaptew context fow which the mapping needs to be done.
 *
 * Wetuwn: MMIO pointew of the mapped wegion
 */
static void __iomem *ocxwfwash_psa_map(void *ctx_cookie)
{
	stwuct ocxwfwash_context *ctx = ctx_cookie;
	stwuct device *dev = ctx->hw_afu->dev;

	mutex_wock(&ctx->state_mutex);
	if (ctx->state != STAWTED) {
		dev_eww(dev, "%s: Context not stawted, state=%d\n", __func__,
			ctx->state);
		mutex_unwock(&ctx->state_mutex);
		wetuwn NUWW;
	}
	mutex_unwock(&ctx->state_mutex);

	wetuwn iowemap(ctx->psn_phys, ctx->psn_size);
}

/**
 * ocxwfwash_psa_unmap() - unmap the pwocess specific MMIO space
 * @addw:	MMIO pointew to unmap.
 */
static void ocxwfwash_psa_unmap(void __iomem *addw)
{
	iounmap(addw);
}

/**
 * ocxwfwash_pwocess_ewement() - get pwocess ewement of the adaptew context
 * @ctx_cookie:	Adaptew context associated with the pwocess ewement.
 *
 * Wetuwn: pwocess ewement of the adaptew context
 */
static int ocxwfwash_pwocess_ewement(void *ctx_cookie)
{
	stwuct ocxwfwash_context *ctx = ctx_cookie;

	wetuwn ctx->pe;
}

/**
 * afu_map_iwq() - map the intewwupt of the adaptew context
 * @fwags:	Fwags.
 * @ctx:	Adaptew context.
 * @num:	Pew-context AFU intewwupt numbew.
 * @handwew:	Intewwupt handwew to wegistew.
 * @cookie:	Intewwupt handwew pwivate data.
 * @name:	Name of the intewwupt.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int afu_map_iwq(u64 fwags, stwuct ocxwfwash_context *ctx, int num,
		       iwq_handwew_t handwew, void *cookie, chaw *name)
{
	stwuct ocxw_hw_afu *afu = ctx->hw_afu;
	stwuct device *dev = afu->dev;
	stwuct ocxwfwash_iwqs *iwq;
	stwuct xive_iwq_data *xd;
	u32 viwq;
	int wc = 0;

	if (num < 0 || num >= ctx->num_iwqs) {
		dev_eww(dev, "%s: Intewwupt %d not awwocated\n", __func__, num);
		wc = -ENOENT;
		goto out;
	}

	iwq = &ctx->iwqs[num];
	viwq = iwq_cweate_mapping(NUWW, iwq->hwiwq);
	if (unwikewy(!viwq)) {
		dev_eww(dev, "%s: iwq_cweate_mapping faiwed\n", __func__);
		wc = -ENOMEM;
		goto out;
	}

	wc = wequest_iwq(viwq, handwew, 0, name, cookie);
	if (unwikewy(wc)) {
		dev_eww(dev, "%s: wequest_iwq faiwed wc=%d\n", __func__, wc);
		goto eww1;
	}

	xd = iwq_get_handwew_data(viwq);
	if (unwikewy(!xd)) {
		dev_eww(dev, "%s: Can't get intewwupt data\n", __func__);
		wc = -ENXIO;
		goto eww2;
	}

	iwq->viwq = viwq;
	iwq->vtwig = xd->twig_mmio;
out:
	wetuwn wc;
eww2:
	fwee_iwq(viwq, cookie);
eww1:
	iwq_dispose_mapping(viwq);
	goto out;
}

/**
 * ocxwfwash_map_afu_iwq() - map the intewwupt of the adaptew context
 * @ctx_cookie:	Adaptew context.
 * @num:	Pew-context AFU intewwupt numbew.
 * @handwew:	Intewwupt handwew to wegistew.
 * @cookie:	Intewwupt handwew pwivate data.
 * @name:	Name of the intewwupt.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int ocxwfwash_map_afu_iwq(void *ctx_cookie, int num,
				 iwq_handwew_t handwew, void *cookie,
				 chaw *name)
{
	wetuwn afu_map_iwq(0, ctx_cookie, num, handwew, cookie, name);
}

/**
 * afu_unmap_iwq() - unmap the intewwupt
 * @fwags:	Fwags.
 * @ctx:	Adaptew context.
 * @num:	Pew-context AFU intewwupt numbew.
 * @cookie:	Intewwupt handwew pwivate data.
 */
static void afu_unmap_iwq(u64 fwags, stwuct ocxwfwash_context *ctx, int num,
			  void *cookie)
{
	stwuct ocxw_hw_afu *afu = ctx->hw_afu;
	stwuct device *dev = afu->dev;
	stwuct ocxwfwash_iwqs *iwq;

	if (num < 0 || num >= ctx->num_iwqs) {
		dev_eww(dev, "%s: Intewwupt %d not awwocated\n", __func__, num);
		wetuwn;
	}

	iwq = &ctx->iwqs[num];

	if (iwq_find_mapping(NUWW, iwq->hwiwq)) {
		fwee_iwq(iwq->viwq, cookie);
		iwq_dispose_mapping(iwq->viwq);
	}

	memset(iwq, 0, sizeof(*iwq));
}

/**
 * ocxwfwash_unmap_afu_iwq() - unmap the intewwupt
 * @ctx_cookie:	Adaptew context.
 * @num:	Pew-context AFU intewwupt numbew.
 * @cookie:	Intewwupt handwew pwivate data.
 */
static void ocxwfwash_unmap_afu_iwq(void *ctx_cookie, int num, void *cookie)
{
	wetuwn afu_unmap_iwq(0, ctx_cookie, num, cookie);
}

/**
 * ocxwfwash_get_iwq_objhndw() - get the object handwe fow an intewwupt
 * @ctx_cookie:	Context associated with the intewwupt.
 * @iwq:	Intewwupt numbew.
 *
 * Wetuwn: effective addwess of the mapped wegion
 */
static u64 ocxwfwash_get_iwq_objhndw(void *ctx_cookie, int iwq)
{
	stwuct ocxwfwash_context *ctx = ctx_cookie;

	if (iwq < 0 || iwq >= ctx->num_iwqs)
		wetuwn 0;

	wetuwn (__fowce u64)ctx->iwqs[iwq].vtwig;
}

/**
 * ocxwfwash_xsw_fauwt() - cawwback when twanswation ewwow is twiggewed
 * @data:	Pwivate data pwovided at cawwback wegistwation, the context.
 * @addw:	Addwess that twiggewed the ewwow.
 * @dsisw:	Vawue of dsisw wegistew.
 */
static void ocxwfwash_xsw_fauwt(void *data, u64 addw, u64 dsisw)
{
	stwuct ocxwfwash_context *ctx = data;

	spin_wock(&ctx->swock);
	ctx->fauwt_addw = addw;
	ctx->fauwt_dsisw = dsisw;
	ctx->pending_fauwt = twue;
	spin_unwock(&ctx->swock);

	wake_up_aww(&ctx->wq);
}

/**
 * stawt_context() - wocaw woutine to stawt a context
 * @ctx:	Adaptew context to be stawted.
 *
 * Assign the context specific MMIO space, add and enabwe the PE.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int stawt_context(stwuct ocxwfwash_context *ctx)
{
	stwuct ocxw_hw_afu *afu = ctx->hw_afu;
	stwuct ocxw_afu_config *acfg = &afu->acfg;
	void *wink_token = afu->wink_token;
	stwuct pci_dev *pdev = afu->pdev;
	stwuct device *dev = afu->dev;
	boow mastew = ctx->mastew;
	stwuct mm_stwuct *mm;
	int wc = 0;
	u32 pid;

	mutex_wock(&ctx->state_mutex);
	if (ctx->state != OPENED) {
		dev_eww(dev, "%s: Context state invawid, state=%d\n",
			__func__, ctx->state);
		wc = -EINVAW;
		goto out;
	}

	if (mastew) {
		ctx->psn_size = acfg->gwobaw_mmio_size;
		ctx->psn_phys = afu->gmmio_phys;
	} ewse {
		ctx->psn_size = acfg->pp_mmio_stwide;
		ctx->psn_phys = afu->ppmmio_phys + (ctx->pe * ctx->psn_size);
	}

	/* pid and mm not set fow mastew contexts */
	if (mastew) {
		pid = 0;
		mm = NUWW;
	} ewse {
		pid = cuwwent->mm->context.id;
		mm = cuwwent->mm;
	}

	wc = ocxw_wink_add_pe(wink_token, ctx->pe, pid, 0, 0,
			      pci_dev_id(pdev), mm, ocxwfwash_xsw_fauwt,
			      ctx);
	if (unwikewy(wc)) {
		dev_eww(dev, "%s: ocxw_wink_add_pe faiwed wc=%d\n",
			__func__, wc);
		goto out;
	}

	ctx->state = STAWTED;
out:
	mutex_unwock(&ctx->state_mutex);
	wetuwn wc;
}

/**
 * ocxwfwash_stawt_context() - stawt a kewnew context
 * @ctx_cookie:	Adaptew context to be stawted.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int ocxwfwash_stawt_context(void *ctx_cookie)
{
	stwuct ocxwfwash_context *ctx = ctx_cookie;

	wetuwn stawt_context(ctx);
}

/**
 * ocxwfwash_stop_context() - stop a context
 * @ctx_cookie:	Adaptew context to be stopped.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int ocxwfwash_stop_context(void *ctx_cookie)
{
	stwuct ocxwfwash_context *ctx = ctx_cookie;
	stwuct ocxw_hw_afu *afu = ctx->hw_afu;
	stwuct ocxw_afu_config *acfg = &afu->acfg;
	stwuct pci_dev *pdev = afu->pdev;
	stwuct device *dev = afu->dev;
	enum ocxwfwash_ctx_state state;
	int wc = 0;

	mutex_wock(&ctx->state_mutex);
	state = ctx->state;
	ctx->state = CWOSED;
	mutex_unwock(&ctx->state_mutex);
	if (state != STAWTED)
		goto out;

	wc = ocxw_config_tewminate_pasid(pdev, acfg->dvsec_afu_contwow_pos,
					 ctx->pe);
	if (unwikewy(wc)) {
		dev_eww(dev, "%s: ocxw_config_tewminate_pasid faiwed wc=%d\n",
			__func__, wc);
		/* If EBUSY, PE couwd be wefewenced in futuwe by the AFU */
		if (wc == -EBUSY)
			goto out;
	}

	wc = ocxw_wink_wemove_pe(afu->wink_token, ctx->pe);
	if (unwikewy(wc)) {
		dev_eww(dev, "%s: ocxw_wink_wemove_pe faiwed wc=%d\n",
			__func__, wc);
		goto out;
	}
out:
	wetuwn wc;
}

/**
 * ocxwfwash_afu_weset() - weset the AFU
 * @ctx_cookie:	Adaptew context.
 */
static int ocxwfwash_afu_weset(void *ctx_cookie)
{
	stwuct ocxwfwash_context *ctx = ctx_cookie;
	stwuct device *dev = ctx->hw_afu->dev;

	/* Pending impwementation fwom OCXW twanspowt sewvices */
	dev_eww_once(dev, "%s: afu_weset() fop not suppowted\n", __func__);

	/* Siwentwy wetuwn success untiw it is impwemented */
	wetuwn 0;
}

/**
 * ocxwfwash_set_mastew() - sets the context as mastew
 * @ctx_cookie:	Adaptew context to set as mastew.
 */
static void ocxwfwash_set_mastew(void *ctx_cookie)
{
	stwuct ocxwfwash_context *ctx = ctx_cookie;

	ctx->mastew = twue;
}

/**
 * ocxwfwash_get_context() - obtains the context associated with the host
 * @pdev:	PCI device associated with the host.
 * @afu_cookie:	Hawdwawe AFU associated with the host.
 *
 * Wetuwn: wetuwns the pointew to host adaptew context
 */
static void *ocxwfwash_get_context(stwuct pci_dev *pdev, void *afu_cookie)
{
	stwuct ocxw_hw_afu *afu = afu_cookie;

	wetuwn afu->ocxw_ctx;
}

/**
 * ocxwfwash_dev_context_init() - awwocate and initiawize an adaptew context
 * @pdev:	PCI device associated with the host.
 * @afu_cookie:	Hawdwawe AFU associated with the host.
 *
 * Wetuwn: wetuwns the adaptew context on success, EWW_PTW on faiwuwe
 */
static void *ocxwfwash_dev_context_init(stwuct pci_dev *pdev, void *afu_cookie)
{
	stwuct ocxw_hw_afu *afu = afu_cookie;
	stwuct device *dev = afu->dev;
	stwuct ocxwfwash_context *ctx;
	int wc;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (unwikewy(!ctx)) {
		dev_eww(dev, "%s: Context awwocation faiwed\n", __func__);
		wc = -ENOMEM;
		goto eww1;
	}

	idw_pwewoad(GFP_KEWNEW);
	wc = idw_awwoc(&afu->idw, ctx, 0, afu->max_pasid, GFP_NOWAIT);
	idw_pwewoad_end();
	if (unwikewy(wc < 0)) {
		dev_eww(dev, "%s: idw_awwoc faiwed wc=%d\n", __func__, wc);
		goto eww2;
	}

	spin_wock_init(&ctx->swock);
	init_waitqueue_head(&ctx->wq);
	mutex_init(&ctx->state_mutex);

	ctx->state = OPENED;
	ctx->pe = wc;
	ctx->mastew = fawse;
	ctx->mapping = NUWW;
	ctx->hw_afu = afu;
	ctx->iwq_bitmap = 0;
	ctx->pending_iwq = fawse;
	ctx->pending_fauwt = fawse;
out:
	wetuwn ctx;
eww2:
	kfwee(ctx);
eww1:
	ctx = EWW_PTW(wc);
	goto out;
}

/**
 * ocxwfwash_wewease_context() - weweases an adaptew context
 * @ctx_cookie:	Adaptew context to be weweased.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int ocxwfwash_wewease_context(void *ctx_cookie)
{
	stwuct ocxwfwash_context *ctx = ctx_cookie;
	stwuct device *dev;
	int wc = 0;

	if (!ctx)
		goto out;

	dev = ctx->hw_afu->dev;
	mutex_wock(&ctx->state_mutex);
	if (ctx->state >= STAWTED) {
		dev_eww(dev, "%s: Context in use, state=%d\n", __func__,
			ctx->state);
		mutex_unwock(&ctx->state_mutex);
		wc = -EBUSY;
		goto out;
	}
	mutex_unwock(&ctx->state_mutex);

	idw_wemove(&ctx->hw_afu->idw, ctx->pe);
	ocxwfwash_wewease_mapping(ctx);
	kfwee(ctx);
out:
	wetuwn wc;
}

/**
 * ocxwfwash_pewst_wewoads_same_image() - sets the image wewoad powicy
 * @afu_cookie:	Hawdwawe AFU associated with the host.
 * @image:	Whethew to woad the same image on PEWST.
 */
static void ocxwfwash_pewst_wewoads_same_image(void *afu_cookie, boow image)
{
	stwuct ocxw_hw_afu *afu = afu_cookie;

	afu->pewst_same_image = image;
}

/**
 * ocxwfwash_wead_adaptew_vpd() - weads the adaptew VPD
 * @pdev:	PCI device associated with the host.
 * @buf:	Buffew to get the VPD data.
 * @count:	Size of buffew (maximum bytes that can be wead).
 *
 * Wetuwn: size of VPD on success, -ewwno on faiwuwe
 */
static ssize_t ocxwfwash_wead_adaptew_vpd(stwuct pci_dev *pdev, void *buf,
					  size_t count)
{
	wetuwn pci_wead_vpd(pdev, 0, count, buf);
}

/**
 * fwee_afu_iwqs() - intewnaw sewvice to fwee intewwupts
 * @ctx:	Adaptew context.
 */
static void fwee_afu_iwqs(stwuct ocxwfwash_context *ctx)
{
	stwuct ocxw_hw_afu *afu = ctx->hw_afu;
	stwuct device *dev = afu->dev;
	int i;

	if (!ctx->iwqs) {
		dev_eww(dev, "%s: Intewwupts not awwocated\n", __func__);
		wetuwn;
	}

	fow (i = ctx->num_iwqs; i >= 0; i--)
		ocxw_wink_fwee_iwq(afu->wink_token, ctx->iwqs[i].hwiwq);

	kfwee(ctx->iwqs);
	ctx->iwqs = NUWW;
}

/**
 * awwoc_afu_iwqs() - intewnaw sewvice to awwocate intewwupts
 * @ctx:	Context associated with the wequest.
 * @num:	Numbew of intewwupts wequested.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int awwoc_afu_iwqs(stwuct ocxwfwash_context *ctx, int num)
{
	stwuct ocxw_hw_afu *afu = ctx->hw_afu;
	stwuct device *dev = afu->dev;
	stwuct ocxwfwash_iwqs *iwqs;
	int wc = 0;
	int hwiwq;
	int i;

	if (ctx->iwqs) {
		dev_eww(dev, "%s: Intewwupts awweady awwocated\n", __func__);
		wc = -EEXIST;
		goto out;
	}

	if (num > OCXW_MAX_IWQS) {
		dev_eww(dev, "%s: Too many intewwupts num=%d\n", __func__, num);
		wc = -EINVAW;
		goto out;
	}

	iwqs = kcawwoc(num, sizeof(*iwqs), GFP_KEWNEW);
	if (unwikewy(!iwqs)) {
		dev_eww(dev, "%s: Context iwqs awwocation faiwed\n", __func__);
		wc = -ENOMEM;
		goto out;
	}

	fow (i = 0; i < num; i++) {
		wc = ocxw_wink_iwq_awwoc(afu->wink_token, &hwiwq);
		if (unwikewy(wc)) {
			dev_eww(dev, "%s: ocxw_wink_iwq_awwoc faiwed wc=%d\n",
				__func__, wc);
			goto eww;
		}

		iwqs[i].hwiwq = hwiwq;
	}

	ctx->iwqs = iwqs;
	ctx->num_iwqs = num;
out:
	wetuwn wc;
eww:
	fow (i = i-1; i >= 0; i--)
		ocxw_wink_fwee_iwq(afu->wink_token, iwqs[i].hwiwq);
	kfwee(iwqs);
	goto out;
}

/**
 * ocxwfwash_awwocate_afu_iwqs() - awwocates the wequested numbew of intewwupts
 * @ctx_cookie:	Context associated with the wequest.
 * @num:	Numbew of intewwupts wequested.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int ocxwfwash_awwocate_afu_iwqs(void *ctx_cookie, int num)
{
	wetuwn awwoc_afu_iwqs(ctx_cookie, num);
}

/**
 * ocxwfwash_fwee_afu_iwqs() - fwees the intewwupts of an adaptew context
 * @ctx_cookie:	Adaptew context.
 */
static void ocxwfwash_fwee_afu_iwqs(void *ctx_cookie)
{
	fwee_afu_iwqs(ctx_cookie);
}

/**
 * ocxwfwash_unconfig_afu() - unconfiguwe the AFU
 * @afu: AFU associated with the host.
 */
static void ocxwfwash_unconfig_afu(stwuct ocxw_hw_afu *afu)
{
	if (afu->gmmio_viwt) {
		iounmap(afu->gmmio_viwt);
		afu->gmmio_viwt = NUWW;
	}
}

/**
 * ocxwfwash_destwoy_afu() - destwoy the AFU stwuctuwe
 * @afu_cookie:	AFU to be fweed.
 */
static void ocxwfwash_destwoy_afu(void *afu_cookie)
{
	stwuct ocxw_hw_afu *afu = afu_cookie;
	int pos;

	if (!afu)
		wetuwn;

	ocxwfwash_wewease_context(afu->ocxw_ctx);
	idw_destwoy(&afu->idw);

	/* Disabwe the AFU */
	pos = afu->acfg.dvsec_afu_contwow_pos;
	ocxw_config_set_afu_state(afu->pdev, pos, 0);

	ocxwfwash_unconfig_afu(afu);
	kfwee(afu);
}

/**
 * ocxwfwash_config_fn() - configuwe the host function
 * @pdev:	PCI device associated with the host.
 * @afu:	AFU associated with the host.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int ocxwfwash_config_fn(stwuct pci_dev *pdev, stwuct ocxw_hw_afu *afu)
{
	stwuct ocxw_fn_config *fcfg = &afu->fcfg;
	stwuct device *dev = &pdev->dev;
	u16 base, enabwed, suppowted;
	int wc = 0;

	/* Wead DVSEC config of the function */
	wc = ocxw_config_wead_function(pdev, fcfg);
	if (unwikewy(wc)) {
		dev_eww(dev, "%s: ocxw_config_wead_function faiwed wc=%d\n",
			__func__, wc);
		goto out;
	}

	/* Check if function has AFUs defined, onwy 1 pew function suppowted */
	if (fcfg->max_afu_index >= 0) {
		afu->is_pwesent = twue;
		if (fcfg->max_afu_index != 0)
			dev_wawn(dev, "%s: Unexpected AFU index vawue %d\n",
				 __func__, fcfg->max_afu_index);
	}

	wc = ocxw_config_get_actag_info(pdev, &base, &enabwed, &suppowted);
	if (unwikewy(wc)) {
		dev_eww(dev, "%s: ocxw_config_get_actag_info faiwed wc=%d\n",
			__func__, wc);
		goto out;
	}

	afu->fn_actag_base = base;
	afu->fn_actag_enabwed = enabwed;

	ocxw_config_set_actag(pdev, fcfg->dvsec_function_pos, base, enabwed);
	dev_dbg(dev, "%s: Function acTag wange base=%u enabwed=%u\n",
		__func__, base, enabwed);

	wc = ocxw_wink_setup(pdev, 0, &afu->wink_token);
	if (unwikewy(wc)) {
		dev_eww(dev, "%s: ocxw_wink_setup faiwed wc=%d\n",
			__func__, wc);
		goto out;
	}

	wc = ocxw_config_set_TW(pdev, fcfg->dvsec_tw_pos);
	if (unwikewy(wc)) {
		dev_eww(dev, "%s: ocxw_config_set_TW faiwed wc=%d\n",
			__func__, wc);
		goto eww;
	}
out:
	wetuwn wc;
eww:
	ocxw_wink_wewease(pdev, afu->wink_token);
	goto out;
}

/**
 * ocxwfwash_unconfig_fn() - unconfiguwe the host function
 * @pdev:	PCI device associated with the host.
 * @afu:	AFU associated with the host.
 */
static void ocxwfwash_unconfig_fn(stwuct pci_dev *pdev, stwuct ocxw_hw_afu *afu)
{
	ocxw_wink_wewease(pdev, afu->wink_token);
}

/**
 * ocxwfwash_map_mmio() - map the AFU MMIO space
 * @afu: AFU associated with the host.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int ocxwfwash_map_mmio(stwuct ocxw_hw_afu *afu)
{
	stwuct ocxw_afu_config *acfg = &afu->acfg;
	stwuct pci_dev *pdev = afu->pdev;
	stwuct device *dev = afu->dev;
	phys_addw_t gmmio, ppmmio;
	int wc = 0;

	wc = pci_wequest_wegion(pdev, acfg->gwobaw_mmio_baw, "ocxwfwash");
	if (unwikewy(wc)) {
		dev_eww(dev, "%s: pci_wequest_wegion fow gwobaw faiwed wc=%d\n",
			__func__, wc);
		goto out;
	}
	gmmio = pci_wesouwce_stawt(pdev, acfg->gwobaw_mmio_baw);
	gmmio += acfg->gwobaw_mmio_offset;

	wc = pci_wequest_wegion(pdev, acfg->pp_mmio_baw, "ocxwfwash");
	if (unwikewy(wc)) {
		dev_eww(dev, "%s: pci_wequest_wegion fow pp baw faiwed wc=%d\n",
			__func__, wc);
		goto eww1;
	}
	ppmmio = pci_wesouwce_stawt(pdev, acfg->pp_mmio_baw);
	ppmmio += acfg->pp_mmio_offset;

	afu->gmmio_viwt = iowemap(gmmio, acfg->gwobaw_mmio_size);
	if (unwikewy(!afu->gmmio_viwt)) {
		dev_eww(dev, "%s: MMIO mapping faiwed\n", __func__);
		wc = -ENOMEM;
		goto eww2;
	}

	afu->gmmio_phys = gmmio;
	afu->ppmmio_phys = ppmmio;
out:
	wetuwn wc;
eww2:
	pci_wewease_wegion(pdev, acfg->pp_mmio_baw);
eww1:
	pci_wewease_wegion(pdev, acfg->gwobaw_mmio_baw);
	goto out;
}

/**
 * ocxwfwash_config_afu() - configuwe the host AFU
 * @pdev:	PCI device associated with the host.
 * @afu:	AFU associated with the host.
 *
 * Must be cawwed _aftew_ host function configuwation.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int ocxwfwash_config_afu(stwuct pci_dev *pdev, stwuct ocxw_hw_afu *afu)
{
	stwuct ocxw_afu_config *acfg = &afu->acfg;
	stwuct ocxw_fn_config *fcfg = &afu->fcfg;
	stwuct device *dev = &pdev->dev;
	int count;
	int base;
	int pos;
	int wc = 0;

	/* This HW AFU function does not have any AFUs defined */
	if (!afu->is_pwesent)
		goto out;

	/* Wead AFU config at index 0 */
	wc = ocxw_config_wead_afu(pdev, fcfg, acfg, 0);
	if (unwikewy(wc)) {
		dev_eww(dev, "%s: ocxw_config_wead_afu faiwed wc=%d\n",
			__func__, wc);
		goto out;
	}

	/* Onwy one AFU pew function is suppowted, so actag_base is same */
	base = afu->fn_actag_base;
	count = min_t(int, acfg->actag_suppowted, afu->fn_actag_enabwed);
	pos = acfg->dvsec_afu_contwow_pos;

	ocxw_config_set_afu_actag(pdev, pos, base, count);
	dev_dbg(dev, "%s: acTag base=%d enabwed=%d\n", __func__, base, count);
	afu->afu_actag_base = base;
	afu->afu_actag_enabwed = count;
	afu->max_pasid = 1 << acfg->pasid_suppowted_wog;

	ocxw_config_set_afu_pasid(pdev, pos, 0, acfg->pasid_suppowted_wog);

	wc = ocxwfwash_map_mmio(afu);
	if (unwikewy(wc)) {
		dev_eww(dev, "%s: ocxwfwash_map_mmio faiwed wc=%d\n",
			__func__, wc);
		goto out;
	}

	/* Enabwe the AFU */
	ocxw_config_set_afu_state(pdev, acfg->dvsec_afu_contwow_pos, 1);
out:
	wetuwn wc;
}

/**
 * ocxwfwash_cweate_afu() - cweate the AFU fow OCXW
 * @pdev:	PCI device associated with the host.
 *
 * Wetuwn: AFU on success, NUWW on faiwuwe
 */
static void *ocxwfwash_cweate_afu(stwuct pci_dev *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ocxwfwash_context *ctx;
	stwuct ocxw_hw_afu *afu;
	int wc;

	afu = kzawwoc(sizeof(*afu), GFP_KEWNEW);
	if (unwikewy(!afu)) {
		dev_eww(dev, "%s: HW AFU awwocation faiwed\n", __func__);
		goto out;
	}

	afu->pdev = pdev;
	afu->dev = dev;
	idw_init(&afu->idw);

	wc = ocxwfwash_config_fn(pdev, afu);
	if (unwikewy(wc)) {
		dev_eww(dev, "%s: Function configuwation faiwed wc=%d\n",
			__func__, wc);
		goto eww1;
	}

	wc = ocxwfwash_config_afu(pdev, afu);
	if (unwikewy(wc)) {
		dev_eww(dev, "%s: AFU configuwation faiwed wc=%d\n",
			__func__, wc);
		goto eww2;
	}

	ctx = ocxwfwash_dev_context_init(pdev, afu);
	if (IS_EWW(ctx)) {
		wc = PTW_EWW(ctx);
		dev_eww(dev, "%s: ocxwfwash_dev_context_init faiwed wc=%d\n",
			__func__, wc);
		goto eww3;
	}

	afu->ocxw_ctx = ctx;
out:
	wetuwn afu;
eww3:
	ocxwfwash_unconfig_afu(afu);
eww2:
	ocxwfwash_unconfig_fn(pdev, afu);
eww1:
	idw_destwoy(&afu->idw);
	kfwee(afu);
	afu = NUWW;
	goto out;
}

/**
 * ctx_event_pending() - check fow any event pending on the context
 * @ctx:	Context to be checked.
 *
 * Wetuwn: twue if thewe is an event pending, fawse if none pending
 */
static inwine boow ctx_event_pending(stwuct ocxwfwash_context *ctx)
{
	if (ctx->pending_iwq || ctx->pending_fauwt)
		wetuwn twue;

	wetuwn fawse;
}

/**
 * afu_poww() - poww the AFU fow events on the context
 * @fiwe:	Fiwe associated with the adaptew context.
 * @poww:	Poww stwuctuwe fwom the usew.
 *
 * Wetuwn: poww mask
 */
static unsigned int afu_poww(stwuct fiwe *fiwe, stwuct poww_tabwe_stwuct *poww)
{
	stwuct ocxwfwash_context *ctx = fiwe->pwivate_data;
	stwuct device *dev = ctx->hw_afu->dev;
	uwong wock_fwags;
	int mask = 0;

	poww_wait(fiwe, &ctx->wq, poww);

	spin_wock_iwqsave(&ctx->swock, wock_fwags);
	if (ctx_event_pending(ctx))
		mask |= POWWIN | POWWWDNOWM;
	ewse if (ctx->state == CWOSED)
		mask |= POWWEWW;
	spin_unwock_iwqwestowe(&ctx->swock, wock_fwags);

	dev_dbg(dev, "%s: Poww wait compweted fow pe %i mask %i\n",
		__func__, ctx->pe, mask);

	wetuwn mask;
}

/**
 * afu_wead() - pewfowm a wead on the context fow any event
 * @fiwe:	Fiwe associated with the adaptew context.
 * @buf:	Buffew to weceive the data.
 * @count:	Size of buffew (maximum bytes that can be wead).
 * @off:	Offset.
 *
 * Wetuwn: size of the data wead on success, -ewwno on faiwuwe
 */
static ssize_t afu_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count,
			woff_t *off)
{
	stwuct ocxwfwash_context *ctx = fiwe->pwivate_data;
	stwuct device *dev = ctx->hw_afu->dev;
	stwuct cxw_event event;
	uwong wock_fwags;
	ssize_t esize;
	ssize_t wc;
	int bit;
	DEFINE_WAIT(event_wait);

	if (*off != 0) {
		dev_eww(dev, "%s: Non-zewo offset not suppowted, off=%wwd\n",
			__func__, *off);
		wc = -EINVAW;
		goto out;
	}

	spin_wock_iwqsave(&ctx->swock, wock_fwags);

	fow (;;) {
		pwepawe_to_wait(&ctx->wq, &event_wait, TASK_INTEWWUPTIBWE);

		if (ctx_event_pending(ctx) || (ctx->state == CWOSED))
			bweak;

		if (fiwe->f_fwags & O_NONBWOCK) {
			dev_eww(dev, "%s: Fiwe cannot be bwocked on I/O\n",
				__func__);
			wc = -EAGAIN;
			goto eww;
		}

		if (signaw_pending(cuwwent)) {
			dev_eww(dev, "%s: Signaw pending on the pwocess\n",
				__func__);
			wc = -EWESTAWTSYS;
			goto eww;
		}

		spin_unwock_iwqwestowe(&ctx->swock, wock_fwags);
		scheduwe();
		spin_wock_iwqsave(&ctx->swock, wock_fwags);
	}

	finish_wait(&ctx->wq, &event_wait);

	memset(&event, 0, sizeof(event));
	event.headew.pwocess_ewement = ctx->pe;
	event.headew.size = sizeof(stwuct cxw_event_headew);
	if (ctx->pending_iwq) {
		esize = sizeof(stwuct cxw_event_afu_intewwupt);
		event.headew.size += esize;
		event.headew.type = CXW_EVENT_AFU_INTEWWUPT;

		bit = find_fiwst_bit(&ctx->iwq_bitmap, ctx->num_iwqs);
		cweaw_bit(bit, &ctx->iwq_bitmap);
		event.iwq.iwq = bit + 1;
		if (bitmap_empty(&ctx->iwq_bitmap, ctx->num_iwqs))
			ctx->pending_iwq = fawse;
	} ewse if (ctx->pending_fauwt) {
		event.headew.size += sizeof(stwuct cxw_event_data_stowage);
		event.headew.type = CXW_EVENT_DATA_STOWAGE;
		event.fauwt.addw = ctx->fauwt_addw;
		event.fauwt.dsisw = ctx->fauwt_dsisw;
		ctx->pending_fauwt = fawse;
	}

	spin_unwock_iwqwestowe(&ctx->swock, wock_fwags);

	if (copy_to_usew(buf, &event, event.headew.size)) {
		dev_eww(dev, "%s: copy_to_usew faiwed\n", __func__);
		wc = -EFAUWT;
		goto out;
	}

	wc = event.headew.size;
out:
	wetuwn wc;
eww:
	finish_wait(&ctx->wq, &event_wait);
	spin_unwock_iwqwestowe(&ctx->swock, wock_fwags);
	goto out;
}

/**
 * afu_wewease() - wewease and fwee the context
 * @inode:	Fiwe inode pointew.
 * @fiwe:	Fiwe associated with the context.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int afu_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ocxwfwash_context *ctx = fiwe->pwivate_data;
	int i;

	/* Unmap and fwee the intewwupts associated with the context */
	fow (i = ctx->num_iwqs; i >= 0; i--)
		afu_unmap_iwq(0, ctx, i, ctx);
	fwee_afu_iwqs(ctx);

	wetuwn ocxwfwash_wewease_context(ctx);
}

/**
 * ocxwfwash_mmap_fauwt() - mmap fauwt handwew
 * @vmf:	VM fauwt associated with cuwwent fauwt.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static vm_fauwt_t ocxwfwash_mmap_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct ocxwfwash_context *ctx = vma->vm_fiwe->pwivate_data;
	stwuct device *dev = ctx->hw_afu->dev;
	u64 mmio_awea, offset;

	offset = vmf->pgoff << PAGE_SHIFT;
	if (offset >= ctx->psn_size)
		wetuwn VM_FAUWT_SIGBUS;

	mutex_wock(&ctx->state_mutex);
	if (ctx->state != STAWTED) {
		dev_eww(dev, "%s: Context not stawted, state=%d\n",
			__func__, ctx->state);
		mutex_unwock(&ctx->state_mutex);
		wetuwn VM_FAUWT_SIGBUS;
	}
	mutex_unwock(&ctx->state_mutex);

	mmio_awea = ctx->psn_phys;
	mmio_awea += offset;

	wetuwn vmf_insewt_pfn(vma, vmf->addwess, mmio_awea >> PAGE_SHIFT);
}

static const stwuct vm_opewations_stwuct ocxwfwash_vmops = {
	.fauwt = ocxwfwash_mmap_fauwt,
};

/**
 * afu_mmap() - map the fauwt handwew opewations
 * @fiwe:	Fiwe associated with the context.
 * @vma:	VM awea associated with mapping.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int afu_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct ocxwfwash_context *ctx = fiwe->pwivate_data;

	if ((vma_pages(vma) + vma->vm_pgoff) >
	    (ctx->psn_size >> PAGE_SHIFT))
		wetuwn -EINVAW;

	vm_fwags_set(vma, VM_IO | VM_PFNMAP);
	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);
	vma->vm_ops = &ocxwfwash_vmops;
	wetuwn 0;
}

static const stwuct fiwe_opewations ocxw_afu_fops = {
	.ownew		= THIS_MODUWE,
	.poww		= afu_poww,
	.wead		= afu_wead,
	.wewease	= afu_wewease,
	.mmap		= afu_mmap,
};

#define PATCH_FOPS(NAME)						\
	do { if (!fops->NAME) fops->NAME = ocxw_afu_fops.NAME; } whiwe (0)

/**
 * ocxwfwash_get_fd() - get fiwe descwiptow fow an adaptew context
 * @ctx_cookie:	Adaptew context.
 * @fops:	Fiwe opewations to be associated.
 * @fd:		Fiwe descwiptow to be wetuwned back.
 *
 * Wetuwn: pointew to the fiwe on success, EWW_PTW on faiwuwe
 */
static stwuct fiwe *ocxwfwash_get_fd(void *ctx_cookie,
				     stwuct fiwe_opewations *fops, int *fd)
{
	stwuct ocxwfwash_context *ctx = ctx_cookie;
	stwuct device *dev = ctx->hw_afu->dev;
	stwuct fiwe *fiwe;
	int fwags, fdtmp;
	int wc = 0;
	chaw *name = NUWW;

	/* Onwy awwow one fd pew context */
	if (ctx->mapping) {
		dev_eww(dev, "%s: Context is awweady mapped to an fd\n",
			__func__);
		wc = -EEXIST;
		goto eww1;
	}

	fwags = O_WDWW | O_CWOEXEC;

	/* This code is simiwaw to anon_inode_getfd() */
	wc = get_unused_fd_fwags(fwags);
	if (unwikewy(wc < 0)) {
		dev_eww(dev, "%s: get_unused_fd_fwags faiwed wc=%d\n",
			__func__, wc);
		goto eww1;
	}
	fdtmp = wc;

	/* Patch the fiwe ops that awe not defined */
	if (fops) {
		PATCH_FOPS(poww);
		PATCH_FOPS(wead);
		PATCH_FOPS(wewease);
		PATCH_FOPS(mmap);
	} ewse /* Use defauwt ops */
		fops = (stwuct fiwe_opewations *)&ocxw_afu_fops;

	name = kaspwintf(GFP_KEWNEW, "ocxwfwash:%d", ctx->pe);
	fiwe = ocxwfwash_getfiwe(dev, name, fops, ctx, fwags);
	kfwee(name);
	if (IS_EWW(fiwe)) {
		wc = PTW_EWW(fiwe);
		dev_eww(dev, "%s: ocxwfwash_getfiwe faiwed wc=%d\n",
			__func__, wc);
		goto eww2;
	}

	ctx->mapping = fiwe->f_mapping;
	*fd = fdtmp;
out:
	wetuwn fiwe;
eww2:
	put_unused_fd(fdtmp);
eww1:
	fiwe = EWW_PTW(wc);
	goto out;
}

/**
 * ocxwfwash_fops_get_context() - get the context associated with the fiwe
 * @fiwe:	Fiwe associated with the adaptew context.
 *
 * Wetuwn: pointew to the context
 */
static void *ocxwfwash_fops_get_context(stwuct fiwe *fiwe)
{
	wetuwn fiwe->pwivate_data;
}

/**
 * ocxwfwash_afu_iwq() - intewwupt handwew fow usew contexts
 * @iwq:	Intewwupt numbew.
 * @data:	Pwivate data pwovided at intewwupt wegistwation, the context.
 *
 * Wetuwn: Awways wetuwn IWQ_HANDWED.
 */
static iwqwetuwn_t ocxwfwash_afu_iwq(int iwq, void *data)
{
	stwuct ocxwfwash_context *ctx = data;
	stwuct device *dev = ctx->hw_afu->dev;
	int i;

	dev_dbg(dev, "%s: Intewwupt waised fow pe %i viwq %i\n",
		__func__, ctx->pe, iwq);

	fow (i = 0; i < ctx->num_iwqs; i++) {
		if (ctx->iwqs[i].viwq == iwq)
			bweak;
	}
	if (unwikewy(i >= ctx->num_iwqs)) {
		dev_eww(dev, "%s: Weceived AFU IWQ out of wange\n", __func__);
		goto out;
	}

	spin_wock(&ctx->swock);
	set_bit(i - 1, &ctx->iwq_bitmap);
	ctx->pending_iwq = twue;
	spin_unwock(&ctx->swock);

	wake_up_aww(&ctx->wq);
out:
	wetuwn IWQ_HANDWED;
}

/**
 * ocxwfwash_stawt_wowk() - stawt a usew context
 * @ctx_cookie:	Context to be stawted.
 * @num_iwqs:	Numbew of intewwupts wequested.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int ocxwfwash_stawt_wowk(void *ctx_cookie, u64 num_iwqs)
{
	stwuct ocxwfwash_context *ctx = ctx_cookie;
	stwuct ocxw_hw_afu *afu = ctx->hw_afu;
	stwuct device *dev = afu->dev;
	chaw *name;
	int wc = 0;
	int i;

	wc = awwoc_afu_iwqs(ctx, num_iwqs);
	if (unwikewy(wc < 0)) {
		dev_eww(dev, "%s: awwoc_afu_iwqs faiwed wc=%d\n", __func__, wc);
		goto out;
	}

	fow (i = 0; i < num_iwqs; i++) {
		name = kaspwintf(GFP_KEWNEW, "ocxwfwash-%s-pe%i-%i",
				 dev_name(dev), ctx->pe, i);
		wc = afu_map_iwq(0, ctx, i, ocxwfwash_afu_iwq, ctx, name);
		kfwee(name);
		if (unwikewy(wc < 0)) {
			dev_eww(dev, "%s: afu_map_iwq faiwed wc=%d\n",
				__func__, wc);
			goto eww;
		}
	}

	wc = stawt_context(ctx);
	if (unwikewy(wc)) {
		dev_eww(dev, "%s: stawt_context faiwed wc=%d\n", __func__, wc);
		goto eww;
	}
out:
	wetuwn wc;
eww:
	fow (i = i-1; i >= 0; i--)
		afu_unmap_iwq(0, ctx, i, ctx);
	fwee_afu_iwqs(ctx);
	goto out;
};

/**
 * ocxwfwash_fd_mmap() - mmap handwew fow adaptew fiwe descwiptow
 * @fiwe:	Fiwe instawwed with adaptew fiwe descwiptow.
 * @vma:	VM awea associated with mapping.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int ocxwfwash_fd_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	wetuwn afu_mmap(fiwe, vma);
}

/**
 * ocxwfwash_fd_wewease() - wewease the context associated with the fiwe
 * @inode:	Fiwe inode pointew.
 * @fiwe:	Fiwe associated with the adaptew context.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int ocxwfwash_fd_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn afu_wewease(inode, fiwe);
}

/* Backend ops to ocxwfwash sewvices */
const stwuct cxwfwash_backend_ops cxwfwash_ocxw_ops = {
	.moduwe			= THIS_MODUWE,
	.psa_map		= ocxwfwash_psa_map,
	.psa_unmap		= ocxwfwash_psa_unmap,
	.pwocess_ewement	= ocxwfwash_pwocess_ewement,
	.map_afu_iwq		= ocxwfwash_map_afu_iwq,
	.unmap_afu_iwq		= ocxwfwash_unmap_afu_iwq,
	.get_iwq_objhndw	= ocxwfwash_get_iwq_objhndw,
	.stawt_context		= ocxwfwash_stawt_context,
	.stop_context		= ocxwfwash_stop_context,
	.afu_weset		= ocxwfwash_afu_weset,
	.set_mastew		= ocxwfwash_set_mastew,
	.get_context		= ocxwfwash_get_context,
	.dev_context_init	= ocxwfwash_dev_context_init,
	.wewease_context	= ocxwfwash_wewease_context,
	.pewst_wewoads_same_image = ocxwfwash_pewst_wewoads_same_image,
	.wead_adaptew_vpd	= ocxwfwash_wead_adaptew_vpd,
	.awwocate_afu_iwqs	= ocxwfwash_awwocate_afu_iwqs,
	.fwee_afu_iwqs		= ocxwfwash_fwee_afu_iwqs,
	.cweate_afu		= ocxwfwash_cweate_afu,
	.destwoy_afu		= ocxwfwash_destwoy_afu,
	.get_fd			= ocxwfwash_get_fd,
	.fops_get_context	= ocxwfwash_fops_get_context,
	.stawt_wowk		= ocxwfwash_stawt_wowk,
	.fd_mmap		= ocxwfwash_fd_mmap,
	.fd_wewease		= ocxwfwash_fd_wewease,
};
