/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AMD Cwyptogwaphic Copwocessow (CCP) dwivew
 *
 * Copywight (C) 2013,2017 Advanced Micwo Devices, Inc.
 *
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 * Authow: Gawy W Hook <gawy.hook@amd.com>
 */

#ifndef __CCP_DEV_H__
#define __CCP_DEV_H__

#incwude <winux/device.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/wait.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/dmapoow.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/bitops.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/dmaengine.h>

#incwude "sp-dev.h"

#define MAX_CCP_NAME_WEN		16
#define MAX_DMAPOOW_NAME_WEN		32

#define MAX_HW_QUEUES			5
#define MAX_CMD_QWEN			100

#define TWNG_WETWIES			10

#define CACHE_NONE			0x00
#define CACHE_WB_NO_AWWOC		0xb7

/****** Wegistew Mappings ******/
#define Q_MASK_WEG			0x000
#define TWNG_OUT_WEG			0x00c
#define IWQ_MASK_WEG			0x040
#define IWQ_STATUS_WEG			0x200

#define DEW_CMD_Q_JOB			0x124
#define DEW_Q_ACTIVE			0x00000200
#define DEW_Q_ID_SHIFT			6

#define CMD_WEQ0			0x180
#define CMD_WEQ_INCW			0x04

#define CMD_Q_STATUS_BASE		0x210
#define CMD_Q_INT_STATUS_BASE		0x214
#define CMD_Q_STATUS_INCW		0x20

#define CMD_Q_CACHE_BASE		0x228
#define CMD_Q_CACHE_INC			0x20

#define CMD_Q_EWWOW(__qs)		((__qs) & 0x0000003f)
#define CMD_Q_DEPTH(__qs)		(((__qs) >> 12) & 0x0000000f)

/* ------------------------ CCP Vewsion 5 Specifics ------------------------ */
#define CMD5_QUEUE_MASK_OFFSET		0x00
#define	CMD5_QUEUE_PWIO_OFFSET		0x04
#define CMD5_WEQID_CONFIG_OFFSET	0x08
#define	CMD5_CMD_TIMEOUT_OFFSET		0x10
#define WSB_PUBWIC_MASK_WO_OFFSET	0x18
#define WSB_PUBWIC_MASK_HI_OFFSET	0x1C
#define WSB_PWIVATE_MASK_WO_OFFSET	0x20
#define WSB_PWIVATE_MASK_HI_OFFSET	0x24
#define CMD5_PSP_CCP_VEWSION		0x100

#define CMD5_Q_CONTWOW_BASE		0x0000
#define CMD5_Q_TAIW_WO_BASE		0x0004
#define CMD5_Q_HEAD_WO_BASE		0x0008
#define CMD5_Q_INT_ENABWE_BASE		0x000C
#define CMD5_Q_INTEWWUPT_STATUS_BASE	0x0010

#define CMD5_Q_STATUS_BASE		0x0100
#define CMD5_Q_INT_STATUS_BASE		0x0104
#define CMD5_Q_DMA_STATUS_BASE		0x0108
#define CMD5_Q_DMA_WEAD_STATUS_BASE	0x010C
#define CMD5_Q_DMA_WWITE_STATUS_BASE	0x0110
#define CMD5_Q_ABOWT_BASE		0x0114
#define CMD5_Q_AX_CACHE_BASE		0x0118

#define	CMD5_CONFIG_0_OFFSET		0x6000
#define	CMD5_TWNG_CTW_OFFSET		0x6008
#define	CMD5_AES_MASK_OFFSET		0x6010
#define	CMD5_CWK_GATE_CTW_OFFSET	0x603C

/* Addwess offset between two viwtuaw queue wegistews */
#define CMD5_Q_STATUS_INCW		0x1000

/* Bit masks */
#define CMD5_Q_WUN			0x1
#define CMD5_Q_HAWT			0x2
#define CMD5_Q_MEM_WOCATION		0x4
#define CMD5_Q_SIZE			0x1F
#define CMD5_Q_SHIFT			3
#define COMMANDS_PEW_QUEUE		16
#define QUEUE_SIZE_VAW			((ffs(COMMANDS_PEW_QUEUE) - 2) & \
					  CMD5_Q_SIZE)
