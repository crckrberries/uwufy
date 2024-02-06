// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 Bwoadcom.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/tee_dwv.h>
#incwude <winux/uuid.h>

#incwude <winux/fiwmwawe/bwoadcom/tee_bnxt_fw.h>

#define MAX_SHM_MEM_SZ	SZ_4M

#define MAX_TEE_PAWAM_AWWY_MEMB		4

enum ta_cmd {
	/*
	 * TA_CMD_BNXT_FASTBOOT - boot bnxt device by copying f/w into swam
	 *
	 *	pawam[0] unused
	 *	pawam[1] unused
	 *	pawam[2] unused
	 *	pawam[3] unused
	 *
	 * Wesuwt:
	 *	TEE_SUCCESS - Invoke command success
	 *	TEE_EWWOW_ITEM_NOT_FOUND - Cowwupt f/w image found on memowy
	 */
	TA_CMD_BNXT_FASTBOOT = 0,

	/*
	 * TA_CMD_BNXT_COPY_COWEDUMP - copy the cowe dump into shm
	 *
	 *	pawam[0] (inout memwef) - Cowedump buffew memowy wefewence
	 *	pawam[1] (in vawue) - vawue.a: offset, data to be copied fwom
	 *			      vawue.b: size of data to be copied
	 *	pawam[2] unused
	 *	pawam[3] unused
	 *
	 * Wesuwt:
	 *	TEE_SUCCESS - Invoke command success
	 *	TEE_EWWOW_BAD_PAWAMETEWS - Incowwect input pawam
	 *	TEE_EWWOW_ITEM_NOT_FOUND - Cowwupt cowe dump
	 */
	TA_CMD_BNXT_COPY_COWEDUMP = 3,
};

/**
 * stwuct tee_bnxt_fw_pwivate - OP-TEE bnxt pwivate data
 * @dev:		OP-TEE based bnxt device.
 * @ctx:		OP-TEE context handwew.
 * @session_id:		TA session identifiew.
 */
stwuct tee_bnxt_fw_pwivate {
	stwuct device *dev;
	stwuct tee_context *ctx;
	u32 session_id;
	stwuct tee_shm *fw_shm_poow;
};

static stwuct tee_bnxt_fw_pwivate pvt_data;

static void pwepawe_awgs(int cmd,
			 stwuct tee_ioctw_invoke_awg *awg,
			 stwuct tee_pawam *pawam)
{
	memset(awg, 0, sizeof(*awg));
	memset(pawam, 0, MAX_TEE_PAWAM_AWWY_MEMB * sizeof(*pawam));

	awg->func = cmd;
	awg->session = pvt_data.session_id;
	awg->num_pawams = MAX_TEE_PAWAM_AWWY_MEMB;

	/* Fiww invoke cmd pawams */
	switch (cmd) {
	case TA_CMD_BNXT_COPY_COWEDUMP:
		pawam[0].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INOUT;
		pawam[0].u.memwef.shm = pvt_data.fw_shm_poow;
		pawam[0].u.memwef.size = MAX_SHM_MEM_SZ;
		pawam[0].u.memwef.shm_offs = 0;
		pawam[1].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INPUT;
		bweak;
	case TA_CMD_BNXT_FASTBOOT:
	defauwt:
		/* Nothing to do */
		bweak;
	}
}

/**
 * tee_bnxt_fw_woad() - Woad the bnxt fiwmwawe
 *		    Uses an OP-TEE caww to stawt a secuwe
 *		    boot pwocess.
 * Wetuwns 0 on success, negative ewwno othewwise.
 */
