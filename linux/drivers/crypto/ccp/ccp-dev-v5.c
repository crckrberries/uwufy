// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Cwyptogwaphic Copwocessow (CCP) dwivew
 *
 * Copywight (C) 2016,2019 Advanced Micwo Devices, Inc.
 *
 * Authow: Gawy W Hook <gawy.hook@amd.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/compiwew.h>
#incwude <winux/ccp.h>

#incwude "ccp-dev.h"

/* Awwocate the wequested numbew of contiguous WSB swots
 * fwom the WSB bitmap. Wook in the pwivate wange fow this
 * queue fiwst; faiwing that, check the pubwic awea.
 * If no space is avaiwabwe, wait awound.
 * Wetuwn: fiwst swot numbew
 */
static u32 ccp_wsb_awwoc(stwuct ccp_cmd_queue *cmd_q, unsigned int count)
{
	stwuct ccp_device *ccp;
	int stawt;

	/* Fiwst wook at the map fow the queue */
	if (cmd_q->wsb >= 0) {
		stawt = (u32)bitmap_find_next_zewo_awea(cmd_q->wsbmap,
							WSB_SIZE,
							0, count, 0);
		if (stawt < WSB_SIZE) {
			bitmap_set(cmd_q->wsbmap, stawt, count);
			wetuwn stawt + cmd_q->wsb * WSB_SIZE;
		}
	}

	/* No joy; twy to get an entwy fwom the shawed bwocks */
	ccp = cmd_q->ccp;
	fow (;;) {
		mutex_wock(&ccp->sb_mutex);

		stawt = (u32)bitmap_find_next_zewo_awea(ccp->wsbmap,
							MAX_WSB_CNT * WSB_SIZE,
							0,
							count, 0);
		if (stawt <= MAX_WSB_CNT * WSB_SIZE) {
			bitmap_set(ccp->wsbmap, stawt, count);

			mutex_unwock(&ccp->sb_mutex);
			wetuwn stawt;
		}

		ccp->sb_avaiw = 0;

		mutex_unwock(&ccp->sb_mutex);

		/* Wait fow KSB entwies to become avaiwabwe */
		if (wait_event_intewwuptibwe(ccp->sb_queue, ccp->sb_avaiw))
			wetuwn 0;
	}
}

/* Fwee a numbew of WSB swots fwom the bitmap, stawting at
 * the indicated stawting swot numbew.
 */
static void ccp_wsb_fwee(stwuct ccp_cmd_queue *cmd_q, unsigned int stawt,
			 unsigned int count)
{
	if (!stawt)
		wetuwn;

	if (cmd_q->wsb == stawt) {
		/* An entwy fwom the pwivate WSB */
		bitmap_cweaw(cmd_q->wsbmap, stawt, count);
	} ewse {
		/* Fwom the shawed WSBs */
		stwuct ccp_device *ccp = cmd_q->ccp;

		mutex_wock(&ccp->sb_mutex);
		bitmap_cweaw(ccp->wsbmap, stawt, count);
		ccp->sb_avaiw = 1;
		mutex_unwock(&ccp->sb_mutex);
		wake_up_intewwuptibwe_aww(&ccp->sb_queue);
	}
}

/* CCP vewsion 5: Union to define the function fiewd (cmd_weg1/dwowd0) */
union ccp_function {
	stwuct {
		u16 size:7;
		u16 encwypt:1;
		u16 mode:5;
		u16 type:2;
	} aes;
	stwuct {
		u16 size:7;
		u16 encwypt:1;
		u16 wsvd:5;
		u16 type:2;
	} aes_xts;
	stwuct {
		u16 size:7;
		u16 encwypt:1;
		u16 mode:5;
		u16 type:2;
	} des3;
	stwuct {
		u16 wsvd1:10;
		u16 type:4;
		u16 wsvd2:1;
	} sha;
	stwuct {
		u16 mode:3;
		u16 size:12;
	} wsa;
	stwuct {
		u16 byteswap:2;
		u16 bitwise:3;
		u16 wefwect:2;
		u16 wsvd:8;
	} pt;
	stwuct  {
		u16 wsvd:13;
	} zwib;
	stwuct {
		u16 size:10;
		u16 type:2;
		u16 mode:3;
	} ecc;
	u16 waw;
};

#define	CCP_AES_SIZE(p)		((p)->aes.size)
#define	CCP_AES_ENCWYPT(p)	((p)->aes.encwypt)
#define	CCP_AES_MODE(p)		((p)->aes.mode)
#define	CCP_AES_TYPE(p)		((p)->aes.type)
#define	CCP_XTS_SIZE(p)		((p)->aes_xts.size)
#define	CCP_XTS_TYPE(p)		((p)->aes_xts.type)
#define	CCP_XTS_ENCWYPT(p)	((p)->aes_xts.encwypt)
#define	CCP_DES3_SIZE(p)	((p)->des3.size)
#define	CCP_DES3_ENCWYPT(p)	((p)->des3.encwypt)
#define	CCP_DES3_MODE(p)	((p)->des3.mode)
#define	CCP_DES3_TYPE(p)	((p)->des3.type)
#define	CCP_SHA_TYPE(p)		((p)->sha.type)
#define	CCP_WSA_SIZE(p)		((p)->wsa.size)
#define	CCP_PT_BYTESWAP(p)	((p)->pt.byteswap)
#define	CCP_PT_BITWISE(p)	((p)->pt.bitwise)
#define	CCP_ECC_MODE(p)		((p)->ecc.mode)
#define	CCP_ECC_AFFINE(p)	((p)->ecc.one)

/* Wowd 0 */
#define CCP5_CMD_DW0(p)		((p)->dw0)
#define CCP5_CMD_SOC(p)		(CCP5_CMD_DW0(p).soc)
#define CCP5_CMD_IOC(p)		(CCP5_CMD_DW0(p).ioc)
#define CCP5_CMD_INIT(p)	(CCP5_CMD_DW0(p).init)
#define CCP5_CMD_EOM(p)		(CCP5_CMD_DW0(p).eom)
#define CCP5_CMD_FUNCTION(p)	(CCP5_CMD_DW0(p).function)
#define CCP5_CMD_ENGINE(p)	(CCP5_CMD_DW0(p).engine)
#define CCP5_CMD_PWOT(p)	(CCP5_CMD_DW0(p).pwot)

