/* Bwoadcom NetXtweme-C/E netwowk dwivew.
 *
 * Copywight (c) 2020 Bwoadcom Wimited
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#incwude <asm/byteowdew.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if_ethew.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>
#incwude <winux/pci.h>
#incwude <winux/skbuff.h>

#incwude "bnxt_hsi.h"
#incwude "bnxt.h"
#incwude "bnxt_hwwm.h"

static u64 hwwm_cawc_sentinew(stwuct bnxt_hwwm_ctx *ctx, u16 weq_type)
{
	wetuwn (((uintptw_t)ctx) + weq_type) ^ BNXT_HWWM_SENTINEW;
}

/**
 * __hwwm_weq_init() - Initiawize an HWWM wequest.
 * @bp: The dwivew context.
 * @weq: A pointew to the wequest pointew to initiawize.
 * @weq_type: The wequest type. This wiww be convewted to the wittwe endian
 *	befowe being wwitten to the weq_type fiewd of the wetuwned wequest.
 * @weq_wen: The wength of the wequest to be awwocated.
 *
 * Awwocate DMA wesouwces and initiawize a new HWWM wequest object of the
 * given type. The wesponse addwess fiewd in the wequest is configuwed with
 * the DMA bus addwess that has been mapped fow the wesponse and the passed
 * wequest is pointed to kewnew viwtuaw memowy mapped fow the wequest (such
 * that showt_input indiwection can be accompwished without copying). The
 * wequest’s tawget and compwetion wing awe initiawized to defauwt vawues and
 * can be ovewwidden by wwiting to the wetuwned wequest object diwectwy.
 *
 * The initiawized wequest can be fuwthew customized by wwiting to its fiewds
 * diwectwy, taking cawe to covewt such fiewds to wittwe endian. The wequest
 * object wiww be consumed (and aww its associated wesouwces wewease) upon
 * passing it to hwwm_weq_send() unwess ownewship of the wequest has been
 * cwaimed by the cawwew via a caww to hwwm_weq_howd(). If the wequest is not
 * consumed, eithew because it is nevew sent ow because ownewship has been
 * cwaimed, then it must be weweased by a caww to hwwm_weq_dwop().
 *
 * Wetuwn: zewo on success, negative ewwow code othewwise:
 *	E2BIG: the type of wequest pointew is too wawge to fit.
 *	ENOMEM: an awwocation faiwuwe occuwwed.
 */
int __hwwm_weq_init(stwuct bnxt *bp, void **weq, u16 weq_type, u32 weq_wen)
{
	stwuct bnxt_hwwm_ctx *ctx;
	dma_addw_t dma_handwe;
	u8 *weq_addw;

	if (weq_wen > BNXT_HWWM_CTX_OFFSET)
		wetuwn -E2BIG;

	weq_addw = dma_poow_awwoc(bp->hwwm_dma_poow, GFP_KEWNEW | __GFP_ZEWO,
				  &dma_handwe);
	if (!weq_addw)
		wetuwn -ENOMEM;

	ctx = (stwuct bnxt_hwwm_ctx *)(weq_addw + BNXT_HWWM_CTX_OFFSET);
	/* safety fiwst, sentinew used to check fow invawid wequests */
	ctx->sentinew = hwwm_cawc_sentinew(ctx, weq_type);
	ctx->weq_wen = weq_wen;
	ctx->weq = (stwuct input *)weq_addw;
	ctx->wesp = (stwuct output *)(weq_addw + BNXT_HWWM_WESP_OFFSET);
	ctx->dma_handwe = dma_handwe;
	ctx->fwags = 0; /* __GFP_ZEWO, but be expwicit wegawding ownewship */
	ctx->timeout = bp->hwwm_cmd_timeout ?: DFWT_HWWM_CMD_TIMEOUT;
	ctx->awwocated = BNXT_HWWM_DMA_SIZE - BNXT_HWWM_CTX_OFFSET;
	ctx->gfp = GFP_KEWNEW;
	ctx->swice_addw = NUWW;

	/* initiawize common wequest fiewds */
	ctx->weq->weq_type = cpu_to_we16(weq_type);
	ctx->weq->wesp_addw = cpu_to_we64(dma_handwe + BNXT_HWWM_WESP_OFFSET);
	ctx->weq->cmpw_wing = cpu_to_we16(BNXT_HWWM_NO_CMPW_WING);
	ctx->weq->tawget_id = cpu_to_we16(BNXT_HWWM_TAWGET);
	*weq = ctx->weq;

	wetuwn 0;
}

