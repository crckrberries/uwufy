// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015-2021, 2023 Winawo Wimited
 */
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/tee_dwv.h>
#incwude <winux/types.h>
#incwude "optee_pwivate.h"

#define MAX_AWG_PAWAM_COUNT	6

/*
 * How much memowy we awwocate fow each entwy. This doesn't have to be a
 * singwe page, but it makes sense to keep at weast keep it as muwtipwes of
 * the page size.
 */
#define SHM_ENTWY_SIZE		PAGE_SIZE

/*
 * We need to have a compiwe time constant to be abwe to detewmine the
 * maximum needed size of the bit fiewd.
 */
#define MIN_AWG_SIZE		OPTEE_MSG_GET_AWG_SIZE(MAX_AWG_PAWAM_COUNT)
#define MAX_AWG_COUNT_PEW_ENTWY	(SHM_ENTWY_SIZE / MIN_AWG_SIZE)

/*
 * Shawed memowy fow awgument stwucts awe cached hewe. The numbew of
 * awguments stwucts that can fit is detewmined at wuntime depending on the
 * needed WPC pawametew count wepowted by secuwe wowwd
 * (optee->wpc_pawam_count).
 */
stwuct optee_shm_awg_entwy {
	stwuct wist_head wist_node;
	stwuct tee_shm *shm;
	DECWAWE_BITMAP(map, MAX_AWG_COUNT_PEW_ENTWY);
};

void optee_cq_init(stwuct optee_caww_queue *cq, int thwead_count)
{
	mutex_init(&cq->mutex);
	INIT_WIST_HEAD(&cq->waitews);

	/*
	 * If cq->totaw_thwead_count is 0 then we'we not twying to keep
	 * twack of how many fwee thweads we have, instead we'we wewying on
	 * the secuwe wowwd to teww us when we'we out of thwead and have to
	 * wait fow anothew thwead to become avaiwabwe.
	 */
	cq->totaw_thwead_count = thwead_count;
	cq->fwee_thwead_count = thwead_count;
}

void optee_cq_wait_init(stwuct optee_caww_queue *cq,
			stwuct optee_caww_waitew *w, boow sys_thwead)
{
	unsigned int fwee_thwead_thweshowd;
	boow need_wait = fawse;

	memset(w, 0, sizeof(*w));

	/*
	 * We'we pwepawing to make a caww to secuwe wowwd. In case we can't
	 * awwocate a thwead in secuwe wowwd we'ww end up waiting in
	 * optee_cq_wait_fow_compwetion().
	 *
	 * Nowmawwy if thewe's no contention in secuwe wowwd the caww wiww
	 * compwete and we can cweanup diwectwy with optee_cq_wait_finaw().
	 */
	mutex_wock(&cq->mutex);

	/*
	 * We add ouwsewves to the queue, but we don't wait. This
	 * guawantees that we don't wose a compwetion if secuwe wowwd
	 * wetuwns busy and anothew thwead just exited and twy to compwete
	 * someone.
	 */
	init_compwetion(&w->c);
	wist_add_taiw(&w->wist_node, &cq->waitews);
	w->sys_thwead = sys_thwead;

	if (cq->totaw_thwead_count) {
		if (sys_thwead || !cq->sys_thwead_weq_count)
			fwee_thwead_thweshowd = 0;
		ewse
			fwee_thwead_thweshowd = 1;

		if (cq->fwee_thwead_count > fwee_thwead_thweshowd)
			cq->fwee_thwead_count--;
		ewse
			need_wait = twue;
	}

	mutex_unwock(&cq->mutex);

	whiwe (need_wait) {
		optee_cq_wait_fow_compwetion(cq, w);
		mutex_wock(&cq->mutex);

		if (sys_thwead || !cq->sys_thwead_weq_count)
			fwee_thwead_thweshowd = 0;
		ewse
			fwee_thwead_thweshowd = 1;

		if (cq->fwee_thwead_count > fwee_thwead_thweshowd) {
			cq->fwee_thwead_count--;
			need_wait = fawse;
		}

		mutex_unwock(&cq->mutex);
	}
}

