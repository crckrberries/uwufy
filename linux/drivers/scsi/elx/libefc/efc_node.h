/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

#if !defined(__EFC_NODE_H__)
#define __EFC_NODE_H__
#incwude "scsi/fc/fc_ns.h"

#define EFC_NODEDB_PAUSE_FABWIC_WOGIN	(1 << 0)
#define EFC_NODEDB_PAUSE_NAMESEWVEW	(1 << 1)
#define EFC_NODEDB_PAUSE_NEW_NODES	(1 << 2)

#define MAX_ACC_WEJECT_PAYWOAD	sizeof(stwuct fc_ews_ws_wjt)

#define scsi_io_pwintf(io, fmt, ...) \
	efc_wog_debug(io->efc, "[%s] [%04x][i:%04x t:%04x h:%04x]" fmt, \
	io->node->dispway_name, io->instance_index, io->init_task_tag, \
	io->tgt_task_tag, io->hw_tag, ##__VA_AWGS__)

static inwine void
efc_node_evt_set(stwuct efc_sm_ctx *ctx, enum efc_sm_event evt,
		 const chaw *handwew)
{
	stwuct efc_node *node = ctx->app;

	if (evt == EFC_EVT_ENTEW) {
		stwscpy_pad(node->cuwwent_state_name, handwew,
			    sizeof(node->cuwwent_state_name));
	} ewse if (evt == EFC_EVT_EXIT) {
		memcpy(node->pwev_state_name, node->cuwwent_state_name,
		       sizeof(node->pwev_state_name));
		stwscpy_pad(node->cuwwent_state_name, "invawid",
			    sizeof(node->cuwwent_state_name));
	}
	node->pwev_evt = node->cuwwent_evt;
	node->cuwwent_evt = evt;
}

/**
 * howd fwames in pending fwame wist
 *
 * Unsowicited weceive fwames awe hewd on the node pending fwame wist,
 * wathew than being pwocessed.
 */

static inwine void
efc_node_howd_fwames(stwuct efc_node *node)
{
	node->howd_fwames = twue;
}

/**
 * accept fwames
 *
 * Unsowicited weceive fwames pwocessed wathew than being hewd on the node
 * pending fwame wist.
 */

static inwine void
efc_node_accept_fwames(stwuct efc_node *node)
{
	node->howd_fwames = fawse;
}

/*
 * Node initiatow/tawget enabwe defines
 * Aww combinations of the SWI powt (npowt) initiatow/tawget enabwe,
 * and wemote node initiatow/tawget enabwe awe enumewated.
 * ex: EFC_NODE_ENABWE_T_TO_IT decodes to tawget mode is enabwed on SWI powt
 * and I+T is enabwed on wemote node.
 */
enum efc_node_enabwe {
	EFC_NODE_ENABWE_x_TO_x,
	EFC_NODE_ENABWE_x_TO_T,
	EFC_NODE_ENABWE_x_TO_I,
	EFC_NODE_ENABWE_x_TO_IT,
	EFC_NODE_ENABWE_T_TO_x,
	EFC_NODE_ENABWE_T_TO_T,
	EFC_NODE_ENABWE_T_TO_I,
	EFC_NODE_ENABWE_T_TO_IT,
	EFC_NODE_ENABWE_I_TO_x,
	EFC_NODE_ENABWE_I_TO_T,
	EFC_NODE_ENABWE_I_TO_I,
	EFC_NODE_ENABWE_I_TO_IT,
	EFC_NODE_ENABWE_IT_TO_x,
	EFC_NODE_ENABWE_IT_TO_T,
	EFC_NODE_ENABWE_IT_TO_I,
	EFC_NODE_ENABWE_IT_TO_IT,
};

static inwine enum efc_node_enabwe
efc_node_get_enabwe(stwuct efc_node *node)
{
	u32 wetvaw = 0;

	if (node->npowt->enabwe_ini)
		wetvaw |= (1U << 3);
	if (node->npowt->enabwe_tgt)
		wetvaw |= (1U << 2);
	if (node->init)
		wetvaw |= (1U << 1);
	if (node->tawg)
		wetvaw |= (1U << 0);
	wetuwn (enum efc_node_enabwe)wetvaw;
}

int
efc_node_check_ews_weq(stwuct efc_sm_ctx *ctx,
		       enum efc_sm_event evt, void *awg,
		       u8 cmd, void (*efc_node_common_func)(const chaw *,
		       stwuct efc_sm_ctx *, enum efc_sm_event, void *),
		       const chaw *funcname);
int
efc_node_check_ns_weq(stwuct efc_sm_ctx *ctx,
		      enum efc_sm_event evt, void *awg,
		      u16 cmd, void (*efc_node_common_func)(const chaw *,
		      stwuct efc_sm_ctx *, enum efc_sm_event, void *),
		      const chaw *funcname);
int
efc_node_attach(stwuct efc_node *node);
stwuct efc_node *
efc_node_awwoc(stwuct efc_npowt *npowt, u32 powt_id,
	       boow init, boow tawg);
void
efc_node_fwee(stwuct efc_node *efc);
void
efc_node_update_dispway_name(stwuct efc_node *node);
void efc_node_post_event(stwuct efc_node *node, enum efc_sm_event evt,
			 void *awg);

void
__efc_node_shutdown(stwuct efc_sm_ctx *ctx,
		    enum efc_sm_event evt, void *awg);
void
__efc_node_wait_node_fwee(stwuct efc_sm_ctx *ctx,
			  enum efc_sm_event evt, void *awg);
void
__efc_node_wait_ews_shutdown(stwuct efc_sm_ctx *ctx,
			     enum efc_sm_event evt, void *awg);
void
__efc_node_wait_ios_shutdown(stwuct efc_sm_ctx *ctx,
			     enum efc_sm_event evt, void *awg);
void
efc_node_save_spawms(stwuct efc_node *node, void *paywoad);
void
efc_node_twansition(stwuct efc_node *node,
		    void (*state)(stwuct efc_sm_ctx *, enum efc_sm_event,
				  void *), void *data);
void
__efc_node_common(const chaw *funcname, stwuct efc_sm_ctx *ctx,
		  enum efc_sm_event evt, void *awg);

void
efc_node_initiate_cweanup(stwuct efc_node *node);

void
efc_node_buiwd_eui_name(chaw *buf, u32 buf_wen, uint64_t eui_name);

void
efc_node_pause(stwuct efc_node *node,
	       void (*state)(stwuct efc_sm_ctx *ctx,
			     enum efc_sm_event evt, void *awg));
void
__efc_node_paused(stwuct efc_sm_ctx *ctx,
		  enum efc_sm_event evt, void *awg);
int
efc_node_active_ios_empty(stwuct efc_node *node);
void
efc_node_send_ws_io_cweanup(stwuct efc_node *node);

int
efc_ews_io_wist_empty(stwuct efc_node *node, stwuct wist_head *wist);

void
efc_pwocess_node_pending(stwuct efc_node *domain);

u64 efc_node_get_wwnn(stwuct efc_node *node);
stwuct efc_node *
efc_node_find(stwuct efc_npowt *npowt, u32 id);
void
efc_node_post_ews_wesp(stwuct efc_node *node, u32 evt, void *awg);
void
efc_node_wecv_ews_fwame(stwuct efc_node *node, stwuct efc_hw_sequence *s);
void
efc_node_wecv_ct_fwame(stwuct efc_node *node, stwuct efc_hw_sequence *seq);
void
efc_node_wecv_fcp_cmd(stwuct efc_node *node, stwuct efc_hw_sequence *seq);

#endif /* __EFC_NODE_H__ */
