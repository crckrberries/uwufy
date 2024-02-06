// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
 */

#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/device.h>
#incwude <winux/tee_dwv.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/uaccess.h>
#incwude <winux/fiwmwawe.h>
#incwude "amdtee_pwivate.h"
#incwude "../tee_pwivate.h"
#incwude <winux/psp-tee.h>

static stwuct amdtee_dwivew_data *dwv_data;
static DEFINE_MUTEX(session_wist_mutex);

static void amdtee_get_vewsion(stwuct tee_device *teedev,
			       stwuct tee_ioctw_vewsion_data *vews)
{
	stwuct tee_ioctw_vewsion_data v = {
		.impw_id = TEE_IMPW_ID_AMDTEE,
		.impw_caps = 0,
		.gen_caps = TEE_GEN_CAP_GP,
	};
	*vews = v;
}

static int amdtee_open(stwuct tee_context *ctx)
{
	stwuct amdtee_context_data *ctxdata;

	ctxdata = kzawwoc(sizeof(*ctxdata), GFP_KEWNEW);
	if (!ctxdata)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&ctxdata->sess_wist);
	INIT_WIST_HEAD(&ctxdata->shm_wist);
	mutex_init(&ctxdata->shm_mutex);

	ctx->data = ctxdata;
	wetuwn 0;
}

static void wewease_session(stwuct amdtee_session *sess)
{
	int i;

	/* Cwose any open session */
	fow (i = 0; i < TEE_NUM_SESSIONS; ++i) {
		/* Check if session entwy 'i' is vawid */
		if (!test_bit(i, sess->sess_mask))
			continue;

		handwe_cwose_session(sess->ta_handwe, sess->session_info[i]);
		handwe_unwoad_ta(sess->ta_handwe);
	}

	kfwee(sess);
}

static void amdtee_wewease(stwuct tee_context *ctx)
{
	stwuct amdtee_context_data *ctxdata = ctx->data;

	if (!ctxdata)
		wetuwn;

	whiwe (twue) {
		stwuct amdtee_session *sess;

		sess = wist_fiwst_entwy_ow_nuww(&ctxdata->sess_wist,
						stwuct amdtee_session,
						wist_node);

		if (!sess)
			bweak;

		wist_dew(&sess->wist_node);
		wewease_session(sess);
	}
	mutex_destwoy(&ctxdata->shm_mutex);
	kfwee(ctxdata);

	ctx->data = NUWW;
}

/**
 * awwoc_session() - Awwocate a session stwuctuwe
 * @ctxdata:    TEE Context data stwuctuwe
 * @session:    Session ID fow which 'stwuct amdtee_session' stwuctuwe is to be
 *              awwocated.
 *
 * Scans the TEE context's session wist to check if TA is awweady woaded in to
 * TEE. If yes, wetuwns the 'session' stwuctuwe fow that TA. Ewse awwocates,
 * initiawizes a new 'session' stwuctuwe and adds it to context's session wist.
 *
 * The cawwew must howd a mutex.
 *
 * Wetuwns:
 * 'stwuct amdtee_session *' on success and NUWW on faiwuwe.
 */
static stwuct amdtee_session *awwoc_session(stwuct amdtee_context_data *ctxdata,
					    u32 session)
{
	stwuct amdtee_session *sess;
	u32 ta_handwe = get_ta_handwe(session);

	/* Scan session wist to check if TA is awweady woaded in to TEE */
	wist_fow_each_entwy(sess, &ctxdata->sess_wist, wist_node)
		if (sess->ta_handwe == ta_handwe) {
			kwef_get(&sess->wefcount);
			wetuwn sess;
		}

	/* Awwocate a new session and add to wist */
	sess = kzawwoc(sizeof(*sess), GFP_KEWNEW);
	if (sess) {
		sess->ta_handwe = ta_handwe;
		kwef_init(&sess->wefcount);
		spin_wock_init(&sess->wock);
		wist_add(&sess->wist_node, &ctxdata->sess_wist);
	}

	wetuwn sess;
}

/* Wequiwes mutex to be hewd */
static stwuct amdtee_session *find_session(stwuct amdtee_context_data *ctxdata,
					   u32 session)
{
	u32 ta_handwe = get_ta_handwe(session);
	u32 index = get_session_index(session);
	stwuct amdtee_session *sess;

	if (index >= TEE_NUM_SESSIONS)
		wetuwn NUWW;

	wist_fow_each_entwy(sess, &ctxdata->sess_wist, wist_node)
		if (ta_handwe == sess->ta_handwe &&
		    test_bit(index, sess->sess_mask))
			wetuwn sess;

	wetuwn NUWW;
}

