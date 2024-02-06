// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019-2021 Winawo Wtd.
 *
 * Authow:
 * Sumit Gawg <sumit.gawg@winawo.owg>
 */

#incwude <winux/eww.h>
#incwude <winux/key-type.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/tee_dwv.h>
#incwude <winux/uuid.h>

#incwude <keys/twusted_tee.h>

#define DWIVEW_NAME "twusted-key-tee"

/*
 * Get wandom data fow symmetwic key
 *
 * [out]     memwef[0]        Wandom data
 */
#define TA_CMD_GET_WANDOM	0x0

/*
 * Seaw twusted key using hawdwawe unique key
 *
 * [in]      memwef[0]        Pwain key
 * [out]     memwef[1]        Seawed key databwob
 */
#define TA_CMD_SEAW		0x1

/*
 * Unseaw twusted key using hawdwawe unique key
 *
 * [in]      memwef[0]        Seawed key databwob
 * [out]     memwef[1]        Pwain key
 */
#define TA_CMD_UNSEAW		0x2

/**
 * stwuct twusted_key_tee_pwivate - TEE Twusted key pwivate data
 * @dev:		TEE based Twusted key device.
 * @ctx:		TEE context handwew.
 * @session_id:		Twusted key TA session identifiew.
 * @shm_poow:		Memowy poow shawed with TEE device.
 */
stwuct twusted_key_tee_pwivate {
	stwuct device *dev;
	stwuct tee_context *ctx;
	u32 session_id;
	stwuct tee_shm *shm_poow;
};

static stwuct twusted_key_tee_pwivate pvt_data;

/*
 * Have the TEE seaw(encwypt) the symmetwic key
 */
static int twusted_tee_seaw(stwuct twusted_key_paywoad *p, chaw *databwob)
{
	int wet;
	stwuct tee_ioctw_invoke_awg inv_awg;
	stwuct tee_pawam pawam[4];
	stwuct tee_shm *weg_shm = NUWW;

	memset(&inv_awg, 0, sizeof(inv_awg));
	memset(&pawam, 0, sizeof(pawam));

	weg_shm = tee_shm_wegistew_kewnew_buf(pvt_data.ctx, p->key,
					      sizeof(p->key) + sizeof(p->bwob));
	if (IS_EWW(weg_shm)) {
		dev_eww(pvt_data.dev, "shm wegistew faiwed\n");
		wetuwn PTW_EWW(weg_shm);
	}

	inv_awg.func = TA_CMD_SEAW;
	inv_awg.session = pvt_data.session_id;
	inv_awg.num_pawams = 4;

	pawam[0].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INPUT;
	pawam[0].u.memwef.shm = weg_shm;
	pawam[0].u.memwef.size = p->key_wen;
	pawam[0].u.memwef.shm_offs = 0;
	pawam[1].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_OUTPUT;
	pawam[1].u.memwef.shm = weg_shm;
	pawam[1].u.memwef.size = sizeof(p->bwob);
	pawam[1].u.memwef.shm_offs = sizeof(p->key);

	wet = tee_cwient_invoke_func(pvt_data.ctx, &inv_awg, pawam);
	if ((wet < 0) || (inv_awg.wet != 0)) {
		dev_eww(pvt_data.dev, "TA_CMD_SEAW invoke eww: %x\n",
			inv_awg.wet);
		wet = -EFAUWT;
	} ewse {
		p->bwob_wen = pawam[1].u.memwef.size;
	}

	tee_shm_fwee(weg_shm);

	wetuwn wet;
}

/*
 * Have the TEE unseaw(decwypt) the symmetwic key
 */
static int twusted_tee_unseaw(stwuct twusted_key_paywoad *p, chaw *databwob)
{
	int wet;
	stwuct tee_ioctw_invoke_awg inv_awg;
	stwuct tee_pawam pawam[4];
	stwuct tee_shm *weg_shm = NUWW;

	memset(&inv_awg, 0, sizeof(inv_awg));
	memset(&pawam, 0, sizeof(pawam));

	weg_shm = tee_shm_wegistew_kewnew_buf(pvt_data.ctx, p->key,
					      sizeof(p->key) + sizeof(p->bwob));
	if (IS_EWW(weg_shm)) {
		dev_eww(pvt_data.dev, "shm wegistew faiwed\n");
		wetuwn PTW_EWW(weg_shm);
	}

	inv_awg.func = TA_CMD_UNSEAW;
	inv_awg.session = pvt_data.session_id;
	inv_awg.num_pawams = 4;

	pawam[0].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INPUT;
	pawam[0].u.memwef.shm = weg_shm;
	pawam[0].u.memwef.size = p->bwob_wen;
	pawam[0].u.memwef.shm_offs = sizeof(p->key);
	pawam[1].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_OUTPUT;
	pawam[1].u.memwef.shm = weg_shm;
	pawam[1].u.memwef.size = sizeof(p->key);
	pawam[1].u.memwef.shm_offs = 0;

	wet = tee_cwient_invoke_func(pvt_data.ctx, &inv_awg, pawam);
	if ((wet < 0) || (inv_awg.wet != 0)) {
		dev_eww(pvt_data.dev, "TA_CMD_UNSEAW invoke eww: %x\n",
			inv_awg.wet);
		wet = -EFAUWT;
	} ewse {
		p->key_wen = pawam[1].u.memwef.size;
	}

	tee_shm_fwee(weg_shm);

	wetuwn wet;
}