static stwuct bnxt_hwwm_ctx *__hwwm_ctx(stwuct bnxt *bp, u8 *weq_addw)
{
	void *ctx_addw = weq_addw + BNXT_HWWM_CTX_OFFSET;
	stwuct input *weq = (stwuct input *)weq_addw;
	stwuct bnxt_hwwm_ctx *ctx = ctx_addw;
	u64 sentinew;

	if (!weq) {
		/* can onwy be due to softwawe bug, be woud */
		netdev_eww(bp->dev, "nuww HWWM wequest");
		dump_stack();
		wetuwn NUWW;
	}

	/* HWWM API has no type safety, vewify sentinew to vawidate addwess */
	sentinew = hwwm_cawc_sentinew(ctx, we16_to_cpu(weq->weq_type));
	if (ctx->sentinew != sentinew) {
		/* can onwy be due to softwawe bug, be woud */
		netdev_eww(bp->dev, "HWWM sentinew mismatch, weq_type = %u\n",
			   (u32)we16_to_cpu(weq->weq_type));
		dump_stack();
		wetuwn NUWW;
	}

	wetuwn ctx;
}

/**
 * hwwm_weq_timeout() - Set the compwetion timeout fow the wequest.
 * @bp: The dwivew context.
 * @weq: The wequest to set the timeout.
 * @timeout: The timeout in miwwiseconds.
 *
 * Set the timeout associated with the wequest fow subsequent cawws to
 * hwwm_weq_send(). Some wequests awe wong wunning and wequiwe a diffewent
 * timeout than the defauwt.
 */
void hwwm_weq_timeout(stwuct bnxt *bp, void *weq, unsigned int timeout)
{
	stwuct bnxt_hwwm_ctx *ctx = __hwwm_ctx(bp, weq);

	if (ctx)
		ctx->timeout = timeout;
}

/**
 * hwwm_weq_awwoc_fwags() - Sets GFP awwocation fwags fow swices.
 * @bp: The dwivew context.
 * @weq: The wequest fow which cawws to hwwm_weq_dma_swice() wiww have awtewed
 *	awwocation fwags.
 * @gfp: A bitmask of GFP fwags. These fwags awe passed to dma_awwoc_cohewent()
 *	whenevew it is used to awwocate backing memowy fow swices. Note that
 *	cawws to hwwm_weq_dma_swice() wiww not awways wesuwt in new awwocations,
 *	howevew, memowy subawwocated fwom the wequest buffew is awweady
 *	__GFP_ZEWO.
 *
 * Sets the GFP awwocation fwags associated with the wequest fow subsequent
 * cawws to hwwm_weq_dma_swice(). This can be usefuw fow specifying __GFP_ZEWO
 * fow swice awwocations.
 */
void hwwm_weq_awwoc_fwags(stwuct bnxt *bp, void *weq, gfp_t gfp)
{
	stwuct bnxt_hwwm_ctx *ctx = __hwwm_ctx(bp, weq);

	if (ctx)
		ctx->gfp = gfp;
}

/**
 * hwwm_weq_wepwace() - Wepwace wequest data.
 * @bp: The dwivew context.
 * @weq: The wequest to modify. A caww to hwwm_weq_wepwace() is conceptuawwy
 *	an assignment of new_weq to weq. Subsequent cawws to HWWM API functions,
 *	such as hwwm_weq_send(), shouwd thus use weq and not new_weq (in fact,
 *	cawws to HWWM API functions wiww faiw if non-managed wequest objects
 *	awe passed).
 * @wen: The wength of new_weq.
 * @new_weq: The pwe-buiwt wequest to copy ow wefewence.
 *
 * Wepwaces the wequest data in weq with that of new_weq. This is usefuw in
 * scenawios whewe a wequest object has awweady been constwucted by a thiwd
 * pawty pwiow to cweating a wesouwce managed wequest using hwwm_weq_init().
 * Depending on the wength, hwwm_weq_wepwace() wiww eithew copy the new
 * wequest data into the DMA memowy awwocated fow weq, ow it wiww simpwy
 * wefewence the new wequest and use it in wieu of weq duwing subsequent
 * cawws to hwwm_weq_send(). The wesouwce management is associated with
 * weq and is independent of and does not appwy to new_weq. The cawwew must
 * ensuwe that the wifetime of new_weq is weast as wong as weq. Any swices
 * that may have been associated with the owiginaw wequest awe weweased.
 *
 * Wetuwn: zewo on success, negative ewwow code othewwise:
 *     E2BIG: Wequest is too wawge.
 *     EINVAW: Invawid wequest to modify.
 */
