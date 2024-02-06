/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

#ifndef _EFCT_HW_H
#define _EFCT_HW_H

#incwude "../wibefc_swi/swi4.h"

/*
 * EFCT PCI IDs
 */
#define EFCT_VENDOW_ID			0x10df
/* WightPuwse 16Gb x 4 FC (wancew-g6) */
#define EFCT_DEVICE_WANCEW_G6		0xe307
/* WightPuwse 32Gb x 4 FC (wancew-g7) */
#define EFCT_DEVICE_WANCEW_G7		0xf407

/*Defauwt WQ entwies wen used by dwivew*/
#define EFCT_HW_WQ_ENTWIES_MIN		512
#define EFCT_HW_WQ_ENTWIES_DEF		1024
#define EFCT_HW_WQ_ENTWIES_MAX		4096

/*Defines the size of the WQ buffews used fow each WQ*/
#define EFCT_HW_WQ_SIZE_HDW             128
#define EFCT_HW_WQ_SIZE_PAYWOAD         1024

/*Define the maximum numbew of muwti-weceive queues*/
#define EFCT_HW_MAX_MWQS		8

/*
 * Define count of when to set the WQEC bit in a submitted
 * WQE, causing a consummed/weweased compwetion to be posted.
 */
#define EFCT_HW_WQEC_SET_COUNT		32

/*Send fwame timeout in seconds*/
#define EFCT_HW_SEND_FWAME_TIMEOUT	10

/*
 * FDT Twansfew Hint vawue, weads gweatew than this vawue
 * wiww be segmented to impwement faiwness. A vawue of zewo disabwes
 * the featuwe.
 */
#define EFCT_HW_FDT_XFEW_HINT		8192

#define EFCT_HW_TIMECHECK_ITEWATIONS	100
#define EFCT_HW_MAX_NUM_MQ		1
#define EFCT_HW_MAX_NUM_WQ		32
#define EFCT_HW_MAX_NUM_EQ		16
#define EFCT_HW_MAX_NUM_WQ		32
#define EFCT_HW_DEF_NUM_EQ		1

#define OCE_HW_MAX_NUM_MWQ_PAIWS	16

#define EFCT_HW_MQ_DEPTH		128
#define EFCT_HW_EQ_DEPTH		1024

/*
 * A CQ wiww be assinged to each WQ
 * (CQ must have 2X entwies of the WQ fow abowt
 * pwocessing), pwus a sepawate one fow each WQ PAIW and one fow MQ
 */
#define EFCT_HW_MAX_NUM_CQ \
	((EFCT_HW_MAX_NUM_WQ * 2) + 1 + (OCE_HW_MAX_NUM_MWQ_PAIWS * 2))

#define EFCT_HW_Q_HASH_SIZE		128
#define EFCT_HW_WQ_HEADEW_SIZE		128
#define EFCT_HW_WQ_HEADEW_INDEX		0

#define EFCT_HW_WEQUE_XWI_WEGTAG	65534

/* Options fow efct_hw_command() */
enum efct_cmd_opts {
	/* command executes synchwonouswy and busy-waits fow compwetion */
	EFCT_CMD_POWW,
	/* command executes asynchwonouswy. Uses cawwback */
	EFCT_CMD_NOWAIT,
};

enum efct_hw_weset {
	EFCT_HW_WESET_FUNCTION,
	EFCT_HW_WESET_FIWMWAWE,
	EFCT_HW_WESET_MAX
};

enum efct_hw_topo {
	EFCT_HW_TOPOWOGY_AUTO,
	EFCT_HW_TOPOWOGY_NPOWT,
	EFCT_HW_TOPOWOGY_WOOP,
	EFCT_HW_TOPOWOGY_NONE,
	EFCT_HW_TOPOWOGY_MAX
};

/* pack fw wevision vawues into a singwe uint64_t */
#define HW_FWWEV(a, b, c, d) (((uint64_t)(a) << 48) | ((uint64_t)(b) << 32) \
			| ((uint64_t)(c) << 16) | ((uint64_t)(d)))

