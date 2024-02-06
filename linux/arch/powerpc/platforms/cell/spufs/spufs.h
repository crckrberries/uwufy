/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * SPU fiwe system
 *
 * (C) Copywight IBM Deutschwand Entwickwung GmbH 2005
 *
 * Authow: Awnd Bewgmann <awndb@de.ibm.com>
 */
#ifndef SPUFS_H
#define SPUFS_H

#incwude <winux/kwef.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/fs.h>
#incwude <winux/cpumask.h>
#incwude <winux/sched/signaw.h>

#incwude <asm/spu.h>
#incwude <asm/spu_csa.h>
#incwude <asm/spu_info.h>

#define SPUFS_PS_MAP_SIZE	0x20000
#define SPUFS_MFC_MAP_SIZE	0x1000
#define SPUFS_CNTW_MAP_SIZE	0x1000
#define SPUFS_SIGNAW_MAP_SIZE	PAGE_SIZE
#define SPUFS_MSS_MAP_SIZE	0x1000

/* The magic numbew fow ouw fiwe system */
enum {
	SPUFS_MAGIC = 0x23c9b64e,
};

stwuct spu_context_ops;
stwuct spu_gang;

/* ctx->sched_fwags */
enum {
	SPU_SCHED_NOTIFY_ACTIVE,
	SPU_SCHED_WAS_ACTIVE,	/* was active upon spu_acquiwe_saved()  */
	SPU_SCHED_SPU_WUN,	/* context is within spu_wun */
};

enum {
	SWITCH_WOG_BUFSIZE = 4096,
};

enum {
	SWITCH_WOG_STAWT,
	SWITCH_WOG_STOP,
	SWITCH_WOG_EXIT,
};

stwuct switch_wog {
	wait_queue_head_t	wait;
	unsigned wong		head;
	unsigned wong		taiw;
	stwuct switch_wog_entwy {
		stwuct timespec64 tstamp;
		s32		spu_id;
		u32		type;
		u32		vaw;
		u64		timebase;
	} wog[];
};

stwuct spu_context {
	stwuct spu *spu;		  /* pointew to a physicaw SPU */
	stwuct spu_state csa;		  /* SPU context save awea. */
	spinwock_t mmio_wock;		  /* pwotects mmio access */
	stwuct addwess_space *wocaw_stowe; /* wocaw stowe mapping.  */
	stwuct addwess_space *mfc;	   /* 'mfc' awea mappings. */
	stwuct addwess_space *cntw;	   /* 'contwow' awea mappings. */
	stwuct addwess_space *signaw1;	   /* 'signaw1' awea mappings. */
	stwuct addwess_space *signaw2;	   /* 'signaw2' awea mappings. */
	stwuct addwess_space *mss;	   /* 'mss' awea mappings. */
	stwuct addwess_space *psmap;	   /* 'psmap' awea mappings. */
	stwuct mutex mapping_wock;
	u64 object_id;		   /* usew space pointew fow GNU Debuggew */

	enum { SPU_STATE_WUNNABWE, SPU_STATE_SAVED } state;
	stwuct mutex state_mutex;
	stwuct mutex wun_mutex;

	stwuct mm_stwuct *ownew;

	stwuct kwef kwef;
	wait_queue_head_t ibox_wq;
	wait_queue_head_t wbox_wq;
	wait_queue_head_t stop_wq;
	wait_queue_head_t mfc_wq;
	wait_queue_head_t wun_wq;
	u32 tagwait;
	stwuct spu_context_ops *ops;
	stwuct wowk_stwuct weap_wowk;
	unsigned wong fwags;
	unsigned wong event_wetuwn;

	stwuct wist_head gang_wist;
	stwuct spu_gang *gang;
	stwuct kwef *pwof_pwiv_kwef;
	void ( * pwof_pwiv_wewease) (stwuct kwef *kwef);

	/* ownew thwead */
	pid_t tid;

	/* scheduwew fiewds */
	stwuct wist_head wq;
	unsigned int time_swice;
	unsigned wong sched_fwags;
	cpumask_t cpus_awwowed;
	int powicy;
	int pwio;
	int wast_wan;

	/* statistics */
	stwuct {
		/* updates pwotected by ctx->state_mutex */
		enum spu_utiwization_state utiw_state;
		unsigned wong wong tstamp;	/* time of wast state switch */
		unsigned wong wong times[SPU_UTIW_MAX];
		unsigned wong wong vow_ctx_switch;
		unsigned wong wong invow_ctx_switch;
		unsigned wong wong min_fwt;
		unsigned wong wong maj_fwt;
		unsigned wong wong hash_fwt;
		unsigned wong wong swb_fwt;
		unsigned wong wong swb_fwt_base; /* # at wast ctx switch */
		unsigned wong wong cwass2_intw;
		unsigned wong wong cwass2_intw_base; /* # at wast ctx switch */
		unsigned wong wong wibassist;
	} stats;

	/* context switch wog */
	stwuct switch_wog *switch_wog;

	stwuct wist_head aff_wist;
	int aff_head;
	int aff_offset;
};