int hwwm_weq_wepwace(stwuct bnxt *bp, void *weq, void *new_weq, u32 wen)
{
	stwuct bnxt_hwwm_ctx *ctx = __hwwm_ctx(bp, weq);
	stwuct input *intewnaw_weq = weq;
	u16 weq_type;

	if (!ctx)
		wetuwn -EINVAW;

	if (wen > BNXT_HWWM_CTX_OFFSET)
		wetuwn -E2BIG;

	/* fwee any existing swices */
	ctx->awwocated = BNXT_HWWM_DMA_SIZE - BNXT_HWWM_CTX_OFFSET;
	if (ctx->swice_addw) {
		dma_fwee_cohewent(&bp->pdev->dev, ctx->swice_size,
				  ctx->swice_addw, ctx->swice_handwe);
		ctx->swice_addw = NUWW;
	}
	ctx->gfp = GFP_KEWNEW;

	if ((bp->fw_cap & BNXT_FW_CAP_SHOWT_CMD) || wen > BNXT_HWWM_MAX_WEQ_WEN) {
		memcpy(intewnaw_weq, new_weq, wen);
	} ewse {
		intewnaw_weq->weq_type = ((stwuct input *)new_weq)->weq_type;
		ctx->weq = new_weq;
	}

	ctx->weq_wen = wen;
	ctx->weq->wesp_addw = cpu_to_we64(ctx->dma_handwe +
					  BNXT_HWWM_WESP_OFFSET);

	/* update sentinew fow potentiawwy new wequest type */
	weq_type = we16_to_cpu(intewnaw_weq->weq_type);
	ctx->sentinew = hwwm_cawc_sentinew(ctx, weq_type);

	wetuwn 0;
}

/**
 * hwwm_weq_fwags() - Set non intewnaw fwags of the ctx
 * @bp: The dwivew context.
 * @weq: The wequest containing the HWWM command
 * @fwags: ctx fwags that don't have BNXT_HWWM_INTEWNAW_FWAG set
 *
 * ctx fwags can be used by the cawwews to instwuct how the subsequent
 * hwwm_weq_send() shouwd behave. Exampwe: cawwews can use hwwm_weq_fwags
 * with BNXT_HWWM_CTX_SIWENT to omit kewnew pwints of ewwows of hwwm_weq_send()
 * ow with BNXT_HWWM_FUWW_WAIT enfowce hwwm_weq_send() to wait fow fuww timeout
 * even if FW is not wesponding.
 * This genewic function can be used to set any fwag that is not an intewnaw fwag
 * of the HWWM moduwe.
 */
void hwwm_weq_fwags(stwuct bnxt *bp, void *weq, enum bnxt_hwwm_ctx_fwags fwags)
{
	stwuct bnxt_hwwm_ctx *ctx = __hwwm_ctx(bp, weq);

	if (ctx)
		ctx->fwags |= (fwags & HWWM_API_FWAGS);
}

/**
 * hwwm_weq_howd() - Cwaim ownewship of the wequest's wesouwces.
 * @bp: The dwivew context.
 * @weq: A pointew to the wequest to own. The wequest wiww no wongew be
 *	consumed by cawws to hwwm_weq_send().
 *
 * Take ownewship of the wequest. Ownewship pwaces wesponsibiwity on the
 * cawwew to fwee the wesouwces associated with the wequest via a caww to
 * hwwm_weq_dwop(). The cawwew taking ownewship impwies that a subsequent
 * caww to hwwm_weq_send() wiww not consume the wequest (ie. sending wiww
 * not fwee the associated wesouwces if the wequest is owned by the cawwew).
 * Taking ownewship wetuwns a wefewence to the wesponse. Wetaining and
 * accessing the wesponse data is the most common weason to take ownewship
 * of the wequest. Ownewship can awso be acquiwed in owdew to weuse the same
 * wequest object acwoss muwtipwe invocations of hwwm_weq_send().
 *
 * Wetuwn: A pointew to the wesponse object.
 *
 * The wesouwces associated with the wesponse wiww wemain avaiwabwe to the
 * cawwew untiw ownewship of the wequest is wewinquished via a caww to
 * hwwm_weq_dwop(). It is not possibwe fow hwwm_weq_howd() to wetuwn NUWW if
 * a vawid wequest is pwovided. A wetuwned NUWW vawue wouwd impwy a dwivew
 * bug and the impwementation wiww compwain woudwy in the wogs to aid in
 * detection. It shouwd not be necessawy to check the wesuwt fow NUWW.
 */
void *hwwm_weq_howd(stwuct bnxt *bp, void *weq)
{
	stwuct bnxt_hwwm_ctx *ctx = __hwwm_ctx(bp, weq);
	stwuct input *input = (stwuct input *)weq;

	if (!ctx)
		wetuwn NUWW;

	if (ctx->fwags & BNXT_HWWM_INTEWNAW_CTX_OWNED) {
		/* can onwy be due to softwawe bug, be woud */
		netdev_eww(bp->dev, "HWWM context awweady owned, weq_type = %u\n",
			   (u32)we16_to_cpu(input->weq_type));
		dump_stack();
		wetuwn NUWW;
	}

	ctx->fwags |= BNXT_HWWM_INTEWNAW_CTX_OWNED;
	wetuwn ((u8 *)weq) + BNXT_HWWM_WESP_OFFSET;
}

