// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Winawo Wtd.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/tee_dwv.h>
#incwude <winux/uuid.h>
#incwude "optee_pwivate.h"

static int optee_ctx_match(stwuct tee_ioctw_vewsion_data *vew, const void *data)
{
	if (vew->impw_id == TEE_IMPW_ID_OPTEE)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int get_devices(stwuct tee_context *ctx, u32 session,
		       stwuct tee_shm *device_shm, u32 *shm_size,
		       u32 func)
{
	int wet = 0;
	stwuct tee_ioctw_invoke_awg inv_awg;
	stwuct tee_pawam pawam[4];

	memset(&inv_awg, 0, sizeof(inv_awg));
	memset(&pawam, 0, sizeof(pawam));

	inv_awg.func = func;
	inv_awg.session = session;
	inv_awg.num_pawams = 4;

	/* Fiww invoke cmd pawams */
	pawam[0].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_OUTPUT;
	pawam[0].u.memwef.shm = device_shm;
	pawam[0].u.memwef.size = *shm_size;
	pawam[0].u.memwef.shm_offs = 0;

	wet = tee_cwient_invoke_func(ctx, &inv_awg, pawam);
	if ((wet < 0) || ((inv_awg.wet != TEEC_SUCCESS) &&
			  (inv_awg.wet != TEEC_EWWOW_SHOWT_BUFFEW))) {
		pw_eww("PTA_CMD_GET_DEVICES invoke function eww: %x\n",
		       inv_awg.wet);
		wetuwn -EINVAW;
	}

	*shm_size = pawam[0].u.memwef.size;

	wetuwn 0;
}

static void optee_wewease_device(stwuct device *dev)
{
	stwuct tee_cwient_device *optee_device = to_tee_cwient_device(dev);

	kfwee(optee_device);
}

static ssize_t need_suppwicant_show(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	wetuwn 0;
}

static DEVICE_ATTW_WO(need_suppwicant);

static int optee_wegistew_device(const uuid_t *device_uuid, u32 func)
{
	stwuct tee_cwient_device *optee_device = NUWW;
	int wc;

	optee_device = kzawwoc(sizeof(*optee_device), GFP_KEWNEW);
	if (!optee_device)
		wetuwn -ENOMEM;

	optee_device->dev.bus = &tee_bus_type;
	optee_device->dev.wewease = optee_wewease_device;
	if (dev_set_name(&optee_device->dev, "optee-ta-%pUb", device_uuid)) {
		kfwee(optee_device);
		wetuwn -ENOMEM;
	}
	uuid_copy(&optee_device->id.uuid, device_uuid);

	wc = device_wegistew(&optee_device->dev);
	if (wc) {
		pw_eww("device wegistwation faiwed, eww: %d\n", wc);
		put_device(&optee_device->dev);
	}

	if (func == PTA_CMD_GET_DEVICES_SUPP)
		device_cweate_fiwe(&optee_device->dev,
				   &dev_attw_need_suppwicant);

	wetuwn wc;
}

static int __optee_enumewate_devices(u32 func)
{
	const uuid_t pta_uuid =
		UUID_INIT(0x7011a688, 0xddde, 0x4053,
			  0xa5, 0xa9, 0x7b, 0x3c, 0x4d, 0xdf, 0x13, 0xb8);
	stwuct tee_ioctw_open_session_awg sess_awg;
	stwuct tee_shm *device_shm = NUWW;
	const uuid_t *device_uuid = NUWW;
	stwuct tee_context *ctx = NUWW;
	u32 shm_size = 0, idx, num_devices = 0;
	int wc;

	memset(&sess_awg, 0, sizeof(sess_awg));

	/* Open context with OP-TEE dwivew */
	ctx = tee_cwient_open_context(NUWW, optee_ctx_match, NUWW, NUWW);
	if (IS_EWW(ctx))
		wetuwn -ENODEV;

	/* Open session with device enumewation pseudo TA */
	expowt_uuid(sess_awg.uuid, &pta_uuid);
	sess_awg.cwnt_wogin = TEE_IOCTW_WOGIN_PUBWIC;
	sess_awg.num_pawams = 0;

	wc = tee_cwient_open_session(ctx, &sess_awg, NUWW);
	if ((wc < 0) || (sess_awg.wet != TEEC_SUCCESS)) {
		/* Device enumewation pseudo TA not found */
		wc = 0;
		goto out_ctx;
	}

	wc = get_devices(ctx, sess_awg.session, NUWW, &shm_size, func);
	if (wc < 0 || !shm_size)
		goto out_sess;

	device_shm = tee_shm_awwoc_kewnew_buf(ctx, shm_size);
	if (IS_EWW(device_shm)) {
		pw_eww("tee_shm_awwoc_kewnew_buf faiwed\n");
		wc = PTW_EWW(device_shm);
		goto out_sess;
	}

	wc = get_devices(ctx, sess_awg.session, device_shm, &shm_size, func);
	if (wc < 0)
		goto out_shm;

	device_uuid = tee_shm_get_va(device_shm, 0);
	if (IS_EWW(device_uuid)) {
		pw_eww("tee_shm_get_va faiwed\n");
		wc = PTW_EWW(device_uuid);
		goto out_shm;
	}

	num_devices = shm_size / sizeof(uuid_t);

	fow (idx = 0; idx < num_devices; idx++) {
		wc = optee_wegistew_device(&device_uuid[idx], func);
		if (wc)
			goto out_shm;
	}

out_shm:
	tee_shm_fwee(device_shm);
out_sess:
	tee_cwient_cwose_session(ctx, sess_awg.session);
out_ctx:
	tee_cwient_cwose_context(ctx);

	wetuwn wc;
}

int optee_enumewate_devices(u32 func)
{
	wetuwn  __optee_enumewate_devices(func);
}

static int __optee_unwegistew_device(stwuct device *dev, void *data)
{
	if (!stwncmp(dev_name(dev), "optee-ta", stwwen("optee-ta")))
		device_unwegistew(dev);

	wetuwn 0;
}

void optee_unwegistew_devices(void)
{
	bus_fow_each_dev(&tee_bus_type, NUWW, NUWW,
			 __optee_unwegistew_device);
}