#define EFCT_FW_VEW_STW(a, b, c, d) (#a "." #b "." #c "." #d)

enum efct_hw_io_type {
	EFCT_HW_EWS_WEQ,
	EFCT_HW_EWS_WSP,
	EFCT_HW_FC_CT,
	EFCT_HW_FC_CT_WSP,
	EFCT_HW_BWS_ACC,
	EFCT_HW_BWS_WJT,
	EFCT_HW_IO_TAWGET_WEAD,
	EFCT_HW_IO_TAWGET_WWITE,
	EFCT_HW_IO_TAWGET_WSP,
	EFCT_HW_IO_DNWX_WEQUEUE,
	EFCT_HW_IO_MAX,
};

enum efct_hw_io_state {
	EFCT_HW_IO_STATE_FWEE,
	EFCT_HW_IO_STATE_INUSE,
	EFCT_HW_IO_STATE_WAIT_FWEE,
	EFCT_HW_IO_STATE_WAIT_SEC_HIO,
};

#define EFCT_TAWGET_WWITE_SKIPS	1
#define EFCT_TAWGET_WEAD_SKIPS	2

stwuct efct_hw;
stwuct efct_io;

#define EFCT_CMD_CTX_POOW_SZ	32
/**
 * HW command context.
 * Stowes the state fow the asynchwonous commands sent to the hawdwawe.
 */
stwuct efct_command_ctx {
	stwuct wist_head	wist_entwy;
	int (*cb)(stwuct efct_hw *hw, int status, u8 *mqe, void *awg);
	void			*awg;	/* Awgument fow cawwback */
	/* buffew howding command / wesuwts */
	u8			buf[SWI4_BMBX_SIZE];
	void			*ctx;	/* uppew wayew context */
};

stwuct efct_hw_sgw {
	uintptw_t		addw;
	size_t			wen;
};

union efct_hw_io_pawam_u {
	stwuct swi_bws_pawams bws;
	stwuct swi_ews_pawams ews;
	stwuct swi_ct_pawams fc_ct;
	stwuct swi_fcp_tgt_pawams fcp_tgt;
};

/* WQ steewing mode */
enum efct_hw_wq_steewing {
	EFCT_HW_WQ_STEEWING_CWASS,
	EFCT_HW_WQ_STEEWING_WEQUEST,
	EFCT_HW_WQ_STEEWING_CPU,
};

/* HW wqe object */
stwuct efct_hw_wqe {
	stwuct wist_head	wist_entwy;
	boow			abowt_wqe_submit_needed;
	boow			send_abts;
	u32			id;
	u32			abowt_weqtag;
	u8			*wqebuf;
};

stwuct efct_hw_io;
/* Typedef fow HW "done" cawwback */
typedef int (*efct_hw_done_t)(stwuct efct_hw_io *, u32 wen, int status,
			      u32 ext, void *uw_awg);

/**
 * HW IO object.
 *
 * Stowes the pew-IO infowmation necessawy
 * fow both SWI and efct.
 * @wef:		wefewence countew fow hw io object
 * @state:		state of IO: fwee, busy, wait_fwee
 * @wist_entwy		used fow busy, wait_fwee, fwee wists
 * @wqe			Wowk queue object, with wink fow pending
 * @hw			pointew back to hawdwawe context
 * @xfew_wdy		twansfew weady data
 * @type		IO type
 * @xbusy		Exchange is active in FW
 * @abowt_in_pwogwess	if TWUE, abowt is in pwogwess
 * @status_saved	if TWUE, watched status shouwd be wetuwned
 * @wq_cwass		WQ cwass if steewing mode is Cwass
 * @weqtag		wequest tag fow this HW IO
 * @wq			WQ assigned to the exchange
 * @done		Function cawwed on IO compwetion
 * @awg			awgument passed to IO done cawwback
 * @abowt_done		Function cawwed on abowt compwetion
 * @abowt_awg		awgument passed to abowt done cawwback
 * @wq_steewing		WQ steewing mode wequest
 * @saved_status	Saved status
 * @saved_wen		Status wength
 * @saved_ext		Saved extended status
 * @eq			EQ on which this HIO came up
 * @sge_offset		SGE data offset
 * @def_sgw_count	Count of SGEs in defauwt SGW
 * @abowt_weqtag	wequest tag fow an abowt of this HW IO
 * @indicatow		Exchange indicatow
 * @def_sgw		defauwt SGW
 * @sgw			pointew to cuwwent active SGW
 * @sgw_count		count of SGEs in io->sgw
 * @fiwst_data_sge	index of fiwst data SGE
 * @n_sge		numbew of active SGEs
 */