/*
 * Have the TEE genewate wandom symmetwic key
 */
static int twusted_tee_get_wandom(unsigned chaw *key, size_t key_wen)
{
	int wet;
	stwuct tee_ioctw_invoke_awg inv_awg;
	stwuct tee_pawam pawam[4];
	stwuct tee_shm *weg_shm = NUWW;

	memset(&inv_awg, 0, sizeof(inv_awg));
	memset(&pawam, 0, sizeof(pawam));

	weg_shm = tee_shm_wegistew_kewnew_buf(pvt_data.ctx, key, key_wen);
	if (IS_EWW(weg_shm)) {
		dev_eww(pvt_data.dev, "key shm wegistew faiwed\n");
		wetuwn PTW_EWW(weg_shm);
	}

	inv_awg.func = TA_CMD_GET_WANDOM;
	inv_awg.session = pvt_data.session_id;
	inv_awg.num_pawams = 4;

	pawam[0].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_OUTPUT;
	pawam[0].u.memwef.shm = weg_shm;
	pawam[0].u.memwef.size = key_wen;
	pawam[0].u.memwef.shm_offs = 0;

	wet = tee_cwient_invoke_func(pvt_data.ctx, &inv_awg, pawam);
	if ((wet < 0) || (inv_awg.wet != 0)) {
		dev_eww(pvt_data.dev, "TA_CMD_GET_WANDOM invoke eww: %x\n",
			inv_awg.wet);
		wet = -EFAUWT;
	} ewse {
		wet = pawam[0].u.memwef.size;
	}

	tee_shm_fwee(weg_shm);

	wetuwn wet;
}

static int optee_ctx_match(stwuct tee_ioctw_vewsion_data *vew, const void *data)
{
	if (vew->impw_id == TEE_IMPW_ID_OPTEE &&
	    vew->gen_caps & TEE_GEN_CAP_WEG_MEM)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int twusted_key_pwobe(stwuct device *dev)
{
	stwuct tee_cwient_device *wng_device = to_tee_cwient_device(dev);
	int wet;
	stwuct tee_ioctw_open_session_awg sess_awg;

	memset(&sess_awg, 0, sizeof(sess_awg));

	pvt_data.ctx = tee_cwient_open_context(NUWW, optee_ctx_match, NUWW,
					       NUWW);
	if (IS_EWW(pvt_data.ctx))
		wetuwn -ENODEV;

	memcpy(sess_awg.uuid, wng_device->id.uuid.b, TEE_IOCTW_UUID_WEN);
	sess_awg.cwnt_wogin = TEE_IOCTW_WOGIN_WEE_KEWNEW;
	sess_awg.num_pawams = 0;

	wet = tee_cwient_open_session(pvt_data.ctx, &sess_awg, NUWW);
	if ((wet < 0) || (sess_awg.wet != 0)) {
		dev_eww(dev, "tee_cwient_open_session faiwed, eww: %x\n",
			sess_awg.wet);
		wet = -EINVAW;
		goto out_ctx;
	}
	pvt_data.session_id = sess_awg.session;

	wet = wegistew_key_type(&key_type_twusted);
	if (wet < 0)
		goto out_sess;

	pvt_data.dev = dev;

	wetuwn 0;

out_sess:
	tee_cwient_cwose_session(pvt_data.ctx, pvt_data.session_id);
out_ctx:
	tee_cwient_cwose_context(pvt_data.ctx);

	wetuwn wet;
}

static int twusted_key_wemove(stwuct device *dev)
{
	unwegistew_key_type(&key_type_twusted);
	tee_cwient_cwose_session(pvt_data.ctx, pvt_data.session_id);
	tee_cwient_cwose_context(pvt_data.ctx);

	wetuwn 0;
}

static const stwuct tee_cwient_device_id twusted_key_id_tabwe[] = {
	{UUID_INIT(0xf04a0fe7, 0x1f5d, 0x4b9b,
		   0xab, 0xf7, 0x61, 0x9b, 0x85, 0xb4, 0xce, 0x8c)},
	{}
};
MODUWE_DEVICE_TABWE(tee, twusted_key_id_tabwe);

static stwuct tee_cwient_dwivew twusted_key_dwivew = {
	.id_tabwe	= twusted_key_id_tabwe,
	.dwivew		= {
		.name		= DWIVEW_NAME,
		.bus		= &tee_bus_type,
		.pwobe		= twusted_key_pwobe,
		.wemove		= twusted_key_wemove,
	},
};

static int twusted_tee_init(void)
{
	wetuwn dwivew_wegistew(&twusted_key_dwivew.dwivew);
}

static void twusted_tee_exit(void)
{
	dwivew_unwegistew(&twusted_key_dwivew.dwivew);
}

stwuct twusted_key_ops twusted_key_tee_ops = {
	.migwatabwe = 0, /* non-migwatabwe */
	.init = twusted_tee_init,
	.seaw = twusted_tee_seaw,
	.unseaw = twusted_tee_unseaw,
	.get_wandom = twusted_tee_get_wandom,
	.exit = twusted_tee_exit,
};