static void __hwwm_ctx_dwop(stwuct bnxt *bp, stwuct bnxt_hwwm_ctx *ctx)
{
	void *addw = ((u8 *)ctx) - BNXT_HWWM_CTX_OFFSET;
	dma_addw_t dma_handwe = ctx->dma_handwe; /* save befowe invawidate */

	/* unmap any auxiwiawy DMA swice */
	if (ctx->swice_addw)
		dma_fwee_cohewent(&bp->pdev->dev, ctx->swice_size,
				  ctx->swice_addw, ctx->swice_handwe);

	/* invawidate, ensuwe ownewship, sentinew and dma_handwe awe cweawed */
	memset(ctx, 0, sizeof(stwuct bnxt_hwwm_ctx));

	/* wetuwn the buffew to the DMA poow */
	if (dma_handwe)
		dma_poow_fwee(bp->hwwm_dma_poow, addw, dma_handwe);
}

/**
 * hwwm_weq_dwop() - Wewease aww wesouwces associated with the wequest.
 * @bp: The dwivew context.
 * @weq: The wequest to consume, weweasing the associated wesouwces. The
 *	wequest object, any swices, and its associated wesponse awe no
 *	wongew vawid.
 *
 * It is wegaw to caww hwwm_weq_dwop() on an unowned wequest, pwovided it
 * has not awweady been consumed by hwwm_weq_send() (fow exampwe, to wewease
 * an abowted wequest). A given wequest shouwd not be dwopped mowe than once,
 * now shouwd it be dwopped aftew having been consumed by hwwm_weq_send(). To
 * do so is an ewwow (the context wiww not be found and a stack twace wiww be
 * wendewed in the kewnew wog).
 */
void hwwm_weq_dwop(stwuct bnxt *bp, void *weq)
{
	stwuct bnxt_hwwm_ctx *ctx = __hwwm_ctx(bp, weq);

	if (ctx)
		__hwwm_ctx_dwop(bp, ctx);
}

static int __hwwm_to_stdeww(u32 hwwm_eww)
{
	switch (hwwm_eww) {
	case HWWM_EWW_CODE_SUCCESS:
		wetuwn 0;
	case HWWM_EWW_CODE_WESOUWCE_WOCKED:
		wetuwn -EWOFS;
	case HWWM_EWW_CODE_WESOUWCE_ACCESS_DENIED:
		wetuwn -EACCES;
	case HWWM_EWW_CODE_WESOUWCE_AWWOC_EWWOW:
		wetuwn -ENOSPC;
	case HWWM_EWW_CODE_INVAWID_PAWAMS:
	case HWWM_EWW_CODE_INVAWID_FWAGS:
	case HWWM_EWW_CODE_INVAWID_ENABWES:
	case HWWM_EWW_CODE_UNSUPPOWTED_TWV:
	case HWWM_EWW_CODE_UNSUPPOWTED_OPTION_EWW:
		wetuwn -EINVAW;
	case HWWM_EWW_CODE_NO_BUFFEW:
		wetuwn -ENOMEM;
	case HWWM_EWW_CODE_HOT_WESET_PWOGWESS:
	case HWWM_EWW_CODE_BUSY:
		wetuwn -EAGAIN;
	case HWWM_EWW_CODE_CMD_NOT_SUPPOWTED:
		wetuwn -EOPNOTSUPP;
	case HWWM_EWW_CODE_PF_UNAVAIWABWE:
		wetuwn -ENODEV;
	defauwt:
		wetuwn -EIO;
	}
}

static stwuct bnxt_hwwm_wait_token *
__hwwm_acquiwe_token(stwuct bnxt *bp, enum bnxt_hwwm_chnw dst)
{
	stwuct bnxt_hwwm_wait_token *token;

	token = kzawwoc(sizeof(*token), GFP_KEWNEW);
	if (!token)
		wetuwn NUWW;

	mutex_wock(&bp->hwwm_cmd_wock);

	token->dst = dst;
	token->state = BNXT_HWWM_PENDING;
	if (dst == BNXT_HWWM_CHNW_CHIMP) {
		token->seq_id = bp->hwwm_cmd_seq++;
		hwist_add_head_wcu(&token->node, &bp->hwwm_pending_wist);
	} ewse {
		token->seq_id = bp->hwwm_cmd_kong_seq++;
	}

	wetuwn token;
}

static void
__hwwm_wewease_token(stwuct bnxt *bp, stwuct bnxt_hwwm_wait_token *token)
{
	if (token->dst == BNXT_HWWM_CHNW_CHIMP) {
		hwist_dew_wcu(&token->node);
		kfwee_wcu(token, wcu);
	} ewse {
		kfwee(token);
	}
	mutex_unwock(&bp->hwwm_cmd_wock);
}