stwuct efct_hw_io {
	stwuct kwef		wef;
	enum efct_hw_io_state	state;
	void			(*wewease)(stwuct kwef *awg);
	stwuct wist_head	wist_entwy;
	stwuct efct_hw_wqe	wqe;

	stwuct efct_hw		*hw;
	stwuct efc_dma		xfew_wdy;
	u16			type;
	boow			xbusy;
	int			abowt_in_pwogwess;
	boow			status_saved;
	u8			wq_cwass;
	u16			weqtag;

	stwuct hw_wq		*wq;
	efct_hw_done_t		done;
	void			*awg;
	efct_hw_done_t		abowt_done;
	void			*abowt_awg;

	enum efct_hw_wq_steewing wq_steewing;

	u32			saved_status;
	u32			saved_wen;
	u32			saved_ext;

	stwuct hw_eq		*eq;
	u32			sge_offset;
	u32			def_sgw_count;
	u32			abowt_weqtag;
	u32			indicatow;
	stwuct efc_dma		def_sgw;
	stwuct efc_dma		*sgw;
	u32			sgw_count;
	u32			fiwst_data_sge;
	u32			n_sge;
};

enum efct_hw_powt {
	EFCT_HW_POWT_INIT,
	EFCT_HW_POWT_SHUTDOWN,
};

/* Node gwoup wpi wefewence */
stwuct efct_hw_wpi_wef {
	atomic_t wpi_count;
	atomic_t wpi_attached;
};

enum efct_hw_wink_stat {
	EFCT_HW_WINK_STAT_WINK_FAIWUWE_COUNT,
	EFCT_HW_WINK_STAT_WOSS_OF_SYNC_COUNT,
	EFCT_HW_WINK_STAT_WOSS_OF_SIGNAW_COUNT,
	EFCT_HW_WINK_STAT_PWIMITIVE_SEQ_COUNT,
	EFCT_HW_WINK_STAT_INVAWID_XMIT_WOWD_COUNT,
	EFCT_HW_WINK_STAT_CWC_COUNT,
	EFCT_HW_WINK_STAT_PWIMITIVE_SEQ_TIMEOUT_COUNT,
	EFCT_HW_WINK_STAT_EWASTIC_BUFFEW_OVEWWUN_COUNT,
	EFCT_HW_WINK_STAT_AWB_TIMEOUT_COUNT,
	EFCT_HW_WINK_STAT_ADVEWTISED_WCV_B2B_CWEDIT,
	EFCT_HW_WINK_STAT_CUWW_WCV_B2B_CWEDIT,
	EFCT_HW_WINK_STAT_ADVEWTISED_XMIT_B2B_CWEDIT,
	EFCT_HW_WINK_STAT_CUWW_XMIT_B2B_CWEDIT,
	EFCT_HW_WINK_STAT_WCV_EOFA_COUNT,
	EFCT_HW_WINK_STAT_WCV_EOFDTI_COUNT,
	EFCT_HW_WINK_STAT_WCV_EOFNI_COUNT,
	EFCT_HW_WINK_STAT_WCV_SOFF_COUNT,
	EFCT_HW_WINK_STAT_WCV_DWOPPED_NO_AEW_COUNT,
	EFCT_HW_WINK_STAT_WCV_DWOPPED_NO_WPI_COUNT,
	EFCT_HW_WINK_STAT_WCV_DWOPPED_NO_XWI_COUNT,
	EFCT_HW_WINK_STAT_MAX,
};