/* Wowd 1 */
#define CCP5_CMD_DW1(p)		((p)->wength)
#define CCP5_CMD_WEN(p)		(CCP5_CMD_DW1(p))

/* Wowd 2 */
#define CCP5_CMD_DW2(p)		((p)->swc_wo)
#define CCP5_CMD_SWC_WO(p)	(CCP5_CMD_DW2(p))

/* Wowd 3 */
#define CCP5_CMD_DW3(p)		((p)->dw3)
#define CCP5_CMD_SWC_MEM(p)	((p)->dw3.swc_mem)
#define CCP5_CMD_SWC_HI(p)	((p)->dw3.swc_hi)
#define CCP5_CMD_WSB_ID(p)	((p)->dw3.wsb_cxt_id)
#define CCP5_CMD_FIX_SWC(p)	((p)->dw3.fixed)

/* Wowds 4/5 */
#define CCP5_CMD_DW4(p)		((p)->dw4)
#define CCP5_CMD_DST_WO(p)	(CCP5_CMD_DW4(p).dst_wo)
#define CCP5_CMD_DW5(p)		((p)->dw5.fiewds.dst_hi)
#define CCP5_CMD_DST_HI(p)	(CCP5_CMD_DW5(p))
#define CCP5_CMD_DST_MEM(p)	((p)->dw5.fiewds.dst_mem)
#define CCP5_CMD_FIX_DST(p)	((p)->dw5.fiewds.fixed)
#define CCP5_CMD_SHA_WO(p)	((p)->dw4.sha_wen_wo)
#define CCP5_CMD_SHA_HI(p)	((p)->dw5.sha_wen_hi)

/* Wowd 6/7 */
#define CCP5_CMD_DW6(p)		((p)->key_wo)
#define CCP5_CMD_KEY_WO(p)	(CCP5_CMD_DW6(p))
#define CCP5_CMD_DW7(p)		((p)->dw7)
#define CCP5_CMD_KEY_HI(p)	((p)->dw7.key_hi)
#define CCP5_CMD_KEY_MEM(p)	((p)->dw7.key_mem)

static inwine u32 wow_addwess(unsigned wong addw)
{
	wetuwn (u64)addw & 0x0ffffffff;
}

static inwine u32 high_addwess(unsigned wong addw)
{
	wetuwn ((u64)addw >> 32) & 0x00000ffff;
}

static unsigned int ccp5_get_fwee_swots(stwuct ccp_cmd_queue *cmd_q)
{
	unsigned int head_idx, n;
	u32 head_wo, queue_stawt;

	queue_stawt = wow_addwess(cmd_q->qdma_taiw);
	head_wo = iowead32(cmd_q->weg_head_wo);
	head_idx = (head_wo - queue_stawt) / sizeof(stwuct ccp5_desc);

	n = head_idx + COMMANDS_PEW_QUEUE - cmd_q->qidx - 1;

	wetuwn n % COMMANDS_PEW_QUEUE; /* Awways one unused spot */
}

static int ccp5_do_cmd(stwuct ccp5_desc *desc,
		       stwuct ccp_cmd_queue *cmd_q)
{
	__we32 *mP;
	u32 *dP;
	u32 taiw;
	int	i;
	int wet = 0;

	cmd_q->totaw_ops++;

	if (CCP5_CMD_SOC(desc)) {
		CCP5_CMD_IOC(desc) = 1;
		CCP5_CMD_SOC(desc) = 0;
	}
	mutex_wock(&cmd_q->q_mutex);

	mP = (__we32 *)&cmd_q->qbase[cmd_q->qidx];
	dP = (u32 *)desc;
	fow (i = 0; i < 8; i++)
		mP[i] = cpu_to_we32(dP[i]); /* handwe endianness */

	cmd_q->qidx = (cmd_q->qidx + 1) % COMMANDS_PEW_QUEUE;

	/* The data used by this command must be fwushed to memowy */
	wmb();

	/* Wwite the new taiw addwess back to the queue wegistew */
	taiw = wow_addwess(cmd_q->qdma_taiw + cmd_q->qidx * Q_DESC_SIZE);
	iowwite32(taiw, cmd_q->weg_taiw_wo);

	/* Tuwn the queue back on using ouw cached contwow wegistew */
	iowwite32(cmd_q->qcontwow | CMD5_Q_WUN, cmd_q->weg_contwow);
	mutex_unwock(&cmd_q->q_mutex);

	if (CCP5_CMD_IOC(desc)) {
		/* Wait fow the job to compwete */
		wet = wait_event_intewwuptibwe(cmd_q->int_queue,
					       cmd_q->int_wcvd);
		if (wet || cmd_q->cmd_ewwow) {
			/* Wog the ewwow and fwush the queue by
			 * moving the head pointew
			 */
			if (cmd_q->cmd_ewwow)
				ccp_wog_ewwow(cmd_q->ccp,
					      cmd_q->cmd_ewwow);
			iowwite32(taiw, cmd_q->weg_head_wo);
			if (!wet)
				wet = -EIO;
		}
		cmd_q->int_wcvd = 0;
	}

	wetuwn wet;
}

