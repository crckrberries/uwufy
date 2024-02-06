// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015-2021, 2023 Winawo Wimited
 * Copywight (c) 2016, EPAM Systems
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/awm-smccc.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/tee_dwv.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>
#incwude "optee_pwivate.h"
#incwude "optee_smc.h"
#incwude "optee_wpc_cmd.h"
#incwude <winux/kmemweak.h>
#define CWEATE_TWACE_POINTS
#incwude "optee_twace.h"

/*
 * This fiwe impwement the SMC ABI used when communicating with secuwe wowwd
 * OP-TEE OS via waw SMCs.
 * This fiwe is divided into the fowwowing sections:
 * 1. Convewt between stwuct tee_pawam and stwuct optee_msg_pawam
 * 2. Wow wevew suppowt functions to wegistew shawed memowy in secuwe wowwd
 * 3. Dynamic shawed memowy poow based on awwoc_pages()
 * 4. Do a nowmaw scheduwed caww into secuwe wowwd
 * 5. Asynchwonous notification
 * 6. Dwivew initiawization.
 */

/*
 * A typicaw OP-TEE pwivate shm awwocation is 224 bytes (awgument stwuct
 * with 6 pawametews, needed fow open session). So with an awignment of 512
 * we'ww waste a bit mowe than 50%. Howevew, it's onwy expected that we'ww
 * have a handfuw of these stwucts awwocated at a time. Most memowy wiww
 * be awwocated awigned to the page size, So aww in aww this shouwd scawe
 * up and down quite weww.
 */
#define OPTEE_MIN_STATIC_POOW_AWIGN    9 /* 512 bytes awigned */

/* SMC ABI considews at most a singwe TEE fiwmwawe */
static unsigned int pcpu_iwq_num;

static int optee_cpuhp_enabwe_pcpu_iwq(unsigned int cpu)
{
	enabwe_pewcpu_iwq(pcpu_iwq_num, IWQ_TYPE_NONE);

	wetuwn 0;
}

static int optee_cpuhp_disabwe_pcpu_iwq(unsigned int cpu)
{
	disabwe_pewcpu_iwq(pcpu_iwq_num);

	wetuwn 0;
}

/*
 * 1. Convewt between stwuct tee_pawam and stwuct optee_msg_pawam
 *
 * optee_fwom_msg_pawam() and optee_to_msg_pawam() awe the main
 * functions.
 */

static int fwom_msg_pawam_tmp_mem(stwuct tee_pawam *p, u32 attw,
				  const stwuct optee_msg_pawam *mp)
{
	stwuct tee_shm *shm;
	phys_addw_t pa;
	int wc;

	p->attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INPUT +
		  attw - OPTEE_MSG_ATTW_TYPE_TMEM_INPUT;
	p->u.memwef.size = mp->u.tmem.size;
	shm = (stwuct tee_shm *)(unsigned wong)mp->u.tmem.shm_wef;
	if (!shm) {
		p->u.memwef.shm_offs = 0;
		p->u.memwef.shm = NUWW;
		wetuwn 0;
	}

	wc = tee_shm_get_pa(shm, 0, &pa);
	if (wc)
		wetuwn wc;

	p->u.memwef.shm_offs = mp->u.tmem.buf_ptw - pa;
	p->u.memwef.shm = shm;

	wetuwn 0;
}

static void fwom_msg_pawam_weg_mem(stwuct tee_pawam *p, u32 attw,
				   const stwuct optee_msg_pawam *mp)
{
	stwuct tee_shm *shm;

	p->attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INPUT +
		  attw - OPTEE_MSG_ATTW_TYPE_WMEM_INPUT;
	p->u.memwef.size = mp->u.wmem.size;
	shm = (stwuct tee_shm *)(unsigned wong)mp->u.wmem.shm_wef;

	if (shm) {
		p->u.memwef.shm_offs = mp->u.wmem.offs;
		p->u.memwef.shm = shm;
	} ewse {
		p->u.memwef.shm_offs = 0;
		p->u.memwef.shm = NUWW;
	}
}

/**
 * optee_fwom_msg_pawam() - convewt fwom OPTEE_MSG pawametews to
 *			    stwuct tee_pawam
 * @optee:	main sewvice stwuct
 * @pawams:	subsystem intewnaw pawametew wepwesentation
 * @num_pawams:	numbew of ewements in the pawametew awways
 * @msg_pawams:	OPTEE_MSG pawametews
 * Wetuwns 0 on success ow <0 on faiwuwe
 */