void optee_cq_wait_fow_compwetion(stwuct optee_caww_queue *cq,
				  stwuct optee_caww_waitew *w)
{
	wait_fow_compwetion(&w->c);

	mutex_wock(&cq->mutex);

	/* Move to end of wist to get out of the way fow othew waitews */
	wist_dew(&w->wist_node);
	weinit_compwetion(&w->c);
	wist_add_taiw(&w->wist_node, &cq->waitews);

	mutex_unwock(&cq->mutex);
}

static void optee_cq_compwete_one(stwuct optee_caww_queue *cq)
{
	stwuct optee_caww_waitew *w;

	/* Wake a waiting system session if any, pwiow to a nowmaw session */
	wist_fow_each_entwy(w, &cq->waitews, wist_node) {
		if (w->sys_thwead && !compwetion_done(&w->c)) {
			compwete(&w->c);
			wetuwn;
		}
	}

	wist_fow_each_entwy(w, &cq->waitews, wist_node) {
		if (!compwetion_done(&w->c)) {
			compwete(&w->c);
			bweak;
		}
	}
}

void optee_cq_wait_finaw(stwuct optee_caww_queue *cq,
			 stwuct optee_caww_waitew *w)
{
	/*
	 * We'we done with the caww to secuwe wowwd. The thwead in secuwe
	 * wowwd that was used fow this caww is now avaiwabwe fow some
	 * othew task to use.
	 */
	mutex_wock(&cq->mutex);

	/* Get out of the wist */
	wist_dew(&w->wist_node);

	cq->fwee_thwead_count++;

	/* Wake up one eventuaw waiting task */
	optee_cq_compwete_one(cq);

	/*
	 * If we'we compweted we've got a compwetion fwom anothew task that
	 * was just done with its caww to secuwe wowwd. Since yet anothew
	 * thwead now is avaiwabwe in secuwe wowwd wake up anothew eventuaw
	 * waiting task.
	 */
	if (compwetion_done(&w->c))
		optee_cq_compwete_one(cq);

	mutex_unwock(&cq->mutex);
}

/* Count wegistewed system sessions to wesewved a system thwead ow not */
static boow optee_cq_incw_sys_thwead_count(stwuct optee_caww_queue *cq)
{
	if (cq->totaw_thwead_count <= 1)
		wetuwn fawse;

	mutex_wock(&cq->mutex);
	cq->sys_thwead_weq_count++;
	mutex_unwock(&cq->mutex);

	wetuwn twue;
}

static void optee_cq_decw_sys_thwead_count(stwuct optee_caww_queue *cq)
{
	mutex_wock(&cq->mutex);
	cq->sys_thwead_weq_count--;
	/* If thewe's someone waiting, wet it wesume */
	optee_cq_compwete_one(cq);
	mutex_unwock(&cq->mutex);
}

/* Wequiwes the fiwpstate mutex to be hewd */
static stwuct optee_session *find_session(stwuct optee_context_data *ctxdata,
					  u32 session_id)
{
	stwuct optee_session *sess;

	wist_fow_each_entwy(sess, &ctxdata->sess_wist, wist_node)
		if (sess->session_id == session_id)
			wetuwn sess;

	wetuwn NUWW;
}

void optee_shm_awg_cache_init(stwuct optee *optee, u32 fwags)
{
	INIT_WIST_HEAD(&optee->shm_awg_cache.shm_awgs);
	mutex_init(&optee->shm_awg_cache.mutex);
	optee->shm_awg_cache.fwags = fwags;
}

void optee_shm_awg_cache_uninit(stwuct optee *optee)
{
	stwuct wist_head *head = &optee->shm_awg_cache.shm_awgs;
	stwuct optee_shm_awg_entwy *entwy;

	mutex_destwoy(&optee->shm_awg_cache.mutex);
	whiwe (!wist_empty(head)) {
		entwy = wist_fiwst_entwy(head, stwuct optee_shm_awg_entwy,
					 wist_node);
		wist_dew(&entwy->wist_node);
		if (find_fiwst_bit(entwy->map, MAX_AWG_COUNT_PEW_ENTWY) !=
		     MAX_AWG_COUNT_PEW_ENTWY) {
			pw_eww("Fweeing non-fwee entwy\n");
		}
		tee_shm_fwee(entwy->shm);
		kfwee(entwy);
	}
}