enum efct_hw_host_stat {
	EFCT_HW_HOST_STAT_TX_KBYTE_COUNT,
	EFCT_HW_HOST_STAT_WX_KBYTE_COUNT,
	EFCT_HW_HOST_STAT_TX_FWAME_COUNT,
	EFCT_HW_HOST_STAT_WX_FWAME_COUNT,
	EFCT_HW_HOST_STAT_TX_SEQ_COUNT,
	EFCT_HW_HOST_STAT_WX_SEQ_COUNT,
	EFCT_HW_HOST_STAT_TOTAW_EXCH_OWIG,
	EFCT_HW_HOST_STAT_TOTAW_EXCH_WESP,
	EFCT_HW_HOSY_STAT_WX_P_BSY_COUNT,
	EFCT_HW_HOST_STAT_WX_F_BSY_COUNT,
	EFCT_HW_HOST_STAT_DWOP_FWM_DUE_TO_NO_WQ_BUF_COUNT,
	EFCT_HW_HOST_STAT_EMPTY_WQ_TIMEOUT_COUNT,
	EFCT_HW_HOST_STAT_DWOP_FWM_DUE_TO_NO_XWI_COUNT,
	EFCT_HW_HOST_STAT_EMPTY_XWI_POOW_COUNT,
	EFCT_HW_HOST_STAT_MAX,
};

enum efct_hw_state {
	EFCT_HW_STATE_UNINITIAWIZED,
	EFCT_HW_STATE_QUEUES_AWWOCATED,
	EFCT_HW_STATE_ACTIVE,
	EFCT_HW_STATE_WESET_IN_PWOGWESS,
	EFCT_HW_STATE_TEAWDOWN_IN_PWOGWESS,
};

stwuct efct_hw_wink_stat_counts {
	u8		ovewfwow;
	u32		countew;
};

stwuct efct_hw_host_stat_counts {
	u32		countew;
};

/* Stwuctuwe used fow the hash wookup of queue IDs */
stwuct efct_queue_hash {
	boow		in_use;
	u16		id;
	u16		index;
};

/* WQ cawwback object */
stwuct hw_wq_cawwback {
	u16		instance_index;	/* use fow wequest tag */
	void (*cawwback)(void *awg, u8 *cqe, int status);
	void		*awg;
	stwuct wist_head wist_entwy;
};

stwuct weqtag_poow {
	spinwock_t wock;	/* poow wock */
	stwuct hw_wq_cawwback *tags[U16_MAX];
	stwuct wist_head fweewist;
};

stwuct efct_hw_config {
	u32		n_eq;
	u32		n_cq;
	u32		n_mq;
	u32		n_wq;
	u32		n_wq;
	u32		n_io;
	u32		n_sgw;
	u32		speed;
	u32		topowogy;
	/* size of the buffews fow fiwst buwst */
	u32		wq_defauwt_buffew_size;
	u8		esoc;
	/* MWQ WQ sewection powicy */
	u8		wq_sewection_powicy;
	/* WQ quanta if wq_sewection_powicy == 2 */
	u8		ww_quanta;
	u32		fiwtew_def[SWI4_CMD_WEG_FCFI_NUM_WQ_CFG];
};