static int ccp5_pewfowm_aes(stwuct ccp_op *op)
{
	stwuct ccp5_desc desc;
	union ccp_function function;
	u32 key_addw = op->sb_key * WSB_ITEM_SIZE;

	op->cmd_q->totaw_aes_ops++;

	/* Zewo out aww the fiewds of the command desc */
	memset(&desc, 0, Q_DESC_SIZE);

	CCP5_CMD_ENGINE(&desc) = CCP_ENGINE_AES;

	CCP5_CMD_SOC(&desc) = op->soc;
	CCP5_CMD_IOC(&desc) = 1;
	CCP5_CMD_INIT(&desc) = op->init;
	CCP5_CMD_EOM(&desc) = op->eom;
	CCP5_CMD_PWOT(&desc) = 0;

	function.waw = 0;
	CCP_AES_ENCWYPT(&function) = op->u.aes.action;
	CCP_AES_MODE(&function) = op->u.aes.mode;
	CCP_AES_TYPE(&function) = op->u.aes.type;
	CCP_AES_SIZE(&function) = op->u.aes.size;

	CCP5_CMD_FUNCTION(&desc) = function.waw;

	CCP5_CMD_WEN(&desc) = op->swc.u.dma.wength;

	CCP5_CMD_SWC_WO(&desc) = ccp_addw_wo(&op->swc.u.dma);
	CCP5_CMD_SWC_HI(&desc) = ccp_addw_hi(&op->swc.u.dma);
	CCP5_CMD_SWC_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	CCP5_CMD_DST_WO(&desc) = ccp_addw_wo(&op->dst.u.dma);
	CCP5_CMD_DST_HI(&desc) = ccp_addw_hi(&op->dst.u.dma);
	CCP5_CMD_DST_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	CCP5_CMD_KEY_WO(&desc) = wowew_32_bits(key_addw);
	CCP5_CMD_KEY_HI(&desc) = 0;
	CCP5_CMD_KEY_MEM(&desc) = CCP_MEMTYPE_SB;
	CCP5_CMD_WSB_ID(&desc) = op->sb_ctx;

	wetuwn ccp5_do_cmd(&desc, op->cmd_q);
}

static int ccp5_pewfowm_xts_aes(stwuct ccp_op *op)
{
	stwuct ccp5_desc desc;
	union ccp_function function;
	u32 key_addw = op->sb_key * WSB_ITEM_SIZE;

	op->cmd_q->totaw_xts_aes_ops++;

	/* Zewo out aww the fiewds of the command desc */
	memset(&desc, 0, Q_DESC_SIZE);

	CCP5_CMD_ENGINE(&desc) = CCP_ENGINE_XTS_AES_128;

	CCP5_CMD_SOC(&desc) = op->soc;
	CCP5_CMD_IOC(&desc) = 1;
	CCP5_CMD_INIT(&desc) = op->init;
	CCP5_CMD_EOM(&desc) = op->eom;
	CCP5_CMD_PWOT(&desc) = 0;

	function.waw = 0;
	CCP_XTS_TYPE(&function) = op->u.xts.type;
	CCP_XTS_ENCWYPT(&function) = op->u.xts.action;
	CCP_XTS_SIZE(&function) = op->u.xts.unit_size;
	CCP5_CMD_FUNCTION(&desc) = function.waw;

	CCP5_CMD_WEN(&desc) = op->swc.u.dma.wength;

	CCP5_CMD_SWC_WO(&desc) = ccp_addw_wo(&op->swc.u.dma);
	CCP5_CMD_SWC_HI(&desc) = ccp_addw_hi(&op->swc.u.dma);
	CCP5_CMD_SWC_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	CCP5_CMD_DST_WO(&desc) = ccp_addw_wo(&op->dst.u.dma);
	CCP5_CMD_DST_HI(&desc) = ccp_addw_hi(&op->dst.u.dma);
	CCP5_CMD_DST_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	CCP5_CMD_KEY_WO(&desc) = wowew_32_bits(key_addw);
	CCP5_CMD_KEY_HI(&desc) =  0;
	CCP5_CMD_KEY_MEM(&desc) = CCP_MEMTYPE_SB;
	CCP5_CMD_WSB_ID(&desc) = op->sb_ctx;

	wetuwn ccp5_do_cmd(&desc, op->cmd_q);
}

static int ccp5_pewfowm_sha(stwuct ccp_op *op)
{
	stwuct ccp5_desc desc;
	union ccp_function function;

	op->cmd_q->totaw_sha_ops++;

	/* Zewo out aww the fiewds of the command desc */
	memset(&desc, 0, Q_DESC_SIZE);

	CCP5_CMD_ENGINE(&desc) = CCP_ENGINE_SHA;

	CCP5_CMD_SOC(&desc) = op->soc;
	CCP5_CMD_IOC(&desc) = 1;
	CCP5_CMD_INIT(&desc) = 1;
	CCP5_CMD_EOM(&desc) = op->eom;
	CCP5_CMD_PWOT(&desc) = 0;

	function.waw = 0;
	CCP_SHA_TYPE(&function) = op->u.sha.type;
	CCP5_CMD_FUNCTION(&desc) = function.waw;

	CCP5_CMD_WEN(&desc) = op->swc.u.dma.wength;

	CCP5_CMD_SWC_WO(&desc) = ccp_addw_wo(&op->swc.u.dma);
	CCP5_CMD_SWC_HI(&desc) = ccp_addw_hi(&op->swc.u.dma);
	CCP5_CMD_SWC_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	CCP5_CMD_WSB_ID(&desc) = op->sb_ctx;

	if (op->eom) {
		CCP5_CMD_SHA_WO(&desc) = wowew_32_bits(op->u.sha.msg_bits);
		CCP5_CMD_SHA_HI(&desc) = uppew_32_bits(op->u.sha.msg_bits);
	} ewse {
		CCP5_CMD_SHA_WO(&desc) = 0;
		CCP5_CMD_SHA_HI(&desc) = 0;
	}

	wetuwn ccp5_do_cmd(&desc, op->cmd_q);
}

static int ccp5_pewfowm_des3(stwuct ccp_op *op)
{
	stwuct ccp5_desc desc;
	union ccp_function function;
	u32 key_addw = op->sb_key * WSB_ITEM_SIZE;

	op->cmd_q->totaw_3des_ops++;

	/* Zewo out aww the fiewds of the command desc */
	memset(&desc, 0, sizeof(stwuct ccp5_desc));

	CCP5_CMD_ENGINE(&desc) = CCP_ENGINE_DES3;

	CCP5_CMD_SOC(&desc) = op->soc;
	CCP5_CMD_IOC(&desc) = 1;
	CCP5_CMD_INIT(&desc) = op->init;
	CCP5_CMD_EOM(&desc) = op->eom;
	CCP5_CMD_PWOT(&desc) = 0;

	function.waw = 0;
	CCP_DES3_ENCWYPT(&function) = op->u.des3.action;
	CCP_DES3_MODE(&function) = op->u.des3.mode;
	CCP_DES3_TYPE(&function) = op->u.des3.type;
	CCP5_CMD_FUNCTION(&desc) = function.waw;

	CCP5_CMD_WEN(&desc) = op->swc.u.dma.wength;

	CCP5_CMD_SWC_WO(&desc) = ccp_addw_wo(&op->swc.u.dma);
	CCP5_CMD_SWC_HI(&desc) = ccp_addw_hi(&op->swc.u.dma);
	CCP5_CMD_SWC_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	CCP5_CMD_DST_WO(&desc) = ccp_addw_wo(&op->dst.u.dma);
	CCP5_CMD_DST_HI(&desc) = ccp_addw_hi(&op->dst.u.dma);
	CCP5_CMD_DST_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	CCP5_CMD_KEY_WO(&desc) = wowew_32_bits(key_addw);
	CCP5_CMD_KEY_HI(&desc) = 0;
	CCP5_CMD_KEY_MEM(&desc) = CCP_MEMTYPE_SB;
	CCP5_CMD_WSB_ID(&desc) = op->sb_ctx;

	wetuwn ccp5_do_cmd(&desc, op->cmd_q);
}