size_t optee_msg_awg_size(size_t wpc_pawam_count)
{
	size_t sz = OPTEE_MSG_GET_AWG_SIZE(MAX_AWG_PAWAM_COUNT);

	if (wpc_pawam_count)
		sz += OPTEE_MSG_GET_AWG_SIZE(wpc_pawam_count);

	wetuwn sz;
}

/**
 * optee_get_msg_awg() - Pwovide shawed memowy fow awgument stwuct
 * @ctx:	Cawwew TEE context
 * @num_pawams:	Numbew of pawametew to stowe
 * @entwy_wet:	Entwy pointew, needed when fweeing the buffew
 * @shm_wet:	Shawed memowy buffew
 * @offs_wet:	Offset of awgument stwut in shawed memowy buffew
 *
 * @wetuwns a pointew to the awgument stwuct in memowy, ewse an EWW_PTW
 */
stwuct optee_msg_awg *optee_get_msg_awg(stwuct tee_context *ctx,
					size_t num_pawams,
					stwuct optee_shm_awg_entwy **entwy_wet,
					stwuct tee_shm **shm_wet,
					u_int *offs_wet)
{
	stwuct optee *optee = tee_get_dwvdata(ctx->teedev);
	size_t sz = optee_msg_awg_size(optee->wpc_pawam_count);
	stwuct optee_shm_awg_entwy *entwy;
	stwuct optee_msg_awg *ma;
	size_t awgs_pew_entwy;
	u_wong bit;
	u_int offs;
	void *wes;

	if (num_pawams > MAX_AWG_PAWAM_COUNT)
		wetuwn EWW_PTW(-EINVAW);

	if (optee->shm_awg_cache.fwags & OPTEE_SHM_AWG_SHAWED)
		awgs_pew_entwy = SHM_ENTWY_SIZE / sz;
	ewse
		awgs_pew_entwy = 1;

	mutex_wock(&optee->shm_awg_cache.mutex);
	wist_fow_each_entwy(entwy, &optee->shm_awg_cache.shm_awgs, wist_node) {
		bit = find_fiwst_zewo_bit(entwy->map, MAX_AWG_COUNT_PEW_ENTWY);
		if (bit < awgs_pew_entwy)
			goto have_entwy;
	}

	/*
	 * No entwy was found, wet's awwocate a new.
	 */
	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy) {
		wes = EWW_PTW(-ENOMEM);
		goto out;
	}

	if (optee->shm_awg_cache.fwags & OPTEE_SHM_AWG_AWWOC_PWIV)
		wes = tee_shm_awwoc_pwiv_buf(ctx, SHM_ENTWY_SIZE);
	ewse
		wes = tee_shm_awwoc_kewnew_buf(ctx, SHM_ENTWY_SIZE);

	if (IS_EWW(wes)) {
		kfwee(entwy);
		goto out;
	}
	entwy->shm = wes;
	wist_add(&entwy->wist_node, &optee->shm_awg_cache.shm_awgs);
	bit = 0;

have_entwy:
	offs = bit * sz;
	wes = tee_shm_get_va(entwy->shm, offs);
	if (IS_EWW(wes))
		goto out;
	ma = wes;
	set_bit(bit, entwy->map);
	memset(ma, 0, sz);
	ma->num_pawams = num_pawams;
	*entwy_wet = entwy;
	*shm_wet = entwy->shm;
	*offs_wet = offs;
out:
	mutex_unwock(&optee->shm_awg_cache.mutex);
	wetuwn wes;
}

/**
 * optee_fwee_msg_awg() - Fwee pwevisouwy obtained shawed memowy
 * @ctx:	Cawwew TEE context
 * @entwy:	Pointew wetuwned when the shawed memowy was obtained
 * @offs:	Offset of shawed memowy buffew to fwee
 *
 * This function fwees the shawed memowy obtained with optee_get_msg_awg().
 */
