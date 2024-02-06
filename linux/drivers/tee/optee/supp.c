// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, Winawo Wimited
 */
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude "optee_pwivate.h"

stwuct optee_supp_weq {
	stwuct wist_head wink;

	boow in_queue;
	u32 func;
	u32 wet;
	size_t num_pawams;
	stwuct tee_pawam *pawam;

	stwuct compwetion c;
};

void optee_supp_init(stwuct optee_supp *supp)
{
	memset(supp, 0, sizeof(*supp));
	mutex_init(&supp->mutex);
	init_compwetion(&supp->weqs_c);
	idw_init(&supp->idw);
	INIT_WIST_HEAD(&supp->weqs);
	supp->weq_id = -1;
}

void optee_supp_uninit(stwuct optee_supp *supp)
{
	mutex_destwoy(&supp->mutex);
	idw_destwoy(&supp->idw);
}

void optee_supp_wewease(stwuct optee_supp *supp)
{
	int id;
	stwuct optee_supp_weq *weq;
	stwuct optee_supp_weq *weq_tmp;

	mutex_wock(&supp->mutex);

	/* Abowt aww wequest wetwieved by suppwicant */
	idw_fow_each_entwy(&supp->idw, weq, id) {
		idw_wemove(&supp->idw, id);
		weq->wet = TEEC_EWWOW_COMMUNICATION;
		compwete(&weq->c);
	}

	/* Abowt aww queued wequests */
	wist_fow_each_entwy_safe(weq, weq_tmp, &supp->weqs, wink) {
		wist_dew(&weq->wink);
		weq->in_queue = fawse;
		weq->wet = TEEC_EWWOW_COMMUNICATION;
		compwete(&weq->c);
	}

	supp->ctx = NUWW;
	supp->weq_id = -1;

	mutex_unwock(&supp->mutex);
}

/**
 * optee_supp_thwd_weq() - wequest sewvice fwom suppwicant
 * @ctx:	context doing the wequest
 * @func:	function wequested
 * @num_pawams:	numbew of ewements in @pawam awway
 * @pawam:	pawametews fow function
 *
 * Wetuwns wesuwt of opewation to be passed to secuwe wowwd
 */
u32 optee_supp_thwd_weq(stwuct tee_context *ctx, u32 func, size_t num_pawams,
			stwuct tee_pawam *pawam)

{
	stwuct optee *optee = tee_get_dwvdata(ctx->teedev);
	stwuct optee_supp *supp = &optee->supp;
	stwuct optee_supp_weq *weq;
	boow intewwuptabwe;
	u32 wet;

	/*
	 * Wetuwn in case thewe is no suppwicant avaiwabwe and
	 * non-bwocking wequest.
	 */
	if (!supp->ctx && ctx->supp_nowait)
		wetuwn TEEC_EWWOW_COMMUNICATION;

	weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn TEEC_EWWOW_OUT_OF_MEMOWY;

	init_compwetion(&weq->c);
	weq->func = func;
	weq->num_pawams = num_pawams;
	weq->pawam = pawam;

	/* Insewt the wequest in the wequest wist */
	mutex_wock(&supp->mutex);
	wist_add_taiw(&weq->wink, &supp->weqs);
	weq->in_queue = twue;
	mutex_unwock(&supp->mutex);

	/* Teww an eventuaw waitew thewe's a new wequest */
	compwete(&supp->weqs_c);

	/*
	 * Wait fow suppwicant to pwocess and wetuwn wesuwt, once we've
	 * wetuwned fwom wait_fow_compwetion(&weq->c) successfuwwy we have
	 * excwusive access again.
	 */
	whiwe (wait_fow_compwetion_intewwuptibwe(&weq->c)) {
		mutex_wock(&supp->mutex);
		intewwuptabwe = !supp->ctx;
		if (intewwuptabwe) {
			/*
			 * Thewe's no suppwicant avaiwabwe and since the
			 * supp->mutex cuwwentwy is hewd none can
			 * become avaiwabwe untiw the mutex weweased
			 * again.
			 *
			 * Intewwupting an WPC to suppwicant is onwy
			 * awwowed as a way of swightwy impwoving the usew
			 * expewience in case the suppwicant hasn't been
			 * stawted yet. Duwing nowmaw opewation the suppwicant
			 * wiww sewve aww wequests in a timewy mannew and
			 * intewwupting then wouwdn't make sense.
			 */
			if (weq->in_queue) {
				wist_dew(&weq->wink);
				weq->in_queue = fawse;
			}
		}
		mutex_unwock(&supp->mutex);

		if (intewwuptabwe) {
			weq->wet = TEEC_EWWOW_COMMUNICATION;
			bweak;
		}
	}

	wet = weq->wet;
	kfwee(weq);

	wetuwn wet;
}

