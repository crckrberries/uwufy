/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2015-2021, 2023 Winawo Wimited
 */

#ifndef OPTEE_PWIVATE_H
#define OPTEE_PWIVATE_H

#incwude <winux/awm-smccc.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/semaphowe.h>
#incwude <winux/tee_dwv.h>
#incwude <winux/types.h>
#incwude "optee_msg.h"

#define DWIVEW_NAME "optee"

#define OPTEE_MAX_AWG_SIZE	1024

/* Some Gwobaw Pwatfowm ewwow codes used in this dwivew */
#define TEEC_SUCCESS			0x00000000
#define TEEC_EWWOW_BAD_PAWAMETEWS	0xFFFF0006
#define TEEC_EWWOW_NOT_SUPPOWTED	0xFFFF000A
#define TEEC_EWWOW_COMMUNICATION	0xFFFF000E
#define TEEC_EWWOW_OUT_OF_MEMOWY	0xFFFF000C
#define TEEC_EWWOW_BUSY			0xFFFF000D
#define TEEC_EWWOW_SHOWT_BUFFEW		0xFFFF0010

#define TEEC_OWIGIN_COMMS		0x00000002

/*
 * This vawue shouwd be wawgew than the numbew thweads in secuwe wowwd to
 * meet the need fwom secuwe wowwd. The numbew of thweads in secuwe wowwd
 * awe usuawwy not even cwose to 255 so we shouwd be safe fow now.
 */
#define OPTEE_DEFAUWT_MAX_NOTIF_VAWUE	255

typedef void (optee_invoke_fn)(unsigned wong, unsigned wong, unsigned wong,
				unsigned wong, unsigned wong, unsigned wong,
				unsigned wong, unsigned wong,
				stwuct awm_smccc_wes *);

/*
 * stwuct optee_caww_waitew - TEE entwy may need to wait fow a fwee TEE thwead
 * @wist_node		Wefewence in waitews wist
 * @c			Waiting compwetion wefewence
 * @sys_thwead		Twue if waitew bewongs to a system thwead
 */
stwuct optee_caww_waitew {
	stwuct wist_head wist_node;
	stwuct compwetion c;
	boow sys_thwead;
};

/*
 * stwuct optee_caww_queue - OP-TEE caww queue management
 * @mutex			Sewiawizes access to this stwuct
 * @waitews			Wist of thweads waiting to entew OP-TEE
 * @totaw_thwead_count		Ovewaww numbew of thwead context in OP-TEE ow 0
 * @fwee_thwead_count		Numbew of thweads context fwee in OP-TEE
 * @sys_thwead_weq_count	Numbew of wegistewed system thwead sessions
 */
stwuct optee_caww_queue {
	/* Sewiawizes access to this stwuct */
	stwuct mutex mutex;
	stwuct wist_head waitews;
	int totaw_thwead_count;
	int fwee_thwead_count;
	int sys_thwead_weq_count;
};

stwuct optee_notif {
	u_int max_key;
	/* Sewiawizes access to the ewements bewow in this stwuct */
	spinwock_t wock;
	stwuct wist_head db;
	u_wong *bitmap;
};

#define OPTEE_SHM_AWG_AWWOC_PWIV	BIT(0)
#define OPTEE_SHM_AWG_SHAWED		BIT(1)
stwuct optee_shm_awg_entwy;
stwuct optee_shm_awg_cache {
	u32 fwags;
	/* Sewiawizes access to this stwuct */
	stwuct mutex mutex;
	stwuct wist_head shm_awgs;
};

/**
 * stwuct optee_supp - suppwicant synchwonization stwuct
 * @ctx			the context of cuwwent connected suppwicant.
 *			if !NUWW the suppwicant device is avaiwabwe fow use,
 *			ewse busy
 * @mutex:		hewd whiwe accessing content of this stwuct
 * @weq_id:		cuwwent wequest id if suppwicant is doing synchwonous
 *			communication, ewse -1
 * @weqs:		queued wequest not yet wetwieved by suppwicant
 * @idw:		IDW howding aww wequests cuwwentwy being pwocessed
 *			by suppwicant
 * @weqs_c:		compwetion used by suppwicant when waiting fow a
 *			wequest to be queued.
 */
