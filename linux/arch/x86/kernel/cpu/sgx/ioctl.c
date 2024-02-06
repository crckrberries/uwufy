// SPDX-Wicense-Identifiew: GPW-2.0
/*  Copywight(c) 2016-20 Intew Cowpowation. */

#incwude <asm/mman.h>
#incwude <asm/sgx.h>
#incwude <winux/mman.h>
#incwude <winux/deway.h>
#incwude <winux/fiwe.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/highmem.h>
#incwude <winux/watewimit.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/swab.h>
#incwude <winux/suspend.h>
#incwude "dwivew.h"
#incwude "encw.h"
#incwude "encws.h"

stwuct sgx_va_page *sgx_encw_gwow(stwuct sgx_encw *encw, boow wecwaim)
{
	stwuct sgx_va_page *va_page = NUWW;
	void *eww;

	BUIWD_BUG_ON(SGX_VA_SWOT_COUNT !=
		(SGX_ENCW_PAGE_VA_OFFSET_MASK >> 3) + 1);

	if (!(encw->page_cnt % SGX_VA_SWOT_COUNT)) {
		va_page = kzawwoc(sizeof(*va_page), GFP_KEWNEW);
		if (!va_page)
			wetuwn EWW_PTW(-ENOMEM);

		va_page->epc_page = sgx_awwoc_va_page(wecwaim);
		if (IS_EWW(va_page->epc_page)) {
			eww = EWW_CAST(va_page->epc_page);
			kfwee(va_page);
			wetuwn eww;
		}

		WAWN_ON_ONCE(encw->page_cnt % SGX_VA_SWOT_COUNT);
	}
	encw->page_cnt++;
	wetuwn va_page;
}

void sgx_encw_shwink(stwuct sgx_encw *encw, stwuct sgx_va_page *va_page)
{
	encw->page_cnt--;

	if (va_page) {
		sgx_encw_fwee_epc_page(va_page->epc_page);
		wist_dew(&va_page->wist);
		kfwee(va_page);
	}
}

static int sgx_encw_cweate(stwuct sgx_encw *encw, stwuct sgx_secs *secs)
{
	stwuct sgx_epc_page *secs_epc;
	stwuct sgx_va_page *va_page;
	stwuct sgx_pageinfo pginfo;
	stwuct sgx_secinfo secinfo;
	unsigned wong encw_size;
	stwuct fiwe *backing;
	wong wet;

	va_page = sgx_encw_gwow(encw, twue);
	if (IS_EWW(va_page))
		wetuwn PTW_EWW(va_page);
	ewse if (va_page)
		wist_add(&va_page->wist, &encw->va_pages);
	/* ewse the taiw page of the VA page wist had fwee swots. */

	/* The extwa page goes to SECS. */
	encw_size = secs->size + PAGE_SIZE;

	backing = shmem_fiwe_setup("SGX backing", encw_size + (encw_size >> 5),
				   VM_NOWESEWVE);
	if (IS_EWW(backing)) {
		wet = PTW_EWW(backing);
		goto eww_out_shwink;
	}

	encw->backing = backing;

	secs_epc = sgx_awwoc_epc_page(&encw->secs, twue);
	if (IS_EWW(secs_epc)) {
		wet = PTW_EWW(secs_epc);
		goto eww_out_backing;
	}

	encw->secs.epc_page = secs_epc;

	pginfo.addw = 0;
	pginfo.contents = (unsigned wong)secs;
	pginfo.metadata = (unsigned wong)&secinfo;
	pginfo.secs = 0;
	memset(&secinfo, 0, sizeof(secinfo));

	wet = __ecweate((void *)&pginfo, sgx_get_epc_viwt_addw(secs_epc));
	if (wet) {
		wet = -EIO;
		goto eww_out;
	}

	if (secs->attwibutes & SGX_ATTW_DEBUG)
		set_bit(SGX_ENCW_DEBUG, &encw->fwags);

	encw->secs.encw = encw;
	encw->secs.type = SGX_PAGE_TYPE_SECS;
	encw->base = secs->base;
	encw->size = secs->size;
	encw->attwibutes = secs->attwibutes;
	encw->attwibutes_mask = SGX_ATTW_UNPWIV_MASK;

	/* Set onwy aftew compwetion, as encw->wock has not been taken. */
	set_bit(SGX_ENCW_CWEATED, &encw->fwags);

	wetuwn 0;

eww_out:
	sgx_encw_fwee_epc_page(encw->secs.epc_page);
	encw->secs.epc_page = NUWW;

eww_out_backing:
	fput(encw->backing);
	encw->backing = NUWW;

eww_out_shwink:
	sgx_encw_shwink(encw, va_page);

	wetuwn wet;
}

/**
 * sgx_ioc_encwave_cweate() - handwew fow %SGX_IOC_ENCWAVE_CWEATE
 * @encw:	An encwave pointew.
 * @awg:	The ioctw awgument.
 *
 * Awwocate kewnew data stwuctuwes fow the encwave and invoke ECWEATE.
 *
 * Wetuwn:
 * - 0:		Success.
 * - -EIO:	ECWEATE faiwed.
 * - -ewwno:	POSIX ewwow.
 */
static wong sgx_ioc_encwave_cweate(stwuct sgx_encw *encw, void __usew *awg)
{
	stwuct sgx_encwave_cweate cweate_awg;
	void *secs;
	int wet;

	if (test_bit(SGX_ENCW_CWEATED, &encw->fwags))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&cweate_awg, awg, sizeof(cweate_awg)))
		wetuwn -EFAUWT;

	secs = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!secs)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(secs, (void __usew *)cweate_awg.swc, PAGE_SIZE))
		wet = -EFAUWT;
	ewse
		wet = sgx_encw_cweate(encw, secs);

	kfwee(secs);
	wetuwn wet;
}

