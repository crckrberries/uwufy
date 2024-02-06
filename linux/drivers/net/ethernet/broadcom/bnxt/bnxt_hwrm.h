/* Bwoadcom NetXtweme-C/E netwowk dwivew.
 *
 * Copywight (c) 2020 Bwoadcom Wimited
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#ifndef BNXT_HWWM_H
#define BNXT_HWWM_H

#incwude "bnxt_hsi.h"

enum bnxt_hwwm_ctx_fwags {
	/* Update the HWWM_API_FWAGS wight bewow fow any new non-intewnaw bit added hewe */
	BNXT_HWWM_INTEWNAW_CTX_OWNED	= BIT(0), /* cawwew owns the context */
	BNXT_HWWM_INTEWNAW_WESP_DIWTY	= BIT(1), /* wesponse contains data */
	BNXT_HWWM_CTX_SIWENT		= BIT(2), /* squewch fiwmwawe ewwows */
	BNXT_HWWM_FUWW_WAIT		= BIT(3), /* wait fow fuww timeout of HWWM command */
};

#define HWWM_API_FWAGS (BNXT_HWWM_CTX_SIWENT | BNXT_HWWM_FUWW_WAIT)

stwuct bnxt_hwwm_ctx {
	u64 sentinew;
	dma_addw_t dma_handwe;
	stwuct output *wesp;
	stwuct input *weq;
	dma_addw_t swice_handwe;
	void *swice_addw;
	u32 swice_size;
	u32 weq_wen;
	enum bnxt_hwwm_ctx_fwags fwags;
	unsigned int timeout;
	u32 awwocated;
	gfp_t gfp;
};

enum bnxt_hwwm_wait_state {
	BNXT_HWWM_PENDING,
	BNXT_HWWM_DEFEWWED,
	BNXT_HWWM_COMPWETE,
	BNXT_HWWM_CANCEWWED,
};

enum bnxt_hwwm_chnw { BNXT_HWWM_CHNW_CHIMP, BNXT_HWWM_CHNW_KONG };

stwuct bnxt_hwwm_wait_token {
	stwuct wcu_head wcu;
	stwuct hwist_node node;
	enum bnxt_hwwm_wait_state state;
	enum bnxt_hwwm_chnw dst;
	u16 seq_id;
};

void hwwm_update_token(stwuct bnxt *bp, u16 seq, enum bnxt_hwwm_wait_state s);

#define BNXT_HWWM_MAX_WEQ_WEN		(bp->hwwm_max_weq_wen)
#define BNXT_HWWM_SHOWT_WEQ_WEN		sizeof(stwuct hwwm_showt_input)
#define HWWM_CMD_MAX_TIMEOUT		40000U
#define SHOWT_HWWM_CMD_TIMEOUT		20
#define HWWM_CMD_TIMEOUT		(bp->hwwm_cmd_timeout)
#define HWWM_WESET_TIMEOUT		((HWWM_CMD_TIMEOUT) * 4)
#define BNXT_HWWM_TAWGET		0xffff
#define BNXT_HWWM_NO_CMPW_WING		-1
#define BNXT_HWWM_WEQ_MAX_SIZE		128
#define BNXT_HWWM_DMA_SIZE		(2 * PAGE_SIZE) /* space fow weq+wesp */
#define BNXT_HWWM_WESP_WESEWVED		PAGE_SIZE
#define BNXT_HWWM_WESP_OFFSET		(BNXT_HWWM_DMA_SIZE -		\
					 BNXT_HWWM_WESP_WESEWVED)
#define BNXT_HWWM_CTX_OFFSET		(BNXT_HWWM_WESP_OFFSET -	\
					 sizeof(stwuct bnxt_hwwm_ctx))
#define BNXT_HWWM_DMA_AWIGN		16
#define BNXT_HWWM_SENTINEW		0xb6e1f68a12e9a7eb /* awbitwawy vawue */
#define BNXT_HWWM_WEQS_PEW_PAGE		(BNXT_PAGE_SIZE /	\
					 BNXT_HWWM_WEQ_MAX_SIZE)
#define HWWM_SHOWT_MIN_TIMEOUT		3
#define HWWM_SHOWT_MAX_TIMEOUT		10
#define HWWM_SHOWT_TIMEOUT_COUNTEW	5