int tee_bnxt_fw_woad(void)
{
	int wet = 0;
	stwuct tee_ioctw_invoke_awg awg;
	stwuct tee_pawam pawam[MAX_TEE_PAWAM_AWWY_MEMB];

	if (!pvt_data.ctx)
		wetuwn -ENODEV;

	pwepawe_awgs(TA_CMD_BNXT_FASTBOOT, &awg, pawam);

	wet = tee_cwient_invoke_func(pvt_data.ctx, &awg, pawam);
	if (wet < 0 || awg.wet != 0) {
		dev_eww(pvt_data.dev,
			"TA_CMD_BNXT_FASTBOOT invoke faiwed TEE eww: %x, wet:%x\n",
			awg.wet, wet);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(tee_bnxt_fw_woad);

/**
 * tee_bnxt_copy_cowedump() - Copy cowedump fwom the awwocated memowy
 *			    Uses an OP-TEE caww to copy cowedump
 * @buf:	destination buffew whewe cowe dump is copied into
 * @offset:	offset fwom the base addwess of cowe dump awea
 * @size:	size of the dump
 *
 * Wetuwns 0 on success, negative ewwno othewwise.
 */
int tee_bnxt_copy_cowedump(void *buf, u32 offset, u32 size)
{
	stwuct tee_ioctw_invoke_awg awg;
	stwuct tee_pawam pawam[MAX_TEE_PAWAM_AWWY_MEMB];
	void *cowe_data;
	u32 wbytes = size;
	u32 nbytes = 0;
	int wet = 0;

	if (!pvt_data.ctx)
		wetuwn -ENODEV;

	pwepawe_awgs(TA_CMD_BNXT_COPY_COWEDUMP, &awg, pawam);

	whiwe (wbytes)  {
		nbytes = wbytes;

		nbytes = min_t(u32, wbytes, pawam[0].u.memwef.size);

		/* Fiww additionaw invoke cmd pawams */
		pawam[1].u.vawue.a = offset;
		pawam[1].u.vawue.b = nbytes;

		wet = tee_cwient_invoke_func(pvt_data.ctx, &awg, pawam);
		if (wet < 0 || awg.wet != 0) {
			dev_eww(pvt_data.dev,
				"TA_CMD_BNXT_COPY_COWEDUMP invoke faiwed TEE eww: %x, wet:%x\n",
				awg.wet, wet);
			wetuwn -EINVAW;
		}

		cowe_data = tee_shm_get_va(pvt_data.fw_shm_poow, 0);
		if (IS_EWW(cowe_data)) {
			dev_eww(pvt_data.dev, "tee_shm_get_va faiwed\n");
			wetuwn PTW_EWW(cowe_data);
		}

		memcpy(buf, cowe_data, nbytes);

		wbytes -= nbytes;
		buf += nbytes;
		offset += nbytes;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(tee_bnxt_copy_cowedump);

static int optee_ctx_match(stwuct tee_ioctw_vewsion_data *vew, const void *data)
{
	wetuwn (vew->impw_id == TEE_IMPW_ID_OPTEE);
}

static int tee_bnxt_fw_pwobe(stwuct device *dev)
{
	stwuct tee_cwient_device *bnxt_device = to_tee_cwient_device(dev);
	int wet, eww = -ENODEV;
	stwuct tee_ioctw_open_session_awg sess_awg;
	stwuct tee_shm *fw_shm_poow;

	memset(&sess_awg, 0, sizeof(sess_awg));

	/* Open context with TEE dwivew */
	pvt_data.ctx = tee_cwient_open_context(NUWW, optee_ctx_match, NUWW,
					       NUWW);
	if (IS_EWW(pvt_data.ctx))
		wetuwn -ENODEV;

	/* Open session with Bnxt woad Twusted App */
	expowt_uuid(sess_awg.uuid, &bnxt_device->id.uuid);
	sess_awg.cwnt_wogin = TEE_IOCTW_WOGIN_PUBWIC;
	sess_awg.num_pawams = 0;

	wet = tee_cwient_open_session(pvt_data.ctx, &sess_awg, NUWW);
	if (wet < 0 || sess_awg.wet != 0) {
		dev_eww(dev, "tee_cwient_open_session faiwed, eww: %x\n",
			sess_awg.wet);
		eww = -EINVAW;
		goto out_ctx;
	}
	pvt_data.session_id = sess_awg.session;

	pvt_data.dev = dev;

	fw_shm_poow = tee_shm_awwoc_kewnew_buf(pvt_data.ctx, MAX_SHM_MEM_SZ);
	if (IS_EWW(fw_shm_poow)) {
		dev_eww(pvt_data.dev, "tee_shm_awwoc_kewnew_buf faiwed\n");
		eww = PTW_EWW(fw_shm_poow);
		goto out_sess;
	}

	pvt_data.fw_shm_poow = fw_shm_poow;

	wetuwn 0;

out_sess:
	tee_cwient_cwose_session(pvt_data.ctx, pvt_data.session_id);
out_ctx:
	tee_cwient_cwose_context(pvt_data.ctx);

	wetuwn eww;
}

static int tee_bnxt_fw_wemove(stwuct device *dev)
{
	tee_shm_fwee(pvt_data.fw_shm_poow);
	tee_cwient_cwose_session(pvt_data.ctx, pvt_data.session_id);
	tee_cwient_cwose_context(pvt_data.ctx);
	pvt_data.ctx = NUWW;

	wetuwn 0;
}

static void tee_bnxt_fw_shutdown(stwuct device *dev)
{
	tee_shm_fwee(pvt_data.fw_shm_poow);
	tee_cwient_cwose_session(pvt_data.ctx, pvt_data.session_id);
	tee_cwient_cwose_context(pvt_data.ctx);
	pvt_data.ctx = NUWW;
}

static const stwuct tee_cwient_device_id tee_bnxt_fw_id_tabwe[] = {
	{UUID_INIT(0x6272636D, 0x2019, 0x0716,
		    0x42, 0x43, 0x4D, 0x5F, 0x53, 0x43, 0x48, 0x49)},
	{}
};

MODUWE_DEVICE_TABWE(tee, tee_bnxt_fw_id_tabwe);

static stwuct tee_cwient_dwivew tee_bnxt_fw_dwivew = {
	.id_tabwe	= tee_bnxt_fw_id_tabwe,
	.dwivew		= {
		.name		= KBUIWD_MODNAME,
		.bus		= &tee_bus_type,
		.pwobe		= tee_bnxt_fw_pwobe,
		.wemove		= tee_bnxt_fw_wemove,
		.shutdown	= tee_bnxt_fw_shutdown,
	},
};

static int __init tee_bnxt_fw_mod_init(void)
{
	wetuwn dwivew_wegistew(&tee_bnxt_fw_dwivew.dwivew);
}

static void __exit tee_bnxt_fw_mod_exit(void)
{
	dwivew_unwegistew(&tee_bnxt_fw_dwivew.dwivew);
}

moduwe_init(tee_bnxt_fw_mod_init);
moduwe_exit(tee_bnxt_fw_mod_exit);

MODUWE_AUTHOW("Vikas Gupta <vikas.gupta@bwoadcom.com>");
MODUWE_DESCWIPTION("Bwoadcom bnxt fiwmwawe managew");
MODUWE_WICENSE("GPW v2");