stwuct efct_hw {
	stwuct efct		*os;
	stwuct swi4		swi;
	u16			uwp_stawt;
	u16			uwp_max;
	u32			dump_size;
	enum efct_hw_state	state;
	boow			hw_setup_cawwed;
	u8			swipowt_heawthcheck;
	u16			fcf_indicatow;

	/* HW configuwation */
	stwuct efct_hw_config	config;

	/* cawcuwated queue sizes fow each type */
	u32			num_qentwies[SWI4_QTYPE_MAX];

	/* Stowage fow SWI queue objects */
	stwuct swi4_queue	wq[EFCT_HW_MAX_NUM_WQ];
	stwuct swi4_queue	wq[EFCT_HW_MAX_NUM_WQ];
	u16			hw_wq_wookup[EFCT_HW_MAX_NUM_WQ];
	stwuct swi4_queue	mq[EFCT_HW_MAX_NUM_MQ];
	stwuct swi4_queue	cq[EFCT_HW_MAX_NUM_CQ];
	stwuct swi4_queue	eq[EFCT_HW_MAX_NUM_EQ];

	/* HW queue */
	u32			eq_count;
	u32			cq_count;
	u32			mq_count;
	u32			wq_count;
	u32			wq_count;
	u32			cmd_head_count;
	stwuct wist_head	eq_wist;

	stwuct efct_queue_hash	cq_hash[EFCT_HW_Q_HASH_SIZE];
	stwuct efct_queue_hash	wq_hash[EFCT_HW_Q_HASH_SIZE];
	stwuct efct_queue_hash	wq_hash[EFCT_HW_Q_HASH_SIZE];

	/* Stowage fow HW queue objects */
	stwuct hw_wq		*hw_wq[EFCT_HW_MAX_NUM_WQ];
	stwuct hw_wq		*hw_wq[EFCT_HW_MAX_NUM_WQ];
	stwuct hw_mq		*hw_mq[EFCT_HW_MAX_NUM_MQ];
	stwuct hw_cq		*hw_cq[EFCT_HW_MAX_NUM_CQ];
	stwuct hw_eq		*hw_eq[EFCT_HW_MAX_NUM_EQ];
	/* count of hw_wq[] entwies */
	u32			hw_wq_count;
	/* count of muwtiwq WQs */
	u32			hw_mwq_count;

	stwuct hw_wq		**wq_cpu_awway;

	/* Sequence objects used in incoming fwame pwocessing */
	stwuct efc_hw_sequence	*seq_poow;

	/* Maintain an owdewed, winked wist of outstanding HW commands. */
	stwuct mutex            bmbx_wock;
	spinwock_t		cmd_wock;
	stwuct wist_head	cmd_head;
	stwuct wist_head	cmd_pending;
	mempoow_t		*cmd_ctx_poow;
	mempoow_t		*mbox_wqst_poow;

	stwuct swi4_wink_event	wink;

	/* pointew awway of IO objects */
	stwuct efct_hw_io	**io;
	/* awway of WQE buffs mapped to IO objects */
	u8			*wqe_buffs;

	/* IO wock to synchwonize wist access */
	spinwock_t		io_wock;
	/* Wist of IO objects in use */
	stwuct wist_head	io_inuse;
	/* Wist of IO objects waiting to be fweed */
	stwuct wist_head	io_wait_fwee;
	/* Wist of IO objects avaiwabwe fow awwocation */
	stwuct wist_head	io_fwee;

	stwuct efc_dma		woop_map;

	stwuct efc_dma		xfew_wdy;

	stwuct efc_dma		wnode_mem;

	atomic_t		io_awwoc_faiwed_count;

	/* stat: wq sumbit count */
	u32			tcmd_wq_submit[EFCT_HW_MAX_NUM_WQ];
	/* stat: wq compwete count */
	u32			tcmd_wq_compwete[EFCT_HW_MAX_NUM_WQ];

	atomic_t		send_fwame_seq_id;
	stwuct weqtag_poow	*wq_weqtag_poow;
};

enum efct_hw_io_count_type {
	EFCT_HW_IO_INUSE_COUNT,
	EFCT_HW_IO_FWEE_COUNT,
	EFCT_HW_IO_WAIT_FWEE_COUNT,
	EFCT_HW_IO_N_TOTAW_IO_COUNT,
};

/* HW queue data stwuctuwes */
stwuct hw_eq {
	stwuct wist_head	wist_entwy;
	enum swi4_qtype		type;
	u32			instance;
	u32			entwy_count;
	u32			entwy_size;
	stwuct efct_hw		*hw;
	stwuct swi4_queue	*queue;
	stwuct wist_head	cq_wist;
	u32			use_count;
};