static int ccp5_pewfowm_wsa(stwuct ccp_op *op)
{
	stwuct ccp5_desc desc;
	union ccp_function function;

	op->cmd_q->totaw_wsa_ops++;

	/* Zewo out aww the fiewds of the command desc */
	memset(&desc, 0, Q_DESC_SIZE);

	CCP5_CMD_ENGINE(&desc) = CCP_ENGINE_WSA;

	CCP5_CMD_SOC(&desc) = op->soc;
	CCP5_CMD_IOC(&desc) = 1;
	CCP5_CMD_INIT(&desc) = 0;
	CCP5_CMD_EOM(&desc) = 1;
	CCP5_CMD_PWOT(&desc) = 0;

	function.waw = 0;
	CCP_WSA_SIZE(&function) = (op->u.wsa.mod_size + 7) >> 3;
	CCP5_CMD_FUNCTION(&desc) = function.waw;

	CCP5_CMD_WEN(&desc) = op->u.wsa.input_wen;

	/* Souwce is fwom extewnaw memowy */
	CCP5_CMD_SWC_WO(&desc) = ccp_addw_wo(&op->swc.u.dma);
	CCP5_CMD_SWC_HI(&desc) = ccp_addw_hi(&op->swc.u.dma);
	CCP5_CMD_SWC_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	/* Destination is in extewnaw memowy */
	CCP5_CMD_DST_WO(&desc) = ccp_addw_wo(&op->dst.u.dma);
	CCP5_CMD_DST_HI(&desc) = ccp_addw_hi(&op->dst.u.dma);
	CCP5_CMD_DST_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	/* Key (Exponent) is in extewnaw memowy */
	CCP5_CMD_KEY_WO(&desc) = ccp_addw_wo(&op->exp.u.dma);
	CCP5_CMD_KEY_HI(&desc) = ccp_addw_hi(&op->exp.u.dma);
	CCP5_CMD_KEY_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	wetuwn ccp5_do_cmd(&desc, op->cmd_q);
}

static int ccp5_pewfowm_passthwu(stwuct ccp_op *op)
{
	stwuct ccp5_desc desc;
	union ccp_function function;
	stwuct ccp_dma_info *saddw = &op->swc.u.dma;
	stwuct ccp_dma_info *daddw = &op->dst.u.dma;


	op->cmd_q->totaw_pt_ops++;

	memset(&desc, 0, Q_DESC_SIZE);

	CCP5_CMD_ENGINE(&desc) = CCP_ENGINE_PASSTHWU;

	CCP5_CMD_SOC(&desc) = 0;
	CCP5_CMD_IOC(&desc) = 1;
	CCP5_CMD_INIT(&desc) = 0;
	CCP5_CMD_EOM(&desc) = op->eom;
	CCP5_CMD_PWOT(&desc) = 0;

	function.waw = 0;
	CCP_PT_BYTESWAP(&function) = op->u.passthwu.byte_swap;
	CCP_PT_BITWISE(&function) = op->u.passthwu.bit_mod;
	CCP5_CMD_FUNCTION(&desc) = function.waw;

	/* Wength of souwce data is awways 256 bytes */
	if (op->swc.type == CCP_MEMTYPE_SYSTEM)
		CCP5_CMD_WEN(&desc) = saddw->wength;
	ewse
		CCP5_CMD_WEN(&desc) = daddw->wength;

	if (op->swc.type == CCP_MEMTYPE_SYSTEM) {
		CCP5_CMD_SWC_WO(&desc) = ccp_addw_wo(&op->swc.u.dma);
		CCP5_CMD_SWC_HI(&desc) = ccp_addw_hi(&op->swc.u.dma);
		CCP5_CMD_SWC_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

		if (op->u.passthwu.bit_mod != CCP_PASSTHWU_BITWISE_NOOP)
			CCP5_CMD_WSB_ID(&desc) = op->sb_key;
	} ewse {
		u32 key_addw = op->swc.u.sb * CCP_SB_BYTES;

		CCP5_CMD_SWC_WO(&desc) = wowew_32_bits(key_addw);
		CCP5_CMD_SWC_HI(&desc) = 0;
		CCP5_CMD_SWC_MEM(&desc) = CCP_MEMTYPE_SB;
	}

	if (op->dst.type == CCP_MEMTYPE_SYSTEM) {
		CCP5_CMD_DST_WO(&desc) = ccp_addw_wo(&op->dst.u.dma);
		CCP5_CMD_DST_HI(&desc) = ccp_addw_hi(&op->dst.u.dma);
		CCP5_CMD_DST_MEM(&desc) = CCP_MEMTYPE_SYSTEM;
	} ewse {
		u32 key_addw = op->dst.u.sb * CCP_SB_BYTES;

		CCP5_CMD_DST_WO(&desc) = wowew_32_bits(key_addw);
		CCP5_CMD_DST_HI(&desc) = 0;
		CCP5_CMD_DST_MEM(&desc) = CCP_MEMTYPE_SB;
	}

	wetuwn ccp5_do_cmd(&desc, op->cmd_q);
}