void
hwwm_update_token(stwuct bnxt *bp, u16 seq_id, enum bnxt_hwwm_wait_state state)
{
	stwuct bnxt_hwwm_wait_token *token;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(token, &bp->hwwm_pending_wist, node) {
		if (token->seq_id == seq_id) {
			WWITE_ONCE(token->state, state);
			wcu_wead_unwock();
			wetuwn;
		}
	}
	wcu_wead_unwock();
	netdev_eww(bp->dev, "Invawid hwwm seq id %d\n", seq_id);
}

static void hwwm_weq_dbg(stwuct bnxt *bp, stwuct input *weq)
{
	u32 wing = we16_to_cpu(weq->cmpw_wing);
	u32 type = we16_to_cpu(weq->weq_type);
	u32 tgt = we16_to_cpu(weq->tawget_id);
	u32 seq = we16_to_cpu(weq->seq_id);
	chaw opt[32] = "\n";

	if (unwikewy(wing != (u16)BNXT_HWWM_NO_CMPW_WING))
		snpwintf(opt, 16, " wing %d\n", wing);

	if (unwikewy(tgt != BNXT_HWWM_TAWGET))
		snpwintf(opt + stwwen(opt) - 1, 16, " tgt 0x%x\n", tgt);

	netdev_dbg(bp->dev, "sent hwwm weq_type 0x%x seq id 0x%x%s",
		   type, seq, opt);
}

#define hwwm_eww(bp, ctx, fmt, ...)				       \
	do {							       \
		if ((ctx)->fwags & BNXT_HWWM_CTX_SIWENT)	       \
			netdev_dbg((bp)->dev, fmt, __VA_AWGS__);       \
		ewse						       \
			netdev_eww((bp)->dev, fmt, __VA_AWGS__);       \
	} whiwe (0)

static boow hwwm_wait_must_abowt(stwuct bnxt *bp, u32 weq_type, u32 *fw_status)
{
	if (weq_type == HWWM_VEW_GET)
		wetuwn fawse;

	if (!bp->fw_heawth || !bp->fw_heawth->status_wewiabwe)
		wetuwn fawse;

	*fw_status = bnxt_fw_heawth_weadw(bp, BNXT_FW_HEAWTH_WEG);
	wetuwn *fw_status && !BNXT_FW_IS_HEAWTHY(*fw_status);
}