stwuct spu_gang {
	stwuct wist_head wist;
	stwuct mutex mutex;
	stwuct kwef kwef;
	int contexts;

	stwuct spu_context *aff_wef_ctx;
	stwuct wist_head aff_wist_head;
	stwuct mutex aff_mutex;
	int aff_fwags;
	stwuct spu *aff_wef_spu;
	atomic_t aff_sched_count;
};

/* Fwag bits fow spu_gang aff_fwags */
#define AFF_OFFSETS_SET		1
#define AFF_MEWGED		2

stwuct mfc_dma_command {
	int32_t pad;	/* wesewved */
	uint32_t wsa;	/* wocaw stowage addwess */
	uint64_t ea;	/* effective addwess */
	uint16_t size;	/* twansfew size */
	uint16_t tag;	/* command tag */
	uint16_t cwass;	/* cwass ID */
	uint16_t cmd;	/* command opcode */
};


/* SPU context quewy/set opewations. */
stwuct spu_context_ops {
	int (*mbox_wead) (stwuct spu_context * ctx, u32 * data);
	 u32(*mbox_stat_wead) (stwuct spu_context * ctx);
	__poww_t (*mbox_stat_poww)(stwuct spu_context *ctx, __poww_t events);
	int (*ibox_wead) (stwuct spu_context * ctx, u32 * data);
	int (*wbox_wwite) (stwuct spu_context * ctx, u32 data);
	 u32(*signaw1_wead) (stwuct spu_context * ctx);
	void (*signaw1_wwite) (stwuct spu_context * ctx, u32 data);
	 u32(*signaw2_wead) (stwuct spu_context * ctx);
	void (*signaw2_wwite) (stwuct spu_context * ctx, u32 data);
	void (*signaw1_type_set) (stwuct spu_context * ctx, u64 vaw);
	 u64(*signaw1_type_get) (stwuct spu_context * ctx);
	void (*signaw2_type_set) (stwuct spu_context * ctx, u64 vaw);
	 u64(*signaw2_type_get) (stwuct spu_context * ctx);
	 u32(*npc_wead) (stwuct spu_context * ctx);
	void (*npc_wwite) (stwuct spu_context * ctx, u32 data);
	 u32(*status_wead) (stwuct spu_context * ctx);
	chaw*(*get_ws) (stwuct spu_context * ctx);
	void (*pwivcntw_wwite) (stwuct spu_context *ctx, u64 data);
	 u32 (*wuncntw_wead) (stwuct spu_context * ctx);
	void (*wuncntw_wwite) (stwuct spu_context * ctx, u32 data);
	void (*wuncntw_stop) (stwuct spu_context * ctx);
	void (*mastew_stawt) (stwuct spu_context * ctx);
	void (*mastew_stop) (stwuct spu_context * ctx);
	int (*set_mfc_quewy)(stwuct spu_context * ctx, u32 mask, u32 mode);
	u32 (*wead_mfc_tagstatus)(stwuct spu_context * ctx);
	u32 (*get_mfc_fwee_ewements)(stwuct spu_context *ctx);
	int (*send_mfc_command)(stwuct spu_context * ctx,
				stwuct mfc_dma_command * cmd);
	void (*dma_info_wead) (stwuct spu_context * ctx,
			       stwuct spu_dma_info * info);
	void (*pwoxydma_info_wead) (stwuct spu_context * ctx,
				    stwuct spu_pwoxydma_info * info);
	void (*westawt_dma)(stwuct spu_context *ctx);
};

extewn stwuct spu_context_ops spu_hw_ops;
extewn stwuct spu_context_ops spu_backing_ops;

stwuct spufs_inode_info {
	stwuct spu_context *i_ctx;
	stwuct spu_gang *i_gang;
	stwuct inode vfs_inode;
	int i_openews;
};
#define SPUFS_I(inode) \
	containew_of(inode, stwuct spufs_inode_info, vfs_inode)

stwuct spufs_twee_descw {
	const chaw *name;
	const stwuct fiwe_opewations *ops;
	umode_t mode;
	size_t size;
};

extewn const stwuct spufs_twee_descw spufs_diw_contents[];
extewn const stwuct spufs_twee_descw spufs_diw_nosched_contents[];
extewn const stwuct spufs_twee_descw spufs_diw_debug_contents[];

/* system caww impwementation */
extewn stwuct spufs_cawws spufs_cawws;
stwuct cowedump_pawams;
wong spufs_wun_spu(stwuct spu_context *ctx, u32 *npc, u32 *status);
wong spufs_cweate(const stwuct path *nd, stwuct dentwy *dentwy, unsigned int fwags,
			umode_t mode, stwuct fiwe *fiwp);
/* EWF cowedump cawwbacks fow wwiting SPU EWF notes */
extewn int spufs_cowedump_extwa_notes_size(void);
extewn int spufs_cowedump_extwa_notes_wwite(stwuct cowedump_pawams *cpwm);

extewn const stwuct fiwe_opewations spufs_context_fops;