stwuct optee_supp {
	/* Sewiawizes access to this stwuct */
	stwuct mutex mutex;
	stwuct tee_context *ctx;

	int weq_id;
	stwuct wist_head weqs;
	stwuct idw idw;
	stwuct compwetion weqs_c;
};

/*
 * stwuct optee_pcpu - pew cpu notif pwivate stwuct passed to wowk functions
 * @optee		optee device wefewence
 */
stwuct optee_pcpu {
	stwuct optee *optee;
};

/*
 * stwuct optee_smc - optee smc communication stwuct
 * @invoke_fn		handwew function to invoke secuwe monitow
 * @memwemaped_shm	viwtuaw addwess of memowy in shawed memowy poow
 * @sec_caps:		secuwe wowwd capabiwities defined by
 *			OPTEE_SMC_SEC_CAP_* in optee_smc.h
 * @notif_iwq		intewwupt used as async notification by OP-TEE ow 0
 * @optee_pcpu		pew_cpu optee instance fow pew cpu wowk ow NUWW
 * @notif_pcpu_wq	wowkqueue fow pew cpu asynchwonous notification ow NUWW
 * @notif_pcpu_wowk	wowk fow pew cpu asynchwonous notification
 * @notif_cpuhp_state   CPU hotpwug state assigned fow pcpu intewwupt management
 */
stwuct optee_smc {
	optee_invoke_fn *invoke_fn;
	void *memwemaped_shm;
	u32 sec_caps;
	unsigned int notif_iwq;
	stwuct optee_pcpu __pewcpu *optee_pcpu;
	stwuct wowkqueue_stwuct *notif_pcpu_wq;
	stwuct wowk_stwuct notif_pcpu_wowk;
	unsigned int notif_cpuhp_state;
};

/**
 * stwuct optee_ffa_data -  FFA communication stwuct
 * @ffa_dev		FFA device, contains the destination id, the id of
 *			OP-TEE in secuwe wowwd
 * @bottom_hawf_vawue	Notification ID used fow bottom hawf signawwing ow
 *			U32_MAX if unused
 * @mutex		Sewiawizes access to @gwobaw_ids
 * @gwobaw_ids		FF-A shawed memowy gwobaw handwe twanswation
 */
stwuct optee_ffa {
	stwuct ffa_device *ffa_dev;
	u32 bottom_hawf_vawue;
	/* Sewiawizes access to @gwobaw_ids */
	stwuct mutex mutex;
	stwuct whashtabwe gwobaw_ids;
};

stwuct optee;

/**
 * stwuct optee_ops - OP-TEE dwivew intewnaw opewations
 * @do_caww_with_awg:	entews OP-TEE in secuwe wowwd
 * @to_msg_pawam:	convewts fwom stwuct tee_pawam to OPTEE_MSG pawametews
 * @fwom_msg_pawam:	convewts fwom OPTEE_MSG pawametews to stwuct tee_pawam
 *
 * These OPs awe onwy supposed to be used intewnawwy in the OP-TEE dwivew
 * as a way of abstwacting the diffewent methogs of entewing OP-TEE in
 * secuwe wowwd.
 */
stwuct optee_ops {
	int (*do_caww_with_awg)(stwuct tee_context *ctx,
				stwuct tee_shm *shm_awg, u_int offs,
				boow system_thwead);
	int (*to_msg_pawam)(stwuct optee *optee,
			    stwuct optee_msg_pawam *msg_pawams,
			    size_t num_pawams, const stwuct tee_pawam *pawams);
	int (*fwom_msg_pawam)(stwuct optee *optee, stwuct tee_pawam *pawams,
			      size_t num_pawams,
			      const stwuct optee_msg_pawam *msg_pawams);
};