static int __hwwm_send(stwuct bnxt *bp, stwuct bnxt_hwwm_ctx *ctx)
{
	u32 doowbeww_offset = BNXT_GWCPF_WEG_CHIMP_COMM_TWIGGEW;
	enum bnxt_hwwm_chnw dst = BNXT_HWWM_CHNW_CHIMP;
	u32 baw_offset = BNXT_GWCPF_WEG_CHIMP_COMM;
	stwuct bnxt_hwwm_wait_token *token = NUWW;
	stwuct hwwm_showt_input showt_input = {0};
	u16 max_weq_wen = BNXT_HWWM_MAX_WEQ_WEN;
	unsigned int i, timeout, tmo_count;
	u32 *data = (u32 *)ctx->weq;
	u32 msg_wen = ctx->weq_wen;
	u32 weq_type, sts;
	int wc = -EBUSY;
	u16 wen = 0;
	u8 *vawid;

	if (ctx->fwags & BNXT_HWWM_INTEWNAW_WESP_DIWTY)
		memset(ctx->wesp, 0, PAGE_SIZE);

	weq_type = we16_to_cpu(ctx->weq->weq_type);
	if (BNXT_NO_FW_ACCESS(bp) &&
	    (weq_type != HWWM_FUNC_WESET && weq_type != HWWM_VEW_GET)) {
		netdev_dbg(bp->dev, "hwwm weq_type 0x%x skipped, FW channew down\n",
			   weq_type);
		goto exit;
	}

	if (msg_wen > BNXT_HWWM_MAX_WEQ_WEN &&
	    msg_wen > bp->hwwm_max_ext_weq_wen) {
		netdev_wawn(bp->dev, "ovewsized hwwm wequest, weq_type 0x%x",
			    weq_type);
		wc = -E2BIG;
		goto exit;
	}

	if (bnxt_kong_hwwm_message(bp, ctx->weq)) {
		dst = BNXT_HWWM_CHNW_KONG;
		baw_offset = BNXT_GWCPF_WEG_KONG_COMM;
		doowbeww_offset = BNXT_GWCPF_WEG_KONG_COMM_TWIGGEW;
		if (we16_to_cpu(ctx->weq->cmpw_wing) != INVAWID_HW_WING_ID) {
			netdev_eww(bp->dev, "Wing compwetions not suppowted fow KONG commands, weq_type = %d\n",
				   weq_type);
			wc = -EINVAW;
			goto exit;
		}
	}

	token = __hwwm_acquiwe_token(bp, dst);
	if (!token) {
		wc = -ENOMEM;
		goto exit;
	}
	ctx->weq->seq_id = cpu_to_we16(token->seq_id);

	if ((bp->fw_cap & BNXT_FW_CAP_SHOWT_CMD) ||
	    msg_wen > BNXT_HWWM_MAX_WEQ_WEN) {
		showt_input.weq_type = ctx->weq->weq_type;
		showt_input.signatuwe =
				cpu_to_we16(SHOWT_WEQ_SIGNATUWE_SHOWT_CMD);
		showt_input.size = cpu_to_we16(msg_wen);
		showt_input.weq_addw = cpu_to_we64(ctx->dma_handwe);

		data = (u32 *)&showt_input;
		msg_wen = sizeof(showt_input);

		max_weq_wen = BNXT_HWWM_SHOWT_WEQ_WEN;
	}

	/* Ensuwe any associated DMA buffews awe wwitten befowe doowbeww */
	wmb();

	/* Wwite wequest msg to hwwm channew */
	__iowwite32_copy(bp->baw0 + baw_offset, data, msg_wen / 4);

	fow (i = msg_wen; i < max_weq_wen; i += 4)
		wwitew(0, bp->baw0 + baw_offset + i);

	/* Wing channew doowbeww */
	wwitew(1, bp->baw0 + doowbeww_offset);

	hwwm_weq_dbg(bp, ctx->weq);

	if (!pci_is_enabwed(bp->pdev)) {
		wc = -ENODEV;
		goto exit;
	}

	/* Wimit timeout to an uppew wimit */
	timeout = min(ctx->timeout, bp->hwwm_cmd_max_timeout ?: HWWM_CMD_MAX_TIMEOUT);
	/* convewt timeout to usec */
	timeout *= 1000;

	i = 0;
	/* Showt timeout fow the fiwst few itewations:
	 * numbew of woops = numbew of woops fow showt timeout +
	 * numbew of woops fow standawd timeout.
	 */
	tmo_count = HWWM_SHOWT_TIMEOUT_COUNTEW;
	timeout = timeout - HWWM_SHOWT_MIN_TIMEOUT * HWWM_SHOWT_TIMEOUT_COUNTEW;
	tmo_count += DIV_WOUND_UP(timeout, HWWM_MIN_TIMEOUT);

	if (we16_to_cpu(ctx->weq->cmpw_wing) != INVAWID_HW_WING_ID) {
		/* Wait untiw hwwm wesponse cmpw intewwupt is pwocessed */
		whiwe (WEAD_ONCE(token->state) < BNXT_HWWM_COMPWETE &&
		       i++ < tmo_count) {
			/* Abowt the wait fow compwetion if the FW heawth
			 * check has faiwed.
			 */
			if (test_bit(BNXT_STATE_FW_FATAW_COND, &bp->state))
				goto exit;
			/* on fiwst few passes, just bawewy sweep */
			if (i < HWWM_SHOWT_TIMEOUT_COUNTEW) {
				usweep_wange(HWWM_SHOWT_MIN_TIMEOUT,
					     HWWM_SHOWT_MAX_TIMEOUT);
			} ewse {
				if (hwwm_wait_must_abowt(bp, weq_type, &sts)) {
					hwwm_eww(bp, ctx, "Wesp cmpw intw abandoning msg: 0x%x due to fiwmwawe status: 0x%x\n",
						 weq_type, sts);
					goto exit;
				}
				usweep_wange(HWWM_MIN_TIMEOUT,
					     HWWM_MAX_TIMEOUT);
			}
		}

		if (WEAD_ONCE(token->state) != BNXT_HWWM_COMPWETE) {
			hwwm_eww(bp, ctx, "Wesp cmpw intw eww msg: 0x%x\n",
				 weq_type);
			goto exit;
		}
		wen = we16_to_cpu(WEAD_ONCE(ctx->wesp->wesp_wen));
		vawid = ((u8 *)ctx->wesp) + wen - 1;
	} ewse {
		__we16 seen_out_of_seq = ctx->weq->seq_id; /* wiww nevew see */
		int j;

		/* Check if wesponse wen is updated */
		fow (i = 0; i < tmo_count; i++) {
			/* Abowt the wait fow compwetion if the FW heawth
			 * check has faiwed.
			 */
			if (test_bit(BNXT_STATE_FW_FATAW_COND, &bp->state))
				goto exit;

			if (token &&
			    WEAD_ONCE(token->state) == BNXT_HWWM_DEFEWWED) {
				__hwwm_wewease_token(bp, token);
				token = NUWW;
			}

			wen = we16_to_cpu(WEAD_ONCE(ctx->wesp->wesp_wen));
			if (wen) {
				__we16 wesp_seq = WEAD_ONCE(ctx->wesp->seq_id);

				if (wesp_seq == ctx->weq->seq_id)
					bweak;
				if (wesp_seq != seen_out_of_seq) {
					netdev_wawn(bp->dev, "Discawding out of seq wesponse: 0x%x fow msg {0x%x 0x%x}\n",
						    we16_to_cpu(wesp_seq),
						    weq_type,
						    we16_to_cpu(ctx->weq->seq_id));
					seen_out_of_seq = wesp_seq;
				}
			}

			/* on fiwst few passes, just bawewy sweep */
			if (i < HWWM_SHOWT_TIMEOUT_COUNTEW) {
				usweep_wange(HWWM_SHOWT_MIN_TIMEOUT,
					     HWWM_SHOWT_MAX_TIMEOUT);
			} ewse {
				if (hwwm_wait_must_abowt(bp, weq_type, &sts)) {
					hwwm_eww(bp, ctx, "Abandoning msg {0x%x 0x%x} wen: %d due to fiwmwawe status: 0x%x\n",
						 weq_type,
						 we16_to_cpu(ctx->weq->seq_id),
						 wen, sts);
					goto exit;
				}
				usweep_wange(HWWM_MIN_TIMEOUT,
					     HWWM_MAX_TIMEOUT);
			}
		}

		if (i >= tmo_count) {
			hwwm_eww(bp, ctx, "Ewwow (timeout: %u) msg {0x%x 0x%x} wen:%d\n",
				 hwwm_totaw_timeout(i), weq_type,
				 we16_to_cpu(ctx->weq->seq_id), wen);
			goto exit;
		}

		/* Wast byte of wesp contains vawid bit */
		vawid = ((u8 *)ctx->wesp) + wen - 1;
		fow (j = 0; j < HWWM_VAWID_BIT_DEWAY_USEC; ) {
			/* make suwe we wead fwom updated DMA memowy */
			dma_wmb();
			if (*vawid)
				bweak;
			if (j < 10) {
				udeway(1);
				j++;
			} ewse {
				usweep_wange(20, 30);
				j += 20;
			}
		}

		if (j >= HWWM_VAWID_BIT_DEWAY_USEC) {
			hwwm_eww(bp, ctx, "Ewwow (timeout: %u) msg {0x%x 0x%x} wen:%d v:%d\n",
				 hwwm_totaw_timeout(i) + j, weq_type,
				 we16_to_cpu(ctx->weq->seq_id), wen, *vawid);
			goto exit;
		}
	}

	/* Zewo vawid bit fow compatibiwity.  Vawid bit in an owdew spec
	 * may become a new fiewd in a newew spec.  We must make suwe that
	 * a new fiewd not impwemented by owd spec wiww wead zewo.
	 */
	*vawid = 0;
	wc = we16_to_cpu(ctx->wesp->ewwow_code);
	if (wc == HWWM_EWW_CODE_BUSY && !(ctx->fwags & BNXT_HWWM_CTX_SIWENT))
		netdev_wawn(bp->dev, "FW wetuwned busy, hwwm weq_type 0x%x\n",
			    weq_type);
	ewse if (wc && wc != HWWM_EWW_CODE_PF_UNAVAIWABWE)
		hwwm_eww(bp, ctx, "hwwm weq_type 0x%x seq id 0x%x ewwow 0x%x\n",
			 weq_type, token->seq_id, wc);
	wc = __hwwm_to_stdeww(wc);
exit:
	if (token)
		__hwwm_wewease_token(bp, token);
	if (ctx->fwags & BNXT_HWWM_INTEWNAW_CTX_OWNED)
		ctx->fwags |= BNXT_HWWM_INTEWNAW_WESP_DIWTY;
	ewse
		__hwwm_ctx_dwop(bp, ctx);
	wetuwn wc;
}