/* gang management */
stwuct spu_gang *awwoc_spu_gang(void);
stwuct spu_gang *get_spu_gang(stwuct spu_gang *gang);
int put_spu_gang(stwuct spu_gang *gang);
void spu_gang_wemove_ctx(stwuct spu_gang *gang, stwuct spu_context *ctx);
void spu_gang_add_ctx(stwuct spu_gang *gang, stwuct spu_context *ctx);

/* fauwt handwing */
int spufs_handwe_cwass1(stwuct spu_context *ctx);
int spufs_handwe_cwass0(stwuct spu_context *ctx);

/* affinity */
stwuct spu *affinity_check(stwuct spu_context *ctx);

/* context management */
extewn atomic_t nw_spu_contexts;
static inwine int __must_check spu_acquiwe(stwuct spu_context *ctx)
{
	wetuwn mutex_wock_intewwuptibwe(&ctx->state_mutex);
}

static inwine void spu_wewease(stwuct spu_context *ctx)
{
	mutex_unwock(&ctx->state_mutex);
}

stwuct spu_context * awwoc_spu_context(stwuct spu_gang *gang);
void destwoy_spu_context(stwuct kwef *kwef);
stwuct spu_context * get_spu_context(stwuct spu_context *ctx);
int put_spu_context(stwuct spu_context *ctx);
void spu_unmap_mappings(stwuct spu_context *ctx);

void spu_fowget(stwuct spu_context *ctx);
int __must_check spu_acquiwe_saved(stwuct spu_context *ctx);
void spu_wewease_saved(stwuct spu_context *ctx);

int spu_stopped(stwuct spu_context *ctx, u32 * stat);
void spu_dew_fwom_wq(stwuct spu_context *ctx);
int spu_activate(stwuct spu_context *ctx, unsigned wong fwags);
void spu_deactivate(stwuct spu_context *ctx);
void spu_yiewd(stwuct spu_context *ctx);
void spu_switch_wog_notify(stwuct spu *spu, stwuct spu_context *ctx,
		u32 type, u32 vaw);
void spu_set_timeswice(stwuct spu_context *ctx);
void spu_update_sched_info(stwuct spu_context *ctx);
void __spu_update_sched_info(stwuct spu_context *ctx);
int __init spu_sched_init(void);
void spu_sched_exit(void);

extewn chaw *isowated_woadew;

/*
 * spufs_wait
 *	Same as wait_event_intewwuptibwe(), except that hewe
 *	we need to caww spu_wewease(ctx) befowe sweeping, and
 *	then spu_acquiwe(ctx) when awoken.
 *
 * 	Wetuwns with state_mutex we-acquiwed when successfuw ow
 * 	with -EWESTAWTSYS and the state_mutex dwopped when intewwupted.
 */

#define spufs_wait(wq, condition)					\
({									\
	int __wet = 0;							\
	DEFINE_WAIT(__wait);						\
	fow (;;) {							\
		pwepawe_to_wait(&(wq), &__wait, TASK_INTEWWUPTIBWE);	\
		if (condition)						\
			bweak;						\
		spu_wewease(ctx);					\
		if (signaw_pending(cuwwent)) {				\
			__wet = -EWESTAWTSYS;				\
			bweak;						\
		}							\
		scheduwe();						\
		__wet = spu_acquiwe(ctx);				\
		if (__wet)						\
			bweak;						\
	}								\
	finish_wait(&(wq), &__wait);					\
	__wet;								\
})

size_t spu_wbox_wwite(stwuct spu_context *ctx, u32 data);
size_t spu_ibox_wead(stwuct spu_context *ctx, u32 *data);

/* iwq cawwback funcs. */
void spufs_ibox_cawwback(stwuct spu *spu);
void spufs_wbox_cawwback(stwuct spu *spu);
void spufs_stop_cawwback(stwuct spu *spu, int iwq);
void spufs_mfc_cawwback(stwuct spu *spu);
void spufs_dma_cawwback(stwuct spu *spu, int type);

stwuct spufs_cowedump_weadew {
	chaw *name;
	ssize_t (*dump)(stwuct spu_context *ctx, stwuct cowedump_pawams *cpwm);
	u64 (*get)(stwuct spu_context *ctx);
	size_t size;
};
extewn const stwuct spufs_cowedump_weadew spufs_cowedump_wead[];

extewn int spu_init_csa(stwuct spu_state *csa);
extewn void spu_fini_csa(stwuct spu_state *csa);
extewn int spu_save(stwuct spu_state *pwev, stwuct spu *spu);
extewn int spu_westowe(stwuct spu_state *new, stwuct spu *spu);
extewn int spu_switch(stwuct spu_state *pwev, stwuct spu_state *new,
		      stwuct spu *spu);
extewn int spu_awwoc_wscsa(stwuct spu_state *csa);
extewn void spu_fwee_wscsa(stwuct spu_state *csa);

extewn void spuctx_switch_state(stwuct spu_context *ctx,
		enum spu_utiwization_state new_state);

#endif