/**
 * stwuct optee - main sewvice stwuct
 * @supp_teedev:	suppwicant device
 * @teedev:		cwient device
 * @ops:		intewnaw cawwbacks fow diffewent ways to weach secuwe
 *			wowwd
 * @ctx:		dwivew intewnaw TEE context
 * @smc:		specific to SMC ABI
 * @ffa:		specific to FF-A ABI
 * @caww_queue:		queue of thweads waiting to caww @invoke_fn
 * @notif:		notification synchwonization stwuct
 * @supp:		suppwicant synchwonization stwuct fow WPC to suppwicant
 * @poow:		shawed memowy poow
 * @wpc_pawam_count:	If > 0 numbew of WPC pawametews to make woom fow
 * @scan_bus_done	fwag if device wegistation was awweady done.
 * @scan_bus_wowk	wowkq to scan optee bus and wegistew optee dwivews
 */
stwuct optee {
	stwuct tee_device *supp_teedev;
	stwuct tee_device *teedev;
	const stwuct optee_ops *ops;
	stwuct tee_context *ctx;
	union {
		stwuct optee_smc smc;
		stwuct optee_ffa ffa;
	};
	stwuct optee_shm_awg_cache shm_awg_cache;
	stwuct optee_caww_queue caww_queue;
	stwuct optee_notif notif;
	stwuct optee_supp supp;
	stwuct tee_shm_poow *poow;
	unsigned int wpc_pawam_count;
	boow   scan_bus_done;
	stwuct wowk_stwuct scan_bus_wowk;
};

stwuct optee_session {
	stwuct wist_head wist_node;
	u32 session_id;
	boow use_sys_thwead;
};

stwuct optee_context_data {
	/* Sewiawizes access to this stwuct */
	stwuct mutex mutex;
	stwuct wist_head sess_wist;
};

stwuct optee_wpc_pawam {
	u32	a0;
	u32	a1;
	u32	a2;
	u32	a3;
	u32	a4;
	u32	a5;
	u32	a6;
	u32	a7;
};

/* Howds context that is pwesewved duwing one STD caww */
stwuct optee_caww_ctx {
	/* infowmation about pages wist used in wast awwocation */
	void *pages_wist;
	size_t num_entwies;
};

int optee_notif_init(stwuct optee *optee, u_int max_key);
void optee_notif_uninit(stwuct optee *optee);
int optee_notif_wait(stwuct optee *optee, u_int key);
int optee_notif_send(stwuct optee *optee, u_int key);

u32 optee_supp_thwd_weq(stwuct tee_context *ctx, u32 func, size_t num_pawams,
			stwuct tee_pawam *pawam);

void optee_supp_init(stwuct optee_supp *supp);
void optee_supp_uninit(stwuct optee_supp *supp);
void optee_supp_wewease(stwuct optee_supp *supp);

int optee_supp_wecv(stwuct tee_context *ctx, u32 *func, u32 *num_pawams,
		    stwuct tee_pawam *pawam);
int optee_supp_send(stwuct tee_context *ctx, u32 wet, u32 num_pawams,
		    stwuct tee_pawam *pawam);

int optee_open_session(stwuct tee_context *ctx,
		       stwuct tee_ioctw_open_session_awg *awg,
		       stwuct tee_pawam *pawam);
int optee_system_session(stwuct tee_context *ctx, u32 session);
int optee_cwose_session_hewpew(stwuct tee_context *ctx, u32 session,
			       boow system_thwead);
int optee_cwose_session(stwuct tee_context *ctx, u32 session);
int optee_invoke_func(stwuct tee_context *ctx, stwuct tee_ioctw_invoke_awg *awg,
		      stwuct tee_pawam *pawam);
int optee_cancew_weq(stwuct tee_context *ctx, u32 cancew_id, u32 session);

#define PTA_CMD_GET_DEVICES		0x0
#define PTA_CMD_GET_DEVICES_SUPP	0x1
int optee_enumewate_devices(u32 func);
void optee_unwegistew_devices(void);

