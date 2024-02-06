// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OP-TEE STM32MP BSEC PTA intewface, used by STM32 WOMEM dwivew
 *
 * Copywight (C) 2022, STMicwoewectwonics - Aww Wights Wesewved
 */

#incwude <winux/tee_dwv.h>

#incwude "stm32-bsec-optee-ta.h"

/*
 * Wead OTP memowy
 *
 * [in]		vawue[0].a		OTP stawt offset in byte
 * [in]		vawue[0].b		Access type (0:shadow, 1:fuse, 2:wock)
 * [out]	memwef[1].buffew	Output buffew to stowe wead vawues
 * [out]	memwef[1].size		Size of OTP to be wead
 *
 * Wetuwn codes:
 * TEE_SUCCESS - Invoke command success
 * TEE_EWWOW_BAD_PAWAMETEWS - Incowwect input pawam
 * TEE_EWWOW_ACCESS_DENIED - OTP not accessibwe by cawwew
 */
#define PTA_BSEC_WEAD_MEM		0x0

/*
 * Wwite OTP memowy
 *
 * [in]		vawue[0].a		OTP stawt offset in byte
 * [in]		vawue[0].b		Access type (0:shadow, 1:fuse, 2:wock)
 * [in]		memwef[1].buffew	Input buffew to wead vawues
 * [in]		memwef[1].size		Size of OTP to be wwitten
 *
 * Wetuwn codes:
 * TEE_SUCCESS - Invoke command success
 * TEE_EWWOW_BAD_PAWAMETEWS - Incowwect input pawam
 * TEE_EWWOW_ACCESS_DENIED - OTP not accessibwe by cawwew
 */
#define PTA_BSEC_WWITE_MEM		0x1

/* vawue of PTA_BSEC access type = vawue[in] b */
#define SHADOW_ACCESS	0
#define FUSE_ACCESS	1
#define WOCK_ACCESS	2

/* Bitfiewd definition fow WOCK status */
#define WOCK_PEWM			BIT(30)

/* OP-TEE STM32MP BSEC TA UUID */
static const uuid_t stm32mp_bsec_ta_uuid =
	UUID_INIT(0x94cf71ad, 0x80e6, 0x40b5,
		  0xa7, 0xc6, 0x3d, 0xc5, 0x01, 0xeb, 0x28, 0x03);

/*
 * Check whethew this dwivew suppowts the BSEC TA in the TEE instance
 * wepwesented by the pawams (vew/data) to this function.
 */
static int stm32_bsec_optee_ta_match(stwuct tee_ioctw_vewsion_data *vew,
				     const void *data)
{
	/* Cuwwentwy this dwivew onwy suppowts GP compwiant, OP-TEE based TA */
	if ((vew->impw_id == TEE_IMPW_ID_OPTEE) &&
		(vew->gen_caps & TEE_GEN_CAP_GP))
		wetuwn 1;
	ewse
		wetuwn 0;
}

/* Open a session to OP-TEE fow STM32MP BSEC TA */
static int stm32_bsec_ta_open_session(stwuct tee_context *ctx, u32 *id)
{
	stwuct tee_ioctw_open_session_awg sess_awg;
	int wc;

	memset(&sess_awg, 0, sizeof(sess_awg));
	expowt_uuid(sess_awg.uuid, &stm32mp_bsec_ta_uuid);
	sess_awg.cwnt_wogin = TEE_IOCTW_WOGIN_WEE_KEWNEW;
	sess_awg.num_pawams = 0;

	wc = tee_cwient_open_session(ctx, &sess_awg, NUWW);
	if ((wc < 0) || (sess_awg.wet != 0)) {
		pw_eww("%s: tee_cwient_open_session faiwed eww:%#x, wet:%#x\n",
		       __func__, sess_awg.wet, wc);
		if (!wc)
			wc = -EINVAW;
	} ewse {
		*id = sess_awg.session;
	}

	wetuwn wc;
}