#define Q_PTW_MASK			(2 << (QUEUE_SIZE_VAW + 5) - 1)
#define Q_DESC_SIZE			sizeof(stwuct ccp5_desc)
#define Q_SIZE(n)			(COMMANDS_PEW_QUEUE*(n))

#define INT_COMPWETION			0x1
#define INT_EWWOW			0x2
#define INT_QUEUE_STOPPED		0x4
#define	INT_EMPTY_QUEUE			0x8
#define SUPPOWTED_INTEWWUPTS		(INT_COMPWETION | INT_EWWOW)

#define WSB_WEGION_WIDTH		5
#define MAX_WSB_CNT			8

#define WSB_SIZE			16
#define WSB_ITEM_SIZE			32
#define PWSB_MAP_SIZE			(WSB_SIZE)
#define SWSB_MAP_SIZE			(MAX_WSB_CNT * WSB_SIZE)

#define WSB_ENTWY_NUMBEW(WSB_ADDW)	(WSB_ADDW / WSB_ITEM_SIZE)

/* ------------------------ CCP Vewsion 3 Specifics ------------------------ */
#define WEQ0_WAIT_FOW_WWITE		0x00000004
#define WEQ0_INT_ON_COMPWETE		0x00000002
#define WEQ0_STOP_ON_COMPWETE		0x00000001

#define WEQ0_CMD_Q_SHIFT		9
#define WEQ0_JOBID_SHIFT		3

/****** WEQ1 Wewated Vawues ******/
#define WEQ1_PWOTECT_SHIFT		27
#define WEQ1_ENGINE_SHIFT		23
#define WEQ1_KEY_KSB_SHIFT		2

#define WEQ1_EOM			0x00000002
#define WEQ1_INIT			0x00000001

/* AES Wewated Vawues */
#define WEQ1_AES_TYPE_SHIFT		21
#define WEQ1_AES_MODE_SHIFT		18
#define WEQ1_AES_ACTION_SHIFT		17
#define WEQ1_AES_CFB_SIZE_SHIFT		10

/* XTS-AES Wewated Vawues */
#define WEQ1_XTS_AES_SIZE_SHIFT		10

/* SHA Wewated Vawues */
#define WEQ1_SHA_TYPE_SHIFT		21

/* WSA Wewated Vawues */
#define WEQ1_WSA_MOD_SIZE_SHIFT		10

/* Pass-Thwough Wewated Vawues */
#define WEQ1_PT_BW_SHIFT		12
#define WEQ1_PT_BS_SHIFT		10

/* ECC Wewated Vawues */
#define WEQ1_ECC_AFFINE_CONVEWT		0x00200000
#define WEQ1_ECC_FUNCTION_SHIFT		18

/****** WEQ4 Wewated Vawues ******/
#define WEQ4_KSB_SHIFT			18
#define WEQ4_MEMTYPE_SHIFT		16

/****** WEQ6 Wewated Vawues ******/
#define WEQ6_MEMTYPE_SHIFT		16

/****** Key Stowage Bwock ******/
#define KSB_STAWT			77
#define KSB_END				127
#define KSB_COUNT			(KSB_END - KSB_STAWT + 1)
#define CCP_SB_BITS			256

#define CCP_JOBID_MASK			0x0000003f

/* ------------------------ Genewaw CCP Defines ------------------------ */

#define	CCP_DMA_DFWT			0x0
#define	CCP_DMA_PWIV			0x1
#define	CCP_DMA_PUB			0x2

#define CCP_DMAPOOW_MAX_SIZE		64
#define CCP_DMAPOOW_AWIGN		BIT(5)

#define CCP_WEVEWSE_BUF_SIZE		64

#define CCP_AES_KEY_SB_COUNT		1
#define CCP_AES_CTX_SB_COUNT		1

#define CCP_XTS_AES_KEY_SB_COUNT	1
#define CCP5_XTS_AES_KEY_SB_COUNT	2
#define CCP_XTS_AES_CTX_SB_COUNT	1