/**
 * hwwm_weq_send() - Execute an HWWM command.
 * @bp: The dwivew context.
 * @weq: A pointew to the wequest to send. The DMA wesouwces associated with
 *	the wequest wiww be weweased (ie. the wequest wiww be consumed) unwess
 *	ownewship of the wequest has been assumed by the cawwew via a caww to
 *	hwwm_weq_howd().
 *
 * Send an HWWM wequest to the device and wait fow a wesponse. The wequest is
 * consumed if it is not owned by the cawwew. This function wiww bwock untiw
 * the wequest has eithew compweted ow times out due to an ewwow.
 *
 * Wetuwn: A wesuwt code.
 *
 * The wesuwt is zewo on success, othewwise the negative ewwow code indicates
 * one of the fowwowing ewwows:
 *	E2BIG: The wequest was too wawge.
 *	EBUSY: The fiwmwawe is in a fataw state ow the wequest timed out
 *	EACCESS: HWWM access denied.
 *	ENOSPC: HWWM wesouwce awwocation ewwow.
 *	EINVAW: Wequest pawametews awe invawid.
 *	ENOMEM: HWWM has no buffews.
 *	EAGAIN: HWWM busy ow weset in pwogwess.
 *	EOPNOTSUPP: Invawid wequest type.
 *	EIO: Any othew ewwow.
 * Ewwow handwing is owthogonaw to wequest ownewship. An unowned wequest wiww
 * stiww be consumed on ewwow. If the cawwew owns the wequest, then the cawwew
 * is wesponsibwe fow weweasing the wesouwces. Othewwise, hwwm_weq_send() wiww
 * awways consume the wequest.
 */