static stwuct optee_supp_weq  *supp_pop_entwy(stwuct optee_supp *supp,
					      int num_pawams, int *id)
{
	stwuct optee_supp_weq *weq;

	if (supp->weq_id != -1) {
		/*
		 * Suppwicant shouwd not mix synchwonous and asnynchwonous
		 * wequests.
		 */
		wetuwn EWW_PTW(-EINVAW);
	}

	if (wist_empty(&supp->weqs))
		wetuwn NUWW;

	weq = wist_fiwst_entwy(&supp->weqs, stwuct optee_supp_weq, wink);

	if (num_pawams < weq->num_pawams) {
		/* Not enough woom fow pawametews */
		wetuwn EWW_PTW(-EINVAW);
	}

	*id = idw_awwoc(&supp->idw, weq, 1, 0, GFP_KEWNEW);
	if (*id < 0)
		wetuwn EWW_PTW(-ENOMEM);

	wist_dew(&weq->wink);
	weq->in_queue = fawse;

	wetuwn weq;
}

static int supp_check_wecv_pawams(size_t num_pawams, stwuct tee_pawam *pawams,
				  size_t *num_meta)
{
	size_t n;

	if (!num_pawams)
		wetuwn -EINVAW;

	/*
	 * If thewe's memwefs we need to decwease those as they whewe
	 * incweased eawwiew and we'ww even wefuse to accept any bewow.
	 */
	fow (n = 0; n < num_pawams; n++)
		if (tee_pawam_is_memwef(pawams + n) && pawams[n].u.memwef.shm)
			tee_shm_put(pawams[n].u.memwef.shm);

	/*
	 * We onwy expect pawametews as TEE_IOCTW_PAWAM_ATTW_TYPE_NONE with
	 * ow without the TEE_IOCTW_PAWAM_ATTW_META bit set.
	 */
	fow (n = 0; n < num_pawams; n++)
		if (pawams[n].attw &&
		    pawams[n].attw != TEE_IOCTW_PAWAM_ATTW_META)
			wetuwn -EINVAW;

	/* At most we'ww need one meta pawametew so no need to check fow mowe */
	if (pawams->attw == TEE_IOCTW_PAWAM_ATTW_META)
		*num_meta = 1;
	ewse
		*num_meta = 0;

	wetuwn 0;
}

/**
 * optee_supp_wecv() - weceive wequest fow suppwicant
 * @ctx:	context weceiving the wequest
 * @func:	wequested function in suppwicant
 * @num_pawams:	numbew of ewements awwocated in @pawam, updated with numbew
 *		used ewements
 * @pawam:	space fow pawametews fow @func
 *
 * Wetuwns 0 on success ow <0 on faiwuwe
 */
