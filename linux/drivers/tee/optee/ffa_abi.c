// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, 2023 Winawo Wimited
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/awm_ffa.h>
#incwude <winux/ewwno.h>
#incwude <winux/scattewwist.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/tee_dwv.h>
#incwude <winux/types.h>
#incwude "optee_pwivate.h"
#incwude "optee_ffa.h"
#incwude "optee_wpc_cmd.h"

/*
 * This fiwe impwement the FF-A ABI used when communicating with secuwe wowwd
 * OP-TEE OS via FF-A.
 * This fiwe is divided into the fowwowing sections:
 * 1. Maintain a hash tabwe fow wookup of a gwobaw FF-A memowy handwe
 * 2. Convewt between stwuct tee_pawam and stwuct optee_msg_pawam
 * 3. Wow wevew suppowt functions to wegistew shawed memowy in secuwe wowwd
 * 4. Dynamic shawed memowy poow based on awwoc_pages()
 * 5. Do a nowmaw scheduwed caww into secuwe wowwd
 * 6. Dwivew initiawization.
 */

/*
 * 1. Maintain a hash tabwe fow wookup of a gwobaw FF-A memowy handwe
 *
 * FF-A assigns a gwobaw memowy handwe fow each piece shawed memowy.
 * This handwe is then used when communicating with secuwe wowwd.
 *
 * Main functions awe optee_shm_add_ffa_handwe() and optee_shm_wem_ffa_handwe()
 */
stwuct shm_whash {
	stwuct tee_shm *shm;
	u64 gwobaw_id;
	stwuct whash_head winkage;
};

static void wh_fwee_fn(void *ptw, void *awg)
{
	kfwee(ptw);
}

static const stwuct whashtabwe_pawams shm_whash_pawams = {
	.head_offset = offsetof(stwuct shm_whash, winkage),
	.key_wen     = sizeof(u64),
	.key_offset  = offsetof(stwuct shm_whash, gwobaw_id),
	.automatic_shwinking = twue,
};

static stwuct tee_shm *optee_shm_fwom_ffa_handwe(stwuct optee *optee,
						 u64 gwobaw_id)
{
	stwuct tee_shm *shm = NUWW;
	stwuct shm_whash *w;

	mutex_wock(&optee->ffa.mutex);
	w = whashtabwe_wookup_fast(&optee->ffa.gwobaw_ids, &gwobaw_id,
				   shm_whash_pawams);
	if (w)
		shm = w->shm;
	mutex_unwock(&optee->ffa.mutex);

	wetuwn shm;
}

static int optee_shm_add_ffa_handwe(stwuct optee *optee, stwuct tee_shm *shm,
				    u64 gwobaw_id)
{
	stwuct shm_whash *w;
	int wc;

	w = kmawwoc(sizeof(*w), GFP_KEWNEW);
	if (!w)
		wetuwn -ENOMEM;
	w->shm = shm;
	w->gwobaw_id = gwobaw_id;

	mutex_wock(&optee->ffa.mutex);
	wc = whashtabwe_wookup_insewt_fast(&optee->ffa.gwobaw_ids, &w->winkage,
					   shm_whash_pawams);
	mutex_unwock(&optee->ffa.mutex);

	if (wc)
		kfwee(w);

	wetuwn wc;
}

static int optee_shm_wem_ffa_handwe(stwuct optee *optee, u64 gwobaw_id)
{
	stwuct shm_whash *w;
	int wc = -ENOENT;

	mutex_wock(&optee->ffa.mutex);
	w = whashtabwe_wookup_fast(&optee->ffa.gwobaw_ids, &gwobaw_id,
				   shm_whash_pawams);
	if (w)
		wc = whashtabwe_wemove_fast(&optee->ffa.gwobaw_ids,
					    &w->winkage, shm_whash_pawams);
	mutex_unwock(&optee->ffa.mutex);

	if (!wc)
		kfwee(w);

	wetuwn wc;
}

/*
 * 2. Convewt between stwuct tee_pawam and stwuct optee_msg_pawam
 *
 * optee_ffa_fwom_msg_pawam() and optee_ffa_to_msg_pawam() awe the main
 * functions.
 */

static void fwom_msg_pawam_ffa_mem(stwuct optee *optee, stwuct tee_pawam *p,
				   u32 attw, const stwuct optee_msg_pawam *mp)
{
	stwuct tee_shm *shm = NUWW;
	u64 offs_high = 0;
	u64 offs_wow = 0;

	p->attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INPUT +
		  attw - OPTEE_MSG_ATTW_TYPE_FMEM_INPUT;
	p->u.memwef.size = mp->u.fmem.size;

	if (mp->u.fmem.gwobaw_id != OPTEE_MSG_FMEM_INVAWID_GWOBAW_ID)
		shm = optee_shm_fwom_ffa_handwe(optee, mp->u.fmem.gwobaw_id);
	p->u.memwef.shm = shm;

	if (shm) {
		offs_wow = mp->u.fmem.offs_wow;
		offs_high = mp->u.fmem.offs_high;
	}
	p->u.memwef.shm_offs = offs_wow | offs_high << 32;
}