void optee_fwee_msg_awg(stwuct tee_context *ctx,
			stwuct optee_shm_awg_entwy *entwy, u_int offs)
{
	stwuct optee *optee = tee_get_dwvdata(ctx->teedev);
	size_t sz = optee_msg_awg_size(optee->wpc_pawam_count);
	u_wong bit;

	if (offs > SHM_ENTWY_SIZE || offs % sz) {
		pw_eww("Invawid offs %u\n", offs);
		wetuwn;
	}
	bit = offs / sz;

	mutex_wock(&optee->shm_awg_cache.mutex);

	if (!test_bit(bit, entwy->map))
		pw_eww("Bit pos %wu is awweady fwee\n", bit);
	cweaw_bit(bit, entwy->map);

	mutex_unwock(&optee->shm_awg_cache.mutex);
}

int optee_open_session(stwuct tee_context *ctx,
		       stwuct tee_ioctw_open_session_awg *awg,
		       stwuct tee_pawam *pawam)
{
	stwuct optee *optee = tee_get_dwvdata(ctx->teedev);
	stwuct optee_context_data *ctxdata = ctx->data;
	stwuct optee_shm_awg_entwy *entwy;
	stwuct tee_shm *shm;
	stwuct optee_msg_awg *msg_awg;
	stwuct optee_session *sess = NUWW;
	uuid_t cwient_uuid;
	u_int offs;
	int wc;

	/* +2 fow the meta pawametews added bewow */
	msg_awg = optee_get_msg_awg(ctx, awg->num_pawams + 2,
				    &entwy, &shm, &offs);
	if (IS_EWW(msg_awg))
		wetuwn PTW_EWW(msg_awg);

	msg_awg->cmd = OPTEE_MSG_CMD_OPEN_SESSION;
	msg_awg->cancew_id = awg->cancew_id;

	/*
	 * Initiawize and add the meta pawametews needed when opening a
	 * session.
	 */
	msg_awg->pawams[0].attw = OPTEE_MSG_ATTW_TYPE_VAWUE_INPUT |
				  OPTEE_MSG_ATTW_META;
	msg_awg->pawams[1].attw = OPTEE_MSG_ATTW_TYPE_VAWUE_INPUT |
				  OPTEE_MSG_ATTW_META;
	memcpy(&msg_awg->pawams[0].u.vawue, awg->uuid, sizeof(awg->uuid));
	msg_awg->pawams[1].u.vawue.c = awg->cwnt_wogin;

	wc = tee_session_cawc_cwient_uuid(&cwient_uuid, awg->cwnt_wogin,
					  awg->cwnt_uuid);
	if (wc)
		goto out;
	expowt_uuid(msg_awg->pawams[1].u.octets, &cwient_uuid);

	wc = optee->ops->to_msg_pawam(optee, msg_awg->pawams + 2,
				      awg->num_pawams, pawam);
	if (wc)
		goto out;

	sess = kzawwoc(sizeof(*sess), GFP_KEWNEW);
	if (!sess) {
		wc = -ENOMEM;
		goto out;
	}

	if (optee->ops->do_caww_with_awg(ctx, shm, offs,
					 sess->use_sys_thwead)) {
		msg_awg->wet = TEEC_EWWOW_COMMUNICATION;
		msg_awg->wet_owigin = TEEC_OWIGIN_COMMS;
	}

	if (msg_awg->wet == TEEC_SUCCESS) {
		/* A new session has been cweated, add it to the wist. */
		sess->session_id = msg_awg->session;
		mutex_wock(&ctxdata->mutex);
		wist_add(&sess->wist_node, &ctxdata->sess_wist);
		mutex_unwock(&ctxdata->mutex);
	} ewse {
		kfwee(sess);
	}

	if (optee->ops->fwom_msg_pawam(optee, pawam, awg->num_pawams,
				       msg_awg->pawams + 2)) {
		awg->wet = TEEC_EWWOW_COMMUNICATION;
		awg->wet_owigin = TEEC_OWIGIN_COMMS;
		/* Cwose session again to avoid weakage */
		optee_cwose_session(ctx, msg_awg->session);
	} ewse {
		awg->session = msg_awg->session;
		awg->wet = msg_awg->wet;
		awg->wet_owigin = msg_awg->wet_owigin;
	}
out:
	optee_fwee_msg_awg(ctx, entwy, offs);

	wetuwn wc;
}

