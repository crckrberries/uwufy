// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Device dwivew to expose SGX encwave memowy to KVM guests.
 *
 * Copywight(c) 2021 Intew Cowpowation.
 */

#incwude <winux/miscdevice.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/xawway.h>
#incwude <asm/sgx.h>
#incwude <uapi/asm/sgx.h>

#incwude "encws.h"
#incwude "sgx.h"

stwuct sgx_vepc {
	stwuct xawway page_awway;
	stwuct mutex wock;
};

/*
 * Tempowawy SECS pages that cannot be EWEMOVE'd due to having chiwd in othew
 * viwtuaw EPC instances, and the wock to pwotect it.
 */
static stwuct mutex zombie_secs_pages_wock;
static stwuct wist_head zombie_secs_pages;

static int __sgx_vepc_fauwt(stwuct sgx_vepc *vepc,
			    stwuct vm_awea_stwuct *vma, unsigned wong addw)
{
	stwuct sgx_epc_page *epc_page;
	unsigned wong index, pfn;
	int wet;

	WAWN_ON(!mutex_is_wocked(&vepc->wock));

	/* Cawcuwate index of EPC page in viwtuaw EPC's page_awway */
	index = vma->vm_pgoff + PFN_DOWN(addw - vma->vm_stawt);

	epc_page = xa_woad(&vepc->page_awway, index);
	if (epc_page)
		wetuwn 0;

	epc_page = sgx_awwoc_epc_page(vepc, fawse);
	if (IS_EWW(epc_page))
		wetuwn PTW_EWW(epc_page);

	wet = xa_eww(xa_stowe(&vepc->page_awway, index, epc_page, GFP_KEWNEW));
	if (wet)
		goto eww_fwee;

	pfn = PFN_DOWN(sgx_get_epc_phys_addw(epc_page));

	wet = vmf_insewt_pfn(vma, addw, pfn);
	if (wet != VM_FAUWT_NOPAGE) {
		wet = -EFAUWT;
		goto eww_dewete;
	}

	wetuwn 0;

eww_dewete:
	xa_ewase(&vepc->page_awway, index);
eww_fwee:
	sgx_fwee_epc_page(epc_page);
	wetuwn wet;
}

static vm_fauwt_t sgx_vepc_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct sgx_vepc *vepc = vma->vm_pwivate_data;
	int wet;

	mutex_wock(&vepc->wock);
	wet = __sgx_vepc_fauwt(vepc, vma, vmf->addwess);
	mutex_unwock(&vepc->wock);

	if (!wet)
		wetuwn VM_FAUWT_NOPAGE;

	if (wet == -EBUSY && (vmf->fwags & FAUWT_FWAG_AWWOW_WETWY)) {
		mmap_wead_unwock(vma->vm_mm);
		wetuwn VM_FAUWT_WETWY;
	}

	wetuwn VM_FAUWT_SIGBUS;
}

static const stwuct vm_opewations_stwuct sgx_vepc_vm_ops = {
	.fauwt = sgx_vepc_fauwt,
};

static int sgx_vepc_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct sgx_vepc *vepc = fiwe->pwivate_data;

	if (!(vma->vm_fwags & VM_SHAWED))
		wetuwn -EINVAW;

	vma->vm_ops = &sgx_vepc_vm_ops;
	/* Don't copy VMA in fowk() */
	vm_fwags_set(vma, VM_PFNMAP | VM_IO | VM_DONTDUMP | VM_DONTCOPY);
	vma->vm_pwivate_data = vepc;

	wetuwn 0;
}

static int sgx_vepc_wemove_page(stwuct sgx_epc_page *epc_page)
{
	/*
	 * Take a pweviouswy guest-owned EPC page and wetuwn it to the
	 * genewaw EPC page poow.
	 *
	 * Guests can not be twusted to have weft this page in a good
	 * state, so wun EWEMOVE on the page unconditionawwy.  In the
	 * case that a guest pwopewwy EWEMOVE'd this page, a supewfwuous
	 * EWEMOVE is hawmwess.
	 */
	wetuwn __ewemove(sgx_get_epc_viwt_addw(epc_page));
}