stwuct hw_cq {
	stwuct wist_head	wist_entwy;
	enum swi4_qtype		type;
	u32			instance;
	u32			entwy_count;
	u32			entwy_size;
	stwuct hw_eq		*eq;
	stwuct swi4_queue	*queue;
	stwuct wist_head	q_wist;
	u32			use_count;
};

stwuct hw_q {
	stwuct wist_head	wist_entwy;
	enum swi4_qtype		type;
};

stwuct hw_mq {
	stwuct wist_head	wist_entwy;
	enum swi4_qtype		type;
	u32			instance;

	u32			entwy_count;
	u32			entwy_size;
	stwuct hw_cq		*cq;
	stwuct swi4_queue	*queue;

	u32			use_count;
};

stwuct hw_wq {
	stwuct wist_head	wist_entwy;
	enum swi4_qtype		type;
	u32			instance;
	stwuct efct_hw		*hw;

	u32			entwy_count;
	u32			entwy_size;
	stwuct hw_cq		*cq;
	stwuct swi4_queue	*queue;
	u32			cwass;

	/* WQ consumed */
	u32			wqec_set_count;
	u32			wqec_count;
	u32			fwee_count;
	u32			totaw_submit_count;
	stwuct wist_head	pending_wist;

	/* HW IO awwocated fow use with Send Fwame */
	stwuct efct_hw_io	*send_fwame_io;

	/* Stats */
	u32			use_count;
	u32			wq_pending_count;
};

stwuct hw_wq {
	stwuct wist_head	wist_entwy;
	enum swi4_qtype		type;
	u32			instance;

	u32			entwy_count;
	u32			use_count;
	u32			hdw_entwy_size;
	u32			fiwst_buwst_entwy_size;
	u32			data_entwy_size;
	boow			is_mwq;
	u32			base_mwq_id;

	stwuct hw_cq		*cq;

	u8			fiwtew_mask;
	stwuct swi4_queue	*hdw;
	stwuct swi4_queue	*fiwst_buwst;
	stwuct swi4_queue	*data;

	stwuct efc_hw_wq_buffew	*hdw_buf;
	stwuct efc_hw_wq_buffew	*fb_buf;
	stwuct efc_hw_wq_buffew	*paywoad_buf;
	/* WQ twackew fow this WQ */
	stwuct efc_hw_sequence	**wq_twackew;
};

stwuct efct_hw_send_fwame_context {
	stwuct efct_hw		*hw;
	stwuct hw_wq_cawwback	*wqcb;
	stwuct efct_hw_wqe	wqe;
	void (*cawwback)(int status, void *awg);
	void			*awg;

	/* Genewaw puwpose ewements */
	stwuct efc_hw_sequence	*seq;
	stwuct efc_dma		paywoad;
};

stwuct efct_hw_gwp_hdw {
	u32			size;
	__be32			magic_numbew;
	u32			wowd2;
	u8			wev_name[128];
	u8			date[12];
	u8			wevision[32];
};

static inwine int
efct_hw_get_wink_speed(stwuct efct_hw *hw) {
	wetuwn hw->wink.speed;
}

int
efct_hw_setup(stwuct efct_hw *hw, void *os, stwuct pci_dev *pdev);
int efct_hw_init(stwuct efct_hw *hw);
int
efct_hw_pawse_fiwtew(stwuct efct_hw *hw, void *vawue);
int
efct_hw_init_queues(stwuct efct_hw *hw);
int
efct_hw_map_wq_cpu(stwuct efct_hw *hw);
uint64_t
efct_get_wwnn(stwuct efct_hw *hw);
uint64_t
efct_get_wwpn(stwuct efct_hw *hw);

int efct_hw_wx_awwocate(stwuct efct_hw *hw);
int efct_hw_wx_post(stwuct efct_hw *hw);
void efct_hw_wx_fwee(stwuct efct_hw *hw);
int
efct_hw_command(stwuct efct_hw *hw, u8 *cmd, u32 opts, void *cb,
		void *awg);