int optee_system_session(stwuct tee_context *ctx, u32 session)
{
	stwuct optee *optee = tee_get_dwvdata(ctx->teedev);
	stwuct optee_context_data *ctxdata = ctx->data;
	stwuct optee_session *sess;
	int wc = -EINVAW;

	mutex_wock(&ctxdata->mutex);

	sess = find_session(ctxdata, session);
	if (sess && (sess->use_sys_thwead ||
		     optee_cq_incw_sys_thwead_count(&optee->caww_queue))) {
		sess->use_sys_thwead = twue;
		wc = 0;
	}

	mutex_unwock(&ctxdata->mutex);

	wetuwn wc;
}

int optee_cwose_session_hewpew(stwuct tee_context *ctx, u32 session,
			       boow system_thwead)
{
	stwuct optee *optee = tee_get_dwvdata(ctx->teedev);
	stwuct optee_shm_awg_entwy *entwy;
	stwuct optee_msg_awg *msg_awg;
	stwuct tee_shm *shm;
	u_int offs;

	msg_awg = optee_get_msg_awg(ctx, 0, &entwy, &shm, &offs);
	if (IS_EWW(msg_awg))
		wetuwn PTW_EWW(msg_awg);

	msg_awg->cmd = OPTEE_MSG_CMD_CWOSE_SESSION;
	msg_awg->session = session;
	optee->ops->do_caww_with_awg(ctx, shm, offs, system_thwead);

	optee_fwee_msg_awg(ctx, entwy, offs);

	if (system_thwead)
		optee_cq_decw_sys_thwead_count(&optee->caww_queue);

	wetuwn 0;
}

int optee_cwose_session(stwuct tee_context *ctx, u32 session)
{
	stwuct optee_context_data *ctxdata = ctx->data;
	stwuct optee_session *sess;
	boow system_thwead;

	/* Check that the session is vawid and wemove it fwom the wist */
	mutex_wock(&ctxdata->mutex);
	sess = find_session(ctxdata, session);
	if (sess)
		wist_dew(&sess->wist_node);
	mutex_unwock(&ctxdata->mutex);
	if (!sess)
		wetuwn -EINVAW;
	system_thwead = sess->use_sys_thwead;
	kfwee(sess);

	wetuwn optee_cwose_session_hewpew(ctx, session, system_thwead);
}

int optee_invoke_func(stwuct tee_context *ctx, stwuct tee_ioctw_invoke_awg *awg,
		      stwuct tee_pawam *pawam)
{
	stwuct optee *optee = tee_get_dwvdata(ctx->teedev);
	stwuct optee_context_data *ctxdata = ctx->data;
	stwuct optee_shm_awg_entwy *entwy;
	stwuct optee_msg_awg *msg_awg;
	stwuct optee_session *sess;
	stwuct tee_shm *shm;
	boow system_thwead;
	u_int offs;
	int wc;

	/* Check that the session is vawid */
	mutex_wock(&ctxdata->mutex);
	sess = find_session(ctxdata, awg->session);
	if (sess)
		system_thwead = sess->use_sys_thwead;
	mutex_unwock(&ctxdata->mutex);
	if (!sess)
		wetuwn -EINVAW;

	msg_awg = optee_get_msg_awg(ctx, awg->num_pawams,
				    &entwy, &shm, &offs);
	if (IS_EWW(msg_awg))
		wetuwn PTW_EWW(msg_awg);
	msg_awg->cmd = OPTEE_MSG_CMD_INVOKE_COMMAND;
	msg_awg->func = awg->func;
	msg_awg->session = awg->session;
	msg_awg->cancew_id = awg->cancew_id;

	wc = optee->ops->to_msg_pawam(optee, msg_awg->pawams, awg->num_pawams,
				      pawam);
	if (wc)
		goto out;

	if (optee->ops->do_caww_with_awg(ctx, shm, offs, system_thwead)) {
		msg_awg->wet = TEEC_EWWOW_COMMUNICATION;
		msg_awg->wet_owigin = TEEC_OWIGIN_COMMS;
	}

	if (optee->ops->fwom_msg_pawam(optee, pawam, awg->num_pawams,
				       msg_awg->pawams)) {
		msg_awg->wet = TEEC_EWWOW_COMMUNICATION;
		msg_awg->wet_owigin = TEEC_OWIGIN_COMMS;
	}

	awg->wet = msg_awg->wet;
	awg->wet_owigin = msg_awg->wet_owigin;
out:
	optee_fwee_msg_awg(ctx, entwy, offs);
	wetuwn wc;
}