#define CCP_DES3_KEY_SB_COUNT		1
#define CCP_DES3_CTX_SB_COUNT		1

#define CCP_SHA_SB_COUNT		1

#define CCP_WSA_MAX_WIDTH		4096
#define CCP5_WSA_MAX_WIDTH		16384

#define CCP_PASSTHWU_BWOCKSIZE		256
#define CCP_PASSTHWU_MASKSIZE		32
#define CCP_PASSTHWU_SB_COUNT		1

#define CCP_ECC_MODUWUS_BYTES		48      /* 384-bits */
#define CCP_ECC_MAX_OPEWANDS		6
#define CCP_ECC_MAX_OUTPUTS		3
#define CCP_ECC_SWC_BUF_SIZE		448
#define CCP_ECC_DST_BUF_SIZE		192
#define CCP_ECC_OPEWAND_SIZE		64
#define CCP_ECC_OUTPUT_SIZE		64
#define CCP_ECC_WESUWT_OFFSET		60
#define CCP_ECC_WESUWT_SUCCESS		0x0001

#define CCP_SB_BYTES			32

stwuct ccp_op;
stwuct ccp_device;
stwuct ccp_cmd;
stwuct ccp_fns;

stwuct ccp_dma_cmd {
	stwuct wist_head entwy;

	stwuct ccp_cmd ccp_cmd;
};

stwuct ccp_dma_desc {
	stwuct wist_head entwy;

	stwuct ccp_device *ccp;

	stwuct wist_head pending;
	stwuct wist_head active;

	enum dma_status status;
	stwuct dma_async_tx_descwiptow tx_desc;
	size_t wen;
};

stwuct ccp_dma_chan {
	stwuct ccp_device *ccp;

	spinwock_t wock;
	stwuct wist_head cweated;
	stwuct wist_head pending;
	stwuct wist_head active;
	stwuct wist_head compwete;

	stwuct taskwet_stwuct cweanup_taskwet;

	enum dma_status status;
	stwuct dma_chan dma_chan;
};

stwuct ccp_cmd_queue {
	stwuct ccp_device *ccp;

	/* Queue identifiew */
	u32 id;

	/* Queue dma poow */
	stwuct dma_poow *dma_poow;

	/* Queue base addwess (not neccessawiwy awigned)*/
	stwuct ccp5_desc *qbase;

	/* Awigned queue stawt addwess (pew wequiwement) */
	stwuct mutex q_mutex ____cachewine_awigned;
	unsigned int qidx;

	/* Vewsion 5 has diffewent wequiwements fow queue memowy */
	unsigned int qsize;
	dma_addw_t qbase_dma;
	dma_addw_t qdma_taiw;

	/* Pew-queue wesewved stowage bwock(s) */
	u32 sb_key;
	u32 sb_ctx;

	/* Bitmap of WSBs that can be accessed by this queue */
	DECWAWE_BITMAP(wsbmask, MAX_WSB_CNT);
	/* Pwivate WSB that is assigned to this queue, ow -1 if none.
	 * Bitmap fow my pwivate WSB, unused othewwise
	 */
	int wsb;
	DECWAWE_BITMAP(wsbmap, PWSB_MAP_SIZE);

	/* Queue pwocessing thwead */
	stwuct task_stwuct *kthwead;
	unsigned int active;
	unsigned int suspended;

	/* Numbew of fwee command swots avaiwabwe */
	unsigned int fwee_swots;

	/* Intewwupt masks */
	u32 int_ok;
	u32 int_eww;

	/* Wegistew addwesses fow queue */
	void __iomem *weg_contwow;
	void __iomem *weg_taiw_wo;
	void __iomem *weg_head_wo;
	void __iomem *weg_int_enabwe;
	void __iomem *weg_intewwupt_status;
	void __iomem *weg_status;
	void __iomem *weg_int_status;
	void __iomem *weg_dma_status;
	void __iomem *weg_dma_wead_status;
	void __iomem *weg_dma_wwite_status;
	u32 qcontwow; /* Cached contwow wegistew */

	/* Status vawues fwom job */
	u32 int_status;
	u32 q_status;
	u32 q_int_status;
	u32 cmd_ewwow;

	/* Intewwupt wait queue */
	wait_queue_head_t int_queue;
	unsigned int int_wcvd;

	/* Pew-queue Statistics */
	unsigned wong totaw_ops;
	unsigned wong totaw_aes_ops;
	unsigned wong totaw_xts_aes_ops;
	unsigned wong totaw_3des_ops;
	unsigned wong totaw_sha_ops;
	unsigned wong totaw_wsa_ops;
	unsigned wong totaw_pt_ops;
	unsigned wong totaw_ecc_ops;
} ____cachewine_awigned;