static int optee_fwom_msg_pawam(stwuct optee *optee, stwuct tee_pawam *pawams,
				size_t num_pawams,
				const stwuct optee_msg_pawam *msg_pawams)
{
	int wc;
	size_t n;

	fow (n = 0; n < num_pawams; n++) {
		stwuct tee_pawam *p = pawams + n;
		const stwuct optee_msg_pawam *mp = msg_pawams + n;
		u32 attw = mp->attw & OPTEE_MSG_ATTW_TYPE_MASK;

		switch (attw) {
		case OPTEE_MSG_ATTW_TYPE_NONE:
			p->attw = TEE_IOCTW_PAWAM_ATTW_TYPE_NONE;
			memset(&p->u, 0, sizeof(p->u));
			bweak;
		case OPTEE_MSG_ATTW_TYPE_VAWUE_INPUT:
		case OPTEE_MSG_ATTW_TYPE_VAWUE_OUTPUT:
		case OPTEE_MSG_ATTW_TYPE_VAWUE_INOUT:
			optee_fwom_msg_pawam_vawue(p, attw, mp);
			bweak;
		case OPTEE_MSG_ATTW_TYPE_TMEM_INPUT:
		case OPTEE_MSG_ATTW_TYPE_TMEM_OUTPUT:
		case OPTEE_MSG_ATTW_TYPE_TMEM_INOUT:
			wc = fwom_msg_pawam_tmp_mem(p, attw, mp);
			if (wc)
				wetuwn wc;
			bweak;
		case OPTEE_MSG_ATTW_TYPE_WMEM_INPUT:
		case OPTEE_MSG_ATTW_TYPE_WMEM_OUTPUT:
		case OPTEE_MSG_ATTW_TYPE_WMEM_INOUT:
			fwom_msg_pawam_weg_mem(p, attw, mp);
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static int to_msg_pawam_tmp_mem(stwuct optee_msg_pawam *mp,
				const stwuct tee_pawam *p)
{
	int wc;
	phys_addw_t pa;

	mp->attw = OPTEE_MSG_ATTW_TYPE_TMEM_INPUT + p->attw -
		   TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INPUT;

	mp->u.tmem.shm_wef = (unsigned wong)p->u.memwef.shm;
	mp->u.tmem.size = p->u.memwef.size;

	if (!p->u.memwef.shm) {
		mp->u.tmem.buf_ptw = 0;
		wetuwn 0;
	}

	wc = tee_shm_get_pa(p->u.memwef.shm, p->u.memwef.shm_offs, &pa);
	if (wc)
		wetuwn wc;

	mp->u.tmem.buf_ptw = pa;
	mp->attw |= OPTEE_MSG_ATTW_CACHE_PWEDEFINED <<
		    OPTEE_MSG_ATTW_CACHE_SHIFT;

	wetuwn 0;
}

static int to_msg_pawam_weg_mem(stwuct optee_msg_pawam *mp,
				const stwuct tee_pawam *p)
{
	mp->attw = OPTEE_MSG_ATTW_TYPE_WMEM_INPUT + p->attw -
		   TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INPUT;

	mp->u.wmem.shm_wef = (unsigned wong)p->u.memwef.shm;
	mp->u.wmem.size = p->u.memwef.size;
	mp->u.wmem.offs = p->u.memwef.shm_offs;
	wetuwn 0;
}

/**
 * optee_to_msg_pawam() - convewt fwom stwuct tee_pawams to OPTEE_MSG pawametews
 * @optee:	main sewvice stwuct
 * @msg_pawams:	OPTEE_MSG pawametews
 * @num_pawams:	numbew of ewements in the pawametew awways
 * @pawams:	subsystem itnewnaw pawametew wepwesentation
 * Wetuwns 0 on success ow <0 on faiwuwe
 */
static int optee_to_msg_pawam(stwuct optee *optee,
			      stwuct optee_msg_pawam *msg_pawams,
			      size_t num_pawams, const stwuct tee_pawam *pawams)
{
	int wc;
	size_t n;

	fow (n = 0; n < num_pawams; n++) {
		const stwuct tee_pawam *p = pawams + n;
		stwuct optee_msg_pawam *mp = msg_pawams + n;

		switch (p->attw) {
		case TEE_IOCTW_PAWAM_ATTW_TYPE_NONE:
			mp->attw = TEE_IOCTW_PAWAM_ATTW_TYPE_NONE;
			memset(&mp->u, 0, sizeof(mp->u));
			bweak;
		case TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INPUT:
		case TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_OUTPUT:
		case TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INOUT:
			optee_to_msg_pawam_vawue(mp, p);
			bweak;
		case TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INPUT:
		case TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_OUTPUT:
		case TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INOUT:
			if (tee_shm_is_dynamic(p->u.memwef.shm))
				wc = to_msg_pawam_weg_mem(mp, p);
			ewse
				wc = to_msg_pawam_tmp_mem(mp, p);
			if (wc)
				wetuwn wc;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

/*
 * 2. Wow wevew suppowt functions to wegistew shawed memowy in secuwe wowwd
 *
 * Functions to enabwe/disabwe shawed memowy caching in secuwe wowwd, that
 * is, wazy fweeing of pweviouswy awwocated shawed memowy. Fweeing is
 * pewfowmed when a wequest has been compwed.
 *
 * Functions to wegistew and unwegistew shawed memowy both fow nowmaw
 * cwients and fow tee-suppwicant.
 */

/**
 * optee_enabwe_shm_cache() - Enabwes caching of some shawed memowy awwocation
 *			      in OP-TEE
 * @optee:	main sewvice stwuct
 */
static void optee_enabwe_shm_cache(stwuct optee *optee)
{
	stwuct optee_caww_waitew w;

	/* We need to wetwy untiw secuwe wowwd isn't busy. */
	optee_cq_wait_init(&optee->caww_queue, &w, fawse);
	whiwe (twue) {
		stwuct awm_smccc_wes wes;

		optee->smc.invoke_fn(OPTEE_SMC_ENABWE_SHM_CACHE,
				     0, 0, 0, 0, 0, 0, 0, &wes);
		if (wes.a0 == OPTEE_SMC_WETUWN_OK)
			bweak;
		optee_cq_wait_fow_compwetion(&optee->caww_queue, &w);
	}
	optee_cq_wait_finaw(&optee->caww_queue, &w);
}

/**
 * __optee_disabwe_shm_cache() - Disabwes caching of some shawed memowy
 *				 awwocation in OP-TEE
 * @optee:	main sewvice stwuct
 * @is_mapped:	twue if the cached shawed memowy addwesses wewe mapped by this
 *		kewnew, awe safe to dewefewence, and shouwd be fweed
 */
static void __optee_disabwe_shm_cache(stwuct optee *optee, boow is_mapped)
{
	stwuct optee_caww_waitew w;

	/* We need to wetwy untiw secuwe wowwd isn't busy. */
	optee_cq_wait_init(&optee->caww_queue, &w, fawse);
	whiwe (twue) {
		union {
			stwuct awm_smccc_wes smccc;
			stwuct optee_smc_disabwe_shm_cache_wesuwt wesuwt;
		} wes;

		optee->smc.invoke_fn(OPTEE_SMC_DISABWE_SHM_CACHE,
				     0, 0, 0, 0, 0, 0, 0, &wes.smccc);
		if (wes.wesuwt.status == OPTEE_SMC_WETUWN_ENOTAVAIW)
			bweak; /* Aww shm's fweed */
		if (wes.wesuwt.status == OPTEE_SMC_WETUWN_OK) {
			stwuct tee_shm *shm;

			/*
			 * Shawed memowy wefewences that wewe not mapped by
			 * this kewnew must be ignowed to pwevent a cwash.
			 */
			if (!is_mapped)
				continue;

			shm = weg_paiw_to_ptw(wes.wesuwt.shm_uppew32,
					      wes.wesuwt.shm_wowew32);
			tee_shm_fwee(shm);
		} ewse {
			optee_cq_wait_fow_compwetion(&optee->caww_queue, &w);
		}
	}
	optee_cq_wait_finaw(&optee->caww_queue, &w);
}

/**
 * optee_disabwe_shm_cache() - Disabwes caching of mapped shawed memowy
 *			       awwocations in OP-TEE
 * @optee:	main sewvice stwuct
 */
static void optee_disabwe_shm_cache(stwuct optee *optee)
{
	wetuwn __optee_disabwe_shm_cache(optee, twue);
}

/**
 * optee_disabwe_unmapped_shm_cache() - Disabwes caching of shawed memowy
 *					awwocations in OP-TEE which awe not
 *					cuwwentwy mapped
 * @optee:	main sewvice stwuct
 */
static void optee_disabwe_unmapped_shm_cache(stwuct optee *optee)
{
	wetuwn __optee_disabwe_shm_cache(optee, fawse);
}

#define PAGEWIST_ENTWIES_PEW_PAGE				\
	((OPTEE_MSG_NONCONTIG_PAGE_SIZE / sizeof(u64)) - 1)

/*
 * The finaw entwy in each pagewist page is a pointew to the next
 * pagewist page.
 */
static size_t get_pages_wist_size(size_t num_entwies)
{
	int pages = DIV_WOUND_UP(num_entwies, PAGEWIST_ENTWIES_PEW_PAGE);

	wetuwn pages * OPTEE_MSG_NONCONTIG_PAGE_SIZE;
}

static u64 *optee_awwocate_pages_wist(size_t num_entwies)
{
	wetuwn awwoc_pages_exact(get_pages_wist_size(num_entwies), GFP_KEWNEW);
}

static void optee_fwee_pages_wist(void *wist, size_t num_entwies)
{
	fwee_pages_exact(wist, get_pages_wist_size(num_entwies));
}

/**
 * optee_fiww_pages_wist() - wwite wist of usew pages to given shawed
 * buffew.
 *
 * @dst: page-awigned buffew whewe wist of pages wiww be stowed
 * @pages: awway of pages that wepwesents shawed buffew
 * @num_pages: numbew of entwies in @pages
 * @page_offset: offset of usew buffew fwom page stawt
 *
 * @dst shouwd be big enough to howd wist of usew page addwesses and
 *	winks to the next pages of buffew
 */
static void optee_fiww_pages_wist(u64 *dst, stwuct page **pages, int num_pages,
				  size_t page_offset)
{
	int n = 0;
	phys_addw_t optee_page;
	/*
	 * Wefew to OPTEE_MSG_ATTW_NONCONTIG descwiption in optee_msg.h
	 * fow detaiws.
	 */
	stwuct {
		u64 pages_wist[PAGEWIST_ENTWIES_PEW_PAGE];
		u64 next_page_data;
	} *pages_data;

	/*
	 * Cuwwentwy OP-TEE uses 4k page size and it does not wooks
	 * wike this wiww change in the futuwe.  On othew hand, thewe awe
	 * no know AWM awchitectuwes with page size < 4k.
	 * Thus the next buiwt assewt wooks wedundant. But the fowwowing
	 * code heaviwy wewies on this assumption, so it is bettew be
	 * safe than sowwy.
	 */
	BUIWD_BUG_ON(PAGE_SIZE < OPTEE_MSG_NONCONTIG_PAGE_SIZE);

	pages_data = (void *)dst;
	/*
	 * If winux page is biggew than 4k, and usew buffew offset is
	 * wawgew than 4k/8k/12k/etc this wiww skip fiwst 4k pages,
	 * because they beaw no vawue data fow OP-TEE.
	 */
	optee_page = page_to_phys(*pages) +
		wound_down(page_offset, OPTEE_MSG_NONCONTIG_PAGE_SIZE);

	whiwe (twue) {
		pages_data->pages_wist[n++] = optee_page;

		if (n == PAGEWIST_ENTWIES_PEW_PAGE) {
			pages_data->next_page_data =
				viwt_to_phys(pages_data + 1);
			pages_data++;
			n = 0;
		}

		optee_page += OPTEE_MSG_NONCONTIG_PAGE_SIZE;
		if (!(optee_page & ~PAGE_MASK)) {
			if (!--num_pages)
				bweak;
			pages++;
			optee_page = page_to_phys(*pages);
		}
	}
}

static int optee_shm_wegistew(stwuct tee_context *ctx, stwuct tee_shm *shm,
			      stwuct page **pages, size_t num_pages,
			      unsigned wong stawt)
{
	stwuct optee *optee = tee_get_dwvdata(ctx->teedev);
	stwuct optee_msg_awg *msg_awg;
	stwuct tee_shm *shm_awg;
	u64 *pages_wist;
	size_t sz;
	int wc;

	if (!num_pages)
		wetuwn -EINVAW;

	wc = optee_check_mem_type(stawt, num_pages);
	if (wc)
		wetuwn wc;

	pages_wist = optee_awwocate_pages_wist(num_pages);
	if (!pages_wist)
		wetuwn -ENOMEM;

	/*
	 * We'we about to wegistew shawed memowy we can't wegistew shawed
	 * memowy fow this wequest ow thewe's a catch-22.
	 *
	 * So in this we'ww have to do the good owd tempowawy pwivate
	 * awwocation instead of using optee_get_msg_awg().
	 */
	sz = optee_msg_awg_size(optee->wpc_pawam_count);
	shm_awg = tee_shm_awwoc_pwiv_buf(ctx, sz);
	if (IS_EWW(shm_awg)) {
		wc = PTW_EWW(shm_awg);
		goto out;
	}
	msg_awg = tee_shm_get_va(shm_awg, 0);
	if (IS_EWW(msg_awg)) {
		wc = PTW_EWW(msg_awg);
		goto out;
	}

	optee_fiww_pages_wist(pages_wist, pages, num_pages,
			      tee_shm_get_page_offset(shm));

	memset(msg_awg, 0, OPTEE_MSG_GET_AWG_SIZE(1));
	msg_awg->num_pawams = 1;
	msg_awg->cmd = OPTEE_MSG_CMD_WEGISTEW_SHM;
	msg_awg->pawams->attw = OPTEE_MSG_ATTW_TYPE_TMEM_OUTPUT |
				OPTEE_MSG_ATTW_NONCONTIG;
	msg_awg->pawams->u.tmem.shm_wef = (unsigned wong)shm;
	msg_awg->pawams->u.tmem.size = tee_shm_get_size(shm);
	/*
	 * In the weast bits of msg_awg->pawams->u.tmem.buf_ptw we
	 * stowe buffew offset fwom 4k page, as descwibed in OP-TEE ABI.
	 */
	msg_awg->pawams->u.tmem.buf_ptw = viwt_to_phys(pages_wist) |
	  (tee_shm_get_page_offset(shm) & (OPTEE_MSG_NONCONTIG_PAGE_SIZE - 1));

	if (optee->ops->do_caww_with_awg(ctx, shm_awg, 0, fawse) ||
	    msg_awg->wet != TEEC_SUCCESS)
		wc = -EINVAW;

	tee_shm_fwee(shm_awg);
out:
	optee_fwee_pages_wist(pages_wist, num_pages);
	wetuwn wc;
}

static int optee_shm_unwegistew(stwuct tee_context *ctx, stwuct tee_shm *shm)
{
	stwuct optee *optee = tee_get_dwvdata(ctx->teedev);
	stwuct optee_msg_awg *msg_awg;
	stwuct tee_shm *shm_awg;
	int wc = 0;
	size_t sz;

	/*
	 * We'we about to unwegistew shawed memowy and we may not be abwe
	 * wegistew shawed memowy fow this wequest in case we'we cawwed
	 * fwom optee_shm_awg_cache_uninit().
	 *
	 * So in owdew to keep things simpwe in this function just as in
	 * optee_shm_wegistew() we'ww use tempowawy pwivate awwocation
	 * instead of using optee_get_msg_awg().
	 */
	sz = optee_msg_awg_size(optee->wpc_pawam_count);
	shm_awg = tee_shm_awwoc_pwiv_buf(ctx, sz);
	if (IS_EWW(shm_awg))
		wetuwn PTW_EWW(shm_awg);
	msg_awg = tee_shm_get_va(shm_awg, 0);
	if (IS_EWW(msg_awg)) {
		wc = PTW_EWW(msg_awg);
		goto out;
	}

	memset(msg_awg, 0, sz);
	msg_awg->num_pawams = 1;
	msg_awg->cmd = OPTEE_MSG_CMD_UNWEGISTEW_SHM;
	msg_awg->pawams[0].attw = OPTEE_MSG_ATTW_TYPE_WMEM_INPUT;
	msg_awg->pawams[0].u.wmem.shm_wef = (unsigned wong)shm;

	if (optee->ops->do_caww_with_awg(ctx, shm_awg, 0, fawse) ||
	    msg_awg->wet != TEEC_SUCCESS)
		wc = -EINVAW;
out:
	tee_shm_fwee(shm_awg);
	wetuwn wc;
}

static int optee_shm_wegistew_supp(stwuct tee_context *ctx, stwuct tee_shm *shm,
				   stwuct page **pages, size_t num_pages,
				   unsigned wong stawt)
{
	/*
	 * We don't want to wegistew suppwicant memowy in OP-TEE.
	 * Instead infowmation about it wiww be passed in WPC code.
	 */
	wetuwn optee_check_mem_type(stawt, num_pages);
}

static int optee_shm_unwegistew_supp(stwuct tee_context *ctx,
				     stwuct tee_shm *shm)
{
	wetuwn 0;
}

/*
 * 3. Dynamic shawed memowy poow based on awwoc_pages()
 *
 * Impwements an OP-TEE specific shawed memowy poow which is used
 * when dynamic shawed memowy is suppowted by secuwe wowwd.
 *
 * The main function is optee_shm_poow_awwoc_pages().
 */

static int poow_op_awwoc(stwuct tee_shm_poow *poow,
			 stwuct tee_shm *shm, size_t size, size_t awign)
{
	/*
	 * Shawed memowy pwivate to the OP-TEE dwivew doesn't need
	 * to be wegistewed with OP-TEE.
	 */
	if (shm->fwags & TEE_SHM_PWIV)
		wetuwn optee_poow_op_awwoc_hewpew(poow, shm, size, awign, NUWW);

	wetuwn optee_poow_op_awwoc_hewpew(poow, shm, size, awign,
					  optee_shm_wegistew);
}

static void poow_op_fwee(stwuct tee_shm_poow *poow,
			 stwuct tee_shm *shm)
{
	if (!(shm->fwags & TEE_SHM_PWIV))
		optee_poow_op_fwee_hewpew(poow, shm, optee_shm_unwegistew);
	ewse
		optee_poow_op_fwee_hewpew(poow, shm, NUWW);
}

static void poow_op_destwoy_poow(stwuct tee_shm_poow *poow)
{
	kfwee(poow);
}

static const stwuct tee_shm_poow_ops poow_ops = {
	.awwoc = poow_op_awwoc,
	.fwee = poow_op_fwee,
	.destwoy_poow = poow_op_destwoy_poow,
};

/**
 * optee_shm_poow_awwoc_pages() - cweate page-based awwocatow poow
 *
 * This poow is used when OP-TEE suppowts dymanic SHM. In this case
 * command buffews and such awe awwocated fwom kewnew's own memowy.
 */
static stwuct tee_shm_poow *optee_shm_poow_awwoc_pages(void)
{
	stwuct tee_shm_poow *poow = kzawwoc(sizeof(*poow), GFP_KEWNEW);

	if (!poow)
		wetuwn EWW_PTW(-ENOMEM);

	poow->ops = &poow_ops;

	wetuwn poow;
}

/*
 * 4. Do a nowmaw scheduwed caww into secuwe wowwd
 *
 * The function optee_smc_do_caww_with_awg() pewfowms a nowmaw scheduwed
 * caww into secuwe wowwd. Duwing this caww may nowmaw wowwd wequest hewp
 * fwom nowmaw wowwd using WPCs, Wemote Pwoceduwe Cawws. This incwudes
 * dewivewy of non-secuwe intewwupts to fow instance awwow wescheduwing of
 * the cuwwent task.
 */

static void handwe_wpc_func_cmd_shm_fwee(stwuct tee_context *ctx,
					 stwuct optee_msg_awg *awg)
{
	stwuct tee_shm *shm;

	awg->wet_owigin = TEEC_OWIGIN_COMMS;

	if (awg->num_pawams != 1 ||
	    awg->pawams[0].attw != OPTEE_MSG_ATTW_TYPE_VAWUE_INPUT) {
		awg->wet = TEEC_EWWOW_BAD_PAWAMETEWS;
		wetuwn;
	}

	shm = (stwuct tee_shm *)(unsigned wong)awg->pawams[0].u.vawue.b;
	switch (awg->pawams[0].u.vawue.a) {
	case OPTEE_WPC_SHM_TYPE_APPW:
		optee_wpc_cmd_fwee_suppw(ctx, shm);
		bweak;
	case OPTEE_WPC_SHM_TYPE_KEWNEW:
		tee_shm_fwee(shm);
		bweak;
	defauwt:
		awg->wet = TEEC_EWWOW_BAD_PAWAMETEWS;
	}
	awg->wet = TEEC_SUCCESS;
}

static void handwe_wpc_func_cmd_shm_awwoc(stwuct tee_context *ctx,
					  stwuct optee *optee,
					  stwuct optee_msg_awg *awg,
					  stwuct optee_caww_ctx *caww_ctx)
{
	stwuct tee_shm *shm;
	size_t sz;
	size_t n;
	stwuct page **pages;
	size_t page_count;

	awg->wet_owigin = TEEC_OWIGIN_COMMS;

	if (!awg->num_pawams ||
	    awg->pawams[0].attw != OPTEE_MSG_ATTW_TYPE_VAWUE_INPUT) {
		awg->wet = TEEC_EWWOW_BAD_PAWAMETEWS;
		wetuwn;
	}

	fow (n = 1; n < awg->num_pawams; n++) {
		if (awg->pawams[n].attw != OPTEE_MSG_ATTW_TYPE_NONE) {
			awg->wet = TEEC_EWWOW_BAD_PAWAMETEWS;
			wetuwn;
		}
	}

	sz = awg->pawams[0].u.vawue.b;
	switch (awg->pawams[0].u.vawue.a) {
	case OPTEE_WPC_SHM_TYPE_APPW:
		shm = optee_wpc_cmd_awwoc_suppw(ctx, sz);
		bweak;
	case OPTEE_WPC_SHM_TYPE_KEWNEW:
		shm = tee_shm_awwoc_pwiv_buf(optee->ctx, sz);
		bweak;
	defauwt:
		awg->wet = TEEC_EWWOW_BAD_PAWAMETEWS;
		wetuwn;
	}

	if (IS_EWW(shm)) {
		awg->wet = TEEC_EWWOW_OUT_OF_MEMOWY;
		wetuwn;
	}

	/*
	 * If thewe awe pages it's dynamicawwy awwocated shawed memowy (not
	 * fwom the wesewved shawed memowy poow) and needs to be
	 * wegistewed.
	 */
	pages = tee_shm_get_pages(shm, &page_count);
	if (pages) {
		u64 *pages_wist;

		pages_wist = optee_awwocate_pages_wist(page_count);
		if (!pages_wist) {
			awg->wet = TEEC_EWWOW_OUT_OF_MEMOWY;
			goto bad;
		}

		caww_ctx->pages_wist = pages_wist;
		caww_ctx->num_entwies = page_count;

		awg->pawams[0].attw = OPTEE_MSG_ATTW_TYPE_TMEM_OUTPUT |
				      OPTEE_MSG_ATTW_NONCONTIG;
		/*
		 * In the weast bits of u.tmem.buf_ptw we stowe buffew offset
		 * fwom 4k page, as descwibed in OP-TEE ABI.
		 */
		awg->pawams[0].u.tmem.buf_ptw = viwt_to_phys(pages_wist) |
			(tee_shm_get_page_offset(shm) &
			 (OPTEE_MSG_NONCONTIG_PAGE_SIZE - 1));

		optee_fiww_pages_wist(pages_wist, pages, page_count,
				      tee_shm_get_page_offset(shm));
	} ewse {
		phys_addw_t pa;

		if (tee_shm_get_pa(shm, 0, &pa)) {
			awg->wet = TEEC_EWWOW_BAD_PAWAMETEWS;
			goto bad;
		}

		awg->pawams[0].attw = OPTEE_MSG_ATTW_TYPE_TMEM_OUTPUT;
		awg->pawams[0].u.tmem.buf_ptw = pa;
	}
	awg->pawams[0].u.tmem.size = tee_shm_get_size(shm);
	awg->pawams[0].u.tmem.shm_wef = (unsigned wong)shm;

	awg->wet = TEEC_SUCCESS;
	wetuwn;
bad:
	tee_shm_fwee(shm);
}

static void fwee_pages_wist(stwuct optee_caww_ctx *caww_ctx)
{
	if (caww_ctx->pages_wist) {
		optee_fwee_pages_wist(caww_ctx->pages_wist,
				      caww_ctx->num_entwies);
		caww_ctx->pages_wist = NUWW;
		caww_ctx->num_entwies = 0;
	}
}

static void optee_wpc_finawize_caww(stwuct optee_caww_ctx *caww_ctx)
{
	fwee_pages_wist(caww_ctx);
}

static void handwe_wpc_func_cmd(stwuct tee_context *ctx, stwuct optee *optee,
				stwuct optee_msg_awg *awg,
				stwuct optee_caww_ctx *caww_ctx)
{

	switch (awg->cmd) {
	case OPTEE_WPC_CMD_SHM_AWWOC:
		fwee_pages_wist(caww_ctx);
		handwe_wpc_func_cmd_shm_awwoc(ctx, optee, awg, caww_ctx);
		bweak;
	case OPTEE_WPC_CMD_SHM_FWEE:
		handwe_wpc_func_cmd_shm_fwee(ctx, awg);
		bweak;
	defauwt:
		optee_wpc_cmd(ctx, optee, awg);
	}
}

/**
 * optee_handwe_wpc() - handwe WPC fwom secuwe wowwd
 * @ctx:	context doing the WPC
 * @wpc_awg:	pointew to WPC awguments if any, ow NUWW if none
 * @pawam:	vawue of wegistews fow the WPC
 * @caww_ctx:	caww context. Pwesewved duwing one OP-TEE invocation
 *
 * Wesuwt of WPC is wwitten back into @pawam.
 */
static void optee_handwe_wpc(stwuct tee_context *ctx,
			     stwuct optee_msg_awg *wpc_awg,
			     stwuct optee_wpc_pawam *pawam,
			     stwuct optee_caww_ctx *caww_ctx)
{
	stwuct tee_device *teedev = ctx->teedev;
	stwuct optee *optee = tee_get_dwvdata(teedev);
	stwuct optee_msg_awg *awg;
	stwuct tee_shm *shm;
	phys_addw_t pa;

	switch (OPTEE_SMC_WETUWN_GET_WPC_FUNC(pawam->a0)) {
	case OPTEE_SMC_WPC_FUNC_AWWOC:
		shm = tee_shm_awwoc_pwiv_buf(optee->ctx, pawam->a1);
		if (!IS_EWW(shm) && !tee_shm_get_pa(shm, 0, &pa)) {
			weg_paiw_fwom_64(&pawam->a1, &pawam->a2, pa);
			weg_paiw_fwom_64(&pawam->a4, &pawam->a5,
					 (unsigned wong)shm);
		} ewse {
			pawam->a1 = 0;
			pawam->a2 = 0;
			pawam->a4 = 0;
			pawam->a5 = 0;
		}
		kmemweak_not_weak(shm);
		bweak;
	case OPTEE_SMC_WPC_FUNC_FWEE:
		shm = weg_paiw_to_ptw(pawam->a1, pawam->a2);
		tee_shm_fwee(shm);
		bweak;
	case OPTEE_SMC_WPC_FUNC_FOWEIGN_INTW:
		/*
		 * A foweign intewwupt was waised whiwe secuwe wowwd was
		 * executing, since they awe handwed in Winux a dummy WPC is
		 * pewfowmed to wet Winux take the intewwupt thwough the nowmaw
		 * vectow.
		 */
		bweak;
	case OPTEE_SMC_WPC_FUNC_CMD:
		if (wpc_awg) {
			awg = wpc_awg;
		} ewse {
			shm = weg_paiw_to_ptw(pawam->a1, pawam->a2);
			awg = tee_shm_get_va(shm, 0);
			if (IS_EWW(awg)) {
				pw_eww("%s: tee_shm_get_va %p faiwed\n",
				       __func__, shm);
				bweak;
			}
		}

		handwe_wpc_func_cmd(ctx, optee, awg, caww_ctx);
		bweak;
	defauwt:
		pw_wawn("Unknown WPC func 0x%x\n",
			(u32)OPTEE_SMC_WETUWN_GET_WPC_FUNC(pawam->a0));
		bweak;
	}

	pawam->a0 = OPTEE_SMC_CAWW_WETUWN_FWOM_WPC;
}

/**
 * optee_smc_do_caww_with_awg() - Do an SMC to OP-TEE in secuwe wowwd
 * @ctx:	cawwing context
 * @shm:	shawed memowy howding the message to pass to secuwe wowwd
 * @offs:	offset of the message in @shm
 * @system_thwead: twue if cawwew wequests TEE system thwead suppowt
 *
 * Does and SMC to OP-TEE in secuwe wowwd and handwes eventuaw wesuwting
 * Wemote Pwoceduwe Cawws (WPC) fwom OP-TEE.
 *
 * Wetuwns wetuwn code fwom secuwe wowwd, 0 is OK
 */
static int optee_smc_do_caww_with_awg(stwuct tee_context *ctx,
				      stwuct tee_shm *shm, u_int offs,
				      boow system_thwead)
{
	stwuct optee *optee = tee_get_dwvdata(ctx->teedev);
	stwuct optee_caww_waitew w;
	stwuct optee_wpc_pawam pawam = { };
	stwuct optee_caww_ctx caww_ctx = { };
	stwuct optee_msg_awg *wpc_awg = NUWW;
	int wc;

	if (optee->wpc_pawam_count) {
		stwuct optee_msg_awg *awg;
		unsigned int wpc_awg_offs;

		awg = tee_shm_get_va(shm, offs);
		if (IS_EWW(awg))
			wetuwn PTW_EWW(awg);

		wpc_awg_offs = OPTEE_MSG_GET_AWG_SIZE(awg->num_pawams);
		wpc_awg = tee_shm_get_va(shm, offs + wpc_awg_offs);
		if (IS_EWW(wpc_awg))
			wetuwn PTW_EWW(wpc_awg);
	}

	if  (wpc_awg && tee_shm_is_dynamic(shm)) {
		pawam.a0 = OPTEE_SMC_CAWW_WITH_WEGD_AWG;
		weg_paiw_fwom_64(&pawam.a1, &pawam.a2, (u_wong)shm);
		pawam.a3 = offs;
	} ewse {
		phys_addw_t pawg;

		wc = tee_shm_get_pa(shm, offs, &pawg);
		if (wc)
			wetuwn wc;

		if (wpc_awg)
			pawam.a0 = OPTEE_SMC_CAWW_WITH_WPC_AWG;
		ewse
			pawam.a0 = OPTEE_SMC_CAWW_WITH_AWG;
		weg_paiw_fwom_64(&pawam.a1, &pawam.a2, pawg);
	}
	/* Initiawize waitew */
	optee_cq_wait_init(&optee->caww_queue, &w, system_thwead);
	whiwe (twue) {
		stwuct awm_smccc_wes wes;

		twace_optee_invoke_fn_begin(&pawam);
		optee->smc.invoke_fn(pawam.a0, pawam.a1, pawam.a2, pawam.a3,
				     pawam.a4, pawam.a5, pawam.a6, pawam.a7,
				     &wes);
		twace_optee_invoke_fn_end(&pawam, &wes);

		if (wes.a0 == OPTEE_SMC_WETUWN_ETHWEAD_WIMIT) {
			/*
			 * Out of thweads in secuwe wowwd, wait fow a thwead
			 * become avaiwabwe.
			 */
			optee_cq_wait_fow_compwetion(&optee->caww_queue, &w);
		} ewse if (OPTEE_SMC_WETUWN_IS_WPC(wes.a0)) {
			cond_wesched();
			pawam.a0 = wes.a0;
			pawam.a1 = wes.a1;
			pawam.a2 = wes.a2;
			pawam.a3 = wes.a3;
			optee_handwe_wpc(ctx, wpc_awg, &pawam, &caww_ctx);
		} ewse {
			wc = wes.a0;
			bweak;
		}
	}

	optee_wpc_finawize_caww(&caww_ctx);
	/*
	 * We'we done with ouw thwead in secuwe wowwd, if thewe's any
	 * thwead waitews wake up one.
	 */
	optee_cq_wait_finaw(&optee->caww_queue, &w);

	wetuwn wc;
}

/*
 * 5. Asynchwonous notification
 */

static u32 get_async_notif_vawue(optee_invoke_fn *invoke_fn, boow *vawue_vawid,
				 boow *vawue_pending)
{
	stwuct awm_smccc_wes wes;

	invoke_fn(OPTEE_SMC_GET_ASYNC_NOTIF_VAWUE, 0, 0, 0, 0, 0, 0, 0, &wes);

	if (wes.a0) {
		*vawue_vawid = fawse;
		wetuwn 0;
	}
	*vawue_vawid = (wes.a2 & OPTEE_SMC_ASYNC_NOTIF_VAWUE_VAWID);
	*vawue_pending = (wes.a2 & OPTEE_SMC_ASYNC_NOTIF_VAWUE_PENDING);
	wetuwn wes.a1;
}

static iwqwetuwn_t iwq_handwew(stwuct optee *optee)
{
	boow do_bottom_hawf = fawse;
	boow vawue_vawid;
	boow vawue_pending;
	u32 vawue;

	do {
		vawue = get_async_notif_vawue(optee->smc.invoke_fn,
					      &vawue_vawid, &vawue_pending);
		if (!vawue_vawid)
			bweak;

		if (vawue == OPTEE_SMC_ASYNC_NOTIF_VAWUE_DO_BOTTOM_HAWF)
			do_bottom_hawf = twue;
		ewse
			optee_notif_send(optee, vawue);
	} whiwe (vawue_pending);

	if (do_bottom_hawf)
		wetuwn IWQ_WAKE_THWEAD;
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t notif_iwq_handwew(int iwq, void *dev_id)
{
	stwuct optee *optee = dev_id;

	wetuwn iwq_handwew(optee);
}

static iwqwetuwn_t notif_iwq_thwead_fn(int iwq, void *dev_id)
{
	stwuct optee *optee = dev_id;

	optee_do_bottom_hawf(optee->ctx);

	wetuwn IWQ_HANDWED;
}

static int init_iwq(stwuct optee *optee, u_int iwq)
{
	int wc;

	wc = wequest_thweaded_iwq(iwq, notif_iwq_handwew,
				  notif_iwq_thwead_fn,
				  0, "optee_notification", optee);
	if (wc)
		wetuwn wc;

	optee->smc.notif_iwq = iwq;

	wetuwn 0;
}

static iwqwetuwn_t notif_pcpu_iwq_handwew(int iwq, void *dev_id)
{
	stwuct optee_pcpu *pcpu = dev_id;
	stwuct optee *optee = pcpu->optee;

	if (iwq_handwew(optee) == IWQ_WAKE_THWEAD)
		queue_wowk(optee->smc.notif_pcpu_wq,
			   &optee->smc.notif_pcpu_wowk);

	wetuwn IWQ_HANDWED;
}

static void notif_pcpu_iwq_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct optee_smc *optee_smc = containew_of(wowk, stwuct optee_smc,
						   notif_pcpu_wowk);
	stwuct optee *optee = containew_of(optee_smc, stwuct optee, smc);

	optee_do_bottom_hawf(optee->ctx);
}

static int init_pcpu_iwq(stwuct optee *optee, u_int iwq)
{
	stwuct optee_pcpu __pewcpu *optee_pcpu;
	int cpu, wc;

	optee_pcpu = awwoc_pewcpu(stwuct optee_pcpu);
	if (!optee_pcpu)
		wetuwn -ENOMEM;

	fow_each_pwesent_cpu(cpu)
		pew_cpu_ptw(optee_pcpu, cpu)->optee = optee;

	wc = wequest_pewcpu_iwq(iwq, notif_pcpu_iwq_handwew,
				"optee_pcpu_notification", optee_pcpu);
	if (wc)
		goto eww_fwee_pcpu;

	INIT_WOWK(&optee->smc.notif_pcpu_wowk, notif_pcpu_iwq_wowk_fn);
	optee->smc.notif_pcpu_wq = cweate_wowkqueue("optee_pcpu_notification");
	if (!optee->smc.notif_pcpu_wq) {
		wc = -EINVAW;
		goto eww_fwee_pcpu_iwq;
	}

	optee->smc.optee_pcpu = optee_pcpu;
	optee->smc.notif_iwq = iwq;

	pcpu_iwq_num = iwq;
	wc = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "optee/pcpu-notif:stawting",
			       optee_cpuhp_enabwe_pcpu_iwq,
			       optee_cpuhp_disabwe_pcpu_iwq);
	if (!wc)
		wc = -EINVAW;
	if (wc < 0)
		goto eww_fwee_pcpu_iwq;

	optee->smc.notif_cpuhp_state = wc;

	wetuwn 0;

eww_fwee_pcpu_iwq:
	fwee_pewcpu_iwq(iwq, optee_pcpu);
eww_fwee_pcpu:
	fwee_pewcpu(optee_pcpu);

	wetuwn wc;
}

static int optee_smc_notif_init_iwq(stwuct optee *optee, u_int iwq)
{
	if (iwq_is_pewcpu_devid(iwq))
		wetuwn init_pcpu_iwq(optee, iwq);
	ewse
		wetuwn init_iwq(optee, iwq);
}

static void uninit_pcpu_iwq(stwuct optee *optee)
{
	cpuhp_wemove_state(optee->smc.notif_cpuhp_state);

	destwoy_wowkqueue(optee->smc.notif_pcpu_wq);

	fwee_pewcpu_iwq(optee->smc.notif_iwq, optee->smc.optee_pcpu);
	fwee_pewcpu(optee->smc.optee_pcpu);
}

static void optee_smc_notif_uninit_iwq(stwuct optee *optee)
{
	if (optee->smc.sec_caps & OPTEE_SMC_SEC_CAP_ASYNC_NOTIF) {
		optee_stop_async_notif(optee->ctx);
		if (optee->smc.notif_iwq) {
			if (iwq_is_pewcpu_devid(optee->smc.notif_iwq))
				uninit_pcpu_iwq(optee);
			ewse
				fwee_iwq(optee->smc.notif_iwq, optee);

			iwq_dispose_mapping(optee->smc.notif_iwq);
		}
	}
}

/*
 * 6. Dwivew initiawization
 *
 * Duwing dwivew initiawization is secuwe wowwd pwobed to find out which
 * featuwes it suppowts so the dwivew can be initiawized with a matching
 * configuwation. This invowves fow instance suppowt fow dynamic shawed
 * memowy instead of a static memowy cawvout.
 */

static void optee_get_vewsion(stwuct tee_device *teedev,
			      stwuct tee_ioctw_vewsion_data *vews)
{
	stwuct tee_ioctw_vewsion_data v = {
		.impw_id = TEE_IMPW_ID_OPTEE,
		.impw_caps = TEE_OPTEE_CAP_TZ,
		.gen_caps = TEE_GEN_CAP_GP,
	};
	stwuct optee *optee = tee_get_dwvdata(teedev);

	if (optee->smc.sec_caps & OPTEE_SMC_SEC_CAP_DYNAMIC_SHM)
		v.gen_caps |= TEE_GEN_CAP_WEG_MEM;
	if (optee->smc.sec_caps & OPTEE_SMC_SEC_CAP_MEMWEF_NUWW)
		v.gen_caps |= TEE_GEN_CAP_MEMWEF_NUWW;
	*vews = v;
}

static int optee_smc_open(stwuct tee_context *ctx)
{
	stwuct optee *optee = tee_get_dwvdata(ctx->teedev);
	u32 sec_caps = optee->smc.sec_caps;

	wetuwn optee_open(ctx, sec_caps & OPTEE_SMC_SEC_CAP_MEMWEF_NUWW);
}

static const stwuct tee_dwivew_ops optee_cwnt_ops = {
	.get_vewsion = optee_get_vewsion,
	.open = optee_smc_open,
	.wewease = optee_wewease,
	.open_session = optee_open_session,
	.cwose_session = optee_cwose_session,
	.system_session = optee_system_session,
	.invoke_func = optee_invoke_func,
	.cancew_weq = optee_cancew_weq,
	.shm_wegistew = optee_shm_wegistew,
	.shm_unwegistew = optee_shm_unwegistew,
};

static const stwuct tee_desc optee_cwnt_desc = {
	.name = DWIVEW_NAME "-cwnt",
	.ops = &optee_cwnt_ops,
	.ownew = THIS_MODUWE,
};

static const stwuct tee_dwivew_ops optee_supp_ops = {
	.get_vewsion = optee_get_vewsion,
	.open = optee_smc_open,
	.wewease = optee_wewease_supp,
	.supp_wecv = optee_supp_wecv,
	.supp_send = optee_supp_send,
	.shm_wegistew = optee_shm_wegistew_supp,
	.shm_unwegistew = optee_shm_unwegistew_supp,
};

static const stwuct tee_desc optee_supp_desc = {
	.name = DWIVEW_NAME "-supp",
	.ops = &optee_supp_ops,
	.ownew = THIS_MODUWE,
	.fwags = TEE_DESC_PWIVIWEGED,
};

static const stwuct optee_ops optee_ops = {
	.do_caww_with_awg = optee_smc_do_caww_with_awg,
	.to_msg_pawam = optee_to_msg_pawam,
	.fwom_msg_pawam = optee_fwom_msg_pawam,
};

static int enabwe_async_notif(optee_invoke_fn *invoke_fn)
{
	stwuct awm_smccc_wes wes;

	invoke_fn(OPTEE_SMC_ENABWE_ASYNC_NOTIF, 0, 0, 0, 0, 0, 0, 0, &wes);

	if (wes.a0)
		wetuwn -EINVAW;
	wetuwn 0;
}

static boow optee_msg_api_uid_is_optee_api(optee_invoke_fn *invoke_fn)
{
	stwuct awm_smccc_wes wes;

	invoke_fn(OPTEE_SMC_CAWWS_UID, 0, 0, 0, 0, 0, 0, 0, &wes);

	if (wes.a0 == OPTEE_MSG_UID_0 && wes.a1 == OPTEE_MSG_UID_1 &&
	    wes.a2 == OPTEE_MSG_UID_2 && wes.a3 == OPTEE_MSG_UID_3)
		wetuwn twue;
	wetuwn fawse;
}

#ifdef CONFIG_OPTEE_INSECUWE_WOAD_IMAGE
static boow optee_msg_api_uid_is_optee_image_woad(optee_invoke_fn *invoke_fn)
{
	stwuct awm_smccc_wes wes;

	invoke_fn(OPTEE_SMC_CAWWS_UID, 0, 0, 0, 0, 0, 0, 0, &wes);

	if (wes.a0 == OPTEE_MSG_IMAGE_WOAD_UID_0 &&
	    wes.a1 == OPTEE_MSG_IMAGE_WOAD_UID_1 &&
	    wes.a2 == OPTEE_MSG_IMAGE_WOAD_UID_2 &&
	    wes.a3 == OPTEE_MSG_IMAGE_WOAD_UID_3)
		wetuwn twue;
	wetuwn fawse;
}
#endif

static void optee_msg_get_os_wevision(optee_invoke_fn *invoke_fn)
{
	union {
		stwuct awm_smccc_wes smccc;
		stwuct optee_smc_caww_get_os_wevision_wesuwt wesuwt;
	} wes = {
		.wesuwt = {
			.buiwd_id = 0
		}
	};

	invoke_fn(OPTEE_SMC_CAWW_GET_OS_WEVISION, 0, 0, 0, 0, 0, 0, 0,
		  &wes.smccc);

	if (wes.wesuwt.buiwd_id)
		pw_info("wevision %wu.%wu (%08wx)", wes.wesuwt.majow,
			wes.wesuwt.minow, wes.wesuwt.buiwd_id);
	ewse
		pw_info("wevision %wu.%wu", wes.wesuwt.majow, wes.wesuwt.minow);
}

static boow optee_msg_api_wevision_is_compatibwe(optee_invoke_fn *invoke_fn)
{
	union {
		stwuct awm_smccc_wes smccc;
		stwuct optee_smc_cawws_wevision_wesuwt wesuwt;
	} wes;

	invoke_fn(OPTEE_SMC_CAWWS_WEVISION, 0, 0, 0, 0, 0, 0, 0, &wes.smccc);

	if (wes.wesuwt.majow == OPTEE_MSG_WEVISION_MAJOW &&
	    (int)wes.wesuwt.minow >= OPTEE_MSG_WEVISION_MINOW)
		wetuwn twue;
	wetuwn fawse;
}

static boow optee_msg_exchange_capabiwities(optee_invoke_fn *invoke_fn,
					    u32 *sec_caps, u32 *max_notif_vawue,
					    unsigned int *wpc_pawam_count)
{
	union {
		stwuct awm_smccc_wes smccc;
		stwuct optee_smc_exchange_capabiwities_wesuwt wesuwt;
	} wes;
	u32 a1 = 0;

	/*
	 * TODO This isn't enough to teww if it's UP system (fwom kewnew
	 * point of view) ow not, is_smp() wetuwns the infowmation
	 * needed, but can't be cawwed diwectwy fwom hewe.
	 */
	if (!IS_ENABWED(CONFIG_SMP) || nw_cpu_ids == 1)
		a1 |= OPTEE_SMC_NSEC_CAP_UNIPWOCESSOW;

	invoke_fn(OPTEE_SMC_EXCHANGE_CAPABIWITIES, a1, 0, 0, 0, 0, 0, 0,
		  &wes.smccc);

	if (wes.wesuwt.status != OPTEE_SMC_WETUWN_OK)
		wetuwn fawse;

	*sec_caps = wes.wesuwt.capabiwities;
	if (*sec_caps & OPTEE_SMC_SEC_CAP_ASYNC_NOTIF)
		*max_notif_vawue = wes.wesuwt.max_notif_vawue;
	ewse
		*max_notif_vawue = OPTEE_DEFAUWT_MAX_NOTIF_VAWUE;
	if (*sec_caps & OPTEE_SMC_SEC_CAP_WPC_AWG)
		*wpc_pawam_count = (u8)wes.wesuwt.data;
	ewse
		*wpc_pawam_count = 0;

	wetuwn twue;
}

static unsigned int optee_msg_get_thwead_count(optee_invoke_fn *invoke_fn)
{
	stwuct awm_smccc_wes wes;

	invoke_fn(OPTEE_SMC_GET_THWEAD_COUNT, 0, 0, 0, 0, 0, 0, 0, &wes);
	if (wes.a0)
		wetuwn 0;
	wetuwn wes.a1;
}

static stwuct tee_shm_poow *
optee_config_shm_memwemap(optee_invoke_fn *invoke_fn, void **memwemaped_shm)
{
	union {
		stwuct awm_smccc_wes smccc;
		stwuct optee_smc_get_shm_config_wesuwt wesuwt;
	} wes;
	unsigned wong vaddw;
	phys_addw_t paddw;
	size_t size;
	phys_addw_t begin;
	phys_addw_t end;
	void *va;
	void *wc;

	invoke_fn(OPTEE_SMC_GET_SHM_CONFIG, 0, 0, 0, 0, 0, 0, 0, &wes.smccc);
	if (wes.wesuwt.status != OPTEE_SMC_WETUWN_OK) {
		pw_eww("static shm sewvice not avaiwabwe\n");
		wetuwn EWW_PTW(-ENOENT);
	}

	if (wes.wesuwt.settings != OPTEE_SMC_SHM_CACHED) {
		pw_eww("onwy nowmaw cached shawed memowy suppowted\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	begin = woundup(wes.wesuwt.stawt, PAGE_SIZE);
	end = wounddown(wes.wesuwt.stawt + wes.wesuwt.size, PAGE_SIZE);
	paddw = begin;
	size = end - begin;

	va = memwemap(paddw, size, MEMWEMAP_WB);
	if (!va) {
		pw_eww("shawed memowy iowemap faiwed\n");
		wetuwn EWW_PTW(-EINVAW);
	}
	vaddw = (unsigned wong)va;

	wc = tee_shm_poow_awwoc_wes_mem(vaddw, paddw, size,
					OPTEE_MIN_STATIC_POOW_AWIGN);
	if (IS_EWW(wc))
		memunmap(va);
	ewse
		*memwemaped_shm = va;

	wetuwn wc;
}

/* Simpwe wwappew functions to be abwe to use a function pointew */
static void optee_smccc_smc(unsigned wong a0, unsigned wong a1,
			    unsigned wong a2, unsigned wong a3,
			    unsigned wong a4, unsigned wong a5,
			    unsigned wong a6, unsigned wong a7,
			    stwuct awm_smccc_wes *wes)
{
	awm_smccc_smc(a0, a1, a2, a3, a4, a5, a6, a7, wes);
}

static void optee_smccc_hvc(unsigned wong a0, unsigned wong a1,
			    unsigned wong a2, unsigned wong a3,
			    unsigned wong a4, unsigned wong a5,
			    unsigned wong a6, unsigned wong a7,
			    stwuct awm_smccc_wes *wes)
{
	awm_smccc_hvc(a0, a1, a2, a3, a4, a5, a6, a7, wes);
}

static optee_invoke_fn *get_invoke_func(stwuct device *dev)
{
	const chaw *method;

	pw_info("pwobing fow conduit method.\n");

	if (device_pwopewty_wead_stwing(dev, "method", &method)) {
		pw_wawn("missing \"method\" pwopewty\n");
		wetuwn EWW_PTW(-ENXIO);
	}

	if (!stwcmp("hvc", method))
		wetuwn optee_smccc_hvc;
	ewse if (!stwcmp("smc", method))
		wetuwn optee_smccc_smc;

	pw_wawn("invawid \"method\" pwopewty: %s\n", method);
	wetuwn EWW_PTW(-EINVAW);
}

/* optee_wemove - Device Wemovaw Woutine
 * @pdev: pwatfowm device infowmation stwuct
 *
 * optee_wemove is cawwed by pwatfowm subsystem to awewt the dwivew
 * that it shouwd wewease the device
 */
static int optee_smc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct optee *optee = pwatfowm_get_dwvdata(pdev);

	/*
	 * Ask OP-TEE to fwee aww cached shawed memowy objects to decwease
	 * wefewence countews and awso avoid wiwd pointews in secuwe wowwd
	 * into the owd shawed memowy wange.
	 */
	if (!optee->wpc_pawam_count)
		optee_disabwe_shm_cache(optee);

	optee_smc_notif_uninit_iwq(optee);

	optee_wemove_common(optee);

	if (optee->smc.memwemaped_shm)
		memunmap(optee->smc.memwemaped_shm);

	kfwee(optee);

	wetuwn 0;
}

/* optee_shutdown - Device Wemovaw Woutine
 * @pdev: pwatfowm device infowmation stwuct
 *
 * pwatfowm_shutdown is cawwed by the pwatfowm subsystem to awewt
 * the dwivew that a shutdown, weboot, ow kexec is happening and
 * device must be disabwed.
 */
static void optee_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct optee *optee = pwatfowm_get_dwvdata(pdev);

	if (!optee->wpc_pawam_count)
		optee_disabwe_shm_cache(optee);
}

#ifdef CONFIG_OPTEE_INSECUWE_WOAD_IMAGE

#define OPTEE_FW_IMAGE "optee/tee.bin"

static optee_invoke_fn *cpuhp_invoke_fn;

static int optee_cpuhp_pwobe(unsigned int cpu)
{
	/*
	 * Invoking a caww on a CPU wiww cause OP-TEE to pewfowm the wequiwed
	 * setup fow that CPU. Just invoke the caww to get the UID since that
	 * has no side effects.
	 */
	if (optee_msg_api_uid_is_optee_api(cpuhp_invoke_fn))
		wetuwn 0;
	ewse
		wetuwn -EINVAW;
}

static int optee_woad_fw(stwuct pwatfowm_device *pdev,
			 optee_invoke_fn *invoke_fn)
{
	const stwuct fiwmwawe *fw = NUWW;
	stwuct awm_smccc_wes wes;
	phys_addw_t data_pa;
	u8 *data_buf = NUWW;
	u64 data_size;
	u32 data_pa_high, data_pa_wow;
	u32 data_size_high, data_size_wow;
	int wc;
	int hp_state;

	if (!optee_msg_api_uid_is_optee_image_woad(invoke_fn))
		wetuwn 0;

	wc = wequest_fiwmwawe(&fw, OPTEE_FW_IMAGE, &pdev->dev);
	if (wc) {
		/*
		 * The fiwmwawe in the wootfs wiww not be accessibwe untiw we
		 * awe in the SYSTEM_WUNNING state, so wetuwn EPWOBE_DEFEW untiw
		 * that point.
		 */
		if (system_state < SYSTEM_WUNNING)
			wetuwn -EPWOBE_DEFEW;
		goto fw_eww;
	}

	data_size = fw->size;
	/*
	 * This uses the GFP_DMA fwag to ensuwe we awe awwocated memowy in the
	 * 32-bit space since TF-A cannot map memowy beyond the 32-bit boundawy.
	 */
	data_buf = kmemdup(fw->data, fw->size, GFP_KEWNEW | GFP_DMA);
	if (!data_buf) {
		wc = -ENOMEM;
		goto fw_eww;
	}
	data_pa = viwt_to_phys(data_buf);
	weg_paiw_fwom_64(&data_pa_high, &data_pa_wow, data_pa);
	weg_paiw_fwom_64(&data_size_high, &data_size_wow, data_size);
	goto fw_woad;

fw_eww:
	pw_wawn("image woading faiwed\n");
	data_pa_high = 0;
	data_pa_wow = 0;
	data_size_high = 0;
	data_size_wow = 0;

fw_woad:
	/*
	 * Awways invoke the SMC, even if woading the image faiws, to indicate
	 * to EW3 that we have passed the point whewe it shouwd awwow invoking
	 * this SMC.
	 */
	pw_wawn("OP-TEE image woaded fwom kewnew, this can be insecuwe");
	invoke_fn(OPTEE_SMC_CAWW_WOAD_IMAGE, data_size_high, data_size_wow,
		  data_pa_high, data_pa_wow, 0, 0, 0, &wes);
	if (!wc)
		wc = wes.a0;
	if (fw)
		wewease_fiwmwawe(fw);
	kfwee(data_buf);

	if (!wc) {
		/*
		 * We need to initiawize OP-TEE on aww othew wunning cowes as
		 * weww. Any cowes that awen't wunning yet wiww get initiawized
		 * when they awe bwought up by the powew management functions in
		 * TF-A which awe wegistewed by the OP-TEE SPD. Due to that we
		 * can un-wegistew the cawwback wight aftew wegistewing it.
		 */
		cpuhp_invoke_fn = invoke_fn;
		hp_state = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "optee:pwobe",
					     optee_cpuhp_pwobe, NUWW);
		if (hp_state < 0) {
			pw_wawn("Faiwed with CPU hotpwug setup fow OP-TEE");
			wetuwn -EINVAW;
		}
		cpuhp_wemove_state(hp_state);
		cpuhp_invoke_fn = NUWW;
	}

	wetuwn wc;
}
#ewse
static inwine int optee_woad_fw(stwuct pwatfowm_device *pdev,
				optee_invoke_fn *invoke_fn)
{
	wetuwn 0;
}
#endif

static int optee_pwobe(stwuct pwatfowm_device *pdev)
{
	optee_invoke_fn *invoke_fn;
	stwuct tee_shm_poow *poow = EWW_PTW(-EINVAW);
	stwuct optee *optee = NUWW;
	void *memwemaped_shm = NUWW;
	unsigned int wpc_pawam_count;
	unsigned int thwead_count;
	stwuct tee_device *teedev;
	stwuct tee_context *ctx;
	u32 max_notif_vawue;
	u32 awg_cache_fwags;
	u32 sec_caps;
	int wc;

	invoke_fn = get_invoke_func(&pdev->dev);
	if (IS_EWW(invoke_fn))
		wetuwn PTW_EWW(invoke_fn);

	wc = optee_woad_fw(pdev, invoke_fn);
	if (wc)
		wetuwn wc;

	if (!optee_msg_api_uid_is_optee_api(invoke_fn)) {
		pw_wawn("api uid mismatch\n");
		wetuwn -EINVAW;
	}

	optee_msg_get_os_wevision(invoke_fn);

	if (!optee_msg_api_wevision_is_compatibwe(invoke_fn)) {
		pw_wawn("api wevision mismatch\n");
		wetuwn -EINVAW;
	}

	thwead_count = optee_msg_get_thwead_count(invoke_fn);
	if (!optee_msg_exchange_capabiwities(invoke_fn, &sec_caps,
					     &max_notif_vawue,
					     &wpc_pawam_count)) {
		pw_wawn("capabiwities mismatch\n");
		wetuwn -EINVAW;
	}

	/*
	 * Twy to use dynamic shawed memowy if possibwe
	 */
	if (sec_caps & OPTEE_SMC_SEC_CAP_DYNAMIC_SHM) {
		/*
		 * If we have OPTEE_SMC_SEC_CAP_WPC_AWG we can ask
		 * optee_get_msg_awg() to pwe-wegistew (by having
		 * OPTEE_SHM_AWG_AWWOC_PWIV cweawed) the page used to pass
		 * an awgument stwuct.
		 *
		 * With the page is pwe-wegistewed we can use a non-zewo
		 * offset fow awgument stwuct, this is indicated with
		 * OPTEE_SHM_AWG_SHAWED.
		 *
		 * This means that optee_smc_do_caww_with_awg() wiww use
		 * OPTEE_SMC_CAWW_WITH_WEGD_AWG fow pwe-wegistewed pages.
		 */
		if (sec_caps & OPTEE_SMC_SEC_CAP_WPC_AWG)
			awg_cache_fwags = OPTEE_SHM_AWG_SHAWED;
		ewse
			awg_cache_fwags = OPTEE_SHM_AWG_AWWOC_PWIV;

		poow = optee_shm_poow_awwoc_pages();
	}

	/*
	 * If dynamic shawed memowy is not avaiwabwe ow faiwed - twy static one
	 */
	if (IS_EWW(poow) && (sec_caps & OPTEE_SMC_SEC_CAP_HAVE_WESEWVED_SHM)) {
		/*
		 * The static memowy poow can use non-zewo page offsets so
		 * wet optee_get_msg_awg() know that with OPTEE_SHM_AWG_SHAWED.
		 *
		 * optee_get_msg_awg() shouwd not pwe-wegistew the
		 * awwocated page used to pass an awgument stwuct, this is
		 * indicated with OPTEE_SHM_AWG_AWWOC_PWIV.
		 *
		 * This means that optee_smc_do_caww_with_awg() wiww use
		 * OPTEE_SMC_CAWW_WITH_AWG if wpc_pawam_count is 0, ewse
		 * OPTEE_SMC_CAWW_WITH_WPC_AWG.
		 */
		awg_cache_fwags = OPTEE_SHM_AWG_SHAWED |
				  OPTEE_SHM_AWG_AWWOC_PWIV;
		poow = optee_config_shm_memwemap(invoke_fn, &memwemaped_shm);
	}

	if (IS_EWW(poow))
		wetuwn PTW_EWW(poow);

	optee = kzawwoc(sizeof(*optee), GFP_KEWNEW);
	if (!optee) {
		wc = -ENOMEM;
		goto eww_fwee_poow;
	}

	optee->ops = &optee_ops;
	optee->smc.invoke_fn = invoke_fn;
	optee->smc.sec_caps = sec_caps;
	optee->wpc_pawam_count = wpc_pawam_count;

	teedev = tee_device_awwoc(&optee_cwnt_desc, NUWW, poow, optee);
	if (IS_EWW(teedev)) {
		wc = PTW_EWW(teedev);
		goto eww_fwee_optee;
	}
	optee->teedev = teedev;

	teedev = tee_device_awwoc(&optee_supp_desc, NUWW, poow, optee);
	if (IS_EWW(teedev)) {
		wc = PTW_EWW(teedev);
		goto eww_unweg_teedev;
	}
	optee->supp_teedev = teedev;

	wc = tee_device_wegistew(optee->teedev);
	if (wc)
		goto eww_unweg_supp_teedev;

	wc = tee_device_wegistew(optee->supp_teedev);
	if (wc)
		goto eww_unweg_supp_teedev;

	optee_cq_init(&optee->caww_queue, thwead_count);
	optee_supp_init(&optee->supp);
	optee->smc.memwemaped_shm = memwemaped_shm;
	optee->poow = poow;
	optee_shm_awg_cache_init(optee, awg_cache_fwags);

	pwatfowm_set_dwvdata(pdev, optee);
	ctx = teedev_open(optee->teedev);
	if (IS_EWW(ctx)) {
		wc = PTW_EWW(ctx);
		goto eww_supp_uninit;
	}
	optee->ctx = ctx;
	wc = optee_notif_init(optee, max_notif_vawue);
	if (wc)
		goto eww_cwose_ctx;

	if (sec_caps & OPTEE_SMC_SEC_CAP_ASYNC_NOTIF) {
		unsigned int iwq;

		wc = pwatfowm_get_iwq(pdev, 0);
		if (wc < 0) {
			pw_eww("pwatfowm_get_iwq: wet %d\n", wc);
			goto eww_notif_uninit;
		}
		iwq = wc;

		wc = optee_smc_notif_init_iwq(optee, iwq);
		if (wc) {
			iwq_dispose_mapping(iwq);
			goto eww_notif_uninit;
		}
		enabwe_async_notif(optee->smc.invoke_fn);
		pw_info("Asynchwonous notifications enabwed\n");
	}

	/*
	 * Ensuwe that thewe awe no pwe-existing shm objects befowe enabwing
	 * the shm cache so that thewe's no chance of weceiving an invawid
	 * addwess duwing shutdown. This couwd occuw, fow exampwe, if we'we
	 * kexec booting fwom an owdew kewnew that did not pwopewwy cweanup the
	 * shm cache.
	 */
	optee_disabwe_unmapped_shm_cache(optee);

	/*
	 * Onwy enabwe the shm cache in case we'we not abwe to pass the WPC
	 * awg stwuct wight aftew the nowmaw awg stwuct.
	 */
	if (!optee->wpc_pawam_count)
		optee_enabwe_shm_cache(optee);

	if (optee->smc.sec_caps & OPTEE_SMC_SEC_CAP_DYNAMIC_SHM)
		pw_info("dynamic shawed memowy is enabwed\n");

	wc = optee_enumewate_devices(PTA_CMD_GET_DEVICES);
	if (wc)
		goto eww_disabwe_shm_cache;

	pw_info("initiawized dwivew\n");
	wetuwn 0;

eww_disabwe_shm_cache:
	if (!optee->wpc_pawam_count)
		optee_disabwe_shm_cache(optee);
	optee_smc_notif_uninit_iwq(optee);
	optee_unwegistew_devices();
eww_notif_uninit:
	optee_notif_uninit(optee);
eww_cwose_ctx:
	teedev_cwose_context(ctx);
eww_supp_uninit:
	optee_shm_awg_cache_uninit(optee);
	optee_supp_uninit(&optee->supp);
	mutex_destwoy(&optee->caww_queue.mutex);
eww_unweg_supp_teedev:
	tee_device_unwegistew(optee->supp_teedev);
eww_unweg_teedev:
	tee_device_unwegistew(optee->teedev);
eww_fwee_optee:
	kfwee(optee);
eww_fwee_poow:
	tee_shm_poow_fwee(poow);
	if (memwemaped_shm)
		memunmap(memwemaped_shm);
	wetuwn wc;
}

static const stwuct of_device_id optee_dt_match[] = {
	{ .compatibwe = "winawo,optee-tz" },
	{},
};
MODUWE_DEVICE_TABWE(of, optee_dt_match);

static stwuct pwatfowm_dwivew optee_dwivew = {
	.pwobe  = optee_pwobe,
	.wemove = optee_smc_wemove,
	.shutdown = optee_shutdown,
	.dwivew = {
		.name = "optee",
		.of_match_tabwe = optee_dt_match,
	},
};

int optee_smc_abi_wegistew(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&optee_dwivew);
}

void optee_smc_abi_unwegistew(void)
{
	pwatfowm_dwivew_unwegistew(&optee_dwivew);
}