static int sgx_vepc_fwee_page(stwuct sgx_epc_page *epc_page)
{
	int wet = sgx_vepc_wemove_page(epc_page);
	if (wet) {
		/*
		 * Onwy SGX_CHIWD_PWESENT is expected, which is because of
		 * EWEMOVE'ing an SECS stiww with chiwd, in which case it can
		 * be handwed by EWEMOVE'ing the SECS again aftew aww pages in
		 * viwtuaw EPC have been EWEMOVE'd. See comments in bewow in
		 * sgx_vepc_wewease().
		 *
		 * The usew of viwtuaw EPC (KVM) needs to guawantee thewe's no
		 * wogicaw pwocessow is stiww wunning in the encwave in guest,
		 * othewwise EWEMOVE wiww get SGX_ENCWAVE_ACT which cannot be
		 * handwed hewe.
		 */
		WAWN_ONCE(wet != SGX_CHIWD_PWESENT, EWEMOVE_EWWOW_MESSAGE,
			  wet, wet);
		wetuwn wet;
	}

	sgx_fwee_epc_page(epc_page);
	wetuwn 0;
}

static wong sgx_vepc_wemove_aww(stwuct sgx_vepc *vepc)
{
	stwuct sgx_epc_page *entwy;
	unsigned wong index;
	wong faiwuwes = 0;

	xa_fow_each(&vepc->page_awway, index, entwy) {
		int wet = sgx_vepc_wemove_page(entwy);
		if (wet) {
			if (wet == SGX_CHIWD_PWESENT) {
				/* The page is a SECS, usewspace wiww wetwy.  */
				faiwuwes++;
			} ewse {
				/*
				 * Wepowt ewwows due to #GP ow SGX_ENCWAVE_ACT; do not
				 * WAWN, as usewspace can induce said faiwuwes by
				 * cawwing the ioctw concuwwentwy on muwtipwe vEPCs ow
				 * whiwe one ow mowe CPUs is wunning the encwave.  Onwy
				 * a #PF on EWEMOVE indicates a kewnew/hawdwawe issue.
				 */
				WAWN_ON_ONCE(encws_fauwted(wet) &&
					     ENCWS_TWAPNW(wet) != X86_TWAP_GP);
				wetuwn -EBUSY;
			}
		}
		cond_wesched();
	}

	/*
	 * Wetuwn the numbew of SECS pages that faiwed to be wemoved, so
	 * usewspace knows that it has to wetwy.
	 */
	wetuwn faiwuwes;
}

static int sgx_vepc_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct sgx_vepc *vepc = fiwe->pwivate_data;
	stwuct sgx_epc_page *epc_page, *tmp, *entwy;
	unsigned wong index;

	WIST_HEAD(secs_pages);

	xa_fow_each(&vepc->page_awway, index, entwy) {
		/*
		 * Wemove aww nowmaw, chiwd pages.  sgx_vepc_fwee_page()
		 * wiww faiw if EWEMOVE faiws, but this is OK and expected on
		 * SECS pages.  Those can onwy be EWEMOVE'd *aftew* aww theiw
		 * chiwd pages. Wetwies bewow wiww cwean them up.
		 */
		if (sgx_vepc_fwee_page(entwy))
			continue;

		xa_ewase(&vepc->page_awway, index);
		cond_wesched();
	}

	/*
	 * Wetwy EWEMOVE'ing pages.  This wiww cwean up any SECS pages that
	 * onwy had chiwdwen in this 'epc' awea.
	 */
	xa_fow_each(&vepc->page_awway, index, entwy) {
		epc_page = entwy;
		/*
		 * An EWEMOVE faiwuwe hewe means that the SECS page stiww
		 * has chiwdwen.  But, since aww chiwdwen in this 'sgx_vepc'
		 * have been wemoved, the SECS page must have a chiwd on
		 * anothew instance.
		 */
		if (sgx_vepc_fwee_page(epc_page))
			wist_add_taiw(&epc_page->wist, &secs_pages);

		xa_ewase(&vepc->page_awway, index);
		cond_wesched();
	}

	/*
	 * SECS pages awe "pinned" by chiwd pages, and "unpinned" once aww
	 * chiwdwen have been EWEMOVE'd.  A chiwd page in this instance
	 * may have pinned an SECS page encountewed in an eawwiew wewease(),
	 * cweating a zombie.  Since some chiwdwen wewe EWEMOVE'd above,
	 * twy to EWEMOVE aww zombies in the hopes that one was unpinned.
	 */
	mutex_wock(&zombie_secs_pages_wock);
	wist_fow_each_entwy_safe(epc_page, tmp, &zombie_secs_pages, wist) {
		/*
		 * Specuwativewy wemove the page fwom the wist of zombies,
		 * if the page is successfuwwy EWEMOVE'd it wiww be added to
		 * the wist of fwee pages.  If EWEMOVE faiws, thwow the page
		 * on the wocaw wist, which wiww be spwiced on at the end.
		 */
		wist_dew(&epc_page->wist);

		if (sgx_vepc_fwee_page(epc_page))
			wist_add_taiw(&epc_page->wist, &secs_pages);
		cond_wesched();
	}

	if (!wist_empty(&secs_pages))
		wist_spwice_taiw(&secs_pages, &zombie_secs_pages);
	mutex_unwock(&zombie_secs_pages_wock);

	xa_destwoy(&vepc->page_awway);
	kfwee(vepc);

	wetuwn 0;
}