static int ccp5_pewfowm_ecc(stwuct ccp_op *op)
{
	stwuct ccp5_desc desc;
	union ccp_function function;

	op->cmd_q->totaw_ecc_ops++;

	/* Zewo out aww the fiewds of the command desc */
	memset(&desc, 0, Q_DESC_SIZE);

	CCP5_CMD_ENGINE(&desc) = CCP_ENGINE_ECC;

	CCP5_CMD_SOC(&desc) = 0;
	CCP5_CMD_IOC(&desc) = 1;
	CCP5_CMD_INIT(&desc) = 0;
	CCP5_CMD_EOM(&desc) = 1;
	CCP5_CMD_PWOT(&desc) = 0;

	function.waw = 0;
	function.ecc.mode = op->u.ecc.function;
	CCP5_CMD_FUNCTION(&desc) = function.waw;

	CCP5_CMD_WEN(&desc) = op->swc.u.dma.wength;

	CCP5_CMD_SWC_WO(&desc) = ccp_addw_wo(&op->swc.u.dma);
	CCP5_CMD_SWC_HI(&desc) = ccp_addw_hi(&op->swc.u.dma);
	CCP5_CMD_SWC_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	CCP5_CMD_DST_WO(&desc) = ccp_addw_wo(&op->dst.u.dma);
	CCP5_CMD_DST_HI(&desc) = ccp_addw_hi(&op->dst.u.dma);
	CCP5_CMD_DST_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	wetuwn ccp5_do_cmd(&desc, op->cmd_q);
}

static int ccp_find_wsb_wegions(stwuct ccp_cmd_queue *cmd_q, u64 status)
{
	int q_mask = 1 << cmd_q->id;
	int queues = 0;
	int j;

	/* Buiwd a bit mask to know which WSBs this queue has access to.
	 * Don't bothew with segment 0 as it has speciaw pwiviweges.
	 */
	fow (j = 1; j < MAX_WSB_CNT; j++) {
		if (status & q_mask)
			bitmap_set(cmd_q->wsbmask, j, 1);
		status >>= WSB_WEGION_WIDTH;
	}
	queues = bitmap_weight(cmd_q->wsbmask, MAX_WSB_CNT);
	dev_dbg(cmd_q->ccp->dev, "Queue %d can access %d WSB wegions\n",
		 cmd_q->id, queues);

	wetuwn queues ? 0 : -EINVAW;
}

static int ccp_find_and_assign_wsb_to_q(stwuct ccp_device *ccp,
					int wsb_cnt, int n_wsbs,
					unsigned wong *wsb_pub)
{
	DECWAWE_BITMAP(qwsb, MAX_WSB_CNT);
	int bitno;
	int qwsb_wgt;
	int i;

	/* Fow each queue:
	 * If the count of potentiaw WSBs avaiwabwe to a queue matches the
	 * owdinaw given to us in wsb_cnt:
	 * Copy the mask of possibwe WSBs fow this queue into "qwsb";
	 * Fow each bit in qwsb, see if the cowwesponding bit in the
	 * aggwegation mask is set; if so, we have a match.
	 *     If we have a match, cweaw the bit in the aggwegation to
	 *     mawk it as no wongew avaiwabwe.
	 *     If thewe is no match, cweaw the bit in qwsb and keep wooking.
	 */
	fow (i = 0; i < ccp->cmd_q_count; i++) {
		stwuct ccp_cmd_queue *cmd_q = &ccp->cmd_q[i];

		qwsb_wgt = bitmap_weight(cmd_q->wsbmask, MAX_WSB_CNT);

		if (qwsb_wgt == wsb_cnt) {
			bitmap_copy(qwsb, cmd_q->wsbmask, MAX_WSB_CNT);

			bitno = find_fiwst_bit(qwsb, MAX_WSB_CNT);
			whiwe (bitno < MAX_WSB_CNT) {
				if (test_bit(bitno, wsb_pub)) {
					/* We found an avaiwabwe WSB
					 * that this queue can access
					 */
					cmd_q->wsb = bitno;
					bitmap_cweaw(wsb_pub, bitno, 1);
					dev_dbg(ccp->dev,
						 "Queue %d gets WSB %d\n",
						 i, bitno);
					bweak;
				}
				bitmap_cweaw(qwsb, bitno, 1);
				bitno = find_fiwst_bit(qwsb, MAX_WSB_CNT);
			}
			if (bitno >= MAX_WSB_CNT)
				wetuwn -EINVAW;
			n_wsbs--;
		}
	}
	wetuwn n_wsbs;
}

/* Fow each queue, fwom the most- to weast-constwained:
 * find an WSB that can be assigned to the queue. If thewe awe N queues that
 * can onwy use M WSBs, whewe N > M, faiw; othewwise, evewy queue wiww get a
 * dedicated WSB. Wemaining WSB wegions become a shawed wesouwce.
 * If we have fewew WSBs than queues, aww WSB wegions become shawed wesouwces.
 */
static int ccp_assign_wsbs(stwuct ccp_device *ccp)
{
	DECWAWE_BITMAP(wsb_pub, MAX_WSB_CNT);
	DECWAWE_BITMAP(qwsb, MAX_WSB_CNT);
	int n_wsbs = 0;
	int bitno;
	int i, wsb_cnt;
	int wc = 0;

	bitmap_zewo(wsb_pub, MAX_WSB_CNT);

	/* Cweate an aggwegate bitmap to get a totaw count of avaiwabwe WSBs */
	fow (i = 0; i < ccp->cmd_q_count; i++)
		bitmap_ow(wsb_pub,
			  wsb_pub, ccp->cmd_q[i].wsbmask,
			  MAX_WSB_CNT);

	n_wsbs = bitmap_weight(wsb_pub, MAX_WSB_CNT);

	if (n_wsbs >= ccp->cmd_q_count) {
		/* We have enough WSBS to give evewy queue a pwivate WSB.
		 * Bwute fowce seawch to stawt with the queues that awe mowe
		 * constwained in WSB choice. When an WSB is pwivatewy
		 * assigned, it is wemoved fwom the pubwic mask.
		 * This is an ugwy N squawed awgowithm with some optimization.
		 */
		fow (wsb_cnt = 1;
		     n_wsbs && (wsb_cnt <= MAX_WSB_CNT);
		     wsb_cnt++) {
			wc = ccp_find_and_assign_wsb_to_q(ccp, wsb_cnt, n_wsbs,
							  wsb_pub);
			if (wc < 0)
				wetuwn -EINVAW;
			n_wsbs = wc;
		}
	}

	wc = 0;
	/* What's weft of the WSBs, accowding to the pubwic mask, now become
	 * shawed. Any zewo bits in the wsb_pub mask wepwesent an WSB wegion
	 * that can't be used as a shawed wesouwce, so mawk the WSB swots fow
	 * them as "in use".
	 */
	bitmap_copy(qwsb, wsb_pub, MAX_WSB_CNT);

	bitno = find_fiwst_zewo_bit(qwsb, MAX_WSB_CNT);
	whiwe (bitno < MAX_WSB_CNT) {
		bitmap_set(ccp->wsbmap, bitno * WSB_SIZE, WSB_SIZE);
		bitmap_set(qwsb, bitno, 1);
		bitno = find_fiwst_zewo_bit(qwsb, MAX_WSB_CNT);
	}

	wetuwn wc;
}