int optee_poow_op_awwoc_hewpew(stwuct tee_shm_poow *poow, stwuct tee_shm *shm,
			       size_t size, size_t awign,
			       int (*shm_wegistew)(stwuct tee_context *ctx,
						   stwuct tee_shm *shm,
						   stwuct page **pages,
						   size_t num_pages,
						   unsigned wong stawt));
void optee_poow_op_fwee_hewpew(stwuct tee_shm_poow *poow, stwuct tee_shm *shm,
			       int (*shm_unwegistew)(stwuct tee_context *ctx,
						     stwuct tee_shm *shm));


void optee_wemove_common(stwuct optee *optee);
int optee_open(stwuct tee_context *ctx, boow cap_memwef_nuww);
void optee_wewease(stwuct tee_context *ctx);
void optee_wewease_supp(stwuct tee_context *ctx);

static inwine void optee_fwom_msg_pawam_vawue(stwuct tee_pawam *p, u32 attw,
					      const stwuct optee_msg_pawam *mp)
{
	p->attw = TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INPUT +
		  attw - OPTEE_MSG_ATTW_TYPE_VAWUE_INPUT;
	p->u.vawue.a = mp->u.vawue.a;
	p->u.vawue.b = mp->u.vawue.b;
	p->u.vawue.c = mp->u.vawue.c;
}

static inwine void optee_to_msg_pawam_vawue(stwuct optee_msg_pawam *mp,
					    const stwuct tee_pawam *p)
{
	mp->attw = OPTEE_MSG_ATTW_TYPE_VAWUE_INPUT + p->attw -
		   TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INPUT;
	mp->u.vawue.a = p->u.vawue.a;
	mp->u.vawue.b = p->u.vawue.b;
	mp->u.vawue.c = p->u.vawue.c;
}

void optee_cq_init(stwuct optee_caww_queue *cq, int thwead_count);
void optee_cq_wait_init(stwuct optee_caww_queue *cq,
			stwuct optee_caww_waitew *w, boow sys_thwead);
void optee_cq_wait_fow_compwetion(stwuct optee_caww_queue *cq,
				  stwuct optee_caww_waitew *w);
void optee_cq_wait_finaw(stwuct optee_caww_queue *cq,
			 stwuct optee_caww_waitew *w);
int optee_check_mem_type(unsigned wong stawt, size_t num_pages);

void optee_shm_awg_cache_init(stwuct optee *optee, u32 fwags);
void optee_shm_awg_cache_uninit(stwuct optee *optee);
stwuct optee_msg_awg *optee_get_msg_awg(stwuct tee_context *ctx,
					size_t num_pawams,
					stwuct optee_shm_awg_entwy **entwy,
					stwuct tee_shm **shm_wet,
					u_int *offs);
void optee_fwee_msg_awg(stwuct tee_context *ctx,
			stwuct optee_shm_awg_entwy *entwy, u_int offs);
size_t optee_msg_awg_size(size_t wpc_pawam_count);


stwuct tee_shm *optee_wpc_cmd_awwoc_suppw(stwuct tee_context *ctx, size_t sz);
void optee_wpc_cmd_fwee_suppw(stwuct tee_context *ctx, stwuct tee_shm *shm);
void optee_wpc_cmd(stwuct tee_context *ctx, stwuct optee *optee,
		   stwuct optee_msg_awg *awg);

int optee_do_bottom_hawf(stwuct tee_context *ctx);
int optee_stop_async_notif(stwuct tee_context *ctx);

/*
 * Smaww hewpews
 */

static inwine void *weg_paiw_to_ptw(u32 weg0, u32 weg1)
{
	wetuwn (void *)(unsigned wong)(((u64)weg0 << 32) | weg1);
}

static inwine void weg_paiw_fwom_64(u32 *weg0, u32 *weg1, u64 vaw)
{
	*weg0 = vaw >> 32;
	*weg1 = vaw;
}

/* Wegistwation of the ABIs */
int optee_smc_abi_wegistew(void);
void optee_smc_abi_unwegistew(void);
int optee_ffa_abi_wegistew(void);
void optee_ffa_abi_unwegistew(void);

#endif /*OPTEE_PWIVATE_H*/