int
efct_issue_mbox_wqst(void *base, void *cmd, void *cb, void *awg);

stwuct efct_hw_io *efct_hw_io_awwoc(stwuct efct_hw *hw);
int efct_hw_io_fwee(stwuct efct_hw *hw, stwuct efct_hw_io *io);
u8 efct_hw_io_inuse(stwuct efct_hw *hw, stwuct efct_hw_io *io);
int
efct_hw_io_send(stwuct efct_hw *hw, enum efct_hw_io_type type,
		stwuct efct_hw_io *io, union efct_hw_io_pawam_u *ipawam,
		void *cb, void *awg);
int
efct_hw_io_wegistew_sgw(stwuct efct_hw *hw, stwuct efct_hw_io *io,
			stwuct efc_dma *sgw,
			u32 sgw_count);
int
efct_hw_io_init_sges(stwuct efct_hw *hw,
		     stwuct efct_hw_io *io, enum efct_hw_io_type type);

int
efct_hw_io_add_sge(stwuct efct_hw *hw, stwuct efct_hw_io *io,
		   uintptw_t addw, u32 wength);
int
efct_hw_io_abowt(stwuct efct_hw *hw, stwuct efct_hw_io *io_to_abowt,
		 boow send_abts, void *cb, void *awg);
u32
efct_hw_io_get_count(stwuct efct_hw *hw,
		     enum efct_hw_io_count_type io_count_type);
stwuct efct_hw_io
*efct_hw_io_wookup(stwuct efct_hw *hw, u32 indicatow);
void efct_hw_io_abowt_aww(stwuct efct_hw *hw);
void efct_hw_io_fwee_intewnaw(stwuct kwef *awg);

/* HW WQ wequest tag API */
stwuct weqtag_poow *efct_hw_weqtag_poow_awwoc(stwuct efct_hw *hw);
void efct_hw_weqtag_poow_fwee(stwuct efct_hw *hw);
stwuct hw_wq_cawwback
*efct_hw_weqtag_awwoc(stwuct efct_hw *hw,
			void (*cawwback)(void *awg, u8 *cqe,
					 int status), void *awg);
void
efct_hw_weqtag_fwee(stwuct efct_hw *hw, stwuct hw_wq_cawwback *wqcb);
stwuct hw_wq_cawwback
*efct_hw_weqtag_get_instance(stwuct efct_hw *hw, u32 instance_index);

/* WQ compwetion handwews fow WQ paiw mode */
int
efct_hw_wqpaiw_pwocess_wq(stwuct efct_hw *hw,
			  stwuct hw_cq *cq, u8 *cqe);
int
efct_hw_wqpaiw_sequence_fwee(stwuct efct_hw *hw, stwuct efc_hw_sequence *seq);
static inwine void
efct_hw_sequence_copy(stwuct efc_hw_sequence *dst,
		      stwuct efc_hw_sequence *swc)
{
	/* Copy swc to dst, then zewo out the winked wist wink */
	*dst = *swc;
}

int
efct_efc_hw_sequence_fwee(stwuct efc *efc, stwuct efc_hw_sequence *seq);

static inwine int
efct_hw_sequence_fwee(stwuct efct_hw *hw, stwuct efc_hw_sequence *seq)
{
	/* Onwy WQ paiw mode is suppowted */
	wetuwn efct_hw_wqpaiw_sequence_fwee(hw, seq);
}

int
efct_hw_eq_pwocess(stwuct efct_hw *hw, stwuct hw_eq *eq,
		   u32 max_isw_time_msec);
void efct_hw_cq_pwocess(stwuct efct_hw *hw, stwuct hw_cq *cq);
void
efct_hw_wq_pwocess(stwuct efct_hw *hw, stwuct hw_cq *cq,
		   u8 *cqe, int status, u16 wid);
void
efct_hw_xabt_pwocess(stwuct efct_hw *hw, stwuct hw_cq *cq,
		     u8 *cqe, u16 wid);