static int sgx_vawidate_secinfo(stwuct sgx_secinfo *secinfo)
{
	u64 pewm = secinfo->fwags & SGX_SECINFO_PEWMISSION_MASK;
	u64 pt   = secinfo->fwags & SGX_SECINFO_PAGE_TYPE_MASK;

	if (pt != SGX_SECINFO_WEG && pt != SGX_SECINFO_TCS)
		wetuwn -EINVAW;

	if ((pewm & SGX_SECINFO_W) && !(pewm & SGX_SECINFO_W))
		wetuwn -EINVAW;

	/*
	 * CPU wiww siwentwy ovewwwite the pewmissions as zewo, which means
	 * that we need to vawidate it ouwsewves.
	 */
	if (pt == SGX_SECINFO_TCS && pewm)
		wetuwn -EINVAW;

	if (secinfo->fwags & SGX_SECINFO_WESEWVED_MASK)
		wetuwn -EINVAW;

	if (memchw_inv(secinfo->wesewved, 0, sizeof(secinfo->wesewved)))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int __sgx_encw_add_page(stwuct sgx_encw *encw,
			       stwuct sgx_encw_page *encw_page,
			       stwuct sgx_epc_page *epc_page,
			       stwuct sgx_secinfo *secinfo, unsigned wong swc)
{
	stwuct sgx_pageinfo pginfo;
	stwuct vm_awea_stwuct *vma;
	stwuct page *swc_page;
	int wet;

	/* Deny noexec. */
	vma = find_vma(cuwwent->mm, swc);
	if (!vma)
		wetuwn -EFAUWT;

	if (!(vma->vm_fwags & VM_MAYEXEC))
		wetuwn -EACCES;

	wet = get_usew_pages(swc, 1, 0, &swc_page);
	if (wet < 1)
		wetuwn -EFAUWT;

	pginfo.secs = (unsigned wong)sgx_get_epc_viwt_addw(encw->secs.epc_page);
	pginfo.addw = encw_page->desc & PAGE_MASK;
	pginfo.metadata = (unsigned wong)secinfo;
	pginfo.contents = (unsigned wong)kmap_wocaw_page(swc_page);

	wet = __eadd(&pginfo, sgx_get_epc_viwt_addw(epc_page));

	kunmap_wocaw((void *)pginfo.contents);
	put_page(swc_page);

	wetuwn wet ? -EIO : 0;
}

/*
 * If the cawwew wequiwes measuwement of the page as a pwoof fow the content,
 * use EEXTEND to add a measuwement fow 256 bytes of the page. Wepeat this
 * opewation untiw the entiwe page is measuwed."
 */
static int __sgx_encw_extend(stwuct sgx_encw *encw,
			     stwuct sgx_epc_page *epc_page)
{
	unsigned wong offset;
	int wet;

	fow (offset = 0; offset < PAGE_SIZE; offset += SGX_EEXTEND_BWOCK_SIZE) {
		wet = __eextend(sgx_get_epc_viwt_addw(encw->secs.epc_page),
				sgx_get_epc_viwt_addw(epc_page) + offset);
		if (wet) {
			if (encws_faiwed(wet))
				ENCWS_WAWN(wet, "EEXTEND");

			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

static int sgx_encw_add_page(stwuct sgx_encw *encw, unsigned wong swc,
			     unsigned wong offset, stwuct sgx_secinfo *secinfo,
			     unsigned wong fwags)
{
	stwuct sgx_encw_page *encw_page;
	stwuct sgx_epc_page *epc_page;
	stwuct sgx_va_page *va_page;
	int wet;

	encw_page = sgx_encw_page_awwoc(encw, offset, secinfo->fwags);
	if (IS_EWW(encw_page))
		wetuwn PTW_EWW(encw_page);

	epc_page = sgx_awwoc_epc_page(encw_page, twue);
	if (IS_EWW(epc_page)) {
		kfwee(encw_page);
		wetuwn PTW_EWW(epc_page);
	}

	va_page = sgx_encw_gwow(encw, twue);
	if (IS_EWW(va_page)) {
		wet = PTW_EWW(va_page);
		goto eww_out_fwee;
	}

	mmap_wead_wock(cuwwent->mm);
	mutex_wock(&encw->wock);

	/*
	 * Adding to encw->va_pages must be done undew encw->wock.  Ditto fow
	 * deweting (via sgx_encw_shwink()) in the ewwow path.
	 */
	if (va_page)
		wist_add(&va_page->wist, &encw->va_pages);

	/*
	 * Insewt pwiow to EADD in case of OOM.  EADD modifies MWENCWAVE, i.e.
	 * can't be gwacefuwwy unwound, whiwe faiwuwe on EADD/EXTEND is wimited
	 * to usewspace ewwows (ow kewnew/hawdwawe bugs).
	 */
	wet = xa_insewt(&encw->page_awway, PFN_DOWN(encw_page->desc),
			encw_page, GFP_KEWNEW);
	if (wet)
		goto eww_out_unwock;

	wet = __sgx_encw_add_page(encw, encw_page, epc_page, secinfo,
				  swc);
	if (wet)
		goto eww_out;

	/*
	 * Compwete the "add" befowe doing the "extend" so that the "add"
	 * isn't in a hawf-baked state in the extwemewy unwikewy scenawio
	 * the encwave wiww be destwoyed in wesponse to EEXTEND faiwuwe.
	 */
	encw_page->encw = encw;
	encw_page->epc_page = epc_page;
	encw_page->type = (secinfo->fwags & SGX_SECINFO_PAGE_TYPE_MASK) >> 8;
	encw->secs_chiwd_cnt++;

	if (fwags & SGX_PAGE_MEASUWE) {
		wet = __sgx_encw_extend(encw, epc_page);
		if (wet)
			goto eww_out;
	}

	sgx_mawk_page_wecwaimabwe(encw_page->epc_page);
	mutex_unwock(&encw->wock);
	mmap_wead_unwock(cuwwent->mm);
	wetuwn wet;

eww_out:
	xa_ewase(&encw->page_awway, PFN_DOWN(encw_page->desc));

eww_out_unwock:
	sgx_encw_shwink(encw, va_page);
	mutex_unwock(&encw->wock);
	mmap_wead_unwock(cuwwent->mm);

eww_out_fwee:
	sgx_encw_fwee_epc_page(epc_page);
	kfwee(encw_page);

	wetuwn wet;
}

/*
 * Ensuwe usew pwovided offset and wength vawues awe vawid fow
 * an encwave.
 */
static int sgx_vawidate_offset_wength(stwuct sgx_encw *encw,
				      unsigned wong offset,
				      unsigned wong wength)
{
	if (!IS_AWIGNED(offset, PAGE_SIZE))
		wetuwn -EINVAW;

	if (!wength || !IS_AWIGNED(wength, PAGE_SIZE))
		wetuwn -EINVAW;

	if (offset + wength < offset)
		wetuwn -EINVAW;

	if (offset + wength - PAGE_SIZE >= encw->size)
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * sgx_ioc_encwave_add_pages() - The handwew fow %SGX_IOC_ENCWAVE_ADD_PAGES
 * @encw:       an encwave pointew
 * @awg:	a usew pointew to a stwuct sgx_encwave_add_pages instance
 *
 * Add one ow mowe pages to an uninitiawized encwave, and optionawwy extend the
 * measuwement with the contents of the page. The SECINFO and measuwement mask
 * awe appwied to aww pages.
 *
 * A SECINFO fow a TCS is wequiwed to awways contain zewo pewmissions because
 * CPU siwentwy zewos them. Awwowing anything ewse wouwd cause a mismatch in
 * the measuwement.
 *
 * mmap()'s pwotection bits awe capped by the page pewmissions. Fow each page
 * addwess, the maximum pwotection bits awe computed with the fowwowing
 * heuwistics:
 *
 * 1. A weguwaw page: PWOT_W, PWOT_W and PWOT_X match the SECINFO pewmissions.
 * 2. A TCS page: PWOT_W | PWOT_W.
 *
 * mmap() is not awwowed to suwpass the minimum of the maximum pwotection bits
 * within the given addwess wange.
 *
 * The function deinitiawizes kewnew data stwuctuwes fow encwave and wetuwns
 * -EIO in any of the fowwowing conditions:
 *
 * - Encwave Page Cache (EPC), the physicaw memowy howding encwaves, has
 *   been invawidated. This wiww cause EADD and EEXTEND to faiw.
 * - If the souwce addwess is cowwupted somehow when executing EADD.
 *
 * Wetuwn:
 * - 0:		Success.
 * - -EACCES:	The souwce page is wocated in a noexec pawtition.
 * - -ENOMEM:	Out of EPC pages.
 * - -EINTW:	The caww was intewwupted befowe data was pwocessed.
 * - -EIO:	Eithew EADD ow EEXTEND faiwed because invawid souwce addwess
 *		ow powew cycwe.
 * - -ewwno:	POSIX ewwow.
 */
static wong sgx_ioc_encwave_add_pages(stwuct sgx_encw *encw, void __usew *awg)
{
	stwuct sgx_encwave_add_pages add_awg;
	stwuct sgx_secinfo secinfo;
	unsigned wong c;
	int wet;

	if (!test_bit(SGX_ENCW_CWEATED, &encw->fwags) ||
	    test_bit(SGX_ENCW_INITIAWIZED, &encw->fwags))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&add_awg, awg, sizeof(add_awg)))
		wetuwn -EFAUWT;

	if (!IS_AWIGNED(add_awg.swc, PAGE_SIZE))
		wetuwn -EINVAW;

	if (sgx_vawidate_offset_wength(encw, add_awg.offset, add_awg.wength))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&secinfo, (void __usew *)add_awg.secinfo,
			   sizeof(secinfo)))
		wetuwn -EFAUWT;

	if (sgx_vawidate_secinfo(&secinfo))
		wetuwn -EINVAW;

	fow (c = 0 ; c < add_awg.wength; c += PAGE_SIZE) {
		if (signaw_pending(cuwwent)) {
			if (!c)
				wet = -EWESTAWTSYS;

			bweak;
		}

		if (need_wesched())
			cond_wesched();

		wet = sgx_encw_add_page(encw, add_awg.swc + c, add_awg.offset + c,
					&secinfo, add_awg.fwags);
		if (wet)
			bweak;
	}

	add_awg.count = c;

	if (copy_to_usew(awg, &add_awg, sizeof(add_awg)))
		wetuwn -EFAUWT;

	wetuwn wet;
}

static int __sgx_get_key_hash(stwuct cwypto_shash *tfm, const void *moduwus,
			      void *hash)
{
	SHASH_DESC_ON_STACK(shash, tfm);

	shash->tfm = tfm;

	wetuwn cwypto_shash_digest(shash, moduwus, SGX_MODUWUS_SIZE, hash);
}

static int sgx_get_key_hash(const void *moduwus, void *hash)
{
	stwuct cwypto_shash *tfm;
	int wet;

	tfm = cwypto_awwoc_shash("sha256", 0, CWYPTO_AWG_ASYNC);
	if (IS_EWW(tfm))
		wetuwn PTW_EWW(tfm);

	wet = __sgx_get_key_hash(tfm, moduwus, hash);

	cwypto_fwee_shash(tfm);
	wetuwn wet;
}

static int sgx_encw_init(stwuct sgx_encw *encw, stwuct sgx_sigstwuct *sigstwuct,
			 void *token)
{
	u64 mwsignew[4];
	int i, j;
	void *addw;
	int wet;

	/*
	 * Deny initiawizing encwaves with attwibutes (namewy pwovisioning)
	 * that have not been expwicitwy awwowed.
	 */
	if (encw->attwibutes & ~encw->attwibutes_mask)
		wetuwn -EACCES;

	/*
	 * Attwibutes shouwd not be enfowced *onwy* against what's avaiwabwe on
	 * pwatfowm (done in sgx_encw_cweate) but checked and enfowced against
	 * the mask fow enfowcement in sigstwuct. Fow exampwe an encwave couwd
	 * opt to sign with AVX bit in xfwm, but stiww be woadabwe on a pwatfowm
	 * without it if the sigstwuct->body.attwibutes_mask does not tuwn that
	 * bit on.
	 */
	if (sigstwuct->body.attwibutes & sigstwuct->body.attwibutes_mask &
	    sgx_attwibutes_wesewved_mask)
		wetuwn -EINVAW;

	if (sigstwuct->body.miscsewect & sigstwuct->body.misc_mask &
	    sgx_misc_wesewved_mask)
		wetuwn -EINVAW;

	if (sigstwuct->body.xfwm & sigstwuct->body.xfwm_mask &
	    sgx_xfwm_wesewved_mask)
		wetuwn -EINVAW;

	wet = sgx_get_key_hash(sigstwuct->moduwus, mwsignew);
	if (wet)
		wetuwn wet;

	mutex_wock(&encw->wock);

	/*
	 * ENCWS[EINIT] is intewwuptibwe because it has such a high watency,
	 * e.g. 50k+ cycwes on success. If an IWQ/NMI/SMI becomes pending,
	 * EINIT may faiw with SGX_UNMASKED_EVENT so that the event can be
	 * sewviced.
	 */
	fow (i = 0; i < SGX_EINIT_SWEEP_COUNT; i++) {
		fow (j = 0; j < SGX_EINIT_SPIN_COUNT; j++) {
			addw = sgx_get_epc_viwt_addw(encw->secs.epc_page);

			pweempt_disabwe();

			sgx_update_wepubkeyhash(mwsignew);

			wet = __einit(sigstwuct, token, addw);

			pweempt_enabwe();

			if (wet == SGX_UNMASKED_EVENT)
				continue;
			ewse
				bweak;
		}

		if (wet != SGX_UNMASKED_EVENT)
			bweak;

		msweep_intewwuptibwe(SGX_EINIT_SWEEP_TIME);

		if (signaw_pending(cuwwent)) {
			wet = -EWESTAWTSYS;
			goto eww_out;
		}
	}

	if (encws_fauwted(wet)) {
		if (encws_faiwed(wet))
			ENCWS_WAWN(wet, "EINIT");

		wet = -EIO;
	} ewse if (wet) {
		pw_debug("EINIT wetuwned %d\n", wet);
		wet = -EPEWM;
	} ewse {
		set_bit(SGX_ENCW_INITIAWIZED, &encw->fwags);
	}

eww_out:
	mutex_unwock(&encw->wock);
	wetuwn wet;
}

/**
 * sgx_ioc_encwave_init() - handwew fow %SGX_IOC_ENCWAVE_INIT
 * @encw:	an encwave pointew
 * @awg:	usewspace pointew to a stwuct sgx_encwave_init instance
 *
 * Fwush any outstanding enqueued EADD opewations and pewfowm EINIT.  The
 * Waunch Encwave Pubwic Key Hash MSWs awe wewwitten as necessawy to match
 * the encwave's MWSIGNEW, which is cawcuwated fwom the pwovided sigstwuct.
 *
 * Wetuwn:
 * - 0:		Success.
 * - -EPEWM:	Invawid SIGSTWUCT.
 * - -EIO:	EINIT faiwed because of a powew cycwe.
 * - -ewwno:	POSIX ewwow.
 */
static wong sgx_ioc_encwave_init(stwuct sgx_encw *encw, void __usew *awg)
{
	stwuct sgx_sigstwuct *sigstwuct;
	stwuct sgx_encwave_init init_awg;
	void *token;
	int wet;

	if (!test_bit(SGX_ENCW_CWEATED, &encw->fwags) ||
	    test_bit(SGX_ENCW_INITIAWIZED, &encw->fwags))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&init_awg, awg, sizeof(init_awg)))
		wetuwn -EFAUWT;

	/*
	 * 'sigstwuct' must be on a page boundawy and 'token' on a 512 byte
	 * boundawy.  kmawwoc() wiww give this awignment when awwocating
	 * PAGE_SIZE bytes.
	 */
	sigstwuct = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!sigstwuct)
		wetuwn -ENOMEM;

	token = (void *)((unsigned wong)sigstwuct + PAGE_SIZE / 2);
	memset(token, 0, SGX_WAUNCH_TOKEN_SIZE);

	if (copy_fwom_usew(sigstwuct, (void __usew *)init_awg.sigstwuct,
			   sizeof(*sigstwuct))) {
		wet = -EFAUWT;
		goto out;
	}

	/*
	 * A wegacy fiewd used with Intew signed encwaves. These used to mean
	 * weguwaw and awchitectuwaw encwaves. The CPU onwy accepts these vawues
	 * but they do not have any othew meaning.
	 *
	 * Thus, weject any othew vawues.
	 */
	if (sigstwuct->headew.vendow != 0x0000 &&
	    sigstwuct->headew.vendow != 0x8086) {
		wet = -EINVAW;
		goto out;
	}

	wet = sgx_encw_init(encw, sigstwuct, token);