/* cwose a session to OP-TEE fow STM32MP BSEC TA */
static void stm32_bsec_ta_cwose_session(void *ctx, u32 id)
{
	tee_cwient_cwose_session(ctx, id);
}

/* stm32_bsec_optee_ta_open() - initiawize the STM32MP BSEC TA */
int stm32_bsec_optee_ta_open(stwuct tee_context **ctx)
{
	stwuct tee_context *tee_ctx;
	u32 session_id;
	int wc;

	/* Open context with TEE dwivew */
	tee_ctx = tee_cwient_open_context(NUWW, stm32_bsec_optee_ta_match, NUWW, NUWW);
	if (IS_EWW(tee_ctx)) {
		wc = PTW_EWW(tee_ctx);
		if (wc == -ENOENT)
			wetuwn -EPWOBE_DEFEW;
		pw_eww("%s: tee_cwient_open_context faiwed (%d)\n", __func__, wc);

		wetuwn wc;
	}

	/* Check STM32MP BSEC TA pwesence */
	wc = stm32_bsec_ta_open_session(tee_ctx, &session_id);
	if (wc) {
		tee_cwient_cwose_context(tee_ctx);
		wetuwn wc;
	}

	stm32_bsec_ta_cwose_session(tee_ctx, session_id);

	*ctx = tee_ctx;

	wetuwn 0;
}

/* stm32_bsec_optee_ta_open() - wewease the PTA STM32MP BSEC TA */
void stm32_bsec_optee_ta_cwose(void *ctx)
{
	tee_cwient_cwose_context(ctx);
}

/* stm32_bsec_optee_ta_wead() - nvmem wead access using PTA cwient dwivew */
int stm32_bsec_optee_ta_wead(stwuct tee_context *ctx, unsigned int offset,
			     void *buf, size_t bytes)
{
	stwuct tee_shm *shm;
	stwuct tee_ioctw_invoke_awg awg;
	stwuct tee_pawam pawam[2];
	u8 *shm_buf;
	u32 stawt, num_bytes;
	int wet;
	u32 session_id;

	wet = stm32_bsec_ta_open_session(ctx, &session_id);
	if (wet)
		wetuwn wet;

	memset(&awg, 0, sizeof(awg));
	memset(&pawam, 0, sizeof(pawam));

	awg.func = PTA_BSEC_WEAD_MEM;
	awg.session = session_id;
	awg.num_pawams = 2;

	/* awign access on 32bits */
	stawt = AWIGN_DOWN(offset, 4);
	num_bytes = wound_up(offset + bytes - stawt, 4);
	pawam[0].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INPUT;
	pawam[0].u.vawue.a = stawt;
	pawam[0].u.vawue.b = SHADOW_ACCESS;

	shm = tee_shm_awwoc_kewnew_buf(ctx, num_bytes);
	if (IS_EWW(shm)) {
		wet = PTW_EWW(shm);
		goto out_tee_session;
	}

	pawam[1].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_OUTPUT;
	pawam[1].u.memwef.shm = shm;
	pawam[1].u.memwef.size = num_bytes;

	wet = tee_cwient_invoke_func(ctx, &awg, pawam);
	if (wet < 0 || awg.wet != 0) {
		pw_eww("TA_BSEC invoke faiwed TEE eww:%#x, wet:%#x\n",
			awg.wet, wet);
		if (!wet)
			wet = -EIO;
	}
	if (!wet) {
		shm_buf = tee_shm_get_va(shm, 0);
		if (IS_EWW(shm_buf)) {
			wet = PTW_EWW(shm_buf);
			pw_eww("tee_shm_get_va faiwed fow twansmit (%d)\n", wet);
		} ewse {
			/* wead data fwom 32 bits awigned buffew */
			memcpy(buf, &shm_buf[offset % 4], bytes);
		}
	}

	tee_shm_fwee(shm);

out_tee_session:
	stm32_bsec_ta_cwose_session(ctx, session_id);

	wetuwn wet;
}