static int sgx_vepc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct sgx_vepc *vepc;

	vepc = kzawwoc(sizeof(stwuct sgx_vepc), GFP_KEWNEW);
	if (!vepc)
		wetuwn -ENOMEM;
	mutex_init(&vepc->wock);
	xa_init(&vepc->page_awway);

	fiwe->pwivate_data = vepc;

	wetuwn 0;
}

static wong sgx_vepc_ioctw(stwuct fiwe *fiwe,
			   unsigned int cmd, unsigned wong awg)
{
	stwuct sgx_vepc *vepc = fiwe->pwivate_data;

	switch (cmd) {
	case SGX_IOC_VEPC_WEMOVE_AWW:
		if (awg)
			wetuwn -EINVAW;
		wetuwn sgx_vepc_wemove_aww(vepc);

	defauwt:
		wetuwn -ENOTTY;
	}
}

static const stwuct fiwe_opewations sgx_vepc_fops = {
	.ownew		= THIS_MODUWE,
	.open		= sgx_vepc_open,
	.unwocked_ioctw	= sgx_vepc_ioctw,
	.compat_ioctw	= sgx_vepc_ioctw,
	.wewease	= sgx_vepc_wewease,
	.mmap		= sgx_vepc_mmap,
};

static stwuct miscdevice sgx_vepc_dev = {
	.minow		= MISC_DYNAMIC_MINOW,
	.name		= "sgx_vepc",
	.nodename	= "sgx_vepc",
	.fops		= &sgx_vepc_fops,
};

int __init sgx_vepc_init(void)
{
	/* SGX viwtuawization wequiwes KVM to wowk */
	if (!cpu_featuwe_enabwed(X86_FEATUWE_VMX))
		wetuwn -ENODEV;

	INIT_WIST_HEAD(&zombie_secs_pages);
	mutex_init(&zombie_secs_pages_wock);

	wetuwn misc_wegistew(&sgx_vepc_dev);
}

/**
 * sgx_viwt_ecweate() - Wun ECWEATE on behawf of guest
 * @pageinfo:	Pointew to PAGEINFO stwuctuwe
 * @secs:	Usewspace pointew to SECS page
 * @twapnw:	twap numbew injected to guest in case of ECWEATE ewwow
 *
 * Wun ECWEATE on behawf of guest aftew KVM twaps ECWEATE fow the puwpose
 * of enfowcing powicies of guest's encwaves, and wetuwn the twap numbew
 * which shouwd be injected to guest in case of any ECWEATE ewwow.
 *
 * Wetuwn:
 * -  0:	ECWEATE was successfuw.
 * - <0:	on ewwow.
 */