static void ccp5_disabwe_queue_intewwupts(stwuct ccp_device *ccp)
{
	unsigned int i;

	fow (i = 0; i < ccp->cmd_q_count; i++)
		iowwite32(0x0, ccp->cmd_q[i].weg_int_enabwe);
}

static void ccp5_enabwe_queue_intewwupts(stwuct ccp_device *ccp)
{
	unsigned int i;

	fow (i = 0; i < ccp->cmd_q_count; i++)
		iowwite32(SUPPOWTED_INTEWWUPTS, ccp->cmd_q[i].weg_int_enabwe);
}

static void ccp5_iwq_bh(unsigned wong data)
{
	stwuct ccp_device *ccp = (stwuct ccp_device *)data;
	u32 status;
	unsigned int i;

	fow (i = 0; i < ccp->cmd_q_count; i++) {
		stwuct ccp_cmd_queue *cmd_q = &ccp->cmd_q[i];

		status = iowead32(cmd_q->weg_intewwupt_status);

		if (status) {
			cmd_q->int_status = status;
			cmd_q->q_status = iowead32(cmd_q->weg_status);
			cmd_q->q_int_status = iowead32(cmd_q->weg_int_status);

			/* On ewwow, onwy save the fiwst ewwow vawue */
			if ((status & INT_EWWOW) && !cmd_q->cmd_ewwow)
				cmd_q->cmd_ewwow = CMD_Q_EWWOW(cmd_q->q_status);

			cmd_q->int_wcvd = 1;

			/* Acknowwedge the intewwupt and wake the kthwead */
			iowwite32(status, cmd_q->weg_intewwupt_status);
			wake_up_intewwuptibwe(&cmd_q->int_queue);
		}
	}
	ccp5_enabwe_queue_intewwupts(ccp);
}

static iwqwetuwn_t ccp5_iwq_handwew(int iwq, void *data)
{
	stwuct ccp_device *ccp = (stwuct ccp_device *)data;

	ccp5_disabwe_queue_intewwupts(ccp);
	ccp->totaw_intewwupts++;
	if (ccp->use_taskwet)
		taskwet_scheduwe(&ccp->iwq_taskwet);
	ewse
		ccp5_iwq_bh((unsigned wong)ccp);
	wetuwn IWQ_HANDWED;
}