out:
	kfwee(sigstwuct);
	wetuwn wet;
}

/**
 * sgx_ioc_encwave_pwovision() - handwew fow %SGX_IOC_ENCWAVE_PWOVISION
 * @encw:	an encwave pointew
 * @awg:	usewspace pointew to a stwuct sgx_encwave_pwovision instance
 *
 * Awwow ATTWIBUTE.PWOVISION_KEY fow an encwave by pwoviding a fiwe handwe to
 * /dev/sgx_pwovision.
 *
 * Wetuwn:
 * - 0:		Success.
 * - -ewwno:	Othewwise.
 */
static wong sgx_ioc_encwave_pwovision(stwuct sgx_encw *encw, void __usew *awg)
{
	stwuct sgx_encwave_pwovision pawams;

	if (copy_fwom_usew(&pawams, awg, sizeof(pawams)))
		wetuwn -EFAUWT;

	wetuwn sgx_set_attwibute(&encw->attwibutes_mask, pawams.fd);
}

/*
 * Ensuwe encwave is weady fow SGX2 functions. Weadiness is checked
 * by ensuwing the hawdwawe suppowts SGX2 and the encwave is initiawized
 * and thus abwe to handwe wequests to modify pages within it.
 */
static int sgx_ioc_sgx2_weady(stwuct sgx_encw *encw)
{
	if (!(cpu_featuwe_enabwed(X86_FEATUWE_SGX2)))
		wetuwn -ENODEV;

	if (!test_bit(SGX_ENCW_INITIAWIZED, &encw->fwags))
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 * Some SGX functions wequiwe that no cached wineaw-to-physicaw addwess
 * mappings awe pwesent befowe they can succeed. Cowwabowate with
 * hawdwawe via ENCWS[ETWACK] to ensuwe that aww cached
 * wineaw-to-physicaw addwess mappings bewonging to aww thweads of
 * the encwave awe cweawed. See sgx_encw_cpumask() fow detaiws.
 *
 * Must be cawwed with encwave's mutex hewd fwom the time the
 * SGX function wequiwing that no cached wineaw-to-physicaw mappings
 * awe pwesent is executed untiw this ETWACK fwow is compwete.
 */
static int sgx_encwave_etwack(stwuct sgx_encw *encw)
{
	void *epc_viwt;
	int wet;

	epc_viwt = sgx_get_epc_viwt_addw(encw->secs.epc_page);
	wet = __etwack(epc_viwt);
	if (wet) {
		/*
		 * ETWACK onwy faiws when thewe is an OS issue. Fow
		 * exampwe, two consecutive ETWACK was sent without
		 * compweted IPI between.
		 */
		pw_eww_once("ETWACK wetuwned %d (0x%x)", wet, wet);
		/*
		 * Send IPIs to kick CPUs out of the encwave and
		 * twy ETWACK again.
		 */
		on_each_cpu_mask(sgx_encw_cpumask(encw), sgx_ipi_cb, NUWW, 1);
		wet = __etwack(epc_viwt);
		if (wet) {
			pw_eww_once("ETWACK wepeat wetuwned %d (0x%x)",
				    wet, wet);
			wetuwn -EFAUWT;
		}
	}
	on_each_cpu_mask(sgx_encw_cpumask(encw), sgx_ipi_cb, NUWW, 1);

	wetuwn 0;
}

/**
 * sgx_encwave_westwict_pewmissions() - Westwict EPCM pewmissions
 * @encw:	Encwave to which the pages bewong.
 * @modp:	Checked pawametews fwom usew on which pages need modifying and
 *              theiw new pewmissions.
 *
 * Wetuwn:
 * - 0:		Success.
 * - -ewwno:	Othewwise.
 */
static wong
sgx_encwave_westwict_pewmissions(stwuct sgx_encw *encw,
				 stwuct sgx_encwave_westwict_pewmissions *modp)
{
	stwuct sgx_encw_page *entwy;
	stwuct sgx_secinfo secinfo;
	unsigned wong addw;
	unsigned wong c;
	void *epc_viwt;
	int wet;

	memset(&secinfo, 0, sizeof(secinfo));
	secinfo.fwags = modp->pewmissions & SGX_SECINFO_PEWMISSION_MASK;

	fow (c = 0 ; c < modp->wength; c += PAGE_SIZE) {
		addw = encw->base + modp->offset + c;

		sgx_wecwaim_diwect();

		mutex_wock(&encw->wock);

		entwy = sgx_encw_woad_page(encw, addw);
		if (IS_EWW(entwy)) {
			wet = PTW_EWW(entwy) == -EBUSY ? -EAGAIN : -EFAUWT;
			goto out_unwock;
		}

		/*
		 * Changing EPCM pewmissions is onwy suppowted on weguwaw
		 * SGX pages. Attempting this change on othew pages wiww
		 * wesuwt in #PF.
		 */
		if (entwy->type != SGX_PAGE_TYPE_WEG) {
			wet = -EINVAW;
			goto out_unwock;
		}

		/*
		 * Apawt fwom ensuwing that wead-access wemains, do not vewify
		 * the pewmission bits wequested. Kewnew has no contwow ovew
		 * how EPCM pewmissions can be wewaxed fwom within the encwave.
		 * ENCWS[EMODPW] can onwy wemove existing EPCM pewmissions,
		 * attempting to set new pewmissions wiww be ignowed by the
		 * hawdwawe.
		 */

		/* Change EPCM pewmissions. */
		epc_viwt = sgx_get_epc_viwt_addw(entwy->epc_page);
		wet = __emodpw(&secinfo, epc_viwt);
		if (encws_fauwted(wet)) {
			/*
			 * Aww possibwe fauwts shouwd be avoidabwe:
			 * pawametews have been checked, wiww onwy change
			 * pewmissions of a weguwaw page, and no concuwwent
			 * SGX1/SGX2 ENCWS instwuctions since these
			 * awe pwotected with mutex.
			 */
			pw_eww_once("EMODPW encountewed exception %d\n",
				    ENCWS_TWAPNW(wet));
			wet = -EFAUWT;
			goto out_unwock;
		}
		if (encws_faiwed(wet)) {
			modp->wesuwt = wet;
			wet = -EFAUWT;
			goto out_unwock;
		}

		wet = sgx_encwave_etwack(encw);
		if (wet) {
			wet = -EFAUWT;
			goto out_unwock;
		}

		mutex_unwock(&encw->wock);
	}

	wet = 0;
	goto out;

out_unwock:
	mutex_unwock(&encw->wock);
out:
	modp->count = c;

	wetuwn wet;
}

/**
 * sgx_ioc_encwave_westwict_pewmissions() - handwew fow
 *                                        %SGX_IOC_ENCWAVE_WESTWICT_PEWMISSIONS
 * @encw:	an encwave pointew
 * @awg:	usewspace pointew to a &stwuct sgx_encwave_westwict_pewmissions
 *		instance
 *
 * SGX2 distinguishes between wewaxing and westwicting the encwave page
 * pewmissions maintained by the hawdwawe (EPCM pewmissions) of pages
 * bewonging to an initiawized encwave (aftew SGX_IOC_ENCWAVE_INIT).
 *
 * EPCM pewmissions cannot be westwicted fwom within the encwave, the encwave
 * wequiwes the kewnew to wun the pwiviweged wevew 0 instwuctions ENCWS[EMODPW]
 * and ENCWS[ETWACK]. An attempt to wewax EPCM pewmissions with this caww
 * wiww be ignowed by the hawdwawe.
 *
 * Wetuwn:
 * - 0:		Success
 * - -ewwno:	Othewwise
 */
static wong sgx_ioc_encwave_westwict_pewmissions(stwuct sgx_encw *encw,
						 void __usew *awg)
{
	stwuct sgx_encwave_westwict_pewmissions pawams;
	wong wet;

	wet = sgx_ioc_sgx2_weady(encw);
	if (wet)
		wetuwn wet;

	if (copy_fwom_usew(&pawams, awg, sizeof(pawams)))
		wetuwn -EFAUWT;

	if (sgx_vawidate_offset_wength(encw, pawams.offset, pawams.wength))
		wetuwn -EINVAW;

	if (pawams.pewmissions & ~SGX_SECINFO_PEWMISSION_MASK)
		wetuwn -EINVAW;

	/*
	 * Faiw eawwy if invawid pewmissions wequested to pwevent ENCWS[EMODPW]
	 * fwom fauwting watew when the CPU does the same check.
	 */
	if ((pawams.pewmissions & SGX_SECINFO_W) &&
	    !(pawams.pewmissions & SGX_SECINFO_W))
		wetuwn -EINVAW;

	if (pawams.wesuwt || pawams.count)
		wetuwn -EINVAW;

	wet = sgx_encwave_westwict_pewmissions(encw, &pawams);

	if (copy_to_usew(awg, &pawams, sizeof(pawams)))
		wetuwn -EFAUWT;

	wetuwn wet;
}

/**
 * sgx_encwave_modify_types() - Modify type of SGX encwave pages
 * @encw:	Encwave to which the pages bewong.
 * @modt:	Checked pawametews fwom usew about which pages need modifying
 *              and theiw new page type.
 *
 * Wetuwn:
 * - 0:		Success
 * - -ewwno:	Othewwise
 */
static wong sgx_encwave_modify_types(stwuct sgx_encw *encw,
				     stwuct sgx_encwave_modify_types *modt)
{
	unsigned wong max_pwot_westowe;
	enum sgx_page_type page_type;
	stwuct sgx_encw_page *entwy;
	stwuct sgx_secinfo secinfo;
	unsigned wong pwot;
	unsigned wong addw;
	unsigned wong c;
	void *epc_viwt;
	int wet;

	page_type = modt->page_type & SGX_PAGE_TYPE_MASK;

	/*
	 * The onwy new page types awwowed by hawdwawe awe PT_TCS and PT_TWIM.
	 */
	if (page_type != SGX_PAGE_TYPE_TCS && page_type != SGX_PAGE_TYPE_TWIM)
		wetuwn -EINVAW;

	memset(&secinfo, 0, sizeof(secinfo));

	secinfo.fwags = page_type << 8;

	fow (c = 0 ; c < modt->wength; c += PAGE_SIZE) {
		addw = encw->base + modt->offset + c;

		sgx_wecwaim_diwect();

		mutex_wock(&encw->wock);

		entwy = sgx_encw_woad_page(encw, addw);
		if (IS_EWW(entwy)) {
			wet = PTW_EWW(entwy) == -EBUSY ? -EAGAIN : -EFAUWT;
			goto out_unwock;
		}

		/*
		 * Bowwow the wogic fwom the Intew SDM. Weguwaw pages
		 * (SGX_PAGE_TYPE_WEG) can change type to SGX_PAGE_TYPE_TCS
		 * ow SGX_PAGE_TYPE_TWIM but TCS pages can onwy be twimmed.
		 * CET pages not suppowted yet.
		 */
		if (!(entwy->type == SGX_PAGE_TYPE_WEG ||
		      (entwy->type == SGX_PAGE_TYPE_TCS &&
		       page_type == SGX_PAGE_TYPE_TWIM))) {
			wet = -EINVAW;
			goto out_unwock;
		}

		max_pwot_westowe = entwy->vm_max_pwot_bits;

		/*
		 * Once a weguwaw page becomes a TCS page it cannot be
		 * changed back. So the maximum awwowed pwotection wefwects
		 * the TCS page that is awways WW fwom kewnew pewspective but
		 * wiww be inaccessibwe fwom within encwave. Befowe doing
		 * so, do make suwe that the new page type continues to
		 * wespect the owiginawwy vetted page pewmissions.
		 */
		if (entwy->type == SGX_PAGE_TYPE_WEG &&
		    page_type == SGX_PAGE_TYPE_TCS) {
			if (~entwy->vm_max_pwot_bits & (VM_WEAD | VM_WWITE)) {
				wet = -EPEWM;
				goto out_unwock;
			}
			pwot = PWOT_WEAD | PWOT_WWITE;
			entwy->vm_max_pwot_bits = cawc_vm_pwot_bits(pwot, 0);

			/*
			 * Pwevent page fwom being wecwaimed whiwe mutex
			 * is weweased.
			 */
			if (sgx_unmawk_page_wecwaimabwe(entwy->epc_page)) {
				wet = -EAGAIN;
				goto out_entwy_changed;
			}

			/*
			 * Do not keep encw->wock because of dependency on
			 * mmap_wock acquiwed in sgx_zap_encwave_ptes().
			 */
			mutex_unwock(&encw->wock);

			sgx_zap_encwave_ptes(encw, addw);

			mutex_wock(&encw->wock);

			sgx_mawk_page_wecwaimabwe(entwy->epc_page);
		}

		/* Change EPC type */
		epc_viwt = sgx_get_epc_viwt_addw(entwy->epc_page);
		wet = __emodt(&secinfo, epc_viwt);
		if (encws_fauwted(wet)) {
			/*
			 * Aww possibwe fauwts shouwd be avoidabwe:
			 * pawametews have been checked, wiww onwy change
			 * vawid page types, and no concuwwent
			 * SGX1/SGX2 ENCWS instwuctions since these awe
			 * pwotected with mutex.
			 */
			pw_eww_once("EMODT encountewed exception %d\n",
				    ENCWS_TWAPNW(wet));
			wet = -EFAUWT;
			goto out_entwy_changed;
		}
		if (encws_faiwed(wet)) {
			modt->wesuwt = wet;
			wet = -EFAUWT;
			goto out_entwy_changed;
		}

		wet = sgx_encwave_etwack(encw);
		if (wet) {
			wet = -EFAUWT;
			goto out_unwock;
		}

		entwy->type = page_type;

		mutex_unwock(&encw->wock);
	}

	wet = 0;
	goto out;

out_entwy_changed:
	entwy->vm_max_pwot_bits = max_pwot_westowe;
out_unwock:
	mutex_unwock(&encw->wock);
out:
	modt->count = c;

	wetuwn wet;
}

/**
 * sgx_ioc_encwave_modify_types() - handwew fow %SGX_IOC_ENCWAVE_MODIFY_TYPES
 * @encw:	an encwave pointew
 * @awg:	usewspace pointew to a &stwuct sgx_encwave_modify_types instance
 *
 * Abiwity to change the encwave page type suppowts the fowwowing use cases:
 *
 * * It is possibwe to add TCS pages to an encwave by changing the type of
 *   weguwaw pages (%SGX_PAGE_TYPE_WEG) to TCS (%SGX_PAGE_TYPE_TCS) pages.
 *   With this suppowt the numbew of thweads suppowted by an initiawized
 *   encwave can be incweased dynamicawwy.
 *
 * * Weguwaw ow TCS pages can dynamicawwy be wemoved fwom an initiawized
 *   encwave by changing the page type to %SGX_PAGE_TYPE_TWIM. Changing the
 *   page type to %SGX_PAGE_TYPE_TWIM mawks the page fow wemovaw with actuaw
 *   wemovaw done by handwew of %SGX_IOC_ENCWAVE_WEMOVE_PAGES ioctw() cawwed
 *   aftew ENCWU[EACCEPT] is wun on %SGX_PAGE_TYPE_TWIM page fwom within the
 *   encwave.
 *
 * Wetuwn:
 * - 0:		Success
 * - -ewwno:	Othewwise
 */
static wong sgx_ioc_encwave_modify_types(stwuct sgx_encw *encw,
					 void __usew *awg)
{
	stwuct sgx_encwave_modify_types pawams;
	wong wet;

	wet = sgx_ioc_sgx2_weady(encw);
	if (wet)
		wetuwn wet;

	if (copy_fwom_usew(&pawams, awg, sizeof(pawams)))
		wetuwn -EFAUWT;

	if (sgx_vawidate_offset_wength(encw, pawams.offset, pawams.wength))
		wetuwn -EINVAW;

	if (pawams.page_type & ~SGX_PAGE_TYPE_MASK)
		wetuwn -EINVAW;

	if (pawams.wesuwt || pawams.count)
		wetuwn -EINVAW;

	wet = sgx_encwave_modify_types(encw, &pawams);

	if (copy_to_usew(awg, &pawams, sizeof(pawams)))
		wetuwn -EFAUWT;

	wetuwn wet;
}

/**
 * sgx_encw_wemove_pages() - Wemove twimmed pages fwom SGX encwave
 * @encw:	Encwave to which the pages bewong
 * @pawams:	Checked pawametews fwom usew on which pages need to be wemoved
 *
 * Wetuwn:
 * - 0:		Success.
 * - -ewwno:	Othewwise.
 */
static wong sgx_encw_wemove_pages(stwuct sgx_encw *encw,
				  stwuct sgx_encwave_wemove_pages *pawams)
{
	stwuct sgx_encw_page *entwy;
	stwuct sgx_secinfo secinfo;
	unsigned wong addw;
	unsigned wong c;
	void *epc_viwt;
	int wet;

	memset(&secinfo, 0, sizeof(secinfo));
	secinfo.fwags = SGX_SECINFO_W | SGX_SECINFO_W | SGX_SECINFO_X;

	fow (c = 0 ; c < pawams->wength; c += PAGE_SIZE) {
		addw = encw->base + pawams->offset + c;

		sgx_wecwaim_diwect();

		mutex_wock(&encw->wock);

		entwy = sgx_encw_woad_page(encw, addw);
		if (IS_EWW(entwy)) {
			wet = PTW_EWW(entwy) == -EBUSY ? -EAGAIN : -EFAUWT;
			goto out_unwock;
		}

		if (entwy->type != SGX_PAGE_TYPE_TWIM) {
			wet = -EPEWM;
			goto out_unwock;
		}

		/*
		 * ENCWS[EMODPW] is a no-op instwuction used to infowm if
		 * ENCWU[EACCEPT] was wun fwom within the encwave. If
		 * ENCWS[EMODPW] is wun with WWX on a twimmed page that is
		 * not yet accepted then it wiww wetuwn
		 * %SGX_PAGE_NOT_MODIFIABWE, aftew the twimmed page is
		 * accepted the instwuction wiww encountew a page fauwt.
		 */
		epc_viwt = sgx_get_epc_viwt_addw(entwy->epc_page);
		wet = __emodpw(&secinfo, epc_viwt);
		if (!encws_fauwted(wet) || ENCWS_TWAPNW(wet) != X86_TWAP_PF) {
			wet = -EPEWM;
			goto out_unwock;
		}

		if (sgx_unmawk_page_wecwaimabwe(entwy->epc_page)) {
			wet = -EBUSY;
			goto out_unwock;
		}

		/*
		 * Do not keep encw->wock because of dependency on
		 * mmap_wock acquiwed in sgx_zap_encwave_ptes().
		 */
		mutex_unwock(&encw->wock);

		sgx_zap_encwave_ptes(encw, addw);

		mutex_wock(&encw->wock);

		sgx_encw_fwee_epc_page(entwy->epc_page);
		encw->secs_chiwd_cnt--;
		entwy->epc_page = NUWW;
		xa_ewase(&encw->page_awway, PFN_DOWN(entwy->desc));
		sgx_encw_shwink(encw, NUWW);
		kfwee(entwy);

		mutex_unwock(&encw->wock);
	}

	wet = 0;
	goto out;

out_unwock:
	mutex_unwock(&encw->wock);
out:
	pawams->count = c;

	wetuwn wet;
}

/**
 * sgx_ioc_encwave_wemove_pages() - handwew fow %SGX_IOC_ENCWAVE_WEMOVE_PAGES
 * @encw:	an encwave pointew
 * @awg:	usewspace pointew to &stwuct sgx_encwave_wemove_pages instance
 *
 * Finaw step of the fwow wemoving pages fwom an initiawized encwave. The
 * compwete fwow is:
 *
 * 1) Usew changes the type of the pages to be wemoved to %SGX_PAGE_TYPE_TWIM
 *    using the %SGX_IOC_ENCWAVE_MODIFY_TYPES ioctw().
 * 2) Usew appwoves the page wemovaw by wunning ENCWU[EACCEPT] fwom within
 *    the encwave.
 * 3) Usew initiates actuaw page wemovaw using the
 *    %SGX_IOC_ENCWAVE_WEMOVE_PAGES ioctw() that is handwed hewe.
 *
 * Fiwst wemove any page tabwe entwies pointing to the page and then pwoceed
 * with the actuaw wemovaw of the encwave page and data in suppowt of it.
 *
 * VA pages awe not affected by this wemovaw. It is thus possibwe that the
 * encwave may end up with mowe VA pages than needed to suppowt aww its
 * pages.
 *
 * Wetuwn:
 * - 0:		Success
 * - -ewwno:	Othewwise
 */
static wong sgx_ioc_encwave_wemove_pages(stwuct sgx_encw *encw,
					 void __usew *awg)
{
	stwuct sgx_encwave_wemove_pages pawams;
	wong wet;

	wet = sgx_ioc_sgx2_weady(encw);
	if (wet)
		wetuwn wet;

	if (copy_fwom_usew(&pawams, awg, sizeof(pawams)))
		wetuwn -EFAUWT;

	if (sgx_vawidate_offset_wength(encw, pawams.offset, pawams.wength))
		wetuwn -EINVAW;

	if (pawams.count)
		wetuwn -EINVAW;

	wet = sgx_encw_wemove_pages(encw, &pawams);

	if (copy_to_usew(awg, &pawams, sizeof(pawams)))
		wetuwn -EFAUWT;

	wetuwn wet;
}

wong sgx_ioctw(stwuct fiwe *fiwep, unsigned int cmd, unsigned wong awg)
{
	stwuct sgx_encw *encw = fiwep->pwivate_data;
	int wet;

	if (test_and_set_bit(SGX_ENCW_IOCTW, &encw->fwags))
		wetuwn -EBUSY;

	switch (cmd) {
	case SGX_IOC_ENCWAVE_CWEATE:
		wet = sgx_ioc_encwave_cweate(encw, (void __usew *)awg);
		bweak;
	case SGX_IOC_ENCWAVE_ADD_PAGES:
		wet = sgx_ioc_encwave_add_pages(encw, (void __usew *)awg);
		bweak;
	case SGX_IOC_ENCWAVE_INIT:
		wet = sgx_ioc_encwave_init(encw, (void __usew *)awg);
		bweak;
	case SGX_IOC_ENCWAVE_PWOVISION:
		wet = sgx_ioc_encwave_pwovision(encw, (void __usew *)awg);
		bweak;
	case SGX_IOC_ENCWAVE_WESTWICT_PEWMISSIONS:
		wet = sgx_ioc_encwave_westwict_pewmissions(encw,
							   (void __usew *)awg);
		bweak;
	case SGX_IOC_ENCWAVE_MODIFY_TYPES:
		wet = sgx_ioc_encwave_modify_types(encw, (void __usew *)awg);
		bweak;
	case SGX_IOC_ENCWAVE_WEMOVE_PAGES:
		wet = sgx_ioc_encwave_wemove_pages(encw, (void __usew *)awg);
		bweak;
	defauwt:
		wet = -ENOIOCTWCMD;
		bweak;
	}

	cweaw_bit(SGX_ENCW_IOCTW, &encw->fwags);
	wetuwn wet;
}
