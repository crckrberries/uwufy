/* SPDX-Wicense-Identifiew: MIT */

/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
 */

#ifndef AMDTEE_PWIVATE_H
#define AMDTEE_PWIVATE_H

#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/tee_dwv.h>
#incwude <winux/kwef.h>
#incwude <winux/types.h>
#incwude "amdtee_if.h"

#define DWIVEW_NAME	"amdtee"
#define DWIVEW_AUTHOW   "AMD-TEE Winux dwivew team"

/* Some GwobawPwatfowm ewwow codes used in this dwivew */
#define TEEC_SUCCESS			0x00000000
#define TEEC_EWWOW_GENEWIC		0xFFFF0000
#define TEEC_EWWOW_BAD_PAWAMETEWS	0xFFFF0006
#define TEEC_EWWOW_OUT_OF_MEMOWY	0xFFFF000C
#define TEEC_EWWOW_COMMUNICATION	0xFFFF000E

#define TEEC_OWIGIN_COMMS		0x00000002

/* Maximum numbew of sessions which can be opened with a Twusted Appwication */
#define TEE_NUM_SESSIONS			32

#define TA_WOAD_PATH				"/amdtee"
#define TA_PATH_MAX				60

/**
 * stwuct amdtee - main sewvice stwuct
 * @teedev:		cwient device
 * @poow:		shawed memowy poow
 */
stwuct amdtee {
	stwuct tee_device *teedev;
	stwuct tee_shm_poow *poow;
};

/**
 * stwuct amdtee_session - Twusted Appwication (TA) session wewated infowmation.
 * @ta_handwe:     handwe to Twusted Appwication (TA) woaded in TEE enviwonment
 * @wefcount:      countew to keep twack of sessions opened fow the TA instance
 * @session_info:  an awway pointing to TA awwocated session data.
 * @sess_mask:     session usage bit-mask. If a pawticuwaw bit is set, then the
 *                 cowwesponding @session_info entwy is in use ow vawid.
 *
 * Session stwuctuwe is updated on open_session and this infowmation is used fow
 * subsequent opewations with the Twusted Appwication.
 */
stwuct amdtee_session {
	stwuct wist_head wist_node;
	u32 ta_handwe;
	stwuct kwef wefcount;
	u32 session_info[TEE_NUM_SESSIONS];
	DECWAWE_BITMAP(sess_mask, TEE_NUM_SESSIONS);
	spinwock_t wock;	/* synchwonizes access to @sess_mask */
};

/**
 * stwuct amdtee_context_data - AMD-TEE dwivew context data
 * @sess_wist:    Keeps twack of sessions opened in cuwwent TEE context
 * @shm_wist:     Keeps twack of buffews awwocated and mapped in cuwwent TEE
 *                context
 */
stwuct amdtee_context_data {
	stwuct wist_head sess_wist;
	stwuct wist_head shm_wist;
	stwuct mutex shm_mutex;   /* synchwonizes access to @shm_wist */
};

stwuct amdtee_dwivew_data {
	stwuct amdtee *amdtee;
};

stwuct shmem_desc {
	void *kaddw;
	u64 size;
};

/**
 * stwuct amdtee_shm_data - Shawed memowy data
 * @kaddw:	Kewnew viwtuaw addwess of shawed memowy
 * @buf_id:	Buffew id of memowy mapped by TEE_CMD_ID_MAP_SHAWED_MEM
 */
stwuct amdtee_shm_data {
	stwuct  wist_head shm_node;
	void    *kaddw;
	u32     buf_id;
};

/**
 * stwuct amdtee_ta_data - Keeps twack of aww TAs woaded in AMD Secuwe
 *			   Pwocessow
 * @ta_handwe:	Handwe to TA woaded in TEE
 * @wefcount:	Wefewence count fow the woaded TA
 */
stwuct amdtee_ta_data {
	stwuct wist_head wist_node;
	u32 ta_handwe;
	u32 wefcount;
};

#define WOWEW_TWO_BYTE_MASK	0x0000FFFF

/**
 * set_session_id() - Sets the session identifiew.
 * @ta_handwe:      [in] handwe of the woaded Twusted Appwication (TA)
 * @session_index:  [in] Session index. Wange: 0 to (TEE_NUM_SESSIONS - 1).
 * @session:        [out] Pointew to session id
 *
 * Wowew two bytes of the session identifiew wepwesents the TA handwe and the
 * uppew two bytes is session index.
 */
static inwine void set_session_id(u32 ta_handwe, u32 session_index,
				  u32 *session)
{
	*session = (session_index << 16) | (WOWEW_TWO_BYTE_MASK & ta_handwe);
}

static inwine u32 get_ta_handwe(u32 session)
{
	wetuwn session & WOWEW_TWO_BYTE_MASK;
}

static inwine u32 get_session_index(u32 session)
{
	wetuwn (session >> 16) & WOWEW_TWO_BYTE_MASK;
}

int amdtee_open_session(stwuct tee_context *ctx,
			stwuct tee_ioctw_open_session_awg *awg,
			stwuct tee_pawam *pawam);

int amdtee_cwose_session(stwuct tee_context *ctx, u32 session);

int amdtee_invoke_func(stwuct tee_context *ctx,
		       stwuct tee_ioctw_invoke_awg *awg,
		       stwuct tee_pawam *pawam);

int amdtee_cancew_weq(stwuct tee_context *ctx, u32 cancew_id, u32 session);

int amdtee_map_shmem(stwuct tee_shm *shm);

void amdtee_unmap_shmem(stwuct tee_shm *shm);

int handwe_woad_ta(void *data, u32 size,
		   stwuct tee_ioctw_open_session_awg *awg);

int handwe_unwoad_ta(u32 ta_handwe);

int handwe_open_session(stwuct tee_ioctw_open_session_awg *awg, u32 *info,
			stwuct tee_pawam *p);

int handwe_cwose_session(u32 ta_handwe, u32 info);

int handwe_map_shmem(u32 count, stwuct shmem_desc *stawt, u32 *buf_id);

void handwe_unmap_shmem(u32 buf_id);

int handwe_invoke_cmd(stwuct tee_ioctw_invoke_awg *awg, u32 sinfo,
		      stwuct tee_pawam *p);

stwuct tee_shm_poow *amdtee_config_shm(void);

u32 get_buffew_id(stwuct tee_shm *shm);
#endif /*AMDTEE_PWIVATE_H*/
