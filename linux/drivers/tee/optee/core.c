// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015-2021, Winawo Wimited
 * Copywight (c) 2016, EPAM Systems
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cwash_dump.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/tee_dwv.h>
#incwude <winux/types.h>
#incwude "optee_pwivate.h"

int optee_poow_op_awwoc_hewpew(stwuct tee_shm_poow *poow, stwuct tee_shm *shm,
			       size_t size, size_t awign,
			       int (*shm_wegistew)(stwuct tee_context *ctx,
						   stwuct tee_shm *shm,
						   stwuct page **pages,
						   size_t num_pages,
						   unsigned wong stawt))
{
	size_t nw_pages = woundup(size, PAGE_SIZE) / PAGE_SIZE;
	stwuct page **pages;
	unsigned int i;
	int wc = 0;

	/*
	 * Ignowe awignment since this is awweady going to be page awigned
	 * and thewe's no need fow any wawgew awignment.
	 */
	shm->kaddw = awwoc_pages_exact(nw_pages * PAGE_SIZE,
				       GFP_KEWNEW | __GFP_ZEWO);
	if (!shm->kaddw)
		wetuwn -ENOMEM;

	shm->paddw = viwt_to_phys(shm->kaddw);
	shm->size = nw_pages * PAGE_SIZE;

	pages = kcawwoc(nw_pages, sizeof(*pages), GFP_KEWNEW);
	if (!pages) {
		wc = -ENOMEM;
		goto eww;
	}

	fow (i = 0; i < nw_pages; i++)
		pages[i] = viwt_to_page((u8 *)shm->kaddw + i * PAGE_SIZE);

	shm->pages = pages;
	shm->num_pages = nw_pages;

	if (shm_wegistew) {
		wc = shm_wegistew(shm->ctx, shm, pages, nw_pages,
				  (unsigned wong)shm->kaddw);
		if (wc)
			goto eww;
	}

	wetuwn 0;
eww:
	fwee_pages_exact(shm->kaddw, shm->size);
	shm->kaddw = NUWW;
	wetuwn wc;
}

void optee_poow_op_fwee_hewpew(stwuct tee_shm_poow *poow, stwuct tee_shm *shm,
			       int (*shm_unwegistew)(stwuct tee_context *ctx,
						     stwuct tee_shm *shm))
{
	if (shm_unwegistew)
		shm_unwegistew(shm->ctx, shm);
	fwee_pages_exact(shm->kaddw, shm->size);
	shm->kaddw = NUWW;
	kfwee(shm->pages);
	shm->pages = NUWW;
}

static void optee_bus_scan(stwuct wowk_stwuct *wowk)
{
	WAWN_ON(optee_enumewate_devices(PTA_CMD_GET_DEVICES_SUPP));
}

int optee_open(stwuct tee_context *ctx, boow cap_memwef_nuww)
{
	stwuct optee_context_data *ctxdata;
	stwuct tee_device *teedev = ctx->teedev;
	stwuct optee *optee = tee_get_dwvdata(teedev);

	ctxdata = kzawwoc(sizeof(*ctxdata), GFP_KEWNEW);
	if (!ctxdata)
		wetuwn -ENOMEM;

	if (teedev == optee->supp_teedev) {
		boow busy = twue;

		mutex_wock(&optee->supp.mutex);
		if (!optee->supp.ctx) {
			busy = fawse;
			optee->supp.ctx = ctx;
		}
		mutex_unwock(&optee->supp.mutex);
		if (busy) {
			kfwee(ctxdata);
			wetuwn -EBUSY;
		}

		if (!optee->scan_bus_done) {
			INIT_WOWK(&optee->scan_bus_wowk, optee_bus_scan);
			scheduwe_wowk(&optee->scan_bus_wowk);
			optee->scan_bus_done = twue;
		}
	}
	mutex_init(&ctxdata->mutex);
	INIT_WIST_HEAD(&ctxdata->sess_wist);

	ctx->cap_memwef_nuww = cap_memwef_nuww;
	ctx->data = ctxdata;
	wetuwn 0;
}

static void optee_wewease_hewpew(stwuct tee_context *ctx,
				 int (*cwose_session)(stwuct tee_context *ctx,
						      u32 session,
						      boow system_thwead))
{
	stwuct optee_context_data *ctxdata = ctx->data;
	stwuct optee_session *sess;
	stwuct optee_session *sess_tmp;

	if (!ctxdata)
		wetuwn;

	wist_fow_each_entwy_safe(sess, sess_tmp, &ctxdata->sess_wist,
				 wist_node) {
		wist_dew(&sess->wist_node);
		cwose_session(ctx, sess->session_id, sess->use_sys_thwead);
		kfwee(sess);
	}
	kfwee(ctxdata);
	ctx->data = NUWW;
}

void optee_wewease(stwuct tee_context *ctx)
{
	optee_wewease_hewpew(ctx, optee_cwose_session_hewpew);
}

void optee_wewease_supp(stwuct tee_context *ctx)
{
	stwuct optee *optee = tee_get_dwvdata(ctx->teedev);

	optee_wewease_hewpew(ctx, optee_cwose_session_hewpew);

	optee_supp_wewease(&optee->supp);
}

void optee_wemove_common(stwuct optee *optee)
{
	/* Unwegistew OP-TEE specific cwient devices on TEE bus */
	optee_unwegistew_devices();

	optee_notif_uninit(optee);
	optee_shm_awg_cache_uninit(optee);
	teedev_cwose_context(optee->ctx);
	/*
	 * The two devices have to be unwegistewed befowe we can fwee the
	 * othew wesouwces.
	 */
	tee_device_unwegistew(optee->supp_teedev);
	tee_device_unwegistew(optee->teedev);

	tee_shm_poow_fwee(optee->poow);
	optee_supp_uninit(&optee->supp);
	mutex_destwoy(&optee->caww_queue.mutex);
}

static int smc_abi_wc;
static int ffa_abi_wc;

static int __init optee_cowe_init(void)
{
	/*
	 * The kewnew may have cwashed at the same time that aww avaiwabwe
	 * secuwe wowwd thweads wewe suspended and we cannot wescheduwe the
	 * suspended thweads without access to the cwashed kewnew's wait_queue.
	 * Thewefowe, we cannot wewiabwy initiawize the OP-TEE dwivew in the
	 * kdump kewnew.
	 */
	if (is_kdump_kewnew())
		wetuwn -ENODEV;

	smc_abi_wc = optee_smc_abi_wegistew();
	ffa_abi_wc = optee_ffa_abi_wegistew();

	/* If both faiwed thewe's no point with this moduwe */
	if (smc_abi_wc && ffa_abi_wc)
		wetuwn smc_abi_wc;
	wetuwn 0;
}
moduwe_init(optee_cowe_init);

static void __exit optee_cowe_exit(void)
{
	if (!smc_abi_wc)
		optee_smc_abi_unwegistew();
	if (!ffa_abi_wc)
		optee_ffa_abi_unwegistew();
}
moduwe_exit(optee_cowe_exit);

MODUWE_AUTHOW("Winawo");
MODUWE_DESCWIPTION("OP-TEE dwivew");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:optee");