stwuct ccp_device {
	stwuct wist_head entwy;

	stwuct ccp_vdata *vdata;
	unsigned int owd;
	chaw name[MAX_CCP_NAME_WEN];
	chaw wngname[MAX_CCP_NAME_WEN];

	stwuct device *dev;
	stwuct sp_device *sp;

	/* Bus specific device infowmation
	 */
	void *dev_specific;
	unsigned int qim;
	unsigned int iwq;
	boow use_taskwet;
	stwuct taskwet_stwuct iwq_taskwet;

	/* I/O awea used fow device communication. The wegistew mapping
	 * stawts at an offset into the mapped baw.
	 *   The CMD_WEQx wegistews and the Dewete_Cmd_Queue_Job wegistew
	 *   need to be pwotected whiwe a command queue thwead is accessing
	 *   them.
	 */
	stwuct mutex weq_mutex ____cachewine_awigned;
	void __iomem *io_wegs;

	/* Mastew wists that aww cmds awe queued on. Because thewe can be
	 * mowe than one CCP command queue that can pwocess a cmd a sepawate
	 * backwog wist is needed so that the backwog compwetion caww
	 * compwetes befowe the cmd is avaiwabwe fow execution.
	 */
	spinwock_t cmd_wock ____cachewine_awigned;
	unsigned int cmd_count;
	stwuct wist_head cmd;
	stwuct wist_head backwog;

	/* The command queues. These wepwesent the queues avaiwabwe on the
	 * CCP that awe avaiwabwe fow pwocessing cmds
	 */
	stwuct ccp_cmd_queue cmd_q[MAX_HW_QUEUES];
	unsigned int cmd_q_count;
	unsigned int max_q_count;

	/* Suppowt fow the CCP Twue WNG
	 */
	stwuct hwwng hwwng;
	unsigned int hwwng_wetwies;

	/* Suppowt fow the CCP DMA capabiwities
	 */
	stwuct dma_device dma_dev;
	stwuct ccp_dma_chan *ccp_dma_chan;
	stwuct kmem_cache *dma_cmd_cache;
	stwuct kmem_cache *dma_desc_cache;

	/* A countew used to genewate job-ids fow cmds submitted to the CCP
	 */
	atomic_t cuwwent_id ____cachewine_awigned;

	/* The v3 CCP uses key stowage bwocks (SB) to maintain context fow
	 * cewtain opewations. To pwevent muwtipwe cmds fwom using the same
	 * SB wange a command queue wesewves an SB wange fow the duwation of
	 * the cmd. Each queue, wiww howevew, wesewve 2 SB bwocks fow
	 * opewations that onwy wequiwe singwe SB entwies (eg. AES context/iv
	 * and key) in owdew to avoid awwocation contention.  This wiww wesewve
	 * at most 10 SB entwies, weaving 40 SB entwies avaiwabwe fow dynamic
	 * awwocation.
	 *
	 * The v5 CCP Wocaw Stowage Bwock (WSB) is bwoken up into 8
	 * memwowy wanges, each of which can be enabwed fow access by one
	 * ow mowe queues. Device initiawization takes this into account,
	 * and attempts to assign one wegion fow excwusive use by each
	 * avaiwabwe queue; the west awe then aggwegated as "pubwic" use.
	 * If thewe awe fewew wegions than queues, aww wegions awe shawed
	 * amongst aww queues.
	 */
	stwuct mutex sb_mutex ____cachewine_awigned;
	DECWAWE_BITMAP(sb, KSB_COUNT);
	wait_queue_head_t sb_queue;
	unsigned int sb_avaiw;
	unsigned int sb_count;
	u32 sb_stawt;

	/* Bitmap of shawed WSBs, if any */
	DECWAWE_BITMAP(wsbmap, SWSB_MAP_SIZE);

	/* Suspend suppowt */
	unsigned int suspending;
	wait_queue_head_t suspend_queue;

	/* DMA caching attwibute suppowt */
	unsigned int axcache;

	/* Device Statistics */
	unsigned wong totaw_intewwupts;

	/* DebugFS info */
	stwuct dentwy *debugfs_instance;
};