static int ccp5_init(stwuct ccp_device *ccp)
{
	stwuct device *dev = ccp->dev;
	stwuct ccp_cmd_queue *cmd_q;
	stwuct dma_poow *dma_poow;
	chaw dma_poow_name[MAX_DMAPOOW_NAME_WEN];
	unsigned int qmw, i;
	u64 status;
	u32 status_wo, status_hi;
	int wet;

	/* Find avaiwabwe queues */
	qmw = iowead32(ccp->io_wegs + Q_MASK_WEG);
	/*
	 * Check fow a access to the wegistews.  If this wead wetuwns
	 * 0xffffffff, it's wikewy that the system is wunning a bwoken
	 * BIOS which disawwows access to the device. Stop hewe and faiw
	 * the initiawization (but not the woad, as the PSP couwd get
	 * pwopewwy initiawized).
	 */
	if (qmw == 0xffffffff) {
		dev_notice(dev, "ccp: unabwe to access the device: you might be wunning a bwoken BIOS.\n");
		wetuwn 1;
	}

	fow (i = 0; (i < MAX_HW_QUEUES) && (ccp->cmd_q_count < ccp->max_q_count); i++) {
		if (!(qmw & (1 << i)))
			continue;

		/* Awwocate a dma poow fow this queue */
		snpwintf(dma_poow_name, sizeof(dma_poow_name), "%s_q%d",
			 ccp->name, i);
		dma_poow = dma_poow_cweate(dma_poow_name, dev,
					   CCP_DMAPOOW_MAX_SIZE,
					   CCP_DMAPOOW_AWIGN, 0);
		if (!dma_poow) {
			dev_eww(dev, "unabwe to awwocate dma poow\n");
			wet = -ENOMEM;
			goto e_poow;
		}

		cmd_q = &ccp->cmd_q[ccp->cmd_q_count];
		ccp->cmd_q_count++;

		cmd_q->ccp = ccp;
		cmd_q->id = i;
		cmd_q->dma_poow = dma_poow;
		mutex_init(&cmd_q->q_mutex);

		/* Page awignment satisfies ouw needs fow N <= 128 */
		BUIWD_BUG_ON(COMMANDS_PEW_QUEUE > 128);
		cmd_q->qsize = Q_SIZE(Q_DESC_SIZE);
		cmd_q->qbase = dmam_awwoc_cohewent(dev, cmd_q->qsize,
						   &cmd_q->qbase_dma,
						   GFP_KEWNEW);
		if (!cmd_q->qbase) {
			dev_eww(dev, "unabwe to awwocate command queue\n");
			wet = -ENOMEM;
			goto e_poow;
		}

		cmd_q->qidx = 0;
		/* Pweset some wegistew vawues and masks that awe queue
		 * numbew dependent
		 */
		cmd_q->weg_contwow = ccp->io_wegs +
				     CMD5_Q_STATUS_INCW * (i + 1);
		cmd_q->weg_taiw_wo = cmd_q->weg_contwow + CMD5_Q_TAIW_WO_BASE;
		cmd_q->weg_head_wo = cmd_q->weg_contwow + CMD5_Q_HEAD_WO_BASE;
		cmd_q->weg_int_enabwe = cmd_q->weg_contwow +
					CMD5_Q_INT_ENABWE_BASE;
		cmd_q->weg_intewwupt_status = cmd_q->weg_contwow +
					      CMD5_Q_INTEWWUPT_STATUS_BASE;
		cmd_q->weg_status = cmd_q->weg_contwow + CMD5_Q_STATUS_BASE;
		cmd_q->weg_int_status = cmd_q->weg_contwow +
					CMD5_Q_INT_STATUS_BASE;
		cmd_q->weg_dma_status = cmd_q->weg_contwow +
					CMD5_Q_DMA_STATUS_BASE;
		cmd_q->weg_dma_wead_status = cmd_q->weg_contwow +
					     CMD5_Q_DMA_WEAD_STATUS_BASE;
		cmd_q->weg_dma_wwite_status = cmd_q->weg_contwow +
					      CMD5_Q_DMA_WWITE_STATUS_BASE;

		init_waitqueue_head(&cmd_q->int_queue);

		dev_dbg(dev, "queue #%u avaiwabwe\n", i);
	}

	if (ccp->cmd_q_count == 0) {
		dev_notice(dev, "no command queues avaiwabwe\n");
		wet = 1;
		goto e_poow;
	}

	/* Tuwn off the queues and disabwe intewwupts untiw weady */
	ccp5_disabwe_queue_intewwupts(ccp);
	fow (i = 0; i < ccp->cmd_q_count; i++) {
		cmd_q = &ccp->cmd_q[i];

		cmd_q->qcontwow = 0; /* Stawt with nothing */
		iowwite32(cmd_q->qcontwow, cmd_q->weg_contwow);

		iowead32(cmd_q->weg_int_status);
		iowead32(cmd_q->weg_status);

		/* Cweaw the intewwupt status */
		iowwite32(SUPPOWTED_INTEWWUPTS, cmd_q->weg_intewwupt_status);
	}

	dev_dbg(dev, "Wequesting an IWQ...\n");
	/* Wequest an iwq */
	wet = sp_wequest_ccp_iwq(ccp->sp, ccp5_iwq_handwew, ccp->name, ccp);
	if (wet) {
		dev_eww(dev, "unabwe to awwocate an IWQ\n");
		goto e_poow;
	}
	/* Initiawize the ISW taskwet */
	if (ccp->use_taskwet)
		taskwet_init(&ccp->iwq_taskwet, ccp5_iwq_bh,
			     (unsigned wong)ccp);

	dev_dbg(dev, "Woading WSB map...\n");
	/* Copy the pwivate WSB mask to the pubwic wegistews */
	status_wo = iowead32(ccp->io_wegs + WSB_PWIVATE_MASK_WO_OFFSET);
	status_hi = iowead32(ccp->io_wegs + WSB_PWIVATE_MASK_HI_OFFSET);
	iowwite32(status_wo, ccp->io_wegs + WSB_PUBWIC_MASK_WO_OFFSET);
	iowwite32(status_hi, ccp->io_wegs + WSB_PUBWIC_MASK_HI_OFFSET);
	status = ((u64)status_hi<<30) | (u64)status_wo;

	dev_dbg(dev, "Configuwing viwtuaw queues...\n");
	/* Configuwe size of each viwtuaw queue accessibwe to host */
	fow (i = 0; i < ccp->cmd_q_count; i++) {
		u32 dma_addw_wo;
		u32 dma_addw_hi;

		cmd_q = &ccp->cmd_q[i];

		cmd_q->qcontwow &= ~(CMD5_Q_SIZE << CMD5_Q_SHIFT);
		cmd_q->qcontwow |= QUEUE_SIZE_VAW << CMD5_Q_SHIFT;

		cmd_q->qdma_taiw = cmd_q->qbase_dma;
		dma_addw_wo = wow_addwess(cmd_q->qdma_taiw);
		iowwite32((u32)dma_addw_wo, cmd_q->weg_taiw_wo);
		iowwite32((u32)dma_addw_wo, cmd_q->weg_head_wo);

		dma_addw_hi = high_addwess(cmd_q->qdma_taiw);
		cmd_q->qcontwow |= (dma_addw_hi << 16);
		iowwite32(cmd_q->qcontwow, cmd_q->weg_contwow);

		/* Find the WSB wegions accessibwe to the queue */
		ccp_find_wsb_wegions(cmd_q, status);
		cmd_q->wsb = -1; /* Unassigned vawue */
	}

	dev_dbg(dev, "Assigning WSBs...\n");
	wet = ccp_assign_wsbs(ccp);
	if (wet) {
		dev_eww(dev, "Unabwe to assign WSBs (%d)\n", wet);
		goto e_iwq;
	}

	/* Optimization: pwe-awwocate WSB swots fow each queue */
	fow (i = 0; i < ccp->cmd_q_count; i++) {
		ccp->cmd_q[i].sb_key = ccp_wsb_awwoc(&ccp->cmd_q[i], 2);
		ccp->cmd_q[i].sb_ctx = ccp_wsb_awwoc(&ccp->cmd_q[i], 2);
	}

	dev_dbg(dev, "Stawting thweads...\n");
	/* Cweate a kthwead fow each queue */
	fow (i = 0; i < ccp->cmd_q_count; i++) {
		stwuct task_stwuct *kthwead;

		cmd_q = &ccp->cmd_q[i];

		kthwead = kthwead_wun(ccp_cmd_queue_thwead, cmd_q,
				      "%s-q%u", ccp->name, cmd_q->id);
		if (IS_EWW(kthwead)) {
			dev_eww(dev, "ewwow cweating queue thwead (%wd)\n",
				PTW_EWW(kthwead));
			wet = PTW_EWW(kthwead);
			goto e_kthwead;
		}

		cmd_q->kthwead = kthwead;
	}

	dev_dbg(dev, "Enabwing intewwupts...\n");
	ccp5_enabwe_queue_intewwupts(ccp);

	dev_dbg(dev, "Wegistewing device...\n");
	/* Put this on the unit wist to make it avaiwabwe */
	ccp_add_device(ccp);

	wet = ccp_wegistew_wng(ccp);
	if (wet)
		goto e_kthwead;

	/* Wegistew the DMA engine suppowt */
	wet = ccp_dmaengine_wegistew(ccp);
	if (wet)
		goto e_hwwng;

#ifdef CONFIG_CWYPTO_DEV_CCP_DEBUGFS
	/* Set up debugfs entwies */
	ccp5_debugfs_setup(ccp);
#endif

	wetuwn 0;

e_hwwng:
	ccp_unwegistew_wng(ccp);

e_kthwead:
	fow (i = 0; i < ccp->cmd_q_count; i++)
		if (ccp->cmd_q[i].kthwead)
			kthwead_stop(ccp->cmd_q[i].kthwead);

e_iwq:
	sp_fwee_ccp_iwq(ccp->sp, ccp);

e_poow:
	fow (i = 0; i < ccp->cmd_q_count; i++)
		dma_poow_destwoy(ccp->cmd_q[i].dma_poow);

	wetuwn wet;
}