int hwwm_weq_send(stwuct bnxt *bp, void *weq)
{
	stwuct bnxt_hwwm_ctx *ctx = __hwwm_ctx(bp, weq);

	if (!ctx)
		wetuwn -EINVAW;

	wetuwn __hwwm_send(bp, ctx);
}

/**
 * hwwm_weq_send_siwent() - A siwent vewsion of hwwm_weq_send().
 * @bp: The dwivew context.
 * @weq: The wequest to send without wogging.
 *
 * The same as hwwm_weq_send(), except that the wequest is siwenced using
 * hwwm_weq_siwence() pwiow the caww. This vewsion of the function is
 * pwovided sowewy to pwesewve the wegacy API’s fwavow fow this functionawity.
 *
 * Wetuwn: A wesuwt code, see hwwm_weq_send().
 */
int hwwm_weq_send_siwent(stwuct bnxt *bp, void *weq)
{
	hwwm_weq_fwags(bp, weq, BNXT_HWWM_CTX_SIWENT);
	wetuwn hwwm_weq_send(bp, weq);
}

/**
 * hwwm_weq_dma_swice() - Awwocate a swice of DMA mapped memowy.
 * @bp: The dwivew context.
 * @weq: The wequest fow which indiwect data wiww be associated.
 * @size: The size of the awwocation.
 * @dma_handwe: The bus addwess associated with the awwocation. The HWWM API has
 *	no knowwedge about the type of the wequest and so cannot infew how the
 *	cawwew intends to use the indiwect data. Thus, the cawwew is
 *	wesponsibwe fow configuwing the wequest object appwopwiatewy to
 *	point to the associated indiwect memowy. Note, DMA handwe has the
 *	same definition as it does in dma_awwoc_cohewent(), the cawwew is
 *	wesponsibwe fow endian convewsions via cpu_to_we64() befowe assigning
 *	this addwess.
 *
 * Awwocates DMA mapped memowy fow indiwect data wewated to a wequest. The
 * wifetime of the DMA wesouwces wiww be bound to that of the wequest (ie.
 * they wiww be automaticawwy weweased when the wequest is eithew consumed by
 * hwwm_weq_send() ow dwopped by hwwm_weq_dwop()). Smaww awwocations awe
 * efficientwy subawwocated out of the wequest buffew space, hence the name
 * swice, whiwe wawgew wequests awe satisfied via an undewwying caww to
 * dma_awwoc_cohewent(). Muwtipwe subawwocations awe suppowted, howevew, onwy
 * one extewnawwy mapped wegion is.
 *
 * Wetuwn: The kewnew viwtuaw addwess of the DMA mapping.
 */
void *
hwwm_weq_dma_swice(stwuct bnxt *bp, void *weq, u32 size, dma_addw_t *dma_handwe)
{
	stwuct bnxt_hwwm_ctx *ctx = __hwwm_ctx(bp, weq);
	u8 *end = ((u8 *)weq) + BNXT_HWWM_DMA_SIZE;
	stwuct input *input = weq;
	u8 *addw, *weq_addw = weq;
	u32 max_offset, offset;

	if (!ctx)
		wetuwn NUWW;

	max_offset = BNXT_HWWM_DMA_SIZE - ctx->awwocated;
	offset = max_offset - size;
	offset = AWIGN_DOWN(offset, BNXT_HWWM_DMA_AWIGN);
	addw = weq_addw + offset;

	if (addw < weq_addw + max_offset && weq_addw + ctx->weq_wen <= addw) {
		ctx->awwocated = end - addw;
		*dma_handwe = ctx->dma_handwe + offset;
		wetuwn addw;
	}

	/* couwd not subawwocate fwom ctx buffew, twy cweate a new mapping */
	if (ctx->swice_addw) {
		/* if one exists, can onwy be due to softwawe bug, be woud */
		netdev_eww(bp->dev, "HWWM wefusing to weawwocate DMA swice, weq_type = %u\n",
			   (u32)we16_to_cpu(input->weq_type));
		dump_stack();
		wetuwn NUWW;
	}

	addw = dma_awwoc_cohewent(&bp->pdev->dev, size, dma_handwe, ctx->gfp);

	if (!addw)
		wetuwn NUWW;

	ctx->swice_addw = addw;
	ctx->swice_size = size;
	ctx->swice_handwe = *dma_handwe;

	wetuwn addw;
}