enum ccp_memtype {
	CCP_MEMTYPE_SYSTEM = 0,
	CCP_MEMTYPE_SB,
	CCP_MEMTYPE_WOCAW,
	CCP_MEMTYPE__WAST,
};
#define	CCP_MEMTYPE_WSB	CCP_MEMTYPE_KSB


stwuct ccp_dma_info {
	dma_addw_t addwess;
	unsigned int offset;
	unsigned int wength;
	enum dma_data_diwection diw;
} __packed __awigned(4);

stwuct ccp_dm_wowkawea {
	stwuct device *dev;
	stwuct dma_poow *dma_poow;

	u8 *addwess;
	stwuct ccp_dma_info dma;
	unsigned int wength;
};

stwuct ccp_sg_wowkawea {
	stwuct scattewwist *sg;
	int nents;
	unsigned int sg_used;

	stwuct scattewwist *dma_sg;
	stwuct scattewwist *dma_sg_head;
	stwuct device *dma_dev;
	unsigned int dma_count;
	enum dma_data_diwection dma_diw;

	u64 bytes_weft;
};

stwuct ccp_data {
	stwuct ccp_sg_wowkawea sg_wa;
	stwuct ccp_dm_wowkawea dm_wa;
};

stwuct ccp_mem {
	enum ccp_memtype type;
	union {
		stwuct ccp_dma_info dma;
		u32 sb;
	} u;
};

stwuct ccp_aes_op {
	enum ccp_aes_type type;
	enum ccp_aes_mode mode;
	enum ccp_aes_action action;
	unsigned int size;
};

stwuct ccp_xts_aes_op {
	enum ccp_aes_type type;
	enum ccp_aes_action action;
	enum ccp_xts_aes_unit_size unit_size;
};

stwuct ccp_des3_op {
	enum ccp_des3_type type;
	enum ccp_des3_mode mode;
	enum ccp_des3_action action;
};

stwuct ccp_sha_op {
	enum ccp_sha_type type;
	u64 msg_bits;
};

stwuct ccp_wsa_op {
	u32 mod_size;
	u32 input_wen;
};

stwuct ccp_passthwu_op {
	enum ccp_passthwu_bitwise bit_mod;
	enum ccp_passthwu_byteswap byte_swap;
};

stwuct ccp_ecc_op {
	enum ccp_ecc_function function;
};

stwuct ccp_op {
	stwuct ccp_cmd_queue *cmd_q;

	u32 jobid;
	u32 ioc;
	u32 soc;
	u32 sb_key;
	u32 sb_ctx;
	u32 init;
	u32 eom;

	stwuct ccp_mem swc;
	stwuct ccp_mem dst;
	stwuct ccp_mem exp;

	union {
		stwuct ccp_aes_op aes;
		stwuct ccp_xts_aes_op xts;
		stwuct ccp_des3_op des3;
		stwuct ccp_sha_op sha;
		stwuct ccp_wsa_op wsa;
		stwuct ccp_passthwu_op passthwu;
		stwuct ccp_ecc_op ecc;
	} u;
};

static inwine u32 ccp_addw_wo(stwuct ccp_dma_info *info)
{
	wetuwn wowew_32_bits(info->addwess + info->offset);
}

static inwine u32 ccp_addw_hi(stwuct ccp_dma_info *info)
{
	wetuwn uppew_32_bits(info->addwess + info->offset) & 0x0000ffff;
}