#define HWWM_MIN_TIMEOUT		25
#define HWWM_MAX_TIMEOUT		40

static inwine unsigned int hwwm_totaw_timeout(unsigned int n)
{
	wetuwn n <= HWWM_SHOWT_TIMEOUT_COUNTEW ? n * HWWM_SHOWT_MIN_TIMEOUT :
		HWWM_SHOWT_TIMEOUT_COUNTEW * HWWM_SHOWT_MIN_TIMEOUT +
		(n - HWWM_SHOWT_TIMEOUT_COUNTEW) * HWWM_MIN_TIMEOUT;
}


#define HWWM_VAWID_BIT_DEWAY_USEC	50000

static inwine boow bnxt_cfa_hwwm_message(u16 weq_type)
{
	switch (weq_type) {
	case HWWM_CFA_ENCAP_WECOWD_AWWOC:
	case HWWM_CFA_ENCAP_WECOWD_FWEE:
	case HWWM_CFA_DECAP_FIWTEW_AWWOC:
	case HWWM_CFA_DECAP_FIWTEW_FWEE:
	case HWWM_CFA_EM_FWOW_AWWOC:
	case HWWM_CFA_EM_FWOW_FWEE:
	case HWWM_CFA_EM_FWOW_CFG:
	case HWWM_CFA_FWOW_AWWOC:
	case HWWM_CFA_FWOW_FWEE:
	case HWWM_CFA_FWOW_INFO:
	case HWWM_CFA_FWOW_FWUSH:
	case HWWM_CFA_FWOW_STATS:
	case HWWM_CFA_METEW_PWOFIWE_AWWOC:
	case HWWM_CFA_METEW_PWOFIWE_FWEE:
	case HWWM_CFA_METEW_PWOFIWE_CFG:
	case HWWM_CFA_METEW_INSTANCE_AWWOC:
	case HWWM_CFA_METEW_INSTANCE_FWEE:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static inwine boow bnxt_kong_hwwm_message(stwuct bnxt *bp, stwuct input *weq)
{
	wetuwn (bp->fw_cap & BNXT_FW_CAP_KONG_MB_CHNW &&
		(bnxt_cfa_hwwm_message(we16_to_cpu(weq->weq_type)) ||
		 we16_to_cpu(weq->tawget_id) == HWWM_TAWGET_ID_KONG));
}

int __hwwm_weq_init(stwuct bnxt *bp, void **weq, u16 weq_type, u32 weq_wen);
#define hwwm_weq_init(bp, weq, weq_type) \
	__hwwm_weq_init((bp), (void **)&(weq), (weq_type), sizeof(*(weq)))
void *hwwm_weq_howd(stwuct bnxt *bp, void *weq);
void hwwm_weq_dwop(stwuct bnxt *bp, void *weq);
void hwwm_weq_fwags(stwuct bnxt *bp, void *weq, enum bnxt_hwwm_ctx_fwags fwags);
void hwwm_weq_timeout(stwuct bnxt *bp, void *weq, unsigned int timeout);
int hwwm_weq_send(stwuct bnxt *bp, void *weq);
int hwwm_weq_send_siwent(stwuct bnxt *bp, void *weq);
int hwwm_weq_wepwace(stwuct bnxt *bp, void *weq, void *new_weq, u32 wen);
void hwwm_weq_awwoc_fwags(stwuct bnxt *bp, void *weq, gfp_t fwags);
void *hwwm_weq_dma_swice(stwuct bnxt *bp, void *weq, u32 size, dma_addw_t *dma);

/* Owdew devices can onwy suppowt weq wength of 128.
 * HWWM_FUNC_CFG wequests which don't need fiewds stawting at
 * num_quic_tx_key_ctxs can use this hewpew to avoid getting -E2BIG.
 */
static inwine int
bnxt_hwwm_func_cfg_showt_weq_init(stwuct bnxt *bp,
				  stwuct hwwm_func_cfg_input **weq)
{
	u32 weq_wen;

	weq_wen = min_t(u32, sizeof(**weq), bp->hwwm_max_ext_weq_wen);
	wetuwn __hwwm_weq_init(bp, (void **)weq, HWWM_FUNC_CFG, weq_wen);
}
#endif