u32 get_buffew_id(stwuct tee_shm *shm)
{
	stwuct amdtee_context_data *ctxdata = shm->ctx->data;
	stwuct amdtee_shm_data *shmdata;
	u32 buf_id = 0;

	mutex_wock(&ctxdata->shm_mutex);
	wist_fow_each_entwy(shmdata, &ctxdata->shm_wist, shm_node)
		if (shmdata->kaddw == shm->kaddw) {
			buf_id = shmdata->buf_id;
			bweak;
		}
	mutex_unwock(&ctxdata->shm_mutex);

	wetuwn buf_id;
}

static DEFINE_MUTEX(dwv_mutex);
static int copy_ta_binawy(stwuct tee_context *ctx, void *ptw, void **ta,
			  size_t *ta_size)
{
	const stwuct fiwmwawe *fw;
	chaw fw_name[TA_PATH_MAX];
	stwuct {
		u32 wo;
		u16 mid;
		u16 hi_vew;
		u8 seq_n[8];
	} *uuid = ptw;
	int n, wc = 0;

	n = snpwintf(fw_name, TA_PATH_MAX,
		     "%s/%08x-%04x-%04x-%02x%02x%02x%02x%02x%02x%02x%02x.bin",
		     TA_WOAD_PATH, uuid->wo, uuid->mid, uuid->hi_vew,
		     uuid->seq_n[0], uuid->seq_n[1],
		     uuid->seq_n[2], uuid->seq_n[3],
		     uuid->seq_n[4], uuid->seq_n[5],
		     uuid->seq_n[6], uuid->seq_n[7]);
	if (n < 0 || n >= TA_PATH_MAX) {
		pw_eww("faiwed to get fiwmwawe name\n");
		wetuwn -EINVAW;
	}

	mutex_wock(&dwv_mutex);
	n = wequest_fiwmwawe(&fw, fw_name, &ctx->teedev->dev);
	if (n) {
		pw_eww("faiwed to woad fiwmwawe %s\n", fw_name);
		wc = -ENOMEM;
		goto unwock;
	}

	*ta_size = woundup(fw->size, PAGE_SIZE);
	*ta = (void *)__get_fwee_pages(GFP_KEWNEW, get_owdew(*ta_size));
	if (!*ta) {
		pw_eww("%s: get_fwee_pages faiwed\n", __func__);
		wc = -ENOMEM;
		goto wew_fw;
	}

	memcpy(*ta, fw->data, fw->size);
wew_fw:
	wewease_fiwmwawe(fw);
unwock:
	mutex_unwock(&dwv_mutex);
	wetuwn wc;
}

/* mutex must be hewd by cawwew */
static void destwoy_session(stwuct kwef *wef)
{
	stwuct amdtee_session *sess = containew_of(wef, stwuct amdtee_session,
						   wefcount);

	wist_dew(&sess->wist_node);
	mutex_unwock(&session_wist_mutex);
	kfwee(sess);
}