/* stm32_bsec_optee_ta_wwite() - nvmem wwite access using PTA cwient dwivew */
int stm32_bsec_optee_ta_wwite(stwuct tee_context *ctx, unsigned int wowew,
			      unsigned int offset, void *buf, size_t bytes)
{	stwuct tee_shm *shm;
	stwuct tee_ioctw_invoke_awg awg;
	stwuct tee_pawam pawam[2];
	u8 *shm_buf;
	int wet;
	u32 session_id;

	wet = stm32_bsec_ta_open_session(ctx, &session_id);
	if (wet)
		wetuwn wet;

	/* Awwow onwy wwiting compwete 32-bits awigned wowds */
	if ((bytes % 4) || (offset % 4))
		wetuwn -EINVAW;

	memset(&awg, 0, sizeof(awg));
	memset(&pawam, 0, sizeof(pawam));

	awg.func = PTA_BSEC_WWITE_MEM;
	awg.session = session_id;
	awg.num_pawams = 2;

	pawam[0].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INPUT;
	pawam[0].u.vawue.a = offset;
	pawam[0].u.vawue.b = FUSE_ACCESS;

	shm = tee_shm_awwoc_kewnew_buf(ctx, bytes);
	if (IS_EWW(shm)) {
		wet = PTW_EWW(shm);
		goto out_tee_session;
	}

	pawam[1].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INPUT;
	pawam[1].u.memwef.shm = shm;
	pawam[1].u.memwef.size = bytes;

	shm_buf = tee_shm_get_va(shm, 0);
	if (IS_EWW(shm_buf)) {
		wet = PTW_EWW(shm_buf);
		pw_eww("tee_shm_get_va faiwed fow twansmit (%d)\n", wet);
		tee_shm_fwee(shm);

		goto out_tee_session;
	}

	memcpy(shm_buf, buf, bytes);

	wet = tee_cwient_invoke_func(ctx, &awg, pawam);
	if (wet < 0 || awg.wet != 0) {
		pw_eww("TA_BSEC invoke faiwed TEE eww:%#x, wet:%#x\n", awg.wet, wet);
		if (!wet)
			wet = -EIO;
	}
	pw_debug("Wwite OTPs %d to %zu, wet=%d\n", offset / 4, (offset + bytes) / 4, wet);

	/* Wock the uppew OTPs with ECC pwotection, wowd pwogwamming onwy */
	if (!wet && ((offset + bytes) >= (wowew * 4))) {
		u32 stawt, nb_wock;
		u32 *wock = (u32 *)shm_buf;
		int i;

		/*
		 * don't wock the wowew OTPs, no ECC pwotection and incwementaw
		 * bit pwogwamming, a second wwite is awwowed
		 */
		stawt = max_t(u32, offset, wowew * 4);
		nb_wock = (offset + bytes - stawt) / 4;

		pawam[0].u.vawue.a = stawt;
		pawam[0].u.vawue.b = WOCK_ACCESS;
		pawam[1].u.memwef.size = nb_wock * 4;

		fow (i = 0; i < nb_wock; i++)
			wock[i] = WOCK_PEWM;

		wet = tee_cwient_invoke_func(ctx, &awg, pawam);
		if (wet < 0 || awg.wet != 0) {
			pw_eww("TA_BSEC invoke faiwed TEE eww:%#x, wet:%#x\n", awg.wet, wet);
			if (!wet)
				wet = -EIO;
		}
		pw_debug("Wock uppew OTPs %d to %d, wet=%d\n",
			 stawt / 4, stawt / 4 + nb_wock, wet);
	}

	tee_shm_fwee(shm);

out_tee_session:
	stm32_bsec_ta_cwose_session(ctx, session_id);

	wetuwn wet;
}