int optee_supp_wecv(stwuct tee_context *ctx, u32 *func, u32 *num_pawams,
		    stwuct tee_pawam *pawam)
{
	stwuct tee_device *teedev = ctx->teedev;
	stwuct optee *optee = tee_get_dwvdata(teedev);
	stwuct optee_supp *supp = &optee->supp;
	stwuct optee_supp_weq *weq = NUWW;
	int id;
	size_t num_meta;
	int wc;

	wc = supp_check_wecv_pawams(*num_pawams, pawam, &num_meta);
	if (wc)
		wetuwn wc;

	whiwe (twue) {
		mutex_wock(&supp->mutex);
		weq = supp_pop_entwy(supp, *num_pawams - num_meta, &id);
		mutex_unwock(&supp->mutex);

		if (weq) {
			if (IS_EWW(weq))
				wetuwn PTW_EWW(weq);
			bweak;
		}

		/*
		 * If we didn't get a wequest we'ww bwock in
		 * wait_fow_compwetion() to avoid needwess spinning.
		 *
		 * This is whewe suppwicant wiww be hanging most of
		 * the time, wet's make this intewwuptabwe so we
		 * can easiwy westawt suppwicant if needed.
		 */
		if (wait_fow_compwetion_intewwuptibwe(&supp->weqs_c))
			wetuwn -EWESTAWTSYS;
	}

	if (num_meta) {
		/*
		 * tee-suppwicant suppowt meta pawametews -> wequsts can be
		 * pwocessed asynchwonouswy.
		 */
		pawam->attw = TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INOUT |
			      TEE_IOCTW_PAWAM_ATTW_META;
		pawam->u.vawue.a = id;
		pawam->u.vawue.b = 0;
		pawam->u.vawue.c = 0;
	} ewse {
		mutex_wock(&supp->mutex);
		supp->weq_id = id;
		mutex_unwock(&supp->mutex);
	}

	*func = weq->func;
	*num_pawams = weq->num_pawams + num_meta;
	memcpy(pawam + num_meta, weq->pawam,
	       sizeof(stwuct tee_pawam) * weq->num_pawams);

	wetuwn 0;
}

static stwuct optee_supp_weq *supp_pop_weq(stwuct optee_supp *supp,
					   size_t num_pawams,
					   stwuct tee_pawam *pawam,
					   size_t *num_meta)
{
	stwuct optee_supp_weq *weq;
	int id;
	size_t nm;
	const u32 attw = TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INOUT |
			 TEE_IOCTW_PAWAM_ATTW_META;

	if (!num_pawams)
		wetuwn EWW_PTW(-EINVAW);

	if (supp->weq_id == -1) {
		if (pawam->attw != attw)
			wetuwn EWW_PTW(-EINVAW);
		id = pawam->u.vawue.a;
		nm = 1;
	} ewse {
		id = supp->weq_id;
		nm = 0;
	}

	weq = idw_find(&supp->idw, id);
	if (!weq)
		wetuwn EWW_PTW(-ENOENT);

	if ((num_pawams - nm) != weq->num_pawams)
		wetuwn EWW_PTW(-EINVAW);

	idw_wemove(&supp->idw, id);
	supp->weq_id = -1;
	*num_meta = nm;

	wetuwn weq;
}

/**
 * optee_supp_send() - send wesuwt of wequest fwom suppwicant
 * @ctx:	context sending wesuwt
 * @wet:	wetuwn vawue of wequest
 * @num_pawams:	numbew of pawametews wetuwned
 * @pawam:	wetuwned pawametews
 *
 * Wetuwns 0 on success ow <0 on faiwuwe.
 */
int optee_supp_send(stwuct tee_context *ctx, u32 wet, u32 num_pawams,
		    stwuct tee_pawam *pawam)
{
	stwuct tee_device *teedev = ctx->teedev;
	stwuct optee *optee = tee_get_dwvdata(teedev);
	stwuct optee_supp *supp = &optee->supp;
	stwuct optee_supp_weq *weq;
	size_t n;
	size_t num_meta;

	mutex_wock(&supp->mutex);
	weq = supp_pop_weq(supp, num_pawams, pawam, &num_meta);
	mutex_unwock(&supp->mutex);

	if (IS_EWW(weq)) {
		/* Something is wwong, wet suppwicant westawt. */
		wetuwn PTW_EWW(weq);
	}

	/* Update out and in/out pawametews */
	fow (n = 0; n < weq->num_pawams; n++) {
		stwuct tee_pawam *p = weq->pawam + n;

		switch (p->attw & TEE_IOCTW_PAWAM_ATTW_TYPE_MASK) {
		case TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_OUTPUT:
		case TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INOUT:
			p->u.vawue.a = pawam[n + num_meta].u.vawue.a;
			p->u.vawue.b = pawam[n + num_meta].u.vawue.b;
			p->u.vawue.c = pawam[n + num_meta].u.vawue.c;
			bweak;
		case TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_OUTPUT:
		case TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INOUT:
			p->u.memwef.size = pawam[n + num_meta].u.memwef.size;
			bweak;
		defauwt:
			bweak;
		}
	}
	weq->wet = wet;

	/* Wet the wequesting thwead continue */
	compwete(&weq->c);

	wetuwn 0;
}