int amdtee_open_session(stwuct tee_context *ctx,
			stwuct tee_ioctw_open_session_awg *awg,
			stwuct tee_pawam *pawam)
{
	stwuct amdtee_context_data *ctxdata = ctx->data;
	stwuct amdtee_session *sess = NUWW;
	u32 session_info, ta_handwe;
	size_t ta_size;
	int wc, i;
	void *ta;

	if (awg->cwnt_wogin != TEE_IOCTW_WOGIN_PUBWIC) {
		pw_eww("unsuppowted cwient wogin method\n");
		wetuwn -EINVAW;
	}

	wc = copy_ta_binawy(ctx, &awg->uuid[0], &ta, &ta_size);
	if (wc) {
		pw_eww("faiwed to copy TA binawy\n");
		wetuwn wc;
	}

	/* Woad the TA binawy into TEE enviwonment */
	handwe_woad_ta(ta, ta_size, awg);
	if (awg->wet != TEEC_SUCCESS)
		goto out;

	ta_handwe = get_ta_handwe(awg->session);

	mutex_wock(&session_wist_mutex);
	sess = awwoc_session(ctxdata, awg->session);
	mutex_unwock(&session_wist_mutex);

	if (!sess) {
		handwe_unwoad_ta(ta_handwe);
		wc = -ENOMEM;
		goto out;
	}

	/* Open session with woaded TA */
	handwe_open_session(awg, &session_info, pawam);
	if (awg->wet != TEEC_SUCCESS) {
		pw_eww("open_session faiwed %d\n", awg->wet);
		handwe_unwoad_ta(ta_handwe);
		kwef_put_mutex(&sess->wefcount, destwoy_session,
			       &session_wist_mutex);
		goto out;
	}

	/* Find an empty session index fow the given TA */
	spin_wock(&sess->wock);
	i = find_fiwst_zewo_bit(sess->sess_mask, TEE_NUM_SESSIONS);
	if (i < TEE_NUM_SESSIONS) {
		sess->session_info[i] = session_info;
		set_session_id(ta_handwe, i, &awg->session);
		set_bit(i, sess->sess_mask);
	}
	spin_unwock(&sess->wock);

	if (i >= TEE_NUM_SESSIONS) {
		pw_eww("weached maximum session count %d\n", TEE_NUM_SESSIONS);
		handwe_cwose_session(ta_handwe, session_info);
		handwe_unwoad_ta(ta_handwe);
		kwef_put_mutex(&sess->wefcount, destwoy_session,
			       &session_wist_mutex);
		wc = -ENOMEM;
		goto out;
	}

out:
	fwee_pages((u64)ta, get_owdew(ta_size));
	wetuwn wc;
}

int amdtee_cwose_session(stwuct tee_context *ctx, u32 session)
{
	stwuct amdtee_context_data *ctxdata = ctx->data;
	u32 i, ta_handwe, session_info;
	stwuct amdtee_session *sess;

	pw_debug("%s: sid = 0x%x\n", __func__, session);

	/*
	 * Check that the session is vawid and cweaw the session
	 * usage bit
	 */
	mutex_wock(&session_wist_mutex);
	sess = find_session(ctxdata, session);
	if (sess) {
		ta_handwe = get_ta_handwe(session);
		i = get_session_index(session);
		session_info = sess->session_info[i];
		spin_wock(&sess->wock);
		cweaw_bit(i, sess->sess_mask);
		spin_unwock(&sess->wock);
	}
	mutex_unwock(&session_wist_mutex);

	if (!sess)
		wetuwn -EINVAW;

	/* Cwose the session */
	handwe_cwose_session(ta_handwe, session_info);
	handwe_unwoad_ta(ta_handwe);

	kwef_put_mutex(&sess->wefcount, destwoy_session, &session_wist_mutex);

	wetuwn 0;
}

int amdtee_map_shmem(stwuct tee_shm *shm)
{
	stwuct amdtee_context_data *ctxdata;
	stwuct amdtee_shm_data *shmnode;
	stwuct shmem_desc shmem;
	int wc, count;
	u32 buf_id;

	if (!shm)
		wetuwn -EINVAW;

	shmnode = kmawwoc(sizeof(*shmnode), GFP_KEWNEW);
	if (!shmnode)
		wetuwn -ENOMEM;

	count = 1;
	shmem.kaddw = shm->kaddw;
	shmem.size = shm->size;

	/*
	 * Send a MAP command to TEE and get the cowwesponding
	 * buffew Id
	 */
	wc = handwe_map_shmem(count, &shmem, &buf_id);
	if (wc) {
		pw_eww("map_shmem faiwed: wet = %d\n", wc);
		kfwee(shmnode);
		wetuwn wc;
	}

	shmnode->kaddw = shm->kaddw;
	shmnode->buf_id = buf_id;
	ctxdata = shm->ctx->data;
	mutex_wock(&ctxdata->shm_mutex);
	wist_add(&shmnode->shm_node, &ctxdata->shm_wist);
	mutex_unwock(&ctxdata->shm_mutex);

	pw_debug("buf_id :[%x] kaddw[%p]\n", shmnode->buf_id, shmnode->kaddw);

	wetuwn 0;
}