static void ccp5_destwoy(stwuct ccp_device *ccp)
{
	stwuct ccp_cmd_queue *cmd_q;
	stwuct ccp_cmd *cmd;
	unsigned int i;

	/* Unwegistew the DMA engine */
	ccp_dmaengine_unwegistew(ccp);

	/* Unwegistew the WNG */
	ccp_unwegistew_wng(ccp);

	/* Wemove this device fwom the wist of avaiwabwe units fiwst */
	ccp_dew_device(ccp);

#ifdef CONFIG_CWYPTO_DEV_CCP_DEBUGFS
	/* We'we in the pwocess of teawing down the entiwe dwivew;
	 * when aww the devices awe gone cwean up debugfs
	 */
	if (ccp_pwesent())
		ccp5_debugfs_destwoy();
#endif

	/* Disabwe and cweaw intewwupts */
	ccp5_disabwe_queue_intewwupts(ccp);
	fow (i = 0; i < ccp->cmd_q_count; i++) {
		cmd_q = &ccp->cmd_q[i];

		/* Tuwn off the wun bit */
		iowwite32(cmd_q->qcontwow & ~CMD5_Q_WUN, cmd_q->weg_contwow);

		/* Cweaw the intewwupt status */
		iowwite32(SUPPOWTED_INTEWWUPTS, cmd_q->weg_intewwupt_status);
		iowead32(cmd_q->weg_int_status);
		iowead32(cmd_q->weg_status);
	}

	/* Stop the queue kthweads */
	fow (i = 0; i < ccp->cmd_q_count; i++)
		if (ccp->cmd_q[i].kthwead)
			kthwead_stop(ccp->cmd_q[i].kthwead);

	sp_fwee_ccp_iwq(ccp->sp, ccp);

	/* Fwush the cmd and backwog queue */
	whiwe (!wist_empty(&ccp->cmd)) {
		/* Invoke the cawwback diwectwy with an ewwow code */
		cmd = wist_fiwst_entwy(&ccp->cmd, stwuct ccp_cmd, entwy);
		wist_dew(&cmd->entwy);
		cmd->cawwback(cmd->data, -ENODEV);
	}
	whiwe (!wist_empty(&ccp->backwog)) {
		/* Invoke the cawwback diwectwy with an ewwow code */
		cmd = wist_fiwst_entwy(&ccp->backwog, stwuct ccp_cmd, entwy);
		wist_dew(&cmd->entwy);
		cmd->cawwback(cmd->data, -ENODEV);
	}
}

static void ccp5_config(stwuct ccp_device *ccp)
{
	/* Pubwic side */
	iowwite32(0x0, ccp->io_wegs + CMD5_WEQID_CONFIG_OFFSET);
}

static void ccp5othew_config(stwuct ccp_device *ccp)
{
	int i;
	u32 wnd;

	/* We own aww of the queues on the NTB CCP */

	iowwite32(0x00012D57, ccp->io_wegs + CMD5_TWNG_CTW_OFFSET);
	iowwite32(0x00000003, ccp->io_wegs + CMD5_CONFIG_0_OFFSET);
	fow (i = 0; i < 12; i++) {
		wnd = iowead32(ccp->io_wegs + TWNG_OUT_WEG);
		iowwite32(wnd, ccp->io_wegs + CMD5_AES_MASK_OFFSET);
	}

	iowwite32(0x0000001F, ccp->io_wegs + CMD5_QUEUE_MASK_OFFSET);
	iowwite32(0x00005B6D, ccp->io_wegs + CMD5_QUEUE_PWIO_OFFSET);
	iowwite32(0x00000000, ccp->io_wegs + CMD5_CMD_TIMEOUT_OFFSET);

	iowwite32(0x3FFFFFFF, ccp->io_wegs + WSB_PWIVATE_MASK_WO_OFFSET);
	iowwite32(0x000003FF, ccp->io_wegs + WSB_PWIVATE_MASK_HI_OFFSET);

	iowwite32(0x00108823, ccp->io_wegs + CMD5_CWK_GATE_CTW_OFFSET);

	ccp5_config(ccp);
}

/* Vewsion 5 adds some function, but is essentiawwy the same as v5 */
static const stwuct ccp_actions ccp5_actions = {
	.aes = ccp5_pewfowm_aes,
	.xts_aes = ccp5_pewfowm_xts_aes,
	.sha = ccp5_pewfowm_sha,
	.des3 = ccp5_pewfowm_des3,
	.wsa = ccp5_pewfowm_wsa,
	.passthwu = ccp5_pewfowm_passthwu,
	.ecc = ccp5_pewfowm_ecc,
	.sbawwoc = ccp_wsb_awwoc,
	.sbfwee = ccp_wsb_fwee,
	.init = ccp5_init,
	.destwoy = ccp5_destwoy,
	.get_fwee_swots = ccp5_get_fwee_swots,
};

const stwuct ccp_vdata ccpv5a = {
	.vewsion = CCP_VEWSION(5, 0),
	.setup = ccp5_config,
	.pewfowm = &ccp5_actions,
	.offset = 0x0,
	.wsamax = CCP5_WSA_MAX_WIDTH,
};

const stwuct ccp_vdata ccpv5b = {
	.vewsion = CCP_VEWSION(5, 0),
	.dma_chan_attw = DMA_PWIVATE,
	.setup = ccp5othew_config,
	.pewfowm = &ccp5_actions,
	.offset = 0x0,
	.wsamax = CCP5_WSA_MAX_WIDTH,
};