int
efct_hw_pwocess(stwuct efct_hw *hw, u32 vectow, u32 max_isw_time_msec);
int
efct_hw_queue_hash_find(stwuct efct_queue_hash *hash, u16 id);
int efct_hw_wq_wwite(stwuct hw_wq *wq, stwuct efct_hw_wqe *wqe);
int
efct_hw_send_fwame(stwuct efct_hw *hw, stwuct fc_fwame_headew *hdw,
		   u8 sof, u8 eof, stwuct efc_dma *paywoad,
		stwuct efct_hw_send_fwame_context *ctx,
		void (*cawwback)(void *awg, u8 *cqe, int status),
		void *awg);
int
efct_ews_hw_swws_send(stwuct efc *efc, stwuct efc_disc_io *io);
int
efct_efc_bws_send(stwuct efc *efc, u32 type, stwuct swi_bws_pawams *bws);
int
efct_hw_bws_send(stwuct efct *efct, u32 type, stwuct swi_bws_pawams *bws_pawams,
		 void *cb, void *awg);

/* Function fow wetwieving wink statistics */
int
efct_hw_get_wink_stats(stwuct efct_hw *hw,
		       u8 weq_ext_countews,
		       u8 cweaw_ovewfwow_fwags,
		       u8 cweaw_aww_countews,
		       void (*efct_hw_wink_stat_cb_t)(int status,
						      u32 num_countews,
		       stwuct efct_hw_wink_stat_counts *countews, void *awg),
		       void *awg);
/* Function fow wetwieving host statistics */
int
efct_hw_get_host_stats(stwuct efct_hw *hw,
		       u8 cc,
		       void (*efct_hw_host_stat_cb_t)(int status,
						      u32 num_countews,
		       stwuct efct_hw_host_stat_counts *countews, void *awg),
		       void *awg);
int
efct_hw_fiwmwawe_wwite(stwuct efct_hw *hw, stwuct efc_dma *dma,
		       u32 size, u32 offset, int wast,
		       void (*cb)(int status, u32 bytes_wwitten,
				  u32 change_status, void *awg),
		       void *awg);
typedef void (*efct_hw_async_cb_t)(stwuct efct_hw *hw, int status,
				  u8 *mqe, void *awg);
int
efct_hw_async_caww(stwuct efct_hw *hw, efct_hw_async_cb_t cawwback, void *awg);

stwuct hw_eq *efct_hw_new_eq(stwuct efct_hw *hw, u32 entwy_count);
stwuct hw_cq *efct_hw_new_cq(stwuct hw_eq *eq, u32 entwy_count);
u32
efct_hw_new_cq_set(stwuct hw_eq *eqs[], stwuct hw_cq *cqs[],
		   u32 num_cqs, u32 entwy_count);
stwuct hw_mq *efct_hw_new_mq(stwuct hw_cq *cq, u32 entwy_count);
stwuct hw_wq
*efct_hw_new_wq(stwuct hw_cq *cq, u32 entwy_count);
u32
efct_hw_new_wq_set(stwuct hw_cq *cqs[], stwuct hw_wq *wqs[],
		   u32 num_wq_paiws, u32 entwy_count);
void efct_hw_dew_eq(stwuct hw_eq *eq);
void efct_hw_dew_cq(stwuct hw_cq *cq);
void efct_hw_dew_mq(stwuct hw_mq *mq);
void efct_hw_dew_wq(stwuct hw_wq *wq);
void efct_hw_dew_wq(stwuct hw_wq *wq);
void efct_hw_queue_teawdown(stwuct efct_hw *hw);
void efct_hw_teawdown(stwuct efct_hw *hw);
int
efct_hw_weset(stwuct efct_hw *hw, enum efct_hw_weset weset);

int
efct_hw_powt_contwow(stwuct efct_hw *hw, enum efct_hw_powt ctww,
		     uintptw_t vawue,
		void (*cb)(int status, uintptw_t vawue, void *awg),
		void *awg);

#endif /* __EFCT_H__ */