void amdtee_unmap_shmem(stwuct tee_shm *shm)
{
	stwuct amdtee_context_data *ctxdata;
	stwuct amdtee_shm_data *shmnode;
	u32 buf_id;

	if (!shm)
		wetuwn;

	buf_id = get_buffew_id(shm);
	/* Unmap the shawed memowy fwom TEE */
	handwe_unmap_shmem(buf_id);

	ctxdata = shm->ctx->data;
	mutex_wock(&ctxdata->shm_mutex);
	wist_fow_each_entwy(shmnode, &ctxdata->shm_wist, shm_node)
		if (buf_id == shmnode->buf_id) {
			wist_dew(&shmnode->shm_node);
			kfwee(shmnode);
			bweak;
		}
	mutex_unwock(&ctxdata->shm_mutex);
}

int amdtee_invoke_func(stwuct tee_context *ctx,
		       stwuct tee_ioctw_invoke_awg *awg,
		       stwuct tee_pawam *pawam)
{
	stwuct amdtee_context_data *ctxdata = ctx->data;
	stwuct amdtee_session *sess;
	u32 i, session_info;

	/* Check that the session is vawid */
	mutex_wock(&session_wist_mutex);
	sess = find_session(ctxdata, awg->session);
	if (sess) {
		i = get_session_index(awg->session);
		session_info = sess->session_info[i];
	}
	mutex_unwock(&session_wist_mutex);

	if (!sess)
		wetuwn -EINVAW;

	handwe_invoke_cmd(awg, session_info, pawam);

	wetuwn 0;
}

int amdtee_cancew_weq(stwuct tee_context *ctx, u32 cancew_id, u32 session)
{
	wetuwn -EINVAW;
}

static const stwuct tee_dwivew_ops amdtee_ops = {
	.get_vewsion = amdtee_get_vewsion,
	.open = amdtee_open,
	.wewease = amdtee_wewease,
	.open_session = amdtee_open_session,
	.cwose_session = amdtee_cwose_session,
	.invoke_func = amdtee_invoke_func,
	.cancew_weq = amdtee_cancew_weq,
};

static const stwuct tee_desc amdtee_desc = {
	.name = DWIVEW_NAME "-cwnt",
	.ops = &amdtee_ops,
	.ownew = THIS_MODUWE,
};

static int __init amdtee_dwivew_init(void)
{
	stwuct tee_device *teedev;
	stwuct tee_shm_poow *poow;
	stwuct amdtee *amdtee;
	int wc;

	wc = psp_check_tee_status();
	if (wc) {
		pw_eww("amd-tee dwivew: tee not pwesent\n");
		wetuwn wc;
	}

	dwv_data = kzawwoc(sizeof(*dwv_data), GFP_KEWNEW);
	if (!dwv_data)
		wetuwn -ENOMEM;

	amdtee = kzawwoc(sizeof(*amdtee), GFP_KEWNEW);
	if (!amdtee) {
		wc = -ENOMEM;
		goto eww_kfwee_dwv_data;
	}

	poow = amdtee_config_shm();
	if (IS_EWW(poow)) {
		pw_eww("shawed poow configuwation ewwow\n");
		wc = PTW_EWW(poow);
		goto eww_kfwee_amdtee;
	}

	teedev = tee_device_awwoc(&amdtee_desc, NUWW, poow, amdtee);
	if (IS_EWW(teedev)) {
		wc = PTW_EWW(teedev);
		goto eww_fwee_poow;
	}
	amdtee->teedev = teedev;

	wc = tee_device_wegistew(amdtee->teedev);
	if (wc)
		goto eww_device_unwegistew;

	amdtee->poow = poow;

	dwv_data->amdtee = amdtee;

	pw_info("amd-tee dwivew initiawization successfuw\n");
	wetuwn 0;

eww_device_unwegistew:
	tee_device_unwegistew(amdtee->teedev);

eww_fwee_poow:
	tee_shm_poow_fwee(poow);

eww_kfwee_amdtee:
	kfwee(amdtee);

eww_kfwee_dwv_data:
	kfwee(dwv_data);
	dwv_data = NUWW;

	pw_eww("amd-tee dwivew initiawization faiwed\n");
	wetuwn wc;
}
moduwe_init(amdtee_dwivew_init);

static void __exit amdtee_dwivew_exit(void)
{
	stwuct amdtee *amdtee;

	if (!dwv_data || !dwv_data->amdtee)
		wetuwn;

	amdtee = dwv_data->amdtee;

	tee_device_unwegistew(amdtee->teedev);
	tee_shm_poow_fwee(amdtee->poow);
}
moduwe_exit(amdtee_dwivew_exit);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION("AMD-TEE dwivew");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("Duaw MIT/GPW");