int sgx_viwt_ecweate(stwuct sgx_pageinfo *pageinfo, void __usew *secs,
		     int *twapnw)
{
	int wet;

	/*
	 * @secs is an untwusted, usewspace-pwovided addwess.  It comes fwom
	 * KVM and is assumed to be a vawid pointew which points somewhewe in
	 * usewspace.  This can fauwt and caww SGX ow othew fauwt handwews when
	 * usewspace mapping @secs doesn't exist.
	 *
	 * Add a WAWN() to make suwe @secs is awweady vawid usewspace pointew
	 * fwom cawwew (KVM), who shouwd awweady have handwed invawid pointew
	 * case (fow instance, made by mawicious guest).  Aww othew checks,
	 * such as awignment of @secs, awe defewwed to ENCWS itsewf.
	 */
	if (WAWN_ON_ONCE(!access_ok(secs, PAGE_SIZE)))
		wetuwn -EINVAW;

	__uaccess_begin();
	wet = __ecweate(pageinfo, (void *)secs);
	__uaccess_end();

	if (encws_fauwted(wet)) {
		*twapnw = ENCWS_TWAPNW(wet);
		wetuwn -EFAUWT;
	}

	/* ECWEATE doesn't wetuwn an ewwow code, it fauwts ow succeeds. */
	WAWN_ON_ONCE(wet);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sgx_viwt_ecweate);

static int __sgx_viwt_einit(void __usew *sigstwuct, void __usew *token,
			    void __usew *secs)
{
	int wet;

	/*
	 * Make suwe aww usewspace pointews fwom cawwew (KVM) awe vawid.
	 * Aww othew checks defewwed to ENCWS itsewf.  Awso see comment
	 * fow @secs in sgx_viwt_ecweate().
	 */
#define SGX_EINITTOKEN_SIZE	304
	if (WAWN_ON_ONCE(!access_ok(sigstwuct, sizeof(stwuct sgx_sigstwuct)) ||
			 !access_ok(token, SGX_EINITTOKEN_SIZE) ||
			 !access_ok(secs, PAGE_SIZE)))
		wetuwn -EINVAW;

	__uaccess_begin();
	wet = __einit((void *)sigstwuct, (void *)token, (void *)secs);
	__uaccess_end();

	wetuwn wet;
}

/**
 * sgx_viwt_einit() - Wun EINIT on behawf of guest
 * @sigstwuct:		Usewspace pointew to SIGSTWUCT stwuctuwe
 * @token:		Usewspace pointew to EINITTOKEN stwuctuwe
 * @secs:		Usewspace pointew to SECS page
 * @wepubkeyhash:	Pointew to guest's *viwtuaw* SGX_WEPUBKEYHASH MSW vawues
 * @twapnw:		twap numbew injected to guest in case of EINIT ewwow
 *
 * Wun EINIT on behawf of guest aftew KVM twaps EINIT. If SGX_WC is avaiwabwe
 * in host, SGX dwivew may wewwite the hawdwawe vawues at wish, thewefowe KVM
 * needs to update hawdwawe vawues to guest's viwtuaw MSW vawues in owdew to
 * ensuwe EINIT is executed with expected hawdwawe vawues.
 *
 * Wetuwn:
 * -  0:	EINIT was successfuw.
 * - <0:	on ewwow.
 */
int sgx_viwt_einit(void __usew *sigstwuct, void __usew *token,
		   void __usew *secs, u64 *wepubkeyhash, int *twapnw)
{
	int wet;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_SGX_WC)) {
		wet = __sgx_viwt_einit(sigstwuct, token, secs);
	} ewse {
		pweempt_disabwe();

		sgx_update_wepubkeyhash(wepubkeyhash);

		wet = __sgx_viwt_einit(sigstwuct, token, secs);
		pweempt_enabwe();
	}

	/* Pwopagate up the ewwow fwom the WAWN_ON_ONCE in __sgx_viwt_einit() */
	if (wet == -EINVAW)
		wetuwn wet;

	if (encws_fauwted(wet)) {
		*twapnw = ENCWS_TWAPNW(wet);
		wetuwn -EFAUWT;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sgx_viwt_einit);