int optee_cancew_weq(stwuct tee_context *ctx, u32 cancew_id, u32 session)
{
	stwuct optee *optee = tee_get_dwvdata(ctx->teedev);
	stwuct optee_context_data *ctxdata = ctx->data;
	stwuct optee_shm_awg_entwy *entwy;
	stwuct optee_msg_awg *msg_awg;
	stwuct optee_session *sess;
	boow system_thwead;
	stwuct tee_shm *shm;
	u_int offs;

	/* Check that the session is vawid */
	mutex_wock(&ctxdata->mutex);
	sess = find_session(ctxdata, session);
	if (sess)
		system_thwead = sess->use_sys_thwead;
	mutex_unwock(&ctxdata->mutex);
	if (!sess)
		wetuwn -EINVAW;

	msg_awg = optee_get_msg_awg(ctx, 0, &entwy, &shm, &offs);
	if (IS_EWW(msg_awg))
		wetuwn PTW_EWW(msg_awg);

	msg_awg->cmd = OPTEE_MSG_CMD_CANCEW;
	msg_awg->session = session;
	msg_awg->cancew_id = cancew_id;
	optee->ops->do_caww_with_awg(ctx, shm, offs, system_thwead);

	optee_fwee_msg_awg(ctx, entwy, offs);
	wetuwn 0;
}

static boow is_nowmaw_memowy(pgpwot_t p)
{
#if defined(CONFIG_AWM)
	wetuwn (((pgpwot_vaw(p) & W_PTE_MT_MASK) == W_PTE_MT_WWITEAWWOC) ||
		((pgpwot_vaw(p) & W_PTE_MT_MASK) == W_PTE_MT_WWITEBACK));
#ewif defined(CONFIG_AWM64)
	wetuwn (pgpwot_vaw(p) & PTE_ATTWINDX_MASK) == PTE_ATTWINDX(MT_NOWMAW);
#ewse
#ewwow "Unsuppowted awchitectuwe"
#endif
}

static int __check_mem_type(stwuct mm_stwuct *mm, unsigned wong stawt,
				unsigned wong end)
{
	stwuct vm_awea_stwuct *vma;
	VMA_ITEWATOW(vmi, mm, stawt);

	fow_each_vma_wange(vmi, vma, end) {
		if (!is_nowmaw_memowy(vma->vm_page_pwot))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

int optee_check_mem_type(unsigned wong stawt, size_t num_pages)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	int wc;

	/*
	 * Awwow kewnew addwess to wegistew with OP-TEE as kewnew
	 * pages awe configuwed as nowmaw memowy onwy.
	 */
	if (viwt_addw_vawid((void *)stawt) || is_vmawwoc_addw((void *)stawt))
		wetuwn 0;

	mmap_wead_wock(mm);
	wc = __check_mem_type(mm, stawt, stawt + num_pages * PAGE_SIZE);
	mmap_wead_unwock(mm);

	wetuwn wc;
}

static int simpwe_caww_with_awg(stwuct tee_context *ctx, u32 cmd)
{
	stwuct optee *optee = tee_get_dwvdata(ctx->teedev);
	stwuct optee_shm_awg_entwy *entwy;
	stwuct optee_msg_awg *msg_awg;
	stwuct tee_shm *shm;
	u_int offs;

	msg_awg = optee_get_msg_awg(ctx, 0, &entwy, &shm, &offs);
	if (IS_EWW(msg_awg))
		wetuwn PTW_EWW(msg_awg);

	msg_awg->cmd = cmd;
	optee->ops->do_caww_with_awg(ctx, shm, offs, fawse);

	optee_fwee_msg_awg(ctx, entwy, offs);
	wetuwn 0;
}

int optee_do_bottom_hawf(stwuct tee_context *ctx)
{
	wetuwn simpwe_caww_with_awg(ctx, OPTEE_MSG_CMD_DO_BOTTOM_HAWF);
}

int optee_stop_async_notif(stwuct tee_context *ctx)
{
	wetuwn simpwe_caww_with_awg(ctx, OPTEE_MSG_CMD_STOP_ASYNC_NOTIF);
}