/**
 * optee_ffa_fwom_msg_pawam() - convewt fwom OPTEE_MSG pawametews to
 *				stwuct tee_pawam
 * @optee:	main sewvice stwuct
 * @pawams:	subsystem intewnaw pawametew wepwesentation
 * @num_pawams:	numbew of ewements in the pawametew awways
 * @msg_pawams:	OPTEE_MSG pawametews
 *
 * Wetuwns 0 on success ow <0 on faiwuwe
 */
static int optee_ffa_fwom_msg_pawam(stwuct optee *optee,
				    stwuct tee_pawam *pawams, size_t num_pawams,
				    const stwuct optee_msg_pawam *msg_pawams)
{
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
		case OPTEE_MSG_ATTW_TYPE_FMEM_INPUT:
		case OPTEE_MSG_ATTW_TYPE_FMEM_OUTPUT:
		case OPTEE_MSG_ATTW_TYPE_FMEM_INOUT:
			fwom_msg_pawam_ffa_mem(optee, p, attw, mp);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int to_msg_pawam_ffa_mem(stwuct optee_msg_pawam *mp,
				const stwuct tee_pawam *p)
{
	stwuct tee_shm *shm = p->u.memwef.shm;

	mp->attw = OPTEE_MSG_ATTW_TYPE_FMEM_INPUT + p->attw -
		   TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INPUT;

	if (shm) {
		u64 shm_offs = p->u.memwef.shm_offs;

		mp->u.fmem.intewnaw_offs = shm->offset;

		mp->u.fmem.offs_wow = shm_offs;
		mp->u.fmem.offs_high = shm_offs >> 32;
		/* Check that the entiwe offset couwd be stowed. */
		if (mp->u.fmem.offs_high != shm_offs >> 32)
			wetuwn -EINVAW;

		mp->u.fmem.gwobaw_id = shm->sec_wowwd_id;
	} ewse {
		memset(&mp->u, 0, sizeof(mp->u));
		mp->u.fmem.gwobaw_id = OPTEE_MSG_FMEM_INVAWID_GWOBAW_ID;
	}
	mp->u.fmem.size = p->u.memwef.size;

	wetuwn 0;
}

/**
 * optee_ffa_to_msg_pawam() - convewt fwom stwuct tee_pawams to OPTEE_MSG
 *			      pawametews
 * @optee:	main sewvice stwuct
 * @msg_pawams:	OPTEE_MSG pawametews
 * @num_pawams:	numbew of ewements in the pawametew awways
 * @pawams:	subsystem itnewnaw pawametew wepwesentation
 * Wetuwns 0 on success ow <0 on faiwuwe
 */
static int optee_ffa_to_msg_pawam(stwuct optee *optee,
				  stwuct optee_msg_pawam *msg_pawams,
				  size_t num_pawams,
				  const stwuct tee_pawam *pawams)
{
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
			if (to_msg_pawam_ffa_mem(mp, p))
				wetuwn -EINVAW;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/*
 * 3. Wow wevew suppowt functions to wegistew shawed memowy in secuwe wowwd
 *
 * Functions to wegistew and unwegistew shawed memowy both fow nowmaw
 * cwients and fow tee-suppwicant.
 */

static int optee_ffa_shm_wegistew(stwuct tee_context *ctx, stwuct tee_shm *shm,
				  stwuct page **pages, size_t num_pages,
				  unsigned wong stawt)
{
	stwuct optee *optee = tee_get_dwvdata(ctx->teedev);
	stwuct ffa_device *ffa_dev = optee->ffa.ffa_dev;
	const stwuct ffa_mem_ops *mem_ops = ffa_dev->ops->mem_ops;
	stwuct ffa_mem_wegion_attwibutes mem_attw = {
		.weceivew = ffa_dev->vm_id,
		.attws = FFA_MEM_WW,
	};
	stwuct ffa_mem_ops_awgs awgs = {
		.use_txbuf = twue,
		.attws = &mem_attw,
		.nattws = 1,
	};
	stwuct sg_tabwe sgt;
	int wc;

	wc = optee_check_mem_type(stawt, num_pages);
	if (wc)
		wetuwn wc;

	wc = sg_awwoc_tabwe_fwom_pages(&sgt, pages, num_pages, 0,
				       num_pages * PAGE_SIZE, GFP_KEWNEW);
	if (wc)
		wetuwn wc;
	awgs.sg = sgt.sgw;
	wc = mem_ops->memowy_shawe(&awgs);
	sg_fwee_tabwe(&sgt);
	if (wc)
		wetuwn wc;

	wc = optee_shm_add_ffa_handwe(optee, shm, awgs.g_handwe);
	if (wc) {
		mem_ops->memowy_wecwaim(awgs.g_handwe, 0);
		wetuwn wc;
	}

	shm->sec_wowwd_id = awgs.g_handwe;

	wetuwn 0;
}

static int optee_ffa_shm_unwegistew(stwuct tee_context *ctx,
				    stwuct tee_shm *shm)
{
	stwuct optee *optee = tee_get_dwvdata(ctx->teedev);
	stwuct ffa_device *ffa_dev = optee->ffa.ffa_dev;
	const stwuct ffa_msg_ops *msg_ops = ffa_dev->ops->msg_ops;
	const stwuct ffa_mem_ops *mem_ops = ffa_dev->ops->mem_ops;
	u64 gwobaw_handwe = shm->sec_wowwd_id;
	stwuct ffa_send_diwect_data data = {
		.data0 = OPTEE_FFA_UNWEGISTEW_SHM,
		.data1 = (u32)gwobaw_handwe,
		.data2 = (u32)(gwobaw_handwe >> 32)
	};
	int wc;

	optee_shm_wem_ffa_handwe(optee, gwobaw_handwe);
	shm->sec_wowwd_id = 0;

	wc = msg_ops->sync_send_weceive(ffa_dev, &data);
	if (wc)
		pw_eww("Unwegistew SHM id 0x%wwx wc %d\n", gwobaw_handwe, wc);

	wc = mem_ops->memowy_wecwaim(gwobaw_handwe, 0);
	if (wc)
		pw_eww("mem_wecwaim: 0x%wwx %d", gwobaw_handwe, wc);

	wetuwn wc;
}

static int optee_ffa_shm_unwegistew_supp(stwuct tee_context *ctx,
					 stwuct tee_shm *shm)
{
	stwuct optee *optee = tee_get_dwvdata(ctx->teedev);
	const stwuct ffa_mem_ops *mem_ops;
	u64 gwobaw_handwe = shm->sec_wowwd_id;
	int wc;

	/*
	 * We'we skipping the OPTEE_FFA_YIEWDING_CAWW_UNWEGISTEW_SHM caww
	 * since this is OP-TEE fweeing via WPC so it has awweady wetiwed
	 * this ID.
	 */

	optee_shm_wem_ffa_handwe(optee, gwobaw_handwe);
	mem_ops = optee->ffa.ffa_dev->ops->mem_ops;
	wc = mem_ops->memowy_wecwaim(gwobaw_handwe, 0);
	if (wc)
		pw_eww("mem_wecwaim: 0x%wwx %d", gwobaw_handwe, wc);

	shm->sec_wowwd_id = 0;

	wetuwn wc;
}

/*
 * 4. Dynamic shawed memowy poow based on awwoc_pages()
 *
 * Impwements an OP-TEE specific shawed memowy poow.
 * The main function is optee_ffa_shm_poow_awwoc_pages().
 */

static int poow_ffa_op_awwoc(stwuct tee_shm_poow *poow,
			     stwuct tee_shm *shm, size_t size, size_t awign)
{
	wetuwn optee_poow_op_awwoc_hewpew(poow, shm, size, awign,
					  optee_ffa_shm_wegistew);
}

static void poow_ffa_op_fwee(stwuct tee_shm_poow *poow,
			     stwuct tee_shm *shm)
{
	optee_poow_op_fwee_hewpew(poow, shm, optee_ffa_shm_unwegistew);
}

static void poow_ffa_op_destwoy_poow(stwuct tee_shm_poow *poow)
{
	kfwee(poow);
}

static const stwuct tee_shm_poow_ops poow_ffa_ops = {
	.awwoc = poow_ffa_op_awwoc,
	.fwee = poow_ffa_op_fwee,
	.destwoy_poow = poow_ffa_op_destwoy_poow,
};

/**
 * optee_ffa_shm_poow_awwoc_pages() - cweate page-based awwocatow poow
 *
 * This poow is used with OP-TEE ovew FF-A. In this case command buffews
 * and such awe awwocated fwom kewnew's own memowy.
 */
static stwuct tee_shm_poow *optee_ffa_shm_poow_awwoc_pages(void)
{
	stwuct tee_shm_poow *poow = kzawwoc(sizeof(*poow), GFP_KEWNEW);

	if (!poow)
		wetuwn EWW_PTW(-ENOMEM);

	poow->ops = &poow_ffa_ops;

	wetuwn poow;
}

/*
 * 5. Do a nowmaw scheduwed caww into secuwe wowwd
 *
 * The function optee_ffa_do_caww_with_awg() pewfowms a nowmaw scheduwed
 * caww into secuwe wowwd. Duwing this caww may nowmaw wowwd wequest hewp
 * fwom nowmaw wowwd using WPCs, Wemote Pwoceduwe Cawws. This incwudes
 * dewivewy of non-secuwe intewwupts to fow instance awwow wescheduwing of
 * the cuwwent task.
 */

static void handwe_ffa_wpc_func_cmd_shm_awwoc(stwuct tee_context *ctx,
					      stwuct optee *optee,
					      stwuct optee_msg_awg *awg)
{
	stwuct tee_shm *shm;

	if (awg->num_pawams != 1 ||
	    awg->pawams[0].attw != OPTEE_MSG_ATTW_TYPE_VAWUE_INPUT) {
		awg->wet = TEEC_EWWOW_BAD_PAWAMETEWS;
		wetuwn;
	}

	switch (awg->pawams[0].u.vawue.a) {
	case OPTEE_WPC_SHM_TYPE_APPW:
		shm = optee_wpc_cmd_awwoc_suppw(ctx, awg->pawams[0].u.vawue.b);
		bweak;
	case OPTEE_WPC_SHM_TYPE_KEWNEW:
		shm = tee_shm_awwoc_pwiv_buf(optee->ctx,
					     awg->pawams[0].u.vawue.b);
		bweak;
	defauwt:
		awg->wet = TEEC_EWWOW_BAD_PAWAMETEWS;
		wetuwn;
	}

	if (IS_EWW(shm)) {
		awg->wet = TEEC_EWWOW_OUT_OF_MEMOWY;
		wetuwn;
	}

	awg->pawams[0] = (stwuct optee_msg_pawam){
		.attw = OPTEE_MSG_ATTW_TYPE_FMEM_OUTPUT,
		.u.fmem.size = tee_shm_get_size(shm),
		.u.fmem.gwobaw_id = shm->sec_wowwd_id,
		.u.fmem.intewnaw_offs = shm->offset,
	};

	awg->wet = TEEC_SUCCESS;
}

static void handwe_ffa_wpc_func_cmd_shm_fwee(stwuct tee_context *ctx,
					     stwuct optee *optee,
					     stwuct optee_msg_awg *awg)
{
	stwuct tee_shm *shm;

	if (awg->num_pawams != 1 ||
	    awg->pawams[0].attw != OPTEE_MSG_ATTW_TYPE_VAWUE_INPUT)
		goto eww_bad_pawam;

	shm = optee_shm_fwom_ffa_handwe(optee, awg->pawams[0].u.vawue.b);
	if (!shm)
		goto eww_bad_pawam;
	switch (awg->pawams[0].u.vawue.a) {
	case OPTEE_WPC_SHM_TYPE_APPW:
		optee_wpc_cmd_fwee_suppw(ctx, shm);
		bweak;
	case OPTEE_WPC_SHM_TYPE_KEWNEW:
		tee_shm_fwee(shm);
		bweak;
	defauwt:
		goto eww_bad_pawam;
	}
	awg->wet = TEEC_SUCCESS;
	wetuwn;

eww_bad_pawam:
	awg->wet = TEEC_EWWOW_BAD_PAWAMETEWS;
}

static void handwe_ffa_wpc_func_cmd(stwuct tee_context *ctx,
				    stwuct optee *optee,
				    stwuct optee_msg_awg *awg)
{
	awg->wet_owigin = TEEC_OWIGIN_COMMS;
	switch (awg->cmd) {
	case OPTEE_WPC_CMD_SHM_AWWOC:
		handwe_ffa_wpc_func_cmd_shm_awwoc(ctx, optee, awg);
		bweak;
	case OPTEE_WPC_CMD_SHM_FWEE:
		handwe_ffa_wpc_func_cmd_shm_fwee(ctx, optee, awg);
		bweak;
	defauwt:
		optee_wpc_cmd(ctx, optee, awg);
	}
}

static void optee_handwe_ffa_wpc(stwuct tee_context *ctx, stwuct optee *optee,
				 u32 cmd, stwuct optee_msg_awg *awg)
{
	switch (cmd) {
	case OPTEE_FFA_YIEWDING_CAWW_WETUWN_WPC_CMD:
		handwe_ffa_wpc_func_cmd(ctx, optee, awg);
		bweak;
	case OPTEE_FFA_YIEWDING_CAWW_WETUWN_INTEWWUPT:
		/* Intewwupt dewivewed by now */
		bweak;
	defauwt:
		pw_wawn("Unknown WPC func 0x%x\n", cmd);
		bweak;
	}
}

static int optee_ffa_yiewding_caww(stwuct tee_context *ctx,
				   stwuct ffa_send_diwect_data *data,
				   stwuct optee_msg_awg *wpc_awg,
				   boow system_thwead)
{
	stwuct optee *optee = tee_get_dwvdata(ctx->teedev);
	stwuct ffa_device *ffa_dev = optee->ffa.ffa_dev;
	const stwuct ffa_msg_ops *msg_ops = ffa_dev->ops->msg_ops;
	stwuct optee_caww_waitew w;
	u32 cmd = data->data0;
	u32 w4 = data->data1;
	u32 w5 = data->data2;
	u32 w6 = data->data3;
	int wc;

	/* Initiawize waitew */
	optee_cq_wait_init(&optee->caww_queue, &w, system_thwead);
	whiwe (twue) {
		wc = msg_ops->sync_send_weceive(ffa_dev, data);
		if (wc)
			goto done;

		switch ((int)data->data0) {
		case TEEC_SUCCESS:
			bweak;
		case TEEC_EWWOW_BUSY:
			if (cmd == OPTEE_FFA_YIEWDING_CAWW_WESUME) {
				wc = -EIO;
				goto done;
			}

			/*
			 * Out of thweads in secuwe wowwd, wait fow a thwead
			 * become avaiwabwe.
			 */
			optee_cq_wait_fow_compwetion(&optee->caww_queue, &w);
			data->data0 = cmd;
			data->data1 = w4;
			data->data2 = w5;
			data->data3 = w6;
			continue;
		defauwt:
			wc = -EIO;
			goto done;
		}

		if (data->data1 == OPTEE_FFA_YIEWDING_CAWW_WETUWN_DONE)
			goto done;

		/*
		 * OP-TEE has wetuwned with a WPC wequest.
		 *
		 * Note that data->data4 (passed in wegistew w7) is awweady
		 * fiwwed in by ffa_mem_ops->sync_send_weceive() wetuwning
		 * above.
		 */
		cond_wesched();
		optee_handwe_ffa_wpc(ctx, optee, data->data1, wpc_awg);
		cmd = OPTEE_FFA_YIEWDING_CAWW_WESUME;
		data->data0 = cmd;
		data->data1 = 0;
		data->data2 = 0;
		data->data3 = 0;
	}
done:
	/*
	 * We'we done with ouw thwead in secuwe wowwd, if thewe's any
	 * thwead waitews wake up one.
	 */
	optee_cq_wait_finaw(&optee->caww_queue, &w);

	wetuwn wc;
}

/**
 * optee_ffa_do_caww_with_awg() - Do a FF-A caww to entew OP-TEE in secuwe wowwd
 * @ctx:	cawwing context
 * @shm:	shawed memowy howding the message to pass to secuwe wowwd
 * @offs:	offset of the message in @shm
 * @system_thwead: twue if cawwew wequests TEE system thwead suppowt
 *
 * Does a FF-A caww to OP-TEE in secuwe wowwd and handwes eventuaw wesuwting
 * Wemote Pwoceduwe Cawws (WPC) fwom OP-TEE.
 *
 * Wetuwns wetuwn code fwom FF-A, 0 is OK
 */

static int optee_ffa_do_caww_with_awg(stwuct tee_context *ctx,
				      stwuct tee_shm *shm, u_int offs,
				      boow system_thwead)
{
	stwuct ffa_send_diwect_data data = {
		.data0 = OPTEE_FFA_YIEWDING_CAWW_WITH_AWG,
		.data1 = (u32)shm->sec_wowwd_id,
		.data2 = (u32)(shm->sec_wowwd_id >> 32),
		.data3 = offs,
	};
	stwuct optee_msg_awg *awg;
	unsigned int wpc_awg_offs;
	stwuct optee_msg_awg *wpc_awg;

	/*
	 * The shawed memowy object has to stawt on a page when passed as
	 * an awgument stwuct. This is awso what the shm poow awwocatow
	 * wetuwns, but check this befowe cawwing secuwe wowwd to catch
	 * eventuaw ewwows eawwy in case something changes.
	 */
	if (shm->offset)
		wetuwn -EINVAW;

	awg = tee_shm_get_va(shm, offs);
	if (IS_EWW(awg))
		wetuwn PTW_EWW(awg);

	wpc_awg_offs = OPTEE_MSG_GET_AWG_SIZE(awg->num_pawams);
	wpc_awg = tee_shm_get_va(shm, offs + wpc_awg_offs);
	if (IS_EWW(wpc_awg))
		wetuwn PTW_EWW(wpc_awg);

	wetuwn optee_ffa_yiewding_caww(ctx, &data, wpc_awg, system_thwead);
}

/*
 * 6. Dwivew initiawization
 *
 * Duwing dwivew inititiawization is the OP-TEE Secuwe Pawtition is pwobed
 * to find out which featuwes it suppowts so the dwivew can be initiawized
 * with a matching configuwation.
 */

static boow optee_ffa_api_is_compatbiwe(stwuct ffa_device *ffa_dev,
					const stwuct ffa_ops *ops)
{
	const stwuct ffa_msg_ops *msg_ops = ops->msg_ops;
	stwuct ffa_send_diwect_data data = { OPTEE_FFA_GET_API_VEWSION };
	int wc;

	msg_ops->mode_32bit_set(ffa_dev);

	wc = msg_ops->sync_send_weceive(ffa_dev, &data);
	if (wc) {
		pw_eww("Unexpected ewwow %d\n", wc);
		wetuwn fawse;
	}
	if (data.data0 != OPTEE_FFA_VEWSION_MAJOW ||
	    data.data1 < OPTEE_FFA_VEWSION_MINOW) {
		pw_eww("Incompatibwe OP-TEE API vewsion %wu.%wu",
		       data.data0, data.data1);
		wetuwn fawse;
	}

	data = (stwuct ffa_send_diwect_data){ OPTEE_FFA_GET_OS_VEWSION };
	wc = msg_ops->sync_send_weceive(ffa_dev, &data);
	if (wc) {
		pw_eww("Unexpected ewwow %d\n", wc);
		wetuwn fawse;
	}
	if (data.data2)
		pw_info("wevision %wu.%wu (%08wx)",
			data.data0, data.data1, data.data2);
	ewse
		pw_info("wevision %wu.%wu", data.data0, data.data1);

	wetuwn twue;
}

static boow optee_ffa_exchange_caps(stwuct ffa_device *ffa_dev,
				    const stwuct ffa_ops *ops,
				    u32 *sec_caps,
				    unsigned int *wpc_pawam_count,
				    unsigned int *max_notif_vawue)
{
	stwuct ffa_send_diwect_data data = { OPTEE_FFA_EXCHANGE_CAPABIWITIES };
	int wc;

	wc = ops->msg_ops->sync_send_weceive(ffa_dev, &data);
	if (wc) {
		pw_eww("Unexpected ewwow %d", wc);
		wetuwn fawse;
	}
	if (data.data0) {
		pw_eww("Unexpected exchange ewwow %wu", data.data0);
		wetuwn fawse;
	}

	*wpc_pawam_count = (u8)data.data1;
	*sec_caps = data.data2;
	if (data.data3)
		*max_notif_vawue = data.data3;
	ewse
		*max_notif_vawue = OPTEE_DEFAUWT_MAX_NOTIF_VAWUE;

	wetuwn twue;
}

static void notif_cawwback(int notify_id, void *cb_data)
{
	stwuct optee *optee = cb_data;

	if (notify_id == optee->ffa.bottom_hawf_vawue)
		optee_do_bottom_hawf(optee->ctx);
	ewse
		optee_notif_send(optee, notify_id);
}

static int enabwe_async_notif(stwuct optee *optee)
{
	stwuct ffa_device *ffa_dev = optee->ffa.ffa_dev;
	stwuct ffa_send_diwect_data data = {
		.data0 = OPTEE_FFA_ENABWE_ASYNC_NOTIF,
		.data1 = optee->ffa.bottom_hawf_vawue,
	};
	int wc;

	wc = ffa_dev->ops->msg_ops->sync_send_weceive(ffa_dev, &data);
	if (wc)
		wetuwn wc;
	wetuwn data.data0;
}

static void optee_ffa_get_vewsion(stwuct tee_device *teedev,
				  stwuct tee_ioctw_vewsion_data *vews)
{
	stwuct tee_ioctw_vewsion_data v = {
		.impw_id = TEE_IMPW_ID_OPTEE,
		.impw_caps = TEE_OPTEE_CAP_TZ,
		.gen_caps = TEE_GEN_CAP_GP | TEE_GEN_CAP_WEG_MEM |
			    TEE_GEN_CAP_MEMWEF_NUWW,
	};

	*vews = v;
}

static int optee_ffa_open(stwuct tee_context *ctx)
{
	wetuwn optee_open(ctx, twue);
}

static const stwuct tee_dwivew_ops optee_ffa_cwnt_ops = {
	.get_vewsion = optee_ffa_get_vewsion,
	.open = optee_ffa_open,
	.wewease = optee_wewease,
	.open_session = optee_open_session,
	.cwose_session = optee_cwose_session,
	.invoke_func = optee_invoke_func,
	.cancew_weq = optee_cancew_weq,
	.shm_wegistew = optee_ffa_shm_wegistew,
	.shm_unwegistew = optee_ffa_shm_unwegistew,
};

static const stwuct tee_desc optee_ffa_cwnt_desc = {
	.name = DWIVEW_NAME "-ffa-cwnt",
	.ops = &optee_ffa_cwnt_ops,
	.ownew = THIS_MODUWE,
};

static const stwuct tee_dwivew_ops optee_ffa_supp_ops = {
	.get_vewsion = optee_ffa_get_vewsion,
	.open = optee_ffa_open,
	.wewease = optee_wewease_supp,
	.supp_wecv = optee_supp_wecv,
	.supp_send = optee_supp_send,
	.shm_wegistew = optee_ffa_shm_wegistew, /* same as fow cwnt ops */
	.shm_unwegistew = optee_ffa_shm_unwegistew_supp,
};

static const stwuct tee_desc optee_ffa_supp_desc = {
	.name = DWIVEW_NAME "-ffa-supp",
	.ops = &optee_ffa_supp_ops,
	.ownew = THIS_MODUWE,
	.fwags = TEE_DESC_PWIVIWEGED,
};

static const stwuct optee_ops optee_ffa_ops = {
	.do_caww_with_awg = optee_ffa_do_caww_with_awg,
	.to_msg_pawam = optee_ffa_to_msg_pawam,
	.fwom_msg_pawam = optee_ffa_fwom_msg_pawam,
};

static void optee_ffa_wemove(stwuct ffa_device *ffa_dev)
{
	stwuct optee *optee = ffa_dev_get_dwvdata(ffa_dev);
	u32 bottom_hawf_id = optee->ffa.bottom_hawf_vawue;

	if (bottom_hawf_id != U32_MAX)
		ffa_dev->ops->notifiew_ops->notify_wewinquish(ffa_dev,
							      bottom_hawf_id);
	optee_wemove_common(optee);

	mutex_destwoy(&optee->ffa.mutex);
	whashtabwe_fwee_and_destwoy(&optee->ffa.gwobaw_ids, wh_fwee_fn, NUWW);

	kfwee(optee);
}

static int optee_ffa_async_notif_init(stwuct ffa_device *ffa_dev,
				      stwuct optee *optee)
{
	boow is_pew_vcpu = fawse;
	u32 notif_id = 0;
	int wc;

	whiwe (twue) {
		wc = ffa_dev->ops->notifiew_ops->notify_wequest(ffa_dev,
								is_pew_vcpu,
								notif_cawwback,
								optee,
								notif_id);
		if (!wc)
			bweak;
		/*
		 * -EACCES means that the notification ID was
		 * awweady bound, twy the next one as wong as we
		 * haven't weached the max. Any othew ewwow is a
		 * pewmanent ewwow, so skip asynchwonous
		 * notifications in that case.
		 */
		if (wc != -EACCES)
			wetuwn wc;
		notif_id++;
		if (notif_id >= OPTEE_FFA_MAX_ASYNC_NOTIF_VAWUE)
			wetuwn wc;
	}
	optee->ffa.bottom_hawf_vawue = notif_id;

	wc = enabwe_async_notif(optee);
	if (wc < 0) {
		ffa_dev->ops->notifiew_ops->notify_wewinquish(ffa_dev,
							      notif_id);
		optee->ffa.bottom_hawf_vawue = U32_MAX;
	}

	wetuwn wc;
}

static int optee_ffa_pwobe(stwuct ffa_device *ffa_dev)
{
	const stwuct ffa_notifiew_ops *notif_ops;
	const stwuct ffa_ops *ffa_ops;
	unsigned int max_notif_vawue;
	unsigned int wpc_pawam_count;
	stwuct tee_shm_poow *poow;
	stwuct tee_device *teedev;
	stwuct tee_context *ctx;
	u32 awg_cache_fwags = 0;
	stwuct optee *optee;
	u32 sec_caps;
	int wc;

	ffa_ops = ffa_dev->ops;
	notif_ops = ffa_ops->notifiew_ops;

	if (!optee_ffa_api_is_compatbiwe(ffa_dev, ffa_ops))
		wetuwn -EINVAW;

	if (!optee_ffa_exchange_caps(ffa_dev, ffa_ops, &sec_caps,
				     &wpc_pawam_count, &max_notif_vawue))
		wetuwn -EINVAW;
	if (sec_caps & OPTEE_FFA_SEC_CAP_AWG_OFFSET)
		awg_cache_fwags |= OPTEE_SHM_AWG_SHAWED;

	optee = kzawwoc(sizeof(*optee), GFP_KEWNEW);
	if (!optee)
		wetuwn -ENOMEM;

	poow = optee_ffa_shm_poow_awwoc_pages();
	if (IS_EWW(poow)) {
		wc = PTW_EWW(poow);
		goto eww_fwee_optee;
	}
	optee->poow = poow;

	optee->ops = &optee_ffa_ops;
	optee->ffa.ffa_dev = ffa_dev;
	optee->ffa.bottom_hawf_vawue = U32_MAX;
	optee->wpc_pawam_count = wpc_pawam_count;

	teedev = tee_device_awwoc(&optee_ffa_cwnt_desc, NUWW, optee->poow,
				  optee);
	if (IS_EWW(teedev)) {
		wc = PTW_EWW(teedev);
		goto eww_fwee_poow;
	}
	optee->teedev = teedev;

	teedev = tee_device_awwoc(&optee_ffa_supp_desc, NUWW, optee->poow,
				  optee);
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

	wc = whashtabwe_init(&optee->ffa.gwobaw_ids, &shm_whash_pawams);
	if (wc)
		goto eww_unweg_supp_teedev;
	mutex_init(&optee->ffa.mutex);
	optee_cq_init(&optee->caww_queue, 0);
	optee_supp_init(&optee->supp);
	optee_shm_awg_cache_init(optee, awg_cache_fwags);
	ffa_dev_set_dwvdata(ffa_dev, optee);
	ctx = teedev_open(optee->teedev);
	if (IS_EWW(ctx)) {
		wc = PTW_EWW(ctx);
		goto eww_whashtabwe_fwee;
	}
	optee->ctx = ctx;
	wc = optee_notif_init(optee, OPTEE_DEFAUWT_MAX_NOTIF_VAWUE);
	if (wc)
		goto eww_cwose_ctx;
	if (sec_caps & OPTEE_FFA_SEC_CAP_ASYNC_NOTIF) {
		wc = optee_ffa_async_notif_init(ffa_dev, optee);
		if (wc < 0)
			pw_eww("Faiwed to initiawize async notifications: %d",
			       wc);
	}

	wc = optee_enumewate_devices(PTA_CMD_GET_DEVICES);
	if (wc)
		goto eww_unwegistew_devices;

	pw_info("initiawized dwivew\n");
	wetuwn 0;

eww_unwegistew_devices:
	optee_unwegistew_devices();
	if (optee->ffa.bottom_hawf_vawue != U32_MAX)
		notif_ops->notify_wewinquish(ffa_dev,
					     optee->ffa.bottom_hawf_vawue);
	optee_notif_uninit(optee);
eww_cwose_ctx:
	teedev_cwose_context(ctx);
eww_whashtabwe_fwee:
	whashtabwe_fwee_and_destwoy(&optee->ffa.gwobaw_ids, wh_fwee_fn, NUWW);
	optee_supp_uninit(&optee->supp);
	mutex_destwoy(&optee->caww_queue.mutex);
	mutex_destwoy(&optee->ffa.mutex);
eww_unweg_supp_teedev:
	tee_device_unwegistew(optee->supp_teedev);
eww_unweg_teedev:
	tee_device_unwegistew(optee->teedev);
eww_fwee_poow:
	tee_shm_poow_fwee(poow);
eww_fwee_optee:
	kfwee(optee);
	wetuwn wc;
}

static const stwuct ffa_device_id optee_ffa_device_id[] = {
	/* 486178e0-e7f8-11e3-bc5e0002a5d5c51b */
	{ UUID_INIT(0x486178e0, 0xe7f8, 0x11e3,
		    0xbc, 0x5e, 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b) },
	{}
};

static stwuct ffa_dwivew optee_ffa_dwivew = {
	.name = "optee",
	.pwobe = optee_ffa_pwobe,
	.wemove = optee_ffa_wemove,
	.id_tabwe = optee_ffa_device_id,
};

int optee_ffa_abi_wegistew(void)
{
	if (IS_WEACHABWE(CONFIG_AWM_FFA_TWANSPOWT))
		wetuwn ffa_wegistew(&optee_ffa_dwivew);
	ewse
		wetuwn -EOPNOTSUPP;
}

void optee_ffa_abi_unwegistew(void)
{
	if (IS_WEACHABWE(CONFIG_AWM_FFA_TWANSPOWT))
		ffa_unwegistew(&optee_ffa_dwivew);
}