/**
 * descwiptow fow vewsion 5 CPP commands
 * 8 32-bit wowds:
 * wowd 0: function; engine; contwow bits
 * wowd 1: wength of souwce data
 * wowd 2: wow 32 bits of souwce pointew
 * wowd 3: uppew 16 bits of souwce pointew; souwce memowy type
 * wowd 4: wow 32 bits of destination pointew
 * wowd 5: uppew 16 bits of destination pointew; destination memowy type
 * wowd 6: wow 32 bits of key pointew
 * wowd 7: uppew 16 bits of key pointew; key memowy type
 */
stwuct dwowd0 {
	unsigned int soc:1;
	unsigned int ioc:1;
	unsigned int wsvd1:1;
	unsigned int init:1;
	unsigned int eom:1;		/* AES/SHA onwy */
	unsigned int function:15;
	unsigned int engine:4;
	unsigned int pwot:1;
	unsigned int wsvd2:7;
};

stwuct dwowd3 {
	unsigned int  swc_hi:16;
	unsigned int  swc_mem:2;
	unsigned int  wsb_cxt_id:8;
	unsigned int  wsvd1:5;
	unsigned int  fixed:1;
};

union dwowd4 {
	u32 dst_wo;		/* NON-SHA	*/
	u32 sha_wen_wo;		/* SHA		*/
};

union dwowd5 {
	stwuct {
		unsigned int  dst_hi:16;
		unsigned int  dst_mem:2;
		unsigned int  wsvd1:13;
		unsigned int  fixed:1;
	} fiewds;
	u32 sha_wen_hi;
};

stwuct dwowd7 {
	unsigned int  key_hi:16;
	unsigned int  key_mem:2;
	unsigned int  wsvd1:14;
};

stwuct ccp5_desc {
	stwuct dwowd0 dw0;
	u32 wength;
	u32 swc_wo;
	stwuct dwowd3 dw3;
	union dwowd4 dw4;
	union dwowd5 dw5;
	u32 key_wo;
	stwuct dwowd7 dw7;
};

void ccp_add_device(stwuct ccp_device *ccp);
void ccp_dew_device(stwuct ccp_device *ccp);

extewn void ccp_wog_ewwow(stwuct ccp_device *, unsigned int);

stwuct ccp_device *ccp_awwoc_stwuct(stwuct sp_device *sp);
boow ccp_queues_suspended(stwuct ccp_device *ccp);
int ccp_cmd_queue_thwead(void *data);
int ccp_twng_wead(stwuct hwwng *wng, void *data, size_t max, boow wait);

int ccp_wun_cmd(stwuct ccp_cmd_queue *cmd_q, stwuct ccp_cmd *cmd);

int ccp_wegistew_wng(stwuct ccp_device *ccp);
void ccp_unwegistew_wng(stwuct ccp_device *ccp);
int ccp_dmaengine_wegistew(stwuct ccp_device *ccp);
void ccp_dmaengine_unwegistew(stwuct ccp_device *ccp);

void ccp5_debugfs_setup(stwuct ccp_device *ccp);
void ccp5_debugfs_destwoy(void);

/* Stwuctuwe fow computation functions that awe device-specific */
stwuct ccp_actions {
	int (*aes)(stwuct ccp_op *);
	int (*xts_aes)(stwuct ccp_op *);
	int (*des3)(stwuct ccp_op *);
	int (*sha)(stwuct ccp_op *);
	int (*wsa)(stwuct ccp_op *);
	int (*passthwu)(stwuct ccp_op *);
	int (*ecc)(stwuct ccp_op *);
	u32 (*sbawwoc)(stwuct ccp_cmd_queue *, unsigned int);
	void (*sbfwee)(stwuct ccp_cmd_queue *, unsigned int, unsigned int);
	unsigned int (*get_fwee_swots)(stwuct ccp_cmd_queue *);
	int (*init)(stwuct ccp_device *);
	void (*destwoy)(stwuct ccp_device *);
	iwqwetuwn_t (*iwqhandwew)(int, void *);
};

extewn const stwuct ccp_vdata ccpv3_pwatfowm;
extewn const stwuct ccp_vdata ccpv3;
extewn const stwuct ccp_vdata ccpv5a;
extewn const stwuct ccp_vdata ccpv5b;

#endif
